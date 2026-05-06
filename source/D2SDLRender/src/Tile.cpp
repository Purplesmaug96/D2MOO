#include <stdint.h>

#include <SDL2/SDL.h>

#include "D2SDLRender.h"

#include "Texture.h"

#include "Draw.h"

#include "Tile.h"

#include "D2Gfx.h"

int32_t __fastcall D2SDLRender_FloorTileDraw(D2TileLibraryEntryStrc* pTile, D2GfxLightExStrc* pLight, int32_t nPosX, int32_t nPosY, int32_t nWorldXpos, int32_t nWorldYpos, uint8_t nAlpha, int32_t nScreenPanels, void* pTileData) {
	FUNC_STUB_ARGS("D2SDLRender_FloorTileDraw", "pTile: %p, pLight: %p, nPosX: %d, nPosY: %d, nWorldXpos: %d, nWorldYpos: %d, nAlpha: %u, nScreenPanels: %d, pTileData: %p", pTile, pLight, nPosX, nPosY, nWorldXpos, nWorldYpos, nAlpha, nScreenPanels, pTileData);
	return 0;
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
