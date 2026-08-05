#include <stdint.h>
#include <stdarg.h>

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

#define CELFILE_VERSION 6
#define CELFILE_SERIALIZED 1
#define CELFILE_HARDWARE 2
#define CELFILE_24BIT 4

typedef struct {
	SDL_Texture* texture;
	D2GfxCellStrc* pCell;
	uint32_t nFrame;
	uint32_t nDirection;
} CelTextureCacheEntryStrc;

static CelTextureCacheEntryStrc cel_textures[CEL_TEXTURE_POOL_SIZE];

static uint32_t wang_32bit_mix(uint32_t a) {
	a = (a ^ 61) ^ (a >> 16);
	a = a + (a << 3);
	a = a ^ (a >> 4);
	a = a * 0x27d4eb2d;
	a = a ^ (a >> 15);
	return a;
}

static uint8_t* CelGetPixelData(D2GfxCellStrc* pCell) {
	return (uint8_t*)&pCell->pPixels;
}

static int32_t CelGameDirToFileDir(int32_t nGameDir, int32_t nDirections) {
	if (nDirections <= 0) {
		return 0;
	}
	if (nGameDir >= nDirections) {
		nGameDir = (2 * nDirections) - nGameDir - 1;
	}
	if (nGameDir < 0) {
		return 0;
	}
	return nGameDir;
}

static SDL_Texture* LoadTextureFromCel(D2GfxCellStrc* pCell) {
	const uint32_t nWidth = pCell->dwWidth;
	const uint32_t nHeight = pCell->dwHeight;

	if (nWidth == 0 || nHeight == 0 || gPalette == NULL) {
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
										 SDL_TEXTUREACCESS_STATIC, nWidth, nHeight);
	if (!tex) {
		return NULL;
	}
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	uint32_t len = nWidth * nHeight;
	uint8_t* pixels = (uint8_t*)malloc(len * 4); // 4 bytes per pixel (R8 G8 B8 A8)
	if (!pixels) {
		SDL_DestroyTexture(tex);
		return NULL;
	}

	const uint8_t* pSrc = CelGetPixelData(pCell);
	uint32_t nBudget = len * 2 + nHeight * 2;

	for (uint32_t nRow = 0; nRow < nHeight; ++nRow) {
		uint32_t nDestRow = (pCell->bFlip & 1) ? (nHeight - 1 - nRow) : nRow;
		uint8_t* pDest = pixels + (size_t)nDestRow * nWidth * 4;
		uint32_t nX = 0;

		while (nX < nWidth) {
			if (nBudget-- == 0) {
				break;
			}
			uint8_t nOp = *pSrc++;
			if (nOp == 0x80) {
				break; // end of row
			}
			uint32_t nCount = nOp & 0x7F;
			if (nCount > nWidth - nX) {
				nCount = nWidth - nX;
			}
			if (nOp & 0x80) {
				// transparent run
				memset(pDest + (size_t)nX * 4, 0, (size_t)nCount * 4);
			} else {
				// opaque run of nCount palette indices
				for (uint32_t i = 0; i < nCount; ++i) {
					uint8_t nIndex = *pSrc++;
					if (nIndex >= PALETTE_SIZE) {
						nIndex = 0;
					}
					uint8_t* pPx = pDest + (size_t)(nX + i) * 4;
					pPx[0] = gPalette[nIndex].peRed;
					pPx[1] = gPalette[nIndex].peGreen;
					pPx[2] = gPalette[nIndex].peBlue;
					pPx[3] = 255;
				}
			}
			nX += nCount;
		}
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

CelTextureStrc GetTexFromCel(D2GfxDataStrc* pData) {
	CelTextureStrc result;
	memset(&result, 0, sizeof(result));

	if (pData == NULL || pData->pCellFile == NULL || gPalette == NULL) {
		return result;
	}

	D2CellFileStrc* pCellFile = pData->pCellFile;

	D2GfxCellStrc* pCell = pData->pCurrentCell;
	if (pCell == NULL) {
		if (pCellFile->nFrames <= 0 || pCellFile->nDirections <= 0) {
			return result;
		}
		int32_t nFileDir = CelGameDirToFileDir((int32_t)pData->nDirection, pCellFile->nDirections);
		uint32_t nFrame = (uint32_t)pData->nFrame % (uint32_t)pCellFile->nFrames;

		// 1.10f D2CellFileStrc: the frame pointer table is INLINE at +0x18
		// (D2CMP_CelFileNormalize patches entries to absolute pointers in place;
		//  when it skips the patch the entries stay file-relative to pCellFile).
		D2GfxCellStrc** pFrames = (D2GfxCellStrc**)((uint8_t*)pCellFile + 0x18);
		uint32_t nIndex = (uint32_t)nFileDir * (uint32_t)pCellFile->nFrames + nFrame;
		uintptr_t entry = (uintptr_t)pFrames[nIndex];

		if (nFrame == 0) {
			uint32_t* dump = (uint32_t*)pCellFile;
			for (int i = 0; i < 2; i++) {
				uintptr_t e = (uintptr_t)pFrames[i];
				if (e >= 0x10000u) {
					uint32_t* d = (uint32_t*)(uintptr_t)e;
				}
			}
		}

		if (entry >= 0x10000u) {
			MEMORY_BASIC_INFORMATION mbi;
			if (VirtualQuery((LPCVOID)entry, &mbi, sizeof(mbi)) && mbi.State == MEM_COMMIT) {
				D2GfxCellStrc* c = (D2GfxCellStrc*)entry;
				if ((c->bFlip == 0 || c->bFlip == 1) && c->dwWidth > 0 && c->dwWidth < 4096 &&
					c->dwHeight > 0 && c->dwHeight < 4096 && c->dwLength < 0x100000) {
					pCell = c;
				}
			}
		}
		if (pCell == NULL) {
			D2GfxCellStrc* c = (D2GfxCellStrc*)((uint8_t*)pCellFile + entry);
			if ((c->bFlip == 0 || c->bFlip == 1) && c->dwWidth > 0 && c->dwWidth < 4096 &&
				c->dwHeight > 0 && c->dwHeight < 4096 && c->dwLength < 0x100000) {
				pCell = c;
			} else {
				return result;
			}
		}
	}

	if (pCell == NULL) {
		return result;
	}

	result.nWidth = pCell->dwWidth;
	result.nHeight = pCell->dwHeight;
	result.nXOffset = pCell->nXOffset;
	result.nYOffset = pCell->nYOffset;

	uintptr_t ptrval = (uintptr_t)pCell;
	uint64_t ptr64 = (uint64_t)ptrval;
	uint32_t key = wang_32bit_mix((uint32_t)(ptr64 ^ (ptr64 >> 32))) % CEL_TEXTURE_POOL_SIZE;

	CelTextureCacheEntryStrc* pEntry = &cel_textures[key];
	if (pEntry->texture && pEntry->pCell == pCell && pEntry->nFrame == pData->nFrame && pEntry->nDirection == pData->nDirection) {
		result.texture = pEntry->texture;
		return result;
	}

	SDL_Texture* tex = LoadTextureFromCel(pCell);
	if (tex) {
		if (pEntry->texture) {
			SDL_DestroyTexture(pEntry->texture);
		}
		pEntry->texture = tex;
		pEntry->pCell = pCell;
		pEntry->nFrame = pData->nFrame;
		pEntry->nDirection = pData->nDirection;
		result.texture = tex;
	}
	return result;
}
