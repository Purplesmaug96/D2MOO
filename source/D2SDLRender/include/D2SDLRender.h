#pragma once

#include <stddef.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "D2Gfx.h"

#ifndef _D2SDLRENDER_CPP
extern D2GraphicsInterfaceStrc Interface;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t rendererFlags;
#endif

// #define FUNC_LOG_STUB_QUIET

// #define FUNC_STUB_USE_MSGBOX

#ifndef FUNC_LOG_STUB_QUIET

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

#endif

static inline void FUNC_LOG(const char* func) {
	printf("D2SDLRender: Logged function '%s' called\n", func);
	fflush(stdout);
}

static inline void FUNC_LOG_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	printf("D2SDLRender: Logged function '%s' called, args: %s\n", func, argsBuf);
	fflush(stdout);
}

static inline void FUNC_LOGSEMI(const char* func) {
	printf("D2SDLRender: Logged  and semi-implemented function '%s' called\n", func);
	fflush(stdout);
}

static inline void FUNC_LOGSEMI_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	printf("D2SDLRender: Logged and semi-implemented function '%s' called, args: %s\n", func, argsBuf);
	fflush(stdout);
}

#else

static inline void FUNC_STUB(const char* func) {}

static inline void FUNC_STUB_ARGS(const char* func, const char* fmt, ...) {}

static inline void FUNC_LOG(const char* func) {}

static inline void FUNC_LOG_ARGS(const char* func, const char* fmt, ...) {}

static inline void FUNC_LOGSEMI(const char* func) {}
static inline void FUNC_LOGSEMI_ARGS(const char* func, const char* fmt, ...) {}

#endif

static inline void _FUNC_ERR(const char* func, const char* errBuf, const char* file, const int line) {
	char dstBuf[512];
	sprintf(dstBuf, "D2SDLRender: Error in function '%s', %s:%d:\n%s\n", func, file, line, errBuf);
	printf("%s", dstBuf);
	fflush(stdout);
	MessageBoxA(NULL, dstBuf, "D2SDLRender: Error occured", MB_OK);
}

#define FUNC_ERR(func, errBuf) _FUNC_ERR(func, errBuf, __FILE__, __LINE__)

static inline void _FUNC_ASSERT(const char* condBuf, const char* file, const int line) {
	char dstBuf[512];
	sprintf(dstBuf, "D2SDLRender: Assertion triggered at %s:%d:\n%s\n", file, line, condBuf);
	printf("%s", dstBuf);
	fflush(stdout);
	MessageBoxA(NULL, dstBuf, "D2SDLRender: Assertion triggered", MB_OK);
	exit(1);
}

#define FUNC_ASSERT(cond)                            \
	do {                                             \
		if (!(cond))                                 \
			_FUNC_ASSERT(#cond, __FILE__, __LINE__); \
	} while (0)

bool D2SDLRender_Init();

extern "C" {
D2GraphicsInterfaceStrc* D2SDLRender_GraphicsInterface();
}
