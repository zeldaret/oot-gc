#ifndef _MATH_H_
#define _MATH_H_

#include "dolphin/types.h"
#include "intrinsics.h"
#include "macros.h"

#define M_PI 3.1415926535897932
#define M_SQRT3 1.7320499420166016

extern int __float_nan[];
extern int __float_huge[];

#define NAN (*(f32*)__float_nan)
#define INFINITY (*(f32*)__float_huge)

// f64 bit-twiddling macros
#define __HI(x) (((s32*)&x)[0])
#define __LO(x) (((s32*)&x)[1])

f64 ldexp(f64 x, int exp);
f64 pow(f64 x, f64 y);
f64 ceil(f64 x);
f64 floor(f64 x);
f64 copysign(f64 x, f64 y);

f32 sinf(f32 x);
f32 cosf(f32 x);
f32 tanf(f32 x);
f32 log10f(f32);
f32 powf(f32 x, f32 y);
f32 acosf(f32);
f32 atan2f(f32 x, f32 y);

static inline f64 fabs(f64 x) { return __fabs(x); }

// In reality, these are "weak" functions which all have C++ names (except scalbn).
// We fake it by defining them as strong C functions instead.
f32 sin__Ff(f32 x);
f32 cos__Ff(f32 x);
f64 scalbn(f64 x, int n);
f64 fabs__Fd(f64 x);
f32 fabsf__Ff(f32 x);

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

int __fpclassifyd__Fd(f64 x);

#define fpclassify(x) __fpclassifyd__Fd(x)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)
#define isnan(x) (fpclassify(x) == FP_NAN)
#define isinf(x) (fpclassify(x) == FP_INFINITE)
#define isfinite(x) (fpclassify(x) > FP_INFINITE)

// e_pow.c uses a non-inlined version of sqrt() defined in math_inlines.c instead
#ifdef DONT_INLINE_SQRT
f64 sqrt(f64 x);
#else
static inline f64 sqrt(f64 x) {
    if (x > 0.0) {
        f64 guess = __frsqrte(x); /* returns an approximation to  */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 8 sig bits          */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 16 sig bits         */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have 32 sig bits         */
        guess = .5 * guess * (3.0 - guess * guess * x); /* now have > 53 sig bits       */
        return x * guess;
    } else if (x == 0.0) {
        return 0;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}
#endif

static inline f32 sqrtf(f32 x) {
    const f64 _half = .5;
    const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x); /* returns an approximation to  */
        guess = _half * guess * (_three - guess * guess * x); /* now have 12 sig bits         */
        guess = _half * guess * (_three - guess * guess * x); /* now have 24 sig bits         */
        guess = _half * guess * (_three - guess * guess * x); /* now have 32 sig bits         */
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline f32 _inv_sqrtf(f32 x) {
    const f32 _half = .5f;
    const f32 _three = 3.0f;

    if (x > 0.0f) {
        f32 guess = __frsqrte((f64)x); /* returns an approximation to  */
        guess = _half * guess * (_three - guess * guess * x); /* now have 8  sig bits         */
        guess = _half * guess * (_three - guess * guess * x); /* now have 16 sig bits         */
        guess = _half * guess * (_three - guess * guess * x); /* now have >24 sig bits        */
        return guess;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}

#endif
