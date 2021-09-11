# db.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel DBInit
/* 0A2740 800A7CE0 3C808000 */  lis     r4, 0x8000
/* 0A2744 800A7CE4 38040040 */  addi    r0, r4, 0x40
/* 0A2748 800A7CE8 3C60800A */  lis     r3, __DBExceptionDestination@ha
/* 0A274C 800A7CEC 900D8C30 */  stw     r0, __DBInterface-_SDA_BASE_(r13)
/* 0A2750 800A7CF0 38637D50 */  addi    r3, r3, __DBExceptionDestination@l
/* 0A2754 800A7CF4 3C038000 */  addis   r0, r3, 0x8000
/* 0A2758 800A7CF8 90040048 */  stw     r0, 0x48(r4)
/* 0A275C 800A7CFC 38000001 */  li      r0, 1
/* 0A2760 800A7D00 900D8C34 */  stw     r0, DBVerbose-_SDA_BASE_(r13)
/* 0A2764 800A7D04 4E800020 */  blr     

glabel __DBExceptionDestinationAux
/* 0A2768 800A7D08 7C0802A6 */  mflr    r0
/* 0A276C 800A7D0C 3C60800F */  lis     r3, D_800F1AA0@ha
/* 0A2770 800A7D10 90010004 */  stw     r0, 4(r1)
/* 0A2774 800A7D14 38631AA0 */  addi    r3, r3, D_800F1AA0@l
/* 0A2778 800A7D18 4CC63182 */  crclr   6
/* 0A277C 800A7D1C 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0A2780 800A7D20 93E10014 */  stw     r31, 0x14(r1)
/* 0A2784 800A7D24 808000C0 */  lwz     r4, 0xc0(0)
/* 0A2788 800A7D28 3FE48000 */  addis   r31, r4, 0x8000
/* 0A278C 800A7D2C 4BFF68CD */  bl      OSReport
/* 0A2790 800A7D30 7FE3FB78 */  mr      r3, r31
/* 0A2794 800A7D34 4BFF6551 */  bl      OSDumpContext
/* 0A2798 800A7D38 4BFF3DC5 */  bl      PPCHalt
/* 0A279C 800A7D3C 8001001C */  lwz     r0, 0x1c(r1)
/* 0A27A0 800A7D40 83E10014 */  lwz     r31, 0x14(r1)
/* 0A27A4 800A7D44 38210018 */  addi    r1, r1, 0x18
/* 0A27A8 800A7D48 7C0803A6 */  mtlr    r0
/* 0A27AC 800A7D4C 4E800020 */  blr     

glabel __DBExceptionDestination
/* 0A27B0 800A7D50 7C6000A6 */  mfmsr   r3
/* 0A27B4 800A7D54 60630030 */  ori     r3, r3, 0x30
/* 0A27B8 800A7D58 7C600124 */  mtmsr   r3
/* 0A27BC 800A7D5C 4BFFFFAC */  b       __DBExceptionDestinationAux

glabel __DBIsExceptionMarked
/* 0A27C0 800A7D60 808D8C30 */  lwz     r4, __DBInterface-_SDA_BASE_(r13)
/* 0A27C4 800A7D64 5460063E */  clrlwi  r0, r3, 0x18
/* 0A27C8 800A7D68 38600001 */  li      r3, 1
/* 0A27CC 800A7D6C 80840004 */  lwz     r4, 4(r4)
/* 0A27D0 800A7D70 7C600030 */  slw     r0, r3, r0
/* 0A27D4 800A7D74 7C830038 */  and     r3, r4, r0
/* 0A27D8 800A7D78 4E800020 */  blr     

glabel DBPrintf
/* 0A27DC 800A7D7C 9421FF90 */  stwu    r1, -0x70(r1)
/* 0A27E0 800A7D80 40860024 */  bne     cr1, lbl_800A7DA4
/* 0A27E4 800A7D84 D8210028 */  stfd    f1, 0x28(r1)
/* 0A27E8 800A7D88 D8410030 */  stfd    f2, 0x30(r1)
/* 0A27EC 800A7D8C D8610038 */  stfd    f3, 0x38(r1)
/* 0A27F0 800A7D90 D8810040 */  stfd    f4, 0x40(r1)
/* 0A27F4 800A7D94 D8A10048 */  stfd    f5, 0x48(r1)
/* 0A27F8 800A7D98 D8C10050 */  stfd    f6, 0x50(r1)
/* 0A27FC 800A7D9C D8E10058 */  stfd    f7, 0x58(r1)
/* 0A2800 800A7DA0 D9010060 */  stfd    f8, 0x60(r1)
lbl_800A7DA4:
/* 0A2804 800A7DA4 90610008 */  stw     r3, 8(r1)
/* 0A2808 800A7DA8 9081000C */  stw     r4, 0xc(r1)
/* 0A280C 800A7DAC 90A10010 */  stw     r5, 0x10(r1)
/* 0A2810 800A7DB0 90C10014 */  stw     r6, 0x14(r1)
/* 0A2814 800A7DB4 90E10018 */  stw     r7, 0x18(r1)
/* 0A2818 800A7DB8 9101001C */  stw     r8, 0x1c(r1)
/* 0A281C 800A7DBC 91210020 */  stw     r9, 0x20(r1)
/* 0A2820 800A7DC0 91410024 */  stw     r10, 0x24(r1)
/* 0A2824 800A7DC4 38210070 */  addi    r1, r1, 0x70
/* 0A2828 800A7DC8 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000EEB20 800F1AA0 0018 */
D_800F1AA0:
    .asciz "DBExceptionDestination\n"
    .balign 4

.section .sbss, "wa"

.balign 8

/* 000F1B90 80135910 0004 */
glabel __DBInterface
    .skip 4

/* 000F1B94 80135914 0004 */
glabel DBVerbose
    .skip 4
