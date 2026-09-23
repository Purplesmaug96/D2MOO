/*
 * d2server_globals.cpp — Definitions for all extern globals and stub functions
 * referenced by the decompiled D2Server (1.07 beta).
 *
 * The header (d2server.h) declares hundreds of extern symbols, but the
 * decompiled source (d2server.cpp) never defines them — they were internal
 * DLL data at specific addresses in the original binary. This file provides
 * the actual storage and stub implementations.
 *
 * Functions here match the EXACT C++ mangled signatures the decompiled code
 * generates (from d2server.h declarations), even if the linked libraries
 * (Fog, Storm, etc.) export different signatures.
 */

#include "d2server.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>

/* ========================================================================
 * STRING LITERALS
 * ======================================================================== */
char s_d2char_1001ed40[] = "d2char";
char s_d2char_mpq_1001ed48[] = "d2char.mpq";
char s_d2data_1001ed58[] = "d2data";
char s_d2data_mpq_1001ed60[] = "d2data.mpq";
char s_delete_1001ed70[] = "delete";
char s__SERVER__Connected_to_MCP_at__s_1001ed80[] = "[SERVER] Connected to MCP at %s";
char s__SERVER__Hack_listing_IP__s_1001eddc[] = "[SERVER] Hack listing IP: %s";
char s_Diablo_II_1001edc8[] = "Diablo II";
char s_Bnclient_dll_1001ee8c[] = "Bnclient.dll";
char s_Cannot_load_Bnclient_dll__Error___1001ee60[] = "Cannot load Bnclient.dll - Error";
char s_D2Multi_1001ee54[] = "D2Multi";
char s_QueryInterface_1001ee40[] = "QueryInterface";
char s_Unable_to_QueryInterface_for_Bnc_1001ee00[] = "Unable to QueryInterface for Bncclient";
char s___WORD___pbData____nLength_1001eec8[] = " WORD: pbData, nLength";
char s_C__D2_Source_D2Server_CORE_CharS_1001eee8[] = "C:\\D2\\Source\\D2Server\\CORE\\CharServer";
char s__CHARACTER_SERVER__Connecting_to_1001efc4[] = "[CHARACTER SERVER] Connecting...";
char s__CHARACTER_SERVER__Connected_to_C_1001ef5c[] = "[CHARACTER SERVER] Connected.";
char s__CHARACTER_SERVER__Chose_Primary_1001ef18[] = "[CHARACTER SERVER] Chose Primary.";
char s__CHARACTER_SERVER__Lost_connecti_1001f024[] = "[CHARACTER SERVER] Lost connection!";
char Char_Server___d_1001efa0[] = "Char Server: %d";
char s_Display_Console_Commands_1001f15c[] = "Display Console Commands";
char s_ERROR__Unknown_command___10020620[] = "ERROR: Unknown command.";
char s_C__D2_Source_D2Server_CORE_Displ_1002082c[] = "C:\\D2\\Source\\D2Server\\CORE\\Display";
char s_C__D2_Source_D2Server_CORE_FromM_10020b90[] = "C:\\D2\\Source\\D2Server\\CORE\\FromMCP";
char s_C__D2_Source_D2Server_CORE_ToMCP_10020e98[] = "C:\\D2\\Source\\D2Server\\CORE\\ToMCP";
char s_C__D2_Source_D2Server_CORE_WinMa_10021064[] = "C:\\D2\\Source\\D2Server\\CORE\\WinMain";
char s__3d____s___d__d__100208ac[] = "  %d   %s   %d %d";
char s__d___d____d__100208c0[] = "%d | %d | %d";
char s_ptwGameIds_100208d8[] = "ptwGameIds";
char s_Game_Id___d_10020adc[] = "Game Id: %d";
char s_Seed___d_10020ad0[] = "Seed: %d";
char s__d___Busy_100208f8[] = "%d | Busy";
char s_ptGameInfo_100208e8[] = "ptGameInfo";
char s_Frame_Rate___d_10020904[] = "Frame Rate: %d";
char s_Time__min____d_10020918[] = "Time (min): %d";
char s_Frames_h____d_1002092c[] = "Frames/h: %d";
char s_Path_Total_Call___d_1002093c[] = "Path Total Call: %d";
char s_Path_Astar_Pct___d_10020954[] = "Path Astar Pct: %d";
char s_Path_FoWall_Pct___d_1002096c[] = "Path FoWall Pct: %d";
char s_Path_Countr_Pct___d_10020984[] = "Path Countr Pct: %d";
char s_Path_Clock_Pct___d_1002099c[] = "Path Clock Pct: %d";
char s_Path_Toward_Pct___d_100209b4[] = "Path Toward Pct: %d";
char s_Next_Monster_Id___d_10020a5c[] = "Next Monster Id: %d";
char s_Next_Warp_Id___d_100209cc[] = "Next Warp Id: %d";
char s_Next_Item_Id___d_100209f8[] = "Next Item Id: %d";
char s_Next_Missile_Id___d_100209e0[] = "Next Missile Id: %d";
char s_Next_Object_Id___d_10020a0c[] = "Next Object Id: %d";
char s_Next_Player_Id___d_10020a24[] = "Next Player Id: %d";
char s_NPCs___d_10020a3c[] = "NPCs: %d";
char s_Unique_Items___d_10020a48[] = "Unique Items: %d";
char s_Missiles___d_10020a74[] = "Missiles: %d";
char s_Items___d_10020a84[] = "Items: %d";
char s_Objects___d_10020a90[] = "Objects: %d";
char s_Monsters___d_10020aa0[] = "Monsters: %d";
char s_Players___d_10020ab0[] = "Players: %d";
char s_Clients___d_10020ac0[] = "Clients: %d";
char s_C__D2_Performace_txt_10020bd0[] = "C:\\D2\\Performace.txt";
char s_Diablo___s_10020bc0[] = "Diablo - %s";
char s_GTM_RECREATE_shouldn_t_be_sent_f_10020b50[] = "GTM_RECREATE shouldn't be sent from server!";
char s_Busy_Games_Players_ActiveMonster_10020d04[] = "Busy: Games Players ActiveMonsters";
char s_Error_creating_performance_logfi_10020d44[] = "Error creating performance log file";
char s_Error_10020d70[] = "Error";
char s__d__d__d__d__d_10020d78[] = "%d %d %d %d %d";
char s_ptToken_10020d8c[] = "ptToken";
char s_C__D2_Source_D2Server_PlayerToke_10020d98[] = "C:\\D2\\Source\\D2Server\\PlayerToken";
char s_wClass_0x3c_NUM_PLAYERCLASS_10020e78[] = "wClass < 0x3c NUM_PLAYERCLASS";
char MCP___GTM_CREATEGAME__M_10020dc8[] = "MCP: GTM_CREATEGAME";
char s__d__02d__02d_100210e0[] = "%d-%02d-%02d";
char s_FATAL__Lost_connection_to_charac_100210f0[] = "FATAL: Lost connection to character server!";
char s_Invalid_size_of_record_in_SrvDat_10021098[] = "Invalid size of record in SrvData";
char s___AUSGAMEDATA___10021000[] = " ??AUSGAMEDATA?? ";
char s___AV__TSHashObjectChunk_USGAMEDA_10021020[] = " ??AVTSHashObjectChunk<USGAMEDATA>?? ";
char s___AV__TSExplicitList_USGAMEDATA__10021238[] = " ??AVTSExplicitList<USGAMEDATA>?? ";
char s__SERVER__Finished_Loading____100211fc[] = "[SERVER] Finished Loading...";
char s_Shutdown_Remotely_by_MCP_100211dc[] = "Shutdown Remotely by MCP";
char s__Server__GTM_JOINGAME_10020e1c[] = " [Server] GTM_JOINGAME";
char s_C__D2_Source_D2Hell_SRC_Archive__10021274[] = "C:\\D2\\Source\\D2Hell\\SRC\\Archive";
char s_hFile_10021298[] = "hFile";
char s_dwBytesToRead____dwBytes_100212a0[] = "dwBytesToRead: %d";
char s__Server__s__d__d_10020e3c[] = " [Server] %s: %d %d";
char s__Server__s__s__10021208[] = " [Server] %s: %s";
char s__Server__s__08x__100211e8[] = " [Server] %s: %08x ";
char s__Server_[] = " [Server] ";
char s_Game_Server_[] = "Game Server";

/* Additional format/debug strings referenced by Ghidra names */
char s_WORKER_THREAD_START__1002135c[] = "WORKER THREAD START";
char s_WORKER_THREAD_END__10021348[] = "WORKER THREAD END";
char s_WORKER_THREAD_ERROR__10021334[] = "WORKER THREAD ERROR";
char s_WORKER_THREAD_10021328[] = "WORKER THREAD";
char s_GAME_THREAD_START_100211d0[] = "GAME THREAD START";
char s_GAME_THREAD_END_100211c0[] = "GAME THREAD END";
char s_WORKER__100211b8[] = "WORKER";
char s_pParam____10021188[] = "pParam: %p";
char s_wNumPlayers_in_Game_u__10021170[] = "wNumPlayers in Game: %u";
char s__Server__Shutdown_Complete__100211b0[] = "[Server] Shutdown Complete.";
char s_0x3f4[] = "0x3f4";
char s_Stack_Size____u_bytes__10021370[] = "Stack Size: %u bytes";
char s_C__D2_Source_D2Server_CORE_WinM_100211e0[] = "C:\\D2\\Source\\D2Server\\CORE\\WinMain";
char s_WaitForSingleObject_ret___d_10021160[] = "WaitForSingleObject ret: %d";
char s_dwWaitResult_0x_08x_10021140[] = "dwWaitResult: 0x%08x";
char s_dwBytesAvail____d_10021120[] = "dwBytesAvail: %d";
char s_WORKER_s_dwBytesToRead____d_10021100[] = "WORKER: dwBytesToRead: %d";
char s_WORKER_ERROR__ReadFile_failed_100210b8[] = "WORKER: ERROR: ReadFile failed";
char s_WORKER_ERROR__Unknown_packet__10021090[] = "WORKER: ERROR: Unknown packet";
char s_WORKER_ERROR__packet_too_large_10021068[] = "WORKER: ERROR: packet too large";
char s_WORKER_ERROR__malloc_failed_10021018[] = "WORKER: ERROR: malloc failed";
char s_WORKER_ERROR__recv_failed_10020ff0[] = "WORKER: ERROR: recv failed";
char s_WORKER_ERROR__WSARecv_failed_10020fc8[] = "WORKER: ERROR: WSARecv failed";
char s_WORKER_ERROR__connect_failed_10020fa0[] = "WORKER: ERROR: connect failed";
char s_WORKER_ERROR__socket_failed_10020f78[] = "WORKER: ERROR: socket failed";
char s_WORKER_ERROR__WSAStartup_failed_10020f40[] = "WORKER: ERROR: WSAStartup failed";
char s_WORKER_THREAD_ID__d_10020bd0[] = "WORKER THREAD ID: %d";
char s_WORKER_ERROR__CreateThread_failed_10020ba8[] = "WORKER: ERROR: CreateThread failed";
char s_WORKER_ERROR__CreateEvent_failed_10020b80[] = "WORKER: ERROR: CreateEvent failed";
char s_WORKER_WAITING_FOR_SERVER__10020d98[] = "WORKER: WAITING FOR SERVER...";
char s_WORKER_WAITING_FOR_SERVER__d__10020d70[] = "WORKER: WAITING FOR SERVER: %d...";
char s_WORKER_WAITING_FOR_SERVER__d___10020d48[] = "WORKER: WAITING FOR SERVER: %d";
char s_WORKER_ERROR__select_failed_10020c58[] = "WORKER: ERROR: select failed";
char s_WORKER_ERROR__WSASocket_failed_10020c30[] = "WORKER: ERROR: WSASocket failed";
char s_WORKER_ERROR__WSAStartup_failed_10020bf8[] = "WORKER: ERROR: WSAStartup failed";
char s_dwTimeout_ms__d_10020e60[] = "dwTimeout_ms: %d";
char s_dwTimeout_ms__d__10020e40[] = "dwTimeout_ms: %d ";
char s_dwTimeout_ms__d___10020e20[] = "dwTimeout_ms: %d  ";
char s_dwTimeout_ms__d____10020e00[] = "dwTimeout_ms: %d   ";
char s_dwTimeout_ms__d______10020de0[] = "dwTimeout_ms: %d     ";
char s_dwTimeout_ms__d_________10020dc0[] = "dwTimeout_ms: %d        ";
char s_WORKER__d_10020f28[] = "WORKER: %d";
char s_WORKER__s_d_10020f08[] = "WORKER: %s %d";
char s_WORKER__s_s_10020ee8[] = "WORKER: %s %s";
char s_WORKER__s_10020ed4[] = "WORKER: %s";
char s_WORKER_10020ec8[] = "WORKER";
char s_C__D2_Source_D2Server_CORE_Worker_10020ea0[] = "C:\\D2\\Source\\D2Server\\CORE\\Worker";
char s_dwWaitResult_0x_08x_0d_10020e80[] = "dwWaitResult: 0x%08x\r\n";


/* ========================================================================
 * GLOBAL VARIABLES — Server state
 * ======================================================================== */
void *pExceptionList = nullptr;
int bShutdownFlag = 0;
int bMcpConnected = 0;
int bServerRunning = 0;
int nCharServerSelector = 0;
int nGameCount = 0;
int nPlayerCount = 0;
int nActiveWorkerThreads = 0;
int crtInitCount = 0;
int dwLastTickCount = 0;
int dwLastKeepAliveTick = 0;
int stStartTime = 0;

/* ========================================================================
 * GLOBAL VARIABLES — Handles / instances
 * ======================================================================== */
int *ghD2DataMPQ = nullptr;
int *ghD2CharMPQ = nullptr;
void *ghGameServer = nullptr;
void *g_hInstance = nullptr;
void *g_hMainInstance = nullptr;
void *ghConsoleDlg = nullptr;
void *ghCmdDialog = nullptr;
void *g_pDllCallback = nullptr;
void *gpBnclientInterface = nullptr;
void *g_hGraphBrush = nullptr;
void *g_lpOldGraphWndProc = nullptr;
void *hHeap = nullptr;
int pGameEngineFuncTable = 0;

/* ========================================================================
 * GLOBAL VARIABLES — Vtables and function tables
 * ======================================================================== */
int g_ClassFactoryVtable = 0;
int g_GameServerVtable1 = 0;
int g_GameServerVtable2 = 0;
int g_GameServerVtable3 = 0;
int g_GameServerVtable4 = 0;
int g_GameServerCtorUnwind = 0;
int g_InitFuncTableStart = 0;
int g_InitFuncTableEnd = 0;
int g_GameEngineData1 = 0;
int g_GameEngineData2 = 0;
int g_NetEventCallback = 0;
int pInitTable = 0;
int g_McpMessageHandlers = 0;

/* Thread start addresses */
int lpStartAddress_1000133e = 0;
int lpStartAddress_10001104 = 0;
int lpStartAddress_1000113b = 0;

/* ========================================================================
 * GLOBAL VARIABLES — Display / Game state
 * ======================================================================== */
void *sGraphData = nullptr;
void *pTokenListHead = nullptr;
void *pGameListHead = nullptr;
int  sPerfState = 0;
void *sPerfLog = nullptr;
char sGameSearchName[256] = {};
int  sGameDetailTable[64] = {};
int  sCharServerConns[32] = {};
int  sCharServerConnsStatus = 0;

/* ========================================================================
 * GLOBAL VARIABLES — Performance / Timing
 * ======================================================================== */
LARGE_INTEGER lpFrequency_10023180 = {};
LARGE_INTEGER lpPerformanceCount_10023198 = {};
LARGE_INTEGER lpPerformanceCount_10023168 = {};

/* ========================================================================
 * GLOBAL VARIABLES — CRT / Locale
 * ======================================================================== */
int dwTlsIndex_10021408 = -1;
int CodePage_100237cc = 0;
int CodePage_10023898 = 0;
int cbMultiByte_10021b40 = 1;
int lpMem_10023b48 = 0;
int lpMultiByteStr_10021aa4 = 0;
int lpSrcStr_1001c560 = 0;
int lpSrcStr_1001c564 = 0;
int uNumber_10024ffc = 0;
int type_info = 0;
int _localeinfo_table = 0;
int __cfltcvt = 0;
int __fassign = 0;
int _strtod_scan = 0;
int GetLocaleInfoA_exref = 0;
int HandlerRoutine_10011ceb = 0;
int Locale_10023830 = 0;
int Locale_1002384c = 0;
int _EH_except_handler3 = 0;
int __CxxFrameHandler_old = 0;
int lpWideCharStr_100236dc = 0;
int lpWideCharStr_10023730 = 0;
int dwWindowsVersion = 0;
int lpMultiByteStr_10021aa8 = 0;

int (*lpLocaleEnumProc_10013c56)(void) = nullptr;
int (*lpLocaleEnumProc_10013eb0)(void) = nullptr;
int (*lpLocaleEnumProc_10013fa4)(void) = nullptr;

/* ========================================================================
 * GLOBAL VARIABLES — DAT_* (Ghidra data address labels)
 * ======================================================================== */
int DAT_1001c03c = 0;
int DAT_1001c05c = 0;
int DAT_1001c0d0 = 0;
int DAT_1001c0e0 = 0;
int DAT_1001c0f8 = 0;
int DAT_1001c108 = 0;
int DAT_1001c118 = 0;
int DAT_1001c130 = 0;
int DAT_1001c44c = 0;
int DAT_1001c548 = 0;
int DAT_1001c54c = 0;
int DAT_1001c554 = 0;
int DAT_1001c568 = 0;
int DAT_1001c578 = 0;
int DAT_1001cc30 = 0;
int DAT_1001cd5c = 0;
int DAT_1001cd68 = 0;
int DAT_1001cd80 = 0;
int DAT_1001cd98 = 0;
int DAT_1001cda8 = 0;
int DAT_1001e000 = 0;
int DAT_1001e208 = 0;
int DAT_1001e30c = 0;
int DAT_1001e624 = 0;
int DAT_1001e728 = 0;
int DAT_1001e930 = 0;
int DAT_1001ea34 = 0;
int DAT_1001ec3c = 0;
int DAT_1001ee9c = 0;
int DAT_1001f058 = 0;
int DAT_1002027c = 0;
int DAT_1002061c = 0;
int DAT_100207a8 = 0;
int DAT_100207ac = 0;
int DAT_100207d0 = 0;
int DAT_100207d4 = 0;
int DAT_10020814 = 0;
int DAT_10020818 = 0;
byte DAT_100208d0 = 0;
byte DAT_100208d4 = 0;
int DAT_10021094 = 0;
int DAT_1002131c = 0;
int DAT_10021320 = 0;
int DAT_10021324 = 0;
int DAT_10021440 = 0;
int DAT_10021468 = 0;
int DAT_10021518 = 0;
int DAT_10021538 = 0;
int DAT_1002178a = 0;
int DAT_10021990 = 0;
int DAT_10021a08 = 0;
int DAT_10021a0c = 0;
int DAT_10021a10 = 0;
int DAT_10021a14 = 0;
int DAT_10021a18 = 0;
int DAT_10021a1c = 0;
int DAT_10021ab0 = 0;
int DAT_10021ab4 = 0;
int DAT_10021ab8 = 0;
int DAT_10021ac0 = 0;
int DAT_10021ac4 = 0;
int DAT_10021ac8 = 0;
int DAT_10021acc = 0;
int DAT_10021afc = 0;
int DAT_10021b00 = 0;
int DAT_10021b34 = 0;
int DAT_10021b44 = 0;
int DAT_10021b50 = 0;
int DAT_10021b68 = 0;
int DAT_10021b80 = 0;
int DAT_10021b88 = 0;
int DAT_10021c80 = 0;
int DAT_10021de8 = 0;
int DAT_10021dec = 0;
int DAT_10021e70 = 0;
int DAT_10021efc = 0;
int DAT_10021f44 = 0;
int DAT_10021f50 = 0;
int DAT_10021f58 = 0;
int DAT_10021f5c = 0;
int DAT_10021f64 = 0;
int DAT_100223e4 = 0;
int DAT_1002313c = 0;
int DAT_10023160 = 0;
int DAT_10023164 = 0;
int DAT_10023184 = 0;
int DAT_10023188 = 0;
int DAT_1002318c = 0;
int DAT_10023190 = 0;
int DAT_1002319c = 0;
int DAT_100231a4 = 0;
int DAT_100231b8 = 0;
int DAT_100231bc = 0;
int _DAT_10023178 = 0;
int _DAT_1002317c = 0;
int DAT_10023248 = 0;
int DAT_10023254 = 0;
int DAT_1002326c = 0;
int DAT_10023270 = 0;
int DAT_100232b0 = 0;
int DAT_100232b4 = 0;
int DAT_100232b8 = 0;
int sMCPRecvRecord = 0;
int DAT_10023500 = 0;
int DAT_10023504 = 0;
int DAT_10023508 = 0;
int DAT_10023518 = 0;
int DAT_1002351c = 0;
int DAT_10023520 = 0;
int DAT_10023528 = 0;
int DAT_10023530 = 0;
int DAT_10023534 = 0;
int DAT_10023538 = 0;
int DAT_1002353c = 0;
int DAT_1002354c = 0;
int DAT_10023554 = 0;
int DAT_10023558 = 0;
int DAT_100235c0 = 0;
int DAT_100236c4 = 0;
int DAT_100236c8 = 0;
int DAT_100236d0 = 0;
int DAT_100236d8 = 0;
int DAT_1002371c = 0;
int DAT_1002371e = 0;
int DAT_10023720 = 0;
int DAT_10023722 = 0;
int DAT_10023724 = 0;
int DAT_10023726 = 0;
int DAT_10023728 = 0;
int DAT_1002372a = 0;
int DAT_1002372c = 0;
int DAT_10023770 = 0;
int DAT_10023772 = 0;
int DAT_10023774 = 0;
int DAT_10023776 = 0;
int DAT_10023778 = 0;
int DAT_1002377a = 0;
int DAT_1002377c = 0;
int DAT_1002377e = 0;
int DAT_10023780 = 0;
int DAT_10023784 = 0;
int DAT_10023788 = 0;
int DAT_1002378c = 0;
int DAT_10023790 = 0;
int DAT_10023794 = 0;
int DAT_10023798 = 0;
int DAT_1002379c = 0;
int DAT_100237a0 = 0;
int DAT_100237a4 = 0;
int DAT_100237a8 = 0;
int DAT_100237ac = 0;
int DAT_100237b0 = 0;
int DAT_100237b4 = 0;
int DAT_100237bc = 0;
int DAT_100237d4 = 0;
int DAT_100237d8 = 0;
int DAT_100237dc = 0;
int DAT_100237e0 = 0;
int DAT_100237e4 = 0;
int DAT_100237e8 = 0;
int DAT_100237ec = 0;
int DAT_10023804 = 0;
int DAT_10023808 = 0;
int DAT_1002380c = 0;
int DAT_10023818 = 0;
int DAT_10023820 = 0;
int DAT_1002382a = 0;
int DAT_1002382c = 0;
int DAT_10023834 = 0;
int DAT_10023838 = 0;
int DAT_1002383c = 0;
int DAT_10023840 = 0;
int DAT_10023844 = 0;
int DAT_10023848 = 0;
int DAT_10023850 = 0;
int DAT_10023854 = 0;
int DAT_1002385c = 0;
int DAT_10023860 = 0;
int DAT_10023864 = 0;
int DAT_10023868 = 0;
int DAT_1002386c = 0;
int DAT_10023870 = 0;
int DAT_10023880 = 0;
int DAT_10023884 = 0;
int DAT_10023894 = 0;
int DAT_10023910 = 0;
int DAT_10023914 = 0;
int DAT_10023918 = 0;
int DAT_1002391c = 0;
int DAT_10023920 = 0;
int DAT_10023a20 = 0;
int DAT_10023b24 = 0;
int DAT_10023b28 = 0;
int DAT_10023b38 = 0;
int DAT_10023b3c = 0;
int DAT_10023b40 = 0;
int DAT_10023b44 = 0;
int DAT_10023b4c = 0;
int DAT_10024ea0 = 0;
int DAT_10024ec0 = 0;
int DAT_10024ec4 = 0;
int DAT_10025000 = 0;
int DAT_10025014 = 0;
int DAT_10025028 = 0;
int DAT_1002502c = 0;
int DAT_10025030 = 0;
int _DAT_10021a20 = 0;
int _DAT_100234e8 = 0;
int _DAT_100234ec = 0;
int _DAT_100234f0 = 0;
int _DAT_100234f4 = 0;
int _DAT_100234f8 = 0;
int _DAT_10023510 = 0;
int _DAT_10023544 = 0;
int _DAT_100236cc = 0;
int _DAT_100237b0 = 0;
int _DAT_100237d0 = 0;

/* ========================================================================
 * GLOBAL VARIABLES — PTR_* (Pointer tables)
 * ======================================================================== */
void *PTR_DAT_10021340 = nullptr;
void *PTR_DAT_10021344 = nullptr;
void *PTR_DAT_10021780 = nullptr;
void *PTR_DAT_10021784 = nullptr;
void *PTR_DAT_10021f08 = nullptr;
void *PTR_DAT_10021f14 = nullptr;
void *PTR_PTR_100226b8 = nullptr;
void *PTR___CxxFrameHandler_fail_abort_10021420 = nullptr;
void *PTR___exit_1002133c = nullptr;
void *PTR___fptrap_10021424 = nullptr;
void *PTR___fptrap_10021428 = nullptr;
void *PTR___fptrap_1002142c = nullptr;
void *PTR___fptrap_10021430 = nullptr;
void *PTR___fptrap_10021434 = nullptr;
void *PTR___fptrap_10021438 = nullptr;
void *PTR__cinit_10021330 = nullptr;
void *PTR_s_LC_COLLATE_10021f04 = nullptr;
void *PTR_s_November_10022750 = nullptr;
int PTR_Console_DisplayHelp_1001f158 = 0;

/* ========================================================================
 * GLOBAL VARIABLES — Stack leak artifacts from Ghidra
 * ======================================================================== */
unsigned int uStack00000000 = 0;
unsigned int uStack00000008 = 0;
unsigned int uStack00000009 = 0;
unsigned int uStack0000000f = 0;
int uStack_00000004 = 0;

/* ========================================================================
 * STUB FUNCTIONS
 *
 * These match the EXACT C++ mangled signatures the decompiled code generates.
 * The decompiled code includes d2server.h which declares these functions, and
 * the compiler generates calls with those exact parameter types (including const).
 *
 * Many of these ARE defined in d2server.cpp with slightly different signatures
 * (non-const params). Those produce different mangled names. Here we provide
 * the const-qualified versions that the linker actually needs.
 *
 * We use __attribute__((weak)) where possible so these don't override real
 * definitions if they become available.
 * ======================================================================== */

/* --- CRT / Helper functions --- */
int _alpha_len(const char *s) { (void)s; return 0; }
long double _ftol2_sse(int a, int b) { (void)a; (void)b; return 0.0; }
void _heap_free(unsigned int *p, unsigned int sz) { (void)p; (void)sz; }
unsigned int _getmbcurmax(int p) { (void)p; return 1; }
unsigned int _setlocalloc(int p, uint *q) { (void)p; (void)q; return 0; }
int _exit_wrapper(int c) { return c; }
void __tzset() {}
unsigned int _commit(unsigned int fd) { (void)fd; return 0; }
int *_errno() { static int e = 0; return &e; }
longlong __ftol() { return 0; }
void _ld10pow(int *r, int e, int f) { (void)e; (void)f; if(r) *r=0; }
void _ldmul(int *r, int *o) { (void)o; if(r) *r=0; }
int _getlocaleinfo(int a, int b, int c, char *d) { (void)a;(void)b;(void)c;(void)d; return 0; }
void _fmt_locale_time(unsigned char *a, int b, int *c, unsigned int *d, int e) { (void)a;(void)b;(void)c;(void)d;(void)e; }
uint *_install_locale(uint *a, uint *b, unsigned int *c, unsigned int *d) { (void)a;(void)b;(void)c;(void)d; return nullptr; }
unsigned int _get_osfhandle(unsigned int fd) { (void)fd; return (unsigned int)-1; }
uint _heap_lookup_size(int p) { (void)p; return 0; }
void _lock_critical_section(int n) { (void)n; }
void _unlock_critical_section(int n) { (void)n; }
void __CxxFrameHandler_fail_abort() {}
void initterm(void *a, void *b) { (void)a; (void)b; }
int _CRTDLL_INIT(int a, int b) { (void)a; (void)b; return 0; }
void _vsnprintf(char *buf, unsigned char *fmt, ...) { if(buf) buf[0]='\0'; }
void _vsprintf_l(char *buf, unsigned char *fmt, ...) { if(buf) buf[0]='\0'; }
int _ftime64(void *t) { (void)t; return 0; }
void memmove2(void *d, const void *s, unsigned long n) { if(d&&s&&n) memmove(d,s,n); }
int __strncnt(const char *s, int n) { return s ? (int)strnlen(s,(size_t)n) : 0; }

/* --- String functions (const-qualified C++ signatures) --- */
int _strlen(const char *s) { return s ? (int)strlen(s) : 0; }
char *_strchr(const char *s, int c) { return s ? (char*)strchr(s,c) : 0; }
char *_strrchr(const char *s, int c) { return s ? (char*)strrchr(s,c) : 0; }
int _strncmp(const char *a, const char *b, size_t n) { return strncmp(a,b,n); }
size_t _strnlen(const char *s, size_t m) { return s ? strnlen(s,m) : 0; }
char *_strdup(const char *s) { return s ? strdup(s) : 0; }
int _strcmp(const char *a, const char *b) { return strcmp(a,b); }
int _stricmp(const char *a, const char *b) { return strcasecmp(a,b); }
int _strnicmp(const char *a, const char *b, size_t n) { return strncasecmp(a,b,n); }
int _strncpy(char *d, const char *s, size_t n) { if(d&&s) strncpy(d,s,n); return 0; }
void *_malloc(unsigned long sz) { return malloc(sz>0?sz:1); }
void *_memset(void *s, int c, size_t n) { return memset(s,c,n); }
int _fclose(int *s) { (void)s; return 0; }
int _add_carry(unsigned int a, unsigned int b, unsigned int *r) { if(r)*r=a+b; return (a+b)<a; }
unsigned int __alldiv(unsigned int nl, unsigned int nh, unsigned int dl, unsigned int dh) { return 0; }
longlong __allmul(unsigned int al, unsigned int ah, unsigned int bl, unsigned int bh) { return 0; }

/* --- Storm.dll imports --- */
void *SMemAlloc(int size, char *source, int flags, int fill) {
    (void)source; (void)flags; (void)fill;
    return malloc(size > 0 ? size : 1);
}
void SMemFree(void *ptr, char *source, int flags, int u) {
    (void)source; (void)flags; (void)u;
    if (ptr) free(ptr);
}
void *SMemReAlloc(void *ptr, int size, char *source, int flags, int u) {
    (void)source; (void)flags; (void)u;
    return realloc(ptr, size > 0 ? size : 1);
}
int SStrCopy(char *dest, char *src, int maxlen) {
    if (!dest || !src || maxlen <= 0) return 0;
    strncpy(dest, src, maxlen);
    dest[maxlen - 1] = '\0';
    return (int)strlen(dest);
}
int SStrCmp(char *s1, char *s2, int maxlen) {
    if (!s1 || !s2) return (s1 == s2) ? 0 : 1;
    return strncmp(s1, s2, maxlen > 0 ? (size_t)maxlen : strlen(s1) + 1);
}
int SStrPrintf(char *buf, int bufsize, char *fmt, ...) {
    if (!buf || bufsize <= 0) return 0;
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(buf, bufsize, fmt, args);
    va_end(args);
    return ret;
}
int SRegLoadString(char *key, char *subkey, int flags, char *buf, int bufsize) {
    (void)key; (void)subkey; (void)flags;
    if (buf && bufsize > 0) buf[0] = '\0';
    return 0;
}
int SRegSaveString(char *key, char *subkey, int flags, char *buf, int bufsize) {
    (void)key; (void)subkey; (void)flags; (void)buf; (void)bufsize;
    return 0;
}
int SFileGetFileName(int hFile, char *buf, int bufsize) {
    (void)hFile;
    if (buf && bufsize > 0) buf[0] = '\0';
    return 0;
}
int SStrNCat(char *dest, char *src, int maxlen) {
    if (!dest || !src || maxlen <= 0) return 0;
    size_t dl = strlen(dest);
    if ((int)dl >= maxlen) return 0;
    strncat(dest, src, maxlen - dl - 1);
    return (int)strlen(dest);
}
int SFileOpenArchive(char *path, int priority, int flags, int *phArchive) {
    (void)path; (void)priority; (void)flags;
    if (phArchive) *phArchive = 0;
    return 0;
}
int SFileCloseArchive(int hArchive) { (void)hArchive; return 0; }

/* --- FOG.dll imports --- */
int FOG_GetHostIPAddress() { return 0; }
int FOG_InitErrorMgr() { return 0; }
int FOG_SetExceptionFilter() { return 0; }
void FOG_SetLogPrefix(char *a, char *b, int c) { (void)a; (void)b; (void)c; }
void FOG_GetSystemInfo(char *a, char *b, int c) { (void)c; if(a) a[0]='\0'; if(b) b[0]='\0'; }
void FOG_DisplayHalt(int a, char *b, char *c, int d) { (void)a;(void)d; fprintf(stderr,"HALT: %s %s\n",b?b:"",c?c:""); }
void FOG_DisplayError(char *msg, ...) { (void)msg; }
int FOG_CrashDeadlockDetected(int a, int b, ...) { (void)a; (void)b; return 0; }
void FOG_CrashDumpThread(int a, int b) { (void)a; (void)b; }
int FOG_Log() { return 0; }
int FOG_ReallocPool() { return 0; }
int FOG_Noop() { return 0; }
int FOG_Send(void *a, void *b, int c, ...) { (void)a;(void)b;(void)c; return 0; }
int FOG_EnterCriticalSection(int a, void *b, int c) { (void)a;(void)b;(void)c; return 0; }
int FOG_LeaveCriticalSection(void *a, void *b, int c) { (void)a;(void)b;(void)c; return 0; }
int FOG_ExceptionHandler(int a) { (void)a; return 0; }
int FOG_Noop3(int a) { (void)a; return 0; }
int FOG_GetSyncTime(int a, int b) { (void)a; (void)b; return 0; }
int FOG_GetDiskInfo() { return 0; }
int FOG_InitTimers(int a) { (void)a; return 0; }
int FOG_SOCKET_MarkConnected(int a, int b) { (void)a; (void)b; return 0; }
int FOG_SOCKET_InvokeCallback() { return 0; }
int FOG_SOCKET_SetCallbacks(int a, int b, int c, int d) { (void)a;(void)b;(void)c;(void)d; return 0; }
int FOG_SOCKET_SetDispatch() { return 0; }
int FOG_SOCKET_AddRef(int a, int b) { (void)a; (void)b; return 0; }

/* --- D2NET.dll ordinals --- */
int D2NET_10018(int a) { (void)a; return 0; }
int D2NET_10022(int mask) { (void)mask; return 0; }
int SERVER_Initialize(int a, int b) { (void)a; (void)b; return 0; }
int SERVER_Release() { return 0; }
int SERVER_SetHackListEnabled(int a) { (void)a; return 0; }

/* --- D2GAME.dll ordinals --- */
int D2GAME_10002(void *a, void *b) { (void)a; (void)b; return 0; }
int D2GAME_10003() { return 0; }
int D2GAME_10006() { return 0; }
int D2GAME_10012() { return 0; }
int D2GAME_10014(void *a, void *b) { (void)a; (void)b; return 0; }
int D2GAME_10015(void *a, int b) { (void)a; (void)b; return 0; }
int D2GAME_10018(int a, int b, int c, int d, int e) { (void)a;(void)b;(void)c;(void)d;(void)e; return 0; }
int D2GAME_10019(int a, int b, int c) { (void)a;(void)b;(void)c; return 0; }
int D2GAME_10020(void *a) { (void)a; return 0; }
int D2GAME_10021(int a, int b, char *msg) { (void)a;(void)b;(void)msg; return 0; }
int D2GAME_10023(void *a) { (void)a; return 0; }
int D2GAME_10039() { return 0; }
int D2GAME_10040() { return 0; }
int D2GAME_10041() { return 0; }
int D2GAME_10043() { return 0; }
int D2GAME_10045() { return 0; }
int D2GAME_10046() { return 0; }
int D2GAME_10047(int a, int b, int c, int d, int e, int f, int g, int h) { (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h; return 0; }
int D2GAME_10048(int a, void *b, int c, int d, int e, int f) { (void)a;(void)b;(void)c;(void)d;(void)e;(void)f; return 0; }
int D2GAME_10049(int a, void *b, int c, int d, int e, int f) { (void)a;(void)b;(void)c;(void)d;(void)e;(void)f; return 0; }
int D2GAME_10050() { return 0; }

/* --- D2COMMON.dll ordinals --- */
int STATES_CheckStateMaskExp() { return 0; }
int STATES_CheckStateMaskStayDeath(void *a, int b, int c) { (void)a;(void)b;(void)c; return 0; }
int D2COMMON_10983() { return 0; }

/* --- D2Lang.dll ordinals --- */
int D2Lang_Initialize() { return 0; }
int D2Lang_Uninitialize() { return 0; }

/* --- DllRegisterServer --- */
void __fastcall DllRegisterServer(int a, int b, int c) { (void)a;(void)b;(void)c; }

/* --- LAB_* functions (SEH / dialog callbacks) --- */
void LAB_1001a5f5() {}
void LAB_1001a581() {}
void LAB_1001a4c5() {}
void LAB_1001a674() {}
void LAB_1001a62b() {}
void LAB_100012a8() {}
void LAB_1000ac6c() {}
void LAB_1000c97e() {}
void LAB_1000c9cc() {}
void LAB_1000f844() {}
LRESULT __stdcall LAB_100010f0(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { (void)hWnd;(void)uMsg;(void)wParam;(void)lParam; return 0; }
LRESULT __stdcall LAB_10001307(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { (void)hWnd;(void)uMsg;(void)wParam;(void)lParam; return 0; }

/* --- GameData helpers --- */
int * __thiscall GameData_ListNode_Clear(void *a, byte b) { (void)a; (void)b; return nullptr; }
int * __thiscall GameData_PoolGetBeginNode(void *a, int b) { (void)a; (void)b; return nullptr; }

/* Stub functions not in d2server.h — only those NOT defined in d2server.cpp */
void Game_AddToList(char *szGameName) { (void)szGameName; }
