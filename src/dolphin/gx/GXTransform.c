#include "dolphin/gx.h"
#include "dolphin/mtx.h"

inline void WriteProjPS(const register f32 src[6], register volatile void* dst) {
    register f32 ps_0, ps_1, ps_2;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_st ps_0,  0(dst), 0, 0
        psq_st ps_1,  0(dst), 0, 0
        psq_st ps_2,  0(dst), 0, 0
    }
#endif // clang-format on
}

inline void Copy6Floats(const register f32 src[6], register f32 dst[6]) {
    register f32 ps_0, ps_1, ps_2;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_st ps_0,  0(dst), 0, 0
        psq_st ps_1,  8(dst), 0, 0
        psq_st ps_2, 16(dst), 0, 0
    }
#endif // clang-format on
}

inline void __GXSetProjection(void) {
#if IS_MQ
    u32 reg = 0x00061020;

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(32, gx->projMtx[0]);
    GX_WRITE_XF_REG_F(33, gx->projMtx[1]);
    GX_WRITE_XF_REG_F(34, gx->projMtx[2]);
    GX_WRITE_XF_REG_F(35, gx->projMtx[3]);
    GX_WRITE_XF_REG_F(36, gx->projMtx[4]);
    GX_WRITE_XF_REG_F(37, gx->projMtx[5]);
    GX_WRITE_XF_REG_2(38, gx->projType);
#else
    GX_XF_LOAD_REGS(6, GX_XF_REG_PROJECTIONA);
    WriteProjPS(gx->projMtx, (volatile void*)GXFIFO_ADDR);
    GX_WRITE_U32(gx->projType);
#endif
}

void GXSetProjection(const Mtx44 proj, GXProjectionType type) {
    gx->projType = type;

    gx->projMtx[0] = proj[0][0];
    gx->projMtx[2] = proj[1][1];
    gx->projMtx[4] = proj[2][2];
    gx->projMtx[5] = proj[2][3];

    if (type == GX_ORTHOGRAPHIC) {
        gx->projMtx[1] = proj[0][3];
        gx->projMtx[3] = proj[1][3];
    } else {
        gx->projMtx[1] = proj[0][2];
        gx->projMtx[3] = proj[1][2];
    }

    __GXSetProjection();

    gx->bpSentNot = GX_TRUE;
}

void GXSetProjectionv(const f32* proj) {
#if IS_MQ
    gx->projType = proj[0];
    gx->projMtx[0] = proj[1];
    gx->projMtx[1] = proj[2];
    gx->projMtx[2] = proj[3];
    gx->projMtx[3] = proj[4];
    gx->projMtx[4] = proj[5];
    gx->projMtx[5] = proj[6];
#else
    gx->projType = proj[0] == 0.0f ? GX_PERSPECTIVE : GX_ORTHOGRAPHIC;
    Copy6Floats(&proj[1], gx->projMtx);
#endif

    __GXSetProjection();
    gx->bpSentNot = GX_TRUE;
}

inline void WriteMTXPS4x3(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3, ps_4, ps_5;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_l  ps_3, 24(src), 0, 0
        psq_l  ps_4, 32(src), 0, 0
        psq_l  ps_5, 40(src), 0, 0

        psq_st ps_0, 0(dst),  0, 0
        psq_st ps_1, 0(dst),  0, 0
        psq_st ps_2, 0(dst),  0, 0
        psq_st ps_3, 0(dst),  0, 0
        psq_st ps_4, 0(dst),  0, 0
        psq_st ps_5, 0(dst),  0, 0
    }
#endif // clang-format on
}

inline void WriteMTXPS3x3(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3, ps_4, ps_5;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l  ps_0,  0(src), 0, 0
        lfs    ps_1,  8(src)
        psq_l  ps_2, 16(src), 0, 0
        lfs    ps_3, 24(src)
        psq_l  ps_4, 32(src), 0, 0
        lfs    ps_5, 40(src)

        psq_st ps_0, 0(dst),  0, 0
        stfs   ps_1, 0(dst)
        psq_st ps_2, 0(dst),  0, 0
        stfs   ps_3, 0(dst)
        psq_st ps_4, 0(dst),  0, 0
        stfs   ps_5, 0(dst)
    }
#endif // clang-format on
}

inline void WriteMTXPS4x2(register volatile void* dst, register const Mtx src) {
    register f32 ps_0, ps_1, ps_2, ps_3;

#ifdef __MWERKS__ // clang-format off
    asm {
        psq_l  ps_0,  0(src), 0, 0
        psq_l  ps_1,  8(src), 0, 0
        psq_l  ps_2, 16(src), 0, 0
        psq_l  ps_3, 24(src), 0, 0

        psq_st ps_0, 0(dst),  0, 0
        psq_st ps_1, 0(dst),  0, 0
        psq_st ps_2, 0(dst),  0, 0
        psq_st ps_3, 0(dst),  0, 0
    }
#endif // clang-format on
}

void GXLoadPosMtxImm(Mtx mtx, u32 id) {
    GX_XF_LOAD_REGS(4 * 3 - 1, id * 4 + GX_XF_MEM_POSMTX);
    WriteMTXPS4x3(&GXWGFifo, mtx);
}

void GXLoadNrmMtxImm(Mtx mtx, u32 id) {
    GX_XF_LOAD_REGS(3 * 3 - 1, id * 3 + GX_XF_MEM_NRMMTX);
    WriteMTXPS3x3(&GXWGFifo, mtx);
}

void GXSetCurrentMtx(u32 id) {
    GX_SET_REG(gx->matIdxA, id, GX_XF_MTXIDX0_GEOM_ST, GX_XF_MTXIDX0_GEOM_END);
    __GXSetMatrixIndex(GX_VA_PNMTXIDX);
}

void GXLoadTexMtxImm(const Mtx mtx, u32 id, GXTexMtxType type) {
    u32 addr;
    u32 num;
    u32 reg;

    // Matrix address in XF memory
    addr = id >= GX_PTTEXMTX0 ? (id - GX_PTTEXMTX0) * 4 + GX_XF_MEM_DUALTEXMTX : id * 4 + (u64)GX_XF_MEM_POSMTX;

    // Number of elements in matrix
    num = type == GX_MTX2x4 ? (u64)(2 * 4) : 3 * 4;

    reg = addr | (num - 1) << 16;

    GX_XF_LOAD_REG_HDR(reg);

    if (type == GX_MTX3x4) {
        WriteMTXPS4x3(&GXWGFifo, mtx);
    } else {
        WriteMTXPS4x2(&GXWGFifo, mtx);
    }
}

#if IS_CE
void __GXSetViewport(void) {
    f32 sx;
    f32 sy;
    f32 sz;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 zmin;
    f32 zmax;
    u32 reg;

    sx = gx->vpWd / 2.0f;
    sy = -gx->vpHt / 2.0f;
    ox = 342.0f + (gx->vpLeft + (gx->vpWd / 2.0f));
    oy = 342.0f + (gx->vpTop + (gx->vpHt / 2.0f));

    zmin = gx->vpNearz * gx->zScale;
    zmax = gx->vpFarz * gx->zScale;

    sz = zmax - zmin;
    oz = zmax + gx->zOffset;

    reg = 0x5101A;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(26, sx);
    GX_WRITE_XF_REG_F(27, sy);
    GX_WRITE_XF_REG_F(28, sz);
    GX_WRITE_XF_REG_F(29, ox);
    GX_WRITE_XF_REG_F(30, oy);
    GX_WRITE_XF_REG_F(31, oz);
}
#endif

void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field) {
#if IS_MQ
    f32 sx;
    f32 sy;
    f32 sz;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 zmin;
    f32 zmax;
    u32 reg;

    if (field == 0) {
        top -= 0.5f;
    }

    sx = wd / 2.0f;
    sy = -ht / 2.0f;
    ox = 342.0f + (left + (wd / 2.0f));
    oy = 342.0f + (top + (ht / 2.0f));
    zmin = 1.6777215e7f * nearz;
    zmax = 1.6777215e7f * farz;
    sz = zmax - zmin;
    oz = zmax;

    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = wd;
    gx->vpHt = ht;
    gx->vpNearz = nearz;
    gx->vpFarz = farz;

    if (gx->fgRange != 0) {
        __GXSetRange(nearz, gx->fgSideX);
    }

    reg = 0x5101A;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(26, sx);
    GX_WRITE_XF_REG_F(27, sy);
    GX_WRITE_XF_REG_F(28, sz);
    GX_WRITE_XF_REG_F(29, ox);
    GX_WRITE_XF_REG_F(30, oy);
    GX_WRITE_XF_REG_F(31, oz);
#else
    if (field == 0) {
        top -= 0.5f;
    }

    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = wd;
    gx->vpHt = ht;
    gx->vpNearz = nearz;
    gx->vpFarz = farz;

    __GXSetViewport();
#endif

    gx->bpSentNot = GX_TRUE;
}

void GXSetViewport(f32 left, f32 top, f32 width, f32 height, f32 nearZ, f32 farZ) {
#if IS_MQ
    GXSetViewportJitter(left, top, width, height, nearZ, farZ, 1);
#else
    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = width;
    gx->vpHt = height;
    gx->vpNearz = nearZ;
    gx->vpFarz = farZ;
    __GXSetViewport();
    gx->bpSentNot = GX_TRUE;
#endif
}

void GXSetScissor(u32 left, u32 top, u32 width, u32 height) {
    u32 y1, x1, y2, x2;
    u32 reg;

    y1 = top + 342;
    x1 = left + 342;

    GX_SET_REG(gx->suScis0, y1, GX_BP_SCISSORTL_TOP_ST, GX_BP_SCISSORTL_TOP_END);
    GX_SET_REG(gx->suScis0, x1, GX_BP_SCISSORTL_LEFT_ST, GX_BP_SCISSORTL_LEFT_END);

    y2 = y1 + height - 1;
    x2 = x1 + width - 1;

    GX_SET_REG(gx->suScis1, y2, GX_BP_SCISSORBR_BOT_ST, GX_BP_SCISSORBR_BOT_END);
    GX_SET_REG(gx->suScis1, x2, GX_BP_SCISSORBR_RIGHT_ST, GX_BP_SCISSORBR_RIGHT_END);

    GX_BP_LOAD_REG(gx->suScis0);
    GX_BP_LOAD_REG(gx->suScis1);
    gx->bpSentNot = false;
}

void GXGetScissor(u32* left, u32* top, u32* width, u32* height) {
    u32 y1 = (gx->suScis0 & 0x0007FF) >> 0;
    u32 x1 = (gx->suScis0 & 0x7FF000) >> 12;
    u32 y2 = (gx->suScis1 & 0x0007FF) >> 0;
    u32 x2 = (gx->suScis1 & 0x7FF000) >> 12;

    *left = x1 - 0x156;
    *top = y1 - 0x156;
    *width = (x2 - x1) + 1;
    *height = (y2 - y1) + 1;
}

void GXSetScissorBoxOffset(s32 x, s32 y) {
    u32 cmd = 0;
    u32 x1;
    u32 y1;

    x1 = (u32)(x + 342) / 2;
    y1 = (u32)(y + 342) / 2;
    GX_SET_REG(cmd, x1, GX_BP_SCISSOROFS_OX_ST, GX_BP_SCISSOROFS_OX_END);
    GX_SET_REG(cmd, y1, GX_BP_SCISSOROFS_OY_ST, GX_BP_SCISSOROFS_OY_END);

    GX_SET_REG(cmd, GX_BP_REG_SCISSOROFFSET, 0, 7);

    GX_BP_LOAD_REG(cmd);
    gx->bpSentNot = GX_FALSE;
}

void GXSetClipMode(GXClipMode mode) {
    GX_XF_LOAD_REG(GX_XF_REG_CLIPDISABLE, mode);
    gx->bpSentNot = GX_TRUE;
}

void __GXSetMatrixIndex(GXAttr index) {
    // Tex4 and after is stored in XF MatrixIndex1
    if (index < GX_VA_TEX4MTXIDX) {
        GX_CP_LOAD_REG(GX_CP_REG_MTXIDXA, gx->matIdxA);
        GX_XF_LOAD_REG(GX_XF_REG_MATRIXINDEX0, gx->matIdxA);
    } else {
        GX_CP_LOAD_REG(GX_CP_REG_MTXIDXB, gx->matIdxB);
        GX_XF_LOAD_REG(GX_XF_REG_MATRIXINDEX1, gx->matIdxB);
    }

    gx->bpSentNot = GX_TRUE;
}
