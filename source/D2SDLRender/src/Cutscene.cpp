#include <windows.h>

#include "D2Gfx.h"

#include "D2SDLRender.h"

#include "Cutscene.h"

BOOL __fastcall D2SDLRender_PlayCutscene() {
	FUNC_STUB("D2SDLRender_PlayCutscene");
	return FALSE;
}

void __fastcall D2SDLRender_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolutionMode, void* pfFrame) {
	FUNC_STUB_ARGS("D2SDLRender_OpenSmackCutscene", "szFile: %s, nResolutionMode: %d, pfFrame: %p", szFile, nResolutionMode, pfFrame);
}

BOOL __fastcall D2SDLRender_CheckCutScene() {
	FUNC_STUB("D2SDLRender_CheckCutScene");
	return FALSE;
}

void __fastcall D2SDLRender_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion) {
	FUNC_STUB_ARGS("D2SDLRender_DecodeSmacker", "szSmacker: %s, pBuffer: %p, nVersion: %d", szSmacker, pBuffer, nVersion);
}

void __fastcall D2SDLRender_PlaySmacker(void* pContext) {
	FUNC_STUB_ARGS("D2SDLRender_PlaySmacker", "pContext: %p", pContext);
}

void __fastcall D2SDLRender_CloseSmacker(void* pContext) {
	FUNC_STUB_ARGS("D2SDLRender_CloseSmacker", "pContext: %p", pContext);
}