#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>
#include <time.h>

#include "minwinbase.h"
#include "windef.h"

#include <timeapi.h>

typedef struct {
	DWORD dwOSVersionInfoSize;
	uint8_t dwPlatformId;
} OSVERSIONINFOA;

static inline DWORD GetVersion() {
	printf("Stubbed function GetVersion called\n");
	// Windows 10: major version 10, minor version 0
	// Format: low byte = major, next byte = minor, high word = build
	return (10) | (0 << 8) | (19045 << 16);
}

#define VER_PLATFORM_WIN32_NT 0
static inline BOOL GetVersionExA(OSVERSIONINFOA* verInfo) {
	verInfo->dwPlatformId = VER_PLATFORM_WIN32_NT;
	return TRUE;
}

static inline void GetSystemTime(SYSTEMTIME* lpSystemTime) {
	if (lpSystemTime == NULL) {
		return;
	}
	tm time;
	asctime(&time);

	lpSystemTime->wYear = time.tm_year;
	lpSystemTime->wMonth = time.tm_mon;
	lpSystemTime->wDay = time.tm_mday; // might be yday
	lpSystemTime->wDayOfWeek = time.tm_wday;
	lpSystemTime->wHour = time.tm_hour;
	lpSystemTime->wMinute = time.tm_min;
	lpSystemTime->wSecond = time.tm_sec;
	lpSystemTime->wMilliseconds = time.tm_sec / 1000.0f;
}

static inline void GetLocalTime(SYSTEMTIME* lpSystemTime) {
	return GetSystemTime(lpSystemTime);
}

static inline DWORD GetTickCount() {
	return timeGetTime();
	// timeval tv;
	// gettimeofday(&tv, 0);
	// unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	// return ms;
}
