#include "AsyncData.h"

#include "Storm.h"

uint32_t gFileDirectAccessFlags;

char* gFileBasePath;

// Fog.#10101
BOOL __fastcall FOG_MPQSetConfig(uint32_t dwDirectAccessFlags, int bEnableSeekOptimization) {
	BOOL bSuccess;
	// undefined4 uStack_8;
	// undefined4 uStack_4;

	/* 0x11590  10101   */
	SFileSetBasePath(gFileBasePath);
	SFileEnableDirectAccess((HANDLE)dwDirectAccessFlags);
	SFileSetIoErrorMode(0, 0);
	SFileEnableSeekOptimization(bEnableSeekOptimization);
	// uStack_4 = 0x8000;
	gFileDirectAccessFlags = dwDirectAccessFlags;
	StormSetOption(2, /*(int)&uStack_4*/ 0x8000, 4);
	// uStack_8 = 1;
	StormSetOption(1, /*(int)&uStack_8*/ 1, 4);
	bSuccess = StormSetOption(3, /*(int)&uStack_8*/ 1, 4);
	return bSuccess;
}

// Fog.#10117
BOOL FOG_UseDirect() {
	/* 0x11a10  10117   */
	return gFileDirectAccessFlags;
}
