#pragma once

#include <string.h>
#include <sys/time.h>
#include <malloc.h>
#include <dlfcn.h>

#include <windef.h>
#include <winnt.h>

static inline DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	strncpy(lpFilename, hModule->name, nSize);
	return TRUE;
}

static inline DWORD GetTickCount() {
	timeval tv;
	gettimeofday(&tv, 0);
	unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	return ms;
}

static inline HMODULE LoadLibraryA(LPCSTR lpLibFileName) {
	HMODULE lib = (HMODULE)malloc(sizeof(__windows_shim_struct_HMODULE));
	lib->name = (char*)lpLibFileName;
	lib->dlHandle = dlopen(lpLibFileName, RTLD_LAZY);
	if (lib->dlHandle == NULL) {
		printf("Failed to load dynamic lib '%s'.\n", lib->name);
	}
	else {
		printf("Successfully loaded dynamic lib '%s'.\n", lib->name);
	}
	return lib;
}
