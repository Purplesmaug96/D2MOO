#pragma once

#include <stdint.h>

enum {
	ERROR_NONE=0, // Made up
	ERROR_FILE_NOT_FOUND,
	INVALID_SET_FILE_POINTER
};

uint32_t __winerror_LastError = ERROR_NONE;

static inline void /* Should be DWORD, but not defined here */ SetLastError(uint32_t errorCode) {
	__winerror_LastError = errorCode;
}


static inline uint32_t /* Should be DWORD, but not defined here */ GetLastError() {
	return __winerror_LastError;
}
