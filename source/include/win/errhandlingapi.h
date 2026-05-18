#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdint.h>

#ifdef __WINDOWS_SHIM_LASTERROR_LOCAL
#include "__windows_shim_local_lasterror.h"
#else
extern uint32_t __windows_LastError;
#endif

static inline void SetLastError(uint32_t errorCode) {
	__windows_LastError = errorCode;
}

static inline uint32_t /* Should be DWORD, but not defined here */ GetLastError() {
	return __windows_LastError;
}
