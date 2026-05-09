#pragma once

#include <stdio.h>

#define __stdcall
#define __cdecl
#define __fastcall

#define __declspec(x)

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
static inline void __windows_shim_reverse(char str[], int length)
{
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
static inline char* __windows_shim_itoa(int num, char* str, int base)
{
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
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    __windows_shim_reverse(str, i);

    return str;
}

static inline char * _itoa(int value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ltoa(long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ultoa(unsigned long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _i64toa(long long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ui64toa(unsigned long long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

// This implementation is likely incorrect, will need special handling
#ifdef __WINDOWS_SHIM_ENABLE_XTOW

// Wide

static inline char * _itow(int value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ltow(long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ultow(unsigned long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _i64tow(long long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

static inline char * _ui64tow(unsigned long long value, char *buffer, int radix) {
	return __windows_shim_itoa(value, buffer, radix);
}

#endif

static inline void _lock_file(FILE* file) {
	printf("Stubbed function _lock_file called\n");
}

static inline void _unlock_file(FILE* file) {
	printf("Stubbed function _unlock_file called\n");
}
