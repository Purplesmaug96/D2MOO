#pragma once

#include "__windows_shim_msvcrt.h"

#ifdef __linux__
#include <dlfcn.h>
#endif

#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "process.h"
#include "windef.h"
#include "winnt.h"

// Source - https://stackoverflow.com/a/4031835
// Posted by Fred Foo, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-15, License - CC BY-SA 2.5

static inline char* __windows_shim_program_path() {
	char* path = (char*)malloc(MAX_PATH);
	if (path != NULL) {
		if (readlink("/proc/self/exe", path, MAX_PATH) == -1) {
			free(path);
			path = NULL;
		}
	}
	return path;
}

static inline DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	if (hModule == NULL) {
		char* fileName = __windows_shim_program_path();
		if (fileName == NULL) {
			return FALSE;
		}
		strncpy(lpFilename, fileName, nSize);
		free(fileName);
		return TRUE;
	}
	strncpy(lpFilename, hModule->name, nSize);
	return TRUE;
}

#ifdef __linux__

static inline FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

static inline HMODULE LoadLibraryA(LPCSTR lpLibFileName) {
	printf("Attempting to load dynamic lib '%s'.\n", lpLibFileName);
	HMODULE lib = (HMODULE)malloc(sizeof(__windows_shim_struct_HMODULE));

	lib->name = (char*)lpLibFileName;
	lib->dlHandle = dlopen(lpLibFileName, RTLD_LAZY);

	if (lib->dlHandle == NULL) {
		printf("Failed to load dynamic lib '%s'.\n", lib->name);
		free(lib);
		return NULL;
	} else {
		printf("Successfully loaded dynamic lib '%s'.\n", lib->name);
		BOOL(__stdcall * DllMain)(HINSTANCE, DWORD, void*) = (BOOL(__stdcall*)(HINSTANCE, DWORD, void*))GetProcAddress(lib, "DllMain");

		if (DllMain(lib, DLL_PROCESS_ATTACH, NULL)) {
			printf("Successfully called DllMain.\n");
		} else {
			printf("Call to DllMain failed.\n");
		}
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
	} else {
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
	} else {
		printf("Failed to free dynamic lib '%s' - hModule->dlHandle is NULL.\n", hModule->name);
		return FALSE;
	}

	printf("Warning: impossible path taken in FreeLibrary, reaching this should not be possible. (%s:%u)\n", __FILE__, __LINE__);

	return FALSE;
}

#else

static inline HMODULE LoadLibraryA(LPCSTR lpLibFileName) {
	printf("Stubbed function LoadLibraryA called (only supported on linux)\n");
	return NULL;
}

static inline FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	printf("Stubbed function GetProcAddress called (only supported on linux)\n");
	return NULL;
}

static inline BOOL FreeLibrary(HMODULE hModule) {
	printf("Stubbed function FreeLibrary called (only supported on linux)\n");
	return FALSE;
}

#endif

static inline HMODULE GetModuleHandleA(LPCSTR lpModuleName) {
	printf("Stubbed function GetModuleHandleA called\n");
	return NULL;
}