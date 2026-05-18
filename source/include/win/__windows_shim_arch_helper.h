#pragma once

// Source - https://stackoverflow.com/a/66249936
// Posted by FreakAnon, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-10, License - CC BY-SA 4.0

#define __windows_shim_arch_x86 0
#define __windows_shim_arch_ARM 1
#define __windows_shim_arch_MIPS 2
#define __windows_shim_arch_SUPERH 3
#define __windows_shim_arch_PPC 4
#define __windows_shim_arch_SPARC 5
#define __windows_shim_arch_M68K 6
#define __windows_shim_arch_UNKNOWN 7

#define __windows_shim_arch_detailed_x86_64 0
#define __windows_shim_arch_detailed_x86_32 1
#define __windows_shim_arch_detailed_ARM2 2
#define __windows_shim_arch_detailed_ARM3 3
#define __windows_shim_arch_detailed_ARM4T 4
#define __windows_shim_arch_detailed_ARM5 5
#define __windows_shim_arch_detailed_ARM6T2 6
#define __windows_shim_arch_detailed_ARM6 7
#define __windows_shim_arch_detailed_ARM7 8
#define __windows_shim_arch_detailed_ARM7A 9
#define __windows_shim_arch_detailed_ARM7R 10
#define __windows_shim_arch_detailed_ARM7M 11
#define __windows_shim_arch_detailed_ARM7S 12
#define __windows_shim_arch_detailed_ARM64 13
#define __windows_shim_arch_detailed_MIPS 14
#define __windows_shim_arch_detailed_SUPERH 15
#define __windows_shim_arch_detailed_POWERPC 16
#define __windows_shim_arch_detailed_POWERPC64 17
#define __windows_shim_arch_detailed_SPARC 18
#define __windows_shim_arch_detailed_M68K 19
#define __windows_shim_arch_detailed_UNKNOWN 20

// Get current architecture, detectx nearly every architecture. Coded by Freak
#if defined(__x86_64__) || defined(_M_X64)
#define __windows_shim_arch __windows_shim_arch_x86
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_x86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#define __windows_shim_arch __windows_shim_arch_x86
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_x86_32
#elif defined(__ARM_ARCH_2__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM2
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM3
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM4T
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM5
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM6T2
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM6
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM7
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM7A
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM7R
#elif defined(__ARM_ARCH_7M__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM7M
#elif defined(__ARM_ARCH_7S__)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM7S
#elif defined(__aarch64__) || defined(_M_ARM64)
#define __windows_shim_arch __windows_shim_arch_ARM
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_ARM64
#elif defined(mips) || defined(__mips__) || defined(__mips)
#define __windows_shim_arch __windows_shim_arch_MIPS
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_MIPS
#elif defined(__sh__)
#define __windows_shim_arch __windows_shim_arch_SUPERH
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_SUPERH
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#define __windows_shim_arch __windows_shim_arch_PPC
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_POWERPC
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#define __windows_shim_arch __windows_shim_arch_PPC
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_POWERPC64
#elif defined(__sparc__) || defined(__sparc)
#define __windows_shim_arch __windows_shim_arch_SPARC
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_SPARC
#elif defined(__m68k__)
#define __windows_shim_arch __windows_shim_arch_M68K
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_M68K
#else
#define __windows_shim_arch __windows_shim_arch_UNKNOWN
#define __windows_shim_arch_detailed __windows_shim_arch_detailed_UNKNOWN
#endif
