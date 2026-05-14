#include <malloc.h>
#include <stdlib.h>

#include "Mem/Mem.h"

// Fog.#10042
void* __fastcall FOG_Alloc(int nSize, const char* szFile, int nLine, int n0) {
	void* pMem = malloc(nSize);

	if (pMem == NULL) {
		printf("FOG_Alloc failed at %s:%d\n", szFile, nLine);
		exit(1);
	}

	return pMem;
}

// Fog.#10043
void __fastcall FOG_Free(void* pFree, const char* szFile, int nLine, int n0) {
	free(pFree);
}

// Fog.#10044
void __fastcall FOG_Realloc(void* pMemory, int nSize, const char* szFile, int nLine, int n0) {
	void* pMem = realloc(pMemory, nSize);

	if (pMem == NULL) {
		printf("FOG_Realloc failed at %s:%d\n", szFile, nLine);
		exit(1);
	}
}

// Fog.#10045
void* __fastcall FOG_AllocPool(void* pMemPool, int nSize, const char* szFile, int nLine, int n0) {
	void* pMem = malloc(nSize);

	if (pMem == NULL) {
		printf("FOG_AllocPool failed at %s:%d\n", szFile, nLine);
		exit(1);
	}

	return pMem;
}


// Fog.#10046
void __fastcall FOG_FreePool(void* pMemPool, void* pFree, const char* szFile, int nLine, int n0) {
	free(pFree);
}

// Fog.#10047
void* __fastcall FOG_ReallocPool(void* pMemPool, void* pMemory, int nSize, const char* szFile, int nLine, int n0)  {
	void* pMem = realloc(pMemory, nSize);

	if (pMem == NULL) {
		printf("FOG_ReallocPool failed at %s:%d\n", szFile, nLine);
		exit(1);
	}

	return pMem; // Unknown if is right
}
