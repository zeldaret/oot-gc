#include "dolphin/hw_regs.h"
#include "dolphin/mtx.h"
#include "macros.h"
#include "math.h"

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 temp_f4;
    f32 temp_f3;

    // fixes float ordering issue
    (void)1.0f;
    (void)2.0f;
    (void)0.0f;
    (void)-1.0f;

    fovY = 0.5f * fovY;
    temp_f4 = 1.0f / tanf((f32)M_PI / 180 * fovY);
    temp_f3 = 1.0f / (f - n);

    m[0][0] = temp_f4 / aspect;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = temp_f4;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -n * temp_f3;
    m[2][3] = -(f * n) * temp_f3;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 temp_f8;
    f32 temp_f10;
    f32 temp_f4;

    temp_f10 = 1.0f / (r - l);
    m[0][0] = 2.0f * temp_f10;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = temp_f10 * -(r + l);

    temp_f8 = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * temp_f8;
    m[1][2] = 0.0f;
    m[1][3] = temp_f8 * -(t + b);

    temp_f4 = 1.0f / (f - n);
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f * temp_f4;
    m[2][3] = -f * temp_f4;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

ASM void PSMTX44Concat(const register Mtx44 mA, const register Mtx44 mB, register Mtx44 mAB) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    psq_l   FP0, 0(mA), 0, 0
    psq_l   FP2, 0(mB), 0, 0
    ps_muls0    FP6, FP2, FP0
    psq_l   FP3, 16(mB), 0, 0
    psq_l   FP4, 32(mB), 0, 0
    ps_madds1   FP6, FP3, FP0, FP6
    psq_l   FP1, 8(mA), 0, 0
    psq_l   FP5, 48(mB), 0, 0
    ps_madds0   FP6, FP4, FP1, FP6
    psq_l   FP0, 16(mA), 0, 0
    ps_madds1   FP6, FP5, FP1, FP6
    psq_l   FP1, 24(mA), 0, 0
    ps_muls0    FP8, FP2, FP0
    ps_madds1   FP8, FP3, FP0, FP8
    psq_l   FP0, 32(mA), 0, 0
    ps_madds0   FP8, FP4, FP1, FP8
    ps_madds1   FP8, FP5, FP1, FP8
    psq_l   FP1, 40(mA), 0, 0
    ps_muls0    FP10, FP2, FP0
    ps_madds1   FP10, FP3, FP0, FP10
    psq_l   FP0, 48(mA), 0, 0
    ps_madds0   FP10, FP4, FP1, FP10
    ps_madds1   FP10, FP5, FP1, FP10
    psq_l   FP1, 56(mA), 0, 0
    ps_muls0    FP12, FP2, FP0
    psq_l   FP2, 8(mB), 0, 0
    ps_madds1   FP12, FP3, FP0, FP12
    psq_l   FP0, 0(mA), 0, 0
    ps_madds0   FP12, FP4, FP1, FP12
    psq_l   FP3, 24(mB), 0, 0
    ps_madds1   FP12, FP5, FP1, FP12
    psq_l   FP1, 8(mA), 0, 0
    ps_muls0    FP7, FP2, FP0
    psq_l   FP4, 40(mB), 0, 0
    ps_madds1   FP7, FP3, FP0, FP7
    psq_l   FP5, 56(mB), 0, 0
    ps_madds0   FP7, FP4, FP1, FP7
    psq_l   FP0, 16(mA), 0, 0
    ps_madds1   FP7, FP5, FP1, FP7
    psq_l   FP1, 24(mA), 0, 0
    ps_muls0    FP9, FP2, FP0
    psq_st  FP6, 0(mAB), 0, 0
    ps_madds1   FP9, FP3, FP0, FP9
    psq_l   FP0, 32(mA), 0, 0
    ps_madds0   FP9, FP4, FP1, FP9
    psq_st  FP8, 16(mAB), 0, 0
    ps_madds1   FP9, FP5, FP1, FP9
    psq_l   FP1, 40(mA), 0, 0
    ps_muls0    FP11, FP2, FP0
    psq_st  FP10, 32(mAB), 0, 0
    ps_madds1   FP11, FP3, FP0, FP11
    psq_l   FP0, 48(mA), 0, 0
    ps_madds0   FP11, FP4, FP1, FP11
    psq_st  FP12, 48(mAB), 0, 0
    ps_madds1   FP11, FP5, FP1, FP11
    psq_l   FP1, 56(mA), 0, 0
    ps_muls0    FP13, FP2, FP0
    psq_st  FP7, 8(mAB), 0, 0
    ps_madds1   FP13, FP3, FP0, FP13
    psq_st  FP9, 24(mAB), 0, 0
    ps_madds0   FP13, FP4, FP1, FP13
    psq_st  FP11, 40(mAB), 0, 0
    ps_madds1   FP13, FP5, FP1, FP13
    psq_st  FP13, 56(mAB), 0, 0
    blr
#endif // clang-format on
}
