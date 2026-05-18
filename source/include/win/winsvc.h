#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdint.h>
#include <stdio.h>

#include "windef.h"
#include "winnt.h"

typedef struct _SERVICE_STATUS {
	DWORD dwServiceType;
	DWORD dwCurrentState;
	DWORD dwControlsAccepted;
	DWORD dwWin32ExitCode;
	DWORD dwServiceSpecificExitCode;
	DWORD dwCheckPoint;
	DWORD dwWaitHint;
} SERVICE_STATUS;

typedef uint32_t SERVICE_STATUS_HANDLE; // No idea if is correct
typedef HANDLE SC_HANDLE;
typedef void* LPHANDLER_FUNCTION; // It's a callback, will be corrected to a function ptr when implemented

#define SERVICE_WIN32_OWN_PROCESS 0
#define SERVICE_RUNNING 1
#define SERVICE_ACCEPT_STOP 2
#define SERVICE_ACCEPT_SHUTDOWN 3
#define SERVICE_CONTROL_STOP 4
#define SERVICE_CONTROL_SHUTDOWN 5
#define SERVICE_CONTROL_INTERROGATE 6
#define SERVICE_STOPPED 7
#define SERVICE_STOP_PENDING 8
#define SERVICE_ERROR_NORMAL 9
#define SERVICE_AUTO_START 10
#define SERVICE_INTERACTIVE_PROCESS 11
#define SERVICE_ALL_ACCESS 12

#define SC_MANAGER_ALL_ACCESS 0

static inline SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerA(LPCSTR lpServiceName, LPHANDLER_FUNCTION lpHandlerProc) {
	printf("Stubbed function RegisterServiceCtrlHandlerA called\n");
	return 0;
}

static inline BOOL SetServiceStatus(SERVICE_STATUS_HANDLE hServiceStatus, SERVICE_STATUS* lpServiceStatus) {
	printf("Stubbed function SetServiceStatus called\n");
	return FALSE;
}

static inline SC_HANDLE OpenSCManagerA(LPCSTR lpMachineName, LPCSTR lpDatabaseName, DWORD dwDesiredAccess) {
	printf("Stubbed function OpenSCManagerA called\n");
	return NULL;
}

static inline BOOL CloseServiceHandle(SC_HANDLE hSCObject) {
	printf("Stubbed function CloseServiceHandle called\n");
	return FALSE;
}

static inline SC_HANDLE OpenServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, DWORD dwDesiredAccess) {
	printf("Stubbed function OpenServiceA called\n");
	return NULL;
}

static inline SC_HANDLE CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword) {
	printf("Stubbed function CreateServiceA called\n");
	return NULL;
}

typedef struct {
	LPSTR lpServiceName;
	/*LPSERVICE_MAIN_FUNCTIONA*/ void* lpServiceProc;
} SERVICE_TABLE_ENTRYA;

static inline BOOL StartServiceCtrlDispatcherA(SERVICE_TABLE_ENTRYA* lpServiceStartTable) {
	printf("Stubbed function StartServiceCtrlDispatcherA called\n");
	return FALSE;
}
