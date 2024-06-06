#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"

#define GX_WRITE_SOME_REG5(a, b) \
    do {                         \
        GX_WRITE_U8(a);          \
        GX_WRITE_U32(b);         \
    } while (0)

void GXSetTevIndirect(GXTevStageID tevStage, GXIndTexStageID texStage, GXIndTexFormat texFmt, GXIndTexBiasSel biasSel,
                      GXIndTexMtxID mtxId, GXIndTexWrap wrapS, GXIndTexWrap wrapT, u8 addPrev, u8 utcLod,
                      GXIndTexAlphaSel alphaSel) {
    u32 field = 0;

#if IS_MQ
#define STAGE tevStage + 0x10
#else
    const u32 stage = tevStage + 0x10;
#define STAGE stage
#endif

    GX_SET_REG(field, texStage, GX_BP_INDTEV_STAGE_ST, GX_BP_INDTEV_STAGE_END);
    GX_SET_REG(field, texFmt, GX_BP_INDTEV_FMT_ST, GX_BP_INDTEV_FMT_END);
    GX_SET_REG(field, biasSel, GX_BP_INDTEV_BIAS_ST, GX_BP_INDTEV_BIAS_END);
    GX_SET_REG(field, alphaSel, GX_BP_INDTEV_ALPHA_ST, GX_BP_INDTEV_ALPHA_END);
    GX_SET_REG(field, mtxId, GX_BP_INDTEV_MTX_ST, GX_BP_INDTEV_MTX_END);
    GX_SET_REG(field, wrapS, GX_BP_INDTEV_WRAPS_ST, GX_BP_INDTEV_WRAPS_END);
    GX_SET_REG(field, wrapT, GX_BP_INDTEV_WRAPT_ST, GX_BP_INDTEV_WRAPT_END);
    GX_SET_REG(field, utcLod, GX_BP_INDTEV_UNMODTEXCOORD_ST, GX_BP_INDTEV_UNMODTEXCOORD_END);
    GX_SET_REG(field, addPrev, GX_BP_INDTEV_ADDPREV_ST, GX_BP_INDTEV_ADDPREV_END);
    GX_SET_REG(field, STAGE, 0, 7);

    GX_BP_LOAD_REG(field);
    gx->bpSentNot = GX_FALSE;

    NO_INLINE();
}

void GXSetIndTexCoordScale(GXIndTexStageID stage, GXIndTexScale scaleS, GXIndTexScale scaleT) {
    GXData* data;
    switch (stage) {
        case GX_INDTEXSTAGE0:
            GX_SET_REG(gx->IndTexScale0, scaleS, GX_BP_RAS1_SS0_S0_ST, GX_BP_RAS1_SS0_S0_END);
            GX_SET_REG(gx->IndTexScale0, scaleT, GX_BP_RAS1_SS0_T0_ST, GX_BP_RAS1_SS0_T0_END);
            GX_SET_REG(gx->IndTexScale0, 0x25, 0, 7);

            GX_BP_LOAD_REG(gx->IndTexScale0);
            break;

        case GX_INDTEXSTAGE1:
            GX_SET_REG(gx->IndTexScale0, scaleS, GX_BP_RAS1_SS0_S1_ST, GX_BP_RAS1_SS0_S1_END);
            GX_SET_REG(gx->IndTexScale0, scaleT, GX_BP_RAS1_SS0_T1_ST, GX_BP_RAS1_SS0_T1_END);
            GX_SET_REG(gx->IndTexScale0, 0x25, 0, 7);

            GX_BP_LOAD_REG(gx->IndTexScale0);
            break;

        case GX_INDTEXSTAGE2:
            GX_SET_REG(gx->IndTexScale1, scaleS, GX_BP_RAS1_SS1_S2_ST, GX_BP_RAS1_SS1_S2_END);
            GX_SET_REG(gx->IndTexScale1, scaleT, GX_BP_RAS1_SS1_T2_ST, GX_BP_RAS1_SS1_T2_END);
            GX_SET_REG(gx->IndTexScale1, 0x26, 0, 7);

            GX_BP_LOAD_REG(gx->IndTexScale1);
            break;

        case GX_INDTEXSTAGE3:
            GX_SET_REG(gx->IndTexScale1, scaleS, GX_BP_RAS1_SS1_S3_ST, GX_BP_RAS1_SS1_S3_END);
            GX_SET_REG(gx->IndTexScale1, scaleT, GX_BP_RAS1_SS1_T3_ST, GX_BP_RAS1_SS1_T3_END);
            GX_SET_REG(gx->IndTexScale1, 0x26, 0, 7);

            GX_BP_LOAD_REG(gx->IndTexScale1);
            break;
    }

    gx->bpSentNot = GX_FALSE;
}

void GXSetNumIndStages(u8 num) {
    GX_SET_REG(gx->genMode, num, GX_BP_GENMODE_NUMINDSTAGES_ST, GX_BP_GENMODE_NUMINDSTAGES_END);
    gx->dirtyState |= (GX_DIRTY_BP_MASK | GX_DIRTY_GEN_MODE);
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
    nIndStages = GET_REG_FIELD(gx->genMode, 3, 16);

    for (i = 0; i < nIndStages; i++) {
        switch (i) {
            case 0:
                tmap = GET_REG_FIELD(gx->iref, 3, 0);
                break;
            case 1:
                tmap = GET_REG_FIELD(gx->iref, 3, 6);
                break;
            case 2:
                tmap = GET_REG_FIELD(gx->iref, 3, 12);
                break;
            case 3:
                tmap = GET_REG_FIELD(gx->iref, 3, 18);
                break;
        }

        new_imask |= 1 << tmap;
    }

    if ((u8)gx->bpMask != new_imask) {
        SET_REG_FIELD(gx->bpMask, 8, 0, new_imask);
        GX_WRITE_SOME_REG5(0x61, gx->bpMask);
        gx->bpSentNot = GX_FALSE;
    }
#endif
}

void __GXSetIndirectMask(u32 mask) {
    GX_SET_REG(gx->bpMask, mask, GX_BP_INDIMASK_ST, GX_BP_INDIMASK_END);
    GX_BP_LOAD_REG(gx->bpMask);
    gx->bpSentNot = GX_FALSE;
}

void __GXFlushTextureState() {
    GX_BP_LOAD_REG(gx->bpMask);
    gx->bpSentNot = GX_FALSE;
}
