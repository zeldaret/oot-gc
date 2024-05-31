#include "math.h"

#define huge 1.0e300

f64 floor(f64 x) {
    int i0, i1, j0;
    u32 i, j;

    i0 = __HI(x);
    i1 = __LO(x);
    j0 = ((i0 >> 20) & 0x7FF) - 0x3FF;
    if (j0 < 20) {
        if (j0 < 0) { /* raise inexact if x != 0 */
            if (huge + x > 0.0) { /* return 0*sign(x) if |x|<1 */
                if (i0 >= 0) {
                    i0 = i1 = 0;
                } else if (((i0 & 0x7FFFFFFF) | i1) != 0) {
                    i0 = 0xBFF00000;
                    i1 = 0;
                }
            }
        } else {
            i = (0x000FFFFF) >> j0;
            if (((i0 & i) | i1) == 0) {
                return x; /* x is integral */
            }
            if (huge + x > 0.0) { /* raise inexact flag */
                if (i0 < 0) {
                    i0 += (0x00100000) >> j0;
                }
                i0 &= (~i);
                i1 = 0;
            }
        }
    } else if (j0 > 51) {
        if (j0 == 0x400) {
            return x + x; /* inf or NaN */
        } else {
            return x; /* x is integral */
        }
    } else {
        i = ((u32)(0xFFFFFFFF)) >> (j0 - 20);
        if ((i1 & i) == 0) {
            return x; /* x is integral */
        }
        if (huge + x > 0.0) { /* raise inexact flag */
            if (i0 < 0) {
                if (j0 == 20) {
                    i0 += 1;
                } else {
                    j = i1 + (1 << (52 - j0));
                    if (j < i1) {
                        i0 += 1; /* got a carry */
                    }
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    return x;
}
