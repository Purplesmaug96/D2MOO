#pragma once

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

typedef bool BOOL;
typedef uint32_t DWORD;

#define __stdcall
#define __cdecl
#define __fastcall

typedef void* HANDLE;

typedef HANDLE HWND;
typedef HANDLE HRGN;
typedef HANDLE HMODULE;
typedef HANDLE HDC; // Device Context
typedef HANDLE HINSTANCE;
typedef HANDLE HGDIOBJ;

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPCSTR;
typedef DWORD* LPDWORD;

typedef long LONG;
typedef uint UINT;

typedef int LCID;

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}