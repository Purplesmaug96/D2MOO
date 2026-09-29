// Engine game-server host data ownership (see EngineHost.h for why this TU
// exists). The game data table and the server callback struct live here,
// where <GAME/Game.h> can be included safely.

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <pthread.h>

#include <GAME/Game.h>

#include "EngineHost.h"

static D2ServerCallbackFunctions g_engineCallbacks;
static D2GameDataTableStrc       g_engineGameDataTable;

static void Engine_LogMessage(int32_t nLogLevel, const char* szFormat, ...) {
	(void)nLogLevel;
	va_list va;
	va_start(va, szFormat);
	vprintf(szFormat, va);
	va_end(va);
	printf("\n");
}

// D2GS's pfSetGameData hands the game data table pointer back as the opaque
// per-game data id.
static uint32_t Engine_SetGameData(void) {
	return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_engineGameDataTable));
}

// pfFindPlayerToken: the module has no account database, so it accepts the
// token the client presented at GAMELOGON and reports the character name as
// its account.  This is the "real" behavior of a single-game dev server, and
// it lets the engine's join verification proceed.
static int32_t Engine_FindPlayerToken(const char* szCharName, int32_t nTokenId, uint16_t nGameId,
                                      char* pszOutAccountName, int32_t* pOutCharSaveTransactionToken,
                                      int32_t* a6, int32_t* a7) {
	if (pszOutAccountName) {
		pszOutAccountName[0] = 0;
		if (szCharName) {
			strncpy(pszOutAccountName, szCharName, 15);
			pszOutAccountName[15] = 0;
		}
	}
	if (pOutCharSaveTransactionToken) {
		*pOutCharSaveTransactionToken = nTokenId;
	}
	if (a6) {
		*a6 = 0;
	}
	if (a7) {
		*a7 = 0;
	}
	printf("[ENGINE] FindPlayerToken: '%s' token=%d game=%u -> accepted\n",
	       szCharName ? szCharName : "?", nTokenId, nGameId);
	return 1;
}

// pfLeaveGame: the module tracks disconnects itself; nothing to persist.
static void Engine_LeaveGame(D2ClientInfoStrc** /*ppClientInfo*/, uint16_t nGameId, int32_t nClassId,
                             int32_t nLevel, uint64_t nExperience, uint32_t nFlags, const char* szCharName,
                             const char* pPreviewInfo, int32_t bUnlockChar, int32_t nZero11, int32_t nZero12,
                             const char* szAccountName, int32_t nCharSaveTransactionToken,
                             FILETIME* pSaveCreationTimestamp) {
	printf("[ENGINE] LeaveGame: '%s' game=%u class=%d lvl=%d unlock=%d\n",
	       szCharName ? szCharName : "?", nGameId, nClassId, nLevel, bUnlockChar);
}

// pfSaveDatabaseCharacter: no persistent DB; the module holds the uploaded
// .d2s in memory.  Log and drop (the client already has the save).
static void Engine_SaveDatabaseCharacter(D2ClientInfoStrc** /*ppClientInfo*/, const char* szCharName,
                                         const char* szAccountName, uint8_t* pSaveData,
                                         uint32_t nSaveDataSize, int32_t nCharSaveTransactionToken) {
	printf("[ENGINE] SaveDatabaseCharacter: '%s' %u bytes\n",
	       szCharName ? szCharName : "?", nSaveDataSize);
}

// pfEnterGame: notify hook; nothing to notify.
static void Engine_EnterGame(uint16_t nGameId, const char* szCharName, int32_t nClassId, int32_t nLevel,
                             uint32_t nFlags) {
	printf("[ENGINE] EnterGame: game=%u '%s' class=%d lvl=%d flags=%08X\n",
	       nGameId, szCharName ? szCharName : "?", nClassId, nLevel, nFlags);
}

// Host-game lifecycle flag owned by D2Server.cpp (same shared library).
// The engine calls pfCloseGame whenever GAME_CloseGame reaps an empty game
// (its "creator never joined" watchdog in GAME_UpdateClients), so the module
// knows its host game is gone and the next JOIN must create a fresh one.
// Only the module's *current* game clears the flag — a stale reap of an
// already-superseded game must not clobber a newer game's existence.
extern "C" {
extern pthread_mutex_t g_engineGameMutex;
extern int             g_engineGameExists;
extern uint16_t        g_engineGameId;
extern void            D2Server_LockEngineGameState(void);
extern void            D2Server_UnlockEngineGameState(void);
}

static void Engine_CloseGame(uint16_t nGameId, uint32_t nProductCode, uint32_t nSpawnedPlayers,
                             int32_t nFrame) {
	D2Server_LockEngineGameState();
	const int bWasCurrent = (g_engineGameExists && g_engineGameId == nGameId);
	if (bWasCurrent) {
		g_engineGameExists = 0;
	}
	D2Server_UnlockEngineGameState();
	printf("[ENGINE] CloseGame: game=%u product=%08X spawned=%u frame=%d %s\n",
	       nGameId, nProductCode, nSpawnedPlayers, nFrame,
	       bWasCurrent ? "(host game cleared)" : "(stale)");
}

extern "C" {

void* D2Engine_GetGameDataTable(void) {
	return &g_engineGameDataTable;
}

void D2Engine_RegisterEngineCallbacks(void) {
	g_engineCallbacks.pfServerLogMessage = &Engine_LogMessage;
	g_engineCallbacks.pfSetGameData      = &Engine_SetGameData;
	g_engineCallbacks.pfFindPlayerToken  = &Engine_FindPlayerToken;
	g_engineCallbacks.pfLeaveGame        = &Engine_LeaveGame;
	g_engineCallbacks.pfSaveDatabaseCharacter = &Engine_SaveDatabaseCharacter;
	g_engineCallbacks.pfEnterGame        = &Engine_EnterGame;
	g_engineCallbacks.pfCloseGame        = &Engine_CloseGame;
	GAME_SetServerCallbackFunctions(&g_engineCallbacks);
}

} // extern "C"