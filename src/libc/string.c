#include "string.h"
#include "dolphin/types.h"
#include "macros.h"

s32 K1 = 0x80808080;
s32 K2 = 0xFEFEFEFF;

size_t strlen(const char* s) {
    size_t len = -1;
    const u8* p = (u8*)s - 1;

    do {
        len++;
    } while (*++p != 0);

    return len;
}

char* strcpy(char* dst, const char* src) {
    u8* p1 = (u8*)dst;
    const u8* p2 = (u8*)src;
    s32 w;
    s32 t;
    u32 align;
    s32 k1;
    s32 k2;

    if ((align = (u32)src & 3) != ((u32)dst & 3)) {
        goto bytecopy;
    }

    if (align != 0) {
        if ((*p1 = *p2) == 0) {
            return dst;
        }

        align = 3 - align;
        while (align != 0) {
            if ((*++p1 = *++p2) == 0) {
                return dst;
            }
            align--;
        }

        p1++;
        p2++;
    }

    k1 = K1;
    k2 = K2;

    w = *(s32*)p2;
    t = w + k2;
    t &= k1;

    if (t != 0) {
        goto bytecopy;
    }

    p1 -= 4;

    while (true) {
#if __MWERKS__
        *++((s32*)p1) = w;
        w = *++((s32*)p2);
#else
        p1 += 4;
        p2 += 4;
        *(s32*)p1 = w;
        w = *(s32*)p2;
#endif

        t = w + k2;
        t &= k1;
        if (t != 0) {
            break;
        }
    }

    p1 += 4;

bytecopy:
    if ((*p1 = *p2) == 0) {
        return dst;
    }

    align = 3 - align;
    while (true) {
        if ((*++p1 = *++p2) == 0) {
            return dst;
        }
    }

    return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
    const u8* p = (const u8*)src - 1;
    u8* q = (u8*)dst - 1;

    n++;
    while (--n) {
        if ((*++q = *++p) == 0) {
            while (--n) {
                *++q = 0;
            }
            break;
        }
    }
    return dst;
}

#if IS_EU || IS_MM
char* strcat(char* dst, const char* src) {
    const u8* p = (u8*)src - 1;
    u8* q = (u8*)dst - 1;

    while (*++q)
        ;

    q--;

    while (*++q = *++p)
        ;

    return (dst);
}
#endif

int strcmp(const char* str1, const char* str2) {
    register u8* left = (u8*)str1;
    register u8* right = (u8*)str2;
    u32 align, l1, r1, x;

    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return l1 - r1;
    }

    if ((align = ((s32)left & 3)) != ((s32)right & 3)) {
        goto bytecopy;
    }

    if (align) {
        if (l1 == 0) {
            return 0;
        }
        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            if (l1 - r1) {
                return l1 - r1;
            }
            if (l1 == 0) {
                return 0;
            }
        }
        left++;
        right++;
    }

    l1 = *(s32*)left;
    r1 = *(s32*)right;
    x = l1 + K2;
    if (x & K1) {
        goto adjust;
    }

    while (l1 == r1) {
        left += 4;
        right += 4;
        l1 = *(s32*)left;
        r1 = *(s32*)right;
        x = l1 + K2;
        if (x & K1) {
            goto adjust;
        }
    }

    if (l1 > r1) {
        return 1;
    }
    return -1;

adjust:
    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return l1 - r1;
    }

bytecopy:
    if (l1 == 0) {
        return 0;
    }

    do {
        l1 = *(++left);
        r1 = *(++right);
        if (l1 - r1) {
            return l1 - r1;
        }
        if (l1 == 0) {
            return 0;
        }
    } while (true);
}

int strncmp(const char* str1, const char* str2, size_t n) {
    const u8* p1 = (u8*)str1 - 1;
    const u8* p2 = (u8*)str2 - 1;
    u32 c1, c2;

    n++;
    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return c1 - c2;
        } else if (c1 == 0) {
            break;
        }
    }

    return 0;
}

char* strchr(const char* str, int c) {
    const u8* p = (u8*)str - 1;
    u32 chr = (c & 0xFF);

    u32 ch;
    while (ch = *++p) {
        if (ch == chr) {
            return (char*)p;
        }
    }

    return chr ? NULL : (char*)p;
}
