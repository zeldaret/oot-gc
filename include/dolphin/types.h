#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long int s64;
typedef unsigned long long int u64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
typedef double f64;

typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef char* Ptr;

typedef int bool;

#define false 0
#define true 1

#if defined(__MWERKS__)
#define AT_ADDRESS(addr) : (addr)
#elif defined(__GNUC__)
// #define AT_ADDRESS(addr) __attribute__((address((addr))))
#define AT_ADDRESS(addr) // was removed in GCC. define in linker script instead.
#elif __INTELLISENSE__
#define AT_ADDRESS(addr)
#else
#error unknown compiler
#endif

#ifdef __MWERKS__
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#else
#define ATTRIBUTE_ALIGN(num)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#include "libc/ctype.h"
#include "libc/stdarg.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "cmath.h"

#endif
