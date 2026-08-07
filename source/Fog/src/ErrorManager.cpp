#include "ErrorManager.h"

#include <stdio.h>

#ifdef USE_SDL3
#include <SDL3/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

static void showMessageBox(const char* title, const char* desc, bool isError) {
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
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Assertion Failed", msg, true);
}

// Fog.#10024
void FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Halt", msg, true);
}

// Fog.#10025
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nWarned at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Warning", msg, false);
}

// Fog.#10026
void FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d\nError category: %d", szFile, nLine, nCategory);
	strcat(msg, tmp);

	showMessageBox("Diablo II: Error", msg, true);
}
