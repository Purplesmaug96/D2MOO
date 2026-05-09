#pragma once

#include <string.h>
#include <sys/time.h>

#include <windef.h>
#include <winnt.h>

static inline DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	strncpy(lpFilename, "GetModuleFileNameA (stubbed)", nSize);
	return TRUE;
}

static inline DWORD GetTickCount() {
	timeval tv;
	gettimeofday(&tv, 0);
	unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	return ms;
}
