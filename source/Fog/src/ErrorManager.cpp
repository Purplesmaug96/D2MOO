#include "ErrorManager.h"

#include <stdio.h>

#include <SDL2/SDL_messagebox.h>

// Fog.#10023
void FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Diablo II: Assertion Failed", msg, NULL);
}

// Fog.#10024
void FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Diablo II: Halt", msg, NULL);
}

// Fog.#10025
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nWarned at %s:%d", szFile, nLine);
	strcat(msg, tmp);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Diablo II: Warning", msg, NULL);
}

// Fog.#10026
void FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine) {
	char msg[1024];
	char tmp[1024];
	strcpy(msg, szMsg);
	sprintf(tmp, "\n\nFailed at %s:%d\nError category: %d", szFile, nLine, nCategory);
	strcat(msg, tmp);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Diablo II: Error", msg, NULL);
}
