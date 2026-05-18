#pragma once

#include "__windows_shim_msvcrt.h"

#include "windef.h"

typedef struct {
} OVERLAPPED;
typedef OVERLAPPED* LPOVERLAPPED;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME;
