#include <windows.h>
#include <SDL2/SDL.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Surface.h"

BOOL __fastcall D2SDLRender_CreateSurface(SDL_Window* window, D2GameResolutionMode nResolutionMode) {
	FUNC_STUB_ARGS("D2SDLRender_CreateSurface", "window: %p, nResolutionMode: %d", window, nResolutionMode);
	return FALSE;
}

BOOL __fastcall D2SDLRender_CloseSurface() {
	FUNC_STUB("D2SDLRender_CloseSurface");
	return FALSE;
}

void __fastcall D2SDLRender_PauseSurface(SDL_Window* window, D2GameResolutionMode nResolutionMode, int32_t nWindowState) {
	FUNC_STUB_ARGS("D2SDLRender_PauseSurface", "window: %p, nResolutionMode: %d, nWindowState: %d", window, nResolutionMode, nWindowState);
}

BOOL __fastcall D2SDLRender_ChangeRes(SDL_Window* window, D2GameResolutionMode bForceResize) {
	FUNC_STUB_ARGS("D2SDLRender_ChangeRes", "window: %p, bForceResize: %d", window, bForceResize);
	return FALSE;
}

BOOL __fastcall D2SDLRender_GetBackBuffer(uint8_t* pBuffer) {
	FUNC_STUB_ARGS("D2SDLRender_GetBackBuffer", "pBuffer: %p", pBuffer);
	return FALSE;
}

BOOL __fastcall D2SDLRender_ActivateWindow() {
	FUNC_STUB("D2SDLRender_ActivateWindow");
	return FALSE;
}
