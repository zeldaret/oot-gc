glabel frameLoadTexture
/* 024F08 8002A4A8 7C0802A6 */  mflr    r0
/* 024F0C 8002A4AC 90010004 */  stw     r0, 4(r1)
/* 024F10 8002A4B0 9421FFC0 */  stwu    r1, -0x40(r1)
/* 024F14 8002A4B4 BF410028 */  stmw    r26, 0x28(r1)
/* 024F18 8002A4B8 7C7A1B78 */  mr      r26, r3
/* 024F1C 8002A4BC 7C9B2378 */  mr      r27, r4
/* 024F20 8002A4C0 801A0088 */  lwz     r0, 0x88(r26)
/* 024F24 8002A4C4 3C60800F */  lis     r3, D_800EA838@ha
/* 024F28 8002A4C8 3BE3A838 */  addi    r31, r3, D_800EA838@l
/* 024F2C 8002A4CC 901B000C */  stw     r0, 0xc(r27)
/* 024F30 8002A4D0 7CBE2670 */  srawi   r30, r5, 4
/* 024F34 8002A4D4 A8660018 */  lha     r3, 0x18(r6)
/* 024F38 8002A4D8 546007BC */  rlwinm  r0, r3, 0, 0x1e, 0x1e
/* 024F3C 8002A4DC 2C000000 */  cmpwi   r0, 0
/* 024F40 8002A4E0 40820010 */  bne     lbl_8002A4F0
/* 024F44 8002A4E4 A8060014 */  lha     r0, 0x14(r6)
/* 024F48 8002A4E8 2C000000 */  cmpwi   r0, 0
/* 024F4C 8002A4EC 4082001C */  bne     lbl_8002A508
lbl_8002A4F0:
/* 024F50 8002A4F0 801B0000 */  lwz     r0, 0(r27)
/* 024F54 8002A4F4 540007FE */  clrlwi  r0, r0, 0x1f
/* 024F58 8002A4F8 2C000000 */  cmpwi   r0, 0
/* 024F5C 8002A4FC 4082000C */  bne     lbl_8002A508
/* 024F60 8002A500 3BA00000 */  li      r29, 0
/* 024F64 8002A504 4800001C */  b       lbl_8002A520
lbl_8002A508:
/* 024F68 8002A508 546007FE */  clrlwi  r0, r3, 0x1f
/* 024F6C 8002A50C 2C000000 */  cmpwi   r0, 0
/* 024F70 8002A510 4182000C */  beq     lbl_8002A51C
/* 024F74 8002A514 3BA00002 */  li      r29, 2
/* 024F78 8002A518 48000008 */  b       lbl_8002A520
lbl_8002A51C:
/* 024F7C 8002A51C 3BA00001 */  li      r29, 1
lbl_8002A520:
/* 024F80 8002A520 A866001A */  lha     r3, 0x1a(r6)
/* 024F84 8002A524 546007BC */  rlwinm  r0, r3, 0, 0x1e, 0x1e
/* 024F88 8002A528 2C000000 */  cmpwi   r0, 0
/* 024F8C 8002A52C 40820010 */  bne     lbl_8002A53C
/* 024F90 8002A530 A8060016 */  lha     r0, 0x16(r6)
/* 024F94 8002A534 2C000000 */  cmpwi   r0, 0
/* 024F98 8002A538 4082001C */  bne     lbl_8002A554
lbl_8002A53C:
/* 024F9C 8002A53C 801B0000 */  lwz     r0, 0(r27)
/* 024FA0 8002A540 540007BC */  rlwinm  r0, r0, 0, 0x1e, 0x1e
/* 024FA4 8002A544 2C000000 */  cmpwi   r0, 0
/* 024FA8 8002A548 4082000C */  bne     lbl_8002A554
/* 024FAC 8002A54C 3B800000 */  li      r28, 0
/* 024FB0 8002A550 4800001C */  b       lbl_8002A56C
lbl_8002A554:
/* 024FB4 8002A554 546007FE */  clrlwi  r0, r3, 0x1f
/* 024FB8 8002A558 2C000000 */  cmpwi   r0, 0
/* 024FBC 8002A55C 4182000C */  beq     lbl_8002A568
/* 024FC0 8002A560 3B800002 */  li      r28, 2
/* 024FC4 8002A564 48000008 */  b       lbl_8002A56C
lbl_8002A568:
/* 024FC8 8002A568 3B800001 */  li      r28, 1
lbl_8002A56C:
/* 024FCC 8002A56C 801B0064 */  lwz     r0, 0x64(r27)
/* 024FD0 8002A570 7C00E800 */  cmpw    r0, r29
/* 024FD4 8002A574 40820010 */  bne     lbl_8002A584
/* 024FD8 8002A578 801B0068 */  lwz     r0, 0x68(r27)
/* 024FDC 8002A57C 7C00E000 */  cmpw    r0, r28
/* 024FE0 8002A580 418200FC */  beq     lbl_8002A67C
lbl_8002A584:
/* 024FE4 8002A584 93BB0064 */  stw     r29, 0x64(r27)
/* 024FE8 8002A588 939B0068 */  stw     r28, 0x68(r27)
/* 024FEC 8002A58C 80BB0034 */  lwz     r5, 0x34(r27)
/* 024FF0 8002A590 2C050008 */  cmpwi   r5, 8
/* 024FF4 8002A594 4182000C */  beq     lbl_8002A5A0
/* 024FF8 8002A598 2C050009 */  cmpwi   r5, 9
/* 024FFC 8002A59C 4082009C */  bne     lbl_8002A638
lbl_8002A5A0:
/* 025000 8002A5A0 801B0008 */  lwz     r0, 8(r27)
/* 025004 8002A5A4 2C00FFFF */  cmpwi   r0, -1
/* 025008 8002A5A8 4082000C */  bne     lbl_8002A5B4
/* 02500C 8002A5AC 38800000 */  li      r4, 0
/* 025010 8002A5B0 48000014 */  b       lbl_8002A5C4
lbl_8002A5B4:
/* 025014 8002A5B4 5400043E */  clrlwi  r0, r0, 0x10
/* 025018 8002A5B8 807A1C1C */  lwz     r3, 0x1c1c(r26)
/* 02501C 8002A5BC 54002834 */  slwi    r0, r0, 5
/* 025020 8002A5C0 7C830214 */  add     r4, r3, r0
lbl_8002A5C4:
/* 025024 8002A5C4 2C050008 */  cmpwi   r5, 8
/* 025028 8002A5C8 4082000C */  bne     lbl_8002A5D4
/* 02502C 8002A5CC 38000010 */  li      r0, 0x10
/* 025030 8002A5D0 48000008 */  b       lbl_8002A5D8
lbl_8002A5D4:
/* 025034 8002A5D4 38000100 */  li      r0, 0x100
lbl_8002A5D8:
/* 025038 8002A5D8 387B0038 */  addi    r3, r27, 0x38
/* 02503C 8002A5DC 5406043E */  clrlwi  r6, r0, 0x10
/* 025040 8002A5E0 38A00002 */  li      r5, 2
/* 025044 8002A5E4 480827A9 */  bl      GXInitTlutObj
/* 025048 8002A5E8 801B0004 */  lwz     r0, 4(r27)
/* 02504C 8002A5EC 2C00FFFF */  cmpwi   r0, -1
/* 025050 8002A5F0 4082000C */  bne     lbl_8002A5FC
/* 025054 8002A5F4 38800000 */  li      r4, 0
/* 025058 8002A5F8 48000014 */  b       lbl_8002A60C
lbl_8002A5FC:
/* 02505C 8002A5FC 5400043E */  clrlwi  r0, r0, 0x10
/* 025060 8002A600 807A1C18 */  lwz     r3, 0x1c18(r26)
/* 025064 8002A604 54005828 */  slwi    r0, r0, 0xb
/* 025068 8002A608 7C830214 */  add     r4, r3, r0
lbl_8002A60C:
/* 02506C 8002A60C 38000000 */  li      r0, 0
/* 025070 8002A610 90010008 */  stw     r0, 8(r1)
/* 025074 8002A614 7FA8EB78 */  mr      r8, r29
/* 025078 8002A618 7F89E378 */  mr      r9, r28
/* 02507C 8002A61C A0BB0010 */  lhz     r5, 0x10(r27)
/* 025080 8002A620 387B0044 */  addi    r3, r27, 0x44
/* 025084 8002A624 A0DB0012 */  lhz     r6, 0x12(r27)
/* 025088 8002A628 39400000 */  li      r10, 0
/* 02508C 8002A62C 80FB0034 */  lwz     r7, 0x34(r27)
/* 025090 8002A630 480823B5 */  bl      GXInitTexObjCI
/* 025094 8002A634 48000048 */  b       lbl_8002A67C
lbl_8002A638:
/* 025098 8002A638 801B0004 */  lwz     r0, 4(r27)
/* 02509C 8002A63C 2C00FFFF */  cmpwi   r0, -1
/* 0250A0 8002A640 4082000C */  bne     lbl_8002A64C
/* 0250A4 8002A644 38800000 */  li      r4, 0
/* 0250A8 8002A648 48000014 */  b       lbl_8002A65C
lbl_8002A64C:
/* 0250AC 8002A64C 5400043E */  clrlwi  r0, r0, 0x10
/* 0250B0 8002A650 807A1C18 */  lwz     r3, 0x1c18(r26)
/* 0250B4 8002A654 54005828 */  slwi    r0, r0, 0xb
/* 0250B8 8002A658 7C830214 */  add     r4, r3, r0
lbl_8002A65C:
/* 0250BC 8002A65C A0BB0010 */  lhz     r5, 0x10(r27)
/* 0250C0 8002A660 7FA8EB78 */  mr      r8, r29
/* 0250C4 8002A664 A0DB0012 */  lhz     r6, 0x12(r27)
/* 0250C8 8002A668 7F89E378 */  mr      r9, r28
/* 0250CC 8002A66C 80FB0034 */  lwz     r7, 0x34(r27)
/* 0250D0 8002A670 387B0044 */  addi    r3, r27, 0x44
/* 0250D4 8002A674 39400000 */  li      r10, 0
/* 0250D8 8002A678 48082121 */  bl      GXInitTexObj
lbl_8002A67C:
/* 0250DC 8002A67C 801A00A4 */  lwz     r0, 0xa4(r26)
/* 0250E0 8002A680 807B0000 */  lwz     r3, 0(r27)
/* 0250E4 8002A684 540404A6 */  rlwinm  r4, r0, 0, 0x12, 0x13
/* 0250E8 8002A688 546004A6 */  rlwinm  r0, r3, 0, 0x12, 0x13
/* 0250EC 8002A68C 7C002000 */  cmpw    r0, r4
/* 0250F0 8002A690 418200A0 */  beq     lbl_8002A730
/* 0250F4 8002A694 54600522 */  rlwinm  r0, r3, 0, 0x14, 0x11
/* 0250F8 8002A698 901B0000 */  stw     r0, 0(r27)
/* 0250FC 8002A69C 2C042000 */  cmpwi   r4, 0x2000
/* 025100 8002A6A0 801B0000 */  lwz     r0, 0(r27)
/* 025104 8002A6A4 7C002378 */  or      r0, r0, r4
/* 025108 8002A6A8 901B0000 */  stw     r0, 0(r27)
/* 02510C 8002A6AC 4182004C */  beq     lbl_8002A6F8
/* 025110 8002A6B0 40800010 */  bge     lbl_8002A6C0
/* 025114 8002A6B4 2C040000 */  cmpwi   r4, 0
/* 025118 8002A6B8 41820014 */  beq     lbl_8002A6CC
/* 02511C 8002A6BC 48000068 */  b       lbl_8002A724
lbl_8002A6C0:
/* 025120 8002A6C0 2C043000 */  cmpwi   r4, 0x3000
/* 025124 8002A6C4 41820034 */  beq     lbl_8002A6F8
/* 025128 8002A6C8 4800005C */  b       lbl_8002A724
lbl_8002A6CC:
/* 02512C 8002A6CC C0228100 */  lfs     f1, D_80135E00@sda21(r2)
/* 025130 8002A6D0 387B0044 */  addi    r3, r27, 0x44
/* 025134 8002A6D4 38800000 */  li      r4, 0
/* 025138 8002A6D8 FC400890 */  fmr     f2, f1
/* 02513C 8002A6DC 38A00000 */  li      r5, 0
/* 025140 8002A6E0 FC600890 */  fmr     f3, f1
/* 025144 8002A6E4 38C00000 */  li      r6, 0
/* 025148 8002A6E8 38E00000 */  li      r7, 0
/* 02514C 8002A6EC 39000000 */  li      r8, 0
/* 025150 8002A6F0 4808233D */  bl      GXInitTexObjLOD
/* 025154 8002A6F4 4800003C */  b       lbl_8002A730
lbl_8002A6F8:
/* 025158 8002A6F8 C0228100 */  lfs     f1, D_80135E00@sda21(r2)
/* 02515C 8002A6FC 387B0044 */  addi    r3, r27, 0x44
/* 025160 8002A700 38800001 */  li      r4, 1
/* 025164 8002A704 FC400890 */  fmr     f2, f1
/* 025168 8002A708 38A00001 */  li      r5, 1
/* 02516C 8002A70C FC600890 */  fmr     f3, f1
/* 025170 8002A710 38C00000 */  li      r6, 0
/* 025174 8002A714 38E00000 */  li      r7, 0
/* 025178 8002A718 39000000 */  li      r8, 0
/* 02517C 8002A71C 48082311 */  bl      GXInitTexObjLOD
/* 025180 8002A720 48000010 */  b       lbl_8002A730
lbl_8002A724:
/* 025184 8002A724 4CC63182 */  crclr   6
/* 025188 8002A728 387F0A74 */  addi    r3, r31, 0xa74
/* 02518C 8002A72C 48073ECD */  bl      OSReport
lbl_8002A730:
/* 025190 8002A730 801B0034 */  lwz     r0, 0x34(r27)
/* 025194 8002A734 2C000008 */  cmpwi   r0, 8
/* 025198 8002A738 4182000C */  beq     lbl_8002A744
/* 02519C 8002A73C 2C000009 */  cmpwi   r0, 9
/* 0251A0 8002A740 40820018 */  bne     lbl_8002A758
lbl_8002A744:
/* 0251A4 8002A744 57C0103A */  slwi    r0, r30, 2
/* 0251A8 8002A748 7C7F0214 */  add     r3, r31, r0
/* 0251AC 8002A74C 80830020 */  lwz     r4, 0x20(r3)
/* 0251B0 8002A750 387B0038 */  addi    r3, r27, 0x38
/* 0251B4 8002A754 48082671 */  bl      GXLoadTlut
lbl_8002A758:
/* 0251B8 8002A758 57C0103A */  slwi    r0, r30, 2
/* 0251BC 8002A75C 7C7F0214 */  add     r3, r31, r0
/* 0251C0 8002A760 80830040 */  lwz     r4, 0x40(r3)
/* 0251C4 8002A764 387B0044 */  addi    r3, r27, 0x44
/* 0251C8 8002A768 480825D1 */  bl      GXLoadTexObj
/* 0251CC 8002A76C 38600001 */  li      r3, 1
/* 0251D0 8002A770 BB410028 */  lmw     r26, 0x28(r1)
/* 0251D4 8002A774 80010044 */  lwz     r0, 0x44(r1)
/* 0251D8 8002A778 38210040 */  addi    r1, r1, 0x40
/* 0251DC 8002A77C 7C0803A6 */  mtlr    r0
/* 0251E0 8002A780 4E800020 */  blr     
