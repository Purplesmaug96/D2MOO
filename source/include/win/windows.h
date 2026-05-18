#pragma once

#ifdef __windows_shim_dissalow_windows_h
#error Including 'windows.h' is disallowed.
#endif

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// clang-format: off

#include "__windows_shim_msvcrt.h"

#include "debugapi.h"
#include "errhandlingapi.h"
#include "fileapi.h"
#include "libloaderapi.h"
#include "minwinbase.h"
#include "minwindef.h"
#include "ntdef.h"
#include "process.h"
#include "processthreadsapi.h"
#include "profileapi.h"
#include "shellapi.h"
#include "synchapi.h"
#include "timeapi.h"
#include "winbase.h"
#include "windef.h"
#include "winerror.h"
#include "wingdi.h"
#include "winnt.h"
#include "winreg.h"
#include "winsock2.h"
#include "winsvc.h"
#include "winuser.h"
#include "ws2def.h"

// clang-format: on
