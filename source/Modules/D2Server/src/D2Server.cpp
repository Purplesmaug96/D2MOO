// D2Server module implementation
// Bridges the decompiled D2Server code to the D2MOO module interface
// and provides a working server implementation on Linux

// GNU feature-test macros: enables EOWNERDEAD / pthread_mutex_consistent for
// the robust host-game state mutex (Linux-only module).
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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
#include <windows.h>

// Force stdout/stderr to be line-buffered for immediate output
#include <unistd.h>
static struct _InitFlush { _InitFlush() { setvbuf(stdout, NULL, _IOLBF, 0); setvbuf(stderr, NULL, _IOLBF, 0); } } _initFlush;
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>
#include <HuffmanCodec.h>
#include "d2gs_burst_data.h"
#include "d2gs_area_data.h"

#if D2GS_ENGINE
// Engine game-server host: interfaces of the decompiled D2Game/D2Common
// modules that the host drives (see Engine_Initialize/Engine_Tick below).
#include <stdarg.h>
#include <D2DataTbls.h>
#include <FogFileIO.h>
#include "EngineHost.h"
#endif

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
extern int32_t SERVER_GetServerPacketSize(D2PacketBufferStrc* pBuffer, uint32_t nBufferSize, int32_t* pSize);

// Fog network-transport shim bridge (libFog, FogNetShim.cpp): registers a
// client so the engine's outbound path (D2NET_10006 -> FOG_10157) can reach
// its socket, and pushes inbound frames into the engine's message lists
// (0=system 0x66-0x6F, 1=in-game <0x66, 2=admin >=0x70) that
// GAME_ProcessNetworkMessages drains each tick.
extern "C" void     D2FOG_RegisterClientConnection(int32_t nClientId, int32_t nSocketFd, uint32_t dwIp);
extern "C" void     D2FOG_UnregisterClientConnection(int32_t nClientId);
extern "C" int32_t  D2FOG_PushClientMessage(int32_t nList, const uint8_t* pData, int32_t nSize);
extern "C" int32_t  D2FOG_EngineFrameCount(int32_t nClientId);
extern "C" void     D2FOG_SetInjectionCallback(void (*pCallback)(int32_t nClientId, int32_t nEngineFrames,
                                                                 const uint8_t* pPayload, int32_t nPayloadLen));

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
    uint32_t engineEpoch;     // host-game incarnation the engine JOIN targeted.
                              // 0 until the JOIN is pushed; compared against
                              // g_engineGameEpoch by D2Server_EnginePush so a
                              // client of a REAPED host game can never have a
                              // message drained into a freed game (the tick
                              // would spin forever in GAME_LockGame's bucket
                              // walk, wedging the whole server).
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
    // Engine-path entry complement (D2GS_ENGINE=1): the engine streams its
    // own act-init burst (3 S->C frames), then the module appends the
    // captured real burst minus the packets the engine already covered, so
    // the client receives the packet types the engine never sends and the
    // post-tail closure (95 PLAYERDATA + 67 MOVENPC).  engineBurstBase is
    // the shim's engine S->C frame count at ENTERGAME; the worker fires the
    // complement once the count has moved past it by the 3 burst frames.
    bool     complementArmed;  // ENTERGAME seen on the engine path
    bool     complementSent;   // complement appended for this join
    bool     complementHeadSent; // mode 3: interleaved head sent after 59-frame
    int32_t  engineBurstBase;  // D2FOG_EngineFrameCount at ENTERGAME
    uint32_t playerUnitGuid;   // engine-assigned unit guid from the 0x59
                               // ASSIGNPLAYER frame the engine forwarded
                               // (per-game value: 1 on a fresh server's first
                               // game, 2+ afterwards). 0 until a 59-frame is
                               // observed by the injection hook.
    // Mode-5 town-NPC spawn anchor: a world coordinate guaranteed to sit
    // inside the client's generated town.  The engine generates its own
    // Rogue Encampment per game (seed carried in its 0x03 GAMEOPENED), so
    // the captured retail NPC spawn coords (x~6284-6396/y~5105-5195) land
    // ~1900 tiles east of the client's map, and every injected 0xAC unit
    // create hard-halts the 0xAC handler's room lookup ("Unable to find
    // room for unit", client SCmd.cpp:316 assert -- level/area resolve, but
    // the act's drlg-generated room boxes sit at the engine's coords).  The
    // anchor is parsed from the engine's own world frame (0x15 MOVEUNIT of
    // the player, else the first 0x51 OBJECTUPDATE) before the closure is
    // built, and the 11 AC spawns / 3 MOVENPCs are placed in a ~24-tile ring
    // around it -- well inside the town's room boxes.
    int32_t  npcAnchorX;       // town tile world coords (parsed from engine)
    int32_t  npcAnchorY;
    bool     npcAnchorValid;
    // Area-transition replay (Rogue Encampment <-> Blood Moor through the
    // west gate) + client position tracking from C->S walk/run targets.
    int16_t  lastMoveX;       // latest client walk/run target (world units)
    int16_t  lastMoveY;
    bool     havePos;         // at least one target has been seen
    uint8_t  areaState;       // 0=init, 1=in town, 2=in the Blood Moor
    uint64_t lastTransMs;     // monotonic ms of the last fired transition
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
// Retail D2Server.dll entry points the startup path calls
// ============================================================
// The decompiled D2Server module (d2server.cpp + d2server_globals.cpp)
// has been removed: of the 562 functions it defined, only the eleven
// below were ever reachable, and none of them did any work.  They are
// kept here so the call sites in D2Server_MainLoop / shutdown keep
// compiling and behaving exactly as before.
//
// FOG_InitErrorMgr and FOG_SetLogPrefix also have definitions in
// libFog (the D2FUNC_DLL_STUB bodies), and SERVER_Initialize /
// SERVER_Release / SERVER_SetHackListEnabled have real retail
// implementations in libD2Net.  These local definitions interpose on
// them or are interposed on, depending on library load order -- that
// is pre-existing behaviour and is preserved deliberately here, since
// dropping the definitions would silently start calling into libD2Net.
// D2Lang_Initialize, D2Lang_Uninitialize and D2COMMON_10983 have no
// implementation in any library, so these are their only definition.

int __cdecl SERVER_Initialize(int a, int b) { (void)a; (void)b; return 0; }
int __cdecl SERVER_Release() { return 0; }
int __cdecl SERVER_SetHackListEnabled(int a) { (void)a; return 0; }
int __cdecl FOG_InitErrorMgr() { return 0; }
void __cdecl FOG_SetLogPrefix(char* a, char* b, int c) { (void)a; (void)b; (void)c; }
int __cdecl D2Lang_Initialize() { return 0; }
int __cdecl D2Lang_Uninitialize() { return 0; }
int __cdecl D2COMMON_10983() { return 0; }

// ------------------------------------------------------------
// Performance counters
// ------------------------------------------------------------
// Initialised once from D2Server_MainLoop before the worker threads
// start.  The decompiled readers (Console_GraphSetFrameRate and the
// Perf_* console helpers) belonged to the decompiled module's GDI
// console UI, which this port never runs -- the server is headless
// with FOG's GUI disabled -- so these counters are currently
// write-only.  The call sites and these definitions can both go if
// the startup sequence is trimmed.

static LARGE_INTEGER g_PerfFrequency = {};
static LARGE_INTEGER g_PerfStartupCount = {};
static LARGE_INTEGER g_PerfSnapshotCount = {};
static int g_bPerfAvailable = 0;
static int g_nPerfFramePeriodLow = 0;
static int g_nPerfFramePeriodHigh = 0;
static int g_nPerfFrameDeadlineLow = 0;
static int g_nPerfFrameDeadlineHigh = 0;
static int g_PerfScratch1 = 0;
static int g_PerfScratch2 = 0;

void Perf_InitSystem(void) {
    if (QueryPerformanceFrequency(&g_PerfFrequency)) {
        g_bPerfAvailable = 1;
        g_PerfScratch1 = 0;
        g_PerfScratch2 = 0;
        QueryPerformanceCounter(&g_PerfStartupCount);
    } else {
        g_bPerfAvailable = 0;
    }
}

// Frame period = counter frequency / target FPS; the first frame
// deadline is stored as a 64-bit count split across two 32-bit words.
void __fastcall Perf_InitFrameTimer(unsigned int dwTargetFPS) {
    LARGE_INTEGER freq;
    LARGE_INTEGER now;
    QueryPerformanceFrequency(&freq);

    const uint64_t nPeriod = dwTargetFPS ? (uint64_t)freq.QuadPart / dwTargetFPS : 0;
    g_nPerfFramePeriodLow = (int)(uint32_t)nPeriod;
    g_nPerfFramePeriodHigh = (int)(uint32_t)(nPeriod >> 32);

    QueryPerformanceCounter(&now);
    const uint64_t nDeadline = (uint64_t)now.QuadPart + nPeriod;
    g_nPerfFrameDeadlineLow = (int)(uint32_t)nDeadline;
    g_nPerfFrameDeadlineHigh = (int)(uint32_t)(nDeadline >> 32);
}

void Perf_SnapshotCounter(void) {
    QueryPerformanceCounter(&g_PerfSnapshotCount);
}

// ============================================================
// Linux-compatible Windows API stubs
// Only define if not already provided by libwin
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

// Storm error-display hook.  The squall storm stub archive only exports the
// 7-arg variant of SErrDisplayError; the decompiled D2 modules (D2Game/
// D2Server) reference the 6-arg form declared in Storm.h.  Define that form
// here so the final executable link resolves cleanly.  The module logs its
// errors to stderr anyway, so this just mirrors the message to stdout.
int32_t SErrDisplayError(uint32_t errorcode, const char* filename, int32_t linenumber,
                         const char* description, int32_t recoverable, uint32_t exitcode) {
    (void)errorcode; (void)filename; (void)linenumber; (void)recoverable; (void)exitcode;
    printf("[D2Server][SErr] %s\n", description ? description : "(no description)");
    return 0; // not handled; the caller proceeds with its own recovery
}

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
// frame all S->C packets with the D2 Huffman codec in Fog (HuffmanCodec.h).
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
static void D2Server_SendFrame(PlayerConnection& player, const uint8_t* pData, size_t nLen) {
    if (player.sock < 0 || nLen == 0) {
        return;
    }
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
    if (nPayloadLen == 0) {
        // A Huffman frame that declares zero compressed bytes ("01" on the
        // wire) carries no packet at all and the retail client's frame reader
        // cannot make progress over it.  Never emit one.
        return;
    }
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

// ============================================================
// Engine-path entry complement (D2GS_ENGINE=1)
// ------------------------------------------------------------
// The engine's own act-init burst is exactly 3 S->C frames
// (0x59 ASSIGNPLAYER -> 0x29 -> 0x0E, the tail ending
// 04 48 5B 65 8D 5A).  It is structurally identical to the real
// 1.14d burst but never emits: skills (0x94), unit message state
// (0x22/0x27), map reveal (0x9B), the stat stream (0x1D/0x1E/0x1F),
// experience (0x1C), GAMETIME (0x6D), unit updates (0xAC), and the
// post-tail closure (standalone 0x95 PLAYERDATA + 0x67 MOVENPC x3).
// The module replays the captured real burst *minus* the packets the
// engine already sent or that would corrupt this session:
//   0x59 ASSIGNPLAYER  (engine already bound guid=1 class=4 fortesting;
//                       the captured one binds class=1 "Jorvus")
//   0x9C/0x9D itemdata (fortesting is a fresh, naked char)
//   0x03 GAMEOPENED    (would re-seed the client's map away from the
//                       engine's seed -> world mismatch)
//   0x7B slot/skill    (dangling itemGUID/skill refs from Jorvus)
// Everything else is appended verbatim (world-incoherent values accepted
// for the gate experiment).  The complement lands after the engine's 3
// burst frames on the wire, so the client sees burst + complement exactly
// like a real server's stream.  Set D2GS_COMPLEMENT=0 to disable
// (defaults ON on the engine path).  ====================================

// Number of S->C frames in the engine's act-init burst (0x59/0x29/0x0E).
static constexpr int32_t kEngineBurstFrames = 3;

static bool D2Server_SkipComplementPacket(uint8_t nHeader) {
    switch (nHeader) {
    case 0x59: // ASSIGNPLAYER (double-bind with wrong class/name)
    case 0x9C: // ITEM_DATA (naked fresh char)
    case 0x9D: // ITEM_DATA (naked fresh char)
    case 0x03: // GAMEOPENED (would re-seed the client's map)
    case 0x7B: // slot/skill assign (dangling itemGUID/skill refs)
        return true;
    default:
        return false;
    }
}

// Re-split the captured burst frames into packets (SERVER_GetServerPacketSize)
// and rebuild them minus the skipped headers, one payload per source frame
// (empty frames dropped), preserving capture order.
static std::vector<std::vector<uint8_t>> D2Server_BuildComplementFrames() {
    std::vector<std::vector<uint8_t>> frames;
    for (size_t i = 0; i < d2gs_entry::kFrameCount; i++) {
        const d2gs_entry::BurstFrame& f = d2gs_entry::kFrames[i];
        std::vector<uint8_t> payload;
        uint32_t nOff = 0;
        while (nOff < f.len) {
            D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(f.data + nOff);
            int32_t nSize = 0;
            if (!SERVER_GetServerPacketSize(pView, (uint32_t)(f.len - nOff), &nSize) || nSize <= 0) {
                printf("[D2Server] complement: frame %zu stray byte 0x%02X at %u, stopping frame\n",
                       i, f.data[nOff], nOff);
                break;
            }
            if ((uint32_t)nSize > f.len - nOff) {
                printf("[D2Server] complement: frame %zu packet 0x%02X overruns (size %d, %zu left)\n",
                       i, f.data[nOff], nSize, f.len - nOff);
                break;
            }
            if (!D2Server_SkipComplementPacket(f.data[nOff])) {
                payload.insert(payload.end(), f.data + nOff, f.data + nOff + nSize);
            }
            nOff += (uint32_t)nSize;
        }
        if (!payload.empty()) {
            frames.push_back(std::move(payload));
        }
    }
    return frames;
}

// Send the complement.  Env-guarded: D2GS_COMPLEMENT defaults ON on the
// engine path.  Values:
//   0 = disabled (engine burst only)
//   1 = full filtered captured burst (kFrame2..9 minus 0x59/9C/9D/03/7B),
//       preserving capture order; includes the post-tail closure
//       (kFrame8 = standalone 95, kFrame9 = 67 x3)
//   2 = closure-only (kFrame8 + kFrame9 verbatim) -- bisection: tests
//       whether the post-tail 95+67 frames alone clear the loading gate
//   3 = interleave (kFrame2..9 filtered, tail stripped) INJECTED SYNCHRONOUSLY
//       between the engine's ASSIGNPLAYER frame and its world frames (via the
//       FOG_10157 hook), closure after the engine's tail -- tests whether the
//       char/map body (94/22/27/9B/1D-1F) must arrive INSIDE the burst
//   4 = mode 3 + fresh-character head (Jorvus char packets stripped, synthetic
//       level-1 body prepended) -- identity-coherent
//   5 = mode 4 + synthetic 0B current-unit select before the stat-ops (the
//       client's stat-op handler asserts unless the 0B unit is tracked) +
//       captured 0x53/0xA8/0xAA/0x07/0x15/0x7E/0x51/0x0E/0xAC/0x6D dropped
//       from the head (captured DAYNIGHT asserts in the daylight path; A8/AA
//       are Jorvus stat bitstreams; 07/world/object handlers read the current
//       act, which only the engine's own 03 act-setup creates — the engine
//       re-sends all of them in its world frame)
static int D2Server_ComplementMode() {
    static const int s_nMode = [] {
        const char* p = getenv("D2GS_COMPLEMENT");
        if (p) {
            return atoi(p);
        }
        // Default OFF on the engine path.  Every packet the complement used to
        // supply is now produced by the engine itself, from this session's own
        // data: ASSIGNPLAYER/skills(0x94)/stat-ops(0x1D-0x1F)/experience(0x1C)/
        // PLAYERDATA(0x95)/act-init(0x03)/DAYNIGHT(0x53)/sync-tiles(0x07)/
        // world(0x51)/spawns(0xAC)/state(0xA8,0xAA).  What the complement still
        // adds is a verbatim replay of a captured level-93 Sorcerass session
        // ("Jorvus"): her skill list, her stat values, her map, her day/night
        // state.  Injecting that into a level-1 Barbarian is not a plausible
        // cause of a client crash, it *is* a crash.  D2GS_COMPLEMENT=1..5 brings
        // it back for bisection.
        return 0;
    }();
    return s_nMode;
}

// Town population is engine-owned: the Rogue Encampment's residents come from
// the drlg preset units in town2.ds1, resolved through monpreset.txt by
// SUNIT_SpawnPresetUnitsInRoom, and the engine's room vision-sync emits their
// 0xAC spawn bursts to the client.  The old module-injected 0xAC closure is
// gone -- it always carried the client's own town as an all-cow frame that
// silently no-op'd whenever the client resolved the class against its own
// table.

// Post-tail closure complement.  Remaining modes (2/3/4) still append the
// exact captured post-tail frames verbatim -- kFrame8 (standalone 95
// PLAYERDATA) + kFrame9 (67 MOVENPC x3, inert with no client-side units).
// Mode 5 has no client-injected closure any more: the engine spawns the town
// residents server-side and emits their 0xAC spawn bursts itself.
static std::vector<std::vector<uint8_t>> D2Server_BuildClosureFrames(int32_t /*nAnchorX*/,
                                                                     int32_t /*nAnchorY*/) {
    std::vector<std::vector<uint8_t>> frames;
    for (size_t i : { 6u, 7u }) { // kFrame8 (idx 6), kFrame9 (idx 7)
        const d2gs_entry::BurstFrame& f = d2gs_entry::kFrames[i];
        frames.push_back(std::vector<uint8_t>(f.data, f.data + f.len));
    }
    return frames;
}

// Strip the trailing burst-tail packets (04 48 5B 65 8D 5A, plus the stray
// leading 48 the capture's tail run has) from a payload, so an injected head
// complement never terminates the act-init burst early: the client must see
// TSGAMEFLAGS (0x5A) only from the ENGINE at the true end of its burst.
static void D2Server_StripTailPackets(std::vector<uint8_t>& payload) {
    if (payload.empty()) {
        return;
    }
    // Re-split into packet boundaries, collecting only the trailing run of
    // tail headers.  Stop at the first packet whose header is not part of
    // the tail sequence.
    std::vector<size_t> offsets;   // each packet's start offset
    std::vector<uint32_t> sizes;   // each packet's size
    uint32_t nOff = 0;
    while (nOff < payload.size()) {
        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(payload.data() + nOff);
        int32_t nSize = 0;
        if (!SERVER_GetServerPacketSize(pView, (uint32_t)(payload.size() - nOff), &nSize) ||
            nSize <= 0 || (uint32_t)nSize > payload.size() - nOff) {
            break;
        }
        offsets.push_back(nOff);
        sizes.push_back((uint32_t)nSize);
        nOff += (uint32_t)nSize;
    }
    if (offsets.empty()) {
        return;
    }
    // Walk backwards from the end collecting tail-run headers.
    size_t nTailStart = offsets.size();
    for (size_t i = offsets.size(); i-- > 0;) {
        const uint8_t h = payload[offsets[i]];
        const bool bTail = (h == 0x04 || h == 0x48 || h == 0x5B || h == 0x65 ||
                            h == 0x8D || h == 0x5A);
        if (!bTail) {
            break;
        }
        nTailStart = i;
    }
    if (nTailStart == offsets.size()) {
        return; // no trailing tail packets found
    }
    payload.resize(offsets[nTailStart]);
}

// Mode-3 interleaved complement:
//   HEAD    = full filtered captured burst (same as mode 1) with the
//             trailing burst tail stripped, injected SYNCHRONOUSLY between
//             the engine's ASSIGNPLAYER frame and its world frames (via the
//             FOG_10157 injection hook, so it lands mid-burst);
//   CLOSURE = the post-tail frames (95 PLAYERDATA + 67 MOVENPC x3), sent
//             right after the engine's burst tail.
static const std::vector<std::vector<uint8_t>>* D2Server_Mode3HeadFrames() {
    static const std::vector<std::vector<uint8_t>> s_frames = [] {
        std::vector<std::vector<uint8_t>> frames = D2Server_BuildComplementFrames();
        // BuildComplementFrames ends with kFrame8 (standalone 95 PLAYERDATA)
        // and kFrame9 (67 MOVENPC x3) as its trailing frames — those belong to
        // the POST-TAIL closure, not the mid-burst head.  Drop them (a mid
        // burst frame never starts with 0x95/0x67).
        while (!frames.empty()) {
            const uint8_t h = frames.back()[0];
            if (h != 0x95 && h != 0x67) {
                break;
            }
            frames.pop_back();
        }
        if (!frames.empty()) {
            // Strip the trailing burst-tail packets (04 48 5B 65 8D 5A) so the
            // injected head never terminates the act-init burst early: the
            // client must see TSGAMEFLAGS (0x5A) only from the engine at the
            // true end of its burst.
            D2Server_StripTailPackets(frames.back());
        }
        return frames;
    }();
    return &s_frames;
}

static const std::vector<std::vector<uint8_t>>* D2Server_Mode3ClosureFrames() {
    static const std::vector<std::vector<uint8_t>> s_frames = D2Server_BuildClosureFrames(0, 0);
    return &s_frames;
}

// Re-split `payload` into packets and drop every packet whose header pfnSkip
// accepts, rebuilding the frame in place.  Returns true if anything dropped.
static bool D2Server_FilterPackets(std::vector<uint8_t>& payload,
                                   bool (*pfnSkip)(uint8_t)) {
    std::vector<uint8_t> out;
    out.reserve(payload.size());
    uint32_t nOff = 0;
    bool bDropped = false;
    while (nOff < payload.size()) {
        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(payload.data() + nOff);
        int32_t nSize = 0;
        if (!SERVER_GetServerPacketSize(pView, (uint32_t)(payload.size() - nOff), &nSize) ||
            nSize <= 0 || (uint32_t)nSize > payload.size() - nOff) {
            break;
        }
        if (pfnSkip(payload[nOff])) {
            bDropped = true;
        } else {
            out.insert(out.end(), payload.data() + nOff, payload.data() + nOff + nSize);
        }
        nOff += (uint32_t)nSize;
    }
    if (bDropped) {
        payload.swap(out);
    }
    return bDropped;
}

// Mode-4 char-body skip set: every captured packet that encodes Jorvus's OWN
// character (sorc class 1, level 93) rather than game-world state.  Applied
// to the class-4 client these were the crash source in mode 3:
//   0x94 skill list (20 sorc skills), 0x22 skill-quantity assign (sorc skill
//   0xDC), 0x27 serialized unit message list (full Jorvus unit blob),
//   0x9B map-disc (Jorvus's preset/seed), 0x1D/0x1E/0x1F stat ops (level-93
//   values), 0x1C experience (2.09B), 0x95 life/mana snapshot.
static bool D2Server_IsCharBodyPacket(uint8_t nHeader) {
    switch (nHeader) {
    case 0x94:
    case 0x22:
    case 0x27:
    case 0x9B:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x1C:
    case 0x95:
        return true;
    default:
        return false;
    }
}

// Mode-5 additions to the char-body skip set.  Forensics (client asserts):
//   * 0x53 DAYNIGHT: its handler asserts at line 1351 (NULL room/level in the
//     daylight apply path) whenever the captured Jorvus 0x53 fires while the
//     class-4 client's level/room state isn't the captured session's — the
//     engine emits its OWN 0x53 (same value) inside its world frame, so the
//     captured copy is redundant.
//   * 0xA8/0xAA STATS bitstreams: Jorvus's level-93 stat dumps; the engine
//     sends fresh ones for the class-4 client in its world/tail frames.
//   * 0x07 LVLCOORD + world/object packets (0x15/0x7E/0x51/0x0E/0xAC/0x6D):
//     their handlers read (or assert on) the client's CURRENT ACT global
//     (0x7a0634), which is created ONLY by the 0x03 handler (0x44e100).  The
//     0x03 act-setup is base-skipped (D2Server_SkipComplementPacket, would
//     re-seed the map), so any captured world material in the head fires
//     pre-act: the 0x07 handler hard-asserts at line 1418 when
//     0x7a0634 == 0 (mode-5 dump 2026-09-26 11.32.41, assert 0x58A, EIP
//     0x45CADB inside handler 0x45CAB0).  The engine re-sends ALL of these
//     inside its own world frame in the correct order (03 act-setup -> 53
//     -> 07x9 -> 15 -> 7E -> objects), so the captured copies are dropped.
static bool D2Server_IsCharBodyPacketMode5(uint8_t nHeader) {
    if (D2Server_IsCharBodyPacket(nHeader)) {
        return true;
    }
    switch (nHeader) {
    case 0x53:
    case 0xA8:
    case 0xAA:
    case 0x07: // LEVELDATA / LVLCOORD (act-global assert at client line 1418)
    case 0x15: // MOVEUNIT (world, engine re-sends)
    case 0x7E: // world/stat, engine re-sends
    case 0x51: // OBJECTUPDATE (world, engine re-sends)
    case 0x0E: // UNITUPDATE (world, engine re-sends)
    case 0xAC: // UPDATE (world, engine re-sends)
    case 0x6D: // GAMETIME (world, engine re-sends)
        return true;
    default:
        return false;
    }
}

// Synthesized level-1 character assignment for a fresh class-4 (Barbarian),
// using the captured stream's own packet idioms:
//   1D = stat op 8-bit, 1E = stat op 16-bit, 1F = stat op 32-bit (values are
//   stored fixed-point << 8, matching the real stream), 1C = total
//   experience, 94 = skill assignment list (none for a fresh char).
// The body itself only carries the 94 skills assignment (real kFrame2 sends
// its 94 early, at index 3).  The 0B "current-unit select" (unit type 0,
// guid 1 = the local player) and the stat ops must NOT fire immediately
// after ASSIGNPLAYER: the client's 0x0B handler (0x45cc50) sets the tracked
// unit only if the unit already exists in the client's unit list, and the
// 0x19-0x1F stat-op handler (0x45d780) asserts at line 2474 unless that
// tracked unit is non-NULL.  The real stream places its 0B + stat ops later
// in the burst (after "23 23 5E 28 29"), so the stat chunk is emitted just
// after the head frame's "... 0B 5F" instead (D2Server_BuildHeadFrames).
static std::vector<uint8_t> D2Server_BuildFreshBody() {
    const uint8_t body[] = {
        0x94, 0x00, 0x01, 0x00, 0x00, 0x00, // skills: none, unit guid 1
    };
    return std::vector<uint8_t>(body, body + sizeof(body));
}

// 0B current-unit select + fresh stat-op stream (see D2Server_BuildFreshBody
// for why this is deferred past the quest/state packets in the head).
//
// Stat opcodes use the client's ItemStatCost.txt ID mapping (retail 1.14d,
// verified against the extracted table): strength=0, energy=1, dexterity=2,
// vitality=3, statpts=4, newskills=5, hitpoints=6, maxhp=7, mana=8,
// maxmana=9, stamina=10, maxstamina=11, level=12, experience=13, gold=14,
// goldbank=15.  0x1D = 8-bit value op, 0x1E = 16-bit, 0x1F = 32-bit (values
// for str/ene/dex/vit live fixed-point << 8, matching the retail idiom
// "1F 07 00 F0 02 00" == maxhp 752).  0x1C is the dedicated experience
// opcode (u32 value, no stat id).  A fresh TCP/IP player unit is created at
// 0 for every stat, so statpts/newskills (4/5) simply stay 0 and are NOT
// emitted.  The previous revision applied the stat ops to the wrong IDs
// (1F 04... => statpts += 0x1E00 = 7680, 1F 05... => newskills += 0x0A00 =
// 2560), which is exactly the garbage the client displayed.
static std::vector<uint8_t> D2Server_BuildFreshStatOps() {
    const uint8_t statops[] = {
        0x0B, 0x00, 0x01, 0x00, 0x00, 0x00, // current-unit select: player guid 1
        0x1C, 0x00, 0x00, 0x00, 0x00,       // experience = 0 (1C = exp opcode)
        0x1D, 0x0C, 0x01,                   // level (12)    = 1
        0x1D, 0x0E, 0x00,                   // gold (14)     = 0
        0x1E, 0x0F, 0x00, 0x00,             // goldbank (15) = 0
        0x1F, 0x00, 0x00, 0x1E, 0x00, 0x00, // strength  (0) 30 (0x1E << 8)
        0x1F, 0x01, 0x00, 0x0A, 0x00, 0x00, // energy    (1) 10 (0x0A << 8)
        0x1F, 0x02, 0x00, 0x14, 0x00, 0x00, // dexterity (2) 20 (0x14 << 8)
        0x1F, 0x03, 0x00, 0x19, 0x00, 0x00, // vitality  (3) 25 (0x19 << 8)
        // statpts (4) = 0, newskills (5) = 0 (client-initialized, not sent)
        // Current/regen pools (6-11): the client gates the life/mana globes
        // on these stats (a fresh TCP unit has them all 0, so the engine's
        // own 0x95 PLAYERDATA -- life 55 / mana 10 / stamina 92 -- divides
        // by a zero max and renders the globes EMPTY).  Values mirror the
        // engine's fresh level-1 Barbarian figures (the >>8 values
        // PlrMsg.cpp pushes into its 0x95 builder).
        0x1F, 0x06, 0x00, 0x37, 0x00, 0x00, // hitpoints  (6)  55 (0x37 << 8)
        0x1F, 0x07, 0x00, 0x37, 0x00, 0x00, // maxhp      (7)  55
        0x1F, 0x08, 0x00, 0x0A, 0x00, 0x00, // mana       (8)  10
        0x1F, 0x09, 0x00, 0x0A, 0x00, 0x00, // maxmana    (9)  10
        0x1F, 0x0A, 0x00, 0x5C, 0x00, 0x00, // stamina    (10) 92 (0x5C << 8)
        0x1F, 0x0B, 0x00, 0x5C, 0x00, 0x00, // maxstamina (11) 92
    };
    return std::vector<uint8_t>(statops, statops + sizeof(statops));
}

// Shared interleaved-head construction used by modes 4/5: take the full
// captured burst, drop the post-tail closure frames (95/67), strip every
// packet pfnSkip accepts from each frame, drop emptied frames, strip the
// trailing burst-tail packets from the last frame, and prepend the
// synthesized fresh-character body as the first head frame.
static const std::vector<std::vector<uint8_t>> D2Server_BuildHeadFrames(
    bool (*pfnSkip)(uint8_t)) {
    std::vector<std::vector<uint8_t>> frames = D2Server_BuildComplementFrames();
    // The trailing standalone 95/67 frames belong to the post-tail
    // closure (see mode 3), not the mid-burst head.
    while (!frames.empty()) {
        const uint8_t h = frames.back()[0];
        if (h != 0x95 && h != 0x67) {
            break;
        }
        frames.pop_back();
    }
    for (auto& payload : frames) {
        D2Server_FilterPackets(payload, pfnSkip);
    }
    if (!frames.empty()) {
        // Never terminate the act-init burst early (see mode 3).
        D2Server_StripTailPackets(frames.back());
    }
    // Re-drop frames the tail strip emptied.  This MUST come after the strip:
    // D2Server_StripTailPackets resizes the last frame down to 0 when that
    // frame consists solely of tail packets (0x04/0x48/0x5B/0x65/0x8D/0x5A),
    // and mode 5's skip set removes the last frame's real payload (0x0E/0xAC
    // ...) first, so the frame arrives at the strip all-tail.  Leaving it in
    // made the server put a zero-length Huffman frame ("01" = compressed size
    // 0) on the wire, which the retail client's frame reader cannot size.
    frames.erase(std::remove_if(frames.begin(), frames.end(),
                                [](const std::vector<uint8_t>& v) { return v.empty(); }),
                 frames.end());
    // Prepend the synthesized fresh-character body as the first head frame.
    frames.insert(frames.begin(), D2Server_BuildFreshBody());
    // Append the 0B select + stat ops to the FIRST captured head frame — its
    // surviving tail is "... 5E 28 29 0B 5F", so the stat chunk lands right
    // after the 0B/5F, mirroring the real stream's proven position (kFrame2
    // "... 28 29 0B 5F 1D 1D ...").  Firing 0B+stat ops here, a full head
    // frame after ASSIGNPLAYER's unit creation, avoids the client's line-2474
    // stat-op assert when the 0B-selected unit has not registered yet.
    if (frames.size() >= 2) {
        const std::vector<uint8_t> statops = D2Server_BuildFreshStatOps();
        frames[1].insert(frames[1].end(), statops.begin(), statops.end());
    }
    return frames;
}

// Mode-4 interleaved complement (identity-coherent):
//   Same FOG_10157 interleave mechanism as mode 3, but every Jorvus-owned
//   character packet is stripped from the head so none of the captured
//   class-1 / level-93 data is applied to the class-4 client; the head is
//   instead prefixed with a synthesized fresh-character body (level 1,
//   class-4 base attributes, no skills).  The post-tail closure (95 + 67x3)
//   is unchanged from mode 3.
static const std::vector<std::vector<uint8_t>>* D2Server_Mode4HeadFrames() {
    static const std::vector<std::vector<uint8_t>> s_frames =
        D2Server_BuildHeadFrames(D2Server_IsCharBodyPacket);
    return &s_frames;
}

// Mode-5 interleaved complement (mode 4 + current-unit select + captured
// DAYNIGHT/stat-bitstream removal):
//   Adds the synthetic 0B current-unit select to the fresh body (the stat-op
//   handler asserts unless the 0B-selected unit is tracked) and additionally
//   drops the captured 0x53 DAYNIGHT / 0xA8 / 0xAA from the head, because the
//   mode-3 head proved the captured DAYNIGHT asserts (client line 1351) and
//   0xA8/0xAA are Jorvus stat bitstreams the engine re-sends for the class-4
//   client in its own world/tail frames.
static const std::vector<std::vector<uint8_t>>* D2Server_Mode5HeadFrames() {
    static const std::vector<std::vector<uint8_t>> s_frames =
        D2Server_BuildHeadFrames(D2Server_IsCharBodyPacketMode5);
    return &s_frames;
}

// Extract the engine-assigned player unit guid from a just-written engine
// frame's decompressed payload: the act-init frame's first packet is
// 0x59 ASSIGNPLAYER (guid at +1..+4). Returns 0 when none present.
static uint32_t D2Server_ParseAssignPlayerGuid(const uint8_t* pPayload, int32_t nLen) {
    if (!pPayload || nLen <= 0) {
        return 0;
    }
    uint32_t nOff = 0;
    while (nOff < (uint32_t)nLen) {
        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(pPayload + nOff);
        int32_t nSize = 0;
        if (!SERVER_GetServerPacketSize(pView, (uint32_t)(nLen - nOff), &nSize) ||
            nSize <= 0 || (uint32_t)nSize > (uint32_t)nLen - nOff) {
            break;
        }
        if (pPayload[nOff] == 0x59 && nSize >= 6) {
            return *(const uint32_t*)(pPayload + nOff + 1);
        }
        nOff += (uint32_t)nSize;
    }
    return 0;
}

// The captured/synthesized head frames tag the LOCAL PLAYER with guid 1,
// but the engine assigns a per-game unit guid (1 on a fresh server's first
// game, 2+ afterwards).  Without a rewrite the client's 0x0B handler fails
// its unit-hash lookup (guid 1 is not tracked) and never selects the active
// unit, so the following 0x5F STATEID asserts at client line 3349.  Rewrite
// the player-guid field of every char-body/select packet to the engine's
// session guid, but only where the field still carries the captured value 1.
// Field offsets (D2GSPacketSrv*): 0x0B/0x23/0x76/0x94 -> dwUnitGUID at +2;
// 0x5F STATEID -> 16-bit unit reference at +1.
static void D2Server_RewritePlayerGuid(uint8_t* pPayload, int32_t nLen,
                                       uint32_t nNewGuid) {
    if (!pPayload || nLen <= 0 || nNewGuid == 0 || nNewGuid == 1) {
        return;
    }
    uint32_t nOff = 0;
    while (nOff < (uint32_t)nLen) {
        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(pPayload + nOff);
        int32_t nSize = 0;
        if (!SERVER_GetServerPacketSize(pView, (uint32_t)(nLen - nOff), &nSize) ||
            nSize <= 0 || (uint32_t)nSize > (uint32_t)nLen - nOff) {
            break;
        }
        const uint8_t h = pPayload[nOff];
        if ((h == 0x0B || h == 0x23 || h == 0x76 || h == 0x94) && nSize >= 6) {
            uint32_t v = 0;
            memcpy(&v, pPayload + nOff + 2, 4);
            if (v == 1) {
                memcpy(pPayload + nOff + 2, &nNewGuid, 4);
            }
        } else if (h == 0x5F && nSize >= 3) {
            uint16_t v = 0;
            memcpy(&v, pPayload + nOff + 1, 2);
            if (v == 1) {
                v = (uint16_t)nNewGuid;
                memcpy(pPayload + nOff + 1, &v, 2);
            }
        }
        nOff += (uint32_t)nSize;
    }
}

// Parse a just-written engine frame for the client's town anchor: the 0x15
// MOVEUNIT of the player (x u16 at +6, y u16 at +8) or the first 0x51
// OBJECTUPDATE (x u16 at +8, y u16 at +10).  These are the engine's own
// world-frame coordinates, so they are guaranteed to sit inside the town the
// client generated from the engine's seed.  Returns true on the first
// coordinated packet.
static bool D2Server_ParseWorldAnchor(const uint8_t* pPayload, int32_t nLen,
                                      int32_t* pX, int32_t* pY) {
    if (!pPayload || nLen <= 0 || !pX || !pY) {
        return false;
    }
    uint32_t nOff = 0;
    while (nOff < (uint32_t)nLen) {
        D2PacketBufferStrc* pView = (D2PacketBufferStrc*)(pPayload + nOff);
        int32_t nSize = 0;
        if (!SERVER_GetServerPacketSize(pView, (uint32_t)(nLen - nOff), &nSize) ||
            nSize <= 0 || (uint32_t)nSize > (uint32_t)nLen - nOff) {
            break;
        }
        const uint8_t h = pPayload[nOff];
        if (h == 0x15 && nSize >= 11) {          // MOVEUNIT
            uint16_t wx = 0, wy = 0;
            memcpy(&wx, pPayload + nOff + 6, 2);
            memcpy(&wy, pPayload + nOff + 8, 2);
            if (wx || wy) {
                *pX = wx;
                *pY = wy;
                return true;
            }
        } else if (h == 0x51 && nSize >= 12) {   // OBJECTUPDATE
            uint16_t wx = 0, wy = 0;
            memcpy(&wx, pPayload + nOff + 8, 2);
            memcpy(&wy, pPayload + nOff + 10, 2);
            if (wx || wy) {
                *pX = wx;
                *pY = wy;
                return true;
            }
        }
        nOff += (uint32_t)nSize;
    }
    return false;
}

// FOG_10157 injection hook (registered at startup): fires from the engine's
// S->C write path the moment a frame is fully on the wire, letting mode 3
// interleave the captured head burst BETWEEN the engine's 59 frame and its
// world frames, and append the closure right after the engine's tail.
static void D2Server_OnEngineFrameWritten(int32_t nClientId, int32_t nEngineFrames,
                                          const uint8_t* pPayload, int32_t nPayloadLen) {
    const int nMode = D2Server_ComplementMode();
    if (nMode != 3 && nMode != 4 && nMode != 5) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_PlayerListMutex);
    auto it = g_Players.find((uint32_t)nClientId);
    if (it == g_Players.end() || !it->second.complementArmed) {
        return;
    }
    PlayerConnection& player = it->second;
    // The engine's 0x59 ASSIGNPLAYER carries the player's per-game unit guid;
    // record it the moment the frame is on the wire so the interleaved head
    // (below) can reference the SAME guid the client bound.
    const uint32_t nSessionGuid = D2Server_ParseAssignPlayerGuid(pPayload, nPayloadLen);
    if (nSessionGuid != 0 && player.playerUnitGuid != nSessionGuid) {
        player.playerUnitGuid = nSessionGuid;
        printf("[D2Server] Player %u engine ASSIGNPLAYER unit guid=%u\n",
               player.playerId, nSessionGuid);
    }
    const int32_t nDelta = nEngineFrames - player.engineBurstBase;
    // Mode-5 NPC spawns must land inside the client's generated town, which
    // the engine builds per game from its own seed.  Anchor them to the
    // engine's own world-frame coordinates (the player's spawn, else the
    // first object tile).  World frames are base+2..base+3; parse the FIRST
    // one and keep it (the game's fixed spawn, not the player's later
    // movement).
    if (nMode == 5 && !player.npcAnchorValid && nDelta >= 2) {
        int32_t nAX = 0, nAY = 0;
        if (D2Server_ParseWorldAnchor(pPayload, nPayloadLen, &nAX, &nAY)) {
            player.npcAnchorX = nAX;
            player.npcAnchorY = nAY;
            player.npcAnchorValid = true;
            printf("[D2Server] Player %u mode-5 town anchor from engine world "
                   "frame: %d,%d\n",
                   player.playerId, nAX, nAY);
        }
    }
    if (nDelta == 1 && !player.complementHeadSent) {
        // Engine's ASSIGNPLAYER frame (base+1) just completed: interleave the
        // head burst before the engine writes its world frames.
        player.complementHeadSent = true;
        const std::vector<std::vector<uint8_t>>* pHead =
            (nMode == 4) ? D2Server_Mode4HeadFrames() :
            (nMode == 5) ? D2Server_Mode5HeadFrames() : D2Server_Mode3HeadFrames();
        printf("[D2Server] Player %u mode-%d interleave: head burst after "
               "ASSIGNPLAYER frame (%zu frames)\n",
               player.playerId, nMode, pHead->size());
        const bool bRewrite = (player.playerUnitGuid != 0 && player.playerUnitGuid != 1);
        for (const std::vector<uint8_t>& payload : *pHead) {
            if (bRewrite) {
                std::vector<uint8_t> rewritten = payload; // head frames are shared static data
                D2Server_RewritePlayerGuid(rewritten.data(), (int32_t)rewritten.size(),
                                           player.playerUnitGuid);
                D2Server_SendCompressed(player, rewritten.data(), rewritten.size());
            } else {
                D2Server_SendCompressed(player, payload.data(), payload.size());
            }
        }
        if (bRewrite) {
            printf("[D2Server] Player %u head player-guid rewritten 1 -> %u\n",
                   player.playerId, player.playerUnitGuid);
        }
    } else if (nDelta >= kEngineBurstFrames && !player.complementSent) {
        // Engine's burst tail (base + 3) is on the wire: append the closure.
        player.complementSent = true;
        if (nMode == 5) {
            // No client-injected closure for mode 5: the engine itself
            // spawns the Rogue Encampment's residents from the drlg preset
            // units in town2.ds1 and its room vision-sync emits their 0xAC
            // spawn bursts to the client right after this world tail.
            // Forwarding later clicks to the engine's real handlers (see
            // below) makes NPC talks and the stash click bind to those same
            // units.
            printf("[D2Server] Player %u mode-5: town residents engine-spawned, "
                   "module closure skipped%s\n",
                   player.playerId,
                   player.npcAnchorValid ? " (town anchor parsed)" : "");
        } else {
            const std::vector<std::vector<uint8_t>>* pClosure =
                D2Server_Mode3ClosureFrames();
            printf("[D2Server] Player %u mode-%d interleave: post-tail closure "
                   "(%zu frames)\n",
                   player.playerId, nMode, pClosure->size());
            for (const std::vector<uint8_t>& payload : *pClosure) {
                D2Server_SendCompressed(player, payload.data(), payload.size());
            }
        }
    }
}

static void D2Server_SendEngineComplement(PlayerConnection& player) {
    if (!D2Server_ComplementMode()) {
        return;
    }
    static const std::vector<std::vector<uint8_t>> s_frames =
        (D2Server_ComplementMode() == 2) ? D2Server_BuildClosureFrames(0, 0)
                                         : D2Server_BuildComplementFrames();
    printf("[D2Server] Player %u sending engine-entry complement "
           "(mode %d, %zu frames)\n",
           player.playerId, D2Server_ComplementMode(), s_frames.size());
    for (const std::vector<uint8_t>& payload : s_frames) {
        D2Server_SendCompressed(player, payload.data(), payload.size());
    }
}

// ============================================================
// World interactivity: area transitions + NPC talk (replay streams)
// ------------------------------------------------------------
// The wrapper world IS the world of the captured 1.14d session (same map
// seed, same unit guids), so when the client does something the captured
// character did, we replay the exact S->C response bytes the real server
// sent.  Two behaviours are covered:
//   * Crossing the Rogue Encampment's west gate (town <-> Blood Moor)
//     replays the captured area-change stream, so outside areas generate.
//   * Clicking a town NPC (C->S 0x13 INTERACTWITHENTITY) replays the real
//     NPC_INFO + NPCGOSSIP reply (and the mercenary hire list for the
//     hire-NPC), so NPCs visibly react.
// ============================================================

static uint64_t D2Server_NowMs(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

// Send every frame of a replayed transition burst.
static void D2Server_SendAreaBurst(PlayerConnection& player,
                                   const d2gs_area::BurstFrame* pFrames, size_t nCount) {
    for (size_t i = 0; i < nCount; i++) {
        D2Server_SendCompressed(player, pFrames[i].data, pFrames[i].len);
    }
}

// Town -> Blood Moor (walking west through the gate).  Replays the captured
// leave-town burst: BM monsters at the gate, area=2 tile reveals, the
// REASSIGN chain (6260,5149)->(6228,5147), town-unit culling and the BM
// objects/monsters near the gate -- exactly as the real server sent them
// while the captured character walked out (dump frames #34..#42).
static bool D2Server_WantTransition() {
    static const int s_nTransition = [] {
        const char* p = getenv("D2GS_TRANSITION");
        return p ? atoi(p) : 1;
    }();
    return s_nTransition != 0;
}

static void D2Server_LeaveTown(PlayerConnection& player) {
    if (!D2Server_WantTransition()) {
        printf("[D2Server] Player %u AREA TRANSITION town->BM SKIPPED (D2GS_TRANSITION=0)\n",
               player.playerId);
        return;
    }
    printf("[D2Server] Player %u AREA TRANSITION: town -> Blood Moor (%zu frames)\n",
           player.playerId, d2gs_area::kLeaveTownCount);
    D2Server_SendAreaBurst(player, d2gs_area::kLeaveTownFrames, d2gs_area::kLeaveTownCount);
    player.areaState = 2;
    player.lastTransMs = D2Server_NowMs();
    printf("[D2Server] Player %u now in the Blood Moor\n", player.playerId);
}

// Blood Moor -> town (walking east back through the gate).  Replays the
// synthesized return burst: town tile reveals, respawn of the town units
// the leave stream culled, BM tile hides + BM unit culls, REASSIGN to the
// town side of the gate.
static void D2Server_EnterTown(PlayerConnection& player) {
    if (!D2Server_WantTransition()) {
        printf("[D2Server] Player %u AREA TRANSITION BM->town SKIPPED (D2GS_TRANSITION=0)\n",
               player.playerId);
        return;
    }
    printf("[D2Server] Player %u AREA TRANSITION: Blood Moor -> town (%zu frames)\n",
           player.playerId, d2gs_area::kEnterTownCount);
    D2Server_SendAreaBurst(player, d2gs_area::kEnterTownFrames, d2gs_area::kEnterTownCount);
    player.areaState = 1;
    player.lastTransMs = D2Server_NowMs();
    printf("[D2Server] Player %u back in town\n", player.playerId);
}

// Track the client's ground-movement targets (0x03 RunToLocation /
// 0x59 MoveToTarget) and detect west-gate crossings.  The Rogue
// Encampment's gate to the Blood Moor sits around x 6258-6266, y 5128-5172
// (the capture's walk-out REASSIGNs were (6260,5149)->(6228,5147), and the
// retail client was observed blocked just east of it in earlier sessions).
//
// The client walks in small 4-6px steps, so a single move packet never
// "hops" cleanly across the gate zone (lastX>6266 && x<=6258 failed for the
// real walk 6272->6267->6260->6254...).  Trigger on the reported location
// relative to the gate line instead: once the character is west of the BM
// line (x<=6258) while in town, swap areas; once east of the town line
// (x>=6266) while in the Blood Moor, swap back.
static void D2Server_OnMoveTarget(PlayerConnection& player, int16_t nX, int16_t nY) {
    if (player.areaState == 0) {
        player.areaState = 1; // the world starts in town
    }
    if (!player.havePos) {
        player.lastMoveX = nX;
        player.lastMoveY = nY;
        player.havePos = true;
        return;
    }
    const uint64_t nNow = D2Server_NowMs();
    const bool bInGateY = (nY >= d2gs_area::kGateYMin && nY <= d2gs_area::kGateYMax);
    if (bInGateY && (nNow - player.lastTransMs) >= 1500) {
        if (player.areaState == 1 && nX <= d2gs_area::kGateCrossEast) {
            D2Server_LeaveTown(player);
        } else if (player.areaState == 2 && nX >= d2gs_area::kGateCrossWest) {
            D2Server_EnterTown(player);
        }
    }
    player.lastMoveX = nX;
    player.lastMoveY = nY;
}

// Reply to a click/talk on a town NPC (C->S 0x13 INTERACTWITHENTITY
// { nUnitType=1, nUnitGUID }).  The real 1.14d server's observable reply
// chain (from the captured session):
//   NPC_INFO (0x27)       -> flags the NPC as interactable ("!" marker)
//   NPCGOSSIP (0x91)      -> broadcast listing which NPCs have new gossip
//
// Talk + panel handlers.  Payloads are replayed from the real 1.14d D2GS
// capture (frames #141 and #143):
//   C->S 0x13 INTERACT          -> NPC_INFO + gossip (+ merc list for the
//                                  hire-NPC guid 10): capture frame #141.
//   C->S 0x2F NPCINIT (panel)   -> CLEARMERCLIST + 10x MERCFORHIRE again:
//                                  capture frame #143 populates the window.
// The NPCGOSSIP template keeps the captured talk-topic string ids verbatim
// (npcId[0]=0x9a, npcId[1]=0x93 -- those are menu-topic StrIds, NOT the
// character class id; a class id in that field shows a blank talk menu).
// Vendor shop wares are not present in the capture, so non-merc NPCs get
// the talk intro only.  The clicked-guid -> class-id map is the captured
// world's (our replayed town has the same guids).
static void D2Server_SendNpcReply(PlayerConnection& player, int32_t nGuid) {
    uint8_t npcInfo[sizeof(d2gs_area::kNpcInfoTemplate)];
    memcpy(npcInfo, d2gs_area::kNpcInfoTemplate, sizeof(npcInfo));
    if (nGuid > 0) {
        memcpy(npcInfo + 2, &nGuid, 4); // NPC_INFO unit guid at offset 2
    }
    printf("[D2Server] Player %u NPC talk guid=%d: NPC_INFO + gossip\n",
           player.playerId, nGuid);
    D2Server_SendCompressed(player, npcInfo, sizeof(npcInfo));
    D2Server_SendCompressed(player, d2gs_area::kNpcGossipTemplate,
                            sizeof(d2gs_area::kNpcGossipTemplate));
    if (nGuid == d2gs_area::kMercNpcGuid) {
        printf("[D2Server] Player %u NPC talk: mercenary hire list (%zu bytes)\n",
               player.playerId, sizeof(d2gs_area::kMercListPayload));
        D2Server_SendCompressed(player, d2gs_area::kMercListPayload,
                                sizeof(d2gs_area::kMercListPayload));
    }
}

// 0x2F NPCINIT -- the client asks to open the NPC's panel (hire window for
// the merc-NPC).  The real server re-sends the merc list to populate it.
static void D2Server_SendNpcPanel(PlayerConnection& player, int32_t nGuid) {
    if (nGuid == d2gs_area::kMercNpcGuid) {
        printf("[D2Server] Player %u NPC panel guid=%d: merc list\n",
               player.playerId, nGuid);
        D2Server_SendCompressed(player, d2gs_area::kMercListOnlyPayload,
                                sizeof(d2gs_area::kMercListOnlyPayload));
    } else {
        printf("[D2Server] Player %u NPC panel guid=%d: no shop data in capture\n",
               player.playerId, nGuid);
    }
}

// Host-game lifecycle state shared with EngineHost.cpp's pfCloseGame hook
// (same shared library).  extern "C" so both TUs agree on linkage.
extern "C" {
uint16_t        g_engineGameId  = 0;
pthread_mutex_t g_engineGameMutex  = PTHREAD_MUTEX_INITIALIZER;
int             g_engineGameExists = 0;
}
static int      g_engineRunning = 0;

// Monotonic incarnation counter for the host game.  Bumped on every
// successful GAME_CreateNewEmptyGame; read together with g_engineGameExists
// under g_engineGameMutex.  Lets D2Server_EnginePush reject messages for a
// player whose game was reaped even after a NEW host game was created for
// another logon (their client->game GUID is never cleared by the engine, so
// a drained message would resolve the OLD freed game's GUID and spin in the
// hash-bucket walk).
static uint32_t g_engineGameEpoch = 0;

// Serializes host-game CREATION only.  Kept separate from g_engineGameMutex
// so the creation path never holds the state mutex while calling INTO the
// engine.  GAME_CreateNewEmptyGame takes the engine game-table lock
// (tHashTable -> CCritSect, a REAL pthread mutex on Linux), while the
// engine's reap path (GAME_UpdateClients -> GAME_CloseGame -> pfCloseGame ->
// Engine_CloseGame) holds that same game-table lock while it takes
// g_engineGameMutex.  Holding g_engineGameMutex across the create call is
// therefore an ABBA deadlock (worker: state mutex -> table lock; tick
// thread: table lock -> state mutex).  g_engineCreateMutex is never touched
// by the engine, so it cannot join that cycle.
static pthread_mutex_t g_engineCreateMutex = PTHREAD_MUTEX_INITIALIZER;

// Robust-enable the host-game state mutex.  A thread killed while holding a
// plain mutex would wedge EVERY future logon (pthread_mutex_lock forever);
// with PTHREAD_MUTEX_ROBUST the next locker gets EOWNERDEAD and we reset the
// indeterminate flags instead of hanging the server.
static void D2Server_InitEngineLocks(void) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
    pthread_mutex_init(&g_engineGameMutex, &attr);
    pthread_mutex_init(&g_engineCreateMutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

extern "C" void D2Server_LockEngineGameState(void) {
    const int nRc = pthread_mutex_lock(&g_engineGameMutex);
    (void)nRc;
#ifdef EOWNERDEAD
    if (nRc == EOWNERDEAD) {
        // Previous owner died mid-update: the flags are indeterminate.
        g_engineGameExists = 0;
        g_engineGameId = 0;
        g_engineGameEpoch = 0;
        pthread_mutex_consistent(&g_engineGameMutex);
    }
#endif
}

extern "C" void D2Server_UnlockEngineGameState(void) {
    pthread_mutex_unlock(&g_engineGameMutex);
}

// Engine entry points the module calls for the on-demand host game (the
// D2Game .so exports them; declared here as the module has no D2Game
// include path).
struct D2GameDataTableStrc; // forward: only the address is passed around here
extern void     GAME_InitGameDataTable(D2GameDataTableStrc* pGameDataTbl, void* pGameList);
extern BOOL     GAME_CreateNewEmptyGame(char* szGameName, const char* szPassword,
                                        const char* szGameDescription, uint32_t nFlags,
                                        uint8_t nArenaTemplate, uint8_t nMaxLevelDifference,
                                        uint8_t nMaxPlayers, uint16_t* pGameId);

// GAME/Game.h GAMEFLAG_ARENA_EXPANSION = 0x00100000
constexpr uint32_t D2GS_GAMEFLAG_ARENA_EXPANSION = 0x00100000u;

// Fog layer helpers not exposed through the module include path.
extern "C" void D2FOG_SetInstallPath(const char* szPath);

// ============================================================
// Engine-driven packet path (D2GS_ENGINEPACKETS=1, the default)
// ------------------------------------------------------------
// Replaces the capture-replay dispatch with the real engine flow: the
// module owns only the D2GS-level accept choreography (logon validation,
// save-chunk assembly, PING->PONG); everything the client sees afterwards
// is generated by the decompiled D2Game engine via its message lists
// (drained by GAME_ProcessNetworkMessages) and the real D2Net outbound
// path (D2NET_10006 -> Huffman frame -> socket).
//
// The retail 1.14d direct-connect flow never sends the lobby packets
// (0x66/0x67/0x69/0x6A); the module synthesizes the engine's D2CLTSYS
// messages from the accept flow instead:
//   0x68 GAMELOGON   -> engine JOINGAME (0x67): join game 1 as the client
//                       (the engine replies GAMELOADING/GAMEFLAGS itself)
//   0x6C save chunks -> engine OPENCHAR (0x6B) once the .d2s is complete
//   0x6B enter env   -> engine JOINACT (0x6A): GAME_SendActInit creates the
//                       player unit and streams the real world-data burst
//   0x6D PING        -> engine ping (0x6C) for its stats (PONG stays here)
//   0x01-0x5F        -> message list 1 (in-game: move/interact/chat/...)
//   0x66-0x6F lobby variants, if ever sent -> message list 0, raw
// ============================================================
static bool D2Server_EnginePacketsEnabled() {
    static const bool s_bEngine = [] {
        const char* p = getenv("D2GS_ENGINEPACKETS");
        return p ? atoi(p) != 0 : true;
    }();
    return s_bEngine;
}

// Push {int32 clientId}{packet} into the engine's message list.
static void D2Server_EnginePush(PlayerConnection& player, int nList,
                                const uint8_t* pData, uint32_t nLen) {
    if (nLen > 512) {
        printf("[D2Server] Player %u frame too large (%u bytes) for engine list %d\n",
               player.playerId, nLen, nList);
        return;
    }

    // Engine-liveness guard.  The engine reaps (frees) the host game the
    // moment its last client is removed -- cheat-kick, heartbeat timeout, or
    // a normal disconnect -- while the module only learns the socket died on
    // a later poll cycle.  ANY message drained AFTER the free (disconnect,
    // ping, in-game movement) is resolved via GAME_LockGame with the
    // client's NEVER-cleared game GUID; the freed/reused node's bucket walk
    // (TSList::RawNext) never terminates, so the tick spins forever holding
    // the game-table CS and the whole server wedges (workers block on the
    // table lock; the log freezes mid-tick).  At reap time the engine has
    // already released the client's name/state, so there is nothing left to
    // tell it: drop the push instead of risking the walk.
    //
    // The epoch check additionally covers a reap immediately followed by a
    // NEW host game for another logon: a client of the old incarnation must
    // not have its late messages pushed into a game it never joined (their
    // stale GUID would resolve the OLD freed game -> same infinite walk).
    D2Server_LockEngineGameState();
    const bool      bHostAlive = g_engineGameExists != 0;
    const uint32_t  nEpoch     = g_engineGameEpoch;
    D2Server_UnlockEngineGameState();
    if (!bHostAlive || player.engineEpoch != nEpoch) {
        static uint32_t s_dropLogs = 0;
        if (s_dropLogs < 8) {
            ++s_dropLogs;
            printf("[D2Server] engine push dropped (player %u, list %d, hdr %02X): "
                   "host game %s\n",
                   player.playerId, nList, pData[0],
                   bHostAlive ? "re-created after this player joined" : "reaped");
        }
        return;
    }

    uint8_t msg[4 + 512];
    memcpy(msg, &player.playerId, 4);
    memcpy(msg + 4, pData, nLen);
    D2FOG_PushClientMessage(nList, msg, (int32_t)(4 + nLen));
}

// Create the engine's single host game on demand, mirroring the real D2GS
// (a game lives only while clients are in it).  The engine reaps an empty
// game whose frame counter sits in the 1s-5min "creator never joined"
// window; its pfCloseGame hook (Engine_CloseGame) clears g_engineGameExists,
// so the next JOIN creates a fresh game and the JOIN packet must carry the
// engine-assigned gameId (it is 1 on a fresh server, but drifts upward as
// games are created/reaped).  Called from the player worker threads before
// the engine JOIN is pushed; serialized by g_engineGameMutex.
static bool D2Server_EnsureEngineGame(void) {
    // Fast path (common): the host game already exists.  g_engineGameMutex
    // guards ONLY the flags; we never call into the engine while holding it
    // (see the ABBA deadlock note at g_engineCreateMutex).
    D2Server_LockEngineGameState();
    if (g_engineGameExists) {
        D2Server_UnlockEngineGameState();
        return true;
    }
    D2Server_UnlockEngineGameState();

    // Serialize the (rare) creation path with a mutex the engine never
    // touches, so no lock-order inversion with the engine game-table lock
    // can occur.  The create call blocks on the table lock while the engine
    // tick thread reaps an empty game -- that is fine as long as we do NOT
    // hold g_engineGameMutex (the reaper needs it to call Engine_CloseGame).
    pthread_mutex_lock(&g_engineCreateMutex);

    // Re-check under the create lock: another worker may have created the
    // game while we waited above.
    D2Server_LockEngineGameState();
    const bool bAlreadyExists = g_engineGameExists;
    D2Server_UnlockEngineGameState();
    if (bAlreadyExists) {
        pthread_mutex_unlock(&g_engineCreateMutex);
        return true;
    }

    char szGameName[32] = "D2MOO-Test";
    // Flags the real D2GS uses for a normal softcore expansion game:
    // UPDATECLIENTS(0x4) + EXPANSION(0x100000).  UPDATECLIENTS is mandatory:
    // without it the per-frame client updater (D2GAME_UpdateAllClients) hits
    // "This should never happen!" and halts.  EXPANSION makes the game
    // expansion-format (wItemFormat 101).
    //
    // GAMEFLAG_ARENA_MODE (0x2) must NOT be set for a normal game: in arena
    // mode the GS build picks the town via ARENA_GetAlternateStartTown(), and
    // nothing in the engine ever writes that field (retail ARENA_AllocArena
    // zeroes it and ignores its own start-town arg), so the act would be
    // allocated with nTownId=0 and the first spawn requests DRLG level 0 ->
    // FOG_ASSERT.  Arena mode additionally disables LEVEL_ChangeAct and forces
    // full HP/Mana on save load, neither of which applies to normal games.
    constexpr uint32_t D2GS_GAMEFLAG_ARENA_UPDATECLIENTS = 0x00000004u;
    const uint32_t nGameFlags =
        D2GS_GAMEFLAG_ARENA_UPDATECLIENTS | D2GS_GAMEFLAG_ARENA_EXPANSION;
    uint16_t nGameId = 0;
    const BOOL bCreated = GAME_CreateNewEmptyGame(szGameName, "", "",
                                                  nGameFlags, 0, 0, 8, &nGameId);

    D2Server_LockEngineGameState();
    if (bCreated) {
        g_engineGameId = nGameId;
        g_engineGameExists = 1;
        ++g_engineGameEpoch;
    }
    D2Server_UnlockEngineGameState();
    pthread_mutex_unlock(&g_engineCreateMutex);

    if (!bCreated) {
        printf("[D2Server][ENGINE] failed to create host game\n");
        return false;
    }
    printf("[D2Server][ENGINE] host game created (gameId=%u)\n", (unsigned)nGameId);
    return true;
}

static void D2Server_EngineDispatchPacket(PlayerConnection& player,
                                          const uint8_t* pData, uint32_t nLen) {
    const uint8_t nHeader = pData[0];

    // 0x68 GAMELOGON: authenticate, then synthesize engine JOINGAME (0x67).
    if (nHeader == D2GS_HDR_GAMELOGON) {
        if (player.authenticated) {
            return;
        }
        if (nLen < sizeof(D2ServerPacketGameLogon)) {
            return;
        }
        const D2ServerPacketGameLogon* pLogon = (const D2ServerPacketGameLogon*)pData;
        char szCharName[17] = {};
        memcpy(szCharName, pLogon->szCharName, sizeof(pLogon->szCharName));
        szCharName[16] = '\0';
        memcpy(player.playerName, szCharName, 16);
        player.playerName[16] = '\0';
        printf("[D2Server] Player %u GAMELOGON char='%s' token=%u ver=%u hash=%08X [engine path]\n",
               player.playerId, szCharName, pLogon->wToken, pLogon->dwVersion, pLogon->dwHash);
        player.authenticated = true;

        // The engine host game is created on demand (it may have been reaped
        // after a previous session emptied it).  The JOIN packet must use the
        // engine-assigned gameId, not a hardcoded one.
        if (!D2Server_EnsureEngineGame()) {
            printf("[D2Server] Player %u engine host game unavailable; dropping logon\n",
                   player.playerId);
            player.authenticated = false;
            return;
        }

        // D2GSPacketClt67 JOINGAME (packed): nTokenId(4) nGameId(2) nPlayerClass(1)
        // unk0x08(4)=10 nLocale(1) szClientName(16).  Game id = the host game;
        // unk0x08=10 is what CCMD_CanClientJoinGame demands.
        uint8_t packet[0x1D] = {};
        packet[0] = 0x67;
        memcpy(packet + 0x01, &pLogon->wToken, 4);   // nTokenId
        const uint16_t nGameId = g_engineGameId;
        memcpy(packet + 0x05, &nGameId, 2);          // nGameId (our single game)
        packet[0x07] = 0;                            // nPlayerClass (real class from save at spawn)
        const int32_t nJoinUnk = 10;                 // demanded by CCMD_CanClientJoinGame
        memcpy(packet + 0x08, &nJoinUnk, 4);
        packet[0x0C] = 0;                            // nLocale
        memcpy(packet + 0x0D, szCharName, 16);       // szClientName
        printf("[D2Server] Player %u engine JOINGAME (gameId=%u, class=0, locale=0)\n",
               player.playerId, (unsigned)nGameId);
        // Bind this player to the created/current host-game incarnation so
        // D2Server_EnginePush accepts their follow-up messages (and rejects
        // them once THIS game is reaped).  Must happen BEFORE the JOIN push:
        // the push guard drops messages whose engineEpoch mismatches.
        D2Server_LockEngineGameState();
        player.engineEpoch = g_engineGameEpoch;
        D2Server_UnlockEngineGameState();
        D2Server_EnginePush(player, 0, packet, sizeof(packet));
        return;
    }

    // 0x6C UPLOADSAVE chunks: assemble here (GS-level framing); when the
    // .d2s is complete, hand it to the engine as OPENCHAR (0x6B).
    if (nHeader == 0x6C) {
        if (nLen < 7) {
            return;
        }
        const uint32_t nFullSize = *(const uint32_t*)(pData + 2);
        const uint32_t nDataLen = nLen - 7; // chunk[chunkLen]; terminator byte at end
        const uint8_t nTerm = pData[nLen - 1];
        if (player.saveFull == 0) {
            player.saveFull = nFullSize;
            printf("[D2Server] Player %u UPLOADSAVE start: fullSize=%u bytes [engine path]\n",
                   player.playerId, nFullSize);
        }
        if (player.saveGot + nDataLen > sizeof(player.saveBuf)) {
            printf("[D2Server] Player %u UPLOADSAVE overflow, ignoring chunk\n", player.playerId);
            return;
        }
        memcpy(player.saveBuf + player.saveGot, pData + 6, nDataLen);
        player.saveGot += nDataLen;
        printf("[D2Server] Player %u UPLOADSAVE chunk: %u/%u bytes (term=%02X)\n",
               player.playerId, player.saveGot, player.saveFull, nTerm);
        if (!player.saveComplete && player.saveFull > 0 && player.saveGot >= player.saveFull) {
            player.saveComplete = true;
            // D2GSPacketClt6B OPENCHAR (packed): nSize(1) nTotalSize(4) saveData[nSize].
            // The engine's CLIENTS_AttachSaveFile appends nSize bytes per OPENCHAR
            // and only marks the save complete when the accumulated size reaches
            // nTotalSize.  nSize is a single byte (<=255), so the save must be
            // replayed as <=255-byte chunks — exactly the framing the client's
            // 0x6C upload used.  A one-shot OPENCHAR would carry nSize =
            // saveGot & 0xFF (335 -> 79), uploading only 79 of 335 bytes, and the
            // act join would then fail in CLIENTS_AddPlayerToGame (character
            // incomplete) -> engine kicks with 0xB3.
            const int32_t nTotalSize = (int32_t)player.saveFull;
            uint32_t nOffset = 0;
            uint32_t nChunks = 0;
            while (nOffset < player.saveGot) {
                const uint32_t nChunk =
                    (player.saveGot - nOffset > 255) ? 255u : (player.saveGot - nOffset);
                uint8_t packet[4 + 1 + 4 + 255];
                packet[0] = 0x6B;
                packet[1] = (uint8_t)nChunk;             // nSize
                memcpy(packet + 2, &nTotalSize, 4);       // nTotalSize
                memcpy(packet + 6, player.saveBuf + nOffset, nChunk);
                D2Server_EnginePush(player, 0, packet, 6 + nChunk);
                nOffset += nChunk;
                ++nChunks;
            }
            printf("[D2Server] Player %u engine OPENCHAR: sent %u-byte save to engine in %u chunks\n",
                   player.playerId, player.saveGot, nChunks);
            return;
        }
        return;
    }

    // 0x6B ENTERGAME (bare header): the client finished uploading; run
    // JOINACT -> GAME_SendActInit (creates the player unit, loads the act,
    // streams the real world-data burst).
    if (nHeader == D2GS_HDR_ENTERGAME14) {
        player.inGame = true;
        printf("[D2Server] Player %u ENTERGAME -> engine JOINACT (save %u/%u)%s\n",
               player.playerId, player.saveGot, player.saveFull,
               player.saveComplete ? " [save complete]" :
               (player.saveFull > 0 ? " [upload incomplete!]" : ""));
        // Arm the engine-entry complement (D2GS_COMPLEMENT=1, the default on
        // the engine path): record the engine's current S->C frame count now.
        // The worker fires once the engine's 3-frame act-init burst
        // (0x59/0x29/0x0E) has been fully written, appending the filtered
        // captured burst so the client gets every packet type a real server
        // sends, plus the post-tail closure (95 PLAYERDATA + 67 MOVENPC x3).
        {
            if (D2Server_ComplementMode() != 0) {
                player.complementArmed = true;
                player.complementSent = false;
                player.complementHeadSent = false;
                player.engineBurstBase =
                    D2FOG_EngineFrameCount((int32_t)player.playerId);
                printf("[D2Server] Player %u engine-entry complement armed "
                       "(mode %d, engine S->C base frame %d)\n",
                       player.playerId, D2Server_ComplementMode(),
                       player.engineBurstBase);
            }
        }
        const uint8_t packet[1] = { 0x6A }; // D2CLTSYS_JOINACT
        D2Server_EnginePush(player, 0, packet, sizeof(packet));
        return;
    }

    // 0x6D PING: keep the GS-level PONG (the engine has no pong), and mirror
    // the ping into the engine (D2CLTSYS_0x6C) for its client stats.
    if (nHeader == D2GS_HDR_PING) {
        uint32_t nTick = 0, nDelay = 0, nWarden = 0;
        if (nLen >= 13) {
            nTick   = *(const uint32_t*)(pData + 1);
            nDelay  = *(const uint32_t*)(pData + 5);
            nWarden = *(const uint32_t*)(pData + 9);
        }
        printf("[D2Server] Player %u PING tick=%u delay=%u warden=%u [engine path]\n",
               player.playerId, nTick, nDelay, nWarden);
        uint8_t pong[33] = {};
        pong[0] = D2GS_HDR_PONG;
        D2Server_SendCompressed(player, pong, sizeof(pong));
        uint8_t packet[1 + 4 + 4] = {};
        packet[0] = 0x6C; // D2CLTSYS_0x6C (ping)
        memcpy(packet + 1, &nTick, 4);
        memcpy(packet + 5, &nDelay, 4);
        D2Server_EnginePush(player, 0, packet, sizeof(packet));
        return;
    }

    // NPC interaction (0x13 INTERACT / 0x2F NPCINIT / 0x38 NPCTRADE): the
    // engine's Act-1 resident units now exist in its world (spawned by
    // GAME_SendActInit), so these flow straight to the engine's real in-game
    // handlers like any other packet: 0x13 -> PlrMsg sub_6FC828D0 (monster
    // interact for townsfolk, object interact for the stash/chests), 0x2F ->
    // sub_6FC61AB0 (NPC chat/heal/panel init), 0x38 -> Rcv0x38 (trade/merc).
    // Fall through to the generic in-game path below.

    // In-game packets (0x01-0x5F) -> list 1 (CCMD_ProcessClientMessage).
    if (nHeader < 0x66) {
        printf("[D2Server] Player %u -> engine list1: 0x%02X %s (%u bytes)\n",
               player.playerId, nHeader, D2Server_PacketName(nHeader), nLen);
        D2Server_EnginePush(player, 1, pData, nLen);
        return;
    }

    // Lobby/system variants (0x66/0x67/0x69/0x6A/0x6D/0x6F) if a client ever
    // sends them directly: push to list 0 raw (the engine dispatches by the
    // byte's D2CLTSYS id).
    if (nHeader < 0x70 && nHeader != 0x6B && nHeader != 0x6C && nHeader != 0x6D && nHeader != 0x68) {
        printf("[D2Server] Player %u -> engine list0: 0x%02X %s (%u bytes)\n",
               player.playerId, nHeader, D2Server_PacketName(nHeader), nLen);
        D2Server_EnginePush(player, 0, pData, nLen);
        return;
    }

    printf("[D2Server] Player %u engine path: unhandled frame 0x%02X (%u bytes)\n",
           player.playerId, nHeader, nLen);
}

// Dispatch one complete, validated client->server frame
static void D2Server_DispatchPacket(PlayerConnection& player, const uint8_t* pData, uint32_t nLen) {
    const uint8_t nHeader = pData[0];
    const char* szName = D2Server_PacketName(nHeader);

    player.framesRecv++;

    // Engine-driven path (default): every frame is fed to the real D2Game
    // engine; the legacy capture-replay switch below only runs with
    // D2GS_ENGINEPACKETS=0.
    if (D2Server_EnginePacketsEnabled()) {
        D2Server_EngineDispatchPacket(player, pData, nLen);
        return;
    }

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
        memcpy(player.playerName, szCharName, sizeof(szCharName) - 1);
        player.playerName[sizeof(szCharName) - 1] = '\0';
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
    case 0x03: { // 0x03 — RunToLocation { short nX, short nY } (5 bytes)
        // Tracks the client's ground-move target to detect the gate crossing
        // (town -> Blood Moor / back).  Coords are absolute world units.
        if (nLen >= 5) {
            const int16_t nX = *(const int16_t*)(pData + 1);
            const int16_t nY = *(const int16_t*)(pData + 3);
            D2Server_OnMoveTarget(player, nX, nY);
        }
        break;
    }
    case 0x59: { // 0x59 — MoveToTarget { int nType, int nGuid, int nX, int nY } (17 bytes)
        if (nLen >= 17) {
            const int16_t nX = (int16_t)*(const int32_t*)(pData + 9);
            const int16_t nY = (int16_t)*(const int32_t*)(pData + 13);
            D2Server_OnMoveTarget(player, nX, nY);
        }
        break;
    }
    case 0x13: { // 0x13 — INTERACTWITHENTITY { int nUnitType, int nUnitGUID } (9 bytes)
        if (nLen >= 9) {
            const int32_t nType = *(const int32_t*)(pData + 1);
            const int32_t nGuid = *(const int32_t*)(pData + 5);
            if (nType == 1) {
                D2Server_SendNpcReply(player, nGuid);
            } else {
                printf("[D2Server] Player %u INTERACT type=%d guid=%d (not an NPC, ignored)\n",
                       player.playerId, nType, nGuid);
            }
        }
        break;
    }
    case 0x2F: { // 0x2F — NPCINIT { int nType, int nGuid } (9 bytes): open panel
        if (nLen >= 9) {
            const int32_t nType = *(const int32_t*)(pData + 1);
            const int32_t nGuid = *(const int32_t*)(pData + 5);
            if (nType == 1) {
                D2Server_SendNpcPanel(player, nGuid);
            } else {
                printf("[D2Server] Player %u NPCINIT type=%d guid=%d (not an NPC, ignored)\n",
                       player.playerId, nType, nGuid);
            }
        }
        break;
    }
    case 0x30: { // 0x30 — NPCCANCEL { int nType, int nGuid } (9 bytes): close panel
        if (nLen >= 9) {
            const int32_t nType = *(const int32_t*)(pData + 1);
            const int32_t nGuid = *(const int32_t*)(pData + 5);
            printf("[D2Server] Player %u NPCCANCEL type=%d guid=%d (panel closed)\n",
                   player.playerId, nType, nGuid);
        }
        break;
    }
    case 0x38: { // 0x38 — NPCTRADE { int nType, int nGuid, int unk1 } (13 bytes)
        if (nLen >= 13) {
            const int32_t nType = *(const int32_t*)(pData + 1);
            const int32_t nGuid = *(const int32_t*)(pData + 5);
            const int32_t nUnk  = *(const int32_t*)(pData + 9);
            // Merc hire: the real server answers trade requests with a fresh
            // merc list + world nudge.  Re-send the list so the window stays
            // populated while the client walks the hire flow.  The first int
            // is a window/panel id (observed 3), not the unit type, so match
            // on the NPC guid only.
            printf("[D2Server] Player %u NPCTRADE type=%d guid=%d unk=%d\n",
                   player.playerId, nType, nGuid, nUnk);
            if (nGuid == d2gs_area::kMercNpcGuid) {
                D2Server_SendCompressed(player, d2gs_area::kMercListOnlyPayload,
                                        sizeof(d2gs_area::kMercListOnlyPayload));
            }
        }
        break;
    }
    case 0x4D: { // 0x4D — UNK1 { short nClass } (3 bytes): class-id follow-up
        if (nLen >= 3) {
            const uint16_t nClass = *(const uint16_t*)(pData + 1);
            printf("[D2Server] Player %u packet 0x4D class=%u\n",
                   player.playerId, nClass);
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
                player.areaState = 1; // the replayed world starts in town
                {
                    std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                    g_Players[player.playerId] = player;
                }
                printf("[D2Server] Player %u assigned\n", player.playerId);

                // Register the client with the Fog transport shim so the
                // engine's outbound path (D2NET_10006 -> FOG_10157) and per-
                // client lookups (SERVER_Get/SetClientGameGUID, IP) work.
                D2FOG_RegisterClientConnection((int32_t)player.playerId, clientSock,
                                               ntohl(clientAddr.sin_addr.s_addr));

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
                    // Tell the engine the client dropped (D2CLTSYS_DISCONNECT)
                    // so it frees the D2ClientStrc, releases the character name
                    // and decrements nClients.  Without this the dead client
                    // still holds its name and the next logon with the same
                    // character is rejected ("Already in a Game").
                    {
                        const uint8_t disc[1] = { 0x6D };
                        D2Server_EnginePush(*player, 0, disc, sizeof(disc));
                    }
                    close(pollFds[i].fd);
                    D2FOG_UnregisterClientConnection((int32_t)player->playerId);
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

                // Accumulate raw bytes; D2 frames are self-framing (header byte
                // selects the size from the libD2Net table), so we may need
                // several recv() calls before a full frame is available.
                if (player->recvLen + (uint32_t)bytesRead > sizeof(player->recvBuf)) {
                    printf("[D2Server] Player %u receive buffer overflow, disconnecting\n",
                           player->playerId);
                    const uint8_t disc[1] = { 0x6D }; // D2CLTSYS_DISCONNECT
                    D2Server_EnginePush(*player, 0, disc, sizeof(disc));
                    close(pollFds[i].fd);
                    D2FOG_UnregisterClientConnection((int32_t)player->playerId);
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
                        const uint8_t disc[1] = { 0x6D }; // D2CLTSYS_DISCONNECT
                        D2Server_EnginePush(*player, 0, disc, sizeof(disc));
                        close(pollFds[i].fd);
                        D2FOG_UnregisterClientConnection((int32_t)player->playerId);
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

        // Engine-entry complement (D2GS_ENGINE=1): once the engine's act-init
        // burst (3 S->C frames: 0x59/0x29/0x0E) has been fully written to the
        // socket, append the filtered captured real burst so the client
        // receives every packet type a real server sends (skills 0x94, stats
        // 0x1D-0x1F, exp 0x1C, GAMETIME 0x6D, unit updates 0xAC, map reveal
        // 0x9B, ...) plus the post-tail closure (95 PLAYERDATA + 67 MOVENPC).
        // Re-look players up by id (they may have been erased above); sending
        // while holding g_PlayerListMutex is fine here because it is a small
        // burst of tiny frames and no other worker touches this shard's
        // players (the accept thread only inserts).
        {
            std::vector<uint32_t> readyIds;
            {
                std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                for (auto& pair : g_Players) {
                    PlayerConnection& p = pair.second;
                    if (!p.complementArmed || p.complementSent) {
                        continue;
                    }
                    if ((uintptr_t)(pair.first % (uint32_t)kNumWorkers) != nWorkerIndex) {
                        continue;
                    }
                    // Modes 3/4/5 are driven by the FOG_10157 injection hook,
                    // which interleaves the head mid-burst and the closure
                    // post-tail synchronously on the engine write path.
                    if (D2Server_ComplementMode() == 3 || D2Server_ComplementMode() == 4 ||
                        D2Server_ComplementMode() == 5) {
                        continue;
                    }
                    const int32_t nEngineFrames =
                        D2FOG_EngineFrameCount((int32_t)pair.first);
                    if (nEngineFrames - p.engineBurstBase >= kEngineBurstFrames) {
                        readyIds.push_back(pair.first);
                    }
                }
                for (uint32_t id : readyIds) {
                    auto it = g_Players.find(id);
                    if (it != g_Players.end()) {
                        it->second.complementSent = true;
                    }
                }
            }
            for (uint32_t id : readyIds) {
                std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                auto it = g_Players.find(id);
                if (it != g_Players.end()) {
                    D2Server_SendEngineComplement(it->second);
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

#if D2GS_ENGINE
// ============================================================
// Engine game-server host
// ------------------------------------------------------------
// With D2GS_ENGINE=1 the world is driven by the real decompiled D2Game
// module instead of the capture-replay mini-server:
//   1. d2data.mpq is opened through StormLib (squall STORMLIB backend);
//   2. DATATBLS_LoadAllTxts() compiles the retail excel tables through the
//      real FOG_F* file layer (src/File/FogFileIO.cpp);
//   3. D2Game_10046() initializes the game module, the server callbacks and
//      the game data table are registered, and one empty game is created
//      up front;
//   4. each main-loop iteration pumps the inbound message lists
//      (GAME_ProcessNetworkMessages) and the per-frame game progress.
// The join flow (feeding client packets into the engine) lands in M3; this
// host only boots the engine and keeps it ticking.
// ============================================================

// D2Game entry points (@10046/@10050 and @10003/@10004/@10005/@10006).
// Declared here with exact parameter types so the mangled references match
// libD2Game's exports; the heavyweight D2Game headers stay in EngineHost.cpp.
struct D2GameDataTableStrc; // forward: only the address is passed around here
extern int32_t D2Game_10046(void);
extern int32_t D2Game_10050(void);
extern void     GAME_ProcessNetworkMessages(void);
extern int32_t  GAME_UpdateGamesProgress(int32_t a1);
extern void     GAME_UpdateClients(int32_t a1, int32_t a2);
extern void     GAME_CloseAllGames(void);
static int Engine_Initialize(void) {
	D2FOG_SetInstallPath("/hdd/Games/D2Play");

	// Register the retail data archives, highest priority first. 1.14d
	// keeps the current excel tables in Patch_D2.mpq (compcode.txt etc.),
	// with d2data.mpq/d2exp.mpq underneath.
	static const char* kDataArchives[] = {
		"/hdd/Games/D2Play/Patch_D2.mpq",
		"/hdd/Games/D2Play/d2data.mpq",
		"/hdd/Games/D2Play/d2exp.mpq",
		nullptr,
	};
	for (int i = 0; kDataArchives[i]; ++i) {
		void* pArchive = nullptr;
		if (!D2FOG_AddDataArchive(kDataArchives[i], &pArchive)) {
			printf("[D2Server][ENGINE] Failed to open %s\n", kDataArchives[i]);
			return 0;
		}
		printf("[D2Server][ENGINE] opened %s (archive=%p)\n", kDataArchives[i], pArchive);
	}

	// Compile the excel tables out of the MPQs through the real FOG_F* layer.
	// (The archive handles are unused here — ARCHIVE_OpenFile serves every
	// open through FOG_FOpenFile, which searches the registered stack.)
	DATATBLS_LoadFromBin = FALSE;
	DATATBLS_LoadAllTxts(nullptr, 0, 0);
	printf("[D2Server][ENGINE] tables: levels=%d items=%d monstats=%d\n",
	       sgptDataTables->nLevelsTxtRecordCount,
	       sgptDataTables->pItemDataTables.nItemsTxtRecordCount,
	       sgptDataTables->nMonStatsTxtRecordCount);

	if (!D2Game_10046()) {
		printf("[D2Server][ENGINE] D2Game_10046() failed\n");
		return 0;
	}

	D2Engine_RegisterEngineCallbacks();

	GAME_InitGameDataTable((D2GameDataTableStrc*)D2Engine_GetGameDataTable(),
	                       D2Engine_GetGameDataTable());

	// No game is pre-created here: the engine runs on-demand game lifecycle
	// like the real D2GS.  GAME_UpdateClients reaps an empty game whose
	// dwGameFrame is between 1s and 5min of frames ("creator never joined"),
	// so a game created at startup would be closed ~2.4s later with zero
	// clients — and a subsequent JOIN would then lock the freed game's stale
	// GUID (lpCriticalSection already NULL) and hit D2_ASSERT.  Instead the
	// first JOIN (D2Server_EnsureEngineGame) creates the game; the engine's
	// pfCloseGame hook clears g_engineGameExists when it reaps it.
	g_engineRunning = 1;
	return 1;
}

static void Engine_Tick(void) {
	if (!g_engineRunning) {
		return;
	}

	GAME_ProcessNetworkMessages();
	GAME_UpdateGamesProgress(0);
	GAME_UpdateClients(0, 0);
}

static void Engine_Release(void) {
	if (!g_engineRunning) {
		return;
	}

	GAME_CloseAllGames();
	D2Server_LockEngineGameState();
	g_engineGameExists = 0;
	g_engineGameId = 0;
	D2Server_UnlockEngineGameState();
	D2Game_10050();
	D2FOG_CloseDataArchive();
	g_engineRunning = 0;
}
#endif // D2GS_ENGINE

// ============================================================
// Main server loop (Linux)
// ============================================================

// Game-frame pacer.
//
// The D2GS engine advances one *game frame* per Engine_Tick() call, and every
// timed mechanic in D2Game is expressed in frames rather than in wall-clock
// milliseconds: animation frame counts, "duration in frames" in objects.txt,
// per-frame AI and per-frame stat deltas.  The retail D2GS therefore had to
// drive the engine at a fixed game-frame rate -- 25 Hz, one frame every 40 ms
// (the rate D2's client animation is authored at) -- and the engine's timing
// constants are all calibrated against it.  Two examples that pin the number
// down from inside the engine itself:
//
//   * PLRMODE run drain: 2 * charstats.RunDrain raw stat units per frame
//     (Barbarian: 2*20 = 40).  Calibrated to roughly cancel walk regen.
//   * EVENTS_StaminaRegen: nMaxStamina >> 9 raw units per frame while
//     walking (Barbarian: 46).  At 25 Hz a full 92-point stamina pool
//     refills in ~20 s walking, which is the retail behaviour.
//
// This loop used to run Engine_Tick() as fast as the CPU allowed behind a
// bare usleep(1000), which measured ~900 ticks/s -- 36x too fast.  Every
// frame-quantised system (stamina, movement speed, attack rate, cooldowns,
// animation, AI) ran at 36x speed, and the S->C firehose also grew the debug
// log at ~190 KB/s.
//
// D2GS_TICK_HZ overrides the rate (0 or absent = 25).
struct D2Server_FramePacer {
    std::chrono::steady_clock::time_point nNextFrame;
    int nHz;
    uint64_t nFrame;
    int nOverruns;

    explicit D2Server_FramePacer(int hz)
        : nNextFrame(std::chrono::steady_clock::now())
        , nHz(hz > 0 ? hz : 25)
        , nFrame(0)
        , nOverruns(0) {}

    // Block until the next game frame is due.  Frames are scheduled on a
    // fixed grid rather than "40 ms after the last tick finished", so the
    // long-term average is exactly nHz even though a tick costs real time.
    void Wait() {
        using namespace std::chrono;
        nNextFrame += nanoseconds(1000000000LL / nHz);

        // If a tick overran its slot, do not try to replay the missed frames
        // back to back -- that would dump the backlog at the client in one
        // burst.  Skip forward to the next slot instead and count it, so a
        // persistent overrun is visible in the log rather than silent.
        const time_point nNow = steady_clock::now();
        if (nNextFrame < nNow) {
            nOverruns++;
            nNextFrame = nNow;
        }

        // sleep_until has ~50us of overshoot; give the last bit of the wait
        // back as a plain short sleep so the frame boundary stays sharp.
        while (true) {
            const time_point nNow2 = steady_clock::now();
            if (nNow2 >= nNextFrame) {
                break;
            }
            const nanoseconds nLeft = nNextFrame - nNow2;
            if (nLeft > nanoseconds(2000)) {
                std::this_thread::sleep_for(nLeft - nanoseconds(1000));
            } else {
                std::this_thread::yield();
            }
        }

        nFrame++;
        if (nOverruns == 1000) {
            printf("[D2Server] frame pacer: %llu overruns in %llu frames\n",
                   (unsigned long long)nOverruns, (unsigned long long)nFrame);
            nOverruns = 0;
        }
    }
};

static int D2Server_MainLoop(void) {
    printf("[D2Server] Starting D2Server...\n");
    printf("[D2Server] Game port: %d\n", g_nGamePort);

    // Unattended process: keep Fog's assert/halt/error text on stderr but never
    // try to open a GUI message box on the logged-in desktop.
    FOG_SetGuiEnabled(false);

    // Robust-enable the host-game state locks before any other thread can
    // touch them (must precede Engine_Initialize: the engine tick may call
    // Engine_CloseGame, which takes g_engineGameMutex).
    D2Server_InitEngineLocks();

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

    // Mode-3 complement interleaving: hook the engine's S->C frame write path
    // (FOG_10157) so module frames can be injected BETWEEN the engine's
    // own act-init burst frames.  The hook self-guards on D2GS_COMPLEMENT=3.
    D2FOG_SetInjectionCallback(D2Server_OnEngineFrameWritten);

#if D2GS_ENGINE
    if (Engine_Initialize()) {
        printf("[D2Server] Engine game server ready (host game created on first join)\n");
    } else {
        printf("[D2Server][ERROR] Engine game server failed to initialize\n");
        g_bShutdownRequested = true;
    }
#endif

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

    // Main loop.  One Engine_Tick() per game frame, paced to the retail D2
    // game-frame rate (25 Hz) -- see D2Server_FramePacer.
    D2Server_FramePacer sPacer([]
        {
            const char* p = getenv("D2GS_TICK_HZ");
            return p ? atoi(p) : 25;
        }());
    printf("[D2Server] Game frame rate: %d Hz\n", sPacer.nHz);

    while (g_bServerRunning && !g_bShutdownRequested) {
#if D2GS_ENGINE
        Engine_Tick();
        sPacer.Wait();
#else
        usleep(1000);
#endif
    }

    // Shutdown
    printf("[D2Server] Shutting down...\n");
    g_bServerRunning = false;
    usleep(100000);

    #if D2GS_ENGINE
    // Release the engine while its data tables are still alive.
    Engine_Release();
    #endif

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
