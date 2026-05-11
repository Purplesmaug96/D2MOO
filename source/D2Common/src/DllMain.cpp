#include <windef.h>
#include <process.h>
#include <winnt.h>
#include <libloaderapi.h>

#include <Imports/DllBases.h>

#ifdef _WIN32

HMODULE delayedD2CMPDllBaseGet()
{
	static HMODULE DLLBASE_D2CMP = LoadLibraryA("D2CMP.dll");
	return DLLBASE_D2CMP;
}

HMODULE delayedD2LANGDllBaseGet()
{
	static HMODULE DLLBASE_D2LANG = LoadLibraryA("D2Lang.dll");
	return DLLBASE_D2LANG;
}

HMODULE delayedFOGDllBaseGet() {
	static HMODULE DLLBASE_FOG = LoadLibraryA("Fog.dll");
	return DLLBASE_FOG;
}

#else

HMODULE delayedD2CMPDllBaseGet()
{
	static HMODULE DLLBASE_D2CMP = LoadLibraryA("libD2CMP.so");
	return DLLBASE_D2CMP;
}

HMODULE delayedD2LANGDllBaseGet()
{
	static HMODULE DLLBASE_D2LANG = LoadLibraryA("libD2Lang.so");
	return DLLBASE_D2LANG;
}

HMODULE delayedFOGDllBaseGet() {
	static HMODULE DLLBASE_FOG = LoadLibraryA("libFog.so");
	return DLLBASE_FOG;
}

#endif

// NOLINTBEGIN(bugprone-branch-clone)
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}
// NOLINTEND(bugprone-branch-clone)
