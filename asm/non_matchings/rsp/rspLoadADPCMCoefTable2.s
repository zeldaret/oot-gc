glabel rspLoadADPCMCoefTable2
/* 085AE0 8008B080 9421FFC8 */  stwu    r1, -0x38(r1)
/* 085AE4 8008B084 38000004 */  li      r0, 4
/* 085AE8 8008B088 7C0903A6 */  mtctr   r0
/* 085AEC 8008B08C 38830000 */  addi    r4, r3, 0
/* 085AF0 8008B090 BF21001C */  stmw    r25, 0x1c(r1)
/* 085AF4 8008B094 A0A338D6 */  lhz     r5, 0x38d6(r3)
/* 085AF8 8008B098 7CA50E70 */  srawi   r5, r5, 1
/* 085AFC 8008B09C 7CA50194 */  addze   r5, r5
/* 085B00 8008B0A0 54A6083C */  slwi    r6, r5, 1
lbl_8008B0A4:
/* 085B04 8008B0A4 81033294 */  lwz     r8, 0x3294(r3)
/* 085B08 8008B0A8 38E50008 */  addi    r7, r5, 8
/* 085B0C 8008B0AC 38050001 */  addi    r0, r5, 1
/* 085B10 8008B0B0 7D0832AE */  lhax    r8, r8, r6
/* 085B14 8008B0B4 3B450009 */  addi    r26, r5, 9
/* 085B18 8008B0B8 3B650002 */  addi    r27, r5, 2
/* 085B1C 8008B0BC B1043298 */  sth     r8, 0x3298(r4)
/* 085B20 8008B0C0 3B85000A */  addi    r28, r5, 0xa
/* 085B24 8008B0C4 3BA50003 */  addi    r29, r5, 3
/* 085B28 8008B0C8 81033294 */  lwz     r8, 0x3294(r3)
/* 085B2C 8008B0CC 54E7083C */  slwi    r7, r7, 1
/* 085B30 8008B0D0 3BC5000B */  addi    r30, r5, 0xb
/* 085B34 8008B0D4 7CE83AAE */  lhax    r7, r8, r7
/* 085B38 8008B0D8 3BE50004 */  addi    r31, r5, 4
/* 085B3C 8008B0DC 3985000C */  addi    r12, r5, 0xc
/* 085B40 8008B0E0 B0E432A8 */  sth     r7, 0x32a8(r4)
/* 085B44 8008B0E4 39650005 */  addi    r11, r5, 5
/* 085B48 8008B0E8 3945000D */  addi    r10, r5, 0xd
/* 085B4C 8008B0EC 80E33294 */  lwz     r7, 0x3294(r3)
/* 085B50 8008B0F0 5400083C */  slwi    r0, r0, 1
/* 085B54 8008B0F4 39250006 */  addi    r9, r5, 6
/* 085B58 8008B0F8 7C0702AE */  lhax    r0, r7, r0
/* 085B5C 8008B0FC 3905000E */  addi    r8, r5, 0xe
/* 085B60 8008B100 38E50007 */  addi    r7, r5, 7
/* 085B64 8008B104 B004329A */  sth     r0, 0x329a(r4)
/* 085B68 8008B108 3805000F */  addi    r0, r5, 0xf
/* 085B6C 8008B10C 575A083C */  slwi    r26, r26, 1
/* 085B70 8008B110 83233294 */  lwz     r25, 0x3294(r3)
/* 085B74 8008B114 577B083C */  slwi    r27, r27, 1
/* 085B78 8008B118 579C083C */  slwi    r28, r28, 1
/* 085B7C 8008B11C 7F59D2AE */  lhax    r26, r25, r26
/* 085B80 8008B120 57BD083C */  slwi    r29, r29, 1
/* 085B84 8008B124 57DE083C */  slwi    r30, r30, 1
/* 085B88 8008B128 B34432AA */  sth     r26, 0x32aa(r4)
/* 085B8C 8008B12C 57FF083C */  slwi    r31, r31, 1
/* 085B90 8008B130 558C083C */  slwi    r12, r12, 1
/* 085B94 8008B134 83433294 */  lwz     r26, 0x3294(r3)
/* 085B98 8008B138 556B083C */  slwi    r11, r11, 1
/* 085B9C 8008B13C 554A083C */  slwi    r10, r10, 1
/* 085BA0 8008B140 7F7ADAAE */  lhax    r27, r26, r27
/* 085BA4 8008B144 5529083C */  slwi    r9, r9, 1
/* 085BA8 8008B148 5508083C */  slwi    r8, r8, 1
/* 085BAC 8008B14C B364329C */  sth     r27, 0x329c(r4)
/* 085BB0 8008B150 54E7083C */  slwi    r7, r7, 1
/* 085BB4 8008B154 5400083C */  slwi    r0, r0, 1
/* 085BB8 8008B158 83633294 */  lwz     r27, 0x3294(r3)
/* 085BBC 8008B15C 38A50010 */  addi    r5, r5, 0x10
/* 085BC0 8008B160 38C60020 */  addi    r6, r6, 0x20
/* 085BC4 8008B164 7F9BE2AE */  lhax    r28, r27, r28
/* 085BC8 8008B168 B38432AC */  sth     r28, 0x32ac(r4)
/* 085BCC 8008B16C 83833294 */  lwz     r28, 0x3294(r3)
/* 085BD0 8008B170 7FBCEAAE */  lhax    r29, r28, r29
/* 085BD4 8008B174 B3A4329E */  sth     r29, 0x329e(r4)
/* 085BD8 8008B178 83A33294 */  lwz     r29, 0x3294(r3)
/* 085BDC 8008B17C 7FDDF2AE */  lhax    r30, r29, r30
/* 085BE0 8008B180 B3C432AE */  sth     r30, 0x32ae(r4)
/* 085BE4 8008B184 83C33294 */  lwz     r30, 0x3294(r3)
/* 085BE8 8008B188 7FFEFAAE */  lhax    r31, r30, r31
/* 085BEC 8008B18C B3E432A0 */  sth     r31, 0x32a0(r4)
/* 085BF0 8008B190 83E33294 */  lwz     r31, 0x3294(r3)
/* 085BF4 8008B194 7D9F62AE */  lhax    r12, r31, r12
/* 085BF8 8008B198 B18432B0 */  sth     r12, 0x32b0(r4)
/* 085BFC 8008B19C 81833294 */  lwz     r12, 0x3294(r3)
/* 085C00 8008B1A0 7D6C5AAE */  lhax    r11, r12, r11
/* 085C04 8008B1A4 B16432A2 */  sth     r11, 0x32a2(r4)
/* 085C08 8008B1A8 81633294 */  lwz     r11, 0x3294(r3)
/* 085C0C 8008B1AC 7D4B52AE */  lhax    r10, r11, r10
/* 085C10 8008B1B0 B14432B2 */  sth     r10, 0x32b2(r4)
/* 085C14 8008B1B4 81433294 */  lwz     r10, 0x3294(r3)
/* 085C18 8008B1B8 7D2A4AAE */  lhax    r9, r10, r9
/* 085C1C 8008B1BC B12432A4 */  sth     r9, 0x32a4(r4)
/* 085C20 8008B1C0 81233294 */  lwz     r9, 0x3294(r3)
/* 085C24 8008B1C4 7D0942AE */  lhax    r8, r9, r8
/* 085C28 8008B1C8 B10432B4 */  sth     r8, 0x32b4(r4)
/* 085C2C 8008B1CC 81033294 */  lwz     r8, 0x3294(r3)
/* 085C30 8008B1D0 7CE83AAE */  lhax    r7, r8, r7
/* 085C34 8008B1D4 B0E432A6 */  sth     r7, 0x32a6(r4)
/* 085C38 8008B1D8 80E33294 */  lwz     r7, 0x3294(r3)
/* 085C3C 8008B1DC 7C0702AE */  lhax    r0, r7, r0
/* 085C40 8008B1E0 B00432B6 */  sth     r0, 0x32b6(r4)
/* 085C44 8008B1E4 38840020 */  addi    r4, r4, 0x20
/* 085C48 8008B1E8 4200FEBC */  bdnz    lbl_8008B0A4
/* 085C4C 8008B1EC BB21001C */  lmw     r25, 0x1c(r1)
/* 085C50 8008B1F0 38600001 */  li      r3, 1
/* 085C54 8008B1F4 38210038 */  addi    r1, r1, 0x38
/* 085C58 8008B1F8 4E800020 */  blr     