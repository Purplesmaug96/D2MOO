#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdint.h>
#include <stdio.h>

#include "winnt.h"

typedef struct {
	uint8_t peRed;
	uint8_t peGreen;
	uint8_t peBlue;
	uint8_t peFlags;
} PALETTEENTRY;

typedef PALETTEENTRY* LPPALETTEENTRY;
typedef PALETTEENTRY* LPPALETTE;

static inline HGDIOBJ GetStockObject(int i) {
	printf("Stubbed function GetStockObject called\n");
	return NULL;
}

static inline DWORD GdiSetBatchLimit(DWORD dw) {
	printf("Stubbed function GdiSetBatchLimit called\n");
	return 0;
}
