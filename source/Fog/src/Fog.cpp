#include <D2Dll.h>

#undef D2FUNC_DLL
#define D2FUNC_DLL D2FUNC_DLL_STUB

#include <Fog.h>

// Fog.#10227
int __fastcall FOG_IsExpansion() {
	return (int)false;
}
