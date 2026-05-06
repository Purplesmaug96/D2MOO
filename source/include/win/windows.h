#pragma once

#include <stdio.h>

typedef bool BOOL;

#define __stdcall
#define __cdecl

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}