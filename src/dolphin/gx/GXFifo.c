#include "dolphin/base.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"

static GXFifoObj* CPUFifo;
static GXFifoObj* GPFifo;
static OSThread* __GXCurrentThread;
static u8 CPGPLinked;
static bool GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32 __GXOverflowCount;

static inline void GXOverflowHandler(void) {
    __GXOverflowCount += 1;
    __GXWriteFifoIntEnable(0, 1);
    __GXWriteFifoIntReset(1, 0);
    GXOverflowSuspendInProgress = true;
    OSSuspendThread(__GXCurrentThread);
}

static inline void GXUnderflowHandler(void) {
    OSResumeThread(__GXCurrentThread);
    GXOverflowSuspendInProgress = false;
    __GXWriteFifoIntReset(1, 1);
    __GXWriteFifoIntEnable(1, 0);
}

static inline void GXBreakPointHandler(OSContext* context) {
    OSContext bpContext;
    GX_SET_REG(gx->cpEnable, 0, 26, 26);
    GX_SET_CP_REG(1, gx->cpEnable);

    if (BreakPointCB) {
        OSClearContext(&bpContext);
        OSSetCurrentContext(&bpContext);
        BreakPointCB();
        OSClearContext(&bpContext);
        OSSetCurrentContext(context);
    }
}

void GXCPInterruptHandler(s16 p1, OSContext* context) {

    gx->cpStatus = GX_GET_CP_REG(0);

    if ((gx->cpEnable >> 3 & 1) && (gx->cpStatus >> 1 & 1)) {
        GXUnderflowHandler();
    }

    if ((gx->cpEnable >> 2 & 1) && (gx->cpStatus >> 0 & 1)) {
        GXOverflowHandler();
    }

    if ((gx->cpEnable >> 5 & 1) && (gx->cpStatus >> 4 & 1)) {
        GXBreakPointHandler(context);
    }
}

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size) {
    GXFifoObjPriv* pFifo = (GXFifoObjPriv*)fifo;
    pFifo->base = base;
    pFifo->end = (void*)((u32)base + size - 4);
    pFifo->size = size;
    pFifo->rwDistance = 0;
    GXInitFifoLimits(fifo, size - 0x4000, OSRoundDown32B(size / 2));
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr) {
    GXFifoObjPriv* pFifo = (GXFifoObjPriv*)fifo;
    int interrupts = OSDisableInterrupts();
    pFifo->readPtr = readPtr;
    pFifo->writePtr = writePtr;
    pFifo->rwDistance = (u32)writePtr - (u32)readPtr;
    if (pFifo->rwDistance < 0) {
        pFifo->rwDistance += pFifo->size;
    }
    OSRestoreInterrupts(interrupts);
}

void GXInitFifoLimits(GXFifoObj* fifo, u32 highWatermark, u32 lowWatermark) {
    GXFifoObjPriv* pFifo = (GXFifoObjPriv*)fifo;
    pFifo->highWatermark = highWatermark;
    pFifo->lowWatermark = lowWatermark;
}

void GXSetCPUFifo(GXFifoObj* fifo) {
    bool interrupts;
    interrupts = OSDisableInterrupts();

    CPUFifo = fifo;

    if (fifo == GPFifo) {
        u32 reg;
        GX_SET_PI_REG(3, (u32)((GXFifoObjPriv*)fifo)->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)((GXFifoObjPriv*)fifo)->end & 0x3FFFFFFF);
        reg = 0;

#if IS_MQ
        SET_REG_FIELD(reg, 21, 5, ((u32)((GXFifoObjPriv*)fifo)->writePtr & 0x3FFFFFFF) >> 5);
#else
        GX_SET_REG(reg, (u32)((GXFifoObjPriv*)fifo)->writePtr >> 5, 6, 26);
#endif

        GX_SET_REG(reg, 0, 5, 5);
        GX_SET_PI_REG(5, reg);

        CPGPLinked = GX_TRUE;

        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        u32 reg;
        if (CPGPLinked) {
            __GXFifoLink(0);
            CPGPLinked = GX_FALSE;
        }
        __GXWriteFifoIntEnable(0, 0);

        GX_SET_PI_REG(3, (u32)((GXFifoObjPriv*)fifo)->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)((GXFifoObjPriv*)fifo)->end & 0x3FFFFFFF);
        reg = 0;

#if IS_MQ
        SET_REG_FIELD(reg, 21, 5, ((u32)((GXFifoObjPriv*)fifo)->writePtr & 0x3FFFFFFF) >> 5);
#else
        GX_SET_REG(reg, (u32)((GXFifoObjPriv*)fifo)->writePtr >> 5, 6, 26);
#endif

        GX_SET_REG(reg, 0, 5, 5);
        GX_SET_PI_REG(5, reg);
    }

    PPCSync();

    OSRestoreInterrupts(interrupts);
}

void GXSetGPFifo(GXFifoObj* fifo) {
    GXFifoObjPriv* pFifo = (GXFifoObjPriv*)fifo;
    int interrupts = OSDisableInterrupts();
    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;
    GX_SET_CP_REG(16, (u16)pFifo->base);
    GX_SET_CP_REG(18, (u16)pFifo->end);
    GX_SET_CP_REG(24, (u16)pFifo->rwDistance);
    GX_SET_CP_REG(26, (u16)pFifo->writePtr);
    GX_SET_CP_REG(28, (u16)pFifo->readPtr);
    GX_SET_CP_REG(20, (u16)pFifo->highWatermark);
    GX_SET_CP_REG(22, (u16)pFifo->lowWatermark);

    GX_SET_CP_REG(17, ((u32)pFifo->base & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(19, ((u32)pFifo->end & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(25, (pFifo->rwDistance) >> 16);
    GX_SET_CP_REG(27, ((u32)pFifo->writePtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(29, ((u32)pFifo->readPtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(21, (pFifo->highWatermark) >> 16);
    GX_SET_CP_REG(23, (pFifo->lowWatermark) >> 16);

    PPCSync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = 1;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        CPGPLinked = 0;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(interrupts);
}

void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt) {
    gx->cpStatus = GX_GET_CP_REG(0);
    *overhi = gx->cpStatus & 1;
    *underlow = (gx->cpStatus >> 1) & 1;
    *readIdle = (gx->cpStatus >> 2) & 1;
    *cmdIdle = (gx->cpStatus >> 3) & 1;
    *brkpt = (gx->cpStatus >> 4) & 1;
}

void* GXGetFifoBase(const GXFifoObj* obj) {
    GXFifoObjPriv* realFifo = (GXFifoObjPriv*)obj;
    return realFifo->base;
}

u32 GXGetFifoSize(const GXFifoObj* obj) {
    GXFifoObjPriv* realFifo = (GXFifoObjPriv*)obj;
    return realFifo->size;
}

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb) {
    GXBreakPtCallback oldCallback = BreakPointCB;
    int interrupts = OSDisableInterrupts();
    BreakPointCB = cb;
    OSRestoreInterrupts(interrupts);
    return oldCallback;
}

void __GXFifoInit(void) {
    __OSSetInterruptHandler(0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = 0;
    CPUFifo = NULL;
    GPFifo = NULL;
}

void __GXFifoReadEnable(void) {
    GX_SET_REG(gx->cpEnable, GX_TRUE, 31, 31);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXFifoReadDisable(void) {
    GX_SET_REG(gx->cpEnable, GX_FALSE, 31, 31);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXFifoLink(u8 link) {
    u32 b;
    if (link) {
        b = 1;
    } else {
        b = 0;
    }
    GX_SET_REG(gx->cpEnable, b, 27, 27);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXWriteFifoIntEnable(u32 p1, u32 p2) {
#if IS_MQ
    SET_REG_FIELD(gx->cpEnable, 1, 2, (u8)p1);
    SET_REG_FIELD(gx->cpEnable, 1, 3, (u8)p2);
#else
    GX_SET_REG(gx->cpEnable, p1, 29, 29);
    GX_SET_REG(gx->cpEnable, (u8)p2, 28, 28);
#endif

    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXWriteFifoIntReset(u32 p1, u32 p2) {
#if IS_MQ
    SET_REG_FIELD(gx->cpClr, 1, 0, (u8)p1);
    SET_REG_FIELD(gx->cpClr, 1, 1, (u8)p2);
#else
    GX_SET_REG(gx->cpClr, p1, 31, 31);
    GX_SET_REG(gx->cpClr, (u8)p2, 30, 30);
#endif

    GX_SET_CP_REG(2, gx->cpClr);
}

void __GXCleanGPFifo(void) {
    bool interrupts;
    GXFifoObjPriv tempObj;
    u32 i;
    u32 j;
    u32 k;
    GXFifoObjPriv* gpFifo;
    GXFifoObjPriv* cpuFifo;
    void* tempPtr;

    gpFifo = (GXFifoObjPriv*)GXGetGPFifo();
    if (!gpFifo) {
        return;
    }

    cpuFifo = (GXFifoObjPriv*)GXGetCPUFifo();
    tempPtr = gpFifo->base;

    tempObj = *gpFifo;

    interrupts = OSDisableInterrupts();

    tempObj.readPtr = tempPtr;
    tempObj.writePtr = tempPtr;
    tempObj.rwDistance = 0;
    if (tempObj.rwDistance < 0) {
        tempObj.rwDistance += tempObj.size;
    }

    OSRestoreInterrupts(interrupts);

    GXSetGPFifo((GXFifoObj*)&tempObj);

    if (cpuFifo == gpFifo) {
        GXSetCPUFifo((GXFifoObj*)&tempObj);
    }

    interrupts = OSDisableInterrupts();

    gpFifo->readPtr = tempPtr;
    gpFifo->writePtr = tempPtr;
    gpFifo->rwDistance = 0;

    if (gpFifo->rwDistance < 0) {
        gpFifo->rwDistance += gpFifo->size;
    }
    OSRestoreInterrupts(interrupts);

    GXSetGPFifo((GXFifoObj*)gpFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo((GXFifoObj*)cpuFifo);
    }
}

GXFifoObj* GXGetCPUFifo(void) { return CPUFifo; }

GXFifoObj* GXGetGPFifo(void) { return GPFifo; }
