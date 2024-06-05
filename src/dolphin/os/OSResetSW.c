#include "dolphin/hw_regs.h"
#include "dolphin/os.h"

static OSResetCallback ResetCallback;
static bool Down;
static bool LastState;
static OSTime HoldUp;
static OSTime HoldDown;

void __OSResetSWInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    OSResetCallback callback;

    HoldDown = __OSGetSystemTime();
    while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100) && !(__PIRegs[0] & 0x00010000)) {
        ;
    }
    if (!(__PIRegs[0] & 0x00010000)) {
        LastState = Down = true;
        __OSMaskInterrupts(OS_INTERRUPTMASK_PI_RSW);
        if (ResetCallback) {
            callback = ResetCallback;
            ResetCallback = NULL;
            callback();
        }
    }
    __PIRegs[0] = 2;
}

#if IS_MQ
#define GAME_CHOICE_MASK 0x3F
#else
#define GAME_CHOICE_MASK 0x1F
#endif

bool OSGetResetButtonState(void) {
    bool enabled;
    bool state;
    u32 reg;
    OSTime now;

    enabled = OSDisableInterrupts();

    now = __OSGetSystemTime();

    reg = __PIRegs[0];
    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = true;
            state = HoldUp ? true : false;
            HoldDown = now;
        } else {
            state = (HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown)) ? true : false;
        }
    } else if (Down) {
        Down = false;
        state = LastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = true;
    } else {
        state = false;
        HoldUp = 0;
    }

    LastState = state;

    if (GameChoice & GAME_CHOICE_MASK) {
        OSTime fire = (GameChoice & GAME_CHOICE_MASK) * 60;
        fire = __OSStartTime + OSSecondsToTicks(fire);
        if (fire < now) {
            now -= fire;
            now = OSTicksToSeconds(now) / 2;
            if ((now & 1) == 0) {
                state = true;
            } else {
                state = false;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}
