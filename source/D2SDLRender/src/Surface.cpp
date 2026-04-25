#include <windows.h>
#include <SDL2/SDL.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Surface.h"
#include "Options.h"

static void GetResFromResMode(uint16_t* w, uint16_t* h, D2GameResolutionMode nResolutionMode) {
	FUNC_LOG_ARGS("GetResFromResMode", "w: %p, h: %p, nResolutionMode: %d", w, h, nResolutionMode);
	switch (nResolutionMode)
	{
		case D2GAMERES_640x480:
			*w = 640;
			*h = 480;
			break;

		case D2GAMERES_800x600:
		case NUM_GAME_RESOLUTIONS:
			*w = 800;
			*h = 600;
			break;

		case D2GAMERES_1344x700:
			*w = 1344;
			*h = 700;
			break;

		default:
			static char szLocalBuffer[256];
			sprintf(szLocalBuffer, "Unknown resolution %d", nResolutionMode);
			FUNC_ERR("GetResFromResMode", szLocalBuffer);
	}
}

BOOL __fastcall D2SDLRender_CreateSurface(SDL_Window* pWindow, D2GameResolutionMode nResolutionMode) {
	FUNC_LOG_ARGS("D2SDLRender_CreateSurface", "pWindow: %p, nResolutionMode: %d", pWindow, nResolutionMode);

	FUNC_ASSERT(window == NULL);
	window = pWindow;
	FUNC_ASSERT(window != NULL);
	FUNC_ASSERT(renderer == NULL);

	rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, 0, rendererFlags);

	GetResFromResMode(&nResW, &nResH, nResolutionMode);

	return TRUE;
}

BOOL __fastcall D2SDLRender_CloseSurface() {
	FUNC_LOG("D2SDLRender_CloseSurface");
	FUNC_ASSERT(window != NULL);
	FUNC_ASSERT(renderer != NULL);

	SDL_DestroyRenderer(renderer);

	return TRUE;
}

void __fastcall D2SDLRender_PauseSurface(SDL_Window* pWindow, D2GameResolutionMode nResolutionMode, int32_t nWindowState) {
	FUNC_STUB_ARGS("D2SDLRender_PauseSurface", "pWindow: %p, nResolutionMode: %d, nWindowState: %d", pWindow, nResolutionMode, nWindowState);
}

BOOL __fastcall D2SDLRender_ChangeRes(SDL_Window* pWindow, D2GameResolutionMode bForceResize) {
	FUNC_LOG_ARGS("D2SDLRender_ChangeRes", "pWindow: %p, bForceResize: %d", pWindow, bForceResize);
	GetResFromResMode(&nResW, &nResH, bForceResize);
	return TRUE;
}

BOOL __fastcall D2SDLRender_GetBackBuffer(uint8_t* pBuffer) {
	FUNC_STUB_ARGS("D2SDLRender_GetBackBuffer", "pBuffer: %p", pBuffer);
	return FALSE;
}

BOOL __fastcall D2SDLRender_ActivateWindow() {
	FUNC_STUB("D2SDLRender_ActivateWindow");
	return FALSE;
}
