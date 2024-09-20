#include "dolphin/types.h"
#include "mem_funcs.h"
#include "string.h"

void* memmove(void* dst, const void* src, size_t n) {
    const u8* p1;
    u8* p2;
    bool rev = (u32)src < (u32)dst;

    if (n >= 32) {
        if ((((u32)dst ^ (u32)src) & 3) != 0) {
            if (!rev) {
                __copy_longs_unaligned(dst, src, n);
            } else {
                __copy_longs_rev_unaligned(dst, src, n);
            }
        } else {
            if (!rev) {
                __copy_longs_aligned(dst, src, n);
            } else {
                __copy_longs_rev_aligned(dst, src, n);
            }
        }
        return dst;
    }

    if (!rev) {
        p1 = (u8*)src - 1;
        p2 = (u8*)dst - 1;
        n++;
        while (--n) {
            *++p2 = *++p1;
        }
    } else {
        p1 = (u8*)src + n;
        p2 = (u8*)dst + n;
        n++;
        while (--n) {
            *--p2 = *--p1;
        }
    }

    return dst;
}

void* memchr(const void* src, int val, size_t n) {
    const u8* p;
    u32 v = val & 0xFF;

    p = (u8*)src - 1;
    n++;
    while (--n) {
        if (*++p == v) {
            return (void*)p;
        }
    }

    return NULL;
}

int memcmp(const void* src1, const void* src2, size_t n) {
    const u8* p1 = (u8*)src1 - 1;
    const u8* p2 = (u8*)src2 - 1;

    n++;
    while (--n) {
        if (*++p1 != *++p2) {
            return *p1 < *p2 ? -1 : 1;
        }
    }

    return 0;
}
