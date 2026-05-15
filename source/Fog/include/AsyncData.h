#pragma once

#include <windef.h>

#ifndef __windows_shim
#define __fastcall
#endif

BOOL __fastcall FOG_MPQSetConfig(uint32_t dwDirectAccessFlags, int bEnableSeekOptimization);
BOOL FOG_UseDirect();
