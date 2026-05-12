#pragma once

#include <string.h>

#include <windef.h>
#include <winnt.h>

#define HKEY_CLASSES_ROOT                   ((HKEY)0)
#define HKEY_CURRENT_USER                   ((HKEY)1)
#define HKEY_LOCAL_MACHINE                  ((HKEY)2)
#define HKEY_USERS                          ((HKEY)3)
#define HKEY_PERFORMANCE_DATA               ((HKEY)4)
#define HKEY_PERFORMANCE_TEXT               ((HKEY)5)
#define HKEY_PERFORMANCE_NLSTEXT            ((HKEY)6)

/*

typedef struct {
	char* path;
	char** pathSeperated; // List of folders (example: ["HKCU", "SOFTWARE", "Blizzard Entertainment"])
	char* name;
	int type;
	uint32_t value;
} __windows_shim_struct_HKEY;

typedef __windows_shim_struct_HKEY* HKEY;

*/

static inline const char* __windows_shim_pathSeparatedHKeyClassesRoot[] = {"HKEY_CLASSES_ROOT", NULL};

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyClassesRoot = {
    .path = (char*)"HKEY_CLASSES_ROOT",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyClassesRoot,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyCurrentUser[] = {"HKEY_CURRENT_USER", NULL};


static inline const __windows_shim_struct_HKEY __windows_shim_hKeyCurrentUser = {
    .path = (char*)"HKEY_CURRENT_USER",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyCurrentUser,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyLocalMachine[] = {"HKEY_LOCAL_MACHINE", NULL};


static inline const __windows_shim_struct_HKEY __windows_shim_hKeyLocalMachine = {
    .path = (char*)"HKEY_LOCAL_MACHINE",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyLocalMachine,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyUsers[] = {"HKEY_USERS", NULL};

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyUsers = {
    .path = (char*)"HKEY_USERS",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyUsers,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceData[] = {"HKEY_PERFORMANCE_DATA", NULL};

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceData = {
    .path = (char*)"HKEY_PERFORMANCE_DATA",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceData,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceText[] = {"HKEY_PERFORMANCE_TEXT", NULL};

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceText = {
    .path = (char*)"HKEY_PERFORMANCE_TEXT",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceText,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceNLSText[] = {"HKEY_PERFORMANCE_NLSTEXT", NULL};

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceNLSText = {
    .path = (char*)"HKEY_PERFORMANCE_NLSTEXT",
    .pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceNLSText,
    .name = NULL,
    .type = -1,
    .value = 0
};

static inline const __windows_shim_struct_HKEY* __windows_shim_hKeysLookup[7] = {
	&__windows_shim_hKeyClassesRoot,
	&__windows_shim_hKeyCurrentUser,
	&__windows_shim_hKeyLocalMachine,
	&__windows_shim_hKeyUsers,
	&__windows_shim_hKeyPerformanceData,
	&__windows_shim_hKeyPerformanceText,
	&__windows_shim_hKeyPerformanceNLSText
};

static inline HKEY __windows_shim_GetHKey(const HKEY hKey) {
	if ((uintptr_t)hKey > 6) {
		return hKey;
	}
	else {
		return (HKEY)__windows_shim_hKeysLookup[(uintptr_t)hKey];
	}
}

static inline HKEY __windows_shim_GetInstancedBuiltinHKey(const int id) {
	char* pathSeparatedhKey[] = {NULL, NULL};
	HKEY hKey = (HKEY)malloc(sizeof(__windows_shim_struct_HKEY));

	hKey->path = (char*)"HKEY_PERFORMANCE_NLSTEXT";
	hKey->pathSeperated = (char**)pathSeparatedhKey;
	hKey->name = NULL;
	hKey->type = -1;
	hKey->value = 0;

	switch (id) {
		case 0:
			pathSeparatedhKey[0] = (char*)"HKEY_CLASSES_ROOT";
			hKey->path = (char*)"HKEY_CLASSES_ROOT";
			break;
		case 1:
			pathSeparatedhKey[0] = (char*)"HKEY_CURRENT_USER";
			hKey->path = (char*)"HKEY_CURRENT_USER";
			break;
		case 2:
			pathSeparatedhKey[0] = (char*)"HKEY_LOCAL_MACHINE";
			hKey->path = (char*)"HKEY_LOCAL_MACHINE";
			break;
		case 3:
			pathSeparatedhKey[0] = (char*)"HKEY_USERS";
			hKey->path = (char*)"HKEY_USERS";
			break;
		case 4:
			pathSeparatedhKey[0] = (char*)"HKEY_PERFORMANCE_DATA";
			hKey->path = (char*)"HKEY_PERFORMANCE_DATA";
			break;
		case 5:
			pathSeparatedhKey[0] = (char*)"HKEY_PERFORMANCE_TEXT";
			hKey->path = (char*)"HKEY_PERFORMANCE_TEXT";
			break;
		case 6:
			pathSeparatedhKey[0] = (char*)"HKEY_PERFORMANCE_NLSTEXT";
			hKey->path = (char*)"HKEY_PERFORMANCE_NLSTEXT";
			break;
		default:
			return NULL;
	}

	return hKey;
}

// Format of pathSeperated should be [..., NULL]

static inline int __windows_shim_HKeyPathLength(char** pathSeperated) {
	int i;
	for (i = 0; pathSeperated[i] != NULL; i++) {}
	return i;
}

static inline char** __windows_shim_HKeyPathSeperate(char* lpSubKey, char** lpNewSubKey) {
	char** subKeyPathSeperated = NULL;
	int lpSubKeyLen = strlen(lpSubKey);
	char* lptmpSubKey = (char*)malloc(sizeof(char) * strlen(lpSubKey));

	for (int i = 0; i < lpSubKeyLen; i++) {
		if (((int)lpSubKey[i] - ((intptr_t)"\\")) == 0) { // If lpSubKey == "\\", then lptmpSubKey[i] = "/"
			lptmpSubKey[i] = "/"[0];
		}
		else {
			lptmpSubKey[i] = lpSubKey[i];
		}
	}

	char** pathSeperatedNew = (char**)malloc(sizeof(char*) * strlen(lptmpSubKey) + 1);
	pathSeperatedNew[strlen(lptmpSubKey)] = NULL;

	int j = 0;
	int k = 0;
	for (int i = 0; i < lpSubKeyLen; i++) {
		if (((int)lptmpSubKey[i] - ((intptr_t)"/")) == 0) { // If lpSubKey == "/", then lptmpSubKey[i] = "/"
			pathSeperatedNew[k] = (char*)malloc(j);
			strncpy(pathSeperatedNew[k], lptmpSubKey + i, j);
			j = 0;
			k++;
		}
		else {
			j++;
		}
	}

	*lpNewSubKey = lpSubKey;

	return pathSeperatedNew;
}

#define HKEY_CURRENT_CONFIG                 7
#define HKEY_DYN_DATA                       8
#define HKEY_CURRENT_USER_LOCAL_SETTINGS    9

#define KEY_QUERY_VALUE 0

#define REG_DWORD_LITTLE_ENDIAN 0

typedef int32_t LSTATUS;

static inline LSTATUS RegOpenKeyA(HKEY hKey, LPCSTR lpSubKey, HKEY* phkResult) {
	if (strlen(lpSubKey) == 0) {
		if ((uintptr_t)hKey > 6) {
			*phkResult = hKey;
		}
		else {
			*phkResult = __windows_shim_GetInstancedBuiltinHKey((uintptr_t)hKey);
		}
	}
	else {
		HKEY tmpHKey;
		tmpHKey = __windows_shim_GetHKey(hKey);

		HKEY newHKey = (HKEY)malloc(sizeof(__windows_shim_struct_HKEY));
		newHKey->path = (char*)malloc(sizeof(char) * (strlen(tmpHKey->path) + strlen(lpSubKey)));
		strcpy(newHKey->path, tmpHKey->path);
		strcat(newHKey->path, lpSubKey);
		newHKey->pathSeperated = __windows_shim_HKeyPathSeperate(newHKey->path, &newHKey->path);
		if (newHKey->pathSeperated[strlen(newHKey->path) - 1] != NULL) {
			newHKey->name = (char*)malloc(strlen(newHKey->pathSeperated[strlen(newHKey->path) - 1]));
			strcpy(newHKey->name, newHKey->pathSeperated[strlen(newHKey->path) - 1]);
		}
		else {
			newHKey->name = (char*)"UNKNOWN";
		}
		newHKey->type = -1;
		newHKey->value = 0;
		*phkResult = newHKey;
	}

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
	return 0;
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
