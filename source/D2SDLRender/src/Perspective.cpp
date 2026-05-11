#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Perspective.h"

void __fastcall D2SDLRender_UpdatePerspective(int32_t nScaleX, int32_t nScaleY) {
	FUNC_STUB_ARGS("D2SDLRender_UpdatePerspective", "nScaleX: %d, nScaleY: %d", nScaleX, nScaleY);
}

void __fastcall D2SDLRender_PerspectiveTransform(int32_t nPosX, int32_t nPosY, int32_t nBais, int32_t* pXAdjust, int32_t* pYAdjust) {
	FUNC_STUB_ARGS("D2SDLRender_PerspectiveTransform", "nPosX: %d, nPosY: %d, nBais: %d, pXAdjust: %p, pYAdjust: %p", nPosX, nPosY, nBais, pXAdjust, pYAdjust);
}

void __fastcall D2SDLRender_PerspectiveTransformScale(int32_t nPosX, int32_t nPosY, int32_t nAngle, int32_t* pXAdjust, int32_t* pYAdjust, int32_t bOrder) {
	FUNC_STUB_ARGS("D2SDLRender_PerspectiveTransformScale", "nPosX: %d, nPosY: %d, nAngle: %d, pXAdjust: %p, pYAdjust: %p, bOrder: %d", nPosX, nPosY, nAngle, pXAdjust, pYAdjust, bOrder);
}

void __fastcall D2SDLRender_PerspectiveClearScale() {
	FUNC_STUB("D2SDLRender_PerspectiveClearScale");
}
