#pragma once
#include <stdint.h>

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

#define SERVICE_WIN32_OWN_PROCESS 0
#define SERVICE_RUNNING 1
#define SERVICE_ACCEPT_STOP 2
#define SERVICE_ACCEPT_SHUTDOWN 3
