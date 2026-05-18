#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>
#include <unistd.h>

#include "windef.h"
#include "winnt.h"

typedef struct {
} CRITICAL_SECTION;
typedef CRITICAL_SECTION* LPCRITICAL_SECTION;

static inline void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function InitializeCriticalSection called\n");
}

static inline void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function DeleteCriticalSection called\n");
}

static inline void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function EnterCriticalSection called\n");
}

static inline void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function LeaveCriticalSection called\n");
}

static inline void Sleep(DWORD dwMilliseconds) {
	sleep(dwMilliseconds / 1000.0f);
}

static inline DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
	printf("Stubbed function WaitForSingleObject called\n");
	return 0xffffffff; // WAIT_FAILED
}

#define EVENT_MODIFY_STATE 0

static inline HANDLE OpenEventA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) {
	printf("Stubbed function OpenEventA called\n");
	return NULL;
}

static inline BOOL SetEvent(HANDLE hEvent) {
	printf("Stubbed function SetEvent called\n");
	return FALSE;
}
