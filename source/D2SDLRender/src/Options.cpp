#include "D2Gfx.h"

#include "D2SDLRender.h"

#define _OPTIONS_CPP
#include "Options.h"

int32_t options[D2SDLRENDER_OPTIONS_SIZE];

int32_t nGlobalScaleFactor;
int32_t nGlobalGamma;

uint16_t nResW;
uint16_t nResH;

BOOL __fastcall D2SDLRender_SetOption(int32_t nOption, int32_t nValue) {
	FUNC_LOG_ARGS("D2SDLRender_SetOption", "nOption: %d, nValue: %d", nOption, nValue);
	char errBuf[256];
	if (nOption >= D2SDLRENDER_OPTIONS_SIZE) {
		sprintf(errBuf, "nOption (%d) exeeded options[] size (%u).", nOption, D2SDLRENDER_OPTIONS_SIZE-1);
		FUNC_ERR("D2SDLRender_SetOption", errBuf);
		return FALSE;
	}
	return TRUE;
}

void __fastcall D2SDLRender_SetGlobalScale(int32_t nScaleFactor) {
	FUNC_LOG_ARGS("D2SDLRender_SetGlobalScale", "nScaleFactor: %d", nScaleFactor);
	nGlobalScaleFactor = nScaleFactor;
}

BOOL __fastcall D2SDLRender_SetGamma(int32_t nGamma) {
	FUNC_LOG_ARGS("D2SDLRender_SetGamma", "nGamma: %d", nGamma);
	nGlobalGamma = true;
	return TRUE;
}

int32_t __fastcall D2SDLRender_GammaCanBeControlled() {
	FUNC_LOG("D2SDLRender_GammaCanBeControlled");
	return TRUE;
}
