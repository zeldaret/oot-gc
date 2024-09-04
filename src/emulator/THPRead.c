#include "emulator/THPRead.h"
#include "emulator/THPBuffer.h"
#include "emulator/THPPlayer.h"
#include "emulator/simGCN.h"
#include "emulator/xlCoreGCN.h"
#include "macros.h"

#define STACK_SIZE 0x1000
#define BUFFER_COUNT 10

static OSMessageQueue FreeReadBufferQueue;
static OSMessageQueue ReadedBufferQueue;
static OSMessageQueue ReadedBufferQueue2;
static void* FreeReadBufferMessage[10];
static void* ReadedBufferMessage[10];
static void* ReadedBufferMessage2[10];
static OSThread ReadThread;
static u8 ReadThreadStack[4096];
static f32 gOrthoMtx[4][4];

//! TODO: make static (data ordering issues)
// and remove suffix (there's other global variables sharing the same name)
u32 gnTickReset_thpread;
bool gbReset_thpread;
bool toggle_184;

bool gMovieErrorToggle;
bool ReadThreadCreated;

static void* Reader(void* ptr);

bool movieGXInit(void) {
    s32 i;
    GXColor GX_DEFAULT_BG = {0};
    GXColor BLACK = {0};
    GXColor WHITE = {0};
    Mtx identity_mtx = {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, -1.0}};

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

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

    GXLoadPosMtxImm(identity_mtx, GX_PNMTX0);
    GXLoadNrmMtxImm(identity_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);

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

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
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

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, BLACK);
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
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
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
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
    GXClearGPMetric();
    return true;
}

bool movieDrawImage(TEXPalette* tpl, s16 nX0, s16 nY0) {
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
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);

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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(320.0f, 0.0f, 0.0f);
    GXPosition3f32(320.0f, 240.0f, 0.0f);
    GXPosition3f32(0.0f, 240.0f, 0.0f);
    GXEnd();

    movieGXInit();
    Vert_s16[0] = nX0;
    Vert_s16[1] = nY0;
    Vert_s16[3] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[4] = nY0;
    Vert_s16[6] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[7] = nY0 + tpl->descriptorArray->textureHeader->height;
    Vert_s16[9] = nX0;
    Vert_s16[10] = nY0 + tpl->descriptorArray->textureHeader->height;
    DCStoreRange(&Vert_s16, 24);

    C_MTXOrtho(gOrthoMtx, 0.0f, 240.0f, 0.0f, 320.0f, 0.1f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, 160.0f, 120.0f, 0.0f);
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(0, 1);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

    DEMODoneRender();

    PAD_STACK();
    return true;
}

static inline void movieDrawErrorMessageImpl(MovieMessage movieMessage, TEXPalette* coverOpen, TEXPalette* wrongDisk,
                                             TEXPalette* readingDisk, TEXPalette* retryErr, TEXPalette* fatalErr,
                                             TEXPalette* noDisk) {
    switch (movieMessage) {
        case M_M_DISK_COVER_OPEN:
            movieDrawImage(coverOpen, 160 - coverOpen->descriptorArray->textureHeader->width / 2,
                           120 - coverOpen->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_WRONG_DISK:
            movieDrawImage(wrongDisk, 160 - wrongDisk->descriptorArray->textureHeader->width / 2,
                           120 - wrongDisk->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_READING_DISK:
            movieDrawImage(readingDisk, 160 - readingDisk->descriptorArray->textureHeader->width / 2,
                           120 - readingDisk->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_RETRY_ERROR:
            movieDrawImage(retryErr, 160 - retryErr->descriptorArray->textureHeader->width / 2,
                           120 - retryErr->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_FATAL_ERROR:
            movieDrawImage(fatalErr, 160 - fatalErr->descriptorArray->textureHeader->width / 2,
                           120 - fatalErr->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_NO_DISK:
            movieDrawImage(noDisk, 160 - noDisk->descriptorArray->textureHeader->width / 2,
                           120 - noDisk->descriptorArray->textureHeader->height / 2);
            break;
        case M_M_DISK_DEFAULT_ERROR:
            movieDrawImage(fatalErr, 160 - fatalErr->descriptorArray->textureHeader->width / 2,
                           120 - fatalErr->descriptorArray->textureHeader->height / 2);
            break;
        default:
            break;
    }
}

bool movieDrawErrorMessage(MovieMessage movieMessage) {
#if IS_EU
    if (gLanguage == 1) {
        movieDrawErrorMessageImpl(movieMessage, (TEXPalette*)(u8*)ggerman_coverOpen,
                                  (TEXPalette*)(u8*)ggerman_wrongDisk, (TEXPalette*)(u8*)ggerman_readingDisk,
                                  (TEXPalette*)(u8*)ggerman_retryErr, (TEXPalette*)(u8*)ggerman_fatalErr,
                                  (TEXPalette*)(u8*)ggerman_noDisk);
    } else if (gLanguage == 2) {
        movieDrawErrorMessageImpl(movieMessage, (TEXPalette*)(u8*)gfrench_coverOpen,
                                  (TEXPalette*)(u8*)gfrench_wrongDisk, (TEXPalette*)(u8*)gfrench_readingDisk,
                                  (TEXPalette*)(u8*)gfrench_retryErr, (TEXPalette*)(u8*)gfrench_fatalErr,
                                  (TEXPalette*)(u8*)gfrench_noDisk);
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        movieDrawErrorMessageImpl(movieMessage, (TEXPalette*)(u8*)gspanish_coverOpen,
                                  (TEXPalette*)(u8*)gspanish_wrongDisk, (TEXPalette*)(u8*)gspanish_readingDisk,
                                  (TEXPalette*)(u8*)gspanish_retryErr, (TEXPalette*)(u8*)gspanish_fatalErr,
                                  (TEXPalette*)(u8*)gspanish_noDisk);
    } else if (gLanguage == 4) {
        movieDrawErrorMessageImpl(movieMessage, (TEXPalette*)(u8*)gitalian_coverOpen,
                                  (TEXPalette*)(u8*)gitalian_wrongDisk, (TEXPalette*)(u8*)gitalian_readingDisk,
                                  (TEXPalette*)(u8*)gitalian_retryErr, (TEXPalette*)(u8*)gitalian_fatalErr,
                                  (TEXPalette*)(u8*)gitalian_noDisk);
#endif

    } else
#endif
    {
        movieDrawErrorMessageImpl(movieMessage, (TEXPalette*)(u8*)gcoverOpen, (TEXPalette*)(u8*)gwrongDisk,
                                  (TEXPalette*)(u8*)greadingDisk, (TEXPalette*)(u8*)gretryErr,
                                  (TEXPalette*)(u8*)gfatalErr, (TEXPalette*)(u8*)gnoDisk);
    }

    NO_INLINE();
    return true;
}

bool movieDVDShowError(s32 nStatus, void* anData, s32 nSizeRead, u32 nOffset) {
    MovieMessage nMessage;

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
        gMovieErrorToggle = true;
        toggle_184 = true;
    } else if (toggle_184 == true) {
        toggle_184 = false;
        nMessage = M_M_DISK_READING_DISK;
    }

    if (nStatus == 5) {
        movieTestReset(true, true);
    } else if (nStatus != -1) {
        movieTestReset(true, false);
    }

    if (nMessage != M_M_NONE) {
        movieDrawErrorMessage(nMessage);
    }

    return 1;
}

bool movieDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset) {
    s32 nStatus;
    bool bRetry;

    do {
        bRetry = false;
        DVDReadAsync(pFileInfo, anData, nSizeRead, nOffset, NULL);
        while ((nStatus = DVDGetCommandBlockStatus(&pFileInfo->cb)) != 0) {
            movieDVDShowError(nStatus, anData, nSizeRead, nOffset);
            if ((nStatus == 11) || (nStatus == -1)) {
                DVDCancel(&pFileInfo->cb);
                bRetry = true;
                break;
            }
        }
    } while (bRetry);

    gMovieErrorToggle = false;
    return true;
}

bool movieTestReset(bool IPL, bool forceMenu) {
    s32 nTick;
    u32 bFlag;

    nTick = OSGetTick();
    DEMOPadRead();
    bFlag = OSGetResetButtonState();

    if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
        gnTickReset_thpread = nTick;
        if (!gbReset_thpread || bFlag) {
            gbReset_thpread = bFlag;
            return 1;
        }
        movieReset(IPL, forceMenu);
    } else if (nTick - gnTickReset_thpread >= OSSecondsToTicks(0.5f)) {
        movieReset(IPL, forceMenu);
    }

    PAD_STACK();
    return true;
}

void movieReset(bool IPL, bool forceMenu) {
    VISetBlack(true);
    VIFlush();
    VIWaitForRetrace();
    PADRecalibrate(0xF0000000);
    GXAbortFrame();
    LCDisable();
    VIWaitForRetrace();
    if (IPL == true) {
        if (forceMenu == true) {
            OSResetSystem(OS_RESET_HOTRESET, 0, true);
        } else {
            OSResetSystem(OS_RESET_HOTRESET, 0, false);
        }
    } else {
        OSResetSystem(OS_RESET_RESTART, 0, false);
    }
}

bool CreateReadThread(OSPriority priority) {
    if (OSCreateThread(&ReadThread, Reader, NULL, ReadThreadStack + STACK_SIZE, STACK_SIZE, priority, 1) == false) {
        OSReport("Can't create read thread\n");
        return false;
    }

    OSInitMessageQueue(&FreeReadBufferQueue, FreeReadBufferMessage, BUFFER_COUNT);
    OSInitMessageQueue(&ReadedBufferQueue, ReadedBufferMessage, BUFFER_COUNT);
    OSInitMessageQueue(&ReadedBufferQueue2, ReadedBufferMessage2, BUFFER_COUNT);
    ReadThreadCreated = true;

    return true;
}

void ReadThreadStart(void) {
    if (ReadThreadCreated) {
        OSResumeThread(&ReadThread);
    }
}

static void* Reader(void* ptr) {
    THPReadBuffer* readBuffer;
    s32 offset;
    s32 size;
    s32 readFrame;
    s32 frameNumber;

    readFrame = 0;
    offset = ActivePlayer.initOffset;
    size = ActivePlayer.initReadSize;

    while (true) {
        readBuffer = PopFreeReadBuffer();
        // TODO: fake match
        movieDVDRead(&ActivePlayer.fileInfo, readBuffer->ptr, size, (s64)offset);
        readBuffer->frameNumber = readFrame;
        PushReadedBuffer(readBuffer);
        offset += size;
        size = *(s32*)readBuffer->ptr;

        frameNumber = (readFrame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
        if (frameNumber == ActivePlayer.header.numFrames - 1) {
            if ((ActivePlayer.playFlag & 1)) {
                offset = ActivePlayer.header.movieDataOffsets;
            } else {
                OSSuspendThread(&ReadThread);
            }
        }

        readFrame++;
    }
    return NULL;
}

void* PopReadedBuffer(void) {
    OSMessage msg;
    OSReceiveMessage(&ReadedBufferQueue, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

inline void PushReadedBuffer(void* buffer) { OSSendMessage(&ReadedBufferQueue, buffer, OS_MESSAGE_BLOCK); }

inline void* PopFreeReadBuffer(void) {
    OSMessage msg;
    OSReceiveMessage(&FreeReadBufferQueue, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

void PushFreeReadBuffer(void* buffer) { OSSendMessage(&FreeReadBufferQueue, buffer, OS_MESSAGE_BLOCK); }

void* PopReadedBuffer2(void) {
    OSMessage msg;
    OSReceiveMessage(&ReadedBufferQueue2, &msg, OS_MESSAGE_BLOCK);
    return msg;
}

void PushReadedBuffer2(void* buffer) { OSSendMessage(&ReadedBufferQueue2, buffer, OS_MESSAGE_BLOCK); }
