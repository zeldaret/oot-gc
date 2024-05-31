#include "math.h"

static const f64 two54 = 1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */
static const f64 twom54 = 5.55111512312578270212e-17; /* 0x3C900000, 0x00000000 */
static const f64 big = 1.0e+300;
static const f64 tiny = 1.0e-300;

f64 ldexp(f64 x, int n) {
    int k, hx, lx; /*- cc 020130 -*/

    if (!isfinite(x) || x == 0.0) {
        return x;
    }

    hx = __HI(x);
    lx = __LO(x);
    k = (hx & 0x7FF00000) >> 20; /* extract exponent */
    if (k == 0) { /* 0 or subnormal x */
        if ((lx | (hx & 0x7FFFFFFF)) == 0) {
            return x; /* +-0 */
        }
        x *= two54;
        hx = __HI(x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) {
            return tiny * x; /*underflow*/
        }
    }
    if (k == 0x7FF) {
        return x + x; /* NaN or Inf */
    }
    k = k + n;
    if (k > 0x7FE) {
        return big * copysign(big, x); /* overflow  */
    }
    if (k > 0) /* normal result */
    {
        __HI(x) = (hx & 0x800FFFFF) | (k << 20);
        return x;
    }
    if (k <= -54) {
        if (n > 50000) { /* in case integer overflow in n+k */
            return big * copysign(big, x); /*overflow*/
        } else {
            return tiny * copysign(tiny, x); /*underflow*/
        }
    }
    k += 54; /* subnormal result */
    __HI(x) = (hx & 0x800FFFFF) | (k << 20);
    return x * twom54;
}
