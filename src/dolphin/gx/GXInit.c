#include "dolphin/base.h"
#include "dolphin/gx.h"
#include "dolphin/hw_regs.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "dolphin/vi.h"
#include "macros.h"

#if IS_MQ
static GXData gxData;
static GXFifoObj FifoObj;
#else
static GXFifoObj FifoObj;
static GXData gxData;
#endif

GXData* const __GXData = &gxData;

#if IS_MQ
char* __GXVersion = "<< Dolphin SDK - GX\trelease build: Sep  5 2002 05:33:28 (0x2301) >>";
#else
char* __GXVersion = "<< Dolphin SDK - GX\trelease build: Jul 23 2003 11:27:39 (0x2301) >>";
#endif

void* __piReg = NULL;
void* __cpReg = NULL;
void* __peReg = NULL;
void* __memReg = NULL;

#if IS_CE
static u16 DefaultTexData[] ATTRIBUTE_ALIGN(32) = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
#endif

static GXVtxAttrFmtList GXDefaultVATList[] = {
    {GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
    {GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
    {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
    {GX_VA_NULL, GX_COMPCNT_NULL, GX_COMP_NULL, 0},
};

static f32 GXDefaultProjData[] = {1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -2.0f, 0.0f};

#if IS_CE
static u32 GXTexRegionAddrTable[] = {
    0x00000, 0x10000, 0x20000, 0x30000, 0x40000, 0x50000, 0x60000, 0x70000, 0x08000, 0x18000, 0x28000, 0x38000,
    0x48000, 0x58000, 0x68000, 0x78000, 0x00000, 0x90000, 0x20000, 0xB0000, 0x40000, 0x98000, 0x60000, 0xB8000,
    0x80000, 0x10000, 0xA0000, 0x30000, 0x88000, 0x50000, 0xA8000, 0x70000, 0x00000, 0x90000, 0x20000, 0xB0000,
    0x40000, 0x90000, 0x60000, 0xB0000, 0x80000, 0x10000, 0xA0000, 0x30000, 0x80000, 0x50000, 0xA0000, 0x70000,
};

static bool __GXShutdown(bool);
static OSResetFunctionInfo GXResetFuncInfo = {__GXShutdown, OS_RESET_PRIO_GX};
#endif

// ``IsWriteGatherBufferEmpty`` is an handwritten function that the linker removed
#pragma peephole off

static inline void EnableWriteGatherPipe(void) {
    u32 hid2;
    hid2 = PPCMfhid2();
    PPCMtwpar(OSUncachedToPhysical((void*)GXFIFO_ADDR));
    hid2 |= 0x40000000;
    PPCMthid2(hid2);
}

static GXTexRegion* __GXDefaultTexRegionCallback(GXTexObj* obj, GXTexMapID id) {
    GXTexFmt format;
    GXBool isMipMap;

    format = GXGetTexObjFmt(obj);

#if IS_MQ
    if (format != GX_TF_C4 && format != GX_TF_C8 && format != GX_TF_C14X2) {
        return &gx->TexRegions0[gx->nextTexRgn++ & 7];
    } else {
        return &gx->TexRegionsCI[gx->nextTexRgnCI++ & 3];
    }
#else
    isMipMap = GXGetTexObjMipMap(obj);
    id = (GXTexMapID)(id % GX_MAX_TEXMAP);

    switch (format) {
        case GX_TF_RGBA8:
            if (isMipMap) {
                return &gx->TexRegions2[id];
            }
            return &gx->TexRegions1[id];
        case GX_TF_C4:
        case GX_TF_C8:
        case GX_TF_C14X2:
            return &gx->TexRegions0[id];
        default:
            if (isMipMap) {
                return &gx->TexRegions1[id];
            }
            return &gx->TexRegions0[id];
    }
#endif
}

static GXTlutRegion* __GXDefaultTlutRegionCallback(u32 tlut) {
    if (tlut >= GX_MAX_TLUT_ALL) {
        return NULL;
    }

    return &gx->TlutRegions[tlut];
}

#if IS_CE
bool __GXShutdown(bool final) {
    static u32 peCount;
    static OSTime time;
    static u32 calledOnce = 0;

    u32 val;
    u32 newPeCount;
    OSTime newTime;

    if (!final) {
        if (!calledOnce) {
            peCount = GXReadMEMReg(0x28, 0x27);
            time = OSGetTime();
            calledOnce = 1;
            return false;
        }

        newTime = OSGetTime();
        newPeCount = GXReadMEMReg(0x28, 0x27);

        if (newTime - time < 10) {
            return false;
        }

        if (newPeCount != peCount) {
            peCount = newPeCount;
            time = newTime;
            return false;
        }

    } else {
        GXSetBreakPtCallback(NULL);
        GXSetDrawSyncCallback(NULL);
        GXSetDrawDoneCallback(NULL);

        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);
        GX_WRITE_U32(0);

        PPCSync();

        GX_SET_CP_REG(1, 0);
        GX_SET_CP_REG(2, 3);

        gx->abtWaitPECopy = GX_TRUE;

        __GXAbort();
    }

    return true;
}
#endif

GXFifoObj* GXInit(void* base, u32 size) {
#if IS_CE
    static u32 resetFuncRegistered = 0;
#endif
    u32 i;
    u32 reg;
    u32 freqBase;

    OSRegisterVersion(__GXVersion);
    gx->inDispList = GX_FALSE;
    gx->dlSaveContext = GX_TRUE;

#if IS_CE
    gx->abtWaitPECopy = GX_TRUE;
#endif

    gx->tcsManEnab = 0;
    gx->tevTcEnab = 0;

    GXSetMisc(GX_MT_XF_FLUSH, 0);

    __piReg = (void*)OSPhysicalToUncached(GX_PI_ADDR);
    __cpReg = (void*)OSPhysicalToUncached(GX_CP_ADDR);
    __peReg = (void*)OSPhysicalToUncached(GX_PE_ADDR);
    __memReg = (void*)OSPhysicalToUncached(GX_MEM_ADDR);

    __GXFifoInit();

    GXInitFifoBase(&FifoObj, base, size);
    GXSetCPUFifo(&FifoObj);
    GXSetGPFifo(&FifoObj);

#if IS_CE
    if (!resetFuncRegistered) {
        OSRegisterResetFunction(&GXResetFuncInfo);
        resetFuncRegistered = 1;
    }
#endif

    __GXPEInit();
    EnableWriteGatherPipe();

    gx->genMode = 0;
    SET_REG_FIELD(gx->genMode, 8, 24, 0);

    gx->bpMask = 255;
    SET_REG_FIELD(gx->bpMask, 8, 24, 0x0F);

    gx->lpSize = 0;
    SET_REG_FIELD(gx->lpSize, 8, 24, 0x22);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        gx->tevc[i] = 0;
        gx->teva[i] = 0;
        gx->tref[i / 2] = 0;
        gx->texmapId[i] = GX_TEXMAP_NULL;

        SET_REG_FIELD(gx->tevc[i], 8, 24, 0xC0 + i * 2);
        SET_REG_FIELD(gx->teva[i], 8, 24, 0xC1 + i * 2);
        SET_REG_FIELD(gx->tevKsel[i / 2], 8, 24, 0xF6 + i / 2);
        SET_REG_FIELD(gx->tref[i / 2], 8, 24, 0x28 + i / 2);
    }

    gx->iref = 0;
    SET_REG_FIELD(gx->iref, 8, 24, 0x27);

    for (i = 0; i < GX_MAX_TEXCOORD; i++) {
        gx->suTs0[i] = 0;
        gx->suTs1[i] = 0;

        SET_REG_FIELD(gx->suTs0[i], 8, 24, 0x30 + i * 2);
        SET_REG_FIELD(gx->suTs1[i], 8, 24, 0x31 + i * 2);
    }

    SET_REG_FIELD(gx->suScis0, 8, 24, 0x20);
    SET_REG_FIELD(gx->suScis1, 8, 24, 0x21);

    SET_REG_FIELD(gx->cmode0, 8, 24, 0x41);
    SET_REG_FIELD(gx->cmode1, 8, 24, 0x42);

    SET_REG_FIELD(gx->zmode, 8, 24, 0x40);
    SET_REG_FIELD(gx->peCtrl, 8, 24, 0x43);

    SET_REG_FIELD(gx->cpTex, 2, 7, 0);

#if IS_CE
    gx->zScale = 1.6777216E7f;
    gx->zOffset = 0.0f;
#endif

    gx->dirtyState = 0;
    gx->dirtyVAT = 0;

    freqBase = OS_BUS_CLOCK / 500;

    __GXFlushTextureState();
    reg = (freqBase / 2048) | 0x400 | 0x69000000;
    GX_WRITE_RAS_REG(reg);

    __GXFlushTextureState();
    reg = (freqBase / 4224) | 0x200 | 0x46000000;
    GX_WRITE_RAS_REG(reg);

    for (i = GX_VTXFMT0; i < GX_MAX_VTXFMT; i++) {
#if IS_MQ
        s32 pad[4];
#else
        s32 pad[2];
#endif

        SET_REG_FIELD(gx->vatA[i], 1, 30, 1);
        SET_REG_FIELD(gx->vatB[i], 1, 31, 1);
        GX_WRITE_U8(8);
        GX_WRITE_U8(i | 0x80);
        GX_WRITE_U32(gx->vatB[i]);

        // TODO: Hacks to prevent loop unrolling
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
    }

    {
        u32 reg1 = 0;
        u32 reg2 = 0;

        SET_REG_FIELD(reg1, 1, 0, 1);
        SET_REG_FIELD(reg1, 1, 1, 1);
        SET_REG_FIELD(reg1, 1, 2, 1);
        SET_REG_FIELD(reg1, 1, 3, 1);
        SET_REG_FIELD(reg1, 1, 4, 1);
        SET_REG_FIELD(reg1, 1, 5, 1);

        GX_WRITE_XF_REG(0, reg1);

        SET_REG_FIELD(reg2, 1, 0, 1);

        GX_WRITE_XF_REG(0x12, reg2);
    }

    {
        u32 reg = 0;
        SET_REG_FIELD(reg, 1, 0, 1);
        SET_REG_FIELD(reg, 1, 1, 1);
        SET_REG_FIELD(reg, 1, 2, 1);
        SET_REG_FIELD(reg, 1, 3, 1);
        SET_REG_FIELD(reg, 8, 24, 0x58);

        GX_WRITE_RAS_REG(reg);
    }

#if IS_MQ
    for (i = 0; i < 8; i++) {
        GXInitTexCacheRegion(&gx->TexRegions0[i], 0, i * 0x8000, 0, 0x80000 + i * 0x8000, 0);
    }

    for (i = 0; i < 4; i++) {
        GXInitTexCacheRegion(&gx->TexRegionsCI[i], 0, (i * 2 + 8) * 0x8000, 0, (i * 2 + 9) * 0x8000, 0);
    }
#else
    for (i = 0; i < GX_MAX_TEXMAP; i++) {
        GXInitTexCacheRegion(&gx->TexRegions0[i], GX_FALSE, GXTexRegionAddrTable[i], GX_TEXCACHE_32K,
                             GXTexRegionAddrTable[i + 8], GX_TEXCACHE_32K);
        GXInitTexCacheRegion(&gx->TexRegions1[i], GX_FALSE, GXTexRegionAddrTable[i + 16], GX_TEXCACHE_32K,
                             GXTexRegionAddrTable[i + 24], GX_TEXCACHE_32K);
        GXInitTexCacheRegion(&gx->TexRegions2[i], GX_TRUE, GXTexRegionAddrTable[i + 32], GX_TEXCACHE_32K,
                             GXTexRegionAddrTable[i + 40], GX_TEXCACHE_32K);
    }
#endif

    for (i = 0; i < GX_MAX_TLUT; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i], 0xC0000 + 0x2000 * i, GX_TLUT_256);
    }

    for (i = 0; i < GX_MAX_BIGTLUT; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i + 16], 0xE0000 + 0x8000 * i, GX_TLUT_1K);
    }

    GX_SET_CP_REG(3, 0);

    GX_SET_REG(gx->perfSel, 0, 24, 27);

    GX_CP_LOAD_REG(0x20, gx->perfSel)

    GX_XF_LOAD_REG(0x1006, 0);

    GX_BP_LOAD_REG(0x23000000)
    GX_BP_LOAD_REG(0x24000000)
    GX_BP_LOAD_REG(0x67000000)

#if IS_MQ
    __GXSetTmemConfig(0);
#else
    __GXSetIndirectMask(0);
    __GXSetTmemConfig(2);
#endif

    __GXInitGX();

    return &FifoObj;
}

void __GXInitGX(void) {
    GXRenderModeObj* renderObj;

#if IS_CE
    GXTexObj texObj;
#endif

    Mtx ident;
    GXColor clearColor = {64, 64, 64, 255};
    GXColor ambColor = {0, 0, 0, 0};
    GXColor matColor = {255, 255, 255, 255};
    u32 i;

    switch (VIGetTvFormat()) {
        case VI_NTSC:
            renderObj = &GXNtsc480IntDf;
            break;

        case VI_PAL:
            renderObj = &GXPal528IntDf;
            break;

        case VI_EURGB60:
            renderObj = &GXEurgb60Hz480IntDf;
            break;

        case VI_MPAL:
            renderObj = &GXMpal480IntDf;
            break;

        default:
            renderObj = &GXNtsc480IntDf;
            break;
    }

    GXSetCopyClear(clearColor, 0xFFFFFF);

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

    for (i = GX_VA_POS; i <= GX_LIGHT_ARRAY; i++) {
        GXSetArray((GXAttr)i, gx, 0);
    }

    for (i = 0; i < GX_MAX_VTXFMT; i++) {
        GXSetVtxAttrFmtv((GXVtxFmt)i, GXDefaultVATList);
    }

    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);
    GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_FALSE, GX_FALSE);

    ident[0][0] = 1.0f;
    ident[0][1] = 0.0f;
    ident[0][2] = 0.0f;
    ident[0][3] = 0.0f;

    ident[1][0] = 0.0f;
    ident[1][1] = 1.0f;
    ident[1][2] = 0.0f;
    ident[1][3] = 0.0f;

    ident[2][0] = 0.0f;
    ident[2][1] = 0.0f;
    ident[2][2] = 1.0f;
    ident[2][3] = 0.0f;

    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXLoadNrmMtxImm(ident, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXLoadTexMtxImm(ident, GX_IDENTITY, GX_MTX3x4);
    GXLoadTexMtxImm(ident, GX_PTIDENTITY, GX_MTX3x4);

    GXSetViewport(0.0f, 0.0f, renderObj->fbWidth, renderObj->xfbHeight, 0.0f, 1.0f);

    GXSetProjectionv(GXDefaultProjData);

    GXSetCoPlanar(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);

    GXSetScissor(0, 0, renderObj->fbWidth, renderObj->efbHeight);
    GXSetScissorBoxOffset(0, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, ambColor);
    GXSetChanMatColor(GX_COLOR0A0, matColor);

    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, ambColor);
    GXSetChanMatColor(GX_COLOR1A1, matColor);

    GXInvalidateTexAll();

#if IS_MQ
    gx->nextTexRgn = 0;
    gx->nextTexRgnCI = 0;
#endif

    GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);

#if IS_CE
    GXInitTexObj(&texObj, DefaultTexData, 4, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    GXLoadTexObj(&texObj, GX_TEXMAP2);
    GXLoadTexObj(&texObj, GX_TEXMAP3);
    GXLoadTexObj(&texObj, GX_TEXMAP4);
    GXLoadTexObj(&texObj, GX_TEXMAP5);
    GXLoadTexObj(&texObj, GX_TEXMAP6);
    GXLoadTexObj(&texObj, GX_TEXMAP7);
#endif

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
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect((GXTevStageID)i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, ambColor);
    GXSetFogRangeAdj(GX_FALSE, 0, NULL);

    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);

    GXSetDither(GX_TRUE);

    GXSetDstAlpha(GX_FALSE, 0);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

    GXSetFieldMask(GX_TRUE, GX_TRUE);
    GXSetFieldMode((GXBool)renderObj->field_rendering,
                   (GXBool)((renderObj->viHeight == 2 * renderObj->xfbHeight) ? GX_TRUE : GX_FALSE));

    GXSetDispCopySrc(0, 0, renderObj->fbWidth, renderObj->efbHeight);
    GXSetDispCopyDst(renderObj->fbWidth, renderObj->efbHeight);
    GXSetDispCopyYScale((f32)renderObj->xfbHeight / (f32)renderObj->efbHeight);
    GXSetCopyClamp(GX_CLAMP_BOTH);

    GXSetCopyFilter(renderObj->aa, renderObj->sample_pattern, GX_TRUE, renderObj->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();

    GXPokeColorUpdate(GX_TRUE);
    GXPokeAlphaUpdate(GX_TRUE);
    GXPokeDither(GX_FALSE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_FALSE, 0);
    GXPokeZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
    GXClearGPMetric();
}
