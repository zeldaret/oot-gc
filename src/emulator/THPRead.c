#include "emulator/THPRead.h"
#include "emulator/THPRead_jumptables.h"
#include "macros.h"

#define STACK_SIZE 0x1000
#define BUFFER_COUNT 10

const f32 D_800D3130[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3160[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

const f32 D_800D3190[12] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0};

char D_800EA4B0[] = "Can't create read thread\n";

#ifndef NON_MATCHING
void* jtbl_800EA4CC[] = {
    &lbl_80011F4C, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F54, &lbl_80011F5C,
    &lbl_80011F64, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F70, &lbl_80011F6C,
};

void* jtbl_800EA500[] = {
    &lbl_8001219C, &lbl_800121D4, &lbl_8001220C, &lbl_8001227C, &lbl_80012244, &lbl_800122B4, &lbl_800122EC,
};
#else
void* jtbl_800EA4CC[] = {0};
void* jtbl_800EA500[] = {0};
#endif

static OSMessageQueue FreeReadBufferQueue;
static OSMessageQueue ReadedBufferQueue;
static OSMessageQueue ReadedBufferQueue2;
static void* FreeReadBufferMessage[10];
static void* ReadedBufferMessage[10];
static void* ReadedBufferMessage2[10];
static OSThread ReadThread;
static u8 ReadThreadStack[4096];
f32 gOrthoMtx[4][4];

//! TODO: make static (data ordering issues)
// and remove prefix (there's other global variables sharing the same name)
u32 gnTickReset_thpread;
s32 gbReset_thpread;
s32 toggle_184;

s32 gMovieErrorToggle;
s32 ReadThreadCreated;

const s32 D_80135DA0 = 0x00000000;
const s32 D_80135DA4 = 0x00000000;
const s32 D_80135DA8 = 0x00000000;
const f32 D_80135DAC = 0.5;
const f64 D_80135DB0 = 4503599627370496.0;
const f32 D_80135DB8 = 0.0;
const f32 D_80135DBC = 240.0;
const f32 D_80135DC0 = 320.0;
const f32 D_80135DC4 = 0.10000000149011612;
const f32 D_80135DC8 = 10000.0;
const f32 D_80135DCC = 160.0;
const f32 D_80135DD0 = 120.0;
const f32 D_80135DD4 = 1.0;

extern s16 Vert_s16[12];
extern u32 Colors_u32[3];
extern u8 TexCoords_u8[8];

static void* Reader();

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieGXInit.s")
#else
s32 movieGXInit(void) {
    s32 i;
    GXColor GX_DEFAULT_BG = {0};
    GXColor BLACK = {0};
    GXColor WHITE = {0};
    Mtx identity_mtx = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, -1.0}};

    // possible bug? GX_TG_MTX3x4 vs GX_TG_MTX2x4 (see identity_mtx)
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, 0x3C, GX_FALSE, 0x7D);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);

    GXEnableTexOffsets(GX_TEXCOORD0, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_DISABLE, GX_DISABLE);

    GXLoadPosMtxImm(identity_mtx, 0);
    GXLoadNrmMtxImm(identity_mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, 0);

    GXSetCoPlanar(GX_DISABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissorBoxOffset(0, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, BLACK);
    GXSetChanMatColor(GX_COLOR0A0, WHITE);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, BLACK);
    GXSetChanMatColor(GX_COLOR1A1, WHITE);
    GXInvalidateTexAll();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = 0; i < 0x10; i++) {
        GXSetTevKColorSel(i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel(i, GX_TEV_KASEL_1);
        GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect(i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.10000000149011612f, 1.0f, BLACK);
    GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetZCompLoc(GX_ENABLE);
    GXSetDither(GX_ENABLE);
    GXSetDstAlpha(GX_DISABLE, 0);
    GXSetPixelFmt(GX_DISABLE, GX_ZC_LINEAR);
    GXSetFieldMask(GX_ENABLE, GX_ENABLE);

    GXSetCopyClear(GX_DEFAULT_BG, 0xFFFFFF);
    GXSetCopyClamp(3); // missing enum?
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();
    GXPokeColorUpdate(GX_ENABLE);
    GXPokeAlphaUpdate(GX_ENABLE);
    GXPokeDither(GX_DISABLE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_DISABLE, 0);
    GXPokeZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF0_TRIANGLES_7TEX);
    GXClearGPMetric();
    return 1;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDrawImage.s")
#else
s32 movieDrawImage(TEXPalettePtr tpl, s16 nX0, s16 nY0) {
    GXTexObj texObj;
    s32 pad2;
    GXColor color;
    Mtx identity_mtx = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, -1.0}};
    Mtx g2DviewMtx = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, -1.0}};
    Mtx g2;

    movieGXInit();
    xlCoreBeforeRender();
    GXSetZMode(0, 3, 0);
    GXSetZCompLoc(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);

    C_MTXOrtho(gOrthoMtx, 0.0f, 240.0f, 0.0f, 320.0f, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, 160.0f, 120.0f, 0.0f);
    PSMTXScaleApply(g2, g2, D_80135DAC, D_80135DAC, 1.0f);

    GXLoadPosMtxImm(g2, 0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, 0);

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 320.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 240.0f;
    GXWGFifo.f32 = 0.0f;

    movieGXInit();
    Vert_s16[0] = nX0;
    Vert_s16[1] = nY0;
    Vert_s16[3] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[4] = nY0;
    Vert_s16[6] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[7] = nY0 + tpl->descriptorArray->textureHeader->height;
    Vert_s16[9] = nX0;
    Vert_s16[10] = nY0 + tpl->descriptorArray->textureHeader->height;
    DCStoreRange(&Vert_s16, sizeof(Vert_s16));

    C_MTXOrtho(gOrthoMtx, 0.0f, 240.0f, 0.0f, 320.0f, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, 160.0f, 120.0f, 0.0f);
    PSMTXScaleApply(g2, g2, D_80135DAC, D_80135DAC, 1.0f);
    GXLoadPosMtxImm(g2, 0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, GX_MTX3x4);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0);
    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(0, 1);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    DEMODoneRender();

    PAD_STACK();
    return 1;
}
#endif

#ifndef NON_MATCHING
//! TODO: figure out how to make this work with simGCN's incbins
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDrawErrorMessage.s")
#else
s32 movieDrawErrorMessage(MovieMessage movieMessage) {
    switch (movieMessage) {
        case M_M_DISK_COVER_OPEN:
            movieDrawImage(&gcoverOpen, 0xA0 - ((s32)gcoverOpen->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gcoverOpen->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_WRONG_DISK:
            movieDrawImage(&gwrongDisk, 0xA0 - ((s32)gwrongDisk->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gwrongDisk->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_READING_DISK:
            movieDrawImage(&greadingDisk, 0xA0 - ((s32)greadingDisk->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)greadingDisk->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_RETRY_ERROR:
            movieDrawImage(&gretryErr, 0xA0 - ((s32)gretryErr->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gretryErr->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_FATAL_ERROR:
            movieDrawImage(&gfatalErr, 0xA0 - ((s32)gfatalErr->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gfatalErr->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_NO_DISK:
            movieDrawImage(&gnoDisk, 0xA0 - ((s32)gnoDisk->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gnoDisk->descriptorArray->textureHeader->height / 2));
            break;
        case M_M_DISK_DEFAULT_ERROR:
            movieDrawImage(&gfatalErr, 0xA0 - ((s32)gfatalErr->descriptorArray->textureHeader->width / 2),
                           0x78 - ((s32)gfatalErr->descriptorArray->textureHeader->height / 2));
            break;
    }

    return 1;
}
#endif

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieDVDShowError.s")
#else
s32 movieDVDShowError(s32 nStatus, void*, s32, u32) {
    MovieMessage nMessage;
    s32 nTick;
    u32 bFlag;

    nMessage = M_M_NONE;
    switch (nStatus) {
        case -1:
            nMessage = M_M_DISK_FATAL_ERROR;
            break;
        case 4:
            nMessage = M_M_DISK_NO_DISK;
            break;
        case 5:
            nMessage = M_M_DISK_COVER_OPEN;
            break;
        case 6:
            nMessage = M_M_DISK_WRONG_DISK;
            break;
        case 11:
            nMessage = M_M_DISK_RETRY_ERROR;
            break;
    }

    if ((nStatus != 1) && (nStatus != 0) && (nStatus != 2) && (nStatus != 3) && (nStatus != 7) && (nStatus != 8) &&
        (nStatus != 0xA)) {
        gMovieErrorToggle = 1;
        toggle_184 = 1;
    } else if (toggle_184 == 1) {
        toggle_184 = 0;
        nMessage = M_M_DISK_READING_DISK;
    }

    if (nStatus == 5) {
        nTick = OSGetTick();
        DEMOPadRead();
        bFlag = OSGetResetButtonState();
        if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
            gnTickReset_thpread = nTick;
            if ((gbReset_thpread == 0) || (bFlag != 0U)) {
                gbReset_thpread = bFlag;
            } else {
                movieReset(1, 1);
            }
        } else if ((nTick - gnTickReset_thpread) >= OSSecondsToTicks(0.5f)) {
            movieReset(1, 1);
        }
    } else if (nStatus != -1) {
        nTick = OSGetTick();
        DEMOPadRead();
        bFlag = OSGetResetButtonState();
        if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
            gnTickReset_thpread = nTick;
            if ((gbReset_thpread == 0) || (bFlag != 0U)) {
                gbReset_thpread = bFlag;
            } else {
                movieReset(1, 0);
            }
        } else if ((nTick - gnTickReset_thpread) >= OSSecondsToTicks(0.5f)) {
            movieReset(1, 0);
        }
    }

    if (nMessage != M_M_NONE) {
        movieDrawErrorMessage(nMessage);
    }

    PAD_STACK();
    return 1;
}
#endif

s32 movieDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset) {
    s32 nStatus;
    s32 bRetry;

    do {
        bRetry = 0;
        DVDReadAsync(pFileInfo, anData, nSizeRead, nOffset, NULL);
        while ((nStatus = DVDGetCommandBlockStatus(&pFileInfo->cb)) != 0) {
            movieDVDShowError(nStatus, anData, nSizeRead, nOffset);
            if ((nStatus == 11) || (nStatus == -1)) {
                DVDCancel(&pFileInfo->cb);
                bRetry = 1;
                break;
            }
        }
    } while (bRetry);

    gMovieErrorToggle = 0;
    return 1;
}

#ifndef NON_MATCHING
// matches but data doesn't
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/movieTestReset.s")
#else
s32 movieTestReset(s32 IPL, s32 forceMenu) {
    s32 nTick;
    u32 bFlag;

    nTick = OSGetTick();
    DEMOPadRead();
    bFlag = OSGetResetButtonState();

    if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
        gnTickReset_thpread = nTick;
        if ((gbReset_thpread == 0) || (bFlag != 0U)) {
            gbReset_thpread = bFlag;
            return 1;
        }
        VISetBlack(1);
        VIFlush();
        VIWaitForRetrace();
        PADRecalibrate(0xF0000000);
        GXAbortFrame();
        LCDisable();
        VIWaitForRetrace();
        if (IPL == 1) {
            if (forceMenu == 1) {
                OSResetSystem(1, 0, 1);
            } else {
                OSResetSystem(1, 0, 0);
            }
        } else {
            OSResetSystem(0, 0, 0);
        }
    } else if ((nTick - gnTickReset_thpread) >= OSSecondsToTicks(0.5f)) {
        VISetBlack(1);
        VIFlush();
        VIWaitForRetrace();
        PADRecalibrate(0xF0000000);
        GXAbortFrame();
        LCDisable();
        VIWaitForRetrace();
        if (IPL == 1) {
            if (forceMenu == 1) {
                OSResetSystem(1, 0, 1);
            } else {
                OSResetSystem(1, 0, 0);
            }
        } else {
            OSResetSystem(0, 0, 0);
        }
    }

    PAD_STACK();
    return 1;
}
#endif

void movieReset(s32 IPL, s32 forceMenu) {
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    PADRecalibrate(0xF0000000);
    GXAbortFrame();
    LCDisable();
    VIWaitForRetrace();
    if (IPL == 1) {
        if (forceMenu == 1) {
            OSResetSystem(1, 0, 1);
            return;
        }
        OSResetSystem(1, 0, 0);
        return;
    }
    OSResetSystem(0, 0, 0);
    NO_INLINE();
}

s32 CreateReadThread(OSPriority priority) {
    if (OSCreateThread(&ReadThread, Reader, NULL, ReadThreadStack + STACK_SIZE, STACK_SIZE, priority, 1) == FALSE) {
        OSReport(D_800EA4B0);
        return FALSE;
    }

    OSInitMessageQueue(&FreeReadBufferQueue, FreeReadBufferMessage, BUFFER_COUNT);
    OSInitMessageQueue(&ReadedBufferQueue, ReadedBufferMessage, BUFFER_COUNT);
    OSInitMessageQueue(&ReadedBufferQueue2, ReadedBufferMessage2, BUFFER_COUNT);
    ReadThreadCreated = TRUE;

    return TRUE;
}

void ReadThreadStart() {
    if (ReadThreadCreated != FALSE) {
        OSResumeThread(&ReadThread);
    }
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/THPRead/Reader.s")
#else
// regalloc issues
static void* Reader() {
    THPReadBuffer* readBuffer;
    s32 offset;
    s32 size;
    s32 readFrame;
    s32 bRetry;
    s32 nStatus;
    s32 frameNumber;
    u8* ptr;

    readFrame = 0;
    offset = ActivePlayer.initOffset;
    size = ActivePlayer.initReadSize;

    while (TRUE) {
        readBuffer = PopFreeReadBuffer();
        ptr = readBuffer->ptr;

        do {
            bRetry = 0;
            DVDReadAsync(&ActivePlayer.fileInfo, ptr, size, offset, NULL);
            while ((nStatus = DVDGetCommandBlockStatus(&ActivePlayer.fileInfo.cb)) != 0) {
                movieDVDShowError(nStatus, ptr, size, offset);
                if ((nStatus == 11) || (nStatus == -1)) {
                    DVDCancel(&ActivePlayer.fileInfo.cb);
                    bRetry = 1;
                    break;
                }
            }
        } while (bRetry);

        gMovieErrorToggle = 0;
        readBuffer->frameNumber = readFrame;
        PushReadedBuffer(readBuffer);
        offset += size;
        size = *(s32*)readBuffer->ptr;

        frameNumber = (readFrame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
        if (frameNumber == ActivePlayer.header.numFrames - 1) {
            if ((ActivePlayer.playFlag & 1))
                offset = ActivePlayer.header.movieDataOffsets;
            else
                OSSuspendThread(&ReadThread);
        }

        readFrame++;
    }

    PAD_STACK();
    return NULL;
}
#endif

void* PopReadedBuffer() {
    OSMessage msg;
    OSReceiveMessage(&ReadedBufferQueue, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

inline void PushReadedBuffer(void* buffer) { OSSendMessage(&ReadedBufferQueue, buffer, OS_MESSAGE_BLOCK); }

inline void* PopFreeReadBuffer() {
    OSMessage msg;
    OSReceiveMessage(&FreeReadBufferQueue, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

void PushFreeReadBuffer(void* buffer) { OSSendMessage(&FreeReadBufferQueue, buffer, OS_MESSAGE_BLOCK); }

void* PopReadedBuffer2() {
    OSMessage msg;
    OSReceiveMessage(&ReadedBufferQueue2, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

void PushReadedBuffer2(void* buffer) { OSSendMessage(&ReadedBufferQueue2, buffer, OS_MESSAGE_BLOCK); }
