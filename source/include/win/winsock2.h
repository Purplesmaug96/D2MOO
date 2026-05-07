#pragma once

#include <stdint.h>
#include <stdio.h>

#include <ws2def.h>

typedef int SOCKET;

typedef struct {} WSADATA;
typedef WSADATA* LPWSADATA;

#define AF_INET 0 // address family for IPv4

enum {
	SOCK_STREAM=0, // Supports reliable connection-oriented byte stream communication.
	SOCK_DGRAM, // Supports unreliable connectionless datagram communication.
	SOCK_RAW // Supports raw access to the transport protocol.
};

enum {
	SOCKET_ERROR=0
};

int WSAStartup(/*WORD*/ uint16_t wVersionRequired, LPWSADATA lpWSAData) {
	printf("Stubbed function WSAStartup called\n");
	return SOCKET_ERROR;
}
