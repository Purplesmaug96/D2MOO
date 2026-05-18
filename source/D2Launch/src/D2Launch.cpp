#include "D2Launch.h"

#include <stddef.h>

extern "C" {

typedef void*(__stdcall* ModuleInitPointer)(void*);
void* __stdcall UnkFunc(void*) { return NULL; }

// A global variable to hold the actual function pointer
static ModuleInitPointer gInterface = UnkFunc;

void* __stdcall QueryInterface() {
	return (void*)&gInterface;
}
}
