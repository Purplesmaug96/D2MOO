#pragma once

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <__windows_shim_arch_helper.h>

#ifdef __ANDROID__
#include <android/log.h>
#define printf(...) __android_log_print(ANDROID_LOG_INFO, "D2MOO", __VA_ARGS__)
#endif

// Greatly increases comilation time
// #define __windows_shim_BitScanReverse_x86_intrin

#if __windows_shim_arch == __windows_shim_arch_x86 && defined(__windows_shim_BitScanReverse_x86_intrin)
#include <x86intrin.h>
#endif

#ifndef __windows_shim

#ifndef __stdcall
#define __stdcall
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __fastcall
#define __fastcall
#endif

#ifndef __vectorcall
#define __vectorcall
#endif

#ifndef __declspec
#define __declspec(x)
#endif

#ifndef __forceinline
#define __forceinline __attribute__((always_inline)) inline
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#ifndef __Acquires_lock_
#define _Acquires_lock_(x)
#endif

#ifndef _Releases_lock_
#define _Releases_lock_(x)
#endif

#ifndef _Requires_lock_held_
#define _Requires_lock_held_(x)
#endif

#ifndef _Curr_
#define _Curr_ NULL
#endif

#ifndef _Analysis_assume_
#define _Analysis_assume_(x)
#endif

#ifndef _strcmpi
#define _strcmpi strcasecmp
#endif

#endif

#define __windows_shim

#pragma diagnostic ignored "-Wunused-function"

typedef int64_t __int64;
typedef int32_t __int32;
typedef int16_t __int16;
typedef int8_t __int8;

/*

// Normal

static inline char * _itoa(int value, char *buffer, int radix) {
	return itoa(value, buffer, radix);
}

static inline char * _ltoa(long value, char *buffer, int radix) {
	return ltoa(value, buffer, radix);
}

static inline char * _ultoa(unsigned long value, char *buffer, int radix) {
	return ultoa(value, buffer, radix);
}

static inline char * _i64toa(long long value, char *buffer, int radix) {
	return i64toa(value, buffer, radix);
}

static inline char * _ui64toa(unsigned long long value, char *buffer, int radix) {
	return ui64toa(value, buffer, radix);
}

// Wide

static inline char * _itow(int value, char *buffer, int radix) {
	return itow(value, buffer, radix);
}

static inline char * _ltow(long value, char *buffer, int radix) {
	return ltow(value, buffer, radix);
}

static inline char * _ultow(unsigned long value, char *buffer, int radix) {
	return ultow(value, buffer, radix);
}

static inline char * _i64tow(long long value, char *buffer, int radix) {
	return i64tow(value, buffer, radix);
}

static inline char * _ui64tow(unsigned long long value, char *buffer, int radix) {
	return ui64tow(value, buffer, radix);
}

*/

// Taken from geeksforgeeks - https://www.geeksforgeeks.org/c/implement-itoa/

// A utility function to reverse a string
static inline void __windows_shim_reverse(char str[], int length) {
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}
}
// Implementation of citoa()
static inline char* __windows_shim_itoa(int num, char* str, int base) {
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitly, otherwise empty string is
	 * printed for 0 */
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled
	// only with base 10. Otherwise numbers are
	// considered unsigned.
	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-'
	if (isNegative) {
		str[i++] = '-';
	}

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	__windows_shim_reverse(str, i);

	return str;
}

static inline char* _itoa(int value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ltoa(long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ultoa(unsigned long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _i64toa(long long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ui64toa(unsigned long long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

// This implementation is likely incorrect, will need special handling
#ifdef __WINDOWS_SHIM_ENABLE_XTOW

// Wide

static inline char* _itow(int value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ltow(long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ultow(unsigned long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _i64tow(long long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char* _ui64tow(unsigned long long value, char* buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

#endif

static inline void _lock_file(FILE* file) {
	printf("Stubbed function _lock_file called\n");
}

static inline void _unlock_file(FILE* file) {
	printf("Stubbed function _unlock_file called\n");
}

// Source - https://stackoverflow.com/a/1513215
// Posted by Alex B, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-08, License - CC BY-SA 2.5

static inline int fopen_s(FILE** f, const char* name, const char* mode) {
	int ret = 0;
	assert(f);
	*f = fopen(name, mode);
	// Can't be sure about 1-to-1 mapping of errno and MS' errno_t

	// if (!*f)
	//     ret = errno;
	return ret;
}

static inline int strcpy_s(char* dest, size_t dest_size, const char* src) {
	strncpy(dest, src, dest_size);
	return 1; // Assumed success return
}

static inline int strncpy_s(char* dest, size_t dest_size, const char* src, size_t count) {
	strncpy(dest, src, dest_size < count ? dest_size : count);
	return 1; // Assumed success return
}

static inline int sprintf_s(char* buffer, size_t sizeOfBuffer, const char* format, ...) {
	int result;
	va_list args;

	va_start(args, format);

	result = vsprintf(buffer, format, args);

	va_end(args);

	return result;
}

static inline int sprintf_s(char* buffer, const char* format, ...) {
	int result;
	va_list args;

	va_start(args, format);

	result = vsprintf(buffer, format, args);

	va_end(args);

	return result;
}

// #define strcpy_s strcpy
// #define strncpy_s strncpy
// #define sprintf_s sprintf

#if __windows_shim_arch == __windows_shim_arch_x86 && defined(__windows_shim_BitScanReverse_x86_intrin)

static unsigned char _BitScanReverse(uint32_t* Index, uint32_t Mask) {
	if (Mask == 0) {
		return 0;
	}
	*Index = _bit_scan_reverse(Mask);
	return 1;
}

static unsigned char _BitScanReverse64(uint32_t* Index, uint64_t Mask) {
	if (Mask == 0) {
		return 0;
	}
	*Index = _bit_scan_reverse(Mask);
	return 1;
}

#else

static unsigned char _BitScanReverse(uint32_t* Index, uint32_t Mask) {
	if (Mask == 0) {
		return 0;
	}
	*Index = (uint32_t)(31 - __builtin_clz(Mask));
	return 1;
}

static unsigned char _BitScanReverse64(uint32_t* Index, uint64_t Mask) {
	if (Mask == 0) {
		return 0;
	}
	*Index = (uint64_t)(63 - __builtin_clzll(Mask));
	return 1;
}

#endif

static inline char* _strrev(char* str) {
	const unsigned int str_len = strlen(str);
	char* tmp = (char*)malloc(str_len);

	for (int i = str_len; i != 0; i--) {
		tmp[str_len - i] = str[i];
	}

	strcpy(str, tmp);

	free(tmp);

	return str;
}

typedef int LCID;

#pragma diagnostic pop
