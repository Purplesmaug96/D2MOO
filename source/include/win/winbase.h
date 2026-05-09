#pragma once

#include <windef.h>
#include <string.h>

static inline DWORD GetLogicalDriveStringsA(DWORD nBufferLength,  LPSTR lpBuffer) {
	return 0; // Length written
}

static inline LPSTR lstrcpyA(LPSTR  lpString1, LPCSTR lpString2) {
	return strcpy(lpString1, lpString2);
}

static inline LPSTR lstrcpynA(LPSTR  lpString1, LPCSTR lpString2, int iMaxLength) {
	return strncpy(lpString1, lpString2, iMaxLength);
}

static inline LPSTR lstrcatA(LPSTR  lpString1, LPCSTR lpString2) {
	return strcat(lpString1, lpString2);
}
