#pragma once

void FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine);
void FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine);
