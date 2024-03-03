#ifndef _MATH_H
#define _MATH_H

#include "dolphin.h"

extern u32 __float_nan[];
extern u32 __float_huge[];

#define NAN (*(f32*)__float_nan)
#define INFINITY (*(f32*)__float_huge)

f64 floor(f64);
f64 ceil(f64);

inline f64 fabs(f64 x) { return __fabs(x); }

inline f64 sqrt(f64 x) {
    if (x > 0.0) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0.0;
    } else if (x) {
        return NAN;
    }

    return INFINITY;
}

#endif
