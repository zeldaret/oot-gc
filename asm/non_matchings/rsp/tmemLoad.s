glabel tmemLoad
/* 074F18 8007A4B8 7C0802A6 */  mflr    r0
/* 074F1C 8007A4BC 90010004 */  stw     r0, 4(r1)
/* 074F20 8007A4C0 9421FFB0 */  stwu    r1, -0x50(r1)
/* 074F24 8007A4C4 BE810020 */  stmw    r20, 0x20(r1)
/* 074F28 8007A4C8 7CF93B78 */  mr      r25, r7
/* 074F2C 8007A4CC 7CD83378 */  mr      r24, r6
/* 074F30 8007A4D0 7F3F0734 */  extsh   r31, r25
/* 074F34 8007A4D4 3AA30000 */  addi    r21, r3, 0
/* 074F38 8007A4D8 3AC40000 */  addi    r22, r4, 0
/* 074F3C 8007A4DC 3AE50000 */  addi    r23, r5, 0
/* 074F40 8007A4E0 A8E60000 */  lha     r7, 0(r6)
/* 074F44 8007A4E4 7D060734 */  extsh   r6, r8
/* 074F48 8007A4E8 A00D8AC0 */  lhz     r0, flagSplit@sda21(r13)
/* 074F4C 8007A4EC 7CDF3214 */  add     r6, r31, r6
/* 074F50 8007A4F0 7CC60734 */  extsh   r6, r6
/* 074F54 8007A4F4 7C003850 */  subf    r0, r0, r7
/* 074F58 8007A4F8 7C1D0734 */  extsh   r29, r0
/* 074F5C 8007A4FC 7C1D3000 */  cmpw    r29, r6
/* 074F60 8007A500 4180003C */  blt     lbl_8007A53C
/* 074F64 8007A504 80B70000 */  lwz     r5, 0(r23)
/* 074F68 8007A508 7EA3AB78 */  mr      r3, r21
/* 074F6C 8007A50C A8ED8ABC */  lha     r7, tmemSliceWmax@sda21(r13)
/* 074F70 8007A510 7EC4B378 */  mr      r4, r22
/* 074F74 8007A514 480002C1 */  bl      tmemLoad_B
/* 074F78 8007A518 A00D8ABE */  lhz     r0, imageSrcWsize@sda21(r13)
/* 074F7C 8007A51C 80770000 */  lwz     r3, 0(r23)
/* 074F80 8007A520 7C00F9D6 */  mullw   r0, r0, r31
/* 074F84 8007A524 7C030214 */  add     r0, r3, r0
/* 074F88 8007A528 90170000 */  stw     r0, 0(r23)
/* 074F8C 8007A52C A8180000 */  lha     r0, 0(r24)
/* 074F90 8007A530 7C190050 */  subf    r0, r25, r0
/* 074F94 8007A534 B0180000 */  sth     r0, 0(r24)
/* 074F98 8007A538 480001D8 */  b       lbl_8007A710
lbl_8007A53C:
/* 074F9C 8007A53C 7C073050 */  subf    r0, r7, r6
/* 074FA0 8007A540 808D8AC4 */  lwz     r4, imageTop@sda21(r13)
/* 074FA4 8007A544 7C060734 */  extsh   r6, r0
/* 074FA8 8007A548 7CC00735 */  extsh.  r0, r6
/* 074FAC 8007A54C 549E000E */  rlwinm  r30, r4, 0, 0, 7
/* 074FB0 8007A550 7F87F850 */  subf    r28, r7, r31
/* 074FB4 8007A554 40810040 */  ble     lbl_8007A594
/* 074FB8 8007A558 A06D8AC2 */  lhz     r3, imagePtrX0@sda21(r13)
/* 074FBC 8007A55C 54E007FF */  clrlwi. r0, r7, 0x1f
/* 074FC0 8007A560 7CA41A14 */  add     r5, r4, r3
/* 074FC4 8007A564 4182001C */  beq     lbl_8007A580
/* 074FC8 8007A568 A00D8ABE */  lhz     r0, imageSrcWsize@sda21(r13)
/* 074FCC 8007A56C 38E7FFFF */  addi    r7, r7, -1
/* 074FD0 8007A570 38C60001 */  addi    r6, r6, 1
/* 074FD4 8007A574 7CA02850 */  subf    r5, r0, r5
/* 074FD8 8007A578 54A0023E */  clrlwi  r0, r5, 8
/* 074FDC 8007A57C 7FC50378 */  or      r5, r30, r0
lbl_8007A580:
/* 074FE0 8007A580 A10D8ABC */  lhz     r8, tmemSliceWmax@sda21(r13)
/* 074FE4 8007A584 38750000 */  addi    r3, r21, 0
/* 074FE8 8007A588 38960000 */  addi    r4, r22, 0
/* 074FEC 8007A58C 7CE741D6 */  mullw   r7, r7, r8
/* 074FF0 8007A590 48000199 */  bl      tmemLoad_A
lbl_8007A594:
/* 074FF4 8007A594 A00D8AC0 */  lhz     r0, flagSplit@sda21(r13)
/* 074FF8 8007A598 28000000 */  cmplwi  r0, 0
/* 074FFC 8007A59C 41820098 */  beq     lbl_8007A634
/* 075000 8007A5A0 A0CD8ABE */  lhz     r6, imageSrcWsize@sda21(r13)
/* 075004 8007A5A4 57A007FF */  clrlwi. r0, r29, 0x1f
/* 075008 8007A5A8 80770000 */  lwz     r3, 0(r23)
/* 07500C 8007A5AC 389D0000 */  addi    r4, r29, 0
/* 075010 8007A5B0 7C1D31D6 */  mullw   r0, r29, r6
/* 075014 8007A5B4 80AD8AC4 */  lwz     r5, imageTop@sda21(r13)
/* 075018 8007A5B8 7F630214 */  add     r27, r3, r0
/* 07501C 8007A5BC 41820020 */  beq     lbl_8007A5DC
/* 075020 8007A5C0 7CA62850 */  subf    r5, r6, r5
/* 075024 8007A5C4 54A0023E */  clrlwi  r0, r5, 8
/* 075028 8007A5C8 7F66D850 */  subf    r27, r6, r27
/* 07502C 8007A5CC 7FC50378 */  or      r5, r30, r0
/* 075030 8007A5D0 3B400002 */  li      r26, 2
/* 075034 8007A5D4 3884FFFF */  addi    r4, r4, -1
/* 075038 8007A5D8 48000008 */  b       lbl_8007A5E0
lbl_8007A5DC:
/* 07503C 8007A5DC 3B400001 */  li      r26, 1
lbl_8007A5E0:
/* 075040 8007A5E0 A0ED8ABC */  lhz     r7, tmemSliceWmax@sda21(r13)
/* 075044 8007A5E4 7C9E0734 */  extsh   r30, r4
/* 075048 8007A5E8 A08D8AC2 */  lhz     r4, imagePtrX0@sda21(r13)
/* 07504C 8007A5EC 38750000 */  addi    r3, r21, 0
/* 075050 8007A5F0 7C1E39D6 */  mullw   r0, r30, r7
/* 075054 8007A5F4 7C843050 */  subf    r4, r4, r6
/* 075058 8007A5F8 7C841E70 */  srawi   r4, r4, 3
/* 07505C 8007A5FC 7C940734 */  extsh   r20, r4
/* 075060 8007A600 7D143850 */  subf    r8, r20, r7
/* 075064 8007A604 38960000 */  addi    r4, r22, 0
/* 075068 8007A608 38DA0000 */  addi    r6, r26, 0
/* 07506C 8007A60C 7CF40214 */  add     r7, r20, r0
/* 075070 8007A610 48000119 */  bl      tmemLoad_A
/* 075074 8007A614 A00D8ABC */  lhz     r0, tmemSliceWmax@sda21(r13)
/* 075078 8007A618 38750000 */  addi    r3, r21, 0
/* 07507C 8007A61C 38960000 */  addi    r4, r22, 0
/* 075080 8007A620 7CFE01D6 */  mullw   r7, r30, r0
/* 075084 8007A624 38BB0000 */  addi    r5, r27, 0
/* 075088 8007A628 38DA0000 */  addi    r6, r26, 0
/* 07508C 8007A62C 39140000 */  addi    r8, r20, 0
/* 075090 8007A630 480000F9 */  bl      tmemLoad_A
lbl_8007A634:
/* 075094 8007A634 7FA00735 */  extsh.  r0, r29
/* 075098 8007A638 40810024 */  ble     lbl_8007A65C
/* 07509C 8007A63C 80B70000 */  lwz     r5, 0(r23)
/* 0750A0 8007A640 7EA3AB78 */  mr      r3, r21
/* 0750A4 8007A644 A90D8ABC */  lha     r8, tmemSliceWmax@sda21(r13)
/* 0750A8 8007A648 38960000 */  addi    r4, r22, 0
/* 0750AC 8007A64C 38DD0000 */  addi    r6, r29, 0
/* 0750B0 8007A650 38E00000 */  li      r7, 0
/* 0750B4 8007A654 480000D5 */  bl      tmemLoad_A
/* 0750B8 8007A658 4800005C */  b       lbl_8007A6B4
lbl_8007A65C:
/* 0750BC 8007A65C 3CD50004 */  addis   r6, r21, 4
/* 0750C0 8007A660 38000002 */  li      r0, 2
/* 0750C4 8007A664 9006C48C */  stw     r0, -0x3b74(r6)
/* 0750C8 8007A668 38A00000 */  li      r5, 0
/* 0750CC 8007A66C 38750000 */  addi    r3, r21, 0
/* 0750D0 8007A670 90A6C490 */  stw     r5, -0x3b70(r6)
/* 0750D4 8007A674 38800001 */  li      r4, 1
/* 0750D8 8007A678 90A6C494 */  stw     r5, -0x3b6c(r6)
/* 0750DC 8007A67C A00D8ABC */  lhz     r0, tmemSliceWmax@sda21(r13)
/* 0750E0 8007A680 9006C498 */  stw     r0, -0x3b68(r6)
/* 0750E4 8007A684 90A6C49C */  stw     r5, -0x3b64(r6)
/* 0750E8 8007A688 B0A6C4A0 */  sth     r5, -0x3b60(r6)
/* 0750EC 8007A68C B0A6C4A2 */  sth     r5, -0x3b5e(r6)
/* 0750F0 8007A690 B0A6C4A4 */  sth     r5, -0x3b5c(r6)
/* 0750F4 8007A694 B0A6C4A6 */  sth     r5, -0x3b5a(r6)
/* 0750F8 8007A698 B0A6C4A8 */  sth     r5, -0x3b58(r6)
/* 0750FC 8007A69C B0A6C4AA */  sth     r5, -0x3b56(r6)
/* 075100 8007A6A0 4BFA5C5D */  bl      frameDrawReset
/* 075104 8007A6A4 2C030000 */  cmpwi   r3, 0
/* 075108 8007A6A8 4082000C */  bne     lbl_8007A6B4
/* 07510C 8007A6AC 38600000 */  li      r3, 0
/* 075110 8007A6B0 48000064 */  b       lbl_8007A714
lbl_8007A6B4:
/* 075114 8007A6B4 A8180000 */  lha     r0, 0(r24)
/* 075118 8007A6B8 7C190050 */  subf    r0, r25, r0
/* 07511C 8007A6BC B0180000 */  sth     r0, 0(r24)
/* 075120 8007A6C0 A8180000 */  lha     r0, 0(r24)
/* 075124 8007A6C4 2C000000 */  cmpwi   r0, 0
/* 075128 8007A6C8 4081001C */  ble     lbl_8007A6E4
/* 07512C 8007A6CC A00D8ABE */  lhz     r0, imageSrcWsize@sda21(r13)
/* 075130 8007A6D0 80770000 */  lwz     r3, 0(r23)
/* 075134 8007A6D4 7C00F9D6 */  mullw   r0, r0, r31
/* 075138 8007A6D8 7C030214 */  add     r0, r3, r0
/* 07513C 8007A6DC 90170000 */  stw     r0, 0(r23)
/* 075140 8007A6E0 48000030 */  b       lbl_8007A710
lbl_8007A6E4:
/* 075144 8007A6E4 A80D8AC8 */  lha     r0, tmemSrcLines@sda21(r13)
/* 075148 8007A6E8 7F830734 */  extsh   r3, r28
/* 07514C 8007A6EC 7C030050 */  subf    r0, r3, r0
/* 075150 8007A6F0 B0180000 */  sth     r0, 0(r24)
/* 075154 8007A6F4 A00D8ABE */  lhz     r0, imageSrcWsize@sda21(r13)
/* 075158 8007A6F8 A08D8AC2 */  lhz     r4, imagePtrX0@sda21(r13)
/* 07515C 8007A6FC 7C0301D6 */  mullw   r0, r3, r0
/* 075160 8007A700 806D8AC4 */  lwz     r3, imageTop@sda21(r13)
/* 075164 8007A704 7C002214 */  add     r0, r0, r4
/* 075168 8007A708 7C030214 */  add     r0, r3, r0
/* 07516C 8007A70C 90170000 */  stw     r0, 0(r23)
lbl_8007A710:
/* 075170 8007A710 38600001 */  li      r3, 1
lbl_8007A714:
/* 075174 8007A714 BA810020 */  lmw     r20, 0x20(r1)
/* 075178 8007A718 80010054 */  lwz     r0, 0x54(r1)
/* 07517C 8007A71C 38210050 */  addi    r1, r1, 0x50
/* 075180 8007A720 7C0803A6 */  mtlr    r0
/* 075184 8007A724 4E800020 */  blr     
