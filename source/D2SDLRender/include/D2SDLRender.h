#pragma once

#include <cstddef>
#include <cstdio>

#include "D2Gfx.h"


#ifndef _D2SDLRENDER_CPP
extern D2GraphicsInterfaceStrc Interface;
#endif

#define FUNC_STUB_USE_MSGBOX

#ifdef FUNC_STUB_USE_MSGBOX

static inline void FUNC_STUB(const char* func) {
	char dstBuf[512];
	sprintf(dstBuf, "D2SDLRender: Stubbed function '%s' called\n", func);
	printf("%s", dstBuf);
	MessageBoxA(NULL, dstBuf, "D2SDLRender: Stubbed function called", MB_OK);
}

static inline void FUNC_STUB_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	char dstBuf[512];
	sprintf(dstBuf, "D2SDLRender: Stubbed function '%s', args: %s called\n", func, argsBuf);
	printf("%s", dstBuf);
	MessageBoxA(NULL, dstBuf, "D2SDLRender: Stubbed function called", MB_OK);
}

#else

static inline void FUNC_STUB(const char* func) {
	printf("D2SDLRender: Stubbed function '%s' called\n", func);
}

static inline void FUNC_STUB_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	printf("D2SDLRender: Stubbed function '%s' called, args: %s\n", func, argsBuf);
}

static inline void FUNC_LOG(const char* func) {
	printf("D2SDLRender: Logged function '%s' called\n", func);
}

static inline void FUNC_LOG_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	printf("D2SDLRender: Logged function '%s' called, args: %s\n", func, argsBuf);
}

#endif

bool D2SDLRender_Init();

D2GraphicsInterfaceStrc* D2SDLRender_GetGraphicsInterface();
