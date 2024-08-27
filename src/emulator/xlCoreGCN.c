#include "emulator/xlCoreGCN.h"
#include "dolphin.h"
#include "emulator/simGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlList.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"

#include "gTgPcTPL.inc"

static GXRenderModeObj rmodeobj;
GXTexObj g_texMap[4];
static s32 gnCountArgument;
static char** gaszArgument;
static void* DefaultFifo;
static GXFifoObj* DefaultFifoObj;
static void* gpHeap;
static void* gArenaHi;
static void* gArenaLo;
GXRenderModeObj* rmode;

const GXColor D_80135D00 = {0};

bool xlCoreReset(void) {
    OSFreeToHeap(__OSCurrHeap, gpHeap);
    OSSetArenaLo(gArenaLo);
    OSSetArenaHi(gArenaHi);
    return true;
}

static void xlCoreInitRenderMode(GXRenderModeObj* mode) {
    char* szText;
    s32 iArgument;

    if (mode != NULL) {
        rmode = mode;
        return;
    }

#if VERSION == CE_E
    rmode = &GXEurgb60Hz480IntDf;
    rmode->viXOrigin -= 0x20;
    rmode->viWidth += 0x40;
#else
    switch (VIGetTvFormat()) {
        case 0:
            rmode = &GXNtsc480IntDf;

            for (iArgument = 0; iArgument < gnCountArgument; iArgument++) {
                if (iArgument >= 0 && iArgument < gnCountArgument) {
                    szText = gaszArgument[iArgument];
                }

                if ((szText[0] == '-' || szText[0] == '/' || szText[0] == '\\') &&
                    (szText[1] == 'p' || szText[1] == 'P') && szText[2] == '1') {
                    rmode = &GXNtsc480Prog;
                    break;
                }
            }

            rmode->viXOrigin -= 0x20;
            rmode->viWidth += 0x40;
            break;
        case 1:
            rmode = &GXPal528IntDf;
            break;
        case 2:
            rmode = &GXMpal480IntDf;
            break;
#if VERSION == MQ_E
        case 5:
            rmode = &GXEurgb60Hz480IntDf;
            rmode->viXOrigin -= 0x20;
            rmode->viWidth += 0x40;
            break;
#endif
        default:
            OSPanic("xlCoreGCN.c", VERSION == MQ_E ? 189 : 182, "DEMOInit: invalid TV format\n");
            break;
    }
#endif

    GXAdjustForOverscan(rmode, &rmodeobj, 0, 0);
    rmode = &rmodeobj;
    NO_INLINE();
}

static void xlCoreInitMem(void) {
    void* arenaLo;
    void* arenaHi;
    u32 fbSize;

    gArenaLo = arenaLo = OSGetArenaLo();
    gArenaHi = arenaHi = OSGetArenaHi();

    fbSize = (((u16)(rmode->fbWidth + 0xF) & 0xFFF0) * rmode->xfbHeight * 2);
    DemoFrameBuffer1 = (void*)(((u32)arenaLo + 0x1F) & 0xFFFFFFE0);
    DemoFrameBuffer2 = (void*)(((u32)DemoFrameBuffer1 + fbSize + 0x1F) & 0xFFFFFFE0);
    DemoCurrentBuffer = DemoFrameBuffer2;
    OSSetArenaLo((void*)(((s32)DemoFrameBuffer2 + fbSize + 0x1F) & 0xFFFFFFE0));

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();

    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);

    arenaLo = (void*)(((s32)arenaLo + 0x1F) & ~0x1F);
    arenaHi = (void*)((s32)arenaHi & ~0x1F);
    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
    OSSetArenaLo(arenaHi);
}

static inline void xlCoreInitFilter(u8* pFilter, s32 size, f32 factor) {
    s32 iFilter;

    for (iFilter = 0; iFilter < size; iFilter++) {
        pFilter[iFilter] = rmode->vfilter[iFilter] * factor;
    }
}

void xlCoreInitGX(void) {
    s32 pad1;
    u8 newFilter[7];
    s32 pad2;

    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->xfbHeight);
    GXSetDispCopyYScale((f32)rmode->xfbHeight / (f32)rmode->efbHeight);

    xlCoreInitFilter(newFilter, ARRAY_COUNT(newFilter), 1.0f);

    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, newFilter);

    if (rmode->aa != 0) {
        GXSetPixelFmt(2, 0);
    } else {
        GXSetPixelFmt(0, 0);
    }

    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDispCopyGamma(0);
    NO_INLINE();
}

s32 xlCoreGetArgumentCount(void) { return gnCountArgument; }

bool xlCoreGetArgument(s32 iArgument, char** pszArgument) {
    if ((iArgument >= 0) && (iArgument < gnCountArgument)) {
        *pszArgument = *(gaszArgument + iArgument);
        return true;
    }

    return false;
}

bool xlCoreHiResolution(void) { return true; }

int main(int nCount, char** aszArgument) {
    void* pHeap;
    u32 i;
    TEXDescriptor* tdp;
    GXColor black;
    s32 nSizeHeap;
    s32 nSize;

    gnCountArgument = nCount;
    gaszArgument = aszArgument;

    __PADDisableRecalibration(true);
    OSInitAlarm();
    OSInitFastCast();

    nSizeHeap = 0;

    ARInit(NULL, 0);
    OSInit();
    DVDInit();
    VIInit();
    DEMOPadInit();
    xlCoreInitRenderMode(NULL);
    xlCoreInitMem();
    VIConfigure(rmode);
    DefaultFifo = OSAllocFromHeap(__OSCurrHeap, 0x40000);
    DefaultFifoObj = GXInit(DefaultFifo, 0x40000);
    xlCoreInitGX();
    VISetNextFrameBuffer(DemoFrameBuffer1);
    DemoCurrentBuffer = DemoFrameBuffer2;
    VIFlush();
    VIWaitForRetrace();

    if (rmode->viTVmode & 1) {
        VIWaitForRetrace();
    }

    simulatorUnpackTexPalette((TEXPalette*)gTgPcTPL);

    black = D_80135D00;
    for (i = 0; i < 2; i++) {
        tdp = TEXGet((TEXPalette*)gTgPcTPL, i);
        GXInitTexObj(&g_texMap[i], tdp->textureHeader->data, tdp->textureHeader->width, tdp->textureHeader->height,
                     tdp->textureHeader->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
    }

    GXSetDispCopyGamma(GX_GM_1_0);
    nSizeHeap = OSCheckHeap(__OSCurrHeap);

    if (nSizeHeap != -1) {
        nSize = nSizeHeap;
        if (nSize > 0x04000000) {
            nSize = 0x04000000;
        }
        pHeap = OSAllocFromHeap(__OSCurrHeap, nSize);
        gpHeap = pHeap;
    }

    if (!xlPostSetup()) {
        return false;
    }

    if (!xlHeapSetup(pHeap, nSize)) {
        return false;
    }

    if (!xlListSetup()) {
        return false;
    }

    if (!xlObjectSetup()) {
        return false;
    }

    __PADDisableRecalibration(false);
    xlMain();

    if (!xlObjectReset()) {
        return false;
    }

    if (!xlListReset()) {
        return false;
    }

    if (!xlHeapReset()) {
        return false;
    }

    if (!xlPostReset()) {
        return false;
    }

    OSPanic("xlCoreGCN.c", VERSION == CE_E ? 593 : VERSION == MQ_E ? 584 : 577, "CORE DONE!");
    return false;
}

void xlCoreBeforeRender(void) {
    if (rmode->field_rendering != 0) {
        GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f, VIGetNextField());
    } else {
        GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
    }

    GXInvalidateVtxCache();
    GXInvalidateTexAll();
    GXSetDrawSync(0);
}
