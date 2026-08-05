#pragma once

#include <stdint.h>
#include <windef.h>

BOOL __fastcall FOG_MPQSetConfig(uint32_t dwDirectAccessFlags, int bEnableSeekOptimization);
BOOL FOG_UseDirect();
