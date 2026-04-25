#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Options.h"

BOOL __fastcall D2SDLRender_SetOption(int32_t nOption, int32_t nValue) {
	FUNC_STUB_ARGS("D2SDLRender_SetOption", "nOption: %d, nValue: %d", nOption, nValue);
	return FALSE;
}

void __fastcall D2SDLRender_SetGlobalScale(int32_t nScaleFactor) {
	FUNC_STUB_ARGS("D2SDLRender_SetGlobalScale", "nScaleFactor: %d", nScaleFactor);
}

BOOL __fastcall D2SDLRender_SetGamma(int32_t nGamma) {
	FUNC_STUB_ARGS("D2SDLRender_SetGamma", "nGamma: %d", nGamma);
	return FALSE;
}

int32_t __fastcall D2SDLRender_GammaCanBeControlled() {
	FUNC_STUB("D2SDLRender_GammaCanBeControlled");
	return FALSE;
}
