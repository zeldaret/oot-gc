# PPCArch.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel PPCMfmsr
/* 09651C 8009BABC 7C6000A6 */  mfmsr   r3
/* 096520 8009BAC0 4E800020 */  blr     

glabel PPCMtmsr
/* 096524 8009BAC4 7C600124 */  mtmsr   r3
/* 096528 8009BAC8 4E800020 */  blr     

glabel PPCMfhid0
/* 09652C 8009BACC 7C70FAA6 */  mfspr   r3, 0x3f0
/* 096530 8009BAD0 4E800020 */  blr     

glabel PPCMthid0
/* 096534 8009BAD4 7C70FBA6 */  mtspr   0x3f0, r3
/* 096538 8009BAD8 4E800020 */  blr     

glabel PPCMfl2cr
/* 09653C 8009BADC 7C79FAA6 */  mfspr   r3, 0x3f9
/* 096540 8009BAE0 4E800020 */  blr     

glabel PPCMtl2cr
/* 096544 8009BAE4 7C79FBA6 */  mtspr   0x3f9, r3
/* 096548 8009BAE8 4E800020 */  blr     

glabel PPCMtdec
/* 09654C 8009BAEC 7C7603A6 */  mtspr   0x16, r3
/* 096550 8009BAF0 4E800020 */  blr     

glabel PPCSync
/* 096554 8009BAF4 44000002 */  sc      
/* 096558 8009BAF8 4E800020 */  blr     

glabel PPCHalt
/* 09655C 8009BAFC 7C0004AC */  sync    0
lbl_8009BB00:
/* 096560 8009BB00 60000000 */  nop     
/* 096564 8009BB04 38600000 */  li      r3, 0
/* 096568 8009BB08 60000000 */  nop     
/* 09656C 8009BB0C 4BFFFFF4 */  b       lbl_8009BB00

glabel PPCMtmmcr0
/* 096570 8009BB10 7C78EBA6 */  mtspr   0x3b8, r3
/* 096574 8009BB14 4E800020 */  blr     

glabel PPCMtmmcr1
/* 096578 8009BB18 7C7CEBA6 */  mtspr   0x3bc, r3
/* 09657C 8009BB1C 4E800020 */  blr     

glabel PPCMtpmc1
/* 096580 8009BB20 7C79EBA6 */  mtspr   0x3b9, r3
/* 096584 8009BB24 4E800020 */  blr     

glabel PPCMtpmc2
/* 096588 8009BB28 7C7AEBA6 */  mtspr   0x3ba, r3
/* 09658C 8009BB2C 4E800020 */  blr     

glabel PPCMtpmc3
/* 096590 8009BB30 7C7DEBA6 */  mtspr   0x3bd, r3
/* 096594 8009BB34 4E800020 */  blr     

glabel PPCMtpmc4
/* 096598 8009BB38 7C7EEBA6 */  mtspr   0x3be, r3
/* 09659C 8009BB3C 4E800020 */  blr     

glabel PPCMffpscr
/* 0965A0 8009BB40 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0965A4 8009BB44 DBE10010 */  stfd    f31, 0x10(r1)
/* 0965A8 8009BB48 FFE0048E */  mffs    f31
/* 0965AC 8009BB4C DBE10008 */  stfd    f31, 8(r1)
/* 0965B0 8009BB50 8061000C */  lwz     r3, 0xc(r1)
/* 0965B4 8009BB54 CBE10010 */  lfd     f31, 0x10(r1)
/* 0965B8 8009BB58 38210018 */  addi    r1, r1, 0x18
/* 0965BC 8009BB5C 4E800020 */  blr     

glabel PPCMtfpscr
/* 0965C0 8009BB60 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0965C4 8009BB64 DBE10018 */  stfd    f31, 0x18(r1)
/* 0965C8 8009BB68 38800000 */  li      r4, 0
/* 0965CC 8009BB6C 90810010 */  stw     r4, 0x10(r1)
/* 0965D0 8009BB70 90610014 */  stw     r3, 0x14(r1)
/* 0965D4 8009BB74 CBE10010 */  lfd     f31, 0x10(r1)
/* 0965D8 8009BB78 FDFEFD8E */  mtfsf   0xff, f31
/* 0965DC 8009BB7C CBE10018 */  lfd     f31, 0x18(r1)
/* 0965E0 8009BB80 38210020 */  addi    r1, r1, 0x20
/* 0965E4 8009BB84 4E800020 */  blr     

glabel PPCMfhid2
/* 0965E8 8009BB88 7C78E2A6 */  mfspr   r3, 0x398
/* 0965EC 8009BB8C 4E800020 */  blr     

glabel PPCMthid2
/* 0965F0 8009BB90 7C78E3A6 */  mtspr   0x398, r3
/* 0965F4 8009BB94 4E800020 */  blr     

glabel PPCMtwpar
/* 0965F8 8009BB98 7C79E3A6 */  mtspr   0x399, r3
/* 0965FC 8009BB9C 4E800020 */  blr     

glabel PPCDisableSpeculation
/* 096600 8009BBA0 7C0802A6 */  mflr    r0
/* 096604 8009BBA4 90010004 */  stw     r0, 4(r1)
/* 096608 8009BBA8 9421FFF8 */  stwu    r1, -8(r1)
/* 09660C 8009BBAC 4BFFFF21 */  bl      PPCMfhid0
/* 096610 8009BBB0 60630200 */  ori     r3, r3, 0x200
/* 096614 8009BBB4 4BFFFF21 */  bl      PPCMthid0
/* 096618 8009BBB8 8001000C */  lwz     r0, 0xc(r1)
/* 09661C 8009BBBC 38210008 */  addi    r1, r1, 8
/* 096620 8009BBC0 7C0803A6 */  mtlr    r0
/* 096624 8009BBC4 4E800020 */  blr     

glabel PPCSetFpNonIEEEMode
/* 096628 8009BBC8 FFA0004C */  mtfsb1  0x1d
/* 09662C 8009BBCC 4E800020 */  blr     


