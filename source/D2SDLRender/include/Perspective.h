#pragma once

#include <windef.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

void __fastcall D2SDLRender_UpdatePerspective(int32_t nScaleX, int32_t nScaleY);
void __fastcall D2SDLRender_PerspectiveTransform(int32_t nPosX, int32_t nPosY, int32_t nBais, int32_t* pXAdjust, int32_t* pYAdjust);
void __fastcall D2SDLRender_PerspectiveTransformScale(int32_t nPosX, int32_t nPosY, int32_t nAngle, int32_t* pXAdjust, int32_t* pYAdjust, int32_t bOrder);
void __fastcall D2SDLRender_PerspectiveClearScale();