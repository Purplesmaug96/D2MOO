#pragma once

#include <windef.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#ifndef _DRAW_CPP
extern SDL_Texture* screenTexture;
#endif

void RenderSquare(SDL_Texture* tex, float nStartPosX, float nStartPosY, float nEndPosX, float nEndPosY, uint8_t nRed, uint8_t nGreen, uint8_t nBlue);

BOOL __fastcall D2SDLRender_StartDraw(int32_t bClear, uint8_t nRed, uint8_t nGreen, uint8_t nBlue);
BOOL __fastcall D2SDLRender_EndDraw();
BOOL __fastcall D2SDLRender_Blit();

void __fastcall D2SDLRender_SetAmbientColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue);

void __fastcall D2SDLRender_DrawBox(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, DrawMode eDrawMode);
void __fastcall D2SDLRender_DrawBoxAlpha(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha);
void __fastcall D2SDLRender_DrawLine(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha);

void __fastcall D2SDLRender_ClearScreen(int32_t bPartial);

void __fastcall D2SDLRender_OutputString(int32_t nPosX, int32_t nPosY, const char* szFormat, va_list va);

void __fastcall D2SDLRender_DebugDraw(uint32_t* pLight, uint32_t* pPlayerLight, int32_t nPosX, int32_t nPosY); // Related to lightmap debugging. Called from an unused stub in D2Client ?
void __fastcall D2SDLRender_DebugFillBackBuffer(int32_t nPosX, int32_t nPosY);
