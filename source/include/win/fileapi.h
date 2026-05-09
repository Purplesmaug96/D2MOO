#pragma once

#include <windef.h>

typedef struct {} FILETIME;

typedef FILETIME* LPFILETIME;

enum {
	DRIVE_UNKNOWN=0,
	DRIVE_NO_ROOT_DIR,
	DRIVE_REMOVABLE,
	DRIVE_FIXED,
	DRIVE_REMOTE,
	DRIVE_CDROM,
	DRIVE_RAMDISK
};

static inline UINT GetDriveTypeA(LPCSTR lpRootPathName) {
	return DRIVE_UNKNOWN;
}
