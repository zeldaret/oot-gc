#include "dolphin.h"
#include "dolphin/demo.h"
#include "dolphin/gx.h"
#include "dolphin/pad.h"
#include "dolphin/vi.h"

extern unsigned char DemoStatEnable;
static GXRenderModeObj rmodeobj;
static unsigned char DemoFirstFrame = 1;
static void* DefaultFifo = NULL;
static GXFifoObj* DefaultFifoObj = NULL;
static GXRenderModeObj* rmode;
static int allocatedFrameBufferSize;
static int GPHangWorkaround;
static unsigned long FrameCount;
static unsigned long FrameMissThreshold;
void* DemoFrameBuffer1;
void* DemoFrameBuffer2;
void* DemoCurrentBuffer;

static void __DEMOInitRenderMode(GXRenderModeObj* mode);
static void __DEMOInitMem(void);
static void __DEMOInitGX(void);
static void __DEMOInitVI(void);
static void __NoHangDoneRender(void);
void __DEMODiagnoseHang(void);

void DEMOInit(GXRenderModeObj* mode) {
    OSInit();
    DVDInit();
    VIInit();
    DEMOPadInit();
    __DEMOInitRenderMode(mode);
    __DEMOInitMem();
    VIConfigure(rmode);
    DefaultFifo = OSAllocFromHeap(__OSCurrHeap, 0x40000);
    DefaultFifoObj = GXInit(DefaultFifo, 0x40000);
    __DEMOInitGX();
    __DEMOInitVI();
}

static void __DEMOInitRenderMode(GXRenderModeObj* mode) {
    if (mode != NULL) {
        rmodeobj = *mode;
        rmode = &rmodeobj;
    } else {
        switch (VIGetTvFormat()) {
            case VI_NTSC:
                rmode = &GXNtsc480IntDf;
                break;
            case VI_PAL:
                rmode = &GXPal528IntDf;
                break;
            case VI_EURGB60:
                rmode = &GXEurgb60Hz480IntDf;
                break;
            case VI_MPAL:
                rmode = &GXMpal480IntDf;
                break;
            default:
                OSPanic("DEMOInit.c", IS_MQ ? 462 : 470, "DEMOInit: invalid TV format\n");
                break;
        }
        GXAdjustForOverscan(rmode, &rmodeobj, 0, 0x10);
        rmode = &rmodeobj;
    }
}

static void __DEMOInitMem() {
    void* arenaLo = OSGetArenaLo();
    void* arenaHi = OSGetArenaHi();
    unsigned long fbSize = ((u16)(rmode->fbWidth + 15) & 0xFFF0) * rmode->xfbHeight * 2;

#if IS_CE
    allocatedFrameBufferSize = fbSize;
#endif

    DemoFrameBuffer1 = (void*)(((u32)arenaLo + 0x1F) & 0xFFFFFFE0);
    DemoFrameBuffer2 = (void*)(((u32)DemoFrameBuffer1 + fbSize + 0x1F) & 0xFFFFFFE0);
    DemoCurrentBuffer = DemoFrameBuffer2;
    arenaLo = (void*)(((u32)DemoFrameBuffer2 + fbSize + 0x1F) & 0xFFFFFFE0);
    OSSetArenaLo(arenaLo);
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);
    arenaLo = (void*)(((u32)arenaLo + 0x1F) & 0xFFFFFFE0);
    arenaHi = (void*)((u32)arenaHi & 0xFFFFFFE0);
    OSSetCurrentHeap(OSCreateHeap((void*)(((u32)arenaLo)), arenaHi));
    OSSetArenaLo((arenaLo = arenaHi));
}

static void __DEMOInitGX() {
    u16 xfbHeight;
    f32 yScale;

    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);

    yScale = GXGetYScaleFactor(rmode->efbHeight, rmode->xfbHeight);
    xfbHeight = GXSetDispCopyYScale(yScale);

    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, xfbHeight);
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);

    if (rmode->aa != 0) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }

    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDispCopyGamma(GX_GM_1_0);
}

static void __DEMOInitVI() {
    unsigned long nin;

    VISetNextFrameBuffer(DemoFrameBuffer1);
    DemoCurrentBuffer = DemoFrameBuffer2;
    VIFlush();
    VIWaitForRetrace();
    nin = rmode->viTVmode & 1;
    if (nin != 0) {
        VIWaitForRetrace();
    }
}

void DEMOBeforeRender() {
    if (GPHangWorkaround != 0) {
        GXSetDrawSync(0xFEEB);
        GXClearGPMetric();
    }
    if (rmode->field_rendering != 0) {
        GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f, VIGetNextField());
    } else {
        GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
    }
    GXInvalidateVtxCache();
    GXInvalidateTexAll();
}

void DEMODoneRender() {
    if (GPHangWorkaround != 0) {
        __NoHangDoneRender();
        return;
    }
    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(1, 3, 1);
    GXSetColorUpdate(1);
    GXCopyDisp(DemoCurrentBuffer, 1);
    GXDrawDone();
    DEMOSwapBuffers();
}

void DEMOSwapBuffers() {
    VISetNextFrameBuffer(DemoCurrentBuffer);
    if (DemoFirstFrame != 0) {
        VISetBlack(0);
        DemoFirstFrame = 0;
    }
    VIFlush();
    VIWaitForRetrace();
    if ((u32)DemoCurrentBuffer == (u32)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
        return;
    }
    DemoCurrentBuffer = DemoFrameBuffer1;
}

GXRenderModeObj* DEMOGetRenderModeObj() { return rmode; }

// strings in .data from unused ``__NoHangRetraceCallback``
static char unused1[] = "---------WARNING : HANG AT HIGH WATERMARK----------\n";
static char unused2[] = "Halting program";

static void __NoHangDoneRender() {
    bool abort = false;

    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXSetDrawSync(0xB00B);
    FrameCount = 0;
    while ((GXReadDrawSync() != 0xB00B) && (abort == false)) {
        if (FrameCount >= FrameMissThreshold) {
            OSReport("---------WARNING : ABORTING FRAME----------\n");
            abort = true;
            __DEMODiagnoseHang();
            DEMOReInit(rmode);
            DEMOSetGPHangMetric(GX_TRUE);
        }
    }
    DEMOSwapBuffers();
}

void DEMOSetGPHangMetric(GXBool enable) {
    if (enable) {
        GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
        GXCmd1u8(GX_LOAD_BP_REG);
        GXParam1u32(0x2402C004);
        GXCmd1u8(GX_LOAD_BP_REG);
        GXParam1u32(0x23000020);
        GXCmd1u8(GX_LOAD_XF_REG);
        GXParam1u16(0x0000);
        GXParam1u16(0x1006);
        GXParam1u32(0x00084400);
    } else {
        GXCmd1u8(GX_LOAD_BP_REG);
        GXParam1u32(0x24000000);
        GXCmd1u8(GX_LOAD_BP_REG);
        GXParam1u32(0x23000000);
        GXCmd1u8(GX_LOAD_XF_REG);
        GXParam1u16(0x0000);
        GXParam1u16(0x1006);
        GXParam1u32(0x00000000);
    }
}

void __DEMODiagnoseHang(void) {
    u32 xfTop0;
    u32 xfBot0;
    u32 suRdy0;
    u32 r0Rdy0;
    u32 xfTop1;
    u32 xfBot1;
    u32 suRdy1;
    u32 r0Rdy1;
    u32 xfTopD;
    u32 xfBotD;
    u32 suRdyD;
    u32 r0RdyD;
    GXBool readIdle;
    GXBool cmdIdle;
    GXBool junk;

    GXReadXfRasMetric(&xfBot0, &xfTop0, &r0Rdy0, &suRdy0);
    GXReadXfRasMetric(&xfBot1, &xfTop1, &r0Rdy1, &suRdy1);

    xfTopD = (xfTop1 - xfTop0) == 0;
    xfBotD = (xfBot1 - xfBot0) == 0;
    suRdyD = (suRdy1 - suRdy0) > 0;
    r0RdyD = (r0Rdy1 - r0Rdy0) > 0;

    GXGetGPStatus(&junk, &junk, &readIdle, &cmdIdle, &junk);
    OSReport("GP status %d%d%d%d%d%d --> ", readIdle, cmdIdle, xfTopD, xfBotD, suRdyD, r0RdyD);

    if (xfBotD == 0 && suRdyD != 0) {
        OSReport("GP hang due to XF stall bug.\n");
    } else if (xfTopD == 0 && xfBotD != 0 && suRdyD != 0) {
        OSReport("GP hang due to unterminated primitive.\n");
    } else if (cmdIdle == 0 && xfTopD != 0 && xfBotD != 0 && suRdyD != 0) {
        OSReport("GP hang due to illegal instruction.\n");
    } else if (readIdle != 0 && cmdIdle != 0 && xfTopD != 0 && xfBotD != 0 && suRdyD != 0 && r0RdyD != 0) {
        OSReport("GP appears to be not hung (waiting for input).\n");
    } else {
        OSReport("GP is in unknown state.\n");
    }
}

void DEMOReInit(GXRenderModeObj* mode) {
#if IS_CE
    s32 pad;
#endif
    GXFifoObj tmpobj;
    void* tmpFifo;
    GXFifoObj* realFifoObj;
    void* realFifoBase;
    unsigned long realFifoSize;

    tmpFifo = OSAllocFromHeap(__OSCurrHeap, 0x10000);
    realFifoObj = GXGetCPUFifo();
    realFifoBase = GXGetFifoBase(realFifoObj);
    realFifoSize = GXGetFifoSize(realFifoObj);
    GXAbortFrame();
    GXInitFifoBase(&tmpobj, tmpFifo, 0x10000);
    GXSetCPUFifo(&tmpobj);
    GXSetGPFifo(&tmpobj);
    __DEMOInitRenderMode(mode);
    DefaultFifoObj = GXInit(realFifoBase, realFifoSize);
    __DEMOInitGX();
    VIConfigure(rmode);
    __DEMOInitVI();
    OSFreeToHeap(__OSCurrHeap, tmpFifo);
}
