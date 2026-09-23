// D2Server module implementation
// Bridges the decompiled D2Server code to the D2MOO module interface
// and provides a working server implementation on Linux

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include "d2server.h"

// Force stdout/stderr to be line-buffered for immediate output
#include <unistd.h>
static struct _InitFlush { _InitFlush() { setvbuf(stdout, NULL, _IOLBF, 0); setvbuf(stderr, NULL, _IOLBF, 0); } } _initFlush;
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <atomic>
#include "d2gs_huffman.h"
#include "d2gs_burst_data.h"

// ============================================================
// D2 game-protocol support (packet framing)
// ------------------------------------------------------------
// The D2 wire protocol is self-framing: the first byte of every
// packet is its header, and the total packet size is derived from
// a size table (fixed sizes) or from embedded length fields
// (variable-size packets such as 0x14/0x15 chat and 0x6B save data).
// libD2Net exports exactly this parser, and D2Server already links
// D2Net, so we reuse SERVER_GetClientPacketSize() rather than
// duplicating the table. Note: it has C++ linkage (mangled symbol
// _Z26SERVER_GetClientPacketSizeP18D2PacketBufferStrcjPi).
#include <Packet.h>

extern int32_t SERVER_GetClientPacketSize(D2PacketBufferStrc* pBuffer, uint32_t nBufferSize, int32_t* pSize);

// Size of the fixed 0xFF (frame/tick) packet and other protocol constants.
// NOTE: the accept greeting is NOT a bare 0xAF byte.  The reference BNet
// game server (D2GS trunk, both 1.11b and 1.13c) sends GSPacket0xAF =
// { CHAR type=0xAF; CHAR suffix=0x01 } = the 2 bytes AF 01 on accept.
constexpr uint8_t  D2GS_HDR_COMPRESSNEG     = 0xAF; // S->C compression negotiate (type byte)
constexpr uint8_t  D2GS_SUFFIX_COMPRESSNEG  = 0x01; // ... suffix byte (GSPacket0xAF.suffix)
constexpr uint8_t  D2GS_HDR_GAMELOGON       = 0x68; // C->S game logon (GSPacket0x68, 37 bytes)
constexpr uint8_t  D2GS_HDR_GAMELOADING     = 0x00; // S->C game loading (1.14 accept reply, empty)
constexpr uint8_t  D2GS_HDR_ENTERGAME14     = 0x6B; // C->S JOINGAME (1.14, bare 1-byte header)
constexpr uint8_t  D2GS_HDR_ENTERGAME_LEGACY= 0x6A; // C->S enter game env (1.10-era id; not sent by 1.14)
constexpr uint8_t  D2GS_HDR_PING            = 0x6D; // C->S ping (13 bytes: u32 tick, u32 delay, u32 warden)
constexpr uint8_t  D2GS_HDR_PONG            = 0x8F; // S->C pong (33 bytes: 8F + 32 zero bytes)
constexpr uint8_t  D2GS_HDR_CHAT           = 0x14; // C->S chat (also 0x15)
constexpr uint8_t  D2GS_HDR_LEAVEGAME      = 0x69; // C->S leave game
constexpr uint32_t D2GS_MAX_PACKET         = MAX_MSG_SIZE; // largest legal frame

// ============================================================
// Module interface types (must match Main.h)
// ============================================================

enum D2_MODULES {
    MODULE_NONE,
    MODULE_CLIENT,
    MODULE_SERVER,
    MODULE_MULTIPLAYER,
    MODULE_LAUNCHER,
#if D2_HAS_MULTILAN
    MODULE_MULTILAN,
#endif
    MODULE_EXPAND,
    D2_MODULES_COUNT
};

// ============================================================
// Global server state
// ============================================================

static std::atomic<bool> g_bServerRunning{false};
static std::atomic<bool> g_bShutdownRequested{false};
static int g_nServerPort = 6113;
static int g_nGamePort = 4000;
static int g_nListenSocket = -1;
static std::mutex g_PlayerListMutex;
static std::mutex g_GameListMutex;

// Player connection info
struct PlayerConnection {
    int sock;
    uint32_t playerId;
    uint32_t gameId;
    uint32_t playerGUID;      // unit GUID assigned by the game server
    char playerName[32];
    char accountName[32];
    bool authenticated;       // GAMELOGON (0x68) accepted
    bool inGame;              // entered game environment (0x6A)
    struct sockaddr_in addr;
    uint8_t recvBuf[8192];    // partial-frame accumulation buffer
    uint32_t recvLen;         // valid bytes in recvBuf
    // 1.14 D2GS_UPLOADSAVE (0x6C): the retail client uploads its local .d2s
    // save in chunks (1B id + 1B chunkLen + 4B fullSize + chunk + 1B term)
    // after GAMELOADING, then sends D2GS_JOINGAME (0x6B).  We accumulate the
    // save so the session trace shows it complete and can seed an in-game
    // state later.
    uint8_t saveBuf[4096];    // received .d2s bytes (concatenated chunks)
    uint32_t saveFull;        // full save size announced by the client
    uint32_t saveGot;         // bytes received so far
    bool     saveComplete;    // whole save arrived
    bool     joinReplySent;   // game-entry burst already sent for this join
    // Diagnostics (server-side connect tracing; the real client is
    // un-instrumentable, so everything observed is logged from here)
    uint64_t totalRecvBytes;  // all bytes received on this socket
    uint64_t totalSendBytes;  // all bytes sent on this socket
    uint32_t framesRecv;      // complete client->server frames dispatched
    bool sawFirstRecv;        // has the client sent anything after 0xAF?
    bool recvStallLogged;     // logged that a partial frame awaits more data
};

// Game instance info
struct GameInstance {
    uint32_t gameId;
    char gameName[32];
    char gamePass[16];
    uint32_t maxPlayers;
    uint32_t currentPlayers;
    bool active;
    time_t createTime;
};

static std::map<uint32_t, PlayerConnection> g_Players;
static std::map<uint32_t, GameInstance> g_Games;
static uint32_t g_NextPlayerId = 1;
static uint32_t g_NextGameId = 1;

// Number of game worker threads (each player socket is owned by exactly one worker)
static const int kNumWorkers = 2;

// ============================================================
// Forward declarations for decompiled functions
// Use d2server.h declarations where available
// ============================================================

extern "C" {
    // Server core — defined in d2server.cpp
    extern int Server_MainEntry(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nCmdShow);

    // Game data — defined in d2server.cpp
    extern void GameData_PoolInit(unsigned int* param_1);
    extern void GameDataPool_DetachAll(int* param_1);
}

// Functions declared in d2server.h — use those declarations (C++ linkage)
// Perf functions not in header — provide forward declarations
extern void Perf_InitSystem(void);
extern void Perf_InitFrameTimer(unsigned int);
extern void Perf_SnapshotCounter(void);

// ============================================================
// Linux-compatible Windows API stubs
// Only define if not already provided by d2server.h or libwin
// ============================================================

#ifndef _WIN32
// CreateDialogParamA - simulated on Linux
void* CreateDialogParamA(void* hInstance, const char* templateName,
                          void* hWndParent, void* dlgProc, int param) {
    printf("[D2Server] CreateDialogParamA: template=%p parent=%p\n",
           (void*)templateName, hWndParent);
    static int fakeHwnd = 0x12345;
    return (void*)&fakeHwnd;
}

int PeekMessageA(void* msg, void* hwnd, int min, int max, int remove) { return 0; }
int GetMessageA(void* msg, void* hwnd, int min, int max) {
    while (!g_bShutdownRequested) usleep(10000);
    return 0;
}
int IsDialogMessageA(void* hwnd, void* msg) { return 0; }
int TranslateMessage(void* msg) { return 0; }
int DispatchMessageA(void* msg) { return 0; }
void* CreateThread(void* attr, unsigned stackSize, void* startRoutine,
                    void* arg, unsigned flags, void* threadId) {
    return (void*)1;
}
long InterlockedIncrement(long* val) { return __sync_add_and_fetch(val, 1); }
long InterlockedDecrement(long* val) { return __sync_sub_and_fetch(val, 1); }
void DeleteCriticalSection(void* cs) {}
void __amsg_exit(int code) {
    printf("[D2Server] Fatal error: __amsg_exit(%d)\n", code);
    exit(code);
}
#endif /* !_WIN32 */

// ============================================================
// D2 protocol dispatch (client <-> game server)
// ------------------------------------------------------------
// Implements the 1.14d accept sequence verified against the
// MephisTools/diablo2-protocol reference (bot flow) and against real
// D2GS 1.13/1.14 S->C captures in /tmp/opencode/diablo2-protocol:
//
//   S->C  [0xAF 0x01] compression negotiate (GSPacket0xAF, 2 raw bytes)
//   C->S  [0x68]      GAMELOGON (37 bytes)
//   S->C  [00]        GAMELOADING (Huffman frame; the 1.14 client awaits it)
//   S->C  [0x01]      GAMEFLAGS (10 bytes, difficulty/expansion/ladder)
//   C->S  [0x6C]      UPLOADSAVE: the client uploads its local .d2s in
//                     chunks (1B id + 1B chunkLen + 4B fullSize + chunk
//                     + 1B terminator), interleaved with [0x6D] PINGs
//   C->S  [0x6B]      JOINGAME (bare 1-byte header; "enter game environment")
//   S->C              PONG (to each PING) + the world-entry burst
//                     (ASSIGNPLAYER/skills/states -> ITEM_WORLD/OWNED ->
//                     SETSTATE/PLAYER_JOIN/HPMPUPDATE/NPC_MOVE), replayed
//                     from a real 1.14d capture (d2gs_burst_data.h)
//   ...   game packets flow after that
//
// Real D2GS compress-negotiates with 0xAF 0x01 and then sends every
// subsequent S->C packet as a Huffman frame (verified: the first frame
// after the greeting in a real capture is already compressed).  So we
// frame all S->C packets with the D2 Huffman codec in d2gs_huffman.*.
// Client->server stays bare and self-framing.
//
// Frames are self-framing (first byte = header, size from the
// libD2Net size table). Subset frames with known sizes (0x68/0x6B/0x6D)
// are special-cased because the 1.10-era libD2Net table does not model
// the 1.14 accept packets.
// ============================================================

// GSPacket0x68 (D2GS/trunk.h) — the real GAMELOGON the retail client sends.
// 37 bytes total: 1 + 4 + 2 + 1 + 4 + 4 + 4 + 1 + 16.
#pragma pack(push, 1)
struct D2ServerPacketGameLogon {
    uint8_t  nHeader;      // 0x68
    uint32_t dwHash;       // session hash
    uint16_t wToken;       // join token
    uint8_t  bCharId;      // character id
    uint32_t dwVersion;    // client/game version
    uint32_t dwReserved1;
    uint32_t dwReserved2;
    uint8_t  bReserved;
    char     szCharName[16];
};
#pragma pack(pop)
static_assert(sizeof(D2ServerPacketGameLogon) == 37, "GAMELOGON packet must be 37 bytes");

static const char* D2Server_PacketName(uint8_t nHeader) {
    switch (nHeader) {
    case 0x01: return "MoveToLocation";
    case 0x02: return "MoveToEntity";
    case 0x03: return "WalkToLocation";
    case 0x04: return "WalkToEntity";
    case 0x05: return "LeftSkillOnLocation";
    case 0x06: return "LeftSkillOnEntity";
    case 0x07: return "LeftSkillOnEntityEx";
    case 0x08: return "LeftSkillOnLocationEx";
    case 0x09: return "LeftSkillOnEntityEx2";
    case 0x0A: return "LeftSkillOnEntityEx3";
    case 0x0C: return "RightSkillOnLocation";
    case 0x0D: return "RightSkillOnEntity";
    case 0x0E: return "RightSkillOnEntityEx";
    case 0x0F: return "RightSkillOnLocationEx";
    case 0x12: return "UnloadComplete";
    case 0x14: return "Chat";
    case 0x15: return "ChatEx";
    case 0x16: return "OwnedItemOperation";
    case 0x17: return "PickupItemToCursor";
    case 0x18: return "SwapItemInContainer";
    case 0x19: return "DropItemToFloor";
    case 0x20: return "GoldOperation";
    case 0x23: return "QuestOperation";
    case 0x26: return "PartyOperation";
    case 0x27: return "TradeStartRequest";
    case 0x2B: return "GameAction";
    case 0x42: return "CharacterSave";
    case 0x44: return "WarpRequest";
    case 0x51: return "SkillLevelUp";
    case 0x58: return "QuestState";
    case 0x59: return "MoveToTarget";
    case 0x66: return "GameInfo";
    case 0x67: return "JoinWithToken";
    case 0x68: return "GAMELOGON";
    case 0x69: return "LEAVEGAME";
    case 0x6A: return "ENTERGAMEENV(legacy)";
    case 0x6B: return "JOINGAME";
    case 0x6C: return "UPLOADSAVE";
    case 0x6D: return "PING";
    case 0xFF: return "Tick/Frame";
    default:   return "Unknown";
    }
}

// Send a raw frame to a player (frames are already fully formed)
static void D2Server_HexDump(const char* szWhere, uint32_t playerId, const uint8_t* pData, size_t nLen) {
    printf("[D2Server] %s (p%u, %zu bytes):", szWhere, playerId, nLen);
    // Log the whole frame up to a sane cap so handshakes (short) are fully
    // visible while long payloads (chats/saves) stay bounded.  Raised to 1024
    // so a 1.14 client's full game-data request (a ~262-byte burst) is visible.
    size_t nShown = nLen < 1024 ? nLen : 1024;
    for (size_t i = 0; i < nShown; i++) {
        printf(" %02X", pData[i]);
    }
    if (nLen > nShown) {
        printf(" ... (+%zu more)", nLen - nShown);
    }
    printf("\n");
    fflush(stdout);
}

// Send a raw frame to a player (frames are already fully formed)
static void D2Server_SendFrame(PlayerConnection& player, const uint8_t* pData, size_t nLen) {
    if (player.sock < 0 || nLen == 0) {
        return;
    }
    D2Server_HexDump("send", player.playerId, pData, nLen);
    player.totalSendBytes += nLen;
    ssize_t nSent = send(player.sock, pData, nLen, MSG_NOSIGNAL);
    if (nSent < 0) {
        printf("[D2Server] send to player %u failed: %s\n", player.playerId, strerror(errno));
    } else if ((size_t)nSent != nLen) {
        printf("[D2Server] send to player %u short write %zd/%zu\n",
               player.playerId, nSent, nLen);
    }
}

// Compress + frame + send an S->C packet after the 0xAF compression
// negotiation.  Real D2GS sends every post-greeting packet as a Huffman
// frame (verified against real captures), so this is the default.  Set
// D2GS_COMPRESS=0 to emit the raw len+1-prefixed frame instead (used to
// A/B-test the accept sequence against the retail client).
static bool D2Server_WantCompression() {
    static const int s_nCompress = [] {
        const char* p = getenv("D2GS_COMPRESS");
        return p ? atoi(p) : 1;
    }();
    return s_nCompress != 0;
}

static void D2Server_SendCompressed(PlayerConnection& player, const uint8_t* pPayload, size_t nPayloadLen) {
    if (!D2Server_WantCompression()) {
        uint8_t raw[4096 + 1];
        if (nPayloadLen + 1 > sizeof(raw)) {
            printf("[D2Server] Player %u raw frame too large (%zu payload bytes)\n",
                   player.playerId, nPayloadLen);
            return;
        }
        raw[0] = (uint8_t)(nPayloadLen + 1);
        memcpy(raw + 1, pPayload, nPayloadLen);
        D2Server_SendFrame(player, raw, nPayloadLen + 1);
        return;
    }
    uint8_t compressed[4096];
    uint8_t frame[4096 + 2];
    int nComp = d2gs::Huffman_Compress(pPayload, (int)nPayloadLen, compressed, (int)sizeof(compressed));
    if (nComp < 0) {
        printf("[D2Server] Player %u compress failed for %zu-byte packet\n",
               player.playerId, nPayloadLen);
        return;
    }
    int nFrame = d2gs::Huffman_WriteFrame(frame, (int)sizeof(frame), compressed, nComp);
    if (nFrame < 0) {
        printf("[D2Server] Player %u frame too large (%d compressed bytes)\n", player.playerId, nComp);
        return;
    }
    D2Server_SendFrame(player, frame, (size_t)nFrame);
}

// Reply to D2GS_JOINGAME (0x6B): send the real world-entry burst captured
// from a 1.14d D2GS S->C session (d2gs_sc.dump frames #2..#9, with the
// captured character renamed to the one that just logged on).  This is the
// data a real server streams once the client finishes uploading its save:
//   ASSIGNPLAYER (own char: guid/name/pos) + skills/states/stat bitstreams,
//   ITEM_WORLD / ITEM_OWNED (ground + owned items),
//   MAPREVEAL/OBJECTSTATE/SETSTATE (world state),
//   PLAYER_JOIN + EVENTMESSAGES (other players),
//   HPMPUPDATE (life/mana), NPC_MOVE (monster pack positions).
// Each payload is re-compressed + Huffman-framed, exactly like the real
// server frames it.  No LOADSUCCESSFUL (0x02): the real session never sends
// it.  The client is kept alive afterwards by PING->PONG.
static void D2Server_SendEntryBurst(PlayerConnection& player) {
    // Set D2GS_SENDBURST=0 to skip the burst entirely (A/B-test the reply).
    static const bool s_nSendBurst = [] {
        const char* p = getenv("D2GS_SENDBURST");
        return p ? atoi(p) != 0 : true;
    }();
    if (!s_nSendBurst) {
        printf("[D2Server] Player %u game-entry burst SKIPPED (D2GS_SENDBURST=0)\n",
               player.playerId);
        return;
    }
    printf("[D2Server] Player %u sending real game-entry burst (%zu frames)\n",
           player.playerId, d2gs_entry::kFrameCount);
    for (size_t i = 0; i < d2gs_entry::kFrameCount; i++) {
        const d2gs_entry::BurstFrame& f = d2gs_entry::kFrames[i];
        D2Server_SendCompressed(player, f.data, f.len);
    }
    printf("[D2Server] Player %u game-entry burst complete\n", player.playerId);
}

// Dispatch one complete, validated client->server frame
static void D2Server_DispatchPacket(PlayerConnection& player, const uint8_t* pData, uint32_t nLen) {
    const uint8_t nHeader = pData[0];
    const char* szName = D2Server_PacketName(nHeader);

    player.framesRecv++;
    D2Server_HexDump("recv frame", player.playerId, pData, nLen);

    switch (nHeader) {
    case D2GS_HDR_GAMELOGON: { // 0x68 — GSPacket0x68 GAMELOGON (37 bytes)
        if (player.authenticated) {
            return;
        }
        if (nLen < sizeof(D2ServerPacketGameLogon)) {
            printf("[D2Server] Player %u GAMELOGON too short (%u bytes), ignoring\n",
                   player.playerId, nLen);
            break;
        }
        const D2ServerPacketGameLogon* pLogon = (const D2ServerPacketGameLogon*)pData;
        char szCharName[17] = {};
        memcpy(szCharName, pLogon->szCharName, sizeof(pLogon->szCharName));
        szCharName[sizeof(pLogon->szCharName)] = '\0';
        memcpy(player.playerName, szCharName, sizeof(player.playerName) - 1);
        player.playerName[sizeof(player.playerName) - 1] = '\0';
        printf("[D2Server] Player %u GAMELOGON char='%s' token=%u ver=%u hash=%08X\n",
               player.playerId, szCharName, pLogon->wToken, pLogon->dwVersion, pLogon->dwHash);

        player.authenticated = true;
        player.playerGUID = player.playerId; // assign a game server unit GUID
        printf("[D2Server] Player %u GAMELOGON accepted, GUID=%u\n",
               player.playerId, player.playerGUID);
        // 1.14d accept: the client awaits D2GS_GAMELOADING (0x00) after its
        // GAMELOGON (MephisTools 1.14 flow), then uploads its save and sends
        // D2GS_JOINGAME.  Real D2GS sends this as a Huffman frame: 00 ->
        // compressed 80 -> wire 02 80.  (The old 0x5C STARTGAME reply told
        // a 1.14 client "player #2 left" and deadlocked the accept sequence.)
        const uint8_t nLoading = D2GS_HDR_GAMELOADING;
        D2Server_SendCompressed(player, &nLoading, 1);

        // Real D2GS follows GAMELOADING with D2GS_GAMEFLAGS (0x01) as the
        // first setup payload (see the real S->C dump: right after the AF 01
        // greeting comes `01 02 04 20 10 00 01 00 00 02`, whose Huffman
        // frame is 07 75 D0 1D 9A 5F 5C).  Without it a 1.14d retail client
        // accepts the handshake but never learns the game's flags and stays
        // parked on the loading screen.  Send the exact real bytes (difficulty,
        // hardcore, expansion, ladder).  Set D2GS_SENDFLAGS=0 to skip.
        static const bool s_nSendFlags = [] {
            const char* p = getenv("D2GS_SENDFLAGS");
            return p ? atoi(p) != 0 : true;
        }();
        if (s_nSendFlags) {
            static const uint8_t nGameFlags[10] = {
                0x01, 0x02, 0x04, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x02
            };
            D2Server_SendCompressed(player, nGameFlags, sizeof(nGameFlags));
        }
        break;
    }
    case D2GS_HDR_PING: { // 0x6D — client heartbeat (13 bytes: u32 tick, u32 delay, u32 warden)
        uint32_t nTick = 0, nDelay = 0, nWarden = 0;
        if (nLen >= 13) {
            nTick   = *(const uint32_t*)(pData + 1);
            nDelay  = *(const uint32_t*)(pData + 5);
            nWarden = *(const uint32_t*)(pData + 9);
        }
        printf("[D2Server] Player %u PING tick=%u delay=%u warden=%u\n",
               player.playerId, nTick, nDelay, nWarden);
        // Reply D2GS_PONG (0x8F + 32 zero bytes) as a Huffman frame; this is
        // exactly the real wire form seen in captures: 07 1f 7f ff ff ff c0.
        uint8_t pong[33] = {};
        pong[0] = D2GS_HDR_PONG;
        D2Server_SendCompressed(player, pong, sizeof(pong));
        break;
    }
    case D2GS_HDR_ENTERGAME14: { // 0x6B — D2GS_JOINGAME (1.14, bare 1-byte header)
        player.inGame = true;
        printf("[D2Server] Player %u JOINGAME (1.14, gameId=%u, save=%u/%u bytes)",
               player.playerId, player.gameId, player.saveGot, player.saveFull);
        if (player.saveComplete) {
            printf(" [save upload complete]\n");
        } else if (player.saveFull > 0) {
            printf(" [upload incomplete!]\n");
        } else {
            printf("\n");
        }
        // Reply with the real game-entry burst once (the world/player data
        // the client needs to leave the loading screen).  The client keeps
        // the session alive with PING->PONG afterwards.
        if (!player.joinReplySent) {
            player.joinReplySent = true;
            D2Server_SendEntryBurst(player);
        }
        break;
    }
    case 0x6C: { // D2GS_UPLOADSAVE (1.14): client uploads its .d2s in chunks
        // Frame layout: id(1) + chunkLen(1) + fullSize(4) + chunk[chunkLen] + term(1)
        if (nLen < 7) {
            printf("[D2Server] Player %u UPLOADSAVE too short (%u bytes)\n",
                   player.playerId, nLen);
            break;
        }
        const uint32_t nChunkSize = pData[1];
        const uint32_t nFullSize = *(const uint32_t*)(pData + 2);
        const uint32_t nDataLen = nLen - 7; // equals nChunkSize on a clean frame
        const uint8_t nTerm = pData[nLen - 1];
        if (player.saveFull == 0) {
            player.saveFull = nFullSize;
            printf("[D2Server] Player %u UPLOADSAVE start: fullSize=%u bytes\n",
                   player.playerId, nFullSize);
        }
        if (player.saveGot + nDataLen > sizeof(player.saveBuf)) {
            printf("[D2Server] Player %u UPLOADSAVE overflow (%u+%u > %zu), ignoring chunk\n",
                   player.playerId, player.saveGot, nDataLen, sizeof(player.saveBuf));
            break;
        }
        memcpy(player.saveBuf + player.saveGot, pData + 6, nDataLen);
        player.saveGot += nDataLen;
        printf("[D2Server] Player %u UPLOADSAVE chunk: %u/%u bytes (term=%02X)\n",
               player.playerId, player.saveGot, player.saveFull, nTerm);
        if (player.saveFull > 0 && player.saveGot >= player.saveFull) {
            player.saveComplete = true;
            printf("[D2Server] Player %u SAVE UPLOAD COMPLETE (%u bytes):",
                   player.playerId, player.saveGot);
            const uint32_t nShow = player.saveGot < 32 ? player.saveGot : 32;
            for (uint32_t i = 0; i < nShow; i++) {
                printf(" %02X", player.saveBuf[i]);
            }
            printf("\n");
        }
        break;
    }
    case D2GS_HDR_ENTERGAME_LEGACY: { // 0x6A — 1.10-era id (not sent by 1.14)
        if (!player.inGame) {
            player.inGame = true;
        }
        printf("[D2Server] Player %u legacy 0x6A enter-game (ignored, inGame=%d)\n",
               player.playerId, player.inGame ? 1 : 0);
        break;
    }
    case D2GS_HDR_CHAT:      // 0x14 — chat message (variable: msgType, lang, string)
    case 0x15: {             // 0x15 — chat with name list
        if (nLen >= 4) {
            // message text begins at offset 3 and is NUL terminated
            const uint8_t nMsgType = pData[1];
            const uint8_t nLang = pData[2];
            const char* szMsg = (const char*)(pData + 3);
            printf("[D2Server] Player %u chat(type=%u lang=%u): \"%s\"\n",
                   player.playerId, nMsgType, nLang, szMsg);
        } else {
            printf("[D2Server] Player %u %s (short frame, %u bytes)\n",
                   player.playerId, szName, nLen);
        }
        break;
    }
    case D2GS_HDR_LEAVEGAME: { // 0x69 — client leaves the game
        printf("[D2Server] Player %u LEFT GAME (state: auth=%d inGame=%d)\n",
               player.playerId, player.authenticated ? 1 : 0, player.inGame ? 1 : 0);
        player.inGame = false;
        break;
    }
    case 0x66: { // 0x66 — game info: client name at offset 0x15, game flags at 0x27
        if (nLen >= 0x2B) {
            const char* szClientName = (const char*)(pData + 0x15);
            printf("[D2Server] Player %u GameInfo: client=\"%s\" gameType=%u class=%u\n",
                   player.playerId, szClientName, pData[0x11], pData[0x12]);
        } else {
            printf("[D2Server] Player %u %s (%u bytes)\n", player.playerId, szName, nLen);
        }
        break;
    }
    case 0x67: { // 0x67 — join with token: client name at offset 0x0D
        if (nLen >= 0x1D) {
            const char* szClientName = (const char*)(pData + 0x0D);
            const uint32_t nTokenId = *(const uint32_t*)(pData + 0x01);
            printf("[D2Server] Player %u JoinWithToken: token=%u client=\"%s\"\n",
                   player.playerId, nTokenId, szClientName);
        } else {
            printf("[D2Server] Player %u %s (%u bytes)\n", player.playerId, szName, nLen);
        }
        break;
    }
    default:
        if (nLen <= 8) {
            printf("[D2Server] Player %u packet 0x%02X %s (%u bytes):",
                   player.playerId, nHeader, szName, nLen);
            for (uint32_t i = 0; i < nLen; i++) {
                printf(" %02X", pData[i]);
            }
            printf("\n");
        } else {
            printf("[D2Server] Player %u packet 0x%02X %s (%u bytes)\n",
                   player.playerId, nHeader, szName, nLen);
        }
        break;
    }
}

// ============================================================
// Server threads
// ============================================================

static void* ServerAcceptThread(void* arg) {
    printf("[D2Server] Accept thread started on game port %d\n", g_nGamePort);

    while (g_bServerRunning && !g_bShutdownRequested) {
        struct pollfd pfd;
        pfd.fd = g_nListenSocket;
        pfd.events = POLLIN;
        pfd.revents = 0;

        int ret = poll(&pfd, 1, 100);
        if (ret > 0 && (pfd.revents & POLLIN)) {
            struct sockaddr_in clientAddr;
            socklen_t addrLen = sizeof(clientAddr);
            int clientSock = accept(g_nListenSocket, (struct sockaddr*)&clientAddr, &addrLen);
            if (clientSock >= 0) {
                printf("[D2Server] New connection from %s:%d\n",
                       inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                PlayerConnection player = {};
                player.sock = clientSock;
                player.playerId = g_NextPlayerId++;
                player.playerGUID = 0;
                player.addr = clientAddr;
                {
                    std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                    g_Players[player.playerId] = player;
                }
                printf("[D2Server] Player %u assigned\n", player.playerId);

                // Step 1 of the D2GS accept sequence: greet the client with
                // GSPacket0xAF = { type=0xAF; suffix=0x01 } (2 bytes),
                // exactly as the reference D2GS trunk sends on accept.
                const uint8_t nGreet[2] = { D2GS_HDR_COMPRESSNEG, D2GS_SUFFIX_COMPRESSNEG };
                D2Server_SendFrame(player, nGreet, sizeof(nGreet));
            }
        }
    }
    printf("[D2Server] Accept thread exiting\n");
    return nullptr;
}

static void* GameWorkerThread(void* arg) {
    // Each worker owns a shard of the players (playerId % kNumWorkers).
    const uintptr_t nWorkerIndex = (uintptr_t)arg % (uintptr_t)kNumWorkers;
    printf("[D2Server] Game worker thread %lu started\n", (unsigned long)nWorkerIndex);

    while (g_bServerRunning && !g_bShutdownRequested) {
        std::vector<struct pollfd> pollFds;
        std::vector<PlayerConnection*> players;

        {
            std::lock_guard<std::mutex> lock(g_PlayerListMutex);
            for (auto& pair : g_Players) {
                // Shard: only this worker touches this player's socket/buffer.
                if (pair.second.sock >= 0 && (uintptr_t)(pair.first % (uint32_t)kNumWorkers) == nWorkerIndex) {
                    struct pollfd pfd;
                    pfd.fd = pair.second.sock;
                    pfd.events = POLLIN;
                    pfd.revents = 0;
                    pollFds.push_back(pfd);
                    players.push_back(&pair.second);
                }
            }
        }

        if (pollFds.empty()) {
            usleep(10000);
            continue;
        }

        int ret = poll(pollFds.data(), pollFds.size(), 100);
        if (ret > 0) {
            for (size_t i = 0; i < pollFds.size(); i++) {
                if (!(pollFds[i].revents & (POLLIN | POLLHUP | POLLERR))) {
                    continue;
                }
                PlayerConnection* player = players[i];
                char buffer[4096];
                ssize_t bytesRead = recv(pollFds[i].fd, buffer, sizeof(buffer), 0);
                if (bytesRead <= 0) {
                    printf("[D2Server] Player %u disconnected (recv=%zd). Stats: "
                           "recv=%llu bytes, send=%llu bytes, frames=%u\n",
                           player->playerId, bytesRead,
                           (unsigned long long)player->totalRecvBytes,
                           (unsigned long long)player->totalSendBytes,
                           player->framesRecv);
                    if (player->recvLen > 0) {
                        printf("[D2Server] Player %u had %u unparsed bytes at disconnect:",
                               player->playerId, player->recvLen);
                        for (uint32_t i = 0; i < player->recvLen && i < 64; i++) {
                            printf(" %02X", player->recvBuf[i]);
                        }
                        printf("\n");
                    }
                    close(pollFds[i].fd);
                    std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                    g_Players.erase(player->playerId);
                    continue;
                }

                if (!player->sawFirstRecv) {
                    player->sawFirstRecv = true;
                    printf("[D2Server] Player %u FIRST CLIENT DATA after 0xAF "
                           "(game protocol begins)\n", player->playerId);
                }
                player->totalRecvBytes += (uint64_t)bytesRead;
                D2Server_HexDump("recv", player->playerId, (const uint8_t*)buffer, (size_t)bytesRead);

                // Accumulate raw bytes; D2 frames are self-framing (header byte
                // selects the size from the libD2Net table), so we may need
                // several recv() calls before a full frame is available.
                if (player->recvLen + (uint32_t)bytesRead > sizeof(player->recvBuf)) {
                    printf("[D2Server] Player %u receive buffer overflow, disconnecting\n",
                           player->playerId);
                    close(pollFds[i].fd);
                    std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                    g_Players.erase(player->playerId);
                    continue;
                }
                memcpy(player->recvBuf + player->recvLen, buffer, bytesRead);
                player->recvLen += (uint32_t)bytesRead;

                // Parse and dispatch every complete frame in the buffer.
                uint32_t nConsumed = 0;
                bool bDisconnected = false;
                while (player->recvLen - nConsumed >= 1) {
                    const uint32_t nAvail = player->recvLen - nConsumed;
                    const uint8_t nHeader = player->recvBuf[nConsumed];

                    // Mirror SERVER_ValidateClientPacket: headers >= 0x70
                    // (except 0xFF) are never legal C->S headers.  A live 1.14d
                    // retail client can transiently misalign our frame splitter
                    // (its 0x6C heartbeat / game-data request have sizes we do
                    // not model), so instead of killing the session we log and
                    // skip one byte to resync.  This keeps the connection alive
                    // long enough to observe the full exchange in the log.
                    if (nHeader >= 0x70 && nHeader != 0xFF) {
                        printf("[D2Server] Player %u unknown header 0x%02X at "
                               "buffer offset %u -- skipping 1 byte to resync\n",
                               player->playerId, nHeader, nConsumed);
                        nConsumed++;
                        uint32_t nSkips = 0;
                        while (nConsumed < player->recvLen &&
                               (player->recvBuf[nConsumed] >= 0x70 && player->recvBuf[nConsumed] != 0xFF)) {
                            nConsumed++;
                            if (++nSkips > 64) {
                                printf("[D2Server] Player %u too many unknown bytes "
                                       "in a row (%u), keeping buffer for later\n",
                                       player->playerId, nSkips);
                                break;
                            }
                        }
                        continue;
                    }

                    int32_t nSize = 0;
                    // The pre-auth GAMELOGON is NOT the 1-byte Clt68 frame the
                    // libD2Net table implies (that entry is for the in-game
                    // context).  D2GS trunk waits for a full GSPacket0x68
                    // (37 bytes) before it considers the accept sequence done.
                    // The same is true of the 1.14 accept packets: 0x6D PING
                    // is a fixed 13-byte frame (u32 tick, u32 delay, u32 warden)
                    // and 0x6B ENTERGAMEENVIRONMENT is a bare 1-byte header.
                    // The 1.10-era libD2Net table models none of those.
                    if (!player->authenticated && nHeader == D2GS_HDR_GAMELOGON) {
                        nSize = (int32_t)sizeof(D2ServerPacketGameLogon);
                        if ((uint32_t)nSize > nAvail) {
                            break; // wait for the rest of the 37-byte logon
                        }
                    } else if (nHeader == D2GS_HDR_PING) {
                        nSize = 13; // 0x6D PING (u32 tick + u32 delay + u32 wardenResponse)
                        if ((uint32_t)nSize > nAvail) {
                            break; // wait for the whole ping
                        }
                    } else if (player->authenticated && nHeader == 0x6C) {
                        // D2GS_UPLOADSAVE (1.14): a real retail client streams
                        // its .d2s in chunks after GAMELOADING.  Frame layout:
                        //   id(1) + chunkLen(1) + fullSize(4) + chunk + term(1)
                        // The legacy libD2Net table sizes 0x6C as 9 bytes,
                        // which fragments the stream -- derive the true size
                        // from the embedded chunk length instead.
                        if (nAvail < 6) {
                            break; // need id+chunkLen+fullSize to size the frame
                        }
                        nSize = 6 + (int32_t)player->recvBuf[nConsumed + 1] + 1;
                        if ((uint32_t)nSize > nAvail) {
                            break; // wait for the whole chunk
                        }
                    } else if (player->authenticated && nHeader == D2GS_HDR_ENTERGAME14) {
                        nSize = 1; // 0x6B ENTERGAMEENVIRONMENT is a bare header in 1.14
                    } else {
                        // D2PacketBufferStrc is data[1976]; our buffer layout matches,
                        // and the function only reads data[0..nAvail-1] (data is the
                        // first member of the struct).
                        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(player->recvBuf + nConsumed);
                        if (!SERVER_GetClientPacketSize(pView, nAvail, &nSize) || nSize <= 0) {
                            // Frame incomplete (variable-size packet) or buffer empty:
                            // wait for more bytes.
                            break;
                        }
                        if ((uint32_t)nSize > nAvail) {
                            // Fixed-size frame not fully received yet.
                            break;
                        }
                    }
                    if ((uint32_t)nSize > D2GS_MAX_PACKET) {
                        printf("[D2Server] Player %u oversized frame %u bytes, disconnecting\n",
                               player->playerId, (uint32_t)nSize);
                        close(pollFds[i].fd);
                        {
                            std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                            g_Players.erase(player->playerId);
                        }
                        bDisconnected = true;
                        break;
                    }

                    D2Server_DispatchPacket(*player, player->recvBuf + nConsumed, (uint32_t)nSize);
                    nConsumed += (uint32_t)nSize;
                }

                // Compact any leftover partial frame (skip if we just dropped the player).
                if (!bDisconnected && nConsumed > 0) {
                    memmove(player->recvBuf, player->recvBuf + nConsumed, player->recvLen - nConsumed);
                    player->recvLen -= nConsumed;
                    player->recvStallLogged = false; // progress: allow re-logging next stall
                }

                // If a complete frame was NOT parsed but bytes are buffered,
                // the server is waiting for more data of a variable-size frame.
                // This is normal transiently, but log it once per arrival so a
                // handshake deadlock (client waits for our 0x5C, we wait for
                // the rest of its packet) is visible in the log.
                if (!bDisconnected && nConsumed == 0 && player->recvLen > 0 && !player->recvStallLogged) {
                    player->recvStallLogged = true;
                    printf("[D2Server] Player %u STALL: %u bytes buffered, waiting for "
                           "rest of frame (header 0x%02X). If this persists the client "
                           "is awaiting a reply we have not sent.\n",
                           player->playerId, player->recvLen, player->recvBuf[0]);
                }
            }
        }
    }
    printf("[D2Server] Game worker thread %lu exiting\n", (unsigned long)nWorkerIndex);
    return nullptr;
}

static void* NetworkListenerThread(void* arg) {
    printf("[D2Server] Network listener thread started on port %d\n", g_nGamePort);

    g_nListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (g_nListenSocket < 0) {
        printf("[D2Server] Failed to create socket: %s\n", strerror(errno));
        return nullptr;
    }

    int opt = 1;
    setsockopt(g_nListenSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(g_nGamePort);

    if (bind(g_nListenSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("[D2Server] Failed to bind to port %d: %s\n", g_nGamePort, strerror(errno));
        close(g_nListenSocket);
        g_nListenSocket = -1;
        return nullptr;
    }

    if (listen(g_nListenSocket, 5) < 0) {
        printf("[D2Server] Failed to listen: %s\n", strerror(errno));
        close(g_nListenSocket);
        g_nListenSocket = -1;
        return nullptr;
    }

    printf("[D2Server] Listening on port %d\n", g_nGamePort);

    while (g_bServerRunning && !g_bShutdownRequested) {
        usleep(100000);
    }

    close(g_nListenSocket);
    g_nListenSocket = -1;
    printf("[D2Server] Network listener thread exiting\n");
    return nullptr;
}

// ============================================================
// Main server loop (Linux)
// ============================================================

static int D2Server_MainLoop(void) {
    printf("[D2Server] Starting D2Server on Linux...\n");
    printf("[D2Server] Game port: %d\n", g_nGamePort);

    g_bServerRunning = true;
    g_bShutdownRequested = false;

    // Initialize server subsystems
    printf("[D2Server] Initializing server subsystems...\n");
    SERVER_Initialize(0, 0);
    SERVER_SetHackListEnabled(1);
    FOG_InitErrorMgr();
    FOG_SetLogPrefix((char*)"D2Server", (char*)"", 0);
    D2Lang_Initialize();

    // Initialize performance counters
    Perf_InitSystem();
    Perf_InitFrameTimer(2);
    Perf_SnapshotCounter();

    printf("[D2Server] Server initialized successfully\n");

    // Launch network threads
    pthread_t listenerThread, acceptThread;
    pthread_create(&listenerThread, nullptr, NetworkListenerThread, nullptr);
    pthread_detach(listenerThread);
    pthread_create(&acceptThread, nullptr, ServerAcceptThread, nullptr);
    pthread_detach(acceptThread);

    // Launch game worker threads (one per shard; each player is owned by
    // the worker matching playerId % kNumWorkers)
    for (int i = 0; i < kNumWorkers; i++) {
        pthread_t workerThread;
        pthread_create(&workerThread, nullptr, GameWorkerThread, (void*)(uintptr_t)i);
        pthread_detach(workerThread);
    }
    printf("[D2Server] Started %d worker threads\n", kNumWorkers);

    // Main loop
    while (g_bServerRunning && !g_bShutdownRequested) {
        usleep(1000);
    }

    // Shutdown
    printf("[D2Server] Shutting down...\n");
    g_bServerRunning = false;
    usleep(100000);

    SERVER_Release();
    D2COMMON_10983();
    D2Lang_Uninitialize();

    printf("[D2Server] Server stopped\n");
    return 0;
}

// ============================================================
// D2ServerInterface - entry point called by Game.D2MOO
// ============================================================

extern "C" {

typedef void*(__stdcall* ModuleInitPointer)(void*);

void* __stdcall D2ServerInterface(void* pCfg) {
    printf("[D2Server] Server module initialized\n");
    printf("[D2Server] Starting server main loop...\n");

    int result = D2Server_MainLoop();

    printf("[D2Server] Server shut down (result=%d)\n", result);
    return (void*)MODULE_NONE;
}

static ModuleInitPointer gInterface = D2ServerInterface;

#ifdef D2MOO_SHARED_LIBS
void* __stdcall QueryInterface() {
    return (void*)&gInterface;
}
#endif

void D2Server_SetPort(int gamePort, int serverPort) {
    g_nGamePort = gamePort;
    g_nServerPort = serverPort;
}

void D2Server_RequestShutdown(void) {
    g_bShutdownRequested = true;
}

int D2Server_IsRunning(void) {
    return g_bServerRunning ? 1 : 0;
}

} // extern "C"
