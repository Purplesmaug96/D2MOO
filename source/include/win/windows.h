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

// #include <windef.h>
// #include <synchapi.h>
// #include <debugapi.h>
// #include <sysinfoapi.h>
// #include <winbase.h>
// #include <fileapi.h>
// #include <winnt.h>
// #include <processthreadsapi.h>
// #include <winuser.h>
// #include <process.h>
// #include <libloaderapi.h>
// #include <timeapi.h>
// #include <winsvc.h>

#error Including 'windows.h' is disallowed.
