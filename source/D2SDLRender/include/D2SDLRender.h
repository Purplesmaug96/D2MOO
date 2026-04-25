#pragma once

#include <cstddef>
#include "../../D2Gfx/include/D2Gfx.h"

#ifndef _D2SDLRENDER_CPP
D2GraphicsInterfaceStrc Interface;
#endif

bool D2SDLRender_Init();

D2GraphicsInterfaceStrc* D2SDLRender_GetGraphicsInterface();