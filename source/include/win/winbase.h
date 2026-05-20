#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>
#include <string.h>

#if defined(__linux__) || defined(__ANDROID__)
#include <sys/mman.h>
#endif

#include <sys/types.h>
#include <unistd.h>

#include "windef.h"

static inline DWORD GetLogicalDriveStringsA(DWORD nBufferLength, LPSTR lpBuffer) {
	return 0; // Length written
}

static inline LPSTR lstrcpyA(LPSTR lpString1, LPCSTR lpString2) {
	return strcpy(lpString1, lpString2);
}

static inline LPSTR lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength) {
	return strncpy(lpString1, lpString2, iMaxLength);
}

static inline LPSTR lstrcatA(LPSTR lpString1, LPCSTR lpString2) {
	return strcat(lpString1, lpString2);
}

static inline BOOL IsBadCodePtr(FARPROC lpfn) {
	if (lpfn == NULL) {
		return FALSE;
	}

#if defined(__linux__) || defined(__ANDROID__)
	// Taken from https://renatocunha.com/2015/12/msync-pointer-validity/

	/* get the page size */
	size_t page_size = sysconf(_SC_PAGESIZE);
	/* find the address of the page that contains p */
	void* base = (void*)((((size_t)lpfn) / page_size) * page_size);
	/* call msync, if it returns non-zero, return false */
	return msync(base, page_size, MS_ASYNC) == 0;
#endif
}

static inline DWORD GetCurrentDirectoryA(DWORD nBufferLength, LPTSTR lpBuffer) {
	printf("Stubbed function GetCurrentDirectoryA called\n");
	return 0; // Chars written
}

static inline BOOL SetCurrentDirectoryA(LPCTSTR lpPathName) {
	printf("Stubbed function SetCurrentDirectory called\n");
	return FALSE;
}

static inline /* MS docs say it's a UINT, but that would cause underflow if nDefault is negetive */ int GetPrivateProfileIntA(LPCSTR lpAppName, LPCSTR lpKeyName, int nDefault, LPCSTR lpFileName) {
	printf("Stubbed function GetProfileIntA called\n");
	return nDefault;
}

static inline DWORD GetPrivateProfileStringA(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, DWORD nSize, LPCSTR lpFileName) {
	printf("Stubbed function GetPrivateProfileStringA called\n");
	return 0;
}
