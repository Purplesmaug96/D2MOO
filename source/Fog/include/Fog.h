#pragma once

#include <D2BasicTypes.h>
#include <D2Dll.h>
#include <StormHandles.h>
#include <stdlib.h>

#include <minwinbase.h>
#include <synchapi.h>
#include <windef.h>
#include <winnt.h>

#include "AsyncData.h"
#include "ErrorManager.h"
#include "Mem/Mem.h"

// 1.10f Image base: 0x6FF50000

#ifdef D2_VERSION_110F
constexpr int FogImageBase = 0x6FF50000;
#endif

#pragma pack(1)

struct D2TxtLinkNodeStrc {
	char szText[32];			  // 0x00
	int nLinkIndex;				  // 0x20
	D2TxtLinkNodeStrc* pPrevious; // 0x24
	D2TxtLinkNodeStrc* pNext;	  // 0x28
};

struct D2TxtLinkTblStrc {
	union {
		char szCode[4];	 // 0x00
		uint32_t dwCode; // 0x00
	};
	int nLinkIndex; // 0x04
};

struct D2TxtLinkStrc {
	int32_t nRecords;			   // 0x00
	int32_t nAllocatedCells;	   // 0x04
	D2TxtLinkTblStrc* pTbl;		   // 0x08
	D2TxtLinkNodeStrc* pFirstNode; // 0x0C
};

struct D2BinFileStrc {
	uint8_t* pDataBuffer; // 0x00
	uint8_t* pData;		  // 0x04
	int32_t nRecordCount; // 0x08
	int32_t nCellCount;	  // 0x0C
};

enum D2C_TxtFieldTypes : uint32_t {
	TXTFIELD_NONE,
	TXTFIELD_ASCII,
	TXTFIELD_DWORD,
	TXTFIELD_WORD,
	TXTFIELD_BYTE,
	TXTFIELD_UNKNOWN1,
	TXTFIELD_UNKNOWN2,
	TXTFIELD_BYTE2,
	TXTFIELD_DWORD2,
	TXTFIELD_RAW,
	TXTFIELD_ASCIITOCODE,
	TXTFIELD_UNKNOWN3,
	TXTFIELD_UNKNOWN4,
	TXTFIELD_CODETOBYTE,
	TXTFIELD_UNKNOWN5,
	TXTFIELD_CODETOWORD,
	TXTFIELD_UNKNOWN6,
	TXTFIELD_NAMETOINDEX,
	TXTFIELD_NAMETOINDEX2,
	TXTFIELD_NAMETODWORD,
	TXTFIELD_NAMETOWORD,
	TXTFIELD_NAMETOWORD2,
	TXTFIELD_KEYTOWORD,
	TXTFIELD_CUSTOMLINK,
	TXTFIELD_UNKNOWN7,
	TXTFIELD_CALCTODWORD,
	TXTFIELD_BIT
};

struct D2BinFieldStrc {
	const char* szFieldName;	  // 0x00
	D2C_TxtFieldTypes nFieldType; // 0x04
	int32_t nFieldLength;		  // 0x08
	int32_t nFieldOffset;		  // 0x0C
	void* pLinkField;			  // 0x10
};

struct D2UnkExcelStrc {
	D2UnkExcelStrc* pNext;	   // 0x00
	uint32_t dwHash;		   // 0x04
	D2BinFieldStrc* pBinField; // 0x08
};

enum D2C_AsyncDataPriority {
	ASYNC_DATA_PRIORITY_NORMAL = 0,
	ASYNC_DATA_PRIORITY_HIGH = 1,
};

enum D2C_AsyncDataFlags : uint32_t {
	ASYNC_DATA_FLAGS_LOADED = 0x1,
	ASYNC_DATA_FLAGS_OWNS_BUFFER = 0x2,
	ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE = 0x8,

	ASYNC_DATA_FLAGS_DEBUG_TAG = 0x41737960,
	ASYNC_DATA_FLAGS_DEBUG_TAG_MASK = 0xFFFFFFF0,
};

struct AsyncDataLoadFileCallback // sizeof(0x1C)
{
	DWORD(__stdcall* callback)(void* pFileData, size_t nDataLength, AsyncDataLoadFileCallback* pCallbackData); // 0x00
	DWORD userData[4];																						   // 0x04
	void* pData;																							   // 0x14
	size_t nFileSize;																						   // 0x18
};

struct AsyncData // sizeof(0x54)
{
	HSFILE hFile;							 // 0x00
	void* pMemPool;							 // 0x04
	OVERLAPPED tOverlapped;					 // 0x08
	AsyncDataLoadFileCallback pAsyncOpDesc;	 // 0x1C
	struct AsyncDataEventSlot* pEventSlot;	 // 0x38
	void* pBuffer;							 // 0x3C
	uint32_t nFileSize;						 // 0x40
	uint32_t nPriority;						 // 0x44 D2C_AsyncDataPriority
	uint32_t nFlags;						 // 0x48
	uint32_t nPreviousPriority;				 // 0x4C
	AsyncData* pNextPostponedPriorityChange; // 0x50
};

struct AsyncDataEventSlot // sizeof(0x0C)
{
	HANDLE hEvent;		  // 0x00
	DWORD bSlotAvailable; // 0x04
	AsyncData* pAsyncOp;  // 0x08
};

struct QServer;

#pragma pack()

typedef int (*D2ExceptionCallback)();

const char* __cdecl FOG_csprintf(char* szDest, const char* szFormat, ...);
D2FUNC_DLL(FOG, InitErrorMgr, void, __fastcall, (const char* szProgramName, D2ExceptionCallback pExceptionCallback, const char* szVersion, BOOL bLogToFile), 0xE1B0) // Fog.#10019
D2FUNC_DLL(FOG, SetLogPrefix, int, __fastcall, (const char* szLogPrefix), 0xE1A0)																					 // Fog.#10021
FOG_DLL_DECL void* __cdecl FOG_GetSystemInfo();																											 // Fog.#10022
// Log to default logfile with date and `\n` at end of message
D2FUNC_DLL(FOG, Trace, void, __cdecl, (const char* szFormat, ...), 0x120A0) // Fog.#10029
// Log to file. Will be prefixed with "D2" and suffixed by date. Log includes date prefix and `\n` at end of message.
D2FUNC_DLL(FOG, TraceF, void, __cdecl, (const char* pFileSubName, const char* szFormat, ...), 0x120E0) // Fog.#10030
// Append to the default logfile. No date nor '\n'.
FOG_DLL_DECL void __cdecl FOG_TraceAppend(const char* szFormat, ...);																										// Fog.#10031
FOG_DLL_DECL void __cdecl FOG_TraceMemory(const char* pFileSubName, const char* szMessage, void* pMemory, size_t nByteCount, BOOL bLogOffset, BOOL bNoCopy, BOOL bNoASCII); // Fog.#10032
FOG_DLL_DECL void __fastcall FOG_CrashDeadlockDetected(HANDLE hThreadToWalk);																								// Fog.#10033
FOG_DLL_DECL void __fastcall FOG_CrashDumpThread(HANDLE hThreadToWalk);																										// Fog.#10034
D2FUNC_DLL(FOG, IsHandlingError, BOOL, __cdecl, (), 0xF2A0)																																// Fog.#10039
D2FUNC_DLL(FOG, 10050_EnterCriticalSection, void, __fastcall, (_Acquires_lock_(*_Curr_) CRITICAL_SECTION * pCriticalSection, int nLine), 0xDC20)										// Fog.#10050
D2FUNC_DLL(FOG, 10055_GetSyncTime, int32_t, __fastcall, (), 0xA690)																														// Fog.#10055
// Noop, same as 10048, 10049, 10053, 10054, 10146, 10194, 10195, 10196, 10197, 10220, 10221, 10225, 10232, 10240, 10241, 10242
D2FUNC_DLL(FOG, 10082_Noop, void, __fastcall, (), 0x1DE0)												 // Fog.#10082
D2FUNC_DLL(FOG, 10083_Cos_LUT, float, __stdcall, (int16_t index), 0x1DF0)								 // Fog.#10083
D2FUNC_DLL(FOG, 10084_Sin_LUT, float, __stdcall, (int16_t index), 0x1E10)								 // Fog.#10084
FOG_DLL_DECL unsigned __stdcall FOG_Decode14BitsFromString(uint16_t* p2Characters);			 // Fog.#10085
D2FUNC_DLL(FOG, Encode14BitsToString, void, __stdcall, (uint16_t* p2Characters, uint32_t value), 0x1B40) // Fog.#10086
// Note: works up to value 0xFC05FC00
FOG_DLL_DECL unsigned __stdcall FOG_Decode32BitsFromString(uint32_t* p4Characters);																																											// Fog.#10087
FOG_DLL_DECL void __stdcall FOG_Encode32BitsToString(uint32_t* p4Characters, uint32_t value);																																								// Fog.#10088
D2FUNC_DLL(FOG, AsyncDataInitialize, void, __fastcall, (BOOL bEnableAsyncOperations), 0xC010)																																											// Fog.#10089
D2FUNC_DLL(FOG, AsyncDataDestroy, void, __fastcall, (), 0xC0E0)																																																			// Fog.#10090
FOG_DLL_DECL AsyncData* __fastcall FOG_AsyncDataLoadFileEx(void* pMemPool, const char* pFileName, BOOL bAllowAsync, LONG nFileOffset, int nFileSize, void* pBuffer, AsyncDataLoadFileCallback* asyncOpDesc, int a8, const char* sourceFile, int sourceLine); // Fog.#10091
FOG_DLL_DECL BOOL __fastcall FOG_AsyncDataTestLoaded(AsyncData * pAsyncData);																																												// Fog.#10092
FOG_DLL_DECL void __fastcall FOG_AsyncDataWaitAndGetBuffer(AsyncData * pAsyncData);																																											// Fog.#10093
FOG_DLL_DECL void* __fastcall FOG_AsyncDataGetBuffer(AsyncData * pAsyncData);																																												// Fog.#10094
FOG_DLL_DECL DWORD __fastcall FOG_AsyncDataGetBufferSize(AsyncData * pAsyncData);																																											// Fog.#10095
FOG_DLL_DECL void __fastcall FOG_AsyncDataSetResults(AsyncData * pAsyncData, void* pBuffer, int nBufferSize);																																				// Fog.#10096
FOG_DLL_DECL void __fastcall FOG_AsyncDataFree(AsyncData * pAsyncData);																																														// Fog.#10097
FOG_DLL_DECL void __fastcall FOG_AsyncDataSetPriority(AsyncData * pAsyncData, int nPriority);																																								// Fog.#10099
FOG_DLL_DECL void __fastcall FOG_AsyncDataHandlePriorityChanges(BOOL bPostpone);																																												// Fog.#10100
FOG_DLL_DECL BOOL __fastcall FOG_FOpenFile(const char* szFile, HSFILE* pFileHandle);																																										// Fog.#10102
FOG_DLL_DECL void __fastcall FOG_FCloseFile(HSFILE pFile);																																																	// Fog.#10103
FOG_DLL_DECL BOOL __fastcall FOG_FReadFile(HSFILE pFile, void* pBuffer, size_t nSize, int* nBytesRead, uint32_t, uint32_t, uint32_t);																														// Fog.#10104
FOG_DLL_DECL uint32_t __fastcall FOG_FGetFileSize(HSFILE pFileHandle, size_t* lpFileSizeHigh);																																								// Fog.#10105
FOG_DLL_DECL size_t __fastcall FOG_FSetFilePointer(HSFILE hFile, int32_t lDistanceToMove, int32_t* lpDistanceToMoveHigh, uint32_t dwMoveMethod);																											// Fog.#10106
D2FUNC_DLL(FOG, CreateFileA, HANDLE, __fastcall, (LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile), 0x11680);					// Fog.#10107
FOG_DLL_DECL BOOL __fastcall FOG_DeleteFileA(LPCSTR lpFileName);;																																															// Fog.#10108
D2FUNC_DLL(FOG, CloseFile, BOOL, __fastcall, (HANDLE hFILE), 0x116C0);																																																	// Fog.#10109
FOG_DLL_DECL BOOL __fastcall FOG_CreatePathHierarchy(char* szPath);																																															// Fog.#10114
FOG_DLL_DECL size_t __fastcall FOG_GetSavePath(char* pPathBuffer, size_t nBufferSize);																																										// Fog.#10115
FOG_DLL_DECL BOOL __fastcall FOG_GetInstallPath(char* pPathBuffer, size_t nBufferSize);																																										// Fog.#10116
D2FUNC_DLL(FOG, ComputeStringCRC16, uint16_t, __stdcall, (const char* szString), 0x3DB0)																																												// Fog.#10137
D2FUNC_DLL(FOG, CreateNewPoolSystem, void, __cdecl, (void** pMemPoolSystem, const char* szName, uint32_t nPools, uint32_t nUnused), 0xA280)																																// Fog.#10142
D2FUNC_DLL(FOG, DestroyMemoryPoolSystem, void, __cdecl, (void* pMemoryPoolSystem), 0xA100)																																												// Fog.#10143
FOG_DLL_DECL void __cdecl FOG_SetMemoryPoolSystemMode(void* pMemoryPoolSystem, BOOL bFreePoolAlloc);																																							// Fog.#10145
D2FUNC_DLL(FOG, GetMemoryUsage, DWORD, __cdecl, (void*), 0xA4E0)																																																		// Fog.#10147
FOG_DLL_DECL QServer* __stdcall FOG_InitializeServer(int, int, int, int, void*, void*, void*, void*);																																						// Fog.#10149
FOG_DLL_DECL int __stdcall FOG_SetMaxClientsPerGame(QServer*, int);																																															// Fog.#10151
FOG_DLL_DECL int __stdcall FOG_10152(void*, const uint8_t*, int);																																															// Fog.#10152
FOG_DLL_DECL int __stdcall FOG_WaitForSingleObject(void*, int);																																																// Fog.#10154
FOG_DLL_DECL int __stdcall FOG_10156(void*, int, uint8_t*, int);																																																// Fog.#10156
FOG_DLL_DECL int __stdcall FOG_10157(void*, int, const uint8_t*, int);																																														// Fog.#10157
FOG_DLL_DECL int __stdcall FOG_10158(void*, int);																																																			// Fog.#10158
FOG_DLL_DECL int __stdcall FOG_10159(void*, int, char*, int);																																																// Fog.#10159
FOG_DLL_DECL int __stdcall FOG_10161(void*, int);																																																			// Fog.#10161
FOG_DLL_DECL int __stdcall FOG_10162(void*, int, const char*, int);																																															// Fog.#10162
FOG_DLL_DECL int __stdcall FOG_10163(void*, int, const char*, int);																																															// Fog.#10163
FOG_DLL_DECL int __stdcall FOG_10164(void*, int, int, int);																																																	// Fog.#10164
FOG_DLL_DECL int __stdcall FOG_10165(void*, int, const char*, int);																																															// Fog.#10165
FOG_DLL_DECL int __stdcall FOG_10166(void*, int, int, int);																																																	// Fog.#10166
FOG_DLL_DECL int __stdcall FOG_10170(void*, int);																																																			// Fog.#10170
FOG_DLL_DECL int __stdcall FOG_10171(void*, void*);																																																			// Fog.#10171
FOG_DLL_DECL int __stdcall FOG_10172(void*, int, int);																																																		// Fog.#10172
FOG_DLL_DECL int __stdcall FOG_10173(void*, int);																																																			// Fog.#10173
FOG_DLL_DECL int __stdcall FOG_10175(void*, const uint8_t*, int, int);																																														// Fog.#10175
FOG_DLL_DECL int __stdcall FOG_10177(void*, int);																																																			// Fog.#10177
FOG_DLL_DECL int __stdcall FOG_SetHackListEnabled(QServer * pServer, BOOL bHacklistEnabled);																																									// Fog.#10178
FOG_DLL_DECL int __stdcall FOG_10180(void*);																																																					// Fog.#10180
FOG_DLL_DECL int __stdcall FOG_10181(void*, const uint8_t*, int, int);																																														// Fog.#10181
D2FUNC_DLL(FOG, 10182_Return, int, __stdcall, (void*), 0x1B10)																																																			// Fog.#10182
D2FUNC_DLL(FOG, 10183_Return, int, __stdcall, (void*, int), 0x7620)																																																		// Fog.#10183
FOG_DLL_DECL int __stdcall FOG_10186(void*, int, int);																																																		// Fog.#10186
FOG_DLL_DECL int __fastcall FOG_10187(void*, int, int);																																																		// Fog.#10187
FOG_DLL_DECL void __stdcall FOG_10207(D2BinFileStrc * pBinFile, D2BinFieldStrc* pBinField, void* pTxt, int nRecordCount, int nRecordSize);																													// Fog.#10207
FOG_DLL_DECL D2BinFileStrc* __stdcall FOG_CreateBinFile(void* pDataBuffer, int nBufferSize);																																									// Fog.#10208
FOG_DLL_DECL void __stdcall FOG_FreeBinFile(D2BinFileStrc * pBinFile);																																														// Fog.#10209
FOG_DLL_DECL int __stdcall FOG_GetRecordCountFromBinFile(D2BinFileStrc * pBinFile);																																											// Fog.#10210
FOG_DLL_DECL void* __stdcall FOG_AllocLinker(const char* szFile, int nLine);																																													// Fog.#10211
FOG_DLL_DECL void __stdcall FOG_FreeLinker(void* pLinker);																																																	// Fog.#10212
FOG_DLL_DECL int __stdcall FOG_GetLinkIndex(void* pLink, uint32_t dwCode, BOOL bLogError);																																									// Fog.#10213
FOG_DLL_DECL int __stdcall FOG_GetStringFromLinkIndex(void* pLinker, int nIndex, char* szString);																																							// Fog.#10214
FOG_DLL_DECL int __stdcall FOG_10215(void* pBin, int a2);																																																	// Fog.#10215
FOG_DLL_DECL int __stdcall FOG_10216_AddRecordToLinkingTable(void* pBin, const char* a2);																																									// Fog.#10216
FOG_DLL_DECL int __stdcall FOG_GetRowFromTxt(void* pBin, char* szText, int nColumn);																																											// Fog.#10217
D2FUNC_DLL(FOG, 10218, int, __fastcall, (), 0xCC40)																																																						// Fog.#10218
FOG_DLL_DECL int __fastcall FOG_10219(uint8_t*);																																																				// Fog.#10219
FOG_DLL_DECL int __fastcall FOG_10222(const uint8_t*, int);																																																	// Fog.#10222
FOG_DLL_DECL int __fastcall FOG_10223(uint8_t*, int, const uint8_t*, int);																																													// Fog.#10223
FOG_DLL_DECL int __fastcall FOG_10224(char*, int, uint8_t*, int);																																															// Fog.#10224
int __fastcall FOG_IsExpansion();
FOG_DLL_DECL uint32_t __stdcall FOG_ComputeChecksum(void* pData, size_t dwSize); // Fog.#10229
D2FUNC_DLL(FOG, PopCount, uint32_t, __stdcall, (void* pData, size_t dwSize), 0x3970)		// Fog.#10230
D2FUNC_DLL(FOG, 10233, void, __fastcall, (const char*, int), 0xF300)						// Fog.#10233
FOG_DLL_DECL uint32_t __stdcall FOG_LeadingZeroesCount(uint32_t nValue);			// Fog.#10252
FOG_DLL_DECL char* __stdcall FOG_10255(void* pLinker, int nId, int a3);			// Fog.#10255

#define D2_ALLOC(size) FOG_Alloc((size), __FILE__, __LINE__, 0)
#define D2_CALLOC(size) memset(FOG_Alloc(size, __FILE__, __LINE__, 0), 0x00, size)
#define D2_ALLOC_STRC(type) (type*)FOG_Alloc(sizeof(type), __FILE__, __LINE__, 0)
#define D2_CALLOC_STRC(type) (type*)memset(FOG_Alloc(sizeof(type), __FILE__, __LINE__, 0), 0x00, sizeof(type))
#define D2_FREE(ptr) FOG_Free(ptr, __FILE__, __LINE__, 0)

#define D2_ALLOC_POOL(pMemPool, size) FOG_AllocPool(pMemPool, size, __FILE__, __LINE__, 0)
#define D2_CALLOC_POOL(pMemPool, size) memset(FOG_AllocPool(pMemPool, size, __FILE__, __LINE__, 0), 0x00, size)
#define D2_REALLOC_POOL(pMemPool, pMem, size) FOG_ReallocPool(pMemPool, pMem, size, __FILE__, __LINE__, 0)
#define D2_ALLOC_STRC_POOL(pMemPool, type) (type*)FOG_AllocPool(pMemPool, sizeof(type), __FILE__, __LINE__, 0)
#define D2_CALLOC_STRC_POOL(pMemPool, type) (type*)memset(FOG_AllocPool(pMemPool, sizeof(type), __FILE__, __LINE__, 0), 0x00, sizeof(type))
#define D2_FREE_POOL(pMemPool, ptr) FOG_FreePool(pMemPool, ptr, __FILE__, __LINE__, 0)

#ifndef NDEBUG
// Assert that an expression must be true, otherwise assume the program state will not be recoverable.
// In debug builds, this will trigger a log and exit, in release this is used as a hint for performance optimization.
// Do NOT use this if the program can recover when expr if false, as it is used as a hint for performance and can impact generated code.
// For recoverable errors, use D2_VERIFY
#define D2_DISPLAY_ASSERT_THEN_BREAK(msg) (FOG_DisplayAssert(msg, __FILE__, __LINE__), __debugbreak())
#define D2_ASSERT(expr)                                                       \
	(void)((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(#expr), exit(-1), 0)); \
	_Analysis_assume_(expr)
#define D2_ASSERTM(expr, msg)                                               \
	(void)((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(msg), exit(-1), 0)); \
	_Analysis_assume_(expr)
#define D2_CHECK(expr)                                                        \
	(void)((!!(expr)) || (FOG_DisplayWarning(#expr, __FILE__, __LINE__), 0)); \
	_Analysis_assume_(expr)

// Assert that an expression must be true, even though the program may be recoverable.
// Contrary to D2_ASSERT, this is still evaluated in release builds, and can be used anywhere the expression would be valid.
// This is to be used when one can recover from an error
// Example:
// if(D2_VERIFY(ptr != nullptr)) ptr->method(); // The only difference between debug and release build is the logging and breakpoint
#define D2_VERIFY(expr) ((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(#expr), false))
#define D2_VERIFYM(expr, msg) ((!!(expr)) || (D2_DISPLAY_ASSERT_THEN_BREAK(msg), false))
#else
#if defined(__clang__)
																				   // the argument to '__builtin_assume' has side effects that will be discarded
#pragma clang diagnostic ignored "-Wassume"
#endif // defined(__clang__)
#ifdef __clang__
#define D2_ASSERT(expr) (__builtin_assume(expr), (void)0)
#define D2_ASSERTM(expr, msg) (__builtin_assume(expr), (void)0)
#define D2_VERIFY(expr) (!!(expr))
#define D2_VERIFYM(expr, msg) (!!(expr))
#define D2_CHECK(expr) (__builtin_assume(expr), (void)0)
#else
#define D2_ASSERT(expr) (__assume(expr), (void)0)
#define D2_ASSERTM(expr, msg) (__assume(expr), (void)0)
#define D2_VERIFY(expr) (!!(expr))
#define D2_VERIFYM(expr, msg) (!!(expr))
#define D2_CHECK(expr) (__assume(expr), (void)0)
#endif
#endif
#define D2_UNREACHABLE D2_ASSERT(false)

#define D2_LOCK(pCriticalSection) \
	D2_ASSERT(pCriticalSection);  \
	FOG_10050_EnterCriticalSection(pCriticalSection, __LINE__);
#define D2_UNLOCK(pCriticalSection) \
	D2_ASSERT(pCriticalSection);    \
	LeaveCriticalSection(pCriticalSection);
