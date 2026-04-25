#pragma once

#include <cstddef>
#include <cstdio>

#include "D2Gfx.h"


#ifndef _D2SDLRENDER_CPP
extern D2GraphicsInterfaceStrc Interface;
#endif

static inline void FUNC_STUB(const char* func) {
	printf("D2SDLRender: Stubbed function '%s'\n", func);
}

static inline void FUNC_STUB_ARGS(const char* func, const char* fmt, ...) {
	char argsBuf[256];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(argsBuf, sizeof argsBuf, fmt, ap);
	va_end(ap);
	printf("D2SDLRender: Stubbed function '%s', args: %s\n", func, argsBuf);
}

bool D2SDLRender_Init();

D2GraphicsInterfaceStrc* D2SDLRender_GetGraphicsInterface();