#ifndef D2SERVER_H
#define D2SERVER_H
#include <windows.h>

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
/* Note: bool is handled in the cleanup script since it conflicts with C++ bool */

/* Ghidra struct name fixes for mingw */
/* These are needed because Ghidra outputs tagRECT etc. without struct keyword */

/* Ghidra 'code' type - function pointer */
typedef int (*code_funcptr)(void);

/* SEH compatibility */
void *pExceptionList;

/* CONCAT macros */
#define CONCAT11(a,b) ((unsigned short)((unsigned char)(a) | ((unsigned short)(unsigned char)(b) << 8)))
#define CONCAT13(a,b) ((unsigned int)((unsigned char)(a) | ((unsigned int)(b) << 8)))
#define CONCAT22(a,b) ((unsigned int)((unsigned short)(a) | ((unsigned int)(unsigned short)(b) << 16)))
#define CONCAT31(a,b) ((unsigned int)((unsigned int)(a) | ((unsigned int)(unsigned char)(b) << 24)))
#define CONCAT41(a,b) ((unsigned long long)((unsigned int)(a) | ((unsigned long long)(unsigned char)(b) << 32)))

/* CRT intrinsics */
longlong __allmul(unsigned int a_lo, unsigned int a_hi, unsigned int b_lo, unsigned int b_hi);
unsigned int __cdecl __alldiv(unsigned int num_lo, unsigned int num_hi, unsigned int den_lo, unsigned int den_hi);

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

/* FOG.dll ordinals - named from D2MOO source + binary analysis
   Note: signatures match actual call patterns in D2Server 1.07 beta, 
   which may differ from D2MOO 1.10f signatures */
int __cdecl FOG_GetHostIPAddress(void);  /* #10013 */
int __cdecl FOG_InitErrorMgr(void);  /* #10019 */
int __cdecl FOG_SetExceptionFilter(void);  /* #10020 */
void __cdecl FOG_SetLogPrefix(char *a, char *b, int c);  /* #10021 */
void __cdecl FOG_GetSystemInfo(char *a, char *b, int c);  /* #10022 */
void __cdecl FOG_DisplayHalt(int a, char *b, char *c, int d);  /* #10024 */
void __cdecl FOG_DisplayError(char *msg, ...);  /* #10026 */
int __cdecl FOG_CrashDeadlockDetected(int a, int b, ...);  /* #10033 */
void __cdecl FOG_CrashDumpThread(int a, int b);  /* #10034 */
int __cdecl FOG_Log(void);  /* #10036 */
int __cdecl FOG_ReallocPool(void);  /* #10047 - called with 0 or 2 args */
int __cdecl FOG_Noop(void);  /* #10048 */
int __cdecl FOG_Send(void *a, void *b, int c, ...);  /* #10049 - Send data */
int __cdecl FOG_EnterCriticalSection(int a, void *b, int c);  /* #10050 */
int __cdecl FOG_LeaveCriticalSection(void *a, void *b, int c);  /* #10051 */
int __cdecl FOG_ExceptionHandler(int a);  /* #10052 */
int __cdecl FOG_Noop3(int a);  /* #10053 - called with 1 arg */
int __cdecl FOG_GetSyncTime(int a, int b);  /* #10055 */
int __cdecl FOG_GetDiskInfo(void);  /* #10056 */
int __cdecl FOG_InitTimers(int a);  /* #10058 */
int __cdecl FOG_SOCKET_MarkConnected(int a, int b);  /* #10075 */
int __cdecl FOG_SOCKET_InvokeCallback(void);  /* #10076 */
int __cdecl FOG_SOCKET_SetCallbacks(int a, int b, int c, int d);  /* #10077 */
int __cdecl FOG_SOCKET_SetDispatch(void);  /* #10078 */
int __cdecl FOG_SOCKET_AddRef(int a, int b);  /* #10079 */
void __cdecl FOG_GetSavePath(void);  /* #10113 */
void __cdecl FOG_CharToUpper(void);  /* #10139 */

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
int __cdecl SERVER_Initialize(int a, int b);  /* #10003 */
int __cdecl SERVER_Release(void);  /* #10004 */
int __cdecl D2NET_10018(int a);  /* #10018 - purpose unknown */
int __cdecl D2NET_10022(int mask);  /* #10022 - purpose unknown */
int __cdecl SERVER_SetHackListEnabled(int a);  /* #10023 */

/* D2COMMON.dll ordinals */
int __cdecl STATES_CheckStateMaskExp(void);  /* #10553 - called with 0 args in D2Server */
int __cdecl STATES_CheckStateMaskStayDeath(void *a, int b, int c);  /* #10554 */
int __cdecl D2COMMON_10980(void);  /* #10980 */
int __cdecl D2COMMON_10983(void);  /* #10983 */
int __cdecl D2COMMON_10984(void);  /* #10984 */

/* D2LANG.dll ordinals */
int __cdecl D2Lang_Initialize(void);  /* #10000 */
int __cdecl D2Lang_Uninitialize(void);  /* #10001 */

/* Forward declarations for functions called before definition.
   These signatures come from the actual decompiled definitions. */
uint * __fastcall Game_FindByGameId(uint dwGameId);
undefined4 __fastcall Token_AddOrUpdate(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);
undefined4 Server_EnumerateCharacters(void);
undefined4 __fastcall Server_SendFileData(char *szFileName, int pFileBuffer, int nFileSize);
int __thiscall GameData_DeletingDestructor2(void *this, byte param_1);
uint __thiscall GameData_PoolIndexToNode(void *this, int param_1);
int * __thiscall GameData_PoolGetBeginNode(void *this, int param_1);
int * __thiscall GameData_ListNode_Clear(void *this, byte param_1);
uint __thiscall GameData_PoolIndexToNode2(void *this, int param_1);
int __fastcall GameData_PoolAddOffset(int param_1, int param_2);
int * __fastcall MPQ_OpenWithRetry(undefined4 pArchiveInfo, LPCSTR szFileName, undefined4 nPriority, undefined4 nFlags, undefined *pRetryCallback);
LPSTR __thiscall Archive_FindFileEx(void *this, LPCSTR szFileName, undefined4 dwFlags, undefined4 dwTimeout);
undefined4 __fastcall Archive_SearchCdDrives(LPSTR szPath, LPCSTR szFileName, undefined4 dwFlags, undefined4 pFileHandle);

/* MSVC CRT */
int __cdecl _exit_wrapper(int code);
int __cdecl __exit(int code);
void __cdecl _cexit(void);
void __cdecl __crt_exit_process(int code);
void __cdecl initterm(void *a, void *b);
void __cdecl _initterm_table(void);
void __cdecl _lock_cs_d(int n);
void __cdecl _unlock_cs_d(int n);
int __cdecl _ftime64(void *t);
void __cdecl _alloca_probe(void);
int __cdecl _CRTDLL_INIT(int a, int b);
int __cdecl _cinit(int f);
int __cdecl _rand(void);
char * __cdecl _strrchr(const char *s, int c);
int __cdecl _stricmp(const char *a, const char *b);
void __cdecl _vsprintf_l(char *buf, byte *fmt, ...);
void __cdecl _vsnprintf(char *buf, int count, char *fmt, ...);
void __cdecl _except_handler3(void);
void __cdecl __global_unwind2(void *e);
void __cdecl __local_unwind2(void *f, int t);
void __cdecl __NLG_Notify1(int a, int b);
void __cdecl _EH_prolog3_catch(void *a);

/* Dialog/SEH callback functions */
int __stdcall LAB_10001307(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int __stdcall LAB_100010f0(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int __cdecl LAB_1001a4c5(void);
int __cdecl LAB_1001a581(void);
int __cdecl LAB_1001a5f5(void);
int __cdecl LAB_1001a62b(void);
int __cdecl LAB_1001a674(void);
int __cdecl LAB_100012a8(void);

/* ===================== GLOBAL VARIABLES ===================== */
int *ghD2DataMPQ;
int *ghD2CharMPQ;
int  ghGameServer;
int  g_hInstance;
int  g_hMainInstance;
int  bShutdownFlag;
int  bMcpConnected;
int  bServerRunning;
int  nCharServerSelector;
int  ghConsoleDlg;
int  ghCmdDialog;
int  nGameCount;
int  nPlayerCount;
int  g_pDllCallback;
int  crtInitCount;
int  dwLastTickCount;
int  dwLastKeepAliveTick;
int  stStartTime;
int  nActiveWorkerThreads;
int  gpBnclientInterface;
int  sPerfState;
int *sPerfLog;
void *sGraphState;
void *sGraphData;
void *pTokenListHead;
void *pGameListHead;
char sGameSearchName[256];
int  sGameDetailTable[64];
char gameInfoBuf[256];
int  sCharServerConns[32];
int  sCharServerConnsStatus;
char charName[32];
void *g_hGraphBrush;
int  g_lpOldGraphWndProc;
LARGE_INTEGER lpFrequency_10023180;
LARGE_INTEGER lpPerformanceCount_10023198;
LARGE_INTEGER lpPerformanceCount_10023168;
int  g_ClassFactoryVtable;
int  g_GameServerVtable1;
int  g_GameServerVtable2;
int  g_GameServerVtable3;
int  g_GameServerVtable4;
int  g_InitFuncTableStart;
int  g_InitFuncTableEnd;
int  g_GameEngineData1;
int  g_GameEngineData2;
int  g_NetEventCallback;
int  pInitTable;
int  pGameEngineFuncTable;
int  lpStartAddress_1000133e;
int  lpStartAddress_10001104;
int  lpStartAddress_1000113b;
int  PTR_Console_DisplayHelp_1001f158;
int  DAT_1001ee9c;
int  DAT_1001f058;
int  DAT_1002027c;
int  DAT_1002061c;
int  DAT_100207a8;
int  DAT_100207ac;
int  DAT_100207d0;
int  DAT_100207d4;
int  DAT_10020814;
int  DAT_10020818;
int  DAT_100208d0;
int  DAT_100208d4;
int  DAT_10021094;
int  DAT_1002313c;
int  DAT_10023160;
int  DAT_10023164;
int  DAT_10023184;
int  DAT_10023188;
int  DAT_1002318c;
int  DAT_10023190;
int  DAT_1002319c;
int  DAT_100231a4;
int  DAT_100231b8;
int  DAT_100231bc;
int  DAT_10023248;
int  DAT_10023254;
int  DAT_1002326c;
int  DAT_10023270;
int  DAT_100232b0;
int  DAT_100232b4;
int  DAT_100232b8;
int  _DAT_10023178;
int  _DAT_1002317c;
int  sMCPRecvRecord;
int  g_McpMessageHandlers;
int  g_GameServerCtorUnwind;

/* Stack variable stubs (Ghidra decompiler artifacts) */
unsigned int uStack00000000;
unsigned int uStack00000008;
unsigned int uStack00000009;
unsigned int uStack0000000f;
unsigned int uStack00000011;

/* String literals */
char s_d2data_mpq_1001ed60[];
char s_d2data_1001ed58[];
char s_d2char_mpq_1001ed48[];
char s_d2char_1001ed40[];
char s_delete_1001ed70[];
char s__SERVER__Connected_to_MCP_at__s_1001ed80[];
char s__SERVER__Hack_listing_IP__s_1001eddc[];
char s_Diablo_II_1001edc8[];
char s_Bnclient_dll_1001ee8c[];
char s_Cannot_load_Bnclient_dll__Error___1001ee60[];
char s_D2Multi_1001ee54[];
char s_QueryInterface_1001ee40[];
char s_Unable_to_QueryInterface_for_Bnc_1001ee00[];
char s___WORD___pbData____nLength_1001eec8[];
char s_C__D2_Source_D2Server_CORE_CharS_1001eee8[];
char s__CHARACTER_SERVER__Connecting_to_1001efc4[];
char s__CHARACTER_SERVER__Connected_to_C_1001ef5c[];
char s__CHARACTER_SERVER__Chose_Primary_1001ef18[];
char s__CHARACTER_SERVER__Lost_connecti_1001f024[];
char s_Game_Server_[];
char Char_Server___d_1001efa0[];
char s_Display_Console_Commands_1001f15c[];
char s_ERROR__Unknown_command___10020620[];
char s_GTM_RECREATE_shouldn_t_be_sent_f_10020b50[];
char s_C__D2_Source_D2Server_CORE_FromM_10020b90[];
char s_C__D2_Source_D2Server_CORE_Displ_1002082c[];
char s__d__02d__02d_100210e0[];
char s__d___Busy_100208f8[];
char s__d___d____d__100208c0[];
char s__d__d__d__d__d_10020d78[];
char s__3d____s___d__d__100208ac[];
char s_Game_Id___d_10020adc[];
char s_Seed___d_10020ad0[];
char s_Clients___d_10020ac0[];
char s_Players___d_10020ab0[];
char s_Monsters___d_10020aa0[];
char s_Objects___d_10020a90[];
char s_Items___d_10020a84[];
char s_Missiles___d_10020a74[];
char s_Unique_Items___d_10020a48[];
char s_NPCs___d_10020a3c[];
char s_Next_Player_Id___d_10020a24[];
char s_Next_Object_Id___d_10020a0c[];
char s_Next_Item_Id___d_100209f8[];
char s_Next_Missile_Id___d_100209e0[];
char s_Next_Warp_Id___d_100209cc[];
char s_Next_Monster_Id___d_10020a5c[];
char s_Path_Toward_Pct___d_100209b4[];
char s_Path_Clock_Pct___d_1002099c[];
char s_Path_Countr_Pct___d_10020984[];
char s_Path_FoWall_Pct___d_1002096c[];
char s_Path_Astar_Pct___d_10020954[];
char s_Path_Total_Call___d_1002093c[];
char s_Frames_h____d_1002092c[];
char s_Time__min____d_10020918[];
char s_Frame_Rate___d_10020904[];
char s_ptwGameIds_100208d8[];
char s_ptGameInfo_100208e8[];
char s_Busy_Games_Players_ActiveMonster_10020d04[];
char s_Error_creating_performance_logfi_10020d44[];
char s_Error_10020d70[];
char s_C__D2_Performace_txt_10020bd0[];
char s__SERVER__Finished_Loading____100211fc[];
char s_FATAL__Lost_connection_to_charac_100210f0[];
char s_Shutdown_Remotely_by_MCP_100211dc[];
char s_Invalid_size_of_record_in_SrvDat_10021098[];
char s___AUSGAMEDATA___10021000[];
char s___AV__TSHashObjectChunk_USGAMEDA_10021020[];
char s___AV__TSExplicitList_USGAMEDATA__10021238[];
char s__Server_[];
char MCP___GTM_CREATEGAME__M_10020dc8[];
char MCP___GTM_JOINGAME__MCP_10020e1c[];
char s_hFile_10021298[];
char s_C__D2_Source_D2Hell_SRC_Archive__10021274[];
char s_dwBytesToRead____dwBytes_100212a0[];
char s_hWnd_10020e50[];
char s_CONSOLE_COMMANDS_10020e60[];
char s__Server__GTM_CREATEGAME_10020dc8[];
char s__Server__GTM_JOINGAME_10020e1c[];
char s_Diablo___s_10020bc0[];
char s_ptToken_10020d8c[];
char s_C__D2_Source_D2Server_PlayerToke_10020d98[];
char s_wClass_0x3c_NUM_PLAYERCLASS_10020e78[];
char s_C__D2_Source_D2Server_CORE_ToMCP_10020e98[];
char s_C__D2_Source_D2Server_CORE_WinMa_10021064[];
char s_wNumPlayers_in_Game_u__10021170[];
char s__Server__Shutdown_Complete__100211b0[];
char s_0x3f4[];
char s_Stack_Size____u_bytes__10021370[];
char s_WORKER_THREAD_START__1002135c[];
char s_WORKER_THREAD_END__10021348[];
char s_WORKER_THREAD_ERROR__10021334[];
char s_WORKER_THREAD_10021328[];
char s_C__D2_Source_D2Server_CORE_WinM_100211e0[];
char s__Server__s__d__d__10020e3c[];
char s__Server__s__s__10021208[];
char s__Server__s__08x__100211e8[];
char s_GAME_THREAD_START_100211d0[];
char s_GAME_THREAD_END_100211c0[];
char s_WORKER__100211b8[];
char s_pParam____10021188[];
char s_WaitForSingleObject_ret___d_10021160[];
char s_dwWaitResult_0x_08x_10021140[];
char s_dwBytesAvail____d_10021120[];
char s_WORKER_s_dwBytesToRead____d_10021100[];
char s_WORKER_ERROR__ReadFile_failed_100210b8[];
char s_WORKER_ERROR__Unknown_packet__10021090[];
char s_WORKER_ERROR__packet_too_large_10021068[];
char s_WORKER_ERROR__malloc_failed_10021018[];
char s_WORKER_ERROR__recv_failed_10020ff0[];
char s_WORKER_ERROR__WSARecv_failed_10020fc8[];
char s_WORKER_ERROR__connect_failed_10020fa0[];
char s_WORKER_ERROR__socket_failed_10020f78[];
char s_WORKER_ERROR__WSAStartup_failed_10020f40[];
char s_WORKER_THREAD_ID__d_10020bd0[];
char s_WORKER_ERROR__CreateThread_failed_10020ba8[];
char s_WORKER_ERROR__CreateEvent_failed_10020b80[];
char s_WORKER_WAITING_FOR_SERVER__10020d98[];
char s_WORKER_WAITING_FOR_SERVER__d__10020d70[];
char s_WORKER_WAITING_FOR_SERVER__d___10020d48[];
char s_WORKER_ERROR__select_failed_10020c58[];
char s_WORKER_ERROR__WSASocket_failed_10020c30[];
char s_WORKER_ERROR__WSAStartup_failed_10020bf8[];
char s_dwTimeout_ms__d_10020e60[];
char s_dwTimeout_ms__d__10020e40[];
char s_dwTimeout_ms__d___10020e20[];
char s_dwTimeout_ms__d____10020e00[];
char s_dwTimeout_ms__d______10020de0[];
char s_dwTimeout_ms__d_________10020dc0[];
char s_WORKER__d_10020f28[];
char s_WORKER__s_d_10020f08[];
char s_WORKER__s_s_10020ee8[];
char s_WORKER__s_10020ed4[];
char s_WORKER_10020ec8[];
char s_C__D2_Source_D2Server_CORE_Worker_10020ea0[];
char s_dwWaitResult_0x_08x_0d_10020e80[];

#endif

/* ============================================== */
/* Auto-generated extern declarations from GCC errors */
/* ============================================== */

/* Data variables (.data/.bss segment) */
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

/* Pointer variables */
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

/* SEH labels */
void LAB_1000ac6c(void); /* label */
void LAB_1000c97e(void); /* label */
void LAB_1000c9cc(void); /* label */
void LAB_1000f844(void); /* label */

/* Critical sections */
extern CRITICAL_SECTION lpCriticalSection_10021348;
extern CRITICAL_SECTION lpCriticalSection_1002134c;
extern CRITICAL_SECTION lpCriticalSection_1002136c;
extern CRITICAL_SECTION lpCriticalSection_1002137c;
extern CRITICAL_SECTION lpCriticalSection_1002138c;

/* Callback function pointers */
extern int (CALLBACK *lpLocaleEnumProc_10013c56)(void);
extern int (CALLBACK *lpLocaleEnumProc_10013eb0)(void);
extern int (CALLBACK *lpLocaleEnumProc_10013fa4)(void);

/* Other extern declarations */
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
extern int hHeap;
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

/* Missing types from Ghidra */
typedef int int3;
