glabel mcardWriteAnywherePartial
/* 01557C 8001AB1C 7C0802A6 */  mflr    r0
/* 015580 8001AB20 3D208010 */  lis     r9, mCard@ha
/* 015584 8001AB24 90010004 */  stw     r0, 4(r1)
/* 015588 8001AB28 392979B0 */  addi    r9, r9, mCard@l
/* 01558C 8001AB2C 9421FD78 */  stwu    r1, -0x288(r1)
/* 015590 8001AB30 BF21026C */  stmw    r25, 0x26c(r1)
/* 015594 8001AB34 3BE30000 */  addi    r31, r3, 0
/* 015598 8001AB38 3B240000 */  addi    r25, r4, 0
/* 01559C 8001AB3C 3B450000 */  addi    r26, r5, 0
/* 0155A0 8001AB40 3B660000 */  addi    r27, r6, 0
/* 0155A4 8001AB44 3B870000 */  addi    r28, r7, 0
/* 0155A8 8001AB48 3BA80000 */  addi    r29, r8, 0
/* 0155AC 8001AB4C 80090470 */  lwz     r0, 0x470(r9)
/* 0155B0 8001AB50 2C000001 */  cmpwi   r0, 1
/* 0155B4 8001AB54 4082015C */  bne     lbl_8001ACB0
/* 0155B8 8001AB58 801F0470 */  lwz     r0, 0x470(r31)
/* 0155BC 8001AB5C 2C000001 */  cmpwi   r0, 1
/* 0155C0 8001AB60 408200B0 */  bne     lbl_8001AC10
/* 0155C4 8001AB64 40820070 */  bne     lbl_8001ABD4
/* 0155C8 8001AB68 38810020 */  addi    r4, r1, 0x20
/* 0155CC 8001AB6C 7C802E70 */  srawi   r0, r4, 5
/* 0155D0 8001AB70 7C000194 */  addze   r0, r0
/* 0155D4 8001AB74 54002834 */  slwi    r0, r0, 5
/* 0155D8 8001AB78 7C002010 */  subfc   r0, r0, r4
/* 0155DC 8001AB7C 20600020 */  subfic  r3, r0, 0x20
/* 0155E0 8001AB80 7C602E70 */  srawi   r0, r3, 5
/* 0155E4 8001AB84 7C000194 */  addze   r0, r0
/* 0155E8 8001AB88 54002834 */  slwi    r0, r0, 5
/* 0155EC 8001AB8C 7C001810 */  subfc   r0, r0, r3
/* 0155F0 8001AB90 7FC40214 */  add     r30, r4, r0
/* 0155F4 8001AB94 389E0000 */  addi    r4, r30, 0
/* 0155F8 8001AB98 387F0348 */  addi    r3, r31, 0x348
/* 0155FC 8001AB9C 38A00200 */  li      r5, 0x200
/* 015600 8001ABA0 38C00000 */  li      r6, 0
/* 015604 8001ABA4 480A5F71 */  bl      CARDRead
/* 015608 8001ABA8 38830000 */  addi    r4, r3, 0
/* 01560C 8001ABAC 387F0000 */  addi    r3, r31, 0
/* 015610 8001ABB0 480016F1 */  bl      mcardGCErrorHandler
/* 015614 8001ABB4 2C030001 */  cmpwi   r3, 1
/* 015618 8001ABB8 4182000C */  beq     lbl_8001ABC4
/* 01561C 8001ABBC 38000000 */  li      r0, 0
/* 015620 8001ABC0 48000018 */  b       lbl_8001ABD8
lbl_8001ABC4:
/* 015624 8001ABC4 389E0000 */  addi    r4, r30, 0
/* 015628 8001ABC8 38610240 */  addi    r3, r1, 0x240
/* 01562C 8001ABCC 38A00028 */  li      r5, 0x28
/* 015630 8001ABD0 4BFEA8F5 */  bl      memcpy
lbl_8001ABD4:
/* 015634 8001ABD4 38000001 */  li      r0, 1
lbl_8001ABD8:
/* 015638 8001ABD8 2C000000 */  cmpwi   r0, 0
/* 01563C 8001ABDC 4082000C */  bne     lbl_8001ABE8
/* 015640 8001ABE0 38000000 */  li      r0, 0
/* 015644 8001ABE4 48000030 */  b       lbl_8001AC14
lbl_8001ABE8:
/* 015648 8001ABE8 38610240 */  addi    r3, r1, 0x240
/* 01564C 8001ABEC 389F0320 */  addi    r4, r31, 0x320
/* 015650 8001ABF0 38A00028 */  li      r5, 0x28
/* 015654 8001ABF4 480B3D1D */  bl      memcmp
/* 015658 8001ABF8 2C030000 */  cmpwi   r3, 0
/* 01565C 8001ABFC 41820014 */  beq     lbl_8001AC10
/* 015660 8001AC00 38000017 */  li      r0, 0x17
/* 015664 8001AC04 901F035C */  stw     r0, 0x35c(r31)
/* 015668 8001AC08 38000000 */  li      r0, 0
/* 01566C 8001AC0C 48000008 */  b       lbl_8001AC14
lbl_8001AC10:
/* 015670 8001AC10 38000001 */  li      r0, 1
lbl_8001AC14:
/* 015674 8001AC14 2C000000 */  cmpwi   r0, 0
/* 015678 8001AC18 4082000C */  bne     lbl_8001AC24
/* 01567C 8001AC1C 38600000 */  li      r3, 0
/* 015680 8001AC20 48000094 */  b       lbl_8001ACB4
lbl_8001AC24:
/* 015684 8001AC24 387B0000 */  addi    r3, r27, 0
/* 015688 8001AC28 389A0000 */  addi    r4, r26, 0
/* 01568C 8001AC2C 48082B81 */  bl      DCStoreRange
/* 015690 8001AC30 389B0000 */  addi    r4, r27, 0
/* 015694 8001AC34 38BA0000 */  addi    r5, r26, 0
/* 015698 8001AC38 38D90000 */  addi    r6, r25, 0
/* 01569C 8001AC3C 387F0348 */  addi    r3, r31, 0x348
/* 0156A0 8001AC40 38E00000 */  li      r7, 0
/* 0156A4 8001AC44 480A6139 */  bl      CARDWriteAsync
/* 0156A8 8001AC48 38830000 */  addi    r4, r3, 0
/* 0156AC 8001AC4C 387F0000 */  addi    r3, r31, 0
/* 0156B0 8001AC50 48001651 */  bl      mcardGCErrorHandler
/* 0156B4 8001AC54 2C030001 */  cmpwi   r3, 1
/* 0156B8 8001AC58 4182000C */  beq     lbl_8001AC64
/* 0156BC 8001AC5C 38600000 */  li      r3, 0
/* 0156C0 8001AC60 48000054 */  b       lbl_8001ACB4
lbl_8001AC64:
/* 0156C4 8001AC64 3C608001 */  lis     r3, simulatorMCardPollDrawBar@ha
/* 0156C8 8001AC68 93BF036C */  stw     r29, 0x36c(r31)
/* 0156CC 8001AC6C 38038A14 */  addi    r0, r3, simulatorMCardPollDrawBar@l
/* 0156D0 8001AC70 2C1C0000 */  cmpwi   r28, 0
/* 0156D4 8001AC74 901F0364 */  stw     r0, 0x364(r31)
/* 0156D8 8001AC78 40820010 */  bne     lbl_8001AC88
/* 0156DC 8001AC7C 807F0360 */  lwz     r3, 0x360(r31)
/* 0156E0 8001AC80 480A28A1 */  bl      CARDGetXferredBytes
/* 0156E4 8001AC84 907F0368 */  stw     r3, 0x368(r31)
lbl_8001AC88:
/* 0156E8 8001AC88 7FE3FB78 */  mr      r3, r31
/* 0156EC 8001AC8C 480004DD */  bl      mcardPoll
/* 0156F0 8001AC90 2C030001 */  cmpwi   r3, 1
/* 0156F4 8001AC94 41820014 */  beq     lbl_8001ACA8
/* 0156F8 8001AC98 38000000 */  li      r0, 0
/* 0156FC 8001AC9C 901F0364 */  stw     r0, 0x364(r31)
/* 015700 8001ACA0 38600000 */  li      r3, 0
/* 015704 8001ACA4 48000010 */  b       lbl_8001ACB4
lbl_8001ACA8:
/* 015708 8001ACA8 38000000 */  li      r0, 0
/* 01570C 8001ACAC 901F0364 */  stw     r0, 0x364(r31)
lbl_8001ACB0:
/* 015710 8001ACB0 38600001 */  li      r3, 1
lbl_8001ACB4:
/* 015714 8001ACB4 BB21026C */  lmw     r25, 0x26c(r1)
/* 015718 8001ACB8 8001028C */  lwz     r0, 0x28c(r1)
/* 01571C 8001ACBC 38210288 */  addi    r1, r1, 0x288
/* 015720 8001ACC0 7C0803A6 */  mtlr    r0
/* 015724 8001ACC4 4E800020 */  blr     
