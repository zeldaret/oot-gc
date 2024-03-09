#include "xlCoreGCN.h"
#include "macros.h"
#include "simGCN.h"

u8 gTgPcTPL[32897] = {
#pragma INCBIN("SIM_original.elf", 0x000D07A0, 0x00008081)
};

char D_800DB7A4[] = "xlCoreGCN.c";
char D_800DB7B0[] = "CORE DONE!";
char D_800DB7BC[] = "DEMOInit: invalid TV format\n";

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

const s32 D_80135D00 = 0x00000000;

__anon_0xDAF8* TEXGet(u8* pTexture, u32 i);
s32 __PADDisableRecalibration(s32 bDisable);

s32 xlCoreReset(void) {
    OSFreeToHeap(__OSCurrHeap, gpHeap);
    OSSetArenaLo(gArenaLo);
    OSSetArenaHi(gArenaHi);
    return 1;
}

static void xlCoreInitRenderMode(GXRenderModeObj* mode) {
    char* szText;
    s32 iArgument;

    if (mode != NULL) {
        rmode = mode;
        return;
    }

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
        default:
            OSPanic(D_800DB7A4, 182, D_800DB7BC);
            break;
    }

    GXAdjustForOverscan(rmode, &rmodeobj, 0, 0);
    rmode = &rmodeobj;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/xlCoreInitMem.s")
static void xlCoreInitMem(void);
#else
static void xlCoreInitMem(void) {
    void* arenaLo;
    void* arenaHi;
    u32 fbSize;

    gArenaLo = arenaLo = OSGetArenaLo();
    gArenaHi = arenaHi = OSGetArenaHi();

    fbSize = (((rmode->fbWidth + 0xF) & 0xFFF0) * rmode->xfbHeight * 2);
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
#endif

inline void xlCoreInitFilter(u8* pFilter, s32 size, f32 factor) {
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

s32 xlCoreGetArgument(s32 iArgument, char** pszArgument) {
    if ((iArgument >= 0) && (iArgument < gnCountArgument)) {
        *pszArgument = *(gaszArgument + iArgument);
        return 1;
    }

    return 0;
}

s32 xlCoreHiResolution(void) { return 1; }

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlCoreGCN/main.s")
#else
s32 main(s32 nCount, char** aszArgument) {
    // Parameters
    // s32 nCount; // r1+0x8
    // char** aszArgument; // r1+0xC

    // Local variables
    void* pHeap; // r27
    u32 i; // r26
    __anon_0xDAF8* tdp; // r1+0x8
    GXColor black; // r1+0x10
    s32 nSizeHeap; // r3
    s32 nSize; // r31
    volatile int t;

    gnCountArgument = nCount;
    gaszArgument = aszArgument;

    __PADDisableRecalibration(1);
    OSInitAlarm();

#ifdef __MWERKS__
    asm {
        li      r3, 4
        oris    r3, r3, 4
        mtspr   GQR2, r3
        li      r3, 5
        oris    r3, r3, 5
        mtspr   GQR3, r3
        li      r3, 6
        oris    r3, r3, 6
        mtspr   GQR4, r3
        li      r3, 7
        oris    r3, r3, 7
        mtspr   GQR5, r3
    }
#endif

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

    simulatorUnpackTexPalette((__anon_0xDB69*)gTgPcTPL);

    // t = D_80135D00;
    for (i = 0; i < ARRAY_COUNTU(g_texMap); i++) {
        tdp = TEXGet(gTgPcTPL, i);
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
        return 0;
    }

    if (!xlHeapSetup(pHeap, nSize)) {
        return 0;
    }

    if (!xlListSetup()) {
        return 0;
    }

    if (!xlObjectSetup()) {
        return 0;
    }

    __PADDisableRecalibration(0);
    xlMain();

    if (!xlObjectReset()) {
        return 0;
    }

    if (!xlListReset()) {
        return 0;
    }

    if (!xlHeapReset()) {
        return 0;
    }

    if (!xlPostReset()) {
        return 0;
    }

    // this is matching (just regalloc), idk why it's broken on decompme
    OSPanic("xlCoreGCN.c", 577, "CORE DONE!");
    return 0;
}
#endif

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
