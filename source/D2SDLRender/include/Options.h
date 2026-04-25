#pragma once

#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#define D2SDLRENDER_OPTIONS_SIZE 256 // I have no idea what the actual max is

#ifndef _OPTIONS_CPP
extern int32_t options[D2SDLRENDER_OPTIONS_SIZE];

extern int32_t nGlobalScaleFactor;
extern int32_t nGlobalGamma;
#endif

BOOL __fastcall D2SDLRender_SetOption(int32_t nOption, int32_t nValue);

void __fastcall D2SDLRender_SetGlobalScale(int32_t nScaleFactor);

BOOL __fastcall D2SDLRender_SetGamma(int32_t nGamma);
int32_t __fastcall D2SDLRender_GammaCanBeControlled();
