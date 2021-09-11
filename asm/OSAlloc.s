# OSAlloc.c
.include "macros.inc"

.section .text, "ax"

.balign 4

DLInsert:
/* 097878 8009CE18 38E30000 */  addi    r7, r3, 0
/* 09787C 8009CE1C 38C00000 */  li      r6, 0
/* 097880 8009CE20 48000014 */  b       lbl_8009CE34
lbl_8009CE24:
/* 097884 8009CE24 7C043840 */  cmplw   r4, r7
/* 097888 8009CE28 40810014 */  ble     lbl_8009CE3C
/* 09788C 8009CE2C 7CE63B78 */  mr      r6, r7
/* 097890 8009CE30 80E70004 */  lwz     r7, 4(r7)
lbl_8009CE34:
/* 097894 8009CE34 28070000 */  cmplwi  r7, 0
/* 097898 8009CE38 4082FFEC */  bne     lbl_8009CE24
lbl_8009CE3C:
/* 09789C 8009CE3C 90E40004 */  stw     r7, 4(r4)
/* 0978A0 8009CE40 28070000 */  cmplwi  r7, 0
/* 0978A4 8009CE44 90C40000 */  stw     r6, 0(r4)
/* 0978A8 8009CE48 41820038 */  beq     lbl_8009CE80
/* 0978AC 8009CE4C 90870000 */  stw     r4, 0(r7)
/* 0978B0 8009CE50 80A40008 */  lwz     r5, 8(r4)
/* 0978B4 8009CE54 7C042A14 */  add     r0, r4, r5
/* 0978B8 8009CE58 7C003840 */  cmplw   r0, r7
/* 0978BC 8009CE5C 40820024 */  bne     lbl_8009CE80
/* 0978C0 8009CE60 80070008 */  lwz     r0, 8(r7)
/* 0978C4 8009CE64 7C050214 */  add     r0, r5, r0
/* 0978C8 8009CE68 90040008 */  stw     r0, 8(r4)
/* 0978CC 8009CE6C 80E70004 */  lwz     r7, 4(r7)
/* 0978D0 8009CE70 28070000 */  cmplwi  r7, 0
/* 0978D4 8009CE74 90E40004 */  stw     r7, 4(r4)
/* 0978D8 8009CE78 41820008 */  beq     lbl_8009CE80
/* 0978DC 8009CE7C 90870000 */  stw     r4, 0(r7)
lbl_8009CE80:
/* 0978E0 8009CE80 28060000 */  cmplwi  r6, 0
/* 0978E4 8009CE84 41820038 */  beq     lbl_8009CEBC
/* 0978E8 8009CE88 90860004 */  stw     r4, 4(r6)
/* 0978EC 8009CE8C 80A60008 */  lwz     r5, 8(r6)
/* 0978F0 8009CE90 7C062A14 */  add     r0, r6, r5
/* 0978F4 8009CE94 7C002040 */  cmplw   r0, r4
/* 0978F8 8009CE98 4C820020 */  bnelr   
/* 0978FC 8009CE9C 80040008 */  lwz     r0, 8(r4)
/* 097900 8009CEA0 28070000 */  cmplwi  r7, 0
/* 097904 8009CEA4 7C050214 */  add     r0, r5, r0
/* 097908 8009CEA8 90060008 */  stw     r0, 8(r6)
/* 09790C 8009CEAC 90E60004 */  stw     r7, 4(r6)
/* 097910 8009CEB0 4D820020 */  beqlr   
/* 097914 8009CEB4 90C70000 */  stw     r6, 0(r7)
/* 097918 8009CEB8 4E800020 */  blr     
lbl_8009CEBC:
/* 09791C 8009CEBC 7C832378 */  mr      r3, r4
/* 097920 8009CEC0 4E800020 */  blr     

glabel OSAllocFromHeap
/* 097924 8009CEC4 1C03000C */  mulli   r0, r3, 0xc
/* 097928 8009CEC8 806D8B18 */  lwz     r3, HeapArray-_SDA_BASE_(r13)
/* 09792C 8009CECC 7CA30214 */  add     r5, r3, r0
/* 097930 8009CED0 3804003F */  addi    r0, r4, 0x3f
/* 097934 8009CED4 80C50004 */  lwz     r6, 4(r5)
/* 097938 8009CED8 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 09793C 8009CEDC 48000014 */  b       lbl_8009CEF0
lbl_8009CEE0:
/* 097940 8009CEE0 80060008 */  lwz     r0, 8(r6)
/* 097944 8009CEE4 7C030000 */  cmpw    r3, r0
/* 097948 8009CEE8 40810010 */  ble     lbl_8009CEF8
/* 09794C 8009CEEC 80C60004 */  lwz     r6, 4(r6)
lbl_8009CEF0:
/* 097950 8009CEF0 28060000 */  cmplwi  r6, 0
/* 097954 8009CEF4 4082FFEC */  bne     lbl_8009CEE0
lbl_8009CEF8:
/* 097958 8009CEF8 28060000 */  cmplwi  r6, 0
/* 09795C 8009CEFC 4082000C */  bne     lbl_8009CF08
/* 097960 8009CF00 38600000 */  li      r3, 0
/* 097964 8009CF04 4E800020 */  blr     
lbl_8009CF08:
/* 097968 8009CF08 80060008 */  lwz     r0, 8(r6)
/* 09796C 8009CF0C 7C030050 */  subf    r0, r3, r0
/* 097970 8009CF10 28000040 */  cmplwi  r0, 0x40
/* 097974 8009CF14 40800040 */  bge     lbl_8009CF54
/* 097978 8009CF18 80860004 */  lwz     r4, 4(r6)
/* 09797C 8009CF1C 80650004 */  lwz     r3, 4(r5)
/* 097980 8009CF20 28040000 */  cmplwi  r4, 0
/* 097984 8009CF24 4182000C */  beq     lbl_8009CF30
/* 097988 8009CF28 80060000 */  lwz     r0, 0(r6)
/* 09798C 8009CF2C 90040000 */  stw     r0, 0(r4)
lbl_8009CF30:
/* 097990 8009CF30 80860000 */  lwz     r4, 0(r6)
/* 097994 8009CF34 28040000 */  cmplwi  r4, 0
/* 097998 8009CF38 4082000C */  bne     lbl_8009CF44
/* 09799C 8009CF3C 80660004 */  lwz     r3, 4(r6)
/* 0979A0 8009CF40 4800000C */  b       lbl_8009CF4C
lbl_8009CF44:
/* 0979A4 8009CF44 80060004 */  lwz     r0, 4(r6)
/* 0979A8 8009CF48 90040004 */  stw     r0, 4(r4)
lbl_8009CF4C:
/* 0979AC 8009CF4C 90650004 */  stw     r3, 4(r5)
/* 0979B0 8009CF50 48000048 */  b       lbl_8009CF98
lbl_8009CF54:
/* 0979B4 8009CF54 90660008 */  stw     r3, 8(r6)
/* 0979B8 8009CF58 7C861A14 */  add     r4, r6, r3
/* 0979BC 8009CF5C 90040008 */  stw     r0, 8(r4)
/* 0979C0 8009CF60 80060000 */  lwz     r0, 0(r6)
/* 0979C4 8009CF64 90040000 */  stw     r0, 0(r4)
/* 0979C8 8009CF68 80060004 */  lwz     r0, 4(r6)
/* 0979CC 8009CF6C 90040004 */  stw     r0, 4(r4)
/* 0979D0 8009CF70 80640004 */  lwz     r3, 4(r4)
/* 0979D4 8009CF74 28030000 */  cmplwi  r3, 0
/* 0979D8 8009CF78 41820008 */  beq     lbl_8009CF80
/* 0979DC 8009CF7C 90830000 */  stw     r4, 0(r3)
lbl_8009CF80:
/* 0979E0 8009CF80 80640000 */  lwz     r3, 0(r4)
/* 0979E4 8009CF84 28030000 */  cmplwi  r3, 0
/* 0979E8 8009CF88 4182000C */  beq     lbl_8009CF94
/* 0979EC 8009CF8C 90830004 */  stw     r4, 4(r3)
/* 0979F0 8009CF90 48000008 */  b       lbl_8009CF98
lbl_8009CF94:
/* 0979F4 8009CF94 90850004 */  stw     r4, 4(r5)
lbl_8009CF98:
/* 0979F8 8009CF98 80650008 */  lwz     r3, 8(r5)
/* 0979FC 8009CF9C 38000000 */  li      r0, 0
/* 097A00 8009CFA0 90660004 */  stw     r3, 4(r6)
/* 097A04 8009CFA4 28030000 */  cmplwi  r3, 0
/* 097A08 8009CFA8 90060000 */  stw     r0, 0(r6)
/* 097A0C 8009CFAC 41820008 */  beq     lbl_8009CFB4
/* 097A10 8009CFB0 90C30000 */  stw     r6, 0(r3)
lbl_8009CFB4:
/* 097A14 8009CFB4 90C50008 */  stw     r6, 8(r5)
/* 097A18 8009CFB8 38660020 */  addi    r3, r6, 0x20
/* 097A1C 8009CFBC 4E800020 */  blr     

glabel OSFreeToHeap
/* 097A20 8009CFC0 7C0802A6 */  mflr    r0
/* 097A24 8009CFC4 38C4FFE0 */  addi    r6, r4, -32
/* 097A28 8009CFC8 90010004 */  stw     r0, 4(r1)
/* 097A2C 8009CFCC 1C03000C */  mulli   r0, r3, 0xc
/* 097A30 8009CFD0 9421FFE8 */  stwu    r1, -0x18(r1)
/* 097A34 8009CFD4 93E10014 */  stw     r31, 0x14(r1)
/* 097A38 8009CFD8 808D8B18 */  lwz     r4, HeapArray-_SDA_BASE_(r13)
/* 097A3C 8009CFDC 80660004 */  lwz     r3, 4(r6)
/* 097A40 8009CFE0 7FE40214 */  add     r31, r4, r0
/* 097A44 8009CFE4 28030000 */  cmplwi  r3, 0
/* 097A48 8009CFE8 80BF0008 */  lwz     r5, 8(r31)
/* 097A4C 8009CFEC 7CC43378 */  mr      r4, r6
/* 097A50 8009CFF0 4182000C */  beq     lbl_8009CFFC
/* 097A54 8009CFF4 80040000 */  lwz     r0, 0(r4)
/* 097A58 8009CFF8 90030000 */  stw     r0, 0(r3)
lbl_8009CFFC:
/* 097A5C 8009CFFC 80640000 */  lwz     r3, 0(r4)
/* 097A60 8009D000 28030000 */  cmplwi  r3, 0
/* 097A64 8009D004 4082000C */  bne     lbl_8009D010
/* 097A68 8009D008 80A40004 */  lwz     r5, 4(r4)
/* 097A6C 8009D00C 4800000C */  b       lbl_8009D018
lbl_8009D010:
/* 097A70 8009D010 80040004 */  lwz     r0, 4(r4)
/* 097A74 8009D014 90030004 */  stw     r0, 4(r3)
lbl_8009D018:
/* 097A78 8009D018 90BF0008 */  stw     r5, 8(r31)
/* 097A7C 8009D01C 807F0004 */  lwz     r3, 4(r31)
/* 097A80 8009D020 4BFFFDF9 */  bl      DLInsert
/* 097A84 8009D024 907F0004 */  stw     r3, 4(r31)
/* 097A88 8009D028 8001001C */  lwz     r0, 0x1c(r1)
/* 097A8C 8009D02C 83E10014 */  lwz     r31, 0x14(r1)
/* 097A90 8009D030 38210018 */  addi    r1, r1, 0x18
/* 097A94 8009D034 7C0803A6 */  mtlr    r0
/* 097A98 8009D038 4E800020 */  blr     

glabel OSSetCurrentHeap
/* 097A9C 8009D03C 800D8740 */  lwz     r0, __OSCurrHeap-_SDA_BASE_(r13)
/* 097AA0 8009D040 906D8740 */  stw     r3, __OSCurrHeap-_SDA_BASE_(r13)
/* 097AA4 8009D044 7C030378 */  mr      r3, r0
/* 097AA8 8009D048 4E800020 */  blr     

glabel OSInitAlloc
/* 097AAC 8009D04C 1CE5000C */  mulli   r7, r5, 0xc
/* 097AB0 8009D050 906D8B18 */  stw     r3, HeapArray-_SDA_BASE_(r13)
/* 097AB4 8009D054 90AD8B1C */  stw     r5, NumHeaps-_SDA_BASE_(r13)
/* 097AB8 8009D058 38C00000 */  li      r6, 0
/* 097ABC 8009D05C 38660000 */  addi    r3, r6, 0
/* 097AC0 8009D060 39000000 */  li      r8, 0
/* 097AC4 8009D064 38A0FFFF */  li      r5, -1
/* 097AC8 8009D068 48000020 */  b       lbl_8009D088
lbl_8009D06C:
/* 097ACC 8009D06C 800D8B18 */  lwz     r0, HeapArray-_SDA_BASE_(r13)
/* 097AD0 8009D070 39080001 */  addi    r8, r8, 1
/* 097AD4 8009D074 7D203214 */  add     r9, r0, r6
/* 097AD8 8009D078 90A90000 */  stw     r5, 0(r9)
/* 097ADC 8009D07C 38C6000C */  addi    r6, r6, 0xc
/* 097AE0 8009D080 90690008 */  stw     r3, 8(r9)
/* 097AE4 8009D084 90690004 */  stw     r3, 4(r9)
lbl_8009D088:
/* 097AE8 8009D088 800D8B1C */  lwz     r0, NumHeaps-_SDA_BASE_(r13)
/* 097AEC 8009D08C 7C080000 */  cmpw    r8, r0
/* 097AF0 8009D090 4180FFDC */  blt     lbl_8009D06C
/* 097AF4 8009D094 806D8B18 */  lwz     r3, HeapArray-_SDA_BASE_(r13)
/* 097AF8 8009D098 54800034 */  rlwinm  r0, r4, 0, 0, 0x1a
/* 097AFC 8009D09C 3880FFFF */  li      r4, -1
/* 097B00 8009D0A0 900D8B24 */  stw     r0, ArenaEnd-_SDA_BASE_(r13)
/* 097B04 8009D0A4 7C633A14 */  add     r3, r3, r7
/* 097B08 8009D0A8 3803001F */  addi    r0, r3, 0x1f
/* 097B0C 8009D0AC 908D8740 */  stw     r4, __OSCurrHeap-_SDA_BASE_(r13)
/* 097B10 8009D0B0 54030034 */  rlwinm  r3, r0, 0, 0, 0x1a
/* 097B14 8009D0B4 906D8B20 */  stw     r3, ArenaStart-_SDA_BASE_(r13)
/* 097B18 8009D0B8 4E800020 */  blr     

glabel OSCreateHeap
/* 097B1C 8009D0BC 80CD8B1C */  lwz     r6, NumHeaps-_SDA_BASE_(r13)
/* 097B20 8009D0C0 3803001F */  addi    r0, r3, 0x1f
/* 097B24 8009D0C4 80AD8B18 */  lwz     r5, HeapArray-_SDA_BASE_(r13)
/* 097B28 8009D0C8 54070034 */  rlwinm  r7, r0, 0, 0, 0x1a
/* 097B2C 8009D0CC 2C060000 */  cmpwi   r6, 0
/* 097B30 8009D0D0 7CC903A6 */  mtctr   r6
/* 097B34 8009D0D4 54840034 */  rlwinm  r4, r4, 0, 0, 0x1a
/* 097B38 8009D0D8 38600000 */  li      r3, 0
/* 097B3C 8009D0DC 40810044 */  ble     lbl_8009D120
lbl_8009D0E0:
/* 097B40 8009D0E0 80050000 */  lwz     r0, 0(r5)
/* 097B44 8009D0E4 2C000000 */  cmpwi   r0, 0
/* 097B48 8009D0E8 4080002C */  bge     lbl_8009D114
/* 097B4C 8009D0EC 7C072050 */  subf    r0, r7, r4
/* 097B50 8009D0F0 90050000 */  stw     r0, 0(r5)
/* 097B54 8009D0F4 38800000 */  li      r4, 0
/* 097B58 8009D0F8 90870000 */  stw     r4, 0(r7)
/* 097B5C 8009D0FC 90870004 */  stw     r4, 4(r7)
/* 097B60 8009D100 80050000 */  lwz     r0, 0(r5)
/* 097B64 8009D104 90070008 */  stw     r0, 8(r7)
/* 097B68 8009D108 90E50004 */  stw     r7, 4(r5)
/* 097B6C 8009D10C 90850008 */  stw     r4, 8(r5)
/* 097B70 8009D110 4E800020 */  blr     
lbl_8009D114:
/* 097B74 8009D114 38A5000C */  addi    r5, r5, 0xc
/* 097B78 8009D118 38630001 */  addi    r3, r3, 1
/* 097B7C 8009D11C 4200FFC4 */  bdnz    lbl_8009D0E0
lbl_8009D120:
/* 097B80 8009D120 3860FFFF */  li      r3, -1
/* 097B84 8009D124 4E800020 */  blr     

glabel OSCheckHeap
/* 097B88 8009D128 7C0802A6 */  mflr    r0
/* 097B8C 8009D12C 3C80800F */  lis     r4, D_800F0830@ha
/* 097B90 8009D130 90010004 */  stw     r0, 4(r1)
/* 097B94 8009D134 38C40830 */  addi    r6, r4, D_800F0830@l
/* 097B98 8009D138 38000000 */  li      r0, 0
/* 097B9C 8009D13C 9421FFF8 */  stwu    r1, -8(r1)
/* 097BA0 8009D140 38800000 */  li      r4, 0
/* 097BA4 8009D144 80ED8B18 */  lwz     r7, HeapArray-_SDA_BASE_(r13)
/* 097BA8 8009D148 28070000 */  cmplwi  r7, 0
/* 097BAC 8009D14C 4082001C */  bne     lbl_8009D168
/* 097BB0 8009D150 38660000 */  addi    r3, r6, 0
/* 097BB4 8009D154 4CC63182 */  crclr   6
/* 097BB8 8009D158 3880037D */  li      r4, 0x37d
/* 097BBC 8009D15C 4800149D */  bl      OSReport
/* 097BC0 8009D160 3860FFFF */  li      r3, -1
/* 097BC4 8009D164 48000314 */  b       lbl_8009D478
lbl_8009D168:
/* 097BC8 8009D168 2C030000 */  cmpwi   r3, 0
/* 097BCC 8009D16C 41800010 */  blt     lbl_8009D17C
/* 097BD0 8009D170 80AD8B1C */  lwz     r5, NumHeaps-_SDA_BASE_(r13)
/* 097BD4 8009D174 7C032800 */  cmpw    r3, r5
/* 097BD8 8009D178 4180001C */  blt     lbl_8009D194
lbl_8009D17C:
/* 097BDC 8009D17C 38660024 */  addi    r3, r6, 0x24
/* 097BE0 8009D180 4CC63182 */  crclr   6
/* 097BE4 8009D184 3880037E */  li      r4, 0x37e
/* 097BE8 8009D188 48001471 */  bl      OSReport
/* 097BEC 8009D18C 3860FFFF */  li      r3, -1
/* 097BF0 8009D190 480002E8 */  b       lbl_8009D478
lbl_8009D194:
/* 097BF4 8009D194 1C63000C */  mulli   r3, r3, 0xc
/* 097BF8 8009D198 7CA71A14 */  add     r5, r7, r3
/* 097BFC 8009D19C 80650000 */  lwz     r3, 0(r5)
/* 097C00 8009D1A0 2C030000 */  cmpwi   r3, 0
/* 097C04 8009D1A4 4080001C */  bge     lbl_8009D1C0
/* 097C08 8009D1A8 3866005C */  addi    r3, r6, 0x5c
/* 097C0C 8009D1AC 4CC63182 */  crclr   6
/* 097C10 8009D1B0 38800381 */  li      r4, 0x381
/* 097C14 8009D1B4 48001445 */  bl      OSReport
/* 097C18 8009D1B8 3860FFFF */  li      r3, -1
/* 097C1C 8009D1BC 480002BC */  b       lbl_8009D478
lbl_8009D1C0:
/* 097C20 8009D1C0 80E50008 */  lwz     r7, 8(r5)
/* 097C24 8009D1C4 28070000 */  cmplwi  r7, 0
/* 097C28 8009D1C8 41820028 */  beq     lbl_8009D1F0
/* 097C2C 8009D1CC 80670000 */  lwz     r3, 0(r7)
/* 097C30 8009D1D0 28030000 */  cmplwi  r3, 0
/* 097C34 8009D1D4 4182001C */  beq     lbl_8009D1F0
/* 097C38 8009D1D8 38660084 */  addi    r3, r6, 0x84
/* 097C3C 8009D1DC 4CC63182 */  crclr   6
/* 097C40 8009D1E0 38800383 */  li      r4, 0x383
/* 097C44 8009D1E4 48001415 */  bl      OSReport
/* 097C48 8009D1E8 3860FFFF */  li      r3, -1
/* 097C4C 8009D1EC 4800028C */  b       lbl_8009D478
lbl_8009D1F0:
/* 097C50 8009D1F0 812D8B20 */  lwz     r9, ArenaStart-_SDA_BASE_(r13)
/* 097C54 8009D1F4 7CE83B78 */  mr      r8, r7
/* 097C58 8009D1F8 814D8B24 */  lwz     r10, ArenaEnd-_SDA_BASE_(r13)
/* 097C5C 8009D1FC 480000F0 */  b       lbl_8009D2EC
lbl_8009D200:
/* 097C60 8009D200 7C094040 */  cmplw   r9, r8
/* 097C64 8009D204 4181000C */  bgt     lbl_8009D210
/* 097C68 8009D208 7C085040 */  cmplw   r8, r10
/* 097C6C 8009D20C 4180001C */  blt     lbl_8009D228
lbl_8009D210:
/* 097C70 8009D210 386600D4 */  addi    r3, r6, 0xd4
/* 097C74 8009D214 4CC63182 */  crclr   6
/* 097C78 8009D218 38800386 */  li      r4, 0x386
/* 097C7C 8009D21C 480013DD */  bl      OSReport
/* 097C80 8009D220 3860FFFF */  li      r3, -1
/* 097C84 8009D224 48000254 */  b       lbl_8009D478
lbl_8009D228:
/* 097C88 8009D228 550306FF */  clrlwi. r3, r8, 0x1b
/* 097C8C 8009D22C 4182001C */  beq     lbl_8009D248
/* 097C90 8009D230 38660114 */  addi    r3, r6, 0x114
/* 097C94 8009D234 4CC63182 */  crclr   6
/* 097C98 8009D238 38800387 */  li      r4, 0x387
/* 097C9C 8009D23C 480013BD */  bl      OSReport
/* 097CA0 8009D240 3860FFFF */  li      r3, -1
/* 097CA4 8009D244 48000234 */  b       lbl_8009D478
lbl_8009D248:
/* 097CA8 8009D248 80E80004 */  lwz     r7, 4(r8)
/* 097CAC 8009D24C 28070000 */  cmplwi  r7, 0
/* 097CB0 8009D250 41820028 */  beq     lbl_8009D278
/* 097CB4 8009D254 80670000 */  lwz     r3, 0(r7)
/* 097CB8 8009D258 7C034040 */  cmplw   r3, r8
/* 097CBC 8009D25C 4182001C */  beq     lbl_8009D278
/* 097CC0 8009D260 3866014C */  addi    r3, r6, 0x14c
/* 097CC4 8009D264 4CC63182 */  crclr   6
/* 097CC8 8009D268 38800388 */  li      r4, 0x388
/* 097CCC 8009D26C 4800138D */  bl      OSReport
/* 097CD0 8009D270 3860FFFF */  li      r3, -1
/* 097CD4 8009D274 48000204 */  b       lbl_8009D478
lbl_8009D278:
/* 097CD8 8009D278 81080008 */  lwz     r8, 8(r8)
/* 097CDC 8009D27C 28080040 */  cmplwi  r8, 0x40
/* 097CE0 8009D280 4080001C */  bge     lbl_8009D29C
/* 097CE4 8009D284 38660198 */  addi    r3, r6, 0x198
/* 097CE8 8009D288 4CC63182 */  crclr   6
/* 097CEC 8009D28C 38800389 */  li      r4, 0x389
/* 097CF0 8009D290 48001369 */  bl      OSReport
/* 097CF4 8009D294 3860FFFF */  li      r3, -1
/* 097CF8 8009D298 480001E0 */  b       lbl_8009D478
lbl_8009D29C:
/* 097CFC 8009D29C 550306FF */  clrlwi. r3, r8, 0x1b
/* 097D00 8009D2A0 4182001C */  beq     lbl_8009D2BC
/* 097D04 8009D2A4 386601CC */  addi    r3, r6, 0x1cc
/* 097D08 8009D2A8 4CC63182 */  crclr   6
/* 097D0C 8009D2AC 3880038A */  li      r4, 0x38a
/* 097D10 8009D2B0 48001349 */  bl      OSReport
/* 097D14 8009D2B4 3860FFFF */  li      r3, -1
/* 097D18 8009D2B8 480001C0 */  b       lbl_8009D478
lbl_8009D2BC:
/* 097D1C 8009D2BC 7C004215 */  add.    r0, r0, r8
/* 097D20 8009D2C0 40810010 */  ble     lbl_8009D2D0
/* 097D24 8009D2C4 80650000 */  lwz     r3, 0(r5)
/* 097D28 8009D2C8 7C001800 */  cmpw    r0, r3
/* 097D2C 8009D2CC 4081001C */  ble     lbl_8009D2E8
lbl_8009D2D0:
/* 097D30 8009D2D0 3866020C */  addi    r3, r6, 0x20c
/* 097D34 8009D2D4 4CC63182 */  crclr   6
/* 097D38 8009D2D8 3880038D */  li      r4, 0x38d
/* 097D3C 8009D2DC 4800131D */  bl      OSReport
/* 097D40 8009D2E0 3860FFFF */  li      r3, -1
/* 097D44 8009D2E4 48000194 */  b       lbl_8009D478
lbl_8009D2E8:
/* 097D48 8009D2E8 7CE83B78 */  mr      r8, r7
lbl_8009D2EC:
/* 097D4C 8009D2EC 28080000 */  cmplwi  r8, 0
/* 097D50 8009D2F0 4082FF10 */  bne     lbl_8009D200
/* 097D54 8009D2F4 81650004 */  lwz     r11, 4(r5)
/* 097D58 8009D2F8 280B0000 */  cmplwi  r11, 0
/* 097D5C 8009D2FC 4182014C */  beq     lbl_8009D448
/* 097D60 8009D300 806B0000 */  lwz     r3, 0(r11)
/* 097D64 8009D304 28030000 */  cmplwi  r3, 0
/* 097D68 8009D308 41820140 */  beq     lbl_8009D448
/* 097D6C 8009D30C 38660248 */  addi    r3, r6, 0x248
/* 097D70 8009D310 4CC63182 */  crclr   6
/* 097D74 8009D314 38800395 */  li      r4, 0x395
/* 097D78 8009D318 480012E1 */  bl      OSReport
/* 097D7C 8009D31C 3860FFFF */  li      r3, -1
/* 097D80 8009D320 48000158 */  b       lbl_8009D478
/* 097D84 8009D324 48000124 */  b       lbl_8009D448
lbl_8009D328:
/* 097D88 8009D328 7C095840 */  cmplw   r9, r11
/* 097D8C 8009D32C 4181000C */  bgt     lbl_8009D338
/* 097D90 8009D330 7C0B5040 */  cmplw   r11, r10
/* 097D94 8009D334 4180001C */  blt     lbl_8009D350
lbl_8009D338:
/* 097D98 8009D338 386600D4 */  addi    r3, r6, 0xd4
/* 097D9C 8009D33C 4CC63182 */  crclr   6
/* 097DA0 8009D340 38800398 */  li      r4, 0x398
/* 097DA4 8009D344 480012B5 */  bl      OSReport
/* 097DA8 8009D348 3860FFFF */  li      r3, -1
/* 097DAC 8009D34C 4800012C */  b       lbl_8009D478
lbl_8009D350:
/* 097DB0 8009D350 556306FF */  clrlwi. r3, r11, 0x1b
/* 097DB4 8009D354 4182001C */  beq     lbl_8009D370
/* 097DB8 8009D358 38660114 */  addi    r3, r6, 0x114
/* 097DBC 8009D35C 4CC63182 */  crclr   6
/* 097DC0 8009D360 38800399 */  li      r4, 0x399
/* 097DC4 8009D364 48001295 */  bl      OSReport
/* 097DC8 8009D368 3860FFFF */  li      r3, -1
/* 097DCC 8009D36C 4800010C */  b       lbl_8009D478
lbl_8009D370:
/* 097DD0 8009D370 80EB0004 */  lwz     r7, 4(r11)
/* 097DD4 8009D374 28070000 */  cmplwi  r7, 0
/* 097DD8 8009D378 41820028 */  beq     lbl_8009D3A0
/* 097DDC 8009D37C 80670000 */  lwz     r3, 0(r7)
/* 097DE0 8009D380 7C035840 */  cmplw   r3, r11
/* 097DE4 8009D384 4182001C */  beq     lbl_8009D3A0
/* 097DE8 8009D388 3866014C */  addi    r3, r6, 0x14c
/* 097DEC 8009D38C 4CC63182 */  crclr   6
/* 097DF0 8009D390 3880039A */  li      r4, 0x39a
/* 097DF4 8009D394 48001265 */  bl      OSReport
/* 097DF8 8009D398 3860FFFF */  li      r3, -1
/* 097DFC 8009D39C 480000DC */  b       lbl_8009D478
lbl_8009D3A0:
/* 097E00 8009D3A0 810B0008 */  lwz     r8, 8(r11)
/* 097E04 8009D3A4 28080040 */  cmplwi  r8, 0x40
/* 097E08 8009D3A8 4080001C */  bge     lbl_8009D3C4
/* 097E0C 8009D3AC 38660198 */  addi    r3, r6, 0x198
/* 097E10 8009D3B0 4CC63182 */  crclr   6
/* 097E14 8009D3B4 3880039B */  li      r4, 0x39b
/* 097E18 8009D3B8 48001241 */  bl      OSReport
/* 097E1C 8009D3BC 3860FFFF */  li      r3, -1
/* 097E20 8009D3C0 480000B8 */  b       lbl_8009D478
lbl_8009D3C4:
/* 097E24 8009D3C4 550306FF */  clrlwi. r3, r8, 0x1b
/* 097E28 8009D3C8 4182001C */  beq     lbl_8009D3E4
/* 097E2C 8009D3CC 386601CC */  addi    r3, r6, 0x1cc
/* 097E30 8009D3D0 4CC63182 */  crclr   6
/* 097E34 8009D3D4 3880039C */  li      r4, 0x39c
/* 097E38 8009D3D8 48001221 */  bl      OSReport
/* 097E3C 8009D3DC 3860FFFF */  li      r3, -1
/* 097E40 8009D3E0 48000098 */  b       lbl_8009D478
lbl_8009D3E4:
/* 097E44 8009D3E4 28070000 */  cmplwi  r7, 0
/* 097E48 8009D3E8 41820028 */  beq     lbl_8009D410
/* 097E4C 8009D3EC 7C6B4214 */  add     r3, r11, r8
/* 097E50 8009D3F0 7C033840 */  cmplw   r3, r7
/* 097E54 8009D3F4 4180001C */  blt     lbl_8009D410
/* 097E58 8009D3F8 38660290 */  addi    r3, r6, 0x290
/* 097E5C 8009D3FC 4CC63182 */  crclr   6
/* 097E60 8009D400 3880039D */  li      r4, 0x39d
/* 097E64 8009D404 480011F5 */  bl      OSReport
/* 097E68 8009D408 3860FFFF */  li      r3, -1
/* 097E6C 8009D40C 4800006C */  b       lbl_8009D478
lbl_8009D410:
/* 097E70 8009D410 7C004215 */  add.    r0, r0, r8
/* 097E74 8009D414 7C882214 */  add     r4, r8, r4
/* 097E78 8009D418 3884FFE0 */  addi    r4, r4, -32
/* 097E7C 8009D41C 40810010 */  ble     lbl_8009D42C
/* 097E80 8009D420 80650000 */  lwz     r3, 0(r5)
/* 097E84 8009D424 7C001800 */  cmpw    r0, r3
/* 097E88 8009D428 4081001C */  ble     lbl_8009D444
lbl_8009D42C:
/* 097E8C 8009D42C 3866020C */  addi    r3, r6, 0x20c
/* 097E90 8009D430 4CC63182 */  crclr   6
/* 097E94 8009D434 388003A1 */  li      r4, 0x3a1
/* 097E98 8009D438 480011C1 */  bl      OSReport
/* 097E9C 8009D43C 3860FFFF */  li      r3, -1
/* 097EA0 8009D440 48000038 */  b       lbl_8009D478
lbl_8009D444:
/* 097EA4 8009D444 7CEB3B78 */  mr      r11, r7
lbl_8009D448:
/* 097EA8 8009D448 280B0000 */  cmplwi  r11, 0
/* 097EAC 8009D44C 4082FEDC */  bne     lbl_8009D328
/* 097EB0 8009D450 80650000 */  lwz     r3, 0(r5)
/* 097EB4 8009D454 7C001800 */  cmpw    r0, r3
/* 097EB8 8009D458 4182001C */  beq     lbl_8009D474
/* 097EBC 8009D45C 386602F0 */  addi    r3, r6, 0x2f0
/* 097EC0 8009D460 4CC63182 */  crclr   6
/* 097EC4 8009D464 388003A8 */  li      r4, 0x3a8
/* 097EC8 8009D468 48001191 */  bl      OSReport
/* 097ECC 8009D46C 3860FFFF */  li      r3, -1
/* 097ED0 8009D470 48000008 */  b       lbl_8009D478
lbl_8009D474:
/* 097ED4 8009D474 7C832378 */  mr      r3, r4
lbl_8009D478:
/* 097ED8 8009D478 8001000C */  lwz     r0, 0xc(r1)
/* 097EDC 8009D47C 38210008 */  addi    r1, r1, 8
/* 097EE0 8009D480 7C0803A6 */  mtlr    r0
/* 097EE4 8009D484 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000ED8B0 800F0830 0024 */
D_800F0830:
    .asciz "OSCheckHeap: Failed HeapArray in %d"
    .balign 4

/* 000ED8D4 800F0854 0037 */
D_800F0854:
    .asciz "OSCheckHeap: Failed 0 <= heap && heap < NumHeaps in %d"
    .balign 4

/* 000ED90C 800F088C 0028 */
D_800F088C:
    .asciz "OSCheckHeap: Failed 0 <= hd->size in %d"
    .balign 4

/* 000ED934 800F08B4 004F */
D_800F08B4:
    .asciz "OSCheckHeap: Failed hd->allocated == NULL || hd->allocated->prev == NULL in %d"
    .balign 4

/* 000ED984 800F0904 003E */
D_800F0904:
    .asciz "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d"
    .balign 4

/* 000ED9C4 800F0944 0037 */
D_800F0944:
    .asciz "OSCheckHeap: Failed OFFSET(cell, ALIGNMENT) == 0 in %d"
    .balign 4

/* 000ED9FC 800F097C 0049 */
D_800F097C:
    .asciz "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d"
    .balign 4

/* 000EDA48 800F09C8 0033 */
D_800F09C8:
    .asciz "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d"
    .balign 4

/* 000EDA7C 800F09FC 003D */
D_800F09FC:
    .asciz "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d"
    .balign 4

/* 000EDABC 800F0A3C 0039 */
D_800F0A3C:
    .asciz "OSCheckHeap: Failed 0 < total && total <= hd->size in %d"
    .balign 4

/* 000EDAF8 800F0A78 0045 */
D_800F0A78:
    .asciz "OSCheckHeap: Failed hd->free == NULL || hd->free->prev == NULL in %d"
    .balign 4

/* 000EDB40 800F0AC0 005F */
D_800F0AC0:
    .asciz "OSCheckHeap: Failed cell->next == NULL || (char*) cell + cell->size < (char*) cell->next in %d"
    .balign 4

/* 000EDBA0 800F0B20 002C */
D_800F0B20:
    .asciz "OSCheckHeap: Failed total == hd->size in %d"
    .balign 4

/* 000EDBCC 800F0B4C 0012 */
D_800F0B4C:
    .asciz "\nOSDumpHeap(%d):\n"
    .balign 4

/* 000EDBE0 800F0B60 0012 */
D_800F0B60:
    .asciz "--------Inactive\n"
    .balign 4

/* 000EDBF4 800F0B74 001A */
D_800F0B74:
    .asciz "addr\tsize\t\tend\tprev\tnext\n"
    .balign 4

/* 000EDC10 800F0B90 0013 */
D_800F0B90:
    .asciz "--------Allocated\n"
    .balign 4

/* 000EDC24 800F0BA4 0010 */
D_800F0BA4:
    .asciz "%x\t%d\t%x\t%x\t%x\n"
    .balign 4

/* 000EDC34 800F0BB4 000E */
D_800F0BB4:
    .asciz "--------Free\n"
    .balign 4

.section .sdata, "wa"

.balign 8

/* 000F16A0 80135420 0004 */
glabel __OSCurrHeap
    .long 0xFFFFFFFF

.section .sbss, "wa"

.balign 8

/* 000F1A78 801357F8 0004 */
HeapArray:
    .skip 4

/* 000F1A7C 801357FC 0004 */
NumHeaps:
    .skip 4

/* 000F1A80 80135800 0004 */
ArenaStart:
    .skip 4

/* 000F1A84 80135804 0004 */
ArenaEnd:
    .skip 4
