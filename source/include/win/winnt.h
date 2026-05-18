#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdint.h>

#include "windef.h"

typedef union {
	//   struct {
	//     DWORD LowPart;
	//     LONG  HighPart;
	//   } DUMMYSTRUCTNAME;
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
	long long QuadPart;
} LARGE_INTEGER;

typedef void* HANDLE;

// Quite possible the wrong place
typedef HANDLE HWND;
typedef HANDLE HRGN;

typedef struct {
	char* name;
	void* dlHandle;
} __windows_shim_struct_HMODULE;
typedef __windows_shim_struct_HMODULE* HMODULE;

typedef HANDLE HDC; // Device Context
typedef HANDLE HINSTANCE;
typedef HANDLE HGDIOBJ;

typedef struct __windows_shim_struct_HKEY {
	char* path;
	char** pathSeperated; // List of folders (example: ["HKCU", "SOFTWARE", "Blizzard Entertainment"])
	char* name;
	int type;
	uint32_t value;
	__windows_shim_struct_HKEY* parent = NULL;
}* HKEY;

typedef HANDLE HICON;
typedef HANDLE HCURSOR;
typedef HANDLE HBRUSH;

typedef struct {
} SECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES* LPSECURITY_ATTRIBUTES;

typedef int32_t HRESULT;

typedef DWORD(__stdcall* LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

static inline long InterlockedIncrement(long volatile* Addend) {
	*Addend++;
	return *Addend;
}

static inline long long InterlockedIncrement64(long long volatile* Addend) {
	*Addend++;
	return *Addend;
}

static inline long InterlockedDecrement(long volatile* Addend) {
	*Addend--;
	return *Addend;
}

static inline long long InterlockedDecrement64(long long volatile* Addend) {
	*Addend--;
	return *Addend;
}

// InterlockedCompareExchange taken from this issue: https://github.com/itsmattkc/dotnet9x/issues/19

// Reimplemented
static inline LONG InterlockedCompareExchange(LONG volatile* dest, LONG xchg, LONG compare) {
	LONG temp = *dest;

	if (compare == *dest) {
		*dest = xchg;
	}

	return temp;
}
