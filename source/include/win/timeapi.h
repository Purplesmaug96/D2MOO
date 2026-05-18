#pragma once

#include "__windows_shim_msvcrt.h"

#include <sys/time.h>

#include "windef.h"

static inline DWORD timeGetTime() {
	timeval tv;
	gettimeofday(&tv, 0);
	unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	return ms;
}
