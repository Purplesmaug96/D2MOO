#pragma once

#include "__windows_shim_msvcrt.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
	int left;	// X of top-left
	int top;	// Y of top-left
	int right;	// X of down-right
	int bottom; // Y of down-right
} RECT;

typedef int BOOL;

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#define TRUE ((BOOL)(uint32_t)true)
#define FALSE ((BOOL)(uint32_t)false)

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;

typedef long LONG;
typedef unsigned long ULONG;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef short SHORT;
typedef unsigned short USHORT;

typedef int INT;
typedef unsigned int UINT;
typedef size_t SIZE_T;
typedef char CHAR;
typedef char TCHAR;
typedef void VOID;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef wchar_t* LPWSTR;
typedef const wchar_t* PCWSTR;
#ifdef UNICODE
typedef LPWSTR LPTSTR;
typedef LPCWSTR LPCTSTR;
#else
typedef LPSTR LPTSTR;
typedef LPCSTR LPCTSTR;
#endif
typedef DWORD* LPDWORD;
typedef uint8_t* LPBYTE;

#ifdef __linux__
#include <linux/limits.h>
#define MAX_PATH PATH_MAX
#else
#define MAX_PATH 256 // Might need to be increased later
#endif

#define _MAX_DIR MAX_PATH // Don't know if correct

typedef int (*FARPROC)();

typedef struct {
	int32_t x;
	int32_t y;
} POINT;

typedef int32_t ATOMIC32;

#define WINAPI
