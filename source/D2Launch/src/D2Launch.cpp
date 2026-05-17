#include "D2Launch.h"

#include <stddef.h>

extern "C" {
	void* QueryInterface() {
		return (void*)&UnkFunc;
	}
}

void* UnkFunc(void*) {
	return NULL;
}