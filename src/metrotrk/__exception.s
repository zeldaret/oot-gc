# __exception.s
.include "macros.inc"

.section .init

.balign 4

glabel gTRKInterruptVectorTable
    .string "Metrowerks Target Resident Kernel for PowerPC"
    .balign 4

    .skip 208

    b       __TRK_reset

    .skip 252

    mtspr   0x111, r2
    mfspr   r2, 0x1A
    icbi    0, r2
    mfdar   r2
    dcbi    0, r2
    mfspr   r2, 0x111
    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x200
    rfi     

    .skip 180

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x300
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x400
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x500
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x600
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x700
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x800
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x900
    rfi     

    .skip 716

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0xC00
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0xD00
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0xE00
    rfi     

    .skip 204

    b       lbl_800043D0

    .skip 28

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0xF20
    rfi     

lbl_800043D0:
    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0xF00
    rfi     

    .skip 120

    mtspr   0x111, r2
    mfcr    r2
    mtspr   0x112, r2
    mfmsr   r2
    andis.  r2, r2, 2
    beq     lbl_800044AC
    mfmsr   r2
    xoris   r2, r2, 2
    sync    0
    mtmsr   r2
    sync    0
    mtspr   0x111, r2
lbl_800044AC:
    mfspr   r2, 0x112
    mtcrf   0xFF, r2
    mfspr   r2, 0x111
    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1000
    rfi     

    .skip 144

    mtspr   0x111, r2
    mfcr    r2
    mtspr   0x112, r2
    mfmsr   r2
    andis.  r2, r2, 2
    beq     lbl_800045AC
    mfmsr   r2
    xoris   r2, r2, 2
    sync    0
    mtmsr   r2
    sync    0
    mtspr   0x111, r2
lbl_800045AC:
    mfspr   r2, 0x112
    mtcrf   0xFF, r2
    mfspr   r2, 0x111
    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1100
    rfi     

    .skip 144

    mtspr   0x111, r2
    mfcr    r2
    mtspr   0x112, r2
    mfmsr   r2
    andis.  r2, r2, 2
    beq     lbl_800046AC
    mfmsr   r2
    xoris   r2, r2, 2
    sync    0
    mtmsr   r2
    sync    0
    mtspr   0x111, r2
lbl_800046AC:
    mfspr   r2, 0x112
    mtcrf   0xFF, r2
    mfspr   r2, 0x111
    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1200
    rfi     

    .skip 144

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1300
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1400
    rfi     

    .skip 460

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1600
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1700
    rfi     

    .skip 1228

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1C00
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1D00
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1E00
    rfi     

    .skip 204

    mtspr   0x111, r2
    mtspr   0x112, r3
    mtspr   0x113, r4
    mfspr   r2, 0x1A
    mfspr   r4, 0x1B
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   0x1B, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   0x1A, r3
    li      r3, 0x1F00
    rfi     
