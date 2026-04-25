#include <Windows.h>
#include "D2SDLRender.h"

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			return D2SDLRender_Init();
			break;

		default:
			return FALSE;
			break;
	}
	
}
