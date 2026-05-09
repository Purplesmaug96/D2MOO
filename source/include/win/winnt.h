#pragma once

#include <stdint.h>

#include <__windows_shim_msvcrt.h>
#include <windef.h>

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
typedef HANDLE HKEY;

typedef struct {} SECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES* LPSECURITY_ATTRIBUTES;

typedef int32_t HRESULT;

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);

static long InterlockedIncrement(long volatile *Addend) {
	*Addend++;
	return *Addend;
}

static long long InterlockedIncrement64(long long volatile *Addend) {
	*Addend++;
	return *Addend;
}

static long InterlockedDecrement(long volatile *Addend) {
	*Addend--;
	return *Addend;
}

static long long InterlockedDecrement64(long long volatile *Addend) {
	*Addend--;
	return *Addend;
}

