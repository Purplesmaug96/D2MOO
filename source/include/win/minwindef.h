#pragma once

#include "__windows_shim_msvcrt.h"

#define MAKEWORD(x, y) ((uint16_t)((uint16_t)x | ((uint16_t)y >> 8)))
