#include "math.h"

f64 copysign(f64 x, f64 y) {
    __HI(x) = (__HI(x) & 0x7FFFFFFF) | (__HI(y) & 0x80000000);
    return x;
}
