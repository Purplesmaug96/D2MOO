#include "D2Gfx.h"
#include <cassert>
#include <cstddef>
#include <malloc.h>

#define _D2SDLRENDER_CPP
#include "D2SDLRender.h"

#include "Cell.h"
#include "Cutscene.h"
#include "Draw.h"
#include "Options.h"
#include "Perspective.h"
#include "Surface.h"
#include "Texture.h"
#include "Tile.h"
#include "Utils.h"

D2GraphicsInterfaceStrc* Interface;
SDL_Window* window;
SDL_Renderer* renderer;
uint32_t rendererFlags;

BOOL __fastcall D2SDLRender_pfInit(D2GfxSettingsStrc* pSettings, const D2GfxHelperStrc* pHelpers) {
	FUNC_LOG_ARGS("D2SDLRender_pfInit", "pSettings: %p, pHelpers: %p", pSettings, pHelpers);
	window = NULL;
	renderer = NULL;
	return TRUE;
}

BOOL __fastcall D2SDLRender_pfClose() {
	FUNC_LOG("D2SDLRender_pfClose");
	window = NULL;
	renderer = NULL;
	return TRUE;
}

bool D2SDLRender_Init() {
#ifdef _WIN32
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif

	FUNC_LOG("D2SDLRender_Init");
	Interface = (D2GraphicsInterfaceStrc*)malloc(sizeof(D2GraphicsInterfaceStrc));
	assert(Interface != NULL);

	// Function assignments
	Interface->pfDetect = &D2SDLRender_Detect;
	Interface->pfInit = &D2SDLRender_pfInit;
	Interface->pfClose = &D2SDLRender_pfClose;
	Interface->pfCreateSurface = (BOOL(__fastcall*)(HWND, D2GameResolutionMode))(&D2SDLRender_CreateSurface);
	Interface->pfCloseSurface = (BOOL(__fastcall*)())(&D2SDLRender_CloseSurface);
	Interface->pfPauseSurface = (void(__fastcall*)(HWND, D2GameResolutionMode, int32_t))(&D2SDLRender_PauseSurface);
	Interface->pfStartDraw = &D2SDLRender_StartDraw;
	Interface->pfEndDraw = &D2SDLRender_EndDraw;
	Interface->pfBlit = &D2SDLRender_Blit;
	Interface->pfChangeRes = (BOOL(__fastcall*)(HWND, D2GameResolutionMode))(&D2SDLRender_ChangeRes);
	Interface->pfGetBackBuffer = &D2SDLRender_GetBackBuffer;
	Interface->pfActivateWindow = &D2SDLRender_ActivateWindow;
	Interface->pfSetOption = &D2SDLRender_SetOption;
	Interface->pfPlayCutscene = &D2SDLRender_PlayCutscene;
	Interface->pfOpenSmackCutscene = &D2SDLRender_OpenSmackCutscene;
	Interface->pfCheckCutScene = &D2SDLRender_CheckCutScene;
	Interface->pfDecodeSmacker = &D2SDLRender_DecodeSmacker;
	Interface->pfPlaySmacker = &D2SDLRender_PlaySmacker;
	Interface->pfCloseSmacker = &D2SDLRender_CloseSmacker;
	Interface->pfGetCacheResults = &D2SDLRender_GetCacheResults;
	Interface->pfGetDimensions = &D2SDLRender_GetDimensions;
	Interface->pfSetGlobalScale = &D2SDLRender_SetGlobalScale;
	Interface->pfSetGamma = &D2SDLRender_SetGamma;
	Interface->pfGammaCanBeControlled = &D2SDLRender_GammaCanBeControlled;
	Interface->pfUpdatePerspective = &D2SDLRender_UpdatePerspective;
	Interface->pfPerspectiveTransform = &D2SDLRender_PerspectiveTransform;
	Interface->pfPerspectiveTransformScale = &D2SDLRender_PerspectiveTransformScale;
	Interface->pfPerspectiveClearScale = &D2SDLRender_PerspectiveClearScale;
	Interface->pfSetPalette = &D2SDLRender_SetPalette;
	Interface->pfSetPaletteTables = &D2SDLRender_SetPaletteTables;
	Interface->pfSetAmbientColor = &D2SDLRender_SetAmbientColor;
	Interface->pfFloorTileDraw = &D2SDLRender_FloorTileDraw;
	Interface->pfCelFlatSpriteDraw = &D2SDLRender_CelFlatSpriteDraw;
	Interface->pfCelDraw = &D2SDLRender_CelDraw;
	Interface->pfCelDrawColor = &D2SDLRender_CelDrawColor;
	Interface->pfCelDrawEx = &D2SDLRender_CelDrawEx;
	Interface->pfCelDrawShadow = &D2SDLRender_CelDrawShadow;
	Interface->pfCelDrawHilight = &D2SDLRender_CelDrawHilight;
	Interface->pfCelDrawClipped = &D2SDLRender_CelDrawClipped;
	Interface->pfTileDrawLit = &D2SDLRender_TileDrawLit;
	Interface->pfTileDrawTrans = &D2SDLRender_TileDrawTrans;
	Interface->pfShadowTileDraw = &D2SDLRender_ShadowTileDraw;
	Interface->pfUtilDiamond = &D2SDLRender_UtilDiamond;
	Interface->pfUtilRect = &D2SDLRender_UtilRect;
	Interface->pfUtilFilledRect = &D2SDLRender_UtilFilledRect;
	Interface->pfUtilPoint = &D2SDLRender_UtilPoint;
	Interface->pfDrawBox = &D2SDLRender_DrawBox;
	Interface->pfDrawBoxAlpha = &D2SDLRender_DrawBoxAlpha;
	Interface->pfDrawLine = &D2SDLRender_DrawLine;
	Interface->pfClearScreen = &D2SDLRender_ClearScreen;
	Interface->pfOutputString = &D2SDLRender_OutputString;
	Interface->pfDebugDraw = &D2SDLRender_DebugDraw;
	Interface->pfDebugFillBackBuffer = &D2SDLRender_DebugFillBackBuffer;
	Interface->pfClearCaches = &D2SDLRender_ClearCaches;
	return TRUE;
}

extern "C" {
D2GraphicsInterfaceStrc* GraphicsInterface() {
	return Interface;
}
}
