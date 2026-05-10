#pragma once

#include <stdarg.h>
#include <stdio.h>

#include <windef.h>
#include <winnt.h>

typedef struct {} PAINTSTRUCT;

typedef PAINTSTRUCT* LPPAINTSTRUCT;

/* Taken from wine */

#define MB_OK			0x00000000
#define MB_OKCANCEL		0x00000001
#define MB_ABORTRETRYIGNORE	0x00000002
#define MB_YESNOCANCEL		0x00000003
#define MB_YESNO		0x00000004
#define MB_RETRYCANCEL		0x00000005
#define MB_CANCELTRYCONTINUE	0x00000006
#define MB_TYPEMASK		0x0000000F

#define MB_ICONHAND		0x00000010
#define MB_ICONQUESTION		0x00000020
#define MB_ICONEXCLAMATION	0x00000030
#define MB_ICONASTERISK		0x00000040
#define	MB_USERICON		0x00000080
#define MB_ICONMASK		0x000000F0

#define MB_ICONINFORMATION	MB_ICONASTERISK
#define MB_ICONSTOP		MB_ICONHAND
#define MB_ICONWARNING		MB_ICONEXCLAMATION
#define MB_ICONERROR		MB_ICONHAND

#define MB_DEFBUTTON1		0x00000000
#define MB_DEFBUTTON2		0x00000100
#define MB_DEFBUTTON3		0x00000200
#define MB_DEFBUTTON4		0x00000300
#define MB_DEFMASK		0x00000F00

#define MB_APPLMODAL		0x00000000
#define MB_SYSTEMMODAL		0x00001000
#define MB_TASKMODAL		0x00002000
#define MB_MODEMASK		0x00003000

#define MB_HELP			0x00004000
#define MB_NOFOCUS		0x00008000
#define MB_MISCMASK		0x0000C000

#define MB_SETFOREGROUND	0x00010000
#define MB_DEFAULT_DESKTOP_ONLY	0x00020000
#define MB_SERVICE_NOTIFICATION	0x00040000
#define MB_TOPMOST		0x00040000
#define MB_RIGHT		0x00080000
#define MB_RTLREADING		0x00100000

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
	IDABORT=0,
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
