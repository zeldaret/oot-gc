#include "dolphin/types.h"
#include "macros.h"
#include "stddef.h"

INIT void* memcpy(void* dst, const void* src, size_t n) {
    const char* p;
    char* q;
    int rev = ((u32)src < (u32)dst);

    if (!rev) {
        for (p = (const char*)src - 1, q = (char*)dst - 1, n++; --n;) {
            *++q = *++p;
        }
    } else {
        for (p = (const char*)src + n, q = (char*)dst + n, n++; --n;) {
            *--q = *--p;
        }
    }

    return dst;
}

INIT void __fill_mem(void* dst, int val, size_t n) {
    u32 v = (u8)val;
    u32 i;

    dst = (void*)((u8*)dst - 1);

    if (n >= 32) {
        i = (~(u32)dst) & 3;

        if (i) {
            n -= i;

            do {
                dst = (void*)((u8*)dst + 1);
                *(u8*)dst = v;
            } while (--i);
        }

        if (v) {
            v |= v << 24 | v << 16 | v << 8;
        }

        dst = (void*)((u32*)((u8*)dst + 1) - 1);
        i = n >> 5;

        if (i) {
            do {
#if __MWERKS__
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
                *++(((u32*)dst)) = v;
#else
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
#endif
            } while (--i);
        }

        i = (n & 31) >> 2;

        if (i) {
            do {
                dst = (void*)((u32*)dst + 1);
                *(u32*)dst = v;
            } while (--i);
        }

        dst = (void*)((u8*)((u32*)dst + 1) - 1);
        n &= 3;
    }

    if (n) {
        do {
            dst = (void*)((u8*)dst + 1);
            *(u8*)dst = v;
        } while (--n);
    }
}

INIT void* memset(void* dst, int val, size_t n) {
    __fill_mem(dst, val, n);

    return dst;
}
