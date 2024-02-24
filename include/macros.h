#ifndef _MACROS_H
#define _MACROS_H

#define ALIGNAS(N) __attribute__((aligned(N)))

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

// Adds no-ops to increase a function's size, preventing automatic inlining
#define NO_INLINE() \
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

#endif
