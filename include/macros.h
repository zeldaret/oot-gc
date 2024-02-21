#ifndef _MACROS_H
#define _MACROS_H

#define ALIGNAS(N) __attribute__((aligned(N)))

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

// No-ops increate the function's size, preventing automatic inline
#define NO_INLINE \
    {             \
        (void)0;  \
        (void)0;  \
        (void)0;  \
        (void)0;  \
    }

#endif
