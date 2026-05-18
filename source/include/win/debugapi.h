#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>

#define __debugbreak() printf("__debugbreak\n")

static inline void __windows_shim_OutputDebugStringA(const char* str, const char* file, const int line) {
	printf("OutputDebugStringA (%s:%d): %s\n", file, line, str);
}

#define OutputDebugStringA(str) __windows_shim_OutputDebugStringA(str, __FILE__, __LINE__)
