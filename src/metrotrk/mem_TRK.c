#include "metrotrk/mem_TRK.h"
#include "dolphin/types.h"
#include "macros.h"
#include "metrotrk/ppc_mem.h"

void TRK_fill_mem(void* dest, int val, size_t count);

INIT void* TRK_memcpy(void* dest, const void* src, size_t count) {
    u8* s = (u8*)src - 1;
    u8* d = (u8*)dest - 1;

    count++;

    while (--count) {
        *++d = *++s;
    }
}

INIT void* TRK_memset(void* dest, int val, size_t count) {
    TRK_fill_mem(dest, val, count);
    return dest;
}

void TRK_fill_mem(void* dest, int val, size_t count) {
    u32 v = (u8)val;
    u32 i;
    union {
        u8* cpd;
        u32* lpd;
    } dstu;

    dstu.cpd = (u8*)dest - 1;

    if (count >= 32) {
        i = ~(u32)dstu.cpd & 3;

        if (i) {
            count -= i;

            do {
                *++(dstu.cpd) = (u8)v;
            } while (--i);
        }

        if (v) {
            v |= ((v << 24) | (v << 16) | (v << 8));
        }

        dstu.lpd = (((u32*)(dstu.cpd + 1)) - 1);
        i = (count >> 5);

        if (i) {
            do {
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
            } while (--i);
        }

        i = ((count & 31) >> 2);

        if (i) {
            do {
                *++(dstu.lpd) = v;
            } while (--i);
        }

        dstu.cpd = (((u8*)(dstu.lpd + 1)) - 1);
        count &= 3;
    }

    if (count) {
        do {
            *++(dstu.cpd) = (u8)v;
        } while (--count);
    }
}
