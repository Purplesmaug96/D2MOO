#include <cstddef>
#include <malloc.h>
#include <cassert>
#include "D2Gfx.h"

#define _D2SDLRENDER_CPP
#include "D2SDLRender.h"

D2GraphicsInterfaceStrc* Interface;

bool D2SDLRender_Init() {
	Interface = (D2GraphicsInterfaceStrc*)malloc(sizeof(D2GraphicsInterfaceStrc));
	assert(Interface != NULL);

	// Function assignments
	Interface->pfDetect = NULL;
	Interface->pfInit = NULL;
	Interface->pfClose = NULL;
	Interface->pfCreateSurface = NULL;
	Interface->pfCloseSurface = NULL;
	Interface->pfPauseSurface = NULL;
	Interface->pfStartDraw = NULL;
	Interface->pfEndDraw = NULL;
	Interface->pfBlit = NULL;
	Interface->pfChangeRes = NULL;
	Interface->pfGetBackBuffer = NULL;
	Interface->pfActivateWindow = NULL;
	Interface->pfSetOption = NULL;
	Interface->pfPlayCutscene = NULL;
	Interface->pfOpenSmackCutscene = NULL;
	Interface->pfCheckCutScene = NULL;
	Interface->pfDecodeSmacker = NULL;
	Interface->pfPlaySmacker = NULL;
	Interface->pfCloseSmacker = NULL;
	Interface->pfGetCacheResults = NULL;
	Interface->pfGetDimensions = NULL;
	Interface->pfSetGlobalScale = NULL;
	Interface->pfSetGamma = NULL;
	Interface->pfGammaCanBeControlled = NULL;
	Interface->pfUpdatePerspective = NULL;
	Interface->pfPerspectiveTransform = NULL;
	Interface->pfPerspectiveTransformScale = NULL;
	Interface->pfPerspectiveClearScale = NULL;
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
	Interface->pfUtilDiamond = NULL;
	Interface->pfUtilRect = NULL;
	Interface->pfUtilFilledRect = NULL;
	Interface->pfUtilPoint = NULL;
	Interface->pfDrawBox = NULL;
	Interface->pfDrawBoxAlpha = NULL;
	Interface->pfDrawLine = NULL;
	Interface->pfClearScreen = NULL;
	Interface->pfOutputString = NULL;
	Interface->pfDebugDraw = NULL;
	Interface->pfDebugFillBackBuffer = NULL;
	Interface->pfClearCaches = NULL;
	return TRUE;
}

D2GraphicsInterfaceStrc* D2SDLRender_GetGraphicsInterface() {
	return Interface;
}