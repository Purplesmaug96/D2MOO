#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdio.h>
#include <stdlib.h>

#include "windef.h"
#include "winnt.h"

static inline HANDLE GetCurrentProcess() {
	return NULL;
}

static inline BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode) {
	return FALSE;
}

static inline HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
	printf("Stubbed function CreateThread called\n");
	return NULL;
}

static inline void ExitThread(DWORD dwExitCode) {
	exit(dwExitCode);
}

static inline BOOL SetThreadPriority(HANDLE hThread, int nPriority) {
	printf("Stubbed function SetThreadPriority called\n");
	return FALSE;
}

static inline HRESULT SetThreadDescription(HANDLE hThread, PCWSTR lpThreadDescription) {
	printf("Stubbed function SetThreadDescription called\n");
	return 0;
}
