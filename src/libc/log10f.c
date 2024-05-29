#include "math.h"

#define __log10_2 0.301029995664f
#define __sqrt2_m1 0.41421356237f

const f32 _log10_poly[] = {
    0.868588984013f,
    0.289530873299f,
    0.173569247127f,
    0.130724057555f,
};

f32 log10f(f32 x) {
    f32 __log10_sqrt2;
    f32 y;
    f32 zsq;
    s32 exp;
    s32 tmp;

    switch (*(s32*)&x & 0xFF800000) {
        default:
            __log10_sqrt2 = 0.150514997831990597606869447362247f;
            if (*(s32*)&x & 0x80000000) {
                return NAN;
            }
            exp = (*(u32*)&x >> 23) - 126;
            if (*(s32*)& x &= 0x0007FFFFF) {
                *(s32*)&x |= 0x3F000000;
            } else {
                return --exp * __log10_2;
            }

            if (*(s32*)&x < 0x3F3504F3) {
                x += __sqrt2_m1 * x;
            } else {
                __log10_sqrt2 = 0.0f;
            }
            x = 1.0f - (2.0f / (x + 1.0f));
            zsq = x * x;
            y = (((_log10_poly[3] * zsq + _log10_poly[2]) * zsq + _log10_poly[1]) * zsq + _log10_poly[0]) * x;
            tmp = (s32)y;
            y -= (f32)tmp;
            return (exp * __log10_2 + tmp) + (y - __log10_sqrt2);
        case 0x7F800000:
        case 0xFF800000:
            if (*(s32*)&x & 0x007FFFFF) {
                return x;
            }
            if (*(s32*)&x & 0x80000000) {
                return NAN;
            }
            return INFINITY;
        case 0x00000000:
        case 0x80000000:
            return -INFINITY;
    }
}
