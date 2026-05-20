#pragma once

#include "__windows_shim_msvcrt.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>

#include "windef.h"
#include "winnt.h"

typedef struct {
} PAINTSTRUCT;

typedef PAINTSTRUCT* LPPAINTSTRUCT;

/* Taken from wine */

#define MB_OK 0x00000000
#define MB_OKCANCEL 0x00000001
#define MB_ABORTRETRYIGNORE 0x00000002
#define MB_YESNOCANCEL 0x00000003
#define MB_YESNO 0x00000004
#define MB_RETRYCANCEL 0x00000005
#define MB_CANCELTRYCONTINUE 0x00000006
#define MB_TYPEMASK 0x0000000F

#define MB_ICONHAND 0x00000010
#define MB_ICONQUESTION 0x00000020
#define MB_ICONEXCLAMATION 0x00000030
#define MB_ICONASTERISK 0x00000040
#define MB_USERICON 0x00000080
#define MB_ICONMASK 0x000000F0

#define MB_ICONINFORMATION MB_ICONASTERISK
#define MB_ICONSTOP MB_ICONHAND
#define MB_ICONWARNING MB_ICONEXCLAMATION
#define MB_ICONERROR MB_ICONHAND

#define MB_DEFBUTTON1 0x00000000
#define MB_DEFBUTTON2 0x00000100
#define MB_DEFBUTTON3 0x00000200
#define MB_DEFBUTTON4 0x00000300
#define MB_DEFMASK 0x00000F00

#define MB_APPLMODAL 0x00000000
#define MB_SYSTEMMODAL 0x00001000
#define MB_TASKMODAL 0x00002000
#define MB_MODEMASK 0x00003000

#define MB_HELP 0x00004000
#define MB_NOFOCUS 0x00008000
#define MB_MISCMASK 0x0000C000

#define MB_SETFOREGROUND 0x00010000
#define MB_DEFAULT_DESKTOP_ONLY 0x00020000
#define MB_SERVICE_NOTIFICATION 0x00040000
#define MB_TOPMOST 0x00040000
#define MB_RIGHT 0x00080000
#define MB_RTLREADING 0x00100000

static inline int wsprintfA(char* lpOut, const char* lpFmt, ...) {
	int result;
	va_list args;

	va_start(args, lpFmt);

	result = vsprintf(lpOut, lpFmt, args);

	va_end(args);

	return result;
}

static inline int MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	printf("Stubbed function MessageBoxA called\n");
	return 0;
}

enum {
	IDABORT = 0,
	IDC_STATIC,
	IDCANCEL,
	IDD_ABOUTBOX,
	IDI_PROJECTNAME,
	IDI_SMALL,
	IDIGNORE,
	IDM_ABOUT,
	IDM_EXIT,
	IDNO,
	IDOK,
	IDRETRY,
	IDS_APP_TITLE,
	IDYES
};

typedef LRESULT (*WNDPROC)(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);

typedef struct {
	uint length;
	uint flags;
	uint showCmd;
	POINT ptMinPosition;
	POINT ptMaxPosition;
	RECT rcNormalPosition;
	RECT rcDevice;
} WINDOWPLACEMENT;

typedef struct {
	uint style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCSTR lpszMenuName;
	LPCSTR lpszClassName;
} WNDCLASSA;

enum {
	CS_VREDRAW = 0x0001,
	CS_HREDRAW = 0x0002,
	CS_DBLCLKS = 0x0008,
	CS_OWNDC = 0x0020,
	CS_CLASSDC = 0x0040,
	CS_PARENTDC = 0x0080,
	CS_NOCLOSE = 0x0200,
	CS_SAVEBITS = 0x0800,
	CS_BYTEALIGNWINDOW = 0x2000,
	CS_BYTEALIGNCLIENT = 0x1000,
	CS_GLOBALCLASS = 0x4000,
	CS_DROPSHADOW = 0x00020000
};

#define IMAGE_ICON 0

#define LR_DEFAULTCOLOR 0

#define COLOR_WINDOW 0

static inline HANDLE LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad) {
	printf("Stubbed function LoadImageA called\n");
	return NULL;
}

static inline HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) {
	printf("Stubbed function LoadCursorA called\n");
	return NULL;
}

static inline /*ATOM*/ BOOL RegisterClassA(const WNDCLASSA* lpWndClass) {
	printf("Stubbed function RegisterClassA called\n");
	return FALSE;
}

static inline BOOL UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance) {
	printf("Stubbed function UnregisterClassA called\n");
	return FALSE;
}

static inline HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) {
	printf("Stubbed function FindWindowA called\n");
	return NULL;
}

static inline long ChangeDisplaySettingsA(/*DEVMODEA*/ void* lpDevMode, DWORD dwFlags) {
	printf("Stubbed function ChangeDisplaySettingsA called\n");
	return 0; // should be DISP_CHANGE_FAILED
}

static inline BOOL GetWindowPlacement(HWND hWnd, WINDOWPLACEMENT* lpwndpl) {
	printf("Stubbed function GetWindowPlacement called\n");
	return FALSE;
}

static inline BOOL IsIconic(HWND hWnd) {
	printf("Stubbed function IsIconic called\n");
	return FALSE;
}

static inline BOOL ShowWindow(HWND hWnd, int nCmdShow) {
	printf("Stubbed function ShowWindow called\n");
	return FALSE;
}

static inline short GetKeyState(int nVirtKey) {
	printf("Stubbed function GetKeyState called\n");
	return FALSE;
}

typedef struct {
} MSG;

static inline BOOL PeekMessageA(/*LPMSG*/ MSG* lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	printf("Stubbed function PeekMessageA called\n");
	return FALSE;
}

static inline BOOL TranslateMessage(const MSG* lpMsg) {
	printf("Stubbed function TranslateMessage called\n");
	return FALSE;
}

static inline LRESULT DispatchMessageA(const MSG* lpMsg) {
	printf("Stubbed function DispatchMessageA called\n");
	return (LRESULT)NULL;
}

static inline BOOL PtInRect(const RECT* lpRect, const POINT point) {
	return (
		point.x >= lpRect->left /* X of top-left */ &&
		point.y >= lpRect->top /* Y of top-left */ &&
		point.x <= lpRect->right /* X of down-right */ &&
		point.y <= lpRect->bottom /* Y of down-right */
	);
}

static inline BOOL SetCursorPos(int X, int Y) {
	printf("Stubbed function SetCursorPos called\n");
	return FALSE;
}

static inline void PostQuitMessage(int nExitCode) {
	printf("PostQuitMessage called with %d; calling exit(%d)\n", nExitCode, nExitCode);
	exit(nExitCode);
}

static inline LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	printf("Stubbed function DefWindowProcA called\n");
	return (LRESULT)NULL;
}

static inline BOOL GetMessageA(MSG* lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) {
	printf("Stubbed function GetMessageA called\n");
	return FALSE;
}

#define MAKELPARAM(l, h) ((LPARAM)((uint16_t)l | (uint16_t)((uint16_t)h >> 16)))
#define MAKEWPARAM(l, h) ((LPARAM)((uint16_t)l | (uint16_t)((uint16_t)h >> 16)))

#define SIZE_RESTORED 0

#define INVALID_HANDLE_VALUE -1

#include <__windows_shim_winuser_defs.h>
