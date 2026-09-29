// Shared state and module-facing API of the Fog network-transport shim
// (FogNetShim.cpp). Only that TU defines the state; the D2Server module
// registers accepted 1.14d client connections and pushes inbound packets
// through the D2FOG_* helpers declared here.
#pragma once

#include <cstdint>
#include <deque>
#include <map>
#include <mutex>
#include <vector>

struct FogClientConnection {
	int32_t nSocketFd = -1;
	uint32_t dwIp = 0;
	int32_t nGameGuid = 0;
	int32_t nEngineFrames = 0; // S->C frames the engine wrote for this client
};

extern std::mutex g_shimMutex;
extern std::map<int32_t, FogClientConnection> g_clientConnections;

// One FIFO per message list (0 = game management, 1 = in-game, 2 = other).
extern std::deque<std::vector<uint8_t>> g_messageQueues[3];

extern void* g_pffCallback;
extern void* g_pDummyServer;
extern char g_installPath[512];

#ifdef __cplusplus
extern "C" {
#endif

// Register/unregister an accepted client socket (id assigned by the module).
void D2FOG_RegisterClientConnection(int32_t nClientId, int32_t nSocketFd, uint32_t dwIp);
void D2FOG_UnregisterClientConnection(int32_t nClientId);

// Push an inbound message (already [4-byte clientId][packet] where required)
// into a message list (0/1/2). Returns 1 on success.
int32_t D2FOG_PushClientMessage(int32_t nList, const uint8_t* pData, int32_t nSize);

// Seed the install/save path used by FOG_GetInstallPath/FOG_GetSavePath
// (defaults to /hdd/Games/D2Play).
void D2FOG_SetInstallPath(const char* szPath);

// Return the number of S->C frames the engine has written for this client
// (incremented in FOG_10157 after each frame). -1 when the client is not
// registered. Used by the D2Server module to detect when the engine's
// act-init burst has been fully written, so it can append the module-side
// entry complement in the right order.
int32_t D2FOG_EngineFrameCount(int32_t nClientId);

// Engine-frame injection hook: called from inside FOG_10157 (the engine's
// S->C write path) right after a complete engine frame has been written for
// a client, so a module can synchronously interleave module-side frames
// BETWEEN the engine's own burst frames (mode-3 complement: head right after
// ASSIGNPLAYER, before the world frames). No shim lock is held when the hook
// runs, and the module hook must not re-enter the shim.
//
// pPayload / nPayloadLen additionally carry the just-written engine frame's
// DECOMPRESSED packet stream (NULL + 0 when the frame is not a clean huffman
// frame, e.g. the 0xAE / a1==2 raw passthroughs), so the module can read the
// engine's actual packets -- most importantly the 0x59 ASSIGNPLAYER guid,
// which is a per-game value that must match the module's own complements.
typedef void (*D2FOG_InjectionCallback)(int32_t nClientId, int32_t nEngineFrames,
                                        const uint8_t* pPayload, int32_t nPayloadLen);
void D2FOG_SetInjectionCallback(D2FOG_InjectionCallback pCallback);

#ifdef __cplusplus
}
#endif