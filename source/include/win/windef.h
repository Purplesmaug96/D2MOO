#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} RECT;

typedef int BOOL;

#define TRUE ((BOOL)(uint32_t)true)
#define FALSE ((BOOL)(uint32_t)false)

typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;

typedef int32_t LONG;
typedef uint32_t ULONG;
typedef unsigned int UINT;
typedef size_t SIZE_T;
typedef char CHAR;
typedef void VOID;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef wchar_t* PWSTR;
typedef const wchar_t* PCWSTR;
typedef DWORD* LPDWORD;
typedef uint8_t* LPBYTE;

#define MAX_PATH 256 // Might need to be increased later

typedef int (*FARPROC)();
