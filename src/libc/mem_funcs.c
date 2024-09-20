#include "dolphin/types.h"

#ifdef __MWERKS__

void __copy_longs_aligned(void* dst, const void* src, unsigned long n) {
    u32 i;

    i = (-(u32)dst) & 3;
    src = ((u8*)src) - 1;
    dst = ((u8*)dst) - 1;

    if (i > 0) {
        n -= i;
        do {
            *(++((u8*)dst)) = *(++((u8*)src));
        } while (--i);
    }

    i = n >> 5;
    src = (u32*)((u8*)src + 1) - 1;
    dst = (u32*)((u8*)dst + 1) - 1;

    if (i > 0) {
        do {
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
            *(++((u32*)dst)) = *(++((u32*)src));
        } while (--i);
    }

    i = (n & 31) >> 2;
    if (i > 0) {
        do {
            *(++((u32*)dst)) = *(++((u32*)src));
        } while (--i);
    }

    src = (u8*)((u32*)src + 1) - 1;
    dst = (u8*)((u32*)dst + 1) - 1;

    n &= 3;
    if (n > 0) {
        do {
            *(++((u8*)dst)) = *(++((u8*)src));
        } while (--n);
    }
}

void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n) {
    u32 i;

    src = ((u8*)src) + n;
    dst = ((u8*)dst) + n;
    i = ((u32)dst) & 3;

    if (i > 0) {
        n -= i;
        do {
            *(--((u8*)dst)) = *(--((u8*)src));
        } while (--i);
    }

    i = n >> 5;

    if (i > 0) {
        do {
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
            *(--((u32*)dst)) = *(--((u32*)src));
        } while (--i);
    }

    i = (n & 31) >> 2;
    if (i > 0) {
        do {
            *(--((u32*)dst)) = *(--((u32*)src));
        } while (--i);
    }

    n &= 3;
    if (n > 0) {
        do {
            *(--((u8*)dst)) = *(--((u8*)src));
        } while (--n);
    }
}

void __copy_longs_unaligned(void* dst, const void* src, unsigned long n) {
    u32 i;
    u32 v1;
    u32 v2;
    u32 offset;
    u32 shiftl;
    u32 shiftr;

    i = (-(u32)dst) & 3;
    src = ((u8*)src) - 1;
    dst = ((u8*)dst) - 1;

    if (i > 0) {
        n -= i;
        do {
            *(++((u8*)dst)) = *(++((u8*)src));
        } while (--i);
    }

    offset = (u32)((u8*)src + 1) & 3;
    shiftl = offset << 3;
    shiftr = 32 - shiftl;

    (u8*)src -= offset;
    src = (u32*)((u8*)src + 1) - 1;
    dst = (u32*)((u8*)dst + 1) - 1;

    i = n >> 3;
    v1 = *(++((u32*)src));
    do {
        v2 = *(++((u32*)src));
        *(++((u32*)dst)) = (v1 << shiftl) | (v2 >> shiftr);
        v1 = *(++((u32*)src));
        *(++((u32*)dst)) = (v2 << shiftl) | (v1 >> shiftr);
    } while (--i);

    if ((n & 4) != 0) {
        v2 = *(++((u32*)src));
        *(++((u32*)dst)) = (v1 << shiftl) | (v2 >> shiftr);
    }

    src = (u8*)((u32*)src + 1) - 1;
    dst = (u8*)((u32*)dst + 1) - 1;

    n &= 3;
    if (n > 0) {
        (u8*)src -= 4 - offset;
        do {
            *(++((u8*)dst)) = *(++((u8*)src));
        } while (--n);
    }
}

void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n) {
    u32 i;
    u32 v1;
    u32 v2;
    u32 offset;
    u32 shiftl;
    u32 shiftr;

    src = ((u8*)src) + n;
    dst = ((u8*)dst) + n;
    i = (u32)dst & 3;

    if (i > 0) {
        n -= i;
        do {
            *(--((u8*)dst)) = *(--((u8*)src));
        } while (--i);
    }

    offset = (u32)src & 3;
    shiftl = offset << 3;
    shiftr = 32 - shiftl;

    (u8*)src += 4 - offset;

    i = n >> 3;
    v1 = *(--((u32*)src));
    do {
        v2 = *(--((u32*)src));
        *(--((u32*)dst)) = (v2 << shiftl) | (v1 >> shiftr);
        v1 = *(--((u32*)src));
        *(--((u32*)dst)) = (v1 << shiftl) | (v2 >> shiftr);
    } while (--i);

    if ((n & 4) != 0) {
        v2 = *(--((u32*)src));
        *(--((u32*)dst)) = (v2 << shiftl) | (v1 >> shiftr);
    }

    n &= 3;
    if (n > 0) {
        (u8*)src += offset;
        do {
            *(--((u8*)dst)) = *(--((u8*)src));
        } while (--n);
    }
}

#else

void __copy_longs_aligned(void* dst, const void* src, unsigned long n) { memcpy(dst, src, n); }

void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n) { memcpy(dst, src, n); }

void __copy_longs_unaligned(void* dst, const void* src, unsigned long n) { memcpy(dst, src, n); }

void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n) { memcpy(dst, src, n); }

#endif
