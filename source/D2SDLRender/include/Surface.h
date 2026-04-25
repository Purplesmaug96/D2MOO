#pragma once

#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

// When things start getting implemented, all the HWNDs will be changed to SDL_Window
BOOL __fastcall D2SDLRender_CreateSurface(HWND hWnd, D2GameResolutionMode nResolutionMode);
BOOL __fastcall D2SDLRender_CloseSurface();
void __fastcall D2SDLRender_PauseSurface(HWND hWnd, D2GameResolutionMode nResolutionMode, int32_t nWindowState);
