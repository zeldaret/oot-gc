#ifndef _MATH_H_
#define _MATH_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MATH_INLINE
#define _MATH_INLINE static inline
#endif

#ifndef _INT32
typedef int _INT32;
typedef unsigned int _UINT32;
#endif

int abs(int n);
#ifdef __MWERKS__
#define abs(n) __abs(n)
#define labs(n) __labs(n)
static inline double fabs(double x) { return __fabs(x); }
#else
// static inline int abs(int n) {
//   int mask = n >> 31;
//   return (n + mask) ^ mask;
// }
#endif

extern _INT32 __float_huge[];
extern _INT32 __float_nan[];
extern _INT32 __double_huge[];
extern _INT32 __extended_huge[];

#define HUGE_VAL (*(double*)__double_huge)
#define INFINITY (*(float*)__float_huge)
#define NAN (*(float*)__float_nan)
#define HUGE_VALF (*(float*)__float_huge)
#define HUGE_VALL (*(long double*)__extended_huge)
#define M_PI 3.14159265358979323846

double fabs(double x);
double fmod(double x, double m);
double sin(double x);
double cos(double x);
double atan(double x);
double atan2(double y, double x);
double tan(double x);
double ceil(double x);

_MATH_INLINE float fabsf(float x) { return (float)fabs((double)x); }
_MATH_INLINE float atan2f(float y, float x) { return (float)atan2((double)y, (double)x); }
_MATH_INLINE float fmodf(float x, float m) { return (float)fmod((double)x, (double)m); }
float sinf(float x);
float cosf(float x);
float tanf(float x);
double asin(double x);
double acos(double x);
float acosf(float x);
double log(double x);
double exp(double x);

double ldexp(double x, int exp);

double copysign(double x, double y);

double floor(double x);
_MATH_INLINE float floorf(float x) { return floor(x); }

double fabs(double x);
double pow(double x, double y);
_MATH_INLINE float powf(float __x, float __y) { return pow(__x, __y); }

#ifdef __MWERKS__
#pragma cplusplus on
#endif

double __frsqrte(double x);

extern inline float sqrtf(float x) {
  const double _half = .5;
  const double _three = 3.0;
  volatile float y;

  if (x > 0.0f) {
    double guess = __frsqrte((double)x);                  /* returns an approximation to  */
    guess = _half * guess * (_three - guess * guess * x); /* now have 12 sig bits         */
    guess = _half * guess * (_three - guess * guess * x); /* now have 24 sig bits         */
    guess = _half * guess * (_three - guess * guess * x); /* now have 32 sig bits         */
    y = (float)(x * guess);
    return y;
  }
  return x;
}

_MATH_INLINE double sqrt(double x) {
  if (x > 0.0) {
    double guess = __frsqrte(x);                    /* returns an approximation to  */
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

_MATH_INLINE float _inv_sqrtf(float x) {
  const float _half = .5f;
  const float _three = 3.0f;

  if (x > 0.0f) {
    float guess = __frsqrte((double)x);                   /* returns an approximation to  */
    guess = _half * guess * (_three - guess * guess * x); /* now have 8  sig bits         */
    guess = _half * guess * (_three - guess * guess * x); /* now have 16 sig bits         */
    guess = _half * guess * (_three - guess * guess * x); /* now have >24 sig bits        */
    return guess;
  } else if (x) {
    return NAN;
  }
  return INFINITY;
}

static inline float ldexpf(float x, int exp) { return (float)ldexp((double)x, exp); }
static inline double scalbn(double x, int n) { return ldexp(x, n); }
static inline float scalbnf(float x, int n) { return (float)ldexpf(x, n); }

#ifdef __MWERKS__
#pragma cplusplus reset
#endif

#ifdef __cplusplus
}
#endif

#endif
