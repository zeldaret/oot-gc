#include "math.h"

extern f64 __ieee754_pow(f64 x, f64 y);

f64 pow(f64 x, f64 y) { return __ieee754_pow(x, y); }
