#ifndef _MACROS_H
#define _MACROS_H

#define ALIGNAS(N) __attribute__((aligned(N)))
#define ALIGN_PREV(X, N) ((X) & ~((N)-1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N)-1), N)

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define OFFSETOF(p, field) ((u8*)&(p)->field - (u8*)(p))

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
inline void padStack(void) { s32 pad = 0; }
#define PAD_STACK() padStack()

#ifdef __MWERKS__
#define ASM asm
#else
#define ASM
#endif

#ifdef __MWERKS__
#define WEAK __declspec(weak)
#else
#define WEAK
#endif

#ifdef __MWERKS__
#define INIT __declspec(section ".init")
#else
#define INIT
#endif

#ifdef __MWERKS__
#define AT_ADDRESS(xyz) : (xyz)
#else
#define AT_ADDRESS(xyz)
#endif

#endif
