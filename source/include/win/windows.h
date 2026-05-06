#pragma once

#include <stdio.h>
#include <stdint.h>

typedef bool BOOL;
typedef uint32_t DWORD;

#define __stdcall
#define __cdecl

typedef void* HANDLE;

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}