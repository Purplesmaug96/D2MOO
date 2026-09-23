#ifndef D2SERVER_H
#define D2SERVER_H

/*
 * d2server.h — Header for decompiled D2Server (1.07 beta)
 * Only type aliases, macros, forward declarations, and extern globals.
 * NO function bodies — the decompiled .cpp defines everything itself.
 */

#include <windows.h>
#include <stdint.h>

#ifndef __thiscall
#ifdef _MSC_VER
#define __thiscall __thiscall
#else
#define __thiscall
#endif
#endif

#ifndef ULONG_PTR
typedef uintptr_t ULONG_PTR;
#endif

/* Ghidra decompiler type aliases */
typedef unsigned char byte;
typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined3;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef int int3;

/* Missing type aliases */
typedef wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef BOOL* LPBOOL;
typedef WORD* LPWORD;
typedef void* PVOID;
typedef const wchar_t* PCNZWCH;
typedef const char* PCNZCH;
typedef DWORD LCTYPE;
typedef struct _EXCEPTION_RECORD *PEXCEPTION_RECORD;

#ifndef CPINFO
typedef struct _cpinfo {
    UINT MaxCharSize;
    BYTE DefaultChar[2];
    BYTE LeadByte[12];
} CPINFO, *LPCPINFO;
#endif

/* Forward declare RtlUnwind */
void RtlUnwind(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue);

struct _EXCEPTION_RECORD {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[15];
};



/* CONCAT macros */
#define CONCAT11(a,b) ((unsigned short)((unsigned char)(a) | ((unsigned short)(unsigned char)(b) << 8)))
#define CONCAT13(a,b) ((unsigned int)((unsigned char)(a) | ((unsigned int)(b) << 8)))
#define CONCAT22(a,b) ((unsigned int)((unsigned short)(a) | ((unsigned int)(unsigned short)(b) << 16)))
#define CONCAT31(a,b) ((unsigned int)((unsigned int)(a) | ((unsigned int)(unsigned char)(b) << 24)))
#define CONCAT41(a,b) ((unsigned long long)((unsigned int)(a) | ((unsigned long long)(unsigned char)(b) << 32)))
#define CONCAT12(a,b) ((unsigned int)((unsigned char)(a) | ((unsigned int)(unsigned short)(b) << 8)))
#define CONCAT44(a,b) ((unsigned long long)((unsigned int)(a) | ((unsigned long long)(unsigned int)(b) << 32)))
#define CARRY4(a,b) ((unsigned int)(a) + (unsigned int)(b) < (unsigned int)(a))

/* MSVC CRT intrinsics - only ones NOT defined in decompiled code */
longlong __allmul(unsigned int a_lo, unsigned int a_hi, unsigned int b_lo, unsigned int b_hi);
unsigned int __cdecl __alldiv(unsigned int num_lo, unsigned int num_hi, unsigned int den_lo, unsigned int den_hi);
int __cdecl _ftime64(void *t);
int __cdecl _CRTDLL_INIT(int a, int b);
int __cdecl _cinit(int f);
void __cdecl _cexit(void);
void __cdecl initterm(void *a, void *b);
void __cdecl _initterm_table(void);
void __cdecl _lock_cs_d(int n);
void __cdecl _unlock_cs_d(int n);
int __cdecl _rand(void);
void __cdecl __crt_exit_process(int code);
void __cdecl __global_unwind2(void *e);
void __cdecl __local_unwind2(void *f, int t);
void __cdecl __NLG_Notify1(int a, int b);
void __cdecl _EH_prolog3_catch(void *a);
void __cdecl _except_handler3(void);
int __cdecl _exit_wrapper(int code);
int __cdecl __exit(int code);

/* Forward declarations for decompiled D2Server internal functions */
void __fastcall GameData_ChunkClearEntry(int param_1);
void __fastcall GameData_ListNode_Detach4(int *param_1);
void __fastcall GameDataPool_FreeList(int param_1);
void __fastcall GameDataPool_DetachAll3(int *param_1);
void __fastcall GameDataPool_DetachList(int *param_1);
void __fastcall GameData_ListNode_Detach2(int *param_1);
void __fastcall GameDataPool_RemoveAll(int param_1);
uint * __fastcall Game_FindByGameId(uint dwGameId);
undefined4 __fastcall Token_AddOrUpdate(undefined4 p1, undefined4 p2, undefined4 p3, undefined4 p4, undefined4 p5);
undefined4 Server_EnumerateCharacters(void);
undefined4 __fastcall Server_SendFileData(char *szFileName, int pFileBuffer, int nFileSize);
int __fastcall GameData_PoolAddOffset(int param_1, int param_2);
int * __fastcall MPQ_OpenWithRetry(undefined4 pArchiveInfo, LPCSTR szFileName, undefined4 nPriority, undefined4 nFlags, undefined *pRetryCallback);
LPSTR __thiscall Archive_FindFileEx(void *_this, LPCSTR szFileName, undefined4 dwFlags, undefined4 dwTimeout);
undefined4 __fastcall Archive_SearchCdDrives(LPSTR szPath, LPCSTR szFileName, undefined4 dwFlags, undefined4 pFileHandle);
void Console_WriteGraphDisplay(int bAlsoDebugFile, byte *szFormat);
void Console_DestroyGraphDisplay(void);
void Console_SyncGameList(void);
void Console_UpdateBusyPercent(void);
void Console_UpdateGameDetails(void);
void __fastcall Console_GraphDrawDataPoint(int pGraph, int x);
void Game_AddToList(char *szGameName);
void __thiscall GameData_AllocGameEntry(void *_this, unsigned int p1, int p2, uint p3);
int __thiscall GameData_DeletingDestructor2(void *_this, byte param_1);
uint __thiscall GameData_PoolIndexToNode(void *_this, int param_1);
int * __thiscall GameData_PoolGetBeginNode(void *_this, int param_1);
int * __thiscall GameData_ListNode_Clear(void *_this, byte param_1);
uint __thiscall GameData_PoolIndexToNode2(void *_this, int param_1);

/* Dialog/SEH callback functions */
LRESULT __stdcall LAB_10001307(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall LAB_100010f0(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void LAB_1001a5f5(void);
void LAB_1001a581(void);
void LAB_1001a4c5(void);
void LAB_1001a674(void);
void LAB_1001a62b(void);
void LAB_100012a8(void);
void LAB_1000ac6c(void);
void LAB_1000c97e(void);
void LAB_1000c9cc(void);
void LAB_1000f844(void);

/* Forward declarations for CRT functions defined in decompiled code */
int _strlen(const char *s);
void* _malloc(size_t size);
void* _memset(void *s, int c, size_t n);
char* _strchr(const char *s, int c);
char* _strrchr(const char *s, int c);
size_t _strnlen(const char *s, size_t maxlen);
char* _strdup(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _stricmp(const char *s1, const char *s2);
int _strnicmp(const char *s1, const char *s2, size_t n);
int* _errno(void);
int _fclose(int *stream);
int __strncnt(const char *s, int n);
void memmove2(void *dest, const void *src, size_t n);
int _add_carry(unsigned int a, unsigned int b, unsigned int *result);
void _ld10pow(int *result, int exp, int flag);
void _ldmul(int *result, int *operands);
int _getlocaleinfo(int a, int b, int c, char *d);
void _strip_semicolons2(char *s);
int _alpha_len(const char *s);
void _fmt_dec_out(int a, unsigned int b, int *c, unsigned int *d);
void _fmt_dec_out_lz(int a, int *b, unsigned int *c);
void _fmt_str_out(char *a, int *b, int *c);
void _fmt_locale_time(unsigned char *a, int b, int *c, unsigned int *d, int e);
int _strcoll_core(int a, unsigned int b, unsigned char *c, int d, unsigned char *e, int f, unsigned int g);
void _lock_critical_section(int n);
void _unlock_critical_section(int n);
void _strip_semicolons(char *s);
void _vsprintf_l(char *buf, byte *fmt, ...);
void _vsnprintf(char *buf, byte *fmt, ...);
void _build_case_tables(void);

/* Win32 API stubs (not defined elsewhere) */
static inline int WideCharToMultiByte(UINT a, DWORD b, LPCWSTR c, int d, LPSTR e, int f, LPCSTR g, LPBOOL h) { return 0; }
static inline int MultiByteToWideChar(UINT a, DWORD b, LPCSTR c, int d, LPWSTR e, int f) { return 0; }
static inline BOOL GetStringTypeA(LCID a, DWORD b, LPCSTR c, int d, LPWORD e) { return 0; }
static inline BOOL GetStringTypeW(DWORD a, LPCWSTR b, int c, LPWORD d) { return 0; }
static inline int LCMapStringA(LCID a, DWORD b, LPCSTR c, int d, LPSTR e, int f) { return 0; }
static inline int LCMapStringW(LCID a, DWORD b, LPCWSTR c, int d, LPWSTR e, int f) { return 0; }
static inline int CompareStringA(LCID a, DWORD b, PCNZCH c, int d, PCNZCH e, int f) { return 0; }
static inline int CompareStringW(LCID a, DWORD b, PCNZWCH c, int d, PCNZWCH e, int f) { return 0; }
static inline int GetLocaleInfoA(LCID a, LCTYPE b, LPSTR c, int d) { return 0; }
static inline int GetLocaleInfoW(LCID a, LCTYPE b, LPWSTR c, int d) { return 0; }
static inline BOOL EnumSystemLocalesA(void* a, DWORD b) { return 0; }
static inline BOOL GetCPInfo(UINT a, void *b) { return 0; }
static inline DWORD GetACP(void) { return 65001; }
static inline DWORD GetOEMCP(void) { return 437; }
static inline int _getlocale_all(void) { return 0; }
static inline void SetStdHandle(int a, void* b) {}
static inline BOOL HeapFree(void* a, DWORD b, void* c) { return 0; }
static inline void* HeapAlloc(void* a, DWORD b, size_t c) { return 0; }
static inline void* GetProcessHeap(void) { return 0; }
static inline void HeapDestroy(void* a) {}
static inline void HeapCreate_v(int a, int b, int c) {}
static inline BOOL IsBadWritePtr(void* a, UINT b) { return 0; }
static inline void* VirtualAlloc(void* a, size_t b, DWORD c, DWORD d) { return 0; }
static inline BOOL VirtualFree(void* a, size_t b, DWORD c) { return 0; }
static inline DWORD TlsAlloc(void) { return 0; }
static inline BOOL TlsFree(DWORD a) { return 0; }
static inline void* TlsGetValue(DWORD a) { return 0; }
static inline BOOL TlsSetValue(DWORD a, void* b) { return 0; }
static inline void _ldclrbit(unsigned int *a, int b) {}
static inline void _dosmaperr(unsigned int a) {}
static inline void builtin_memcpy(void *a, const void *b, size_t c) {}
static inline void swi(int a) {}
static inline void _strshift_right(int a, int b) {}
static inline void _flush(int a) {}
static inline void _lcmapstring(int a, int b, int c, int d, int e, int f, int g, int h) {}
static inline void _out_putc_wide(int a, int b) {}
static inline void _lock_cs_uninit(void) {}
static inline void _statusfp_get(void* a) {}
static inline void _pcgetenv_denorm(int a) {}
static inline int _getptd(void) { return 0; }
static inline int _siglookup(int a, int b) { return 0; }

/* Storm.dll imports */
void * __stdcall SMemAlloc(int size, char *source, int flags, int fill);
void __stdcall SMemFree(void *ptr, char *source, int flags, int u);
void * __stdcall SMemReAlloc(void *ptr, int size, char *source, int flags, int u);
int __stdcall SStrCopy(char *dest, char *src, int maxlen);
int __stdcall SStrCmp(char *s1, char *s2, int maxlen);
int __cdecl SStrPrintf(char *buf, int bufsize, char *fmt, ...);
int __stdcall SRegLoadString(char *key, char *subkey, int flags, char *buf, int bufsize);
int __stdcall SRegSaveString(char *key, char *subkey, int flags, char *buf, int bufsize);
int __stdcall SFileGetFileName(int hFile, char *buf, int bufsize);
int __stdcall SStrNCat(char *dest, char *src, int maxlen);
int __stdcall SFileOpenArchive(char *path, int priority, int flags, int *phArchive);
int __stdcall SFileCloseArchive(int hArchive);

/* FOG.dll ordinals */
int __cdecl FOG_GetHostIPAddress(void);
int __cdecl FOG_InitErrorMgr(void);
int __cdecl FOG_SetExceptionFilter(void);
void __cdecl FOG_SetLogPrefix(char *a, char *b, int c);
void __cdecl FOG_GetSystemInfo(char *a, char *b, int c);
void __cdecl FOG_DisplayHalt(int a, char *b, char *c, int d);
void __cdecl FOG_DisplayError(char *msg, ...);
int __cdecl FOG_CrashDeadlockDetected(int a, int b, ...);
void __cdecl FOG_CrashDumpThread(int a, int b);
int __cdecl FOG_Log(void);
int __cdecl FOG_ReallocPool(void);
int __cdecl FOG_Noop(void);
int __cdecl FOG_Send(void *a, void *b, int c, ...);
int __cdecl FOG_EnterCriticalSection(int a, void *b, int c);
int __cdecl FOG_LeaveCriticalSection(void *a, void *b, int c);
int __cdecl FOG_ExceptionHandler(int a);
int __cdecl FOG_Noop3(int a);
int __cdecl FOG_GetSyncTime(int a, int b);
int __cdecl FOG_GetDiskInfo(void);
int __cdecl FOG_InitTimers(int a);
int __cdecl FOG_SOCKET_MarkConnected(int a, int b);
int __cdecl FOG_SOCKET_InvokeCallback(void);
int __cdecl FOG_SOCKET_SetCallbacks(int a, int b, int c, int d);
int __cdecl FOG_SOCKET_SetDispatch(void);
int __cdecl FOG_SOCKET_AddRef(int a, int b);
void __cdecl FOG_GetSavePath(void);
void __cdecl FOG_CharToUpper(void);

/* D2GAME.dll ordinals */
int __cdecl D2GAME_10002(void *a, void *b);
int __cdecl D2GAME_10003(void);
int __cdecl D2GAME_10006(void);
int __cdecl D2GAME_10007(void);
int __cdecl D2GAME_10012(void);
int __cdecl D2GAME_10014(void *a, void *b);
int __cdecl D2GAME_10015(void *a, int b);
int __cdecl D2GAME_10018(int a, int b, int c, int d, int e);
int __cdecl D2GAME_10019(int a, int b, int c);
int __cdecl D2GAME_10020(void *a);
int __cdecl D2GAME_10021(int a, int b, char *msg);
int __cdecl D2GAME_10023(void *a);
int __cdecl D2GAME_10039(void);
int __cdecl D2GAME_10040(void);
int __cdecl D2GAME_10041(void);
int __cdecl D2GAME_10043(void);
int __cdecl D2GAME_10045(void);
int __cdecl D2GAME_10046(void);
int __cdecl D2GAME_10047(int a, int b, int c, int d, int e, int f, int g, int h);
int __cdecl D2GAME_10048(int a, void *b, int c, int d, int e, int f);
int __cdecl D2GAME_10049(int a, void *b, int c, int d, int e, int f);
int __cdecl D2GAME_10050(void);

/* D2NET.dll ordinals */
int __cdecl SERVER_Initialize(int a, int b);
int __cdecl SERVER_Release(void);
int __cdecl D2NET_10018(int a);
int __cdecl D2NET_10022(int mask);
int __cdecl SERVER_SetHackListEnabled(int a);
int __cdecl D2NET_10033(int a);

/* D2COMMON.dll ordinals */
int __cdecl STATES_CheckStateMaskExp(void);
int __cdecl STATES_CheckStateMaskStayDeath(void *a, int b, int c);
int __cdecl D2COMMON_10980(void);
int __cdecl D2COMMON_10983(void);
int __cdecl D2COMMON_10984(void);

/* D2LANG.dll ordinals */
int __cdecl D2Lang_Initialize(void);
int __cdecl D2Lang_Uninitialize(void);

/* ===================== GLOBAL VARIABLES ===================== */
extern void *pExceptionList;
extern char s__3d____s___d__d__100208ac[];
extern int *ghD2DataMPQ;
extern int *ghD2CharMPQ;
extern void *ghGameServer;
extern void *g_hInstance;
extern void *g_hMainInstance;
extern int  bShutdownFlag;
extern int  bMcpConnected;
extern int  bServerRunning;
extern int  nCharServerSelector;
extern void *ghConsoleDlg;
extern void *ghCmdDialog;
extern int  nGameCount;
extern int  nPlayerCount;
extern void *g_pDllCallback;
extern int  crtInitCount;
extern int  dwLastTickCount;
extern int  dwLastKeepAliveTick;
extern int  stStartTime;
extern int  nActiveWorkerThreads;
extern void *gpBnclientInterface;
extern int  sPerfState;
extern void *sPerfLog;
extern void *sGraphState;
extern void *sGraphData;
extern void *pTokenListHead;
extern void *pGameListHead;
extern char sGameSearchName[256];
extern int  sGameDetailTable[64];
extern char gameInfoBuf[256];
extern int  sCharServerConns[32];
extern int  sCharServerConnsStatus;
extern char charName[32];
extern void *g_hGraphBrush;
extern void *g_lpOldGraphWndProc;
extern LARGE_INTEGER lpFrequency_10023180;
extern LARGE_INTEGER lpPerformanceCount_10023198;
extern LARGE_INTEGER lpPerformanceCount_10023168;
extern int  g_ClassFactoryVtable;
extern int  g_GameServerVtable1;
extern int  g_GameServerVtable2;
extern int  g_GameServerVtable3;
extern int  g_GameServerVtable4;
extern int  g_InitFuncTableStart;
extern int  g_InitFuncTableEnd;
extern int  g_GameEngineData1;
extern int  g_GameEngineData2;
extern int  g_NetEventCallback;
extern int  pInitTable;
extern int  pGameEngineFuncTable;
extern int  lpStartAddress_1000133e;
extern int  lpStartAddress_10001104;
extern int  lpStartAddress_1000113b;
extern int  PTR_Console_DisplayHelp_1001f158;
extern int  DAT_1001ee9c;
extern int  DAT_1001f058;
extern int  DAT_1002027c;
extern int  DAT_1002061c;
extern int  DAT_100207a8;
extern int  DAT_100207ac;
extern int  DAT_100207d0;
extern int  DAT_100207d4;
extern int  DAT_10020814;
extern int  DAT_10020818;
extern byte DAT_100208d0;
extern byte DAT_100208d4;
extern int  DAT_10021094;
extern int  DAT_1002313c;
extern int  DAT_10023160;
extern int  DAT_10023164;
extern int  DAT_10023184;
extern int  DAT_10023188;
extern int  DAT_1002318c;
extern int  DAT_10023190;
extern int  DAT_1002319c;
extern int  DAT_100231a4;
extern int  DAT_100231b8;
extern int  DAT_100231bc;
extern int  DAT_10023248;
extern int  DAT_10023254;
extern int  DAT_1002326c;
extern int  DAT_10023270;
extern int  DAT_100232b0;
extern int  DAT_100232b4;
extern int  DAT_100232b8;
extern int  _DAT_10023178;
extern int  _DAT_1002317c;
extern int  sMCPRecvRecord;
extern int  g_McpMessageHandlers;
extern int  g_GameServerCtorUnwind;
extern unsigned int uStack00000000;
extern unsigned int uStack00000008;
extern unsigned int uStack00000009;
extern unsigned int uStack0000000f;
extern unsigned int uStack00000011;

/* String literals */
extern char s_d2data_mpq_1001ed60[];
extern char s_d2data_1001ed58[];
extern char s_d2char_mpq_1001ed48[];
extern char s_d2char_1001ed40[];
extern char s_delete_1001ed70[];
extern char s__SERVER__Connected_to_MCP_at__s_1001ed80[];
extern char s__SERVER__Hack_listing_IP__s_1001eddc[];
extern char s_Diablo_II_1001edc8[];
extern char s_Bnclient_dll_1001ee8c[];
extern char s_Cannot_load_Bnclient_dll__Error___1001ee60[];
extern char s_D2Multi_1001ee54[];
extern char s_QueryInterface_1001ee40[];
extern char s_Unable_to_QueryInterface_for_Bnc_1001ee00[];
extern char s___WORD___pbData____nLength_1001eec8[];
extern char s_C__D2_Source_D2Server_CORE_CharS_1001eee8[];
extern char s__CHARACTER_SERVER__Connecting_to_1001efc4[];
extern char s__CHARACTER_SERVER__Connected_to_C_1001ef5c[];
extern char s__CHARACTER_SERVER__Chose_Primary_1001ef18[];
extern char s__CHARACTER_SERVER__Lost_connecti_1001f024[];
extern char s_Game_Server_[];
extern char Char_Server___d_1001efa0[];
extern char s_Display_Console_Commands_1001f15c[];
extern char s_ERROR__Unknown_command___10020620[];
extern char s_GTM_RECREATE_shouldn_t_be_sent_f_10020b50[];
extern char s_C__D2_Source_D2Server_CORE_FromM_10020b90[];
extern char s_C__D2_Source_D2Server_CORE_Displ_1002082c[];
extern char s__d__02d__02d_100210e0[];
extern char s__d___Busy_100208f8[];
extern char s__d___d____d__100208c0[];
extern char s__d__d__d__d__d_10020d78[];
extern char s__3d____s___d__d_100208ac[];
extern char s_Game_Id___d_10020adc[];
extern char s_Seed___d_10020ad0[];
extern char s_Clients___d_10020ac0[];
extern char s_Players___d_10020ab0[];
extern char s_Monsters___d_10020aa0[];
extern char s_Objects___d_10020a90[];
extern char s_Items___d_10020a84[];
extern char s_Missiles___d_10020a74[];
extern char s_Unique_Items___d_10020a48[];
extern char s_NPCs___d_10020a3c[];
extern char s_Next_Player_Id___d_10020a24[];
extern char s_Next_Object_Id___d_10020a0c[];
extern char s_Next_Item_Id___d_100209f8[];
extern char s_Next_Missile_Id___d_100209e0[];
extern char s_Next_Warp_Id___d_100209cc[];
extern char s_Next_Monster_Id___d_10020a5c[];
extern char s_Path_Toward_Pct___d_100209b4[];
extern char s_Path_Clock_Pct___d_1002099c[];
extern char s_Path_Countr_Pct___d_10020984[];
extern char s_Path_FoWall_Pct___d_1002096c[];
extern char s_Path_Astar_Pct___d_10020954[];
extern char s_Path_Total_Call___d_1002093c[];
extern char s_Frames_h____d_1002092c[];
extern char s_Time__min____d_10020918[];
extern char s_Frame_Rate___d_10020904[];
extern char s_ptwGameIds_100208d8[];
extern char s_ptGameInfo_100208e8[];
extern char s_Busy_Games_Players_ActiveMonster_10020d04[];
extern char s_Error_creating_performance_logfi_10020d44[];
extern char s_Error_10020d70[];
extern char s_C__D2_Performace_txt_10020bd0[];
extern char s__SERVER__Finished_Loading____100211fc[];
extern char s_FATAL__Lost_connection_to_charac_100210f0[];
extern char s_Shutdown_Remotely_by_MCP_100211dc[];
extern char s_Invalid_size_of_record_in_SrvDat_10021098[];
extern char s___AUSGAMEDATA___10021000[];
extern char s___AV__TSHashObjectChunk_USGAMEDA_10021020[];
extern char s___AV__TSExplicitList_USGAMEDATA__10021238[];
extern char s__Server_[];
extern char MCP___GTM_CREATEGAME__M_10020dc8[];
extern char MCP___GTM_JOINGAME__MCP_10020e1c[];
extern char s_hFile_10021298[];
extern char s_C__D2_Source_D2Hell_SRC_Archive__10021274[];
extern char s_dwBytesToRead____dwBytes_100212a0[];
extern char s_hWnd_10020e50[];
extern char s_CONSOLE_COMMANDS_10020e60[];
extern char s__Server__GTM_CREATEGAME_10020dc8[];
extern char s__Server__GTM_JOINGAME_10020e1c[];
extern char s_Diablo___s_10020bc0[];
extern char s_ptToken_10020d8c[];
extern char s_C__D2_Source_D2Server_PlayerToke_10020d98[];
extern char s_wClass_0x3c_NUM_PLAYERCLASS_10020e78[];
extern char s_C__D2_Source_D2Server_CORE_ToMCP_10020e98[];
extern char s_C__D2_Source_D2Server_CORE_WinMa_10021064[];
extern char s_wNumPlayers_in_Game_u__10021170[];
extern char s__Server__Shutdown_Complete__100211b0[];
extern char s_0x3f4[];
extern char s_Stack_Size____u_bytes__10021370[];
extern char s_WORKER_THREAD_START__1002135c[];
extern char s_WORKER_THREAD_END__10021348[];
extern char s_WORKER_THREAD_ERROR__10021334[];
extern char s_WORKER_THREAD_10021328[];
extern char s_C__D2_Source_D2Server_CORE_WinM_100211e0[];
extern char s__Server__s__d__d__10020e3c[];
extern char s__Server__s__s__10021208[];
extern char s__Server__s__08x__100211e8[];
extern char s_GAME_THREAD_START_100211d0[];
extern char s_GAME_THREAD_END_100211c0[];
extern char s_WORKER__100211b8[];
extern char s_pParam____10021188[];
extern char s_WaitForSingleObject_ret___d_10021160[];
extern char s_dwWaitResult_0x_08x_10021140[];
extern char s_dwBytesAvail____d_10021120[];
extern char s_WORKER_s_dwBytesToRead____d_10021100[];
extern char s_WORKER_ERROR__ReadFile_failed_100210b8[];
extern char s_WORKER_ERROR__Unknown_packet__10021090[];
extern char s_WORKER_ERROR__packet_too_large_10021068[];
extern char s_WORKER_ERROR__malloc_failed_10021018[];
extern char s_WORKER_ERROR__recv_failed_10020ff0[];
extern char s_WORKER_ERROR__WSARecv_failed_10020fc8[];
extern char s_WORKER_ERROR__connect_failed_10020fa0[];
extern char s_WORKER_ERROR__socket_failed_10020f78[];
extern char s_WORKER_ERROR__WSAStartup_failed_10020f40[];
extern char s_WORKER_THREAD_ID__d_10020bd0[];
extern char s_WORKER_ERROR__CreateThread_failed_10020ba8[];
extern char s_WORKER_ERROR__CreateEvent_failed_10020b80[];
extern char s_WORKER_WAITING_FOR_SERVER__10020d98[];
extern char s_WORKER_WAITING_FOR_SERVER__d__10020d70[];
extern char s_WORKER_WAITING_FOR_SERVER__d___10020d48[];
extern char s_WORKER_ERROR__select_failed_10020c58[];
extern char s_WORKER_ERROR__WSASocket_failed_10020c30[];
extern char s_WORKER_ERROR__WSAStartup_failed_10020bf8[];
extern char s_dwTimeout_ms__d_10020e60[];
extern char s_dwTimeout_ms__d__10020e40[];
extern char s_dwTimeout_ms__d___10020e20[];
extern char s_dwTimeout_ms__d____10020e00[];
extern char s_dwTimeout_ms__d______10020de0[];
extern char s_dwTimeout_ms__d_________10020dc0[];
extern char s_WORKER__d_10020f28[];
extern char s_WORKER__s_d_10020f08[];
extern char s_WORKER__s_s_10020ee8[];
extern char s_WORKER__s_10020ed4[];
extern char s_WORKER_10020ec8[];
extern char s_C__D2_Source_D2Server_CORE_Worker_10020ea0[];
extern char s_dwWaitResult_0x_08x_0d_10020e80[];

/* Data variables */
extern int DAT_1001c03c;
extern int DAT_1001c05c;
extern int DAT_1001c0d0;
extern int DAT_1001c0e0;
extern int DAT_1001c0f8;
extern int DAT_1001c108;
extern int DAT_1001c118;
extern int DAT_1001c130;
extern int DAT_1001c44c;
extern int DAT_1001c548;
extern int DAT_1001c54c;
extern int DAT_1001c554;
extern int DAT_1001c568;
extern int DAT_1001c578;
extern int DAT_1001cc30;
extern int DAT_1001cd5c;
extern int DAT_1001cd68;
extern int DAT_1001cd80;
extern int DAT_1001cd98;
extern int DAT_1001cda8;
extern int DAT_1001e000;
extern int DAT_1001e208;
extern int DAT_1001e30c;
extern int DAT_1001e624;
extern int DAT_1001e728;
extern int DAT_1001e930;
extern int DAT_1001ea34;
extern int DAT_1001ec3c;
extern int DAT_1002131c;
extern int DAT_10021320;
extern int DAT_10021324;
extern int DAT_10021440;
extern int DAT_10021468;
extern int DAT_10021518;
extern int DAT_10021538;
extern int DAT_1002178a;
extern int DAT_10021990;
extern int DAT_10021a08;
extern int DAT_10021a0c;
extern int DAT_10021a10;
extern int DAT_10021a14;
extern int DAT_10021a18;
extern int DAT_10021a1c;
extern int DAT_10021ab0;
extern int DAT_10021ab4;
extern int DAT_10021ab8;
extern int DAT_10021ac0;
extern int DAT_10021ac4;
extern int DAT_10021ac8;
extern int DAT_10021acc;
extern int DAT_10021afc;
extern int DAT_10021b00;
extern int DAT_10021b34;
extern int DAT_10021b44;
extern int DAT_10021b50;
extern int DAT_10021b68;
extern int DAT_10021b80;
extern int DAT_10021b88;
extern int DAT_10021c80;
extern int DAT_10021de8;
extern int DAT_10021dec;
extern int DAT_10021e70;
extern int DAT_10021efc;
extern int DAT_10021f44;
extern int DAT_10021f50;
extern int DAT_10021f58;
extern int DAT_10021f5c;
extern int DAT_10021f64;
extern int DAT_100223e4;
extern int DAT_10023500;
extern int DAT_10023504;
extern int DAT_10023508;
extern int DAT_10023518;
extern int DAT_1002351c;
extern int DAT_10023520;
extern int DAT_10023528;
extern int DAT_10023530;
extern int DAT_10023534;
extern int DAT_10023538;
extern int DAT_1002353c;
extern int DAT_1002354c;
extern int DAT_10023554;
extern int DAT_10023558;
extern int DAT_100235c0;
extern int DAT_100236c4;
extern int DAT_100236c8;
extern int DAT_100236d0;
extern int DAT_100236d8;
extern int DAT_1002371c;
extern int DAT_1002371e;
extern int DAT_10023720;
extern int DAT_10023722;
extern int DAT_10023724;
extern int DAT_10023726;
extern int DAT_10023728;
extern int DAT_1002372a;
extern int DAT_1002372c;
extern int DAT_10023770;
extern int DAT_10023772;
extern int DAT_10023774;
extern int DAT_10023776;
extern int DAT_10023778;
extern int DAT_1002377a;
extern int DAT_1002377c;
extern int DAT_1002377e;
extern int DAT_10023780;
extern int DAT_10023784;
extern int DAT_10023788;
extern int DAT_1002378c;
extern int DAT_10023790;
extern int DAT_10023794;
extern int DAT_10023798;
extern int DAT_1002379c;
extern int DAT_100237a0;
extern int DAT_100237a4;
extern int DAT_100237a8;
extern int DAT_100237ac;
extern int DAT_100237b0;
extern int DAT_100237b4;
extern int DAT_100237bc;
extern int DAT_100237d4;
extern int DAT_100237d8;
extern int DAT_100237dc;
extern int DAT_100237e0;
extern int DAT_100237e4;
extern int DAT_100237e8;
extern int DAT_100237ec;
extern int DAT_10023804;
extern int DAT_10023808;
extern int DAT_1002380c;
extern int DAT_10023818;
extern int DAT_10023820;
extern int DAT_1002382a;
extern int DAT_1002382c;
extern int DAT_10023834;
extern int DAT_10023838;
extern int DAT_1002383c;
extern int DAT_10023840;
extern int DAT_10023844;
extern int DAT_10023848;
extern int DAT_10023850;
extern int DAT_10023854;
extern int DAT_1002385c;
extern int DAT_10023860;
extern int DAT_10023864;
extern int DAT_10023868;
extern int DAT_1002386c;
extern int DAT_10023870;
extern int DAT_10023880;
extern int DAT_10023884;
extern int DAT_10023894;
extern int DAT_10023910;
extern int DAT_10023914;
extern int DAT_10023918;
extern int DAT_1002391c;
extern int DAT_10023920;
extern int DAT_10023a20;
extern int DAT_10023b24;
extern int DAT_10023b28;
extern int DAT_10023b38;
extern int DAT_10023b3c;
extern int DAT_10023b40;
extern int DAT_10023b44;
extern int DAT_10023b4c;
extern int DAT_10024ea0;
extern int DAT_10024ec0;
extern int DAT_10024ec4;
extern int DAT_10025000;
extern int DAT_10025014;
extern int DAT_10025028;
extern int DAT_1002502c;
extern int DAT_10025030;
extern int _DAT_10021a20;
extern int _DAT_100234e8;
extern int _DAT_100234ec;
extern int _DAT_100234f0;
extern int _DAT_100234f4;
extern int _DAT_100234f8;
extern int _DAT_10023510;
extern int _DAT_10023544;
extern int _DAT_100236cc;
extern int _DAT_100237b0;
extern int _DAT_100237d0;
extern void *PTR_DAT_10021340;
extern void *PTR_DAT_10021344;
extern void *PTR_DAT_10021780;
extern void *PTR_DAT_10021784;
extern void *PTR_DAT_10021f08;
extern void *PTR_DAT_10021f14;
extern void *PTR_PTR_100226b8;
extern void *PTR___CxxFrameHandler_fail_abort_10021420;
extern void *PTR___exit_1002133c;
extern void *PTR___fptrap_10021424;
extern void *PTR___fptrap_10021428;
extern void *PTR___fptrap_1002142c;
extern void *PTR___fptrap_10021430;
extern void *PTR___fptrap_10021434;
extern void *PTR___fptrap_10021438;
extern void *PTR__cinit_10021330;
extern void *PTR_s_LC_COLLATE_10021f04;
extern void *PTR_s_November_10022750;
extern CRITICAL_SECTION lpCriticalSection_10021348;
extern CRITICAL_SECTION lpCriticalSection_1002134c;
extern CRITICAL_SECTION lpCriticalSection_1002136c;
extern CRITICAL_SECTION lpCriticalSection_1002137c;
extern CRITICAL_SECTION lpCriticalSection_1002138c;
extern int (*lpLocaleEnumProc_10013c56)(void);
extern int (*lpLocaleEnumProc_10013eb0)(void);
extern int (*lpLocaleEnumProc_10013fa4)(void);
extern int CodePage_100237cc;
extern int CodePage_10023898;
extern int GetLocaleInfoA_exref;
extern int HandlerRoutine_10011ceb;
extern int Locale_10023830;
extern int Locale_1002384c;
extern int _EH_except_handler3;
extern int __CxxFrameHandler_old;
extern int __cfltcvt;
extern int __fassign;
extern int _localeinfo_table;
extern int _strtod_scan;
extern int cbMultiByte_10021b40;
extern int dwTlsIndex_10021408;
extern int dwWindowsVersion;
extern void *hHeap;
extern int lpMem_10023b48;
extern int lpMultiByteStr_10021aa4;
extern int lpMultiByteStr_10021aa8;
extern int lpSrcStr_1001c560;
extern int lpSrcStr_1001c564;
extern int lpWideCharStr_100236dc;
extern int lpWideCharStr_10023730;
extern int type_info;
extern int uNumber_10024ffc;
extern int uStack_00000004;


/* Auto forward declarations */
void __fastcall Archive_Close(int *pArchiveObj);
void __fastcall DllRegisterServer(int gameMCPId,int gameToken,int serverToken);
void Server_FreeMemory(void);
void __CallSettingFrame_12(unsigned int param_1,unsigned int param_2,int param_3);
void __CxxFrameHandler_fail_abort(void);
void __cdecl __amsg_exit(int param_1);
longlong __ftol(void);
void __tzset(void);
void _alloca_probe(void);
unsigned int __cdecl _commit(uint param_1);
void __thiscall _controlfp_s_restore(void *_this,uint param_1,uint param_2);
void __cdecl
_dstShiftCalc(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
             int param_8,int param_9,int param_10,int param_11);
long double __cdecl _ftol2_sse(int param_1,int param_2);
unsigned int __cdecl _get_osfhandle(uint param_1);
int __cdecl _getmbcp(int param_1);
unsigned int __cdecl _getmbcurmax(int param_1);
BOOL __cdecl
_getstringtype(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
              int param_7);
void __cdecl _heap_free(uint *param_1,uint param_2);
BOOL _heap_init(void);
uint __cdecl _heap_lookup_size(int param_1);
void _init_time(void);
uint * __cdecl _install_locale(uint *param_1,uint *param_2,unsigned int *param_3,unsigned int *param_4);
void _invalid_parameter(void);
int __cdecl _isDST(int *param_1);
int __cdecl _isDST2(int *param_1);
void __cdecl _lock_fh(uint param_1);
void _mbcp_reset(void);
void __cdecl _set_ptd_field(DWORD param_1);
unsigned int __cdecl _setlocalloc(int param_1,uint *param_2);
void __cdecl _unlock_fh(uint param_1);


#endif /* D2SERVER_H */
