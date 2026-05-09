#pragma once

#include <stdio.h>

#define __debugbreak() printf("__debugbreak\n")

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}
