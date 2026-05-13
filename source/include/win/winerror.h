#pragma once

#include <stdint.h>

enum {
	ERROR_NONE=0, // Made up
	ERROR_FILE_NOT_FOUND,
	INVALID_SET_FILE_POINTER
};

#ifdef __WINDOWS_SHIM_LASTERROR_LOCAL
#include <__windows_shim_local_lasterror.h>
#else
extern uint32_t __winerror_LastError = ERROR_NONE;
#endif

static inline void SetLastError(uint32_t errorCode) {
	__winerror_LastError = errorCode;
}


static inline uint32_t /* Should be DWORD, but not defined here */ GetLastError() {
	return __winerror_LastError;
}
