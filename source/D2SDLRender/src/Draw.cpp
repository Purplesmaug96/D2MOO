#include <windows.h>
#include <malloc.h>

typedef unsigned int uint;

#include <SDL_image.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#define _DRAW_CPP
#include "Draw.h"

#include "Texture.h"

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
