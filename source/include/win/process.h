#pragma once

#include "__windows_shim_msvcrt.h"

enum {
	DLL_PROCESS_ATTACH = 0,
	DLL_PROCESS_DETACH,
	DLL_THREAD_ATTACH,
	DLL_THREAD_DETACH
};