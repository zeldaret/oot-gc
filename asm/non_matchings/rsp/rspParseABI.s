glabel rspParseABI
/* 0835A8 80088B48 7C0802A6 */  mflr    r0
/* 0835AC 80088B4C 90010004 */  stw     r0, 4(r1)
/* 0835B0 80088B50 9421FFD8 */  stwu    r1, -0x28(r1)
/* 0835B4 80088B54 93E10024 */  stw     r31, 0x24(r1)
/* 0835B8 80088B58 3BE40000 */  addi    r31, r4, 0
/* 0835BC 80088B5C 93C10020 */  stw     r30, 0x20(r1)
/* 0835C0 80088B60 7C7E1B78 */  mr      r30, r3
/* 0835C4 80088B64 800338D0 */  lwz     r0, 0x38d0(r3)
/* 0835C8 80088B68 2C000000 */  cmpwi   r0, 0
/* 0835CC 80088B6C 41820184 */  beq     lbl_80088CF0
/* 0835D0 80088B70 2C000001 */  cmpwi   r0, 1
/* 0835D4 80088B74 4182017C */  beq     lbl_80088CF0
/* 0835D8 80088B78 2C000004 */  cmpwi   r0, 4
/* 0835DC 80088B7C 41820174 */  beq     lbl_80088CF0
/* 0835E0 80088B80 807E38E8 */  lwz     r3, 0x38e8(r30)
/* 0835E4 80088B84 3881001C */  addi    r4, r1, 0x1c
/* 0835E8 80088B88 80BF0010 */  lwz     r5, 0x10(r31)
/* 0835EC 80088B8C 38C00000 */  li      r6, 0
/* 0835F0 80088B90 8063002C */  lwz     r3, 0x2c(r3)
/* 0835F4 80088B94 4BFE450D */  bl      ramGetBuffer
/* 0835F8 80088B98 2C030000 */  cmpwi   r3, 0
/* 0835FC 80088B9C 4082000C */  bne     lbl_80088BA8
/* 083600 80088BA0 38600000 */  li      r3, 0
/* 083604 80088BA4 480001B8 */  b       lbl_80088D5C
lbl_80088BA8:
/* 083608 80088BA8 80A1001C */  lwz     r5, 0x1c(r1)
/* 08360C 80088BAC 88850000 */  lbz     r4, 0(r5)
/* 083610 80088BB0 88050001 */  lbz     r0, 1(r5)
/* 083614 80088BB4 88650002 */  lbz     r3, 2(r5)
/* 083618 80088BB8 7C840214 */  add     r4, r4, r0
/* 08361C 80088BBC 88050003 */  lbz     r0, 3(r5)
/* 083620 80088BC0 7C841A14 */  add     r4, r4, r3
/* 083624 80088BC4 88650004 */  lbz     r3, 4(r5)
/* 083628 80088BC8 7C840214 */  add     r4, r4, r0
/* 08362C 80088BCC 88050005 */  lbz     r0, 5(r5)
/* 083630 80088BD0 7C841A14 */  add     r4, r4, r3
/* 083634 80088BD4 88650006 */  lbz     r3, 6(r5)
/* 083638 80088BD8 7C840214 */  add     r4, r4, r0
/* 08363C 80088BDC 88050007 */  lbz     r0, 7(r5)
/* 083640 80088BE0 7C841A14 */  add     r4, r4, r3
/* 083644 80088BE4 7C840214 */  add     r4, r4, r0
/* 083648 80088BE8 2C040171 */  cmpwi   r4, 0x171
/* 08364C 80088BEC 4182002C */  beq     lbl_80088C18
/* 083650 80088BF0 4080001C */  bge     lbl_80088C0C
/* 083654 80088BF4 2C040151 */  cmpwi   r4, 0x151
/* 083658 80088BF8 41820088 */  beq     lbl_80088C80
/* 08365C 80088BFC 408000EC */  bge     lbl_80088CE8
/* 083660 80088C00 2C040131 */  cmpwi   r4, 0x131
/* 083664 80088C04 418200B0 */  beq     lbl_80088CB4
/* 083668 80088C08 480000E0 */  b       lbl_80088CE8
lbl_80088C0C:
/* 08366C 80088C0C 2C0401F4 */  cmpwi   r4, 0x1f4
/* 083670 80088C10 4182003C */  beq     lbl_80088C4C
/* 083674 80088C14 480000D4 */  b       lbl_80088CE8
lbl_80088C18:
/* 083678 80088C18 38000000 */  li      r0, 0
/* 08367C 80088C1C 901E38D0 */  stw     r0, 0x38d0(r30)
/* 083680 80088C20 380005C0 */  li      r0, 0x5c0
/* 083684 80088C24 386004C0 */  li      r3, 0x4c0
/* 083688 80088C28 B01E38D4 */  sth     r0, 0x38d4(r30)
/* 08368C 80088C2C 38800360 */  li      r4, 0x360
/* 083690 80088C30 38000F90 */  li      r0, 0xf90
/* 083694 80088C34 B07E38D6 */  sth     r3, 0x38d6(r30)
/* 083698 80088C38 7FC3F378 */  mr      r3, r30
/* 08369C 80088C3C B09E38DA */  sth     r4, 0x38da(r30)
/* 0836A0 80088C40 B01E38D8 */  sth     r0, 0x38d8(r30)
/* 0836A4 80088C44 48002F99 */  bl      rspInitAudioDMEM1
/* 0836A8 80088C48 480000A8 */  b       lbl_80088CF0
lbl_80088C4C:
/* 0836AC 80088C4C 38000001 */  li      r0, 1
/* 0836B0 80088C50 901E38D0 */  stw     r0, 0x38d0(r30)
/* 0836B4 80088C54 380003B0 */  li      r0, 0x3b0
/* 0836B8 80088C58 38600330 */  li      r3, 0x330
/* 0836BC 80088C5C B01E38D4 */  sth     r0, 0x38d4(r30)
/* 0836C0 80088C60 38800000 */  li      r4, 0
/* 0836C4 80088C64 38000FB0 */  li      r0, 0xfb0
/* 0836C8 80088C68 B07E38D6 */  sth     r3, 0x38d6(r30)
/* 0836CC 80088C6C 7FC3F378 */  mr      r3, r30
/* 0836D0 80088C70 B09E38DA */  sth     r4, 0x38da(r30)
/* 0836D4 80088C74 B01E38D8 */  sth     r0, 0x38d8(r30)
/* 0836D8 80088C78 4BFFE8A9 */  bl      rspInitAudioDMEM2
/* 0836DC 80088C7C 48000074 */  b       lbl_80088CF0
lbl_80088C80:
/* 0836E0 80088C80 38000002 */  li      r0, 2
/* 0836E4 80088C84 901E38D0 */  stw     r0, 0x38d0(r30)
/* 0836E8 80088C88 38000450 */  li      r0, 0x450
/* 0836EC 80088C8C 386003D0 */  li      r3, 0x3d0
/* 0836F0 80088C90 B01E38D4 */  sth     r0, 0x38d4(r30)
/* 0836F4 80088C94 38800330 */  li      r4, 0x330
/* 0836F8 80088C98 38000FA0 */  li      r0, 0xfa0
/* 0836FC 80088C9C B07E38D6 */  sth     r3, 0x38d6(r30)
/* 083700 80088CA0 7FC3F378 */  mr      r3, r30
/* 083704 80088CA4 B09E38DA */  sth     r4, 0x38da(r30)
/* 083708 80088CA8 B01E38D8 */  sth     r0, 0x38d8(r30)
/* 08370C 80088CAC 4BFFA1B5 */  bl      rspInitAudioDMEM3
/* 083710 80088CB0 48000040 */  b       lbl_80088CF0
lbl_80088CB4:
/* 083714 80088CB4 38000003 */  li      r0, 3
/* 083718 80088CB8 901E38D0 */  stw     r0, 0x38d0(r30)
/* 08371C 80088CBC 38000450 */  li      r0, 0x450
/* 083720 80088CC0 386003C0 */  li      r3, 0x3c0
/* 083724 80088CC4 B01E38D4 */  sth     r0, 0x38d4(r30)
/* 083728 80088CC8 38800320 */  li      r4, 0x320
/* 08372C 80088CCC 38000F90 */  li      r0, 0xf90
/* 083730 80088CD0 B07E38D6 */  sth     r3, 0x38d6(r30)
/* 083734 80088CD4 7FC3F378 */  mr      r3, r30
/* 083738 80088CD8 B09E38DA */  sth     r4, 0x38da(r30)
/* 08373C 80088CDC B01E38D8 */  sth     r0, 0x38d8(r30)
/* 083740 80088CE0 4BFF84E1 */  bl      rspInitAudioDMEM4
/* 083744 80088CE4 4800000C */  b       lbl_80088CF0
lbl_80088CE8:
/* 083748 80088CE8 38000004 */  li      r0, 4
/* 08374C 80088CEC 901E38D0 */  stw     r0, 0x38d0(r30)
lbl_80088CF0:
/* 083750 80088CF0 801E38D0 */  lwz     r0, 0x38d0(r30)
/* 083754 80088CF4 2C000002 */  cmpwi   r0, 2
/* 083758 80088CF8 41820044 */  beq     lbl_80088D3C
/* 08375C 80088CFC 40800014 */  bge     lbl_80088D10
/* 083760 80088D00 2C000000 */  cmpwi   r0, 0
/* 083764 80088D04 41820018 */  beq     lbl_80088D1C
/* 083768 80088D08 40800024 */  bge     lbl_80088D2C
/* 08376C 80088D0C 4800004C */  b       lbl_80088D58
lbl_80088D10:
/* 083770 80088D10 2C000004 */  cmpwi   r0, 4
/* 083774 80088D14 40800044 */  bge     lbl_80088D58
/* 083778 80088D18 48000034 */  b       lbl_80088D4C
lbl_80088D1C:
/* 08377C 80088D1C 387E0000 */  addi    r3, r30, 0
/* 083780 80088D20 389F0000 */  addi    r4, r31, 0
/* 083784 80088D24 4BFFFAC5 */  bl      rspParseABI1
/* 083788 80088D28 48000030 */  b       lbl_80088D58
lbl_80088D2C:
/* 08378C 80088D2C 387E0000 */  addi    r3, r30, 0
/* 083790 80088D30 389F0000 */  addi    r4, r31, 0
/* 083794 80088D34 4BFFB569 */  bl      rspParseABI2
/* 083798 80088D38 48000020 */  b       lbl_80088D58
lbl_80088D3C:
/* 08379C 80088D3C 387E0000 */  addi    r3, r30, 0
/* 0837A0 80088D40 389F0000 */  addi    r4, r31, 0
/* 0837A4 80088D44 4BFF98E1 */  bl      rspParseABI3
/* 0837A8 80088D48 48000010 */  b       lbl_80088D58
lbl_80088D4C:
/* 0837AC 80088D4C 387E0000 */  addi    r3, r30, 0
/* 0837B0 80088D50 389F0000 */  addi    r4, r31, 0
/* 0837B4 80088D54 4BFF7D51 */  bl      rspParseABI4
lbl_80088D58:
/* 0837B8 80088D58 38600001 */  li      r3, 1
lbl_80088D5C:
/* 0837BC 80088D5C 8001002C */  lwz     r0, 0x2c(r1)
/* 0837C0 80088D60 83E10024 */  lwz     r31, 0x24(r1)
/* 0837C4 80088D64 83C10020 */  lwz     r30, 0x20(r1)
/* 0837C8 80088D68 7C0803A6 */  mtlr    r0
/* 0837CC 80088D6C 38210028 */  addi    r1, r1, 0x28
/* 0837D0 80088D70 4E800020 */  blr     
