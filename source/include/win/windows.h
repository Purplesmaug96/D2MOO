#pragma once

#include <stdio.h>
#include <stdint.h>

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

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;

typedef void* LPVOID;
typedef char* LPCSTR;

typedef long LONG;

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}