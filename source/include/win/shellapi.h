#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdint.h>

#include "windef.h"
#include "winnt.h"

typedef struct {
	DWORD cbSize;
	HWND hWnd;
	UINT uCallbackMessage;
	UINT uEdge;
	RECT rc;
	LPARAM lParam;
} _AppBarData;

static inline uintptr_t SHAppBarMessage(DWORD dwMessage, _AppBarData* pData) {
	printf("Stubbed function SHAppBarMessage called\n");
	return (uintptr_t)NULL;
}
