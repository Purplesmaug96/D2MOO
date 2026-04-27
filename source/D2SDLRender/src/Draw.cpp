#include <windows.h>
#include <malloc.h>

typedef unsigned int uint;

#include <SDL_image.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#define _DRAW_CPP
#include "Draw.h"

SDL_Texture* screenTexture;

uint8_t nAmbientRed = 0;
uint8_t nAmbientGreen = 0;
uint8_t nAmbientBlue = 0;

BOOL __fastcall D2SDLRender_StartDraw(int32_t bClear, uint8_t nRed, uint8_t nGreen, uint8_t nBlue) {
	FUNC_LOG_ARGS("D2SDLRender_StartDraw", "bClear: %d, nRed: %u, nGreen: %u, nBlue: %b", bClear, nRed, nGreen, nBlue);
	FUNC_ASSERT(screenTexture != NULL);
	SDL_SetRenderTarget(renderer, screenTexture);
	SDL_SetRenderDrawColor(renderer, nAmbientRed, nAmbientGreen, nAmbientBlue, 255);
	SDL_RenderClear(renderer);
	return TRUE;
}

BOOL __fastcall D2SDLRender_EndDraw() {
	FUNC_LOG("D2SDLRender_EndDraw");
	FUNC_ASSERT(screenTexture != NULL);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return TRUE;
}

BOOL __fastcall D2SDLRender_Blit() {
	FUNC_STUB("D2SDLRender_Blit");
	return FALSE;
}

void __fastcall D2SDLRender_SetPalette(LPPALETTEENTRY pPalette) {
	FUNC_STUB_ARGS("D2SDLRender_SetPalette", "pPalette: %p", pPalette);
}

void __fastcall D2SDLRender_SetPaletteTables(D2PaletteTableStrc* pPaletteTables) {
	FUNC_STUB_ARGS("D2SDLRender_SetPaletteTables", "pPaletteTables: %p", pPaletteTables);
}

void __fastcall D2SDLRender_SetAmbientColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue) {
	FUNC_LOG_ARGS("D2SDLRender_SetAmbientColor", "nRed: %u, nGreen: %u, nBlue: %u", nRed, nGreen, nBlue);
	nAmbientRed = nRed;
	nAmbientGreen = nGreen;
	nAmbientBlue = nBlue;
}


void RenderSquare(SDL_Texture* tex, float nStartPosX, float nStartPosY, float nEndPosX, float nEndPosY, uint8_t nRed, uint8_t nGreen, uint8_t nBlue) {
	SDL_Vertex verts[4];

	verts[0].position.x = nStartPosX;
	verts[0].position.y = nStartPosY;

	verts[1].position.x = nEndPosX;
	verts[1].position.y = nStartPosY;

	verts[2].position.x = nStartPosX;
	verts[2].position.y = nEndPosY;

	verts[3].position.x = nEndPosX;
	verts[3].position.y = nEndPosY;

	if (tex != NULL) {
		verts[0].tex_coord.x = 0.0f;
		verts[0].tex_coord.y = 0.0f;
		verts[1].tex_coord.x = 1.0f;
		verts[1].tex_coord.y = 0.0f;
		verts[2].tex_coord.x = 0.0f;
		verts[2].tex_coord.y = 1.0f;
		verts[3].tex_coord.x = 1.0f;
		verts[3].tex_coord.y = 1.0f;
	}

	for (int i = 0; i < 4; i++) {
		verts[i].color.r = nRed;
		verts[i].color.g = nGreen;
		verts[i].color.b = nBlue;
		verts[i].color.a = 255;
	}

	int indices[6] = { 0, 1, 2, 1, 3, 2 };
	SDL_RenderGeometry(renderer, tex, verts, 4, indices, 6);
}

#define CEL_TEXTURE_POOL_SIZE 1024

SDL_Texture* cel_textures[CEL_TEXTURE_POOL_SIZE] = {NULL};

uint32_t wang_32bit_mix(uint32_t a) {
	a = (a ^ 61) ^ (a >> 16);
	a = a + (a << 3);
	a = a ^ (a >> 4);
	a = a * 0x27d4eb2d;
	a = a ^ (a >> 15);
	return a;
}

SDL_Texture* LoadTextureFromCel(D2GfxCellStrc* pCell, uint32_t nWidth, uint32_t nHeight) {
	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC, nWidth, nHeight);
	if (!tex) return NULL;

	size_t len = (size_t)nWidth * (size_t)nHeight;
	uint8_t* pixels = (uint8_t*)malloc(len * 4); // 4 bytes per pixel (R8 G8 B8 A8)
	if (!pixels) { SDL_DestroyTexture(tex); return NULL; }

	for (size_t i = 0; i < len; ++i) {
		size_t base = i * 4;
		pixels[base + 0] = (uint8_t)i;    // R
		pixels[base + 1] = (uint8_t)i;    // G
		pixels[base + 2] = (uint8_t)i;    // B
		pixels[base + 3] = 255;           // A
	}

	int pitch = (int)(nWidth * 4);
	if (SDL_UpdateTexture(tex, NULL, pixels, pitch) != 0) {
		free(pixels);
		SDL_DestroyTexture(tex);
		return NULL;
	}

	free(pixels);
	return tex;
}
static SDL_Texture* GetTexFromCel(D2CellFileStrc* pCellFile, uint32_t* nWidth, uint32_t* nHeight) {
	// Doesn't seem to actually work if done by nFrame...
	D2GfxCellStrc* pCell = &pCellFile->pGfxCells[/*pData->nFrame % pData->pCellFile->nFrames*/0];

	*nWidth = pCell->dwWidth - pCell->nXOffset;
	*nHeight = pCell->dwHeight - pCell->nYOffset;

	uintptr_t ptrval = (uintptr_t)pCell;
	uint32_t key = wang_32bit_mix((uint32_t)(ptrval ^ (ptrval >> 32))) % CEL_TEXTURE_POOL_SIZE;

	if (cel_textures[key]) return cel_textures[key];

	SDL_Texture* tex = LoadTextureFromCel(pCell, *nWidth, *nHeight);
	if (tex) cel_textures[key] = tex;
	return tex;
}


int32_t __fastcall D2SDLRender_FloorTileDraw(D2TileLibraryEntryStrc* pTile, D2GfxLightExStrc* pLight, int32_t nPosX, int32_t nPosY, int32_t nWorldXpos, int32_t nWorldYpos, uint8_t nAlpha, int32_t nScreenPanels, void* pTileData) {
	FUNC_STUB_ARGS("D2SDLRender_FloorTileDraw", "pTile: %p, pLight: %p, nPosX: %d, nPosY: %d, nWorldXpos: %d, nWorldYpos: %d, nAlpha: %u, nScreenPanels: %d, pTileData: %p", pTile, pLight, nPosX, nPosY, nWorldXpos, nWorldYpos, nAlpha, nScreenPanels, pTileData);
	return 0;
}

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

int32_t __fastcall D2SDLRender_TileDrawLit(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels) {
	FUNC_STUB_ARGS("D2SDLRender_TileDrawLit", "pTile: %p, nPosX: %d, nPosY: %d, pLight: %p, nScreenPanels: %d", pTile, nPosX, nPosY, pLight, nScreenPanels);
	return 0;
}

int32_t __fastcall D2SDLRender_TileDrawTrans(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels, uint8_t nAlpha) {
	FUNC_STUB_ARGS("D2SDLRender_TileDrawTrans", "pTile: %p, nPosX: %d, nPosY: %d, pLight: %p, nScreenPanels: %d, nAlpha: %u", pTile, nPosX, nPosY, pLight, nScreenPanels, nAlpha);
	return 0;
}

int32_t __fastcall D2SDLRender_ShadowTileDraw(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, DrawMode eDrawMode, int32_t nScreenPanels) {
	FUNC_STUB_ARGS("D2SDLRender_ShadowTileDraw", "pTile: %p, nPosX: %d, nPosY: %d, eDrawMode: %d, nScreenPanels: %d", pTile, nPosX, nPosY, eDrawMode, nScreenPanels);
	return 0;
}

void __fastcall D2SDLRender_DrawBox(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, DrawMode eDrawMode) {
	FUNC_STUB_ARGS("D2SDLRender_DrawBox", "nXStart: %d, nYStart: %d, nXEnd: %d, nYEnd: %d, dwColor: %d, eDrawMode: %d", nXStart, nYStart, nXEnd, nYEnd, dwColor, eDrawMode);
}

void __fastcall D2SDLRender_DrawBoxAlpha(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha) {
	FUNC_STUB_ARGS("D2SDLRender_DrawBoxAlpha", "nXStart: %d, nYStart: %d, nXEnd: %d, nYEnd: %d, dwColor: %d, nAlpha: %u", nXStart, nYStart, nXEnd, nYEnd, dwColor, nAlpha);
}

void __fastcall D2SDLRender_DrawLine(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha) {
	FUNC_STUB_ARGS("D2SDLRender_DrawLine", "nXStart: %d, nYStart: %d, nXEnd: %d, nYEnd: %d, dwColor: %d, nAlpha: %u", nXStart, nYStart, nXEnd, nYEnd, dwColor, nAlpha);
}

void __fastcall D2SDLRender_ClearScreen(int32_t bPartial) {
	FUNC_STUB_ARGS("D2SDLRender_ClearScreen", "bPartial: %d", bPartial);
}

void __fastcall D2SDLRender_OutputString(int32_t nPosX, int32_t nPosY, const char* szFormat, va_list va) {
	FUNC_STUB_ARGS("D2SDLRender_OutputString", "nPosX: %, nPosY: %d, szFormat: %s, va: %p", nPosX, nPosY, szFormat, va);
}

void __fastcall D2SDLRender_DebugDraw(uint32_t* pLight, uint32_t* pPlayerLight, int32_t nPosX, int32_t nPosY) {
	FUNC_STUB_ARGS("D2SDLRender_DebugDraw", "pLight: %p, pPlayerLight: %p, nPosX: %d, nPosY: %d", pLight, pPlayerLight, nPosX, nPosY);
}

void __fastcall D2SDLRender_DebugFillBackBuffer(int32_t nPosX, int32_t nPosY) {
	FUNC_STUB_ARGS("D2SDLRender_DebugFillBackBuffer", "nPosX: %d, nPosY: %d", nPosX, nPosY);
}
