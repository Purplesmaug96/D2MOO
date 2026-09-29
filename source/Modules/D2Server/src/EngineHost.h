// Engine game-server host data ownership.
// <GAME/Game.h> drags squall's Memory.hpp (SMem*/TSFixedArray templates) in,
// which cannot be included from D2Server.cpp (it collides with the Win32
// declarations D2Server.cpp relies on -> ambiguous overloads whenever a
// squall template is instantiated).  So the only TU that builds the heavy
// D2Game header is EngineHost.cpp; the host in D2Server.cpp talks to it
// through the small C API below and forward-declared GAME_* entry points.
#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// Pointer to the module's D2GameDataTableStrc instance (only the address is
// exposed; the host passes it straight to GAME_InitGameDataTable).
void* D2Engine_GetGameDataTable(void);

// Fill the D2ServerCallbackFunctions struct and register it with the engine
// (GAME_SetServerCallbackFunctions). Must be called after D2Game_10046().
void D2Engine_RegisterEngineCallbacks(void);

#ifdef __cplusplus
}
#endif