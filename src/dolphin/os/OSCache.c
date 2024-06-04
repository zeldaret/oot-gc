#include "dolphin/base/PPCArch.h"
#include "dolphin/db.h"
#include "dolphin/os.h"
#include "intrinsics.h"
#include "macros.h"

ASM void DCEnable(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    sync
    mfspr r3, HID0
    ori   r3, r3, 0x4000
    mtspr HID0, r3
    blr
#endif // clang-format on
}

ASM void DCInvalidateRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add    nBytes, nBytes, r5
    addi   nBytes, nBytes, 31
    srwi   nBytes, nBytes, 5
    mtctr  nBytes

@1
    dcbi r0, addr
    addi addr, addr, 32
    bdnz @1
    blr
#endif // clang-format on
}

ASM void DCFlushRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @1
    sc
    blr
#endif // clang-format on
}

ASM void DCStoreRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbst r0, addr
    addi addr, addr, 32
    bdnz @1
    sc

    blr
#endif // clang-format on
}

ASM void DCFlushRangeNoSync(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @1
    blr
#endif // clang-format on
}

ASM void DCZeroRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbz r0, addr
    addi addr, addr, 32
    bdnz @1

    blr
#endif // clang-format on
}

ASM void ICInvalidateRange(register void* addr, register u32 nBytes) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    icbi r0, addr
    addi addr, addr, 32
    bdnz @1
    sync
    isync

    blr
#endif // clang-format on
}

ASM void ICFlashInvalidate(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfspr r3, HID0
    ori r3, r3, 0x800
    mtspr HID0, r3
    blr
#endif // clang-format on
}

ASM void ICEnable(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    isync
    mfspr r3, HID0
    ori r3, r3, 0x8000
    mtspr HID0, r3
    blr
#endif // clang-format on
}

#define LC_LINES 512
#define CACHE_LINES 1024

ASM void __LCEnable(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfmsr   r5
    ori     r5, r5, 0x1000
    mtmsr   r5

    lis     r3, OS_CACHED_REGION_PREFIX
    li      r4, CACHE_LINES
    mtctr   r4
    _touchloop:
    dcbt    0,r3
    dcbst   0,r3
    addi    r3,r3,32
    bdnz    _touchloop
    mfspr   r4, HID2
    oris    r4, r4, 0x100F
    mtspr   HID2, r4

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    lis     r3, LC_BASE_PREFIX
    ori     r3, r3, 0x0002
    mtspr   DBAT3L, r3
    ori     r3, r3, 0x01FE
    mtspr   DBAT3U, r3
    isync
    lis     r3, LC_BASE_PREFIX
    li      r6, LC_LINES
    mtctr   r6
    li      r6, 0

_lockloop:
    dcbz_l  r6, r3
    addi    r3, r3, 32
    bdnz+    _lockloop

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    blr
#endif // clang-format on
}

void LCEnable(void) {
    bool enabled;

    enabled = OSDisableInterrupts();
    __LCEnable();
    OSRestoreInterrupts(enabled);
}

ASM void LCDisable(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    lis     r3, LC_BASE_PREFIX
    li      r4, LC_LINES
    mtctr r4
@1
    dcbi r0, r3
    addi r3, r3, 32
    bdnz @1
    mfspr r4, HID2
    rlwinm r4, r4, 0, 4, 2
    mtspr HID2, r4
    blr
#endif // clang-format on
}

ASM void LCStoreBlocks(register void* destAddr, register void* srcTag, register u32 numBlocks){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    rlwinm  r6, numBlocks, 30, 27, 31
    rlwinm  destAddr, destAddr, 0, 4, 31
    or      r6, r6, destAddr
    mtspr   DMA_U, r6
    rlwinm  r6, numBlocks, 2, 28, 29
    or      r6, r6, srcTag
    ori     r6, r6, 0x2
    mtspr   DMA_L, r6
    blr
#endif // clang-format on
}

u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes) {
    u32 numBlocks = (nBytes + 31) / 32;
    u32 numTransactions = (numBlocks + 128 - 1) / 128;

    while (numBlocks > 0) {
        if (numBlocks < 128) {
            LCStoreBlocks(destAddr, srcAddr, numBlocks);
            numBlocks = 0;
        } else {
            LCStoreBlocks(destAddr, srcAddr, 0);
            numBlocks -= 128;
            destAddr = (void*)((u32)destAddr + 4096);
            srcAddr = (void*)((u32)srcAddr + 4096);
        }
    }

    return numTransactions;
}

ASM void LCQueueWait(register u32 len) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
#if IS_MQ
    addi len, len, 1
#endif
@1
    mfspr r4, HID2
    rlwinm r4, r4, 8, 28, 31
#if IS_MQ
    cmpw cr2, r4, r3
    bge cr2, @1
#else
    cmpw r4, r3
    bgt @1
#endif
    blr
#endif // clang-format on
}

static inline void L2Disable(void) {
    __sync();
    PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
    __sync();
}

void L2GlobalInvalidate(void) {
    L2Disable();
    PPCMtl2cr(PPCMfl2cr() | 0x00200000);
    while (PPCMfl2cr() & 0x00000001u)
        ;
    PPCMtl2cr(PPCMfl2cr() & ~0x00200000);
    while (PPCMfl2cr() & 0x00000001u) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

static inline void L2Init(void) {
    u32 oldMSR;
    oldMSR = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();
    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(oldMSR);
}

inline void L2Enable(void) { PPCMtl2cr((PPCMfl2cr() | L2CR_L2E) & ~L2CR_L2I); }

void DMAErrorHandler(OSError error, OSContext* context, ...) {
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);
    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) || !(context->srr1 & SRR1_DMA_BIT)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport("\t- Requested a locked cache tag that was already in the cache\n");
    }

    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }

    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }

    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    // write hid2 back to clear the error bits
    PPCMthid2(hid2);
}

void __OSCacheInit(void) {
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }
    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

    OSSetErrorHandler(OS_ERROR_MACHINE_CHECK, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
