#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Surface.h"

BOOL __fastcall D2SDLRender_CreateSurface(HWND hWnd, D2GameResolutionMode nResolutionMode) {
	FUNC_STUB_ARGS("D2SDLRender_CreateSurface", "hWnd: %p, nResolutionMode: %d", hWnd, nResolutionMode);
	return FALSE;
}

BOOL __fastcall D2SDLRender_CloseSurface() {
	FUNC_STUB("D2SDLRender_CloseSurface");
	return FALSE;
}

void __fastcall D2SDLRender_PauseSurface(HWND hWnd, D2GameResolutionMode nResolutionMode, int32_t nWindowState) {
	FUNC_STUB_ARGS("D2SDLRender_PauseSurface", "hWnd: %p, nResolutionMode: %d, nWindowState: %d", hWnd, nResolutionMode, nWindowState);
}

BOOL __fastcall D2SDLRender_ChangeRes(HWND hWnd, D2GameResolutionMode bForceResize) {
	FUNC_STUB_ARGS("D2SDLRender_ChangeRes", "hWnd: %p, bForceResize: %d", hWnd, bForceResize);
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
