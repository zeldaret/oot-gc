#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "macros.h"

#include "dolphin/private/__os.h"

#define TRUNC(n, a) (((u32)(n)) & ~((a) - 1))
#define ROUND(n, a) (((u32)(n) + (a) - 1) & ~((a) - 1))

extern OSErrorHandler __OSErrorTable[OS_ERROR_MAX];

static bool OnReset(bool final);

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    127,
    NULL,
    NULL,
};

static bool OnReset(bool final) {
    if (final != false) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return true;
}

inline u32 OSGetPhysicalMemSize(void) { return *(u32*)(OSPhysicalToCached(0x0028)); }

inline u32 OSGetConsoleSimulatedMemSize(void) { return *(u32*)(OSPhysicalToCached(0x00F0)); }

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext* context) {
    u32 addr;
    u32 cause;

    cause = __MEMRegs[0xF];
    addr = (((u32)__MEMRegs[0x12] & 0x3FF) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (__OSErrorTable[__OS_EXCEPTION_MEMORY_PROTECTION]) {
        __OSErrorTable[__OS_EXCEPTION_MEMORY_PROTECTION](__OS_EXCEPTION_MEMORY_PROTECTION, context, cause, addr);
        return;
    }

    __OSUnhandledException(__OS_EXCEPTION_MEMORY_PROTECTION, context, cause, addr);
}

ASM void Config24MB(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc

    addi    r7,r0,0

    addis   r4,r0,0x00000002@ha
    addi    r4,r4,0x00000002@l
    addis   r3,r0,0x800001FF@ha
    addi    r3,r3,0x800001FF@l

    addis   r6,r0,0x01000002@ha
    addi    r6,r6,0x01000002@l
    addis   r5,r0,0x810000FF@ha
    addi    r5,r5,0x810000FF@l

    isync

    mtspr   dbat0u,r7
    mtspr   dbat0l,r4
    mtspr   dbat0u,r3
    isync

    mtspr   ibat0u,r7
    mtspr   ibat0l,r4
    mtspr   ibat0u,r3
    isync

    mtspr   dbat2u,r7
    mtspr   dbat2l,r6
    mtspr   dbat2u,r5
    isync

    mtspr   ibat2u,r7
    mtspr   ibat2l,r6
    mtspr   ibat2u,r5
    isync

    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3

    mflr    r3
    mtsrr0  r3
    rfi
#endif // clang-format on
}

ASM void Config48MB(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc

    addi    r7,r0,0x0000

    addis   r4,r0,0x00000002@ha
    addi    r4,r4,0x00000002@l
    addis   r3,r0,0x800003FF@ha
    addi    r3,r3,0x800003FF@l

    addis   r6,r0,0x02000002@ha
    addi    r6,r6,0x02000002@l
    addis   r5,r0,0x820001FF@ha
    addi    r5,r5,0x820001FF@l

    isync

    mtspr   dbat0u,r7
    mtspr   dbat0l,r4
    mtspr   dbat0u,r3
    isync

    mtspr   ibat0u,r7
    mtspr   ibat0l,r4
    mtspr   ibat0u,r3
    isync

    mtspr   dbat2u,r7
    mtspr   dbat2l,r6
    mtspr   dbat2u,r5
    isync

    mtspr   ibat2u,r7
    mtspr   ibat2l,r6
    mtspr   ibat2u,r5
    isync

    mfmsr   r3
    ori     r3, r3, 0x30
    mtsrr1  r3

    mflr    r3
    mtsrr0  r3
    rfi
#endif // clang-format on
}

ASM void RealMode(register u32 addr) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    clrlwi r3, r3, 2
    mtsrr0 r3
    mfmsr r3
    rlwinm r3, r3, 0, 28, 25
    mtsrr1 r3
    rfi
#endif // clang-format on
}

void __OSInitMemoryProtection(void) {
    u32 padding[8];
    u32 simulatedSize;
    bool enabled;
    simulatedSize = OSGetConsoleSimulatedMemSize();
    enabled = OSDisableInterrupts();

#if IS_MQ
    if (simulatedSize <= 0x1800000) {
        RealMode((u32)&Config24MB);
    } else if (simulatedSize <= 0x3000000) {
        RealMode((u32)&Config48MB);
    }
#endif

    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2 |
                       OS_INTERRUPTMASK_MEM_3);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_0, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_1, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_2, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_3, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_ADDRESS, MEMIntrruptHandler);
    OSRegisterResetFunction(&ResetFunctionInfo);

    if (OSGetConsoleSimulatedMemSize() < OSGetPhysicalMemSize() && OSGetConsoleSimulatedMemSize() == 0x1800000) {
#if IS_CE
        DCInvalidateRange((void*)0x81800000, 0x1800000);
#endif
        __MEMRegs[20] = 2;
    }

#if IS_CE
    if (simulatedSize <= 0x1800000) {
        RealMode((u32)&Config24MB);
    } else if (simulatedSize <= 0x3000000) {
        RealMode((u32)&Config48MB);
    }
#endif

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
    OSRestoreInterrupts(enabled);
}
