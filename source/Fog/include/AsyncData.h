#pragma once

#include <stdint.h>
#include <windef.h>

#ifndef libwin
#define __fastcall
#endif

BOOL __fastcall FOG_MPQSetConfig(uint32_t dwDirectAccessFlags, int bEnableSeekOptimization);
BOOL FOG_UseDirect();
