#include "D2EClient.h"

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
void* __stdcall D2EClientInterface(void*) { return (void*)MODULE_NONE; }

// A global variable to hold the actual function pointer
static ModuleInitPointer gInterface = D2EClientInterface;

void* __stdcall QueryInterface() {
	return (void*)&gInterface;
}
}
