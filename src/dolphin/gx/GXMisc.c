#include "dolphin/base.h"
#include "dolphin/gx.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"

static GXDrawSyncCallback TokenCB;
static GXDrawDoneCallback DrawDoneCB;
static GXBool DrawDone;
static OSThreadQueue FinishQueue;

void GXSetMisc(GXMiscToken token, u32 val) {
    switch (token) {
        case GX_MT_NULL:
            break;

        case GX_MT_XF_FLUSH:
            gx->vNum = val;
            gx->vNumNot = !gx->vNum;
            gx->bpSentNot = GX_TRUE;

            if (gx->vNum) {
                gx->dirtyState |= GX_DIRTY_VCD;
            }
            break;

        case GX_MT_DL_SAVE_CONTEXT:
            gx->dlSaveContext = (val != 0);
            break;

#if IS_CE
        case GX_MT_ABORT_WAIT_COPYOUT:
            gx->abtWaitPECopy = (val != 0);
            break;
#endif
    }
}

void GXFlush(void) {
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    PPCSync();
}

static inline void __GXAbortWait(u32 clocks) {
    OSTime time0, time1;
    time0 = OSGetTime();

    do {
        time1 = OSGetTime();
    } while (time1 - time0 <= clocks / 4);
}

static inline void __GXAbortWaitPECopyDone(void) {
    u32 peCnt0, peCnt1;

    peCnt0 = GXReadMEMReg(0x28, 0x27);
    do {
        peCnt1 = peCnt0;
        __GXAbortWait(32);

        peCnt0 = GXReadMEMReg(0x28, 0x27);
    } while (peCnt0 != peCnt1);
}

void __GXAbort(void) {
#if IS_CE
    if (gx->abtWaitPECopy && GXGetGPFifo()) {
        __GXAbortWaitPECopyDone();
    }
#endif

    __PIRegs[0x18 / 4] = 1;
    __GXAbortWait(200);
    __PIRegs[0x18 / 4] = 0;
    __GXAbortWait(20);
}

void GXAbortFrame(void) {
    __GXAbort();
    __GXCleanGPFifo();
}

void GXSetDrawSync(u16 token) {
    u32 reg;
    bool interrupts;

    interrupts = OSDisableInterrupts();
    reg = token | 0x48000000;
    GX_BP_LOAD_REG(reg);
    GX_SET_REG(reg, token, 16, 31);
    GX_SET_REG(reg, 0x47, 0, 7);
    GX_BP_LOAD_REG(reg);

    GXFlush();
    OSRestoreInterrupts(interrupts);
    gx->bpSentNot = GX_FALSE;
}

u16 GXReadDrawSync(void) {
    u16 token = GX_GET_PE_REG(7);
    return token;
}

void GXSetDrawDone(void) {
    u32 reg;
    bool interrupts;

    interrupts = OSDisableInterrupts();
    reg = 0x45000002;
    GX_BP_LOAD_REG(reg);

    GXFlush();
    DrawDone = GX_FALSE;
    OSRestoreInterrupts(interrupts);
}

static inline void GXWaitDrawDone(void) {
    bool interrupts;
    interrupts = OSDisableInterrupts();
    while (!DrawDone) {
        OSSleepThread(&FinishQueue);
    }

    OSRestoreInterrupts(interrupts);
}

void GXDrawDone(void) {
    GXSetDrawDone();
    GXWaitDrawDone();
}

void GXPixModeSync(void) {
    GX_BP_LOAD_REG(gx->peCtrl);
    gx->bpSentNot = GX_FALSE;
}

void GXPokeAlphaMode(GXCompare func, u8 threshold) { GX_SET_PE_REG(3, func << 8 | threshold); }

void GXPokeAlphaRead(GXAlphaReadMode mode) {
    u32 reg = 0;
    GX_SET_REG(reg, mode, 30, 31);
    GX_SET_REG(reg, 1, 29, 29);
    GX_SET_PE_REG(4, reg);
}

void GXPokeAlphaUpdate(GXBool doUpdate) {
    u32 reg;
    reg = GX_GET_PE_REG(1);
    GX_SET_REG(reg, doUpdate, 27, 27);
    GX_SET_PE_REG(1, reg);
}

void GXPokeBlendMode(GXBlendMode mode, GXBlendFactor srcFactor, GXBlendFactor destFactor, GXLogicOp op) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    GX_SET_REG(reg, (mode == GX_BM_BLEND) || (mode == GX_BM_SUBTRACT), 31, 31);
    GX_SET_REG(reg, (mode == GX_BM_SUBTRACT), 20, 20);
    GX_SET_REG(reg, (mode == GX_BM_LOGIC), 30, 30);
    GX_SET_REG(reg, op, 16, 19);
    GX_SET_REG(reg, srcFactor, 21, 23);
    GX_SET_REG(reg, destFactor, 24, 26);
    GX_SET_REG(reg, 0x41, 0, 7);
    GX_SET_PE_REG(1, reg);
}

void GXPokeColorUpdate(GXBool doUpdate) {
    u32 reg;
    reg = GX_GET_PE_REG(1);
    GX_SET_REG(reg, doUpdate, 28, 28);
    GX_SET_PE_REG(1, reg);
}

void GXPokeDstAlpha(GXBool doEnable, u8 alpha) {
    u32 reg;
    reg = 0;
    GX_SET_REG(reg, alpha, 24, 31);
    GX_SET_REG(reg, doEnable, 23, 23);
    GX_SET_PE_REG(2, reg);
}

void GXPokeDither(GXBool doDither) {
    u32 reg;
    reg = GX_GET_PE_REG(1);
    GX_SET_REG(reg, doDither, 29, 29);
    GX_SET_PE_REG(1, reg);
}

void GXPokeZMode(GXBool doCompare, GXCompare func, GXBool doUpdate) {
    u32 reg;
    reg = 0;
    GX_SET_REG(reg, doCompare, 31, 31);
    GX_SET_REG(reg, func, 28, 30);
    GX_SET_REG(reg, doUpdate, 27, 27);
    GX_SET_PE_REG(0, reg);
}

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback) {
    GXDrawSyncCallback prevCB;
    bool interrupts;

    prevCB = TokenCB;
    interrupts = OSDisableInterrupts();
    TokenCB = callback;
    OSRestoreInterrupts(interrupts);
    return prevCB;
}

static void GXTokenInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    u16 token;
    OSContext exceptContext;
    u32 reg;

    token = GX_GET_PE_REG(7);

    if (TokenCB) {
        OSClearContext(&exceptContext);
        OSSetCurrentContext(&exceptContext);
        TokenCB(token);
        OSClearContext(&exceptContext);
        OSSetCurrentContext(context);
    }

    reg = GX_GET_PE_REG(5);
    GX_SET_REG(reg, 1, 29, 29);
    GX_SET_PE_REG(5, reg);
}

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback) {
    GXDrawDoneCallback prevCB;
    bool interrupts;

    prevCB = DrawDoneCB;
    interrupts = OSDisableInterrupts();
    DrawDoneCB = callback;
    OSRestoreInterrupts(interrupts);
    return prevCB;
}

static void GXFinishInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptContext;
    u32 reg;

    reg = GX_GET_PE_REG(5);
    GX_SET_REG(reg, 1, 28, 28);
    GX_SET_PE_REG(5, reg);

    DrawDone = GX_TRUE;

    if (DrawDoneCB) {
        OSClearContext(&exceptContext);
        OSSetCurrentContext(&exceptContext);
        DrawDoneCB();
        OSClearContext(&exceptContext);
        OSSetCurrentContext(context);
    }

    OSWakeupThread(&FinishQueue);
}

void __GXPEInit(void) {
    u32 reg;

    __OSSetInterruptHandler(__OS_INTERRUPT_PI_PE_TOKEN, GXTokenInterruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_PI_PE_FINISH, GXFinishInterruptHandler);

    OSInitThreadQueue(&FinishQueue);

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_PE_TOKEN);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_PE_FINISH);

    reg = GX_GET_PE_REG(5);
    GX_SET_REG(reg, 1, 29, 29);
    GX_SET_REG(reg, 1, 28, 28);
    GX_SET_REG(reg, 1, 31, 31);
    GX_SET_REG(reg, 1, 30, 30);
    GX_SET_PE_REG(5, reg);
}
