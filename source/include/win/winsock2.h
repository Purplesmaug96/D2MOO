#pragma once

#include "__windows_shim_msvcrt.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

// #include "ws2def.h"

typedef int SOCKET;

typedef struct {
} WSADATA;
typedef WSADATA* LPWSADATA;

#define INVALID_SOCKET 0

enum {
	SOCKET_ERROR_NONE = 0, // Made up
	SOCKET_ERROR
};

static inline int WSAStartup(/*WORD*/ uint16_t wVersionRequired, LPWSADATA lpWSAData) {
	printf("Stubbed function WSAStartup called\n");
	return SOCKET_ERROR;
}

#ifdef __WINDOWS_SHIM_WSA_LASTERROR_LOCAL
#include "__windows_shim_local_wsa_lasterror.h"
#else
extern uint32_t __winsock2_WSA_LastError;
#endif

static inline void WSASetLastError(uint32_t errorCode) {
	__winsock2_WSA_LastError = errorCode;
}

static inline uint32_t /* Should be DWORD, but not defined here */ WSAGetLastError() {
	return __winsock2_WSA_LastError;
}

static inline int __WSAFDIsSet(SOCKET fd, fd_set* fdsetp) {
	return FD_ISSET(fd, fdsetp);
}
