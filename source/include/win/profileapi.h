#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>
#include <time.h>

#include "windef.h"
#include "winnt.h"

// Implementation from https://stackoverflow.com/questions/12468331/queryperformancecounter-linux-equivalent

#define __windows_shim_NSEC_PER_SEC 1000000000

static inline __int64 __windows_shim_QueryPerformanceCounter() {
	__int64 nsec_count, nsec_per_tick;
	/*
	 * clock_gettime() returns the number of secs. We translate that to number of nanosecs.
	 * clock_getres() returns number of seconds per tick. We translate that to number of nanosecs per tick.
	 * Number of nanosecs divided by number of nanosecs per tick - will give the number of ticks.
	 */
	timespec ts1, ts2;

	if (clock_gettime(CLOCK_MONOTONIC, &ts1) != 0) {
		printf("clock_gettime() failed");
		return -1;
	}

	nsec_count = ts1.tv_nsec + ts1.tv_sec * __windows_shim_NSEC_PER_SEC;

	if (clock_getres(CLOCK_MONOTONIC, &ts2) != 0) {
		printf("clock_getres() failed");
		return -1;
	}

	nsec_per_tick = ts2.tv_nsec + ts2.tv_sec * __windows_shim_NSEC_PER_SEC;

	return (nsec_count / nsec_per_tick);
}

static inline __int64 __windows_shim_QueryPerformanceFrequency() {
	timespec ts2;
	if (clock_getres(CLOCK_MONOTONIC, &ts2) != 0) {
		printf("clock_getres() failed");
		return -1;
	}
	return ts2.tv_nsec * __windows_shim_NSEC_PER_SEC;
}

static inline BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount) {
	if (lpPerformanceCount == NULL) {
		return FALSE;
	}
	lpPerformanceCount->QuadPart = __windows_shim_QueryPerformanceCounter();
	return TRUE;
}

static inline BOOL QueryPerformanceFrequency(LARGE_INTEGER* lpPerformanceCount) {
	if (lpPerformanceCount == NULL) {
		return FALSE;
	}
	lpPerformanceCount->QuadPart = __windows_shim_QueryPerformanceFrequency();
	return TRUE;
}

#ifdef __cplusplus

static inline __int64 QueryPerformanceCounter() {
	return __windows_shim_QueryPerformanceCounter();
}

static inline __int64 QueryPerformanceFrequency() {
	return __windows_shim_QueryPerformanceFrequency();
}

#endif
