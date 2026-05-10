#pragma once

#include <stddef.h>

#define CONTAINING_RECORD(address, type, field) ((type*)(address - offsetof(type, field)))
