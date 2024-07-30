#include "dolphin/gx.h"

void __GXSetDirtyState(void) {
#if IS_MQ
#define DIRTY_FLAGS gx->dirtyState
#else
    u32 dirtyFlags = gx->dirtyState;
#define DIRTY_FLAGS dirtyFlags
#endif

    if (DIRTY_FLAGS & 1) {
        __GXSetSUTexRegs();
    }

    if (DIRTY_FLAGS & 2) {
        __GXUpdateBPMask();
    }

    if (DIRTY_FLAGS & 4) {
        __GXSetGenMode();
    }

    if (DIRTY_FLAGS & 8) {
        __GXSetVCD();
    }

    if (DIRTY_FLAGS & 0x10) {
        __GXSetVAT();
    }

    if (DIRTY_FLAGS & 0x18) {
        __GXCalculateVLim();
    }

    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num) {
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }

    if (GX_CHECK_FLUSH()) {
        __GXSendFlushPrim();
    }

    GX_WRITE_U8(fmt | type);
    GX_WRITE_U16(vert_num);
}

void __GXSendFlushPrim(void) {
    u32 i;
    u32 sz = (gx->vNum * gx->vLim);

    GX_WRITE_U8(0x98);
    GX_WRITE_U16(gx->vNum);

    for (i = 0; i < sz; i += 4) {
        GX_WRITE_U32(0);
    }

    gx->bpSentNot = GX_TRUE;
}

void GXSetLineWidth(u8 width, GXTexOffset offsets) {
    GX_SET_REG(gx->lpSize, width, 24, 31);
    GX_SET_REG(gx->lpSize, offsets, 13, 15);

    GX_BP_LOAD_REG(gx->lpSize);

    gx->bpSentNot = GX_FALSE;
}

void GXSetPointSize(u8 size, GXTexOffset offsets) {
    GX_SET_REG(gx->lpSize, size, 16, 23);
    GX_SET_REG(gx->lpSize, offsets, 10, 12);

    GX_BP_LOAD_REG(gx->lpSize);

    gx->bpSentNot = GX_FALSE;
}

void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point) {
    GX_SET_REG(gx->suTs0[coord], line, 13, 13);
    GX_SET_REG(gx->suTs0[coord], point, 12, 12);

    GX_BP_LOAD_REG(gx->suTs0[coord]);

    gx->bpSentNot = GX_FALSE;
}

void GXSetCullMode(GXCullMode mode) {
    switch (mode) {
        case GX_CULL_FRONT:
            mode = GX_CULL_BACK;
            break;
        case GX_CULL_BACK:
            mode = GX_CULL_FRONT;
            break;
    }

    GX_SET_REG(gx->genMode, mode, 16, 17);
    gx->dirtyState |= 4;
}

void GXSetCoPlanar(GXBool enable) {
    GX_SET_REG(gx->genMode, enable, 12, 12);
    GX_BP_LOAD_REG(0xFE080000);
    GX_BP_LOAD_REG(gx->genMode);
}

void __GXSetGenMode(void) {
    GX_BP_LOAD_REG(gx->genMode);
    gx->bpSentNot = GX_FALSE;
}
