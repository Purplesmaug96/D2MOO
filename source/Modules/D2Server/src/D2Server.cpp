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

// Size of the fixed 0xFF (frame/tick) packet and other protocol constants
constexpr uint8_t  D2GS_HDR_COMPRESSNEG     = 0xAF; // S->C compression negotiate
constexpr uint8_t  D2GS_HDR_GAMELOGON       = 0x68; // C->S game logon
constexpr uint8_t  D2GS_HDR_STARTGAME      = 0x5C; // S->C start game (join accepted)
constexpr uint8_t  D2GS_HDR_ENTERGAME      = 0x6A; // C->S enter game environment
constexpr uint8_t  D2GS_HDR_SAVEDATA       = 0x6B; // C->S save data chunk
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
static int g_nGamePort = 6112;
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
// Implements the D2GS accept sequence (see BNETDocs "Diablo II
// Game Server Accept Sequence"):
//
//   S->C  [0xAF] compression negotiate       (sent on accept)
//   C->S  [0x68] D2GS_GAMELOGON
//   S->C  [0x5C] D2GS_STARTGAME (+ player GUID)
//   C->S  [0x6A] D2GS_ENTERGAMEENVIRONMENT
//   ...   game packets flow after that
//
// Frames are self-framing (first byte = header, size from the
// libD2Net size table). Variable-size packets (0x14/0x15 chat,
// 0x6B save data) carry their own length and are only dispatched
// once enough bytes have been buffered.
// ============================================================

// D2GSPacketSrv5C layout, kept local to avoid pulling the whole D2Common header set
#pragma pack(push, 1)
struct D2ServerPacketStartGame {
    uint8_t nHeader;      // 0x5C
    uint32_t dwPlayerGUID; // player unit GUID assigned by the server
};
#pragma pack(pop)
static_assert(sizeof(D2ServerPacketStartGame) == 5, "StartGame packet must be 5 bytes");

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
    case 0x6A: return "ENTERGAMEENV";
    case 0x6B: return "SAVEDATA";
    case 0x6C: return "ClientHeartbeat";
    case 0xFF: return "Tick/Frame";
    default:   return "Unknown";
    }
}

// Send a raw frame to a player (frames are already fully formed)
static void D2Server_HexDump(const char* szWhere, uint32_t playerId, const uint8_t* pData, size_t nLen) {
    printf("[D2Server] %s (p%u, %zu bytes):", szWhere, playerId, nLen);
    // Log the whole frame up to a sane cap so handshakes (short) are fully
    // visible while long payloads (chats/saves) stay bounded.
    size_t nShown = nLen < 128 ? nLen : 128;
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
    // One-byte 0xAF handshake is the only frame sent before the client's
    // first packet; log everything so a mismatched client's behavior is
    // observable server-side.
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

// Dispatch one complete, validated client->server frame
static void D2Server_DispatchPacket(PlayerConnection& player, const uint8_t* pData, uint32_t nLen) {
    const uint8_t nHeader = pData[0];
    const char* szName = D2Server_PacketName(nHeader);

    player.framesRecv++;
    D2Server_HexDump("recv frame", player.playerId, pData, nLen);

    switch (nHeader) {
    case D2GS_HDR_GAMELOGON: { // 0x68 — client confirms it can log on
        if (player.authenticated) {
            return;
        }
        player.authenticated = true;
        player.playerGUID = player.playerId; // assign a game server unit GUID
        D2ServerPacketStartGame reply;
        reply.nHeader = D2GS_HDR_STARTGAME;
        reply.dwPlayerGUID = player.playerGUID;
        printf("[D2Server] Player %u GAMELOGON accepted, GUID=%u\n",
               player.playerId, player.playerGUID);
        D2Server_SendFrame(player, (const uint8_t*)&reply, sizeof(reply));
        break;
    }
    case D2GS_HDR_ENTERGAME: { // 0x6A — client enters the game environment
        player.inGame = true;
        printf("[D2Server] Player %u entered game environment (gameId=%u)\n",
               player.playerId, player.gameId);
        break;
    }
    case D2GS_HDR_SAVEDATA: { // 0x6B — multi-chunk character save upload
        const uint8_t nChunkSize = nLen > 1 ? pData[1] : 0;
        const uint32_t nTotalSize = nLen >= 6 ? *(const uint32_t*)(pData + 2) : 0;
        printf("[D2Server] Player %u SAVEDATA chunk=%u bytes, total=%u\n",
               player.playerId, (uint32_t)nChunkSize, nTotalSize);
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

                // Step 1 of the D2GS accept sequence: tell the client the
                // server's compression mode with a single 0xAF byte.
                const uint8_t nCompressNegotiate = D2GS_HDR_COMPRESSNEG;
                D2Server_SendFrame(player, &nCompressNegotiate, 1);
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
                    // (except 0xFF) are never legal.
                    if (nHeader >= 0x70 && nHeader != 0xFF) {
                        printf("[D2Server] Player %u sent illegal packet header 0x%02X, disconnecting\n",
                               player->playerId, nHeader);
                        close(pollFds[i].fd);
                        {
                            std::lock_guard<std::mutex> lock(g_PlayerListMutex);
                            g_Players.erase(player->playerId);
                        }
                        bDisconnected = true;
                        break;
                    }

                    int32_t nSize = 0;
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
