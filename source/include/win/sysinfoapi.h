#pragma once

#include <time.h>

#include <windef.h>
#include <minwinbase.h>

typedef struct {
	DWORD dwOSVersionInfoSize;
	uint8_t dwPlatformId;
} OSVERSIONINFOA;

#define VER_PLATFORM_WIN32_NT 0
static inline BOOL GetVersionExA(OSVERSIONINFOA* verInfo) {
	verInfo->dwPlatformId = VER_PLATFORM_WIN32_NT;
	return TRUE;
}

static inline void GetSystemTime(SYSTEMTIME* lpSystemTime) {
	if (lpSystemTime == NULL) {return;}
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

