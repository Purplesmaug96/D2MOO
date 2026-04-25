#pragma once

#include <windows.h>
#include <SDL2/SDL.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

// When things start getting implemented, all the HWNDs will be changed to SDL_Window
BOOL __fastcall D2SDLRender_CreateSurface(SDL_Window* pWindow, D2GameResolutionMode nResolutionMode);
BOOL __fastcall D2SDLRender_CloseSurface();
void __fastcall D2SDLRender_PauseSurface(SDL_Window* pWindow, D2GameResolutionMode nResolutionMode, int32_t nWindowState);

BOOL __fastcall D2SDLRender_ChangeRes(SDL_Window* pWindow, D2GameResolutionMode bForceResize);
BOOL __fastcall D2SDLRender_GetBackBuffer(uint8_t* pBuffer);
BOOL __fastcall D2SDLRender_ActivateWindow();