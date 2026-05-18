#pragma once

#include "__windows_shim_msvcrt.h"

#include <string.h>

#include "windef.h"
#include "winerror.h"
#include "winnt.h"

#ifdef __windows_shim_has_jsonc

#include <json.h>

#endif

#define HKEY_CLASSES_ROOT ((HKEY)0)
#define HKEY_CURRENT_USER ((HKEY)1)
#define HKEY_LOCAL_MACHINE ((HKEY)2)
#define HKEY_USERS ((HKEY)3)
#define HKEY_PERFORMANCE_DATA ((HKEY)4)
#define HKEY_PERFORMANCE_TEXT ((HKEY)5)
#define HKEY_PERFORMANCE_NLSTEXT ((HKEY)6)

#define HKEY_CURRENT_CONFIG ((HKEY)7)
#define HKEY_DYN_DATA ((HKEY)8)
#define HKEY_CURRENT_USER_LOCAL_SETTINGS ((HKEY)9)

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

static inline const char* __windows_shim_pathSeparatedHKeyClassesRoot[] = { "HKEY_CLASSES_ROOT", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyClassesRoot = {
	.path = (char*)"HKEY_CLASSES_ROOT",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyClassesRoot,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyCurrentUser[] = { "HKEY_CURRENT_USER", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyCurrentUser = {
	.path = (char*)"HKEY_CURRENT_USER",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyCurrentUser,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyLocalMachine[] = { "HKEY_LOCAL_MACHINE", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyLocalMachine = {
	.path = (char*)"HKEY_LOCAL_MACHINE",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyLocalMachine,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyUsers[] = { "HKEY_USERS", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyUsers = {
	.path = (char*)"HKEY_USERS",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyUsers,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceData[] = { "HKEY_PERFORMANCE_DATA", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceData = {
	.path = (char*)"HKEY_PERFORMANCE_DATA",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceData,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceText[] = { "HKEY_PERFORMANCE_TEXT", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceText = {
	.path = (char*)"HKEY_PERFORMANCE_TEXT",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceText,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyPerformanceNLSText[] = { "HKEY_PERFORMANCE_NLSTEXT", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyPerformanceNLSText = {
	.path = (char*)"HKEY_PERFORMANCE_NLSTEXT",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyPerformanceNLSText,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyCurrentConfig[] = { "HKEY_CURRENT_CONFIG", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyCurrentConfig = {
	.path = (char*)"HKEY_CURRENT_CONFIG",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyCurrentConfig,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyDynData[] = { "HKEY_DYN_DATA", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyDynData = {
	.path = (char*)"HKEY_DYN_DATA",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyDynData,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const char* __windows_shim_pathSeparatedHKeyCurrentUserLocalSettings[] = { "HKEY_CURRENT_USER_LOCAL_SETTINGS", NULL };

static inline const __windows_shim_struct_HKEY __windows_shim_hKeyCurrentUserLocalSettings = {
	.path = (char*)"HKEY_CURRENT_USER_LOCAL_SETTINGS",
	.pathSeperated = (char**)__windows_shim_pathSeparatedHKeyCurrentUserLocalSettings,
	.name = NULL,
	.type = -1,
	.value = 0,
	.parent = NULL
};

static inline const __windows_shim_struct_HKEY* __windows_shim_hKeysLookup[10] = {
	&__windows_shim_hKeyClassesRoot,
	&__windows_shim_hKeyCurrentUser,
	&__windows_shim_hKeyLocalMachine,
	&__windows_shim_hKeyUsers,
	&__windows_shim_hKeyPerformanceData,
	&__windows_shim_hKeyPerformanceText,
	&__windows_shim_hKeyPerformanceNLSText,
	&__windows_shim_hKeyCurrentConfig,
	&__windows_shim_hKeyDynData,
	&__windows_shim_hKeyCurrentUserLocalSettings
};

static inline HKEY __windows_shim_GetHKey(const HKEY hKey) {
	if ((uintptr_t)hKey > 6) {
		return hKey;
	} else {
		return (HKEY)__windows_shim_hKeysLookup[(uintptr_t)hKey];
	}
}

static inline HKEY __windows_shim_GetInstancedBuiltinHKey(const int id) {
	char* pathSeparatedhKey[] = { NULL, NULL };
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
	case 7:
		pathSeparatedhKey[0] = (char*)"HKEY_CURRENT_CONFIG";
		hKey->path = (char*)"HKEY_CURRENT_CONFIG";
		break;
	case 8:
		pathSeparatedhKey[0] = (char*)"HKEY_DYN_DATA";
		hKey->path = (char*)"HKEY_DYN_DATA";
		break;
	case 9:
		pathSeparatedhKey[0] = (char*)"HKEY_CURRENT_USER_LOCAL_SETTINGS";
		hKey->path = (char*)"HKEY_CURRENT_USER_LOCAL_SETTINGS";
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

static inline char** __windows_shim_HKeyPathSeperate(char* lpSubKey, char** lpNewSubKey, bool freeNewSubKey, int* pCntElements) {
	char** subKeyPathSeperated = NULL;
	int lpSubKeyLen = strlen(lpSubKey);
	char* lptmpSubKey = (char*)malloc(sizeof(char) * strlen(lpSubKey) + 1);
	lptmpSubKey[strlen(lpSubKey)] = "\0"[0];

	int cntElements = 1;

	for (int i = 0; i < lpSubKeyLen; i++) {
		// printf("%c\n", lpSubKey[i]);
		if (lpSubKey[i] == '/') { // If lpSubKey == "\\", then lptmpSubKey[i] = "/"
			lptmpSubKey[i] = '/';
			cntElements++;
		} else if (lpSubKey[i] == '\\') { // If lpSubKey == "\\", then lptmpSubKey[i] = "/"
			lptmpSubKey[i] = '/';
			cntElements++;
		} else {
			lptmpSubKey[i] = lpSubKey[i];
		}
	}

	// printf("path2 %s\n", lptmpSubKey);

	*pCntElements = cntElements;

	char** pathSeperatedNew = (char**)malloc(sizeof(char*) * cntElements + 1);
	pathSeperatedNew[cntElements] = NULL;

	int j = 0;
	int k = 0;
	int l = 0;
	for (int i = 0; i < lpSubKeyLen + 1; i++) {
		// printf("lptmpSubKey[i]: %c: ", lptmpSubKey[i]);
		if ((lptmpSubKey[i] == '/') || (i == lpSubKeyLen)) {
			pathSeperatedNew[k] = (char*)malloc(j + 1);
			strncpy(pathSeperatedNew[k], lptmpSubKey + l, j);
			pathSeperatedNew[k][j] = '\0';
			j = 0;
			l = i + 1;
			k++;
			// printf("A\n");
		} else {
			j++;
			// printf("B\n");
		}
	}
	pathSeperatedNew[k] = NULL;

	if (freeNewSubKey) {
		free(*lpNewSubKey);
	}

	*lpNewSubKey = lptmpSubKey;

	return pathSeperatedNew;
}

#ifdef __windows_shim_has_jsonc

#include <__windows_shim_json_helper.h>

#else

static inline void __windows_shim_writeJson(HKEY hKey) {
	printf("Stubbed function __windows_shim_writeJson called\n");
}

static inline bool __windows_shim_readJson(HKEY hKey) {
	printf("Stubbed function __windows_shim_writeJson called\n");
	return false;
}

#endif

#define KEY_QUERY_VALUE 0

#define REG_DWORD_LITTLE_ENDIAN 0

typedef int32_t LSTATUS;

static inline LSTATUS RegOpenKeyA(HKEY hKey, LPCSTR lpSubKey, HKEY* phkResult) {
	if ((uintptr_t)hKey > 6 && !__windows_shim_readJson(hKey)) {
		return ERROR_FILE_NOT_FOUND;
	}

	if (lpSubKey == NULL || strlen(lpSubKey) == 0) {
		if ((uintptr_t)hKey > 6) {
			*phkResult = hKey;
		} else {
			*phkResult = __windows_shim_GetInstancedBuiltinHKey((uintptr_t)hKey);
		}
	} else {
		HKEY tmpHKey;
		tmpHKey = __windows_shim_GetHKey(hKey);

		HKEY newHKey = (HKEY)malloc(sizeof(__windows_shim_struct_HKEY));
		newHKey->path = (char*)malloc(sizeof(char) * (strlen(tmpHKey->path) + strlen(lpSubKey)) + 2);
		strcpy(newHKey->path, tmpHKey->path);
		strcat(newHKey->path, "/");
		strcat(newHKey->path, lpSubKey);
		int cntElements;
		newHKey->pathSeperated = __windows_shim_HKeyPathSeperate(newHKey->path, &newHKey->path, true, &cntElements);
		if (newHKey->pathSeperated[cntElements - 1] != NULL) {
			newHKey->name = (char*)malloc(strlen(newHKey->pathSeperated[cntElements - 1]) + 1);
			newHKey->name[strlen(newHKey->pathSeperated[cntElements - 1])] = '\0';
			strcpy(newHKey->name, newHKey->pathSeperated[cntElements - 1]);
		} else {
			newHKey->name = (char*)"UNKNOWN";
		}
		newHKey->type = -1;
		newHKey->value = 0;
		newHKey->parent = hKey;

		if (!__windows_shim_readJson(newHKey)) {
			return ERROR_FILE_NOT_FOUND;
		}

		*phkResult = newHKey;
	}

	// printf("path %s\n", (*phkResult)->path);

	// printf("pathSeperated [");
	// for (int i=0; (*phkResult)->pathSeperated[i] != NULL; i++) {
	// 	printf("%s, ", (*phkResult)->pathSeperated[i]);
	// }
	// printf("NULL]\n");

	// __windows_shim_writeJson(*phkResult);

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

static inline LSTATUS RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData) {
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
