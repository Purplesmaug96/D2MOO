#include <stdint.h>

#include <SDL2/SDL.h>

#include "D2SDLRender.h"

#include "Texture.h"

#include "Draw.h"

#include "Cell.h"

#include "D2Gfx.h"

void __fastcall D2SDLRender_CelFlatSpriteDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nScreenMode, uint8_t* pPalette) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelFlatSpriteDraw", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, nScreenMode: %d, pPalette: %p", pData, nPosX, nPosY, dwGamma, eDrawMode, nScreenMode, pPalette);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, uint8_t* pPalette) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDraw", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, pPalette: %p", pData, nPosX, nPosY, dwGamma, eDrawMode, pPalette);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDrawColor(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nGlobalPaletteShift) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawColor", "pData: %p, nPosX: %d, nPosY: %d, dwGamma: %u, eDrawMode: %d, nGlobalPaletteShift: %d", pData, nPosX, nPosY, dwGamma, eDrawMode, nGlobalPaletteShift);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDrawEx(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, int32_t nSkipLines, int32_t nDrawLines, DrawMode eDrawMode) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawEx", "pData: %p, nPosX: %d, nPosY: %d, nSkipLines: %d, nDrawLines: %d, eDrawMode: %d", pData, nPosX, nPosY, nSkipLines, nDrawLines, eDrawMode);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDrawShadow(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawShadow", "pData: %p, nPosX: %d, nPosY: %d", pData, nPosX, nPosY);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDrawHilight(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint8_t nPaletteIndex) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawHilight", "pData: %p, nPosX: %d, nPosY: %d, nPaletteIndex: %u");

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}

void __fastcall D2SDLRender_CelDrawClipped(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, void* pCropRect, DrawMode eDrawMode) {
	FUNC_LOGSEMI_ARGS("D2SDLRender_CelDrawClipped", "pData: %p, nPosX: %d, nPosY: %d, pCropRect: %p, eDrawMode: %d", pData, nPosX, nPosY, pCropRect, eDrawMode);

	uint32_t nWidth, nHeight;
	SDL_Texture* tex = GetTexFromCel(pData->pCellFile, &nWidth, &nHeight);

	RenderSquare(tex, nPosX, nPosY, nPosX + nWidth, nPosY + nHeight, 255, 0, 255);
}