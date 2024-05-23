#include "dolphin/hw_regs.h"
#include "dolphin/mtx.h"
#include "macros.h"

ASM void PSMTXMultVec(const register Mtx m, const register Vec* src, register Vec* dst) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    psq_l   FP0, 0(src), 0, 0
    psq_l   FP2, 0(m), 0, 0
    psq_l   FP1, 8(src), 1, 0
    ps_mul  FP4, FP2, FP0
    psq_l   FP3, 8(m), 0, 0
    ps_madd FP5, FP3, FP1, FP4
    psq_l   FP8, 16(m), 0, 0
    ps_sum0 FP6, FP5, FP6, FP5
    psq_l   FP9, 24(m), 0, 0
    ps_mul  FP10, FP8, FP0
    psq_st  FP6, 0(dst), 1, 0
    ps_madd FP11, FP9, FP1, FP10
    psq_l   FP2, 32(m), 0, 0
    ps_sum0 FP12, FP11, FP12, FP11
    psq_l   FP3, 40(m), 0, 0
    ps_mul  FP4, FP2, FP0
    psq_st  FP12, 4(dst), 1, 0
    ps_madd FP5, FP3, FP1, FP4
    ps_sum0 FP6, FP5, FP6, FP5
    psq_st  FP6, 8(dst), 1, 0
    blr
#endif // clang-format on
}
