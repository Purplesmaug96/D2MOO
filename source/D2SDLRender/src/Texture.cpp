#include <stdint.h>

#include <SDL2/SDL.h>

#include "D2SDLRender.h"

#define _TEXTURE_CPP
#include "Texture.h"

#include "D2Gfx.h"

LPPALETTEENTRY gPalette = NULL;
D2PaletteTableStrc* gPaletteTables = NULL;

void __fastcall D2SDLRender_SetPalette(LPPALETTEENTRY pPalette) {
	FUNC_LOG_ARGS("D2SDLRender_SetPalette", "pPalette: %p", pPalette);
	gPalette = pPalette;
}

void __fastcall D2SDLRender_SetPaletteTables(D2PaletteTableStrc* pPaletteTables) {
	FUNC_STUB_ARGS("D2SDLRender_SetPaletteTables", "pPaletteTables: %p", pPaletteTables);
	gPaletteTables = pPaletteTables;
}

SDL_Texture* cel_textures[CEL_TEXTURE_POOL_SIZE] = { NULL };

static uint32_t wang_32bit_mix(uint32_t a) {
	a = (a ^ 61) ^ (a >> 16);
	a = a + (a << 3);
	a = a ^ (a >> 4);
	a = a * 0x27d4eb2d;
	a = a ^ (a >> 15);
	return a;
}

static SDL_Texture* LoadTextureFromCel(D2GfxCellStrc* pCell, uint32_t nWidth, uint32_t nHeight) {
	if (pCell->pPixels == NULL || gPalette == NULL) {
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
										 SDL_TEXTUREACCESS_STATIC, nWidth, nHeight);
	if (!tex) {
		return NULL;
	}

	uint32_t len = (uint32_t)nWidth * (uint32_t)nHeight;
	uint8_t* pixels = (uint8_t*)malloc(len * 4); // 4 bytes per pixel (R8 G8 B8 A8)
	if (!pixels) {
		SDL_DestroyTexture(tex);
		return NULL;
	}

	for (uint32_t i = 0; i < len; ++i) {
		uint8_t colorIndex = pCell->pPixels[i];
		printf("pixel data: %u (%u %u %u)\n", colorIndex, gPalette[colorIndex].peRed, gPalette[colorIndex].peGreen, gPalette[colorIndex].peBlue);
		uint32_t base = i * 4;
		pixels[base + 0] = gPalette[colorIndex].peRed;	 // R
		pixels[base + 1] = gPalette[colorIndex].peGreen; // G
		pixels[base + 2] = gPalette[colorIndex].peBlue;	 // B
		pixels[base + 3] = 255;							 // A
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

SDL_Texture* GetTexFromCel(D2CellFileStrc* pCellFile, uint32_t* nWidth, uint32_t* nHeight) {
	// Doesn't seem to actually work if done by nFrame...
	D2GfxCellStrc* pCell = &pCellFile->pGfxCells[/*pData->nFrame % pData->pCellFile->nFrames*/ 0];

	*nWidth = pCell->dwWidth - pCell->nXOffset;
	*nHeight = pCell->dwHeight - pCell->nYOffset;

	uintptr_t ptrval = (uintptr_t)pCell;
	uint32_t key = wang_32bit_mix((uint32_t)(ptrval ^ (ptrval >> 32))) % CEL_TEXTURE_POOL_SIZE;

	if (cel_textures[key]) {
		return cel_textures[key];
	}

	SDL_Texture* tex = LoadTextureFromCel(pCell, pCell->dwWidth, pCell->dwHeight);
	if (tex) {
		cel_textures[key] = tex;
	}
	return tex;
}
