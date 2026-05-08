#include <stdint.h>

#ifndef SOCKET_ERROR_NONE
#define SOCKET_ERROR_NONE 0
#endif

uint32_t __winsock2_WSA_LastError = SOCKET_ERROR_NONE;
