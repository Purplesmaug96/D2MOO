#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef bool BOOL;
typedef uint32_t DWORD;

#define __stdcall
#define __cdecl
#define __fastcall

#define CALLBACK __stdcall

#define __declspec(x)

#define TRUE true
#define FALSE false

#define _Acquires_lock_(x)
#define _Releases_lock_(x)

#define _Curr_ NULL

#define MAX_PATH 256 // Might need to be increased later

typedef void* HANDLE;

typedef HANDLE HWND;
typedef HANDLE HRGN;
typedef HANDLE HMODULE;
typedef HANDLE HDC; // Device Context
typedef HANDLE HINSTANCE;
typedef HANDLE HGDIOBJ;
typedef HANDLE HKEY;

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef DWORD* LPDWORD;
typedef uint8_t* LPBYTE;

typedef long LONG;
typedef unsigned long ULONG;
typedef uint UINT;
typedef uint8_t BYTE;
typedef size_t SIZE_T;
typedef char CHAR;
typedef void VOID;

typedef int LCID;

enum {
	DLL_PROCESS_ATTACH=0,
	DLL_PROCESS_DETACH,
	DLL_THREAD_ATTACH,
	DLL_THREAD_DETACH
};

typedef struct {} CRITICAL_SECTION;
typedef CRITICAL_SECTION* LPCRITICAL_SECTION;

typedef struct {} SECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES LPSECURITY_ATTRIBUTES;

// Source - https://stackoverflow.com/a/19472847
// Posted by Reed Copsey
// Retrieved 2026-05-06, License - CC BY-SA 3.0

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);

typedef struct {
	DWORD dwOSVersionInfoSize;
	uint8_t dwPlatformId;
} OSVERSIONINFOA;

#define VER_PLATFORM_WIN32_NT 0
static inline BOOL GetVersionExA(OSVERSIONINFOA* verInfo) {
	verInfo->dwPlatformId = VER_PLATFORM_WIN32_NT;
	return TRUE;
}

#define __debugbreak() printf("__debugbreak\n")
#define _Analysis_assume_(x)

static inline void OutputDebugStringA(char* str) {
	printf("OutputDebugStringA: %s\n", str);
}

static inline DWORD GetLogicalDriveStringsA(DWORD nBufferLength,  LPSTR lpBuffer) {
	return 0; // Length written
}

enum {
	DRIVE_UNKNOWN=0,
	DRIVE_NO_ROOT_DIR,
	DRIVE_REMOVABLE,
	DRIVE_FIXED,
	DRIVE_REMOTE,
	DRIVE_CDROM,
	DRIVE_RAMDISK
};

static inline UINT GetDriveTypeA(LPCSTR lpRootPathName) {
	return DRIVE_UNKNOWN;
}

static inline LPSTR lstrcpyA(LPSTR  lpString1, LPCSTR lpString2) {
	return strcpy(lpString1, lpString2);
}

static inline LPSTR lstrcpynA(LPSTR  lpString1, LPCSTR lpString2, int iMaxLength) {
	return strncpy(lpString1, lpString2, iMaxLength);
}

static inline LPSTR lstrcatA(LPSTR  lpString1, LPCSTR lpString2) {
	return strcat(lpString1, lpString2);
}

static inline DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	strncpy(lpFilename, "GetModuleFileNameA (stubbed)", nSize);
	return TRUE;
}

static inline void Sleep(DWORD dwMilliseconds) {
	sleep(dwMilliseconds / 1000);
}

static inline void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function InitializeCriticalSection called\n");
}

static inline void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function DeleteCriticalSection called\n");
}

static inline void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function EnterCriticalSection called\n");
}

static inline void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	printf("Stubbed function LeaveCriticalSection called\n");
}

static inline int wsprintfA(char* lpOut, const char* lpFmt, ...) {
    int result;
    va_list args;

    va_start(args, lpFmt);

    result = vsprintf(lpOut, lpFmt, args);

    va_end(args);

    return result;
}

static inline int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	printf("Stubbed function MessageBoxA called\n");
	return 0;
}

enum {
	IDABORT=0,
	IDC_STATIC,
	IDCANCEL,
	IDD_ABOUTBOX,
	IDI_PROJECTNAME,
	IDI_SMALL,
	IDIGNORE,
	IDM_ABOUT,
	IDM_EXIT,
	IDNO,
	IDOK,
	IDRETRY,
	IDS_APP_TITLE,
	IDYES
};

static inline HANDLE GetCurrentProcess() {
	return NULL;
}

static inline BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode) {
	return FALSE;
}

static inline void _lock_file(FILE* file) {
	printf("Stubbed function _lock_file called\n");
}

static inline void _unlock_file(FILE* file) {
	printf("Stubbed function _unlock_file called\n");
}

/*

// Normal

static inline char * _itoa(int value, char *buffer, int radix) {
	return itoa(value, buffer, radix);
}

static inline char * _ltoa(long value, char *buffer, int radix) {
	return ltoa(value, buffer, radix);
}

static inline char * _ultoa(unsigned long value, char *buffer, int radix) {
	return ultoa(value, buffer, radix);
}

static inline char * _i64toa(long long value, char *buffer, int radix) {
	return i64toa(value, buffer, radix);
}

static inline char * _ui64toa(unsigned long long value, char *buffer, int radix) {
	return ui64toa(value, buffer, radix);
}

// Wide

static inline char * _itow(int value, char *buffer, int radix) {
	return itow(value, buffer, radix);
}

static inline char * _ltow(long value, char *buffer, int radix) {
	return ltow(value, buffer, radix);
}

static inline char * _ultow(unsigned long value, char *buffer, int radix) {
	return ultow(value, buffer, radix);
}

static inline char * _i64tow(long long value, char *buffer, int radix) {
	return i64tow(value, buffer, radix);
}

static inline char * _ui64tow(unsigned long long value, char *buffer, int radix) {
	return ui64tow(value, buffer, radix);
}

*/

// Taken from geeksforgeeks - https://www.geeksforgeeks.org/c/implement-itoa/

// A utility function to reverse a string
static inline void __windows_reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}
// Implementation of citoa()
static inline char* __windows_itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    __windows_reverse(str, i);

    return str;
}

static inline char * _itoa(int value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ltoa(long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ultoa(unsigned long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _i64toa(long long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ui64toa(unsigned long long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

// Wide

static inline char * _itow(int value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ltow(long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ultow(unsigned long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _i64tow(long long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}

static inline char * _ui64tow(unsigned long long value, char *buffer, int radix) {
	return __windows_itoa(value, buffer, radix);
}
