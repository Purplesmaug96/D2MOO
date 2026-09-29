// Fog network-transport shim (real implementations)
// ---------------------------------------------------------------------
// Real implementations for the Storm/Fog-layer symbols that libD2Net.so
// imports (the D2GS/Storm transport primitives). They used to be weak
// stubs (Fog.cpp); the strong definitions here win at link time.
//
// What this provides:
//   * Per-client connection table (id -> socket/ip/guid) fed by the
//     D2Server module through the D2FOG_* helpers.
//   * FOG_10156/10175 - the per-client inbound message FIFOs (lists
//     0/1/2) that the decompiled D2Game engine drains from
//     (GAME_ProcessNetworkMessages breaks on -1).
//   * FOG_10157       - raw S->C send; the engine's D2NET_10006 funnels
//     every huffman-framed frame here.
//   * FOG_10152/58/59/61/62-66/70/71/72/73/77/80/86/87 - the remaining
//     QServer/Storm plumbing (mostly benign for the engine-driven host).
//   * FOG_InitializeServer/SetMaxClientsPerGame/WaitForSingleObject/... -
//     the D2GS-host surface; the module already owns accept/listen.
//   * FOG_GetInstallPath/GetSavePath - install dir access (seeded via
//     D2FOG_SetInstallPath).
//
// Huffman codec entry points (FOG_10222/10223/10224/10219) live in
// Net/Huffman.cpp; the txt/linker tables in Excel/ExcelBin.cpp and
// Excel/TxtLink.cpp.

#include <Fog.h>

#include <D2NetPacketSize.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "FogNetShim.h"

#include <HuffmanCodec.h>

#include <D2PacketDef.h>

// ---------------------------------------------------------------------
// Shared state (see FogNetShim.h)
// ---------------------------------------------------------------------

std::mutex g_shimMutex;
std::map<int32_t, FogClientConnection> g_clientConnections;
std::deque<std::vector<uint8_t>> g_messageQueues[3];
void* g_pffCallback = nullptr;
void* g_pDummyServer = nullptr;
char g_installPath[512] = "/hdd/Games/D2Play";

// Module-registered injection hook (see FogNetShim.h): invoked from inside
// FOG_10157 after each engine frame is fully written, OUTSIDE g_shimMutex,
// so the module can interleave its own frames between the engine's.
static D2FOG_InjectionCallback g_pInjectionCallback = nullptr;

// ---------------------------------------------------------------------
// Client transport
// ---------------------------------------------------------------------

// FOG_LeadingZeroesCount: index of the highest set bit (0-31), or
// 0xFFFFFFFF when nValue == 0 so loops of the form
//   for (nBit = FOG_LeadingZeroesCount(x); nBit >= 0; ...)
// terminate. (The weak stub from Fog.cpp returned 0 unconditionally,
// which sent the state/stat bit loops in D2GAME_STATES_SendUnitStates
// into an infinite loop.)
uint32_t __stdcall FOG_LeadingZeroesCount(uint32_t nValue) {
	if (nValue == 0) {
		return 0xFFFFFFFFu;
	}
	return 31u - __builtin_clz(nValue);
}

// FOG_ComputeChecksum: Diablo II's "rotating add" 32-bit save checksum
// (Fog.#10229). The weak stub returned 0 unconditionally, which rejected
// every real .d2s upload: retail clients store a non-zero checksum computed
// by this exact algorithm, so PLRSAVE2_ReadSaveHeader bailed out with
// INVALID_CHECKSUM and the engine kicked the client at act-init ("no HUNIT
// to save"). Verified bit-for-bit against a real 1.14d client save captured
// in the server trace (dwChecksum 0x66E4C367 reproduced exactly):
//
//   checksum = 0
//   for each byte b:
//       carry    = (checksum >> 31) & 1
//       checksum = (checksum << 1) + b + carry      // mod 2^32
//
// The caller (PLRSAVE2_ReadSaveHeader / PLRSAVE2_CreateSaveFile) zeroes the
// header's dwChecksum field (offset 0x0C) before hashing, exactly as the
// retail writer does, so no field masking is needed here.
uint32_t __stdcall FOG_ComputeChecksum(void* pData, size_t dwSize) {
	uint32_t nChecksum = 0;
	const uint8_t* pBytes = (const uint8_t*)pData;
	for (size_t i = 0; i < dwSize; ++i) {
		const uint32_t nCarry = (nChecksum >> 31) & 1u;
		nChecksum = (nChecksum << 1) + pBytes[i] + nCarry; // uint32_t wraps mod 2^32
	}
	return nChecksum;
}

// ---------------------------------------------------------------------
// Engine 0xA8 STATS drop (module-side guard, off by default)
// ---------------------------------------------------------------------
// History: the decompiled engine used to emit 0xA8 (STATS) with `nState`
// modeled as a uint16 -- a pad byte at 0x08 that pushed the bitstream to
// 0x09 -- while the retail client's handler (0x45EE20) reads
//     state   = BYTE @ 0x07
//     payload = 0x08, (BYTE @ 0x06) - 8 bytes
// so the client saw a pad byte plus a stat stream truncated by one byte, its
// 9-bit stat-id decode loop never reached the 0x1FF terminator and spun at
// ~100% CPU on the loading screen (crash EIP 0x45EF2E).  The engine used to be
// filtered around that here.  Both halves are now correct -- D2GSPacketSrvA8's
// nState is a uint8_t with the stream at 0x08, and the sender computes
// nSize == BITMANIP_GetSize() + 8, which is exactly what the client subtracts --
// so the raw engine output is passed straight through.  Set D2GS_DROPA8=1 to
// re-enable the guard while diagnosing.

static bool D2FOG_WantDropA8() {
	static const bool s_bDrop = [] {
		const char* p = getenv("D2GS_DROPA8");
		return p ? atoi(p) != 0 : false;
	}();
	return s_bDrop;
}

// Size of the S->C packet at pBuf, using the retail client's own table.  Shared
// with D2Net/src/Server.cpp so both frame walkers agree by construction; see
// D2NetPacketSize.h for the derivation and for why the numbers cannot drift.
// Returns -1 when the payload cannot be walked safely.
static int FogA8PktSize(const uint8_t* pBuf, size_t nBufLen) {
	int32_t nSize = 0;
	if (!D2NET_GetServerPacketSizeFromBuffer(pBuf, (uint32_t)nBufLen, &nSize) || nSize <= 0) {
		return -1;
	}
	return nSize;
}

// Walk an uncompressed S->C payload and repack it without 0xA8 packets.
// Returns the filtered length (>0), 0 when the payload consisted only of
// 0xA8 packets, or -1 when the payload cannot be walked safely (the caller
// then keeps the original frame).
static int D2FOG_RepackWithoutA8(uint8_t* pOut, int nOutCap,
                                 const uint8_t* pIn, int nInLen) {
	uint32_t nOff = 0;
	int nOutLen = 0;
	int nDropped = 0;
	while (nOff < (uint32_t)nInLen) {
		const int nSize = FogA8PktSize(pIn + nOff, (size_t)(nInLen - nOff));
		if (nSize <= 0 || nOff + (uint32_t)nSize > (uint32_t)nInLen) {
			return -1;
		}
		if (pIn[nOff] == 0xA8) {
			nDropped++;
		} else {
			if (nOutLen + nSize > nOutCap) {
				return -1;
			}
			memcpy(pOut + nOutLen, pIn + nOff, (size_t)nSize);
			nOutLen += nSize;
		}
		nOff += (uint32_t)nSize;
	}
	return nDropped > 0 ? nOutLen : -1;
}

// Filter 0xA8 packets out of a framed engine frame.  Returns:
//   -1 : not a clean huffman frame / no 0xA8 to drop -> send the original
//    0 : the whole frame was 0xA8 packets -> drop the frame
//   >0 : length of the repacked frame written to outFrame
static int D2FOG_DropA8FromFrame(uint8_t* outFrame, int nOutCap,
                                 const uint8_t* pFrame, int nFrameLen) {
	int nHeaderSize = 0;
	const int nCompSize = d2gs::Huffman_GetPacketSize(pFrame, &nHeaderSize);
	if (nCompSize <= 0 || nHeaderSize <= 0 || nHeaderSize + nCompSize != nFrameLen) {
		return -1;
	}
	uint8_t raw[4096];
	const int nRawLen = d2gs::Huffman_Decompress(pFrame + nHeaderSize, nCompSize,
	                                             raw, (int)sizeof(raw));
	if (nRawLen <= 0) {
		return -1;
	}

	uint8_t filtered[4096];
	const int nFiltered = D2FOG_RepackWithoutA8(filtered, (int)sizeof(filtered),
	                                            raw, nRawLen);
	if (nFiltered < 0) {
		return -1; // nothing dropped / cannot walk
	}
	if (nFiltered == 0) {
		return 0; // all-0xA8 frame
	}

	uint8_t comp[4096];
	const int nComp = d2gs::Huffman_Compress(filtered, nFiltered, comp, (int)sizeof(comp));
	if (nComp < 0) {
		return -1;
	}
	const int nNewFrame = d2gs::Huffman_WriteFrame(outFrame, nOutCap, comp, nComp);
	if (nNewFrame < 0) {
		return -1;
	}
	return nNewFrame;
}

// FOG_10157: send raw bytes to a client socket. Called by D2NET_10006 with
// already-framed (huffman + length prefix) data.
int FOG_10157(void* pServer, int nClientId, const uint8_t* pBuffer, int nBufferSize) {
	if (!pBuffer || nBufferSize <= 0) {
		return 0;
	}

	int32_t nSocketFd = -1;

	{
		std::lock_guard<std::mutex> lock(g_shimMutex);
		auto it = g_clientConnections.find(nClientId);
		if (it == g_clientConnections.end()) {
			return 0;
		}
		nSocketFd = it->second.nSocketFd;
	}

	if (nSocketFd < 0) {
		return 0;
	}

	// Module-side guard (see "Engine 0xA8 STATS drop" above): the engine's
	// 0xA8 packets are irrecoverably malformed for the retail client, so
	// drop them from the framed payload before the raw bytes hit the wire.
	const uint8_t* pSend = pBuffer;
	int nSend = nBufferSize;
	bool bFrameDropped = false;
	if (D2FOG_WantDropA8()) {
		uint8_t repacked[4096];
		const int nRepacked = D2FOG_DropA8FromFrame(repacked, (int)sizeof(repacked),
		                                            pBuffer, nBufferSize);
		if (nRepacked > 0) {
			pSend = repacked;
			nSend = nRepacked;
			printf("[D2Net][FOG_10157] clientId=%d dropped engine 0xA8: frame %d -> %d bytes\n",
			       nClientId, nBufferSize, nRepacked);
		} else if (nRepacked == 0) {
			bFrameDropped = true;
			printf("[D2Net][FOG_10157] clientId=%d dropped all-0xA8 engine frame (%d bytes)\n",
			       nClientId, nBufferSize);
		}
	}

	if (!bFrameDropped) {
		size_t nSent = 0;
		const size_t nTotal = (size_t)nSend;
		while (nSent < nTotal) {
			const ssize_t nResult = send(nSocketFd, pSend + nSent, nTotal - nSent, MSG_NOSIGNAL);
			if (nResult <= 0) {
				return 0;
			}
			nSent += (size_t)nResult;
		}
	}

	// Count the frame only AFTER the bytes are fully written, so a reader of
	// D2FOG_EngineFrameCount() sees a count that reflects frames actually on
	// the wire (the D2Server module fires its entry complement exactly when
	// the engine's act-init burst has been fully sent).
	int32_t nCountAfter = -1;
	{
		std::lock_guard<std::mutex> lock(g_shimMutex);
		auto it = g_clientConnections.find(nClientId);
		if (it != g_clientConnections.end()) {
			it->second.nEngineFrames++;
			nCountAfter = it->second.nEngineFrames;
		}
	}

	// Injection hook (module-registered): run OUTSIDE the shim lock, after
	// the frame is fully on the wire, so the module can synchronously
	// interleave its own frames between the engine's burst frames.
	if (nCountAfter >= 0 && g_pInjectionCallback) {
		// Hand the just-written engine frame's decompressed payload to the
		// hook too: the module must read the engine's actual packet stream
		// (the 0x59 ASSIGNPLAYER unit guid is a per-game value, not the
		// captured session's guid=1).  Raw passthroughs (0xAE / a1==2) fail
		// the huffman frame check and arrive as a NULL payload.
		uint8_t raw[4096];
		int nRawLen = 0;
		int nHeaderSize = 0;
		const int nCompSize = d2gs::Huffman_GetPacketSize(pBuffer, &nHeaderSize);
		if (nCompSize > 0 && nHeaderSize > 0 &&
		    nHeaderSize + nCompSize == nBufferSize) {
			nRawLen = d2gs::Huffman_Decompress(pBuffer + nHeaderSize, nCompSize,
			                                   raw, (int)sizeof(raw));
		}
		g_pInjectionCallback(nClientId, nCountAfter,
		                     nRawLen > 0 ? raw : nullptr, nRawLen);
	}

	return 1;
}

// FOG_10156: pop the next buffered inbound message from a list.
// Returns the payload size, or -1 when the list is empty (the engine's
// GAME_ProcessNetworkMessages loop breaks on -1).
int FOG_10156(void* pServer, int nList, uint8_t* pBuffer, int nBufferSize) {
	if (nList < 0 || nList > 2 || !pBuffer || nBufferSize <= 0) {
		return -1;
	}

	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto& rQueue = g_messageQueues[nList];
	if (rQueue.empty()) {
		return -1;
	}

	const std::vector<uint8_t>& rMsg = rQueue.front();
	const uint32_t nCopy = ((uint32_t)rMsg.size() < (uint32_t)nBufferSize) ? (uint32_t)rMsg.size() : (uint32_t)nBufferSize;
	std::memcpy(pBuffer, rMsg.data(), nCopy);
	rQueue.pop_front();
	return (int32_t)nCopy;
}

// FOG_10175: enqueue an inbound message into a list. SERVER_EnqueuePacketToMessageList
// uses list 0; the D2Server module uses list 1 (in-game) with the clientId prefix.
int FOG_10175(void* pServer, const uint8_t* pBuffer, int nBufferSize, int nList) {
	if (!pBuffer || nBufferSize <= 0 || nList < 0 || nList > 2) {
		return 0;
	}

	std::lock_guard<std::mutex> lock(g_shimMutex);
	g_messageQueues[nList].push_back(std::vector<uint8_t>(pBuffer, pBuffer + nBufferSize));
	return 1;
}

// FOG_10158: client IP (host order int).
int FOG_10158(void* pServer, int nClientId) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto it = g_clientConnections.find(nClientId);
	return it == g_clientConnections.end() ? 0 : (int)it->second.dwIp;
}

// FOG_10159: client IP as string.
int FOG_10159(void* pServer, int nClientId, char* szOut, int nSize) {
	if (!szOut || nSize <= 0) {
		return 0;
	}

	uint32_t dwIp = 0;
	{
		std::lock_guard<std::mutex> lock(g_shimMutex);
		auto it = g_clientConnections.find(nClientId);
		if (it != g_clientConnections.end()) {
			dwIp = it->second.dwIp;
		}
	}

	struct in_addr sAddr;
	sAddr.s_addr = htonl(dwIp);
	const char* pStr = inet_ntop(AF_INET, &sAddr, szOut, (socklen_t)nSize);
	if (!pStr) {
		szOut[0] = '\0';
	}
	return 0;
}

// FOG_10161: client socket fd.
int FOG_10161(void* pServer, int nClientId) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto it = g_clientConnections.find(nClientId);
	return it == g_clientConnections.end() ? -1 : it->second.nSocketFd;
}

// FOG_10152: used by SERVER_Release-style cleanup; benign.
int FOG_10152(void* pServer, const uint8_t* pBuffer, int nSize) {
	return 1;
}

// FOG_10162/10163/10165: client trace/log helpers (file+line); no-op server-side.
int FOG_10162(void* pServer, int nClientId, const char* szFile, int nLine) { return 0; }
int FOG_10163(void* pServer, int nClientId, const char* szFile, int nLine) { return 0; }
int FOG_10165(void* pServer, int nClientId, const char* szFile, int nLine) { return 0; }

// FOG_10164 / FOG_10166 / FOG_10170 / FOG_10177 / FOG_10180 / FOG_10186:
// misc QServer plumbing; never used by the engine-driven host.
int FOG_10164(void* pServer, int a, int b, int c) { return 1; }
int FOG_10166(void* pServer, int nClientId, int a, int b) { return 1; }
int FOG_10170(void* pServer, int a) { return 0; }
int FOG_10171(void* pServer, void* pCallback) { g_pffCallback = pCallback; return 1; }
int FOG_10177(void* pServer, int nMilliseconds) { return 0; }
int FOG_10180(void* pServer) { return 0; }
int FOG_10186(void* pServer, int nIndex, int nValue) { return 0; }
int FOG_10187(void* pServer, int a, int b) { return 0; }

// FOG_10172/10173: per-client game GUID storage (SERVER_Set/GetClientGameGUID).
int FOG_10172(void* pServer, int nClientId, int nGameGuid) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto it = g_clientConnections.find(nClientId);
	if (it != g_clientConnections.end()) {
		it->second.nGameGuid = nGameGuid;
	}
	return nGameGuid;
}

int FOG_10173(void* pServer, int nClientId) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto it = g_clientConnections.find(nClientId);
	return it == g_clientConnections.end() ? 0 : it->second.nGameGuid;
}

// ---------------------------------------------------------------------
// D2GS-host surface (accept/listen is owned by the D2Server module)
// ---------------------------------------------------------------------

// FOG_InitializeServer: creates a dummy server handle. The connection table
// is fed via D2FOG_RegisterClientConnection instead.
QServer* FOG_InitializeServer(int a1, int a2, int a3, int a4, void* a5, void* a6, void* a7, void* a8) {
	static char sDummyServer = 0;
	g_pDummyServer = &sDummyServer;
	return (QServer*)&sDummyServer;
}

int FOG_SetMaxClientsPerGame(QServer* pServer, int nMaxClients) {
	return nMaxClients;
}

int FOG_WaitForSingleObject(void* pServer, int nMilliseconds) {
	if (nMilliseconds > 0) {
		usleep((useconds_t)nMilliseconds * 1000);
	}
	return 0;
}

int FOG_SetHackListEnabled(QServer* pServer, BOOL bHacklistEnabled) {
	return 0;
}

// ---------------------------------------------------------------------
// Install/save paths
// ---------------------------------------------------------------------

BOOL FOG_GetInstallPath(char* pPathBuffer, size_t nBufferSize) {
	if (!pPathBuffer || nBufferSize == 0) {
		return 0;
	}
	std::snprintf(pPathBuffer, nBufferSize, "%s", g_installPath);
	return 1;
}

size_t FOG_GetSavePath(char* pPathBuffer, size_t nBufferSize) {
	if (!pPathBuffer || nBufferSize == 0) {
		return 0;
	}
	const size_t nLen = std::snprintf(pPathBuffer, nBufferSize, "%s", g_installPath);
	return nLen;
}

// ---------------------------------------------------------------------
// D2Server-module helpers (extern "C", exported by libFog.so)
// ---------------------------------------------------------------------

extern "C" void D2FOG_RegisterClientConnection(int32_t nClientId, int32_t nSocketFd, uint32_t dwIp) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	FogClientConnection conn;
	conn.nSocketFd = nSocketFd;
	conn.dwIp = dwIp;
	g_clientConnections[nClientId] = conn;
}

extern "C" void D2FOG_UnregisterClientConnection(int32_t nClientId) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	g_clientConnections.erase(nClientId);
}

extern "C" int32_t D2FOG_PushClientMessage(int32_t nList, const uint8_t* pData, int32_t nSize) {
	return FOG_10175(nullptr, pData, nSize, nList);
}

extern "C" void D2FOG_SetInstallPath(const char* szPath) {
	if (szPath && szPath[0]) {
		std::snprintf(g_installPath, sizeof(g_installPath), "%s", szPath);
	}
}

extern "C" int32_t D2FOG_EngineFrameCount(int32_t nClientId) {
	std::lock_guard<std::mutex> lock(g_shimMutex);
	auto it = g_clientConnections.find(nClientId);
	if (it == g_clientConnections.end()) {
		return -1;
	}
	return it->second.nEngineFrames;
}

extern "C" void D2FOG_SetInjectionCallback(D2FOG_InjectionCallback pCallback) {
	g_pInjectionCallback = pCallback;
}