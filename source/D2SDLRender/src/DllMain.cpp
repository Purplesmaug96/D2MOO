#include <Windows.h>
#include "D2SDLRender.h"

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	return D2SDLRender_Init();
}
