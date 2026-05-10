#pragma once

#include <stdint.h>
#include <winnt.h>

typedef struct {
	uint8_t peRed;
	uint8_t peGreen;
	uint8_t peBlue;
	uint8_t peFlags;
} PALETTEENTRY;

typedef PALETTEENTRY* LPPALETTEENTRY;
typedef PALETTEENTRY* LPPALETTE;

static inline HGDIOBJ GetStockObject(int i) {
	return NULL;
}
