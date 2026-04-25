#include <cstddef>
#include <malloc.h>
#include <cassert>
#include "D2Gfx.h"

#define _D2SDLRENDER_CPP
#include "D2SDLRender.h"

#include "Cutscene.h"
#include "Surface.h"
#include "Perspective.h"
#include "Options.h"
#include "Utils.h"

D2GraphicsInterfaceStrc* Interface;

BOOL __fastcall D2SDLRender_pfInit(D2GfxSettingsStrc* pSettings, const D2GfxHelperStrc* pHelpers) {
	FUNC_STUB_ARGS("D2SDLRender_pfInit", "pSettings: %p, pHelpers: %p", pSettings, pHelpers);
	return FALSE;
}

BOOL __fastcall D2SDLRender_pfClose() {
	FUNC_STUB("D2SDLRender_pfClose");
	return FALSE;
}

bool D2SDLRender_Init() {
	FUNC_STUB("D2SDLRender_Init");
	Interface = (D2GraphicsInterfaceStrc*)malloc(sizeof(D2GraphicsInterfaceStrc));
	assert(Interface != NULL);

	// Function assignments
	Interface->pfDetect = &D2SDLRender_Detect;
	Interface->pfInit = &D2SDLRender_pfInit;
	Interface->pfClose = &D2SDLRender_pfClose;
	Interface->pfCreateSurface = &D2SDLRender_CreateSurface;
	Interface->pfCloseSurface = &D2SDLRender_CloseSurface;
	Interface->pfPauseSurface = &D2SDLRender_PauseSurface;
	Interface->pfStartDraw = NULL;
	Interface->pfEndDraw = NULL;
	Interface->pfBlit = NULL;
	Interface->pfChangeRes = &D2SDLRender_ChangeRes;
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
	Interface->pfSetPalette = NULL;
	Interface->pfSetPaletteTables = NULL;
	Interface->pfSetAmbientColor = NULL;
	Interface->pfFloorTileDraw = NULL;
	Interface->pfCelFlatSpriteDraw = NULL;
	Interface->pfCelDraw = NULL;
	Interface->pfCelDrawColor = NULL;
	Interface->pfCelDrawEx = NULL;
	Interface->pfCelDrawShadow = NULL;
	Interface->pfCelDrawHilight = NULL;
	Interface->pfCelDrawClipped = NULL;
	Interface->pfTileDrawLit = NULL;
	Interface->pfTileDrawTrans = NULL;
	Interface->pfShadowTileDraw = NULL;
	Interface->pfUtilDiamond = &D2SDLRender_UtilDiamond;
	Interface->pfUtilRect = &D2SDLRender_UtilRect;
	Interface->pfUtilFilledRect = &D2SDLRender_UtilFilledRect;
	Interface->pfUtilPoint = &D2SDLRender_UtilPoint;
	Interface->pfDrawBox = NULL;
	Interface->pfDrawBoxAlpha = NULL;
	Interface->pfDrawLine = NULL;
	Interface->pfClearScreen = NULL;
	Interface->pfOutputString = NULL;
	Interface->pfDebugDraw = NULL;
	Interface->pfDebugFillBackBuffer = NULL;
	Interface->pfClearCaches = &D2SDLRender_ClearCaches;
	return TRUE;
}

D2GraphicsInterfaceStrc* D2SDLRender_GetGraphicsInterface() {
	return Interface;
}
