#include "D2Multi.h"

#include "D2CommonDefinitions.h"
#include <stddef.h>

// Should be the same as in Main.h
enum D2_MODULES {
	MODULE_NONE,
	MODULE_CLIENT,
	MODULE_SERVER,
	MODULE_MULTIPLAYER,
	MODULE_LAUNCHER,
#if D2_HAS_MULTILAN
	MODULE_MULTILAN,
#endif
	MODULE_EXPAND,
	D2_MODULES_COUNT
};

extern "C" {

typedef void*(__stdcall* ModuleInitPointer)(void*);
void* __stdcall D2MultiInterface(void*) { return (void*)MODULE_NONE; }

// A global variable to hold the actual function pointer
static ModuleInitPointer gInterface = D2MultiInterface;

#ifdef D2MOO_SHARED_LIBS
void* __stdcall QueryInterface() {
	return (void*)&gInterface;
}
#endif
}
