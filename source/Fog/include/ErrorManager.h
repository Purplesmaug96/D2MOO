#pragma once

void FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine);

// Fog: dedicated servers (and any other headless process) must never try to pop
// up a GUI message box -- it steals focus on whatever desktop happens to be
// logged in and blocks on a window nobody will ever dismiss.  The text always
// still goes to stderr.  Defaults to enabled; the D2Server module calls
// FOG_SetGuiEnabled(false) at startup, and D2GS_NO_GUI in the environment forces
// it off as well.
void FOG_SetGuiEnabled(bool bEnabled);
bool FOG_IsGuiEnabled(void);
