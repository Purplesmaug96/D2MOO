#pragma once

#include <windef.h>

typedef struct {
	DWORD dwOSVersionInfoSize;
	uint8_t dwPlatformId;
} OSVERSIONINFOA;

#define VER_PLATFORM_WIN32_NT 0
static inline BOOL GetVersionExA(OSVERSIONINFOA* verInfo) {
	verInfo->dwPlatformId = VER_PLATFORM_WIN32_NT;
	return TRUE;
}
