#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Utils.h"
#include "Options.h"

// No idea what this is supposed to do, but returning TRUE gets it to keep running, so.
BOOL __fastcall D2SDLRender_Detect(HINSTANCE hInst) {
	FUNC_LOG_ARGS("D2SDLRender_Detect", "hInst: %p", hInst);
	return TRUE;
}

void* __fastcall D2SDLRender_GetCacheResults() {
	FUNC_STUB("D2SDLRender_GetCacheResults");
	return NULL;
}

BOOL __fastcall D2SDLRender_GetDimensions(int32_t* pWidth, int32_t* pHeight) {
	FUNC_LOG_ARGS("D2SDLRender_GetDimensions", "pWidth: %p, pHeight: %p", pWidth, pHeight);
	*pWidth = nResW;
	*pHeight = nResH;
	return TRUE;
}

void __fastcall D2SDLRender_UtilDiamond(RECT* pRect, uint8_t nPaletteIndex) {
	FUNC_STUB_ARGS("D2SDLRender_UtilDiamond", "pRect: %p, nPaletteIndex: %u", pRect, nPaletteIndex);
}

void __fastcall D2SDLRender_UtilRect(RECT* pRect, uint8_t nPaletteIndex) {
	FUNC_STUB_ARGS("D2SDLRender_UtilRect", "pRect: %p, nPaletteIndex: %u", pRect, nPaletteIndex);
}

void __fastcall D2SDLRender_UtilFilledRect(RECT* pRect, uint8_t nPaletteIndex) {
	FUNC_STUB_ARGS("D2SDLRender_UtilFilledRect", "pRect: %p, nPaletteIndex: %u", pRect, nPaletteIndex);
}

void __fastcall D2SDLRender_UtilPoint(POINT* pPoint, uint8_t nSize, uint8_t nPaletteIndex) {
	FUNC_STUB_ARGS("D2SDLRender_UtilPoint", "pPoint: %p, nSize: %u, nPaletteIndex: %u", pPoint, nSize, nPaletteIndex);
}

void __fastcall D2SDLRender_ClearCaches() {
	FUNC_STUB("D2SDLRender_ClearCaches");
}
