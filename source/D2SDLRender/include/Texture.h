#pragma once

#include <SDL2/SDL.h>

#define CEL_TEXTURE_POOL_SIZE 1024

#ifndef _TEXTURE_CPP
extern SDL_Texture* cel_textures[CEL_TEXTURE_POOL_SIZE];
#endif

void __fastcall D2SDLRender_SetPalette(LPPALETTEENTRY pPalette);
void __fastcall D2SDLRender_SetPaletteTables(D2PaletteTableStrc* pPaletteTables);

SDL_Texture* GetTexFromCel(D2CellFileStrc* pCellFile, uint32_t* nWidth, uint32_t* nHeight);