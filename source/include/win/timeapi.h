#pragma once

#include <windef.h>
#include <sys/time.h>

static inline DWORD timeGetTime() {
	timeval tv;
	gettimeofday(&tv, 0);
	unsigned int ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000.0f);
	return ms;
}
