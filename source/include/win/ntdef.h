#pragma once

#include "__windows_shim_msvcrt.h"

#include <stddef.h>

#define CONTAINING_RECORD(address, type, field) ((type*)(address - offsetof(type, field)))
