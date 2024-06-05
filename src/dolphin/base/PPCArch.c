#include "dolphin/base/PPCArch.h"
#include "dolphin/types.h"
#include "macros.h"

union FpscrUnion {
    f64 f;
    struct {
        u32 fpscr_pad;
        u32 fpscr;
    } u;
};

void PPCMthid0(u32 newHID0);

ASM u32 PPCMfmsr(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfmsr r3
    blr
#endif // clang-format on
}

ASM void PPCMtmsr(register u32 newMSR){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtmsr newMSR
    blr
#endif // clang-format on
}

ASM u32 PPCMfhid0(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfspr r3, HID0
    blr
#endif // clang-format on
}

ASM void PPCMthid0(register u32 newHID0){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtspr HID0, newHID0
    blr
#endif // clang-format on
}

ASM u32 PPCMfl2cr(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfspr r3, L2CR
    blr
#endif // clang-format on
}

ASM void PPCMtl2cr(register u32 newL2cr){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtspr L2CR, newL2cr
    blr
#endif // clang-format on
}

WEAK ASM void PPCMtdec(register u32 newDec){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtdec newDec
    blr
#endif // clang-format on
}

ASM void PPCSync(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    sc
    blr
#endif // clang-format on
}

// spins infinitely
WEAK ASM void PPCHalt(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc

    sync

_spin:
    nop
    li r3, 0
    nop
    b _spin

    // NEVER REACHED
#endif // clang-format on
}

#if IS_CE

ASM void PPCMtmmcr0(register u32 newMmcr0){
#ifdef __MWERKS__ // clang-format off
    mtspr MMCR0, newMmcr0
#endif // clang-format on
}

ASM void PPCMtmmcr1(register u32 newMmcr1){
#ifdef __MWERKS__ // clang-format off
    mtspr MMCR1, newMmcr1
#endif // clang-format on
}

ASM void PPCMtpmc1(register u32 newPmc1){
#ifdef __MWERKS__ // clang-format off
    mtspr PMC1, newPmc1
#endif // clang-format on
}

ASM void PPCMtpmc2(register u32 newPmc2){
#ifdef __MWERKS__ // clang-format off
    mtspr PMC2, newPmc2
#endif // clang-format on
}

ASM void PPCMtpmc3(register u32 newPmc3){
#ifdef __MWERKS__ // clang-format off
    mtspr PMC3, newPmc3
#endif // clang-format on
}

ASM void PPCMtpmc4(register u32 newPmc4){
#ifdef __MWERKS__ // clang-format off
    mtspr PMC4, newPmc4
#endif // clang-format on
}

#endif

u32 PPCMffpscr(void) {
    union FpscrUnion m;

    ASM {
#ifdef __MWERKS__ // clang-format off
        mffs fp31
        stfd fp31, m.f;
#endif // clang-format on
    }

    return m.u.fpscr;
}

void PPCMtfpscr(register u32 newFPSCR) {
    union FpscrUnion m;

    ASM {
#ifdef __MWERKS__ // clang-format off
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xFF, fp31
#endif // clang-format on
    }
}

ASM u32 PPCMfhid2(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mfspr r3, HID2
    blr
#endif // clang-format on
}

ASM void PPCMthid2(register u32 newhid2){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtspr HID2, newhid2
    blr
#endif // clang-format on
}

ASM void PPCMtwpar(register u32 newwpar) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtspr WPAR, newwpar
    blr
#endif // clang-format on
}

void PPCDisableSpeculation(void) { PPCMthid0(PPCMfhid0() | HID0_SPD); }

ASM void PPCSetFpNonIEEEMode(void) {
#ifdef __MWERKS__ // clang-format off
    nofralloc
    mtfsb1      4*7+1
    blr
#endif // clang-format on
}
