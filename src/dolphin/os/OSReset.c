#include "dolphin/OSRtcPriv.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "dolphin/pad.h"
#include "dolphin/vi.h"
#include "macros.h"

extern void __OSReboot(u32 resetCode, u32 bootDol);
extern void __OSStopAudioSystem(void);

typedef struct OSResetQueue {
    OSResetFunctionInfo* first;
    OSResetFunctionInfo* last;
} OSResetQueue;

static OSResetQueue ResetFunctionQueue;

#if IS_CE
static u32 bootThisDol;
#endif

void OSRegisterResetFunction(OSResetFunctionInfo* func) {
    OSResetFunctionInfo* tmp;
    OSResetFunctionInfo* iter;

    for (iter = ResetFunctionQueue.first; iter && iter->priority <= func->priority; iter = iter->next)
        ;

    if (iter == NULL) {
        tmp = ResetFunctionQueue.last;
        if (tmp == NULL) {
            ResetFunctionQueue.first = func;
        } else {
            tmp->next = func;
        }
        func->prev = tmp;
        func->next = NULL;
        ResetFunctionQueue.last = func;
        return;
    }

    func->next = iter;
    tmp = iter->prev;
    iter->prev = func;
    func->prev = tmp;
    if (tmp == NULL) {
        ResetFunctionQueue.first = func;
        return;
    }
    tmp->next = func;
}

static inline bool __OSCallResetFunctions(u32 arg0) {
    OSResetFunctionInfo* iter;
    s32 retCode = 0;

#if IS_MQ
    for (iter = ResetFunctionQueue.first; iter != NULL; iter = iter->next)
#else
    for (iter = ResetFunctionQueue.first; iter != NULL && retCode == false; iter = iter->next)
#endif
    {
        retCode |= !iter->func(arg0);
    }
    retCode |= !__OSSyncSram();
    if (retCode) {
        return 0;
    }
    return 1;
}

ASM void Reset(register s32 resetCode) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    b lbl_8038315C
lbl_80383140:
    mfspr r8, HID0
    ori r8, r8, 8
    mtspr HID0, r8
    isync
    sync
    nop
    b lbl_80383160
lbl_8038315C:
    b lbl_8038317C
lbl_80383160:
    mftb r5, 268
lbl_80383164:
    mftb r6, 268
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt lbl_80383164
    nop
    b lbl_80383180
lbl_8038317C:
    b lbl_8038319C
lbl_80383180:
    lis r8, 0xCC003000@h
    ori r8, r8, 0xCC003000@l
    li r4, 3
    stw r4, 0x24(r8)
    stw r3, 0x24(r8)
    nop
    b lbl_803831A0
lbl_8038319C:
    b lbl_803831A8
lbl_803831A0:
    nop
    b lbl_803831A0
lbl_803831A8:
    b lbl_80383140
#endif // clang-format on
}

OSThreadQueue __OSActiveThreadQueue AT_ADDRESS(OS_BASE_CACHED | 0x00DC);

inline void KillThreads(void) {
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->linkActive.next;
        switch (thread->state) {
            case 1:
            case 4:
                OSCancelThread(thread);
                break;
            default:
                break;
        }
    }
}

void __OSDoHotReset(s32 arg0) {
    OSDisableInterrupts();
    __VIRegs[1] = 0;
    ICFlashInvalidate();
    Reset(arg0 * 8);
}

void OSResetSystem(int reset, u32 resetCode, bool forceMenu) {
    bool rc;
    bool disableRecalibration;
    u32 unk[3];
    OSDisableScheduler();
    __OSStopAudioSystem();

#if IS_MQ
    if (reset == OS_RESET_SHUTDOWN)
#else
    if (reset == OS_RESET_SHUTDOWN || (reset == OS_RESET_RESTART && bootThisDol != 0))
#endif
    {
        disableRecalibration = __PADDisableRecalibration(true);
    }

    while (!__OSCallResetFunctions(false))
        ;

    if (reset == OS_RESET_HOTRESET && forceMenu) {
        OSSram* sram;

        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(true);

        while (!__OSSyncSram())
            ;
    }

    OSDisableInterrupts();
    __OSCallResetFunctions(true);
    LCDisable();

    if (reset == OS_RESET_HOTRESET) {
        __OSDoHotReset(resetCode);
    } else if (reset == OS_RESET_RESTART) {
#if IS_CE
        if ((*(u32*)OSPhysicalToCached(0x30EC) = bootThisDol) != 0) {
            __PADDisableRecalibration(disableRecalibration);
        }
#endif
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }
    KillThreads();
    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
    memset(OSPhysicalToCached(0x30E2), 0, 1);

    __PADDisableRecalibration(disableRecalibration);
}

u32 OSGetResetCode(void) {
    if (*(u8*)OSPhysicalToCached(0x30E2) != 0) {
        return 0x80000000;
    }

    return ((__PIRegs[PI_RESETCODE] & ~7) >> 3);
}
