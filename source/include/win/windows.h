#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include <__windows_shim_msvcrt.h>

#include <windef.h>
#include <synchapi.h>
#include <debugapi.h>
#include <sysinfoapi.h>
#include <winbase.h>
#include <fileapi.h>
#include <winnt.h>
#include <processthreadsapi.h>
#include <winuser.h>
#include <process.h>
#include <libloaderapi.h>
#include <timeapi.h>
#include <winsvc.h>

#define CALLBACK __stdcall

#define _Acquires_lock_(x)
#define _Releases_lock_(x)

#define _Requires_lock_held_(x)

#define _Curr_ NULL

typedef int LCID;

// Source - https://stackoverflow.com/a/19472847
// Posted by Reed Copsey
// Retrieved 2026-05-06, License - CC BY-SA 3.0

#define _Analysis_assume_(x)

#define _strcmpi strcasecmp
