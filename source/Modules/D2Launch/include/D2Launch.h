#pragma once

extern "C" {
#ifdef D2MOO_SHARED_LIBS
void* __stdcall QueryInterface();
#endif
void* __stdcall D2LaunchInterface(void*);
}
