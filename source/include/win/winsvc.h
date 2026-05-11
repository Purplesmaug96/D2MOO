#pragma once
#include <stdint.h>
#include <stdio.h>

#include <windef.h>

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

static inline SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerA(LPCSTR lpServiceName, LPHANDLER_FUNCTION lpHandlerProc) {
	printf("Stubbed function RegisterServiceCtrlHandlerA called\n");
	return 0;
}

static inline BOOL SetServiceStatus(SERVICE_STATUS_HANDLE hServiceStatus, SERVICE_STATUS* lpServiceStatus) {
	printf("Stubbed function SetServiceStatus called\n");
	return FALSE;
}
