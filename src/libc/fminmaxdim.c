#include "math.h"

#define __HI(x) (((s32*)&x)[0])
#define __LO(x) (((s32*)&x)[1])

// Referenced by a some unused function in this file
int __fpclassifyd__Fd(f64 x) {
    switch (__HI(x) & 0x7FF00000) {
        case 0x7FF00000: {
            if ((__HI(x) & 0x000FFFFF) || (__LO(x) & 0xFFFFFFFF))
                return FP_NAN;
            else
                return FP_INFINITE;
            break;
        }
        case 0: {
            if ((__HI(x) & 0x000FFFFF) || (__LO(x) & 0xFFFFFFFF))
                return FP_SUBNORMAL;
            else
                return FP_ZERO;
            break;
        }
    }
    return FP_NORMAL;
}
