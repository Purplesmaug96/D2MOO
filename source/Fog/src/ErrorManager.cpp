#include "ErrorManager.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef USE_SDL3
#include <SDL3/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

// -1 = not decided yet, resolved on first use
static int g_bFogGuiEnabled = -1;

// Fog
void FOG_SetGuiEnabled(bool bEnabled) {
	g_bFogGuiEnabled = bEnabled ? 1 : 0;
}

// Fog
bool FOG_IsGuiEnabled(void) {
	if (g_bFogGuiEnabled < 0) {
		// D2GS_NO_GUI is the manual override for headless/remote runs; the
		// desktop client leaves it unset and keeps the real message boxes.
		g_bFogGuiEnabled = (getenv("D2SERVER_NO_GUI") != nullptr) ? 0 : 1;
	}
	return g_bFogGuiEnabled != 0;
}

static void showMessageBox(const char* title, const char* desc, bool isError) {
	if (!FOG_IsGuiEnabled()) {
		return;
	}

	#ifdef _WIN32
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		MessageBoxA(NULL, title, desc, MB_OK);
	} else
	#endif
	{
		SDL_ShowSimpleMessageBox(isError ? SDL_MESSAGEBOX_ERROR : SDL_MESSAGEBOX_WARNING, title, desc, NULL);
	}
}

// Fog.#10023
void FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine) {
	fprintf(stderr, "[FOG] ASSERT: %s\n       at %s:%d\n", szMsg, szFile, nLine);
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Assertion Failed", msg, true);
}

// Fog.#10024
void FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine) {
	fprintf(stderr, "[FOG] HALT: %s\n       at %s:%d\n", szMsg, szFile, nLine);
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Halt", msg, true);
}

// Fog.#10025
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine) {
	fprintf(stderr, "[FOG] WARNING: %s\n       at %s:%d\n", szMsg, szFile, nLine);
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nWarned at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Warning", msg, false);
}

// Fog.#10026
void FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine) {
	fprintf(stderr, "[FOG] ERROR: %s\n       at %s:%d (category %d)\n", szMsg, szFile, nLine, nCategory);
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d\nError category: %d", szFile, nLine, nCategory);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Error", msg, true);
}
