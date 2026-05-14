#pragma once

void* __fastcall FOG_Alloc(int nSize, const char* szFile, int nLine, int n0);
void __fastcall FOG_Free(void* pFree, const char* szFile, int nLine, int n0);
void __fastcall FOG_Realloc(void* pMemory, int nSize, const char* szFile, int nLine, int n0);
void* __fastcall FOG_AllocPool(void* pMemPool, int nSize, const char* szFile, int nLine, int n0);
void __fastcall FOG_FreePool(void* pMemPool, void* pFree, const char* szFile, int nLine, int n0);
void* __fastcall FOG_ReallocPool(void* pMemPool, void* pMemory, int nSize, const char* szFile, int nLine, int n0);
