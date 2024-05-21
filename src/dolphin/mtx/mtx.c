#include "dolphin/mtx.h"
#include "dolphin/hw_regs.h"
#include "macros.h"

static f32 Unit01[] = {0.0f, 1.0f};

void PSMTXIdentity(register Mtx m) {
    register f32 zero_c;
    register f32 one_c;
    register f32 c_01;
    register f32 c_10;

    // fixes float ordering issue
    (void)1.0f;

    zero_c = 0.0f;
    one_c = 1.0f;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_st zero_c, 8(m), 0, 0
        ps_merge01 c_01, zero_c, one_c
        psq_st zero_c, 24(m), 0, 0
        ps_merge10 c_10, one_c, zero_c
        psq_st zero_c, 32(m), 0, 0
        psq_st c_01, 16(m), 0, 0
        psq_st c_10, 0(m), 0, 0
        psq_st c_10, 40(m), 0, 0
    }
#endif // clang-format on
}

ASM void PSMTXConcat(const register Mtx mA, const register Mtx mB, register Mtx mAB) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    stwu    r1, -64(r1);
    psq_l   FP0, 0(mA), 0, 0;
    stfd    fp14, 8(r1);
    psq_l   FP6, 0(mB), 0, 0;
    addis   r6, 0, Unit01@ha;
    psq_l   FP7, 8(mB), 0, 0;
    stfd    fp15, 16(r1)
    addi    r6, r6, Unit01@l;
    stfd    fp31, 40(r1)
    psq_l   FP8, 16(mB), 0, 0
    ps_muls0 FP12, FP6, FP0
    psq_l   FP2, 16(mA), 0, 0
    ps_muls0 FP13, FP7, FP0
    psq_l   FP31, 0(r6), 0, 0
    ps_muls0 FP14, FP6, FP2
    psq_l   FP9, 24(mB), 0, 0
    ps_muls0 FP15, FP7, FP2
    psq_l   FP1, 8(mA), 0, 0
    ps_madds1 FP12, FP8, FP0, FP12
    psq_l   FP3, 24(mA), 0, 0
    ps_madds1 FP14, FP8, FP2, FP14
    psq_l   FP10, 32(mB), 0, 0
    ps_madds1 FP13, FP9, FP0, FP13
    psq_l   FP11, 40(mB), 0, 0
    ps_madds1 FP15, FP9, FP2, FP15
    psq_l   FP4, 32(mA), 0, 0
    psq_l   FP5, 40(mA), 0, 0
    ps_madds0 FP12, FP10, FP1, FP12
    ps_madds0 FP13, FP11, FP1, FP13
    ps_madds0 FP14, FP10, FP3, FP14
    ps_madds0 FP15, FP11, FP3, FP15
    psq_st  FP12, 0(mAB), 0, 0

    ps_muls0 FP2, FP6, FP4
    ps_madds1 FP13, FP31, FP1, FP13
    ps_muls0 FP0, FP7, FP4
    psq_st  FP14, 16(mAB), 0, 0
    ps_madds1 FP15, FP31, FP3, FP15

    psq_st  FP13, 8(mAB), 0, 0

    ps_madds1 FP2, FP8, FP4, FP2
    ps_madds1 FP0, FP9, FP4, FP0
    ps_madds0 FP2, FP10, FP5, FP2
    lfd    fp14, 8(r1)
    psq_st  FP15, 24(mAB), 0, 0
    ps_madds0 FP0, FP11, FP5, FP0
    psq_st  FP2, 32(mAB), 0, 0
    ps_madds1 FP0, FP31, FP5, FP0
    lfd    fp15, 16(r1)
    psq_st  FP0, 40(mAB), 0, 0

    lfd    fp31, 40(r1)
    addi   r1, r1, 64

    blr
#endif // clang-format on
}

void PSMTXTrans(register Mtx m, register f32 xT, register f32 yT, register f32 zT) {
    register f32 c0 = 0.0F;
    register f32 c1 = 1.0F;

#ifdef __MWERKS__ // clang-format off
    asm {
        stfs        xT,     12(m)
        stfs        yT,     28(m)
        psq_st      c0,      4(m), 0, 0
        psq_st      c0,     32(m), 0, 0
        stfs        c0,     16(m)
        stfs        c1,     20(m)
        stfs        c0,     24(m)
        stfs        c1,     40(m)
        stfs        zT,     44(m)
        stfs        c1,      0(m)
    }
#endif // clang-format on
}

ASM void PSMTXTransApply(const register Mtx src, register Mtx dst, register f32 xT, register f32 yT, register f32 zT) {
#ifdef __MWERKS__ // clang-format off
    nofralloc;
    psq_l       fp4, 0(src),        0, 0
    frsp        xT, xT
    psq_l       fp5, 8(src),        0, 0
    frsp        yT, yT
    psq_l       fp7, 24(src),       0, 0
    frsp        zT, zT
    psq_l       fp8, 40(src),       0, 0
    psq_st      fp4, 0(dst),        0, 0
    ps_sum1     fp5, xT, fp5, fp5
    psq_l       fp6, 16(src),       0, 0   
    psq_st      fp5, 8(dst),        0, 0
    ps_sum1     fp7, yT, fp7, fp7
    psq_l       fp9, 32(src),       0, 0
    psq_st      fp6, 16(dst),       0, 0
    ps_sum1     fp8, zT, fp8, fp8
    psq_st      fp7, 24(dst),       0, 0
    psq_st      fp9, 32(dst),       0, 0
    psq_st      fp8, 40(dst),       0, 0
    blr
#endif // clang-format on
}

void PSMTXScale(register Mtx m, register f32 xS, register f32 yS, register f32 zS) {
    register f32 c0 = 0.0F;

#ifdef __MWERKS__ // clang-format off
    asm {
        stfs        xS,      0(m)
        psq_st      c0,      4(m), 0, 0
        psq_st      c0,     12(m), 0, 0
        stfs        yS,     20(m)
        psq_st      c0,     24(m), 0, 0
        psq_st      c0,     32(m), 0, 0
        stfs        zS,     40(m)
        stfs        c0,     44(m)
    }
#endif // clang-format on
}

ASM void PSMTXScaleApply(const register Mtx src, register Mtx dst, register f32 xS, register f32 yS, register f32 zS) {
#ifdef __MWERKS__ // clang-format off
    nofralloc;
    frsp        xS, xS
    psq_l       fp4, 0(src),        0, 0
    frsp        yS, yS
    psq_l       fp5, 8(src),        0, 0
    frsp        zS, zS
    ps_muls0    fp4, fp4, xS
    psq_l       fp6, 16(src),       0, 0
    ps_muls0    fp5, fp5, xS
    psq_l       fp7, 24(src),       0, 0
    ps_muls0    fp6, fp6, yS
    psq_l       fp8, 32(src),       0, 0
    psq_st      fp4, 0(dst),        0, 0
    ps_muls0    fp7, fp7, yS
    psq_l       fp2, 40(src),       0, 0
    psq_st      fp5, 8(dst),        0, 0
    ps_muls0    fp8, fp8, zS
    psq_st      fp6, 16(dst),       0, 0
    ps_muls0    fp2, fp2, zS
    psq_st      fp7, 24(dst),       0, 0
    psq_st      fp8, 32(dst),       0, 0
    psq_st      fp2, 40(dst),       0, 0
    blr
#endif // clang-format on
}
