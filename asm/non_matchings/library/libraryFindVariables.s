glabel libraryFindVariables
/* 08AADC 8009007C 7C0802A6 */  mflr    r0
/* 08AAE0 80090080 90010004 */  stw     r0, 4(r1)
/* 08AAE4 80090084 9421FFA8 */  stwu    r1, -0x58(r1)
/* 08AAE8 80090088 BEE10034 */  stmw    r23, 0x34(r1)
/* 08AAEC 8009008C 7C781B78 */  mr      r24, r3
/* 08AAF0 80090090 38A1000C */  addi    r5, r1, 0xc
/* 08AAF4 80090094 80630004 */  lwz     r3, 4(r3)
/* 08AAF8 80090098 80980010 */  lwz     r4, 0x10(r24)
/* 08AAFC 8009009C 83630024 */  lwz     r27, 0x24(r3)
/* 08AB00 800900A0 5480843E */  srwi    r0, r4, 0x10
/* 08AB04 800900A4 3B3B0F64 */  addi    r25, r27, 0xf64
/* 08AB08 800900A8 7C1900AE */  lbzx    r0, r25, r0
/* 08AB0C 800900AC 3B5B0B64 */  addi    r26, r27, 0xb64
/* 08AB10 800900B0 5400103A */  slwi    r0, r0, 2
/* 08AB14 800900B4 7C7A002E */  lwzx    r3, r26, r0
/* 08AB18 800900B8 81830014 */  lwz     r12, 0x14(r3)
/* 08AB1C 800900BC 80030008 */  lwz     r0, 8(r3)
/* 08AB20 800900C0 7D8803A6 */  mtlr    r12
/* 08AB24 800900C4 80630004 */  lwz     r3, 4(r3)
/* 08AB28 800900C8 7C840214 */  add     r4, r4, r0
/* 08AB2C 800900CC 4E800021 */  blrl    
/* 08AB30 800900D0 80780010 */  lwz     r3, 0x10(r24)
/* 08AB34 800900D4 3BE10010 */  addi    r31, r1, 0x10
/* 08AB38 800900D8 38BF0000 */  addi    r5, r31, 0
/* 08AB3C 800900DC 38830004 */  addi    r4, r3, 4
/* 08AB40 800900E0 5480843E */  srwi    r0, r4, 0x10
/* 08AB44 800900E4 7C1900AE */  lbzx    r0, r25, r0
/* 08AB48 800900E8 5400103A */  slwi    r0, r0, 2
/* 08AB4C 800900EC 7C7A002E */  lwzx    r3, r26, r0
/* 08AB50 800900F0 81830014 */  lwz     r12, 0x14(r3)
/* 08AB54 800900F4 80030008 */  lwz     r0, 8(r3)
/* 08AB58 800900F8 7D8803A6 */  mtlr    r12
/* 08AB5C 800900FC 80630004 */  lwz     r3, 4(r3)
/* 08AB60 80090100 7C840214 */  add     r4, r4, r0
/* 08AB64 80090104 4E800021 */  blrl    
/* 08AB68 80090108 8081000C */  lwz     r4, 0xc(r1)
/* 08AB6C 8009010C 548036BE */  srwi    r0, r4, 0x1a
/* 08AB70 80090110 2800000F */  cmplwi  r0, 0xf
/* 08AB74 80090114 40820074 */  bne     lbl_80090188
/* 08AB78 80090118 80610010 */  lwz     r3, 0x10(r1)
/* 08AB7C 8009011C 546036BE */  srwi    r0, r3, 0x1a
/* 08AB80 80090120 28000009 */  cmplwi  r0, 9
/* 08AB84 80090124 40820064 */  bne     lbl_80090188
/* 08AB88 80090128 5460043E */  clrlwi  r0, r3, 0x10
/* 08AB8C 8009012C 5483801E */  slwi    r3, r4, 0x10
/* 08AB90 80090130 7C000734 */  extsh   r0, r0
/* 08AB94 80090134 7EE30214 */  add     r23, r3, r0
/* 08AB98 80090138 387B0000 */  addi    r3, r27, 0
/* 08AB9C 8009013C 38B70000 */  addi    r5, r23, 0
/* 08ABA0 80090140 38810028 */  addi    r4, r1, 0x28
/* 08ABA4 80090144 4BFA46B5 */  bl      cpuGetAddressOffset
/* 08ABA8 80090148 2C030000 */  cmpwi   r3, 0
/* 08ABAC 8009014C 4082000C */  bne     lbl_80090158
/* 08ABB0 80090150 38600000 */  li      r3, 0
/* 08ABB4 80090154 48000648 */  b       lbl_8009079C
lbl_80090158:
/* 08ABB8 80090158 66E08000 */  oris    r0, r23, 0x8000
/* 08ABBC 8009015C 90180058 */  stw     r0, 0x58(r24)
/* 08ABC0 80090160 38980030 */  addi    r4, r24, 0x30
/* 08ABC4 80090164 38C00000 */  li      r6, 0
/* 08ABC8 80090168 80780004 */  lwz     r3, 4(r24)
/* 08ABCC 8009016C 80A10028 */  lwz     r5, 0x28(r1)
/* 08ABD0 80090170 8063002C */  lwz     r3, 0x2c(r3)
/* 08ABD4 80090174 4BFDCF2D */  bl      ramGetBuffer
/* 08ABD8 80090178 2C030000 */  cmpwi   r3, 0
/* 08ABDC 8009017C 40820014 */  bne     lbl_80090190
/* 08ABE0 80090180 38600000 */  li      r3, 0
/* 08ABE4 80090184 48000618 */  b       lbl_8009079C
lbl_80090188:
/* 08ABE8 80090188 38600000 */  li      r3, 0
/* 08ABEC 8009018C 48000610 */  b       lbl_8009079C
lbl_80090190:
/* 08ABF0 80090190 80780010 */  lwz     r3, 0x10(r24)
/* 08ABF4 80090194 3BA30008 */  addi    r29, r3, 8
lbl_80090198:
/* 08ABF8 80090198 57A0843E */  srwi    r0, r29, 0x10
/* 08ABFC 8009019C 7C1900AE */  lbzx    r0, r25, r0
/* 08AC00 800901A0 38A10024 */  addi    r5, r1, 0x24
/* 08AC04 800901A4 5400103A */  slwi    r0, r0, 2
/* 08AC08 800901A8 7C7A002E */  lwzx    r3, r26, r0
/* 08AC0C 800901AC 81830014 */  lwz     r12, 0x14(r3)
/* 08AC10 800901B0 80030008 */  lwz     r0, 8(r3)
/* 08AC14 800901B4 7D8803A6 */  mtlr    r12
/* 08AC18 800901B8 80630004 */  lwz     r3, 4(r3)
/* 08AC1C 800901BC 7C9D0214 */  add     r4, r29, r0
/* 08AC20 800901C0 4E800021 */  blrl    
/* 08AC24 800901C4 80610024 */  lwz     r3, 0x24(r1)
/* 08AC28 800901C8 3BBD0004 */  addi    r29, r29, 4
/* 08AC2C 800901CC 3C03FCC0 */  addis   r0, r3, 0xfcc0
/* 08AC30 800901D0 28004021 */  cmplwi  r0, 0x4021
/* 08AC34 800901D4 4182000C */  beq     lbl_800901E0
/* 08AC38 800901D8 28004025 */  cmplwi  r0, 0x4025
/* 08AC3C 800901DC 4082FFBC */  bne     lbl_80090198
lbl_800901E0:
/* 08AC40 800901E0 57A0843E */  srwi    r0, r29, 0x10
/* 08AC44 800901E4 7C1900AE */  lbzx    r0, r25, r0
/* 08AC48 800901E8 38A1000C */  addi    r5, r1, 0xc
/* 08AC4C 800901EC 5400103A */  slwi    r0, r0, 2
/* 08AC50 800901F0 7C7A002E */  lwzx    r3, r26, r0
/* 08AC54 800901F4 81830014 */  lwz     r12, 0x14(r3)
/* 08AC58 800901F8 80030008 */  lwz     r0, 8(r3)
/* 08AC5C 800901FC 7D8803A6 */  mtlr    r12
/* 08AC60 80090200 80630004 */  lwz     r3, 4(r3)
/* 08AC64 80090204 7C9D0214 */  add     r4, r29, r0
/* 08AC68 80090208 4E800021 */  blrl    
/* 08AC6C 8009020C 381D0004 */  addi    r0, r29, 4
/* 08AC70 80090210 5400843E */  srwi    r0, r0, 0x10
/* 08AC74 80090214 7C1900AE */  lbzx    r0, r25, r0
/* 08AC78 80090218 38BF0000 */  addi    r5, r31, 0
/* 08AC7C 8009021C 5400103A */  slwi    r0, r0, 2
/* 08AC80 80090220 7C7A002E */  lwzx    r3, r26, r0
/* 08AC84 80090224 80030008 */  lwz     r0, 8(r3)
/* 08AC88 80090228 81830014 */  lwz     r12, 0x14(r3)
/* 08AC8C 8009022C 7C9D0214 */  add     r4, r29, r0
/* 08AC90 80090230 80630004 */  lwz     r3, 4(r3)
/* 08AC94 80090234 7D8803A6 */  mtlr    r12
/* 08AC98 80090238 38840004 */  addi    r4, r4, 4
/* 08AC9C 8009023C 4E800021 */  blrl    
/* 08ACA0 80090240 381D0008 */  addi    r0, r29, 8
/* 08ACA4 80090244 5400843E */  srwi    r0, r0, 0x10
/* 08ACA8 80090248 7C1900AE */  lbzx    r0, r25, r0
/* 08ACAC 8009024C 3BC10014 */  addi    r30, r1, 0x14
/* 08ACB0 80090250 38BE0000 */  addi    r5, r30, 0
/* 08ACB4 80090254 5400103A */  slwi    r0, r0, 2
/* 08ACB8 80090258 7C7A002E */  lwzx    r3, r26, r0
/* 08ACBC 8009025C 80030008 */  lwz     r0, 8(r3)
/* 08ACC0 80090260 81830014 */  lwz     r12, 0x14(r3)
/* 08ACC4 80090264 7C9D0214 */  add     r4, r29, r0
/* 08ACC8 80090268 80630004 */  lwz     r3, 4(r3)
/* 08ACCC 8009026C 7D8803A6 */  mtlr    r12
/* 08ACD0 80090270 38840008 */  addi    r4, r4, 8
/* 08ACD4 80090274 4E800021 */  blrl    
/* 08ACD8 80090278 8061000C */  lwz     r3, 0xc(r1)
/* 08ACDC 8009027C 3B9D0000 */  addi    r28, r29, 0
/* 08ACE0 80090280 546036BE */  srwi    r0, r3, 0x1a
/* 08ACE4 80090284 2800000F */  cmplwi  r0, 0xf
/* 08ACE8 80090288 4082001C */  bne     lbl_800902A4
/* 08ACEC 8009028C 80010010 */  lwz     r0, 0x10(r1)
/* 08ACF0 80090290 5463801E */  slwi    r3, r3, 0x10
/* 08ACF4 80090294 5400043E */  clrlwi  r0, r0, 0x10
/* 08ACF8 80090298 7C000734 */  extsh   r0, r0
/* 08ACFC 8009029C 7FA30214 */  add     r29, r3, r0
/* 08AD00 800902A0 4800001C */  b       lbl_800902BC
lbl_800902A4:
/* 08AD04 800902A4 80010014 */  lwz     r0, 0x14(r1)
/* 08AD08 800902A8 80610010 */  lwz     r3, 0x10(r1)
/* 08AD0C 800902AC 5400043E */  clrlwi  r0, r0, 0x10
/* 08AD10 800902B0 5463801E */  slwi    r3, r3, 0x10
/* 08AD14 800902B4 7C000734 */  extsh   r0, r0
/* 08AD18 800902B8 7FA30214 */  add     r29, r3, r0
lbl_800902BC:
/* 08AD1C 800902BC 387B0000 */  addi    r3, r27, 0
/* 08AD20 800902C0 38BD0000 */  addi    r5, r29, 0
/* 08AD24 800902C4 38810028 */  addi    r4, r1, 0x28
/* 08AD28 800902C8 4BFA4531 */  bl      cpuGetAddressOffset
/* 08AD2C 800902CC 2C030000 */  cmpwi   r3, 0
/* 08AD30 800902D0 4082000C */  bne     lbl_800902DC
/* 08AD34 800902D4 38600000 */  li      r3, 0
/* 08AD38 800902D8 480004C4 */  b       lbl_8009079C
lbl_800902DC:
/* 08AD3C 800902DC 67A08000 */  oris    r0, r29, 0x8000
/* 08AD40 800902E0 90180060 */  stw     r0, 0x60(r24)
/* 08AD44 800902E4 38980038 */  addi    r4, r24, 0x38
/* 08AD48 800902E8 38C00000 */  li      r6, 0
/* 08AD4C 800902EC 80780004 */  lwz     r3, 4(r24)
/* 08AD50 800902F0 80A10028 */  lwz     r5, 0x28(r1)
/* 08AD54 800902F4 8063002C */  lwz     r3, 0x2c(r3)
/* 08AD58 800902F8 4BFDCDA9 */  bl      ramGetBuffer
/* 08AD5C 800902FC 2C030000 */  cmpwi   r3, 0
/* 08AD60 80090300 4082000C */  bne     lbl_8009030C
/* 08AD64 80090304 38600000 */  li      r3, 0
/* 08AD68 80090308 48000494 */  b       lbl_8009079C
lbl_8009030C:
/* 08AD6C 8009030C 381D0004 */  addi    r0, r29, 4
/* 08AD70 80090310 64008000 */  oris    r0, r0, 0x8000
/* 08AD74 80090314 9018005C */  stw     r0, 0x5c(r24)
/* 08AD78 80090318 38980034 */  addi    r4, r24, 0x34
/* 08AD7C 8009031C 38C00000 */  li      r6, 0
/* 08AD80 80090320 80780004 */  lwz     r3, 4(r24)
/* 08AD84 80090324 80A10028 */  lwz     r5, 0x28(r1)
/* 08AD88 80090328 8063002C */  lwz     r3, 0x2c(r3)
/* 08AD8C 8009032C 38A50004 */  addi    r5, r5, 4
/* 08AD90 80090330 4BFDCD71 */  bl      ramGetBuffer
/* 08AD94 80090334 2C030000 */  cmpwi   r3, 0
/* 08AD98 80090338 4082000C */  bne     lbl_80090344
/* 08AD9C 8009033C 38600000 */  li      r3, 0
/* 08ADA0 80090340 4800045C */  b       lbl_8009079C
lbl_80090344:
/* 08ADA4 80090344 381DFFFC */  addi    r0, r29, -4
/* 08ADA8 80090348 64008000 */  oris    r0, r0, 0x8000
/* 08ADAC 8009034C 90180054 */  stw     r0, 0x54(r24)
/* 08ADB0 80090350 3898002C */  addi    r4, r24, 0x2c
/* 08ADB4 80090354 38C00000 */  li      r6, 0
/* 08ADB8 80090358 80780004 */  lwz     r3, 4(r24)
/* 08ADBC 8009035C 80A10028 */  lwz     r5, 0x28(r1)
/* 08ADC0 80090360 8063002C */  lwz     r3, 0x2c(r3)
/* 08ADC4 80090364 38A5FFFC */  addi    r5, r5, -4
/* 08ADC8 80090368 4BFDCD39 */  bl      ramGetBuffer
/* 08ADCC 8009036C 2C030000 */  cmpwi   r3, 0
/* 08ADD0 80090370 4082000C */  bne     lbl_8009037C
/* 08ADD4 80090374 38600000 */  li      r3, 0
/* 08ADD8 80090378 48000424 */  b       lbl_8009079C
lbl_8009037C:
/* 08ADDC 8009037C 381DFFF8 */  addi    r0, r29, -8
/* 08ADE0 80090380 64008000 */  oris    r0, r0, 0x8000
/* 08ADE4 80090384 90180050 */  stw     r0, 0x50(r24)
/* 08ADE8 80090388 38980028 */  addi    r4, r24, 0x28
/* 08ADEC 8009038C 38C00000 */  li      r6, 0
/* 08ADF0 80090390 80780004 */  lwz     r3, 4(r24)
/* 08ADF4 80090394 80A10028 */  lwz     r5, 0x28(r1)
/* 08ADF8 80090398 8063002C */  lwz     r3, 0x2c(r3)
/* 08ADFC 8009039C 38A5FFF8 */  addi    r5, r5, -8
/* 08AE00 800903A0 4BFDCD01 */  bl      ramGetBuffer
/* 08AE04 800903A4 2C030000 */  cmpwi   r3, 0
/* 08AE08 800903A8 4082000C */  bne     lbl_800903B4
/* 08AE0C 800903AC 38600000 */  li      r3, 0
/* 08AE10 800903B0 480003EC */  b       lbl_8009079C
lbl_800903B4:
/* 08AE14 800903B4 5780843E */  srwi    r0, r28, 0x10
/* 08AE18 800903B8 7C1900AE */  lbzx    r0, r25, r0
/* 08AE1C 800903BC 38A10024 */  addi    r5, r1, 0x24
/* 08AE20 800903C0 5400103A */  slwi    r0, r0, 2
/* 08AE24 800903C4 7C7A002E */  lwzx    r3, r26, r0
/* 08AE28 800903C8 81830014 */  lwz     r12, 0x14(r3)
/* 08AE2C 800903CC 80030008 */  lwz     r0, 8(r3)
/* 08AE30 800903D0 7D8803A6 */  mtlr    r12
/* 08AE34 800903D4 80630004 */  lwz     r3, 4(r3)
/* 08AE38 800903D8 7C9C0214 */  add     r4, r28, r0
/* 08AE3C 800903DC 4E800021 */  blrl    
/* 08AE40 800903E0 80610024 */  lwz     r3, 0x24(r1)
/* 08AE44 800903E4 3B9C0004 */  addi    r28, r28, 4
/* 08AE48 800903E8 3C03EEE0 */  addis   r0, r3, 0xeee0
/* 08AE4C 800903EC 28000013 */  cmplwi  r0, 0x13
/* 08AE50 800903F0 41820024 */  beq     lbl_80090414
/* 08AE54 800903F4 28000011 */  cmplwi  r0, 0x11
/* 08AE58 800903F8 4182001C */  beq     lbl_80090414
/* 08AE5C 800903FC 2800000D */  cmplwi  r0, 0xd
/* 08AE60 80090400 41820014 */  beq     lbl_80090414
/* 08AE64 80090404 2800000B */  cmplwi  r0, 0xb
/* 08AE68 80090408 4182000C */  beq     lbl_80090414
/* 08AE6C 8009040C 28000009 */  cmplwi  r0, 9
/* 08AE70 80090410 4082FFA4 */  bne     lbl_800903B4
lbl_80090414:
/* 08AE74 80090414 381C0004 */  addi    r0, r28, 4
/* 08AE78 80090418 5400843E */  srwi    r0, r0, 0x10
/* 08AE7C 8009041C 7C1900AE */  lbzx    r0, r25, r0
/* 08AE80 80090420 38A1000C */  addi    r5, r1, 0xc
/* 08AE84 80090424 5400103A */  slwi    r0, r0, 2
/* 08AE88 80090428 7C7A002E */  lwzx    r3, r26, r0
/* 08AE8C 8009042C 80030008 */  lwz     r0, 8(r3)
/* 08AE90 80090430 81830014 */  lwz     r12, 0x14(r3)
/* 08AE94 80090434 7C9C0214 */  add     r4, r28, r0
/* 08AE98 80090438 80630004 */  lwz     r3, 4(r3)
/* 08AE9C 8009043C 7D8803A6 */  mtlr    r12
/* 08AEA0 80090440 38840004 */  addi    r4, r4, 4
/* 08AEA4 80090444 4E800021 */  blrl    
/* 08AEA8 80090448 381C0008 */  addi    r0, r28, 8
/* 08AEAC 8009044C 5400843E */  srwi    r0, r0, 0x10
/* 08AEB0 80090450 7C1900AE */  lbzx    r0, r25, r0
/* 08AEB4 80090454 38BF0000 */  addi    r5, r31, 0
/* 08AEB8 80090458 5400103A */  slwi    r0, r0, 2
/* 08AEBC 8009045C 7C7A002E */  lwzx    r3, r26, r0
/* 08AEC0 80090460 80030008 */  lwz     r0, 8(r3)
/* 08AEC4 80090464 81830014 */  lwz     r12, 0x14(r3)
/* 08AEC8 80090468 7C9C0214 */  add     r4, r28, r0
/* 08AECC 8009046C 80630004 */  lwz     r3, 4(r3)
/* 08AED0 80090470 7D8803A6 */  mtlr    r12
/* 08AED4 80090474 38840008 */  addi    r4, r4, 8
/* 08AED8 80090478 4E800021 */  blrl    
/* 08AEDC 8009047C 80010010 */  lwz     r0, 0x10(r1)
/* 08AEE0 80090480 8061000C */  lwz     r3, 0xc(r1)
/* 08AEE4 80090484 5400043E */  clrlwi  r0, r0, 0x10
/* 08AEE8 80090488 5463801E */  slwi    r3, r3, 0x10
/* 08AEEC 8009048C 7C000734 */  extsh   r0, r0
/* 08AEF0 80090490 7FA30214 */  add     r29, r3, r0
/* 08AEF4 80090494 3C1D4000 */  addis   r0, r29, 0x4000
/* 08AEF8 80090498 28000008 */  cmplwi  r0, 8
/* 08AEFC 8009049C 4082000C */  bne     lbl_800904A8
/* 08AF00 800904A0 38600000 */  li      r3, 0
/* 08AF04 800904A4 480002F8 */  b       lbl_8009079C
lbl_800904A8:
/* 08AF08 800904A8 387B0000 */  addi    r3, r27, 0
/* 08AF0C 800904AC 38BD0000 */  addi    r5, r29, 0
/* 08AF10 800904B0 38810028 */  addi    r4, r1, 0x28
/* 08AF14 800904B4 4BFA4345 */  bl      cpuGetAddressOffset
/* 08AF18 800904B8 2C030000 */  cmpwi   r3, 0
/* 08AF1C 800904BC 4082000C */  bne     lbl_800904C8
/* 08AF20 800904C0 38600000 */  li      r3, 0
/* 08AF24 800904C4 480002D8 */  b       lbl_8009079C
lbl_800904C8:
/* 08AF28 800904C8 67A08000 */  oris    r0, r29, 0x8000
/* 08AF2C 800904CC 9018004C */  stw     r0, 0x4c(r24)
/* 08AF30 800904D0 38980024 */  addi    r4, r24, 0x24
/* 08AF34 800904D4 38C00000 */  li      r6, 0
/* 08AF38 800904D8 80780004 */  lwz     r3, 4(r24)
/* 08AF3C 800904DC 80A10028 */  lwz     r5, 0x28(r1)
/* 08AF40 800904E0 8063002C */  lwz     r3, 0x2c(r3)
/* 08AF44 800904E4 4BFDCBBD */  bl      ramGetBuffer
/* 08AF48 800904E8 2C030000 */  cmpwi   r3, 0
/* 08AF4C 800904EC 4082000C */  bne     lbl_800904F8
/* 08AF50 800904F0 38600000 */  li      r3, 0
/* 08AF54 800904F4 480002A8 */  b       lbl_8009079C
lbl_800904F8:
/* 08AF58 800904F8 381DFFFC */  addi    r0, r29, -4
/* 08AF5C 800904FC 64008000 */  oris    r0, r0, 0x8000
/* 08AF60 80090500 90180048 */  stw     r0, 0x48(r24)
/* 08AF64 80090504 38980020 */  addi    r4, r24, 0x20
/* 08AF68 80090508 38C00000 */  li      r6, 0
/* 08AF6C 8009050C 80780004 */  lwz     r3, 4(r24)
/* 08AF70 80090510 80A10028 */  lwz     r5, 0x28(r1)
/* 08AF74 80090514 8063002C */  lwz     r3, 0x2c(r3)
/* 08AF78 80090518 38A5FFFC */  addi    r5, r5, -4
/* 08AF7C 8009051C 4BFDCB85 */  bl      ramGetBuffer
/* 08AF80 80090520 2C030000 */  cmpwi   r3, 0
/* 08AF84 80090524 4082000C */  bne     lbl_80090530
/* 08AF88 80090528 38600000 */  li      r3, 0
/* 08AF8C 8009052C 48000270 */  b       lbl_8009079C
lbl_80090530:
/* 08AF90 80090530 381DFFF8 */  addi    r0, r29, -8
/* 08AF94 80090534 64008000 */  oris    r0, r0, 0x8000
/* 08AF98 80090538 90180044 */  stw     r0, 0x44(r24)
/* 08AF9C 8009053C 3898001C */  addi    r4, r24, 0x1c
/* 08AFA0 80090540 38C00000 */  li      r6, 0
/* 08AFA4 80090544 80780004 */  lwz     r3, 4(r24)
/* 08AFA8 80090548 80A10028 */  lwz     r5, 0x28(r1)
/* 08AFAC 8009054C 8063002C */  lwz     r3, 0x2c(r3)
/* 08AFB0 80090550 38A5FFF8 */  addi    r5, r5, -8
/* 08AFB4 80090554 4BFDCB4D */  bl      ramGetBuffer
/* 08AFB8 80090558 2C030000 */  cmpwi   r3, 0
/* 08AFBC 8009055C 4082000C */  bne     lbl_80090568
/* 08AFC0 80090560 38600000 */  li      r3, 0
/* 08AFC4 80090564 48000238 */  b       lbl_8009079C
lbl_80090568:
/* 08AFC8 80090568 381DFFF0 */  addi    r0, r29, -16
/* 08AFCC 8009056C 64008000 */  oris    r0, r0, 0x8000
/* 08AFD0 80090570 90180040 */  stw     r0, 0x40(r24)
/* 08AFD4 80090574 38980018 */  addi    r4, r24, 0x18
/* 08AFD8 80090578 38C00000 */  li      r6, 0
/* 08AFDC 8009057C 80780004 */  lwz     r3, 4(r24)
/* 08AFE0 80090580 80A10028 */  lwz     r5, 0x28(r1)
/* 08AFE4 80090584 8063002C */  lwz     r3, 0x2c(r3)
/* 08AFE8 80090588 38A5FFF0 */  addi    r5, r5, -16
/* 08AFEC 8009058C 4BFDCB15 */  bl      ramGetBuffer
/* 08AFF0 80090590 2C030000 */  cmpwi   r3, 0
/* 08AFF4 80090594 4082000C */  bne     lbl_800905A0
/* 08AFF8 80090598 38600000 */  li      r3, 0
/* 08AFFC 8009059C 48000200 */  b       lbl_8009079C
lbl_800905A0:
/* 08B000 800905A0 5780843E */  srwi    r0, r28, 0x10
/* 08B004 800905A4 7C1900AE */  lbzx    r0, r25, r0
/* 08B008 800905A8 38A10024 */  addi    r5, r1, 0x24
/* 08B00C 800905AC 5400103A */  slwi    r0, r0, 2
/* 08B010 800905B0 7C7A002E */  lwzx    r3, r26, r0
/* 08B014 800905B4 81830014 */  lwz     r12, 0x14(r3)
/* 08B018 800905B8 80030008 */  lwz     r0, 8(r3)
/* 08B01C 800905BC 7D8803A6 */  mtlr    r12
/* 08B020 800905C0 80630004 */  lwz     r3, 4(r3)
/* 08B024 800905C4 7C9C0214 */  add     r4, r28, r0
/* 08B028 800905C8 4E800021 */  blrl    
/* 08B02C 800905CC 80610024 */  lwz     r3, 0x24(r1)
/* 08B030 800905D0 3B9C0004 */  addi    r28, r28, 4
/* 08B034 800905D4 3C03BF77 */  addis   r0, r3, 0xbf77
/* 08B038 800905D8 28005800 */  cmplwi  r0, 0x5800
/* 08B03C 800905DC 4082FFC4 */  bne     lbl_800905A0
/* 08B040 800905E0 5780843E */  srwi    r0, r28, 0x10
/* 08B044 800905E4 7C1900AE */  lbzx    r0, r25, r0
/* 08B048 800905E8 38A1000C */  addi    r5, r1, 0xc
/* 08B04C 800905EC 5400103A */  slwi    r0, r0, 2
/* 08B050 800905F0 7C7A002E */  lwzx    r3, r26, r0
/* 08B054 800905F4 81830014 */  lwz     r12, 0x14(r3)
/* 08B058 800905F8 80030008 */  lwz     r0, 8(r3)
/* 08B05C 800905FC 7D8803A6 */  mtlr    r12
/* 08B060 80090600 80630004 */  lwz     r3, 4(r3)
/* 08B064 80090604 7C9C0214 */  add     r4, r28, r0
/* 08B068 80090608 4E800021 */  blrl    
/* 08B06C 8009060C 3AFC0004 */  addi    r23, r28, 4
/* 08B070 80090610 56E0843E */  srwi    r0, r23, 0x10
/* 08B074 80090614 7C1900AE */  lbzx    r0, r25, r0
/* 08B078 80090618 38BF0000 */  addi    r5, r31, 0
/* 08B07C 8009061C 5400103A */  slwi    r0, r0, 2
/* 08B080 80090620 7C7A002E */  lwzx    r3, r26, r0
/* 08B084 80090624 80030008 */  lwz     r0, 8(r3)
/* 08B088 80090628 81830014 */  lwz     r12, 0x14(r3)
/* 08B08C 8009062C 7C9C0214 */  add     r4, r28, r0
/* 08B090 80090630 80630004 */  lwz     r3, 4(r3)
/* 08B094 80090634 7D8803A6 */  mtlr    r12
/* 08B098 80090638 38840004 */  addi    r4, r4, 4
/* 08B09C 8009063C 4E800021 */  blrl    
/* 08B0A0 80090640 8061000C */  lwz     r3, 0xc(r1)
/* 08B0A4 80090644 546036BE */  srwi    r0, r3, 0x1a
/* 08B0A8 80090648 28000003 */  cmplwi  r0, 3
/* 08B0AC 8009064C 40820010 */  bne     lbl_8009065C
/* 08B0B0 80090650 547D113A */  rlwinm  r29, r3, 2, 4, 0x1d
/* 08B0B4 80090654 539D0006 */  rlwimi  r29, r28, 0, 0, 3
/* 08B0B8 80090658 48000010 */  b       lbl_80090668
lbl_8009065C:
/* 08B0BC 8009065C 80010010 */  lwz     r0, 0x10(r1)
/* 08B0C0 80090660 541D113A */  rlwinm  r29, r0, 2, 4, 0x1d
/* 08B0C4 80090664 52FD0006 */  rlwimi  r29, r23, 0, 0, 3
lbl_80090668:
/* 08B0C8 80090668 57A0843E */  srwi    r0, r29, 0x10
/* 08B0CC 8009066C 7C1900AE */  lbzx    r0, r25, r0
/* 08B0D0 80090670 38A1000C */  addi    r5, r1, 0xc
/* 08B0D4 80090674 5400103A */  slwi    r0, r0, 2
/* 08B0D8 80090678 7C7A002E */  lwzx    r3, r26, r0
/* 08B0DC 8009067C 81830014 */  lwz     r12, 0x14(r3)
/* 08B0E0 80090680 80030008 */  lwz     r0, 8(r3)
/* 08B0E4 80090684 7D8803A6 */  mtlr    r12
/* 08B0E8 80090688 80630004 */  lwz     r3, 4(r3)
/* 08B0EC 8009068C 7C9D0214 */  add     r4, r29, r0
/* 08B0F0 80090690 4E800021 */  blrl    
/* 08B0F4 80090694 381D0004 */  addi    r0, r29, 4
/* 08B0F8 80090698 5400843E */  srwi    r0, r0, 0x10
/* 08B0FC 8009069C 7C1900AE */  lbzx    r0, r25, r0
/* 08B100 800906A0 38BF0000 */  addi    r5, r31, 0
/* 08B104 800906A4 5400103A */  slwi    r0, r0, 2
/* 08B108 800906A8 7C7A002E */  lwzx    r3, r26, r0
/* 08B10C 800906AC 80030008 */  lwz     r0, 8(r3)
/* 08B110 800906B0 81830014 */  lwz     r12, 0x14(r3)
/* 08B114 800906B4 7C9D0214 */  add     r4, r29, r0
/* 08B118 800906B8 80630004 */  lwz     r3, 4(r3)
/* 08B11C 800906BC 7D8803A6 */  mtlr    r12
/* 08B120 800906C0 38840004 */  addi    r4, r4, 4
/* 08B124 800906C4 4E800021 */  blrl    
/* 08B128 800906C8 381D0008 */  addi    r0, r29, 8
/* 08B12C 800906CC 5400843E */  srwi    r0, r0, 0x10
/* 08B130 800906D0 7C1900AE */  lbzx    r0, r25, r0
/* 08B134 800906D4 38BE0000 */  addi    r5, r30, 0
/* 08B138 800906D8 5400103A */  slwi    r0, r0, 2
/* 08B13C 800906DC 7C7A002E */  lwzx    r3, r26, r0
/* 08B140 800906E0 80030008 */  lwz     r0, 8(r3)
/* 08B144 800906E4 81830014 */  lwz     r12, 0x14(r3)
/* 08B148 800906E8 7C9D0214 */  add     r4, r29, r0
/* 08B14C 800906EC 80630004 */  lwz     r3, 4(r3)
/* 08B150 800906F0 7D8803A6 */  mtlr    r12
/* 08B154 800906F4 38840008 */  addi    r4, r4, 8
/* 08B158 800906F8 4E800021 */  blrl    
/* 08B15C 800906FC 8061000C */  lwz     r3, 0xc(r1)
/* 08B160 80090700 546036BE */  srwi    r0, r3, 0x1a
/* 08B164 80090704 2800000F */  cmplwi  r0, 0xf
/* 08B168 80090708 4082001C */  bne     lbl_80090724
/* 08B16C 8009070C 80010010 */  lwz     r0, 0x10(r1)
/* 08B170 80090710 5463801E */  slwi    r3, r3, 0x10
/* 08B174 80090714 5400043E */  clrlwi  r0, r0, 0x10
/* 08B178 80090718 7C000734 */  extsh   r0, r0
/* 08B17C 8009071C 7EE30214 */  add     r23, r3, r0
/* 08B180 80090720 4800001C */  b       lbl_8009073C
lbl_80090724:
/* 08B184 80090724 80010014 */  lwz     r0, 0x14(r1)
/* 08B188 80090728 80610010 */  lwz     r3, 0x10(r1)
/* 08B18C 8009072C 5400043E */  clrlwi  r0, r0, 0x10
/* 08B190 80090730 5463801E */  slwi    r3, r3, 0x10
/* 08B194 80090734 7C000734 */  extsh   r0, r0
/* 08B198 80090738 7EE30214 */  add     r23, r3, r0
lbl_8009073C:
/* 08B19C 8009073C 387B0000 */  addi    r3, r27, 0
/* 08B1A0 80090740 38B70000 */  addi    r5, r23, 0
/* 08B1A4 80090744 38810028 */  addi    r4, r1, 0x28
/* 08B1A8 80090748 4BFA40B1 */  bl      cpuGetAddressOffset
/* 08B1AC 8009074C 2C030000 */  cmpwi   r3, 0
/* 08B1B0 80090750 4082000C */  bne     lbl_8009075C
/* 08B1B4 80090754 38600000 */  li      r3, 0
/* 08B1B8 80090758 48000044 */  b       lbl_8009079C
lbl_8009075C:
/* 08B1BC 8009075C 66E08000 */  oris    r0, r23, 0x8000
/* 08B1C0 80090760 90180064 */  stw     r0, 0x64(r24)
/* 08B1C4 80090764 3898003C */  addi    r4, r24, 0x3c
/* 08B1C8 80090768 38C00000 */  li      r6, 0
/* 08B1CC 8009076C 80780004 */  lwz     r3, 4(r24)
/* 08B1D0 80090770 80A10028 */  lwz     r5, 0x28(r1)
/* 08B1D4 80090774 8063002C */  lwz     r3, 0x2c(r3)
/* 08B1D8 80090778 4BFDC929 */  bl      ramGetBuffer
/* 08B1DC 8009077C 2C030000 */  cmpwi   r3, 0
/* 08B1E0 80090780 4082000C */  bne     lbl_8009078C
/* 08B1E4 80090784 38600000 */  li      r3, 0
/* 08B1E8 80090788 48000014 */  b       lbl_8009079C
lbl_8009078C:
/* 08B1EC 8009078C 80180000 */  lwz     r0, 0(r24)
/* 08B1F0 80090790 38600001 */  li      r3, 1
/* 08B1F4 80090794 60000004 */  ori     r0, r0, 4
/* 08B1F8 80090798 90180000 */  stw     r0, 0(r24)
lbl_8009079C:
/* 08B1FC 8009079C BAE10034 */  lmw     r23, 0x34(r1)
/* 08B200 800907A0 8001005C */  lwz     r0, 0x5c(r1)
/* 08B204 800907A4 38210058 */  addi    r1, r1, 0x58
/* 08B208 800907A8 7C0803A6 */  mtlr    r0
/* 08B20C 800907AC 4E800020 */  blr     
