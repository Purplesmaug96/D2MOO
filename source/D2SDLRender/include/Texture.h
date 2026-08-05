#pragma once

#include <SDL2/SDL.h>

#define CEL_TEXTURE_POOL_SIZE 1024

#ifndef _TEXTURE_CPP
extern LPPALETTEENTRY gPalette;
extern D2PaletteTableStrc* gPaletteTables;
#endif

#define PALETTE_SIZE 256

void __fastcall D2SDLRender_SetPalette(LPPALETTEENTRY pPalette);
void __fastcall D2SDLRender_SetPaletteTables(D2PaletteTableStrc* pPaletteTables);

typedef struct {
	SDL_Texture* texture;
	uint32_t nWidth;
	uint32_t nHeight;
	int32_t nXOffset;
	int32_t nYOffset;
} CelTextureStrc;

CelTextureStrc GetTexFromCel(D2GfxDataStrc* pData);
