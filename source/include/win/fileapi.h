#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>

#include "windef.h"

typedef struct {
} FILETIME;

typedef FILETIME* LPFILETIME;

enum {
	DRIVE_UNKNOWN = 0,
	DRIVE_NO_ROOT_DIR,
	DRIVE_REMOVABLE,
	DRIVE_FIXED,
	DRIVE_REMOTE,
	DRIVE_CDROM,
	DRIVE_RAMDISK
};

static inline UINT GetDriveTypeA(LPCSTR lpRootPathName) {
	printf("Stubbed function GetDriveTypeA called\n");
	return DRIVE_UNKNOWN;
}

static inline DWORD GetFileAttributesA(LPCSTR lpFileName) {
	printf("Stubbed function GetFileAttributesA called\n");
	return -1; // INVALID_FILE_ATTRIBUTES, i think
}

static inline BOOL DeleteFileA(LPCSTR lpFileName) {
	printf("Stubbed function DeleteFileA called\n");
	return FALSE;
}
