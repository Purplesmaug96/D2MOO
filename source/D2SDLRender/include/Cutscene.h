#pragma once

#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

BOOL __fastcall D2SDLRender_PlayCutscene();
void __fastcall D2SDLRender_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolutionMode, void* pfFrame);
BOOL __fastcall D2SDLRender_CheckCutScene();
void __fastcall D2SDLRender_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion);
void __fastcall D2SDLRender_PlaySmacker(void* pContext);
void __fastcall D2SDLRender_CloseSmacker(void* pContext);
