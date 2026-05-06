#pragma once

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

typedef bool BOOL;
typedef uint32_t DWORD;

#define __stdcall
#define __cdecl
#define __fastcall

#define CALLBACK __stdcall

#define __declspec(x)

#define TRUE true
#define FALSE false

#define _Acquires_lock_(x)
#define _Releases_lock_(x)

#define _Curr_ NULL

typedef void* HANDLE;

typedef HANDLE HWND;
typedef HANDLE HRGN;
typedef HANDLE HMODULE;
typedef HANDLE HDC; // Device Context
typedef HANDLE HINSTANCE;
typedef HANDLE HGDIOBJ;
typedef HANDLE HKEY;

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPSTR;
typedef char* LPCSTR;
typedef DWORD* LPDWORD;
typedef uint8_t* LPBYTE;

typedef long LONG;
typedef unsigned long ULONG;
typedef uint UINT;
typedef uint8_t BYTE;
typedef size_t SIZE_T;

typedef int LCID;

enum {
	DLL_PROCESS_ATTACH=0,
	DLL_PROCESS_DETACH,
	DLL_THREAD_ATTACH,
	DLL_THREAD_DETACH
};

typedef struct {} CRITICAL_SECTION;

typedef struct {} SECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES LPSECURITY_ATTRIBUTES;

// Source - https://stackoverflow.com/a/19472847
// Posted by Reed Copsey
// Retrieved 2026-05-06, License - CC BY-SA 3.0

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);

typedef struct {
	DWORD dwOSVersionInfoSize;
	uint8_t dwPlatformId;
} OSVERSIONINFOA;

#define VER_PLATFORM_WIN32_NT 0
static inline BOOL GetVersionExA(OSVERSIONINFOA* verInfo) {
	verInfo->dwPlatformId = VER_PLATFORM_WIN32_NT;
	return TRUE;
}


static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}