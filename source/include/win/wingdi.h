#pragma once

#include <stdint.h>

typedef struct {
	uint8_t peRed;
	uint8_t peGreen;
	uint8_t peBlue;
	uint8_t peFlags;
} PALETTEENTRY;

typedef PALETTEENTRY* LPPALETTEENTRY;
typedef PALETTEENTRY* LPPALETTE;
