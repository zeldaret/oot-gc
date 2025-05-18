#include "dolphin/exi.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"

#pragma scheduling off

#if IS_MQ
static const char* __EXIVersion = "<< Dolphin SDK - EXI\trelease build: Sep  5 2002 05:33:04 (0x2301) >>";
#else
static const char* __EXIVersion = "<< Dolphin SDK - EXI\trelease build: Apr 17 2003 12:33:17 (0x2301) >>";
static u32 IDSerialPort1;
#endif

#define MAX_DEV 3
#define MAX_CHAN 3

#define REG_MAX 5
#define REG(chan, idx) (__EXIRegs[((chan) * REG_MAX) + (idx)])

#define STATE_IDLE 0
#define STATE_DMA 1
#define STATE_IMM 2
#define STATE_BUSY 3
#define STATE_SELECTED 4
#define STATE_ATTACHED 8
#define STATE_LOCKED 16

#define EXI_0CR(tstart, dma, rw, tlen) \
    ((((u32)(tstart)) << 0) | (((u32)(dma)) << 1) | (((u32)(rw)) << 2) | (((u32)(tlen)) << 4))

#define CPR_CS(x) ((1u << (x)) << 7)
#define CPR_CLK(x) ((x) << 4)

static EXIControl Ecb[MAX_CHAN];

void __OSEnableBarnacle(s32 chan, u32 dev);
u32 EXIClearInterrupts(s32 chan, int exi, int tc, int ext);
static int __EXIProbe(s32 chan);

static void SetExiInterruptMask(s32 chan, EXIControl* exi) {
    EXIControl* exi2;

    exi2 = &Ecb[2];
    switch (chan) {
        case 0:
            if ((exi->exiCallback == 0 && exi2->exiCallback == 0) || (exi->state & STATE_LOCKED)) {
                __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_2_EXI);
            } else {
                __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_2_EXI);
            }
            break;
        case 1:
            if (exi->exiCallback == 0 || (exi->state & STATE_LOCKED)) {
                __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXI);
            } else {
                __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXI);
            }
            break;
        case 2:
            if (__OSGetInterruptHandler(__OS_INTERRUPT_PI_DEBUG) == 0 || (exi->state & STATE_LOCKED)) {
                __OSMaskInterrupts(OS_INTERRUPTMASK_PI_DEBUG);
            } else {
                __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_DEBUG);
            }
            break;
    }
}

static inline void CompleteTransfer(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    u8* buf;
    u32 data;
    int i;
    int len;

    if (exi->state & STATE_BUSY) {
        if ((exi->state & STATE_IMM) && (len = exi->immLen)) {
            buf = exi->immBuf;
            data = REG(chan, 4);
            for (i = 0; i < len; i++) {
                *buf++ = (u8)((data >> ((3 - i) * 8)) & 0xFF);
            }
        }
        exi->state &= ~STATE_BUSY;
    }
}

bool EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_BUSY) || !(exi->state & STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, false, true, false);
        __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= STATE_IMM;

    if (type != EXI_READ) {
        u32 data;
        int i;

        data = 0;
        for (i = 0; i < len; i++) {
            data |= ((u8*)buf)[i] << ((3 - i) * 8);
        }
        REG(chan, 4) = data;
    }

    exi->immBuf = buf;
    exi->immLen = (type != EXI_WRITE) ? len : 0;

    REG(chan, 3) = EXI_0CR(1, 0, type, len - 1);

    OSRestoreInterrupts(enabled);

    return true;
}

bool EXIImmEx(s32 chan, void* buf, s32 len, u32 mode) {
    s32 xLen;

    while (len) {
        xLen = (len < 4) ? len : 4;
        if (!EXIImm(chan, buf, xLen, mode, NULL)) {
            return false;
        }

        if (!EXISync(chan)) {
            return false;
        }

        buf = (void*)((u8*)buf + xLen);
        len -= xLen;
    }
    return true;
}

bool EXIDma(s32 chan, void* buf, s32 len, u32 type, EXICallback callback) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_BUSY) || !(exi->state & STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback) {
        EXIClearInterrupts(chan, false, true, false);
        __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= STATE_DMA;

    REG(chan, 1) = (u32)buf & 0x3FFFFE0;
    REG(chan, 2) = (u32)len;
    REG(chan, 3) = EXI_0CR(1, 1, type, 0);

    OSRestoreInterrupts(enabled);

    return true;
}

extern u32 __OSGetDIConfig(void);

bool EXISync(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    bool rc = false;
    bool enabled;

    while (exi->state & STATE_SELECTED) {
        if (((REG(chan, 3) & 1) >> 0) == 0) {
            enabled = OSDisableInterrupts();
            if (exi->state & STATE_SELECTED) {
                CompleteTransfer(chan);

                if (__OSGetDIConfig() != 0xFF ||
#if IS_CE
                    ((OSGetConsoleType() & 0xF0000000) == OS_CONSOLE_TDEV) ||
#endif
                    exi->immLen != 4 || (REG(chan, 0) & 0x00000070) != (EXI_FREQ_1M << 4) ||
                    (REG(chan, 4) != EXI_USB_ADAPTER && REG(chan, 4) != EXI_IS_VIEWER && REG(chan, 4) != 0x04220001) ||
                    __OSDeviceCode == 0x8200) {
                    rc = true;
                }
            }

            OSRestoreInterrupts(enabled);
            break;
        }
    }
    return rc;
}

u32 EXIClearInterrupts(s32 chan, bool exi, bool tc, bool ext) {
    u32 cpr;
    u32 prev;

    prev = cpr = REG(chan, 0);
    cpr &= 0x7F5;
    if (exi) {
        cpr |= 2;
    }
    if (tc) {
        cpr |= 8;
    }
    if (ext) {
        cpr |= 0x800;
    }
    REG(chan, 0) = cpr;
    return prev;
}

EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback) {
    EXIControl* exi = &Ecb[chan];
    EXICallback prev;
    bool enabled;

    enabled = OSDisableInterrupts();
    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;

    if (chan != 2) {
        SetExiInterruptMask(chan, exi);
    } else {
        SetExiInterruptMask(0, &Ecb[0]);
    }

    OSRestoreInterrupts(enabled);
    return prev;
}

static bool __EXIProbe(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    bool rc;
    u32 cpr;
    s32 t;

    if (chan == 2) {
        return true;
    }

    rc = true;
    enabled = OSDisableInterrupts();
    cpr = REG(chan, 0);
    if (!(exi->state & STATE_ATTACHED)) {
        if (cpr & 0x00000800) {
            EXIClearInterrupts(chan, false, false, true);
            __EXIProbeStartTime[chan] = exi->idTime = 0;
        }

        if (cpr & 0x00001000) {
            t = (s32)(OSTicksToMilliseconds(OSGetTime()) / 100) + 1;
            if (__EXIProbeStartTime[chan] == 0) {
                __EXIProbeStartTime[chan] = t;
            }
            if (t - __EXIProbeStartTime[chan] < 300 / 100) {
                rc = false;
            }
        } else {
            __EXIProbeStartTime[chan] = exi->idTime = 0;
            rc = false;
        }
    } else if (!(cpr & 0x00001000) || (cpr & 0x00000800)) {
        __EXIProbeStartTime[chan] = exi->idTime = 0;
        rc = false;
    }
    OSRestoreInterrupts(enabled);

    return rc;
}

bool EXIProbe(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    bool rc;
    u32 id;

    rc = __EXIProbe(chan);
    if (rc && exi->idTime == 0) {
        rc = EXIGetID(chan, 0, &id) ? true : false;
    }
    return rc;
}

s32 EXIProbeEx(s32 chan) {
    if (EXIProbe(chan)) {
        return 1;
    } else if (__EXIProbeStartTime[chan] != 0) {
        return 0;
    } else {
        return -1;
    }
}

static inline bool __EXIAttach(s32 chan, EXICallback extCallback) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_ATTACHED) || __EXIProbe(chan) == false) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    EXIClearInterrupts(chan, true, false, false);

    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT >> (3 * chan));
    exi->state |= STATE_ATTACHED;
    OSRestoreInterrupts(enabled);

    return true;
}

bool EXIAttach(s32 chan, EXICallback extCallback) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    bool rc;

    EXIProbe(chan);

    enabled = OSDisableInterrupts();
    if (exi->idTime == 0) {
        OSRestoreInterrupts(enabled);
        return false;
    }
    rc = __EXIAttach(chan, extCallback);
    OSRestoreInterrupts(enabled);
    return rc;
}

bool EXIDetach(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_ATTACHED)) {
        OSRestoreInterrupts(enabled);
        return true;
    }
    if ((exi->state & STATE_LOCKED) && exi->dev == 0) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state &= ~STATE_ATTACHED;
    __OSMaskInterrupts((OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_0_EXI) >> (3 * chan));
    OSRestoreInterrupts(enabled);
    return true;
}

bool EXISelect(s32 chan, u32 dev, u32 freq) {
    EXIControl* exi = &Ecb[chan];
    u32 cpr;
    bool enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_SELECTED) ||
        chan != 2 && (dev == 0 && !(exi->state & STATE_ATTACHED) && !__EXIProbe(chan) || !(exi->state & STATE_LOCKED) ||
                      (exi->dev != dev))) {
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state |= STATE_SELECTED;
    cpr = REG(chan, 0);
    cpr &= 0x405;
    cpr |= CPR_CS(dev) | CPR_CLK(freq);
    REG(chan, 0) = cpr;

    if (exi->state & STATE_ATTACHED) {
        switch (chan) {
            case 0:
                __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT);
                break;
            case 1:
                __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXT);
                break;
        }
    }

    OSRestoreInterrupts(enabled);
    return true;
}

bool EXIDeselect(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    u32 cpr;
    bool enabled;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_SELECTED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }
    exi->state &= ~STATE_SELECTED;
    cpr = REG(chan, 0);
    REG(chan, 0) = cpr & 0x405;

    if (exi->state & STATE_ATTACHED) {
        switch (chan) {
            case 0:
                __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT);
                break;
            case 1:
                __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXT);
                break;
        }
    }

    OSRestoreInterrupts(enabled);

    if (chan != 2 && (cpr & CPR_CS(0))) {
        return __EXIProbe(chan) ? true : false;
    }

    return true;
}

static void EXIIntrruptHandler(__OSInterrupt interrupt, OSContext* context) {
    s32 chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_EXI) / 3;
    exi = &Ecb[chan];
    EXIClearInterrupts(chan, true, false, false);
    callback = exi->exiCallback;
    if (callback) {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void TCIntrruptHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;
    s32 chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_TC) / 3;
    exi = &Ecb[chan];
    __OSMaskInterrupts(OS_INTERRUPTMASK(interrupt));
    EXIClearInterrupts(chan, false, true, false);
    callback = exi->tcCallback;
    if (callback) {
        exi->tcCallback = 0;
        CompleteTransfer(chan);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void EXTIntrruptHandler(__OSInterrupt interrupt, OSContext* context) {
    s32 chan;
    EXIControl* exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_EXT) / 3;
    __OSMaskInterrupts((OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_0_EXI) >> (3 * chan));
    exi = &Ecb[chan];
    callback = exi->extCallback;
    exi->state &= ~STATE_ATTACHED;
    if (callback) {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        exi->extCallback = 0;
        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void EXIInit(void) {
#if IS_MQ
    OSRegisterVersion(__EXIVersion);
#else
    u32 id;

    while (((REG(0, 3) & 0x1) == 1) || ((REG(1, 3) & 0x1) == 1) || ((REG(2, 3) & 0x1) == 1)) {
        continue;
    }
#endif

    __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC | OS_INTERRUPTMASK_EXI_0_EXT |
                       OS_INTERRUPTMASK_EXI_1_EXI | OS_INTERRUPTMASK_EXI_1_TC | OS_INTERRUPTMASK_EXI_1_EXT |
                       OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC);

    REG(0, 0) = 0;
    REG(1, 0) = 0;
    REG(2, 0) = 0;

    REG(0, 0) = 0x00002000;

    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_TC, TCIntrruptHandler);

#if IS_MQ
    if ((OSGetConsoleType() & 0x10000000) != 0) {
        __EXIProbeStartTime[0] = __EXIProbeStartTime[1] = 0;
        Ecb[0].idTime = Ecb[1].idTime = 0;
        __EXIProbe(0);
        __EXIProbe(1);
    }
#else
    EXIGetID(0, 2, &IDSerialPort1);

    if (__OSInIPL) {
        __EXIProbeStartTime[0] = __EXIProbeStartTime[1] = 0;
        Ecb[0].idTime = Ecb[1].idTime = 0;
        __EXIProbe(0);
        __EXIProbe(1);
    } else if (EXIGetID(0, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(1, 0);
    } else if (EXIGetID(1, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(0, 2);
    }

    OSRegisterVersion(__EXIVersion);
#endif
}

bool EXILock(s32 chan, u32 dev, EXICallback unlockedCallback) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    int i;

    enabled = OSDisableInterrupts();
    if (exi->state & STATE_LOCKED) {
        if (unlockedCallback) {
            for (i = 0; i < exi->items; i++) {
                if (exi->queue[i].dev == dev) {
                    OSRestoreInterrupts(enabled);
                    return false;
                }
            }
            exi->queue[exi->items].callback = unlockedCallback;
            exi->queue[exi->items].dev = dev;
            exi->items++;
        }
        OSRestoreInterrupts(enabled);
        return false;
    }

    exi->state |= STATE_LOCKED;
    exi->dev = dev;
    SetExiInterruptMask(chan, exi);

    OSRestoreInterrupts(enabled);
    return true;
}

bool EXIUnlock(s32 chan) {
    EXIControl* exi = &Ecb[chan];
    bool enabled;
    EXICallback unlockedCallback;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_LOCKED)) {
        OSRestoreInterrupts(enabled);
        return false;
    }
    exi->state &= ~STATE_LOCKED;
    SetExiInterruptMask(chan, exi);

    if (0 < exi->items) {
        unlockedCallback = exi->queue[0].callback;
        if (0 < --exi->items) {
            memmove(&exi->queue[0], &exi->queue[1], sizeof(exi->queue[0]) * exi->items);
        }
        unlockedCallback(chan, 0);
    }

    OSRestoreInterrupts(enabled);
    return true;
}

u32 EXIGetState(s32 chan) {
    EXIControl* exi = &Ecb[chan];

    return (u32)exi->state;
}

static void UnlockedHandler(s32 chan, OSContext* context) {
    u32 id;

    EXIGetID(chan, 0, &id);
}

s32 EXIGetID(s32 chan, u32 dev, u32* id) {
    EXIControl* exi = &Ecb[chan];
    bool err;
    u32 cmd;
    s32 startTime;
    bool enabled;

#if IS_CE
    bool interrupt;

    if (chan == 0 && dev == 2 && IDSerialPort1) {
        *id = IDSerialPort1;
        return 1;
    }
#endif

    if (chan < 2 && dev == 0) {
        if (!__EXIProbe(chan)) {
            return 0;
        }

        if (exi->idTime == __EXIProbeStartTime[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!__EXIAttach(chan, NULL)) {
            return 0;
        }

        startTime = __EXIProbeStartTime[chan];
    }

#if IS_CE
    interrupt = OSDisableInterrupts();
#endif

    err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : NULL);
    if (!err) {
        err = !EXISelect(chan, dev, EXI_FREQ_1M);
        if (!err) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }

#if IS_CE
    OSRestoreInterrupts(interrupt);
#endif

    if (chan < 2 && dev == 0) {
        EXIDetach(chan);
        enabled = OSDisableInterrupts();
        err |= (startTime != __EXIProbeStartTime[chan]);
        if (!err) {
            exi->id = *id;
            exi->idTime = startTime;
        }
        OSRestoreInterrupts(enabled);

        return err ? 0 : exi->idTime;
    }

    return err ? 0 : !0;
}

// these are strings that belongs to ``EXIGetTypeString``
// this function was removed by the linker but the strings stayed in .data

static char unused1[] = "Memory Card 59";
static char unused2[] = "Memory Card 123";
static char unused3[] = "Memory Card 251";
static char unused4[] = "Memory Card 507";

#if IS_CE
static char unused5[] = "Memory Card 1019";
static char unused6[] = "Memory Card 2043";
#endif

static char unused7[] = "USB Adapter";
static char unused8[] = "Net Card";
static char unused9[] = "Artist Ether";

#if IS_CE
static char unused10[] = "Broadband Adapter";
#endif

static char unused11[] = "Stream Hanger";

#if IS_MQ
static char unused12[] = "IS Viewer";
#else
static char unused12[] = "IS-DOL-VIEWER";
#endif

#pragma scheduling reset
