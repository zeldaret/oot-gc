#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

#include "dolphin/private/__gx.h"

#define GX_WRITE_SOME_REG5(a, b) \
    do {                         \
        GX_WRITE_U8(a);          \
        GX_WRITE_U32(b);         \
    } while (0)

void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format,
                      GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t,
                      GXBool add_prev, GXBool utc_lod, GXIndTexAlphaSel alpha_sel) {

    u32 reg = 0;

    SET_REG_FIELD(reg, 2, 0, ind_stage);
    SET_REG_FIELD(reg, 2, 2, format);
    SET_REG_FIELD(reg, 3, 4, bias_sel);
    SET_REG_FIELD(reg, 2, 7, alpha_sel);
    SET_REG_FIELD(reg, 4, 9, matrix_sel);
    SET_REG_FIELD(reg, 3, 13, wrap_s);
    SET_REG_FIELD(reg, 3, 16, wrap_t);
    SET_REG_FIELD(reg, 1, 19, utc_lod);
    SET_REG_FIELD(reg, 1, 20, add_prev);
    SET_REG_FIELD(reg, 8, 24, tev_stage + 16);
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, reg);
    __GXData->bpSentNot = GX_FALSE;
}

void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t) {
    CHECK_GXBEGIN(249, "GXSetIndTexScale");

    switch (ind_state) {
        case GX_INDTEXSTAGE0:
            SET_REG_FIELD(__GXData->IndTexScale0, 4, 0, scale_s);
            SET_REG_FIELD(__GXData->IndTexScale0, 4, 4, scale_t);
            SET_REG_FIELD(__GXData->IndTexScale0, 8, 24, 0x25);
            GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
            break;
        case GX_INDTEXSTAGE1:
            SET_REG_FIELD(__GXData->IndTexScale0, 4, 8, scale_s);
            SET_REG_FIELD(__GXData->IndTexScale0, 4, 12, scale_t);
            SET_REG_FIELD(__GXData->IndTexScale0, 8, 24, 0x25);
            GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale0);
            break;
        case GX_INDTEXSTAGE2:
            SET_REG_FIELD(__GXData->IndTexScale1, 4, 0, scale_s);
            SET_REG_FIELD(__GXData->IndTexScale1, 4, 4, scale_t);
            SET_REG_FIELD(__GXData->IndTexScale1, 8, 24, 0x26);
            GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale1);
            break;
        case GX_INDTEXSTAGE3:
            SET_REG_FIELD(__GXData->IndTexScale1, 4, 8, scale_s);
            SET_REG_FIELD(__GXData->IndTexScale1, 4, 12, scale_t);
            SET_REG_FIELD(__GXData->IndTexScale1, 8, 24, 0x26);
            GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->IndTexScale1);
            break;
        default:
            ASSERTMSGLINE(277, 0, "GXSetIndTexCoordScale: Invalid Indirect Stage Id");
            break;
    }
    __GXData->bpSentNot = 0;
}

void GXSetNumIndStages(u8 nIndStages) {
    CHECK_GXBEGIN(353, "GXSetNumIndStages");
    ASSERTMSGLINE(355, nIndStages <= 4, "GXSetNumIndStages: Exceeds max. number of indirect texture stages");
    SET_REG_FIELD(__GXData->genMode, 3, 16, nIndStages);
    __GXData->dirtyState |= 6;
}

void GXSetTevDirect(GXTevStageID stage) {
    GXSetTevIndirect(stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, false, false,
                     GX_ITBA_OFF);
}

void __GXUpdateBPMask() {
#if IS_MQ
    u32 nIndStages;
    u32 i;
    u32 tmap;
    u32 new_imask;
    u32 nStages;
    u32 new_dmask;

    new_imask = 0;
    new_dmask = 0;
    nIndStages = GET_REG_FIELD(__GXData->genMode, 3, 16);

    for (i = 0; i < nIndStages; i++) {
        switch (i) {
            case 0:
                tmap = GET_REG_FIELD(__GXData->iref, 3, 0);
                break;
            case 1:
                tmap = GET_REG_FIELD(__GXData->iref, 3, 6);
                break;
            case 2:
                tmap = GET_REG_FIELD(__GXData->iref, 3, 12);
                break;
            case 3:
                tmap = GET_REG_FIELD(__GXData->iref, 3, 18);
                break;
        }

        new_imask |= 1 << tmap;
    }

    if ((u8)__GXData->bpMask != new_imask) {
        SET_REG_FIELD(__GXData->bpMask, 8, 0, new_imask);
        GX_WRITE_SOME_REG5(0x61, __GXData->bpMask);
        __GXData->bpSentNot = GX_FALSE;
    }
#endif
}

void __GXSetIndirectMask(u32 mask) {
    SET_REG_FIELD(__GXData->bpMask, 8, ~0xFF, mask);

    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}

void __GXFlushTextureState(void) {
    GX_WRITE_SOME_REG5(GX_LOAD_BP_REG, __GXData->bpMask);
    __GXData->bpSentNot = 0;
}
