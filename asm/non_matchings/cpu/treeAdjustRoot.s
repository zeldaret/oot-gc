glabel treeAdjustRoot
/* 02CB4C 800320EC 7C0802A6 */  mflr    r0
/* 02CB50 800320F0 90010004 */  stw     r0, 4(r1)
/* 02CB54 800320F4 38000000 */  li      r0, 0
/* 02CB58 800320F8 9421FFB8 */  stwu    r1, -0x48(r1)
/* 02CB5C 800320FC BEC10020 */  stmw    r22, 0x20(r1)
/* 02CB60 80032100 3AE30000 */  addi    r23, r3, 0
/* 02CB64 80032104 3C770001 */  addis   r3, r23, 1
/* 02CB68 80032108 3B050000 */  addi    r24, r5, 0
/* 02CB6C 8003210C 3BD80002 */  addi    r30, r24, 2
/* 02CB70 80032110 3BA00000 */  li      r29, 0
/* 02CB74 80032114 3B800000 */  li      r28, 0
/* 02CB78 80032118 832312A0 */  lwz     r25, 0x12a0(r3)
/* 02CB7C 8003211C 90010018 */  stw     r0, 0x18(r1)
/* 02CB80 80032120 90010014 */  stw     r0, 0x14(r1)
/* 02CB84 80032124 83F90008 */  lwz     r31, 8(r25)
/* 02CB88 80032128 A3790000 */  lhz     r27, 0(r25)
/* 02CB8C 8003212C 83590004 */  lwz     r26, 4(r25)
/* 02CB90 80032130 3ADF0002 */  addi    r22, r31, 2
lbl_80032134:
/* 02CB94 80032134 38000000 */  li      r0, 0
/* 02CB98 80032138 90010018 */  stw     r0, 0x18(r1)
/* 02CB9C 8003213C 38960000 */  addi    r4, r22, 0
/* 02CBA0 80032140 38A10018 */  addi    r5, r1, 0x18
/* 02CBA4 80032144 8079006C */  lwz     r3, 0x6c(r25)
/* 02CBA8 80032148 4BFFFF41 */  bl      treeSearchNode
/* 02CBAC 8003214C 80010018 */  lwz     r0, 0x18(r1)
/* 02CBB0 80032150 28000000 */  cmplwi  r0, 0
/* 02CBB4 80032154 41820154 */  beq     lbl_800322A8
/* 02CBB8 80032158 2C1D0000 */  cmpwi   r29, 0
/* 02CBBC 8003215C 40820008 */  bne     lbl_80032164
/* 02CBC0 80032160 7EDDB378 */  mr      r29, r22
lbl_80032164:
/* 02CBC4 80032164 93D90008 */  stw     r30, 8(r25)
/* 02CBC8 80032168 7EE3BB78 */  mr      r3, r23
/* 02CBCC 8003216C 80A10018 */  lwz     r5, 0x18(r1)
/* 02CBD0 80032170 80850010 */  lwz     r4, 0x10(r5)
/* 02CBD4 80032174 80A50014 */  lwz     r5, 0x14(r5)
/* 02CBD8 80032178 480003E1 */  bl      treeInsert
/* 02CBDC 8003217C 2C030000 */  cmpwi   r3, 0
/* 02CBE0 80032180 4082000C */  bne     lbl_8003218C
/* 02CBE4 80032184 38600000 */  li      r3, 0
/* 02CBE8 80032188 4800013C */  b       lbl_800322C4
lbl_8003218C:
/* 02CBEC 8003218C 80790068 */  lwz     r3, 0x68(r25)
/* 02CBF0 80032190 38960000 */  addi    r4, r22, 0
/* 02CBF4 80032194 38A10014 */  addi    r5, r1, 0x14
/* 02CBF8 80032198 4BFFFEF1 */  bl      treeSearchNode
/* 02CBFC 8003219C 2C030000 */  cmpwi   r3, 0
/* 02CC00 800321A0 4082000C */  bne     lbl_800321AC
/* 02CC04 800321A4 38600000 */  li      r3, 0
/* 02CC08 800321A8 4800011C */  b       lbl_800322C4
lbl_800321AC:
/* 02CC0C 800321AC 80810018 */  lwz     r4, 0x18(r1)
/* 02CC10 800321B0 80610014 */  lwz     r3, 0x14(r1)
/* 02CC14 800321B4 80040028 */  lwz     r0, 0x28(r4)
/* 02CC18 800321B8 90030028 */  stw     r0, 0x28(r3)
/* 02CC1C 800321BC 80810018 */  lwz     r4, 0x18(r1)
/* 02CC20 800321C0 80610014 */  lwz     r3, 0x14(r1)
/* 02CC24 800321C4 8004002C */  lwz     r0, 0x2c(r4)
/* 02CC28 800321C8 9003002C */  stw     r0, 0x2c(r3)
/* 02CC2C 800321CC 80610018 */  lwz     r3, 0x18(r1)
/* 02CC30 800321D0 80830004 */  lwz     r4, 4(r3)
/* 02CC34 800321D4 28040000 */  cmplwi  r4, 0
/* 02CC38 800321D8 41820018 */  beq     lbl_800321F0
/* 02CC3C 800321DC 80610014 */  lwz     r3, 0x14(r1)
/* 02CC40 800321E0 38000000 */  li      r0, 0
/* 02CC44 800321E4 90830004 */  stw     r4, 4(r3)
/* 02CC48 800321E8 80610018 */  lwz     r3, 0x18(r1)
/* 02CC4C 800321EC 90030004 */  stw     r0, 4(r3)
lbl_800321F0:
/* 02CC50 800321F0 80810018 */  lwz     r4, 0x18(r1)
/* 02CC54 800321F4 80610014 */  lwz     r3, 0x14(r1)
/* 02CC58 800321F8 80040008 */  lwz     r0, 8(r4)
/* 02CC5C 800321FC 90030008 */  stw     r0, 8(r3)
/* 02CC60 80032200 80610018 */  lwz     r3, 0x18(r1)
/* 02CC64 80032204 8083000C */  lwz     r4, 0xc(r3)
/* 02CC68 80032208 28040000 */  cmplwi  r4, 0
/* 02CC6C 8003220C 41820018 */  beq     lbl_80032224
/* 02CC70 80032210 80610014 */  lwz     r3, 0x14(r1)
/* 02CC74 80032214 38000000 */  li      r0, 0
/* 02CC78 80032218 9083000C */  stw     r4, 0xc(r3)
/* 02CC7C 8003221C 80610018 */  lwz     r3, 0x18(r1)
/* 02CC80 80032220 9003000C */  stw     r0, 0xc(r3)
lbl_80032224:
/* 02CC84 80032224 80810018 */  lwz     r4, 0x18(r1)
/* 02CC88 80032228 80610014 */  lwz     r3, 0x14(r1)
/* 02CC8C 8003222C 80040024 */  lwz     r0, 0x24(r4)
/* 02CC90 80032230 90030024 */  stw     r0, 0x24(r3)
/* 02CC94 80032234 80810018 */  lwz     r4, 0x18(r1)
/* 02CC98 80032238 80610014 */  lwz     r3, 0x14(r1)
/* 02CC9C 8003223C 80040020 */  lwz     r0, 0x20(r4)
/* 02CCA0 80032240 90030020 */  stw     r0, 0x20(r3)
/* 02CCA4 80032244 80810018 */  lwz     r4, 0x18(r1)
/* 02CCA8 80032248 80610014 */  lwz     r3, 0x14(r1)
/* 02CCAC 8003224C 8004001C */  lwz     r0, 0x1c(r4)
/* 02CCB0 80032250 9003001C */  stw     r0, 0x1c(r3)
/* 02CCB4 80032254 80610018 */  lwz     r3, 0x18(r1)
/* 02CCB8 80032258 8003001C */  lwz     r0, 0x1c(r3)
/* 02CCBC 8003225C 2C000000 */  cmpwi   r0, 0
/* 02CCC0 80032260 4182001C */  beq     lbl_8003227C
/* 02CCC4 80032264 80830018 */  lwz     r4, 0x18(r3)
/* 02CCC8 80032268 38000000 */  li      r0, 0
/* 02CCCC 8003226C 80610014 */  lwz     r3, 0x14(r1)
/* 02CCD0 80032270 90830018 */  stw     r4, 0x18(r3)
/* 02CCD4 80032274 80610018 */  lwz     r3, 0x18(r1)
/* 02CCD8 80032278 90030018 */  stw     r0, 0x18(r3)
lbl_8003227C:
/* 02CCDC 8003227C 80810018 */  lwz     r4, 0x18(r1)
/* 02CCE0 80032280 7EE3BB78 */  mr      r3, r23
/* 02CCE4 80032284 82C40014 */  lwz     r22, 0x14(r4)
/* 02CCE8 80032288 93F90008 */  stw     r31, 8(r25)
/* 02CCEC 8003228C 80A10018 */  lwz     r5, 0x18(r1)
/* 02CCF0 80032290 8099006C */  lwz     r4, 0x6c(r25)
/* 02CCF4 80032294 80C50014 */  lwz     r6, 0x14(r5)
/* 02CCF8 80032298 80A50010 */  lwz     r5, 0x10(r5)
/* 02CCFC 8003229C 38C6FFFC */  addi    r6, r6, -4
/* 02CD00 800322A0 4BFFF651 */  bl      treeKillRange
/* 02CD04 800322A4 7F9C1A14 */  add     r28, r28, r3
lbl_800322A8:
/* 02CD08 800322A8 3AD60004 */  addi    r22, r22, 4
/* 02CD0C 800322AC 7C16C000 */  cmpw    r22, r24
/* 02CD10 800322B0 4081FE84 */  ble     lbl_80032134
/* 02CD14 800322B4 93D90008 */  stw     r30, 8(r25)
/* 02CD18 800322B8 38600001 */  li      r3, 1
/* 02CD1C 800322BC B3790000 */  sth     r27, 0(r25)
/* 02CD20 800322C0 93590004 */  stw     r26, 4(r25)
lbl_800322C4:
/* 02CD24 800322C4 BAC10020 */  lmw     r22, 0x20(r1)
/* 02CD28 800322C8 8001004C */  lwz     r0, 0x4c(r1)
/* 02CD2C 800322CC 38210048 */  addi    r1, r1, 0x48
/* 02CD30 800322D0 7C0803A6 */  mtlr    r0
/* 02CD34 800322D4 4E800020 */  blr     
