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

#define CALLBACK __stdcall

#define _Acquires_lock_(x)
#define _Releases_lock_(x)

#define _Curr_ NULL

typedef int LCID;

// Source - https://stackoverflow.com/a/19472847
// Posted by Reed Copsey
// Retrieved 2026-05-06, License - CC BY-SA 3.0

#define _Analysis_assume_(x)

// Source - https://stackoverflow.com/a/1513215
// Posted by Alex B, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-08, License - CC BY-SA 2.5

static inline int fopen_s(FILE **f, const char *name, const char *mode) {
    int ret = 0;
    assert(f);
    *f = fopen(name, mode);
    // Can't be sure about 1-to-1 mapping of errno and MS' errno_t

    // if (!*f)
    //     ret = errno;
    return ret;
}
