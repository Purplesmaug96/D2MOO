#include "d2server.h"
#include <stddef.h>
#undef _doserrno

void PerfLog_WriteEntry(void)

{
  char cVar1;
  HANDLE hFile;
  uint uVar2;
  char *pcVar3;
  unsigned char uStack_105;
  DWORD DStack_104;
  char acStack_100 [256];
  
  _vsprintf_l(acStack_100,(byte *)s__d__d__d__d__d_10020d78);
  uStack_105 = 0xd;
  if (sPerfLog != (HANDLE)0x0) {
    hFile = CreateFileA(s_C__D2_Performace_txt_10020bd0,0x40000000,2,(LPSECURITY_ATTRIBUTES)0x0,4,
                        0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0x0) {
      MessageBoxA((HWND)0x0,s_Error_creating_performance_logfi_10020d44,s_Error_10020d70,0x10);
      sPerfLog = hFile;
      return;
    }
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    uVar2 = 0xffffffff;
    pcVar3 = acStack_100;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    WriteFile(hFile,acStack_100,~uVar2 - 1,&DStack_104,(LPOVERLAPPED)0x0);
    WriteFile(hFile,&uStack_105,1,&DStack_104,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return;
}



void __fastcall GameData_Destructor_ListBase(unsigned int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  void *pvStack_c;
  unsigned char *puStack_8;
  int iStack_4;
  
  puStack_8 = (unsigned char*)&LAB_1001a5f5;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = (uintptr_t)&g_GameServerVtable2;
  iStack_4 = 2;
  while (iVar5 = param_1[0x10], 0 < iVar5) {
    GameData_ChunkClearEntry(iVar5);
    SMemFree((void*)(iVar5),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (iVar5 = param_1[0xc], 0 < iVar5) {
    GameDataPool_RemoveAll(iVar5);
    SMemFree((void*)(iVar5),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  (*(unsigned short*)&(iStack_4)) = 3;
  piVar3 = param_1 + 0xf;
  while (0 < (intptr_t)param_1[0x10]) {
    GameData_ListNode_Detach4((int *)(param_1[0xe] + param_1[0x10]));
  }
  (*(unsigned short*)&(iStack_4)) = 1;
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode2(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = param_1[0x10];
    *piVar3 = 0;
    param_1[0x10] = 0;
  }
  (*(unsigned short*)&(iStack_4)) = 4;
  piVar3 = param_1 + 0xb;
  while (0 < (intptr_t)param_1[0xc]) {
    GameData_ListNode_Detach2((int *)(param_1[10] + param_1[0xc]));
  }
  iStack_4 = (uintptr_t)(*((unsigned int*)&(iStack_4)+1)) << 8;
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = param_1[0xc];
    *piVar3 = 0;
    param_1[0xc] = 0;
  }
  *param_1 = (uintptr_t)&g_GameServerVtable1;
  param_1[4] = 0;
  iStack_4 = 6;
  GameDataPool_DetachAll3((int*)param_1 + 1);
  uVar4 = 0;
  if (param_1[6] != 0) {
    iVar5 = 0;
    do {
      while( true ) {
        iVar1 = *(int *)(param_1[7] + iVar5 + 8);
        if (iVar1 < 1) break;
        piVar3 = GameData_PoolGetBeginNode((void *)(param_1[7] + iVar5),iVar1);
        GameData_ListNode_Detach2(piVar3);
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0xc;
    } while (uVar4 < (uintptr_t)param_1[6]);
  }
  iStack_4 = CONCAT31((*((unsigned int*)&(iStack_4)+1)),5);
  GameDataPool_FreeList((intptr_t)(param_1 + 5));
  iStack_4 = 7;
  GameDataPool_DetachAll3((int*)param_1 + 1);
  iStack_4 = 0xffffffff;
  GameData_ListNode_Detach2((int*)param_1 + 2);
  pExceptionList = pvStack_c;
  return;
}
#if 0 /* CRT: DllGetClassObject */



#if 0
void * DllGetClassObject(void)

{
                    // 0x1019  10003  QueryInterface
  return &g_ClassFactoryVtable;
}
#endif /* DllGetClassObject */

#endif




void __fastcall GameData_RemoveAllEntries(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  piVar1 = (int *)(param_1 + 0xc);
  iVar2 = *piVar1;
  if (iVar2 != 0) {
    uVar3 = *(uint *)(param_1 + 0x10);
    if ((intptr_t)uVar3 < 0) {
      piVar4 = (int *)~uVar3;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar3 - *(int *)(iVar2 + 4)));
    }
    *piVar4 = iVar2;
    *(unsigned int *)(*piVar1 + 4) = *(unsigned int *)(param_1 + 0x10);
    *piVar1 = 0;
    *(unsigned int *)(param_1 + 0x10) = 0;
  }
  iVar2 = *(int *)(param_1 + 4);
  piVar1 = (int *)(param_1 + 4);
  if (iVar2 != 0) {
    uVar3 = *(uint *)(param_1 + 8);
    if ((intptr_t)uVar3 < 0) {
      piVar4 = (int *)~uVar3;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar3 - *(int *)(iVar2 + 4)));
    }
    *piVar4 = iVar2;
    *(unsigned int *)(*piVar1 + 4) = *(unsigned int *)(param_1 + 8);
    *piVar1 = 0;
    *(unsigned int *)(param_1 + 8) = 0;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void Perf_InitSystem(void)

{
  BOOL BVar1;
  
  BVar1 = QueryPerformanceFrequency((LARGE_INTEGER *)&lpFrequency_10023180);
  if (BVar1 != 0) {
    DAT_10023190 = 1;
    _DAT_10023178 = 0;
    _DAT_1002317c = 0;
    QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount_10023168);
    return;
  }
  DAT_10023190 = 0;
  return;
}



void __fastcall Perf_InitFrameTimer(uint dwTargetFPS)

{
  unsigned long long uVar1;
  LARGE_INTEGER LStack_10;
  LARGE_INTEGER LStack_8;
  
  QueryPerformanceFrequency(&LStack_10);
  uVar1 = __alldiv(LStack_10.u.LowPart,LStack_10.u.HighPart,dwTargetFPS,(intptr_t)dwTargetFPS >> 0x1f);
  DAT_10023164 = (intptr_t)((ulonglong)uVar1 >> 0x20);
  DAT_10023160 = (uintptr_t)uVar1;
  QueryPerformanceCounter(&LStack_8);
  DAT_10023188 = DAT_10023160 + LStack_8.u.LowPart;
  DAT_1002318c = DAT_10023164 + LStack_8.u.HighPart + (uintptr_t)CARRY4(DAT_10023160,LStack_8.u.LowPart);
  return;
}



void __fastcall GameData_PoolInit3(int pPool)

{
  uint uVar1;
  
  uVar1 = pPool + 4;
  *(uint *)uVar1 = uVar1;
  *(uint *)(pPool + 8) = ~uVar1;
  return;
}



int __fastcall GameData_PoolAddOffset(int param_1,int param_2)

{
  return param_1 + param_2;
}



void __fastcall MCP_SendType1(undefined3 param_1)

{
  FOG_Send(ghGameServer,&uStack00000000,1,CONCAT13(1,param_1));
  return;
}



#if 0
int * __thiscall GameData_PoolGetBeginNode(void *_this,int param_1)

{
  if (param_1 != 0) {
    return (int *)(*(int *)_this + param_1);
  }
  return (int *)((intptr_t)_this + 4);
}
#endif /* GameData_PoolGetBeginNode */




void __fastcall GameData_PoolInit(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = (uintptr_t)puVar1;
  *param_1 = 0xdddddddd;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}



unsigned int Console_GetMainDialogHandle(void)

{
  return (uintptr_t)ghConsoleDlg;
}



void __thiscall GameData_AllocGameEntry(void *_this,unsigned int param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int unaff_ESI;
  int *piVar4;
  int iVar5;
  
  iVar2 = (intptr_t)SMemAlloc(param_2 + 0x3060,s___AUSGAMEDATA___10021000,0xfffffffe,param_3 | 8);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    *(unsigned int *)(iVar2 + 4) = 0;
    *(unsigned int *)(iVar2 + 8) = 0;
    *(unsigned int *)(iVar2 + 0xc) = 0;
    *(unsigned int *)(iVar2 + 0x10) = 0;
  }
  if (unaff_ESI != 0) {
    if (iVar2 == 0) {
      piVar3 = (int *)((intptr_t)_this + 4);
    }
    else {
      piVar3 = (int *)(*(int *)_this + iVar2);
    }
    iVar5 = *piVar3;
    if (iVar5 != 0) {
      uVar1 = piVar3[1];
      if ((intptr_t)uVar1 < 0) {
        piVar4 = (int *)~uVar1;
      }
      else {
        piVar4 = (int *)((intptr_t)piVar3 + (uVar1 - *(int *)(iVar5 + 4)));
      }
      *piVar4 = iVar5;
      *(int *)(*piVar3 + 4) = piVar3[1];
      *piVar3 = 0;
      piVar3[1] = 0;
    }
    piVar4 = (int *)((intptr_t)_this + 4);
    if (unaff_ESI != 1) {
      iVar5 = *piVar4;
      *piVar3 = iVar5;
      piVar3[1] = *(int *)(iVar5 + 4);
      *(int *)(iVar5 + 4) = iVar2;
      *piVar4 = (intptr_t)piVar3;
      return;
    }
    *piVar3 = (intptr_t)piVar4;
    piVar3[1] = *(int *)((intptr_t)_this + 8);
    uVar1 = *(uint *)((intptr_t)_this + 8);
    iVar5 = *(int *)_this;
    if ((intptr_t)uVar1 < 0) {
      *(int **)~uVar1 = piVar3;
      *(int *)((intptr_t)_this + 8) = iVar2;
      return;
    }
    if (iVar5 < 0) {
      iVar5 = (intptr_t)piVar4 - *(int *)(*piVar4 + 4);
    }
    *(int **)(uVar1 + iVar5) = piVar3;
    *(int *)((intptr_t)_this + 8) = iVar2;
  }
  return;
}



void Server_SendPlayerLeave(void)

{
  unsigned char auStack_8 [8];
  
  auStack_8[0] = 9;
  FOG_Send(ghGameServer,auStack_8,5);
  return;
}



int __fastcall Console_ShowCmdDialog(HWND hParentWnd)

{
  HINSTANCE hInstance;
  
  hInstance = (HINSTANCE)GetWindowLongA(hParentWnd,-6);
  if (ghCmdDialog != (HWND)0x0) {
    return false;
  }
  ghCmdDialog = CreateDialogParamA(hInstance,(LPCSTR)0x68,hParentWnd,(DLGPROC)&LAB_10001307,0);
  return ghCmdDialog != (HWND)0x0;
}



void __fastcall GameData_Destructor_HashBase(unsigned int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  void *pvStack_c;
  unsigned char *puStack_8;
  uint uStack_4;
  
  puStack_8 = (unsigned char*)&LAB_1001a581;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = (uintptr_t)&g_GameServerVtable1;
  uStack_4 = 1;
  param_1[4] = 0;
  while( true ) {
    if ((intptr_t)param_1[3] < 1) break;
    piVar3 = GameData_PoolGetBeginNode(param_1 + 1,param_1[3]);
    GameData_ListNode_Detach2(piVar3);
  }
  uVar6 = 0;
  if (param_1[6] != 0) {
    iVar7 = 0;
    do {
      while( true ) {
        iVar1 = *(int *)(param_1[7] + 8 + iVar7);
        if (iVar1 < 1) break;
        piVar3 = (int *)(*(int *)(param_1[7] + iVar7) + iVar1);
        if (*piVar3 != 0) {
          uVar2 = piVar3[1];
          if ((intptr_t)uVar2 < 0) {
            piVar5 = (int *)~uVar2;
          }
          else {
            piVar5 = (int *)((intptr_t)piVar3 + (uVar2 - *(int *)(*piVar3 + 4)));
          }
          *piVar5 = *piVar3;
          *(int *)(*piVar3 + 4) = piVar3[1];
          *piVar3 = 0;
          piVar3[1] = 0;
        }
      }
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 0xc;
    } while (uVar6 < (uintptr_t)param_1[6]);
  }
  uVar6 = 0;
  uStack_4 = uStack_4 & 0xffffff00;
  if (param_1[6] != 0) {
    iVar7 = 0;
    do {
      GameDataPool_DetachList((int *)(param_1[7] + iVar7));
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 0xc;
    } while (uVar6 < (uintptr_t)param_1[6]);
  }
  if (param_1[7] != 0) {
    SMemFree((void*)param_1[7],s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  uStack_4 = 2;
  piVar3 = param_1 + 2;
  while (0 < (intptr_t)param_1[3]) {
    piVar5 = (int *)(param_1[1] + param_1[3]);
    if (*piVar5 != 0) {
      piVar4 = (int *)GameData_PoolIndexToNode(piVar5,-1);
      *piVar4 = *piVar5;
      *(int *)(*piVar5 + 4) = piVar5[1];
      *piVar5 = 0;
      piVar5[1] = 0;
    }
  }
  iVar7 = *piVar3;
  if (iVar7 != 0) {
    uVar6 = param_1[3];
    if ((intptr_t)uVar6 < 0) {
      piVar5 = (int *)~uVar6;
    }
    else {
      piVar5 = (int *)((intptr_t)piVar3 + (uVar6 - *(int *)(iVar7 + 4)));
    }
    *piVar5 = iVar7;
    *(unsigned int *)(*piVar3 + 4) = param_1[3];
    *piVar3 = 0;
    param_1[3] = 0;
  }
  pExceptionList = pvStack_c;
  return;
}



void Server_SendVersionHandshake(void)

{
  unsigned char uStack_14;
  unsigned int uStack_13;
  unsigned int uStack_f;
  unsigned int uStack_b;
  unsigned int uStack_7;
  
  uStack_14 = 2;
  uStack_13 = 0x49583836;
  uStack_f = 0x44324456;
  uStack_b = 200;
  uStack_7 = 0;
  FOG_Send(ghGameServer,&uStack_14,0x11);
  return;
}



void __fastcall GameServer_Destructor(unsigned int *pServerObj)

{
  void *_this;
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  void *pvStack_c;
  unsigned char *puStack_8;
  int iStack_4;
  
  iStack_4 = 0xffffffff;
  puStack_8 = (unsigned char*)&LAB_1001a4c5;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  DeleteCriticalSection((LPCRITICAL_SECTION)(pServerObj + 0x14));
  *pServerObj = (uintptr_t)&g_GameServerVtable2;
  iStack_4 = 2;
  while (iVar5 = pServerObj[0x10], 0 < iVar5) {
    GameData_ChunkClearEntry(iVar5);
    SMemFree((void*)(iVar5),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (_this = (void *)pServerObj[0xc], 0 < (intptr_t)_this) {
    GameData_DeletingDestructor2(_this,0);
    SMemFree((void*)(_this),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  (*(unsigned short*)&(iStack_4)) = 3;
  piVar3 = pServerObj + 0xf;
  while (0 < (intptr_t)pServerObj[0x10]) {
    GameData_ListNode_Detach4((int *)(pServerObj[0xe] + pServerObj[0x10]));
  }
  (*(unsigned short*)&(iStack_4)) = 1;
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode2(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = pServerObj[0x10];
    *piVar3 = 0;
    pServerObj[0x10] = 0;
  }
  (*(unsigned short*)&(iStack_4)) = 4;
  piVar3 = pServerObj + 0xb;
  while (0 < (intptr_t)pServerObj[0xc]) {
    GameData_ListNode_Detach2((int *)(pServerObj[10] + pServerObj[0xc]));
  }
  iStack_4 = (uintptr_t)(*((unsigned int*)&(iStack_4)+1)) << 8;
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = pServerObj[0xc];
    *piVar3 = 0;
    pServerObj[0xc] = 0;
  }
  *pServerObj = (uintptr_t)&g_GameServerVtable1;
  pServerObj[4] = 0;
  iStack_4 = 6;
  GameDataPool_DetachAll3((int*)pServerObj + 1);
  uVar4 = 0;
  if (pServerObj[6] != 0) {
    iVar5 = 0;
    do {
      while( true ) {
        iVar1 = *(int *)(pServerObj[7] + iVar5 + 8);
        if (iVar1 < 1) break;
        piVar3 = GameData_PoolGetBeginNode((void *)(pServerObj[7] + iVar5),iVar1);
        GameData_ListNode_Detach2(piVar3);
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0xc;
    } while (uVar4 < (uintptr_t)pServerObj[6]);
  }
  iStack_4 = CONCAT31((*((unsigned int*)&(iStack_4)+1)),5);
  GameDataPool_FreeList((intptr_t)(pServerObj + 5));
  iStack_4 = 7;
  GameDataPool_DetachAll3((int*)pServerObj + 1);
  iStack_4 = 0xffffffff;
  GameData_ListNode_Detach2((int*)pServerObj + 2);
  pExceptionList = pvStack_c;
  return;
}



unsigned int Bnclient_LoadRunGame(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  CHAR aCStack_64 [100];
  
  if (gpBnclientInterface != 0) {
    return 0;
  }
  hModule = LoadLibraryA(s_Bnclient_dll_1001ee8c);
  if (hModule == (HMODULE)0x0) {
    GetLastError();
    _vsprintf_l(aCStack_64,(byte *)s_Cannot_load_Bnclient_dll__Error___1001ee60);
    MessageBoxA((HWND)0x0,aCStack_64,s_D2Multi_1001ee54,0x10);
    return 0;
  }
  pFVar1 = GetProcAddress(hModule,s_QueryInterface_1001ee40);
  if (pFVar1 == (FARPROC)0x0) {
    GetLastError();
    _vsprintf_l(aCStack_64,(byte *)s_Unable_to_QueryInterface_for_Bnc_1001ee00);
    MessageBoxA((HWND)0x0,aCStack_64,s_D2Multi_1001ee54,0x10);
    return 0;
  }
  gpBnclientInterface = (*pFVar1)();
  return 1;
}



void __fastcall List_FreeNode(unsigned int *pNode)

{
  unsigned int *puVar1;
  
  if (pNode != (unsigned int *)0x0) {
    puVar1 = pNode + 1;
    *puVar1 = 0;
    pNode[2] = 0;
    *puVar1 = (uintptr_t)puVar1;
    *pNode = 0xdddddddd;
    pNode[2] = ~(uintptr_t)puVar1;
  }
  return;
}



void Server_SendGameList(void)

{
  unsigned char uStack_10c;
  unsigned int uStack_10b;
  unsigned int uStack_107;
  unsigned char uStack_103;
  
  uStack_10b = 0;
  uStack_107 = 0;
  uStack_103 = 0;
  uStack_10c = 3;
  FOG_Send(ghGameServer,&uStack_10c,0x109);
  return;
}



unsigned int Console_GetCmdDialogHandle(void)

{
  return (uintptr_t)ghCmdDialog;
}



void __fastcall Console_GraphSetFrameRate(LPARAM param_1)

{
  if (ghConsoleDlg != nullptr) {
    SendDlgItemMessageA(ghConsoleDlg,0x3f0,0xc,0,param_1);
  }
  return;
}



void __fastcall GameData_ChunkClearEntry(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = *(int *)(param_1 + 0x10);
  piVar5 = (int *)(param_1 + 0x10);
  if (iVar2 != 0) {
    uVar3 = *(uint *)(param_1 + 0x14);
    if ((intptr_t)uVar3 < 0) {
      piVar1 = (int *)~uVar3;
    }
    else {
      piVar1 = (int *)((intptr_t)piVar5 + (uVar3 - *(int *)(iVar2 + 4)));
    }
    *piVar1 = iVar2;
    *(unsigned int *)(*piVar5 + 4) = *(unsigned int *)(param_1 + 0x14);
    *piVar5 = 0;
    *(unsigned int *)(param_1 + 0x14) = 0;
  }
  uVar3 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    iVar2 = 0;
    do {
      iVar4 = *(int *)(param_1 + 8) + iVar2;
      GameData_ListNode_Detach2((int *)(iVar4 + 0xc));
      piVar5 = (int *)(iVar4 + 4);
      if (*(int *)(iVar4 + 4) != 0) {
        piVar1 = (int *)GameData_PoolIndexToNode(piVar5,-1);
        *piVar1 = *piVar5;
        *(unsigned int *)(*piVar5 + 4) = *(unsigned int *)(iVar4 + 8);
        *piVar5 = 0;
        *(unsigned int *)(iVar4 + 8) = 0;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x3060;
    } while (uVar3 < *(uint *)(param_1 + 4));
  }
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  return;
}



void __fastcall List_InitNode(int pNode)

{
  uint uVar1;
  
  uVar1 = pNode + 4;
  *(uint *)uVar1 = uVar1;
  *(uint *)(pNode + 8) = ~uVar1;
  return;
}



void __fastcall Server_SendGameMsg(undefined3 wMsgData)

{
  FOG_Send(ghGameServer,&uStack00000000,1,CONCAT13(0xb,wMsgData));
  return;
}



unsigned int Server_SetHInstance(unsigned int param_1)

{
  g_hInstance = (void*)(uintptr_t)param_1;
  return 1;
}



unsigned int CharServer_PollAndDispatch(void)

{
  short sVar1;
  int *piVar2;
  byte unaff_retaddr;
  
  _alloca_probe();
  piVar2 = (int*)&sCharServerConns;
  do {
    if (*piVar2 != 0) {
      sVar1 = FOG_LeaveCriticalSection(*piVar2,&uStack00000000,0x1020);
      if ((((sVar1 != 0) && (sVar1 != 0)) && (unaff_retaddr < 9)) &&
         (*(void **)(&DAT_1001ee9c + (uintptr_t)unaff_retaddr * 4) != (void *)0x0)) {
        ((int (*)())(*(void **)(&DAT_1001ee9c + (uintptr_t)unaff_retaddr * 4)))();
      }
    }
    piVar2 = piVar2 + 0xb;
  } while ((intptr_t)piVar2 < 0x1002313c);
  return 1;
}



void __fastcall List_MoveNode(unsigned int *pNode,unsigned int *pDestHead)

{
  unsigned int *puVar1;
  unsigned int uVar2;
  
  if (pNode != (unsigned int *)0x0) {
    puVar1 = pNode + 1;
    *puVar1 = 0;
    pNode[2] = 0;
    uVar2 = *pDestHead;
    *puVar1 = (uintptr_t)puVar1;
    *pNode = uVar2;
    pNode[2] = ~(uintptr_t)puVar1;
  }
  return;
}



void __fastcall GameDataPool_ClearEntry(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  piVar1 = param_1 + 1;
  while (0 < param_1[2]) {
    piVar4 = (int *)(*param_1 + param_1[2]);
    if (*piVar4 != 0) {
      uVar2 = piVar4[1];
      if ((intptr_t)uVar2 < 0) {
        piVar5 = (int *)~uVar2;
      }
      else {
        piVar5 = (int *)((intptr_t)piVar4 + (uVar2 - *(int *)(*piVar4 + 4)));
      }
      *piVar5 = *piVar4;
      *(int *)(*piVar4 + 4) = piVar4[1];
      *piVar4 = 0;
      piVar4[1] = 0;
    }
  }
  iVar3 = *piVar1;
  if (iVar3 != 0) {
    uVar2 = param_1[2];
    if ((intptr_t)uVar2 < 0) {
      piVar4 = (int *)~uVar2;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar2 - *(int *)(iVar3 + 4)));
    }
    *piVar4 = iVar3;
    *(int *)(*piVar1 + 4) = param_1[2];
    *piVar1 = 0;
    param_1[2] = 0;
  }
  return;
}
#if 0 /* CRT: DllCanUnloadNow */



#if 0
void DllCanUnloadNow(void)

{
                    // 0x10dc  10002  
  return;
}
#endif /* DllCanUnloadNow */

#endif




int Game_FindByName(void)

{
  byte bVar1;
  int iVar2;
  WPARAM wParam;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  int bVar6;
  byte abStack_10 [16];
  
  wParam = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x188,0,0);
  if (wParam != 0xffffffff) {
    SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,wParam,(LPARAM)abStack_10);
    pbVar5 = abStack_10;
    pbVar3 = (byte*)&sGameSearchName;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_100039e5:
        iVar4 = (1 - (uintptr_t)bVar6) - (uintptr_t)(bVar6 != 0);
        goto LAB_100039ea;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_100039e5;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_100039ea:
    iVar2 = (intptr_t)pGameListHead;
    if (iVar4 != 0) {
      SStrCopy(sGameSearchName,abStack_10,0x7fffffff);
      DAT_100231b8 = 1;
      iVar2 = (intptr_t)pGameListHead;
    }
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x94)) {
      pbVar3 = abStack_10;
      pbVar5 = (byte *)(iVar2 + 100);
      do {
        bVar1 = *pbVar5;
        bVar6 = bVar1 < *pbVar3;
        if (bVar1 != *pbVar3) {
LAB_10003a45:
          iVar4 = (1 - (uintptr_t)bVar6) - (uintptr_t)(bVar6 != 0);
          goto LAB_10003a4a;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar6 = bVar1 < pbVar3[1];
        if (bVar1 != pbVar3[1]) goto LAB_10003a45;
        pbVar5 = pbVar5 + 2;
        pbVar3 = pbVar3 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_10003a4a:
      if (iVar4 == 0) {
        return iVar2;
      }
    }
  }
  return 0;
}



void Console_HideCmdDialog(void)

{
  SendMessageA(ghCmdDialog,0x10,0,0);
  return;
}



unsigned int CharServer_HeartbeatCheck(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  DWORD DVar4;
  uint uVar5;
  int iVar6;
  unsigned int uVar7;
  int *piVar8;
  unsigned int uVar9;
  char *pcVar10;
  int *piVar11;
  unsigned char uStack_101;
  unsigned char auStack_100 [256];
  
  uVar7 = 0;
  iVar2 = _ftime64((int *)0x0);
  if (DAT_1002313c == 0) {
    DAT_1002313c = iVar2;
  }
  if ((uintptr_t)(iVar2 - DAT_1002313c) < 0x3c) {
    return 1;
  }
  iVar6 = 0;
  piVar8 = (int*)&sCharServerConns;
  DAT_1002313c = iVar2;
  do {
    piVar1 = piVar8 + 1;
    if (((char)piVar8[1] != '\0') && ((char)piVar8[1] != '0')) {
      iVar2 = FOG_InitTimers(*piVar8);
      if (iVar2 == 0) {
        FOG_Noop();
        *piVar8 = 0;
        uStack_101 = 5;
        if ((HANDLE)piVar8[10] == (HANDLE)0x0) {
          pcVar10 = s__CHARACTER_SERVER__Lost_connecti_1001f024;
          uVar9 = 1;
          piVar11 = piVar1;
          Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Lost_connecti_1001f024);
          SStrPrintf((char*)auStack_100,0x100,Char_Server___d_1001efa0,iVar6,uVar9,pcVar10,
                     piVar11);
          iVar2 = FOG_ReallocPool();
          *piVar8 = iVar2;
          iVar2 = FOG_Noop3(iVar2);
          piVar8[10] = iVar2;
          pcVar10 = s__CHARACTER_SERVER__Connecting_to_1001efc4;
LAB_10002a72:
          Console_WriteGraphDisplay(1,(byte *)pcVar10);
        }
        else {
          DVar4 = WaitForSingleObject((HANDLE)piVar8[10],0);
          if (DVar4 != 0x102) {
            CloseHandle((HANDLE)piVar8[10]);
            piVar8[10] = 0;
            if (*piVar8 != 0) {
              FOG_EnterCriticalSection(*piVar8,&uStack_101,1);
              pcVar10 = s__CHARACTER_SERVER__Connected_to_C_1001ef5c;
              goto LAB_10002a72;
            }
            SStrPrintf((char*)auStack_100,0x100,Char_Server___d_1001efa0,iVar6);
            iVar2 = FOG_ReallocPool();
            *piVar8 = iVar2;
            iVar2 = FOG_Noop3(iVar2);
            piVar8[10] = iVar2;
          }
        }
      }
      else {
        uStack_101 = 8;
        iVar2 = 0;
        uVar5 = nCharServerSelector;
        do {
          if ((&sCharServerConns)[uVar5 * 0xb] != 0) {
            iVar3 = FOG_Send((&sCharServerConns)[uVar5 * 0xb],&uStack_101,1);
            if (iVar3 != 0) break;
          }
          uVar5 = (uVar5 + 1) % 3;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 3);
        uVar7 = 1;
        nCharServerSelector = uVar5;
      }
    }
    piVar8 = piVar8 + 0xb;
    iVar6 = iVar6 + 1;
    if (0x1002313b < (intptr_t)piVar8) {
      return uVar7;
    }
  } while( true );
}



void __fastcall GameData_ListNode_Detach4(int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = param_1[1];
    if ((intptr_t)uVar2 < 0) {
      piVar3 = (int *)~uVar2;
    }
    else {
      piVar3 = (int *)((intptr_t)param_1 + (uVar2 - *(int *)(iVar1 + 4)));
    }
    *piVar3 = iVar1;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}



void __fastcall
Server_SendJoinGame(unsigned int gameMCPId,unsigned int serverID,unsigned int playerID,unsigned int token)

{
  unsigned char uStack_14;
  unsigned int uStack_13;
  unsigned int uStack_f;
  unsigned int uStack_b;
  unsigned int uStack_7;
  
  Console_WriteGraphDisplay(0,(byte *)s__Server__GTM_JOINGAME_10020e1c);
  uStack_14 = 7;
  uStack_b = playerID;
  uStack_7 = token;
  uStack_13 = gameMCPId;
  uStack_f = serverID;
  FOG_Send(ghGameServer,&uStack_14,0x11);
  return;
}



void __cdecl Memory_SafeDelete(int nMemory)

{
  if (nMemory != 0) {
    SMemFree((void*)(nMemory),s_delete_1001ed70,0xffffffff,0);
  }
  return;
}



void __fastcall Console_GraphSetTime(LPARAM param_1)

{
  if (ghConsoleDlg != nullptr) {
    SendDlgItemMessageA(ghConsoleDlg,0x3f1,0xc,0,param_1);
  }
  return;
}



unsigned int __fastcall Server_SendFileData(char *szFileName,int pFileBuffer,int nFileSize)

{
  char cVar1;
  unsigned int uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  unsigned int *puVar6;
  char *pcVar7;
  unsigned int *puVar8;
  unsigned char uStack_19c;
  char acStack_19b [4];
  ushort uStack_197;
  ushort uStack_195;
  unsigned short uStack_193;
  unsigned int auStack_191 [100];
  
  if (nFileSize == 0) {
    return 1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = szFileName;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = szFileName + 1;
    cVar1 = *szFileName;
    szFileName = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  uStack_19c = 0xc;
  pcVar5 = pcVar5 + -uVar3;
  pcVar7 = acStack_19b;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pcVar7 = *(unsigned int *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uStack_193 = (unsigned short)nFileSize;
  uStack_197 = 0;
  do {
    uStack_195 = 400;
    if (nFileSize < 0x191) {
      uStack_195 = (ushort)nFileSize;
    }
    puVar6 = (unsigned int *)((uintptr_t)uStack_197 + pFileBuffer);
    puVar8 = auStack_191;
    for (uVar3 = (uintptr_t)(uStack_195 >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    for (uVar3 = uStack_195 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(unsigned char *)puVar8 = *(unsigned char *)puVar6;
      puVar6 = (unsigned int *)((intptr_t)puVar6 + 1);
      puVar8 = (unsigned int *)((intptr_t)puVar8 + 1);
    }
    uVar2 = FOG_Send(ghGameServer,&uStack_19c,CONCAT22(uStack_193,uStack_195) + 0xb);
    uStack_197 = uStack_197 + uStack_195;
    nFileSize = nFileSize - (uintptr_t)uStack_195;
  } while (nFileSize != 0);
  return uVar2;
}



unsigned int __fastcall MCP_DispatchIncomingMessage(byte *param_1,int param_2)

{
  unsigned int uVar1;
  
  uVar1 = 0;
  if (param_2 == 0) {
    return 0;
  }
  if (0x13 < *param_1) {
    return 0;
  }
  if ((void *)(&g_McpMessageHandlers)[*param_1] != (void *)0x0) {
    uVar1 = ((int (*)())(*(void **)(&g_McpMessageHandlers + *param_1)))();
  }
  return uVar1;
}



void __fastcall Server_SendCharInfo(int pCharInfoData,int bIsPlayerAccount)

{
  int iVar1;
  int iVar2;
  unsigned int uStack_238;
  int iStack_234;
  int iStack_230;
  unsigned int uStack_22c;
  unsigned char *puStack_228;
  int iStack_224;
  unsigned int uStack_220;
  unsigned int uStack_20f;
  unsigned char uStack_20b;
  unsigned char uStack_20a;
  unsigned char uStack_209;
  unsigned char uStack_208;
  uint uStack_207;
  unsigned char auStack_203 [515];
  
  uStack_220 = 0x200;
  uStack_20f = *(unsigned int *)(pCharInfoData + 0x88);
  uStack_20b = *(unsigned char *)(pCharInfoData + 0x84);
  uStack_20a = *(unsigned char *)(pCharInfoData + 0x85);
  uStack_209 = *(unsigned char *)(pCharInfoData + 0x86);
  uStack_208 = *(unsigned char *)(pCharInfoData + 8);
  iStack_224 = pCharInfoData + 100;
  puStack_228 = auStack_203;
  uStack_207 = (uintptr_t)(bIsPlayerAccount == 0);
  uStack_22c = 0x10006902;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  iStack_230 = pCharInfoData + 0x74;
  iStack_234 = (intptr_t)&uStack_20f + iVar1 + 1;
  uStack_22c = 0x200;
  uStack_238 = 0x10006915;
  iVar2 = SStrCopy((char*)0, (char*)0, 0);
  iVar1 = (intptr_t)&uStack_20f + iVar2 + iVar1 + 2;
  uStack_238 = 0x200;
  iVar2 = SStrCopy((char*)(intptr_t)iVar1,(char*)&DAT_10023254,0);
  FOG_Send(ghGameServer,&uStack_238,
            iVar2 + 0x12 +
            CONCAT22((short)((uintptr_t)iVar1 >> 0x10),(short)iVar1 - ((short)&puStack_228 + 1)));
  return;
}



unsigned int __fastcall CharServer_ConnectAll(HWND hWnd)

{
  HANDLE hHandle;
  DWORD DVar1;
  BOOL BVar2;
  int iVar3;
  BOOL BVar4;
  char *pcVar5;
  unsigned int uStack_28;
  DWORD DStack_20;
  struct tagMSG tStack_1c;
  
  uStack_28 = 0;
  BVar4 = 1;
  hHandle = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                         (LPTHREAD_START_ROUTINE)&lpStartAddress_1000113b,(LPVOID)0x0,0,&DStack_20);
  do {
    DVar1 = WaitForSingleObject(hHandle,0);
    if (DVar1 == 0) break;
    BVar2 = PeekMessageA(&tStack_1c,(HWND)0x0,0,0,0);
    if (BVar2 == 0) {
      Sleep(10);
    }
    else {
      BVar4 = GetMessageA(&tStack_1c,(HWND)0x0,0,0);
      BVar2 = IsDialogMessageA(hWnd,&tStack_1c);
      if (BVar2 == 0) {
        TranslateMessage(&tStack_1c);
        DispatchMessageA(&tStack_1c);
      }
    }
  } while (BVar4 != 0);
  pcVar5 = (char*)&sCharServerConnsStatus;
  do {
    if ((pcVar5 != (char *)0x0) && (*pcVar5 != '0')) {
      iVar3 = FOG_InitTimers(*(unsigned int *)(pcVar5 + -4));
      if (iVar3 != 0) {
        uStack_28 = 1;
      }
    }
    pcVar5 = pcVar5 + 0x2c;
  } while ((intptr_t)pcVar5 < 0x10023140);
  return uStack_28;
}



void MCP_DisconnectFromServer(void)

{
  D2NET_10018(0);
  FOG_Noop();
  return;
}



void __cdecl Console_WriteGraphDisplay(int bAlsoDebugFile,byte *szFormat)

{
  char cVar1;
  LPARAM lParam;
  int iVar2;
  char *pcVar3;
  char acStack_100 [256];
  
  _vsnprintf((char*)acStack_100,szFormat,&uStack00000008);
  if (bAlsoDebugFile != 0) {
    FOG_DisplayError((char*)0);
  }
  iVar2 = -1;
  pcVar3 = acStack_100;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  lParam = FOG_CrashDeadlockDetected(0x123,0);
  SStrCopy((char*)(intptr_t)lParam,(char*)&uStack00000000,0x7fffffff);
  PostMessageA(ghConsoleDlg,0x401,0,lParam);
  return;
}



#if 0
int * __thiscall GameData_ListNode_Clear(void *_this,byte param_1)

{
  GameDataPool_ClearEntry(_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return _this;
}
#endif /* GameData_ListNode_Clear */




void Server_ShutdownFromMCP(void)

{
  int iVar1;
  
  FOG_DisplayError(s_Shutdown_Remotely_by_MCP_100211dc);
  D2GAME_10006();
  iVar1 = Console_GetMainDialogHandle();
  if (iVar1 != 0) {
    Console_DestroyGraphDisplay();
  }
  iVar1 = Console_GetCmdDialogHandle();
  if (iVar1 != 0) {
    Console_HideCmdDialog();
  }
  bShutdownFlag = 1;
  return;
}



unsigned int Server_OpenMPQArchives(void)

{
  CHAR aCStack_104 [260];
  
  GetModuleFileNameA((HMODULE)0x0,aCStack_104,0x104);
  ghD2DataMPQ = (uintptr_t)MPQ_OpenWithRetry(aCStack_104,s_d2data_mpq_1001ed60,(uintptr_t)s_d2data_1001ed58,0,
                                  (unsigned char *)0x0);
  ghD2CharMPQ = (uintptr_t)MPQ_OpenWithRetry(aCStack_104,s_d2char_mpq_1001ed48,(uintptr_t)s_d2char_1001ed40,0,
                                  (unsigned char *)0x0);
  if ((ghD2DataMPQ != (int *)0x0) && (ghD2CharMPQ != (int *)0x0)) {
    return 1;
  }
  return 0;
}



void __fastcall GameDataPool_FreeList(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 4) != 0) {
    iVar1 = 0;
    do {
      GameDataPool_ClearEntry((int *)(iVar1 + *(int *)(param_1 + 8)));
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0xc;
    } while (uVar2 < *(uint *)(param_1 + 4));
  }
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  return;
}



void __fastcall GameDataPool_DetachAll(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  piVar1 = param_1 + 1;
  while (0 < param_1[2]) {
    piVar4 = (int *)(*param_1 + param_1[2]);
    if (*piVar4 != 0) {
      uVar2 = piVar4[1];
      if ((intptr_t)uVar2 < 0) {
        piVar5 = (int *)~uVar2;
      }
      else {
        piVar5 = (int *)((intptr_t)piVar4 + (uVar2 - *(int *)(*piVar4 + 4)));
      }
      *piVar5 = *piVar4;
      *(int *)(*piVar4 + 4) = piVar4[1];
      *piVar4 = 0;
      piVar4[1] = 0;
    }
  }
  iVar3 = *piVar1;
  if (iVar3 != 0) {
    uVar2 = param_1[2];
    if ((intptr_t)uVar2 < 0) {
      piVar4 = (int *)~uVar2;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar2 - *(int *)(iVar3 + 4)));
    }
    *piVar4 = iVar3;
    *(int *)(*piVar1 + 4) = param_1[2];
    *piVar1 = 0;
    param_1[2] = 0;
  }
  return;
}



void __fastcall Server_SendCharDelete(unsigned int param_1,unsigned int param_2,ushort param_3)

{
  int iVar1;
  unsigned int extraout_EDX;
  char *pcStack_214;
  char *pcStack_210;
  unsigned int uStack_20c;
  char acStack_201 [513];
  
  if (4 < param_3) {
    uStack_20c = 0x15d;
    pcStack_210 = s_C__D2_Source_D2Server_CORE_ToMCP_10020e98;
    pcStack_214 = (char*)s_wClass_0x3c_NUM_PLAYERCLASS_10020e78;
    FOG_SetLogPrefix((char*)0, (char*)0, 0);
    uStack_20c = 0x100070cf;
    _exit_wrapper(0xffffffff);
    param_2 = extraout_EDX;
  }
  uStack_20c = 0x200;
  pcStack_214 = acStack_201;
  pcStack_210 = (char *)param_2;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  FOG_Send(ghGameServer,&pcStack_214,iVar1 + 8);
  return;
}



void __fastcall GameData_PoolInit2(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = (uintptr_t)puVar1;
  *param_1 = 0;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}



void __fastcall GameData_Destructor_ListBase2(unsigned int *param_1)

{
  void *_this;
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  void *pvStack_c;
  unsigned char *puStack_8;
  uint uStack_4;
  
  puStack_8 = (unsigned char*)&LAB_1001a674;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = (uintptr_t)&g_GameServerVtable2;
  uStack_4 = 2;
  while( true ) {
    iVar5 = param_1[0x10];
    uVar4 = 0;
    if (iVar5 < 1) break;
    GameData_ChunkClearEntry(iVar5);
    SMemFree((void*)(iVar5),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (_this = (void *)param_1[0xc], 0 < (intptr_t)_this) {
    GameData_DeletingDestructor2(_this,0);
    SMemFree((void*)(_this),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  uStack_4 = CONCAT31((*((unsigned int*)&(uStack_4)+1)),1);
  piVar3 = param_1 + 0xf;
  while (0 < (intptr_t)param_1[0x10]) {
    GameData_ListNode_Detach4((int *)(param_1[0xe] + param_1[0x10]));
  }
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode2(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = param_1[0x10];
    *piVar3 = 0;
    param_1[0x10] = 0;
  }
  uStack_4 = uStack_4 & 0xffffff00;
  piVar3 = param_1 + 0xb;
  while (0 < (intptr_t)param_1[0xc]) {
    GameData_ListNode_Detach2((int *)(param_1[10] + param_1[0xc]));
  }
  if (*piVar3 != 0) {
    piVar2 = (int *)GameData_PoolIndexToNode(piVar3,-1);
    *piVar2 = *piVar3;
    *(unsigned int *)(*piVar3 + 4) = param_1[0xc];
    *piVar3 = 0;
    param_1[0xc] = 0;
  }
  *param_1 = (uintptr_t)&g_GameServerVtable1;
  uStack_4 = 4;
  param_1[4] = 0;
  GameDataPool_DetachAll3((int*)param_1 + 1);
  if (param_1[6] != 0) {
    iVar5 = 0;
    do {
      while( true ) {
        iVar1 = *(int *)(param_1[7] + iVar5 + 8);
        if (iVar1 < 1) break;
        piVar3 = GameData_PoolGetBeginNode((void *)(param_1[7] + iVar5),iVar1);
        GameData_ListNode_Detach2(piVar3);
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0xc;
    } while (uVar4 < (uintptr_t)param_1[6]);
  }
  GameDataPool_FreeList((intptr_t)(param_1 + 5));
  uStack_4 = 0xffffffff;
  GameDataPool_DetachAll3((int*)param_1 + 1);
  GameData_ListNode_Detach2((int*)param_1 + 2);
  pExceptionList = pvStack_c;
  return;
}



uint __thiscall GameData_PoolIndexToNode2(void *_this,int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)((intptr_t)_this + 4);
  if ((intptr_t)uVar1 < 0) {
    return ~uVar1;
  }
  if (param_1 < 0) {
    param_1 = (intptr_t)_this - *(int *)(*(int *)_this + 4);
  }
  return uVar1 + param_1;
}



int __fastcall CharServer_SendType7Packet(char *szServerName)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  unsigned char uStack_14;
  char acStack_13 [19];
  
  uVar3 = 0xffffffff;
  pcVar6 = szServerName;
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  uStack_14 = 7;
  pcVar6 = pcVar7 + -uVar3;
  pcVar7 = acStack_13;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pcVar7 = *(unsigned int *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *szServerName;
    szServerName = szServerName + 1;
  } while (cVar1 != '\0');
  iVar5 = 0;
  uVar4 = nCharServerSelector;
  do {
    if ((&sCharServerConns)[uVar4 * 0xb] != 0) {
      iVar2 = FOG_Send((&sCharServerConns)[uVar4 * 0xb],&uStack_14,~uVar3 + 1);
      if (iVar2 != 0) break;
    }
    uVar4 = (uVar4 + 1) % 3;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  nCharServerSelector = uVar4;
  return iVar5 < 3;
}



void __fastcall GameData_ListNode_Detach3(int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = param_1[1];
    if ((intptr_t)uVar2 < 0) {
      piVar3 = (int *)~uVar2;
    }
    else {
      piVar3 = (int *)((intptr_t)param_1 + (uVar2 - *(int *)(iVar1 + 4)));
    }
    *piVar3 = iVar1;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}



void __fastcall
Server_SendCharCreateResult
          (unsigned int pThis,unsigned int param_2,unsigned short param_3,unsigned short param_4,
          unsigned short param_5)

{
  int iVar1;
  unsigned char *puStack_218;
  unsigned int uStack_214;
  unsigned int uStack_210;
  unsigned char uStack_20c;
  unsigned int uStack_20b;
  unsigned short uStack_207;
  unsigned short uStack_205;
  unsigned short uStack_203;
  unsigned char auStack_201 [513];
  
  uStack_207 = param_3;
  uStack_205 = param_4;
  uStack_210 = 0x200;
  puStack_218 = auStack_201;
  uStack_20c = 10;
  uStack_203 = param_5;
  uStack_214 = param_2;
  uStack_20b = pThis;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  FOG_Send(ghGameServer,&puStack_218,iVar1 + 0xc);
  return;
}



void Server_SendCharCreateSave
               (unsigned short charlvl,unsigned int charname,unsigned int charBinaryData,unsigned short classId,
               unsigned int charSaveSize)

{
  int iVar1;
  int iVar2;
  unsigned int uStack_230;
  unsigned char *puStack_22c;
  unsigned int uStack_228;
  unsigned int uStack_224;
  unsigned short uStack_20f;
  unsigned int uStack_20d;
  unsigned int uStack_209;
  unsigned short uStack_205;
  unsigned char auStack_203 [11];
  unsigned char auStack_1f8 [504];
  
  uStack_205 = classId;
  uStack_20d = charname;
  uStack_224 = 0x200;
  puStack_22c = auStack_203;
  uStack_228 = charSaveSize;
  uStack_20f = charlvl;
  uStack_209 = charBinaryData;
  uStack_230 = 0x10006bd4;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  iVar1 = (intptr_t)&uStack_20f + iVar1 + 1;
  uStack_230 = 0x200;
  iVar2 = SStrCopy(iVar1,charBinaryData,0);
  FOG_Send(ghGameServer,&uStack_230,iVar2 + 0x16 + (iVar1 - (intptr_t)&uStack00000000));
  return;
}



void __fastcall PerfLog_Init(int bEnable)

{
  char cVar1;
  HANDLE hFile;
  uint uVar2;
  char *pcVar3;
  unsigned char uStack_5;
  DWORD DStack_4;
  
  sPerfLog = (HANDLE)bEnable;
  if (bEnable != 0) {
    uStack_5 = 0xd;
    hFile = CreateFileA(s_C__D2_Performace_txt_10020bd0,0x40000000,2,(LPSECURITY_ATTRIBUTES)0x0,4,
                        0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0x0) {
      MessageBoxA((HWND)0x0,s_Error_creating_performance_logfi_10020d44,s_Error_10020d70,0x10);
      sPerfLog = hFile;
      return;
    }
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    uVar2 = 0xffffffff;
    pcVar3 = s_Busy_Games_Players_ActiveMonster_10020d04;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    WriteFile(hFile,s_Busy_Games_Players_ActiveMonster_10020d04,~uVar2 - 1,&DStack_4,
              (LPOVERLAPPED)0x0);
    WriteFile(hFile,&uStack_5,1,&DStack_4,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return;
}



void Console_RefreshDisplay(void)

{
  uint uVar1;
  uint *puVar2;
  LRESULT LVar3;
  int iVar4;
  WPARAM WVar5;
  unsigned int extraout_ECX;
  uint uVar6;
  unsigned int extraout_ECX_00;
  unsigned int extraout_ECX_01;
  unsigned int extraout_ECX_02;
  unsigned int uVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  unsigned int *puVar11;
  unsigned int *puVar12;
  unsigned long long uVar13;
  unsigned char auStack_4fc [4];
  int iStack_4f8;
  LARGE_INTEGER LStack_4ec;
  struct _SYSTEM_INFO _Stack_4e4;
  unsigned char auStack_4c0 [256];
  LRESULT aLStack_3c0 [16];
  unsigned int auStack_380 [16];
  unsigned char auStack_340 [832];
  
  QueryPerformanceCounter(&LStack_4ec);
  if ((DAT_1002318c <= LStack_4ec.u.HighPart) &&
     ((DAT_1002318c < LStack_4ec.u.HighPart || (DAT_10023188 <= LStack_4ec.u.LowPart)))) {
    GetSystemInfo(&_Stack_4e4);
    uVar13 = __alldiv(DAT_10023160 + LStack_4ec.u.LowPart,
                      DAT_10023164 + LStack_4ec.u.HighPart +
                      (uintptr_t)CARRY4(DAT_10023160,LStack_4ec.u.LowPart),
                      _Stack_4e4.dwNumberOfProcessors,0);
    DAT_1002318c = (intptr_t)((ulonglong)uVar13 >> 0x20);
    DAT_10023188 = (uintptr_t)uVar13;
    iVar10 = 0;
    uVar1 = D2GAME_10012();
    if (uVar1 == 0) {
      puVar11 = (unsigned int *)0x0;
      iVar4 = (intptr_t)pGameListHead;
      uVar7 = extraout_ECX;
    }
    else {
      puVar11 = (unsigned int *)FOG_CrashDeadlockDetected(0x48,0);
      if (puVar11 == (unsigned int *)0x0) {
        FOG_SetLogPrefix(s_ptwGameIds_100208d8,s_C__D2_Source_D2Server_CORE_Displ_1002082c,0x49);
        _exit_wrapper(0xffffffff);
      }
      puVar12 = puVar11;
      for (uVar6 = (uVar1 & 0x7fffffff) >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar12 = 0;
        puVar12 = puVar12 + 1;
      }
      for (uVar6 = uVar1 * 2 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(unsigned char *)puVar12 = 0;
        puVar12 = (unsigned int *)((intptr_t)puVar12 + 1);
      }
      iVar10 = D2GAME_10015(puVar11,uVar1);
      iVar4 = (intptr_t)pGameListHead;
      uVar7 = extraout_ECX_00;
    }
    for (; iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x94)) {
      *(unsigned int *)(iVar4 + 0x90) = 0;
    }
    puVar12 = puVar11;
    if (0 < iVar10) {
      do {
        puVar2 = Game_FindByGameId(CONCAT22((short)((uintptr_t)uVar7 >> 0x10),*(unsigned short *)puVar12));
        if (puVar2 == (uint *)0x0) {
          Game_AddToList(CONCAT22((short)((uintptr_t)extraout_ECX_01 >> 0x10),*(unsigned short *)puVar12));
          uVar7 = extraout_ECX_02;
        }
        else {
          puVar2[0x24] = 1;
          uVar7 = extraout_ECX_01;
        }
        iVar10 = iVar10 + -1;
        puVar12 = (unsigned int *)((intptr_t)puVar12 + 2);
      } while (iVar10 != 0);
    }
    Console_SyncGameList();
    if (puVar11 != (unsigned int *)0x0) {
      FOG_CrashDumpThread(0xcd,0);
    }
    Console_UpdateGameDetails();
    iVar10 = 0;
    LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0);
    if ((LVar3 != -1) && (LVar3 != DAT_100207d0)) {
      for (piVar8 = (int*)&sGameDetailTable; DAT_100207d0 = LVar3, (intptr_t)piVar8 < 0x10020814;
          piVar8 = piVar8 + 3) {
        if (*piVar8 == LVar3) {
          iVar4 = Game_FindByName();
          if (iVar4 != 0) {
            ((int (*)())(*(void (**)(void))(iVar10 * 0xc + 0x100207dc)))();
          }
          break;
        }
        iVar10 = iVar10 + 1;
      }
    }
    piVar8 = (int *)Game_FindByName();
    if ((piVar8 != (int *)0x0) &&
       (LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0), LVar3 != -1)) {
      iVar10 = 0;
      piVar9 = (int*)&sGameDetailTable;
      do {
        if (*piVar9 == LVar3) {
          if (iVar10 < 5) {
            iVar10 = *(int *)(iVar10 * 0xc + 0x100207e0);
            WVar5 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x188,0,0);
            if (((WVar5 != 0xffffffff) &&
                (LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x199,WVar5,0), iVar10 == 0)) &&
               ((*piVar8 != DAT_10020814 || ((DAT_10020818 != 0 || (LVar3 != DAT_100231bc)))))) {
              DAT_10020818 = 0;
              DAT_10020814 = *piVar8;
              DAT_100231bc = LVar3;
              SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fa,0x184,0,0);
              auStack_380[0] = 0;
              aLStack_3c0[0] = LVar3;
              iVar10 = D2GAME_10018(CONCAT22((short)((uintptr_t)aLStack_3c0 >> 0x10),(short)*piVar8),1,
                                    auStack_340,auStack_380,aLStack_3c0);
              WVar5 = 0;
              if (0 < iVar10) {
                do {
                  _vsprintf_l((byte*)auStack_4c0,&DAT_100208d4);
                  SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fa,0x181,WVar5,(LPARAM)auStack_4c0);
                  WVar5 = WVar5 + 1;
                } while ((intptr_t)WVar5 < iVar10);
              }
            }
          }
          break;
        }
        piVar9 = piVar9 + 3;
        iVar10 = iVar10 + 1;
      } while ((intptr_t)piVar9 < 0x10020814);
    }
    D2GAME_10020(auStack_4fc);
    _vsprintf_l((byte*)auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f7,0xc,0,(LPARAM)auStack_4c0);
    _vsprintf_l((byte*)auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f6,0xc,0,(LPARAM)auStack_4c0);
    Console_GraphSetFrameRate((LPARAM)auStack_4c0);
    _vsprintf_l((byte*)auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f8,0xc,0,(LPARAM)auStack_4c0);
    _vsprintf_l((char*)auStack_4c0,(byte *)s__d___d____d__100208c0);
    Console_GraphSetTime((LPARAM)auStack_4c0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f1,0xc,0,(LPARAM)auStack_4c0);
    Console_GraphDrawDataPoint(sPerfState,iStack_4f8);
    PerfLog_WriteEntry();
  }
  Console_UpdateBusyPercent();
  return;
}



int ReturnZero(void)

{
  return 0;
}



unsigned int Server_GameTick(void)

{
  DWORD DVar1;
  int iVar2;
  unsigned int extraout_ECX;
  
  DVar1 = GetTickCount();
  if (dwLastTickCount == 0) {
    dwLastTickCount = DVar1;
  }
  if (59999 < DVar1 - dwLastTickCount) {
    dwLastTickCount = DVar1;
    iVar2 = FOG_InitTimers(0);
    if (iVar2 != 0) {
      bMcpConnected = 1;
      return 1;
    }
    if (bMcpConnected != 0) {
      bMcpConnected = 0;
    }
    FOG_Noop();
    iVar2 = SRegLoadString((char*)0, (char*)0, 0, (char*)0, 0);
    if (iVar2 == 0) {
      SRegSaveString((char*)0, (char*)0, 0, (char*)0, 0);
      return 1;
    }
    ghGameServer = (void*)(intptr_t)FOG_ReallocPool();
    FOG_GetDiskInfo();
    FOG_ExceptionHandler((intptr_t)ghGameServer);
    FOG_EnterCriticalSection((intptr_t)ghGameServer,&uStack00000000,1);
    MCP_SendType1((int3)extraout_ECX);
    D2NET_10018((intptr_t)&g_NetEventCallback);
    Console_WriteGraphDisplay(1,(byte *)s__SERVER__Connected_to_MCP_at__s_1001ed80);
  }
  return 1;
}



int __fastcall CharServer_SendGameData(char *param_1,unsigned int param_2)

{
  int bVar1;
  
  bVar1 = CharServer_SendGameData(param_1,param_2);
  return bVar1;
}



void __fastcall GameDataPool_DetachAll2(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  piVar1 = param_1 + 1;
  while (0 < param_1[2]) {
    piVar4 = (int *)(*param_1 + param_1[2]);
    if (*piVar4 != 0) {
      uVar2 = piVar4[1];
      if ((intptr_t)uVar2 < 0) {
        piVar5 = (int *)~uVar2;
      }
      else {
        piVar5 = (int *)((intptr_t)piVar4 + (uVar2 - *(int *)(*piVar4 + 4)));
      }
      *piVar5 = *piVar4;
      *(int *)(*piVar4 + 4) = piVar4[1];
      *piVar4 = 0;
      piVar4[1] = 0;
    }
  }
  iVar3 = *piVar1;
  if (iVar3 != 0) {
    uVar2 = param_1[2];
    if ((intptr_t)uVar2 < 0) {
      piVar4 = (int *)~uVar2;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar2 - *(int *)(iVar3 + 4)));
    }
    *piVar4 = iVar3;
    *(int *)(*piVar1 + 4) = param_1[2];
    *piVar1 = 0;
    param_1[2] = 0;
  }
  return;
}



void Console_ClearGameList(void)

{
  byte bVar1;
  int iVar2;
  LRESULT LVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  WPARAM wParam;
  int bVar7;
  byte abStack_10 [16];
  
  iVar2 = (intptr_t)pGameListHead;
  do {
    if (iVar2 == 0) {
      pGameListHead = (void*)(intptr_t)iVar2;
      return;
    }
    pGameListHead = (void*)(intptr_t)iVar2;
    LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x18b,0,0);
    wParam = 0;
    if (0 < LVar3) {
      do {
        SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,wParam,(LPARAM)abStack_10);
        pbVar4 = abStack_10;
        pbVar6 = (byte *)(iVar2 + 100);
        do {
          bVar1 = *pbVar4;
          bVar7 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_1000554b:
            iVar5 = (1 - (uintptr_t)bVar7) - (uintptr_t)(bVar7 != 0);
            goto LAB_10005550;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar7 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_1000554b;
          pbVar4 = pbVar4 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_10005550:
        if (iVar5 == 0) {
          SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x182,wParam,0);
          break;
        }
        wParam = wParam + 1;
      } while ((intptr_t)wParam < LVar3);
    }
    pGameListHead = (void*)(intptr_t)*(int *)(iVar2 + 0x94);
    FOG_CrashDumpThread(0x2b6,0);
    iVar2 = (intptr_t)pGameListHead;
  } while( true );
}



void __fastcall GameDataPool_DetachAll3(int *param_1)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  
  while (0 < param_1[2]) {
    piVar2 = (int *)(*param_1 + param_1[2]);
    if (*piVar2 != 0) {
      uVar1 = piVar2[1];
      if ((intptr_t)uVar1 < 0) {
        piVar3 = (int *)~uVar1;
      }
      else {
        piVar3 = (int *)((intptr_t)piVar2 + (uVar1 - *(int *)(*piVar2 + 4)));
      }
      *piVar3 = *piVar2;
      *(int *)(*piVar2 + 4) = piVar2[1];
      *piVar2 = 0;
      piVar2[1] = 0;
    }
  }
  return;
}



int CharServer_SendType2Packet(unsigned int param_1,unsigned char param_2)

{
  byte *pbVar1;
  char cVar2;
  int iVar3;
  char *extraout_ECX;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *extraout_EDX;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  unsigned long long uVar10;
  unsigned int uStack00000009;
  int iStack00000011;
  ushort *in_stack_0000103c;
  uint in_stack_00001040;
  
  _alloca_probe();
  param_2 = 2;
  uStack00000009 = FOG_Log();
  iStack00000011 = 0;
  iVar7 = 0;
  if (0 < (intptr_t)in_stack_00001040) {
    do {
      pbVar1 = (byte *)(iVar7 + (intptr_t)in_stack_0000103c);
      iVar7 = iVar7 + 1;
      iStack00000011 = (uintptr_t)*pbVar1 + (uintptr_t)(iStack00000011 < 0) + iStack00000011 * 2;
    } while (iVar7 < (intptr_t)in_stack_00001040);
  }
  uVar4 = 0xffffffff;
  pcVar8 = extraout_ECX;
  do {
    pcVar9 = pcVar8;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar8 + 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar8 = pcVar9 + -uVar4;
  pcVar9 = (char*)&uStack0000000f;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(unsigned int *)pcVar9 = *(unsigned int *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar8 = extraout_ECX;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar2 != '\0');
  uVar5 = 0xffffffff;
  pcVar8 = extraout_EDX;
  do {
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  pcVar9 = (char*)&uStack0000000f + ~uVar4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pcVar9 = *(unsigned int *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar8 = extraout_EDX;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  if (*in_stack_0000103c != in_stack_00001040) {
    FOG_SetLogPrefix(s___WORD___pbData____nLength_1001eec8,s_C__D2_Source_D2Server_CORE_CharS_1001eee8,0xf8
             );
    uVar10 = _exit_wrapper(0xffffffff);
    in_stack_00001040 = (uintptr_t)((ulonglong)uVar10 >> 0x20);
    uVar5 = (uintptr_t)uVar10;
  }
  pcVar8 = (char*)&uStack0000000f + ~uVar4 + uVar5;
  for (uVar6 = in_stack_00001040 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pcVar8 = *(unsigned int *)in_stack_0000103c;
    in_stack_0000103c = in_stack_0000103c + 2;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar6 = in_stack_00001040 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar8 = (char)*in_stack_0000103c;
    in_stack_0000103c = (ushort *)((intptr_t)in_stack_0000103c + 1);
    pcVar8 = pcVar8 + 1;
  }
  iVar7 = 0;
  uVar6 = nCharServerSelector;
  do {
    if ((&sCharServerConns)[uVar6 * 0xb] != 0) {
      iVar3 = FOG_Send((&sCharServerConns)[uVar6 * 0xb],&param_2,
                        ~uVar4 + 0xd + uVar5 + in_stack_00001040);
      if (iVar3 != 0) break;
    }
    uVar6 = (uVar6 + 1) % 3;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 3);
  nCharServerSelector = uVar6;
  return iVar7 < 3;
}



void __fastcall String_ToLower(char *szString)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = szString;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar3 = 0;
  if (0 < (intptr_t)(~uVar2 - 1)) {
    do {
      cVar1 = szString[iVar3];
      if ((cVar1 < '[') && ('@' < cVar1)) {
        szString[iVar3] = cVar1 + ' ';
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (intptr_t)(~uVar2 - 1));
  }
  return;
}



void __thiscall GameData_PoolReserve(void *_this,int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  
  if (param_1 != *(int *)_this) {
    uVar1 = (intptr_t)_this + 4;
    while (0 < *(int *)((intptr_t)_this + 8)) {
      piVar3 = (int *)(*(int *)_this + *(int *)((intptr_t)_this + 8));
      if (*piVar3 != 0) {
        uVar2 = piVar3[1];
        if ((intptr_t)uVar2 < 0) {
          piVar4 = (int *)~uVar2;
        }
        else {
          piVar4 = (int *)((intptr_t)piVar3 + (uVar2 - *(int *)(*piVar3 + 4)));
        }
        *piVar4 = *piVar3;
        *(int *)(*piVar3 + 4) = piVar3[1];
        *piVar3 = 0;
        piVar3[1] = 0;
      }
    }
    *(uint *)uVar1 = uVar1;
    *(uint *)((intptr_t)_this + 8) = ~uVar1;
    *(int *)_this = param_1;
  }
  return;
}



void Server_SendKeepAlive(void)

{
  Server_SendKeepAlive();
  return;
}



void __fastcall Console_ParseAndExecuteCommand(unsigned int dwContext,byte *pszOutputBuffer)

{
  char cVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  byte *pbVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  int bVar12;
  byte abStack_206 [2];
  unsigned int uStack_204;
  byte abStack_200 [512];
  
  iVar2 = 0;
  abStack_200[0x100] = 0;
  abStack_206[0] = 0x20;
  abStack_206[1] = 9;
  pbVar8 = pszOutputBuffer;
  do {
    bVar7 = *pbVar8;
    iVar4 = 0;
    do {
      if (bVar7 == abStack_206[iVar4]) goto LAB_1000347d;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    if (bVar7 == 0) break;
    pbVar8[(intptr_t)(abStack_200 + -(intptr_t)pszOutputBuffer)] = bVar7;
    iVar2 = iVar2 + 1;
    pbVar8 = pbVar8 + 1;
  } while (iVar2 < 0x100);
LAB_1000347d:
  bVar7 = pszOutputBuffer[iVar2];
  abStack_200[iVar2] = 0;
  if (bVar7 != 0) {
    while (iVar2 < 0x100) {
      abStack_206[0] = 0x20;
      abStack_206[1] = 9;
      iVar4 = 0;
      while (bVar7 != abStack_206[iVar4]) {
        iVar4 = iVar4 + 1;
        if (1 < iVar4) goto LAB_100034b2;
      }
      bVar7 = pszOutputBuffer[iVar2 + 1];
      iVar2 = iVar2 + 1;
      if (bVar7 == 0) break;
    }
LAB_100034b2:
    bVar7 = pszOutputBuffer[iVar2];
    iVar4 = 0;
    while ((bVar7 != 0 && (iVar2 < 0x100))) {
      iVar2 = iVar2 + 1;
      abStack_200[iVar4 + 0x100] = bVar7;
      iVar4 = iVar4 + 1;
      bVar7 = pszOutputBuffer[iVar2];
    }
    abStack_200[iVar4 + 0x100] = 0;
  }
  abStack_206[1] = 9;
  abStack_206[0] = 0x20;
  uStack_204 = dwContext;
  String_ToLower((char *)abStack_200);
  iVar2 = 0;
  pbVar8 = (byte*)&DAT_1001f058;
  do {
    pbVar3 = abStack_200;
    pbVar9 = pbVar8;
    do {
      bVar7 = *pbVar3;
      bVar12 = bVar7 < *pbVar9;
      if (bVar7 != *pbVar9) {
LAB_10003513:
        iVar4 = (1 - (uintptr_t)bVar12) - (uintptr_t)(bVar12 != 0);
        goto LAB_10003518;
      }
      if (bVar7 == 0) break;
      bVar7 = pbVar3[1];
      bVar12 = bVar7 < pbVar9[1];
      if (bVar7 != pbVar9[1]) goto LAB_10003513;
      pbVar3 = pbVar3 + 2;
      pbVar9 = pbVar9 + 2;
    } while (bVar7 != 0);
    iVar4 = 0;
LAB_10003518:
    if (iVar4 == 0) {
      iVar2 = ((int (*)())(*(void **)(&PTR_Console_DisplayHelp_1001f158 + iVar2 * 0x81)))();
      if (iVar2 != 0) {
        return;
      }
      goto LAB_100035a0;
    }
    pbVar8 = pbVar8 + 0x204;
    iVar2 = iVar2 + 1;
  } while (pbVar8 < &DAT_1002027c);
  uVar5 = 0xffffffff;
  pcVar10 = s_ERROR__Unknown_command___10020620;
  do {
    pcVar11 = pcVar10;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar11 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar11;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar8 = (byte *)(pcVar11 + -uVar5);
  pbVar3 = pszOutputBuffer;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
  uVar5 = 0xffffffff;
  pbVar8 = abStack_200;
  do {
    pbVar3 = pbVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pbVar3 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar3;
  } while (bVar7 != 0);
  uVar5 = ~uVar5;
  iVar2 = -1;
  pbVar8 = pszOutputBuffer;
  do {
    pbVar9 = pbVar8;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pbVar9 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar9;
  } while (bVar7 != 0);
  pbVar8 = pbVar3 + -uVar5;
  pbVar3 = pbVar9 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar10 = (char*)&DAT_1002061c;
  do {
    pcVar11 = pcVar10;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar11 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar11;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  iVar2 = -1;
  pbVar8 = pszOutputBuffer;
  do {
    pbVar3 = pbVar8;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pbVar3 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar3;
  } while (bVar7 != 0);
  pbVar8 = (byte *)(pcVar11 + -uVar5);
  pbVar3 = pbVar3 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
LAB_100035a0:
  Console_WriteGraphDisplay(0,pszOutputBuffer);
  return;
}



int __thiscall GameData_DeletingDestructor2(void *_this,byte param_1)

{
  GameData_RemoveAllEntries((intptr_t)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (intptr_t)_this;
}



unsigned int Console_IsPerfLogEnabled(void)

{
  return (uintptr_t)sPerfLog;
}



uint __thiscall GameData_PoolIndexToNode(void *_this,int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)((intptr_t)_this + 4);
  if ((intptr_t)uVar1 < 0) {
    return ~uVar1;
  }
  if (param_1 < 0) {
    param_1 = (intptr_t)_this - *(int *)(*(int *)_this + 4);
  }
  return uVar1 + param_1;
}



unsigned int __fastcall
Token_AddOrUpdate(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4,
                 unsigned int param_5)

{
  DWORD DVar1;
  int iVar2;
  unsigned int *puVar3;
  unsigned int unaff_EBX;
  unsigned int *puVar4;
  int *piVar5;
  unsigned int unaff_retaddr;
  unsigned int uVar6;
  unsigned int uVar7;
  
  DVar1 = GetTickCount();
  piVar5 = (int *)&pTokenListHead;
  puVar3 = (unsigned int*)pTokenListHead;
  puVar4 = (unsigned int*)pTokenListHead;
  if (pTokenListHead != (unsigned int *)0x0) {
    do {
      if (DVar1 - puVar3[2] < 0x1d4c1) {
        piVar5 = puVar3 + 0xc;
      }
      else {
        *piVar5 = puVar3[0xc];
        FOG_CrashDumpThread(0x96,0);
        puVar4 = (unsigned int*)pTokenListHead;
      }
      puVar3 = (unsigned int *)*piVar5;
    } while (puVar3 != (unsigned int *)0x0);
    for (; puVar4 != (unsigned int *)0x0; puVar4 = (unsigned int *)puVar4[0xc]) {
      iVar2 = SStrCmp((char*)puVar4 + 3,param_1,0x7fffffff);
      if (iVar2 == 0) goto LAB_1000657b;
    }
  }
  uVar7 = 0;
  uVar6 = 0x34;
  puVar3 = (unsigned int *)FOG_CrashDeadlockDetected(0x34,0);
  if (puVar3 != (unsigned int *)0x0) {
    puVar4 = puVar3;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    puVar3[1] = param_3;
    *puVar3 = unaff_retaddr;
    DVar1 = GetTickCount();
    puVar3[2] = DVar1;
    SStrCopy((char*)puVar3 + 3,(char*)param_1,0x10);
    SStrCopy((char*)puVar3 + 7,(char*)uVar7,0x10);
    puVar3[0xb] = uVar6;
    puVar3[0xc] = (uintptr_t)pTokenListHead;
    pTokenListHead = puVar3;
    return 1;
  }
  FOG_SetLogPrefix(s_ptToken_10020d8c,s_C__D2_Source_D2Server_PlayerToke_10020d98,0x35);
  _exit_wrapper(0xffffffff);
  puVar4 = (unsigned int *)0x0;
LAB_1000657b:
  puVar4[1] = param_5;
  *puVar4 = param_4;
  DVar1 = GetTickCount();
  puVar4[2] = DVar1;
  SStrCopy((char*)puVar4 + 7,(char*)param_2,0x10);
  puVar4[0xb] = unaff_EBX;
  return 1;
}



void Perf_SnapshotCounter(void)

{
  QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount_10023198);
  return;
}



void __fastcall
Server_SendCharCreateRequest(char *param_1,unsigned char param_2,char *param_3,unsigned int param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  unsigned char uStack_1c;
  unsigned char uStack_1b;
  char acStack_1a [4];
  unsigned int uStack_16;
  char acStack_12 [18];
  
  uStack_16 = param_4;
  uVar2 = 0xffffffff;
  do {
    pcVar4 = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  uStack_1c = 0xe;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = acStack_1a;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pcVar5 = *(unsigned int *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  uVar2 = 0xffffffff;
  do {
    pcVar4 = param_3;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_3 + 1;
    cVar1 = *param_3;
    param_3 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = acStack_1a + 8;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pcVar5 = *(unsigned int *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  uStack_1b = param_2;
  FOG_Send(ghGameServer,&uStack_1c,0x1a);
  return;
}



unsigned int MCP_ConnectToServer(void)

{
  int iVar1;
  unsigned int extraout_ECX;
  
  iVar1 = SRegLoadString((char*)0, (char*)0, 0, (char*)0, 0);
  if (iVar1 == 0) {
    SRegSaveString((char*)0, (char*)0, 0, (char*)0, 0);
    return 0;
  }
  ghGameServer = (void*)(intptr_t)FOG_ReallocPool();
  FOG_GetDiskInfo();
  FOG_ExceptionHandler((intptr_t)ghGameServer);
  FOG_EnterCriticalSection((intptr_t)ghGameServer,&uStack00000000,1);
  MCP_SendType1((int3)extraout_ECX);
  D2NET_10018((intptr_t)&g_NetEventCallback);
  Console_WriteGraphDisplay(1,(byte *)s__SERVER__Connected_to_MCP_at__s_1001ed80);
  return 1;
}



void __fastcall GameDataPool_FreeBackingArray(int param_1)

{
  void **ppvVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  uint uStack_14;
  void *pvStack_c;
  unsigned char *puStack_8;
  unsigned int uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = (unsigned char*)&LAB_1001a62b;
  pvStack_c = pExceptionList;
  iVar3 = 0;
  uStack_14 = 0;
  pExceptionList = &pvStack_c;
  ppvVar1 = &pvStack_c;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      piVar4 = (int *)(*(int *)(param_1 + 8) + iVar3);
      uStack_4 = 0;
      while (0 < piVar4[2]) {
        piVar2 = (int *)GameData_PoolAddOffset(piVar4[2],*piVar4);
        GameData_ListNode_Detach2(piVar2);
      }
      uStack_4 = 0xffffffff;
      GameData_ListNode_Detach2(piVar4 + 1);
      uStack_14 = uStack_14 + 1;
      iVar3 = iVar3 + 0xc;
      ppvVar1 = (void**)pExceptionList;
    } while (uStack_14 < *(uint *)(param_1 + 4));
  }
  pExceptionList = ppvVar1;
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  pExceptionList = pvStack_c;
  return;
}



unsigned int Console_DisplayHelp(void)

{
  char cVar1;
  byte bVar2;
  LRESULT LVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  byte *pbVar11;
  byte abStack_100 [256];
  
  if (ghCmdDialog != (HWND)0x0) {
    LVar3 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    if (0x40 < LVar3) {
      SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x182,0,0);
    }
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x180,0,0x100207b4);
    LVar3 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x186,LVar3 - 1,0);
  }
  pcVar7 = s_Display_Console_Commands_1001f15c;
  do {
    uVar4 = 0xffffffff;
    pcVar9 = (char*)&DAT_100207ac;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = abStack_100;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7 + -0x104;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = abStack_100;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = (char*)&DAT_100207a8;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = abStack_100;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = abStack_100;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    Console_WriteGraphDisplay(0,abStack_100);
    pcVar7 = pcVar7 + 0x204;
    if ((char *)0x1002037f < pcVar7) {
      return 1;
    }
  } while( true );
}



void Console_DestroyGraphDisplay(void)

{
  SendMessageA(ghConsoleDlg,0x10,0,0);
  return;
}



void __fastcall GameData_ListNode_Detach(int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = param_1[1];
    if ((intptr_t)uVar2 < 0) {
      piVar3 = (int *)~uVar2;
    }
    else {
      piVar3 = (int *)((intptr_t)param_1 + (uVar2 - *(int *)(iVar1 + 4)));
    }
    *piVar3 = iVar1;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}



void CharServer_CloseAllConnections(void)

{
  int *piVar1;
  
  piVar1 = (int*)&sCharServerConns;
  do {
    if (*piVar1 != 0) {
      FOG_Noop();
    }
    *piVar1 = 0;
    piVar1 = piVar1 + 0xb;
  } while ((intptr_t)piVar1 < 0x1002313c);
  return;
}



void __thiscall GameData_PoolResize(void *_this,uint dwNewCapacity)

{
  unsigned int *puVar1;
  uint uVar2;
  int iVar3;
  unsigned int uVar4;
  uint uVar5;
  uint uVar6;
  unsigned int *puVar7;
  int iVar8;
  
  if (*(uint *)((intptr_t)_this + 4) < dwNewCapacity) {
    if (*(uint *)_this < dwNewCapacity) {
      uVar5 = *(uint *)((intptr_t)_this + 0xc);
      if (uVar5 == 0) {
        if (dwNewCapacity < 0x15) {
          uVar6 = dwNewCapacity - 1 & dwNewCapacity;
          uVar5 = dwNewCapacity;
          while (uVar2 = uVar6, uVar2 != 0) {
            uVar5 = uVar2;
            uVar6 = uVar2 - 1 & uVar2;
          }
          if (uVar5 == 0) {
            uVar5 = 1;
          }
        }
        else {
          *(unsigned int *)((intptr_t)_this + 0xc) = 0x15;
          uVar5 = 0x15;
        }
      }
      uVar6 = dwNewCapacity;
      if (dwNewCapacity % uVar5 != 0) {
        uVar6 = (uVar5 - dwNewCapacity % uVar5) + dwNewCapacity;
      }
      puVar1 = *(unsigned int **)((intptr_t)_this + 8);
      if (uVar6 < *(uint *)((intptr_t)_this + 4)) {
        puVar7 = puVar1 + uVar6 * 3;
        uVar5 = uVar6;
        do {
          GameData_ListNode_Clear(puVar7,0);
          uVar5 = uVar5 + 1;
          puVar7 = puVar7 + 3;
        } while (uVar5 < *(uint *)((intptr_t)_this + 4));
      }
      *(uint *)_this = uVar6;
      iVar3 = (intptr_t)SMemReAlloc(puVar1,uVar6 * 0xc,s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,
                          0x10);
      *(int *)((intptr_t)_this + 8) = iVar3;
      if (iVar3 == 0) {
        uVar4 = (uintptr_t)SMemAlloc(uVar6 * 0xc,s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
        *(unsigned int *)((intptr_t)_this + 8) = uVar4;
        if (puVar1 != (unsigned int *)0x0) {
          uVar5 = *(uint *)((intptr_t)_this + 4);
          if (uVar6 < *(uint *)((intptr_t)_this + 4)) {
            uVar5 = uVar6;
          }
          if (uVar5 != 0) {
            iVar3 = 0;
            puVar7 = puVar1;
            do {
              List_MoveNode((unsigned int *)(iVar3 + *(int *)((intptr_t)_this + 8)),puVar7);
              GameData_ListNode_Clear(puVar7,0);
              iVar3 = iVar3 + 0xc;
              puVar7 = puVar7 + 3;
              uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
          }
          SMemFree((void*)(puVar1),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
        }
      }
    }
    uVar5 = *(uint *)((intptr_t)_this + 4);
    if (uVar5 < dwNewCapacity) {
      iVar8 = uVar5 * 0xc;
      iVar3 = dwNewCapacity - uVar5;
      do {
        List_FreeNode((unsigned int *)(iVar8 + *(int *)((intptr_t)_this + 8)));
        iVar8 = iVar8 + 0xc;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(uint *)((intptr_t)_this + 4) = dwNewCapacity;
      return;
    }
  }
  else if (dwNewCapacity < *(uint *)((intptr_t)_this + 4)) {
    iVar3 = dwNewCapacity * 0xc;
    uVar5 = dwNewCapacity;
    do {
      GameDataPool_ClearEntry((int *)(iVar3 + *(int *)((intptr_t)_this + 8)));
      uVar5 = uVar5 + 1;
      iVar3 = iVar3 + 0xc;
    } while (uVar5 < *(uint *)((intptr_t)_this + 4));
  }
  *(uint *)((intptr_t)_this + 4) = dwNewCapacity;
  return;
}
#if 0 /* CRT: DllRegisterServer */



#if 0
void __fastcall DllRegisterServer(int gameMCPId,int gameToken,int serverToken)

{
  unsigned char auStack_10 [5];
  int iStack_b;
  
                    // 0x12c1  10001  
  Console_WriteGraphDisplay(0,(byte *)MCP___GTM_CREATEGAME__M_10020dc8);
  auStack_10[0] = 6;
  iStack_b = serverToken;
  FOG_Send(ghGameServer,auStack_10,0xd);
  return;
}
#endif /* DllRegisterServer */

#endif




int Server_MainEntry(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)

{
  int iVar1;
  HANDLE pvVar2;
  BOOL BVar3;
  HWND pHVar4;
  unsigned int *puVar5;
  BOOL BVar6;
  struct tagMSG *ptVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  struct tagMSG tStack_1c;
  
  g_hMainInstance = hInstance;
  FOG_CharToUpper();
  Server_OpenMPQArchives();
  puVar5 = &g_InitFuncTableStart;
  do {
    if ((void *)*puVar5 != (void *)0x0) {
      ((void (*)(void))*puVar5)();
    }
    puVar5 = puVar5 + 1;
  } while (puVar5 < &g_InitFuncTableEnd);
  ghConsoleDlg = CreateDialogParamA(g_hMainInstance,(LPCSTR)0x66,(HWND)0x0,(DLGPROC)&LAB_100010f0,0)
  ;
  ShowWindow(ghConsoleDlg,nCmdShow);
  UpdateWindow(ghConsoleDlg);
  FOG_InitErrorMgr();
  if (bServerRunning != 0) {
    Bnclient_LoadRunGame();
  }
  ReturnZero();
  iVar1 = D2Lang_Initialize();
  if (iVar1 != 0) {
    uVar9 = 0;
    uVar8 = 1;
    iVar1 = ReturnZero();
    STATES_CheckStateMaskStayDeath((void*)iVar1,uVar8,uVar9);
    SERVER_Initialize(0,0);
    SERVER_SetHackListEnabled(1);
    D2GAME_10046();
    if (bServerRunning != 0) {
      MCP_ConnectToServer();
      CharServer_ConnectAll(ghConsoleDlg);
      D2GAME_10023(&pGameEngineFuncTable);
    }
    D2GAME_10002(&g_GameEngineData1,&g_GameEngineData2);
    stStartTime = _ftime64(&stStartTime);
    D2GAME_10039();
    if (bServerRunning != 0) {
      pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                            (LPTHREAD_START_ROUTINE)&lpStartAddress_1000133e,(LPVOID)0x0,0,
                            (LPDWORD)&tStack_1c.wParam);
      CloseHandle(pvVar2);
    }
    iVar1 = FOG_SetExceptionFilter();
    for (iVar1 = *(int *)(iVar1 + 0x28); iVar1 != 0; iVar1 = iVar1 + -1) {
      InterlockedIncrement((LONG *)&nActiveWorkerThreads);
      pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                            (LPTHREAD_START_ROUTINE)&lpStartAddress_10001104,(LPVOID)0x0,0,
                            (LPDWORD)&nCmdShow);
      if (pvVar2 == (HANDLE)0x0) {
        InterlockedDecrement((LONG *)&nActiveWorkerThreads);
      }
      else {
        CloseHandle(pvVar2);
      }
    }
    Perf_InitSystem();
    Perf_InitFrameTimer(2);
    Perf_SnapshotCounter();
    Console_WriteGraphDisplay(1,(byte *)s__SERVER__Finished_Loading____100211fc);
    BVar6 = 1;
    tStack_1c.wParam = 0;
    nGameCount = 0;
    nPlayerCount = 0;
    do {
      if (bShutdownFlag != 0) break;
      BVar3 = PeekMessageA(&tStack_1c,(HWND)0x0,0,0,0);
      if (BVar3 == 0) {
        Sleep(1);
      }
      else {
        BVar6 = GetMessageA(&tStack_1c,(HWND)0x0,0,0);
        ptVar7 = &tStack_1c;
        pHVar4 = (HWND)Console_GetMainDialogHandle();
        BVar3 = IsDialogMessageA(pHVar4,ptVar7);
        if (BVar3 != 0) {
          ptVar7 = &tStack_1c;
          pHVar4 = (HWND)Console_GetCmdDialogHandle();
          BVar3 = IsDialogMessageA(pHVar4,ptVar7);
          if (BVar3 != 0) goto LAB_10008254;
        }
        TranslateMessage(&tStack_1c);
        DispatchMessageA(&tStack_1c);
      }
LAB_10008254:
    } while (BVar6 != 0);
  }
  bShutdownFlag = 1;
  while (0 < (intptr_t)nActiveWorkerThreads) {
    Sleep(100);
  }
  bShutdownFlag = 0;
  Console_ClearGameList();
  D2GAME_10040();
  SERVER_Release();
  if (bServerRunning != 0) {
    MCP_DisconnectFromServer();
    CharServer_CloseAllConnections();
  }
  D2GAME_10050();
  STATES_CheckStateMaskExp();
  D2Lang_Uninitialize();
  D2COMMON_10983();
  Server_FreeMemory();
  return 0;
}



void __fastcall GameDataPool_DetachList(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  piVar1 = param_1 + 1;
  while (0 < param_1[2]) {
    piVar4 = (int *)(*param_1 + param_1[2]);
    if (*piVar4 != 0) {
      uVar2 = piVar4[1];
      if ((intptr_t)uVar2 < 0) {
        piVar5 = (int *)~uVar2;
      }
      else {
        piVar5 = (int *)((intptr_t)piVar4 + (uVar2 - *(int *)(*piVar4 + 4)));
      }
      *piVar5 = *piVar4;
      *(int *)(*piVar4 + 4) = piVar4[1];
      *piVar4 = 0;
      piVar4[1] = 0;
    }
  }
  iVar3 = *piVar1;
  if (iVar3 != 0) {
    uVar2 = param_1[2];
    if ((intptr_t)uVar2 < 0) {
      piVar4 = (int *)~uVar2;
    }
    else {
      piVar4 = (int *)((intptr_t)piVar1 + (uVar2 - *(int *)(iVar3 + 4)));
    }
    *piVar4 = iVar3;
    *(int *)(*piVar1 + 4) = param_1[2];
    *piVar1 = 0;
    param_1[2] = 0;
  }
  return;
}



unsigned int Server_EnumerateCharacters(void)

{
  int iVar1;
  int iVar2;
  unsigned char auStack_800 [2048];
  
  D2GAME_10012();
  iVar1 = D2GAME_10015(auStack_800,0x400);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      Server_SendCharInfo((intptr_t)&uStack00000000,(uintptr_t)(iVar2 == iVar1 + -1));
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
    return 1;
  }
  return 1;
}



void __fastcall GameData_PoolSetCount(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = (uintptr_t)puVar1;
  *param_1 = 0;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}



unsigned int __fastcall
MCP_SendCharCreateWithDedup
          (unsigned int param_1,uint param_2,unsigned int param_3,uint param_4,uint param_5,uint param_6
          )

{
  uint *puVar1;
  int iVar2;
  unsigned int uVar3;
  unsigned int extraout_ECX;
  uint extraout_EDX;
  unsigned char auStack_201 [513];
  
  if (4 < (ushort)param_2) {
    FOG_SetLogPrefix((char*)s_wClass_0x3c_NUM_PLAYERCLASS_10020e78,s_C__D2_Source_D2Server_CORE_ToMCP_10020e98,0x129)
    ;
    _exit_wrapper(0xffffffff);
    param_1 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  if ((param_6 & 4) == 0) {
    if ((DAT_100232b4 < param_5) || ((DAT_100232b4 <= param_5 && (DAT_100232b0 <= param_4))))
    goto LAB_10007008;
    puVar1 = (uint *)(&DAT_100232b8 + (param_2 & 0xffff) * 8);
  }
  else {
    if ((DAT_1002326c < param_5) || ((DAT_1002326c <= param_5 && (sMCPRecvRecord <= param_4))))
    goto LAB_10007008;
    puVar1 = &DAT_10023270 + (param_2 & 0xffff) * 2;
  }
  if ((param_5 <= puVar1[1]) && ((param_5 < puVar1[1] || (param_4 < *puVar1)))) {
    return 0;
  }
LAB_10007008:
  iVar2 = SStrCopy(auStack_201,param_1,0x200);
  uVar3 = FOG_Send(ghGameServer,&uStack00000000,iVar2 + 0x10);
  return uVar3;
}



void __fastcall GameData_PoolZeroEntry(unsigned int *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return;
}



void Server_FreeMemory(void)

{
  if (ghD2DataMPQ != (int *)0x0) {
    Archive_Close(ghD2DataMPQ);
  }
  ghD2DataMPQ = (int *)0x0;
  if (ghD2CharMPQ != (int *)0x0) {
    Archive_Close(ghD2CharMPQ);
  }
  ghD2CharMPQ = (int *)0x0;
  return;
}



void __fastcall GameData_ListNode_Detach2(int *param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = param_1[1];
    if ((intptr_t)uVar2 < 0) {
      piVar3 = (int *)~uVar2;
    }
    else {
      piVar3 = (int *)((intptr_t)param_1 + (uVar2 - *(int *)(iVar1 + 4)));
    }
    *piVar3 = iVar1;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}



unsigned int __fastcall Console_InitGraphDisplay(HWND param_1)

{
  HINSTANCE hInstance;
  HWND hWnd;
  HDC hdc;
  HPEN h;
  HGDIOBJ h_00;
  HBRUSH h_01;
  HGDIOBJ h_02;
  struct tagRECT tStack_10;
  
  hInstance = (HINSTANCE)GetWindowLongA(param_1,-6);
  if (ghConsoleDlg != nullptr) {
    return 0;
  }
  ghConsoleDlg = CreateDialogParamA(hInstance,(LPCSTR)0x67,param_1,(DLGPROC)&LAB_100012a8,0);
  if (ghConsoleDlg == nullptr) {
    return 0;
  }
  hWnd = GetDlgItem(ghConsoleDlg,0x3f2);
  GetClientRect(hWnd,&tStack_10);
  hdc = GetDC(ghConsoleDlg);
  sGraphData = CreateCompatibleDC(hdc);
  g_hGraphBrush =
       CreateCompatibleBitmap(hdc,tStack_10.right - tStack_10.left,tStack_10.bottom - tStack_10.top)
  ;
  ReleaseDC(ghConsoleDlg,hdc);
  SelectObject(sGraphData,g_hGraphBrush);
  h = CreatePen(0,1,0);
  h_00 = SelectObject(sGraphData,h);
  h_01 = CreateSolidBrush(0);
  h_02 = SelectObject(sGraphData,h_01);
  Rectangle(sGraphData,tStack_10.left,tStack_10.top,tStack_10.right,tStack_10.bottom);
  SelectObject(sGraphData,h_00);
  DeleteObject(h);
  SelectObject(sGraphData,h_02);
  DeleteObject(h_01);
  return 1;
}



void __fastcall Console_GraphDrawDataPoint(int param_1,int param_2)

{
  int right;
  int left;
  int iVar1;
  HPEN h;
  HPEN h_00;
  HPEN h_01;
  HBRUSH h_02;
  HWND hWnd;
  HGDIOBJ h_03;
  HGDIOBJ h_04;
  HDC hdc;
  int iVar2;
  struct tagPOINT tStack_18;
  struct tagRECT tStack_10;
  
  if (ghConsoleDlg != nullptr) {
    h = CreatePen(0,1,0);
    h_00 = CreatePen(0,1,0xff00);
    h_01 = CreatePen(0,1,0xff);
    h_02 = CreateSolidBrush(0);
    hWnd = GetDlgItem(ghConsoleDlg,0x3f2);
    GetClientRect(hWnd,&tStack_10);
    iVar2 = tStack_10.bottom - tStack_10.top;
    left = DAT_10023248 + tStack_10.left;
    h_03 = SelectObject(sGraphData,h_02);
    h_04 = SelectObject(sGraphData,h);
    right = left + 2;
    Rectangle(sGraphData,left,tStack_10.top,right,tStack_10.bottom);
    iVar1 = (iVar2 * param_1) / 100;
    SelectObject(sGraphData,h_00);
    MoveToEx(sGraphData,left,tStack_10.bottom - iVar1,&tStack_18);
    LineTo(sGraphData,right,tStack_10.bottom - iVar1);
    iVar1 = (iVar2 * param_2) / 600;
    SelectObject(sGraphData,h_01);
    MoveToEx(sGraphData,left,tStack_10.bottom - iVar1,&tStack_18);
    LineTo(sGraphData,right,tStack_10.bottom - iVar1);
    DAT_10023248 = DAT_10023248 + 2;
    if ((tStack_10.right - tStack_10.left) + -2 <= DAT_10023248) {
      DAT_10023248 = 0;
    }
    SelectObject(sGraphData,h_04);
    SelectObject(sGraphData,h_03);
    DeleteObject(h);
    DeleteObject(h_00);
    DeleteObject(h_01);
    DeleteObject(h_02);
    hdc = GetDC(hWnd);
    GetClientRect(hWnd,&tStack_10);
    BitBlt(hdc,tStack_10.left,tStack_10.top,tStack_10.right - tStack_10.left,
           tStack_10.bottom - tStack_10.top,sGraphData,0,0,0xcc0020);
    ReleaseDC(hWnd,hdc);
  }
  return;
}



/* DUPLICATE: Server_OpenMPQArchives */
#if 0
unsigned int Server_OpenMPQArchives(void)

{
  CHAR szModulePath [260];
  
  GetModuleFileNameA((HMODULE)0x0,szModulePath,0x104);
  ghD2DataMPQ = MPQ_OpenWithRetry(szModulePath,s_d2data_mpq_1001ed60,s_d2data_1001ed58,0,
                                  (unsigned char *)0x0);
  ghD2CharMPQ = MPQ_OpenWithRetry(szModulePath,s_d2char_mpq_1001ed48,s_d2char_1001ed40,0,
                                  (unsigned char *)0x0);
  if ((ghD2DataMPQ != (int *)0x0) && (ghD2CharMPQ != (int *)0x0)) {
    return 1;
  }
  return 0;
}
#endif




int ReturnZero_NoOp(void)

{
  return 0;
}



/* DUPLICATE: Server_FreeMemory */
#if 0
void Server_FreeMemory(void)

{
  if (ghD2DataMPQ != (int *)0x0) {
    Archive_Close(ghD2DataMPQ);
  }
  ghD2DataMPQ = (int *)0x0;
  if (ghD2CharMPQ != (int *)0x0) {
    Archive_Close(ghD2CharMPQ);
  }
  ghD2CharMPQ = (int *)0x0;
  return;
}
#endif




/* DUPLICATE: Memory_SafeDelete */
#if 0
void __cdecl Memory_SafeDelete(int nMemory)

{
  if (nMemory != 0) {
    SMemFree((void*)(nMemory),s_delete_1001ed70,0xffffffff,0);
  }
  return;
}
#endif




/* DUPLICATE: MCP_ConnectToServer */
#if 0
unsigned int MCP_ConnectToServer(void)

{
  int iVar1;
  unsigned int extraout_ECX;
  
  iVar1 = SRegLoadString((char*)0, (char*)0, 0, (char*)0, 0);
  if (iVar1 == 0) {
    SRegSaveString((char*)0, (char*)0, 0, (char*)0, 0);
    return 0;
  }
  ghGameServer = FOG_ReallocPool();
  FOG_GetDiskInfo();
  FOG_ExceptionHandler(ghGameServer);
  FOG_EnterCriticalSection(ghGameServer,&uStack00000000,1);
  MCP_SendType1((int3)extraout_ECX);
  D2NET_10018(&g_NetEventCallback);
  Console_WriteGraphDisplay(1,(byte *)s__SERVER__Connected_to_MCP_at__s_1001ed80);
  return 1;
}
#endif




/* DUPLICATE: Server_GameTick */
#if 0
unsigned int Server_GameTick(void)

{
  DWORD DVar1;
  int iVar2;
  unsigned int extraout_ECX;
  
                    // Server_GameTick: Runs every 60 seconds (60000ms). If MCP disconnected, tries
                    // to reconnect via Ordinal_10047/10056/10052/10050 sequence. Sets bMcpConnected
                    // on success.
  DVar1 = GetTickCount();
  if (dwLastTickCount == 0) {
    dwLastTickCount = DVar1;
  }
  if (59999 < DVar1 - dwLastTickCount) {
    dwLastTickCount = DVar1;
    iVar2 = FOG_InitTimers(0);
    if (iVar2 != 0) {
      bMcpConnected = 1;
      return 1;
    }
    if (bMcpConnected != 0) {
      bMcpConnected = 0;
    }
    FOG_Noop();
    iVar2 = SRegLoadString((char*)0, (char*)0, 0, (char*)0, 0);
    if (iVar2 == 0) {
      SRegSaveString((char*)0, (char*)0, 0, (char*)0, 0);
      return 1;
    }
    ghGameServer = FOG_ReallocPool();
    FOG_GetDiskInfo();
    FOG_ExceptionHandler(ghGameServer);
    FOG_EnterCriticalSection(ghGameServer,&uStack00000000,1);
    MCP_SendType1((int3)extraout_ECX);
    D2NET_10018(&g_NetEventCallback);
    Console_WriteGraphDisplay(1,(byte *)s__SERVER__Connected_to_MCP_at__s_1001ed80);
  }
  return 1;
}
#endif




/* DUPLICATE: MCP_DisconnectFromServer */
#if 0
void MCP_DisconnectFromServer(void)

{
  D2NET_10018(0);
  FOG_Noop();
  return;
}
#endif




void MCP_LogIPAndLeave(void)

{
  FOG_GetHostIPAddress();
  Console_WriteGraphDisplay(1,(byte *)s__SERVER__Hack_listing_IP__s_1001eddc);
  Server_SendPlayerLeave();
  return;
}



// D2Server.Bnclient_LoadRunGame (10001ad0) - Loads Bnclient.dll via LoadLibraryA, retrieves the
// "QueryInterface" export, and stores the interface pointer into gpBnclientInterface. Gated by
// g_hInstance check. This is the Bnclient (battle.net client) bootstrap used by the beta-era
// server.

/* DUPLICATE: Bnclient_LoadRunGame */
#if 0
unsigned int Bnclient_LoadRunGame(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  CHAR szErrorMsg [100];
  
  if (gpBnclientInterface != 0) {
    return 0;
  }
  hModule = LoadLibraryA(s_Bnclient_dll_1001ee8c);
  if (hModule == (HMODULE)0x0) {
    GetLastError();
    _vsprintf_l(szErrorMsg,(byte *)s_Cannot_load_Bnclient_dll__Error___1001ee60);
    MessageBoxA((HWND)0x0,szErrorMsg,s_D2Multi_1001ee54,0x10);
    return 0;
  }
  pFVar1 = GetProcAddress(hModule,s_QueryInterface_1001ee40);
  if (pFVar1 == (FARPROC)0x0) {
    GetLastError();
    _vsprintf_l(szErrorMsg,(byte *)s_Unable_to_QueryInterface_for_Bnc_1001ee00);
    MessageBoxA((HWND)0x0,szErrorMsg,s_D2Multi_1001ee54,0x10);
    return 0;
  }
  gpBnclientInterface = (*pFVar1)();
  return 1;
}
#endif




int __fastcall CharServer_RoundRobinDispatch(unsigned int pData,unsigned int nDataSize)

{
  int nSendResult;
  uint nServerIdx;
  int nAttempts;
  
  nAttempts = 0;
  nServerIdx = nCharServerSelector;
  do {
    if ((&sCharServerConns)[nServerIdx * 0xb] != 0) {
      nSendResult = FOG_Send((&sCharServerConns)[nServerIdx * 0xb],pData,nDataSize);
      if (nSendResult != 0) break;
    }
    nServerIdx = (nServerIdx + 1) % 3;
    nAttempts = nAttempts + 1;
  } while (nAttempts < 3);
  nCharServerSelector = nServerIdx;
  return nAttempts < 3;
}



int CharServer_SendType1Packet(unsigned char param_1)

{
  int nSendResult;
  char *extraout_ECX;
  int nOffset;
  uint nLen;
  uint nCopyLen;
  uint nDwordCopy;
  char *extraout_EDX;
  char *extraout_EDX_00;
  char *pDest;
  char *pSrc;
  char *pDest2;
  int nAttempts;
  int dwChecksum;
  ushort *in_stack_00001034;
  uint in_stack_00001038;
  char cChar;
  byte *pByte;
  
  _alloca_probe();
  dwChecksum = 0;
  nOffset = 0;
  param_1 = 1;
  if (0 < (intptr_t)in_stack_00001038) {
    do {
      pByte = (byte *)(nOffset + (intptr_t)in_stack_00001034);
      nOffset = nOffset + 1;
      dwChecksum = (uintptr_t)*pByte + (uintptr_t)(dwChecksum < 0) + dwChecksum * 2;
    } while (nOffset < (intptr_t)in_stack_00001038);
  }
  nLen = 0xffffffff;
  pDest = extraout_ECX;
  do {
    pSrc = pDest;
    if (nLen == 0) break;
    nLen = nLen - 1;
    pSrc = pDest + 1;
    cChar = *pDest;
    pDest = pSrc;
  } while (cChar != '\0');
  nLen = ~nLen;
  pDest = pSrc + -nLen;
  pSrc = (char*)&uStack0000000f;
  for (nCopyLen = nLen >> 2; nCopyLen != 0; nCopyLen = nCopyLen - 1) {
    *(unsigned int *)pSrc = *(unsigned int *)pDest;
    pDest = pDest + 4;
    pSrc = pSrc + 4;
  }
  for (nLen = nLen & 3; nLen != 0; nLen = nLen - 1) {
    *pSrc = *pDest;
    pDest = pDest + 1;
    pSrc = pSrc + 1;
  }
  nLen = 0xffffffff;
  pDest = extraout_ECX;
  do {
    if (nLen == 0) break;
    nLen = nLen - 1;
    cChar = *pDest;
    pDest = pDest + 1;
  } while (cChar != '\0');
  nCopyLen = 0xffffffff;
  pDest = extraout_EDX;
  do {
    pSrc = pDest;
    if (nCopyLen == 0) break;
    nCopyLen = nCopyLen - 1;
    pSrc = pDest + 1;
    cChar = *pDest;
    pDest = pSrc;
  } while (cChar != '\0');
  nCopyLen = ~nCopyLen;
  pDest = (char*)&uStack0000000f + ~nLen;
  pSrc = pSrc + -nCopyLen;
  pDest2 = pDest;
  for (nDwordCopy = nCopyLen >> 2; nDwordCopy != 0; nDwordCopy = nDwordCopy - 1) {
    *(unsigned int *)pDest2 = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest2 = pDest2 + 4;
  }
  for (nCopyLen = nCopyLen & 3; nCopyLen != 0; nCopyLen = nCopyLen - 1) {
    *pDest2 = *pSrc;
    pSrc = pSrc + 1;
    pDest2 = pDest2 + 1;
  }
  nCopyLen = 0xffffffff;
  pSrc = extraout_EDX;
  do {
    if (nCopyLen == 0) break;
    nCopyLen = nCopyLen - 1;
    cChar = *pSrc;
    pSrc = pSrc + 1;
  } while (cChar != '\0');
  nOffset = ~nLen + ~nCopyLen;
  if (*in_stack_00001034 != in_stack_00001038) {
    FOG_SetLogPrefix(s___WORD___pbData____nLength_1001eec8,s_C__D2_Source_D2Server_CORE_CharS_1001eee8,0xcf
             );
    _exit_wrapper(0xffffffff);
    pDest = extraout_EDX_00;
  }
  pDest = pDest + nOffset;
  for (nLen = in_stack_00001038 >> 2; nLen != 0; nLen = nLen - 1) {
    *(unsigned int *)pDest = *(unsigned int *)in_stack_00001034;
    in_stack_00001034 = in_stack_00001034 + 2;
    pDest = pDest + 4;
  }
  for (nLen = in_stack_00001038 & 3; nLen != 0; nLen = nLen - 1) {
    *pDest = (char)*in_stack_00001034;
    in_stack_00001034 = (ushort *)((intptr_t)in_stack_00001034 + 1);
    pDest = pDest + 1;
  }
  nAttempts = 0;
  nLen = nCharServerSelector;
  do {
    if ((&sCharServerConns)[nLen * 0xb] != 0) {
      nSendResult = FOG_Send((&sCharServerConns)[nLen * 0xb],&param_1,
                              nOffset + 9 + in_stack_00001038);
      if (nSendResult != 0) break;
    }
    nLen = (nLen + 1) % 3;
    nAttempts = nAttempts + 1;
  } while (nAttempts < 3);
  nCharServerSelector = nLen;
  return nAttempts < 3;
}



/* DUPLICATE: CharServer_SendType2Packet */
#if 0
int CharServer_SendType2Packet(unsigned int param_1,unsigned char param_2)

{
  int nSendResult;
  char *extraout_ECX;
  uint nStrLen;
  uint nNameLen;
  uint nCopyLen;
  char *extraout_EDX;
  int nAttempts;
  char *pDest;
  char *pSrc;
  unsigned long long uExitResult;
  unsigned int uStack00000009;
  int dwChecksum;
  ushort *in_stack_0000103c;
  uint in_stack_00001040;
  char cChar;
  byte *pByte;
  
  _alloca_probe();
  param_2 = 2;
  uStack00000009 = FOG_Log();
  dwChecksum = 0;
  nAttempts = 0;
  if (0 < (intptr_t)in_stack_00001040) {
    do {
      pByte = (byte *)(nAttempts + (intptr_t)in_stack_0000103c);
      nAttempts = nAttempts + 1;
      dwChecksum = (uintptr_t)*pByte + (uintptr_t)(dwChecksum < 0) + dwChecksum * 2;
    } while (nAttempts < (intptr_t)in_stack_00001040);
  }
  nStrLen = 0xffffffff;
  pDest = extraout_ECX;
  do {
    pSrc = pDest;
    if (nStrLen == 0) break;
    nStrLen = nStrLen - 1;
    pSrc = pDest + 1;
    cChar = *pDest;
    pDest = pSrc;
  } while (cChar != '\0');
  nStrLen = ~nStrLen;
  pDest = pSrc + -nStrLen;
  pSrc = &uStack0000000f;
  for (nNameLen = nStrLen >> 2; nNameLen != 0; nNameLen = nNameLen - 1) {
    *(unsigned int *)pSrc = *(unsigned int *)pDest;
    pDest = pDest + 4;
    pSrc = pSrc + 4;
  }
  for (nStrLen = nStrLen & 3; nStrLen != 0; nStrLen = nStrLen - 1) {
    *pSrc = *pDest;
    pDest = pDest + 1;
    pSrc = pSrc + 1;
  }
  nStrLen = 0xffffffff;
  pDest = extraout_ECX;
  do {
    if (nStrLen == 0) break;
    nStrLen = nStrLen - 1;
    cChar = *pDest;
    pDest = pDest + 1;
  } while (cChar != '\0');
  nNameLen = 0xffffffff;
  pDest = extraout_EDX;
  do {
    pSrc = pDest;
    if (nNameLen == 0) break;
    nNameLen = nNameLen - 1;
    pSrc = pDest + 1;
    cChar = *pDest;
    pDest = pSrc;
  } while (cChar != '\0');
  nNameLen = ~nNameLen;
  pDest = pSrc + -nNameLen;
  pSrc = &uStack0000000f + ~nStrLen;
  for (nCopyLen = nNameLen >> 2; nCopyLen != 0; nCopyLen = nCopyLen - 1) {
    *(unsigned int *)pSrc = *(unsigned int *)pDest;
    pDest = pDest + 4;
    pSrc = pSrc + 4;
  }
  for (nNameLen = nNameLen & 3; nNameLen != 0; nNameLen = nNameLen - 1) {
    *pSrc = *pDest;
    pDest = pDest + 1;
    pSrc = pSrc + 1;
  }
  nNameLen = 0xffffffff;
  pDest = extraout_EDX;
  do {
    if (nNameLen == 0) break;
    nNameLen = nNameLen - 1;
    cChar = *pDest;
    pDest = pDest + 1;
  } while (cChar != '\0');
  nNameLen = ~nNameLen;
  if (*in_stack_0000103c != in_stack_00001040) {
    FOG_SetLogPrefix(s___WORD___pbData____nLength_1001eec8,s_C__D2_Source_D2Server_CORE_CharS_1001eee8,0xf8
             );
    uExitResult = _exit_wrapper(0xffffffff);
    in_stack_00001040 = (uintptr_t)((ulonglong)uExitResult >> 0x20);
    nNameLen = (uintptr_t)uExitResult;
  }
  pDest = &uStack0000000f + ~nStrLen + nNameLen;
  for (nCopyLen = in_stack_00001040 >> 2; nCopyLen != 0; nCopyLen = nCopyLen - 1) {
    *(unsigned int *)pDest = *(unsigned int *)in_stack_0000103c;
    in_stack_0000103c = in_stack_0000103c + 2;
    pDest = pDest + 4;
  }
  for (nCopyLen = in_stack_00001040 & 3; nCopyLen != 0; nCopyLen = nCopyLen - 1) {
    *pDest = (char)*in_stack_0000103c;
    in_stack_0000103c = (ushort *)((intptr_t)in_stack_0000103c + 1);
    pDest = pDest + 1;
  }
  nAttempts = 0;
  nCopyLen = nCharServerSelector;
  do {
    if ((&sCharServerConns)[nCopyLen * 0xb] != 0) {
      nSendResult = FOG_Send((&sCharServerConns)[nCopyLen * 0xb],&param_2,
                              ~nStrLen + 0xd + nNameLen + in_stack_00001040);
      if (nSendResult != 0) break;
    }
    nCopyLen = (nCopyLen + 1) % 3;
    nAttempts = nAttempts + 1;
  } while (nAttempts < 3);
  nCharServerSelector = nCopyLen;
  return nAttempts < 3;
}
#endif




int __fastcall CharServer_SendGameData_v2(char *param_1,unsigned int param_2)

{
  int nSendResult;
  uint nNameLen;
  uint nServerIdx;
  int nAttempts;
  char *pSrc;
  char *pDest;
  unsigned char local_1c;
  unsigned int local_1b;
  unsigned int local_17;
  char local_13 [19];
  char cChar;
  
  nNameLen = 0xffffffff;
  pSrc = param_1;
  do {
    pDest = pSrc;
    if (nNameLen == 0) break;
    nNameLen = nNameLen - 1;
    pDest = pSrc + 1;
    cChar = *pSrc;
    pSrc = pDest;
  } while (cChar != '\0');
  nNameLen = ~nNameLen;
  local_1c = 3;
  local_1b = 1;
  pSrc = pDest + -nNameLen;
  pDest = local_13;
  for (nServerIdx = nNameLen >> 2; nServerIdx != 0; nServerIdx = nServerIdx - 1) {
    *(unsigned int *)pDest = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest = pDest + 4;
  }
  for (nNameLen = nNameLen & 3; nNameLen != 0; nNameLen = nNameLen - 1) {
    *pDest = *pSrc;
    pSrc = pSrc + 1;
    pDest = pDest + 1;
  }
  nNameLen = 0xffffffff;
  do {
    if (nNameLen == 0) break;
    nNameLen = nNameLen - 1;
    cChar = *param_1;
    param_1 = param_1 + 1;
  } while (cChar != '\0');
  nAttempts = 0;
  nServerIdx = nCharServerSelector;
  local_17 = param_2;
  do {
    if ((&sCharServerConns)[nServerIdx * 0xb] != 0) {
      nSendResult = FOG_Send((&sCharServerConns)[nServerIdx * 0xb],&local_1c,~nNameLen + 9);
      if (nSendResult != 0) break;
    }
    nServerIdx = (nServerIdx + 1) % 3;
    nAttempts = nAttempts + 1;
  } while (nAttempts < 3);
  nCharServerSelector = nServerIdx;
  return nAttempts < 3;
}



int __fastcall CharServer_DispatchPacket5(char *szServerName,unsigned int packetData)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  unsigned char bPacketType;
  unsigned int dwExtraData;
  char szNameCopy [19];
  
  uVar3 = 0xffffffff;
  pcVar6 = szServerName;
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  bPacketType = 5;
  pcVar6 = pcVar7 + -uVar3;
  pcVar7 = szNameCopy;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pcVar7 = *(unsigned int *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *szServerName;
    szServerName = szServerName + 1;
  } while (cVar1 != '\0');
  iVar5 = 0;
  uVar4 = nCharServerSelector;
  dwExtraData = packetData;
  do {
    if ((&sCharServerConns)[uVar4 * 0xb] != 0) {
      iVar2 = FOG_Send((&sCharServerConns)[uVar4 * 0xb],&bPacketType,~uVar3 + 5);
      if (iVar2 != 0) break;
    }
    uVar4 = (uVar4 + 1) % 3;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  nCharServerSelector = uVar4;
  return iVar5 < 3;
}



int __fastcall
CharServer_DispatchPacket4(char *szServerName,unsigned short wGameToken,unsigned int dwAdditionalData)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  unsigned char bPacketType;
  unsigned short wGameTokenCopy;
  unsigned int dwAdditionalDataCopy;
  char szNameCopy [17];
  
  dwAdditionalDataCopy = dwAdditionalData;
  uVar3 = 0xffffffff;
  pcVar6 = szServerName;
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  bPacketType = 4;
  pcVar6 = pcVar7 + -uVar3;
  pcVar7 = szNameCopy;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pcVar7 = *(unsigned int *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *szServerName;
    szServerName = szServerName + 1;
  } while (cVar1 != '\0');
  iVar5 = 0;
  uVar4 = nCharServerSelector;
  wGameTokenCopy = wGameToken;
  do {
    if ((&sCharServerConns)[uVar4 * 0xb] != 0) {
      iVar2 = FOG_Send((&sCharServerConns)[uVar4 * 0xb],&bPacketType,~uVar3 + 7);
      if (iVar2 != 0) break;
    }
    uVar4 = (uVar4 + 1) % 3;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  nCharServerSelector = uVar4;
  return iVar5 < 3;
}



int __fastcall CharServer_SendType7Packet_v2(char *szServerName)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  unsigned char bPacketType;
  char szNameCopy [19];
  
  uVar3 = 0xffffffff;
  pcVar6 = szServerName;
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  bPacketType = 7;
  pcVar6 = pcVar7 + -uVar3;
  pcVar7 = szNameCopy;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pcVar7 = *(unsigned int *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *szServerName;
    szServerName = szServerName + 1;
  } while (cVar1 != '\0');
  iVar5 = 0;
  uVar4 = nCharServerSelector;
  do {
    if ((&sCharServerConns)[uVar4 * 0xb] != 0) {
      iVar2 = FOG_Send((&sCharServerConns)[uVar4 * 0xb],&bPacketType,~uVar3 + 1);
      if (iVar2 != 0) break;
    }
    uVar4 = (uVar4 + 1) % 3;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  nCharServerSelector = uVar4;
  return iVar5 < 3;
}



unsigned int CharServer_InitializeConnections(void)

{
  int iVar1;
  unsigned int uVar2;
  DWORD DVar3;
  uint uVar4;
  char *pServerConfig;
  unsigned char szRegKey [256];
  unsigned char auStack_100 [256];
  int bConnected;
  
  bConnected = false;
  pServerConfig = (char*)&sCharServerConnsStatus;
  do {
    if ((intptr_t)pServerConfig < 0x100230bd) {
      SStrCopy((char*)0, (char*)0, 0);
    }
    else {
      SStrPrintf((char*)szRegKey, 0x100, (char*)0);
    }
    iVar1 = SRegLoadString(s_Diablo_II_1001edc8, (char*)szRegKey, 0, (char*)0, 0);
    if (iVar1 == 0) {
      SRegSaveString(s_Diablo_II_1001edc8, (char*)0, 0, (char*)0, 0);
joined_r0x100025ce:
      if (pServerConfig == &sCharServerConnsStatus) {
        return 0;
      }
    }
    else {
      if ((pServerConfig == (char *)0x0) || (*pServerConfig == '0')) goto joined_r0x100025ce;
      Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Connecting_to_1001efc4);
    }
    pServerConfig = pServerConfig + 0x2c;
  } while ((intptr_t)pServerConfig < 0x10023140);
  while( true ) {
    pServerConfig = (char*)&sCharServerConnsStatus;
    do {
      if ((pServerConfig != (char *)0x0) && (*pServerConfig != '0')) {
        _vsprintf_l((char*)auStack_100,(byte *)Char_Server___d_1001efa0);
        uVar2 = FOG_ReallocPool();
        *(unsigned int *)(pServerConfig + -4) = uVar2;
        FOG_GetDiskInfo();
        FOG_ExceptionHandler(*(unsigned int *)(pServerConfig + -4));
        FOG_EnterCriticalSection(*(unsigned int *)(pServerConfig + -4),&uStack00000000,1);
        iVar1 = FOG_InitTimers(*(unsigned int *)(pServerConfig + -4));
        if (iVar1 != 0) {
          Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Connected_to_C_1001ef5c);
          bConnected = true;
        }
      }
      pServerConfig = pServerConfig + 0x2c;
    } while ((intptr_t)pServerConfig < 0x10023140);
    if (bConnected) break;
    Sleep(100);
  }
  DVar3 = GetTickCount();
  _set_ptd_field(DVar3);
  uVar4 = _rand();
  nCharServerSelector = uVar4 % 3;
  do {
    nCharServerSelector = (nCharServerSelector + 1) % 3;
    if (nCharServerSelector == uVar4 % 3) break;
  } while ((&sCharServerConns)[nCharServerSelector * 0xb] == 0);
  Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Chose_Primary_1001ef18);
  return 1;
}



/* DUPLICATE: CharServer_ConnectAll */
#if 0
unsigned int __fastcall CharServer_ConnectAll(HWND hWnd)

{
  HANDLE hHandle;
  DWORD DVar1;
  BOOL BVar2;
  int iVar3;
  BOOL BVar4;
  char *pcVar5;
  unsigned int dwAnyConnected;
  DWORD dwThreadId;
  struct tagMSG msg;
  
  dwAnyConnected = 0;
  BVar4 = 1;
  hHandle = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                         (LPTHREAD_START_ROUTINE)&lpStartAddress_1000113b,(LPVOID)0x0,0,&dwThreadId)
  ;
  do {
    DVar1 = WaitForSingleObject(hHandle,0);
    if (DVar1 == 0) break;
    BVar2 = PeekMessageA(&msg,(HWND)0x0,0,0,0);
    if (BVar2 == 0) {
      Sleep(10);
    }
    else {
      BVar4 = GetMessageA(&msg,(HWND)0x0,0,0);
      BVar2 = IsDialogMessageA(hWnd,&msg);
      if (BVar2 == 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
      }
    }
  } while (BVar4 != 0);
  pcVar5 = &sCharServerConnsStatus;
  do {
    if ((pcVar5 != (char *)0x0) && (*pcVar5 != '0')) {
      iVar3 = FOG_InitTimers(*(unsigned int *)(pcVar5 + -4));
      if (iVar3 != 0) {
        dwAnyConnected = 1;
      }
    }
    pcVar5 = pcVar5 + 0x2c;
  } while ((intptr_t)pcVar5 < 0x10023140);
  return dwAnyConnected;
}
#endif




/* DUPLICATE: CharServer_HeartbeatCheck */
#if 0
unsigned int CharServer_HeartbeatCheck(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  DWORD DVar4;
  uint uVar5;
  int iVar6;
  unsigned int uVar7;
  int *piVar8;
  unsigned int uVar9;
  char *pcVar10;
  int *piVar11;
  unsigned char uStack_101;
  unsigned char auStack_100 [256];
  
  uVar7 = 0;
  iVar2 = _ftime64((int *)0x0);
  if (DAT_1002313c == 0) {
    DAT_1002313c = iVar2;
  }
  if ((uintptr_t)(iVar2 - DAT_1002313c) < 0x3c) {
    return 1;
  }
  iVar6 = 0;
  piVar8 = &sCharServerConns;
  DAT_1002313c = iVar2;
  do {
    piVar1 = piVar8 + 1;
    if (((char)piVar8[1] != '\0') && ((char)piVar8[1] != '0')) {
      iVar2 = FOG_InitTimers(*piVar8);
      if (iVar2 == 0) {
        FOG_Noop();
        *piVar8 = 0;
        uStack_101 = 5;
        if ((HANDLE)piVar8[10] == (HANDLE)0x0) {
          pcVar10 = s__CHARACTER_SERVER__Lost_connecti_1001f024;
          uVar9 = 1;
          piVar11 = piVar1;
          Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Lost_connecti_1001f024);
          SStrPrintf(auStack_100,0x100,Char_Server___d_1001efa0,iVar6,uVar9,pcVar10,
                     piVar11);
          iVar2 = FOG_ReallocPool();
          *piVar8 = iVar2;
          iVar2 = FOG_Noop3(iVar2);
          piVar8[10] = iVar2;
          pcVar10 = s__CHARACTER_SERVER__Connecting_to_1001efc4;
LAB_10002a72:
          Console_WriteGraphDisplay(1,(byte *)pcVar10);
        }
        else {
          DVar4 = WaitForSingleObject((HANDLE)piVar8[10],0);
          if (DVar4 != 0x102) {
            CloseHandle((HANDLE)piVar8[10]);
            piVar8[10] = 0;
            if (*piVar8 != 0) {
              FOG_EnterCriticalSection(*piVar8,&uStack_101,1);
              pcVar10 = s__CHARACTER_SERVER__Connected_to_C_1001ef5c;
              goto LAB_10002a72;
            }
            SStrPrintf(auStack_100,0x100,Char_Server___d_1001efa0,iVar6);
            iVar2 = FOG_ReallocPool();
            *piVar8 = iVar2;
            iVar2 = FOG_Noop3(iVar2);
            piVar8[10] = iVar2;
          }
        }
      }
      else {
        uStack_101 = 8;
        iVar2 = 0;
        uVar5 = nCharServerSelector;
        do {
          if ((&sCharServerConns)[uVar5 * 0xb] != 0) {
            iVar3 = FOG_Send((&sCharServerConns)[uVar5 * 0xb],&uStack_101,1);
            if (iVar3 != 0) break;
          }
          uVar5 = (uVar5 + 1) % 3;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 3);
        uVar7 = 1;
        nCharServerSelector = uVar5;
      }
    }
    piVar8 = piVar8 + 0xb;
    iVar6 = iVar6 + 1;
    if (0x1002313b < (intptr_t)piVar8) {
      return uVar7;
    }
  } while( true );
}
#endif




unsigned int __cdecl CharServer_HeartbeatCheck_Alt(unsigned int dwPacketType)

{
  int *piVar1;
  unsigned int in_EAX;
  int iVar2;
  int iVar3;
  DWORD DVar4;
  uint uVar5;
  int iVar6;
  unsigned int unaff_EBP;
  int *piVar7;
  unsigned int uVar8;
  char *pcVar9;
  int *piVar10;
  
  iVar6 = 0;
  piVar7 = (int*)&sCharServerConns;
  DAT_1002313c = in_EAX;
  do {
    piVar1 = piVar7 + 1;
    if (((char)piVar7[1] != '\0') && ((char)piVar7[1] != '0')) {
      iVar2 = FOG_InitTimers(*piVar7);
      if (iVar2 == 0) {
        FOG_Noop();
        *piVar7 = 0;
        dwPacketType = CONCAT13(5,(undefined3)dwPacketType);
        if ((HANDLE)piVar7[10] == (HANDLE)0x0) {
          pcVar9 = s__CHARACTER_SERVER__Lost_connecti_1001f024;
          uVar8 = 1;
          piVar10 = piVar1;
          Console_WriteGraphDisplay(1,(byte *)s__CHARACTER_SERVER__Lost_connecti_1001f024);
          SStrPrintf((char*)&uStack00000008,0x100,Char_Server___d_1001efa0,iVar6,uVar8,
                     pcVar9,piVar10);
          iVar2 = FOG_ReallocPool();
          *piVar7 = iVar2;
          iVar2 = FOG_Noop3(iVar2);
          piVar7[10] = iVar2;
          pcVar9 = s__CHARACTER_SERVER__Connecting_to_1001efc4;
LAB_10002a72:
          Console_WriteGraphDisplay(1,(byte *)pcVar9);
        }
        else {
          DVar4 = WaitForSingleObject((HANDLE)piVar7[10],0);
          if (DVar4 != 0x102) {
            CloseHandle((HANDLE)piVar7[10]);
            piVar7[10] = 0;
            if (*piVar7 != 0) {
              FOG_EnterCriticalSection(*piVar7,(intptr_t)&dwPacketType + 3,1);
              pcVar9 = s__CHARACTER_SERVER__Connected_to_C_1001ef5c;
              goto LAB_10002a72;
            }
            SStrPrintf((char*)&uStack00000008,0x100,Char_Server___d_1001efa0,iVar6);
            iVar2 = FOG_ReallocPool();
            *piVar7 = iVar2;
            iVar2 = FOG_Noop3(iVar2);
            piVar7[10] = iVar2;
          }
        }
      }
      else {
        dwPacketType = CONCAT13(8,(undefined3)dwPacketType);
        iVar2 = 0;
        uVar5 = nCharServerSelector;
        do {
          if ((&sCharServerConns)[uVar5 * 0xb] != 0) {
            iVar3 = FOG_Send((&sCharServerConns)[uVar5 * 0xb],(intptr_t)&dwPacketType + 3,1);
            if (iVar3 != 0) break;
          }
          uVar5 = (uVar5 + 1) % 3;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 3);
        unaff_EBP = 1;
        nCharServerSelector = uVar5;
      }
    }
    piVar7 = piVar7 + 0xb;
    iVar6 = iVar6 + 1;
    if (0x1002313b < (intptr_t)piVar7) {
      return unaff_EBP;
    }
  } while( true );
}



/* DUPLICATE: CharServer_CloseAllConnections */
#if 0
void CharServer_CloseAllConnections(void)

{
  int *piVar1;
  
  piVar1 = &sCharServerConns;
  do {
    if (*piVar1 != 0) {
      FOG_Noop();
    }
    *piVar1 = 0;
    piVar1 = piVar1 + 0xb;
  } while ((intptr_t)piVar1 < 0x1002313c);
  return;
}
#endif




/* DUPLICATE: CharServer_PollAndDispatch */
#if 0
unsigned int CharServer_PollAndDispatch(void)

{
  short sVar1;
  int *piVar2;
  byte unaff_retaddr;
  
  _alloca_probe();
  piVar2 = &sCharServerConns;
  do {
    if (*piVar2 != 0) {
      sVar1 = FOG_LeaveCriticalSection(*piVar2,&uStack00000000,0x1020);
      if ((((sVar1 != 0) && (sVar1 != 0)) && (unaff_retaddr < 9)) &&
         (*(void **)(&DAT_1001ee9c + (uintptr_t)unaff_retaddr * 4) != (void *)0x0)) {
        ((int (*)())(*(void **)(&DAT_1001ee9c + (uintptr_t)unaff_retaddr * 4)))();
      }
    }
    piVar2 = piVar2 + 0xb;
  } while ((intptr_t)piVar2 < 0x1002313c);
  return 1;
}
#endif




/* DUPLICATE: Console_GetCmdDialogHandle */
#if 0
unsigned int Console_GetCmdDialogHandle(void)

{
  return ghCmdDialog;
}
#endif




/* DUPLICATE: Console_ShowCmdDialog */
#if 0
int __fastcall Console_ShowCmdDialog(HWND hParentWnd)

{
  HINSTANCE hInstance;
  
  hInstance = (HINSTANCE)GetWindowLongA(hParentWnd,-6);
  if (ghCmdDialog != (HWND)0x0) {
    return false;
  }
  ghCmdDialog = CreateDialogParamA(hInstance,(LPCSTR)0x68,hParentWnd,(DLGPROC)&LAB_10001307,0);
  return ghCmdDialog != (HWND)0x0;
}
#endif




/* DUPLICATE: Console_HideCmdDialog */
#if 0
void Console_HideCmdDialog(void)

{
  SendMessageA(ghCmdDialog,0x10,0,0);
  return;
}
#endif




unsigned int Console_CommandDialogProc(HWND hDlg,int uMsg,int wParam)

{
  LRESULT lTextLen;
  int nCmdIdx;
  byte *pCmdEntry;
  HWND hWnd;
  int nCmpResult;
  uint nStrLen;
  uint nDwordCopy;
  byte bVar1;
  byte *pPattern;
  char *pSrc;
  byte *pCmdTable;
  char *pSrc2;
  char *pDest;
  int bLessThan;
  byte whitespaceDelimiters [2];
  unsigned int szInputBuffer;
  byte szCmdAndArgs [512];
  char cChar;
  
  if (uMsg == 0x10) {
    ghCmdDialog = 0;
    EndDialog(hDlg,0);
  }
  else if (uMsg != 0x110) {
    if (uMsg != 0x111) {
      return 0;
    }
    if (wParam == 1) {
      lTextLen = SendDlgItemMessageA(hDlg,0x3ef,0xd,0x100,(LPARAM)&szInputBuffer);
      if (lTextLen != 0) {
        szCmdAndArgs[0x100] = 0;
        nCmdIdx = 0;
        whitespaceDelimiters[0] = 0x20;
        whitespaceDelimiters[1] = 9;
        do {
          bVar1 = *(byte *)((intptr_t)&szInputBuffer + nCmdIdx);
          nCmpResult = 0;
          do {
            if (bVar1 == whitespaceDelimiters[nCmpResult]) goto LAB_10002d4a;
            nCmpResult = nCmpResult + 1;
          } while (nCmpResult < 2);
          if (bVar1 == 0) break;
          szCmdAndArgs[nCmdIdx] = bVar1;
          nCmdIdx = nCmdIdx + 1;
        } while (nCmdIdx < 0x100);
LAB_10002d4a:
        bVar1 = *(byte *)((intptr_t)&szInputBuffer + nCmdIdx);
        szCmdAndArgs[nCmdIdx] = 0;
        if (bVar1 != 0) {
          while (nCmdIdx < 0x100) {
            whitespaceDelimiters[0] = 0x20;
            whitespaceDelimiters[1] = 9;
            nCmpResult = 0;
            while (bVar1 != whitespaceDelimiters[nCmpResult]) {
              nCmpResult = nCmpResult + 1;
              if (1 < nCmpResult) goto LAB_10002d83;
            }
            bVar1 = *(byte *)((intptr_t)&szInputBuffer + nCmdIdx + 1);
            nCmdIdx = nCmdIdx + 1;
            if (bVar1 == 0) break;
          }
LAB_10002d83:
          bVar1 = *(byte *)((intptr_t)&szInputBuffer + nCmdIdx);
          nCmpResult = 0;
          for (; (bVar1 != 0 && (nCmdIdx < 0x100)); nCmdIdx = nCmdIdx + 1) {
            szCmdAndArgs[nCmpResult + 0x100] = bVar1;
            nCmpResult = nCmpResult + 1;
            bVar1 = *(byte *)((intptr_t)&szInputBuffer + nCmdIdx + 1);
          }
          szCmdAndArgs[nCmpResult + 0x100] = 0;
        }
        whitespaceDelimiters[1] = 9;
        whitespaceDelimiters[0] = 0x20;
        String_ToLower((char *)szCmdAndArgs);
        nCmdIdx = 0;
        pCmdTable = (byte*)&DAT_1001f058;
        do {
          pCmdEntry = szCmdAndArgs;
          pPattern = pCmdTable;
          do {
            bVar1 = *pCmdEntry;
            bLessThan = bVar1 < *pPattern;
            if (bVar1 != *pPattern) {
LAB_10002df1:
              nCmpResult = (1 - (uintptr_t)bLessThan) - (uintptr_t)(bLessThan != 0);
              goto LAB_10002df6;
            }
            if (bVar1 == 0) break;
            bVar1 = pCmdEntry[1];
            bLessThan = bVar1 < pPattern[1];
            if (bVar1 != pPattern[1]) goto LAB_10002df1;
            pCmdEntry = pCmdEntry + 2;
            pPattern = pPattern + 2;
          } while (bVar1 != 0);
          nCmpResult = 0;
LAB_10002df6:
          if (nCmpResult == 0) {
            nCmdIdx = ((int (*)())(*(void **)(&PTR_Console_DisplayHelp_1001f158 + nCmdIdx * 0x81)))();
            if (nCmdIdx == 0) goto LAB_10002e94;
            goto LAB_10002e9e;
          }
          pCmdTable = pCmdTable + 0x204;
          nCmdIdx = nCmdIdx + 1;
        } while (pCmdTable < &DAT_1002027c);
        nStrLen = 0xffffffff;
        pSrc = s_ERROR__Unknown_command___10020620;
        do {
          pDest = pSrc;
          if (nStrLen == 0) break;
          nStrLen = nStrLen - 1;
          pDest = pSrc + 1;
          cChar = *pSrc;
          pSrc = pDest;
        } while (cChar != '\0');
        nStrLen = ~nStrLen;
        pSrc = pDest + -nStrLen;
        pDest = (char *)&szInputBuffer;
        for (nDwordCopy = nStrLen >> 2; nDwordCopy != 0; nDwordCopy = nDwordCopy - 1) {
          *(unsigned int *)pDest = *(unsigned int *)pSrc;
          pSrc = pSrc + 4;
          pDest = pDest + 4;
        }
        for (nStrLen = nStrLen & 3; nStrLen != 0; nStrLen = nStrLen - 1) {
          *pDest = *pSrc;
          pSrc = pSrc + 1;
          pDest = pDest + 1;
        }
        nStrLen = 0xffffffff;
        pCmdTable = szCmdAndArgs;
        do {
          pCmdEntry = pCmdTable;
          if (nStrLen == 0) break;
          nStrLen = nStrLen - 1;
          pCmdEntry = pCmdTable + 1;
          bVar1 = *pCmdTable;
          pCmdTable = pCmdEntry;
        } while (bVar1 != 0);
        nStrLen = ~nStrLen;
        nCmdIdx = -1;
        pSrc = (char *)&szInputBuffer;
        do {
          pDest = pSrc;
          if (nCmdIdx == 0) break;
          nCmdIdx = nCmdIdx + -1;
          pDest = pSrc + 1;
          cChar = *pSrc;
          pSrc = pDest;
        } while (cChar != '\0');
        pCmdTable = pCmdEntry + -nStrLen;
        pCmdEntry = (byte *)(pDest + -1);
        for (nDwordCopy = nStrLen >> 2; nDwordCopy != 0; nDwordCopy = nDwordCopy - 1) {
          *(unsigned int *)pCmdEntry = *(unsigned int *)pCmdTable;
          pCmdTable = pCmdTable + 4;
          pCmdEntry = pCmdEntry + 4;
        }
        for (nStrLen = nStrLen & 3; nStrLen != 0; nStrLen = nStrLen - 1) {
          *pCmdEntry = *pCmdTable;
          pCmdTable = pCmdTable + 1;
          pCmdEntry = pCmdEntry + 1;
        }
        nStrLen = 0xffffffff;
        pSrc = (char*)&DAT_1002061c;
        do {
          pDest = pSrc;
          if (nStrLen == 0) break;
          nStrLen = nStrLen - 1;
          pDest = pSrc + 1;
          cChar = *pSrc;
          pSrc = pDest;
        } while (cChar != '\0');
        nStrLen = ~nStrLen;
        nCmdIdx = -1;
        pSrc = (char *)&szInputBuffer;
        do {
          pSrc2 = pSrc;
          if (nCmdIdx == 0) break;
          nCmdIdx = nCmdIdx + -1;
          pSrc2 = pSrc + 1;
          cChar = *pSrc;
          pSrc = pSrc2;
        } while (cChar != '\0');
        pSrc = pDest + -nStrLen;
        pDest = pSrc2 + -1;
        for (nDwordCopy = nStrLen >> 2; nDwordCopy != 0; nDwordCopy = nDwordCopy - 1) {
          *(unsigned int *)pDest = *(unsigned int *)pSrc;
          pSrc = pSrc + 4;
          pDest = pDest + 4;
        }
        for (nStrLen = nStrLen & 3; nStrLen != 0; nStrLen = nStrLen - 1) {
          *pDest = *pSrc;
          pSrc = pSrc + 1;
          pDest = pDest + 1;
        }
LAB_10002e94:
        Console_WriteGraphDisplay(0,(byte *)&szInputBuffer);
      }
LAB_10002e9e:
      (*(unsigned short*)&(szInputBuffer)) = 0;
      SendDlgItemMessageA(hDlg,0x3ef,0xc,0,(LPARAM)&szInputBuffer);
      hWnd = GetDlgItem(hDlg,0x3ef);
      SetFocus(hWnd);
      return 1;
    }
    if (wParam == 2) {
      ghCmdDialog = 0;
      EndDialog(hDlg,0);
      return 1;
    }
  }
  return 1;
}



/* DUPLICATE: Console_ParseAndExecuteCommand */
#if 0
void __fastcall Console_ParseAndExecuteCommand(unsigned int dwContext,byte *pszOutputBuffer)

{
  char cVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  byte *pbVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  int bVar12;
  byte whitespaceDelimiters [2];
  unsigned int dwReserved;
  byte szParsedCmdAndArgs [512];
  
  iVar2 = 0;
  szParsedCmdAndArgs[0x100] = 0;
  whitespaceDelimiters[0] = 0x20;
  whitespaceDelimiters[1] = 9;
  pbVar8 = pszOutputBuffer;
  do {
    bVar7 = *pbVar8;
    iVar4 = 0;
    do {
      if (bVar7 == whitespaceDelimiters[iVar4]) goto LAB_1000347d;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    if (bVar7 == 0) break;
    pbVar8[(intptr_t)(szParsedCmdAndArgs + -(intptr_t)pszOutputBuffer)] = bVar7;
    iVar2 = iVar2 + 1;
    pbVar8 = pbVar8 + 1;
  } while (iVar2 < 0x100);
LAB_1000347d:
  bVar7 = pszOutputBuffer[iVar2];
  szParsedCmdAndArgs[iVar2] = 0;
  if (bVar7 != 0) {
    while (iVar2 < 0x100) {
      whitespaceDelimiters[0] = 0x20;
      whitespaceDelimiters[1] = 9;
      iVar4 = 0;
      while (bVar7 != whitespaceDelimiters[iVar4]) {
        iVar4 = iVar4 + 1;
        if (1 < iVar4) goto LAB_100034b2;
      }
      bVar7 = pszOutputBuffer[iVar2 + 1];
      iVar2 = iVar2 + 1;
      if (bVar7 == 0) break;
    }
LAB_100034b2:
    bVar7 = pszOutputBuffer[iVar2];
    iVar4 = 0;
    while ((bVar7 != 0 && (iVar2 < 0x100))) {
      iVar2 = iVar2 + 1;
      szParsedCmdAndArgs[iVar4 + 0x100] = bVar7;
      iVar4 = iVar4 + 1;
      bVar7 = pszOutputBuffer[iVar2];
    }
    szParsedCmdAndArgs[iVar4 + 0x100] = 0;
  }
  whitespaceDelimiters[1] = 9;
  whitespaceDelimiters[0] = 0x20;
  dwReserved = dwContext;
  String_ToLower((char *)szParsedCmdAndArgs);
  iVar2 = 0;
  pbVar8 = &DAT_1001f058;
  do {
    pbVar3 = szParsedCmdAndArgs;
    pbVar9 = pbVar8;
    do {
      bVar7 = *pbVar3;
      bVar12 = bVar7 < *pbVar9;
      if (bVar7 != *pbVar9) {
LAB_10003513:
        iVar4 = (1 - (uintptr_t)bVar12) - (uintptr_t)(bVar12 != 0);
        goto LAB_10003518;
      }
      if (bVar7 == 0) break;
      bVar7 = pbVar3[1];
      bVar12 = bVar7 < pbVar9[1];
      if (bVar7 != pbVar9[1]) goto LAB_10003513;
      pbVar3 = pbVar3 + 2;
      pbVar9 = pbVar9 + 2;
    } while (bVar7 != 0);
    iVar4 = 0;
LAB_10003518:
    if (iVar4 == 0) {
      iVar2 = ((int (*)())(*(void **)(&PTR_Console_DisplayHelp_1001f158 + iVar2 * 0x81)))();
      if (iVar2 != 0) {
        return;
      }
      goto LAB_100035a0;
    }
    pbVar8 = pbVar8 + 0x204;
    iVar2 = iVar2 + 1;
  } while (pbVar8 < &DAT_1002027c);
  uVar5 = 0xffffffff;
  pcVar10 = s_ERROR__Unknown_command___10020620;
  do {
    pcVar11 = pcVar10;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar11 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar11;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar8 = (byte *)(pcVar11 + -uVar5);
  pbVar3 = pszOutputBuffer;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
  uVar5 = 0xffffffff;
  pbVar8 = szParsedCmdAndArgs;
  do {
    pbVar3 = pbVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pbVar3 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar3;
  } while (bVar7 != 0);
  uVar5 = ~uVar5;
  iVar2 = -1;
  pbVar8 = pszOutputBuffer;
  do {
    pbVar9 = pbVar8;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pbVar9 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar9;
  } while (bVar7 != 0);
  pbVar8 = pbVar3 + -uVar5;
  pbVar3 = pbVar9 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar10 = &DAT_1002061c;
  do {
    pcVar11 = pcVar10;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar11 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar11;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  iVar2 = -1;
  pbVar8 = pszOutputBuffer;
  do {
    pbVar3 = pbVar8;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pbVar3 = pbVar8 + 1;
    bVar7 = *pbVar8;
    pbVar8 = pbVar3;
  } while (bVar7 != 0);
  pbVar8 = (byte *)(pcVar11 + -uVar5);
  pbVar3 = pbVar3 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(unsigned int *)pbVar3 = *(unsigned int *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
LAB_100035a0:
  Console_WriteGraphDisplay(0,pszOutputBuffer);
  return;
}
#endif




/* DUPLICATE: Console_DisplayHelp */
#if 0
unsigned int Console_DisplayHelp(void)

{
  char cVar1;
  byte bVar2;
  LRESULT LVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  byte *pbVar11;
  byte szLineBuffer [256];
  
  if (ghCmdDialog != (HWND)0x0) {
    LVar3 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    if (0x40 < LVar3) {
      SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x182,0,0);
    }
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x180,0,0x100207b4);
    LVar3 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x186,LVar3 - 1,0);
  }
  pcVar7 = s_Display_Console_Commands_1001f15c;
  do {
    uVar4 = 0xffffffff;
    pcVar9 = &DAT_100207ac;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = szLineBuffer;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7 + -0x104;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = szLineBuffer;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = &DAT_100207a8;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = szLineBuffer;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7;
    do {
      pcVar10 = pcVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar6 = -1;
    pbVar8 = szLineBuffer;
    do {
      pbVar11 = pbVar8;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar11 = pbVar8 + 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar11;
    } while (bVar2 != 0);
    pbVar8 = (byte *)(pcVar10 + -uVar4);
    pbVar11 = pbVar11 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(unsigned int *)pbVar11 = *(unsigned int *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar11 = pbVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar11 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar11 = pbVar11 + 1;
    }
    Console_WriteGraphDisplay(0,szLineBuffer);
    pcVar7 = pcVar7 + 0x204;
    if ((char *)0x1002037f < pcVar7) {
      return 1;
    }
  } while( true );
}
#endif




void __fastcall Console_AddGameToList(LPARAM lParam)

{
  LRESULT LVar1;
  
  if (ghCmdDialog != (HWND)0x0) {
    LVar1 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    if (0x40 < LVar1) {
      SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x182,0,0);
    }
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x180,0,lParam);
    LVar1 = SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x18b,0,0);
    SendDlgItemMessageA((HWND)ghCmdDialog,0x3ee,0x186,LVar1 - 1,0);
  }
  return;
}



/* DUPLICATE: Perf_InitFrameTimer */
#if 0
void __fastcall Perf_InitFrameTimer(uint dwTargetFPS)

{
  unsigned long long uVar1;
  LARGE_INTEGER liPerfFreq;
  LARGE_INTEGER liFrequency;
  
  QueryPerformanceFrequency(&liPerfFreq);
  uVar1 = __alldiv(liPerfFreq.u.LowPart,liPerfFreq.u.HighPart,dwTargetFPS,(intptr_t)dwTargetFPS >> 0x1f);
  DAT_10023164 = (intptr_t)((ulonglong)uVar1 >> 0x20);
  DAT_10023160 = (uintptr_t)uVar1;
  QueryPerformanceCounter(&liFrequency);
  DAT_10023188 = DAT_10023160 + liFrequency.u.LowPart;
  DAT_1002318c = DAT_10023164 + liFrequency.u.HighPart +
                 (uintptr_t)CARRY4(DAT_10023160,liFrequency.u.LowPart);
  return;
}
#endif




/* DUPLICATE: Game_FindByName */
#if 0
int Game_FindByName(void)

{
  byte bVar1;
  int iVar2;
  WPARAM wParam;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  int bVar6;
  byte szSelectedName [16];
  
  wParam = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x188,0,0);
  if (wParam != 0xffffffff) {
    SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,wParam,(LPARAM)szSelectedName);
    pbVar5 = szSelectedName;
    pbVar3 = &sGameSearchName;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_100039e5:
        iVar4 = (1 - (uintptr_t)bVar6) - (uintptr_t)(bVar6 != 0);
        goto LAB_100039ea;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_100039e5;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_100039ea:
    iVar2 = pGameListHead;
    if (iVar4 != 0) {
      SStrCopy(&sGameSearchName,szSelectedName,0x7fffffff);
      DAT_100231b8 = 1;
      iVar2 = pGameListHead;
    }
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x94)) {
      pbVar3 = szSelectedName;
      pbVar5 = (byte *)(iVar2 + 100);
      do {
        bVar1 = *pbVar5;
        bVar6 = bVar1 < *pbVar3;
        if (bVar1 != *pbVar3) {
LAB_10003a45:
          iVar4 = (1 - (uintptr_t)bVar6) - (uintptr_t)(bVar6 != 0);
          goto LAB_10003a4a;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar6 = bVar1 < pbVar3[1];
        if (bVar1 != pbVar3[1]) goto LAB_10003a45;
        pbVar5 = pbVar5 + 2;
        pbVar3 = pbVar3 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_10003a4a:
      if (iVar4 == 0) {
        return iVar2;
      }
    }
  }
  return 0;
}
#endif




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

/* DUPLICATE: Perf_InitSystem */
#if 0
void Perf_InitSystem(void)

{
  BOOL BVar1;
  
  BVar1 = QueryPerformanceFrequency((LARGE_INTEGER *)&lpFrequency_10023180);
  if (BVar1 != 0) {
    DAT_10023190 = 1;
    _DAT_10023178 = 0;
    _DAT_1002317c = 0;
    QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount_10023168);
    return;
  }
  DAT_10023190 = 0;
  return;
}
#endif




/* DUPLICATE: Perf_SnapshotCounter */
#if 0
void Perf_SnapshotCounter(void)

{
  QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount_10023198);
  return;
}
#endif




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

unsigned int Perf_CalcThroughput(void)

{
  uint uVar1;
  LARGE_INTEGER *pLVar2;
  longlong lVar3;
  unsigned long long uVar4;
  LARGE_INTEGER liCurrentTime;
  
  QueryPerformanceCounter(&liCurrentTime);
  pLVar2 = (LARGE_INTEGER *)(liCurrentTime.u.LowPart - lpPerformanceCount_10023198.u.LowPart);
  uVar1 = (liCurrentTime.u.HighPart - DAT_1002319c) -
          (uintptr_t)(liCurrentTime.u.LowPart < lpPerformanceCount_10023198.u.LowPart);
  if ((DAT_10023184 <= (intptr_t)uVar1) &&
     ((DAT_10023184 < (intptr_t)uVar1 || (lpFrequency_10023180.QuadPart <= (longlong)pLVar2)))) {
    lVar3 = __allmul(nGameCount,nPlayerCount,100,0);
    uVar4 = __alldiv((uintptr_t)lVar3,(uintptr_t)((ulonglong)lVar3 >> 0x20),(uintptr_t)pLVar2,uVar1);
    sPerfState = (unsigned int)uVar4;
    _DAT_10023178 = 0;
    _DAT_1002317c = 0;
    nGameCount = 0;
    nPlayerCount = 0;
    QueryPerformanceCounter((LARGE_INTEGER *)&lpPerformanceCount_10023198);
    return 1;
  }
  return 0;
}



/* DUPLICATE: String_ToLower */
#if 0
void __fastcall String_ToLower(char *szString)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = szString;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar3 = 0;
  if (0 < (intptr_t)(~uVar2 - 1)) {
    do {
      cVar1 = szString[iVar3];
      if ((cVar1 < '[') && ('@' < cVar1)) {
        szString[iVar3] = cVar1 + ' ';
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (intptr_t)(~uVar2 - 1));
  }
  return;
}
#endif




void __fastcall Console_RefreshGameList(unsigned short *pwGameId,unsigned int dwFlags)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  unsigned int *puVar5;
  char *pcVar6;
  unsigned int dwGameInfo [32];
  int iStack_10;
  
  puVar5 = dwGameInfo;
  for (iVar2 = 0x24; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  dwGameInfo[0] = 0xffffffff;
  D2GAME_10019(*pwGameId,(intptr_t)dwGameInfo,dwFlags);
  SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x184,0,0);
  iVar2 = iStack_10;
  if (iStack_10 != 0) {
    do {
      _vsprintf_l((char*)&uStack00000000,(byte *)s__3d____s___d__d__100208ac);
      uVar3 = 0xffffffff;
      pcVar6 = (char*)&uStack00000000;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      iVar4 = 0;
      if (0 < (intptr_t)(~uVar3 - 1)) {
        do {
          cVar1 = (&uStack00000000)[iVar4];
          if ((cVar1 < '[') && ('@' < cVar1)) {
            (&uStack00000000)[iVar4] = cVar1 + ' ';
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < (intptr_t)(~uVar3 - 1));
      }
      SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x180,0,(LPARAM)&uStack00000000);
      iVar2 = *(int *)(iVar2 + 0x8c);
    } while (iVar2 != 0);
    while (iStack_10 != 0) {
      iVar2 = *(int *)(iStack_10 + 0x8c);
      FOG_CrashDumpThread(0x19c,0);
      iStack_10 = iVar2;
    }
  }
  return;
}



/* DUPLICATE: Console_RefreshDisplay */
#if 0
void Console_RefreshDisplay(void)

{
  uint uVar1;
  uint *puVar2;
  LRESULT LVar3;
  int iVar4;
  WPARAM WVar5;
  unsigned int extraout_ECX;
  uint uVar6;
  unsigned int extraout_ECX_00;
  unsigned int extraout_ECX_01;
  unsigned int extraout_ECX_02;
  unsigned int uVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  unsigned int *puVar11;
  unsigned int *puVar12;
  unsigned long long uVar13;
  unsigned char auStack_4fc [4];
  int iStack_4f8;
  LARGE_INTEGER perfCount;
  struct _SYSTEM_INFO sysInfo;
  unsigned char auStack_4c0 [256];
  LRESULT aLStack_3c0 [16];
  unsigned int auStack_380 [16];
  unsigned char auStack_340 [832];
  
  QueryPerformanceCounter(&perfCount);
  if ((DAT_1002318c <= perfCount.u.HighPart) &&
     ((DAT_1002318c < perfCount.u.HighPart || (DAT_10023188 <= perfCount.u.LowPart)))) {
    GetSystemInfo(&sysInfo);
    uVar13 = __alldiv(DAT_10023160 + perfCount.u.LowPart,
                      DAT_10023164 + perfCount.u.HighPart +
                      (uintptr_t)CARRY4(DAT_10023160,perfCount.u.LowPart),sysInfo.dwNumberOfProcessors,0)
    ;
    DAT_1002318c = (intptr_t)((ulonglong)uVar13 >> 0x20);
    DAT_10023188 = (uintptr_t)uVar13;
    iVar10 = 0;
    uVar1 = D2GAME_10012();
    if (uVar1 == 0) {
      puVar11 = (unsigned int *)0x0;
      iVar4 = pGameListHead;
      uVar7 = extraout_ECX;
    }
    else {
      puVar11 = (unsigned int *)FOG_CrashDeadlockDetected(0x48,0);
      if (puVar11 == (unsigned int *)0x0) {
        FOG_SetLogPrefix(s_ptwGameIds_100208d8,s_C__D2_Source_D2Server_CORE_Displ_1002082c,0x49);
        _exit_wrapper(0xffffffff);
      }
      puVar12 = puVar11;
      for (uVar6 = (uVar1 & 0x7fffffff) >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar12 = 0;
        puVar12 = puVar12 + 1;
      }
      for (uVar6 = uVar1 * 2 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(unsigned char *)puVar12 = 0;
        puVar12 = (unsigned int *)((intptr_t)puVar12 + 1);
      }
      iVar10 = D2GAME_10015(puVar11,uVar1);
      iVar4 = pGameListHead;
      uVar7 = extraout_ECX_00;
    }
    for (; iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x94)) {
      *(unsigned int *)(iVar4 + 0x90) = 0;
    }
    puVar12 = puVar11;
    if (0 < iVar10) {
      do {
        puVar2 = Game_FindByGameId(CONCAT22((short)((uintptr_t)uVar7 >> 0x10),*(unsigned short *)puVar12));
        if (puVar2 == (uint *)0x0) {
          Game_AddToList(CONCAT22((short)((uintptr_t)extraout_ECX_01 >> 0x10),*(unsigned short *)puVar12));
          uVar7 = extraout_ECX_02;
        }
        else {
          puVar2[0x24] = 1;
          uVar7 = extraout_ECX_01;
        }
        iVar10 = iVar10 + -1;
        puVar12 = (unsigned int *)((intptr_t)puVar12 + 2);
      } while (iVar10 != 0);
    }
    Console_SyncGameList();
    if (puVar11 != (unsigned int *)0x0) {
      FOG_CrashDumpThread(0xcd,0);
    }
    Console_UpdateGameDetails();
    iVar10 = 0;
    LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0);
    if ((LVar3 != -1) && (LVar3 != DAT_100207d0)) {
      for (piVar8 = &sGameDetailTable; DAT_100207d0 = LVar3, (intptr_t)piVar8 < 0x10020814;
          piVar8 = piVar8 + 3) {
        if (*piVar8 == LVar3) {
          iVar4 = Game_FindByName();
          if (iVar4 != 0) {
            ((int (*)())(*(void (**)(void))(iVar10 * 0xc + 0x100207dc)))();
          }
          break;
        }
        iVar10 = iVar10 + 1;
      }
    }
    piVar8 = (int *)Game_FindByName();
    if ((piVar8 != (int *)0x0) &&
       (LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0), LVar3 != -1)) {
      iVar10 = 0;
      piVar9 = &sGameDetailTable;
      do {
        if (*piVar9 == LVar3) {
          if (iVar10 < 5) {
            iVar10 = *(int *)(iVar10 * 0xc + 0x100207e0);
            WVar5 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x188,0,0);
            if (((WVar5 != 0xffffffff) &&
                (LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x199,WVar5,0), iVar10 == 0)) &&
               ((*piVar8 != DAT_10020814 || ((DAT_10020818 != 0 || (LVar3 != DAT_100231bc)))))) {
              DAT_10020818 = 0;
              DAT_10020814 = *piVar8;
              DAT_100231bc = LVar3;
              SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fa,0x184,0,0);
              auStack_380[0] = 0;
              aLStack_3c0[0] = LVar3;
              iVar10 = D2GAME_10018(CONCAT22((short)((uintptr_t)aLStack_3c0 >> 0x10),(short)*piVar8),1,
                                    auStack_340,auStack_380,aLStack_3c0);
              WVar5 = 0;
              if (0 < iVar10) {
                do {
                  _vsprintf_l(auStack_4c0,&DAT_100208d4);
                  SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fa,0x181,WVar5,(LPARAM)auStack_4c0);
                  WVar5 = WVar5 + 1;
                } while ((intptr_t)WVar5 < iVar10);
              }
            }
          }
          break;
        }
        piVar9 = piVar9 + 3;
        iVar10 = iVar10 + 1;
      } while ((intptr_t)piVar9 < 0x10020814);
    }
    D2GAME_10020(auStack_4fc);
    _vsprintf_l(auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f7,0xc,0,(LPARAM)auStack_4c0);
    _vsprintf_l(auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f6,0xc,0,(LPARAM)auStack_4c0);
    Console_GraphSetFrameRate((LPARAM)auStack_4c0);
    _vsprintf_l(auStack_4c0,&DAT_100208d0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f8,0xc,0,(LPARAM)auStack_4c0);
    _vsprintf_l(auStack_4c0,(byte *)s__d___d____d__100208c0);
    Console_GraphSetTime((LPARAM)auStack_4c0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f1,0xc,0,(LPARAM)auStack_4c0);
    Console_GraphDrawDataPoint(sPerfState,iStack_4f8);
    PerfLog_WriteEntry();
  }
  Console_UpdateBusyPercent();
  return;
}
#endif




uint * __fastcall Game_FindByGameId(uint dwGameId)

{
  uint *puVar1;
  
  if (pGameListHead != (uint *)0x0) {
    puVar1 = (uint*)pGameListHead;
    do {
      if (*puVar1 == (dwGameId & 0xffff)) {
        return puVar1;
      }
      puVar1 = (uint *)puVar1[0x25];
    } while (puVar1 != (uint *)0x0);
  }
  return (uint *)0x0;
}



void __fastcall Game_AddToList(unsigned int dwGameId)

{
  unsigned int *puVar1;
  int iVar2;
  unsigned int *puVar3;
  
  puVar1 = (unsigned int *)FOG_CrashDeadlockDetected(0x67,0);
  if (puVar1 == (unsigned int *)0x0) {
    FOG_SetLogPrefix(s_ptGameInfo_100208e8,s_C__D2_Source_D2Server_CORE_Displ_1002082c,0x68);
    _exit_wrapper(0xffffffff);
  }
  puVar3 = puVar1;
  for (iVar2 = 0x26; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  iVar2 = D2GAME_10014(dwGameId,puVar1);
  if (iVar2 == 0) {
    FOG_CrashDumpThread(0x6e,0);
    return;
  }
  puVar1[0x25] = (uintptr_t)pGameListHead;
  pGameListHead = puVar1;
  puVar1[0x24] = 1;
  SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x180,0,(LPARAM)(puVar1 + 0x19));
  return;
}



void Console_SyncGameList(void)

{
  byte bVar1;
  uint uVar2;
  LRESULT LVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  WPARAM wParam;
  int bVar7;
  uint dwPrevGame;
  byte szItemText [16];
  
  dwPrevGame = 0;
  uVar2 = (uintptr_t)pGameListHead;
  do {
    while( true ) {
      if (uVar2 == 0) {
        return;
      }
      if (*(int *)(uVar2 + 0x90) == 0) break;
      dwPrevGame = uVar2;
      uVar2 = *(uint *)(uVar2 + 0x94);
    }
    LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x18b,0,0);
    wParam = 0;
    if (0 < LVar3) {
      do {
        SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,wParam,(LPARAM)szItemText);
        pbVar4 = szItemText;
        pbVar6 = (byte *)(uVar2 + 100);
        do {
          bVar1 = *pbVar4;
          bVar7 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_10004799:
            iVar5 = (1 - (uintptr_t)bVar7) - (uintptr_t)(bVar7 != 0);
            goto LAB_1000479e;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar7 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_10004799;
          pbVar4 = pbVar4 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_1000479e:
        if (iVar5 == 0) {
          SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x182,wParam,0);
          break;
        }
        wParam = wParam + 1;
      } while ((intptr_t)wParam < LVar3);
    }
    if (dwPrevGame == 0) {
      pGameListHead = *(uint *)(uVar2 + 0x94);
      FOG_CrashDumpThread(0xa5,0);
      uVar2 = (uintptr_t)pGameListHead;
    }
    else {
      *(unsigned int *)(dwPrevGame + 0x94) = *(unsigned int *)(uVar2 + 0x94);
      FOG_CrashDumpThread(0xa1,0);
      uVar2 = *(uint *)(dwPrevGame + 0x94);
    }
  } while( true );
}



void Console_UpdateBusyPercent(void)

{
  HWND hWnd;
  CHAR *lpString;
  CHAR szBusyText [100];
  
  if ((DAT_10023190 != 0) && (sPerfState != DAT_100207d4)) {
    lpString = szBusyText;
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ec,0x402,sPerfState,0);
    _vsprintf_l(szBusyText,(byte *)s__d___Busy_100208f8);
    hWnd = GetDlgItem(ghConsoleDlg,0x3ed);
    SetWindowTextA(hWnd,lpString);
    DAT_100207d4 = sPerfState;
  }
  return;
}



void Console_UpdateGameDetails(void)

{
  byte bVar1;
  WPARAM WVar2;
  byte *pbVar3;
  int iVar4;
  WPARAM wParam;
  LRESULT LVar5;
  int iVar6;
  int *piVar7;
  unsigned short *puVar8;
  LPCSTR pCVar9;
  int unaff_EBP;
  byte *pbVar10;
  char *pcVar11;
  unsigned int *puVar12;
  int bVar13;
  byte abStack_730 [8];
  byte szSelectedGame [8];
  CHAR aCStack_720 [8];
  char local_718 [4];
  char local_714 [4];
  char local_710 [4];
  unsigned int local_70c [13];
  char local_6d8 [4];
  char local_6d4 [4];
  char local_6d0;
  unsigned int local_6cf;
  char local_698 [4];
  char local_694 [4];
  char local_690 [4];
  unsigned int local_68c [13];
  char local_658 [4];
  char local_654 [4];
  char local_650 [4];
  unsigned int local_64c [13];
  char local_618 [4];
  char local_614 [4];
  char local_610 [4];
  char local_60c;
  unsigned int local_60b;
  char local_5d8 [4];
  char local_5d4 [4];
  char local_5d0 [4];
  unsigned int local_5cc [13];
  char local_598 [4];
  char local_594 [4];
  char local_590 [2];
  unsigned int local_58e [13];
  char local_558 [4];
  char local_554 [4];
  char local_550 [4];
  char local_54c;
  unsigned int local_54b;
  char local_518 [4];
  char local_514 [4];
  char local_510 [4];
  char local_50c [4];
  char local_508;
  unsigned int local_507;
  char local_4d8 [4];
  char local_4d4 [4];
  char local_4d0;
  unsigned int local_4cf;
  char local_498 [4];
  char local_494 [4];
  char local_490 [4];
  char local_48c [4];
  char local_488 [2];
  char local_486;
  unsigned int local_485 [11];
  unsigned int local_458 [5];
  unsigned int local_444 [11];
  char local_418 [4];
  char local_414 [4];
  char local_410 [4];
  char local_40c [4];
  char local_408 [2];
  char local_406;
  unsigned int local_405 [11];
  char local_3d8 [4];
  char local_3d4 [4];
  char local_3d0 [4];
  char local_3cc [4];
  char local_3c8;
  unsigned int local_3c7;
  unsigned int local_398 [5];
  unsigned int local_384 [11];
  char local_358 [4];
  char local_354 [4];
  char local_350 [4];
  char local_34c [4];
  char local_348;
  unsigned int local_347;
  unsigned int local_318 [5];
  unsigned int local_304 [11];
  unsigned int local_2d8 [5];
  unsigned int local_2c4 [11];
  unsigned int local_298 [5];
  unsigned int local_284 [11];
  unsigned int local_258 [5];
  unsigned int local_244 [11];
  unsigned int local_218 [5];
  unsigned int local_204 [11];
  unsigned int local_1d8 [5];
  unsigned int local_1c4 [11];
  char local_198 [4];
  char local_194 [4];
  char local_190 [4];
  char local_18c [2];
  unsigned int local_18a [12];
  char local_158 [4];
  char local_154 [4];
  char local_150 [4];
  char local_14c [2];
  char local_14a;
  unsigned int local_149 [12];
  char local_118 [4];
  char local_114 [4];
  char local_110 [4];
  char local_10c [2];
  char local_10a;
  unsigned int local_109 [10];
  CHAR aCStack_e0 [64];
  int aiStack_a0 [2];
  unsigned char gameInfoBuf[256] [38];
  
  WVar2 = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x188,0,0);
  if (WVar2 != 0xffffffff) {
    SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,WVar2,(LPARAM)szSelectedGame);
    pbVar10 = szSelectedGame;
    pbVar3 = (byte*)&sGameSearchName;
    do {
      bVar1 = *pbVar3;
      bVar13 = bVar1 < *pbVar10;
      if (bVar1 != *pbVar10) {
LAB_100049a5:
        iVar4 = (1 - (uintptr_t)bVar13) - (uintptr_t)(bVar13 != 0);
        goto LAB_100049aa;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar13 = bVar1 < pbVar10[1];
      if (bVar1 != pbVar10[1]) goto LAB_100049a5;
      pbVar3 = pbVar3 + 2;
      pbVar10 = pbVar10 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_100049aa:
    puVar8 = (short unsigned int*)pGameListHead;
    if (iVar4 != 0) {
      SStrCopy(sGameSearchName,szSelectedGame,0x7fffffff);
      DAT_100231b8 = 1;
      puVar8 = (short unsigned int*)pGameListHead;
    }
    for (; puVar8 != (unsigned short *)0x0; puVar8 = *(unsigned short **)(puVar8 + 0x4a)) {
      pbVar3 = szSelectedGame;
      pbVar10 = (byte *)(puVar8 + 0x32);
      do {
        bVar1 = *pbVar10;
        bVar13 = bVar1 < *pbVar3;
        if (bVar1 != *pbVar3) {
LAB_10004a01:
          iVar4 = (1 - (uintptr_t)bVar13) - (uintptr_t)(bVar13 != 0);
          goto LAB_10004a06;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar10[1];
        bVar13 = bVar1 < pbVar3[1];
        if (bVar1 != pbVar3[1]) goto LAB_10004a01;
        pbVar10 = pbVar10 + 2;
        pbVar3 = pbVar3 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_10004a06:
      if (iVar4 == 0) goto LAB_10004a1e;
    }
  }
  puVar8 = (unsigned short *)0x0;
LAB_10004a1e:
  local_718[0] = s_Game_Id___d_10020adc[0];
  local_718[1] = s_Game_Id___d_10020adc[1];
  local_718[2] = s_Game_Id___d_10020adc[2];
  local_718[3] = s_Game_Id___d_10020adc[3];
  local_714[0] = s_Game_Id___d_10020adc[4];
  local_714[1] = s_Game_Id___d_10020adc[5];
  local_714[2] = s_Game_Id___d_10020adc[6];
  local_714[3] = s_Game_Id___d_10020adc[7];
  local_710[0] = s_Game_Id___d_10020adc[8];
  local_710[1] = s_Game_Id___d_10020adc[9];
  local_710[2] = s_Game_Id___d_10020adc[10];
  local_710[3] = s_Game_Id___d_10020adc[0xb];
  puVar12 = local_70c;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_6d8[0] = s_Seed___d_10020ad0[0];
  local_6d8[1] = s_Seed___d_10020ad0[1];
  local_6d8[2] = s_Seed___d_10020ad0[2];
  local_6d8[3] = s_Seed___d_10020ad0[3];
  local_6d4[0] = s_Seed___d_10020ad0[4];
  local_6d4[1] = s_Seed___d_10020ad0[5];
  local_6d4[2] = s_Seed___d_10020ad0[6];
  local_6d4[3] = s_Seed___d_10020ad0[7];
  local_6d0 = s_Seed___d_10020ad0[8];
  puVar12 = &local_6cf;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  local_694[0] = s_Clients___d_10020ac0[4];
  local_694[1] = s_Clients___d_10020ac0[5];
  local_694[2] = s_Clients___d_10020ac0[6];
  local_694[3] = s_Clients___d_10020ac0[7];
  local_698[0] = s_Clients___d_10020ac0[0];
  local_698[1] = s_Clients___d_10020ac0[1];
  local_698[2] = s_Clients___d_10020ac0[2];
  local_698[3] = s_Clients___d_10020ac0[3];
  local_690[0] = s_Clients___d_10020ac0[8];
  local_690[1] = s_Clients___d_10020ac0[9];
  local_690[2] = s_Clients___d_10020ac0[10];
  local_690[3] = s_Clients___d_10020ac0[0xb];
  puVar12 = local_68c;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_658[0] = s_Players___d_10020ab0[0];
  local_658[1] = s_Players___d_10020ab0[1];
  local_658[2] = s_Players___d_10020ab0[2];
  local_658[3] = s_Players___d_10020ab0[3];
  local_654[0] = s_Players___d_10020ab0[4];
  local_654[1] = s_Players___d_10020ab0[5];
  local_654[2] = s_Players___d_10020ab0[6];
  local_654[3] = s_Players___d_10020ab0[7];
  local_650[0] = s_Players___d_10020ab0[8];
  local_650[1] = s_Players___d_10020ab0[9];
  local_650[2] = s_Players___d_10020ab0[10];
  local_650[3] = s_Players___d_10020ab0[0xb];
  puVar12 = local_64c;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_618[0] = s_Monsters___d_10020aa0[0];
  local_618[1] = s_Monsters___d_10020aa0[1];
  local_618[2] = s_Monsters___d_10020aa0[2];
  local_618[3] = s_Monsters___d_10020aa0[3];
  local_614[0] = s_Monsters___d_10020aa0[4];
  local_614[1] = s_Monsters___d_10020aa0[5];
  local_614[2] = s_Monsters___d_10020aa0[6];
  local_614[3] = s_Monsters___d_10020aa0[7];
  local_610[0] = s_Monsters___d_10020aa0[8];
  local_610[1] = s_Monsters___d_10020aa0[9];
  local_610[2] = s_Monsters___d_10020aa0[10];
  local_610[3] = s_Monsters___d_10020aa0[0xb];
  local_60c = s_Monsters___d_10020aa0[0xc];
  puVar12 = &local_60b;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  local_5d4[0] = s_Objects___d_10020a90[4];
  local_5d4[1] = s_Objects___d_10020a90[5];
  local_5d4[2] = s_Objects___d_10020a90[6];
  local_5d4[3] = s_Objects___d_10020a90[7];
  local_5d8[0] = s_Objects___d_10020a90[0];
  local_5d8[1] = s_Objects___d_10020a90[1];
  local_5d8[2] = s_Objects___d_10020a90[2];
  local_5d8[3] = s_Objects___d_10020a90[3];
  local_5d0[0] = s_Objects___d_10020a90[8];
  local_5d0[1] = s_Objects___d_10020a90[9];
  local_5d0[2] = s_Objects___d_10020a90[10];
  local_5d0[3] = s_Objects___d_10020a90[0xb];
  puVar12 = local_5cc;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_598[0] = s_Items___d_10020a84[0];
  local_598[1] = s_Items___d_10020a84[1];
  local_598[2] = s_Items___d_10020a84[2];
  local_598[3] = s_Items___d_10020a84[3];
  local_594[0] = s_Items___d_10020a84[4];
  local_594[1] = s_Items___d_10020a84[5];
  local_594[2] = s_Items___d_10020a84[6];
  local_594[3] = s_Items___d_10020a84[7];
  local_590[0] = s_Items___d_10020a84[8];
  local_590[1] = s_Items___d_10020a84[9];
  puVar12 = local_58e;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  local_554[0] = s_Missiles___d_10020a74[4];
  local_554[1] = s_Missiles___d_10020a74[5];
  local_554[2] = s_Missiles___d_10020a74[6];
  local_554[3] = s_Missiles___d_10020a74[7];
  local_558[0] = s_Missiles___d_10020a74[0];
  local_558[1] = s_Missiles___d_10020a74[1];
  local_558[2] = s_Missiles___d_10020a74[2];
  local_558[3] = s_Missiles___d_10020a74[3];
  local_550[0] = s_Missiles___d_10020a74[8];
  local_550[1] = s_Missiles___d_10020a74[9];
  local_550[2] = s_Missiles___d_10020a74[10];
  local_550[3] = s_Missiles___d_10020a74[0xb];
  local_54c = s_Missiles___d_10020a74[0xc];
  puVar12 = &local_54b;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  local_514[0] = s_Unique_Items___d_10020a48[4];
  local_514[1] = s_Unique_Items___d_10020a48[5];
  local_514[2] = s_Unique_Items___d_10020a48[6];
  local_514[3] = s_Unique_Items___d_10020a48[7];
  local_518[0] = s_Unique_Items___d_10020a48[0];
  local_518[1] = s_Unique_Items___d_10020a48[1];
  local_518[2] = s_Unique_Items___d_10020a48[2];
  local_518[3] = s_Unique_Items___d_10020a48[3];
  local_50c[0] = s_Unique_Items___d_10020a48[0xc];
  local_50c[1] = s_Unique_Items___d_10020a48[0xd];
  local_50c[2] = s_Unique_Items___d_10020a48[0xe];
  local_50c[3] = s_Unique_Items___d_10020a48[0xf];
  local_510[0] = s_Unique_Items___d_10020a48[8];
  local_510[1] = s_Unique_Items___d_10020a48[9];
  local_510[2] = s_Unique_Items___d_10020a48[10];
  local_510[3] = s_Unique_Items___d_10020a48[0xb];
  local_508 = s_Unique_Items___d_10020a48[0x10];
  puVar12 = &local_507;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  local_4d8[0] = s_NPCs___d_10020a3c[0];
  local_4d8[1] = s_NPCs___d_10020a3c[1];
  local_4d8[2] = s_NPCs___d_10020a3c[2];
  local_4d8[3] = s_NPCs___d_10020a3c[3];
  local_4d4[0] = s_NPCs___d_10020a3c[4];
  local_4d4[1] = s_NPCs___d_10020a3c[5];
  local_4d4[2] = s_NPCs___d_10020a3c[6];
  local_4d4[3] = s_NPCs___d_10020a3c[7];
  local_4d0 = s_NPCs___d_10020a3c[8];
  puVar12 = &local_4cf;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  local_494[0] = s_Next_Player_Id___d_10020a24[4];
  local_494[1] = s_Next_Player_Id___d_10020a24[5];
  local_494[2] = s_Next_Player_Id___d_10020a24[6];
  local_494[3] = s_Next_Player_Id___d_10020a24[7];
  local_498[0] = s_Next_Player_Id___d_10020a24[0];
  local_498[1] = s_Next_Player_Id___d_10020a24[1];
  local_498[2] = s_Next_Player_Id___d_10020a24[2];
  local_498[3] = s_Next_Player_Id___d_10020a24[3];
  local_48c[0] = s_Next_Player_Id___d_10020a24[0xc];
  local_48c[1] = s_Next_Player_Id___d_10020a24[0xd];
  local_48c[2] = s_Next_Player_Id___d_10020a24[0xe];
  local_48c[3] = s_Next_Player_Id___d_10020a24[0xf];
  local_490[0] = s_Next_Player_Id___d_10020a24[8];
  local_490[1] = s_Next_Player_Id___d_10020a24[9];
  local_490[2] = s_Next_Player_Id___d_10020a24[10];
  local_490[3] = s_Next_Player_Id___d_10020a24[0xb];
  local_486 = s_Next_Player_Id___d_10020a24[0x12];
  local_488[0] = s_Next_Player_Id___d_10020a24[0x10];
  local_488[1] = s_Next_Player_Id___d_10020a24[0x11];
  puVar12 = local_485;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned char *)puVar12 = 0;
  pcVar11 = s_Next_Monster_Id___d_10020a5c;
  puVar12 = local_458;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_444;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_418[0] = s_Next_Object_Id___d_10020a0c[0];
  local_418[1] = s_Next_Object_Id___d_10020a0c[1];
  local_418[2] = s_Next_Object_Id___d_10020a0c[2];
  local_418[3] = s_Next_Object_Id___d_10020a0c[3];
  local_414[0] = s_Next_Object_Id___d_10020a0c[4];
  local_414[1] = s_Next_Object_Id___d_10020a0c[5];
  local_414[2] = s_Next_Object_Id___d_10020a0c[6];
  local_414[3] = s_Next_Object_Id___d_10020a0c[7];
  local_410[0] = s_Next_Object_Id___d_10020a0c[8];
  local_410[1] = s_Next_Object_Id___d_10020a0c[9];
  local_410[2] = s_Next_Object_Id___d_10020a0c[10];
  local_410[3] = s_Next_Object_Id___d_10020a0c[0xb];
  local_40c[0] = s_Next_Object_Id___d_10020a0c[0xc];
  local_40c[1] = s_Next_Object_Id___d_10020a0c[0xd];
  local_40c[2] = s_Next_Object_Id___d_10020a0c[0xe];
  local_40c[3] = s_Next_Object_Id___d_10020a0c[0xf];
  local_408[0] = s_Next_Object_Id___d_10020a0c[0x10];
  local_408[1] = s_Next_Object_Id___d_10020a0c[0x11];
  local_406 = s_Next_Object_Id___d_10020a0c[0x12];
  puVar12 = local_405;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned char *)puVar12 = 0;
  local_3d8[0] = s_Next_Item_Id___d_100209f8[0];
  local_3d8[1] = s_Next_Item_Id___d_100209f8[1];
  local_3d8[2] = s_Next_Item_Id___d_100209f8[2];
  local_3d8[3] = s_Next_Item_Id___d_100209f8[3];
  local_3d4[0] = s_Next_Item_Id___d_100209f8[4];
  local_3d4[1] = s_Next_Item_Id___d_100209f8[5];
  local_3d4[2] = s_Next_Item_Id___d_100209f8[6];
  local_3d4[3] = s_Next_Item_Id___d_100209f8[7];
  local_3d0[0] = s_Next_Item_Id___d_100209f8[8];
  local_3d0[1] = s_Next_Item_Id___d_100209f8[9];
  local_3d0[2] = s_Next_Item_Id___d_100209f8[10];
  local_3d0[3] = s_Next_Item_Id___d_100209f8[0xb];
  local_3cc[0] = s_Next_Item_Id___d_100209f8[0xc];
  local_3cc[1] = s_Next_Item_Id___d_100209f8[0xd];
  local_3cc[2] = s_Next_Item_Id___d_100209f8[0xe];
  local_3cc[3] = s_Next_Item_Id___d_100209f8[0xf];
  local_3c8 = s_Next_Item_Id___d_100209f8[0x10];
  puVar12 = &local_3c7;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  pcVar11 = s_Next_Missile_Id___d_100209e0;
  puVar12 = local_398;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_384;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_358[0] = s_Next_Warp_Id___d_100209cc[0];
  local_358[1] = s_Next_Warp_Id___d_100209cc[1];
  local_358[2] = s_Next_Warp_Id___d_100209cc[2];
  local_358[3] = s_Next_Warp_Id___d_100209cc[3];
  local_354[0] = s_Next_Warp_Id___d_100209cc[4];
  local_354[1] = s_Next_Warp_Id___d_100209cc[5];
  local_354[2] = s_Next_Warp_Id___d_100209cc[6];
  local_354[3] = s_Next_Warp_Id___d_100209cc[7];
  local_350[0] = s_Next_Warp_Id___d_100209cc[8];
  local_350[1] = s_Next_Warp_Id___d_100209cc[9];
  local_350[2] = s_Next_Warp_Id___d_100209cc[10];
  local_350[3] = s_Next_Warp_Id___d_100209cc[0xb];
  local_34c[0] = s_Next_Warp_Id___d_100209cc[0xc];
  local_34c[1] = s_Next_Warp_Id___d_100209cc[0xd];
  local_34c[2] = s_Next_Warp_Id___d_100209cc[0xe];
  local_34c[3] = s_Next_Warp_Id___d_100209cc[0xf];
  local_348 = s_Next_Warp_Id___d_100209cc[0x10];
  puVar12 = &local_347;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  *(unsigned char *)((intptr_t)puVar12 + 2) = 0;
  pcVar11 = s_Path_Toward_Pct___d_100209b4;
  puVar12 = local_318;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_304;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  pcVar11 = s_Path_Clock_Pct___d_1002099c;
  puVar12 = local_2d8;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_2c4;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  pcVar11 = s_Path_Countr_Pct___d_10020984;
  puVar12 = local_298;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_284;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  pcVar11 = s_Path_FoWall_Pct___d_1002096c;
  puVar12 = local_258;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_244;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  pcVar11 = s_Path_Astar_Pct___d_10020954;
  puVar12 = local_218;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_204;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  pcVar11 = s_Path_Total_Call___d_1002093c;
  puVar12 = local_1d8;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *(unsigned int *)pcVar11;
    pcVar11 = pcVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  puVar12 = local_1c4;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  local_198[0] = s_Frames_h____d_1002092c[0];
  local_198[1] = s_Frames_h____d_1002092c[1];
  local_198[2] = s_Frames_h____d_1002092c[2];
  local_198[3] = s_Frames_h____d_1002092c[3];
  local_194[0] = s_Frames_h____d_1002092c[4];
  local_194[1] = s_Frames_h____d_1002092c[5];
  local_194[2] = s_Frames_h____d_1002092c[6];
  local_194[3] = s_Frames_h____d_1002092c[7];
  local_190[0] = s_Frames_h____d_1002092c[8];
  local_190[1] = s_Frames_h____d_1002092c[9];
  local_190[2] = s_Frames_h____d_1002092c[10];
  local_190[3] = s_Frames_h____d_1002092c[0xb];
  local_18c[0] = s_Frames_h____d_1002092c[0xc];
  local_18c[1] = s_Frames_h____d_1002092c[0xd];
  puVar12 = local_18a;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned short *)puVar12 = 0;
  local_154[0] = s_Time__min____d_10020918[4];
  local_154[1] = s_Time__min____d_10020918[5];
  local_154[2] = s_Time__min____d_10020918[6];
  local_154[3] = s_Time__min____d_10020918[7];
  local_158[0] = s_Time__min____d_10020918[0];
  local_158[1] = s_Time__min____d_10020918[1];
  local_158[2] = s_Time__min____d_10020918[2];
  local_158[3] = s_Time__min____d_10020918[3];
  local_14c[0] = s_Time__min____d_10020918[0xc];
  local_14c[1] = s_Time__min____d_10020918[0xd];
  local_150[0] = s_Time__min____d_10020918[8];
  local_150[1] = s_Time__min____d_10020918[9];
  local_150[2] = s_Time__min____d_10020918[10];
  local_150[3] = s_Time__min____d_10020918[0xb];
  local_14a = s_Time__min____d_10020918[0xe];
  puVar12 = local_149;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned char *)puVar12 = 0;
  local_118[0] = s_Frame_Rate___d_10020904[0];
  local_118[1] = s_Frame_Rate___d_10020904[1];
  local_118[2] = s_Frame_Rate___d_10020904[2];
  local_118[3] = s_Frame_Rate___d_10020904[3];
  local_114[0] = s_Frame_Rate___d_10020904[4];
  local_114[1] = s_Frame_Rate___d_10020904[5];
  local_114[2] = s_Frame_Rate___d_10020904[6];
  local_114[3] = s_Frame_Rate___d_10020904[7];
  local_110[0] = s_Frame_Rate___d_10020904[8];
  local_110[1] = s_Frame_Rate___d_10020904[9];
  local_110[2] = s_Frame_Rate___d_10020904[10];
  local_110[3] = s_Frame_Rate___d_10020904[0xb];
  local_10c[0] = s_Frame_Rate___d_10020904[0xc];
  local_10c[1] = s_Frame_Rate___d_10020904[0xd];
  local_10a = s_Frame_Rate___d_10020904[0xe];
  puVar12 = local_109;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  *(unsigned char *)puVar12 = 0;
  if (puVar8 == (unsigned short *)0x0) {
    DAT_100231a4 = 0;
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x184,0,0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3ea,0x184,0,0);
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3eb,0x184,0,0);
    DAT_100231b8 = 1;
    return;
  }
  puVar12 = (unsigned int*)gameInfoBuf;
  for (iVar4 = 0x26; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  D2GAME_10014((void*)*puVar8,gameInfoBuf);
  WVar2 = 0;
  piVar7 = aiStack_a0;
  pCVar9 = aCStack_720;
  do {
    if ((*piVar7 != *(int *)((unaff_EBP - (intptr_t)aiStack_a0) + (intptr_t)piVar7)) || (DAT_100231b8 != 0)) {
      wsprintfA(aCStack_e0,pCVar9,*piVar7);
      wParam = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0);
      SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x182,WVar2,0);
      SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x181,WVar2,(LPARAM)aCStack_e0);
      if (wParam != 0xffffffff) {
        SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x186,wParam,0);
      }
      *(int *)((unaff_EBP - (intptr_t)aiStack_a0) + (intptr_t)piVar7) = *piVar7;
    }
    WVar2 = WVar2 + 1;
    pCVar9 = pCVar9 + 0x40;
    piVar7 = piVar7 + 1;
  } while ((intptr_t)WVar2 < 0x19);
  if (DAT_100231a4 == unaff_EBP) {
    DAT_100231b8 = 0;
    return;
  }
  iVar4 = 0;
  DAT_100231a4 = unaff_EBP;
  LVar5 = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3e9,0x188,0,0);
  if (LVar5 == -1) {
    DAT_100231b8 = 0;
    return;
  }
  piVar7 = (int*)&sGameDetailTable;
  while( true ) {
    if (0x10020813 < (intptr_t)piVar7) {
      DAT_100207d0 = LVar5;
      DAT_100231b8 = 0;
      return;
    }
    if (*piVar7 == LVar5) break;
    iVar4 = iVar4 + 1;
    piVar7 = piVar7 + 3;
  }
  DAT_100207d0 = LVar5;
  WVar2 = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x188,0,0);
  if (WVar2 == 0xffffffff) {
    DAT_100231b8 = 0;
    return;
  }
  SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,WVar2,(LPARAM)abStack_730);
  pbVar10 = abStack_730;
  pbVar3 = (byte*)&sGameSearchName;
  do {
    bVar1 = *pbVar3;
    bVar13 = bVar1 < *pbVar10;
    if (bVar1 != *pbVar10) {
LAB_100051cf:
      iVar6 = (1 - (uintptr_t)bVar13) - (uintptr_t)(bVar13 != 0);
      goto LAB_100051d4;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar13 = bVar1 < pbVar10[1];
    if (bVar1 != pbVar10[1]) goto LAB_100051cf;
    pbVar3 = pbVar3 + 2;
    pbVar10 = pbVar10 + 2;
  } while (bVar1 != 0);
  iVar6 = 0;
LAB_100051d4:
  puVar8 = (short unsigned int*)pGameListHead;
  if (iVar6 != 0) {
    SStrCopy(sGameSearchName,abStack_730,0x7fffffff);
    DAT_100231b8 = 1;
    puVar8 = (short unsigned int*)pGameListHead;
  }
  do {
    if (puVar8 == (unsigned short *)0x0) {
      DAT_100231b8 = 0;
      return;
    }
    pbVar3 = abStack_730;
    pbVar10 = (byte *)(puVar8 + 0x32);
    do {
      bVar1 = *pbVar10;
      bVar13 = bVar1 < *pbVar3;
      if (bVar1 != *pbVar3) {
LAB_1000522b:
        iVar6 = (1 - (uintptr_t)bVar13) - (uintptr_t)(bVar13 != 0);
        goto LAB_10005230;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar10[1];
      bVar13 = bVar1 < pbVar3[1];
      if (bVar1 != pbVar3[1]) goto LAB_1000522b;
      pbVar10 = pbVar10 + 2;
      pbVar3 = pbVar3 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_10005230:
    if (iVar6 == 0) {
      if (puVar8 == (unsigned short *)0x0) {
        DAT_100231b8 = 0;
        return;
      }
      ((int (*)())(*(void (**)(void))(iVar4 * 0xc + 0x100207dc)))();
      DAT_100231b8 = 0;
      return;
    }
    puVar8 = *(unsigned short **)(puVar8 + 0x4a);
  } while( true );
}



/* DUPLICATE: Console_ClearGameList */
#if 0
void Console_ClearGameList(void)

{
  byte bVar1;
  int iVar2;
  LRESULT LVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  WPARAM wParam;
  int bVar7;
  byte szItemText [16];
  
  iVar2 = pGameListHead;
  do {
    if (iVar2 == 0) {
      pGameListHead = iVar2;
      return;
    }
    pGameListHead = iVar2;
    LVar3 = SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x18b,0,0);
    wParam = 0;
    if (0 < LVar3) {
      do {
        SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x189,wParam,(LPARAM)szItemText);
        pbVar4 = szItemText;
        pbVar6 = (byte *)(iVar2 + 100);
        do {
          bVar1 = *pbVar4;
          bVar7 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_1000554b:
            iVar5 = (1 - (uintptr_t)bVar7) - (uintptr_t)(bVar7 != 0);
            goto LAB_10005550;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar7 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_1000554b;
          pbVar4 = pbVar4 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_10005550:
        if (iVar5 == 0) {
          SendDlgItemMessageA((HWND)ghConsoleDlg,1000,0x182,wParam,0);
          break;
        }
        wParam = wParam + 1;
      } while ((intptr_t)wParam < LVar3);
    }
    pGameListHead = *(int *)(iVar2 + 0x94);
    FOG_CrashDumpThread(0x2b6,0);
    iVar2 = pGameListHead;
  } while( true );
}
#endif




// D2Server.Server_SetHInstance (100055f0) - Stores the DLL's module handle / instance into
// g_hInstance (called from DllMain-style bootstrap). Verifies against g_hMainInstance and updates
// it.

/* DUPLICATE: Server_SetHInstance */
#if 0
unsigned int Server_SetHInstance(unsigned int param_1)

{
  g_hInstance = param_1;
  return 1;
}
#endif




void * QueryInterface_Impl(void)

{
  return &g_ClassFactoryVtable;
}



unsigned int MCP_ProcessNullMessage(void)

{
  return 1;
}



unsigned int MCP_InitStage2_SendVersion(void)

{
  Server_SendVersionHandshake();
  return 1;
}



unsigned int MCP_InitStage3_SendGameList(void)

{
  Server_SendGameList();
  return 1;
}



unsigned int Server_InitGameEngine(void)

{
  Server_EnumerateCharacters();
  return 1;
}



void MCP_HandleRecreateError(void)

{
  void *pcVar1;
  
  FOG_GetSystemInfo(s_GTM_RECREATE_shouldn_t_be_sent_f_10020b50,s_C__D2_Source_D2Server_CORE_FromM_10020b90,
            0x6b);
  _exit_wrapper(0xffffffff);
  swi(3);
  ((int (*)())pcVar1)();
  return;
}



unsigned int Server_StubReturn1(void)

{
  return 1;
}



unsigned int __fastcall MCP_HandleGameCreate(int pGameCreatePacket)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  undefined3 uVar4;
  int gameMCPId;
  char *pcVar5;
  unsigned long long uVar6;
  uint uVar7;
  int pGameContext;
  
  uVar3 = 0xffffffff;
  pcVar1 = (char *)(pGameCreatePacket + 0xc);
  pcVar5 = pcVar1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  uVar4 = (undefined3)((uintptr_t)&pGameContext >> 8);
  uVar7 = 0;
  pGameContext = pGameCreatePacket;
  uVar6 = D2GAME_10047(pcVar1,pcVar1 + ~uVar3,0,*(unsigned int *)(pGameCreatePacket + 5),
                       CONCAT31(uVar4,*(unsigned char *)(pGameCreatePacket + 9)),
                       CONCAT31(uVar4,*(unsigned char *)(pGameCreatePacket + 10)),
                       CONCAT31(uVar4,*(unsigned char *)(pGameCreatePacket + 0xb)),(intptr_t)&pGameContext);
  if ((intptr_t)uVar6 != 0) {
    DllRegisterServer(gameMCPId,*(int *)(pGameCreatePacket + 1),uVar7 & 0xffff);
    return 1;
  }
  DllRegisterServer(*(int *)(pGameCreatePacket + 1),(intptr_t)((ulonglong)uVar6 >> 0x20),0);
  return 1;
}



unsigned int __fastcall MCP_HandleJoinGame(int pPacketData)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  
  pcVar1 = (char *)(pPacketData + 0x11);
  uVar3 = 0xffffffff;
  pcVar4 = pcVar1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar2 != '\0');
  Token_AddOrUpdate(pcVar1,pcVar1 + ~uVar3,*(unsigned int *)(pPacketData + 0xd),
                    *(unsigned int *)(pPacketData + 9),*(unsigned int *)(pPacketData + 5));
  Server_SendJoinGame(*(unsigned int *)(pPacketData + 1),*(unsigned int *)(pPacketData + 5),
                      *(unsigned int *)(pPacketData + 9),0);
  return 1;
}



unsigned int __fastcall MCP_HandleGameList(char *pPacketData,uint dwPacketSize)

{
  if (dwPacketSize < 0xf) {
    return 0;
  }
  if (*pPacketData != '\f') {
    return 0;
  }
  D2GAME_10048(*(unsigned int *)(pPacketData + 1),pPacketData + 5,*(unsigned short *)(pPacketData + 0xb),
               CONCAT22((short)((uintptr_t)(pPacketData + 0xf) >> 0x10),*(unsigned short *)(pPacketData + 9))
               ,*(unsigned short *)(pPacketData + 0xd),(intptr_t)pPacketData + 0xf);
  return 1;
}



unsigned int __fastcall Game_DispatchPacket(char *pPacketData,uint dwPacketSize)

{
  if (dwPacketSize < 0xf) {
    return 0;
  }
  if (*pPacketData != '\r') {
    return 0;
  }
  D2GAME_10049(*(unsigned int *)(pPacketData + 1),pPacketData + 5,*(unsigned short *)(pPacketData + 0xb),
               CONCAT22((short)((uintptr_t)(pPacketData + 0xf) >> 0x10),*(unsigned short *)(pPacketData + 9))
               ,*(unsigned short *)(pPacketData + 0xd),(intptr_t)pPacketData + 0xf);
  return 1;
}



unsigned int __fastcall MCP_HandleRecordSet(char *pPacketData,int nRecordSize)

{
  unsigned int *puVar1;
  char *pcVar2;
  
  if (nRecordSize != 0x89) {
    return 0;
  }
  if (*pPacketData != '\x0f') {
    return 0;
  }
  puVar1 = &sMCPRecvRecord;
  pcVar2 = pPacketData + 1;
  do {
    *puVar1 = *(unsigned int *)pcVar2;
    puVar1[1] = *(unsigned int *)(pcVar2 + 4);
    puVar1 = puVar1 + 2;
    pcVar2 = pcVar2 + 8;
  } while ((intptr_t)puVar1 < 0x100232f0);
  return 1;
}



unsigned int __fastcall MCP_HandleDiabloMsg(char *pPacketData,uint dwPacketSize)

{
  unsigned char szMessageBuf [256];
  
  if (dwPacketSize < 10) {
    return 0;
  }
  if (*pPacketData != '\x12') {
    return 0;
  }
  SStrPrintf((char*)szMessageBuf,0x100,s_Diablo___s_10020bc0,pPacketData + 9);
  D2GAME_10021(*(unsigned int *)(pPacketData + 1),*(unsigned int *)(pPacketData + 5),(char*)szMessageBuf);
  return 1;
}



/* DUPLICATE: MCP_DispatchIncomingMessage */
#if 0
unsigned int __fastcall MCP_DispatchIncomingMessage(byte *param_1,int param_2)

{
  unsigned int uVar1;
  
  uVar1 = 0;
  if (param_2 == 0) {
    return 0;
  }
  if (0x13 < *param_1) {
    return 0;
  }
  if ((void *)(&g_McpMessageHandlers)[*param_1] != (void *)0x0) {
    uVar1 = ((int (*)())(*(void **)(&g_McpMessageHandlers + *param_1)))();
  }
  return uVar1;
}
#endif




/* DUPLICATE: Console_GetMainDialogHandle */
#if 0
unsigned int Console_GetMainDialogHandle(void)

{
  return ghConsoleDlg;
}
#endif




/* DUPLICATE: Console_InitGraphDisplay */
#if 0
unsigned int __fastcall Console_InitGraphDisplay(HWND param_1)

{
  HINSTANCE hInstance;
  HWND hWnd;
  HDC hdc;
  HPEN hPen;
  HGDIOBJ hOldPen;
  HBRUSH hBrush;
  HGDIOBJ hOldBrush;
  struct tagRECT local_10;
  
  hInstance = (HINSTANCE)GetWindowLongA(param_1,-6);
  if (ghConsoleDlg != (HWND)0x0) {
    return 0;
  }
  ghConsoleDlg = CreateDialogParamA(hInstance,(LPCSTR)0x67,param_1,(DLGPROC)&LAB_100012a8,0);
  if (ghConsoleDlg == (HWND)0x0) {
    return 0;
  }
  hWnd = GetDlgItem(ghConsoleDlg,0x3f2);
  GetClientRect(hWnd,&local_10);
  hdc = GetDC(ghConsoleDlg);
  sGraphData = CreateCompatibleDC(hdc);
  g_hGraphBrush =
       CreateCompatibleBitmap(hdc,local_10.right - local_10.left,local_10.bottom - local_10.top);
  ReleaseDC(ghConsoleDlg,hdc);
  SelectObject(sGraphData,g_hGraphBrush);
  hPen = CreatePen(0,1,0);
  hOldPen = SelectObject(sGraphData,hPen);
  hBrush = CreateSolidBrush(0);
  hOldBrush = SelectObject(sGraphData,hBrush);
  Rectangle(sGraphData,local_10.left,local_10.top,local_10.right,local_10.bottom);
  SelectObject(sGraphData,hOldPen);
  DeleteObject(hPen);
  SelectObject(sGraphData,hOldBrush);
  DeleteObject(hBrush);
  return 1;
}
#endif




/* DUPLICATE: Console_DestroyGraphDisplay */
#if 0
void Console_DestroyGraphDisplay(void)

{
  SendMessageA(ghConsoleDlg,0x10,0,0);
  return;
}
#endif




unsigned int Console_GraphDialogProc(HWND param_1,uint param_2,int param_3)

{
  HWND hWnd;
  HDC hdc;
  struct tagRECT local_50;
  struct tagPAINTSTRUCT local_40;
  
  if (param_2 < 0x111) {
    if (param_2 == 0x110) {
      return 1;
    }
    if (param_2 == 0xf) {
      BeginPaint(param_1,&local_40);
      hWnd = GetDlgItem(param_1,0x3f2);
      hdc = GetDC(hWnd);
      GetClientRect(hWnd,&local_50);
      BitBlt(hdc,local_50.left,local_50.top,local_50.right - local_50.left,
             local_50.bottom - local_50.top,sGraphData,0,0,0xcc0020);
      ReleaseDC(hWnd,hdc);
      EndPaint(param_1,&local_40);
      return 1;
    }
    if (param_2 == 0x10) {
      ghConsoleDlg = 0;
      DeleteObject(g_hGraphBrush);
      g_hGraphBrush = (HGDIOBJ)0x0;
      DeleteObject(sGraphData);
      sGraphData = (HDC)0x0;
      EndDialog(param_1,0);
      return 1;
    }
  }
  else if (param_2 == 0x111) {
    if (param_3 != 2) {
      return 1;
    }
    ghConsoleDlg = 0;
    EndDialog(param_1,0);
    return 1;
  }
  return 0;
}



/* DUPLICATE: Console_GraphSetTime */
#if 0
void __fastcall Console_GraphSetTime(LPARAM param_1)

{
  if (ghConsoleDlg != (HWND)0x0) {
    SendDlgItemMessageA(ghConsoleDlg,0x3f1,0xc,0,param_1);
  }
  return;
}
#endif




/* DUPLICATE: Console_GraphSetFrameRate */
#if 0
void __fastcall Console_GraphSetFrameRate(LPARAM param_1)

{
  if (ghConsoleDlg != (HWND)0x0) {
    SendDlgItemMessageA(ghConsoleDlg,0x3f0,0xc,0,param_1);
  }
  return;
}
#endif




/* DUPLICATE: Console_GraphDrawDataPoint */
#if 0
void __fastcall Console_GraphDrawDataPoint(int param_1,int param_2)

{
  int right;
  int left;
  HPEN hBlackPen;
  HPEN hGreenPen;
  HPEN hRedPen;
  HBRUSH hBlackBrush;
  HWND hWnd;
  HGDIOBJ hOldBrush;
  HGDIOBJ hOldPen;
  HDC hdc;
  int nGraphHeight;
  struct tagPOINT local_18;
  struct tagRECT local_10;
  int nBarHeight;
  
  if (ghConsoleDlg != (HWND)0x0) {
    hBlackPen = CreatePen(0,1,0);
    hGreenPen = CreatePen(0,1,0xff00);
    hRedPen = CreatePen(0,1,0xff);
    hBlackBrush = CreateSolidBrush(0);
    hWnd = GetDlgItem(ghConsoleDlg,0x3f2);
    GetClientRect(hWnd,&local_10);
    nGraphHeight = local_10.bottom - local_10.top;
    left = DAT_10023248 + local_10.left;
    hOldBrush = SelectObject(sGraphData,hBlackBrush);
    hOldPen = SelectObject(sGraphData,hBlackPen);
    right = left + 2;
    Rectangle(sGraphData,left,local_10.top,right,local_10.bottom);
    nBarHeight = (nGraphHeight * param_1) / 100;
    SelectObject(sGraphData,hGreenPen);
    MoveToEx(sGraphData,left,local_10.bottom - nBarHeight,&local_18);
    LineTo(sGraphData,right,local_10.bottom - nBarHeight);
    nBarHeight = (nGraphHeight * param_2) / 600;
    SelectObject(sGraphData,hRedPen);
    MoveToEx(sGraphData,left,local_10.bottom - nBarHeight,&local_18);
    LineTo(sGraphData,right,local_10.bottom - nBarHeight);
    DAT_10023248 = DAT_10023248 + 2;
    if ((local_10.right - local_10.left) + -2 <= DAT_10023248) {
      DAT_10023248 = 0;
    }
    SelectObject(sGraphData,hOldPen);
    SelectObject(sGraphData,hOldBrush);
    DeleteObject(hBlackPen);
    DeleteObject(hGreenPen);
    DeleteObject(hRedPen);
    DeleteObject(hBlackBrush);
    hdc = GetDC(hWnd);
    GetClientRect(hWnd,&local_10);
    BitBlt(hdc,local_10.left,local_10.top,local_10.right - local_10.left,
           local_10.bottom - local_10.top,sGraphData,0,0,0xcc0020);
    ReleaseDC(hWnd,hdc);
  }
  return;
}
#endif




/* DUPLICATE: Console_IsPerfLogEnabled */
#if 0
unsigned int Console_IsPerfLogEnabled(void)

{
  return sPerfLog;
}
#endif




/* DUPLICATE: PerfLog_Init */
#if 0
void __fastcall PerfLog_Init(int bEnable)

{
  char cVar1;
  HANDLE hFile;
  uint uVar2;
  char *pcVar3;
  unsigned char local_5;
  DWORD local_4;
  
  sPerfLog = (HANDLE)bEnable;
  if (bEnable != 0) {
    local_5 = 0xd;
    hFile = CreateFileA(s_C__D2_Performace_txt_10020bd0,0x40000000,2,(LPSECURITY_ATTRIBUTES)0x0,4,
                        0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0x0) {
      MessageBoxA((HWND)0x0,s_Error_creating_performance_logfi_10020d44,s_Error_10020d70,0x10);
      sPerfLog = hFile;
      return;
    }
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    uVar2 = 0xffffffff;
    pcVar3 = s_Busy_Games_Players_ActiveMonster_10020d04;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    WriteFile(hFile,s_Busy_Games_Players_ActiveMonster_10020d04,~uVar2 - 1,&local_4,
              (LPOVERLAPPED)0x0);
    WriteFile(hFile,&local_5,1,&local_4,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return;
}
#endif




void __fastcall PerfLog_SetPath(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar2 = 0xffffffff;
  do {
    pcVar4 = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = s_C__D2_Performace_txt_10020bd0;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pcVar5 = *(unsigned int *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  return;
}



/* DUPLICATE: PerfLog_WriteEntry */
#if 0
void PerfLog_WriteEntry(void)

{
  char cVar1;
  HANDLE hFile;
  uint uVar2;
  char *pcVar3;
  unsigned char local_105;
  DWORD local_104;
  char local_100 [256];
  
  _vsprintf_l(local_100,(byte *)s__d__d__d__d__d_10020d78);
  local_105 = 0xd;
  if (sPerfLog != (HANDLE)0x0) {
    hFile = CreateFileA(s_C__D2_Performace_txt_10020bd0,0x40000000,2,(LPSECURITY_ATTRIBUTES)0x0,4,
                        0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0x0) {
      MessageBoxA((HWND)0x0,s_Error_creating_performance_logfi_10020d44,s_Error_10020d70,0x10);
      sPerfLog = hFile;
      return;
    }
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    uVar2 = 0xffffffff;
    pcVar3 = local_100;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    WriteFile(hFile,local_100,~uVar2 - 1,&local_104,(LPOVERLAPPED)0x0);
    WriteFile(hFile,&local_105,1,&local_104,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return;
}
#endif




void __fastcall PerfLog_WriteString(char *param_1)

{
  char cVar1;
  HANDLE hFile;
  uint uVar2;
  char *pcVar3;
  unsigned char local_5;
  DWORD local_4;
  
  local_5 = 0xd;
  if (sPerfLog != (HANDLE)0x0) {
    hFile = CreateFileA(s_C__D2_Performace_txt_10020bd0,0x40000000,2,(LPSECURITY_ATTRIBUTES)0x0,4,
                        0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0x0) {
      MessageBoxA((HWND)0x0,s_Error_creating_performance_logfi_10020d44,s_Error_10020d70,0x10);
      sPerfLog = hFile;
      return;
    }
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    uVar2 = 0xffffffff;
    pcVar3 = param_1;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    WriteFile(hFile,param_1,~uVar2 - 1,&local_4,(LPOVERLAPPED)0x0);
    WriteFile(hFile,&local_5,1,&local_4,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return;
}



/* DUPLICATE: Token_AddOrUpdate */
#if 0
unsigned int __fastcall
Token_AddOrUpdate(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4,
                 unsigned int param_5)

{
  DWORD dwTickCount;
  int nCmpResult;
  unsigned int *pNewToken;
  unsigned int unaff_EBX;
  unsigned int *pCurToken;
  int *ppPrevNext;
  unsigned int unaff_retaddr;
  unsigned int dwTokenSize;
  unsigned int pZeroInit;
  
  dwTickCount = GetTickCount();
  ppPrevNext = (int *)&pTokenListHead;
  pNewToken = pTokenListHead;
  pCurToken = pTokenListHead;
  if (pTokenListHead != (unsigned int *)0x0) {
    do {
      if (dwTickCount - pNewToken[2] < 0x1d4c1) {
        ppPrevNext = pNewToken + 0xc;
      }
      else {
        *ppPrevNext = pNewToken[0xc];
        FOG_CrashDumpThread(0x96,0);
        pCurToken = pTokenListHead;
      }
      pNewToken = (unsigned int *)*ppPrevNext;
    } while (pNewToken != (unsigned int *)0x0);
    for (; pCurToken != (unsigned int *)0x0; pCurToken = (unsigned int *)pCurToken[0xc]) {
      nCmpResult = SStrCmp(pCurToken + 3,param_1,0x7fffffff);
      if (nCmpResult == 0) goto LAB_1000657b;
    }
  }
  pZeroInit = 0;
  dwTokenSize = 0x34;
  pNewToken = (unsigned int *)FOG_CrashDeadlockDetected(0x34,0);
  if (pNewToken != (unsigned int *)0x0) {
    pCurToken = pNewToken;
    for (nCmpResult = 0xd; nCmpResult != 0; nCmpResult = nCmpResult + -1) {
      *pCurToken = 0;
      pCurToken = pCurToken + 1;
    }
    pNewToken[1] = param_3;
    *pNewToken = unaff_retaddr;
    dwTickCount = GetTickCount();
    pNewToken[2] = dwTickCount;
    SStrCopy(pNewToken + 3,param_1,0x10);
    SStrCopy(pNewToken + 7,pZeroInit,0x10);
    pNewToken[0xb] = dwTokenSize;
    pNewToken[0xc] = pTokenListHead;
    pTokenListHead = pNewToken;
    return 1;
  }
  FOG_SetLogPrefix(s_ptToken_10020d8c,s_C__D2_Source_D2Server_PlayerToke_10020d98,0x35);
  _exit_wrapper(0xffffffff);
  pCurToken = (unsigned int *)0x0;
LAB_1000657b:
  pCurToken[1] = param_5;
  *pCurToken = param_4;
  dwTickCount = GetTickCount();
  pCurToken[2] = dwTickCount;
  SStrCopy(pCurToken + 7,param_2,0x10);
  pCurToken[0xb] = unaff_EBX;
  return 1;
}
#endif




unsigned int __fastcall Token_Validate(unsigned int param_1,int param_2,int param_3,unsigned int param_4)

{
  DWORD dwTickCount;
  int nCmpResult;
  int *ppPrevNext;
  unsigned int bIsValid;
  int *unaff_retaddr;
  int *pToken;
  
  dwTickCount = GetTickCount();
  ppPrevNext = (int *)&pTokenListHead;
  pToken = (int*)pTokenListHead;
  while( true ) {
    if (pToken == (int *)0x0) {
      return 0;
    }
    nCmpResult = SStrCmp((char*)pToken + 3,param_1,0x7fffffff);
    if (nCmpResult == 0) break;
    ppPrevNext = pToken + 0xc;
    pToken = (int *)pToken[0xc];
  }
  *ppPrevNext = pToken[0xc];
  if (((*pToken == param_2) && (pToken[1] == param_3)) && (dwTickCount - pToken[2] < 0x1d4c1)) {
    bIsValid = 1;
  }
  else {
    bIsValid = 0;
  }
  SStrCopy((char*)(intptr_t)param_4,(char*)(pToken + 7),0x10);
  *unaff_retaddr = pToken[0xb];
  FOG_CrashDumpThread(99,0);
  return bIsValid;
}



/* DUPLICATE: MCP_SendType1 */
#if 0
void __fastcall MCP_SendType1(undefined3 param_1)

{
  FOG_Send(ghGameServer,&uStack00000000,1,CONCAT13(1,param_1));
  return;
}
#endif




/* DUPLICATE: Server_SendVersionHandshake */
#if 0
void Server_SendVersionHandshake(void)

{
  unsigned char local_14;
  unsigned int local_13;
  unsigned int local_f;
  unsigned int local_b;
  unsigned int local_7;
  
                    // Server_SendVersionHandshake: Sends MCP version handshake (type 0x02). Magic:
                    // '86IXD2D', Version: 200.
  local_14 = 2;
  local_13 = 0x49583836;
  local_f = 0x44324456;
  local_b = 200;
  local_7 = 0;
  FOG_Send(ghGameServer,&local_14,0x11);
  return;
}
#endif




/* DUPLICATE: Server_SendGameList */
#if 0
void Server_SendGameList(void)

{
  unsigned char local_10c;
  unsigned int local_10b;
  unsigned int local_107;
  unsigned char local_103;
  
                    // Server_SendGameList: Sends the active game list to MCP (type 0x03). Sends 265
                    // bytes of game data.
  local_10b = 0;
  local_107 = 0;
  local_103 = 0;
  local_10c = 3;
  FOG_Send(ghGameServer,&local_10c,0x109);
  return;
}
#endif




/* DUPLICATE: Server_SendCharInfo */
#if 0
void __fastcall Server_SendCharInfo(int pCharInfoData,int bIsPlayerAccount)

{
  int iVar1;
  int iVar2;
  unsigned int uStack_238;
  int iStack_234;
  int pCharStats;
  unsigned int uStack_22c;
  unsigned char *puStack_228;
  int pAccountName;
  unsigned int uStack_220;
  unsigned 
  unsigned char charLevel;
  unsigned char charClass;
  unsigned char charDifficulty;
  unsigned char charStatusFlags;
  uint local_207;
  unsigned char local_203 [515];
  
                    // Server_SendCharInfo: Reads character data from pCharInfoData structure at
                    // offsets 0x84(charName), 0x85(charClass), 0x86(charDifficulty),
                    // 0x88(charLevel), 0x08(charStatusFlags), 0x74(pCharStats), 0x64(pAccountName).
                    // Serializes into GTM_CHARINFO packet (type 4).
  uStack_220 = 0x200;
  charName = *(unsigned int *)(pCharInfoData + 0x88);
  charLevel = *(unsigned char *)(pCharInfoData + 0x84);
  charClass = *(unsigned char *)(pCharInfoData + 0x85);
  charDifficulty = *(unsigned char *)(pCharInfoData + 0x86);
  charStatusFlags = *(unsigned char *)(pCharInfoData + 8);
  pAccountName = pCharInfoData + 100;
  puStack_228 = local_203;
  local_207 = (uintptr_t)(bIsPlayerAccount == 0);
  uStack_22c = 0x10006902;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  pCharStats = pCharInfoData + 0x74;
  iStack_234 = (intptr_t)&charName + iVar1 + 1;
  uStack_22c = 0x200;
  uStack_238 = 0x10006915;
  iVar2 = SStrCopy((char*)0, (char*)0, 0);
  iVar1 = (intptr_t)&charName + iVar2 + iVar1 + 2;
  uStack_238 = 0x200;
  iVar2 = SStrCopy(iVar1,&DAT_10023254,0);
  FOG_Send(ghGameServer,&uStack_238,
            iVar2 + 0x12 +
            CONCAT22((short)((uintptr_t)iVar1 >> 0x10),(short)iVar1 - ((short)&puStack_228 + 1)));
  return;
}
#endif




/* DUPLICATE: Server_EnumerateCharacters */
#if 0
unsigned int Server_EnumerateCharacters(void)

{
  int iVar1;
  int iVar2;
  unsigned char auStack_800 [2048];
  
                    // Enumerates all character headers from char server and sends each one via
                    // Server_SendCharInfo. The last entry in the enumeration has
                    // bIsPlayerAccount=1.
  D2GAME_10012();
  iVar1 = D2GAME_10015(auStack_800,0x400);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      Server_SendCharInfo((intptr_t)&uStack00000000,(uintptr_t)(iVar2 == iVar1 + -1));
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
    return 1;
  }
  return 1;
}
#endif




void Server_SendKeepAlive_v2(void)

{
  unsigned char local_8 [8];
  
  local_8[0] = 5;
  FOG_Send(ghGameServer,local_8,5);
  return;
}



void __fastcall Server_SendCreateGame(int gameMCPId,int gameToken,int serverToken)

{
  unsigned char local_10 [5];
  int local_b;
  
  Console_WriteGraphDisplay(0,(byte *)MCP___GTM_CREATEGAME__M_10020dc8);
  local_10[0] = 6;
  local_b = serverToken;
  FOG_Send(ghGameServer,local_10,0xd);
  return;
}



/* DUPLICATE: Server_SendJoinGame */
#if 0
void __fastcall
Server_SendJoinGame(unsigned int gameMCPId,unsigned int serverID,unsigned int playerID,unsigned int token)

{
  unsigned char local_14;
  unsigned int local_13;
  unsigned int local_f;
  unsigned int local_b;
  unsigned int local_7;
  
  Console_WriteGraphDisplay(0,(byte *)s__Server__GTM_JOINGAME_10020e1c);
  local_14 = 7;
  local_b = playerID;
  local_7 = token;
  local_13 = gameMCPId;
  local_f = serverID;
  FOG_Send(ghGameServer,&local_14,0x11);
  return;
}
#endif




/* DUPLICATE: Server_SendCharCreateSave */
#if 0
void Server_SendCharCreateSave
               (unsigned short charlvl,unsigned int charname,unsigned int charBinaryData,unsigned short classId,
               unsigned int charSaveSize)

{
  int iVar1;
  int iVar2;
  unsigned int uStack_230;
  unsigned char *puStack_22c;
  unsigned int uStack_228;
  unsigned int uStack_224;
  unsigned short local_20f;
  unsigned int local_20d;
  unsigned int local_209;
  unsigned short local_205;
  unsigned char local_203 [11];
  unsigned char auStack_1f8 [504];
  
  local_205 = classId;
  local_20d = charname;
  uStack_224 = 0x200;
  puStack_22c = local_203;
  uStack_228 = charSaveSize;
  local_20f = charlvl;
  local_209 = charBinaryData;
  uStack_230 = 0x10006bd4;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  iVar1 = (intptr_t)&local_20f + iVar1 + 1;
  uStack_230 = 0x200;
  iVar2 = SStrCopy(iVar1,charBinaryData,0);
  FOG_Send(ghGameServer,&uStack_230,iVar2 + 0x16 + (iVar1 - (intptr_t)&uStack00000000));
  return;
}
#endif




/* DUPLICATE: Server_SendCharCreateResult */
#if 0
void __fastcall
Server_SendCharCreateResult
          (unsigned int pThis,unsigned int param_2,unsigned short param_3,unsigned short param_4,
          unsigned short param_5)

{
  int iVar1;
  unsigned char *puStack_218;
  unsigned int uStack_214;
  unsigned int uStack_210;
  unsigned char local_20c;
  unsigned int local_20b;
  unsigned short local_207;
  unsigned short local_205;
  unsigned short local_203;
  unsigned char local_201 [513];
  
  local_207 = param_3;
  local_205 = param_4;
  uStack_210 = 0x200;
  puStack_218 = local_201;
  local_20c = 10;
  local_203 = param_5;
  uStack_214 = param_2;
  local_20b = pThis;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  FOG_Send(ghGameServer,&puStack_218,iVar1 + 0xc);
  return;
}
#endif




/* DUPLICATE: Server_SendPlayerLeave */
#if 0
void Server_SendPlayerLeave(void)

{
  unsigned char pktBuf [8];
  
  pktBuf[0] = 9;
  FOG_Send(ghGameServer,pktBuf,5);
  return;
}
#endif




/* DUPLICATE: Server_SendGameMsg */
#if 0
void __fastcall Server_SendGameMsg(undefined3 wMsgData)

{
  FOG_Send(ghGameServer,&uStack00000000,1,CONCAT13(0xb,wMsgData));
  return;
}
#endif




/* DUPLICATE: Server_SendFileData */
#if 0
unsigned int __fastcall Server_SendFileData(char *szFileName,int pFileBuffer,int nFileSize)

{
  char cVar1;
  unsigned int uVar2;
  uint uVar3;
  uint uVar4;
  char *pSrc;
  unsigned int *pSrcDword;
  char *pDest;
  unsigned int *pDestDword;
  unsigned char msgType;
  char acStack_19b [4];
  ushort nBytesSent;
  ushort nChunkSize;
  unsigned short uStack_193;
  unsigned int auStack_191 [100];
  
  if (nFileSize == 0) {
    return 1;
  }
  uVar3 = 0xffffffff;
  do {
    pSrc = szFileName;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pSrc = szFileName + 1;
    cVar1 = *szFileName;
    szFileName = pSrc;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  msgType = 0xc;
  pSrc = pSrc + -uVar3;
  pDest = acStack_19b;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(unsigned int *)pDest = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest = pDest + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pDest = *pSrc;
    pSrc = pSrc + 1;
    pDest = pDest + 1;
  }
  uStack_193 = (unsigned short)nFileSize;
  nBytesSent = 0;
  do {
    nChunkSize = 400;
    if (nFileSize < 0x191) {
      nChunkSize = (ushort)nFileSize;
    }
    pSrcDword = (unsigned int *)((uintptr_t)nBytesSent + pFileBuffer);
    pDestDword = auStack_191;
    for (uVar3 = (uintptr_t)(nChunkSize >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
      *pDestDword = *pSrcDword;
      pSrcDword = pSrcDword + 1;
      pDestDword = pDestDword + 1;
    }
    for (uVar3 = nChunkSize & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(unsigned char *)pDestDword = *(unsigned char *)pSrcDword;
      pSrcDword = (unsigned int *)((intptr_t)pSrcDword + 1);
      pDestDword = (unsigned int *)((intptr_t)pDestDword + 1);
    }
    uVar2 = FOG_Send(ghGameServer,&msgType,CONCAT22(uStack_193,nChunkSize) + 0xb);
    nBytesSent = nBytesSent + nChunkSize;
    nFileSize = nFileSize - (uintptr_t)nChunkSize;
  } while (nFileSize != 0);
  return uVar2;
}
#endif




void __fastcall MCP_SendFileDataToServer(char *szFileName)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int nFileSize;
  int pFileBuffer;
  char *pSrc;
  unsigned int *pSrcDword;
  char *pDest;
  unsigned int *pDestDword;
  unsigned char uStack00000008;
  ushort uStack0000000d;
  ushort uStack0000000f;
  unsigned short uStack00000011;
  
  uVar2 = 0xffffffff;
  do {
    pSrc = szFileName;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pSrc = szFileName + 1;
    cVar1 = *szFileName;
    szFileName = pSrc;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  uStack00000008 = 0xc;
  pSrc = pSrc + -uVar2;
  pDest = (char*)&uStack00000009;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pDest = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest = pDest + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pDest = *pSrc;
    pSrc = pSrc + 1;
    pDest = pDest + 1;
  }
  uStack00000011 = (unsigned short)nFileSize;
  uStack0000000d = 0;
  do {
    uStack0000000f = 400;
    if (nFileSize < 0x191) {
      uStack0000000f = (ushort)nFileSize;
    }
    pSrcDword = (unsigned int *)((uintptr_t)uStack0000000d + pFileBuffer);
    pDestDword = (unsigned int *)&uStack00000011;
    for (uVar2 = (uintptr_t)(uStack0000000f >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
      *pDestDword = *pSrcDword;
      pSrcDword = pSrcDword + 1;
      pDestDword = pDestDword + 1;
    }
    for (uVar2 = uStack0000000f & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(unsigned char *)pDestDword = *(unsigned char *)pSrcDword;
      pSrcDword = (unsigned int *)((intptr_t)pSrcDword + 1);
      pDestDword = (unsigned int *)((intptr_t)pDestDword + 1);
    }
    FOG_Send(ghGameServer,&uStack00000008,CONCAT22(uStack00000011,uStack0000000f) + 0xb);
    uStack0000000d = uStack0000000d + uStack0000000f;
    nFileSize = nFileSize - (uintptr_t)uStack0000000f;
  } while (nFileSize != 0);
  return;
}



/* DUPLICATE: Server_SendCharCreateRequest */
#if 0
void __fastcall
Server_SendCharCreateRequest(char *param_1,unsigned char param_2,char *param_3,unsigned int param_4)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pSrc;
  char *pDest;
  unsigned char local_1c;
  unsigned char local_1b;
  char local_1a [4];
  unsigned int local_16;
  char local_12 [18];
  
  local_16 = param_4;
  uVar2 = 0xffffffff;
  do {
    pSrc = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pSrc = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pSrc;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  local_1c = 0xe;
  pSrc = pSrc + -uVar2;
  pDest = local_1a;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pDest = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest = pDest + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pDest = *pSrc;
    pSrc = pSrc + 1;
    pDest = pDest + 1;
  }
  uVar2 = 0xffffffff;
  do {
    pSrc = param_3;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pSrc = param_3 + 1;
    cVar1 = *param_3;
    param_3 = pSrc;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pSrc = pSrc + -uVar2;
  pDest = local_1a + 8;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(unsigned int *)pDest = *(unsigned int *)pSrc;
    pSrc = pSrc + 4;
    pDest = pDest + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pDest = *pSrc;
    pSrc = pSrc + 1;
    pDest = pDest + 1;
  }
  local_1b = param_2;
  FOG_Send(ghGameServer,&local_1c,0x1a);
  return;
}
#endif




/* DUPLICATE: MCP_SendCharCreateWithDedup */
#if 0
unsigned int __fastcall
MCP_SendCharCreateWithDedup
          (unsigned int param_1,uint param_2,unsigned int param_3,uint param_4,uint param_5,uint param_6
          )

{
  uint *pRecordEntry;
  int nNameLen;
  unsigned int uVar1;
  unsigned int extraout_ECX;
  uint extraout_EDX;
  unsigned char auStack_201 [513];
  
  if (4 < (ushort)param_2) {
    FOG_SetLogPrefix(s_wClass_0x3c_NUM_PLAYERCLASS_10020e78,s_C__D2_Source_D2Server_CORE_ToMCP_10020e98,0x129)
    ;
    _exit_wrapper(0xffffffff);
    param_1 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  if ((param_6 & 4) == 0) {
    if ((DAT_100232b4 < param_5) || ((DAT_100232b4 <= param_5 && (DAT_100232b0 <= param_4))))
    goto LAB_10007008;
    pRecordEntry = (uint *)(&DAT_100232b8 + (param_2 & 0xffff) * 8);
  }
  else {
    if ((DAT_1002326c < param_5) || ((DAT_1002326c <= param_5 && (sMCPRecvRecord <= param_4))))
    goto LAB_10007008;
    pRecordEntry = &DAT_10023270 + (param_2 & 0xffff) * 2;
  }
  if ((param_5 <= pRecordEntry[1]) && ((param_5 < pRecordEntry[1] || (param_4 < *pRecordEntry)))) {
    return 0;
  }
LAB_10007008:
  nNameLen = SStrCopy(auStack_201,param_1,0x200);
  uVar1 = FOG_Send(ghGameServer,&uStack00000000,nNameLen + 0x10);
  return uVar1;
}
#endif




/* DUPLICATE: Server_SendCharDelete */
#if 0
void __fastcall Server_SendCharDelete(unsigned int param_1,unsigned int param_2,ushort param_3)

{
  int iVar1;
  unsigned int extraout_EDX;
  char *pcStack_214;
  char *pcStack_210;
  unsigned int uStack_20c;
  char local_201 [513];
  
  if (4 < param_3) {
    uStack_20c = 0x15d;
    pcStack_210 = s_C__D2_Source_D2Server_CORE_ToMCP_10020e98;
    pcStack_214 = s_wClass_0x3c_NUM_PLAYERCLASS_10020e78;
    FOG_SetLogPrefix((char*)0, (char*)0, 0);
    uStack_20c = 0x100070cf;
    _exit_wrapper(0xffffffff);
    param_2 = extraout_EDX;
  }
  uStack_20c = 0x200;
  pcStack_214 = local_201;
  pcStack_210 = (char *)param_2;
  iVar1 = SStrCopy((char*)0, (char*)0, 0);
  FOG_Send(ghGameServer,&pcStack_214,iVar1 + 8);
  return;
}
#endif




void __fastcall MCP_SendCharUpload(unsigned short *param_1)

{
  unsigned char local_1c;
  unsigned short local_1b;
  unsigned short local_19;
  unsigned short local_17;
  unsigned short local_15;
  unsigned int local_13;
  unsigned int local_f;
  unsigned int local_b;
  unsigned int local_7;
  unsigned char local_3;
  
  local_1b = *param_1;
  local_17 = param_1[1];
  local_19 = 0x400;
  local_15 = 0x400;
  local_13 = 0;
  local_f = 0;
  local_b = 0;
  local_7 = 0;
  local_3 = *(unsigned char *)(param_1 + 2);
  local_1c = 0x11;
  FOG_Send(ghGameServer,&local_1c,0x1a);
  return;
}



/* DUPLICATE: GameServer_Destructor */
#if 0
void __fastcall GameServer_Destructor(unsigned int *pServerObj)

{
  void *_this;
  int *pPrevLink;
  int *pNode;
  uint nBucketIdx;
  int nBucketOffset;
  void *pvStack_c;
  unsigned char *puStack_8;
  int local_4;
  int nNodeCount;
  
                    // GameServer destructor. Frees all allocated game data entries, cleans up hash
                    // tables, deletes critical section. Called during server shutdown.
  local_4 = 0xffffffff;
  puStack_8 = &LAB_1001a4c5;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  DeleteCriticalSection((LPCRITICAL_SECTION)(pServerObj + 0x14));
  *pServerObj = &g_GameServerVtable2;
  local_4 = 2;
  while (nBucketOffset = pServerObj[0x10], 0 < nBucketOffset) {
    GameData_ChunkClearEntry(nBucketOffset);
    SMemFree((void*)(nBucketOffset),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (_this = (void *)pServerObj[0xc], 0 < (intptr_t)_this) {
    GameData_DeletingDestructor2(_this,0);
    SMemFree((void*)(_this),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  (*(unsigned short*)&(local_4)) = 3;
  pNode = pServerObj + 0xf;
  while (0 < (intptr_t)pServerObj[0x10]) {
    GameData_ListNode_Detach4((int *)(pServerObj[0xe] + pServerObj[0x10]));
  }
  (*(unsigned short*)&(local_4)) = 1;
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode2(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = pServerObj[0x10];
    *pNode = 0;
    pServerObj[0x10] = 0;
  }
  (*(unsigned short*)&(local_4)) = 4;
  pNode = pServerObj + 0xb;
  while (0 < (intptr_t)pServerObj[0xc]) {
    GameData_ListNode_Detach2((int *)(pServerObj[10] + pServerObj[0xc]));
  }
  local_4 = (uintptr_t)(*((unsigned int*)&(local_4)+1)) << 8;
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = pServerObj[0xc];
    *pNode = 0;
    pServerObj[0xc] = 0;
  }
  *pServerObj = &g_GameServerVtable1;
  pServerObj[4] = 0;
  local_4 = 6;
  GameDataPool_DetachAll3(pServerObj + 1);
  nBucketIdx = 0;
  if (pServerObj[6] != 0) {
    nBucketOffset = 0;
    do {
      while( true ) {
        nNodeCount = *(int *)(pServerObj[7] + nBucketOffset + 8);
        if (nNodeCount < 1) break;
        pNode = GameData_PoolGetBeginNode((void *)(pServerObj[7] + nBucketOffset),nNodeCount);
        GameData_ListNode_Detach2(pNode);
      }
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)pServerObj[6]);
  }
  local_4 = CONCAT31((*((unsigned int*)&(local_4)+1)),5);
  GameDataPool_FreeList((intptr_t)(pServerObj + 5));
  local_4 = 7;
  GameDataPool_DetachAll3(pServerObj + 1);
  local_4 = 0xffffffff;
  GameData_ListNode_Detach2(pServerObj + 2);
  pExceptionList = pvStack_c;
  return;
}
#endif




void Server_CallGlobalInitTable(void)

{
  unsigned int *puVar1;
  
  puVar1 = &g_InitFuncTableStart;
  do {
    if ((void *)*puVar1 != (void *)0x0) {
      ((void (*)(void))*puVar1)();
    }
    puVar1 = puVar1 + 1;
  } while (puVar1 < &g_InitFuncTableEnd);
  return;
}



// D2Server.Console_WriteGraphDisplay (10007550) - Logs a formatted message to the console dialog
// (ghConsoleDlg). Builds the text via FUN_1000ad3a (vsprintf), posts WM_USER message 0x401, and
// triggers a repaint of the graph display. FOG_CrashDeadlockDetected/FOG_DisplayError are the FOG logging pair. Matches
// Display.cpp source string.

/* DUPLICATE: Console_WriteGraphDisplay */
#if 0
void __cdecl Console_WriteGraphDisplay(int bAlsoDebugFile,byte *szFormat)

{
  char cVar1;
  LPARAM lParam;
  int iVar2;
  char *pcVar3;
  char local_100 [256];
  
  _vsnprintf(local_100,szFormat,(unsigned int *)&uStack00000008);
  if (bAlsoDebugFile != 0) {
    FOG_DisplayError((char*)0);
  }
  iVar2 = -1;
  pcVar3 = local_100;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  lParam = FOG_CrashDeadlockDetected(0x123,0);
  SStrCopy(lParam,&uStack00000000,0x7fffffff);
  PostMessageA(ghConsoleDlg,0x401,0,lParam);
  return;
}
#endif




/* DUPLICATE: CharServer_SendType7Packet */
#if 0
int __fastcall CharServer_SendType7Packet(char *szServerName)

{
  int bVar1;
  
  bVar1 = CharServer_SendType7Packet(szServerName);
  return bVar1;
}
#endif




void __fastcall
Thunk_Server_SendCharCreateResult
          (unsigned int param_1,unsigned int param_2,unsigned short param_3,unsigned short param_4,
          unsigned short param_5)

{
  Server_SendCharCreateResult(param_1,param_2,param_3,param_4,param_5);
  return;
}



void Thunk_Server_SendCharCreateSave
               (unsigned short param_1,unsigned int param_2,unsigned int param_3,unsigned short param_4,
               char *param_5)

{
  CharServer_SendType7Packet(param_5);
  Server_SendCharCreateSave(param_1,param_2,param_3,param_4,(uintptr_t)param_5);
  return;
}



/* DUPLICATE: CharServer_SendGameData */
#if 0
int __fastcall CharServer_SendGameData(char *param_1,unsigned int param_2)

{
  int bVar1;
  
  bVar1 = CharServer_SendGameData(param_1,param_2);
  return bVar1;
}
#endif




void __thiscall Thunk_SrvData_SendRecord(void *_this,ushort *param_1,uint param_2)

{
  if (*param_1 != param_2) {
    FOG_DisplayError(s_Invalid_size_of_record_in_SrvDat_10021098,_this);
    FOG_SetLogPrefix((char*)&DAT_10021094,s_C__D2_Source_D2Server_CORE_WinMa_10021064,0x174);
    param_1 = (ushort *)_exit_wrapper(0xffffffff);
  }
  CharServer_SendType2Packet(param_1,(char)param_2);
  return;
}



/* DUPLICATE: Server_SendKeepAlive */
#if 0
void Server_SendKeepAlive(void)

{
  Server_SendKeepAlive();
  return;
}
#endif




// D2Server.Server_SendFileData (10007760) - Thin wrapper that forwards (param_1, param_2) to the
// game-data file send routine (FUN_10007740/Server_SendFileData). Used as the ordinal-exported
// entry for sending a file to connected clients via the MCP/game layer.

/* DUPLICATE: Server_SendFileData */
#if 0
void __fastcall Server_SendFileData(char *param_1,int param_2,int param_3)

{
  Server_SendFileData(param_1,param_2,param_3);
  return;
}
#endif




void __fastcall
Thunk_Server_SendCharCreateRequest
          (char *param_1,unsigned char param_2,char *param_3,unsigned int param_4)

{
  Server_SendCharCreateRequest(param_1,param_2,param_3,param_4);
  return;
}



void __fastcall
Thunk_MCP_SendCharCreateWithDedup
          (unsigned int param_1,uint param_2,unsigned int param_3,uint param_4,uint param_5,uint param_6
          )

{
  MCP_SendCharCreateWithDedup(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



void __fastcall Thunk_Server_SendCharDelete(unsigned int param_1,unsigned int param_2,ushort param_3)

{
  Server_SendCharDelete(param_1,param_2,param_3);
  return;
}



unsigned int Console_WindowProc(HWND param_1,uint param_2,uint param_3,LPARAM param_4)

{
  HWND hDlg;
  uint wMenuId;
  HMENU hMenu;
  int nResult;
  LRESULT lItemCount;
  WPARAM wParam;
  unsigned char local_40 [64];
  
  hDlg = param_1;
  if (param_2 < 0x112) {
    if (param_2 == 0x111) {
      wMenuId = param_3 & 0xffff;
      if (wMenuId < 0x3f5) {
        if (wMenuId == 0x3f4) {
          hMenu = GetMenu(param_1);
          nResult = Console_GetCmdDialogHandle();
          if (nResult != 0) {
            CheckMenuItem(hMenu,0x3f4,0);
            Console_HideCmdDialog();
            return 0;
          }
          CheckMenuItem(hMenu,0x3f4,8);
          Console_ShowCmdDialog(hDlg);
          return 0;
        }
        if (wMenuId == 2) {
LAB_10007b98:
          D2GAME_10006();
          nResult = Console_GetMainDialogHandle();
          if (nResult != 0) {
            Console_DestroyGraphDisplay();
          }
          nResult = Console_GetCmdDialogHandle();
          if (nResult != 0) {
            Console_HideCmdDialog();
          }
          PostQuitMessage(0);
          return 1;
        }
        if (wMenuId == 0x3f2) {
          param_1 = (HWND)_ftime64((int *)&param_1);
          _ftol2_sse((intptr_t)param_1,stStartTime);
          __ftol();
          _vsprintf_l((char*)local_40,(byte *)s__d__02d__02d_100210e0);
          SendDlgItemMessageA((HWND)ghConsoleDlg,0x3f9,0xc,0,(LPARAM)local_40);
          Console_RefreshDisplay();
          return 1;
        }
        if (wMenuId == 0x3f3) {
          hMenu = GetMenu(param_1);
          nResult = Console_GetMainDialogHandle();
          if (nResult != 0) {
            CheckMenuItem(hMenu,0x3f3,0);
            Console_DestroyGraphDisplay();
            return 0;
          }
          CheckMenuItem(hMenu,0x3f3,8);
          Console_InitGraphDisplay(hDlg);
          return 0;
        }
      }
      else {
        if (wMenuId == 0x3f5) goto LAB_10007b98;
        if (wMenuId == 0x3f9) {
          hMenu = GetMenu(param_1);
          nResult = Console_IsPerfLogEnabled();
          if (nResult != 0) {
            CheckMenuItem(hMenu,0x3f9,0);
            PerfLog_Init(0);
            return 0;
          }
          CheckMenuItem(hMenu,0x3f9,8);
          PerfLog_Init(1);
          return 0;
        }
      }
    }
    else {
      if (param_2 == 2) {
        hDlg = GetDlgItem(param_1,0x3fd);
        SetWindowLongA(hDlg,-4,(intptr_t)g_lpOldGraphWndProc);
        return 0;
      }
      if (param_2 == 0x110) {
        hDlg = GetDlgItem(param_1,0x3fd);
        g_lpOldGraphWndProc = SetWindowLongA(hDlg,-4,0x10001203);
        return 1;
      }
    }
  }
  else if (param_2 == 0x401) {
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fb,0x181,0xffffffff,param_4);
    lItemCount = SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fb,0x18b,0,0);
    wParam = lItemCount - 1;
    if (99 < (intptr_t)wParam) {
      SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fb,0x182,0,0);
      wParam = lItemCount - 2;
    }
    SendDlgItemMessageA((HWND)ghConsoleDlg,0x3fb,0x186,wParam,0);
    FOG_CrashDumpThread(0x23d,0);
  }
  return 0;
}



// D2Server.Server_MainLoopThread (10007d40) - The server's main message loop thread proc. Calls
// CharServer_PollAndDispatch, drains FOG_GetSyncTime/FOG_LeaveCriticalSection message queues, dispatch MCP incoming
// messages, sends game keepalive via Server_SendGameMsg, ticks game via Server_GameTick, and runs
// CharServer_HeartbeatCheck every nServerTick interval. On CharServer full disconnect it triggers
// shutdown and destroys the console graph display (Console_DestroyGraphDisplay). Matches
// ToMCP.cpp/FromMCP.cpp source strings.

unsigned int Server_MainLoopThread(void)

{
  ushort wMsgSize;
  int nResult;
  DWORD dwTickCount;
  undefined3 uLastTickUnused;
  byte abStack_400 [1024];
  
  if (bShutdownFlag != 0) {
    return 1;
  }
  do {
    CharServer_PollAndDispatch();
    nResult = (intptr_t)FOG_GetSyncTime((intptr_t)ghGameServer,0);
    if (nResult == 0) {
      while (wMsgSize = FOG_LeaveCriticalSection(ghGameServer,abStack_400,0x400), wMsgSize != 0) {
        MCP_DispatchIncomingMessage(abStack_400,(uintptr_t)wMsgSize);
      }
    }
    dwTickCount = GetTickCount();
    if ((dwLastKeepAliveTick == 0) || (30000 < dwTickCount - dwLastKeepAliveTick)) {
      uLastTickUnused = (undefined3)dwLastKeepAliveTick;
      dwLastKeepAliveTick = dwTickCount;
      Server_SendGameMsg(uLastTickUnused);
    }
    Server_GameTick();
    nResult = CharServer_HeartbeatCheck();
    if (nResult == 0) {
      D2GAME_10006();
      nResult = Console_GetMainDialogHandle();
      if (nResult != 0) {
        Console_DestroyGraphDisplay();
      }
      nResult = Console_GetCmdDialogHandle();
      if (nResult != 0) {
        Console_HideCmdDialog();
      }
      FOG_DisplayError(s_FATAL__Lost_connection_to_charac_100210f0);
      bShutdownFlag = 1;
    }
    Sleep(1);
  } while (bShutdownFlag == 0);
  return 1;
}



// D2Server.Server_ShutdownFromMCP (10007e80) - Remote shutdown handler triggered by the MCP
// "Shutdown Remotely by MCP" message. Logs FOG_DisplayError, calls D2GAME_10006 (game cleanup), destroys
// the graph display, hides the command dialog, and sets bShutdownFlag=1 to terminate the main loop.
// Matches ToMCP.cpp remote-shutdown path.

/* DUPLICATE: Server_ShutdownFromMCP */
#if 0
void Server_ShutdownFromMCP(void)

{
  int iVar1;
  
  FOG_DisplayError(s_Shutdown_Remotely_by_MCP_100211dc);
  D2GAME_10006();
  iVar1 = Console_GetMainDialogHandle();
  if (iVar1 != 0) {
    Console_DestroyGraphDisplay();
  }
  iVar1 = Console_GetCmdDialogHandle();
  if (iVar1 != 0) {
    Console_HideCmdDialog();
  }
  bShutdownFlag = 1;
  return;
}
#endif




// D2Server.Server_WorkerLoopThread (10007f50) - Background worker thread proc. Polls
// D2GAME_10006/D2NET_10033 event queues and sleeps ~5ms per iteration. Decrements
// nActiveWorkerThreads on exit. Created from Server_MainLoopThread startup.

unsigned int __fastcall Server_WorkerLoopThread(int param_1)

{
  uint dwEventMask;
  int nNetResult;
  byte bModCounter;
  byte bLoopCount;
  
  D2GAME_10041();
  bLoopCount = 0;
  do {
    if (bShutdownFlag != 0) {
      InterlockedDecrement((LONG *)&nActiveWorkerThreads);
      return 1;
    }
    dwEventMask = D2GAME_10043();
    if (param_1 == 0) {
LAB_10007f82:
      nNetResult = D2NET_10022(((intptr_t)dwEventMask < 0) - 1 & dwEventMask);
      if (nNetResult != 0) {
        D2GAME_10003();
      }
    }
    else {
      bModCounter = bLoopCount & 7;
      bLoopCount = bLoopCount + 1;
      if (bModCounter == 0) goto LAB_10007f82;
    }
    if (param_1 != 0) {
      D2GAME_10045();
    }
  } while( true );
}



// D2Server.Server_IdleHandler (10007ff0) - Empty no-op routine. Exposed as Ordinal_10002 through
// the jump stub at 100010dc. Likely a placeholder/hook stub registered during initialization.

void Server_IdleHandler(void)

{
  return;
}



// Setting prototype: unsigned int __stdcall Server_MainEntry(HINSTANCE hInstance, HINSTANCE
// hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

/* DUPLICATE: Server_MainEntry */
#if 0
int Server_MainEntry(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)

{
  int nResult;
  HANDLE hWorkerThread;
  BOOL bMsgAvailable;
  HWND hDialog;
  unsigned int *pInitTable;
  BOOL bRunning;
  struct tagMSG tStack_1c;
  struct tagMSG *pMsg;
  unsigned int uParam8;
  unsigned int uParam9;
  
                    // Main server entry point. Called from D2SERVE.EXE. Initializes Storm, opens
                    // MPQ archives, creates console dialog, loads Bnclient.dll, creates worker
                    // threads, enters message pump.
  g_hMainInstance = hInstance;
  FOG_CharToUpper();
  Server_OpenMPQArchives();
  pInitTable = &g_InitFuncTableStart;
  do {
    if ((void *)*pInitTable != (void *)0x0) {
      ((void (*)(void))*pInitTable)();
    }
    pInitTable = pInitTable + 1;
  } while (pInitTable < &g_InitFuncTableEnd);
  ghConsoleDlg = CreateDialogParamA(g_hMainInstance,(LPCSTR)0x66,(HWND)0x0,(DLGPROC)&LAB_100010f0,0)
  ;
  ShowWindow(ghConsoleDlg,nCmdShow);
  UpdateWindow(ghConsoleDlg);
  FOG_InitErrorMgr();
  if (bServerRunning != 0) {
    Bnclient_LoadRunGame();
  }
  ReturnZero();
  nResult = D2Lang_Initialize();
  if (nResult != 0) {
    uParam9 = 0;
    uParam8 = 1;
    nResult = ReturnZero();
    STATES_CheckStateMaskStayDeath(nResult,uParam8,uParam9);
    SERVER_Initialize(0,0);
    SERVER_SetHackListEnabled(1);
    D2GAME_10046();
    if (bServerRunning != 0) {
      MCP_ConnectToServer();
      CharServer_ConnectAll(ghConsoleDlg);
      D2GAME_10023(&pGameEngineFuncTable);
    }
    D2GAME_10002(&g_GameEngineData1,&g_GameEngineData2);
    stStartTime = _ftime64(&stStartTime);
    D2GAME_10039();
    if (bServerRunning != 0) {
      hWorkerThread =
           CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                        (LPTHREAD_START_ROUTINE)&lpStartAddress_1000133e,(LPVOID)0x0,0,
                        (LPDWORD)&tStack_1c.wParam);
      CloseHandle(hWorkerThread);
    }
    nResult = FOG_SetExceptionFilter();
    for (nResult = *(int *)(nResult + 0x28); nResult != 0; nResult = nResult + -1) {
      InterlockedIncrement((LONG *)&nActiveWorkerThreads);
      hWorkerThread =
           CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,
                        (LPTHREAD_START_ROUTINE)&lpStartAddress_10001104,(LPVOID)0x0,0,
                        (LPDWORD)&nCmdShow);
      if (hWorkerThread == (HANDLE)0x0) {
        InterlockedDecrement((LONG *)&nActiveWorkerThreads);
      }
      else {
        CloseHandle(hWorkerThread);
      }
    }
    Perf_InitSystem();
    Perf_InitFrameTimer(2);
    Perf_SnapshotCounter();
    Console_WriteGraphDisplay(1,(byte *)s__SERVER__Finished_Loading____100211fc);
    bRunning = 1;
    tStack_1c.wParam = 0;
    nGameCount = 0;
    nPlayerCount = 0;
    do {
      if (bShutdownFlag != 0) break;
      bMsgAvailable = PeekMessageA(&tStack_1c,(HWND)0x0,0,0,0);
      if (bMsgAvailable == 0) {
        Sleep(1);
      }
      else {
        bRunning = GetMessageA(&tStack_1c,(HWND)0x0,0,0);
        pMsg = &tStack_1c;
        hDialog = (HWND)Console_GetMainDialogHandle();
        bMsgAvailable = IsDialogMessageA(hDialog,pMsg);
        if (bMsgAvailable != 0) {
          pMsg = &tStack_1c;
          hDialog = (HWND)Console_GetCmdDialogHandle();
          bMsgAvailable = IsDialogMessageA(hDialog,pMsg);
          if (bMsgAvailable != 0) goto LAB_10008254;
        }
        TranslateMessage(&tStack_1c);
        DispatchMessageA(&tStack_1c);
      }
LAB_10008254:
    } while (bRunning != 0);
  }
  bShutdownFlag = 1;
  while (0 < (intptr_t)nActiveWorkerThreads) {
    Sleep(100);
  }
  bShutdownFlag = 0;
  Console_ClearGameList();
  D2GAME_10040();
  SERVER_Release();
  if (bServerRunning != 0) {
    MCP_DisconnectFromServer();
    CharServer_CloseAllConnections();
  }
  D2GAME_10050();
  STATES_CheckStateMaskExp();
  D2Lang_Uninitialize();
  D2COMMON_10983();
  Server_FreeMemory();
  return 0;
}
#endif




unsigned int * __fastcall GameServer_Constructor(unsigned int *pServerObj)

{
  unsigned int *_this;
  unsigned int *pNode;
  int nBucketOffset;
  uint nBucketIdx;
  void *local_c;
  unsigned char *puStack_8;
  unsigned int local_4;
  
                    // GameServer object constructor. Creates TSHashObjectChunk<SGAMEDATA,
                    // HASHKEY_NONE> structure with 3 hash buckets, TSExplicitList<SGAMEDATA> with
                    // 96 entries, and initializes a critical section for thread safety.
  local_4 = 0xffffffff;
  puStack_8 = (unsigned char*)&g_GameServerCtorUnwind;
  local_c = pExceptionList;
  pExceptionList = &local_c;
  GameData_PoolInit(pServerObj + 1);
  local_4 = 0;
  GameData_PoolZeroEntry(pServerObj + 5);
  local_4 = CONCAT31((*((unsigned int*)&(local_4)+1)),1);
  *pServerObj = (uintptr_t)&g_GameServerVtable1;
  pServerObj[4] = 0;
  GameData_PoolReserve(pServerObj + 1,0xc);
  pServerObj[9] = 3;
  GameData_PoolResize(pServerObj + 5,4);
  nBucketIdx = 0;
  nBucketOffset = 0;
  do {
    GameData_PoolReserve((void *)(pServerObj[7] + nBucketOffset),4);
    nBucketIdx = nBucketIdx + 1;
    nBucketOffset = nBucketOffset + 0xc;
  } while (nBucketIdx <= (uintptr_t)pServerObj[9]);
  _this = pServerObj + 10;
  local_4 = 2;
  GameData_PoolInit2(_this);
  (*(unsigned short*)&(local_4)) = 3;
  *_this = 0xdddddddd;
  GameData_PoolInit3((intptr_t)_this);
  pNode = pServerObj + 0xe;
  (*(unsigned short*)&(local_4)) = 4;
  GameData_PoolSetCount(pNode);
  (*(unsigned short*)&(local_4)) = 5;
  *pNode = 0x10;
  List_InitNode((intptr_t)pNode);
  local_4 = CONCAT31((*((unsigned int*)&(local_4)+1)),6);
  *pServerObj = (uintptr_t)&g_GameServerVtable2;
  pServerObj[0xd] = 0x10;
  GameData_PoolReserve(_this,4);
  *pServerObj = (uintptr_t)&g_GameServerVtable3;
  pServerObj[0x12] = ~(uintptr_t)pServerObj & 0xfffffff;
  pServerObj[0x13] = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(pServerObj + 0x14));
  *pServerObj = (uintptr_t)&g_GameServerVtable4;
  pExceptionList = local_c;
  return pServerObj;
}



void GameData_Destroy(int param_1)

{
  GameData_RemoveAllEntries(param_1);
  SMemFree((void*)(param_1),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  return;
}



void HashTbl_FreeNode(void *param_1,int param_2,uint param_3)

{
  GameData_AllocGameEntry(param_1,1,param_2,param_3);
  return;
}



void __fastcall HashTbl_AllocNode(unsigned int *param_1)

{
  uint nBucketIdx;
  int nOffset;
  int nNodeData;
  
  param_1[4] = 0;
  while (0 < (intptr_t)param_1[3]) {
    GameData_ListNode_Detach2((int *)(param_1[1] + param_1[3]));
  }
  nBucketIdx = 0;
  if (param_1[6] != 0) {
    nOffset = 0;
    do {
      while (nNodeData = *(int *)(param_1[7] + nOffset + 8), 0 < nNodeData) {
        ((void (*)(int))(**(void ***)param_1))(nNodeData);
      }
      nBucketIdx = nBucketIdx + 1;
      nOffset = nOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)param_1[6]);
  }
  while (nOffset = param_1[0x10], 0 < nOffset) {
    GameData_ChunkClearEntry(nOffset);
    SMemFree((void*)(nOffset),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (nOffset = param_1[0xc], 0 < nOffset) {
    GameData_RemoveAllEntries(nOffset);
    SMemFree((void*)(nOffset),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  return;
}



void GameData_RemoveAllData(int param_1)

{
  GameData_RemoveAllEntries(param_1);
  SMemFree((void*)(param_1),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  return;
}



void GameData_AddData(void *param_1,int param_2,uint param_3)

{
  GameData_AllocGameEntry(param_1,1,param_2,param_3);
  return;
}



/* DUPLICATE: GameData_Destructor_HashBase */
#if 0
void __fastcall GameData_Destructor_HashBase(unsigned int *param_1)

{
  int *pNode;
  int *pPrevLink;
  int *pLinkSlot;
  uint nBucketIdx;
  int nBucketOffset;
  void *pvStack_c;
  unsigned char *puStack_8;
  uint local_4;
  uint nNextPtr;
  int nNodeCount;
  
  puStack_8 = &LAB_1001a581;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = &g_GameServerVtable1;
  local_4 = 1;
  param_1[4] = 0;
  while( true ) {
    if ((intptr_t)param_1[3] < 1) break;
    pNode = GameData_PoolGetBeginNode(param_1 + 1,param_1[3]);
    GameData_ListNode_Detach2(pNode);
  }
  nBucketIdx = 0;
  if (param_1[6] != 0) {
    nBucketOffset = 0;
    do {
      while( true ) {
        nNodeCount = *(int *)(param_1[7] + 8 + nBucketOffset);
        if (nNodeCount < 1) break;
        pNode = (int *)(*(int *)(param_1[7] + nBucketOffset) + nNodeCount);
        if (*pNode != 0) {
          nNextPtr = pNode[1];
          if ((intptr_t)nNextPtr < 0) {
            pLinkSlot = (int *)~nNextPtr;
          }
          else {
            pLinkSlot = (int *)((intptr_t)pNode + (nNextPtr - *(int *)(*pNode + 4)));
          }
          *pLinkSlot = *pNode;
          *(int *)(*pNode + 4) = pNode[1];
          *pNode = 0;
          pNode[1] = 0;
        }
      }
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)param_1[6]);
  }
  nBucketIdx = 0;
  local_4 = local_4 & 0xffffff00;
  if (param_1[6] != 0) {
    nBucketOffset = 0;
    do {
      GameDataPool_DetachList((int *)(param_1[7] + nBucketOffset));
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)param_1[6]);
  }
  if (param_1[7] != 0) {
    SMemFree(param_1[7],s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  local_4 = 2;
  pNode = param_1 + 2;
  while (0 < (intptr_t)param_1[3]) {
    pLinkSlot = (int *)(param_1[1] + param_1[3]);
    if (*pLinkSlot != 0) {
      pPrevLink = (int *)GameData_PoolIndexToNode(pLinkSlot,-1);
      *pPrevLink = *pLinkSlot;
      *(int *)(*pLinkSlot + 4) = pLinkSlot[1];
      *pLinkSlot = 0;
      pLinkSlot[1] = 0;
    }
  }
  nBucketOffset = *pNode;
  if (nBucketOffset != 0) {
    nBucketIdx = param_1[3];
    if ((intptr_t)nBucketIdx < 0) {
      pLinkSlot = (int *)~nBucketIdx;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pNode + (nBucketIdx - *(int *)(nBucketOffset + 4)));
    }
    *pLinkSlot = nBucketOffset;
    *(unsigned int *)(*pNode + 4) = param_1[3];
    *pNode = 0;
    param_1[3] = 0;
  }
  pExceptionList = pvStack_c;
  return;
}
#endif




void __fastcall GameData_RemoveAllFromList(int param_1)

{
  int *pBucketEntry;
  int *pLinkSlot;
  int nBucketOffset;
  uint nBucketIdx;
  uint local_4;
  int nNextPtr;
  
  *(unsigned int *)(param_1 + 0x10) = 0;
  while (0 < *(int *)(param_1 + 0xc)) {
    GameData_ListNode_Detach2((int *)(*(int *)(param_1 + 4) + *(int *)(param_1 + 0xc)));
  }
  local_4 = 0;
  if (*(int *)(param_1 + 0x18) != 0) {
    nBucketOffset = 0;
    do {
      while( true ) {
        pBucketEntry = (int *)(*(int *)(param_1 + 0x1c) + nBucketOffset);
        nNextPtr = pBucketEntry[2];
        if (nNextPtr < 1) break;
        pBucketEntry = (int *)(*pBucketEntry + nNextPtr);
        if (*pBucketEntry != 0) {
          nBucketIdx = pBucketEntry[1];
          if ((intptr_t)nBucketIdx < 0) {
            pLinkSlot = (int *)~nBucketIdx;
          }
          else {
            pLinkSlot = (int *)((intptr_t)pBucketEntry + (nBucketIdx - *(int *)(*pBucketEntry + 4)));
          }
          *pLinkSlot = *pBucketEntry;
          *(int *)(*pBucketEntry + 4) = pBucketEntry[1];
          *pBucketEntry = 0;
          pBucketEntry[1] = 0;
        }
      }
      local_4 = local_4 + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (local_4 < *(uint *)(param_1 + 0x18));
  }
  *(unsigned int *)(param_1 + 0x10) = 0;
  *(unsigned int *)(param_1 + 0x24) = 0;
  nBucketIdx = 0;
  if (*(int *)(param_1 + 0x18) != 0) {
    nBucketOffset = 0;
    do {
      GameData_ListNode_Clear((void *)(nBucketOffset + *(int *)(param_1 + 0x1c)),0);
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < *(uint *)(param_1 + 0x18));
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    SMemFree(*(int *)(param_1 + 0x1c),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  *(unsigned int *)(param_1 + 0x14) = 0;
  *(unsigned int *)(param_1 + 0x18) = 0;
  *(unsigned int *)(param_1 + 0x1c) = 0;
  return;
}



unsigned int * __thiscall GameData_DeletingDestructor1(void *_this,byte param_1)

{
  GameServer_Destructor((unsigned int*)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (unsigned int*)_this;
}



/* DUPLICATE: GameData_DeletingDestructor2 */
#if 0
int __thiscall GameData_DeletingDestructor2(void *_this,byte param_1)

{
  GameData_RemoveAllEntries((intptr_t)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (intptr_t)_this;
}
#endif




unsigned int * __thiscall GameData_DeletingDestructor4(void *_this,byte param_1)

{
  GameData_Destructor_ListBase((unsigned int*)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (unsigned int*)_this;
}



/* DUPLICATE: GameData_Destructor_ListBase */
#if 0
void __fastcall GameData_Destructor_ListBase(unsigned int *param_1)

{
  int *pPrevLink;
  int *pNode;
  uint nBucketIdx;
  int nBucketOffset;
  void *pvStack_c;
  unsigned char *puStack_8;
  int local_4;
  int nNodeCount;
  
  puStack_8 = &LAB_1001a5f5;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = &g_GameServerVtable2;
  local_4 = 2;
  while (nBucketOffset = param_1[0x10], 0 < nBucketOffset) {
    GameData_ChunkClearEntry(nBucketOffset);
    SMemFree((void*)(nBucketOffset),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (nBucketOffset = param_1[0xc], 0 < nBucketOffset) {
    GameDataPool_RemoveAll(nBucketOffset);
    SMemFree((void*)(nBucketOffset),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  (*(unsigned short*)&(local_4)) = 3;
  pNode = param_1 + 0xf;
  while (0 < (intptr_t)param_1[0x10]) {
    GameData_ListNode_Detach4((int *)(param_1[0xe] + param_1[0x10]));
  }
  (*(unsigned short*)&(local_4)) = 1;
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode2(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = param_1[0x10];
    *pNode = 0;
    param_1[0x10] = 0;
  }
  (*(unsigned short*)&(local_4)) = 4;
  pNode = param_1 + 0xb;
  while (0 < (intptr_t)param_1[0xc]) {
    GameData_ListNode_Detach2((int *)(param_1[10] + param_1[0xc]));
  }
  local_4 = (uintptr_t)(*((unsigned int*)&(local_4)+1)) << 8;
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = param_1[0xc];
    *pNode = 0;
    param_1[0xc] = 0;
  }
  *param_1 = &g_GameServerVtable1;
  param_1[4] = 0;
  local_4 = 6;
  GameDataPool_DetachAll3(param_1 + 1);
  nBucketIdx = 0;
  if (param_1[6] != 0) {
    nBucketOffset = 0;
    do {
      while( true ) {
        nNodeCount = *(int *)(param_1[7] + nBucketOffset + 8);
        if (nNodeCount < 1) break;
        pNode = GameData_PoolGetBeginNode((void *)(param_1[7] + nBucketOffset),nNodeCount);
        GameData_ListNode_Detach2(pNode);
      }
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)param_1[6]);
  }
  local_4 = CONCAT31((*((unsigned int*)&(local_4)+1)),5);
  GameDataPool_FreeList((intptr_t)(param_1 + 5));
  local_4 = 7;
  GameDataPool_DetachAll3(param_1 + 1);
  local_4 = 0xffffffff;
  GameData_ListNode_Detach2(param_1 + 2);
  pExceptionList = pvStack_c;
  return;
}
#endif




/* DUPLICATE: GameDataPool_ClearEntry */
#if 0
void __fastcall GameDataPool_ClearEntry(int *param_1)

{
  int *pNode;
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = param_1 + 1;
  while (0 < param_1[2]) {
    pNode = (int *)(*param_1 + param_1[2]);
    if (*pNode != 0) {
      nNextOffset = pNode[1];
      if ((intptr_t)nNextOffset < 0) {
        pLinkSlot = (int *)~nNextOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pNode + (nNextOffset - *(int *)(*pNode + 4)));
      }
      *pLinkSlot = *pNode;
      *(int *)(*pNode + 4) = pNode[1];
      *pNode = 0;
      pNode[1] = 0;
    }
  }
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = param_1[2];
    if ((intptr_t)nNextOffset < 0) {
      pNode = (int *)~nNextOffset;
    }
    else {
      pNode = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pNode = nSavedHead;
    *(int *)(*pHeadPtr + 4) = param_1[2];
    *pHeadPtr = 0;
    param_1[2] = 0;
  }
  return;
}
#endif




/* DUPLICATE: GameDataPool_DetachAll */
#if 0
void __fastcall GameDataPool_DetachAll(int *param_1)

{
  int *pNode;
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = param_1 + 1;
  while (0 < param_1[2]) {
    pNode = (int *)(*param_1 + param_1[2]);
    if (*pNode != 0) {
      nNextOffset = pNode[1];
      if ((intptr_t)nNextOffset < 0) {
        pLinkSlot = (int *)~nNextOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pNode + (nNextOffset - *(int *)(*pNode + 4)));
      }
      *pLinkSlot = *pNode;
      *(int *)(*pNode + 4) = pNode[1];
      *pNode = 0;
      pNode[1] = 0;
    }
  }
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = param_1[2];
    if ((intptr_t)nNextOffset < 0) {
      pNode = (int *)~nNextOffset;
    }
    else {
      pNode = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pNode = nSavedHead;
    *(int *)(*pHeadPtr + 4) = param_1[2];
    *pHeadPtr = 0;
    param_1[2] = 0;
  }
  return;
}
#endif




unsigned int * __thiscall GameData_DeletingDestructor3(void *_this,byte param_1)

{
  GameData_Destructor_HashBase((unsigned int*)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (unsigned int*)_this;
}



/* DUPLICATE: GameDataPool_FreeBackingArray */
#if 0
void __fastcall GameDataPool_FreeBackingArray(int param_1)

{
  int *pDetachedNode;
  int nBucketOffset;
  int *pBucket;
  uint nBucketIdx;
  void *local_c;
  unsigned char *puStack_8;
  unsigned int local_4;
  void **ppExceptionList;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_1001a62b;
  local_c = pExceptionList;
  nBucketOffset = 0;
  nBucketIdx = 0;
  pExceptionList = &local_c;
  ppExceptionList = &local_c;
  if (*(int *)(param_1 + 4) != 0) {
    do {
      pBucket = (int *)(*(int *)(param_1 + 8) + nBucketOffset);
      local_4 = 0;
      while (0 < pBucket[2]) {
        pDetachedNode = (int *)GameData_PoolAddOffset(pBucket[2],*pBucket);
        GameData_ListNode_Detach2(pDetachedNode);
      }
      local_4 = 0xffffffff;
      GameData_ListNode_Detach2(pBucket + 1);
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
      ppExceptionList = pExceptionList;
    } while (nBucketIdx < *(uint *)(param_1 + 4));
  }
  pExceptionList = ppExceptionList;
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  pExceptionList = local_c;
  return;
}
#endif




/* DUPLICATE: GameData_RemoveAllEntries */
#if 0
void __fastcall GameData_RemoveAllEntries(int param_1)

{
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = (int *)(param_1 + 0xc);
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = *(uint *)(param_1 + 0x10);
    if ((intptr_t)nNextOffset < 0) {
      pLinkSlot = (int *)~nNextOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pLinkSlot = nSavedHead;
    *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(param_1 + 0x10);
    *pHeadPtr = 0;
    *(unsigned int *)(param_1 + 0x10) = 0;
  }
  nSavedHead = *(int *)(param_1 + 4);
  pHeadPtr = (int *)(param_1 + 4);
  if (nSavedHead != 0) {
    nNextOffset = *(uint *)(param_1 + 8);
    if ((intptr_t)nNextOffset < 0) {
      pLinkSlot = (int *)~nNextOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pLinkSlot = nSavedHead;
    *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(param_1 + 8);
    *pHeadPtr = 0;
    *(unsigned int *)(param_1 + 8) = 0;
  }
  return;
}
#endif




void __fastcall GameDataPool_RemoveAll(int param_1)

{
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = (int *)(param_1 + 0xc);
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = *(uint *)(param_1 + 0x10);
    if ((intptr_t)nNextOffset < 0) {
      pLinkSlot = (int *)~nNextOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pLinkSlot = nSavedHead;
    *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(param_1 + 0x10);
    *pHeadPtr = 0;
    *(unsigned int *)(param_1 + 0x10) = 0;
  }
  nSavedHead = *(int *)(param_1 + 4);
  pHeadPtr = (int *)(param_1 + 4);
  if (nSavedHead != 0) {
    nNextOffset = *(uint *)(param_1 + 8);
    if ((intptr_t)nNextOffset < 0) {
      pLinkSlot = (int *)~nNextOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pLinkSlot = nSavedHead;
    *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(param_1 + 8);
    *pHeadPtr = 0;
    *(unsigned int *)(param_1 + 8) = 0;
  }
  return;
}



/* DUPLICATE: GameData_ListNode_Detach */
#if 0
void __fastcall GameData_ListNode_Detach(int *param_1)

{
  int *pLinkSlot;
  int nNextOffset;
  uint nPrevOffset;
  
  nNextOffset = *param_1;
  if (nNextOffset != 0) {
    nPrevOffset = param_1[1];
    if ((intptr_t)nPrevOffset < 0) {
      pLinkSlot = (int *)~nPrevOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)param_1 + (nPrevOffset - *(int *)(nNextOffset + 4)));
    }
    *pLinkSlot = nNextOffset;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}
#endif




/* DUPLICATE: GameDataPool_DetachList */
#if 0
void __fastcall GameDataPool_DetachList(int *param_1)

{
  int *pNode;
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = param_1 + 1;
  while (0 < param_1[2]) {
    pNode = (int *)(*param_1 + param_1[2]);
    if (*pNode != 0) {
      nNextOffset = pNode[1];
      if ((intptr_t)nNextOffset < 0) {
        pLinkSlot = (int *)~nNextOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pNode + (nNextOffset - *(int *)(*pNode + 4)));
      }
      *pLinkSlot = *pNode;
      *(int *)(*pNode + 4) = pNode[1];
      *pNode = 0;
      pNode[1] = 0;
    }
  }
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = param_1[2];
    if ((intptr_t)nNextOffset < 0) {
      pNode = (int *)~nNextOffset;
    }
    else {
      pNode = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pNode = nSavedHead;
    *(int *)(*pHeadPtr + 4) = param_1[2];
    *pHeadPtr = 0;
    param_1[2] = 0;
  }
  return;
}
#endif




/* DUPLICATE: GameData_AllocGameEntry */
#if 0
void __thiscall GameData_AllocGameEntry(void *_this,unsigned int param_1,int param_2,uint param_3)

{
  int pNewEntry;
  int *pHeadPtr;
  int unaff_ESI;
  int *pLinkSlot;
  int nSavedHead;
  uint nOffset;
  
  pNewEntry = SMemAlloc(param_2 + 0x3060,s___AUSGAMEDATA___10021000,0xfffffffe,param_3 | 8);
  if (pNewEntry == 0) {
    pNewEntry = 0;
  }
  else {
    *(unsigned int *)(pNewEntry + 4) = 0;
    *(unsigned int *)(pNewEntry + 8) = 0;
    *(unsigned int *)(pNewEntry + 0xc) = 0;
    *(unsigned int *)(pNewEntry + 0x10) = 0;
  }
  if (unaff_ESI != 0) {
    if (pNewEntry == 0) {
      pHeadPtr = (int *)((intptr_t)_this + 4);
    }
    else {
      pHeadPtr = (int *)(*(int *)_this + pNewEntry);
    }
    nSavedHead = *pHeadPtr;
    if (nSavedHead != 0) {
      nOffset = pHeadPtr[1];
      if ((intptr_t)nOffset < 0) {
        pLinkSlot = (int *)~nOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pHeadPtr + (nOffset - *(int *)(nSavedHead + 4)));
      }
      *pLinkSlot = nSavedHead;
      *(int *)(*pHeadPtr + 4) = pHeadPtr[1];
      *pHeadPtr = 0;
      pHeadPtr[1] = 0;
    }
    pLinkSlot = (int *)((intptr_t)_this + 4);
    if (unaff_ESI != 1) {
      nSavedHead = *pLinkSlot;
      *pHeadPtr = nSavedHead;
      pHeadPtr[1] = *(int *)(nSavedHead + 4);
      *(int *)(nSavedHead + 4) = pNewEntry;
      *pLinkSlot = (intptr_t)pHeadPtr;
      return;
    }
    *pHeadPtr = (intptr_t)pLinkSlot;
    pHeadPtr[1] = *(int *)((intptr_t)_this + 8);
    nOffset = *(uint *)((intptr_t)_this + 8);
    nSavedHead = *(int *)_this;
    if ((intptr_t)nOffset < 0) {
      *(int **)~nOffset = pHeadPtr;
      *(int *)((intptr_t)_this + 8) = pNewEntry;
      return;
    }
    if (nSavedHead < 0) {
      nSavedHead = (intptr_t)pLinkSlot - *(int *)(*pLinkSlot + 4);
    }
    *(int **)(nOffset + nSavedHead) = pHeadPtr;
    *(int *)((intptr_t)_this + 8) = pNewEntry;
  }
  return;
}
#endif




/* DUPLICATE: GameDataPool_FreeList */
#if 0
void __fastcall GameDataPool_FreeList(int param_1)

{
  int nBucketOffset;
  uint nBucketIdx;
  
  nBucketIdx = 0;
  if (*(int *)(param_1 + 4) != 0) {
    nBucketOffset = 0;
    do {
      GameDataPool_ClearEntry((int *)(nBucketOffset + *(int *)(param_1 + 8)));
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < *(uint *)(param_1 + 4));
  }
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
  }
  return;
}
#endif




/* DUPLICATE: GameDataPool_DetachAll2 */
#if 0
void __fastcall GameDataPool_DetachAll2(int *param_1)

{
  int *pNode;
  int *pLinkSlot;
  uint nNextOffset;
  int nSavedHead;
  int *pHeadPtr;
  
  pHeadPtr = param_1 + 1;
  while (0 < param_1[2]) {
    pNode = (int *)(*param_1 + param_1[2]);
    if (*pNode != 0) {
      nNextOffset = pNode[1];
      if ((intptr_t)nNextOffset < 0) {
        pLinkSlot = (int *)~nNextOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pNode + (nNextOffset - *(int *)(*pNode + 4)));
      }
      *pLinkSlot = *pNode;
      *(int *)(*pNode + 4) = pNode[1];
      *pNode = 0;
      pNode[1] = 0;
    }
  }
  nSavedHead = *pHeadPtr;
  if (nSavedHead != 0) {
    nNextOffset = param_1[2];
    if ((intptr_t)nNextOffset < 0) {
      pNode = (int *)~nNextOffset;
    }
    else {
      pNode = (int *)((intptr_t)pHeadPtr + (nNextOffset - *(int *)(nSavedHead + 4)));
    }
    *pNode = nSavedHead;
    *(int *)(*pHeadPtr + 4) = param_1[2];
    *pHeadPtr = 0;
    param_1[2] = 0;
  }
  return;
}
#endif




unsigned int * __thiscall GameData_DeletingDestructor5(void *_this,byte param_1)

{
  GameData_Destructor_ListBase2((unsigned int*)_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return (unsigned int*)_this;
}



/* DUPLICATE: GameData_Destructor_ListBase2 */
#if 0
void __fastcall GameData_Destructor_ListBase2(unsigned int *param_1)

{
  void *_this;
  int *pPrevLink;
  int *pNode;
  uint nBucketIdx;
  int nBucketOffset;
  void *pvStack_c;
  unsigned char *puStack_8;
  uint local_4;
  int nNodeCount;
  
  puStack_8 = &LAB_1001a674;
  pvStack_c = pExceptionList;
  pExceptionList = &pvStack_c;
  *param_1 = &g_GameServerVtable2;
  local_4 = 2;
  while( true ) {
    nBucketOffset = param_1[0x10];
    nBucketIdx = 0;
    if (nBucketOffset < 1) break;
    GameData_ChunkClearEntry(nBucketOffset);
    SMemFree((void*)(nBucketOffset),s___AV__TSHashObjectChunk_USGAMEDA_10021020,0xfffffffe,0);
  }
  while (_this = (void *)param_1[0xc], 0 < (intptr_t)_this) {
    GameData_DeletingDestructor2(_this,0);
    SMemFree((void*)(_this),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  local_4 = CONCAT31((*((unsigned int*)&(local_4)+1)),1);
  pNode = param_1 + 0xf;
  while (0 < (intptr_t)param_1[0x10]) {
    GameData_ListNode_Detach4((int *)(param_1[0xe] + param_1[0x10]));
  }
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode2(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = param_1[0x10];
    *pNode = 0;
    param_1[0x10] = 0;
  }
  local_4 = local_4 & 0xffffff00;
  pNode = param_1 + 0xb;
  while (0 < (intptr_t)param_1[0xc]) {
    GameData_ListNode_Detach2((int *)(param_1[10] + param_1[0xc]));
  }
  if (*pNode != 0) {
    pPrevLink = (int *)GameData_PoolIndexToNode(pNode,-1);
    *pPrevLink = *pNode;
    *(unsigned int *)(*pNode + 4) = param_1[0xc];
    *pNode = 0;
    param_1[0xc] = 0;
  }
  *param_1 = &g_GameServerVtable1;
  local_4 = 4;
  param_1[4] = 0;
  GameDataPool_DetachAll3(param_1 + 1);
  if (param_1[6] != 0) {
    nBucketOffset = 0;
    do {
      while( true ) {
        nNodeCount = *(int *)(param_1[7] + nBucketOffset + 8);
        if (nNodeCount < 1) break;
        pNode = GameData_PoolGetBeginNode((void *)(param_1[7] + nBucketOffset),nNodeCount);
        GameData_ListNode_Detach2(pNode);
      }
      nBucketIdx = nBucketIdx + 1;
      nBucketOffset = nBucketOffset + 0xc;
    } while (nBucketIdx < (uintptr_t)param_1[6]);
  }
  GameDataPool_FreeList((intptr_t)(param_1 + 5));
  local_4 = 0xffffffff;
  GameDataPool_DetachAll3(param_1 + 1);
  GameData_ListNode_Detach2(param_1 + 2);
  pExceptionList = pvStack_c;
  return;
}
#endif




/* DUPLICATE: GameData_PoolIndexToNode */
#if 0
uint __thiscall GameData_PoolIndexToNode(void *_this,int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)((intptr_t)_this + 4);
  if ((intptr_t)uVar1 < 0) {
    return ~uVar1;
  }
  if (param_1 < 0) {
    param_1 = (intptr_t)_this - *(int *)(*(int *)_this + 4);
  }
  return uVar1 + param_1;
}
#endif




/* DUPLICATE: GameData_ListNode_Detach2 */
#if 0
void __fastcall GameData_ListNode_Detach2(int *param_1)

{
  int *pLinkSlot;
  int nNextOffset;
  uint nPrevOffset;
  
  nNextOffset = *param_1;
  if (nNextOffset != 0) {
    nPrevOffset = param_1[1];
    if ((intptr_t)nPrevOffset < 0) {
      pLinkSlot = (int *)~nPrevOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)param_1 + (nPrevOffset - *(int *)(nNextOffset + 4)));
    }
    *pLinkSlot = nNextOffset;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}
#endif




#if 0
int * __thiscall GameData_PoolGetBeginNode(void *_this,int param_1)

{
  if (param_1 != 0) {
    return (int *)(*(int *)_this + param_1);
  }
  return (int *)((intptr_t)_this + 4);
}
#endif /* GameData_PoolGetBeginNode */




/* DUPLICATE: GameDataPool_DetachAll3 */
#if 0
void __fastcall GameDataPool_DetachAll3(int *param_1)

{
  int *pNode;
  int *pLinkSlot;
  uint nPrevOffset;
  
  while (0 < param_1[2]) {
    pNode = (int *)(*param_1 + param_1[2]);
    if (*pNode != 0) {
      nPrevOffset = pNode[1];
      if ((intptr_t)nPrevOffset < 0) {
        pLinkSlot = (int *)~nPrevOffset;
      }
      else {
        pLinkSlot = (int *)((intptr_t)pNode + (nPrevOffset - *(int *)(*pNode + 4)));
      }
      *pLinkSlot = *pNode;
      *(int *)(*pNode + 4) = pNode[1];
      *pNode = 0;
      pNode[1] = 0;
    }
  }
  return;
}
#endif




/* DUPLICATE: GameData_ListNode_Detach3 */
#if 0
void __fastcall GameData_ListNode_Detach3(int *param_1)

{
  int *pLinkSlot;
  int nNextOffset;
  uint nPrevOffset;
  
  nNextOffset = *param_1;
  if (nNextOffset != 0) {
    nPrevOffset = param_1[1];
    if ((intptr_t)nPrevOffset < 0) {
      pLinkSlot = (int *)~nPrevOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)param_1 + (nPrevOffset - *(int *)(nNextOffset + 4)));
    }
    *pLinkSlot = nNextOffset;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}
#endif




#if 0
int * __thiscall GameData_ListNode_Clear(void *_this,byte param_1)

{
  GameDataPool_ClearEntry(_this);
  if (((param_1 & 1) != 0) && (_this != (void *)0x0)) {
    SMemFree((void*)(_this),s_delete_1001ed70,0xffffffff,0);
  }
  return _this;
}
#endif /* GameData_ListNode_Clear */




/* DUPLICATE: GameData_ChunkClearEntry */
#if 0
void __fastcall GameData_ChunkClearEntry(int param_1)

{
  int *pLinkSlot;
  int nSavedHead;
  uint nEntryIdx;
  int nEntryOffset;
  int *pHeadPtr;
  
  nSavedHead = *(int *)(param_1 + 0x10);
  pHeadPtr = (int *)(param_1 + 0x10);
  if (nSavedHead != 0) {
    nEntryIdx = *(uint *)(param_1 + 0x14);
    if ((intptr_t)nEntryIdx < 0) {
      pLinkSlot = (int *)~nEntryIdx;
    }
    else {
      pLinkSlot = (int *)((intptr_t)pHeadPtr + (nEntryIdx - *(int *)(nSavedHead + 4)));
    }
    *pLinkSlot = nSavedHead;
    *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(param_1 + 0x14);
    *pHeadPtr = 0;
    *(unsigned int *)(param_1 + 0x14) = 0;
  }
  nEntryIdx = 0;
  if (*(int *)(param_1 + 4) != 0) {
    nSavedHead = 0;
    do {
      nEntryOffset = *(int *)(param_1 + 8) + nSavedHead;
      GameData_ListNode_Detach2((int *)(nEntryOffset + 0xc));
      pHeadPtr = (int *)(nEntryOffset + 4);
      if (*(int *)(nEntryOffset + 4) != 0) {
        pLinkSlot = (int *)GameData_PoolIndexToNode(pHeadPtr,-1);
        *pLinkSlot = *pHeadPtr;
        *(unsigned int *)(*pHeadPtr + 4) = *(unsigned int *)(nEntryOffset + 8);
        *pHeadPtr = 0;
        *(unsigned int *)(nEntryOffset + 8) = 0;
      }
      nEntryIdx = nEntryIdx + 1;
      nSavedHead = nSavedHead + 0x3060;
    } while (nEntryIdx < *(uint *)(param_1 + 4));
  }
  if (*(int *)(param_1 + 8) != 0) {
    SMemFree(*(int *)(param_1 + 8),s___AUSGAMEDATA___10021000,0xfffffffe,0);
  }
  return;
}
#endif




/* DUPLICATE: GameData_PoolInit */
#if 0
void __fastcall GameData_PoolInit(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = puVar1;
  *param_1 = 0xdddddddd;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}
#endif




/* DUPLICATE: GameData_PoolReserve */
#if 0
void __thiscall GameData_PoolReserve(void *_this,int param_1)

{
  uint uVar1;
  int *pNode;
  int *pLinkSlot;
  uint nPrevOffset;
  
  if (param_1 != *(int *)_this) {
    uVar1 = (intptr_t)_this + 4;
    while (0 < *(int *)((intptr_t)_this + 8)) {
      pNode = (int *)(*(int *)_this + *(int *)((intptr_t)_this + 8));
      if (*pNode != 0) {
        nPrevOffset = pNode[1];
        if ((intptr_t)nPrevOffset < 0) {
          pLinkSlot = (int *)~nPrevOffset;
        }
        else {
          pLinkSlot = (int *)((intptr_t)pNode + (nPrevOffset - *(int *)(*pNode + 4)));
        }
        *pLinkSlot = *pNode;
        *(int *)(*pNode + 4) = pNode[1];
        *pNode = 0;
        pNode[1] = 0;
      }
    }
    *(uint *)uVar1 = uVar1;
    *(uint *)((intptr_t)_this + 8) = ~uVar1;
    *(int *)_this = param_1;
  }
  return;
}
#endif




/* DUPLICATE: GameData_PoolIndexToNode2 */
#if 0
uint __thiscall GameData_PoolIndexToNode2(void *_this,int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)((intptr_t)_this + 4);
  if ((intptr_t)uVar1 < 0) {
    return ~uVar1;
  }
  if (param_1 < 0) {
    param_1 = (intptr_t)_this - *(int *)(*(int *)_this + 4);
  }
  return uVar1 + param_1;
}
#endif




/* DUPLICATE: GameData_ListNode_Detach4 */
#if 0
void __fastcall GameData_ListNode_Detach4(int *param_1)

{
  int *pLinkSlot;
  int nNextOffset;
  uint nPrevOffset;
  
  nNextOffset = *param_1;
  if (nNextOffset != 0) {
    nPrevOffset = param_1[1];
    if ((intptr_t)nPrevOffset < 0) {
      pLinkSlot = (int *)~nPrevOffset;
    }
    else {
      pLinkSlot = (int *)((intptr_t)param_1 + (nPrevOffset - *(int *)(nNextOffset + 4)));
    }
    *pLinkSlot = nNextOffset;
    *(int *)(*param_1 + 4) = param_1[1];
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}
#endif




/* DUPLICATE: GameData_PoolAddOffset */
#if 0
int __fastcall GameData_PoolAddOffset(int param_1,int param_2)

{
  return param_1 + param_2;
}
#endif




/* DUPLICATE: GameData_PoolInit2 */
#if 0
void __fastcall GameData_PoolInit2(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = puVar1;
  *param_1 = 0;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}
#endif




/* DUPLICATE: GameData_PoolZeroEntry */
#if 0
void __fastcall GameData_PoolZeroEntry(unsigned int *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return;
}
#endif




/* DUPLICATE: GameData_PoolSetCount */
#if 0
void __fastcall GameData_PoolSetCount(unsigned int *param_1)

{
  unsigned int *puVar1;
  
  puVar1 = param_1 + 1;
  *puVar1 = 0;
  param_1[2] = 0;
  *puVar1 = puVar1;
  *param_1 = 0;
  param_1[2] = ~(uintptr_t)puVar1;
  return;
}
#endif




/* DUPLICATE: GameData_PoolInit3 */
#if 0
void __fastcall GameData_PoolInit3(int pPool)

{
  uint uVar1;
  
  uVar1 = pPool + 4;
  *(uint *)uVar1 = uVar1;
  *(uint *)(pPool + 8) = ~uVar1;
  return;
}
#endif




/* DUPLICATE: GameData_PoolResize */
#if 0
void __thiscall GameData_PoolResize(void *_this,uint dwNewCapacity)

{
  int nOffset;
  unsigned int pNewArray;
  uint nIdx;
  uint nAlignedCapacity;
  unsigned int *pEntry;
  int nByteOffset;
  uint nLowBit;
  unsigned int *pOldArray;
  
  if (*(uint *)((intptr_t)_this + 4) < dwNewCapacity) {
    if (*(uint *)_this < dwNewCapacity) {
      nIdx = *(uint *)((intptr_t)_this + 0xc);
      if (nIdx == 0) {
        if (dwNewCapacity < 0x15) {
          nAlignedCapacity = dwNewCapacity - 1 & dwNewCapacity;
          nIdx = dwNewCapacity;
          while (nLowBit = nAlignedCapacity, nLowBit != 0) {
            nIdx = nLowBit;
            nAlignedCapacity = nLowBit - 1 & nLowBit;
          }
          if (nIdx == 0) {
            nIdx = 1;
          }
        }
        else {
          *(unsigned int *)((intptr_t)_this + 0xc) = 0x15;
          nIdx = 0x15;
        }
      }
      nAlignedCapacity = dwNewCapacity;
      if (dwNewCapacity % nIdx != 0) {
        nAlignedCapacity = (nIdx - dwNewCapacity % nIdx) + dwNewCapacity;
      }
      pOldArray = *(unsigned int **)((intptr_t)_this + 8);
      if (nAlignedCapacity < *(uint *)((intptr_t)_this + 4)) {
        pEntry = pOldArray + nAlignedCapacity * 3;
        nIdx = nAlignedCapacity;
        do {
          GameData_ListNode_Clear(pEntry,0);
          nIdx = nIdx + 1;
          pEntry = pEntry + 3;
        } while (nIdx < *(uint *)((intptr_t)_this + 4));
      }
      *(uint *)_this = nAlignedCapacity;
      nOffset = SMemReAlloc(pOldArray,nAlignedCapacity * 0xc,
                            s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0x10);
      *(int *)((intptr_t)_this + 8) = nOffset;
      if (nOffset == 0) {
        pNewArray = SMemAlloc(nAlignedCapacity * 0xc,s___AV__TSExplicitList_USGAMEDATA__10021238,
                              0xfffffffe,0);
        *(unsigned int *)((intptr_t)_this + 8) = pNewArray;
        if (pOldArray != (unsigned int *)0x0) {
          nIdx = *(uint *)((intptr_t)_this + 4);
          if (nAlignedCapacity < *(uint *)((intptr_t)_this + 4)) {
            nIdx = nAlignedCapacity;
          }
          if (nIdx != 0) {
            nOffset = 0;
            pEntry = pOldArray;
            do {
              List_MoveNode((unsigned int *)(nOffset + *(int *)((intptr_t)_this + 8)),pEntry);
              GameData_ListNode_Clear(pEntry,0);
              nOffset = nOffset + 0xc;
              pEntry = pEntry + 3;
              nIdx = nIdx - 1;
            } while (nIdx != 0);
          }
          SMemFree((void*)(pOldArray),s___AV__TSExplicitList_USGAMEDATA__10021238,0xfffffffe,0);
        }
      }
    }
    nIdx = *(uint *)((intptr_t)_this + 4);
    if (nIdx < dwNewCapacity) {
      nByteOffset = nIdx * 0xc;
      nOffset = dwNewCapacity - nIdx;
      do {
        List_FreeNode((unsigned int *)(nByteOffset + *(int *)((intptr_t)_this + 8)));
        nByteOffset = nByteOffset + 0xc;
        nOffset = nOffset + -1;
      } while (nOffset != 0);
      *(uint *)((intptr_t)_this + 4) = dwNewCapacity;
      return;
    }
  }
  else if (dwNewCapacity < *(uint *)((intptr_t)_this + 4)) {
    nOffset = dwNewCapacity * 0xc;
    nIdx = dwNewCapacity;
    do {
      GameDataPool_ClearEntry((int *)(nOffset + *(int *)((intptr_t)_this + 8)));
      nIdx = nIdx + 1;
      nOffset = nOffset + 0xc;
    } while (nIdx < *(uint *)((intptr_t)_this + 4));
  }
  *(uint *)((intptr_t)_this + 4) = dwNewCapacity;
  return;
}
#endif




// D2Server.List_NewNode (10009b50) - Allocates/initializes a new list node for the GameData pool
// (linked-list insert helper). Paired with List_FreeNode.

/* DUPLICATE: List_InitNode */
#if 0
void __fastcall List_InitNode(int pNode)

{
  uint uVar1;
  
  uVar1 = pNode + 4;
  *(uint *)uVar1 = uVar1;
  *(uint *)(pNode + 8) = ~uVar1;
  return;
}
#endif




// D2Server.List_FreeNode (10009b70) - Frees a single list node (node + links) in the
// TSExplicitList/GameData pool. __fastcall, param_1 = node pointer to free. Used by
// GameData_PoolFreeList / pool teardown paths.

/* DUPLICATE: List_FreeNode */
#if 0
void __fastcall List_FreeNode(unsigned int *pNode)

{
  unsigned int *puVar1;
  
  if (pNode != (unsigned int *)0x0) {
    puVar1 = pNode + 1;
    *puVar1 = 0;
    pNode[2] = 0;
    *puVar1 = puVar1;
    *pNode = 0xdddddddd;
    pNode[2] = ~(uintptr_t)puVar1;
  }
  return;
}
#endif




// D2Server.List_MoveNode (10009bb0) - Detaches param_1 from its current list and re-inserts it into
// a fresh/free list head (param_2). Used during pool array relocation in GameData_PoolResize to
// move nodes between old/new backing arrays.

/* DUPLICATE: List_MoveNode */
#if 0
void __fastcall List_MoveNode(unsigned int *pNode,unsigned int *pDestHead)

{
  unsigned int *puVar1;
  unsigned int uVar2;
  
  if (pNode != (unsigned int *)0x0) {
    puVar1 = pNode + 1;
    *puVar1 = 0;
    pNode[2] = 0;
    uVar2 = *pDestHead;
    *puVar1 = puVar1;
    *pNode = uVar2;
    pNode[2] = ~(uintptr_t)puVar1;
  }
  return;
}
#endif




#if 0
void SMemFree(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bd8. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_403();
  return;
}
#endif /* SMemFree */




#if 0
void SMemAlloc(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bde. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_401();
  return;
}
#endif /* SMemAlloc */




#if 0
void SRegSaveString(void)

{
                    // WARNING: Could not recover jumptable at 0x10009be4. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_425();
  return;
}
#endif /* SRegSaveString */




#if 0
void SRegLoadString(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bea. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_422();
  return;
}
#endif /* SRegLoadString */




#if 0
void SStrCopy(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bf0. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_501();
  return;
}
#endif /* SStrCopy */




#if 0
void SStrPrintf(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bf6. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_578();
  return;
}
#endif /* SStrPrintf */




#if 0
void SStrCmp(void)

{
                    // WARNING: Could not recover jumptable at 0x10009bfc. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_508();
  return;
}
#endif /* SStrCmp */




#if 0
void SMemReAlloc(void)

{
                    // WARNING: Could not recover jumptable at 0x10009c02. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_405();
  return;
}
#endif /* SMemReAlloc */




// D2Hell.Archive_ValidateHandle (10009c76) - Asserts handle is non-NULL (FOG_SetLogPrefix "hFile") and
// that a current archive is open (FOG_SOCKET_SetDispatch). Calls exit(-1) on failure. Matches
// C:\D2\Source\D2Hell\SRC\Archive.cpp line ~0x56.

void __fastcall Archive_ValidateHandle(unsigned int pThis,int hFile)

{
  int iVar1;
  unsigned char szFileName [260];
  
  if (hFile == 0) {
    FOG_SetLogPrefix(s_hFile_10021298,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x56);
    _exit_wrapper(0xffffffff);
  }
  iVar1 = FOG_SOCKET_SetDispatch();
  if (iVar1 == 0) {
    SFileGetFileName(hFile,(char*)szFileName,0x104);
    FOG_DisplayHalt(3,(char*)szFileName,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x5c);
    _exit_wrapper(0xffffffff);
  }
  return;
}



// D2Hell.Archive_ReadDword (10009ce5) - Reads a 4-byte DWORD via FOG_SOCKET_AddRef and asserts full read
// (FOG_SOCKET_SetCallbacks check of dwBytesToRead). Exits on error. Matches D2Hell Archive.cpp line ~0x6d.

void __fastcall
Archive_ReadDword(unsigned int pThis,int hFile,unsigned int pDst,unsigned int nStackSize,
                 unsigned int dwFlags)

{
  int iVar1;
  unsigned char szFileName [260];
  
  if (hFile == 0) {
    FOG_SetLogPrefix(s_hFile_10021298,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x6d);
    _exit_wrapper(0xffffffff);
  }
  iVar1 = FOG_SOCKET_AddRef(nStackSize,dwFlags);
  if (iVar1 == -1) {
    SFileGetFileName(hFile,(char*)szFileName,0x104);
    FOG_DisplayHalt(3,(char*)szFileName,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x76);
    _exit_wrapper(0xffffffff);
  }
  return;
}



// D2Hell.Archive_ReadBuffer (10009d5b) - Reads dwBytesToRead bytes via FOG_SOCKET_SetCallbacks, asserts the
// actual read count equals requested. Exits on error. Matches D2Hell Archive.cpp line ~0x84.

void __fastcall Archive_ReadBuffer(unsigned int pThis,int hFile,unsigned int pBuffer,int dwBytesToRead)

{
  int iVar1;
  int iVar2;
  unsigned char szFileName [260];
  
  if (hFile == 0) {
    FOG_SetLogPrefix(s_hFile_10021298,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x84);
    _exit_wrapper(0xffffffff);
  }
  iVar1 = dwBytesToRead;
  iVar2 = (intptr_t)FOG_SOCKET_SetCallbacks(dwBytesToRead,(intptr_t)&dwBytesToRead,0,0);
  if (iVar2 == 0) {
    SFileGetFileName(hFile,(char*)szFileName,0x104);
    FOG_DisplayHalt(3,(char*)szFileName,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x8c);
    _exit_wrapper(0xffffffff);
  }
  if (iVar1 != dwBytesToRead) {
    FOG_SetLogPrefix(s_dwBytesToRead____dwBytes_100212a0,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x8f);
    _exit_wrapper(0xffffffff);
  }
  return;
}



// D2Hell.Archive_LoadFile (10009e01) - Main archive loader: opens archive (FOG_SOCKET_MarkConnected), allocates
// buffer (FOG_CrashDeadlockDetected, tag 0x22a/0x23b), reads full file via Archive_ReadBuffer, closes archive
// (FOG_SOCKET_InvokeCallback). Falls back to retry loop with Sleep(100) polling Archive_FindFileEx. Matches D2Hell
// Archive.cpp line ~0x38.

int * __fastcall Archive_LoadFile(int pThis,unsigned int dwFlags,unsigned int pBuffer,int *pdwFileSize)

{
  int nResult;
  int *pFileData;
  LPSTR pFoundFile;
  int hArchiveFile;
  unsigned int extraout_EDX;
  LPCSTR extraout_EDX_00;
  void *unaff_EBX;
  int *unaff_EDI;
  LPCSTR szFileName;
  
  nResult = FOG_SOCKET_MarkConnected(0, 0);
  if (nResult != 0) {
    Archive_ValidateHandle(pThis,pThis); pFileData = (int *)1;
    if (pdwFileSize < pFileData) {
      FOG_SetLogPrefix((char*)0, (char*)0, 0);
      _exit_wrapper(0xffffffff);
    }
    Archive_ReadBuffer(pThis,pThis,pBuffer,(intptr_t)pdwFileSize);
    if (pThis == 0) {
      FOG_SetLogPrefix((char*)0, (char*)0, 0);
      _exit_wrapper(0xffffffff);
    }
    FOG_SOCKET_InvokeCallback();
    return pdwFileSize;
  }
  FOG_DisplayHalt(0, (char*)0, (char*)0, 0);
  _exit_wrapper(0xffffffff);
  nResult = FOG_SOCKET_MarkConnected(dwFlags,pThis);
  if (nResult == 0) {
    FOG_DisplayHalt(3,(char*)extraout_EDX,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x38);
    _exit_wrapper(0xffffffff);
    szFileName = extraout_EDX_00;
    pFileData = (int *)FOG_CrashDeadlockDetected(0x22a,0,hArchiveFile,extraout_EDX);
    *pFileData = 0;
    while( true ) {
      pFoundFile = Archive_FindFileEx(pFileData + 1,szFileName,dwFlags,1000);
      *pFileData = (intptr_t)pFoundFile;
      if (pFoundFile != (LPSTR)0x0) {
        return pFileData;
      }
      if ((unaff_EBX == (void *)0x0) || (nResult = ((int (*)())unaff_EBX)(), nResult == 0)) break;
      Sleep(100);
      if (*pFileData != 0) {
        return pFileData;
      }
    }
    FOG_CrashDumpThread(0x23b,0);
    return (int *)0x0;
  }
  Archive_ValidateHandle(hArchiveFile,hArchiveFile); nResult = 1;
  pFileData = (int *)FOG_CrashDeadlockDetected(pThis,0);
  if (pFileData != (int *)0x0) {
    Archive_ReadBuffer(hArchiveFile,hArchiveFile,(uintptr_t)pFileData,nResult);
    if (hArchiveFile == 0) {
      FOG_SetLogPrefix(s_hFile_10021298,s_C__D2_Source_D2Hell_SRC_Archive__10021274,0x46);
      _exit_wrapper(0xffffffff);
    }
    FOG_SOCKET_InvokeCallback();
    if (unaff_EDI != (int *)0x0) {
      *unaff_EDI = nResult;
    }
  }
  return pFileData;
}



int * __fastcall
MPQ_OpenWithRetry(unsigned int pArchiveInfo,LPCSTR szFileName,unsigned int nPriority,unsigned int nFlags,
                 unsigned char *pRetryCallback)

{
  int *piVar1;
  LPSTR pCVar2;
  int iVar3;
  
  piVar1 = (int *)FOG_CrashDeadlockDetected(0x22a,0);
  *piVar1 = 0;
  while( true ) {
    pCVar2 = Archive_FindFileEx(piVar1 + 1,szFileName,nPriority,1000);
    *piVar1 = (intptr_t)pCVar2;
    if (pCVar2 != (LPSTR)0x0) {
      return piVar1;
    }
    if ((pRetryCallback == (unsigned char *)0x0) || (iVar3 = ((int (*)(void))pRetryCallback)(), iVar3 == 0))
    break;
    Sleep(100);
    if (*piVar1 != 0) {
      return piVar1;
    }
  }
  FOG_CrashDumpThread(0x23b,0);
  return (int *)0x0;
}



// D2Hell.Archive_FindFileEx (10009fc3) - Searches for a file: tries STORM_266 (SFILE open) in
// current dir, falls back to module directory (GetModuleFileNameA + _strrchr + STORM_503 set base
// path), then CD-ROM scan via Archive_SearchCdDrives. Returns opened file handle or NULL. Matches
// D2Hell Archive.cpp search-file helper.

LPSTR __thiscall
Archive_FindFileEx(void *_this,LPCSTR szFileName,unsigned int dwFlags,unsigned int dwTimeout)

{
  int iVar1;
  DWORD DVar2;
  char *pcVar3;
  LPSTR szArchivePath;
  
  szArchivePath = (LPSTR)_this;
  lstrcpyA((LPSTR)_this,szFileName);
  iVar1 = SFileOpenArchive((char*)_this,dwTimeout,2,(int*)&szArchivePath);
  if (iVar1 == 0) {
    DVar2 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)_this,0x104);
    if (DVar2 == 0) {
      *(unsigned char *)_this = 0;
    }
    pcVar3 = _strrchr(_this,0x5c);
    if (pcVar3 != (char *)0x0) {
      pcVar3[1] = '\0';
    }
    SStrNCat((char*)_this,szFileName,0x7fffffff);
    iVar1 = SFileOpenArchive((char*)_this,dwTimeout,2,(int*)&szArchivePath);
    if (iVar1 == 0) {
      iVar1 = (uintptr_t)Archive_SearchCdDrives((LPSTR)_this,szFileName,dwTimeout,(uintptr_t)&szArchivePath);
      szArchivePath = (LPSTR)(-(uintptr_t)(iVar1 != 0) & (uintptr_t)szArchivePath);
    }
  }
  return szArchivePath;
}



// D2Hell.Archive_SearchCdDrives (1000a050) - Iterates all logical drives via
// GetLogicalDriveStringsA, tries each DRIVE_CDROM (GetDriveTypeA==5) with STORM_266 for the
// requested file. Returns 1 on first hit. Matches D2Hell Archive.cpp CD search helper.

unsigned int __fastcall
Archive_SearchCdDrives(LPSTR szPath,LPCSTR szFileName,unsigned int dwFlags,unsigned int pFileHandle)

{
  char cVar1;
  LPCSTR lpRootPathName;
  DWORD DVar2;
  UINT UVar3;
  int iVar4;
  char *pcVar5;
  char szDriveStrings [260];
  LPSTR local_8;
  
  local_8 = szPath;
  DVar2 = GetLogicalDriveStringsA(0x104,szDriveStrings);
  if ((DVar2 != 0) && (DVar2 < 0x105)) {
    for (; *szFileName == '\\'; szFileName = szFileName + 1) {
    }
    lpRootPathName = szDriveStrings;
    while (pcVar5 = lpRootPathName, szDriveStrings[0] != '\0') {
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      UVar3 = GetDriveTypeA(lpRootPathName);
      if (UVar3 == 5) {
        lstrcpyA(local_8,lpRootPathName);
        lstrcatA(local_8,szFileName);
        iVar4 = SFileOpenArchive(local_8,dwFlags,2,pFileHandle);
        if (iVar4 != 0) {
          return 1;
        }
      }
      lpRootPathName = pcVar5;
      szDriveStrings[0] = *pcVar5;
    }
  }
  return 0;
}



// D2Hell.Archive_Close (1000a0e3) - Closes an open archive handle via STORM_252 and logs
// FOG_CrashDumpThread(0x276). Zeroes the stored handle. Matches D2Hell Archive.cpp close helper.

void __fastcall Archive_Close(int *pArchiveObj)

{
  if (*pArchiveObj != 0) {
    SFileCloseArchive(*pArchiveObj);
  }
  *pArchiveObj = 0;
  FOG_CrashDumpThread(0x276,0);
  return;
}



#if 0
void D2NET_10018(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a10a. Too many branches
                    // WARNING: Treating indirect jump as call
  D2NET_10018();
  return;
}
#endif /* D2NET_10018 */




#if 0
void D2NET_10022(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a110. Too many branches
                    // WARNING: Treating indirect jump as call
  D2NET_10022();
  return;
}
#endif /* D2NET_10022 */




#if 0
void SERVER_Release(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a116. Too many branches
                    // WARNING: Treating indirect jump as call
  SERVER_Release();
  return;
}
#endif /* SERVER_Release */




#if 0
void SERVER_SetHackListEnabled(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a11c. Too many branches
                    // WARNING: Treating indirect jump as call
  SERVER_SetHackListEnabled();
  return;
}
#endif /* SERVER_SetHackListEnabled */




#if 0
void SERVER_Initialize(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a122. Too many branches
                    // WARNING: Treating indirect jump as call
  SERVER_Initialize();
  return;
}
#endif /* SERVER_Initialize */




#if 0
void D2COMMON_10983(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a134. Too many branches
                    // WARNING: Treating indirect jump as call
  D2COMMON_10983();
  return;
}
#endif /* D2COMMON_10983 */




#if 0
void STATES_CheckStateMaskExp(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a13a. Too many branches
                    // WARNING: Treating indirect jump as call
  STATES_CheckStateMaskExp();
  return;
}
#endif /* STATES_CheckStateMaskExp */




#if 0
void STATES_CheckStateMaskStayDeath(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a140. Too many branches
                    // WARNING: Treating indirect jump as call
  STATES_CheckStateMaskStayDeath();
  return;
}
#endif /* STATES_CheckStateMaskStayDeath */




#if 0
void D2GAME_10007(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a146. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10007();
  return;
}
#endif /* D2GAME_10007 */




#if 0
void D2GAME_10021(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a14c. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10021();
  return;
}
#endif /* D2GAME_10021 */




#if 0
void D2GAME_10019(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a164. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10019();
  return;
}
#endif /* D2GAME_10019 */




#if 0
void D2GAME_10020(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a16a. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10020();
  return;
}
#endif /* D2GAME_10020 */




#if 0
void D2GAME_10018(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a170. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10018();
  return;
}
#endif /* D2GAME_10018 */




#if 0
void D2GAME_10015(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a176. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10015();
  return;
}
#endif /* D2GAME_10015 */




#if 0
void D2GAME_10012(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a17c. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10012();
  return;
}
#endif /* D2GAME_10012 */




#if 0
void D2GAME_10014(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a182. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10014();
  return;
}
#endif /* D2GAME_10014 */




#if 0
void D2GAME_10047(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a188. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10047();
  return;
}
#endif /* D2GAME_10047 */




#if 0
void D2GAME_10048(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a18e. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10048();
  return;
}
#endif /* D2GAME_10048 */




#if 0
void D2GAME_10049(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a194. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10049();
  return;
}
#endif /* D2GAME_10049 */




#if 0
void D2GAME_10006(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1a0. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10006();
  return;
}
#endif /* D2GAME_10006 */




#if 0
void D2GAME_10045(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1a6. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10045();
  return;
}
#endif /* D2GAME_10045 */




#if 0
void D2GAME_10003(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1ac. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10003();
  return;
}
#endif /* D2GAME_10003 */




#if 0
void D2GAME_10043(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1b2. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10043();
  return;
}
#endif /* D2GAME_10043 */




#if 0
void D2GAME_10041(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1b8. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10041();
  return;
}
#endif /* D2GAME_10041 */




#if 0
void D2GAME_10050(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1be. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10050();
  return;
}
#endif /* D2GAME_10050 */




#if 0
void D2GAME_10040(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1c4. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10040();
  return;
}
#endif /* D2GAME_10040 */




#if 0
void D2GAME_10039(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1ca. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10039();
  return;
}
#endif /* D2GAME_10039 */




#if 0
void D2GAME_10002(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1d0. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10002();
  return;
}
#endif /* D2GAME_10002 */




#if 0
void D2GAME_10023(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1d6. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10023();
  return;
}
#endif /* D2GAME_10023 */




#if 0
void D2GAME_10046(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1dc. Too many branches
                    // WARNING: Treating indirect jump as call
  D2GAME_10046();
  return;
}
#endif /* D2GAME_10046 */




#if 0
void D2Lang_Uninitialize(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1e2. Too many branches
                    // WARNING: Treating indirect jump as call
  D2Lang_Uninitialize();
  return;
}
#endif /* D2Lang_Uninitialize */




#if 0
void D2Lang_Initialize(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1e8. Too many branches
                    // WARNING: Treating indirect jump as call
  D2Lang_Initialize();
  return;
}
#endif /* D2Lang_Initialize */




#if 0
void FOG_EnterCriticalSection(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1ee. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_EnterCriticalSection();
  return;
}
#endif /* FOG_EnterCriticalSection */




#if 0
void FOG_ExceptionHandler(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a1f4. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_ExceptionHandler();
  return;
}
#endif /* FOG_ExceptionHandler */




#if 0
void FOG_GetDiskInfo()

{
                    // WARNING: Could not recover jumptable at 0x1000a1fa. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_GetDiskInfo();
  return;
}
#endif /* FOG_GetDiskInfo */




#if 0
void FOG_ReallocPool()

{
                    // WARNING: Could not recover jumptable at 0x1000a200. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_ReallocPool();
  return;
}
#endif /* FOG_ReallocPool */




#if 0
void FOG_Noop()

{
                    // WARNING: Could not recover jumptable at 0x1000a206. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_Noop();
  return;
}
#endif /* FOG_Noop */




#if 0
void FOG_InitTimers(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a20c. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_InitTimers(0);
  return;
}
#endif /* FOG_InitTimers */




#if 0
void FOG_GetHostIPAddress(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a212. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_GetHostIPAddress();
  return;
}
#endif /* FOG_GetHostIPAddress */




#if 0
void FOG_Send(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a218. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_Send();
  return;
}
#endif /* FOG_Send */




#if 0
void FOG_SetLogPrefix(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a21e. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SetLogPrefix((char*)0, (char*)0, 0);
  return;
}
#endif /* FOG_SetLogPrefix */




#if 0
void FOG_Log(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a224. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_Log();
  return;
}
#endif /* FOG_Log */




#if 0
void FOG_Noop3(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a22a. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_Noop3();
  return;
}
#endif /* FOG_Noop3 */




#if 0
void FOG_LeaveCriticalSection(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a230. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_LeaveCriticalSection();
  return;
}
#endif /* FOG_LeaveCriticalSection */




void FOG_GetSavePath(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a242. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_GetSavePath();
  return;
}



#if 0
void FOG_CrashDumpThread(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a248. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_CrashDumpThread();
  return;
}
#endif /* FOG_CrashDumpThread */




#if 0
void FOG_CrashDeadlockDetected(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a24e. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_CrashDeadlockDetected();
  return;
}
#endif /* FOG_CrashDeadlockDetected */




#if 0
void FOG_GetSystemInfo(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a254. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_GetSystemInfo();
  return;
}
#endif /* FOG_GetSystemInfo */




#if 0
void FOG_DisplayError(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a25a. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_DisplayError((char*)0);
  return;
}
#endif /* FOG_DisplayError */




#if 0
void FOG_GetSyncTime(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a260. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_GetSyncTime();
  return;
}
#endif /* FOG_GetSyncTime */




#if 0
void FOG_SetExceptionFilter(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a266. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SetExceptionFilter();
  return;
}
#endif /* FOG_SetExceptionFilter */




#if 0
void FOG_InitErrorMgr(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a26c. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_InitErrorMgr();
  return;
}
#endif /* FOG_InitErrorMgr */




void FOG_CharToUpper(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a272. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_CharToUpper();
  return;
}



#if 0
void FOG_DisplayHalt(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a278. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_DisplayHalt(0, (char*)0, (char*)0, 0);
  return;
}
#endif /* FOG_DisplayHalt */




#if 0
void FOG_SOCKET_MarkConnected(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a27e. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SOCKET_MarkConnected(0, 0);
  return;
}
#endif /* FOG_SOCKET_MarkConnected */




#if 0
void FOG_SOCKET_InvokeCallback(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a284. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SOCKET_InvokeCallback();
  return;
}
#endif /* FOG_SOCKET_InvokeCallback */




#if 0
void FOG_SOCKET_SetDispatch(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a28a. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SOCKET_SetDispatch();
  return;
}
#endif /* FOG_SOCKET_SetDispatch */




#if 0
void FOG_SOCKET_AddRef(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a290. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SOCKET_AddRef();
  return;
}
#endif /* FOG_SOCKET_AddRef */




#if 0
void FOG_SOCKET_SetCallbacks(void)

{
                    // WARNING: Could not recover jumptable at 0x1000a296. Too many branches
                    // WARNING: Treating indirect jump as call
  FOG_SOCKET_SetCallbacks();
  return;
}
#endif /* FOG_SOCKET_SetCallbacks */




#if 0
int __cdecl _vsprintf_l(unsigned char *param_1,byte *param_2)

{
  int iVar1;
  unsigned char *local_24;
  int local_20;
  unsigned char *local_1c;
  unsigned int local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = _output((int *)&local_24,param_2,(unsigned int *)&uStack00000008);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    _out_putc_wide(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}
#endif /* _vsprintf_l */




void _initterm_table(void)

{
  if (PTR__cinit_10021330 != (unsigned char *)0x0) {
    ((void (*)(void))PTR__cinit_10021330)();
  }
  initterm((unsigned int *)&DAT_1001e30c,(unsigned int *)&DAT_1001e624);
  initterm((unsigned int *)&DAT_1001e000,(unsigned int *)&DAT_1001e208);
  return;
}



#if 0
void __cdecl _exit_wrapper(UINT param_1)

{
  exit(0);
  return;
}
#endif /* _exit_wrapper */




// Library Function - Single Match
//  __exit
// 
// Library: Visual Studio 2003 Release

#if 0
void __cdecl __exit(int _Code)

{
  exit(0);
  return;
}
#endif /* __exit */




#if 0
void _cexit(void)

{
  exit(0);
  return;
}
#endif /* _cexit */




#if 0
void __cdecl exit(0)

{
  HANDLE hProcess;
  unsigned int *puVar1;
  UINT uExitCode;
  
  _lock_cs_d();
  if (DAT_10023520 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  DAT_1002351c = 1;
  DAT_10023518 = (unsigned char)param_3;
  if (param_2 == 0) {
    if ((DAT_10025030 != (unsigned int *)0x0) &&
       (puVar1 = (unsigned int *)(DAT_1002502c - 4), DAT_10025030 <= puVar1)) {
      do {
        if ((void *)*puVar1 != (void *)0x0) {
          ((void (*)(void))*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (DAT_10025030 <= puVar1);
    }
    initterm((unsigned int *)&DAT_1001e728,(unsigned int *)&DAT_1001e930);
  }
  initterm((unsigned int *)&DAT_1001ea34,(unsigned int *)&DAT_1001ec3c);
  if (param_3 == 0) {
    DAT_10023520 = 1;
                    // WARNING: Subroutine does not return
    ExitProcess(param_1);
  }
  _unlock_cs_d();
  return;
}
#endif /* __crt_exit_process */




#if 0
void _lock_cs_d(void)

{
  _lock_critical_section(0xd);
  return;
}
#endif /* _lock_cs_d */




#if 0
void _unlock_cs_d(void)

{
  _unlock_critical_section(0xd);
  return;
}
#endif /* _unlock_cs_d */




#if 0
void __cdecl initterm(unsigned int *param_1,unsigned int *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((void *)*param_1 != (void *)0x0) {
      ((void (*)(void))*param_1)();
    }
  }
  return;
}
#endif /* initterm */




// WARNING: Unable to track spacebase fully for stack

void _alloca_probe(void)

{
  uint in_EAX;
  unsigned char *puVar1;
  unsigned int unaff_retaddr;
  
  puVar1 = (unsigned char*)&uStack_00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(unsigned int *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}



void __cdecl _set_ptd_field(DWORD param_1)

{
  DWORD *pDVar1;
  
  pDVar1 = (DWORD*)(intptr_t)_getptd();
  pDVar1[5] = param_1;
  return;
}



// Library Function - Single Match
//  _rand
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release, Visual Studio 2008 Release

int __cdecl _rand(void)

{
  DWORD *pDVar1;
  uint uVar2;
  
  pDVar1 = (DWORD*)(intptr_t)_getptd();
  uVar2 = pDVar1[5] * 0x343fd + 0x269ec3;
  pDVar1[5] = uVar2;
  return uVar2 >> 0x10 & 0x7fff;
}



#if 0
void __cdecl _ftime64(int *param_1)

{
  DWORD DVar1;
  int iVar2;
  _TIME_ZONE_INFORMATION local_d0;
  _SYSTEMTIME local_24;
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  GetSystemTime(&local_24);
  if (local_24.wMinute == (*(unsigned short*)((char*)&(DAT_10023538)+2))) {
    if (local_24.wHour == (WORD)DAT_10023538) {
      if (local_24.wDay == (*(unsigned short*)((char*)&(DAT_10023534)+2))) {
        if (local_24.wMonth == (*(unsigned short*)((char*)&(DAT_10023530)+2))) {
          if (local_24.wYear == (WORD)DAT_10023530) goto LAB_1000a6b8;
        }
      }
    }
  }
  DVar1 = GetTimeZoneInformation(&local_d0);
  if (DVar1 == 0xffffffff) {
    DAT_10023528 = -1;
  }
  else if (((DVar1 == 2) && (local_d0.DaylightDate.wMonth != 0)) && (local_d0.DaylightBias != 0)) {
    DAT_10023528 = 1;
  }
  else {
    DAT_10023528 = 0;
  }
  (*(unsigned short*)&(DAT_10023530)) = local_24.wYear;
  (*(unsigned short*)((char*)&(DAT_10023530)+2)) = local_24.wMonth;
  (*(unsigned short*)&(DAT_10023534)) = local_24.wDayOfWeek;
  (*(unsigned short*)((char*)&(DAT_10023534)+2)) = local_24.wDay;
  (*(unsigned short*)&(DAT_10023538)) = local_24.wHour;
  (*(unsigned short*)((char*)&(DAT_10023538)+2)) = local_24.wMinute;
  (*(unsigned short*)&(DAT_1002353c)) = local_24.wSecond;
  (*(unsigned short*)((char*)&(DAT_1002353c)+2)) = local_24.wMilliseconds;
LAB_1000a6b8:
  iVar2 = _mktime((uintptr_t)local_14.wYear,(uintptr_t)local_14.wMonth,(uintptr_t)local_14.wDay,
                  (uintptr_t)local_14.wHour,(uintptr_t)local_14.wMinute,(uintptr_t)local_14.wSecond,DAT_10023528);
  if (param_1 != (int *)0x0) {
    *param_1 = iVar2;
  }
  return;
}
#endif /* _ftime64 */




// Library Function - Single Match
//  __alldiv
// 
// Library: Visual Studio

#if 0
unsigned long long __alldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int bVar10;
  char cVar11;
  uint uVar9;
  
  cVar11 = (intptr_t)param_2 < 0;
  if ((intptr_t)cVar11) {
    bVar10 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uintptr_t)bVar10 - param_2;
  }
  if ((intptr_t)param_4 < 0) {
    cVar11 = cVar11 + '\x01';
    bVar10 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uintptr_t)bVar10 - param_4;
  }
  uVar3 = param_1;
  uVar5 = param_3;
  uVar6 = param_2;
  uVar9 = param_4;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (intptr_t)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar8 = uVar9 >> 1;
      uVar5 = uVar5 >> 1 | (uintptr_t)((uVar9 & 1) != 0) << 0x1f;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uintptr_t)((uVar6 & 1) != 0) << 0x1f;
      uVar6 = uVar7;
      uVar9 = uVar8;
    } while (uVar8 != 0);
    uVar1 = CONCAT44(uVar7,uVar3) / (ulonglong)uVar5;
    iVar4 = (intptr_t)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uintptr_t)((ulonglong)lVar2 >> 0x20);
    uVar5 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar5)) ||
       ((param_2 <= uVar5 && (param_1 < (uintptr_t)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  if (cVar11 == '\x01') {
    bVar10 = iVar4 != 0;
    iVar4 = -iVar4;
    uVar3 = -(uintptr_t)bVar10 - uVar3;
  }
  return CONCAT44(uVar3,iVar4);
}
#endif /* __alldiv */




// Library Function - Single Match
//  __allmul
// 
// Library: Visual Studio

#if 0
longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((intptr_t)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (intptr_t)((ulonglong)param_1 * (ulonglong)param_3));
}
#endif /* __allmul */




#if 0
void __fastcall /* type_info_dtor */(unsigned int *param_1)

{
  *param_1 = &(void*)0;
  _lock_critical_section(0x1b);
  if ((LPVOID)param_1[1] != (LPVOID)0x0) {
    free((LPVOID)param_1[1]);
  }
  _unlock_critical_section(0x1b);
  return;
}
#endif /* type_info_dtor */




#if 0
unsigned int * __thiscall /* type_info_scalar_dtor */(void *_this,byte param_1)

{
  /* type_info_dtor */(_this);
  if ((param_1 & 1) != 0) {
    Memory_SafeDelete((intptr_t)_this);
  }
  return _this;
}
#endif /* type_info_scalar_dtor */

#if 0 /* CRT: _except_handler3 */



void _except_handler3_unwind(unsigned char *UNRECOVERED_JUMPTABLE)

{
  pExceptionList = *(void **)pExceptionList;
                    // WARNING: Could not recover jumptable at 0x1000a96d. Too many branches
                    // WARNING: Treating indirect jump as call
  ((void (*)(void))UNRECOVERED_JUMPTABLE)();
  return;
}
#endif
#if 0 /* CRT: _except_handler3 */




#if 0
void _except_handler3(unsigned int param_1,unsigned char *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    // WARNING: Could not recover jumptable at 0x1000a97b. Too many branches
                    // WARNING: Treating indirect jump as call
  ((void (*)(void))UNRECOVERED_JUMPTABLE)();
  return;
}
#endif /* _except_handler3 */

#endif
#if 0 /* CRT: _except_handler3 */




void _except_handler3_2(unsigned int param_1,unsigned char *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    // WARNING: Could not recover jumptable at 0x1000a982. Too many branches
                    // WARNING: Treating indirect jump as call
  ((void (*)(void))UNRECOVERED_JUMPTABLE)();
  return;
}
#endif
#if 0 /* CRT: _except_handler3 */




void _except_handler3_3(unsigned int param_1,unsigned char *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    // WARNING: Could not recover jumptable at 0x1000a989. Too many branches
                    // WARNING: Treating indirect jump as call
  ((void (*)(void))UNRECOVERED_JUMPTABLE)();
  return;
}
#endif




void _local_unwind_ex(PVOID param_1,PEXCEPTION_RECORD param_2)

{
  void *pvVar1;
  
  pvVar1 = pExceptionList;
  RtlUnwind(param_1,(PVOID)0x1000a9b3,param_2,(PVOID)0x0);
  param_2->ExceptionFlags = param_2->ExceptionFlags & 0xfffffffd;
  *(void **)pvVar1 = pExceptionList;
  pExceptionList = pvVar1;
  return;
}
#if 0 /* CRT: __CppXcptFilter */



unsigned int __cdecl
__CppXcptFilter(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,unsigned int param_4)

{
  int *in_EAX;
  unsigned int uVar1;
  
  uVar1 = _CxxThrowHelper(param_1,param_2,param_3,param_4,in_EAX,0,(PVOID)0x0,'\0');
  return uVar1;
}
#endif
#if 0 /* CRT: _EH_prolog3_catch */




unsigned int __cdecl
_EH_prolog3_catch(unsigned int param_1,unsigned int param_2,unsigned int param_3,int param_4,int param_5)

{
  unsigned int uVar1;
  void *local_18;
  void *local_14;
  unsigned int local_10;
  unsigned int local_c;
  int local_8;
  
  local_10 = param_2;
  local_14 = _EH_except_handler3;
  local_8 = param_4 + 1;
  local_c = param_1;
  local_18 = pExceptionList;
  pExceptionList = &local_18;
  uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
  pExceptionList = local_18;
  return uVar1;
}
#endif
#if 0 /* CRT: _EH_except_handler3 */
#if 0 /* CRT: _except_handler3 */




#if 0
void __cdecl _EH_except_handler3(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3)

{
  _CxxThrowHelper(param_1,*(PVOID *)((intptr_t)param_2 + 0xc),param_3,0,*(int **)((intptr_t)param_2 + 8),
                  *(int *)((intptr_t)param_2 + 0x10),param_2,'\0');
  return;
}
#endif /* _EH_except_handler3 */

#endif

#endif

#if 0 /* CRT: __CxxFrameHandler */



unsigned int __cdecl
__CxxFrameHandler(unsigned int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4,
                 unsigned int param_5,unsigned int param_6,unsigned int param_7)

{
  DWORD *pDVar1;
  unsigned int uVar2;
  unsigned int **ppuVar3;
  unsigned int *local_34;
  unsigned int local_30;
  unsigned int *local_2c;
  void *local_28;
  unsigned int local_24;
  unsigned int local_20;
  unsigned int local_1c;
  unsigned int local_18;
  unsigned int local_14;
  unsigned char *local_10;
  unsigned char *local_c;
  int local_8;
  
  local_c = &uStack00000000;
  local_10 = &uStack00000000;
  local_28 = __CxxFrameHandler_old;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x1000ab2b;
  local_2c = pExceptionList;
  pExceptionList = &local_2c;
  local_34 = param_1;
  local_30 = param_3;
  ppuVar3 = &local_34;
  uVar2 = *param_1;
  pDVar1 = _getptd();
  (*(void *)pDVar1[0x1a])(uVar2,ppuVar3);
  if (local_8 != 0) {
    *local_2c = *(unsigned int *)pExceptionList;
  }
  pExceptionList = local_2c;
  return 0;
}
#endif
#if 0 /* CRT: __CxxFrameHandler */




#if 0
unsigned int __cdecl __CxxFrameHandler_old(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3)

{
  unsigned int uVar1;
  
  if ((param_1->ExceptionFlags & 0x66) != 0) {
    *(unsigned int *)((intptr_t)param_2 + 0x24) = 1;
    return 1;
  }
  _CxxThrowHelper(param_1,*(PVOID *)((intptr_t)param_2 + 0xc),param_3,0,*(int **)((intptr_t)param_2 + 8),
                  *(int *)((intptr_t)param_2 + 0x10),*(PVOID *)((intptr_t)param_2 + 0x14),'\x01');
  if (*(int *)((intptr_t)param_2 + 0x24) == 0) {
    _local_unwind_ex(param_2,param_1);
  }
                    // WARNING: Could not recover jumptable at 0x1000abc3. Too many branches
                    // WARNING: Treating indirect jump as call
  uVar1 = (**(void **)((intptr_t)param_2 + 0x18))();
  return uVar1;
}
#endif /* __CxxFrameHandler_old */

#endif




int __cdecl _RTC_CheckCode(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = *(uint *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  uVar4 = uVar5;
  uVar3 = uVar5;
  while (uVar2 = uVar4, -1 < param_2) {
    if (uVar5 == 0xffffffff) {
      _invalid_parameter();
    }
    uVar5 = uVar5 - 1;
    if (((*(int *)(iVar1 + 4 + uVar5 * 0x14) < param_3) &&
        (param_3 <= *(int *)(iVar1 + uVar5 * 0x14 + 8))) || (uVar4 = uVar2, uVar5 == 0xffffffff)) {
      param_2 = param_2 + -1;
      uVar4 = uVar5;
      uVar3 = uVar2;
    }
  }
  uVar5 = uVar5 + 1;
  *param_4 = uVar5;
  *param_5 = uVar3;
  if ((*(uint *)(param_1 + 0xc) < uVar3) || (uVar3 < uVar5)) {
    _invalid_parameter();
  }
  return iVar1 + uVar5 * 0x14;
}



// Library Function - Single Match
//  __global_unwind2
// 
// Library: Visual Studio

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x1000ac64,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}



// Library Function - Single Match
//  __local_unwind2
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
// Studio 2003 Release
#if 0 /* CRT: __local_unwind2 */

#if 0
void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvStack_1c;
  unsigned char *puStack_18;
  unsigned int local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_1000ac6c;
  pvStack_1c = pExceptionList;
  pExceptionList = &pvStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(unsigned int *)(iVar1 + iVar2 * 0xc);
    *(unsigned int *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      _SEH_prolog();
      ((*(void (**)(void)))iVar1 + 8 + iVar2 * 0xc)();
    }
  }
  pExceptionList = pvStack_1c;
  return;
}
#endif /* __local_unwind2 */

#endif




// Library Function - Single Match
//  __abnormal_termination
// 
// Library: Visual Studio

int __cdecl __abnormal_termination(void)

{
  int iVar1;
  
  iVar1 = 0;
  if ((*(unsigned char **)((intptr_t)pExceptionList + 4) == &LAB_1000ac6c) &&
     (*(int *)((intptr_t)pExceptionList + 8) == *(int *)(*(int *)((intptr_t)pExceptionList + 0xc) + 0xc))) {
    iVar1 = 1;
  }
  return iVar1;
}



// Library Function - Single Match
//  __NLG_Notify1
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
// Studio 2019 Release

#if 0
void __fastcall __NLG_Notify1(unsigned int param_1)

{
  unsigned int in_EAX;
  unsigned int unaff_EBP;
  
  DAT_10021320 = param_1;
  DAT_1002131c = in_EAX;
  DAT_10021324 = unaff_EBP;
  return;
}
#endif /* __NLG_Notify1 */




void _SEH_prolog(void)

{
  unsigned int in_EAX;
  int unaff_EBP;
  
  DAT_10021320 = *(unsigned int *)(unaff_EBP + 8);
  DAT_1002131c = in_EAX;
  DAT_10021324 = unaff_EBP;
  return;
}



#if 0
int __cdecl _vsnprintf(unsigned char *param_1,byte *param_2,unsigned int *param_3)

{
  int iVar1;
  unsigned char *local_24;
  int local_20;
  unsigned char *local_1c;
  unsigned int local_18;
  
  local_1c = param_1;
  local_24 = param_1;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = _output((int *)&local_24,param_2,param_3);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    _out_putc_wide(0,(int *)&local_24);
  }
  else {
    *local_24 = 0;
  }
  return iVar1;
}
#endif /* _vsnprintf */




#if 0
long double __cdecl _ftol2_sse(int param_1,int param_2)

{
  return (long double)(param_1 - param_2);
}
#endif /* _ftol2_sse */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
void _cinit(void)

{
  void *extraout_ECX;
  
  _fptrap_init();
  _DAT_10023544 = __isa_available_init();
  _fprestore(extraout_ECX);
  return;
}
#endif /* _cinit */




void _fptrap_init(void)

{
  PTR___fptrap_10021428 = &LAB_1000c97e;
  PTR___fptrap_10021424 = (void*)(intptr_t)__cfltcvt;
  PTR___fptrap_1002142c = (void*)(intptr_t)__fassign;
  PTR___fptrap_10021430 = (void*)(intptr_t)_strtod_scan;
  PTR___fptrap_10021434 = &LAB_1000c9cc;
  PTR___fptrap_10021438 = (void*)(intptr_t)__cfltcvt;
  return;
}



// Library Function - Single Match
//  __ftol
// 
// Library: Visual Studio

#if 0
longlong __ftol(void)

{
  long double in_ST0;
  
  return (longlong)ROUND(in_ST0);
}
#endif /* __ftol */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
unsigned int _CRTDLL_INIT(unsigned int param_1,int param_2)

{
  BOOL BVar1;
  int iVar2;
  unsigned int uVar3;
  
  if (param_2 == 1) {
    dwWindowsVersion = GetVersion();
    BVar1 = _heap_create(1);
    if (BVar1 != 0) {
      _DAT_100234f0 = dwWindowsVersion >> 8 & 0xff;
      _DAT_100234ec = dwWindowsVersion & 0xff;
      dwWindowsVersion = dwWindowsVersion >> 0x10;
      _DAT_100234e8 = _DAT_100234ec * 0x100 + _DAT_100234f0;
      iVar2 = _lock_init_ptd();
      if (iVar2 != 0) {
        DAT_10025000 = GetCommandLineA();
        DAT_1002354c = _getenv_init();
        _initstdio();
        _parse_cmdline();
        _initenv();
        _initterm_table();
        crtInitCount = crtInitCount + 1;
        goto LAB_1000aef6;
      }
      _heap_teardown();
    }
LAB_1000ae83:
    uVar3 = 0;
  }
  else {
    if (param_2 == 0) {
      if (crtInitCount < 1) goto LAB_1000ae83;
      crtInitCount = crtInitCount + -1;
      if (DAT_1002351c == 0) {
        _cexit();
      }
      _freestdio();
      _lock_ptd_uninit();
      _heap_teardown();
    }
    else if (param_2 == 3) {
      _free_ptd((LPVOID)0x0);
    }
LAB_1000aef6:
    uVar3 = 1;
  }
  return uVar3;
}
#endif /* _CRTDLL_INIT */




BOOL DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpReserved)

{
  DWORD dwServerResult;
  int nCrtResult;
  BOOL resultCallback;
  DWORD nReason;
  
  nReason = fdwReason;
  nCrtResult = crtInitCount;
  if (fdwReason != 0) {
    if ((fdwReason != 1) && (fdwReason != 2)) goto LAB_1000af44;
    if ((g_pDllCallback != nullptr) &&
       (nCrtResult = (*(int (__cdecl *)(void*,int,void*))g_pDllCallback)(hinstDLL,fdwReason,lpReserved), nCrtResult == 0)) {
      return 0;
    }
    nCrtResult = _CRTDLL_INIT(hinstDLL,fdwReason);
  }
  if (nCrtResult == 0) {
    return 0;
  }
LAB_1000af44:
  dwServerResult = Server_SetHInstance(hinstDLL);
  if (fdwReason == 1) {
    if (dwServerResult != 0) {
      return dwServerResult;
    }
    _CRTDLL_INIT(hinstDLL,0);
  }
  if ((fdwReason != 0) && (fdwReason != 3)) {
    return dwServerResult;
  }
  nCrtResult = _CRTDLL_INIT(hinstDLL,fdwReason);
  fdwReason = dwServerResult;
  if (nCrtResult == 0) {
    fdwReason = 0;
  }
  if (fdwReason != 0) {
    if (g_pDllCallback != nullptr) {
      resultCallback = (*(int (__cdecl *)(void*,int,void*))g_pDllCallback)(hinstDLL,nReason,lpReserved);
      return resultCallback;
    }
    return fdwReason;
  }
  return 0;
}



// Library Function - Single Match
//  __amsg_exit
// 
// Library: Visual Studio 2003 Release

#if 0
void __cdecl __amsg_exit(int param_1)

{
  if ((DAT_10023554 == 1) || ((DAT_10023554 == 0 && (DAT_10023558 == 1)))) {
    _invalid_parameter_noinfo();
  }
  _RtMsgAndAbort(param_1);
  (*(void *)PTR___exit_1002133c)(0xff);
  return;
}
#endif /* __amsg_exit */




// Library Function - Single Match
//  _strrchr
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

#if 0
char * __cdecl _strrchr(char *_Str,int _Ch)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = _Str;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = _Str + 1;
    cVar1 = *_Str;
    _Str = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while ((char)_Ch != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != (char)_Ch) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}
#endif /* _strrchr */




#if 0
uint __cdecl _out_putc_wide(uint param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  char *pcVar3;
  int *piVar4;
  byte bVar5;
  undefined3 extraout_var;
  unsigned char *puVar6;
  int *piVar7;
  
  piVar4 = param_2;
  uVar1 = param_2[3];
  uVar2 = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_1000b103:
    param_2[3] = uVar1 | 0x20;
  }
  else {
    if ((uVar1 & 1) != 0) {
      param_2[1] = 0;
      if ((uVar1 & 0x10) == 0) goto LAB_1000b103;
      *param_2 = param_2[2];
      param_2[3] = uVar1 & 0xfffffffe;
    }
    uVar1 = param_2[3];
    param_2[1] = 0;
    param_2 = (int *)0x0;
    piVar4[3] = uVar1 & 0xffffffef | 2;
    if (((uVar1 & 0x10c) == 0) &&
       (((piVar4 != (int *)&DAT_10021518 && (piVar4 != (int *)&DAT_10021538)) ||
        (bVar5 = _isatty_std(uVar2), CONCAT31(extraout_var,bVar5) == 0)))) {
      _flush_stdout_init(piVar4);
    }
    if ((*(ushort *)(piVar4 + 3) & 0x108) == 0) {
      piVar7 = (int *)0x1;
      param_2 = (int *)_write(uVar2,(char *)&param_1,1);
    }
    else {
      pcVar3 = (char *)piVar4[2];
      piVar7 = (int *)(*piVar4 - (intptr_t)pcVar3);
      *piVar4 = (intptr_t)(pcVar3 + 1);
      piVar4[1] = piVar4[6] + -1;
      if ((intptr_t)piVar7 < 1) {
        if (uVar2 == 0xffffffff) {
          puVar6 = &DAT_10021440;
        }
        else {
          puVar6 = (unsigned char *)((&DAT_10024ec0)[(intptr_t)uVar2 >> 5] + (uVar2 & 0x1f) * 0x24);
        }
        if ((puVar6[4] & 0x20) != 0) {
          _lseek(uVar2,0,2);
        }
      }
      else {
        param_2 = (int *)_write(uVar2,pcVar3,(uintptr_t)piVar7);
      }
      *(unsigned char *)piVar4[2] = (unsigned char)param_1;
    }
    if (param_2 == piVar7) {
      return param_1 & 0xff;
    }
    piVar4[3] = piVar4[3] | 0x20;
  }
  return 0xffffffff;
}
#endif /* _out_putc_wide */




#if 0
int __cdecl _output(int *param_1,byte *param_2,unsigned int *param_3)

{
  byte *pbVar1;
  uint uVar2;
  WCHAR *pWVar3;
  WCHAR *pWVar4;
  unsigned int uVar5;
  short *psVar6;
  int *piVar7;
  int iVar8;
  byte bVar9;
  int iVar10;
  uint uVar11;
  unsigned char *puVar12;
  ulonglong uVar13;
  unsigned long long uVar14;
  ulonglong uVar15;
  unsigned char local_24c [511];
  unsigned char local_4d;
  unsigned int local_4c;
  unsigned int local_48;
  uint local_44;
  uint local_40;
  CHAR local_3c [4];
  unsigned int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  char local_1a;
  char local_19;
  int local_18;
  int local_14;
  unsigned char *local_10;
  WCHAR *local_c;
  uint local_8;
  
  local_34 = 0;
  bVar9 = *param_2;
  local_10 = (unsigned char *)0x0;
  local_18 = 0;
  pbVar1 = param_2;
  do {
    if ((bVar9 == 0) || (param_2 = pbVar1 + 1, local_18 < 0)) {
      return local_18;
    }
    if (((char)bVar9 < ' ') || ('x' < (char)bVar9)) {
      uVar2 = 0;
    }
    else {
      uVar2 = (byte)(&DAT_1001c03c)[(char)bVar9] & 0xf;
    }
    local_34 = (intptr_t)(char)(&DAT_1001c05c)[uVar2 * 8 + local_34] >> 4;
    switch(local_34) {
    case 0:
switchD_1000b17d_caseD_0:
      local_28 = 0;
      if ((PTR_DAT_10021780[(uintptr_t)bVar9 * 2 + 1] & 0x80) != 0) {
        _putc_nolock((intptr_t)(char)bVar9,param_1,&local_18);
        bVar9 = *param_2;
        param_2 = pbVar1 + 2;
      }
      _putc_nolock((intptr_t)(char)bVar9,param_1,&local_18);
      break;
    case 1:
      local_14 = -1;
      local_38 = 0;
      local_2c = 0;
      local_24 = 0;
      local_20 = 0;
      local_8 = 0;
      local_28 = 0;
      break;
    case 2:
      if (bVar9 == 0x20) {
        local_8 = local_8 | 2;
      }
      else if (bVar9 == 0x23) {
        local_8 = local_8 | 0x80;
      }
      else if (bVar9 == 0x2b) {
        local_8 = local_8 | 1;
      }
      else if (bVar9 == 0x2d) {
        local_8 = local_8 | 4;
      }
      else if (bVar9 == 0x30) {
        local_8 = local_8 | 8;
      }
      break;
    case 3:
      if (bVar9 == 0x2a) {
        local_24 = _get_int_arg((int *)&param_3);
        if (local_24 < 0) {
          local_8 = local_8 | 4;
          local_24 = -local_24;
        }
      }
      else {
        local_24 = (char)bVar9 + -0x30 + local_24 * 10;
      }
      break;
    case 4:
      local_14 = 0;
      break;
    case 5:
      if (bVar9 == 0x2a) {
        local_14 = _get_int_arg((int *)&param_3);
        if (local_14 < 0) {
          local_14 = -1;
        }
      }
      else {
        local_14 = (char)bVar9 + -0x30 + local_14 * 10;
      }
      break;
    case 6:
      if (bVar9 == 0x49) {
        if ((*param_2 != 0x36) || (pbVar1[2] != 0x34)) {
          local_34 = 0;
          goto switchD_1000b17d_caseD_0;
        }
        param_2 = pbVar1 + 3;
        local_8 = local_8 | 0x8000;
      }
      else if (bVar9 == 0x68) {
        local_8 = local_8 | 0x20;
      }
      else if (bVar9 == 0x6c) {
        local_8 = local_8 | 0x10;
      }
      else if (bVar9 == 0x77) {
        local_8 = local_8 | 0x800;
      }
      break;
    case 7:
      pWVar4 = local_c;
      if ((char)bVar9 < 'h') {
        if ((char)bVar9 < 'e') {
          if ((char)bVar9 < 'Y') {
            if (bVar9 == 0x58) {
LAB_1000b58e:
              local_30 = 7;
LAB_1000b595:
              local_10 = (unsigned char *)0x10;
              if ((local_8 & 0x80) != 0) {
                local_1a = '0';
                local_19 = (char)local_30 + 'Q';
                local_20 = 2;
              }
              goto LAB_1000b5ff;
            }
            if (bVar9 != 0x43) {
              if ((bVar9 != 0x45) && (bVar9 != 0x47)) {
                if (bVar9 == 0x53) {
                  if ((local_8 & 0x830) == 0) {
                    local_8 = local_8 | 0x800;
                  }
                  goto LAB_1000b33c;
                }
                goto LAB_1000b719;
              }
              local_38 = 1;
              bVar9 = bVar9 + 0x20;
              goto LAB_1000b39d;
            }
            if ((local_8 & 0x830) == 0) {
              local_8 = local_8 | 0x800;
            }
LAB_1000b3ca:
            if ((local_8 & 0x810) == 0) {
              uVar5 = _get_int_arg((int *)&param_3);
              local_24c[0] = (char)uVar5;
              local_10 = (unsigned char *)0x1;
            }
            else {
              uVar5 = _get_short_arg((int *)&param_3);
              local_10 = (unsigned char *)_wcstombs_l(local_24c, (WCHAR, NULL, 0)uVar5);
              if ((intptr_t)local_10 < 0) {
                local_2c = 1;
              }
            }
            pWVar4 = (WCHAR *)local_24c;
          }
          else if (bVar9 == 0x5a) {
            psVar6 = (short *)_get_int_arg((int *)&param_3);
            if ((psVar6 == (short *)0x0) ||
               (pWVar4 = *(WCHAR **)(psVar6 + 2), pWVar4 == (WCHAR *)0x0)) {
              local_c = (WCHAR *)PTR_DAT_10021340;
              pWVar4 = (WCHAR *)PTR_DAT_10021340;
              goto LAB_1000b50f;
            }
            if ((local_8 & 0x800) == 0) {
              local_28 = 0;
              local_10 = (unsigned char *)(intptr_t)*psVar6;
            }
            else {
              local_28 = 1;
              local_10 = (unsigned char *)((uintptr_t)(intptr_t)*psVar6 >> 1);
            }
          }
          else {
            if (bVar9 == 99) goto LAB_1000b3ca;
            if (bVar9 == 100) goto LAB_1000b5f4;
          }
        }
        else {
LAB_1000b39d:
          local_8 = local_8 | 0x40;
          pWVar4 = (WCHAR *)local_24c;
          if (local_14 < 0) {
            local_14 = 6;
          }
          else if ((local_14 == 0) && (bVar9 == 0x67)) {
            local_14 = 1;
          }
          local_4c = *param_3;
          local_48 = param_3[1];
          param_3 = param_3 + 2;
          local_c = pWVar4;
          (*(void *)PTR___fptrap_10021424)(&local_4c,local_24c,(intptr_t)(char)bVar9,local_14,local_38);
          uVar2 = local_8 & 0x80;
          if ((uVar2 != 0) && (local_14 == 0)) {
            (*(void *)PTR___fptrap_10021430)(local_24c);
          }
          if ((bVar9 == 0x67) && (uVar2 == 0)) {
            (*(void *)PTR___fptrap_10021428)(local_24c);
          }
          if (local_24c[0] == '-') {
            local_8 = local_8 | 0x100;
            pWVar4 = (WCHAR *)(local_24c + 1);
            local_c = pWVar4;
          }
LAB_1000b50f:
          local_10 = (unsigned char *)_strlen((char *)pWVar4);
          pWVar4 = local_c;
        }
      }
      else {
        if (bVar9 == 0x69) {
LAB_1000b5f4:
          local_8 = local_8 | 0x40;
        }
        else {
          if (bVar9 == 0x6e) {
            piVar7 = (int *)_get_int_arg((int *)&param_3);
            if ((local_8 & 0x20) == 0) {
              *piVar7 = local_18;
            }
            else {
              *(unsigned short *)piVar7 = (unsigned short)local_18;
            }
            local_2c = 1;
            break;
          }
          if (bVar9 == 0x6f) {
            local_10 = (unsigned char *)0x8;
            if ((local_8 & 0x80) != 0) {
              local_8 = local_8 | 0x200;
            }
            goto LAB_1000b5ff;
          }
          if (bVar9 == 0x70) {
            local_14 = 8;
            goto LAB_1000b58e;
          }
          if (bVar9 == 0x73) {
LAB_1000b33c:
            iVar10 = local_14;
            if (local_14 == -1) {
              iVar10 = 0x7fffffff;
            }
            pWVar3 = (WCHAR *)_get_int_arg((int *)&param_3);
            if ((local_8 & 0x810) == 0) {
              pWVar4 = pWVar3;
              if (pWVar3 == (WCHAR *)0x0) {
                pWVar3 = (WCHAR *)PTR_DAT_10021340;
                pWVar4 = (WCHAR *)PTR_DAT_10021340;
              }
              for (; (iVar10 != 0 && ((char)*pWVar3 != '\0')); pWVar3 = (WCHAR *)((intptr_t)pWVar3 + 1))
              {
                iVar10 = iVar10 + -1;
              }
              local_10 = (unsigned char *)((intptr_t)pWVar3 - (intptr_t)pWVar4);
            }
            else {
              if (pWVar3 == (WCHAR *)0x0) {
                pWVar3 = (WCHAR *)PTR_DAT_10021344;
              }
              local_28 = 1;
              for (pWVar4 = pWVar3; (iVar10 != 0 && (*pWVar4 != L'\0')); pWVar4 = pWVar4 + 1) {
                iVar10 = iVar10 + -1;
              }
              local_10 = (unsigned char *)((intptr_t)pWVar4 - (intptr_t)pWVar3 >> 1);
              pWVar4 = pWVar3;
            }
            goto LAB_1000b719;
          }
          if (bVar9 != 0x75) {
            if (bVar9 != 0x78) goto LAB_1000b719;
            local_30 = 0x27;
            goto LAB_1000b595;
          }
        }
        local_10 = (unsigned char *)0xa;
LAB_1000b5ff:
        if ((local_8 & 0x8000) == 0) {
          if ((local_8 & 0x20) == 0) {
            if ((local_8 & 0x40) == 0) {
              uVar2 = _get_int_arg((int *)&param_3);
              uVar13 = (ulonglong)uVar2;
              goto LAB_1000b652;
            }
            uVar2 = _get_int_arg((int *)&param_3);
          }
          else if ((local_8 & 0x40) == 0) {
            uVar2 = _get_int_arg((int *)&param_3);
            uVar2 = uVar2 & 0xffff;
          }
          else {
            uVar5 = _get_int_arg((int *)&param_3);
            uVar2 = (uintptr_t)(short)uVar5;
          }
          uVar13 = (ulonglong)(intptr_t)uVar2;
        }
        else {
          uVar13 = _get_ll_arg((int *)&param_3);
        }
LAB_1000b652:
        iVar10 = (intptr_t)(uVar13 >> 0x20);
        if ((((local_8 & 0x40) != 0) && (iVar10 == 0 || (longlong)uVar13 < 0)) &&
           ((longlong)uVar13 < 0)) {
          local_8 = local_8 | 0x100;
          uVar13 = CONCAT44(-(iVar10 + (uintptr_t)((intptr_t)uVar13 != 0)),-(intptr_t)uVar13);
        }
        uVar2 = (uintptr_t)(uVar13 >> 0x20);
        uVar15 = uVar13 & 0xffffffff;
        if ((local_8 & 0x8000) == 0) {
          uVar2 = 0;
        }
        if (local_14 < 0) {
          local_14 = 1;
        }
        else {
          local_8 = local_8 & 0xfffffff7;
        }
        if ((intptr_t)uVar13 == 0 && uVar2 == 0) {
          local_20 = 0;
        }
        local_c = (WCHAR *)&local_4d;
        while( true ) {
          uVar11 = (uintptr_t)uVar15;
          iVar10 = local_14 + -1;
          if ((local_14 < 1) && (uVar11 == 0 && uVar2 == 0)) break;
          local_40 = (intptr_t)local_10 >> 0x1f;
          local_44 = (uintptr_t)local_10;
          local_14 = iVar10;
          uVar14 = __aullrem(uVar11,uVar2,(uintptr_t)local_10,local_40);
          iVar10 = (intptr_t)uVar14 + 0x30;
          uVar15 = __aulldiv(uVar11,uVar2,local_44,local_40);
          uVar2 = (uintptr_t)(uVar15 >> 0x20);
          if (0x39 < iVar10) {
            iVar10 = iVar10 + local_30;
          }
          pWVar4 = (WCHAR *)((intptr_t)local_c + -1);
          *(char *)local_c = (char)iVar10;
          local_c = pWVar4;
        }
        iVar8 = -(intptr_t)local_c;
        local_10 = &local_4d + iVar8;
        pWVar4 = (WCHAR *)((intptr_t)local_c + 1);
        local_14 = iVar10;
        if (((local_8 & 0x200) != 0) &&
           ((*(char *)pWVar4 != '0' || (local_10 == (unsigned char *)0x0)))) {
          *(char *)local_c = '0';
          local_10 = (unsigned char *)((intptr_t)&local_4c + iVar8);
          pWVar4 = local_c;
        }
      }
LAB_1000b719:
      local_c = pWVar4;
      uVar2 = local_8;
      if (local_2c == 0) {
        if ((local_8 & 0x40) != 0) {
          if ((local_8 & 0x100) == 0) {
            if ((local_8 & 1) == 0) {
              if ((local_8 & 2) == 0) goto LAB_1000b751;
              local_1a = ' ';
            }
            else {
              local_1a = '+';
            }
          }
          else {
            local_1a = '-';
          }
          local_20 = 1;
        }
LAB_1000b751:
        iVar10 = (local_24 - local_20) - (intptr_t)local_10;
        if ((local_8 & 0xc) == 0) {
          _write_padding(0x20,iVar10,param_1,&local_18);
        }
        _write_string(&local_1a,local_20,param_1,&local_18);
        if (((uVar2 & 8) != 0) && ((uVar2 & 4) == 0)) {
          _write_padding(0x30,iVar10,param_1,&local_18);
        }
        if ((local_28 == 0) || (puVar12 = local_10, pWVar4 = local_c, (intptr_t)local_10 < 1)) {
          _write_string((char *)local_c,(intptr_t)local_10,param_1,&local_18);
        }
        else {
          do {
            puVar12 = puVar12 + -1;
            iVar8 = _wcstombs_l(local_3c, *pWVar4, NULL, 0);
            if (iVar8 < 1) break;
            _write_string(local_3c,iVar8,param_1,&local_18);
            pWVar4 = pWVar4 + 1;
          } while (puVar12 != (unsigned char *)0x0);
        }
        if ((local_8 & 4) != 0) {
          _write_padding(0x20,iVar10,param_1,&local_18);
        }
      }
    }
    bVar9 = *param_2;
    pbVar1 = param_2;
  } while( true );
}
#endif /* _output */




void __cdecl _putc_nolock(uint param_1,int *param_2,int *param_3)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    _out_putc_wide(param_1,(intptr_t)param_2);
  }
  else {
    *(unsigned char *)*param_2 = (unsigned char)param_1;
    *param_2 = *param_2 + 1;
    uVar2 = param_1 & 0xff;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}



void __cdecl _write_padding(uint param_1,int param_2,int *param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    _putc_nolock(param_1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}



void __cdecl _write_string(char *param_1,int param_2,int *param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    _putc_nolock((intptr_t)cVar1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}



unsigned int __cdecl _get_int_arg(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(unsigned int *)(*param_1 + -4);
}



unsigned long long __cdecl _get_ll_arg(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(unsigned long long *)(*param_1 + -8);
}



unsigned int __cdecl _get_short_arg(int *param_1)

{
  *param_1 = *param_1 + 4;
  return CONCAT22((short)((uintptr_t)*param_1 >> 0x10),*(unsigned short *)(*param_1 + -4));
}



#if 0
void _lock_cs_init(void)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002138c);
  InitializeCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002137c);
  InitializeCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002136c);
  InitializeCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002134c);
  return;
}
#endif /* _lock_cs_init */




#if 0
void _lock_cs_uninit(void)

{
  LPCRITICAL_SECTION *pp_Var1;
  
  pp_Var1 = &lpCriticalSection_10021348;
  do {
    if ((((*pp_Var1 != (LPCRITICAL_SECTION)0x0) &&
         (pp_Var1 != (LPCRITICAL_SECTION *)&lpCriticalSection_1002138c)) &&
        (pp_Var1 != (LPCRITICAL_SECTION *)&lpCriticalSection_1002137c)) &&
       ((pp_Var1 != (LPCRITICAL_SECTION *)&lpCriticalSection_1002136c &&
        (pp_Var1 != (LPCRITICAL_SECTION *)&lpCriticalSection_1002134c)))) {
      DeleteCriticalSection(*pp_Var1);
      free(*pp_Var1);
    }
    pp_Var1 = pp_Var1 + 1;
  } while ((intptr_t)pp_Var1 < 0x10021408);
  DeleteCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002136c);
  DeleteCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002137c);
  DeleteCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002138c);
  DeleteCriticalSection((LPCRITICAL_SECTION)lpCriticalSection_1002134c);
  return;
}
#endif /* _lock_cs_uninit */




#if 0
void __cdecl _lock_critical_section(int param_1)

{
  LPCRITICAL_SECTION *pp_Var1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  pp_Var1 = &lpCriticalSection_10021348 + param_1;
  if ((&lpCriticalSection_10021348)[param_1] == (LPCRITICAL_SECTION)0x0) {
    lpCriticalSection = _malloc(0x18);
    if (lpCriticalSection == (LPCRITICAL_SECTION)0x0) {
      __amsg_exit(0x11);
    }
    _lock_critical_section(0x11);
    if (*pp_Var1 == (LPCRITICAL_SECTION)0x0) {
      InitializeCriticalSection(lpCriticalSection);
      *pp_Var1 = lpCriticalSection;
    }
    else {
      free(lpCriticalSection);
    }
    _unlock_critical_section(0x11);
  }
  EnterCriticalSection(*pp_Var1);
  return;
}
#endif /* _lock_critical_section */




#if 0
void __cdecl _unlock_critical_section(int param_1)

{
  LeaveCriticalSection((&lpCriticalSection_10021348)[param_1]);
  return;
}
#endif /* _unlock_critical_section */




#if 0
unsigned int _lock_init_ptd(void)

{
  DWORD *lpTlsValue;
  BOOL BVar1;
  DWORD DVar2;
  
  _lock_cs_init();
  dwTlsIndex_10021408 = TlsAlloc();
  if (dwTlsIndex_10021408 != 0xffffffff) {
    lpTlsValue = (DWORD *)malloc(1);
    if (lpTlsValue != (DWORD *)0x0) {
      BVar1 = TlsSetValue(dwTlsIndex_10021408,lpTlsValue);
      if (BVar1 != 0) {
        _ptd_init((intptr_t)lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        return 1;
      }
    }
  }
  return 0;
}
#endif /* _lock_init_ptd */




void _lock_ptd_uninit(void)

{
  _lock_cs_uninit();
  if (dwTlsIndex_10021408 != 0xffffffff) {
    TlsFree(dwTlsIndex_10021408);
    dwTlsIndex_10021408 = 0xffffffff;
  }
  return;
}



void __cdecl _ptd_init(int param_1)

{
  *(unsigned char **)(param_1 + 0x50) = (unsigned char*)&DAT_10021990;
  *(unsigned int *)(param_1 + 0x14) = 1;
  return;
}
#if 0 /* CRT: _getptd */



#if 0
DWORD * _getptd(void)

{
  DWORD dwErrCode;
  DWORD *lpTlsValue;
  BOOL BVar1;
  DWORD DVar2;
  
  dwErrCode = GetLastError();
  lpTlsValue = TlsGetValue(dwTlsIndex_10021408);
  if (lpTlsValue == (DWORD *)0x0) {
    lpTlsValue = (DWORD *)malloc(1);
    if (lpTlsValue != (DWORD *)0x0) {
      BVar1 = TlsSetValue(dwTlsIndex_10021408,lpTlsValue);
      if (BVar1 != 0) {
        _ptd_init((intptr_t)lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        goto LAB_1000bb1c;
      }
    }
    __amsg_exit(0x10);
  }
LAB_1000bb1c:
  SetLastError(dwErrCode);
  return lpTlsValue;
}
#endif /* _getptd */

#endif




void __cdecl _free_ptd(LPVOID param_1)

{
  if (dwTlsIndex_10021408 != 0xffffffff) {
    if ((param_1 != (LPVOID)0x0) ||
       (param_1 = TlsGetValue(dwTlsIndex_10021408), param_1 != (LPVOID)0x0)) {
      if (*(LPVOID *)((intptr_t)param_1 + 0x24) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x24));
      }
      if (*(LPVOID *)((intptr_t)param_1 + 0x28) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x28));
      }
      if (*(LPVOID *)((intptr_t)param_1 + 0x30) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x30));
      }
      if (*(LPVOID *)((intptr_t)param_1 + 0x38) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x38));
      }
      if (*(LPVOID *)((intptr_t)param_1 + 0x40) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x40));
      }
      if (*(LPVOID *)((intptr_t)param_1 + 0x44) != (LPVOID)0x0) {
        free(*(LPVOID *)((intptr_t)param_1 + 0x44));
      }
      if (*(unsigned char **)((intptr_t)param_1 + 0x50) != &DAT_10021990) {
        free(*(unsigned char **)((intptr_t)param_1 + 0x50));
      }
      free(param_1);
    }
    TlsSetValue(dwTlsIndex_10021408,(LPVOID)0x0);
    return;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

int __cdecl
_mktime(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  int bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_28 [2];
  int local_20;
  int local_18;
  uint local_14;
  int local_c;
  
  uVar3 = param_1 - 0x76c;
  if (((intptr_t)uVar3 < 0x46) || (0x8a < (intptr_t)uVar3)) {
    iVar2 = -1;
  }
  else {
    iVar4 = *(int *)(&DAT_10021afc + param_2 * 4) + param_3;
    if (((uVar3 & 3) == 0) && (2 < param_2)) {
      iVar4 = iVar4 + 1;
    }
    _init_time();
    local_20 = param_4;
    local_18 = param_2 + -1;
    iVar2 = ((param_4 + (uVar3 * 0x16d + iVar4 + (param_1 + -0x76d >> 2)) * 0x18) * 0x3c + param_5)
            * 0x3c + DAT_10021a18 + 0x7c558180 + param_6;
    if ((param_7 == 1) ||
       (((param_7 == -1 && (DAT_10021a1c != 0)) &&
        (local_14 = uVar3, local_c = iVar4, bVar1 = _isDST(local_28),
        CONCAT31(extraout_var,bVar1) != 0)))) {
      iVar2 = iVar2 + _DAT_10021a20;
    }
  }
  return iVar2;
}



#if 0
int * __cdecl realloc(int *param_1,uint *param_2)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  
  if (param_1 == (int *)0x0) {
    piVar1 = _malloc((size_t)param_2);
  }
  else {
    if (param_2 == (uint *)0x0) {
      free(param_1);
    }
    else {
      do {
        if (param_2 < (uint *)0xffffffe1) {
          _lock_critical_section(9);
          puVar2 = (uint *)_heap_lookup_size((intptr_t)param_1);
          if (puVar2 == (uint *)0x0) {
            _unlock_critical_section(9);
            if (param_2 == (uint *)0x0) {
              param_2 = (uint *)0x1;
            }
            param_2 = (uint *)((intptr_t)param_2 + 0xfU & 0xfffffff0);
            piVar1 = HeapReAlloc(hHeap,0,param_1,(SIZE_T)param_2);
          }
          else {
            if (DAT_10021b34 < param_2) {
LAB_1000bd35:
              if (param_2 == (uint *)0x0) {
                param_2 = (uint *)0x1;
              }
              param_2 = (uint *)((intptr_t)param_2 + 0xfU & 0xfffffff0);
              piVar1 = HeapAlloc(hHeap,0,(SIZE_T)param_2);
              if (piVar1 != (int *)0x0) {
                puVar4 = (uint *)(param_1[-1] - 1U);
                if (param_2 <= (uint *)(param_1[-1] - 1U)) {
                  puVar4 = param_2;
                }
                memmove(piVar1,param_1,(uintptr_t)puVar4);
                _heap_free(puVar2,(uintptr_t)param_1);
              }
            }
            else {
              iVar3 = _heap_alloc2(puVar2,(intptr_t)param_1,(intptr_t)param_2);
              piVar1 = param_1;
              if (iVar3 == 0) {
                piVar1 = _heap_alloc(param_2);
                if (piVar1 == (int *)0x0) goto LAB_1000bd35;
                puVar4 = (uint *)(param_1[-1] - 1U);
                if (param_2 <= (uint *)(param_1[-1] - 1U)) {
                  puVar4 = param_2;
                }
                memmove(piVar1,param_1,(uintptr_t)puVar4);
                _heap_free(puVar2,(uintptr_t)param_1);
              }
              if (piVar1 == (int *)0x0) goto LAB_1000bd35;
            }
            _unlock_critical_section(9);
          }
          if (piVar1 != (int *)0x0) {
            return piVar1;
          }
        }
        if (DAT_10023790 == 0) {
          return (int *)0x0;
        }
        iVar3 = _heap_link(param_2);
      } while (iVar3 != 0);
    }
    piVar1 = (int *)0x0;
  }
  return piVar1;
}
#endif /* realloc */




// Library Function - Single Match
//  _malloc
// 
// Library: Visual Studio 2003 Release

#if 0
void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(_Size,DAT_10023790);
  return pvVar1;
}
#endif /* _malloc */




// Library Function - Single Match
//  __nh_malloc
// 
// Library: Visual Studio 2003 Release

#if 0
void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  int *piVar1;
  int iVar2;
  
  if (_Size < 0xffffffe1) {
    do {
      piVar1 = _malloc_base((uint *)_Size);
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
      if (_NhFlag == 0) {
        return (void *)0x0;
      }
      iVar2 = _heap_link(_Size);
    } while (iVar2 != 0);
  }
  return (void *)0x0;
}
#endif /* __nh_malloc */




#if 0
int * __cdecl _malloc_base(uint *param_1)

{
  int *piVar1;
  
  if (param_1 <= DAT_10021b34) {
    _lock_critical_section(9);
    piVar1 = _heap_alloc(param_1);
    _unlock_critical_section(9);
    if (piVar1 != (int *)0x0) {
      return piVar1;
    }
  }
  if (param_1 == (uint *)0x0) {
    param_1 = (uint *)0x1;
  }
  piVar1 = HeapAlloc(hHeap,0,(intptr_t)param_1 + 0xfU & 0xfffffff0);
  return piVar1;
}
#endif /* _malloc_base */




void __cdecl free(LPVOID param_1)

{
  uint *puVar1;
  
  if (param_1 != (LPVOID)0x0) {
    _lock_critical_section(9);
    puVar1 = (uint *)_heap_lookup_size((intptr_t)param_1);
    if (puVar1 != (uint *)0x0) {
      _heap_free(puVar1,(uintptr_t)param_1);
      _unlock_critical_section(9);
      return;
    }
    _unlock_critical_section(9);
    HeapFree((void*)hHeap,0,param_1);
  }
  return;
}



// Library Function - Single Match
//  _strcmp
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  unsigned short uVar1;
  unsigned int uVar2;
  byte bVar3;
  byte bVar4;
  int bVar5;
  
  if (((uintptr_t)_Str1 & 3) != 0) {
    if (((uintptr_t)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_1000bf34;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uintptr_t)_Str1 & 2) == 0) goto LAB_1000bf00;
    }
    uVar1 = *(unsigned short *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_1000bf34;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_1000bf34;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_1000bf00:
  while( true ) {
    uVar2 = *(unsigned int *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uintptr_t)uVar2 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uintptr_t)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)_Str2[2];
    if (bVar4 != _Str2[2]) break;
    bVar3 = (byte)((uintptr_t)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_1000bf34:
  return (uintptr_t)bVar5 * -2 + 1;
}
#if 0 /* CRT: _CxxThrowHelper */



unsigned int __cdecl
_CxxThrowHelper(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,unsigned int param_4,
               int *param_5,int param_6,PVOID param_7,char param_8)

{
  void *pcVar1;
  unsigned int uVar2;
  
  if (*param_5 != 0x19930520) {
    _invalid_parameter();
  }
  if ((param_1->ExceptionFlags & 0x66) == 0) {
    if (param_5[3] != 0) {
      if (((param_1->ExceptionCode == 0xe06d7363) && (0x19930520 < param_1->ExceptionInformation[0])
          ) && (pcVar1 = *(void **)(param_1->ExceptionInformation[2] + 8), pcVar1 != (void *)0x0)) {
        uVar2 = (*pcVar1)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        return uVar2;
      }
      __CxxFrameHandler_filter(param_1,param_2,param_3,param_4,(intptr_t)param_5,param_8,param_6,param_7)
      ;
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    __LocalUnwind((intptr_t)param_2,param_4,(intptr_t)param_5,-1);
  }
  return 1;
}
#endif
#if 0 /* CRT: __CxxFrameHandler */
#if 0 /* CRT: __CxxFrameHandler_filter */




void __cdecl
__CxxFrameHandler_filter
          (PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,unsigned int param_4,int param_5,
          char param_6,int param_7,PVOID param_8)

{
  byte *pbVar1;
  int bVar2;
  DWORD *pDVar3;
  undefined3 extraout_var;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_18 = local_18 & 0xffffff00;
  local_14 = *(int *)((intptr_t)param_2 + 8);
  if ((local_14 < -1) || (*(int *)(param_5 + 4) <= local_14)) {
    _invalid_parameter();
  }
  if (param_1->ExceptionCode == 0xe06d7363) {
    if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
       (param_1->ExceptionInformation[2] == 0)) {
      pDVar3 = _getptd();
      if (pDVar3[0x1b] == 0) {
        return;
      }
      pDVar3 = _getptd();
      param_1 = (PEXCEPTION_RECORD)pDVar3[0x1b];
      pDVar3 = _getptd();
      param_3 = pDVar3[0x1c];
      local_18 = CONCAT31((*((unsigned int*)&(local_18)+1)),1);
      bVar2 = IsBadReadPtr(param_1,1);
      if (CONCAT31(extraout_var,bVar2) == 0) {
        _invalid_parameter();
      }
      if (param_1->ExceptionCode != 0xe06d7363) goto LAB_1000c197;
      if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
         (param_1->ExceptionInformation[2] == 0)) {
        _invalid_parameter();
      }
    }
    iVar5 = local_14;
    if (((param_1->ExceptionCode == 0xe06d7363) && (param_1->NumberParameters == 3)) &&
       (param_1->ExceptionInformation[0] == 0x19930520)) {
      piVar4 = (int *)_RTC_CheckCode(param_5,param_7,local_14,&local_8,&local_1c);
      do {
        if (local_1c <= local_8) {
          if (param_6 == '\0') {
            return;
          }
          __CxxFrameHandler_cleanup_exception((intptr_t)param_1);
          return;
        }
        if ((*piVar4 <= iVar5) && (iVar5 <= piVar4[1])) {
          pbVar1 = (byte *)piVar4[4];
          for (local_10 = piVar4[3]; iVar5 = local_14, 0 < local_10; local_10 = local_10 + -1) {
            piVar6 = *(int **)(param_1->ExceptionInformation[2] + 0xc);
            for (local_c = *piVar6; 0 < local_c; local_c = local_c + -1) {
              piVar6 = piVar6 + 1;
              iVar5 = __type_match(pbVar1,(byte *)*piVar6,(uint *)param_1->ExceptionInformation[2]);
              if (iVar5 != 0) {
                __CxxFrameHandler_find_handler
                          (param_1,param_2,param_3,param_4,param_5,pbVar1,(byte *)*piVar6,piVar4,
                           param_7,param_8);
                iVar5 = local_14;
                goto LAB_1000c177;
              }
            }
            pbVar1 = pbVar1 + 0x10;
          }
        }
LAB_1000c177:
        local_8 = local_8 + 1;
        piVar4 = piVar4 + 5;
      } while( true );
    }
  }
LAB_1000c197:
  if (param_6 == '\0') {
    __CxxFrameHandler_unwind(param_1,param_2,param_3,param_4,param_5,local_14,param_7,param_8);
    return;
  }
  __CxxFrameHandler_fail_abort();
  return;
}
#endif

#endif
#if 0 /* CRT: __CxxFrameHandler */




void __cdecl
__CxxFrameHandler_unwind
          (PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,unsigned int param_4,int param_5,
          int param_6,int param_7,PVOID param_8)

{
  DWORD *pDVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint local_c;
  uint local_8;
  
  pDVar1 = _getptd();
  if ((pDVar1[0x1a] != 0) &&
     (iVar2 = __CxxFrameHandler(&param_1->ExceptionCode,param_2,param_3,param_4,param_5,param_7,
                                param_8), iVar2 != 0)) {
    return;
  }
  piVar3 = (int *)_RTC_CheckCode(param_5,param_7,param_6,&local_8,&local_c);
  for (; local_8 < local_c; local_8 = local_8 + 1) {
    if ((*piVar3 <= param_6) && (param_6 <= piVar3[1])) {
      iVar4 = piVar3[3] * 0x10 + piVar3[4];
      iVar2 = *(int *)(iVar4 + -0xc);
      if ((iVar2 == 0) || (*(char *)(iVar2 + 8) == '\0')) {
        __CxxFrameHandler_find_handler
                  (param_1,param_2,param_3,param_4,param_5,(byte *)(iVar4 + -0x10),(byte *)0x0,
                   piVar3,param_7,param_8);
      }
    }
    piVar3 = piVar3 + 5;
  }
  return;
}
#endif




#if 0
unsigned int __cdecl __type_match(byte *param_1,byte *param_2,uint *param_3)

{
  int iVar1;
  unsigned int uVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  if ((iVar1 == 0) || (*(char *)(iVar1 + 8) == '\0')) {
LAB_1000c2c3:
    uVar2 = 1;
  }
  else {
    if (iVar1 == *(int *)(param_2 + 4)) {
LAB_1000c29d:
      if (((((*param_2 & 2) == 0) || ((*param_1 & 8) != 0)) &&
          (((*param_3 & 1) == 0 || ((*param_1 & 1) != 0)))) &&
         (((*param_3 & 2) == 0 || ((*param_1 & 2) != 0)))) goto LAB_1000c2c3;
    }
    else {
      iVar1 = _strcmp((char *)(iVar1 + 8),(char *)(*(int *)(param_2 + 4) + 8));
      if (iVar1 == 0) goto LAB_1000c29d;
    }
    uVar2 = 0;
  }
  return uVar2;
}
#endif /* __type_match */




void __cdecl __LocalUnwind(int param_1,unsigned int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  puStack_c = (unsigned char*)&DAT_1001c0d0;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  pExceptionList = &local_14;
  for (iVar2 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar2 != param_4;
      iVar2 = *(int *)(*(int *)(param_3 + 8) + iVar2 * 8)) {
    if ((iVar2 < 0) || (*(int *)(param_3 + 4) <= iVar2)) {
      _invalid_parameter();
    }
    local_8 = 0;
    iVar1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar2 * 8);
    if (iVar1 != 0) {
      __CallSettingFrame_12(iVar1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar2;
  pExceptionList = local_14;
  return;
}
#if 0 /* CRT: __CxxFrameHandler */



void __cdecl
__CxxFrameHandler_find_handler
          (PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,unsigned int param_4,int param_5,
          byte *param_6,byte *param_7,int *param_8,int param_9,PVOID param_10)

{
  unsigned char *UNRECOVERED_JUMPTABLE;
  
  if (param_7 != (byte *)0x0) {
    __CxxFrameHandler_copy_exception((intptr_t)param_1,(intptr_t)param_2,param_6,param_7);
  }
  if (param_10 == (PVOID)0x0) {
    param_10 = param_2;
  }
  _local_unwind_ex(param_10,param_1);
  __LocalUnwind((intptr_t)param_2,param_4,param_5,*param_8);
  *(int *)((intptr_t)param_2 + 8) = param_8[1] + 1;
  UNRECOVERED_JUMPTABLE =
       (unsigned char *)
       __CxxFrameHandler_dispatch
                 ((uintptr_t)param_1,param_2,param_3,param_5,*(unsigned int *)(param_6 + 0xc),param_9,
                  0x100);
  if (UNRECOVERED_JUMPTABLE != (unsigned char *)0x0) {
    _except_handler3_unwind(UNRECOVERED_JUMPTABLE);
  }
  return;
}
#endif

#if 0 /* CRT: __CxxFrameHandler_dispatch */
#if 0 /* CRT: __CxxFrameHandler */



unsigned int __cdecl
__CxxFrameHandler_dispatch
          (DWORD param_1,unsigned int param_2,DWORD param_3,unsigned int param_4,unsigned int param_5,
          int param_6,int param_7)

{
  DWORD *pDVar1;
  unsigned int uVar2;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_1001c0e0;
  puStack_10 = &LAB_1000f844;
  local_14 = pExceptionList;
  pExceptionList = &local_14;
  _getptd();
  _getptd();
  pDVar1 = _getptd();
  pDVar1[0x1b] = param_1;
  pDVar1 = _getptd();
  pDVar1[0x1c] = param_3;
  local_8 = 1;
  uVar2 = _EH_prolog3_catch(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  __CxxFrameHandler_catch_cleanup();
  pExceptionList = local_14;
  return uVar2;
}
#endif

#endif
#if 0 /* CRT: __CxxFrameHandler */




void __CxxFrameHandler_catch_cleanup(void)

{
  DWORD *pDVar1;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(unsigned int *)(unaff_ESI + -4) = *(unsigned int *)(unaff_EBP + -0x28);
  pDVar1 = _getptd();
  pDVar1[0x1b] = *(DWORD *)(unaff_EBP + -0x1c);
  pDVar1 = _getptd();
  pDVar1[0x1c] = *(DWORD *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (*(int *)(unaff_EBP + -0x2c) != 0)))) {
    __abnormal_termination();
    __CxxFrameHandler_cleanup_exception((intptr_t)unaff_EDI);
  }
  return;
}
#endif
#if 0 /* CRT: __CxxFrameHandler */




void __cdecl __CxxFrameHandler_copy_exception(int param_1,int param_2,byte *param_3,byte *param_4)

{
  int *piVar1;
  int bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  unsigned int *puVar4;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  uint uVar5;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  puStack_c = &DAT_1001c0f8;
  puStack_10 = &LAB_1000f844;
  local_14 = pExceptionList;
  if (*(int *)(param_3 + 4) == 0) {
    return;
  }
  if (*(char *)(*(int *)(param_3 + 4) + 8) == '\0') {
    return;
  }
  if (*(int *)(param_3 + 8) == 0) {
    return;
  }
  piVar1 = (int *)(*(int *)(param_3 + 8) + 0xc + param_2);
  local_8 = 0;
  if ((*param_3 & 8) == 0) {
    if ((*param_4 & 1) == 0) {
      if (*(int *)(param_4 + 0x18) == 0) {
        pExceptionList = &local_14;
        bVar2 = IsBadReadPtr(*(void **)(param_1 + 0x18),1);
        if ((CONCAT31(extraout_var_03,bVar2) != 0) &&
           (bVar2 = IsBadWritePtr(piVar1,1), CONCAT31(extraout_var_04,bVar2) != 0)) {
          uVar5 = *(uint *)(param_4 + 0x14);
          puVar4 = (unsigned int *)
                   __CxxFrameHandler_ptr_offset(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
          memmove2(piVar1,puVar4,uVar5);
          pExceptionList = local_14;
          return;
        }
      }
      else {
        pExceptionList = &local_14;
        bVar2 = IsBadReadPtr(*(void **)(param_1 + 0x18),1);
        if (((CONCAT31(extraout_var_05,bVar2) != 0) &&
            (bVar2 = IsBadWritePtr(piVar1,1), CONCAT31(extraout_var_06,bVar2) != 0)) &&
           (bVar2 = IsBadCodePtr(*(FARPROC *)(param_4 + 0x18)), CONCAT31(extraout_var_07,bVar2) != 0
           )) {
          if ((*param_4 & 4) != 0) {
            __CxxFrameHandler_ptr_offset(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
            _except_handler3_3(piVar1,*(unsigned char **)(param_4 + 0x18));
            pExceptionList = local_14;
            return;
          }
          __CxxFrameHandler_ptr_offset(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
          _except_handler3_2(piVar1,*(unsigned char **)(param_4 + 0x18));
          pExceptionList = local_14;
          return;
        }
      }
    }
    else {
      pExceptionList = &local_14;
      bVar2 = IsBadReadPtr(*(void **)(param_1 + 0x18),1);
      if ((CONCAT31(extraout_var_01,bVar2) != 0) &&
         (bVar2 = IsBadWritePtr(piVar1,1), CONCAT31(extraout_var_02,bVar2) != 0)) {
        memmove2(piVar1,*(unsigned int **)(param_1 + 0x18),*(uint *)(param_4 + 0x14));
        if (*(int *)(param_4 + 0x14) != 4) {
          pExceptionList = local_14;
          return;
        }
        iVar3 = *piVar1;
        if (iVar3 == 0) {
          pExceptionList = local_14;
          return;
        }
        goto LAB_1000c5cb;
      }
    }
  }
  else {
    pExceptionList = &local_14;
    bVar2 = IsBadReadPtr(*(void **)(param_1 + 0x18),1);
    if ((CONCAT31(extraout_var,bVar2) != 0) &&
       (bVar2 = IsBadWritePtr(piVar1,1), CONCAT31(extraout_var_00,bVar2) != 0)) {
      iVar3 = *(int *)(param_1 + 0x18);
      *piVar1 = iVar3;
LAB_1000c5cb:
      iVar3 = __CxxFrameHandler_ptr_offset(iVar3,(int *)(param_4 + 8));
      *piVar1 = iVar3;
      pExceptionList = local_14;
      return;
    }
  }
  _invalid_parameter();
  pExceptionList = local_14;
  return;
}
#endif
#if 0 /* CRT: __CxxFrameHandler */
#if 0 /* CRT: __CxxFrameHandler_cleanup_exception */




void __cdecl __CxxFrameHandler_cleanup_exception(int param_1)

{
  unsigned char *UNRECOVERED_JUMPTABLE;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  puStack_c = &DAT_1001c108;
  puStack_10 = &LAB_1000f844;
  local_14 = pExceptionList;
  if ((param_1 != 0) &&
     (UNRECOVERED_JUMPTABLE = *(unsigned char **)(*(int *)(param_1 + 0x1c) + 4),
     UNRECOVERED_JUMPTABLE != (unsigned char *)0x0)) {
    local_8 = 0;
    pExceptionList = &local_14;
    _except_handler3(*(unsigned int *)(param_1 + 0x18),UNRECOVERED_JUMPTABLE);
  }
  pExceptionList = local_14;
  return;
}
#endif

#endif
#if 0 /* CRT: __CxxFrameHandler */




int __cdecl __CxxFrameHandler_ptr_offset(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2[1];
  iVar2 = *param_2 + param_1;
  if (-1 < iVar1) {
    iVar2 = iVar2 + *(int *)(*(int *)(iVar1 + param_1) + param_2[2]) + iVar1;
  }
  return iVar2;
}
#endif




// WARNING: Restarted to delay deadcode elimination for space: stack
// Library Function - Single Match
//  __CallSettingFrame@12
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
// Studio 2019 Release

void __CallSettingFrame_12(unsigned int param_1,unsigned int param_2,int param_3)

{
  void *pcVar1;
  
  pcVar1 = (void *)/* __NLG_Notify1 */
  ((int (*)())pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  /* __NLG_Notify1 */
  return;
}
#if 0 /* CRT: __CxxFrameHandler */



#if 0
void __CxxFrameHandler_fail_abort(void)

{
  DWORD *pDVar1;
  void *pvStack_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  puStack_c = &DAT_1001c118;
  puStack_10 = &LAB_1000f844;
  pvStack_14 = pExceptionList;
  local_8 = 0;
  pExceptionList = &pvStack_14;
  pDVar1 = _getptd();
  if (pDVar1[0x18] != 0) {
    local_8 = 1;
    pDVar1 = _getptd();
    ((void (*)(void))pDVar1[0x18])();
  }
  local_8 = 0xffffffff;
  _invoke_watson();
  return;
}
#endif /* __CxxFrameHandler_fail_abort */

#endif




void _invalid_parameter(void)

{
  void *pvStack_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  puStack_c = (unsigned char*)&DAT_1001c130;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  pvStack_14 = pExceptionList;
  pExceptionList = &pvStack_14;
  if (PTR___CxxFrameHandler_fail_abort_10021420 != (unsigned char *)0x0) {
    local_8 = 1;
    pExceptionList = &pvStack_14;
    ((void (*)(void))PTR___CxxFrameHandler_fail_abort_10021420)();
  }
  local_8 = 0xffffffff;
  __CxxFrameHandler_fail_abort();
  return;
}



void __fastcall _fprestore(void *param_1)

{
  _controlfp_s_restore(param_1,0x10000,0x30000);
  return;
}



// WARNING: Removing unreachable block (ram,0x1000c8f2)

unsigned int _cpuid_feature_check(void)

{
  return 0;
}



#if 0
void __isa_available_init(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  
  hModule = GetModuleHandleA("KERNEL32");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent");
    if (pFVar1 != (FARPROC)0x0) {
      (*pFVar1)(0);
      return;
    }
  }
  _cpuid_feature_check();
  return;
}
#endif /* __isa_available_init */




#if 0
void __cdecl _strtod_scan(char *param_1)

{
  char cVar1;
  char cVar2;
  unsigned char *_this;
  uint uVar3;
  unsigned char *puVar4;
  
  _this = (unsigned char *)(intptr_t)*param_1;
  uVar3 = towlower((uintptr_t)_this);
  if (uVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (cbMultiByte_10021b40 < 2) {
        uVar3 = (byte)PTR_DAT_10021780[*param_1 * 2] & 4;
        _this = PTR_DAT_10021780;
      }
      else {
        puVar4 = (unsigned char *)0x4;
        uVar3 = iswctype(_this, (intptr_t)*param_1);
        _this = puVar4;
      }
    } while (uVar3 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_10021b44;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}
#endif /* _strtod_scan */




// Library Function - Single Match
//  __fassign
// 
// Library: Visual Studio 2003 Release

#if 0
void __cdecl __fassign(int flag,char *argument,char *number)

{
  void *in_ECX;
  void *local_c;
  void *local_8;
  
  if (flag != 0) {
    local_c = in_ECX;
    local_8 = in_ECX;
    strtod(in_ECX, (uint *)&local_c)number);
    *(void **)argument = local_c;
    *(void **)(argument + 4) = local_8;
    return;
  }
  strtof(in_ECX, (uint *)&number)number);
  *(char **)argument = number;
  return;
}
#endif /* __fassign */




#if 0
unsigned char * __cdecl _ecvt(unsigned long long *param_1,unsigned char *param_2,int param_3,int param_4)

{
  uint local_2c [6];
  int local_14 [4];
  
  _ecvt_core((intptr_t)*param_1,(intptr_t)((ulonglong)*param_1 >> 0x20),local_14,local_2c);
  _cropzeros(param_2 + (uintptr_t)(0 < param_3) + (uintptr_t)(local_14[0] == 0x2d),param_3 + 1,(intptr_t)local_14);
  _cfltcvt_fmt(param_2,param_3,param_4,local_14,'\0');
  return param_2;
}
#endif /* _ecvt */




unsigned char * __cdecl
_cfltcvt_fmt(unsigned char *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  unsigned char *puVar1;
  unsigned char *puVar2;
  uint *puVar3;
  int iVar4;
  
  if (param_5 != '\0') {
    _strshift_right(param_1 + (*param_4 == 0x2d),(uint)(0 < param_2));
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  puVar2 = puVar1;
  if (0 < param_2) {
    puVar2 = puVar1 + 1;
    *puVar1 = puVar1[1];
    *puVar2 = DAT_10021b44;
  }
  puVar3 = (uint *)strcpy((char*)(puVar2 + param_2 + (uintptr_t)(param_5 == '\0')),(char*)"e+000");
  if (param_3 != 0) {
    *(unsigned char *)puVar3 = 0x45;
  }
  if (*(char *)param_4[3] != '0') {
    iVar4 = param_4[1] + -1;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
      *(unsigned char *)((intptr_t)puVar3 + 1) = 0x2d;
    }
    if (99 < iVar4) {
      *(char *)((intptr_t)puVar3 + 2) = *(char *)((intptr_t)puVar3 + 2) + (char)(iVar4 / 100);
      iVar4 = iVar4 % 100;
    }
    if (9 < iVar4) {
      *(char *)((intptr_t)puVar3 + 3) = *(char *)((intptr_t)puVar3 + 3) + (char)(iVar4 / 10);
      iVar4 = iVar4 % 10;
    }
    *(char *)(puVar3 + 1) = (char)puVar3[1] + (char)iVar4;
  }
  return param_1;
}



#if 0
char * __cdecl _fcvt(unsigned long long *param_1,char *param_2,size_t param_3)

{
  uint local_2c [6];
  int local_14;
  int local_10;
  
  _ecvt_core((intptr_t)*param_1,(intptr_t)((ulonglong)*param_1 >> 0x20),&local_14,local_2c);
  _cropzeros(param_2 + (local_14 == 0x2d),local_10 + param_3,(intptr_t)&local_14);
  _cfltcvt_fixed(param_2,param_3,&local_14,'\0');
  return param_2;
}
#endif /* _fcvt */




#if 0
char * __cdecl _cfltcvt_fixed(char *param_1,size_t param_2,int *param_3,char param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = param_3[1];
  if ((param_4 != '\0') && (iVar1 - 1U == param_2)) {
    iVar2 = *param_3;
    param_1[(uintptr_t)(iVar2 == 0x2d) + (iVar1 - 1U)] = '0';
    (param_1 + (uintptr_t)(iVar2 == 0x2d) + (iVar1 - 1U))[1] = '\0';
  }
  pcVar3 = param_1;
  if (*param_3 == 0x2d) {
    *param_1 = '-';
    pcVar3 = param_1 + 1;
  }
  if (param_3[1] < 1) {
    _strshift_right(pcVar3,1);
    *pcVar3 = '0';
    pcVar3 = pcVar3 + 1;
  }
  else {
    pcVar3 = pcVar3 + param_3[1];
  }
  if (0 < (intptr_t)param_2) {
    _strshift_right(pcVar3,1);
    *pcVar3 = DAT_10021b44;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (intptr_t)param_2)) {
        param_2 = -iVar1;
      }
      _strshift_right(pcVar3 + 1,param_2);
      _memset(pcVar3 + 1,0x30,param_2);
    }
  }
  return param_1;
}
#endif /* _cfltcvt_fixed */




#if 0
void __cdecl _gcvt(unsigned long long *param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  uint local_2c [6];
  int local_14;
  int local_10;
  
  _ecvt_core((intptr_t)*param_1,(intptr_t)((ulonglong)*param_1 >> 0x20),&local_14,local_2c);
  iVar1 = local_10 + -1;
  _cropzeros(param_2 + (local_14 == 0x2d),param_3,(intptr_t)&local_14);
  local_10 = local_10 + -1;
  if ((local_10 < -4) || ((intptr_t)param_3 <= local_10)) {
    _cfltcvt_fmt(param_2,param_3,param_4,&local_14,'\x01');
  }
  else {
    pcVar2 = param_2 + (local_14 == 0x2d);
    if (iVar1 < local_10) {
      do {
        pcVar3 = pcVar2;
        pcVar2 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
      pcVar3[-1] = '\0';
    }
    _cfltcvt_fixed(param_2,param_3,&local_14,'\x01');
  }
  return;
}
#endif /* _gcvt */




// Library Function - Single Match
//  __cfltcvt
// 
// Library: Visual Studio 2003 Release
#if 0 /* CRT: __cfltcvt */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  char *pcVar1;
  unsigned char *puVar2;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    puVar2 = _ecvt(arg,buffer,format,precision);
  }
  else {
    if (sizeInBytes == 0x66) {
      pcVar1 = _fcvt(arg,buffer,format);
      return (errno_t)pcVar1;
    }
    puVar2 = (unsigned char *)_gcvt(arg,buffer,format,precision);
  }
  return (errno_t)puVar2;
}
#endif




void __cdecl _strshift_right(char *param_1,int param_2)

{
  size_t sVar1;
  
  if (param_2 != 0) {
    sVar1 = _strlen(param_1);
    memmove2((unsigned int *)(param_1 + param_2),(unsigned int *)param_1,sVar1 + 1);
  }
  return;
}



#if 0
void _initstdio(void)

{
  unsigned int *puVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  DWORD DVar4;
  HANDLE hFile;
  UINT *pUVar5;
  int iVar6;
  uint uVar7;
  UINT UVar8;
  UINT UVar9;
  _STARTUPINFOA local_4c;
  byte *local_8;
  
  puVar2 = _malloc(0x480);
  if (puVar2 == (unsigned int *)0x0) {
    __amsg_exit(0x1b);
  }
  uNumber_10024ffc = 0x20;
  DAT_10024ec0 = puVar2;
  for (; puVar2 < DAT_10024ec0 + 0x120; puVar2 = puVar2 + 9) {
    *(unsigned char *)(puVar2 + 1) = 0;
    *puVar2 = 0xffffffff;
    puVar2[2] = 0;
    *(unsigned char *)((intptr_t)puVar2 + 5) = 10;
  }
  GetStartupInfoA(&local_4c);
  if ((local_4c.cbReserved2 != 0) && ((UINT *)local_4c.lpReserved2 != (UINT *)0x0)) {
    UVar8 = *(UINT *)local_4c.lpReserved2;
    pUVar5 = (UINT *)((intptr_t)local_4c.lpReserved2 + 4);
    local_8 = (byte *)((intptr_t)pUVar5 + UVar8);
    if (0x7ff < (intptr_t)UVar8) {
      UVar8 = 0x800;
    }
    UVar9 = UVar8;
    if ((intptr_t)uNumber_10024ffc < (intptr_t)UVar8) {
      puVar2 = &DAT_10024ec4;
      do {
        puVar3 = _malloc(0x480);
        UVar9 = uNumber_10024ffc;
        if (puVar3 == (unsigned int *)0x0) break;
        uNumber_10024ffc = uNumber_10024ffc + 0x20;
        *puVar2 = puVar3;
        puVar1 = puVar3;
        for (; puVar3 < puVar1 + 0x120; puVar3 = puVar3 + 9) {
          *(unsigned char *)(puVar3 + 1) = 0;
          *puVar3 = 0xffffffff;
          puVar3[2] = 0;
          *(unsigned char *)((intptr_t)puVar3 + 5) = 10;
          puVar1 = (unsigned int *)*puVar2;
        }
        puVar2 = puVar2 + 1;
        UVar9 = UVar8;
      } while ((intptr_t)uNumber_10024ffc < (intptr_t)UVar8);
    }
    uVar7 = 0;
    if (0 < (intptr_t)UVar9) {
      do {
        if (((*(HANDLE *)local_8 != (HANDLE)0xffffffff) && ((*pUVar5 & 1) != 0)) &&
           (((*pUVar5 & 8) != 0 || (DVar4 = GetFileType(*(HANDLE *)local_8), DVar4 != 0)))) {
          puVar2 = (unsigned int *)((intptr_t)(&DAT_10024ec0)[(intptr_t)uVar7 >> 5] + (uVar7 & 0x1f) * 0x24);
          *puVar2 = *(unsigned int *)local_8;
          *(byte *)(puVar2 + 1) = (byte)*pUVar5;
        }
        local_8 = local_8 + 4;
        uVar7 = uVar7 + 1;
        pUVar5 = (UINT *)((intptr_t)pUVar5 + 1);
      } while ((intptr_t)uVar7 < (intptr_t)UVar9);
    }
  }
  iVar6 = 0;
  do {
    puVar2 = DAT_10024ec0 + iVar6 * 9;
    if (DAT_10024ec0[iVar6 * 9] == -1) {
      *(unsigned char *)(puVar2 + 1) = 0x81;
      if (iVar6 == 0) {
        DVar4 = 0xfffffff6;
      }
      else {
        DVar4 = 0xfffffff5 - (iVar6 != 1);
      }
      hFile = GetStdHandle(DVar4);
      if ((hFile != (HANDLE)0xffffffff) && (DVar4 = GetFileType(hFile), DVar4 != 0)) {
        *puVar2 = hFile;
        if ((DVar4 & 0xff) != 2) {
          if ((DVar4 & 0xff) == 3) {
            *(byte *)(puVar2 + 1) = *(byte *)(puVar2 + 1) | 8;
          }
          goto LAB_1000ceef;
        }
      }
      *(byte *)(puVar2 + 1) = *(byte *)(puVar2 + 1) | 0x40;
    }
    else {
      *(byte *)(puVar2 + 1) = *(byte *)(puVar2 + 1) | 0x80;
    }
LAB_1000ceef:
    iVar6 = iVar6 + 1;
    if (2 < iVar6) {
      SetHandleCount(uNumber_10024ffc);
      return;
    }
  } while( true );
}
#endif /* _initstdio */




void _freestdio(void)

{
  LPCRITICAL_SECTION lpCriticalSection;
  uint *puVar1;
  uint uVar2;
  
  puVar1 = &DAT_10024ec0;
  do {
    uVar2 = *puVar1;
    if (uVar2 != 0) {
      if (uVar2 < uVar2 + 0x480) {
        lpCriticalSection = (LPCRITICAL_SECTION)(uVar2 + 0xc);
        do {
          if (lpCriticalSection[-1].SpinCount != 0) {
            DeleteCriticalSection(lpCriticalSection);
          }
          uVar2 = uVar2 + 0x24;
          lpCriticalSection = (LPCRITICAL_SECTION)&lpCriticalSection[1].OwningThread;
        } while (uVar2 < *puVar1 + 0x480);
      }
      free((LPVOID)*puVar1);
      *puVar1 = 0;
    }
    puVar1 = puVar1 + 1;
  } while ((intptr_t)puVar1 < 0x10024fc0);
  return;
}



#if 0
void _initenv(void)

{
  char cVar1;
  size_t sVar2;
  unsigned int *puVar3;
  void *pvVar4;
  int iVar5;
  uint *puVar6;
  
  if (DAT_10025028 == 0) {
    _initmbcp();
  }
  iVar5 = 0;
  for (puVar6 = DAT_1002354c; (char)*puVar6 != '\0'; puVar6 = (uint *)((intptr_t)puVar6 + sVar2 + 1)) {
    if ((char)*puVar6 != '=') {
      iVar5 = iVar5 + 1;
    }
    sVar2 = _strlen((char *)puVar6);
  }
  puVar3 = _malloc(iVar5 * 4 + 4);
  DAT_10023500 = puVar3;
  if (puVar3 == (unsigned int *)0x0) {
    __amsg_exit(9);
  }
  cVar1 = (char)*DAT_1002354c;
  puVar6 = DAT_1002354c;
  while (cVar1 != '\0') {
    sVar2 = _strlen((char *)puVar6);
    if ((char)*puVar6 != '=') {
      pvVar4 = _malloc(sVar2 + 1);
      *puVar3 = pvVar4;
      if (pvVar4 == (void *)0x0) {
        __amsg_exit(9);
      }
      strcpy((char*)*puVar3,puVar6);
      puVar3 = puVar3 + 1;
    }
    puVar6 = (uint *)((intptr_t)puVar6 + sVar2 + 1);
    cVar1 = (char)*puVar6;
  }
  free(DAT_1002354c);
  DAT_1002354c = (uint *)0x0;
  *puVar3 = 0;
  DAT_10025014 = 1;
  return;
}
#endif /* _initenv */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
void _parse_cmdline(void)

{
  unsigned int *puVar1;
  byte *pbVar2;
  int local_c;
  int local_8;
  
  if (DAT_10025028 == 0) {
    _initmbcp();
  }
  GetModuleFileNameA((HMODULE)0x0,&DAT_100235c0,0x104);
  _DAT_10023510 = &DAT_100235c0;
  pbVar2 = &DAT_100235c0;
  if (*DAT_10025000 != 0) {
    pbVar2 = DAT_10025000;
  }
  _parse_cmdline_core(pbVar2,(unsigned int *)0x0,(byte *)0x0,&local_8,&local_c);
  puVar1 = _malloc(local_c + local_8 * 4);
  if (puVar1 == (unsigned int *)0x0) {
    __amsg_exit(8);
  }
  _parse_cmdline_core(pbVar2,puVar1,(byte *)(puVar1 + local_8),&local_8,&local_c);
  _DAT_100234f8 = puVar1;
  _DAT_100234f4 = local_8 + -1;
  return;
}
#endif /* _parse_cmdline */




void __cdecl
_parse_cmdline_core(byte *param_1,unsigned int *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  int bVar2;
  int bVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  unsigned int *puVar7;
  
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (unsigned int *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while( true ) {
      bVar1 = param_1[1];
      pbVar4 = param_1 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      if (((*(byte *)((intptr_t)&DAT_10023a20 + bVar1 + 1) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
        pbVar4 = param_1 + 2;
      }
      *param_5 = *param_5 + 1;
      param_1 = pbVar4;
      if (param_3 != (byte *)0x0) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar4 == 0x22) {
      pbVar4 = param_1 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      bVar1 = *param_1;
      pbVar4 = param_1 + 1;
      if ((*(byte *)((intptr_t)&DAT_10023a20 + bVar1 + 1) & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        pbVar4 = param_1 + 2;
      }
      if (bVar1 == 0x20) break;
      if (bVar1 == 0) goto LAB_1000d157;
      param_1 = pbVar4;
    } while (bVar1 != 9);
    if (bVar1 == 0) {
LAB_1000d157:
      pbVar4 = pbVar4 + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  bVar2 = false;
  puVar7 = param_2;
  while (*pbVar4 != 0) {
    for (; (*pbVar4 == 0x20 || (*pbVar4 == 9)); pbVar4 = pbVar4 + 1) {
    }
    if (*pbVar4 == 0) break;
    if (puVar7 != (unsigned int *)0x0) {
      *puVar7 = param_3;
      puVar7 = puVar7 + 1;
      param_2 = puVar7;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar3 = true;
      uVar6 = 0;
      for (; *pbVar4 == 0x5c; pbVar4 = pbVar4 + 1) {
        uVar6 = uVar6 + 1;
      }
      if (*pbVar4 == 0x22) {
        pbVar5 = pbVar4;
        if ((uVar6 & 1) == 0) {
          if ((!bVar2) || (pbVar5 = pbVar4 + 1, pbVar4[1] != 0x22)) {
            bVar3 = false;
            pbVar5 = pbVar4;
          }
          bVar2 = !bVar2;
          puVar7 = param_2;
        }
        uVar6 = uVar6 >> 1;
        pbVar4 = pbVar5;
      }
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      bVar1 = *pbVar4;
      if ((bVar1 == 0) || ((!bVar2 && ((bVar1 == 0x20 || (bVar1 == 9)))))) break;
      if (bVar3) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)((intptr_t)&DAT_10023a20 + bVar1 + 1) & 4) != 0) {
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if ((*(byte *)((intptr_t)&DAT_10023a20 + bVar1 + 1) & 4) != 0) {
            *param_3 = bVar1;
            param_3 = param_3 + 1;
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      pbVar4 = pbVar4 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (puVar7 != (unsigned int *)0x0) {
    *puVar7 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}



#if 0
LPSTR _getenv_init(void)

{
  char cVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  WCHAR *pWVar4;
  int iVar5;
  size_t _Size;
  LPSTR pCVar6;
  char *pcVar7;
  LPWCH lpWideCharStr;
  LPCH pCVar9;
  LPSTR local_8;
  char *pcVar8;
  
  lpWideCharStr = (LPWCH)0x0;
  pCVar9 = (LPCH)0x0;
  if (DAT_100236c4 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr != (LPWCH)0x0) {
      DAT_100236c4 = 1;
LAB_1000d2b7:
      if ((lpWideCharStr == (LPWCH)0x0) &&
         (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr == (LPWCH)0x0)) {
        return (LPSTR)0x0;
      }
      WVar2 = *lpWideCharStr;
      pWVar4 = lpWideCharStr;
      while (WVar2 != L'\0') {
        do {
          pWVar3 = pWVar4;
          pWVar4 = pWVar3 + 1;
        } while (*pWVar4 != L'\0');
        pWVar4 = pWVar3 + 2;
        WVar2 = *pWVar4;
      }
      iVar5 = ((intptr_t)pWVar4 - (intptr_t)lpWideCharStr >> 1) + 1;
      _Size = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      local_8 = (LPSTR)0x0;
      if (((_Size != 0) && (pCVar6 = _malloc(_Size), pCVar6 != (LPSTR)0x0)) &&
         (iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,pCVar6,_Size,(LPCSTR)0x0,(LPBOOL)0x0),
         local_8 = pCVar6, iVar5 == 0)) {
        free(pCVar6);
        local_8 = (LPSTR)0x0;
      }
      FreeEnvironmentStringsW(lpWideCharStr);
      return local_8;
    }
    pCVar9 = GetEnvironmentStrings();
    if (pCVar9 == (LPCH)0x0) {
      return (LPSTR)0x0;
    }
    DAT_100236c4 = 2;
  }
  else {
    if (DAT_100236c4 == 1) goto LAB_1000d2b7;
    if (DAT_100236c4 != 2) {
      return (LPSTR)0x0;
    }
  }
  if ((pCVar9 == (LPCH)0x0) && (pCVar9 = GetEnvironmentStrings(), pCVar9 == (LPCH)0x0)) {
    return (LPSTR)0x0;
  }
  cVar1 = *pCVar9;
  pcVar7 = pCVar9;
  while (cVar1 != '\0') {
    do {
      pcVar8 = pcVar7;
      pcVar7 = pcVar8 + 1;
    } while (*pcVar7 != '\0');
    pcVar7 = pcVar8 + 2;
    cVar1 = *pcVar7;
  }
  pCVar6 = _malloc((size_t)(pcVar7 + (1 - (intptr_t)pCVar9)));
  if (pCVar6 == (LPSTR)0x0) {
    pCVar6 = (LPSTR)0x0;
  }
  else {
    memmove((unsigned int *)pCVar6,(unsigned int *)pCVar9,(uintptr_t)(pcVar7 + (1 - (intptr_t)pCVar9)));
  }
  FreeEnvironmentStringsA(pCVar9);
  return pCVar6;
}
#endif /* _getenv_init */




BOOL __cdecl _heap_create(int param_1)

{
  BOOL BVar1;
  
  hHeap = HeapCreate((DWORD)(param_1 == 0),0x1000,0);
  if (hHeap != nullptr) {
    BVar1 = _heap_init();
    if (BVar1 != NULL) {
      return TRUE;
    }
    HeapDestroy((void*)hHeap);
  }
  return FALSE;
}



void _heap_teardown(void)

{
  int iVar1;
  unsigned int *puVar2;
  
  iVar1 = 0;
  if (0 < DAT_10023b44) {
    puVar2 = (unsigned int *)((intptr_t)lpMem_10023b48 + 0xc);
    do {
      VirtualFree((LPVOID)*puVar2,0x100000,0x4000);
      VirtualFree((LPVOID)*puVar2,0,0x8000);
      HeapFree((void*)hHeap,0,(LPVOID)puVar2[1]);
      puVar2 = puVar2 + 5;
      iVar1 = iVar1 + 1;
    } while (iVar1 < DAT_10023b44);
  }
  HeapFree(hHeap,0,lpMem_10023b48);
  HeapDestroy((void*)hHeap);
  return;
}



#if 0
void _invalid_parameter_noinfo(void)

{
  if ((DAT_10023554 == 1) || ((DAT_10023554 == 0 && (DAT_10023558 == 1)))) {
    _RtMsgAndAbort(0xfc);
    if (DAT_100236c8 != (void *)0x0) {
      (*DAT_100236c8)();
    }
    _RtMsgAndAbort(0xff);
  }
  return;
}
#endif /* _invalid_parameter_noinfo */




#if 0
void __cdecl _RtMsgAndAbort(DWORD param_1)

{
  unsigned int *puVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  size_t sVar4;
  HANDLE hFile;
  int iVar5;
  uint *_Dest;
  unsigned char auStackY_1e3 [7];
  LPCVOID lpBuffer;
  LPOVERLAPPED lpOverlapped;
  uint local_1a8 [65];
  uint local_a4 [40];
  
  iVar5 = 0;
  pDVar2 = &DAT_10021468;
  do {
    if (param_1 == *pDVar2) break;
    pDVar2 = pDVar2 + 2;
    iVar5 = iVar5 + 1;
  } while ((intptr_t)pDVar2 < 0x100214f8);
  if (param_1 == (&DAT_10021468)[iVar5 * 2]) {
    if ((DAT_10023554 == 1) || ((DAT_10023554 == 0 && (DAT_10023558 == 1)))) {
      pDVar2 = &param_1;
      puVar1 = (unsigned int *)(iVar5 * 8 + 0x1002146c);
      lpOverlapped = (LPOVERLAPPED)0x0;
      sVar4 = _strlen((char *)*puVar1);
      lpBuffer = (LPCVOID)*puVar1;
      hFile = GetStdHandle(0xfffffff4);
      WriteFile(hFile,lpBuffer,sVar4,pDVar2,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)local_1a8,0x104);
      if (DVar3 == 0) {
        strcpy(local_1a8,(char*)"<program name unknown>");
      }
      _Dest = local_1a8;
      sVar4 = _strlen((char *)local_1a8);
      if (0x3c < sVar4 + 1) {
        sVar4 = _strlen((char *)local_1a8);
        _Dest = (uint *)(auStackY_1e3 + sVar4);
        _strncpy((char *)_Dest,"...",3);
      }
      strcpy(local_a4,(char*)"Runtime Error!\n\nProgram: ");
      strcat(local_a4,_Dest);
      strcat(local_a4,(char*)&DAT_1001c44c);
      strcat(local_a4,*(uint **)(iVar5 * 8 + 0x1002146c));
      auStackY_1e3._3_4_ = 0x1000d5a0;
      __crtMessageBoxA(local_a4,"Microsoft Visual C++ Runtime Library",0x12010);
    }
  }
  return;
}
#endif /* _RtMsgAndAbort */




#if 0
DWORD __cdecl _lseek(uint param_1,LONG param_2,DWORD param_3)

{
  DWORD DVar1;
  DWORD *pDVar2;
  
  if ((param_1 < uNumber_10024ffc) &&
     ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    _lock_fh(param_1);
    DVar1 = _lseek_nolock(param_1,param_2,param_3);
    _unlock_fh(param_1);
    return DVar1;
  }
  pDVar2 = _errno();
  *pDVar2 = 9;
  pDVar2 = _doserrno_impl();
  *pDVar2 = 0;
  return 0xffffffff;
}
#endif /* _lseek */




DWORD __cdecl _lseek_nolock(uint param_1,LONG param_2,DWORD param_3)

{
  byte *pbVar1;
  HANDLE hFile;
  DWORD *pDVar2;
  DWORD DVar3;
  uint uVar4;
  
  hFile = (HANDLE)_get_osfhandle(param_1);
  if (hFile == (HANDLE)0xffffffff) {
    pDVar2 = _errno();
    *pDVar2 = 9;
  }
  else {
    DVar3 = SetFilePointer(hFile,param_2,(PLONG)0x0,param_3);
    if (DVar3 == 0xffffffff) {
      uVar4 = GetLastError();
    }
    else {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      pbVar1 = (byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24);
      *pbVar1 = *pbVar1 & 0xfd;
      return DVar3;
    }
    _dosmaperr(uVar4);
  }
  return 0xffffffff;
}



#if 0
int __cdecl _write(uint param_1,char *param_2,uint param_3)

{
  int iVar1;
  DWORD *pDVar2;
  
  if ((param_1 < uNumber_10024ffc) &&
     ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    _lock_fh(param_1);
    iVar1 = _write_nolock(param_1,param_2,param_3);
    _unlock_fh(param_1);
    return iVar1;
  }
  pDVar2 = _errno();
  *pDVar2 = 9;
  pDVar2 = _doserrno_impl();
  *pDVar2 = 0;
  return -1;
}
#endif /* _write */




#if 0
int __cdecl _write_nolock(DWORD param_1,char *param_2,uint param_3)

{
  int *piVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  BOOL BVar6;
  DWORD *pDVar7;
  char local_418 [1028];
  int local_14;
  DWORD local_10;
  DWORD local_c;
  char *local_8;
  
  local_c = 0;
  local_14 = 0;
  if (param_3 == 0) {
LAB_1000d756:
    iVar4 = 0;
  }
  else {
    piVar1 = &DAT_10024ec0 + ((intptr_t)param_1 >> 5);
    iVar4 = (param_1 & 0x1f) * 0x24;
    if ((*(byte *)(*piVar1 + 4 + iVar4) & 0x20) != 0) {
      _lseek_nolock(param_1,0,2);
    }
    if ((*(byte *)((unsigned int *)(*piVar1 + iVar4) + 1) & 0x80) == 0) {
      BVar6 = WriteFile(*(HANDLE *)(*piVar1 + iVar4),param_2,param_3,&local_10,(LPOVERLAPPED)0x0);
      if (BVar6 == 0) {
        param_1 = GetLastError();
      }
      else {
        local_c = local_10;
        param_1 = 0;
      }
LAB_1000d825:
      if (local_c != 0) {
        return local_c - local_14;
      }
      if (param_1 == 0) goto LAB_1000d897;
      if (param_1 == 5) {
        pDVar7 = _errno();
        *pDVar7 = 9;
        pDVar7 = _doserrno_impl();
        *pDVar7 = 5;
      }
      else {
        _dosmaperr(param_1);
      }
    }
    else {
      local_8 = param_2;
      param_1 = 0;
      if (param_3 != 0) {
        do {
          pcVar5 = local_418;
          do {
            if (param_3 <= (uintptr_t)((intptr_t)local_8 - (intptr_t)param_2)) break;
            pcVar2 = local_8 + 1;
            cVar3 = *local_8;
            local_8 = pcVar2;
            if (cVar3 == '\n') {
              local_14 = local_14 + 1;
              *pcVar5 = '\r';
              pcVar5 = pcVar5 + 1;
            }
            *pcVar5 = cVar3;
            pcVar5 = pcVar5 + 1;
          } while ((intptr_t)pcVar5 - (intptr_t)local_418 < 0x400);
          BVar6 = WriteFile(*(HANDLE *)(*piVar1 + iVar4),local_418,(intptr_t)pcVar5 - (intptr_t)local_418,
                            &local_10,(LPOVERLAPPED)0x0);
          if (BVar6 == 0) {
            param_1 = GetLastError();
            goto LAB_1000d825;
          }
          local_c = local_c + local_10;
          if (((intptr_t)local_10 < (intptr_t)pcVar5 - (intptr_t)local_418) ||
             (param_3 <= (uintptr_t)((intptr_t)local_8 - (intptr_t)param_2))) goto LAB_1000d825;
        } while( true );
      }
LAB_1000d897:
      if (((*(byte *)(*piVar1 + 4 + iVar4) & 0x40) != 0) && (*param_2 == '\x1a')) goto LAB_1000d756;
      pDVar7 = _errno();
      *pDVar7 = 0x1c;
      pDVar7 = _doserrno_impl();
      *pDVar7 = 0;
    }
    iVar4 = -1;
  }
  return iVar4;
}
#endif /* _write_nolock */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl _flush_stdout_init(unsigned int *param_1)

{
  void *pvVar1;
  
  _DAT_100236cc = _DAT_100236cc + 1;
  pvVar1 = _malloc(0x1000);
  param_1[2] = (uintptr_t)pvVar1;
  if (pvVar1 == (void *)0x0) {
    param_1[3] = param_1[3] | 4;
    param_1[2] = (uintptr_t)param_1 + 5;
    param_1[6] = 2;
  }
  else {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return;
}



#if 0
byte __cdecl _isatty_std(uint param_1)

{
  if (uNumber_10024ffc <= param_1) {
    return 0;
  }
  return *(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 0x40;
}
#endif /* _isatty_std */




void __cdecl __lock(uint param_1)

{
  if ((0x100214f7 < param_1) && (param_1 < 0x10021759)) {
    _lock_critical_section(((intptr_t)(param_1 + 0xeffdeb08) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}



void __cdecl _lock_file(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _lock_critical_section(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}



void __cdecl __unlock(uint param_1)

{
  if ((0x100214f7 < param_1) && (param_1 < 0x10021759)) {
    _unlock_critical_section(((intptr_t)(param_1 + 0xeffdeb08) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}



void __cdecl _unlock_file(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _unlock_critical_section(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}



// Library Function - Single Match
//  _strlen
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

#if 0
size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uintptr_t)puVar2 & 3) == 0) goto LAB_1000dac0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((intptr_t)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_1000daf3:
  return (size_t)((intptr_t)puVar2 + (-1 - (intptr_t)_Str));
LAB_1000dac0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (intptr_t)puVar3 - (intptr_t)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((intptr_t)puVar3 + (1 - (intptr_t)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((intptr_t)puVar3 + (2 - (intptr_t)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_1000daf3;
}
#endif /* _strlen */

#if 0 /* CRT: _wcstombs_l */



int __cdecl _wcstombs_l(LPSTR param_1, WCHAR param_2, NULL, 0)

{
  int iVar1;
  int bVar2;
  
  InterlockedIncrement(&DAT_10023894);
  bVar2 = DAT_10023884 != 0;
  if (bVar2) {
    InterlockedDecrement(&DAT_10023894);
    _lock_critical_section(0x13);
  }
  iVar1 = __ascii_wcstombs(param_1,param_2);
  if (bVar2) {
    _unlock_critical_section(0x13);
  }
  else {
    InterlockedDecrement(&DAT_10023894);
  }
  return iVar1;
}
#endif




int __cdecl __ascii_wcstombs(LPSTR param_1,WCHAR param_2)

{
  LPSTR lpMultiByteStr;
  int iVar1;
  DWORD *pDVar2;
  
  lpMultiByteStr = param_1;
  if (param_1 == (LPSTR)0x0) {
    return 0;
  }
  if (DAT_100237bc == 0) {
    if ((ushort)param_2 < 0x100) {
      *param_1 = (CHAR)param_2;
      return 1;
    }
  }
  else {
    param_1 = (LPSTR)0x0;
    iVar1 = WideCharToMultiByte(CodePage_100237cc,0x220,&param_2,1,lpMultiByteStr,
                                cbMultiByte_10021b40,(LPCSTR)0x0,(LPBOOL)&param_1);
    if ((iVar1 != 0) && (param_1 == (LPSTR)0x0)) {
      return iVar1;
    }
  }
  pDVar2 = _errno();
  *pDVar2 = 0x2a;
  return -1;
}



// Library Function - Single Match
//  __aulldiv
// 
// Library: Visual Studio

unsigned long long __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar3 = param_1;
  uVar8 = param_4;
  uVar6 = param_2;
  uVar9 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (intptr_t)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar8 >> 1;
      uVar9 = uVar9 >> 1 | (uintptr_t)((uVar8 & 1) != 0) << 0x1f;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uintptr_t)((uVar6 & 1) != 0) << 0x1f;
      uVar8 = uVar5;
      uVar6 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar7,uVar3) / (ulonglong)uVar9;
    iVar4 = (intptr_t)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uintptr_t)((ulonglong)lVar2 >> 0x20);
    uVar8 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar8)) ||
       ((param_2 <= uVar8 && (param_1 < (uintptr_t)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}



// Library Function - Single Match
//  __aullrem
// 
// Library: Visual Studio

unsigned long long __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int bVar11;
  
  uVar3 = param_1;
  uVar4 = param_4;
  uVar9 = param_2;
  uVar10 = param_3;
  if (param_4 == 0) {
    iVar6 = (intptr_t)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar4 >> 1;
      uVar10 = uVar10 >> 1 | (uintptr_t)((uVar4 & 1) != 0) << 0x1f;
      uVar8 = uVar9 >> 1;
      uVar3 = uVar3 >> 1 | (uintptr_t)((uVar9 & 1) != 0) << 0x1f;
      uVar4 = uVar5;
      uVar9 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar3) / (ulonglong)uVar10;
    uVar3 = (intptr_t)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uintptr_t)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uintptr_t)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uintptr_t)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uintptr_t)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uintptr_t)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}



#if 0
int * __cdecl malloc(int param_1)

{
  int *piVar1;
  int iVar2;
  uint *_Size;
  uint *puVar3;
  
  _Size = (uint *)(param_1 * param_2);
  puVar3 = _Size;
  if (_Size < (uint *)0xffffffe1) {
    if (_Size == (uint *)0x0) {
      puVar3 = (uint *)0x1;
    }
    puVar3 = (uint *)((intptr_t)puVar3 + 0xfU & 0xfffffff0);
  }
  do {
    if (puVar3 < (uint *)0xffffffe1) {
      if (_Size < DAT_10021b34 || (intptr_t)_Size - (intptr_t)DAT_10021b34 == 0) {
        _lock_critical_section(9);
        piVar1 = _heap_alloc(_Size);
        _unlock_critical_section(9);
        if (piVar1 != (int *)0x0) {
          _memset(piVar1,0,(size_t)_Size);
          return piVar1;
        }
      }
      piVar1 = HeapAlloc(hHeap,8,(SIZE_T)puVar3);
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
    }
    if (DAT_10023790 == 0) {
      return (int *)0x0;
    }
    iVar2 = _heap_link(puVar3);
  } while (iVar2 != 0);
  return (int *)0x0;
}
#endif /* malloc */




#if 0
LONG __cdecl _XcptFilter(int param_1,_EXCEPTION_POINTERS *param_2)

{
  void *pcVar1;
  DWORD DVar2;
  DWORD DVar3;
  DWORD *pDVar4;
  int *piVar5;
  LONG LVar6;
  int iVar7;
  int iVar8;
  
  pDVar4 = _getptd();
  piVar5 = __validfunc(param_1,(int *)pDVar4[0x14]);
  if ((piVar5 == (int *)0x0) || (pcVar1 = (void *)piVar5[2], pcVar1 == (void *)0x0)) {
    LVar6 = UnhandledExceptionFilter(param_2);
  }
  else if (pcVar1 == (void *)0x5) {
    piVar5[2] = 0;
    LVar6 = 1;
  }
  else {
    if (pcVar1 != (void *)0x1) {
      DVar2 = pDVar4[0x15];
      pDVar4[0x15] = (uintptr_t)param_2;
      if (piVar5[1] == 8) {
        if (DAT_10021a08 < DAT_10021a0c + DAT_10021a08) {
          iVar7 = DAT_10021a08 * 0xc;
          iVar8 = DAT_10021a08;
          do {
            *(unsigned int *)(iVar7 + 8 + pDVar4[0x14]) = 0;
            iVar8 = iVar8 + 1;
            iVar7 = iVar7 + 0xc;
          } while (iVar8 < DAT_10021a0c + DAT_10021a08);
        }
        iVar7 = *piVar5;
        DVar3 = pDVar4[0x16];
        if (iVar7 == -0x3fffff72) {
          pDVar4[0x16] = 0x83;
        }
        else if (iVar7 == -0x3fffff70) {
          pDVar4[0x16] = 0x81;
        }
        else if (iVar7 == -0x3fffff6f) {
          pDVar4[0x16] = 0x84;
        }
        else if (iVar7 == -0x3fffff6d) {
          pDVar4[0x16] = 0x85;
        }
        else if (iVar7 == -0x3fffff73) {
          pDVar4[0x16] = 0x82;
        }
        else if (iVar7 == -0x3fffff71) {
          pDVar4[0x16] = 0x86;
        }
        else if (iVar7 == -0x3fffff6e) {
          pDVar4[0x16] = 0x8a;
        }
        (*pcVar1)(8,pDVar4[0x16]);
        pDVar4[0x16] = DVar3;
      }
      else {
        piVar5[2] = 0;
        (*pcVar1)(piVar5[1]);
      }
      pDVar4[0x15] = DVar2;
    }
    LVar6 = -1;
  }
  return LVar6;
}
#endif /* _XcptFilter */




int * __cdecl __validfunc(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = param_2;
  if (*param_2 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (param_2 + DAT_10021a14 * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_10021a14 * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}



void _init_time(void)

{
  if (DAT_10023788 == 0) {
    _lock_critical_section(0xb);
    if (DAT_10023788 == 0) {
      __tzset();
      DAT_10023788 = DAT_10023788 + 1;
    }
    _unlock_critical_section(0xb);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
void __tzset(void)

{
  char cVar1;
  char cVar2;
  uint *_Str1;
  DWORD DVar3;
  int iVar4;
  size_t sVar5;
  void *_this;
  uint *_Source;
  int local_8;
  
  _lock_critical_section(0xc);
  DAT_10021ac0 = 0xffffffff;
  DAT_10021ab0 = 0xffffffff;
  DAT_100236d0 = 0;
  _Str1 = (uint *)getenv("TZ");
  if (_Str1 == (uint *)0x0) {
    _unlock_critical_section(0xc);
    DVar3 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_100236d8);
    if (DVar3 == 0xffffffff) {
      return;
    }
    DAT_10021a18 = (void *)(DAT_100236d8 * 0x3c);
    DAT_100236d0 = 1;
    if (DAT_1002371e != 0) {
      DAT_10021a18 = (void *)((intptr_t)DAT_10021a18 + DAT_1002372c * 0x3c);
    }
    if ((DAT_10023772 == 0) || (DAT_10023780 == 0)) {
      DAT_10021a1c = 0;
      _DAT_10021a20 = 0;
    }
    else {
      DAT_10021a1c = 1;
      _DAT_10021a20 = (DAT_10023780 - DAT_1002372c) * 0x3c;
    }
    iVar4 = WideCharToMultiByte(CodePage_100237cc,0x220,(LPCWSTR)&lpWideCharStr_100236dc,-1,
                                lpMultiByteStr_10021aa4,0x3f,(LPCSTR)0x0,&local_8);
    if ((iVar4 == 0) || (local_8 != 0)) {
      *lpMultiByteStr_10021aa4 = 0;
    }
    else {
      lpMultiByteStr_10021aa4[0x3f] = 0;
    }
    iVar4 = WideCharToMultiByte(CodePage_100237cc,0x220,(LPCWSTR)&lpWideCharStr_10023730,-1,
                                lpMultiByteStr_10021aa8,0x3f,(LPCSTR)0x0,&local_8);
    if ((iVar4 != 0) && (local_8 == 0)) {
      lpMultiByteStr_10021aa8[0x3f] = 0;
      return;
    }
LAB_1000e17f:
    *lpMultiByteStr_10021aa8 = 0;
  }
  else {
    if (((char)*_Str1 != '\0') &&
       ((DAT_10023784 == (uint *)0x0 ||
        (iVar4 = _strcmp((char *)_Str1,(char *)DAT_10023784), iVar4 != 0)))) {
      free(DAT_10023784);
      sVar5 = _strlen((char *)_Str1);
      DAT_10023784 = _malloc(sVar5 + 1);
      if (DAT_10023784 != (uint *)0x0) {
        strcpy(DAT_10023784,_Str1);
        _unlock_critical_section(0xc);
        _strncpy(lpMultiByteStr_10021aa4,(char *)_Str1,3);
        _Source = (uint *)((intptr_t)_Str1 + 3);
        lpMultiByteStr_10021aa4[3] = 0;
        cVar1 = *(char *)_Source;
        if (cVar1 == '-') {
          _Source = _Str1 + 1;
        }
        iVar4 = atoi(_this)_Source);
        DAT_10021a18 = (void *)(iVar4 * 0xe10);
        for (; (cVar2 = (char)*_Source, cVar2 == '+' || (('/' < cVar2 && (cVar2 < ':'))));
            _Source = (uint *)((intptr_t)_Source + 1)) {
        }
        if ((char)*_Source == ':') {
          _Source = (uint *)((intptr_t)_Source + 1);
          iVar4 = atoi(DAT_10021a18)_Source);
          DAT_10021a18 = (void *)((intptr_t)DAT_10021a18 + iVar4 * 0x3c);
          for (; ('/' < (char)*_Source && ((char)*_Source < ':'));
              _Source = (uint *)((intptr_t)_Source + 1)) {
          }
          if ((char)*_Source == ':') {
            _Source = (uint *)((intptr_t)_Source + 1);
            iVar4 = atoi(DAT_10021a18)_Source);
            DAT_10021a18 = (void *)((intptr_t)DAT_10021a18 + iVar4);
            for (; ('/' < (char)*_Source && ((char)*_Source < ':'));
                _Source = (uint *)((intptr_t)_Source + 1)) {
            }
          }
        }
        if (cVar1 == '-') {
          DAT_10021a18 = (void *)-(intptr_t)DAT_10021a18;
        }
        DAT_10021a1c = (intptr_t)(char)*_Source;
        if (DAT_10021a1c != 0) {
          _strncpy(lpMultiByteStr_10021aa8,(char *)_Source,3);
          lpMultiByteStr_10021aa8[3] = 0;
          return;
        }
        goto LAB_1000e17f;
      }
    }
    _unlock_critical_section(0xc);
  }
  return;
}
#endif /* __tzset */




int __cdecl _isDST(int *param_1)

{
  int bVar1;
  
  _lock_critical_section(0xb);
  bVar1 = _isDST2(param_1);
  _unlock_critical_section(0xb);
  return bVar1;
}



int __cdecl _isDST2(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (DAT_10021a1c != 0) {
    uVar5 = param_1[5];
    if ((uVar5 != DAT_10021ab0) || (uVar5 != DAT_10021ac0)) {
      if (DAT_100236d0 == 0) {
        _dstShiftCalc(1,1,uVar5,4,1,0,0,2,0,0,0);
        _dstShiftCalc(0,1,param_1[5],10,5,0,0,2,0,0,0);
      }
      else {
        if (DAT_10023770 != 0) {
          uVar6 = (uintptr_t)DAT_10023776;
          uVar3 = 0;
          uVar4 = 0;
        }
        else {
          uVar3 = (uintptr_t)DAT_10023774;
          uVar6 = 0;
          uVar4 = (uintptr_t)DAT_10023776;
        }
        _dstShiftCalc(1,(uintptr_t)(DAT_10023770 == 0),uVar5,(uintptr_t)DAT_10023772,uVar4,uVar3,uVar6,
                      (uintptr_t)DAT_10023778,(uintptr_t)DAT_1002377a,(uintptr_t)DAT_1002377c,(uintptr_t)DAT_1002377e);
        if (DAT_1002371c != 0) {
          uVar6 = (uintptr_t)DAT_10023722;
          uVar3 = 0;
          uVar4 = 0;
          uVar5 = param_1[5];
        }
        else {
          uVar3 = (uintptr_t)DAT_10023720;
          uVar6 = 0;
          uVar4 = (uintptr_t)DAT_10023722;
          uVar5 = param_1[5];
        }
        _dstShiftCalc(0,(uintptr_t)(DAT_1002371c == 0),uVar5,(uintptr_t)DAT_1002371e,uVar4,uVar3,uVar6,
                      (uintptr_t)DAT_10023724,(uintptr_t)DAT_10023726,(uintptr_t)DAT_10023728,(uintptr_t)DAT_1002372a);
      }
    }
    iVar1 = param_1[7];
    if (DAT_10021ab4 < DAT_10021ac4) {
      if ((DAT_10021ab4 <= iVar1) && (iVar1 <= DAT_10021ac4)) {
        if ((DAT_10021ab4 < iVar1) && (iVar1 < DAT_10021ac4)) {
          return true;
        }
LAB_1000e32e:
        iVar2 = ((param_1[2] * 0x3c + param_1[1]) * 0x3c + *param_1) * 1000;
        if (iVar1 == DAT_10021ab4) {
          return DAT_10021ab8 <= iVar2;
        }
        return iVar2 < DAT_10021ac8;
      }
    }
    else {
      if (iVar1 < DAT_10021ac4) {
        return true;
      }
      if (DAT_10021ab4 < iVar1) {
        return true;
      }
      if ((iVar1 <= DAT_10021ac4) || (DAT_10021ab4 <= iVar1)) goto LAB_1000e32e;
    }
  }
  return false;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl
_dstShiftCalc(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
             int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      iVar1 = (&DAT_10021ac8)[param_4];
    }
    else {
      iVar1 = *(int *)(&DAT_10021afc + param_4 * 4);
    }
    iVar2 = (intptr_t)(param_3 * 0x16d + -0x63db + iVar1 + 1 + ((intptr_t)(param_3 - 1) >> 2)) % 7;
    if (param_6 < iVar2) {
      iVar1 = iVar1 + 1 + (param_5 * 7 - iVar2) + param_6;
    }
    else {
      iVar1 = iVar1 + -6 + (param_5 * 7 - iVar2) + param_6;
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        iVar2 = *(int *)(&DAT_10021acc + param_4 * 4);
      }
      else {
        iVar2 = *(int *)(&DAT_10021b00 + param_4 * 4);
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      iVar1 = (&DAT_10021ac8)[param_4];
    }
    else {
      iVar1 = *(int *)(&DAT_10021afc + param_4 * 4);
    }
    iVar1 = iVar1 + param_7;
  }
  if (param_1 == 1) {
    DAT_10021ab0 = param_3;
    DAT_10021ab8 = ((param_8 * 0x3c + param_9) * 0x3c + param_10) * 1000 + param_11;
    DAT_10021ab4 = iVar1;
  }
  else {
    DAT_10021ac8 = ((param_8 * 0x3c + param_9) * 0x3c + _DAT_10021a20 + param_10) * 1000 + param_11;
    if (DAT_10021ac8 < 0) {
      DAT_10021ac8 = DAT_10021ac8 + 86400000;
      DAT_10021ac4 = iVar1 + -1;
    }
    else {
      DAT_10021ac4 = iVar1;
      if (86399999 < DAT_10021ac8) {
        DAT_10021ac8 = DAT_10021ac8 + -86400000;
        DAT_10021ac4 = iVar1 + 1;
      }
    }
    DAT_10021ac0 = param_3;
  }
  return;
}



#if 0
unsigned int __cdecl _heap_link(unsigned int param_1)

{
  int iVar1;
  
  if (DAT_1002378c != (void *)0x0) {
    iVar1 = (*DAT_1002378c)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}
#endif /* _heap_link */




BOOL _heap_init(void)

{
  lpMem_10023b48 = HeapAlloc(hHeap,0,0x140);
  if (lpMem_10023b48 == 0) {
    return 0;
  }
  DAT_10023b40 = 0;
  DAT_10023b44 = 0;
  DAT_10023b3c = lpMem_10023b48;
  DAT_10023b28 = 0x10;
  return 1;
}



#if 0
uint __cdecl _heap_lookup_size(int param_1)

{
  LPVOID pvVar1;
  
  pvVar1 = lpMem_10023b48;
  while( true ) {
    if ((LPVOID)((intptr_t)lpMem_10023b48 + DAT_10023b44 * 0x14) <= pvVar1) {
      return 0;
    }
    if ((uintptr_t)(param_1 - *(int *)((intptr_t)pvVar1 + 0xc)) < 0x100000) break;
    pvVar1 = (LPVOID)((intptr_t)pvVar1 + 0x14);
  }
  return (uintptr_t)pvVar1;
}
#endif /* _heap_lookup_size */




#if 0
void __cdecl _heap_free(uint *param_1,uint param_2)

{
  char *pcVar1;
  uint *puVar2;
  int *piVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int local_10;
  
  uVar5 = param_1[4];
  iVar6 = *(int *)(param_2 - 4);
  piVar9 = (int *)(param_2 - 4);
  uVar10 = param_2 - param_1[3] >> 0xf;
  uVar7 = *(uint *)(param_2 - 8);
  local_10 = iVar6 + -1;
  piVar3 = (int *)(uVar10 * 0x204 + 0x144 + uVar5);
  uVar12 = *(uint *)(local_10 + (intptr_t)piVar9);
  if ((uVar12 & 1) == 0) {
    param_2 = ((intptr_t)uVar12 >> 4) - 1;
    if (0x3f < param_2) {
      param_2 = 0x3f;
    }
    if (*(int *)(iVar6 + 3 + (intptr_t)piVar9) == *(int *)(iVar6 + 7 + (intptr_t)piVar9)) {
      if (param_2 < 0x20) {
        pcVar1 = (char *)(param_2 + 4 + uVar5);
        uVar11 = ~(0x80000000U >> ((byte)param_2 & 0x1f));
        puVar2 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
        *puVar2 = *puVar2 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *param_1 = *param_1 & uVar11;
        }
      }
      else {
        pcVar1 = (char *)(param_2 + 4 + uVar5);
        uVar11 = ~(0x80000000U >> ((byte)param_2 - 0x20 & 0x1f));
        puVar2 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
        *puVar2 = *puVar2 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          param_1[1] = param_1[1] & uVar11;
        }
      }
    }
    *(unsigned int *)(*(int *)(iVar6 + 7 + (intptr_t)piVar9) + 4) =
         *(unsigned int *)(iVar6 + 3 + (intptr_t)piVar9);
    local_10 = local_10 + uVar12;
    *(unsigned int *)(*(int *)(iVar6 + 3 + (intptr_t)piVar9) + 8) =
         *(unsigned int *)(iVar6 + 7 + (intptr_t)piVar9);
  }
  uVar12 = (local_10 >> 4) - 1;
  if (0x3f < uVar12) {
    uVar12 = 0x3f;
  }
  if ((uVar7 & 1) == 0) {
    piVar9 = (int *)((intptr_t)piVar9 - uVar7);
    param_2 = ((intptr_t)uVar7 >> 4) - 1;
    if (0x3f < param_2) {
      param_2 = 0x3f;
    }
    local_10 = local_10 + uVar7;
    uVar12 = (local_10 >> 4) - 1;
    if (0x3f < uVar12) {
      uVar12 = 0x3f;
    }
    if (param_2 != uVar12) {
      if (piVar9[1] == piVar9[2]) {
        if (param_2 < 0x20) {
          pcVar1 = (char *)(param_2 + 4 + uVar5);
          uVar11 = ~(0x80000000U >> ((byte)param_2 & 0x1f));
          puVar2 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
          *puVar2 = *puVar2 & uVar11;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *param_1 = *param_1 & uVar11;
          }
        }
        else {
          pcVar1 = (char *)(param_2 + 4 + uVar5);
          uVar11 = ~(0x80000000U >> ((byte)param_2 - 0x20 & 0x1f));
          puVar2 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
          *puVar2 = *puVar2 & uVar11;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            param_1[1] = param_1[1] & uVar11;
          }
        }
      }
      *(int *)(piVar9[2] + 4) = piVar9[1];
      *(int *)(piVar9[1] + 8) = piVar9[2];
    }
  }
  if (((uVar7 & 1) != 0) || (param_2 != uVar12)) {
    piVar9[1] = piVar3[uVar12 * 2 + 1];
    piVar9[2] = (intptr_t)(piVar3 + uVar12 * 2);
    (piVar3 + uVar12 * 2)[1] = (intptr_t)piVar9;
    *(int **)(piVar9[1] + 8) = piVar9;
    if (piVar9[1] == piVar9[2]) {
      cVar4 = *(char *)(uVar12 + 4 + uVar5);
      *(char *)(uVar12 + 4 + uVar5) = cVar4 + '\x01';
      bVar8 = (byte)uVar12;
      if (uVar12 < 0x20) {
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar8 & 0x1f);
        }
        puVar2 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
        *puVar2 = *puVar2 | 0x80000000U >> (bVar8 & 0x1f);
      }
      else {
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
        }
        puVar2 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
        *puVar2 = *puVar2 | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
      }
    }
  }
  *piVar9 = local_10;
  *(int *)(local_10 + -4 + (intptr_t)piVar9) = local_10;
  *piVar3 = *piVar3 + -1;
  uVar5 = DAT_10023b38;
  puVar2 = DAT_10023b40;
  if ((*piVar3 == 0) && (uVar5 = uVar10, puVar2 = param_1, DAT_10023b40 != (uint *)0x0)) {
    VirtualFree((LPVOID)(DAT_10023b38 * 0x8000 + DAT_10023b40[3]),0x8000,0x4000);
    DAT_10023b40[2] = DAT_10023b40[2] | 0x80000000U >> ((byte)DAT_10023b38 & 0x1f);
    *(unsigned int *)(DAT_10023b40[4] + 0xc4 + DAT_10023b38 * 4) = 0;
    *(char *)(DAT_10023b40[4] + 0x43) = *(char *)(DAT_10023b40[4] + 0x43) + -1;
    if (*(char *)(DAT_10023b40[4] + 0x43) == '\0') {
      DAT_10023b40[1] = DAT_10023b40[1] & 0xfffffffe;
    }
    puVar2 = param_1;
    if (DAT_10023b40[2] == 0xffffffff) {
      VirtualFree((LPVOID)DAT_10023b40[3],0,0x8000);
      HeapFree(hHeap,0,(LPVOID)DAT_10023b40[4]);
      memmove2(DAT_10023b40,DAT_10023b40 + 5,
               (DAT_10023b44 * 0x14 - (intptr_t)DAT_10023b40) + -0x14 + (intptr_t)lpMem_10023b48);
      DAT_10023b44 = DAT_10023b44 + -1;
      if (DAT_10023b40 < param_1) {
        param_1 = param_1 + -5;
      }
      DAT_10023b3c = lpMem_10023b48;
      puVar2 = param_1;
    }
  }
  DAT_10023b40 = puVar2;
  DAT_10023b38 = uVar5;
  return;
}
#endif /* _heap_free */




#if 0
int * __cdecl _heap_alloc(uint *param_1)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  int *piVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  uint *puVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  uint local_10;
  uint local_c;
  int local_8;
  
  puVar8 = (uint *)((intptr_t)lpMem_10023b48 + DAT_10023b44 * 0x14);
  uVar6 = (intptr_t)param_1 + 0x17U & 0xfffffff0;
  iVar7 = ((intptr_t)((intptr_t)param_1 + 0x17U) >> 4) + -1;
  bVar5 = (byte)iVar7;
  param_1 = DAT_10023b3c;
  if (iVar7 < 0x20) {
    local_10 = 0xffffffff >> (bVar5 & 0x1f);
    local_c = 0xffffffff;
  }
  else {
    local_c = 0xffffffff >> (bVar5 - 0x20 & 0x1f);
    local_10 = 0;
  }
  for (; (param_1 < puVar8 && ((param_1[1] & local_c) == 0 && (*param_1 & local_10) == 0));
      param_1 = param_1 + 5) {
  }
  puVar11 = lpMem_10023b48;
  if (param_1 == puVar8) {
    for (; (puVar11 < DAT_10023b3c && ((puVar11[1] & local_c) == 0 && (*puVar11 & local_10) == 0));
        puVar11 = puVar11 + 5) {
    }
    param_1 = puVar11;
    if (puVar11 == DAT_10023b3c) {
      for (; (puVar11 < puVar8 && (puVar11[2] == 0)); puVar11 = puVar11 + 5) {
      }
      puVar12 = lpMem_10023b48;
      param_1 = puVar11;
      if (puVar11 == puVar8) {
        for (; (puVar12 < DAT_10023b3c && (puVar12[2] == 0)); puVar12 = puVar12 + 5) {
        }
        param_1 = puVar12;
        if ((puVar12 == DAT_10023b3c) && (param_1 = _heap_page_scan(), param_1 == (uint *)0x0)) {
          return (int *)0x0;
        }
      }
      iVar7 = _heap_page_init((intptr_t)param_1);
      *(int *)param_1[4] = iVar7;
      if (*(int *)param_1[4] == -1) {
        return (int *)0x0;
      }
    }
  }
  piVar4 = (int *)param_1[4];
  local_8 = *piVar4;
  if ((local_8 == -1) ||
     ((piVar4[local_8 + 0x31] & local_c) == 0 && (piVar4[local_8 + 0x11] & local_10) == 0)) {
    local_8 = 0;
    puVar8 = (uint *)(piVar4 + 0x11);
    if ((piVar4[0x31] & local_c) == 0 && (piVar4[0x11] & local_10) == 0) {
      do {
        puVar11 = puVar8 + 0x21;
        local_8 = local_8 + 1;
        puVar8 = puVar8 + 1;
      } while ((*puVar11 & local_c) == 0 && (local_10 & *puVar8) == 0);
    }
  }
  iVar7 = 0;
  piVar2 = piVar4 + local_8 * 0x81 + 0x51;
  local_10 = piVar4[local_8 + 0x11] & local_10;
  if (local_10 == 0) {
    local_10 = piVar4[local_8 + 0x31] & local_c;
    iVar7 = 0x20;
  }
  for (; -1 < (intptr_t)local_10; local_10 = local_10 << 1) {
    iVar7 = iVar7 + 1;
  }
  piVar10 = (int *)piVar2[iVar7 * 2 + 1];
  iVar9 = *piVar10 - uVar6;
  iVar14 = (iVar9 >> 4) + -1;
  if (0x3f < iVar14) {
    iVar14 = 0x3f;
  }
  DAT_10023b3c = param_1;
  if (iVar14 != iVar7) {
    if (piVar10[1] == piVar10[2]) {
      if (iVar7 < 0x20) {
        pcVar1 = (char *)((intptr_t)piVar4 + iVar7 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar7 & 0x1f));
        piVar4[local_8 + 0x11] = uVar13 & piVar4[local_8 + 0x11];
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *param_1 = *param_1 & uVar13;
        }
      }
      else {
        pcVar1 = (char *)((intptr_t)piVar4 + iVar7 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar7 - 0x20 & 0x1f));
        piVar4[local_8 + 0x31] = piVar4[local_8 + 0x31] & uVar13;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          param_1[1] = param_1[1] & uVar13;
        }
      }
    }
    *(int *)(piVar10[2] + 4) = piVar10[1];
    *(int *)(piVar10[1] + 8) = piVar10[2];
    if (iVar9 == 0) goto LAB_1000eb5e;
    piVar10[1] = piVar2[iVar14 * 2 + 1];
    piVar10[2] = (intptr_t)(piVar2 + iVar14 * 2);
    (piVar2 + iVar14 * 2)[1] = (intptr_t)piVar10;
    *(int **)(piVar10[1] + 8) = piVar10;
    if (piVar10[1] == piVar10[2]) {
      cVar3 = *(char *)(iVar14 + 4 + (intptr_t)piVar4);
      bVar5 = (byte)iVar14;
      if (iVar14 < 0x20) {
        *(char *)(iVar14 + 4 + (intptr_t)piVar4) = cVar3 + '\x01';
        if (cVar3 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar5 & 0x1f);
        }
        piVar4[local_8 + 0x11] = piVar4[local_8 + 0x11] | 0x80000000U >> (bVar5 & 0x1f);
      }
      else {
        *(char *)(iVar14 + 4 + (intptr_t)piVar4) = cVar3 + '\x01';
        if (cVar3 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
        }
        piVar4[local_8 + 0x31] = piVar4[local_8 + 0x31] | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
      }
    }
  }
  if (iVar9 != 0) {
    *piVar10 = iVar9;
    *(int *)(iVar9 + -4 + (intptr_t)piVar10) = iVar9;
  }
LAB_1000eb5e:
  piVar10 = (int *)((intptr_t)piVar10 + iVar9);
  *piVar10 = uVar6 + 1;
  *(uint *)((intptr_t)piVar10 + (uVar6 - 4)) = uVar6 + 1;
  iVar7 = *piVar2;
  *piVar2 = iVar7 + 1;
  if (((iVar7 == 0) && (param_1 == DAT_10023b40)) && (local_8 == DAT_10023b38)) {
    DAT_10023b40 = (uint *)0x0;
  }
  *piVar4 = local_8;
  return piVar10 + 1;
}
#endif /* _heap_alloc */




#if 0
unsigned int * _heap_page_scan(void)

{
  unsigned int *puVar1;
  LPVOID pvVar2;
  
  if (DAT_10023b44 == DAT_10023b28) {
    pvVar2 = HeapReAlloc(hHeap,0,lpMem_10023b48,(DAT_10023b28 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (unsigned int *)0x0;
    }
    DAT_10023b28 = DAT_10023b28 + 0x10;
    lpMem_10023b48 = pvVar2;
  }
  puVar1 = (unsigned int *)((intptr_t)lpMem_10023b48 + DAT_10023b44 * 0x14);
  pvVar2 = HeapAlloc(hHeap,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_10023b44 = DAT_10023b44 + 1;
      *(unsigned int *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(hHeap,0,(LPVOID)puVar1[4]);
  }
  return (unsigned int *)0x0;
}
#endif /* _heap_page_scan */




int __cdecl _heap_page_init(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  LPVOID pvVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *lpAddress;
  
  iVar3 = *(int *)(param_1 + 0x10);
  iVar9 = 0;
  for (iVar4 = *(int *)(param_1 + 8); -1 < iVar4; iVar4 = iVar4 << 1) {
    iVar9 = iVar9 + 1;
  }
  iVar8 = 0x3f;
  iVar4 = iVar9 * 0x204 + 0x144 + iVar3;
  iVar5 = iVar4;
  do {
    *(int *)(iVar5 + 8) = iVar5;
    *(int *)(iVar5 + 4) = iVar5;
    iVar5 = iVar5 + 8;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  lpAddress = (int *)(iVar9 * 0x8000 + *(int *)(param_1 + 0xc));
  pvVar6 = VirtualAlloc(lpAddress,0x8000,0x1000,4);
  if (pvVar6 == (LPVOID)0x0) {
    iVar9 = -1;
  }
  else {
    if (lpAddress <= lpAddress + 0x1c00) {
      piVar7 = lpAddress + 4;
      do {
        piVar7[-2] = -1;
        piVar7[0x3fb] = -1;
        piVar7[-1] = 0xff0;
        *piVar7 = (intptr_t)(piVar7 + 0x3ff);
        piVar7[1] = (intptr_t)(piVar7 + -0x401);
        piVar7[0x3fa] = 0xff0;
        piVar1 = piVar7 + 0x3fc;
        piVar7 = piVar7 + 0x400;
      } while (piVar1 <= lpAddress + 0x1c00);
    }
    *(int **)(iVar4 + 0x1fc) = lpAddress + 3;
    lpAddress[5] = iVar4 + 0x1f8;
    *(int **)(iVar4 + 0x200) = lpAddress + 0x1c03;
    lpAddress[0x1c04] = iVar4 + 0x1f8;
    *(unsigned int *)(iVar3 + 0x44 + iVar9 * 4) = 0;
    *(unsigned int *)(iVar3 + 0xc4 + iVar9 * 4) = 1;
    cVar2 = *(char *)(iVar3 + 0x43);
    *(char *)(iVar3 + 0x43) = cVar2 + '\x01';
    if (cVar2 == '\0') {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(0x80000000U >> ((byte)iVar9 & 0x1f));
  }
  return iVar9;
}



#if 0
unsigned int __cdecl _heap_alloc2(uint *param_1,int param_2,int param_3)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_c;
  
  uVar5 = param_1[4];
  uVar12 = param_3 + 0x17U & 0xfffffff0;
  uVar10 = param_2 - param_1[3] >> 0xf;
  iVar3 = uVar10 * 0x204 + 0x144 + uVar5;
  iVar6 = *(int *)(param_2 + -4);
  iVar9 = iVar6 + -1;
  uVar13 = *(uint *)(iVar6 + -5 + param_2);
  iVar6 = iVar6 + -5 + param_2;
  if (iVar9 < (intptr_t)uVar12) {
    if (((uVar13 & 1) != 0) || ((intptr_t)(uVar13 + iVar9) < (intptr_t)uVar12)) {
      return 0;
    }
    local_c = ((intptr_t)uVar13 >> 4) - 1;
    if (0x3f < local_c) {
      local_c = 0x3f;
    }
    if (*(int *)(iVar6 + 4) == *(int *)(iVar6 + 8)) {
      if (local_c < 0x20) {
        pcVar1 = (char *)(local_c + 4 + uVar5);
        uVar11 = ~(0x80000000U >> ((byte)local_c & 0x1f));
        puVar7 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
        *puVar7 = *puVar7 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *param_1 = *param_1 & uVar11;
        }
      }
      else {
        pcVar1 = (char *)(local_c + 4 + uVar5);
        uVar11 = ~(0x80000000U >> ((byte)local_c - 0x20 & 0x1f));
        puVar7 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
        *puVar7 = *puVar7 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          param_1[1] = param_1[1] & uVar11;
        }
      }
    }
    *(unsigned int *)(*(int *)(iVar6 + 8) + 4) = *(unsigned int *)(iVar6 + 4);
    *(unsigned int *)(*(int *)(iVar6 + 4) + 8) = *(unsigned int *)(iVar6 + 8);
    iVar6 = uVar13 + (iVar9 - uVar12);
    if (0 < iVar6) {
      uVar13 = (iVar6 >> 4) - 1;
      iVar9 = param_2 + -4 + uVar12;
      if (0x3f < uVar13) {
        uVar13 = 0x3f;
      }
      iVar3 = iVar3 + uVar13 * 8;
      *(unsigned int *)(iVar9 + 4) = *(unsigned int *)(iVar3 + 4);
      *(int *)(iVar9 + 8) = iVar3;
      *(int *)(iVar3 + 4) = iVar9;
      *(int *)(*(int *)(iVar9 + 4) + 8) = iVar9;
      if (*(int *)(iVar9 + 4) == *(int *)(iVar9 + 8)) {
        cVar4 = *(char *)(uVar13 + 4 + uVar5);
        *(char *)(uVar13 + 4 + uVar5) = cVar4 + '\x01';
        bVar8 = (byte)uVar13;
        if (uVar13 < 0x20) {
          if (cVar4 == '\0') {
            *param_1 = *param_1 | 0x80000000U >> (bVar8 & 0x1f);
          }
          puVar7 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
        }
        else {
          if (cVar4 == '\0') {
            param_1[1] = param_1[1] | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
          }
          puVar7 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
          bVar8 = bVar8 - 0x20;
        }
        *puVar7 = *puVar7 | 0x80000000U >> (bVar8 & 0x1f);
      }
      piVar2 = (int *)(param_2 + -4 + uVar12);
      *piVar2 = iVar6;
      *(int *)(iVar6 + -4 + (intptr_t)piVar2) = iVar6;
    }
    *(uint *)(param_2 + -4) = uVar12 + 1;
    *(uint *)(param_2 + -8 + uVar12) = uVar12 + 1;
  }
  else if ((intptr_t)uVar12 < iVar9) {
    param_3 = iVar9 - uVar12;
    *(uint *)(param_2 + -4) = uVar12 + 1;
    piVar2 = (int *)(param_2 + -4 + uVar12);
    uVar11 = (param_3 >> 4) - 1;
    piVar2[-1] = uVar12 + 1;
    if (0x3f < uVar11) {
      uVar11 = 0x3f;
    }
    if ((uVar13 & 1) == 0) {
      uVar12 = ((intptr_t)uVar13 >> 4) - 1;
      if (0x3f < uVar12) {
        uVar12 = 0x3f;
      }
      if (*(int *)(iVar6 + 4) == *(int *)(iVar6 + 8)) {
        if (uVar12 < 0x20) {
          pcVar1 = (char *)(uVar12 + 4 + uVar5);
          uVar12 = ~(0x80000000U >> ((byte)uVar12 & 0x1f));
          puVar7 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
          *puVar7 = *puVar7 & uVar12;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *param_1 = *param_1 & uVar12;
          }
        }
        else {
          pcVar1 = (char *)(uVar12 + 4 + uVar5);
          uVar12 = ~(0x80000000U >> ((byte)uVar12 - 0x20 & 0x1f));
          puVar7 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
          *puVar7 = *puVar7 & uVar12;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            param_1[1] = param_1[1] & uVar12;
          }
        }
      }
      *(unsigned int *)(*(int *)(iVar6 + 8) + 4) = *(unsigned int *)(iVar6 + 4);
      *(unsigned int *)(*(int *)(iVar6 + 4) + 8) = *(unsigned int *)(iVar6 + 8);
      param_3 = param_3 + uVar13;
      uVar11 = (param_3 >> 4) - 1;
      if (0x3f < uVar11) {
        uVar11 = 0x3f;
      }
    }
    iVar6 = iVar3 + uVar11 * 8;
    piVar2[1] = *(int *)(iVar3 + 4 + uVar11 * 8);
    piVar2[2] = iVar6;
    *(int **)(iVar6 + 4) = piVar2;
    *(int **)(piVar2[1] + 8) = piVar2;
    if (piVar2[1] == piVar2[2]) {
      cVar4 = *(char *)(uVar11 + 4 + uVar5);
      *(char *)(uVar11 + 4 + uVar5) = cVar4 + '\x01';
      bVar8 = (byte)uVar11;
      if (uVar11 < 0x20) {
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar8 & 0x1f);
        }
        puVar7 = (uint *)(uVar5 + 0x44 + uVar10 * 4);
      }
      else {
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
        }
        puVar7 = (uint *)(uVar5 + 0xc4 + uVar10 * 4);
        bVar8 = bVar8 - 0x20;
      }
      *puVar7 = *puVar7 | 0x80000000U >> (bVar8 & 0x1f);
    }
    *piVar2 = param_3;
    *(int *)(param_3 + -4 + (intptr_t)piVar2) = param_3;
  }
  return 1;
}
#endif /* _heap_alloc2 */




unsigned int _heap_validate(void)

{
  LPVOID lp;
  BOOL BVar1;
  unsigned int uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  int *piVar11;
  int bVar12;
  int local_140 [64];
  uint *local_40;
  uint *local_3c;
  uint *local_38;
  int local_34;
  uint local_30;
  uint *local_2c;
  uint local_28;
  int local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  uint *local_10;
  int local_c;
  int *local_8;
  
  BVar1 = IsBadWritePtr(lpMem_10023b48,DAT_10023b44 * 0x14);
  if (BVar1 == 0) {
    local_24 = 0;
    puVar8 = (uint*)(intptr_t)lpMem_10023b48;
    if (0 < DAT_10023b44) {
      do {
        lp = (LPVOID)puVar8[4];
        local_3c = puVar8;
        BVar1 = IsBadWritePtr(lp,0x41c4);
        if (BVar1 != 0) {
          return 0xfffffffe;
        }
        local_10 = (uint *)puVar8[3];
        local_30 = 0;
        local_2c = (uint *)((intptr_t)lp + 0x144);
        local_18 = puVar8[2];
        puVar9 = (uint *)((intptr_t)lp + 0xc4);
        local_1c = 0;
        local_34 = 0;
        do {
          local_28 = 0;
          local_20 = 0;
          local_8 = (int *)0x0;
          bVar12 = -1 < (intptr_t)local_18;
          piVar11 = local_140;
          local_40 = puVar9;
          for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
            *piVar11 = 0;
            piVar11 = piVar11 + 1;
          }
          if (bVar12) {
            BVar1 = IsBadWritePtr(local_10,0x8000);
            if (BVar1 != 0) {
              return 0xfffffffc;
            }
            iVar5 = 0;
            puVar8 = local_10 + 0x3ff;
            do {
              puVar9 = puVar8 + -0x3fc;
              if ((puVar8[-0x3fd] != 0xffffffff) || (*puVar8 != 0xffffffff)) {
                return 0xfffffffb;
              }
              do {
                uVar4 = *puVar9;
                if ((uVar4 & 1) == 0) {
                  iVar3 = ((intptr_t)uVar4 >> 4) + -1;
                  if (0x3f < iVar3) {
                    iVar3 = 0x3f;
                  }
                  local_140[iVar3] = local_140[iVar3] + 1;
                  uVar6 = uVar4;
                }
                else {
                  if (0x400 < (intptr_t)(uVar4 - 1)) {
                    return 0xfffffffa;
                  }
                  local_8 = (int *)((intptr_t)local_8 + 1);
                  uVar6 = uVar4 - 1;
                }
                if ((((intptr_t)uVar6 < 0x10) || ((uVar6 & 0xf) != 0)) || (0xff0 < (intptr_t)uVar6)) {
                  return 0xfffffff9;
                }
                puVar10 = (uint *)((uVar6 - 4) + (intptr_t)puVar9);
                puVar9 = (uint *)(uVar6 + (intptr_t)puVar9);
                if (*puVar10 != uVar4) {
                  return 0xfffffff8;
                }
              } while (puVar9 < puVar8);
              if (puVar9 != puVar8) {
                return 0xfffffff8;
              }
              puVar8 = puVar8 + 0x400;
              iVar5 = iVar5 + 1;
            } while (iVar5 < 8);
            if ((int *)*local_2c != local_8) {
              return 0xfffffff7;
            }
            local_c = 0;
            local_8 = local_140;
            puVar10 = local_2c;
            do {
              local_14 = 0;
              puVar8 = (uint *)puVar10[1];
              local_38 = puVar10;
              if ((uint *)puVar10[1] != puVar10) {
                do {
                  puVar9 = puVar8;
                  if (local_14 == *local_8) break;
                  if ((puVar9 < local_10) || (local_10 + 0x2000 <= puVar9)) {
                    return 0xfffffff6;
                  }
                  puVar7 = (uint *)(((uintptr_t)puVar9 & 0xfffff000) + 0xc);
                  puVar8 = (uint *)(((uintptr_t)puVar9 & 0xfffff000) + 0xffc);
                  if (puVar7 == puVar8) {
                    return 0xfffffff5;
                  }
                  do {
                    if (puVar7 == puVar9) break;
                    puVar7 = (uint *)((intptr_t)puVar7 + (*puVar7 & 0xfffffffe));
                  } while (puVar7 != puVar8);
                  if (puVar7 == puVar8) {
                    return 0xfffffff5;
                  }
                  iVar5 = ((intptr_t)*puVar9 >> 4) + -1;
                  if (0x3f < iVar5) {
                    iVar5 = 0x3f;
                  }
                  if (iVar5 != local_c) {
                    return 0xfffffff4;
                  }
                  if ((uint *)puVar9[2] != local_38) {
                    return 0xfffffff3;
                  }
                  local_14 = local_14 + 1;
                  puVar8 = (uint *)puVar9[1];
                  local_38 = puVar9;
                } while ((uint *)puVar9[1] != puVar10);
                if (local_14 != 0) {
                  if (local_c < 0x20) {
                    uVar4 = 0x80000000 >> ((byte)local_c & 0x1f);
                    local_28 = local_28 | uVar4;
                    local_30 = local_30 | uVar4;
                  }
                  else {
                    uVar4 = 0x80000000 >> ((byte)local_c - 0x20 & 0x1f);
                    local_20 = local_20 | uVar4;
                    local_1c = local_1c | uVar4;
                  }
                }
              }
              if (((uint *)local_38[1] != puVar10) || (local_14 != *local_8)) {
                return 0xfffffff2;
              }
              if ((uint *)puVar10[2] != local_38) {
                return 0xfffffff1;
              }
              local_c = local_c + 1;
              local_8 = local_8 + 1;
              puVar8 = local_3c;
              puVar9 = local_40;
              puVar10 = puVar10 + 2;
            } while (local_c < 0x40);
          }
          if ((local_28 != puVar9[-0x20]) || (local_20 != *puVar9)) {
            return 0xfffffff0;
          }
          local_10 = local_10 + 0x2000;
          local_2c = local_2c + 0x81;
          local_18 = local_18 << 1;
          local_34 = local_34 + 1;
          puVar9 = puVar9 + 1;
        } while (local_34 < 0x20);
        if ((local_30 != *puVar8) || (local_1c != puVar8[1])) {
          return 0xffffffef;
        }
        puVar8 = puVar8 + 5;
        local_24 = local_24 + 1;
        local_40 = puVar9;
      } while (local_24 < DAT_10023b44);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



#if 0
unsigned int * __cdecl memmove(unsigned int *param_1,unsigned int *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  unsigned int *puVar3;
  unsigned int *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (unsigned int *)(param_3 + (intptr_t)param_2))) {
    puVar3 = (unsigned int *)((param_3 - 4) + (intptr_t)param_2);
    puVar4 = (unsigned int *)((param_3 - 4) + (intptr_t)param_1);
    if (((uintptr_t)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_1000f607_caseD_2;
        case 3:
          goto switchD_1000f607_caseD_3;
        }
        goto switchD_1000f607_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_1000f607_caseD_0;
      case 1:
        goto switchD_1000f607_caseD_1;
      case 2:
        goto switchD_1000f607_caseD_2;
      case 3:
        goto switchD_1000f607_caseD_3;
      default:
        uVar1 = param_3 - ((uintptr_t)puVar4 & 3);
        switch((uintptr_t)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000f607_caseD_2;
            case 3:
              goto switchD_1000f607_caseD_3;
            }
            goto switchD_1000f607_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -2);
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000f607_caseD_2;
            case 3:
              goto switchD_1000f607_caseD_3;
            }
            goto switchD_1000f607_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(unsigned char *)((intptr_t)puVar4 + 1) = *(unsigned char *)((intptr_t)puVar3 + 1);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -3);
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000f607_caseD_2;
            case 3:
              goto switchD_1000f607_caseD_3;
            }
            goto switchD_1000f607_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_1000f607_caseD_1:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      return param_1;
    case 2:
switchD_1000f607_caseD_2:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
      return param_1;
    case 3:
switchD_1000f607_caseD_3:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
      *(unsigned char *)((intptr_t)puVar4 + 1) = *(unsigned char *)((intptr_t)puVar3 + 1);
      return param_1;
    }
switchD_1000f607_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uintptr_t)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_1000f485_caseD_2;
      case 3:
        goto switchD_1000f485_caseD_3;
      }
      goto switchD_1000f485_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_1000f485_caseD_0;
    case 1:
      goto switchD_1000f485_caseD_1;
    case 2:
      goto switchD_1000f485_caseD_2;
    case 3:
      goto switchD_1000f485_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uintptr_t)param_1 & 3);
      switch((uintptr_t)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        *(unsigned char *)((intptr_t)param_1 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(unsigned char *)((intptr_t)param_1 + 2) = *(unsigned char *)((intptr_t)param_2 + 2);
        param_2 = (unsigned int *)((intptr_t)param_2 + 3);
        puVar3 = (unsigned int *)((intptr_t)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f485_caseD_2;
          case 3:
            goto switchD_1000f485_caseD_3;
          }
          goto switchD_1000f485_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        uVar1 = uVar1 >> 2;
        *(unsigned char *)((intptr_t)param_1 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
        param_2 = (unsigned int *)((intptr_t)param_2 + 2);
        puVar3 = (unsigned int *)((intptr_t)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f485_caseD_2;
          case 3:
            goto switchD_1000f485_caseD_3;
          }
          goto switchD_1000f485_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        param_2 = (unsigned int *)((intptr_t)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (unsigned int *)((intptr_t)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f485_caseD_2;
          case 3:
            goto switchD_1000f485_caseD_3;
          }
          goto switchD_1000f485_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_1000f485_caseD_1:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    return param_1;
  case 2:
switchD_1000f485_caseD_2:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    *(unsigned char *)((intptr_t)puVar3 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
    return param_1;
  case 3:
switchD_1000f485_caseD_3:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    *(unsigned char *)((intptr_t)puVar3 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
    *(unsigned char *)((intptr_t)puVar3 + 2) = *(unsigned char *)((intptr_t)param_2 + 2);
    return param_1;
  }
switchD_1000f485_caseD_0:
  return param_1;
}
#endif /* memmove */




#if 0
int __onexit(int *param_1)

{
  int *piVar1;
  int bVar2;
  int iVar3;
  undefined3 extraout_var;
  
  piVar1 = (int *)*param_1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    iVar3 = __CxxFrameHandler_fail_abort();
    return iVar3;
  }
  if ((DAT_10023794 != (FARPROC)0x0) &&
     (bVar2 = IsBadCodePtr(DAT_10023794), CONCAT31(extraout_var,bVar2) != 0)) {
    iVar3 = (*DAT_10023794)(param_1);
    return iVar3;
  }
  return 0;
}
#endif /* __onexit */




#if 0
int __cdecl IsBadReadPtr(void *param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadReadPtr(param_1,param_2);
  return BVar1 == 0;
}
#endif /* IsBadReadPtr */




#if 0
int __cdecl IsBadWritePtr(LPVOID param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  return BVar1 == 0;
}
#endif /* IsBadWritePtr */




#if 0
int __cdecl IsBadCodePtr(FARPROC param_1)

{
  BOOL BVar1;
  
  BVar1 = IsBadCodePtr(param_1);
  return BVar1 == 0;
}
#endif /* IsBadCodePtr */




/* DUPLICATE: __local_unwind2 */
#if 0
#if 0 /* CRT: __local_unwind2 */
#if 0
void __local_unwind2(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}
#endif /* __local_unwind2 */

#endif

#endif




#if 0
unsigned int * __cdecl memmove2(unsigned int *param_1,unsigned int *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  unsigned int *puVar3;
  unsigned int *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (unsigned int *)(param_3 + (intptr_t)param_2))) {
    puVar3 = (unsigned int *)((param_3 - 4) + (intptr_t)param_2);
    puVar4 = (unsigned int *)((param_3 - 4) + (intptr_t)param_1);
    if (((uintptr_t)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_1000fad7_caseD_2;
        case 3:
          goto switchD_1000fad7_caseD_3;
        }
        goto switchD_1000fad7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_1000fad7_caseD_0;
      case 1:
        goto switchD_1000fad7_caseD_1;
      case 2:
        goto switchD_1000fad7_caseD_2;
      case 3:
        goto switchD_1000fad7_caseD_3;
      default:
        uVar1 = param_3 - ((uintptr_t)puVar4 & 3);
        switch((uintptr_t)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fad7_caseD_2;
            case 3:
              goto switchD_1000fad7_caseD_3;
            }
            goto switchD_1000fad7_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -2);
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fad7_caseD_2;
            case 3:
              goto switchD_1000fad7_caseD_3;
            }
            goto switchD_1000fad7_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
          *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(unsigned char *)((intptr_t)puVar4 + 1) = *(unsigned char *)((intptr_t)puVar3 + 1);
          puVar3 = (unsigned int *)((intptr_t)puVar3 + -3);
          puVar4 = (unsigned int *)((intptr_t)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fad7_caseD_2;
            case 3:
              goto switchD_1000fad7_caseD_3;
            }
            goto switchD_1000fad7_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_1000fad7_caseD_1:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      return param_1;
    case 2:
switchD_1000fad7_caseD_2:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
      return param_1;
    case 3:
switchD_1000fad7_caseD_3:
      *(unsigned char *)((intptr_t)puVar4 + 3) = *(unsigned char *)((intptr_t)puVar3 + 3);
      *(unsigned char *)((intptr_t)puVar4 + 2) = *(unsigned char *)((intptr_t)puVar3 + 2);
      *(unsigned char *)((intptr_t)puVar4 + 1) = *(unsigned char *)((intptr_t)puVar3 + 1);
      return param_1;
    }
switchD_1000fad7_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uintptr_t)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_1000f955_caseD_2;
      case 3:
        goto switchD_1000f955_caseD_3;
      }
      goto switchD_1000f955_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_1000f955_caseD_0;
    case 1:
      goto switchD_1000f955_caseD_1;
    case 2:
      goto switchD_1000f955_caseD_2;
    case 3:
      goto switchD_1000f955_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uintptr_t)param_1 & 3);
      switch((uintptr_t)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        *(unsigned char *)((intptr_t)param_1 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(unsigned char *)((intptr_t)param_1 + 2) = *(unsigned char *)((intptr_t)param_2 + 2);
        param_2 = (unsigned int *)((intptr_t)param_2 + 3);
        puVar3 = (unsigned int *)((intptr_t)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f955_caseD_2;
          case 3:
            goto switchD_1000f955_caseD_3;
          }
          goto switchD_1000f955_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        uVar1 = uVar1 >> 2;
        *(unsigned char *)((intptr_t)param_1 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
        param_2 = (unsigned int *)((intptr_t)param_2 + 2);
        puVar3 = (unsigned int *)((intptr_t)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f955_caseD_2;
          case 3:
            goto switchD_1000f955_caseD_3;
          }
          goto switchD_1000f955_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(unsigned char *)param_1 = *(unsigned char *)param_2;
        param_2 = (unsigned int *)((intptr_t)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (unsigned int *)((intptr_t)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000f955_caseD_2;
          case 3:
            goto switchD_1000f955_caseD_3;
          }
          goto switchD_1000f955_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_1000f955_caseD_1:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    return param_1;
  case 2:
switchD_1000f955_caseD_2:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    *(unsigned char *)((intptr_t)puVar3 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
    return param_1;
  case 3:
switchD_1000f955_caseD_3:
    *(unsigned char *)puVar3 = *(unsigned char *)param_2;
    *(unsigned char *)((intptr_t)puVar3 + 1) = *(unsigned char *)((intptr_t)param_2 + 1);
    *(unsigned char *)((intptr_t)puVar3 + 2) = *(unsigned char *)((intptr_t)param_2 + 2);
    return param_1;
  }
switchD_1000f955_caseD_0:
  return param_1;
}
#endif /* memmove2 */




#if 0
void _invoke_watson(void)

{
  _RtMsgAndAbort(10);
  raise((DWORD *)0x16);
                    // WARNING: Subroutine does not return
  __exit(3);
}
#endif /* _invoke_watson */




#if 0
void __fptrap(void)

{
  byte in_FPUStatusWord;
  
  _fpreset(in_FPUStatusWord);
  return;
}
#endif /* __fptrap */




uint __thiscall _controlfp_s_save(void *_this,uint param_1,uint param_2)

{
  uint uVar1;
  unsigned short in_FPUControlWord;
  unsigned int local_8;
  
  local_8 = CONCAT22((short)((uintptr_t)_this >> 0x10),in_FPUControlWord);
  _statusfp_get((void*)local_8);
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  _pcgetenv_denorm(uVar1);
  return uVar1;
}



void __thiscall _controlfp_s_restore(void *_this,uint param_1,uint param_2)

{
  _controlfp_s_save(_this,param_1,param_2 & 0xfff7ffff);
  return;
}



#if 0
uint __cdecl _statusfp_get(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 != 0) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
    else if (uVar2 == 0x800) {
      uVar1 = uVar1 | 0x200;
    }
    else if (uVar2 == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}
#endif /* _statusfp_get */




#if 0
uint __cdecl _pcgetenv_denorm(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uintptr_t)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = param_1 & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x800;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
  }
  if ((param_1 & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}
#endif /* _pcgetenv_denorm */




uint __cdecl _fpreset(byte param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  return uVar1;
}



#if 0
uint __thiscall iswctype(void *_this, int param_1)

{
  BOOL BVar1;
  int iVar2;
  unsigned int local_8;
  
  if (param_1 + 1U < 0x101) {
    (*(unsigned short*)((char*)&(param_1)+2)) = *(ushort *)(PTR_DAT_10021780 + param_1 * 2);
  }
  else {
    if ((PTR_DAT_10021780[(param_1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      local_8 = CONCAT31((int3)((uintptr_t)_this >> 8),(char)param_1) & 0xffff00ff;
      iVar2 = 1;
    }
    else {
      (*(unsigned short*)&(local_8)) = CONCAT11((char)param_1,(char)((uintptr_t)param_1 >> 8));
      local_8 = CONCAT22((short)((uintptr_t)_this >> 0x10),(unsigned short)local_8) & 0xff00ffff;
      iVar2 = 2;
    }
    BVar1 = _getstringtype(1,(LPCSTR)&local_8,iVar2,(LPWORD)((intptr_t)&param_1 + 2),0,0,1);
    if (BVar1 == 0) {
      return 0;
    }
  }
  return (*(unsigned short*)((char*)&(param_1)+2)) & param_2;
}
#endif /* iswctype */




#if 0
uint __cdecl towlower(uint param_1)

{
  void *extraout_ECX;
  int bVar1;
  void *_this;
  
  if (DAT_100237bc == 0) {
    if ((0x40 < (intptr_t)param_1) && ((intptr_t)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement(&DAT_10023894);
    bVar1 = DAT_10023884 != 0;
    _this = extraout_ECX;
    if (bVar1) {
      InterlockedDecrement(&DAT_10023894);
      _this = (void *)0x13;
      _lock_critical_section(0x13);
    }
    param_1 = _towlower_l(_this,param_1);
    if (bVar1) {
      _unlock_critical_section(0x13);
    }
    else {
      InterlockedDecrement(&DAT_10023894);
    }
  }
  return param_1;
}
#endif /* towlower */




#if 0
uint __thiscall _towlower_l(void *_this,uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  void *local_8;
  
  uVar1 = param_1;
  if (DAT_100237bc == 0) {
    if ((0x40 < (intptr_t)param_1) && ((intptr_t)param_1 < 0x5b)) {
      uVar1 = param_1 + 0x20;
    }
  }
  else {
    iVar3 = 1;
    local_8 = _this;
    if ((intptr_t)param_1 < 0x100) {
      if (cbMultiByte_10021b40 < 2) {
        uVar2 = (byte)PTR_DAT_10021780[param_1 * 2] & 1;
      }
      else {
        uVar2 = iswctype(_this, param_1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    if ((PTR_DAT_10021780[((intptr_t)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      param_1 = CONCAT31((int3)(param_1 >> 8),(char)uVar1) & 0xffff00ff;
    }
    else {
      uVar2 = param_1 >> 0x10;
      (*(unsigned short*)&(param_1)) = CONCAT11((char)uVar1,(char)(uVar1 >> 8));
      param_1 = CONCAT22((short)uVar2,(unsigned short)param_1) & 0xff00ffff;
      iVar3 = 2;
    }
    iVar3 = _lcmapstring(DAT_100237bc,0x100,(char *)&param_1,iVar3,(LPWSTR)&local_8,3,0,1);
    if (iVar3 != 0) {
      if (iVar3 == 1) {
        uVar1 = (uintptr_t)local_8 & 0xff;
      }
      else {
        uVar1 = (uintptr_t)local_8 & 0xffff;
      }
    }
  }
  return uVar1;
}
#endif /* _towlower_l */




unsigned int __cdecl _ldtestbit(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + (param_2 / 0x20) * 4) & ~(-1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f)))
      != 0) {
    return 0;
  }
  iVar2 = param_2 / 0x20 + 1;
  if (iVar2 < 3) {
    piVar1 = (int *)(param_1 + iVar2 * 4);
    do {
      if (*piVar1 != 0) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 3);
  }
  return 1;
}



void __cdecl _ldaddbit(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = (uint *)(param_1 + (param_2 / 0x20) * 4);
  iVar1 = _add_carry(*puVar3,1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f),puVar3);
  iVar2 = param_2 / 0x20 + -1;
  if (-1 < iVar2) {
    puVar3 = (uint *)(param_1 + iVar2 * 4);
    do {
      if (iVar1 == 0) {
        return;
      }
      iVar1 = _add_carry(*puVar3,1,puVar3);
      iVar2 = iVar2 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
  }
  return;
}



#if 0
unsigned int __cdecl _ldclrbit(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  unsigned int *puVar5;
  unsigned int local_8;
  
  local_8 = 0;
  puVar1 = (uint *)(param_1 + (param_2 / 0x20) * 4);
  bVar3 = 0x1f - (char)(param_2 % 0x20);
  if (((*puVar1 & 1 << (bVar3 & 0x1f)) != 0) &&
     (iVar2 = _ldtestbit(param_1,param_2 + 1), iVar2 == 0)) {
    local_8 = _ldaddbit(param_1,param_2 + -1);
  }
  *puVar1 = *puVar1 & -1 << (bVar3 & 0x1f);
  iVar2 = param_2 / 0x20 + 1;
  if (iVar2 < 3) {
    puVar5 = (unsigned int *)(param_1 + iVar2 * 4);
    for (iVar4 = 3 - iVar2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return local_8;
}
#endif /* _ldclrbit */




void __cdecl _ldcopym(int param_1,unsigned int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 - (intptr_t)param_2;
  iVar2 = 3;
  do {
    *(unsigned int *)(iVar1 + (intptr_t)param_2) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



void __cdecl _ldzero(unsigned int *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}



unsigned int __cdecl _ldtest(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}



void __cdecl _ldshr(uint *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int local_8;
  
  local_8 = 3;
  iVar2 = (intptr_t)param_2 / 0x20;
  iVar5 = (intptr_t)param_2 % 0x20;
  param_2 = 0;
  bVar3 = (byte)iVar5;
  puVar6 = param_1;
  do {
    uVar1 = *puVar6;
    *puVar6 = uVar1 >> (bVar3 & 0x1f) | param_2;
    puVar6 = puVar6 + 1;
    param_2 = (uVar1 & ~(-1 << (bVar3 & 0x1f))) << (0x20 - bVar3 & 0x1f);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  iVar5 = 2;
  iVar4 = 8;
  do {
    if (iVar5 < iVar2) {
      *(unsigned int *)(iVar4 + (intptr_t)param_1) = 0;
    }
    else {
      *(unsigned int *)(iVar4 + (intptr_t)param_1) = *(unsigned int *)(iVar4 + iVar2 * -4 + (intptr_t)param_1);
    }
    iVar5 = iVar5 + -1;
    iVar4 = iVar4 + -4;
  } while (-1 < iVar4);
  return;
}



unsigned int __cdecl _ldtod_core(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned int local_1c [3];
  uint local_10;
  uint local_c;
  int local_8;
  
  uVar1 = param_1[5];
  local_10 = *(uint *)(param_1 + 3);
  local_c = *(uint *)(param_1 + 1);
  uVar3 = uVar1 & 0x7fff;
  iVar4 = uVar3 - 0x3fff;
  local_8 = (uintptr_t)*param_1 << 0x10;
  if (iVar4 == -0x3fff) {
    iVar4 = 0;
    iVar2 = _ldtest((int *)&local_10);
    if (iVar2 != 0) {
LAB_10010336:
      uVar5 = 0;
      goto LAB_10010338;
    }
    _ldzero(&local_10);
  }
  else {
    _ldcopym((intptr_t)local_1c,&local_10);
    _ldclrbit((intptr_t)&local_10,param_3[2]);
    if (iVar2 != 0) {
      iVar4 = uVar3 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar4 < iVar2 - param_3[2]) {
      _ldzero(&local_10);
    }
    else {
      if (iVar2 < iVar4) {
        if (*param_3 <= iVar4) {
          _ldzero(&local_10);
          local_10 = local_10 | 0x80000000;
          _ldshr(&local_10,param_3[3]);
          iVar4 = param_3[5] + *param_3;
          uVar5 = 1;
          goto LAB_10010338;
        }
        local_10 = local_10 & 0x7fffffff;
        iVar4 = param_3[5] + iVar4;
        _ldshr(&local_10,param_3[3]);
        goto LAB_10010336;
      }
      _ldcopym((intptr_t)&local_10,local_1c);
      _ldshr(&local_10,iVar2 - iVar4);
      _ldclrbit((intptr_t)&local_10,param_3[2]);
      _ldshr(&local_10,param_3[3] + 1);
    }
  }
  iVar4 = 0;
  uVar5 = 2;
LAB_10010338:
  local_10 = iVar4 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uintptr_t)((uVar1 & 0x8000) != 0) & 0x80000000 | local_10;
  if (param_3[4] == 0x40) {
    param_2[1] = local_10;
    *param_2 = local_c;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = local_10;
  }
  return uVar5;
}



void __cdecl _ld12tod(ushort *param_1,uint *param_2)

{
  _ldtod_core(param_1,param_2,(int *)&DAT_10021b50);
  return;
}



void __cdecl _ld12tof(ushort *param_1,uint *param_2)

{
  _ldtod_core(param_1,param_2,(int *)&DAT_10021b68);
  return;
}



unsigned int __cdecl _ld12told(ushort *param_1,unsigned int *param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  unsigned int local_14;
  unsigned int local_10;
  int local_c;
  unsigned int local_8;
  
  local_8 = 0;
  uVar1 = param_1[5];
  local_14 = *(unsigned int *)(param_1 + 3);
  local_10 = *(unsigned int *)(param_1 + 1);
  local_c = (uintptr_t)*param_1 << 0x10;
  uVar3 = uVar1 & 0x7fff;
  _ldclrbit((intptr_t)&local_14,0x40);
  if (iVar2 != 0) {
    local_14 = 0x80000000;
    uVar3 = uVar3 + 1;
  }
  if (uVar3 == 0x7fff) {
    local_8 = 1;
  }
  param_2[1] = local_14;
  *(ushort *)(param_2 + 2) = uVar1 & 0x8000 | uVar3;
  *param_2 = local_10;
  return local_8;
}



#if 0
void __thiscall strtod(void *_this, uint *param_1)

{
  ushort local_10 [6];
  
  _strtod_core(_this,local_10,(int *)&param_2,param_2,0,0,0,0);
  _ld12tod(local_10,param_1);
  return;
}
#endif /* strtod */




#if 0
void __thiscall strtold(void *_this,unsigned int *param_1,byte *param_2)

{
  ushort local_10 [6];
  
  _strtod_core(_this,local_10,(int *)&param_2,param_2,1,0,0,0);
  _ld12told(local_10,param_1);
  return;
}
#endif /* strtold */




#if 0
void __thiscall strtof(void *_this, uint *param_1)

{
  ushort local_10 [6];
  
  _strtod_core(_this,local_10,(int *)&param_2,param_2,0,0,0,0);
  _ld12tof(local_10,param_1);
  return;
}
#endif /* strtof */




void __cdecl _cropzeros(char *param_1,int param_2,int param_3)

{
  char *_Str;
  char *pcVar1;
  char *pcVar2;
  size_t sVar3;
  char *pcVar4;
  char cVar5;
  
  pcVar1 = param_1;
  pcVar4 = *(char **)(param_3 + 0xc);
  _Str = param_1 + 1;
  *param_1 = '0';
  pcVar2 = _Str;
  if (0 < param_2) {
    param_1 = (char *)param_2;
    param_2 = 0;
    do {
      cVar5 = *pcVar4;
      if (cVar5 == '\0') {
        cVar5 = '0';
      }
      else {
        pcVar4 = pcVar4 + 1;
      }
      *pcVar2 = cVar5;
      pcVar2 = pcVar2 + 1;
      param_1 = param_1 + -1;
    } while (param_1 != (char *)0x0);
  }
  *pcVar2 = '\0';
  if ((-1 < param_2) && ('4' < *pcVar4)) {
    while (pcVar2 = pcVar2 + -1, *pcVar2 == '9') {
      *pcVar2 = '0';
    }
    *pcVar2 = *pcVar2 + '\x01';
  }
  if (*pcVar1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
  }
  else {
    sVar3 = _strlen(_Str);
    memmove2((unsigned int *)pcVar1,(unsigned int *)_Str,sVar3 + 1);
  }
  return;
}



#if 0
int * __cdecl _ecvt_core(unsigned int param_1,unsigned int param_2,int *param_3,uint *param_4)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  unsigned int in_stack_ffffffbc;
  unsigned short uVar4;
  short local_2c;
  char local_2a;
  uint local_28 [6];
  uint local_10;
  uint uStack_c;
  unsigned short uStack_8;
  
  uVar4 = (unsigned short)((uintptr_t)in_stack_ffffffbc >> 0x10);
  _dtold(&local_10,&param_1);
  iVar3 = _ld2digits(local_10,uStack_c,CONCAT22(uVar4,uStack_8),0x11,0,&local_2c);
  puVar2 = param_4;
  piVar1 = param_3;
  param_3[2] = iVar3;
  *param_3 = (intptr_t)local_2a;
  param_3[1] = (intptr_t)local_2c;
  strcpy(param_4,local_28);
  piVar1[3] = (intptr_t)puVar2;
  return piVar1;
}
#endif /* _ecvt_core */




void __cdecl _dtold(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint local_8;
  
  uVar1 = *(ushort *)((intptr_t)param_2 + 6);
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  uVar2 = *param_2;
  local_8 = 0x80000000;
  if (uVar3 == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(unsigned short *)(param_1 + 2) = 0;
      return;
    }
    iVar4 = 0x3c01;
    local_8 = 0;
  }
  else if (uVar3 == 0x7ff) {
    iVar4 = 0x7fff;
  }
  else {
    iVar4 = uVar3 + 0x3c00;
  }
  local_8 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | local_8;
  param_1[1] = local_8;
  *param_1 = uVar2 << 0xb;
  while ((local_8 & 0x80000000) == 0) {
    local_8 = *param_1 >> 0x1f | local_8 * 2;
    *param_1 = *param_1 * 2;
    param_1[1] = local_8;
    iVar4 = iVar4 + 0xffff;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | (ushort)iVar4;
  return;
}



#if 0
uint * __cdecl strcpy(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uintptr_t)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uintptr_t)bVar1;
    param_2 = (uint *)((intptr_t)param_2 + 1);
    if (bVar1 == 0) goto LAB_10010718;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((intptr_t)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_10010718:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((intptr_t)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}
#endif /* strcpy */




#if 0
uint * __cdecl strcat(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uintptr_t)puVar3 & 3) == 0) goto LAB_1001065c;
    uVar4 = *puVar3;
    puVar3 = (uint *)((intptr_t)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_1001068f;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((intptr_t)puVar5 + 2);
      goto joined_r0x100106ab;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_1001065c:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x100106ab;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((intptr_t)puVar5 + 1);
      goto joined_r0x100106ab;
    }
  }
LAB_1001068f:
  puVar5 = (uint *)((intptr_t)puVar3 + -1);
joined_r0x100106ab:
  do {
    if (((uintptr_t)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_10010718:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((intptr_t)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uintptr_t)bVar1;
    param_2 = (uint *)((intptr_t)param_2 + 1);
    if (bVar1 == 0) goto LAB_10010718;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((intptr_t)puVar5 + 1);
  } while( true );
}
#endif /* strcat */




// Library Function - Single Match
//  _memset
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

#if 0
void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(intptr_t)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(unsigned char *)puVar4 = (unsigned char)_Val;
        puVar4 = (uint *)((intptr_t)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((intptr_t)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}
#endif /* _memset */




// Library Function - Single Match
//  __fptrap
// 
// Library: Visual Studio 2003 Release

/* DUPLICATE: __fptrap */
#if 0
#if 0
void __cdecl __fptrap(void)

{
  __amsg_exit(2);
  return;
}
#endif /* __fptrap */

#endif




unsigned int __cdecl _setmbcp(int param_1)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  BOOL BVar6;
  uint uVar7;
  uint uVar8;
  BYTE *pBVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  byte *pbVar13;
  unsigned int uVar14;
  unsigned int *puVar15;
  struct _cpinfo local_1c;
  uint local_8;
  
  _lock_critical_section(0x19);
  CodePage = _getmbcp(param_1);
  if (CodePage != CodePage_10023898) {
    if (CodePage != 0) {
      iVar12 = 0;
      pUVar5 = &DAT_10021b88;
LAB_100107be:
      if (*pUVar5 != CodePage) goto code_r0x100107c2;
      local_8 = 0;
      puVar15 = &DAT_10023a20;
      for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar15 = 0;
        puVar15 = puVar15 + 1;
      }
      iVar12 = iVar12 * 0x30;
      *(unsigned char *)puVar15 = 0;
      pbVar13 = (byte *)(iVar12 + 0x10021b98);
      do {
        bVar3 = *pbVar13;
        pbVar11 = pbVar13;
        while ((bVar3 != 0 && (bVar3 = pbVar11[1], bVar3 != 0))) {
          uVar8 = (uintptr_t)*pbVar11;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_10021b80)[local_8];
            do {
              pbVar2 = (byte *)((intptr_t)&DAT_10023a20 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          pbVar11 = pbVar11 + 2;
          bVar3 = *pbVar11;
        }
        local_8 = local_8 + 1;
        pbVar13 = pbVar13 + 8;
      } while (local_8 < 4);
      DAT_1002391c = 1;
      CodePage_10023898 = CodePage;
      DAT_10023b24 = _getmbcurmax(CodePage);
      DAT_10023910 = *(unsigned int *)(iVar12 + 0x10021b8c);
      DAT_10023914 = *(unsigned int *)(iVar12 + 0x10021b90);
      DAT_10023918 = *(unsigned int *)(iVar12 + 0x10021b94);
      goto LAB_10010912;
    }
    goto LAB_1001090d;
  }
  goto LAB_100107a8;
code_r0x100107c2:
  pUVar5 = pUVar5 + 0xc;
  iVar12 = iVar12 + 1;
  if (0x10021c77 < (intptr_t)pUVar5) goto code_r0x100107cd;
  goto LAB_100107be;
code_r0x100107cd:
  BVar6 = GetCPInfo(CodePage,&local_1c);
  uVar8 = 1;
  if (BVar6 == 1) {
    DAT_10023b24 = 0;
    puVar15 = &DAT_10023a20;
    for (iVar12 = 0x40; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar15 = 0;
      puVar15 = puVar15 + 1;
    }
    *(unsigned char *)puVar15 = 0;
    if (local_1c.MaxCharSize < 2) {
      DAT_1002391c = 0;
      CodePage_10023898 = CodePage;
    }
    else {
      CodePage_10023898 = CodePage;
      if (local_1c.LeadByte[0] != '\0') {
        pBVar9 = local_1c.LeadByte + 1;
        do {
          bVar3 = *pBVar9;
          if (bVar3 == 0) break;
          for (uVar7 = (uintptr_t)pBVar9[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
            pbVar13 = (byte *)((intptr_t)&DAT_10023a20 + uVar7 + 1);
            *pbVar13 = *pbVar13 | 4;
          }
          pBVar1 = pBVar9 + 1;
          pBVar9 = pBVar9 + 2;
        } while (*pBVar1 != 0);
      }
      do {
        pbVar13 = (byte *)((intptr_t)&DAT_10023a20 + uVar8 + 1);
        *pbVar13 = *pbVar13 | 8;
        uVar8 = uVar8 + 1;
      } while (uVar8 < 0xff);
      DAT_10023b24 = _getmbcurmax(CodePage);
      DAT_1002391c = 1;
    }
    DAT_10023910 = 0;
    DAT_10023914 = 0;
    DAT_10023918 = 0;
  }
  else {
    if (DAT_10023798 == 0) {
      uVar14 = 0xffffffff;
      goto LAB_1001091f;
    }
LAB_1001090d:
    _mbcp_reset();
  }
LAB_10010912:
  _build_case_tables();
LAB_100107a8:
  uVar14 = 0;
LAB_1001091f:
  _unlock_critical_section(0x19);
  return uVar14;
}



int __cdecl _getmbcp(int param_1)

{
  int iVar1;
  int bVar2;
  
  if (param_1 == -2) {
    DAT_10023798 = 1;
                    // WARNING: Could not recover jumptable at 0x10010948. Too many branches
                    // WARNING: Treating indirect jump as call
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_10023798 = 1;
                    // WARNING: Could not recover jumptable at 0x1001095d. Too many branches
                    // WARNING: Treating indirect jump as call
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = CodePage_100237cc;
  }
  DAT_10023798 = (uintptr_t)bVar2;
  return param_1;
}



#if 0
unsigned int __cdecl _getmbcurmax(int param_1)

{
  if (param_1 == 0x3a4) {
    return 0x411;
  }
  if (param_1 == 0x3a8) {
    return 0x804;
  }
  if (param_1 == 0x3b5) {
    return 0x412;
  }
  if (param_1 != 0x3b6) {
    return 0;
  }
  return 0x404;
}
#endif /* _getmbcurmax */




void _mbcp_reset(void)

{
  int iVar1;
  unsigned int *puVar2;
  
  puVar2 = &DAT_10023a20;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(unsigned char *)puVar2 = 0;
  CodePage_10023898 = 0;
  DAT_1002391c = 0;
  DAT_10023b24 = 0;
  DAT_10023910 = 0;
  DAT_10023914 = 0;
  DAT_10023918 = 0;
  return;
}



void _build_case_tables(void)

{
  byte *pbVar1;
  BOOL BVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  unsigned char uVar8;
  BYTE *pBVar9;
  CHAR *pCVar10;
  WORD local_518 [256];
  WCHAR local_318 [128];
  WCHAR local_218 [128];
  CHAR local_118 [256];
  struct _cpinfo local_18;
  
  BVar2 = GetCPInfo(CodePage_10023898,&local_18);
  if (BVar2 == 1) {
    uVar3 = 0;
    do {
      local_118[uVar3] = (CHAR)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    local_118[0] = ' ';
    if (local_18.LeadByte[0] != 0) {
      pBVar9 = local_18.LeadByte + 1;
      do {
        uVar3 = (uintptr_t)local_18.LeadByte[0];
        if (uVar3 <= *pBVar9) {
          uVar5 = (*pBVar9 - uVar3) + 1;
          uVar6 = uVar5 >> 2;
          pCVar10 = local_118 + uVar3;
          while (uVar6 != 0) {
            uVar6 = uVar6 - 1;
            builtin_memcpy(pCVar10,"    ",4);
            pCVar10 = pCVar10 + 4;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pCVar10 = ' ';
            pCVar10 = pCVar10 + 1;
          }
        }
        local_18.LeadByte[0] = pBVar9[1];
        pBVar9 = pBVar9 + 2;
      } while (local_18.LeadByte[0] != 0);
    }
    _getstringtype(1,local_118,0x100,local_518,CodePage_10023898,DAT_10023b24,0);
    _lcmapstring(DAT_10023b24,0x100,local_118,0x100,local_218,0x100,CodePage_10023898,0);
    _lcmapstring(DAT_10023b24,0x200,local_118,0x100,local_318,0x100,CodePage_10023898,0);
    uVar3 = 0;
    puVar7 = local_518;
    do {
      if ((*puVar7 & 1) == 0) {
        if ((*puVar7 & 2) != 0) {
          pbVar1 = (byte *)((intptr_t)&DAT_10023a20 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          uVar8 = *(unsigned char *)((intptr_t)local_318 + uVar3);
          goto LAB_10010ae0;
        }
        (&DAT_10023920)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((intptr_t)&DAT_10023a20 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        uVar8 = *(unsigned char *)((intptr_t)local_218 + uVar3);
LAB_10010ae0:
        (&DAT_10023920)[uVar3] = uVar8;
      }
      uVar3 = uVar3 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar3 < 0x100);
  }
  else {
    uVar3 = 0;
    do {
      if ((uVar3 < 0x41) || (0x5a < uVar3)) {
        if ((0x60 < uVar3) && (uVar3 < 0x7b)) {
          pbVar1 = (byte *)((intptr_t)&DAT_10023a20 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          cVar4 = (char)uVar3 + -0x20;
          goto LAB_10010b2a;
        }
        (&DAT_10023920)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((intptr_t)&DAT_10023a20 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        cVar4 = (char)uVar3 + ' ';
LAB_10010b2a:
        (&DAT_10023920)[uVar3] = cVar4;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  return;
}



void _initmbcp(void)

{
  if (DAT_10025028 == 0) {
    _setmbcp(-3);
    DAT_10025028 = 1;
  }
  return;
}



#if 0
int __cdecl __crtMessageBoxA(unsigned int param_1,unsigned int param_2,unsigned int param_3)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_1002379c == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_1002379c = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_1002379c != (FARPROC)0x0) {
        DAT_100237a0 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_100237a4 = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_10010bd4;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_10010bd4:
    if (DAT_100237a0 != (FARPROC)0x0) {
      iVar1 = (*DAT_100237a0)();
      if ((iVar1 != 0) && (DAT_100237a4 != (FARPROC)0x0)) {
        iVar1 = (*DAT_100237a4)(iVar1);
      }
    }
    iVar1 = (*DAT_1002379c)(iVar1,param_1,param_2,param_3);
  }
  return iVar1;
}
#endif /* __crtMessageBoxA */




// Library Function - Single Match
//  _strncpy
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uintptr_t)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((intptr_t)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((intptr_t)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uintptr_t)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x10010c4e;
      }
    }
    do {
      if (((uintptr_t)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_10010c8b;
        goto LAB_10010cf9;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((intptr_t)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((intptr_t)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x10010cf5:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_10010cf9:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_10010c8b;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x10010cf5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x10010cf5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x10010cf5;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x10010c4e:
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((intptr_t)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((intptr_t)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_10010c8b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((intptr_t)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}



#if 0
void __cdecl _dosmaperr(uint param_1)

{
  DWORD *pDVar1;
  uint *puVar2;
  int iVar3;
  
  pDVar1 = _doserrno_impl();
  iVar3 = 0;
  *pDVar1 = param_1;
  puVar2 = &DAT_10021c80;
  do {
    if (param_1 == *puVar2) {
      pDVar1 = _errno();
      *pDVar1 = *(DWORD *)(iVar3 * 8 + 0x10021c84);
      return;
    }
    puVar2 = puVar2 + 2;
    iVar3 = iVar3 + 1;
  } while ((intptr_t)puVar2 < 0x10021de8);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    pDVar1 = _errno();
    *pDVar1 = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    pDVar1 = _errno();
    *pDVar1 = 8;
    return;
  }
  pDVar1 = _errno();
  *pDVar1 = 0x16;
  return;
}
#endif /* _dosmaperr */




#if 0
DWORD * _errno(void)

{
  DWORD *pDVar1;
  
  pDVar1 = _getptd();
  return pDVar1 + 2;
}
#endif /* _errno */




DWORD * _doserrno_impl(void)

{
  DWORD *pDVar1;
  
  pDVar1 = (DWORD*)(intptr_t)_getptd();
  return pDVar1 + 3;
}



uint _allocfh(void)

{
  unsigned int *puVar1;
  unsigned int *puVar2;
  int *piVar3;
  uint uVar4;
  int local_8;
  int local_4;
  
  uVar4 = 0xffffffff;
  _lock_critical_section(0x12);
  local_8 = 0;
  local_4 = 0;
  piVar3 = &DAT_10024ec0;
  while (puVar2 = (unsigned int *)*piVar3, puVar1 = puVar2, puVar2 != (unsigned int *)0x0) {
    for (; puVar2 < puVar1 + 0x120; puVar2 = puVar2 + 9) {
      if ((*(byte *)(puVar2 + 1) & 1) == 0) {
        if (puVar2[2] == 0) {
          _lock_critical_section(0x11);
          if (puVar2[2] == 0) {
            InitializeCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
            puVar2[2] = puVar2[2] + 1;
          }
          _unlock_critical_section(0x11);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
        if ((*(byte *)(puVar2 + 1) & 1) == 0) {
          *puVar2 = 0xffffffff;
          uVar4 = ((intptr_t)puVar2 - *piVar3) / 0x24 + local_4;
          if (uVar4 != 0xffffffff) goto LAB_10010ea5;
          break;
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(puVar2 + 3));
      }
      puVar1 = (unsigned int *)*piVar3;
    }
    local_4 = local_4 + 0x20;
    piVar3 = piVar3 + 1;
    local_8 = local_8 + 1;
    if (0x10024fbf < (intptr_t)piVar3) goto LAB_10010ea5;
  }
  puVar2 = _malloc(0x480);
  if (puVar2 != (unsigned int *)0x0) {
    uNumber_10024ffc = uNumber_10024ffc + 0x20;
    (&DAT_10024ec0)[local_8] = (intptr_t)puVar2;
    puVar1 = puVar2;
    for (; puVar2 < puVar1 + 0x120; puVar2 = puVar2 + 9) {
      *(unsigned char *)(puVar2 + 1) = 0;
      *puVar2 = 0xffffffff;
      puVar2[2] = 0;
      *(unsigned char *)((intptr_t)puVar2 + 5) = 10;
      puVar1 = (unsigned int *)(&DAT_10024ec0)[local_8];
    }
    uVar4 = local_8 << 5;
    _lock_fh(uVar4);
  }
LAB_10010ea5:
  _unlock_critical_section(0x12);
  return uVar4;
}



unsigned int __cdecl _set_osfhnd(uint param_1,HANDLE param_2)

{
  DWORD *pDVar1;
  int iVar2;
  DWORD nStdHandle;
  
  if (param_1 < uNumber_10024ffc) {
    iVar2 = (param_1 & 0x1f) * 0x24;
    if (*(int *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + iVar2) == -1) {
      if (DAT_10023558 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_10010f0f;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,param_2);
      }
LAB_10010f0f:
      *(HANDLE *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + iVar2) = param_2;
      return 0;
    }
  }
  pDVar1 = _errno();
  *pDVar1 = 9;
  pDVar1 = _doserrno_impl();
  *pDVar1 = 0;
  return 0xffffffff;
}



unsigned int __cdecl _freefd(uint param_1)

{
  int *piVar1;
  DWORD *pDVar2;
  int iVar3;
  DWORD nStdHandle;
  
  if (param_1 < uNumber_10024ffc) {
    iVar3 = (param_1 & 0x1f) * 0x24;
    piVar1 = (int *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + iVar3);
    if (((*(byte *)(piVar1 + 1) & 1) != 0) && (*piVar1 != -1)) {
      if (DAT_10023558 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_10010f8e;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_10010f8e:
      *(unsigned int *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + iVar3) = 0xffffffff;
      return 0;
    }
  }
  pDVar2 = _errno();
  *pDVar2 = 9;
  pDVar2 = _doserrno_impl();
  *pDVar2 = 0;
  return 0xffffffff;
}



#if 0
unsigned int __cdecl _get_osfhandle(uint param_1)

{
  DWORD *pDVar1;
  
  if ((param_1 < uNumber_10024ffc) &&
     ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    return *(unsigned int *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + (param_1 & 0x1f) * 0x24);
  }
  pDVar1 = _errno();
  *pDVar1 = 9;
  pDVar1 = _doserrno_impl();
  *pDVar1 = 0;
  return 0xffffffff;
}
#endif /* _get_osfhandle */




uint __cdecl _open_osfhandle(HANDLE param_1,uint param_2)

{
  DWORD DVar1;
  uint uVar2;
  DWORD *pDVar3;
  byte bVar4;
  
  bVar4 = 0;
  if ((param_2 & 8) != 0) {
    bVar4 = 0x20;
  }
  if ((param_2 & 0x4000) != 0) {
    bVar4 = bVar4 | 0x80;
  }
  if ((param_2 & 0x80) != 0) {
    bVar4 = bVar4 | 0x10;
  }
  DVar1 = GetFileType(param_1);
  if (DVar1 == 0) {
    DVar1 = GetLastError();
    _dosmaperr(DVar1);
  }
  else {
    if (DVar1 == 2) {
      bVar4 = bVar4 | 0x40;
    }
    else if (DVar1 == 3) {
      bVar4 = bVar4 | 8;
    }
    uVar2 = _allocfh();
    if (uVar2 != 0xffffffff) {
      _set_osfhnd(uVar2,param_1);
      *(byte *)((&DAT_10024ec0)[(intptr_t)uVar2 >> 5] + 4 + (uVar2 & 0x1f) * 0x24) = bVar4 | 1;
      _unlock_fh(uVar2);
      return uVar2;
    }
    pDVar3 = _errno();
    *pDVar3 = 0x18;
    pDVar3 = _doserrno_impl();
    *pDVar3 = 0;
  }
  return 0xffffffff;
}



void __cdecl _lock_fh(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (param_1 & 0x1f) * 0x24;
  iVar1 = (&DAT_10024ec0)[(intptr_t)param_1 >> 5] + iVar2;
  if (*(int *)(iVar1 + 8) == 0) {
    _lock_critical_section(0x11);
    if (*(int *)(iVar1 + 8) == 0) {
      InitializeCriticalSection((LPCRITICAL_SECTION)(iVar1 + 0xc));
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    _unlock_critical_section(0x11);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 0xc + iVar2));
  return;
}



void __cdecl _unlock_fh(uint param_1)

{
  LeaveCriticalSection
            ((LPCRITICAL_SECTION)
             ((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 0xc + (param_1 & 0x1f) * 0x24));
  return;
}



int __cdecl _fflush(int *param_1)

{
  int iVar1;
  
  _flush((intptr_t)param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(byte *)((intptr_t)param_1 + 0xd) & 0x40) != 0) {
    iVar1 = _commit(param_1[4]);
    return -(uintptr_t)(iVar1 != 0);
  }
  return 0;
}



#if 0
unsigned int __cdecl _flush(int *param_1)

{
  uint uVar1;
  unsigned int uVar2;
  uint uVar3;
  
  uVar2 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    uVar3 = *param_1 - param_1[2];
    if (0 < (intptr_t)uVar3) {
      uVar1 = _write(param_1[4],(char *)param_1[2],uVar3);
      if (uVar1 == uVar3) {
        if ((param_1[3] & 0x80U) != 0) {
          param_1[3] = param_1[3] & 0xfffffffd;
        }
      }
      else {
        param_1[3] = param_1[3] | 0x20;
        uVar2 = 0xffffffff;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar2;
}
#endif /* _flush */




int __cdecl _flushall(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  _lock_critical_section(2);
  iVar4 = 0;
  if (0 < DAT_10024ea0) {
    do {
      iVar2 = *(int *)(DAT_10023b4c + iVar4 * 4);
      if ((iVar2 != 0) && ((*(byte *)(iVar2 + 0xc) & 0x83) != 0)) {
        _lock_file(iVar4,iVar2);
        piVar1 = *(int **)(DAT_10023b4c + iVar4 * 4);
        if ((piVar1[3] & 0x83U) != 0) {
          if (param_1 == 1) {
            iVar2 = _fflush(piVar1);
            if (iVar2 != -1) {
              iVar3 = iVar3 + 1;
            }
          }
          else if ((param_1 == 0) && ((piVar1[3] & 2U) != 0)) {
            iVar2 = _fflush(piVar1);
            if (iVar2 == -1) {
              iVar5 = -1;
            }
          }
        }
        _unlock_file(iVar4,*(int *)(DAT_10023b4c + iVar4 * 4));
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_10024ea0);
  }
  _unlock_critical_section(2);
  if (param_1 != 1) {
    iVar3 = iVar5;
  }
  return iVar3;
}



uint * __cdecl setlocale(int param_1,uint *param_2)

{
  uint *puVar1;
  byte *pbVar2;
  size_t sVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  unsigned char **ppuVar7;
  unsigned int *puVar8;
  uint local_8c [33];
  size_t local_8;
  
  iVar6 = 0;
  if ((param_1 < 0) || (5 < param_1)) {
    return (uint *)0x0;
  }
  _lock_critical_section(0x13);
  DAT_10023884 = DAT_10023884 + 1;
  while (DAT_10023894 != 0) {
    Sleep(1);
  }
  if (param_1 == 0) {
    local_8 = 1;
    param_1 = 0;
    if (param_2 == (uint *)0x0) {
LAB_10011528:
      puVar1 = (uint*)(intptr_t)_getlocale_all();
    }
    else {
      if ((((char)*param_2 == 'L') && (*(char *)((intptr_t)param_2 + 1) == 'C')) &&
         (*(char *)((intptr_t)param_2 + 2) == '_')) {
        pbVar2 = strpbrk((const char*)param_2,(const char*)&DAT_1001c54c);
        puVar1 = param_2;
        while (((pbVar2 != (byte *)0x0 && (local_8 = (intptr_t)pbVar2 - (intptr_t)puVar1, local_8 != 0)) &&
               (*pbVar2 != 0x3b))) {
          param_2 = (uint *)0x1;
          ppuVar7 = &PTR_s_LC_COLLATE_10021f04;
          do {
            iVar6 = _strncmp(*ppuVar7,(char *)puVar1,local_8);
            if ((iVar6 == 0) && (sVar3 = _strlen(*ppuVar7), local_8 == sVar3)) break;
            param_2 = (uint *)((intptr_t)param_2 + 1);
            ppuVar7 = ppuVar7 + 3;
          } while ((intptr_t)ppuVar7 < 0x10021f35);
          pbVar2 = pbVar2 + 1;
          sVar3 = strcspn((const char*)(intptr_t)pbVar2,(const char*)&DAT_1001c548);
          if ((sVar3 == 0) && (*pbVar2 != 0x3b)) break;
          if ((intptr_t)param_2 < 6) {
            _strncpy((char *)local_8c,(char *)pbVar2,sVar3);
            *(unsigned char *)((intptr_t)local_8c + sVar3) = 0;
            iVar6 = _setlocalloc((intptr_t)param_2,local_8c);
            if (iVar6 != 0) {
              param_1 = param_1 + 1;
            }
          }
          if ((pbVar2[sVar3] == 0) || (puVar1 = (uint *)(pbVar2 + sVar3 + 1), (byte)*puVar1 == 0))
          goto LAB_10011492;
          pbVar2 = strpbrk((const char*)puVar1,(const char*)&DAT_1001c54c);
        }
        _unlock_critical_section(0x13);
        puVar1 = (uint *)0x0;
        goto LAB_10011537;
      }
      puVar4 = _install_locale(param_2,local_8c,(unsigned int *)0x0,(unsigned int *)0x0);
      puVar1 = (uint *)0x0;
      if (puVar4 != (uint *)0x0) {
        puVar8 = &DAT_10021efc;
        do {
          if ((LPVOID *)puVar8 != &DAT_10021efc) {
            iVar5 = _strcmp((char *)local_8c,(char *)*puVar8);
            if ((iVar5 == 0) || (iVar5 = _setlocalloc(iVar6,local_8c), iVar5 != 0)) {
              param_1 = param_1 + 1;
            }
            else {
              local_8 = 0;
            }
          }
          puVar8 = puVar8 + 3;
          iVar6 = iVar6 + 1;
        } while ((intptr_t)puVar8 < 0x10021f39);
        if (local_8 == 0) {
LAB_10011492:
          if (param_1 != 0) goto LAB_10011528;
          puVar1 = (uint *)0x0;
        }
        else {
          puVar1 = (uint*)(intptr_t)_getlocale_all();
          free(DAT_10021efc);
          DAT_10021efc = (LPVOID)0x0;
        }
      }
    }
  }
  else if (param_2 == (uint *)0x0) {
    puVar1 = ((uint*)&DAT_10021efc)[param_1 * 3];
  }
  else {
    puVar1 = (uint *)_setlocalloc(param_1,param_2);
  }
  _unlock_critical_section(0x13);
LAB_10011537:
  DAT_10023884 = DAT_10023884 + -1;
  return puVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
unsigned int __cdecl _setlocalloc(int param_1,uint *param_2)

{
  uint *puVar1;
  unsigned char *puVar2;
  uint *puVar3;
  size_t sVar4;
  uint *puVar5;
  int iVar6;
  uint local_a8 [33];
  unsigned int local_24 [2];
  UINT local_1c;
  uint local_18;
  ushort local_14 [4];
  unsigned int *local_c;
  UINT local_8;
  
  puVar3 = _install_locale(param_2,local_a8,(unsigned int *)local_14,&local_1c);
  if (puVar3 != (uint *)0x0) {
    sVar4 = _strlen((char *)local_a8);
    puVar3 = _malloc(sVar4 + 1);
    if (puVar3 != (uint *)0x0) {
      puVar1 = (uint *)(&DAT_100237b4 + param_1 * 4);
      puVar2 = (unsigned char *)(&DAT_10021efc)[param_1 * 3];
      local_18 = *puVar1;
      local_c = (unsigned int *)(&DAT_1002380c + param_1 * 6);
      memmove(local_24,local_c,6);
      local_8 = CodePage_100237cc;
      puVar5 = strcpy(puVar3,local_a8);
      (&DAT_10021efc)[param_1 * 3] = puVar5;
      *puVar1 = (uintptr_t)local_14[0];
      memmove(local_c,(unsigned int *)local_14,6);
      if (param_1 == 2) {
        CodePage_100237cc = local_1c;
      }
      if (param_1 == 1) {
        _DAT_100237d0 = local_1c;
      }
      iVar6 = ((*(void (**)(void)))&DAT_10021f00 + param_1 * 0xc)();
      if (iVar6 == 0) {
        if (puVar2 != &DAT_10021de8) {
          free(puVar2);
        }
        return (&DAT_10021efc)[param_1 * 3];
      }
      (&DAT_10021efc)[param_1 * 3] = puVar2;
      free(puVar3);
      *puVar1 = local_18;
      CodePage_100237cc = local_8;
    }
  }
  return 0;
}
#endif /* _setlocalloc */




#if 0
uint * _getlocale_all(void)

{
  int bVar1;
  int iVar2;
  unsigned char **ppuVar3;
  unsigned char **ppuVar4;
  
  bVar1 = true;
  if (DAT_10021efc == (uint *)0x0) {
    DAT_10021efc = _malloc(0x351);
  }
  *(unsigned char *)DAT_10021efc = 0;
  _strcat_multi(DAT_10021efc,3);
  ppuVar3 = &PTR_DAT_10021f08;
  do {
    strcat(DAT_10021efc,(char*)&DAT_1001c548);
    ppuVar4 = ppuVar3 + 3;
    iVar2 = _strcmp(*ppuVar3,ppuVar3[3]);
    if (iVar2 != 0) {
      bVar1 = false;
    }
    _strcat_multi(DAT_10021efc,3);
    ppuVar3 = ppuVar4;
  } while ((intptr_t)ppuVar4 < 0x10021f38);
  if (!bVar1) {
    return DAT_10021efc;
  }
  free(DAT_10021efc);
  DAT_10021efc = (uint *)0x0;
  return (uint *)PTR_DAT_10021f14;
}
#endif /* _getlocale_all */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

#if 0
uint * __cdecl _install_locale(uint *param_1,uint *param_2,unsigned int *param_3,unsigned int *param_4)

{
  int iVar1;
  uint *puVar2;
  uint local_8c [34];
  
  if (param_1 == (uint *)0x0) {
LAB_100117c2:
    puVar2 = (uint *)0x0;
  }
  else {
    if (((char)*param_1 == 'C') && (*(char *)((intptr_t)param_1 + 1) == '\0')) {
      *(unsigned char *)((intptr_t)param_2 + 1) = 0;
      *(unsigned char *)param_2 = 0x43;
      if (param_3 != (unsigned int *)0x0) {
        *(unsigned short *)param_3 = 0;
        *(unsigned short *)((intptr_t)param_3 + 2) = 0;
        *(unsigned short *)(param_3 + 1) = 0;
      }
      if (param_4 == (unsigned int *)0x0) {
        return param_2;
      }
      *param_4 = 0;
      return param_2;
    }
    iVar1 = _strcmp(&DAT_10021e70,(char *)param_1);
    if ((iVar1 != 0) && (iVar1 = _strcmp(&DAT_10021dec,(char *)param_1), iVar1 != 0)) {
      puVar2 = param_1;
      iVar1 = _parse_locale_fields((char *)local_8c,(byte *)param_1);
      if ((iVar1 != 0) ||
         (iVar1 = _resolve_locale(puVar2,(char *)local_8c,(unsigned short *)&DAT_100237a8,(intptr_t)local_8c)
         , iVar1 == 0)) goto LAB_100117c2;
      _DAT_100237b0 = (uintptr_t)DAT_100237ac;
      _compose_locale_str((uint *)&DAT_10021e70,local_8c);
      if ((char)*param_1 == '\0') {
        param_1 = (uint *)&DAT_10021e70;
      }
      strcpy((char*)&DAT_10021dec,param_1);
    }
    if (param_3 != (unsigned int *)0x0) {
      memmove(param_3,(unsigned int *)&DAT_100237a8,6);
    }
    if (param_4 != (unsigned int *)0x0) {
      memmove(param_4,(unsigned int *)&DAT_100237b0,4);
    }
    strcpy(param_2,(char*)&DAT_10021e70);
    puVar2 = (uint *)&DAT_10021e70;
  }
  return puVar2;
}
#endif /* _install_locale */




void __cdecl _strcat_multi(uint *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  if (0 < param_2) {
    piVar2 = &param_2;
    iVar3 = param_2;
    do {
      piVar1 = piVar2 + 1;
      piVar2 = piVar2 + 1;
      strcat((char*)param_1,(char*)*piVar1);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}



#if 0
unsigned int __cdecl _parse_locale_fields(char *param_1,byte *param_2)

{
  byte bVar1;
  size_t _Count;
  byte *_Source;
  char *_Dest;
  
  _Source = param_2;
  _memset(param_1,0,0x88);
  if (*param_2 != 0) {
    if ((*param_2 != 0x2e) || (param_2[1] == 0)) {
      param_2 = (byte *)0x0;
      while( true ) {
        _Count = strcspn(_Source,&DAT_1001c554);
        if (_Count == 0) {
          return 0xffffffff;
        }
        bVar1 = _Source[_Count];
        if (param_2 == (byte *)0x0) {
          if (0x3f < (intptr_t)_Count) {
            return 0xffffffff;
          }
          _Dest = param_1;
          if (bVar1 == 0x2e) {
            return 0xffffffff;
          }
        }
        else if (param_2 == (byte *)0x1) {
          if (0x3f < (intptr_t)_Count) {
            return 0xffffffff;
          }
          if (bVar1 == 0x5f) {
            return 0xffffffff;
          }
          _Dest = param_1 + 0x40;
        }
        else {
          if (param_2 != (byte *)0x2) {
            return 0xffffffff;
          }
          if ((bVar1 != 0) && (bVar1 != 0x2c)) {
            return 0xffffffff;
          }
          _Dest = param_1 + 0x80;
        }
        _strncpy(_Dest,(char *)_Source,_Count);
        if (bVar1 == 0x2c) {
          return 0;
        }
        if (bVar1 == 0) break;
        param_2 = param_2 + 1;
        _Source = _Source + _Count + 1;
      }
      return 0;
    }
    strcpy((char*)(param_1 + 0x80),(char*)(param_2 + 1));
  }
  return 0;
}
#endif /* _parse_locale_fields */




void __cdecl _compose_locale_str(uint *param_1,uint *param_2)

{
  strcpy((char*)param_1,(const char*)param_2);
  if ((char)param_2[0x10] != '\0') {
    _strcat_multi(param_1,2);
  }
  if ((char)param_2[0x20] != '\0') {
    _strcat_multi(param_1,2);
  }
  return;
}



#if 0
int __thiscall atoi(void *_this)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  unsigned char *puVar6;
  
  while( true ) {
    if (cbMultiByte_10021b40 < 2) {
      uVar1 = (byte)PTR_DAT_10021780[(uintptr_t)*param_1 * 2] & 8;
      _this = PTR_DAT_10021780;
    }
    else {
      puVar6 = (unsigned char *)0x8;
      uVar1 = iswctype(_this, (uintptr_t)*param_1);
      _this = puVar6;
    }
    if (uVar1 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar1 = (uintptr_t)*param_1;
  pbVar5 = param_1 + 1;
  if ((uVar1 == 0x2d) || (uVar4 = uVar1, uVar1 == 0x2b)) {
    uVar4 = (uintptr_t)*pbVar5;
    pbVar5 = param_1 + 2;
  }
  iVar3 = 0;
  while( true ) {
    if (cbMultiByte_10021b40 < 2) {
      uVar2 = (byte)PTR_DAT_10021780[uVar4 * 2] & 4;
    }
    else {
      puVar6 = (unsigned char *)0x4;
      uVar2 = iswctype(_this, uVar4);
      _this = puVar6;
    }
    if (uVar2 == 0) break;
    iVar3 = (uVar4 - 0x30) + iVar3 * 10;
    uVar4 = (uintptr_t)*pbVar5;
    pbVar5 = pbVar5 + 1;
  }
  if (uVar1 == 0x2d) {
    iVar3 = -iVar3;
  }
  return iVar3;
}
#endif /* atoi */




#if 0
int __cdecl getenv(unsigned char *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  int *piVar3;
  
  if (((DAT_10025014 != 0) &&
      ((DAT_10023500 != (int *)0x0 ||
       (((DAT_10023508 != 0 && (iVar1 = _wide_env_sync(), iVar1 == 0)) &&
        (DAT_10023500 != (int *)0x0)))))) && (piVar3 = DAT_10023500, param_1 != (unsigned char *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; (char *)*piVar3 != (char *)0x0; piVar3 = piVar3 + 1) {
      sVar2 = _strlen((char *)*piVar3);
      if (((_MaxCount < sVar2) && (((unsigned char *)*piVar3)[_MaxCount] == '=')) &&
         (iVar1 = __mbsnbicoll((unsigned char *)*piVar3,param_1,_MaxCount), iVar1 == 0)) {
        return *piVar3 + 1 + _MaxCount;
      }
    }
  }
  return 0;
}
#endif /* getenv */




int __cdecl signal(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  DWORD *pDVar5;
  unsigned int *puVar6;
  uint uVar7;
  BOOL BVar8;
  DWORD DVar9;
  
  if ((param_2 != 4) && (param_2 != 3)) {
    if ((param_1 == 2) || (((param_1 == 0x15 || (param_1 == 0x16)) || (param_1 == 0xf)))) {
      _lock_critical_section(1);
      if (((param_1 == 2) || (param_1 == 0x15)) && (DAT_100237e4 == 0)) {
        BVar8 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&HandlerRoutine_10011ceb,1);
        if (BVar8 != 1) {
          DVar9 = GetLastError();
          pDVar5 = _doserrno_impl();
          *pDVar5 = DVar9;
          _unlock_critical_section(1);
          goto LAB_10011c9f;
        }
        DAT_100237e4 = 1;
      }
      iVar4 = DAT_100237e0;
      iVar3 = DAT_100237dc;
      iVar2 = DAT_100237d8;
      iVar1 = DAT_100237d4;
      if (param_1 == 2) {
        DAT_100237d4 = param_2;
        param_2 = iVar1;
      }
      else if (param_1 == 0xf) {
        DAT_100237e0 = param_2;
        param_2 = iVar4;
      }
      else if (param_1 == 0x15) {
        DAT_100237d8 = param_2;
        param_2 = iVar2;
      }
      else if (param_1 == 0x16) {
        DAT_100237dc = param_2;
        param_2 = iVar3;
      }
      _unlock_critical_section(1);
      return param_2;
    }
    if (((param_1 == 8) || (param_1 == 4)) || (param_1 == 0xb)) {
      pDVar5 = (DWORD*)(intptr_t)_getptd();
      if ((unsigned char *)pDVar5[0x14] == &DAT_10021990) {
        puVar6 = _malloc(DAT_10021a10);
        pDVar5[0x14] = (uintptr_t)puVar6;
        if (puVar6 == (unsigned int *)0x0) goto LAB_10011c9f;
        memmove(puVar6,(unsigned int *)&DAT_10021990,DAT_10021a10);
      }
      uVar7 = _siglookup(param_1,pDVar5[0x14]);
      if (uVar7 != 0) {
        iVar1 = *(int *)(uVar7 + 8);
        do {
          if (*(int *)(uVar7 + 4) != param_1) {
            return iVar1;
          }
          *(int *)(uVar7 + 8) = param_2;
          uVar7 = uVar7 + 0xc;
        } while (uVar7 < pDVar5[0x14] + DAT_10021a14 * 0xc);
        return iVar1;
      }
    }
  }
LAB_10011c9f:
  pDVar5 = _errno();
  *pDVar5 = 0x16;
  return -1;
}



#if 0
unsigned int __cdecl raise(DWORD *param_1)

{
  int bVar1;
  DWORD *pDVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  void *pcVar6;
  unsigned int *puVar7;
  DWORD local_10;
  DWORD local_c;
  
  bVar1 = false;
  if (param_1 == (DWORD *)0x2) {
    puVar7 = &DAT_100237d4;
    pcVar6 = DAT_100237d4;
LAB_10011dd3:
    bVar1 = true;
    _lock_critical_section(1);
    pDVar2 = param_1;
  }
  else {
    if (((param_1 != (DWORD *)0x4) && (param_1 != (DWORD *)0x8)) && (param_1 != (DWORD *)0xb)) {
      if (param_1 == (DWORD *)0xf) {
        puVar7 = &DAT_100237e0;
        pcVar6 = DAT_100237e0;
      }
      else if (param_1 == (DWORD *)0x15) {
        puVar7 = &DAT_100237d8;
        pcVar6 = DAT_100237d8;
      }
      else {
        if (param_1 != (DWORD *)0x16) {
          return 0xffffffff;
        }
        puVar7 = &DAT_100237dc;
        pcVar6 = DAT_100237dc;
      }
      goto LAB_10011dd3;
    }
    pDVar2 = _getptd();
    uVar3 = _siglookup((intptr_t)param_1,pDVar2[0x14]);
    puVar7 = (unsigned int *)(uVar3 + 8);
    pcVar6 = (void *)*puVar7;
  }
  if (pcVar6 == (void *)0x1) {
    if (!bVar1) {
      return 0;
    }
    _unlock_critical_section(1);
    return 0;
  }
  if (pcVar6 == (void *)0x0) {
    if (bVar1) {
      _unlock_critical_section(1);
    }
                    // WARNING: Subroutine does not return
    __exit(3);
  }
  if (((param_1 == (DWORD *)0x8) || (param_1 == (DWORD *)0xb)) || (param_1 == (DWORD *)0x4)) {
    local_c = pDVar2[0x15];
    pDVar2[0x15] = 0;
    if (param_1 == (DWORD *)0x8) {
      local_10 = pDVar2[0x16];
      pDVar2[0x16] = 0x8c;
      goto LAB_10011e47;
    }
  }
  else {
LAB_10011e47:
    if (param_1 == (DWORD *)0x8) {
      if (DAT_10021a08 < DAT_10021a0c + DAT_10021a08) {
        iVar4 = DAT_10021a08 * 0xc;
        iVar5 = DAT_10021a08;
        do {
          iVar4 = iVar4 + 0xc;
          *(unsigned int *)((pDVar2[0x14] - 4) + iVar4) = 0;
          iVar5 = iVar5 + 1;
        } while (iVar5 < DAT_10021a0c + DAT_10021a08);
      }
      goto LAB_10011e85;
    }
  }
  *puVar7 = 0;
LAB_10011e85:
  if (bVar1) {
    _unlock_critical_section(1);
  }
  if (param_1 == (DWORD *)0x8) {
    (*pcVar6)(8,pDVar2[0x16]);
  }
  else {
    (*pcVar6)(param_1);
    if ((param_1 != (DWORD *)0xb) && (param_1 != (DWORD *)0x4)) {
      return 0;
    }
  }
  pDVar2[0x15] = local_c;
  if (param_1 == (DWORD *)0x8) {
    pDVar2[0x16] = local_10;
  }
  return 0;
}
#endif /* raise */




#if 0
uint __cdecl _siglookup(int param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2;
  if (*(int *)(param_2 + 4) != param_1) {
    uVar3 = param_2;
    do {
      uVar2 = uVar3 + 0xc;
      if (param_2 + DAT_10021a14 * 0xc <= uVar2) break;
      piVar1 = (int *)(uVar3 + 0x10);
      uVar3 = uVar2;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_10021a14 * 0xc <= uVar2) || (*(int *)(uVar2 + 4) != param_1)) {
    uVar2 = 0;
  }
  return uVar2;
}
#endif /* _siglookup */




BOOL __cdecl
_getstringtype(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
              int param_7)

{
  unsigned char *puVar1;
  BOOL BVar2;
  int iVar3;
  WORD local_20 [2];
  unsigned char *local_1c;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001c568;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  local_1c = (unsigned char*)&uStack00000000;
  iVar3 = DAT_100237e8;
  pExceptionList = &local_14;
  puVar1 = (unsigned char*)&uStack00000000;
  if (DAT_100237e8 == 0) {
    pExceptionList = &local_14;
    BVar2 = GetStringTypeW(1,(LPCWSTR)&lpSrcStr_1001c564,1,local_20);
    iVar3 = 1;
    puVar1 = local_1c;
    if (BVar2 == 0) {
      BVar2 = GetStringTypeA(0,1,(LPCSTR)&lpSrcStr_1001c560,1,local_20);
      if (BVar2 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      iVar3 = 2;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  DAT_100237e8 = iVar3;
  if (DAT_100237e8 != 2) {
    if (DAT_100237e8 == 1) {
      if (param_5 == 0) {
        param_5 = CodePage_100237cc;
      }
      iVar3 = MultiByteToWideChar(param_5,(-(uintptr_t)(param_7 != 0) & 8) + 1,param_2,param_3,
                                  (LPWSTR)0x0,0);
      if (iVar3 != 0) {
        local_8 = 0;
        _alloca_probe();
        local_1c = (unsigned char*)&uStack00000000;
        _memset(&uStack00000000,0,iVar3 * 2);
        local_8 = 0xffffffff;
        if ((&uStack00000000 != (unsigned char *)0x38) &&
           (iVar3 = MultiByteToWideChar(param_5,1,param_2,param_3,(LPWSTR)&uStack00000000,iVar3),
           iVar3 != 0)) {
          BVar2 = GetStringTypeW(param_1,(LPCWSTR)&uStack00000000,iVar3,param_4);
          pExceptionList = local_14;
          return BVar2;
        }
      }
    }
    pExceptionList = local_14;
    return 0;
  }
  if (param_6 == 0) {
    param_6 = DAT_100237bc;
  }
  BVar2 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
  pExceptionList = local_14;
  return BVar2;
}



int __cdecl
_lcmapstring(LCID param_1,uint param_2,char *param_3,int param_4,LPWSTR param_5,int param_6,
            UINT param_7,int param_8)

{
  int iVar1;
  int iVar2;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001c578;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  pExceptionList = &local_14;
  if (DAT_100237ec == 0) {
    pExceptionList = &local_14;
    iVar1 = LCMapStringW(0,0x100,(LPCWSTR)&lpSrcStr_1001c564,1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,(LPCSTR)&lpSrcStr_1001c560,1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      DAT_100237ec = 2;
    }
    else {
      DAT_100237ec = 1;
    }
  }
  if (0 < param_4) {
    param_4 = _strnlen(param_3,param_4);
  }
  if (DAT_100237ec == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,param_4,(LPSTR)param_5,param_6);
    pExceptionList = local_14;
    return iVar1;
  }
  if (DAT_100237ec == 1) {
    if (param_7 == 0) {
      param_7 = CodePage_100237cc;
    }
    iVar1 = MultiByteToWideChar(param_7,(-(uintptr_t)(param_8 != 0) & 8) + 1,param_3,param_4,(LPWSTR)0x0,
                                0);
    if (iVar1 != 0) {
      local_8 = 0;
      _alloca_probe();
      local_8 = 0xffffffff;
      if ((&uStack00000000 != (unsigned char *)0x3c) &&
         (iVar2 = MultiByteToWideChar(param_7,1,param_3,param_4,(LPWSTR)&uStack00000000,iVar1),
         iVar2 != 0)) {
        iVar2 = LCMapStringW(param_1,param_2,(LPCWSTR)&uStack00000000,iVar1,(LPWSTR)0x0,0);
        if (iVar2 != 0) {
          if ((param_2 & 0x400) == 0) {
            local_8 = 1;
            _alloca_probe();
            local_8 = 0xffffffff;
            if (&uStack00000000 == (unsigned char *)0x3c) {
              pExceptionList = local_14;
              return 0;
            }
            iVar1 = LCMapStringW(param_1,param_2,(LPCWSTR)&uStack00000000,iVar1,
                                 (LPWSTR)&uStack00000000,iVar2);
            if (iVar1 == 0) {
              pExceptionList = local_14;
              return 0;
            }
            if (param_6 == 0) {
              param_6 = 0;
              param_5 = (LPWSTR)0x0;
            }
            iVar2 = WideCharToMultiByte(param_7,0x220,(LPCWSTR)&uStack00000000,iVar2,(LPSTR)param_5
                                        ,param_6,(LPCSTR)0x0,(LPBOOL)0x0);
            iVar1 = iVar2;
          }
          else {
            if (param_6 == 0) {
              pExceptionList = local_14;
              return iVar2;
            }
            if (param_6 < iVar2) {
              pExceptionList = local_14;
              return 0;
            }
            iVar1 = LCMapStringW(param_1,param_2,(LPCWSTR)&uStack00000000,iVar1,param_5,param_6);
          }
          if (iVar1 != 0) {
            pExceptionList = local_14;
            return iVar2;
          }
        }
      }
    }
  }
  pExceptionList = local_14;
  return 0;
}



int __cdecl _strnlen(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 != '\0') {
    return param_2;
  }
  return (intptr_t)pcVar1 - (intptr_t)param_1;
}



#if 0
unsigned int __cdecl _add_carry(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  unsigned int uVar2;
  
  uVar2 = 0;
  uVar1 = param_1 + param_2;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}
#endif /* _add_carry */




// Library Function - Single Match
//  ___add_12
// 
// Library: Visual Studio 2003 Release

void __cdecl ___add_12(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = _add_carry(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = _add_carry(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = _add_carry(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  _add_carry(param_1[2],param_2[2],param_1 + 2);
  return;
}



void __cdecl _ldshl1(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}



void __cdecl _ldshr1(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}



void __cdecl _digits2ld(char *param_1,int param_2,uint *param_3)

{
  uint *puVar1;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  puVar1 = param_3;
  local_8 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      _ldshl1(puVar1);
      _ldshl1(puVar1);
      ___add_12(puVar1,&local_14);
      _ldshl1(puVar1);
      local_10 = 0;
      local_c = 0;
      local_14 = (uintptr_t)*param_1;
      ___add_12(puVar1,&local_14);
      param_1 = param_1 + 1;
      param_3 = (uint *)((intptr_t)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  while (puVar1[2] == 0) {
    puVar1[2] = puVar1[1] >> 0x10;
    local_8 = local_8 + 0xfff0;
    puVar1[1] = *puVar1 >> 0x10 | puVar1[1] << 0x10;
    *puVar1 = *puVar1 << 0x10;
  }
  while ((puVar1[2] & 0x8000) == 0) {
    _ldshl1(puVar1);
    local_8 = local_8 + 0xffff;
  }
  *(unsigned short *)((intptr_t)puVar1 + 10) = (unsigned short)local_8;
  return;
}
#if 0 /* CRT: _strtod_core */



unsigned int __thiscall
_strtod_core(void *_this,ushort *param_1,int *param_2,byte *param_3,int param_4,int param_5,
            int param_6,int param_7)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  byte bVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  char local_60 [23];
  char local_49;
  ushort local_44;
  unsigned short uStack_42;
  unsigned short uStack_40;
  byte *local_3e;
  ushort local_3a;
  int local_34;
  int local_30;
  unsigned int local_2c;
  int local_28;
  int local_24;
  byte *local_20;
  int local_1c;
  unsigned int local_18;
  int local_14;
  char *local_10;
  int local_c;
  uint local_8;
  
  local_10 = local_60;
  local_2c = 0;
  local_1c = 1;
  local_8 = 0;
  local_14 = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0;
  local_34 = 0;
  local_20 = (byte *)0x0;
  local_c = 0;
  local_18 = 0;
  pbVar8 = param_3;
  while( true ) {
    bVar6 = *pbVar8;
    _this = (void *)CONCAT31((int3)((uintptr_t)_this >> 8),bVar6);
    if ((((bVar6 != 0x20) && (bVar6 != 9)) && (bVar6 != 10)) && (bVar6 != 0xd)) break;
    pbVar8 = pbVar8 + 1;
  }
  iVar1 = 4;
  iVar9 = 0;
  iVar5 = local_14;
LAB_100124ae:
  local_14 = iVar5;
  pbVar7 = pbVar8;
  iVar5 = 1;
  bVar6 = *pbVar7;
  pbVar8 = pbVar7 + 1;
  iVar2 = local_14;
  switch(iVar9) {
  case 0:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) {
LAB_100124cb:
      local_14 = iVar2;
      iVar9 = 3;
      goto LAB_100126f0;
    }
    if (bVar6 == DAT_10021b44) goto LAB_100124da;
    if (bVar6 == 0x2b) {
      local_2c = 0;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else if (bVar6 == 0x2d) {
      local_2c = 0x8000;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_100127ca;
    }
    goto LAB_100124ae;
  case 1:
    local_14 = 1;
    if (('0' < (char)bVar6) && (iVar2 = iVar5, (char)bVar6 < ':')) goto LAB_100124cb;
    iVar9 = iVar1;
    if (bVar6 != DAT_10021b44) {
      iVar9 = iVar5;
      if ((bVar6 == 0x2b) || (iVar9 = local_14, bVar6 == 0x2d)) goto LAB_1001255f;
      iVar9 = iVar5;
      local_14 = iVar5;
      if (bVar6 != 0x30) goto LAB_10012538;
    }
    goto LAB_100124ae;
  case 2:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) goto LAB_100124cb;
    if (bVar6 == DAT_10021b44) {
LAB_100124da:
      iVar9 = 5;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      pbVar7 = param_3;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_100127cf;
    }
    goto LAB_100124ae;
  case 3:
    local_14 = iVar5;
    while( true ) {
      if (cbMultiByte_10021b40 < 2) {
        uVar3 = (byte)PTR_DAT_10021780[(uintptr_t)bVar6 * 2] & 4;
        _this = PTR_DAT_10021780;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = iswctype(_this, (uintptr_t)bVar6);
        _this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      else {
        local_c = local_c + 1;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    iVar9 = iVar1;
    iVar5 = local_14;
    if (bVar6 != DAT_10021b44) goto LAB_1001264c;
    goto LAB_100124ae;
  case 4:
    local_14 = 1;
    local_28 = 1;
    iVar9 = iVar5;
    if (local_8 == 0) {
      while (iVar5 = local_28, iVar9 = local_14, bVar6 == 0x30) {
        local_c = local_c + -1;
        bVar6 = *pbVar8;
        pbVar8 = pbVar8 + 1;
      }
    }
    while( true ) {
      local_14 = iVar9;
      local_28 = iVar5;
      if (cbMultiByte_10021b40 < 2) {
        uVar3 = (byte)PTR_DAT_10021780[(uintptr_t)bVar6 * 2] & 4;
        _this = PTR_DAT_10021780;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = iswctype(_this, (uintptr_t)bVar6);
        _this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        local_c = local_c + -1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      iVar5 = local_28;
      iVar9 = local_14;
    }
LAB_1001264c:
    iVar9 = local_14;
    if ((bVar6 == 0x2b) || (bVar6 == 0x2d)) {
LAB_1001255f:
      local_14 = iVar9;
      iVar9 = 0xb;
      pbVar8 = pbVar8 + -1;
      iVar5 = local_14;
    }
    else {
LAB_10012538:
      if (((char)bVar6 < 'D') ||
         (('E' < (char)bVar6 && (((char)bVar6 < 'd' || ('e' < (char)bVar6)))))) goto LAB_100127ca;
      iVar9 = 6;
      iVar5 = local_14;
    }
    goto LAB_100124ae;
  case 5:
    local_28 = iVar5;
    if (cbMultiByte_10021b40 < 2) {
      uVar3 = (byte)PTR_DAT_10021780[(uintptr_t)bVar6 * 2] & 4;
      _this = PTR_DAT_10021780;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = iswctype(_this, (uintptr_t)bVar6);
      _this = pbVar7;
    }
    iVar9 = iVar1;
    pbVar7 = param_3;
    if (uVar3 != 0) goto LAB_100126f0;
    goto LAB_100127cf;
  case 6:
    pbVar7 = pbVar7 + -1;
    _this = pbVar7;
    param_3 = pbVar7;
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      if (bVar6 == 0x2b) goto LAB_10012725;
      if (bVar6 == 0x2d) goto LAB_10012719;
      if (bVar6 != 0x30) goto LAB_100127cf;
LAB_100126be:
      iVar9 = 8;
      iVar5 = local_14;
      goto LAB_100124ae;
    }
    break;
  case 7:
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      pbVar7 = param_3;
      if (bVar6 == 0x30) goto LAB_100126be;
      goto LAB_100127cf;
    }
    break;
  case 8:
    local_24 = 1;
    while (bVar6 == 0x30) {
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) goto LAB_100127ca;
    break;
  case 9:
    local_24 = 1;
    pbVar7 = (byte *)0x0;
    goto LAB_10012750;
  default:
    goto switchD_100124ba_caseD_a;
  case 0xb:
    if (param_7 != 0) {
      if (bVar6 == 0x2b) {
LAB_10012725:
        iVar9 = 7;
        _this = pbVar7;
        param_3 = pbVar7;
        iVar5 = local_14;
      }
      else {
        param_3 = pbVar7;
        if (bVar6 != 0x2d) goto LAB_100127cf;
LAB_10012719:
        local_1c = -1;
        iVar9 = 7;
        _this = pbVar7;
        param_3 = pbVar7;
        iVar5 = local_14;
      }
      goto LAB_100124ae;
    }
    iVar9 = 10;
    pbVar8 = pbVar7;
switchD_100124ba_caseD_a:
    pbVar7 = pbVar8;
    iVar5 = local_14;
    if (iVar9 != 10) goto LAB_100124ae;
    goto LAB_100127cf;
  }
  iVar9 = 9;
LAB_100126f0:
  pbVar8 = pbVar8 + -1;
  iVar5 = local_14;
  goto LAB_100124ae;
LAB_10012750:
  if (cbMultiByte_10021b40 < 2) {
    uVar3 = (byte)PTR_DAT_10021780[(uintptr_t)bVar6 * 2] & 4;
    _this = PTR_DAT_10021780;
  }
  else {
    pbVar10 = (byte *)0x4;
    uVar3 = iswctype(_this, (uintptr_t)bVar6);
    _this = pbVar10;
  }
  if (uVar3 == 0) goto LAB_1001279a;
  _this = (void *)(intptr_t)(char)bVar6;
  pbVar7 = (byte *)((intptr_t)_this + (intptr_t)pbVar7 * 10 + -0x30);
  if (0x1450 < (intptr_t)pbVar7) goto LAB_10012792;
  bVar6 = *pbVar8;
  pbVar8 = pbVar8 + 1;
  goto LAB_10012750;
LAB_10012792:
  pbVar7 = (byte *)0x1451;
LAB_1001279a:
  while( true ) {
    local_20 = pbVar7;
    if (cbMultiByte_10021b40 < 2) {
      uVar3 = (byte)PTR_DAT_10021780[(uintptr_t)bVar6 * 2] & 4;
      _this = PTR_DAT_10021780;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = iswctype(_this, (uintptr_t)bVar6);
      _this = pbVar7;
    }
    if (uVar3 == 0) break;
    bVar6 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar7 = local_20;
  }
LAB_100127ca:
  pbVar7 = pbVar8 + -1;
LAB_100127cf:
  *param_2 = (intptr_t)pbVar7;
  if (local_14 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (byte *)0x0;
    param_3 = (byte *)0x0;
    local_18 = 4;
    goto LAB_100128dd;
  }
  pcVar4 = local_10;
  if (0x18 < local_8) {
    if ('\x04' < local_49) {
      local_49 = local_49 + '\x01';
    }
    local_8 = 0x18;
    local_c = local_c + 1;
    pcVar4 = local_10 + -1;
  }
  if (local_8 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (byte *)0x0;
    param_3 = (byte *)0x0;
  }
  else {
    while (pcVar4 = pcVar4 + -1, *pcVar4 == '\0') {
      local_8 = local_8 - 1;
      local_c = local_c + 1;
    }
    _digits2ld(local_60,local_8,(uint *)&local_44);
    pbVar8 = local_20;
    if (local_1c < 0) {
      pbVar8 = (byte *)-(intptr_t)local_20;
    }
    pbVar8 = pbVar8 + local_c;
    if (local_24 == 0) {
      pbVar8 = pbVar8 + param_5;
    }
    if (local_28 == 0) {
      pbVar8 = pbVar8 + -param_6;
    }
    if ((intptr_t)pbVar8 < 0x1451) {
      if (-0x1451 < (intptr_t)pbVar8) {
        _ld10pow((int *)&local_44,(uintptr_t)pbVar8,param_4);
        param_3 = (byte *)CONCAT22(uStack_40,uStack_42);
        goto LAB_10012862;
      }
      local_34 = 1;
    }
    else {
      local_30 = 1;
    }
    local_3a = (ushort)param_3;
    local_3e = param_3;
    local_44 = local_3a;
  }
LAB_10012862:
  if (local_30 == 0) {
    if (local_34 != 0) {
      local_44 = 0;
      local_3a = 0;
      local_3e = (byte *)0x0;
      param_3 = (byte *)0x0;
      local_18 = 1;
    }
  }
  else {
    param_3 = (byte *)0x0;
    local_3a = 0x7fff;
    local_3e = (byte *)0x80000000;
    local_44 = 0;
    local_18 = 2;
  }
LAB_100128dd:
  *(byte **)(param_1 + 3) = local_3e;
  *(byte **)(param_1 + 1) = param_3;
  param_1[5] = local_3a | (ushort)local_2c;
  *param_1 = local_44;
  return local_18;
}
#endif




#if 0
uint __thiscall _strtod_l(void *_this,unsigned int *param_1,int *param_2,byte *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  ushort local_10 [6];
  
  uVar1 = _strtod_core(_this,local_10,param_2,param_3,param_4,0,0,0);
  iVar2 = _ld12told(local_10,param_1);
  if (iVar2 == 1) {
    uVar1 = uVar1 | 2;
  }
  return uVar1;
}
#endif /* _strtod_l */




unsigned int __cdecl
_ld2digits(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  uint uVar2;
  short *psVar3;
  char cVar4;
  uint uVar5;
  short *psVar6;
  short *psVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  unsigned char local_20;
  unsigned char local_1f;
  unsigned char local_1e;
  unsigned char local_1d;
  unsigned char local_1c;
  unsigned char local_1b;
  unsigned char local_1a;
  unsigned char local_19;
  unsigned char local_18;
  unsigned char local_17;
  unsigned char local_16;
  unsigned char local_15;
  unsigned short local_14;
  unsigned int local_12;
  unsigned int local_e;
  unsigned char local_a;
  char cStack_9;
  unsigned int local_8;
  
  psVar3 = param_6;
  uVar5 = param_3 & 0x7fff;
  local_20 = 0xcc;
  local_1f = 0xcc;
  local_1e = 0xcc;
  local_1d = 0xcc;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xfb;
  local_15 = 0x3f;
  local_8 = 1;
  if ((param_3 & 0x8000) == 0) {
    *(unsigned char *)(param_6 + 1) = 0x20;
  }
  else {
    *(unsigned char *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 != 0) || (param_2 != 0)) || (param_1 != 0)) {
    if ((short)uVar5 == 0x7fff) {
      *param_6 = 1;
      if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
        if (((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) {
          if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_10012a59;
          pcVar11 = "1#INF";
        }
        else {
          if (param_1 != 0) {
LAB_10012a59:
            pcVar11 = "1#QNAN";
            goto LAB_10012a5e;
          }
          pcVar11 = "1#IND";
        }
        strcpy((char*)(param_6 + 2),(char*)pcVar11);
        *(unsigned char *)((intptr_t)psVar3 + 3) = 5;
      }
      else {
        pcVar11 = "1#SNAN";
LAB_10012a5e:
        strcpy((char*)(param_6 + 2),(char*)pcVar11);
        *(unsigned char *)((intptr_t)psVar3 + 3) = 6;
      }
      return 0;
    }
    local_14 = 0;
    local_a = (unsigned char)uVar5;
    cStack_9 = (char)(uVar5 >> 8);
    sVar8 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                   0x10);
    local_e = param_2;
    local_12 = param_1;
    _ld10pow((int *)&local_14,-(intptr_t)sVar8,1);
    if (0x3ffe < CONCAT11(cStack_9,local_a)) {
      sVar8 = sVar8 + 1;
      _ldmul((int *)&local_14,(int *)&local_20);
    }
    *psVar3 = sVar8;
    iVar10 = param_4;
    if (((param_5 & 1) == 0) || (iVar10 = param_4 + sVar8, 0 < param_4 + sVar8)) {
      if (0x15 < iVar10) {
        iVar10 = 0x15;
      }
      iVar9 = CONCAT11(cStack_9,local_a) - 0x3ffe;
      local_a = 0;
      cStack_9 = '\0';
      param_6 = (short *)0x8;
      do {
        _ldshl1((uint *)&local_14);
        param_6 = (short *)((intptr_t)param_6 + -1);
      } while (param_6 != (short *)0x0);
      if (iVar9 < 0) {
        param_6 = (short *)0x0;
        for (uVar5 = -iVar9 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
          _ldshr1((uint *)&local_14);
        }
      }
      param_4 = iVar10 + 1;
      psVar6 = psVar3 + 2;
      param_6 = psVar6;
      uVar5 = local_12;
      uVar2 = local_e;
      if (0 < param_4) {
        do {
          (*(unsigned short*)((char*)&(local_e)+2)) = (unsigned short)(uVar2 >> 0x10);
          (*(unsigned short*)&(local_e)) = (unsigned short)uVar2;
          (*(unsigned short*)((char*)&(local_12)+2)) = (unsigned short)(uVar5 >> 0x10);
          (*(unsigned short*)&(local_12)) = (unsigned short)uVar5;
          param_1 = CONCAT22((unsigned short)local_12,local_14);
          param_2 = CONCAT22((unsigned short)local_e,(*(unsigned short*)((char*)&(local_12)+2)));
          param_3 = CONCAT13(cStack_9,CONCAT12(local_a,(*(unsigned short*)((char*)&(local_e)+2))));
          local_12 = uVar5;
          local_e = uVar2;
          _ldshl1((uint *)&local_14);
          _ldshl1((uint *)&local_14);
          ___add_12((uint *)&local_14,&param_1);
          _ldshl1((uint *)&local_14);
          cVar4 = cStack_9;
          cStack_9 = '\0';
          psVar6 = (short *)((intptr_t)param_6 + 1);
          param_4 = param_4 + -1;
          *(char *)param_6 = cVar4 + '0';
          param_6 = psVar6;
          uVar5 = local_12;
          uVar2 = local_e;
        } while (param_4 != 0);
      }
      psVar7 = psVar6 + -1;
      psVar1 = psVar3 + 2;
      if ('4' < *(char *)((intptr_t)psVar6 + -1)) {
        for (; psVar1 <= psVar7; psVar7 = (short *)((intptr_t)psVar7 + -1)) {
          if ((char)*psVar7 != '9') {
            if (psVar1 <= psVar7) goto LAB_10012bb6;
            break;
          }
          *(char *)psVar7 = '0';
        }
        psVar7 = (short *)((intptr_t)psVar7 + 1);
        *psVar3 = *psVar3 + 1;
LAB_10012bb6:
        *(char *)psVar7 = (char)*psVar7 + '\x01';
LAB_10012bb8:
        cVar4 = ((char*)(intptr_t)psVar7 - (char*)(intptr_t)psVar3) + -3;
        *(char *)((intptr_t)psVar3 + 3) = cVar4;
        *(unsigned char *)(cVar4 + 4 + (intptr_t)psVar3) = 0;
        return local_8;
      }
      for (; psVar1 <= psVar7; psVar7 = (short *)((intptr_t)psVar7 + -1)) {
        if ((char)*psVar7 != '0') {
          if (psVar1 <= psVar7) goto LAB_10012bb8;
          break;
        }
      }
      *psVar3 = 0;
      *(unsigned char *)(psVar3 + 1) = 0x20;
      *(unsigned char *)((intptr_t)psVar3 + 3) = 1;
      *(char *)psVar1 = '0';
      goto LAB_10012bee;
    }
  }
  *psVar3 = 0;
  *(unsigned char *)(psVar3 + 1) = 0x20;
  *(unsigned char *)((intptr_t)psVar3 + 3) = 1;
  *(unsigned char *)(psVar3 + 2) = 0x30;
LAB_10012bee:
  *(unsigned char *)((intptr_t)psVar3 + 5) = 0;
  return 1;
}



unsigned int __cdecl fclose(int *param_1)

{
  unsigned int uVar1;
  
  uVar1 = 0xffffffff;
  if ((*(byte *)(param_1 + 3) & 0x40) == 0) {
    __lock((uintptr_t)param_1);
    uVar1 = _fclose(param_1);
    __unlock((uintptr_t)param_1);
  }
  else {
    param_1[3] = 0;
  }
  return uVar1;
}



#if 0
unsigned int __cdecl _fclose(int *param_1)

{
  int iVar1;
  unsigned int uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 3) & 0x83) != 0) {
    uVar2 = _flush(param_1);
    _freebuf(param_1);
    iVar1 = _close(param_1[4]);
    if (iVar1 < 0) {
      uVar2 = 0xffffffff;
    }
    else if ((LPVOID)param_1[7] != (LPVOID)0x0) {
      free((LPVOID)param_1[7]);
      param_1[7] = 0;
    }
  }
  param_1[3] = 0;
  return uVar2;
}
#endif /* _fclose */




#if 0
unsigned int __cdecl _commit(uint param_1)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  DWORD *pDVar3;
  int iVar4;
  unsigned int uVar5;
  
  if (uNumber_10024ffc <= param_1) {
LAB_10012cf5:
    pDVar3 = _errno();
    *pDVar3 = 9;
    return 0xffffffff;
  }
  iVar4 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + iVar4) & 1) == 0) goto LAB_10012cf5;
  _lock_fh(param_1);
  if ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + iVar4) & 1) != 0) {
    hFile = (HANDLE)_get_osfhandle(param_1);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    else {
      DVar2 = 0;
    }
    uVar5 = 0;
    if (DVar2 == 0) goto LAB_10012cea;
    pDVar3 = _doserrno_impl();
    *pDVar3 = DVar2;
  }
  pDVar3 = _errno();
  *pDVar3 = 9;
  uVar5 = 0xffffffff;
LAB_10012cea:
  _unlock_fh(param_1);
  return uVar5;
}
#endif /* _commit */




uint __cdecl _getloc_datetime(char *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  
  uVar1 = (uintptr_t)DAT_1002382a;
  uVar43 = (uintptr_t)DAT_1002382c;
  if (param_1 == (char *)0x0) {
    uVar43 = 0xffffffff;
  }
  else {
    uVar2 = _getlocaleinfo(1,uVar1,0x31,param_1 + 4);
    uVar3 = _getlocaleinfo(1,uVar1,0x32,param_1 + 8);
    uVar4 = _getlocaleinfo(1,uVar1,0x33,param_1 + 0xc);
    uVar5 = _getlocaleinfo(1,uVar1,0x34,param_1 + 0x10);
    uVar6 = _getlocaleinfo(1,uVar1,0x35,param_1 + 0x14);
    uVar7 = _getlocaleinfo(1,uVar1,0x36,param_1 + 0x18);
    uVar8 = _getlocaleinfo(1,uVar1,0x37,param_1);
    uVar9 = _getlocaleinfo(1,uVar1,0x2a,param_1 + 0x20);
    uVar10 = _getlocaleinfo(1,uVar1,0x2b,param_1 + 0x24);
    uVar11 = _getlocaleinfo(1,uVar1,0x2c,param_1 + 0x28);
    uVar12 = _getlocaleinfo(1,uVar1,0x2d,param_1 + 0x2c);
    uVar13 = _getlocaleinfo(1,uVar1,0x2e,param_1 + 0x30);
    uVar14 = _getlocaleinfo(1,uVar1,0x2f,param_1 + 0x34);
    uVar15 = _getlocaleinfo(1,uVar1,0x30,param_1 + 0x1c);
    uVar16 = _getlocaleinfo(1,uVar1,0x44,param_1 + 0x38);
    uVar17 = _getlocaleinfo(1,uVar1,0x45,param_1 + 0x3c);
    uVar18 = _getlocaleinfo(1,uVar1,0x46,param_1 + 0x40);
    uVar19 = _getlocaleinfo(1,uVar1,0x47,param_1 + 0x44);
    uVar20 = _getlocaleinfo(1,uVar1,0x48,param_1 + 0x48);
    uVar21 = _getlocaleinfo(1,uVar1,0x49,param_1 + 0x4c);
    uVar22 = _getlocaleinfo(1,uVar1,0x4a,param_1 + 0x50);
    uVar23 = _getlocaleinfo(1,uVar1,0x4b,param_1 + 0x54);
    uVar24 = _getlocaleinfo(1,uVar1,0x4c,param_1 + 0x58);
    uVar25 = _getlocaleinfo(1,uVar1,0x4d,param_1 + 0x5c);
    uVar26 = _getlocaleinfo(1,uVar1,0x4e,param_1 + 0x60);
    uVar27 = _getlocaleinfo(1,uVar1,0x4f,param_1 + 100);
    uVar28 = _getlocaleinfo(1,uVar1,0x38,param_1 + 0x68);
    uVar29 = _getlocaleinfo(1,uVar1,0x39,param_1 + 0x6c);
    uVar30 = _getlocaleinfo(1,uVar1,0x3a,param_1 + 0x70);
    uVar31 = _getlocaleinfo(1,uVar1,0x3b,param_1 + 0x74);
    uVar32 = _getlocaleinfo(1,uVar1,0x3c,param_1 + 0x78);
    uVar33 = _getlocaleinfo(1,uVar1,0x3d,param_1 + 0x7c);
    uVar34 = _getlocaleinfo(1,uVar1,0x3e,param_1 + 0x80);
    uVar35 = _getlocaleinfo(1,uVar1,0x3f,param_1 + 0x84);
    uVar36 = _getlocaleinfo(1,uVar1,0x40,param_1 + 0x88);
    uVar37 = _getlocaleinfo(1,uVar1,0x41,param_1 + 0x8c);
    uVar38 = _getlocaleinfo(1,uVar1,0x42,param_1 + 0x90);
    uVar39 = _getlocaleinfo(1,uVar1,0x43,param_1 + 0x94);
    uVar40 = _getlocaleinfo(1,uVar1,0x28,param_1 + 0x98);
    uVar1 = _getlocaleinfo(1,uVar1,0x29,param_1 + 0x9c);
    uVar41 = _getlocaleinfo(1,uVar43,0x1f,param_1 + 0xa0);
    uVar42 = _getlocaleinfo(1,uVar43,0x20,param_1 + 0xa4);
    uVar43 = _getlocaleinfo(1,uVar43,0x1003,param_1 + 0xa8);
    uVar43 = uVar43 | uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 |
                      uVar11 | uVar12 | uVar13 | uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19
                      | uVar20 | uVar21 | uVar22 | uVar23 | uVar24 | uVar25 | uVar26 | uVar27 |
                      uVar28 | uVar29 | uVar30 | uVar31 | uVar32 | uVar33 | uVar34 | uVar35 | uVar36
                      | uVar37 | uVar38 | uVar39 | uVar40 | uVar1 | uVar41 | uVar42;
  }
  return uVar43;
}



void __cdecl _free_locale_datetime(unsigned int *param_1)

{
  if (param_1 != (unsigned int *)0x0) {
    free((LPVOID)param_1[1]);
    free((LPVOID)param_1[2]);
    free((LPVOID)param_1[3]);
    free((LPVOID)param_1[4]);
    free((LPVOID)param_1[5]);
    free((LPVOID)param_1[6]);
    free((LPVOID)*param_1);
    free((LPVOID)param_1[8]);
    free((LPVOID)param_1[9]);
    free((LPVOID)param_1[10]);
    free((LPVOID)param_1[0xb]);
    free((LPVOID)param_1[0xc]);
    free((LPVOID)param_1[0xd]);
    free((LPVOID)param_1[7]);
    free((LPVOID)param_1[0xe]);
    free((LPVOID)param_1[0xf]);
    free((LPVOID)param_1[0x10]);
    free((LPVOID)param_1[0x11]);
    free((LPVOID)param_1[0x12]);
    free((LPVOID)param_1[0x13]);
    free((LPVOID)param_1[0x14]);
    free((LPVOID)param_1[0x15]);
    free((LPVOID)param_1[0x16]);
    free((LPVOID)param_1[0x17]);
    free((LPVOID)param_1[0x18]);
    free((LPVOID)param_1[0x19]);
    free((LPVOID)param_1[0x1a]);
    free((LPVOID)param_1[0x1b]);
    free((LPVOID)param_1[0x1c]);
    free((LPVOID)param_1[0x1d]);
    free((LPVOID)param_1[0x1e]);
    free((LPVOID)param_1[0x1f]);
    free((LPVOID)param_1[0x20]);
    free((LPVOID)param_1[0x21]);
    free((LPVOID)param_1[0x22]);
    free((LPVOID)param_1[0x23]);
    free((LPVOID)param_1[0x24]);
    free((LPVOID)param_1[0x25]);
    free((LPVOID)param_1[0x26]);
    free((LPVOID)param_1[0x27]);
    free((LPVOID)param_1[0x28]);
    free((LPVOID)param_1[0x29]);
    free((LPVOID)param_1[0x2a]);
  }
  return;
}



void __cdecl _strip_semicolons(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = *param_1;
  do {
    if (cVar2 == '\0') {
      return;
    }
    if ((cVar2 < '0') || ('9' < cVar2)) {
      pcVar3 = param_1;
      if (cVar2 != ';') goto LAB_10013462;
      do {
        pcVar1 = pcVar3 + 1;
        *pcVar3 = pcVar3[1];
        pcVar3 = pcVar1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_10013462:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}



uint __cdecl _getloc_names(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  
  uVar15 = (uintptr_t)DAT_10023820;
  if (param_1 == 0) {
    uVar15 = 0xffffffff;
  }
  else {
    uVar1 = _getlocaleinfo(1,uVar15,0x15,(char *)(param_1 + 0xc));
    uVar2 = _getlocaleinfo(1,uVar15,0x14,(char *)(param_1 + 0x10));
    uVar3 = _getlocaleinfo(1,uVar15,0x16,(char *)(param_1 + 0x14));
    uVar4 = _getlocaleinfo(1,uVar15,0x17,(char *)(param_1 + 0x18));
    uVar5 = _getlocaleinfo(1,uVar15,0x18,(char *)(param_1 + 0x1c));
    _strip_semicolons2(*(char **)(param_1 + 0x1c));
    uVar6 = _getlocaleinfo(1,uVar15,0x50,(char *)(param_1 + 0x20));
    uVar7 = _getlocaleinfo(1,uVar15,0x51,(char *)(param_1 + 0x24));
    uVar8 = _getlocaleinfo(0,uVar15,0x1a,(char *)(param_1 + 0x28));
    uVar9 = _getlocaleinfo(0,uVar15,0x19,(char *)(param_1 + 0x29));
    uVar10 = _getlocaleinfo(0,uVar15,0x54,(char *)(param_1 + 0x2a));
    uVar11 = _getlocaleinfo(0,uVar15,0x55,(char *)(param_1 + 0x2b));
    uVar12 = _getlocaleinfo(0,uVar15,0x56,(char *)(param_1 + 0x2c));
    uVar13 = _getlocaleinfo(0,uVar15,0x57,(char *)(param_1 + 0x2d));
    uVar14 = _getlocaleinfo(0,uVar15,0x52,(char *)(param_1 + 0x2e));
    uVar15 = _getlocaleinfo(0,uVar15,0x53,(char *)(param_1 + 0x2f));
    uVar15 = uVar15 | uVar1 | uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10
                      | uVar11 | uVar12 | uVar13 | uVar14;
  }
  return uVar15;
}



void __cdecl _strip_semicolons2(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = *param_1;
  do {
    if (cVar2 == '\0') {
      return;
    }
    if ((cVar2 < '0') || ('9' < cVar2)) {
      pcVar3 = param_1;
      if (cVar2 != ';') goto LAB_10013686;
      do {
        pcVar1 = pcVar3 + 1;
        *pcVar3 = pcVar3[1];
        pcVar3 = pcVar1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_10013686:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}



void __cdecl _free_locale_names(int param_1)

{
  if ((param_1 != 0) && (*(unsigned char **)(param_1 + 0xc) != &DAT_1002385c)) {
    free(*(unsigned char **)(param_1 + 0xc));
    free(*(LPVOID *)(param_1 + 0x10));
    free(*(LPVOID *)(param_1 + 0x14));
    free(*(LPVOID *)(param_1 + 0x18));
    free(*(LPVOID *)(param_1 + 0x1c));
    free(*(LPVOID *)(param_1 + 0x20));
    free(*(LPVOID *)(param_1 + 0x24));
  }
  return;
}
#if 0 /* CRT: _init_mbctype */



unsigned int _init_mbctype(void)

{
  BYTE *pBVar1;
  LPWORD pWVar2;
  byte bVar3;
  int iVar4;
  unsigned short *puVar5;
  BOOL BVar6;
  BYTE *pBVar7;
  uint uVar8;
  LPCWSTR pWVar9;
  unsigned int uVar10;
  struct _cpinfo local_28;
  unsigned short *local_14;
  unsigned short *local_10;
  LPCWSTR local_c;
  LPCSTR local_8;
  
  uVar10 = 0;
  local_8 = (LPCSTR)0x0;
  local_c = (LPCWSTR)0x0;
  if (DAT_100237bc == 0) {
    PTR_DAT_10021780 = &DAT_1002178a;
    PTR_DAT_10021784 = &DAT_1002178a;
    free(DAT_10023804);
    free(DAT_10023808);
    DAT_10023804 = (unsigned short *)0x0;
    DAT_10023808 = (unsigned short *)0x0;
    return 0;
  }
  if ((CodePage_100237cc != 0) ||
     (iVar4 = _getlocaleinfo(0,(uintptr_t)DAT_10023818,0x1004,(char *)&CodePage_100237cc), iVar4 == 0)) {
    puVar5 = _malloc(0x202);
    local_14 = puVar5;
    local_10 = _malloc(0x202);
    local_8 = _malloc(0x101);
    local_c = _malloc(0x202);
    if ((puVar5 != (unsigned short *)0x0) &&
       (((local_10 != (unsigned short *)0x0 && (local_8 != (LPCSTR)0x0)) && (local_c != (LPCWSTR)0x0))))
    {
      iVar4 = 0;
      do {
        local_8[iVar4] = (CHAR)iVar4;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x100);
      BVar6 = GetCPInfo(CodePage_100237cc,&local_28);
      if ((BVar6 != 0) && (local_28.MaxCharSize < 3)) {
        cbMultiByte_10021b40 = local_28.MaxCharSize & 0xffff;
        if ((1 < (uintptr_t)cbMultiByte_10021b40) && (local_28.LeadByte[0] != '\0')) {
          pBVar7 = local_28.LeadByte + 1;
          do {
            bVar3 = *pBVar7;
            if (bVar3 == 0) break;
            for (uVar8 = (uintptr_t)pBVar7[-1]; (intptr_t)uVar8 <= (intptr_t)(uintptr_t)bVar3; uVar8 = uVar8 + 1) {
              local_8[uVar8] = '\0';
              bVar3 = *pBVar7;
            }
            pBVar1 = pBVar7 + 1;
            pBVar7 = pBVar7 + 2;
          } while (*pBVar1 != 0);
        }
        BVar6 = _getstringtype(1,local_8,0x100,puVar5 + 1,0,0,0);
        if (BVar6 != 0) {
          *puVar5 = 0;
          iVar4 = 0;
          pWVar9 = local_c;
          do {
            *pWVar9 = (WCHAR)iVar4;
            pWVar9 = pWVar9 + 1;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x100);
          pWVar2 = local_10 + 1;
          BVar6 = _getstringtype_w(1,local_c,0x100,pWVar2,0,0);
          if (BVar6 != 0) {
            *local_10 = 0;
            if ((1 < cbMultiByte_10021b40) && (local_28.LeadByte[0] != '\0')) {
              pBVar7 = local_28.LeadByte + 1;
              do {
                if (*pBVar7 == 0) break;
                uVar8 = (uintptr_t)pBVar7[-1];
                if (uVar8 <= *pBVar7) {
                  puVar5 = local_14 + uVar8 + 1;
                  do {
                    *puVar5 = 0x8000;
                    uVar8 = uVar8 + 1;
                    puVar5 = puVar5 + 1;
                  } while ((intptr_t)uVar8 <= (intptr_t)(uintptr_t)*pBVar7);
                }
                pBVar1 = pBVar7 + 1;
                pBVar7 = pBVar7 + 2;
              } while (*pBVar1 != 0);
            }
            PTR_DAT_10021780 = (unsigned char *)(local_14 + 1);
            PTR_DAT_10021784 = (unsigned char *)pWVar2;
            if (DAT_10023804 != (unsigned short *)0x0) {
              free(DAT_10023804);
            }
            DAT_10023804 = local_14;
            if (DAT_10023808 != (unsigned short *)0x0) {
              free(DAT_10023808);
            }
            DAT_10023808 = local_10;
            goto LAB_100138d2;
          }
        }
      }
    }
  }
  free(local_14);
  free(local_10);
  uVar10 = 1;
LAB_100138d2:
  free(local_8);
  free(local_c);
  return uVar10;
}
#endif




#if 0
int __cdecl strcspn(byte *param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] = abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  iVar2 = -1;
  do {
    iVar2 = iVar2 + 1;
    bVar1 = *param_1;
    if (bVar1 == 0) {
      return iVar2;
    }
    param_1 = param_1 + 1;
  } while ((abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return iVar2;
}
#endif /* strcspn */




// Library Function - Single Match
//  _strncmp
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}



#if 0
byte * __cdecl strpbrk(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] = abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  do {
    pbVar2 = param_1;
    bVar1 = *pbVar2;
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    param_1 = pbVar2 + 1;
  } while ((abStack_28[(intptr_t)(uintptr_t)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return pbVar2;
}
#endif /* strpbrk */




#if 0
unsigned int __thiscall _resolve_locale(void *_this,char *param_1,unsigned short *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  BOOL BVar3;
  void *extraout_ECX;
  void *extraout_ECX_00;
  
  if (DAT_10023850 == (void *)0x0) {
    iVar1 = _is_nt();
    _this = extraout_ECX;
    if (iVar1 == 0) {
      DAT_10023850 = _localeinfo_table;
    }
    else {
      DAT_10023850 = GetLocaleInfoA_exref;
    }
  }
  if (param_1 != (char *)0x0) {
    DAT_10023840 = param_1;
    if (*param_1 != '\0') {
      _locale_name_lookup(_this,0x100224b0,0x40,(byte *)&DAT_10023840);
      _this = extraout_ECX_00;
    }
    DAT_10023844 = param_1 + 0x40;
    if ((DAT_10023844 != (char *)0x0) && (*DAT_10023844 != '\0')) {
      _locale_name_lookup(_this,0x100223f8,0x16,(byte *)&DAT_10023844);
    }
    DAT_10023848 = 0;
    if ((DAT_10023840 != (char *)0x0) && (*DAT_10023840 != '\0')) {
      if ((DAT_10023844 == (char *)0x0) || (*DAT_10023844 == '\0')) {
        _enum_lang();
      }
      else {
        _enum_lang_country();
      }
      goto LAB_10013ab7;
    }
    if ((DAT_10023844 != (char *)0x0) && (*DAT_10023844 != '\0')) {
      _enum_country();
      goto LAB_10013ab7;
    }
  }
  _default_lcid();
LAB_10013ab7:
  if ((((DAT_10023848 == 0) || (uVar2 = _resolve_codepage((byte *)(param_1 + 0x80)), uVar2 == 0)) ||
      (BVar3 = IsValidCodePage(uVar2 & 0xffff), BVar3 == 0)) ||
     (BVar3 = IsValidLocale(Locale_10023830,1), BVar3 == 0)) {
    return 0;
  }
  if (param_2 != (unsigned short *)0x0) {
    *param_2 = (unsigned short)Locale_10023830;
    param_2[1] = (unsigned short)Locale_1002384c;
    param_2[2] = (short)uVar2;
  }
  if (param_3 != 0) {
    iVar1 = (*DAT_10023850)(Locale_10023830,0x1001,param_3,0x40);
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = (*DAT_10023850)(Locale_1002384c,0x1002,param_3 + 0x40,0x40);
    if (iVar1 == 0) {
      return 0;
    }
    _ltoa(uVar2,(char *)(param_3 + 0x80),10);
  }
  return 1;
}
#endif /* _resolve_locale */




#if 0
void __thiscall _locale_name_lookup(void *_this,int param_1,int param_2,byte *param_3)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  uVar2 = 1;
  if (-1 < param_2) {
    do {
      if (uVar2 == 0) {
        return;
      }
      iVar4 = (param_2 + iVar3) / 2;
      pbVar1 = *(byte **)(param_1 + iVar4 * 8);
      uVar2 = _stricmp(_this, *(byte **)param_3);
      _this = pbVar1;
      if (uVar2 == 0) {
        *(int *)param_3 = param_1 + iVar4 * 8 + 4;
        _this = param_3;
      }
      else if ((intptr_t)uVar2 < 0) {
        param_2 = iVar4 + -1;
      }
      else {
        iVar3 = iVar4 + 1;
      }
    } while (iVar3 <= param_2);
  }
  return;
}
#endif /* _locale_name_lookup */

#if 0 /* CRT: _enum_lang_country */



void _enum_lang_country(void)

{
  size_t sVar1;
  
  sVar1 = _strlen(DAT_10023840);
  DAT_1002383c = (uintptr_t)(sVar1 == 3);
  sVar1 = _strlen(DAT_10023844);
  DAT_10023834 = (uintptr_t)(sVar1 == 3);
  Locale_10023830 = 0;
  if (DAT_1002383c == 0) {
    DAT_10023838 = _alpha_len(DAT_10023840);
  }
  else {
    DAT_10023838 = 2;
  }
  EnumSystemLocalesA(lpLocaleEnumProc_10013c56);
  if ((((DAT_10023848 & 0x100) == 0) || ((DAT_10023848 & 0x200) == 0)) || ((DAT_10023848 & 7) == 0))
  {
    DAT_10023848 = 0;
  }
  return;
}
#endif




// lpLocaleEnumProc parameter of EnumSystemLocalesA
// 

#if 0
uint lpLocaleEnumProc_10013c56(char *param_1)

{
  LCID LVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  void *_this;
  void *this_00;
  void *this_01;
  byte local_7c [120];
  
  LVar1 = _str2lcid(param_1);
  iVar2 = (*DAT_10023850)(LVar1,(-(uintptr_t)(DAT_10023834 != 0) & 0xfffff005) + 0x1002,local_7c,0x78);
  if (iVar2 == 0) {
    DAT_10023848 = 0;
    return 1;
  }
  uVar3 = _stricmp(_this, DAT_10023844);
  if (uVar3 == 0) {
    iVar2 = (*DAT_10023850)(LVar1)(DAT_1002383c != 0) & 0xfffff002) + 0x1001,local_7c,0x78);
    if (iVar2 == 0) {
      DAT_10023848 = 0;
      return 1;
    }
    uVar3 = _stricmp(this_00, DAT_10023840);
    if (uVar3 == 0) {
      DAT_10023848 = DAT_10023848 | 0x304;
      Locale_1002384c = LVar1;
LAB_10013cfc:
      Locale_10023830 = LVar1;
    }
    else if ((DAT_10023848 & 2) == 0) {
      if ((DAT_10023838 == (void *)0x0) ||
         (iVar2 = _strnicmp(DAT_10023840)local_7c,DAT_10023838), iVar2 != 0)) {
        if (((DAT_10023848 & 1) == 0) && (iVar2 = _is_known_sortid((short)LVar1), iVar2 != 0)) {
          DAT_10023848 = DAT_10023848 | 1;
          Locale_1002384c = LVar1;
        }
      }
      else {
        DAT_10023848 = DAT_10023848 | 2;
        Locale_1002384c = LVar1;
        pvVar4 = (void *)_strlen((char *)DAT_10023840);
        if (pvVar4 == DAT_10023838) goto LAB_10013cfc;
      }
    }
  }
  if ((DAT_10023848 & 0x300) == 0x300) goto LAB_10013e46;
  iVar2 = (*DAT_10023850)(LVar1,(-(uintptr_t)(DAT_1002383c != 0) & 0xfffff002) + 0x1001,local_7c,0x78);
  if (iVar2 == 0) {
    DAT_10023848 = 0;
    return 1;
  }
  uVar3 = _stricmp(this_01, DAT_10023840);
  if (uVar3 == 0) {
    DAT_10023848 = DAT_10023848 | 0x200;
    if (((DAT_1002383c == 0) && (DAT_10023838 != (void *)0x0)) &&
       (pvVar4 = (void *)_strlen((char *)DAT_10023840))) {
      iVar2 = 1;
      goto LAB_10013e25;
    }
  }
  else {
    if (((DAT_1002383c != 0) || (DAT_10023838 == (void *)0x0)) ||
       (iVar2 = _strnicmp(DAT_10023840,(char *)local_7c,DAT_10023838), iVar2 != 0))
    goto LAB_10013e46;
    iVar2 = 0;
LAB_10013e25:
    iVar2 = _enum_lcid_match(LVar1,iVar2);
    if (iVar2 == 0) goto LAB_10013e46;
  }
  DAT_10023848 = DAT_10023848 | 0x100;
  if (Locale_10023830 == 0) {
    Locale_10023830 = LVar1;
  }
LAB_10013e46:
  return ~DAT_10023848 >> 2 & 1;
}
#endif /* lpLocaleEnumProc_10013c56 */




void _enum_lang(void)

{
  size_t sVar1;
  
  sVar1 = _strlen(DAT_10023840);
  DAT_1002383c = (uintptr_t)(sVar1 == 3);
  if (sVar1 == 3) {
    DAT_10023838 = 2;
  }
  else {
    DAT_10023838 = _alpha_len(DAT_10023840);
  }
  EnumSystemLocalesA(lpLocaleEnumProc_10013eb0,1);
  if ((DAT_10023848 & 4) == 0) {
    DAT_10023848 = 0;
  }
  return;
}



// lpLocaleEnumProc parameter of EnumSystemLocalesA
// 

#if 0
uint lpLocaleEnumProc_10013eb0(char *param_1)

{
  LCID LVar1;
  int iVar2;
  uint uVar3;
  void *_this;
  byte local_7c [120];
  
  LVar1 = _str2lcid(param_1);
  iVar2 = (*DAT_10023850)(LVar1,(-(uintptr_t)(DAT_1002383c != 0) & 0xfffff002) + 0x1001,local_7c,0x78);
  if (iVar2 == 0) {
    DAT_10023848 = 0;
    return 1;
  }
  uVar3 = _stricmp(_this, DAT_10023840);
  if (uVar3 == 0) {
    if (DAT_1002383c == 0) {
      iVar2 = 1;
      goto LAB_10013f3c;
    }
  }
  else {
    if (((DAT_1002383c != 0) || (DAT_10023838 == (void *)0x0)) ||
       (iVar2 = _strnicmp(DAT_10023840)local_7c,DAT_10023838), iVar2 != 0))
    goto LAB_10013f5b;
    iVar2 = 0;
LAB_10013f3c:
    iVar2 = _enum_lcid_match(LVar1,iVar2);
    if (iVar2 == 0) goto LAB_10013f5b;
  }
  DAT_10023848 = DAT_10023848 | 4;
  Locale_10023830 = LVar1;
  Locale_1002384c = LVar1;
LAB_10013f5b:
  return ~DAT_10023848 >> 2 & 1;
}
#endif /* lpLocaleEnumProc_10013eb0 */




void _enum_country(void)

{
  size_t sVar1;
  
  sVar1 = _strlen(DAT_10023844);
  DAT_10023834 = (uintptr_t)(sVar1 == 3);
  EnumSystemLocalesA(lpLocaleEnumProc_10013fa4,1);
  if ((DAT_10023848 & 4) == 0) {
    DAT_10023848 = 0;
  }
  return;
}



// lpLocaleEnumProc parameter of EnumSystemLocalesA
// 

#if 0
uint lpLocaleEnumProc_10013fa4(char *param_1)

{
  LCID LVar1;
  int iVar2;
  uint uVar3;
  void *_this;
  byte local_7c [120];
  
  LVar1 = _str2lcid(param_1);
  iVar2 = (*DAT_10023850)(LVar1,(-(uintptr_t)(DAT_10023834 != 0) & 0xfffff005) + 0x1002,local_7c,0x78);
  if (iVar2 == 0) {
    DAT_10023848 = 0;
    uVar3 = 1;
  }
  else {
    uVar3 = _stricmp(_this, DAT_10023844);
    if (uVar3 == 0) {
      iVar2 = _is_known_sortid((short)LVar1);
      if (iVar2 != 0) {
        DAT_10023848 = DAT_10023848 | 4;
        Locale_10023830 = LVar1;
        Locale_1002384c = LVar1;
      }
    }
    uVar3 = ~DAT_10023848 >> 2 & 1;
  }
  return uVar3;
}
#endif /* lpLocaleEnumProc_10013fa4 */




#if 0
void _default_lcid(void)

{
  (*(unsigned short*)&(DAT_10023848)) = (ushort)DAT_10023848 | 0x104;
  Locale_1002384c = GetUserDefaultLCID();
  Locale_10023830 = Locale_1002384c;
  return;
}
#endif /* _default_lcid */




#if 0
void __cdecl _resolve_codepage(byte *param_1)

{
  int iVar1;
  unsigned char *extraout_ECX;
  unsigned int uVar2;
  unsigned char *_this;
  byte local_c [8];
  
  if (((param_1 == (byte *)0x0) || (*param_1 == 0)) ||
     (iVar1 = _strcmp((char *)param_1), iVar1 == 0)) {
    uVar2 = 0x1004;
  }
  else {
    _this = &DAT_1001cc30;
    iVar1 = _strcmp((char *)param_1,"OCP");
    if (iVar1 != 0) goto LAB_100140a0;
    uVar2 = 0xb;
  }
  iVar1 = (*DAT_10023850)(Locale_1002384c,uVar2,local_c,8);
  if (iVar1 == 0) {
    return;
  }
  param_1 = local_c;
  _this = extraout_ECX;
LAB_100140a0:
  atoi(_this);
  return;
}
#endif /* _resolve_codepage */




unsigned int __cdecl _is_known_sortid(short param_1)

{
  short *psVar1;
  
  psVar1 = (short int*)&DAT_100223e4;
  do {
    if (param_1 == *psVar1) {
      return 0;
    }
    psVar1 = psVar1 + 1;
  } while ((intptr_t)psVar1 < 0x100223f8);
  return 1;
}



#if 0
unsigned int __cdecl _enum_lcid_match(int param_1,int param_2)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  char local_7c [120];
  
  iVar1 = (*DAT_10023850)((ushort)param_1 & 0x3ff | 0x400,1,local_7c,0x78);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = _str2lcid(local_7c);
  if ((param_1 != iVar1) && (param_2 != 0)) {
    sVar2 = _alpha_len(DAT_10023840);
    sVar3 = _strlen(DAT_10023840);
    if (sVar2 == sVar3) {
      return 0;
    }
  }
  return 1;
}
#endif /* _enum_lcid_match */




unsigned int _is_nt(void)

{
  BOOL BVar1;
  struct _OSVERSIONINFOA local_98;
  
  local_98.dwOSVersionInfoSize = 0x94;
  BVar1 = GetVersionExA(&local_98);
  if ((BVar1 != 0) && (local_98.dwPlatformId == 2)) {
    return 1;
  }
  return 0;
}
#if 0 /* CRT: _localeinfo_table */



#if 0
int _localeinfo_table(uint param_1,LCTYPE param_2,char *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *_Source;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0x1a;
  do {
    iVar2 = (iVar3 + iVar4) / 2;
    uVar1 = *(uint *)(iVar2 * 0x2c + 0x10021f40);
    if (param_1 == uVar1) {
      if (param_2 == 1) {
        _Source = &DAT_10021f44 + iVar2 * 0x2c;
      }
      else if (param_2 == 3) {
        _Source = &DAT_10021f50 + iVar2 * 0x2c;
      }
      else if (param_2 == 7) {
        _Source = &DAT_10021f58 + iVar2 * 0x2c;
      }
      else if (param_2 == 0xb) {
        _Source = &DAT_10021f5c + iVar2 * 0x2c;
      }
      else if (param_2 == 0x1001) {
        _Source = *(char **)(iVar2 * 0x2c + 0x10021f4c);
      }
      else if (param_2 == 0x1002) {
        _Source = *(char **)(iVar2 * 0x2c + 0x10021f54);
      }
      else {
        if (param_2 != 0x1004) break;
        _Source = &DAT_10021f64 + iVar2 * 0x2c;
      }
      if ((_Source != (char *)0x0) && (0 < param_4)) {
        _strncpy(param_3,_Source,param_4 - 1);
        param_3[param_4 + -1] = '\0';
        return 1;
      }
      break;
    }
    if (param_1 < uVar1) {
      iVar3 = iVar2 + -1;
    }
    else {
      iVar4 = iVar2 + 1;
    }
  } while (iVar4 <= iVar3);
  iVar3 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
  return iVar3;
}
#endif /* _localeinfo_table */

#endif




int __cdecl _str2lcid(char *param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = 0;
  while( true ) {
    cVar2 = *param_1;
    param_1 = param_1 + 1;
    if (cVar2 == '\0') break;
    if ((cVar2 < 'a') || ('f' < cVar2)) {
      if (('@' < cVar2) && (cVar2 < 'G')) {
        cVar2 = cVar2 + -7;
      }
    }
    else {
      cVar2 = cVar2 + -0x27;
    }
    iVar1 = (iVar1 + 0xffffffd) * 0x10 + (intptr_t)cVar2;
  }
  return iVar1;
}



int __cdecl _alpha_len(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    if (((cVar1 < 'A') || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}



// Library Function - Single Match
//  __mbsnbicoll
// 
// Library: Visual Studio 2003 Release

int __cdecl __mbsnbicoll(unsigned char *_Str1,unsigned char *_Str2,size_t _MaxCount)

{
  int iVar1;
  
  if (_MaxCount == 0) {
    return 0;
  }
  iVar1 = _strcoll_core(DAT_10023b24,1,_Str1,_MaxCount,_Str2,_MaxCount,CodePage_10023898);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}



#if 0
unsigned int _wide_env_sync(void)

{
  LPCWSTR lpWideCharStr;
  size_t _Size;
  uint *lpMultiByteStr;
  int iVar1;
  unsigned int *puVar2;
  
  lpWideCharStr = (LPCWSTR)*DAT_10023508;
  puVar2 = DAT_10023508;
  while( true ) {
    if (lpWideCharStr == (LPCWSTR)0x0) {
      return 0;
    }
    _Size = WideCharToMultiByte(1,0,lpWideCharStr,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (((_Size == 0) || (lpMultiByteStr = _malloc(_Size), lpMultiByteStr == (uint *)0x0)) ||
       (iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*puVar2,-1,(LPSTR)lpMultiByteStr,_Size,(LPCSTR)0x0,
                                    (LPBOOL)0x0), iVar1 == 0)) break;
    _putenv(lpMultiByteStr,0);
    lpWideCharStr = (LPCWSTR)puVar2[1];
    puVar2 = puVar2 + 1;
  }
  return 0xffffffff;
}
#endif /* _wide_env_sync */




#if 0
void __cdecl _ldmul(int *param_1,int *param_2)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  ushort uVar9;
  uint uVar10;
  ushort uVar11;
  byte local_28;
  unsigned char uStack_27;
  unsigned short uStack_26;
  short local_24;
  unsigned short uStack_22;
  unsigned short local_20;
  unsigned char uStack_1e;
  byte bStack_1d;
  int *local_1c;
  int local_18;
  int local_14;
  ushort *local_10;
  ushort *local_c;
  short *local_8;
  
  piVar5 = param_2;
  piVar4 = param_1;
  local_18 = 0;
  local_28 = 0;
  uStack_27 = 0;
  uStack_26 = 0;
  local_24 = 0;
  uStack_22 = 0;
  local_20 = 0;
  uStack_1e = 0;
  bStack_1d = 0;
  uVar7 = *(ushort *)((intptr_t)param_1 + 10) & 0x7fff;
  uVar10 = *(ushort *)((intptr_t)param_2 + 10) & 0x7fff;
  uVar11 = (*(ushort *)((intptr_t)param_2 + 10) ^ *(ushort *)((intptr_t)param_1 + 10)) & 0x8000;
  uVar6 = (ushort)uVar7;
  piVar1 = (int *)(uVar10 + uVar7);
  if (((uVar6 < 0x7fff) && (uVar9 = (ushort)uVar10, uVar9 < 0x7fff)) && ((ushort)piVar1 < 0xbffe)) {
    if ((ushort)piVar1 < 0x3fc0) {
LAB_100143f1:
      piVar4[2] = 0;
      piVar4[1] = 0;
      *piVar4 = 0;
      return;
    }
    if (((uVar6 != 0) || (piVar1 = (int *)((intptr_t)piVar1 + 1), (param_1[2] & 0x7fffffffU) != 0)) ||
       ((uVar6 = 0, param_1[1] != 0 || (*param_1 != 0)))) {
      param_1 = piVar1;
      if (((uVar9 == 0) && (param_1 = (int *)((intptr_t)param_1 + 1), (param_2[2] & 0x7fffffffU) == 0))
         && ((param_2[1] == 0 && (*param_2 == 0)))) goto LAB_100143f1;
      local_14 = 0;
      local_8 = &local_24;
      param_2 = (int *)0x5;
      do {
        if (0 < (intptr_t)param_2) {
          local_c = (ushort *)(local_14 * 2 + (intptr_t)piVar4);
          local_10 = (ushort *)(piVar5 + 2);
          local_1c = param_2;
          do {
            iVar8 = _add_carry(*(uint *)(local_8 + -2),(uintptr_t)*local_c * (uintptr_t)*local_10,
                               (uint *)(local_8 + -2));
            if (iVar8 != 0) {
              *local_8 = *local_8 + 1;
            }
            local_c = local_c + 1;
            local_10 = local_10 + -1;
            local_1c = (int *)((intptr_t)local_1c + -1);
          } while (local_1c != (int *)0x0);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
        param_2 = (int *)((intptr_t)param_2 + -1);
      } while (0 < (intptr_t)param_2);
      param_1 = (int *)((intptr_t)param_1 + 0xc002);
      if ((short)(ushort)param_1 < 1) {
LAB_100144a5:
        (*(unsigned short*)&(param_1)) = (ushort)param_1 - 1;
        if ((short)(ushort)param_1 < 0) {
          iVar8 = -(intptr_t)(short)(ushort)param_1;
          (*(unsigned short*)&(param_1)) = (ushort)param_1 + (short)iVar8;
          do {
            if ((local_28 & 1) != 0) {
              local_18 = local_18 + 1;
            }
            _ldshr1((uint *)&local_28);
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          if (local_18 != 0) {
            local_28 = local_28 | 1;
          }
        }
      }
      else {
        do {
          if ((bStack_1d & 0x80) != 0) break;
          _ldshl1((uint *)&local_28);
          param_1 = (int *)((intptr_t)param_1 + 0xffff);
        } while (0 < (short)(ushort)param_1);
        if ((short)(ushort)param_1 < 1) goto LAB_100144a5;
      }
      if ((0x8000 < CONCAT11(uStack_27,local_28)) ||
         (sVar2 = CONCAT11(bStack_1d,uStack_1e), iVar3 = CONCAT22(local_20,uStack_22),
         iVar8 = CONCAT22(local_24,uStack_26),
         (CONCAT22(uStack_26,CONCAT11(uStack_27,local_28)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_24,uStack_26) == -1) {
          iVar8 = 0;
          if (CONCAT22(local_20,uStack_22) == -1) {
            if (CONCAT11(bStack_1d,uStack_1e) == -1) {
              (*(unsigned short*)&(param_1)) = (ushort)param_1 + 1;
              sVar2 = -0x8000;
              iVar3 = 0;
              iVar8 = 0;
            }
            else {
              sVar2 = CONCAT11(bStack_1d,uStack_1e) + 1;
              iVar3 = 0;
              iVar8 = 0;
            }
          }
          else {
            sVar2 = CONCAT11(bStack_1d,uStack_1e);
            iVar3 = CONCAT22(local_20,uStack_22) + 1;
          }
        }
        else {
          iVar8 = CONCAT22(local_24,uStack_26) + 1;
          sVar2 = CONCAT11(bStack_1d,uStack_1e);
          iVar3 = CONCAT22(local_20,uStack_22);
        }
      }
      local_24 = (short)((uintptr_t)iVar8 >> 0x10);
      uStack_26 = (unsigned short)iVar8;
      local_20 = (unsigned short)((uintptr_t)iVar3 >> 0x10);
      uStack_22 = (unsigned short)iVar3;
      bStack_1d = (byte)((ushort)sVar2 >> 8);
      uStack_1e = (unsigned char)sVar2;
      if (0x7ffe < (ushort)param_1) goto LAB_1001454e;
      uVar6 = (ushort)param_1 | uVar11;
      *(unsigned short *)piVar4 = uStack_26;
      *(uint *)((intptr_t)piVar4 + 2) = CONCAT22(uStack_22,local_24);
      *(uint *)((intptr_t)piVar4 + 6) = CONCAT13(bStack_1d,CONCAT12(uStack_1e,local_20));
    }
    *(ushort *)((intptr_t)piVar4 + 10) = uVar6;
  }
  else {
LAB_1001454e:
    piVar4[1] = 0;
    *piVar4 = 0;
    piVar4[2] = (-(uintptr_t)(uVar11 != 0) & 0x80000000) + 0x7fff8000;
  }
  return;
}
#endif /* _ldmul */




#if 0
void __cdecl _ld10pow(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  unsigned char **ppuVar3;
  unsigned char **ppuVar4;
  unsigned short local_10;
  unsigned int local_e;
  unsigned short uStack_a;
  unsigned char *puStack_8;
  
  ppuVar3 = &PTR_s_November_10022750;
  if (param_2 != 0) {
    if ((intptr_t)param_2 < 0) {
      param_2 = -param_2;
      ppuVar3 = (unsigned char **)0x100228b0;
    }
    if (param_3 == 0) {
      *(unsigned short *)param_1 = 0;
    }
    while (param_2 != 0) {
      ppuVar3 = ppuVar3 + 0x15;
      uVar1 = (intptr_t)param_2 >> 3;
      uVar2 = param_2 & 7;
      param_2 = uVar1;
      if (uVar2 != 0) {
        ppuVar4 = ppuVar3 + uVar2 * 3;
        if (0x7fff < *(ushort *)(ppuVar3 + uVar2 * 3)) {
          local_10 = SUB42(*ppuVar4,0);
          (*(unsigned short*)&(local_e)) = (unsigned short)((uintptr_t)*ppuVar4 >> 0x10);
          (*(unsigned short*)((char*)&(local_e)+2)) = SUB42(ppuVar4[1],0);
          uStack_a = (unsigned short)((uintptr_t)ppuVar4[1] >> 0x10);
          puStack_8 = ppuVar4[2];
          local_e = CONCAT22((*(unsigned short*)((char*)&(local_e)+2)),(unsigned short)local_e) + -1;
          ppuVar4 = (unsigned char **)&local_10;
        }
        _ldmul(param_1,(int *)ppuVar4);
      }
    }
  }
  return;
}
#endif /* _ld10pow */




#if 0
unsigned int __cdecl _close(uint param_1)

{
  unsigned int uVar1;
  DWORD *pDVar2;
  
  if ((param_1 < uNumber_10024ffc) &&
     ((*(byte *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) & 1) != 0)) {
    _lock_fh(param_1);
    uVar1 = _close_nolock(param_1);
    _unlock_fh(param_1);
    return uVar1;
  }
  pDVar2 = _errno();
  *pDVar2 = 9;
  pDVar2 = _doserrno_impl();
  *pDVar2 = 0;
  return 0xffffffff;
}
#endif /* _close */




#if 0
unsigned int __cdecl _close_nolock(uint param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD DVar4;
  unsigned int uVar5;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = _get_osfhandle(2);
      iVar2 = _get_osfhandle(1);
      if (iVar2 == iVar1) goto LAB_10014695;
    }
    hObject = (HANDLE)_get_osfhandle(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      DVar4 = GetLastError();
      goto LAB_10014697;
    }
  }
LAB_10014695:
  DVar4 = 0;
LAB_10014697:
  _freefd(param_1);
  *(unsigned char *)((&DAT_10024ec0)[(intptr_t)param_1 >> 5] + 4 + (param_1 & 0x1f) * 0x24) = 0;
  if (DVar4 == 0) {
    uVar5 = 0;
  }
  else {
    _dosmaperr(DVar4);
    uVar5 = 0xffffffff;
  }
  return uVar5;
}
#endif /* _close_nolock */




void __cdecl _freebuf(unsigned int *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    free((LPVOID)param_1[2]);
    *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) & 0xfbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}



unsigned char * _c_locale_daystrs(void)

{
  size_t sVar1;
  size_t sVar2;
  unsigned char *puVar3;
  uint *puVar4;
  int iVar5;
  unsigned int *puVar6;
  unsigned char *puVar7;
  uint *puVar8;
  unsigned int *puVar9;
  int local_8;
  
  puVar9 = (unsigned int *)PTR_PTR_100226b8;
  iVar5 = 0;
  local_8 = 7;
  puVar6 = (unsigned int *)PTR_PTR_100226b8;
  do {
    sVar1 = _strlen((char *)puVar6[7]);
    sVar2 = _strlen((char *)*puVar6);
    puVar6 = puVar6 + 1;
    local_8 = local_8 + -1;
    iVar5 = sVar2 + iVar5 + 2 + sVar1;
  } while (local_8 != 0);
  puVar3 = _malloc(iVar5 + 1);
  if (puVar3 != (unsigned char *)0x0) {
    iVar5 = 7;
    puVar7 = puVar3;
    do {
      *puVar7 = 0x3a;
      puVar4 = (uint *)strcpy((char*)(puVar7 + 1),(char*)*puVar9);
      sVar1 = _strlen((char *)puVar4);
      puVar7 = (unsigned char *)((intptr_t)(puVar7 + 1) + sVar1);
      *puVar7 = 0x3a;
      puVar8 = (uint *)(puVar7 + 1);
      puVar4 = (uint *)strcpy((char*)puVar8,(char*)puVar9[7]);
      sVar1 = _strlen((char *)puVar4);
      puVar7 = (unsigned char *)((intptr_t)puVar8 + sVar1);
      puVar9 = puVar9 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    *puVar7 = 0;
  }
  return puVar3;
}



unsigned char * _c_locale_monthstrs(void)

{
  unsigned char *puVar1;
  size_t sVar2;
  size_t sVar3;
  unsigned char *puVar4;
  uint *puVar5;
  int iVar6;
  unsigned char *puVar7;
  uint *puVar8;
  unsigned int *puVar9;
  int local_c;
  int local_8;
  
  puVar1 = (unsigned char*)PTR_PTR_100226b8;
  local_8 = 0;
  local_c = 0xc;
  puVar9 = (unsigned int *)(PTR_PTR_100226b8 + 0x38);
  do {
    sVar2 = _strlen((char *)puVar9[0xc]);
    sVar3 = _strlen((char *)*puVar9);
    puVar9 = puVar9 + 1;
    local_c = local_c + -1;
    local_8 = sVar3 + local_8 + 2 + sVar2;
  } while (local_c != 0);
  puVar4 = _malloc(local_8 + 1);
  if (puVar4 != (unsigned char *)0x0) {
    puVar9 = (unsigned int *)(puVar1 + 0x68);
    iVar6 = 0xc;
    puVar7 = puVar4;
    do {
      *puVar7 = 0x3a;
      puVar5 = (uint *)strcpy((char*)(puVar7 + 1),(char*)puVar9[-0xc]);
      sVar2 = _strlen((char *)puVar5);
      puVar7 = (unsigned char *)((intptr_t)(puVar7 + 1) + sVar2);
      *puVar7 = 0x3a;
      puVar8 = (uint *)(puVar7 + 1);
      puVar5 = (uint *)strcpy((char*)puVar8,(char*)*puVar9);
      sVar2 = _strlen((char *)puVar5);
      puVar7 = (unsigned char *)((intptr_t)puVar8 + sVar2);
      puVar9 = puVar9 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    *puVar7 = 0;
  }
  return puVar4;
}



unsigned int * _c_locale_full(void)

{
  unsigned char *puVar1;
  size_t sVar2;
  size_t sVar3;
  size_t sVar4;
  size_t sVar5;
  size_t sVar6;
  unsigned int *puVar7;
  uint *puVar8;
  unsigned int *puVar9;
  int iVar10;
  uint *puVar11;
  int local_14;
  unsigned int *local_10;
  unsigned int *local_c;
  unsigned int *local_8;
  
  puVar1 = (unsigned char*)PTR_PTR_100226b8;
  iVar10 = 0;
  local_c = (unsigned int *)PTR_PTR_100226b8;
  local_10 = (unsigned int *)0x7;
  do {
    sVar2 = _strlen((char *)local_c[7]);
    sVar3 = _strlen((char *)*local_c);
    local_c = local_c + 1;
    local_10 = (unsigned int *)((intptr_t)local_10 + -1);
    iVar10 = sVar3 + iVar10 + 2 + sVar2;
  } while (local_10 != (unsigned int *)0x0);
  local_c = (unsigned int *)(puVar1 + 0x38);
  local_10 = (unsigned int *)0xc;
  do {
    sVar2 = _strlen((char *)local_c[0xc]);
    sVar3 = _strlen((char *)*local_c);
    local_c = local_c + 1;
    local_10 = (unsigned int *)((intptr_t)local_10 + -1);
    iVar10 = sVar3 + iVar10 + 2 + sVar2;
  } while (local_10 != (unsigned int *)0x0);
  sVar2 = _strlen(*(char **)(puVar1 + 0x98));
  sVar3 = _strlen(*(char **)(puVar1 + 0x9c));
  sVar4 = _strlen(*(char **)(puVar1 + 0xa0));
  sVar5 = _strlen(*(char **)(puVar1 + 0xa4));
  sVar6 = _strlen(*(char **)(puVar1 + 0xa8));
  puVar7 = _malloc(sVar3 + iVar10 + sVar2 + sVar4 + sVar5 + sVar6 + 0xb1);
  if (puVar7 != (unsigned int *)0x0) {
    puVar11 = puVar7 + 0x2b;
    memmove(puVar7,(unsigned int *)PTR_PTR_100226b8,0xac);
    local_8 = (unsigned int *)(puVar1 + 0x1c);
    local_14 = 7;
    local_10 = puVar7;
    do {
      *local_10 = puVar11;
      puVar8 = (uint *)strcpy((char*)puVar11,(char*)local_8[-7]);
      sVar2 = _strlen((char *)puVar8);
      puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
      *(uint **)(((intptr_t)puVar7 - (intptr_t)puVar1) + (intptr_t)local_8) = puVar11;
      puVar8 = (uint *)strcpy((char*)puVar11,(char*)*local_8);
      sVar2 = _strlen((char *)puVar8);
      local_10 = local_10 + 1;
      local_8 = local_8 + 1;
      local_14 = local_14 + -1;
      puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
    } while (local_14 != 0);
    local_10 = puVar7 + 0x1a;
    local_14 = 0xc;
    puVar9 = (unsigned int *)(puVar1 + 0x38);
    do {
      *(uint **)((intptr_t)puVar9 + ((intptr_t)puVar7 - (intptr_t)puVar1)) = puVar11;
      puVar8 = (uint *)strcpy((char*)puVar11,(char*)*puVar9);
      sVar2 = _strlen((char *)puVar8);
      puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
      *local_10 = puVar11;
      puVar8 = (uint *)strcpy((char*)puVar11,(char*)puVar9[0xc]);
      sVar2 = _strlen((char *)puVar8);
      puVar9 = puVar9 + 1;
      local_10 = local_10 + 1;
      local_14 = local_14 + -1;
      puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
    } while (local_14 != 0);
    puVar7[0x26] = puVar11;
    puVar8 = (uint *)strcpy((char*)puVar11,(const char*)*(puVar1 + 0x98));
    sVar2 = _strlen((char *)puVar8);
    puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
    puVar7[0x27] = puVar11;
    puVar8 = (uint *)strcpy((char*)puVar11,(const char*)*(puVar1 + 0x9c));
    sVar2 = _strlen((char *)puVar8);
    puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
    puVar7[0x28] = puVar11;
    puVar8 = (uint *)strcpy((char*)puVar11,(const char*)*(puVar1 + 0xa0));
    sVar2 = _strlen((char *)puVar8);
    puVar11 = (uint *)((intptr_t)puVar11 + sVar2 + 1);
    puVar7[0x29] = puVar11;
    puVar8 = (uint *)strcpy((char*)puVar11,(const char*)*(puVar1 + 0xa4));
    sVar2 = _strlen((char *)puVar8);
    puVar7[0x2a] = sVar2 + 1 + (intptr_t)puVar11;
  }
  return puVar7;
}



#if 0
int __cdecl strftime(byte *param_1,uint param_2,byte *param_3,int *param_4,unsigned char *param_5)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int bVar4;
  uint local_8;
  
  local_8 = param_2;
  InterlockedIncrement(&DAT_10023894);
  bVar4 = DAT_10023884 == 0;
  if (!bVar4) {
    InterlockedDecrement(&DAT_10023894);
    _lock_critical_section(0x13);
  }
  pbVar2 = param_3;
  if (param_5 == (unsigned char *)0x0) {
    param_5 = PTR_PTR_100226b8;
  }
  while ((local_8 != 0 && (bVar1 = *pbVar2, bVar1 != 0))) {
    if (bVar1 == 0x25) {
      pbVar3 = pbVar2 + 1;
      bVar1 = *pbVar3;
      if (bVar1 == 0x23) {
        pbVar3 = pbVar2 + 2;
      }
      DAT_10023870 = (uintptr_t)(bVar1 == 0x23);
      _strftime_spec(*pbVar3,param_4,(byte *)&param_1,&local_8,(intptr_t)param_5);
    }
    else {
      if (((PTR_DAT_10021780[(uintptr_t)bVar1 * 2 + 1] & 0x80) != 0) && (1 < local_8)) {
        *param_1 = bVar1;
        param_1 = param_1 + 1;
        pbVar2 = pbVar2 + 1;
        local_8 = local_8 - 1;
      }
      *param_1 = *pbVar2;
      param_1 = param_1 + 1;
      local_8 = local_8 - 1;
      pbVar3 = pbVar2;
    }
    pbVar2 = pbVar3 + 1;
  }
  if (bVar4) {
    InterlockedDecrement(&DAT_10023894);
  }
  else {
    _unlock_critical_section(0x13);
  }
  if (local_8 == 0) {
    return 0;
  }
  *param_1 = 0;
  return param_2 - local_8;
}
#endif /* strftime */




void __cdecl _strftime_spec(char param_1,int *param_2,byte *param_3,uint *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  char *pcVar6;
  
  if (param_1 < '[') {
    if (param_1 != 'Z') {
      if ('M' < param_1) {
        if (param_1 == 'S') {
          uVar5 = 2;
          iVar2 = *param_2;
        }
        else {
          if (param_1 == 'U') {
            iVar3 = param_2[6];
          }
          else {
            if (param_1 != 'W') {
              if (param_1 == 'X') {
                DAT_10023870 = 0;
                pbVar4 = *(byte **)(param_5 + 0xa8);
                goto LAB_10014ee6;
              }
              if (param_1 != 'Y') {
                return;
              }
              uVar5 = 4;
              iVar2 = (param_2[5] / 100 + 0x13) * 100 + param_2[5] % 100;
              goto LAB_10014c9c;
            }
            if (param_2[6] == 0) {
              iVar3 = 6;
            }
            else {
              iVar3 = param_2[6] + -1;
            }
          }
          iVar1 = param_2[7];
          if (iVar1 < iVar3) {
            iVar2 = 0;
          }
          else {
            iVar2 = iVar1 / 7;
            if (iVar3 <= iVar1 % 7) {
              iVar2 = iVar2 + 1;
            }
          }
          uVar5 = 2;
        }
        goto LAB_10014c9c;
      }
      if (param_1 == 'M') {
        uVar5 = 2;
        iVar2 = param_2[1];
        goto LAB_10014c9c;
      }
      if (param_1 == '%') {
        **(unsigned char **)param_3 = 0x25;
        *(int *)param_3 = *(int *)param_3 + 1;
        *param_4 = *param_4 - 1;
        return;
      }
      if (param_1 == 'A') {
        pcVar6 = *(char **)(param_5 + 0x1c + param_2[6] * 4);
        goto LAB_10014f42;
      }
      if (param_1 == 'B') {
        pcVar6 = *(char **)(param_5 + 0x68 + param_2[4] * 4);
        goto LAB_10014f42;
      }
      if (param_1 == 'H') {
        uVar5 = 2;
        iVar2 = param_2[2];
        goto LAB_10014c9c;
      }
      if (param_1 != 'I') {
        return;
      }
      iVar2 = param_2[2] % 0xc;
      if (iVar2 == 0) {
        iVar2 = 0xc;
      }
LAB_10014bc9:
      uVar5 = 2;
LAB_10014c9c:
      DAT_10023880 = DAT_10023870;
      _fmt_dec_out(iVar2,uVar5,(int *)param_3,param_4);
      return;
    }
  }
  else {
    if (param_1 < 'n') {
      if (param_1 == 'm') {
        iVar2 = param_2[4];
        uVar5 = 2;
      }
      else {
        if (param_1 == 'a') {
          pcVar6 = *(char **)(param_5 + param_2[6] * 4);
          goto LAB_10014f42;
        }
        if (param_1 == 'b') {
          pcVar6 = *(char **)(param_5 + 0x38 + param_2[4] * 4);
          goto LAB_10014f42;
        }
        if (param_1 == 'c') {
          if (DAT_10023870 == 0) {
            pbVar4 = *(byte **)(param_5 + 0xa0);
          }
          else {
            DAT_10023870 = 0;
            pbVar4 = *(byte **)(param_5 + 0xa4);
          }
          _fmt_locale_time((char*)pbVar4,(int)param_2,(int *)param_3,param_4,param_5);
          if (*param_4 == 0) {
            return;
          }
          **(unsigned char **)param_3 = 0x20;
          *(int *)param_3 = *(int *)param_3 + 1;
          *param_4 = *param_4 - 1;
          pbVar4 = *(byte **)(param_5 + 0xa8);
          goto LAB_10014ee6;
        }
        if (param_1 == 'd') {
          uVar5 = 2;
          iVar2 = param_2[3];
          goto LAB_10014c9c;
        }
        if (param_1 != 'j') {
          return;
        }
        iVar2 = param_2[7];
        uVar5 = 3;
      }
      iVar2 = iVar2 + 1;
      goto LAB_10014c9c;
    }
    if (param_1 == 'p') {
      if (param_2[2] < 0xc) {
        pcVar6 = *(char **)(param_5 + 0x98);
      }
      else {
        pcVar6 = *(char **)(param_5 + 0x9c);
      }
      goto LAB_10014f42;
    }
    if (param_1 == 'w') {
      uVar5 = 1;
      iVar2 = param_2[6];
      goto LAB_10014c9c;
    }
    if (param_1 == 'x') {
      if (DAT_10023870 == 0) {
        pbVar4 = *(byte **)(param_5 + 0xa0);
      }
      else {
        DAT_10023870 = 0;
        pbVar4 = *(byte **)(param_5 + 0xa4);
      }
LAB_10014ee6:
      _fmt_locale_time((char*)pbVar4,(int)param_2,(int *)param_3,param_4,param_5);
      return;
    }
    if (param_1 == 'y') {
      iVar2 = param_2[5] % 100;
      goto LAB_10014bc9;
    }
    if (param_1 != 'z') {
      return;
    }
  }
  _init_time();
  pcVar6 = ((char*)&lpMultiByteStr_10021aa4)[param_2[8] != 0];
LAB_10014f42:
  _fmt_str_out(pcVar6,(int *)param_3,(int *)param_4);
  return;
}



void __cdecl _fmt_str_out(char *param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  for (; (iVar1 != 0 && (*param_1 != '\0')); param_1 = param_1 + 1) {
    *(char *)*param_2 = *param_1;
    *param_2 = *param_2 + 1;
    *param_3 = *param_3 + -1;
    iVar1 = *param_3;
  }
  return;
}



void __cdecl _fmt_dec_out(int param_1,uint param_2,int *param_3,uint *param_4)

{
  int iVar1;
  unsigned int local_8;
  
  local_8 = 0;
  if (DAT_10023880 == 0) {
    if (param_2 < *param_4) {
      iVar1 = param_2 - 1;
      if (param_2 != 0) {
        do {
          *(char *)(*param_3 + iVar1) = (char)(param_1 % 10) + '0';
          param_1 = param_1 / 10;
          local_8 = local_8 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != -1);
      }
      *param_3 = *param_3 + local_8;
      *param_4 = *param_4 - local_8;
    }
    else {
      *param_4 = 0;
    }
  }
  else {
    _fmt_dec_out_lz(param_1,param_3,param_4);
  }
  return;
}



void __cdecl _fmt_dec_out_lz(int param_1,int *param_2,uint *param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = (char *)*param_2;
  do {
    if (*param_3 < 2) break;
    *pcVar3 = (char)(param_1 % 10) + '0';
    pcVar3 = pcVar3 + 1;
    param_1 = param_1 / 10;
    *param_3 = *param_3 - 1;
  } while (0 < param_1);
  pcVar2 = (char *)*param_2;
  *param_2 = (intptr_t)pcVar3;
  pcVar3 = pcVar3 + -1;
  do {
    cVar1 = *pcVar3;
    *pcVar3 = *pcVar2;
    pcVar3 = pcVar3 + -1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (pcVar2 < pcVar3);
  return;
}



#if 0
void __cdecl _fmt_locale_time(byte *param_1,int param_2,byte *param_3,uint *param_4,int param_5)

{
  byte bVar1;
  byte *pbVar2;
  uint *puVar3;
  uint uVar4;
  byte *pbVar5;
  void *pvVar6;
  void *_this;
  char *this_00;
  
  puVar3 = param_4;
  pbVar2 = param_3;
  bVar1 = *param_1;
  do {
    if ((bVar1 == 0) || (*puVar3 == 0)) {
      return;
    }
    DAT_10023880 = 0;
    bVar1 = *param_1;
    _this = (void *)0x0;
    pbVar5 = param_1 + 1;
    do {
      param_3 = pbVar5;
      pvVar6 = _this;
      _this = (void *)((intptr_t)pvVar6 + 1);
      pbVar5 = param_3 + 1;
    } while (*param_3 == bVar1);
    if ((char)bVar1 < 'e') {
      if (bVar1 == 100) {
        if (pvVar6 == (void *)0x0) {
          DAT_10023880 = 1;
        }
        else if (pvVar6 != (void *)0x1) {
          if (pvVar6 == (void *)0x2) {
            (*(unsigned short*)&(param_4)) = 'a';
          }
          else {
            if (pvVar6 != (void *)0x3) goto LAB_100150b2;
            (*(unsigned short*)&(param_4)) = 'A';
          }
          goto LAB_100152e8;
        }
        (*(unsigned short*)&(param_4)) = 'd';
        goto LAB_100152e8;
      }
      if (bVar1 != 0x27) {
        if (bVar1 != 0x41) {
          if (bVar1 == 0x48) {
            if (pvVar6 == (void *)0x0) {
              DAT_10023880 = 1;
            }
            else if (_this != (void *)0x2) goto LAB_100150b2;
            (*(unsigned short*)&(param_4)) = 'H';
            goto LAB_100152e8;
          }
          if (bVar1 == 0x4d) {
            if (pvVar6 == (void *)0x0) {
              DAT_10023880 = 1;
            }
            else if (pvVar6 != (void *)0x1) {
              if (pvVar6 == (void *)0x2) {
                (*(unsigned short*)&(param_4)) = 'b';
              }
              else {
                if (pvVar6 != (void *)0x3) goto LAB_100150b2;
                (*(unsigned short*)&(param_4)) = 'B';
              }
              goto LAB_100152e8;
            }
            (*(unsigned short*)&(param_4)) = 'm';
            goto LAB_100152e8;
          }
          if (bVar1 != 0x61) goto LAB_100150b2;
        }
        this_00 = "am/pm";
        uVar4 = _stricmp(_this, param_1)"am/pm");
        if (uVar4 == 0) {
          param_3 = param_1 + 5;
        }
        else {
          uVar4 = _stricmp(this_00);
          if (uVar4 == 0) {
            param_3 = param_1 + 3;
          }
        }
        (*(unsigned short*)&(param_4)) = 'p';
        goto LAB_100152e8;
      }
      if (((uintptr_t)_this & 1) == 0) {
        param_3 = param_1 + (intptr_t)_this;
      }
      else {
        param_3 = param_1 + (intptr_t)_this;
        while( true ) {
          bVar1 = *param_3;
          if ((bVar1 == 0) || (*puVar3 == 0)) goto LAB_100150d8;
          if (bVar1 == 0x27) break;
          if (((PTR_DAT_10021780[(uintptr_t)bVar1 * 2 + 1] & 0x80) != 0) && (1 < *puVar3)) {
            **(byte **)pbVar2 = bVar1;
            *(int *)pbVar2 = *(int *)pbVar2 + 1;
            param_3 = param_3 + 1;
            *puVar3 = *puVar3 - 1;
          }
          **(byte **)pbVar2 = *param_3;
          *(int *)pbVar2 = *(int *)pbVar2 + 1;
          param_3 = param_3 + 1;
          *puVar3 = *puVar3 - 1;
        }
        param_3 = param_3 + 1;
      }
    }
    else {
      if (bVar1 == 0x68) {
        if (pvVar6 == (void *)0x0) {
          DAT_10023880 = 1;
        }
        else if (_this != (void *)0x2) goto LAB_100150b2;
        (*(unsigned short*)&(param_4)) = 'I';
      }
      else if (bVar1 == 0x6d) {
        if (pvVar6 == (void *)0x0) {
          DAT_10023880 = 1;
        }
        else if (_this != (void *)0x2) goto LAB_100150b2;
        (*(unsigned short*)&(param_4)) = 'M';
      }
      else if (bVar1 == 0x73) {
        if (pvVar6 == (void *)0x0) {
          DAT_10023880 = 1;
        }
        else if (_this != (void *)0x2) goto LAB_100150b2;
        (*(unsigned short*)&(param_4)) = 'S';
      }
      else {
        if (bVar1 == 0x74) {
          if (*(int *)(param_2 + 8) < 0xc) {
            pbVar5 = *(byte **)(param_5 + 0x98);
          }
          else {
            pbVar5 = *(byte **)(param_5 + 0x9c);
          }
          while ((0 < (intptr_t)_this && (*puVar3 != 0))) {
            if (((PTR_DAT_10021780[(uintptr_t)*pbVar5 * 2 + 1] & 0x80) != 0) && (1 < *puVar3)) {
              **(byte **)pbVar2 = *pbVar5;
              *(int *)pbVar2 = *(int *)pbVar2 + 1;
              pbVar5 = pbVar5 + 1;
              *puVar3 = *puVar3 - 1;
            }
            **(byte **)pbVar2 = *pbVar5;
            *(int *)pbVar2 = *(int *)pbVar2 + 1;
            pbVar5 = pbVar5 + 1;
            *puVar3 = *puVar3 - 1;
            _this = (void *)((intptr_t)_this + -1);
          }
          goto LAB_100150d8;
        }
        if (bVar1 != 0x79) {
LAB_100150b2:
          if ((PTR_DAT_10021780[(uintptr_t)bVar1 * 2 + 1] & 0x80) != 0) {
            **(byte **)pbVar2 = bVar1;
            *(int *)pbVar2 = *(int *)pbVar2 + 1;
            *puVar3 = *puVar3 - 1;
            param_1 = param_1 + 1;
          }
          **(byte **)pbVar2 = *param_1;
          *(int *)pbVar2 = *(int *)pbVar2 + 1;
          param_3 = param_1 + 1;
          *puVar3 = *puVar3 - 1;
          goto LAB_100150d8;
        }
        if (pvVar6 == (void *)0x1) {
          (*(unsigned short*)&(param_4)) = 'y';
        }
        else {
          if (pvVar6 != (void *)0x3) goto LAB_100150b2;
          (*(unsigned short*)&(param_4)) = 'Y';
        }
      }
LAB_100152e8:
      _strftime_spec((char)param_4,(int *)param_2,pbVar2,puVar3,param_5);
    }
LAB_100150d8:
    bVar1 = *param_3;
    param_1 = param_3;
  } while( true );
}
#endif /* _fmt_locale_time */




#if 0
unsigned int __cdecl _getlocaleinfo(int param_1,LCID param_2,LCTYPE param_3,char *param_4)

{
  byte bVar1;
  int bVar2;
  size_t sVar3;
  DWORD DVar4;
  CHAR *_Source;
  char *_Dest;
  int iVar5;
  uint uVar6;
  void *extraout_ECX;
  unsigned char *puVar7;
  void *_this;
  byte *pbVar8;
  CHAR local_84 [128];
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    pbVar8 = &DAT_10023854;
    iVar5 = __crtGetLocaleInfoW(param_2,param_3,(LPWSTR)&DAT_10023854,4,0);
    if (iVar5 != 0) {
      *param_4 = '\0';
      _this = extraout_ECX;
      while( true ) {
        bVar1 = *pbVar8;
        if (cbMultiByte_10021b40 < 2) {
          uVar6 = (byte)PTR_DAT_10021780[(uintptr_t)bVar1 * 2] & 4;
          puVar7 = PTR_DAT_10021780;
        }
        else {
          puVar7 = (unsigned char *)0x0;
          uVar6 = iswctype(_this, (uintptr_t)bVar1);
        }
        if (uVar6 == 0) break;
        _this = (void *)CONCAT31((int3)((uintptr_t)puVar7 >> 8),10);
        pbVar8 = pbVar8 + 2;
        *param_4 = *param_4 * '\n' + bVar1 + -0x30;
        if (0x1002385b < (intptr_t)pbVar8) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  _Source = local_84;
  bVar2 = false;
  sVar3 = __crtGetLocaleInfoA(param_2,param_3,local_84,0x80,0);
  if (sVar3 == 0) {
    DVar4 = GetLastError();
    if (DVar4 != 0x7a) {
      return 0xffffffff;
    }
    sVar3 = __crtGetLocaleInfoA(param_2,param_3,(LPSTR)0x0,0,0);
    if (sVar3 == 0) {
      return 0xffffffff;
    }
    _Source = _malloc(sVar3);
    if (_Source == (LPSTR)0x0) {
      return 0xffffffff;
    }
    bVar2 = true;
    sVar3 = __crtGetLocaleInfoA(param_2,param_3,_Source,sVar3,0);
    if (sVar3 == 0) goto LAB_1001539b;
  }
  _Dest = _malloc(sVar3);
  *(char **)param_4 = _Dest;
  if (_Dest != (char *)0x0) {
    _strncpy(_Dest,_Source,sVar3);
    if (bVar2) {
      free(_Source);
    }
    return 0;
  }
  if (!bVar2) {
    return 0xffffffff;
  }
LAB_1001539b:
  free(_Source);
  return 0xffffffff;
}
#endif /* _getlocaleinfo */




BOOL __cdecl
_getstringtype_w(DWORD param_1,LPCWSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  unsigned char *puVar1;
  BOOL BVar2;
  size_t _Size;
  int iVar3;
  WORD local_20 [2];
  unsigned char *local_1c;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001cd68;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  local_1c = (unsigned char*)&uStack00000000;
  iVar3 = DAT_10023860;
  pExceptionList = &local_14;
  puVar1 = (unsigned char*)&uStack00000000;
  if (DAT_10023860 == 0) {
    pExceptionList = &local_14;
    BVar2 = GetStringTypeW(1,(LPCWSTR)&lpSrcStr_1001c564,1,local_20);
    iVar3 = 1;
    puVar1 = local_1c;
    if (BVar2 == 0) {
      BVar2 = GetStringTypeA(0,1,(LPCSTR)&lpSrcStr_1001c560,1,local_20);
      if (BVar2 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      iVar3 = 2;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  DAT_10023860 = iVar3;
  if (DAT_10023860 != 1) {
    if (DAT_10023860 == 2) {
      if (param_5 == 0) {
        param_5 = CodePage_100237cc;
      }
      _Size = WideCharToMultiByte(param_5,0x220,param_2,param_3,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0
                                 );
      if (_Size != 0) {
        local_8 = 0;
        _alloca_probe();
        local_1c = (unsigned char*)&uStack00000000;
        _memset(&uStack00000000,0,_Size);
        local_8 = 0xffffffff;
        if (&uStack00000000 != (unsigned char *)0x3c) {
          iVar3 = WideCharToMultiByte((UINT)param_5,0x220,param_2,param_3,(LPSTR)&uStack00000000,_Size,
                                      (LPCSTR)0x0,(LPBOOL)0x0);
          if (iVar3 != 0) {
            local_8 = 1;
            _alloca_probe();
            local_8 = 0xffffffff;
            if (&uStack00000000 != (unsigned char *)0x3c) {
              if (param_6 == 0) {
                param_6 = DAT_100237bc;
              }
              local_1c = (unsigned char*)&uStack00000000;
              *(short *)(&uStack00000000 + param_3 * 2) = -1;
              local_20[param_3 + -0xf] = 0xffff;
              BVar2 = GetStringTypeA((LCID)param_6,param_1,(LPCSTR)&uStack00000000,_Size,(LPWORD)&uStack00000000
                                    );
              if ((local_20[param_3 + -0xf] != 0xffff) &&
                 (*(short *)(&uStack00000000 + param_3 * 2) == -1)) {
                memmove2((unsigned int *)param_4,(unsigned int *)&uStack00000000,param_3 * 2);
                pExceptionList = local_14;
                return BVar2;
              }
            }
          }
        }
      }
    }
    pExceptionList = local_14;
    return 0;
  }
  BVar2 = GetStringTypeW(param_1,param_2,param_3,param_4);
  pExceptionList = local_14;
  return BVar2;
}



#if 0
char * __cdecl _ltoa(uint param_1,char *param_2,uint param_3)

{
  int iVar1;
  
  if ((param_3 == 10) && ((intptr_t)param_1 < 0)) {
    iVar1 = 1;
    param_3 = 10;
  }
  else {
    iVar1 = 0;
  }
  _ltoa_core(param_1,param_2,param_3,iVar1);
  return param_2;
}
#endif /* _ltoa */




void __cdecl _ltoa_core(uint param_1,char *param_2,uint param_3,int param_4)

{
  ulonglong uVar1;
  char *pcVar2;
  char *pcVar3;
  char cVar4;
  
  pcVar2 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    param_2 = param_2 + 1;
    param_1 = -param_1;
    pcVar2 = param_2;
  }
  do {
    pcVar3 = pcVar2;
    uVar1 = (ulonglong)param_1;
    param_1 = param_1 / param_3;
    cVar4 = (char)(uVar1 % (ulonglong)param_3);
    if ((uintptr_t)(uVar1 % (ulonglong)param_3) < 10) {
      cVar4 = cVar4 + '0';
    }
    else {
      cVar4 = cVar4 + 'W';
    }
    *pcVar3 = cVar4;
    pcVar2 = pcVar3 + 1;
  } while (param_1 != 0);
  pcVar3[1] = '\0';
  do {
    cVar4 = *pcVar3;
    *pcVar3 = *param_2;
    *param_2 = cVar4;
    pcVar3 = pcVar3 + -1;
    param_2 = param_2 + 1;
  } while (param_2 < pcVar3);
  return;
}



#if 0
char * __cdecl _ultoa(uint param_1,char *param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if ((param_3 == 10) && ((intptr_t)param_1 < 0)) {
    iVar1 = 1;
  }
  _ltoa_core(param_1,param_2,param_3,iVar1);
  return param_2;
}
#endif /* _ultoa */




#if 0
char * __cdecl _i64toa(int param_1,int param_2,char *param_3,uint param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (((param_4 == 10) && (param_2 < 1)) && (param_2 < 0)) {
    iVar1 = 1;
  }
  _i64toa_core(param_1,param_2,param_3,param_4,iVar1);
  return param_3;
}
#endif /* _i64toa */




void _i64toa_core(int param_1,int param_2,char *param_3,uint param_4,int param_5)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int bVar4;
  unsigned long long uVar5;
  longlong lVar6;
  uint uVar7;
  
  if (param_5 != 0) {
    *param_3 = '-';
    param_3 = param_3 + 1;
    bVar4 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(param_2 + (uintptr_t)bVar4);
  }
  lVar6 = CONCAT44(param_2,param_1);
  pcVar1 = param_3;
  do {
    pcVar3 = pcVar1;
    uVar7 = (uintptr_t)((ulonglong)lVar6 >> 0x20);
    uVar5 = __aullrem((uintptr_t)lVar6,uVar7,param_4,0);
    lVar6 = __aulldiv((uintptr_t)lVar6,uVar7,param_4,0);
    if ((uintptr_t)uVar5 < 10) {
      cVar2 = (char)uVar5 + '0';
    }
    else {
      cVar2 = (char)uVar5 + 'W';
    }
    *pcVar3 = cVar2;
    pcVar1 = pcVar3 + 1;
  } while (lVar6 != 0);
  pcVar3[1] = '\0';
  do {
    cVar2 = *pcVar3;
    *pcVar3 = *param_3;
    *param_3 = cVar2;
    pcVar3 = pcVar3 + -1;
    param_3 = param_3 + 1;
  } while (param_3 < pcVar3);
  return;
}



#if 0
char * __cdecl _ui64toa(int param_1,int param_2,char *param_3,uint param_4)

{
  _i64toa_core(param_1,param_2,param_3,param_4,0);
  return param_3;
}
#endif /* _ui64toa */




#if 0
uint __thiscall _stricmp(void *_this, byte *param_1)

{
  int bVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  void *extraout_ECX;
  void *this_00;
  void *extraout_ECX_00;
  uint uVar8;
  uint uVar9;
  uint uVar7;
  
  iVar2 = DAT_10023894;
  if (DAT_100237bc == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_100157ee;
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_100157ee:
    uVar7 = (uintptr_t)cVar6;
  }
  else {
    LOCK();
    DAT_10023894 = DAT_10023894 + 1;
    UNLOCK();
    bVar1 = 0 < DAT_10023884;
    if (bVar1) {
      LOCK();
      UNLOCK();
      DAT_10023894 = iVar2;
      _lock_critical_section(0x13);
      _this = extraout_ECX;
    }
    uVar9 = (uintptr_t)bVar1;
    uVar7 = 0xff;
    uVar8 = 0;
    do {
      do {
        if ((char)uVar7 == '\0') goto LAB_1001584f;
        bVar5 = *param_2;
        uVar7 = CONCAT31((int3)(uVar7 >> 8));
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar4);
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      uVar8 = _towlower_l(_this,uVar8);
      uVar7 = _towlower_l(this_00,uVar7);
      _this = extraout_ECX_00;
    } while ((byte)uVar8 == (byte)uVar7);
    uVar8 = (uintptr_t)((byte)uVar8 < (byte)uVar7);
    uVar7 = (1 - uVar8) - (uintptr_t)(uVar8 != 0);
LAB_1001584f:
    if (uVar9 == 0) {
      LOCK();
      DAT_10023894 = DAT_10023894 + -1;
      UNLOCK();
    }
    else {
      _unlock_critical_section(0x13);
    }
  }
  return uVar7;
}
#endif /* _stricmp */




#if 0
unsigned int __cdecl _strnicmp(byte *param_1,char *param_2,void *param_3)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  uint uVar5;
  unsigned int uVar6;
  void *_this;
  uint uVar7;
  int bVar8;
  uint uVar9;
  
  iVar2 = DAT_10023894;
  uVar6 = 0;
  if (param_3 != (void *)0x0) {
    if (DAT_100237bc == 0) {
      do {
        bVar3 = *param_1;
        cVar1 = *param_2;
        uVar4 = CONCAT11(bVar3,cVar1);
        if (bVar3 == 0) break;
        uVar4 = CONCAT11(bVar3,cVar1);
        uVar7 = (uintptr_t)uVar4;
        if (cVar1 == '\0') break;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar7 = (uintptr_t)CONCAT11(bVar3 + 0x20,cVar1);
        }
        uVar4 = (ushort)uVar7;
        bVar3 = (byte)uVar7;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar4 = (ushort)CONCAT31((int3)(uVar7 >> 8),bVar3 + 0x20);
        }
        bVar3 = (byte)(uVar4 >> 8);
        bVar8 = bVar3 < (byte)uVar4;
        if (bVar3 != (byte)uVar4) goto LAB_100158cf;
        param_3 = (void *)((intptr_t)param_3 + -1);
      } while (param_3 != (void *)0x0);
      uVar6 = 0;
      bVar3 = (byte)(uVar4 >> 8);
      bVar8 = bVar3 < (byte)uVar4;
      if (bVar3 != (byte)uVar4) {
LAB_100158cf:
        uVar6 = 0xffffffff;
        if (!bVar8) {
          uVar6 = 1;
        }
      }
    }
    else {
      LOCK();
      DAT_10023894 = DAT_10023894 + 1;
      UNLOCK();
      bVar8 = 0 < DAT_10023884;
      if (bVar8) {
        LOCK();
        UNLOCK();
        DAT_10023894 = iVar2;
        _lock_critical_section(0x13);
      }
      uVar9 = (uintptr_t)bVar8;
      uVar5 = 0;
      uVar7 = 0;
      do {
        uVar5 = CONCAT31((int3)(uVar5 >> 8),*param_1);
        uVar7 = CONCAT31((int3)(uVar7 >> 8),*param_2);
        if ((uVar5 == 0) || (uVar7 == 0)) break;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
        uVar7 = _towlower_l(param_3,uVar7);
        uVar5 = _towlower_l(_this,uVar5);
        bVar8 = uVar5 < uVar7;
        if (uVar5 != uVar7) goto LAB_10015945;
        param_3 = (void *)((intptr_t)param_3 + -1);
      } while (param_3 != (void *)0x0);
      uVar6 = 0;
      bVar8 = uVar5 < uVar7;
      if (uVar5 != uVar7) {
LAB_10015945:
        uVar6 = 0xffffffff;
        if (!bVar8) {
          uVar6 = 1;
        }
      }
      if (uVar9 == 0) {
        LOCK();
        DAT_10023894 = DAT_10023894 + -1;
        UNLOCK();
      }
      else {
        _unlock_critical_section(0x13);
      }
    }
  }
  return uVar6;
}
#endif /* _strnicmp */




int __cdecl
_strcoll_core(LCID param_1,DWORD param_2,byte *param_3,int param_4,byte *param_5,int param_6,
             UINT param_7)

{
  unsigned char *puVar1;
  int iVar2;
  BOOL BVar3;
  BYTE *pBVar4;
  int iVar5;
  struct _cpinfo local_40;
  unsigned char *local_2c;
  PCNZWCH local_28;
  int local_24;
  int local_20;
  unsigned char *local_1c;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001cd80;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  local_1c = (unsigned char*)&uStack00000000;
  pExceptionList = &local_14;
  puVar1 = (unsigned char*)&uStack00000000;
  if (DAT_10023864 == 0) {
    pExceptionList = &local_14;
    iVar2 = CompareStringW(0,0,(PCNZWCH)&lpSrcStr_1001c564,1,(PCNZWCH)&lpSrcStr_1001c564,1);
    if (iVar2 == 0) {
      iVar2 = CompareStringA(0,0,(PCNZCH)&lpSrcStr_1001c560,1,(PCNZCH)&lpSrcStr_1001c560,1);
      if (iVar2 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      DAT_10023864 = 2;
      puVar1 = local_1c;
    }
    else {
      DAT_10023864 = 1;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  if (0 < param_4) {
    param_4 = __strncnt((char *)param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = __strncnt((char *)param_5,param_6);
  }
  if (DAT_10023864 == 2) {
    iVar2 = CompareStringA(param_1,param_2,(PCNZCH)param_3,param_4,(PCNZCH)param_5,param_6);
    pExceptionList = local_14;
    return iVar2;
  }
  if (DAT_10023864 == 1) {
    if (param_7 == 0) {
      param_7 = CodePage_100237cc;
    }
    if ((param_4 == 0) || (param_6 == 0)) {
      if (param_4 == param_6) {
        pExceptionList = local_14;
        return 2;
      }
      if (1 < param_6) {
        pExceptionList = local_14;
        return 1;
      }
      if (1 < param_4) {
        pExceptionList = local_14;
        return 3;
      }
      BVar3 = GetCPInfo(param_7,&local_40);
      if (BVar3 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      if (0 < param_4) {
        if (local_40.MaxCharSize < 2) {
          pExceptionList = local_14;
          return 3;
        }
        pBVar4 = local_40.LeadByte;
        while( true ) {
          if (local_40.LeadByte[0] == 0) {
            pExceptionList = local_14;
            return 3;
          }
          if (pBVar4[1] == 0) break;
          if ((*pBVar4 <= *param_3) && (*param_3 <= pBVar4[1])) {
            pExceptionList = local_14;
            return 2;
          }
          pBVar4 = pBVar4 + 2;
          local_40.LeadByte[0] = *pBVar4;
        }
        pExceptionList = local_14;
        return 3;
      }
      if (0 < param_6) {
        if (local_40.MaxCharSize < 2) {
          pExceptionList = local_14;
          return 1;
        }
        pBVar4 = local_40.LeadByte;
        while( true ) {
          if (local_40.LeadByte[0] == 0) {
            pExceptionList = local_14;
            return 1;
          }
          if (pBVar4[1] == 0) break;
          if ((*pBVar4 <= *param_5) && (*param_5 <= pBVar4[1])) {
            pExceptionList = local_14;
            return 2;
          }
          pBVar4 = pBVar4 + 2;
          local_40.LeadByte[0] = *pBVar4;
        }
        pExceptionList = local_14;
        return 1;
      }
    }
    local_20 = MultiByteToWideChar(param_7,9,(LPCSTR)param_3,param_4,(LPWSTR)0x0,0);
    if (local_20 != 0) {
      local_8 = 0;
      _alloca_probe();
      local_8 = 0xffffffff;
      if ((&uStack00000000 != (unsigned char *)0x50) &&
         (local_28 = (PCNZWCH)&uStack00000000, local_1c = (unsigned char*)&uStack00000000,
         iVar2 = MultiByteToWideChar(param_7,1,(LPCSTR)param_3,param_4,(LPWSTR)&uStack00000000,
                                     local_20), iVar2 != 0)) {
        iVar2 = MultiByteToWideChar(param_7,9,(LPCSTR)param_5,param_6,(LPWSTR)0x0,0);
        if (iVar2 != 0) {
          local_8 = 1;
          local_24 = iVar2;
          _alloca_probe();
          local_8 = 0xffffffff;
          if ((&uStack00000000 != (unsigned char *)0x50) &&
             (local_2c = (byte*)&uStack00000000, local_1c = (byte*)&uStack00000000,
             iVar5 = MultiByteToWideChar(param_7,1,(LPCSTR)param_5,param_6,(LPWSTR)&uStack00000000,
                                         iVar2), iVar5 != 0)) {
            iVar2 = CompareStringW(param_1,param_2,local_28,local_20,(PCNZWCH)&uStack00000000,iVar2
                                  );
            pExceptionList = local_14;
            return iVar2;
          }
        }
      }
    }
  }
  pExceptionList = local_14;
  return 0;
}



int __cdecl __strncnt(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 != '\0') {
    return param_2;
  }
  return (intptr_t)pcVar1 - (intptr_t)param_1;
}



#if 0
unsigned int __cdecl _putenv(uint *param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  uint *lpName;
  byte *pbVar5;
  int *piVar6;
  int bVar7;
  
  if (param_1 == (uint *)0x0) {
    return 0xffffffff;
  }
  puVar1 = (uint *)_mbschr((byte *)param_1,0x3d);
  if (puVar1 == (uint *)0x0) {
    return 0xffffffff;
  }
  if (param_1 == puVar1) {
    return 0xffffffff;
  }
  bVar7 = *(byte *)((intptr_t)puVar1 + 1) == 0;
  if (DAT_10023500 == DAT_10023504) {
    DAT_10023500 = _dup_env(DAT_10023500);
  }
  if (DAT_10023500 == (int *)0x0) {
    if ((param_2 == 0) || (DAT_10023508 == (unsigned int *)0x0)) {
      if (bVar7) {
        return 0;
      }
      DAT_10023500 = _malloc(4);
      if (DAT_10023500 == (int *)0x0) {
        return 0xffffffff;
      }
      *DAT_10023500 = 0;
      if (DAT_10023508 == (unsigned int *)0x0) {
        DAT_10023508 = _malloc(4);
        if (DAT_10023508 == (unsigned int *)0x0) {
          return 0xffffffff;
        }
        *DAT_10023508 = 0;
      }
    }
    else {
      iVar2 = _wide_env_sync();
      if (iVar2 != 0) {
        return 0xffffffff;
      }
    }
  }
  piVar3 = DAT_10023500;
  iVar2 = _env_find((unsigned char *)param_1,(intptr_t)puVar1 - (intptr_t)param_1);
  if ((iVar2 < 0) || (*piVar3 == 0)) {
    if (bVar7) {
      return 0;
    }
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    piVar3 = realloc(piVar3,(uint *)(iVar2 * 4 + 8));
    if (piVar3 == (int *)0x0) {
      return 0xffffffff;
    }
    piVar3[iVar2] = (intptr_t)param_1;
    piVar3[iVar2 + 1] = 0;
  }
  else {
    if (!bVar7) {
      piVar3[iVar2] = (intptr_t)param_1;
      goto LAB_10015d4d;
    }
    piVar6 = piVar3 + iVar2;
    free((LPVOID)piVar3[iVar2]);
    for (; *piVar6 != 0; piVar6 = piVar6 + 1) {
      iVar2 = iVar2 + 1;
      *piVar6 = piVar6[1];
    }
    piVar3 = realloc(piVar3,(uint *)(iVar2 << 2));
    if (piVar3 == (int *)0x0) goto LAB_10015d4d;
  }
  DAT_10023500 = piVar3;
LAB_10015d4d:
  if (param_2 != 0) {
    sVar4 = _strlen((char *)param_1);
    lpName = _malloc(sVar4 + 2);
    if (lpName != (uint *)0x0) {
      strcpy(lpName,param_1);
      pbVar5 = (byte *)(((intptr_t)lpName - (intptr_t)param_1) + (intptr_t)puVar1);
      *pbVar5 = 0;
      SetEnvironmentVariableA((LPCSTR)lpName,(LPCSTR)(~-(uintptr_t)bVar7 & (uintptr_t)(pbVar5 + 1)));
      free(lpName);
    }
  }
  return 0;
}
#endif /* _putenv */




#if 0
int __cdecl _env_find(unsigned char *param_1,size_t param_2)

{
  unsigned char *_Str2;
  int iVar1;
  int *piVar2;
  
  _Str2 = (unsigned char *)*DAT_10023500;
  piVar2 = DAT_10023500;
  while( true ) {
    if (_Str2 == (unsigned char *)0x0) {
      return -((intptr_t)piVar2 - (intptr_t)DAT_10023500 >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,_Str2,param_2);
    if ((iVar1 == 0) &&
       ((*(char *)(*piVar2 + param_2) == '=' || (*(char *)(*piVar2 + param_2) == '\0')))) break;
    _Str2 = (unsigned char *)piVar2[1];
    piVar2 = piVar2 + 1;
  }
  return (intptr_t)piVar2 - (intptr_t)DAT_10023500 >> 2;
}
#endif /* _env_find */




unsigned int * __cdecl _dup_env(int *param_1)

{
  int iVar1;
  int *piVar2;
  unsigned int *puVar3;
  uint *puVar4;
  int iVar5;
  unsigned int *puVar6;
  
  iVar5 = 0;
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    piVar2 = param_1;
    while (iVar1 != 0) {
      piVar2 = piVar2 + 1;
      iVar5 = iVar5 + 1;
      iVar1 = *piVar2;
    }
    puVar3 = _malloc((unsigned int*)(iVar5 * 4 + 4));
    if (puVar3 == (unsigned int *)0x0) {
      __amsg_exit(9);
    }
    puVar4 = (uint *)*param_1;
    puVar6 = puVar3;
    while (puVar4 != (uint *)0x0) {
      param_1 = param_1 + 1;
      puVar4 = (uint *)_strdup((const char*)puVar4);
      *puVar6 = puVar4;
      puVar6 = puVar6 + 1;
      puVar4 = (uint *)*param_1;
    }
    *puVar6 = 0;
    return puVar3;
  }
  return (unsigned int *)0x0;
}



int __cdecl __crtGetLocaleInfoW(LCID param_1,LCTYPE param_2,LPWSTR param_3,int param_4,UINT param_5)

{
  int iVar1;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001cd98;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  pExceptionList = &local_14;
  if (DAT_10023868 == 0) {
    pExceptionList = &local_14;
    iVar1 = GetLocaleInfoW(0,1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      DAT_10023868 = 2;
    }
    else {
      DAT_10023868 = 1;
    }
  }
  if (DAT_10023868 != 1) {
    if (DAT_10023868 == 2) {
      if (param_5 == 0) {
        param_5 = CodePage_100237cc;
      }
      iVar1 = GetLocaleInfoA(param_1,param_2,(LPSTR)0x0,0);
      if (iVar1 != 0) {
        local_8 = 0;
        _alloca_probe();
        local_8 = 0xffffffff;
        if ((&uStack00000000 != (unsigned char *)0x34) &&
           (iVar1 = GetLocaleInfoA(param_1,param_2,(LPSTR)&uStack00000000,iVar1), iVar1 != 0)) {
          if (param_4 == 0) {
            param_4 = 0;
            param_3 = (LPWSTR)0x0;
          }
          iVar1 = MultiByteToWideChar((UINT)param_5,1,(LPCSTR)&uStack00000000,-1,param_3,param_4);
          pExceptionList = local_14;
          return iVar1;
        }
      }
    }
    pExceptionList = local_14;
    return 0;
  }
  iVar1 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
  pExceptionList = local_14;
  return iVar1;
}



int __cdecl __crtGetLocaleInfoA(LCID param_1,LCTYPE param_2,LPSTR param_3,int param_4,UINT param_5)

{
  int iVar1;
  void *local_14;
  unsigned char *puStack_10;
  unsigned char *puStack_c;
  unsigned int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = (unsigned char*)&DAT_1001cda8;
  puStack_10 = (unsigned char*)&LAB_1000f844;
  local_14 = pExceptionList;
  pExceptionList = &local_14;
  if (DAT_1002386c == 0) {
    pExceptionList = &local_14;
    iVar1 = GetLocaleInfoW(0,1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        pExceptionList = local_14;
        return 0;
      }
      DAT_1002386c = 2;
    }
    else {
      DAT_1002386c = 1;
    }
  }
  if (DAT_1002386c != 2) {
    if (DAT_1002386c == 1) {
      if (param_5 == 0) {
        param_5 = CodePage_100237cc;
      }
      iVar1 = GetLocaleInfoW(param_1,param_2,(LPWSTR)0x0,0);
      if (iVar1 != 0) {
        local_8 = 0;
        _alloca_probe();
        local_8 = 0xffffffff;
        if ((&uStack00000000 != (unsigned char *)0x34) &&
           (iVar1 = GetLocaleInfoW(param_1,param_2,(LPWSTR)&uStack00000000,iVar1), iVar1 != 0)) {
          if (param_4 == 0) {
            param_4 = 0;
            param_3 = (LPSTR)0x0;
          }
          iVar1 = WideCharToMultiByte(param_5,0x220,(LPCWSTR)&uStack00000000,-1,param_3,param_4,
                                      (LPCSTR)0x0,(LPBOOL)0x0);
          pExceptionList = local_14;
          return iVar1;
        }
      }
    }
    pExceptionList = local_14;
    return 0;
  }
  iVar1 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
  pExceptionList = local_14;
  return iVar1;
}



byte * __cdecl _mbschr(byte *param_1,uint param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  if (DAT_1002391c == 0) {
    pbVar2 = (byte *)_strchr((char *)param_1,param_2);
  }
  else {
    _lock_critical_section(0x19);
    while( true ) {
      bVar1 = *param_1;
      uVar3 = (uintptr_t)bVar1;
      if (bVar1 == 0) break;
      if ((*(byte *)((intptr_t)&DAT_10023a20 + uVar3 + 1) & 4) == 0) {
        pbVar2 = param_1;
        if (param_2 == uVar3) break;
      }
      else {
        pbVar2 = param_1 + 1;
        if (param_1[1] == 0) {
          _unlock_critical_section(0x19);
          return (byte *)0x0;
        }
        if (param_2 == CONCAT11(bVar1,param_1[1])) {
          _unlock_critical_section(0x19);
          return param_1;
        }
      }
      param_1 = pbVar2 + 1;
    }
    _unlock_critical_section(0x19);
    pbVar2 = (byte *)(~-(uintptr_t)(param_2 != uVar3) & (uintptr_t)param_1);
  }
  return pbVar2;
}



#if 0
uint * __cdecl _strdup(uint *param_1)

{
  size_t sVar1;
  uint *puVar2;
  
  if (param_1 != (uint *)0x0) {
    sVar1 = _strlen((char *)param_1);
    puVar2 = _malloc(sVar1 + 1);
    if (puVar2 != (uint *)0x0) {
      puVar2 = strcpy(puVar2,param_1);
      return puVar2;
    }
  }
  return (uint *)0x0;
}
#endif /* _strdup */




// Library Function - Single Match
//  _strchr
// 
// Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release

#if 0
char * __cdecl _strchr(char *_Str,int _Val)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uintptr_t)_Str & 3) != 0) {
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    _Str = (char *)((intptr_t)_Str + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)_Str;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)_Val,(char)_Val),CONCAT11((char)_Val,(char)_Val));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((intptr_t)_Str + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      _Str = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)_Val) {
      return (char *)((intptr_t)_Str + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)_Val) {
      return (char *)((intptr_t)_Str + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)_Val) {
      return (char *)((intptr_t)_Str + 3);
    }
    _Str = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}
#endif /* _strchr */




#if 0
void SFileGetFileName(void)

{
                    // WARNING: Could not recover jumptable at 0x1001622c. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_276();
  return;
}
#endif /* SFileGetFileName */




#if 0
void SStrNCat(void)

{
                    // WARNING: Could not recover jumptable at 0x10016232. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_503();
  return;
}
#endif /* SStrNCat */




#if 0
void SFileOpenArchive(void)

{
                    // WARNING: Could not recover jumptable at 0x10016238. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_266();
  return;
}
#endif /* SFileOpenArchive */




#if 0
void SFileCloseArchive(void)

{
                    // WARNING: Could not recover jumptable at 0x1001623e. Too many branches
                    // WARNING: Treating indirect jump as call
  STORM_252();
  return;
}
#endif /* SFileCloseArchive */




void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    // WARNING: Could not recover jumptable at 0x1001625c. Too many branches
                    // WARNING: Treating indirect jump as call
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}



void Unwind_1001a470(void)

{
  int unaff_EBP;
  
  GameData_Destructor_HashBase(*(unsigned int **)(unaff_EBP + -0x14));
  return;
}



void Unwind_1001a478(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 0x28));
  return;
}



void Unwind_1001a483(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachAll((int *)(*(int *)(unaff_EBP + -0x14) + 0x38));
  return;
}



void Unwind_1001a48e(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach3((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a499(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a4a4(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 4));
  return;
}



void Unwind_1001a4af(void)

{
  int unaff_EBP;
  
  GameDataPool_FreeBackingArray(*(int *)(unaff_EBP + -0x14) + 0x14);
  return;
}



void Unwind_1001a4ba(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a4f0(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 4));
  return;
}



void Unwind_1001a4fb(void)

{
  int unaff_EBP;
  
  GameDataPool_FreeBackingArray(*(int *)(unaff_EBP + -0x14) + 0x14);
  return;
}



void Unwind_1001a506(void)

{
  int unaff_EBP;
  
  GameData_Destructor_HashBase(*(unsigned int **)(unaff_EBP + -0x14));
  return;
}



void Unwind_1001a50e(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachList(*(int **)(unaff_EBP + -0x10));
  return;
}



void Unwind_1001a516(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 0x28));
  return;
}



void Unwind_1001a521(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachAll2(*(int **)(unaff_EBP + -0x10));
  return;
}



void Unwind_1001a529(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachAll((int *)(*(int *)(unaff_EBP + -0x14) + 0x38));
  return;
}



void Unwind_1001a560(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a56b(void)

{
  int unaff_EBP;
  
  GameDataPool_FreeBackingArray(*(int *)(unaff_EBP + -0x10) + 0x14);
  return;
}



void Unwind_1001a576(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a5a0(void)

{
  int unaff_EBP;
  
  GameData_Destructor_HashBase(*(unsigned int **)(unaff_EBP + -0x14));
  return;
}



void Unwind_1001a5a8(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 0x28));
  return;
}



void Unwind_1001a5b3(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachAll((int *)(*(int *)(unaff_EBP + -0x14) + 0x38));
  return;
}



void Unwind_1001a5be(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach3((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a5c9(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a5d4(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x14) + 4));
  return;
}



void Unwind_1001a5df(void)

{
  int unaff_EBP;
  
  GameDataPool_FreeBackingArray(*(int *)(unaff_EBP + -0x14) + 0x14);
  return;
}



void Unwind_1001a5ea(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a620(void)

{
  int unaff_EBP;
  
  GameData_ListNode_Detach((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a640(void)

{
  int unaff_EBP;
  
  GameData_Destructor_HashBase(*(unsigned int **)(unaff_EBP + -0x10));
  return;
}



void Unwind_1001a648(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x10) + 0x28));
  return;
}



void Unwind_1001a653(void)

{
  int unaff_EBP;
  
  GameDataPool_DetachAll((int *)(*(int *)(unaff_EBP + -0x10) + 0x38));
  return;
}



void Unwind_1001a65e(void)

{
  int unaff_EBP;
  
  GameDataPool_ClearEntry((int *)(*(int *)(unaff_EBP + -0x10) + 4));
  return;
}



void Unwind_1001a669(void)

{
  int unaff_EBP;
  
  GameDataPool_FreeBackingArray(*(int *)(unaff_EBP + -0x10) + 0x14);
  return;
}


