#pragma once

#include <windef.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

BOOL __fastcall D2SDLRender_Detect(HINSTANCE hInst);

void* __fastcall D2SDLRender_GetCacheResults();
BOOL __fastcall D2SDLRender_GetDimensions(int32_t* pWidth, int32_t* pHeight);

void __fastcall D2SDLRender_UtilDiamond(RECT* pRect, uint8_t nPaletteIndex);
void __fastcall D2SDLRender_UtilRect(RECT* pRect, uint8_t nPaletteIndex);
void __fastcall D2SDLRender_UtilFilledRect(RECT* pRect, uint8_t nPaletteIndex);
void __fastcall D2SDLRender_UtilPoint(POINT* pPoint, uint8_t nSize, uint8_t nPaletteIndex);

void __fastcall D2SDLRender_ClearCaches();
