glabel simulatorDrawErrorMessage
/* 007DBC 8000D35C 7C0802A6 */  mflr    r0
/* 007DC0 8000D360 3CC0800E */  lis     r6, gcoverOpen@ha
/* 007DC4 8000D364 90010004 */  stw     r0, 4(r1)
/* 007DC8 8000D368 9421FFD8 */  stwu    r1, -0x28(r1)
/* 007DCC 8000D36C 93E10024 */  stw     r31, 0x24(r1)
/* 007DD0 8000D370 3BE50000 */  addi    r31, r5, 0
/* 007DD4 8000D374 93C10020 */  stw     r30, 0x20(r1)
/* 007DD8 8000D378 3BC6B800 */  addi    r30, r6, gcoverOpen@l
/* 007DDC 8000D37C 93A1001C */  stw     r29, 0x1c(r1)
/* 007DE0 8000D380 3BA40000 */  addi    r29, r4, 0
/* 007DE4 8000D384 38800000 */  li      r4, 0
/* 007DE8 8000D388 93810018 */  stw     r28, 0x18(r1)
/* 007DEC 8000D38C 3B830000 */  addi    r28, r3, 0
/* 007DF0 8000D390 38600000 */  li      r3, 0
/* 007DF4 8000D394 480A3A9D */  bl      PADControlMotor
/* 007DF8 8000D398 281C0006 */  cmplwi  r28, 6
/* 007DFC 8000D39C 418101C4 */  bgt     lbl_8000D560
/* 007E00 8000D3A0 3C60800F */  lis     r3, jtbl_800EA150@ha
/* 007E04 8000D3A4 3863A150 */  addi    r3, r3, jtbl_800EA150@l
/* 007E08 8000D3A8 5780103A */  slwi    r0, r28, 2
/* 007E0C 8000D3AC 7C03002E */  lwzx    r0, r3, r0
/* 007E10 8000D3B0 7C0903A6 */  mtctr   r0
/* 007E14 8000D3B4 4E800420 */  bctr    
.global lbl_8000D3B8
lbl_8000D3B8:
/* 007E18 8000D3B8 809E0008 */  lwz     r4, 8(r30)
/* 007E1C 8000D3BC 387E0000 */  addi    r3, r30, 0
/* 007E20 8000D3C0 38DD0000 */  addi    r6, r29, 0
/* 007E24 8000D3C4 80A40000 */  lwz     r5, 0(r4)
/* 007E28 8000D3C8 7FE7FB78 */  mr      r7, r31
/* 007E2C 8000D3CC A0850002 */  lhz     r4, 2(r5)
/* 007E30 8000D3D0 A0050000 */  lhz     r0, 0(r5)
/* 007E34 8000D3D4 7C840E70 */  srawi   r4, r4, 1
/* 007E38 8000D3D8 7C840194 */  addze   r4, r4
/* 007E3C 8000D3DC 208400A0 */  subfic  r4, r4, 0xa0
/* 007E40 8000D3E0 7C000E70 */  srawi   r0, r0, 1
/* 007E44 8000D3E4 7C000194 */  addze   r0, r0
/* 007E48 8000D3E8 20A00078 */  subfic  r5, r0, 0x78
/* 007E4C 8000D3EC 48001099 */  bl      simulatorDrawImage
/* 007E50 8000D3F0 48000170 */  b       lbl_8000D560
.global lbl_8000D3F4
lbl_8000D3F4:
/* 007E54 8000D3F4 3C7E0001 */  addis   r3, r30, 1
/* 007E58 8000D3F8 80839F68 */  lwz     r4, -0x6098(r3)
/* 007E5C 8000D3FC 7FA6EB78 */  mr      r6, r29
/* 007E60 8000D400 7FE7FB78 */  mr      r7, r31
/* 007E64 8000D404 80A40000 */  lwz     r5, 0(r4)
/* 007E68 8000D408 38639F60 */  addi    r3, r3, -24736
/* 007E6C 8000D40C A0850002 */  lhz     r4, 2(r5)
/* 007E70 8000D410 A0050000 */  lhz     r0, 0(r5)
/* 007E74 8000D414 7C840E70 */  srawi   r4, r4, 1
/* 007E78 8000D418 7C840194 */  addze   r4, r4
/* 007E7C 8000D41C 208400A0 */  subfic  r4, r4, 0xa0
/* 007E80 8000D420 7C000E70 */  srawi   r0, r0, 1
/* 007E84 8000D424 7C000194 */  addze   r0, r0
/* 007E88 8000D428 20A00078 */  subfic  r5, r0, 0x78
/* 007E8C 8000D42C 48001059 */  bl      simulatorDrawImage
/* 007E90 8000D430 48000130 */  b       lbl_8000D560
.global lbl_8000D434
lbl_8000D434:
/* 007E94 8000D434 3C7E0001 */  addis   r3, r30, 1
/* 007E98 8000D438 8083BE88 */  lwz     r4, -0x4178(r3)
/* 007E9C 8000D43C 7FA6EB78 */  mr      r6, r29
/* 007EA0 8000D440 7FE7FB78 */  mr      r7, r31
/* 007EA4 8000D444 80A40000 */  lwz     r5, 0(r4)
/* 007EA8 8000D448 3863BE80 */  addi    r3, r3, -16768
/* 007EAC 8000D44C A0850002 */  lhz     r4, 2(r5)
/* 007EB0 8000D450 A0050000 */  lhz     r0, 0(r5)
/* 007EB4 8000D454 7C840E70 */  srawi   r4, r4, 1
/* 007EB8 8000D458 7C840194 */  addze   r4, r4
/* 007EBC 8000D45C 208400A0 */  subfic  r4, r4, 0xa0
/* 007EC0 8000D460 7C000E70 */  srawi   r0, r0, 1
/* 007EC4 8000D464 7C000194 */  addze   r0, r0
/* 007EC8 8000D468 20A00078 */  subfic  r5, r0, 0x78
/* 007ECC 8000D46C 48001019 */  bl      simulatorDrawImage
/* 007ED0 8000D470 480000F0 */  b       lbl_8000D560
.global lbl_8000D474
lbl_8000D474:
/* 007ED4 8000D474 807E4808 */  lwz     r3, 0x4808(r30)
/* 007ED8 8000D478 38DD0000 */  addi    r6, r29, 0
/* 007EDC 8000D47C 38FF0000 */  addi    r7, r31, 0
/* 007EE0 8000D480 80A30000 */  lwz     r5, 0(r3)
/* 007EE4 8000D484 387E4800 */  addi    r3, r30, 0x4800
/* 007EE8 8000D488 A0850002 */  lhz     r4, 2(r5)
/* 007EEC 8000D48C A0050000 */  lhz     r0, 0(r5)
/* 007EF0 8000D490 7C840E70 */  srawi   r4, r4, 1
/* 007EF4 8000D494 7C840194 */  addze   r4, r4
/* 007EF8 8000D498 208400A0 */  subfic  r4, r4, 0xa0
/* 007EFC 8000D49C 7C000E70 */  srawi   r0, r0, 1
/* 007F00 8000D4A0 7C000194 */  addze   r0, r0
/* 007F04 8000D4A4 20A00078 */  subfic  r5, r0, 0x78
/* 007F08 8000D4A8 48000FDD */  bl      simulatorDrawImage
/* 007F0C 8000D4AC 480000B4 */  b       lbl_8000D560
.global lbl_8000D4B0
lbl_8000D4B0:
/* 007F10 8000D4B0 807E6C68 */  lwz     r3, 0x6c68(r30)
/* 007F14 8000D4B4 38DD0000 */  addi    r6, r29, 0
/* 007F18 8000D4B8 38FF0000 */  addi    r7, r31, 0
/* 007F1C 8000D4BC 80A30000 */  lwz     r5, 0(r3)
/* 007F20 8000D4C0 387E6C60 */  addi    r3, r30, 0x6c60
/* 007F24 8000D4C4 A0850002 */  lhz     r4, 2(r5)
/* 007F28 8000D4C8 A0050000 */  lhz     r0, 0(r5)
/* 007F2C 8000D4CC 7C840E70 */  srawi   r4, r4, 1
/* 007F30 8000D4D0 7C840194 */  addze   r4, r4
/* 007F34 8000D4D4 208400A0 */  subfic  r4, r4, 0xa0
/* 007F38 8000D4D8 7C000E70 */  srawi   r0, r0, 1
/* 007F3C 8000D4DC 7C000194 */  addze   r0, r0
/* 007F40 8000D4E0 20A00078 */  subfic  r5, r0, 0x78
/* 007F44 8000D4E4 48000FA1 */  bl      simulatorDrawImage
/* 007F48 8000D4E8 48000078 */  b       lbl_8000D560
.global lbl_8000D4EC
lbl_8000D4EC:
/* 007F4C 8000D4EC 807E28E8 */  lwz     r3, 0x28e8(r30)
/* 007F50 8000D4F0 38DD0000 */  addi    r6, r29, 0
/* 007F54 8000D4F4 38FF0000 */  addi    r7, r31, 0
/* 007F58 8000D4F8 80A30000 */  lwz     r5, 0(r3)
/* 007F5C 8000D4FC 387E28E0 */  addi    r3, r30, 0x28e0
/* 007F60 8000D500 A0850002 */  lhz     r4, 2(r5)
/* 007F64 8000D504 A0050000 */  lhz     r0, 0(r5)
/* 007F68 8000D508 7C840E70 */  srawi   r4, r4, 1
/* 007F6C 8000D50C 7C840194 */  addze   r4, r4
/* 007F70 8000D510 208400A0 */  subfic  r4, r4, 0xa0
/* 007F74 8000D514 7C000E70 */  srawi   r0, r0, 1
/* 007F78 8000D518 7C000194 */  addze   r0, r0
/* 007F7C 8000D51C 20A00078 */  subfic  r5, r0, 0x78
/* 007F80 8000D520 48000F65 */  bl      simulatorDrawImage
/* 007F84 8000D524 4800003C */  b       lbl_8000D560
.global lbl_8000D528
lbl_8000D528:
/* 007F88 8000D528 807E6C68 */  lwz     r3, 0x6c68(r30)
/* 007F8C 8000D52C 38DD0000 */  addi    r6, r29, 0
/* 007F90 8000D530 38FF0000 */  addi    r7, r31, 0
/* 007F94 8000D534 80A30000 */  lwz     r5, 0(r3)
/* 007F98 8000D538 387E6C60 */  addi    r3, r30, 0x6c60
/* 007F9C 8000D53C A0850002 */  lhz     r4, 2(r5)
/* 007FA0 8000D540 A0050000 */  lhz     r0, 0(r5)
/* 007FA4 8000D544 7C840E70 */  srawi   r4, r4, 1
/* 007FA8 8000D548 7C840194 */  addze   r4, r4
/* 007FAC 8000D54C 208400A0 */  subfic  r4, r4, 0xa0
/* 007FB0 8000D550 7C000E70 */  srawi   r0, r0, 1
/* 007FB4 8000D554 7C000194 */  addze   r0, r0
/* 007FB8 8000D558 20A00078 */  subfic  r5, r0, 0x78
/* 007FBC 8000D55C 48000F29 */  bl      simulatorDrawImage
lbl_8000D560:
/* 007FC0 8000D560 38000001 */  li      r0, 1
/* 007FC4 8000D564 900D891C */  stw     r0, gbDisplayedError@sda21(r13)
/* 007FC8 8000D568 38600001 */  li      r3, 1
/* 007FCC 8000D56C 8001002C */  lwz     r0, 0x2c(r1)
/* 007FD0 8000D570 83E10024 */  lwz     r31, 0x24(r1)
/* 007FD4 8000D574 83C10020 */  lwz     r30, 0x20(r1)
/* 007FD8 8000D578 83A1001C */  lwz     r29, 0x1c(r1)
/* 007FDC 8000D57C 83810018 */  lwz     r28, 0x18(r1)
/* 007FE0 8000D580 38210028 */  addi    r1, r1, 0x28
/* 007FE4 8000D584 7C0803A6 */  mtlr    r0
/* 007FE8 8000D588 4E800020 */  blr     

.section .data

jtbl_800EA150:
    .word lbl_8000D3B8
    .word lbl_8000D3F4
    .word lbl_8000D434
    .word lbl_8000D4B0
    .word lbl_8000D474
    .word lbl_8000D4EC
    .word lbl_8000D528
