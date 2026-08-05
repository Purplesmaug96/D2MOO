#include <stdint.h>

#include <SDL2/SDL.h>

#include "D2SDLRender.h"

#include "Texture.h"

#include "Draw.h"

#include "Cell.h"

#include "D2Gfx.h"

static void DrawCel(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY) {
	CelTextureStrc celTex = GetTexFromCel(pData);
	if (celTex.texture == NULL) {
		return;
	}
	RenderSquare(celTex.texture,
				 nPosX - celTex.nXOffset,
				 nPosY - celTex.nYOffset,
				 nPosX - celTex.nXOffset + (float)celTex.nWidth,
				 nPosY - celTex.nYOffset + (float)celTex.nHeight,
				 255, 255, 255);
}

void __fastcall D2SDLRender_CelFlatSpriteDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nScreenMode, uint8_t* pPalette) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelFlatSpriteDraw", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, nScreenMode: %d, pPalette: %p", pData, nPosX, nPosY, dwGamma, eDrawMode, nScreenMode, pPalette);

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, uint8_t* pPalette) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDraw", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, pPalette: %p", pData, nPosX, nPosY, dwGamma, eDrawMode, pPalette);

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDrawColor(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nGlobalPaletteShift) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawColor", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, nGlobalPaletteShift: %d", pData, nPosX, nPosY, dwGamma, eDrawMode, nGlobalPaletteShift);

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDrawEx(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, int32_t nSkipLines, int32_t nDrawLines, DrawMode eDrawMode) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawEx", "pData: %p, nPosX: %d, nPosY: %d, nSkipLines: %d, nDrawLines: %d, eDrawMode: %d", pData, nPosX, nPosY, nSkipLines, nDrawLines, eDrawMode);

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDrawShadow(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawShadow", "pData: %p, nPosX: %d, nPosY: %d", pData, nPosX, nPosY);

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDrawHilight(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint8_t nPaletteIndex) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawHilight", "pData: %p, nPosX: %d, nPosY: %d, nPaletteIndex: %u");

	DrawCel(pData, nPosX, nPosY);
}

void __fastcall D2SDLRender_CelDrawClipped(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, void* pCropRect, DrawMode eDrawMode) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawClipped", "pData: %p, nPosX: %d, nPosY: %d, pCropRect: %p, eDrawMode: %d", pData, nPosX, nPosY, pCropRect, eDrawMode);

	DrawCel(pData, nPosX, nPosY);
}
