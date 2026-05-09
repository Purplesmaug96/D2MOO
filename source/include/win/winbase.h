#pragma once

#include <windef.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

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

static inline BOOL IsBadCodePtr(FARPROC lpfn) {
	if (lpfn == NULL) {return FALSE;}

	// Taken from https://renatocunha.com/2015/12/msync-pointer-validity/

	/* get the page size */
    size_t page_size = sysconf(_SC_PAGESIZE);
    /* find the address of the page that contains p */
    void *base = (void *)((((size_t)lpfn) / page_size) * page_size);
    /* call msync, if it returns non-zero, return false */
    return msync(base, page_size, MS_ASYNC) == 0;
}
