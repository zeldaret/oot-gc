#ifndef _MACROS_H
#define _MACROS_H

#include "versions.h"

// used for line numbers macros
#define UNK_LINE 0

#define ALIGN_PREV(X, N) ((X) & ~((N) - 1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N) - 1), N)

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define OFFSETOF(p, field) ((u8*)&(p)->field - (u8*)(p))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define SQ(x) ((x) * (x))
#define CLAMP(x, l, h) (((x) > (h)) ? (h) : (((x) < (l)) ? (l) : (x)))

// Adds no-ops to increase a function's size, preventing automatic inlining
#define NO_INLINE() \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0;        \
    (void)0

// Adds a stack variable in an inline function, which can be used to pad the
// stack after other functions have been inlined
inline void padStack(void) { int pad = 0; }
#define PAD_STACK() padStack()

#ifdef __MWERKS__
#define DECL_SECTION(x) __declspec(section x)
#define WEAK __declspec(weak)
#define ASM asm
#else
#define DECL_SECTION(x)
#define WEAK
#define ASM
#endif

#define INIT DECL_SECTION(".init")
#define CTORS DECL_SECTION(".ctors")
#define DTORS DECL_SECTION(".dtors")

#endif
