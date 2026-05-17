#include <windef.h>
#include <winnt.h>
#include <process.h>

extern "C" {
	BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved) {
		return TRUE;
	}
}