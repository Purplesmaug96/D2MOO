#include <D2Dll.h>
#include <stdarg.h>
#include <stdio.h>

#undef D2FUNC_DLL
#define D2FUNC_DLL D2FUNC_DLL_STUB

#include <Fog.h>

// Fog.#10227
int __fastcall FOG_IsExpansion() {
	return (int)false;
}

// Fog.#10018
const char* __cdecl FOG_csprintf(char* szDest, const char* szFormat, ...) {
	va_list args;

	va_start(args, szFormat);

	vsprintf(szDest, szFormat, args);

	return szDest;
}
