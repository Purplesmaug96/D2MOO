#pragma once

#include <windef.h>
#include <winnt.h>

#define HKEY_CLASSES_ROOT                   0
#define HKEY_CURRENT_USER                   1
#define HKEY_LOCAL_MACHINE                  2
#define HKEY_USERS                          3
#define HKEY_PERFORMANCE_DATA               4
#define HKEY_PERFORMANCE_TEXT               5
#define HKEY_PERFORMANCE_NLSTEXT            6

#define HKEY_CURRENT_CONFIG                 7
#define HKEY_DYN_DATA                       8
#define HKEY_CURRENT_USER_LOCAL_SETTINGS    9

typedef int32_t LSTATUS;

static inline LSTATUS RegOpenKeyA(HKEY hKey, LPCSTR lpSubKey, HKEY* phkResult) {
	printf("Stubbed function RegOpenKeyA called\n");
	return 0;
}

static inline LSTATUS RegCreateKeyA(HKEY hKey, LPCSTR lpSubKey, HKEY* phkResult) {
	printf("Stubbed function RegCreateKeyA called\n");
	return 0;
}

static inline LSTATUS RegEnumValueA(HKEY hKey, DWORD dwIndex, LPSTR lpValueName, LPDWORD lpcchValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	printf("Stubbed function RegEnumValueA called\n");
	return 0;
}

static inline LSTATUS RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData) {
	printf("Stubbed function RegSetValueExA called\n");
}

static inline LSTATUS RegCloseKey(HKEY hKey) {
	printf("Stubbed function RegCloseKey called\n");
	return 0;
}

static inline LSTATUS RegDeleteKeyA(HKEY hKey, LPCSTR lpSubKey) {
	printf("Stubbed function RegDeleteKeyA called\n");
	return 0;
}

static inline LSTATUS RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, /*REGSAM*/ uint32_t samDesired, HKEY* phkResult) {
	printf("Stubbed function RegOpenKeyExA called\n");
	return 0;
}

static inline LSTATUS RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
	printf("Stubbed function RegQueryValueExA called\n");
	return 0;
}
