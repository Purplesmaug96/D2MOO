#pragma once

#include <string.h>
#include <sys/time.h>
#include <malloc.h>
#include <dlfcn.h>

#include <windef.h>
#include <winnt.h>
#include <timeapi.h>

static inline DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	strncpy(lpFilename, hModule->name, nSize);
	return TRUE;
}

static inline DWORD GetTickCount() {
	return timeGetTime();
	// timeval tv;
	// gettimeofday(&tv, 0);
	// unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	// return ms;
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

static inline FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	if (hModule == NULL) {
		printf("Failed to load symbol '%s' from hModule - hModule is NULL.\n", lpProcName);
	}

	void* ret = dlsym(hModule->dlHandle, lpProcName);

	if (ret == NULL) {
		printf("Failed to load symbol '%s' from '%s'.\n", lpProcName, hModule->name);
	}
	else {
		printf("Successfully loaded symbol '%s' from '%s'.\n", lpProcName, hModule->name);
	}

	return (FARPROC)ret;
}

static inline BOOL FreeLibrary(HMODULE hModule) {
	if (hModule == NULL) {
		printf("Failed to free hModule - hModule is NULL.\n");
		return FALSE;
	}

	if (hModule->dlHandle != NULL) {
		dlclose(hModule->dlHandle);
		printf("Successfully closed hModule->dlHandle from dynamic lib '%s'.\n", hModule->name);
		free(hModule);
		return TRUE;
	}
	else {
		printf("Failed to free dynamic lib '%s' - hModule->dlHandle is NULL.\n", hModule->name);
		return FALSE;
	}

	printf("Warning: impossible path taken in FreeLibrary, reaching this should not be possible. (%s:%u)\n", __FILE__, __LINE__);

	return FALSE;
}
