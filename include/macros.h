#ifndef _MACROS_H
#define _MACROS_H

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define NO_INLINE \
    {             \
        (void)0;  \
        (void)0;  \
        (void)0;  \
        (void)0;  \
    }

#endif
