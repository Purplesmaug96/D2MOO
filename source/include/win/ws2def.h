#pragma once

#include "__windows_shim_msvcrt.h"

// Turned out not to be necessary

// struct in_addr {
// 	union {
// 		struct {
// 			unsigned char s_b1;
// 			unsigned char s_b2;
// 			unsigned char s_b3;
// 			unsigned char s_b4;
// 		} S_un_b;
// 		struct {
// 			unsigned short s_w1;
// 			unsigned short s_w2;
// 		} S_un_w;
// 		unsigned long S_addr;
// 	} S_un;
// };

// typedef struct {
// 	short          sin_family;
// 	unsigned short sin_port;
// 	in_addr        sin_addr;
// 	char           sin_zero[8];
// } sockaddr_in;
