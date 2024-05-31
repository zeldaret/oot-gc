#include "math.h"

static const f64 two54 = 1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */

f64 frexp(f64 x, int* eptr) {
    int hx, ix, lx;
    hx = __HI(x);
    ix = 0x7FFFFFFF & hx;
    lx = __LO(x);
    *eptr = 0;
    if (ix >= 0x7FF00000 || ((ix | lx) == 0)) {
        return x; /* 0,inf,nan */
    }
    if (ix < 0x00100000) { /* subnormal */
        x *= two54;
        hx = __HI(x);
        ix = hx & 0x7FFFFFFF;
        *eptr = -54;
    }
    *eptr += (ix >> 20) - 1022;
    hx = (hx & 0x800FFFFF) | 0x3FE00000;
    __HI(x) = hx;
    return x;
}
