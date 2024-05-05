glabel cpuCheckDelaySlot
/* 062C98 80068238 28030000 */  cmplwi  r3, 0
/* 062C9C 8006823C 38A00000 */  li      r5, 0
/* 062CA0 80068240 4082000C */  bne     lbl_8006824C
/* 062CA4 80068244 38600000 */  li      r3, 0
/* 062CA8 80068248 4E800020 */  blr     
lbl_8006824C:
/* 062CAC 8006824C 546036BE */  srwi    r0, r3, 0x1a
/* 062CB0 80068250 28000017 */  cmplwi  r0, 0x17
/* 062CB4 80068254 4181010C */  bgt     lbl_80068360
/* 062CB8 80068258 3C80800F */  lis     r4, jtbl_800ED514@ha
/* 062CBC 8006825C 3884D514 */  addi    r4, r4, jtbl_800ED514@l
/* 062CC0 80068260 5400103A */  slwi    r0, r0, 2
/* 062CC4 80068264 7C04002E */  lwzx    r0, r4, r0
/* 062CC8 80068268 7C0903A6 */  mtctr   r0
/* 062CCC 8006826C 4E800420 */  bctr    
.global lbl_80068270
lbl_80068270:
/* 062CD0 80068270 546006BE */  clrlwi  r0, r3, 0x1a
/* 062CD4 80068274 2C000009 */  cmpwi   r0, 9
/* 062CD8 80068278 4182001C */  beq     lbl_80068294
/* 062CDC 8006827C 408000E4 */  bge     lbl_80068360
/* 062CE0 80068280 2C000008 */  cmpwi   r0, 8
/* 062CE4 80068284 40800008 */  bge     lbl_8006828C
/* 062CE8 80068288 480000D8 */  b       lbl_80068360
lbl_8006828C:
/* 062CEC 8006828C 38A00D05 */  li      r5, 0xd05
/* 062CF0 80068290 480000D0 */  b       lbl_80068360
lbl_80068294:
/* 062CF4 80068294 38A008AE */  li      r5, 0x8ae
/* 062CF8 80068298 480000C8 */  b       lbl_80068360
.global lbl_8006829C
lbl_8006829C:
/* 062CFC 8006829C 546086FE */  rlwinm  r0, r3, 0x10, 0x1b, 0x1f
/* 062D00 800682A0 2C000010 */  cmpwi   r0, 0x10
/* 062D04 800682A4 40800018 */  bge     lbl_800682BC
/* 062D08 800682A8 2C000004 */  cmpwi   r0, 4
/* 062D0C 800682AC 408000B4 */  bge     lbl_80068360
/* 062D10 800682B0 2C000000 */  cmpwi   r0, 0
/* 062D14 800682B4 40800010 */  bge     lbl_800682C4
/* 062D18 800682B8 480000A8 */  b       lbl_80068360
lbl_800682BC:
/* 062D1C 800682BC 2C000014 */  cmpwi   r0, 0x14
/* 062D20 800682C0 408000A0 */  bge     lbl_80068360
lbl_800682C4:
/* 062D24 800682C4 38A00457 */  li      r5, 0x457
/* 062D28 800682C8 48000098 */  b       lbl_80068360
.global lbl_800682CC
lbl_800682CC:
/* 062D2C 800682CC 546006BE */  clrlwi  r0, r3, 0x1a
/* 062D30 800682D0 28000018 */  cmplwi  r0, 0x18
/* 062D34 800682D4 4181001C */  bgt     lbl_800682F0
/* 062D38 800682D8 3C80800F */  lis     r4, jtbl_800ED4B0@ha
/* 062D3C 800682DC 3884D4B0 */  addi    r4, r4, jtbl_800ED4B0@l
/* 062D40 800682E0 5400103A */  slwi    r0, r0, 2
/* 062D44 800682E4 7C04002E */  lwzx    r0, r4, r0
/* 062D48 800682E8 7C0903A6 */  mtctr   r0
/* 062D4C 800682EC 4E800420 */  bctr    
.global lbl_800682F0
lbl_800682F0:
/* 062D50 800682F0 54605EFE */  rlwinm  r0, r3, 0xb, 0x1b, 0x1f
/* 062D54 800682F4 2C000008 */  cmpwi   r0, 8
/* 062D58 800682F8 41820008 */  beq     lbl_80068300
/* 062D5C 800682FC 48000064 */  b       lbl_80068360
lbl_80068300:
/* 062D60 80068300 546086FE */  rlwinm  r0, r3, 0x10, 0x1b, 0x1f
/* 062D64 80068304 2C000004 */  cmpwi   r0, 4
/* 062D68 80068308 40800058 */  bge     lbl_80068360
/* 062D6C 8006830C 2C000000 */  cmpwi   r0, 0
/* 062D70 80068310 40800008 */  bge     lbl_80068318
/* 062D74 80068314 4800004C */  b       lbl_80068360
lbl_80068318:
/* 062D78 80068318 38A00457 */  li      r5, 0x457
/* 062D7C 8006831C 48000044 */  b       lbl_80068360
.global lbl_80068320
lbl_80068320:
/* 062D80 80068320 54605EFE */  rlwinm  r0, r3, 0xb, 0x1b, 0x1f
/* 062D84 80068324 28000008 */  cmplwi  r0, 8
/* 062D88 80068328 40820038 */  bne     lbl_80068360
/* 062D8C 8006832C 546086FE */  rlwinm  r0, r3, 0x10, 0x1b, 0x1f
/* 062D90 80068330 2C000004 */  cmpwi   r0, 4
/* 062D94 80068334 4080002C */  bge     lbl_80068360
/* 062D98 80068338 2C000000 */  cmpwi   r0, 0
/* 062D9C 8006833C 40800008 */  bge     lbl_80068344
/* 062DA0 80068340 48000020 */  b       lbl_80068360
lbl_80068344:
/* 062DA4 80068344 38A00457 */  li      r5, 0x457
/* 062DA8 80068348 48000018 */  b       lbl_80068360
.global lbl_8006834C
lbl_8006834C:
/* 062DAC 8006834C 38A00D05 */  li      r5, 0xd05
/* 062DB0 80068350 48000010 */  b       lbl_80068360
.global lbl_80068354
lbl_80068354:
/* 062DB4 80068354 38A008AE */  li      r5, 0x8ae
/* 062DB8 80068358 48000008 */  b       lbl_80068360
.global lbl_8006835C
lbl_8006835C:
/* 062DBC 8006835C 38A00457 */  li      r5, 0x457
.global lbl_80068360
lbl_80068360:
/* 062DC0 80068360 7CA32B78 */  mr      r3, r5
/* 062DC4 80068364 4E800020 */  blr     

.section .data

jtbl_800ED4B0:
    .word lbl_800682F0
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_80068360
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_80068360
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_800682F0
    .word lbl_80068360

jtbl_800ED514:
    .word lbl_80068270
    .word lbl_8006829C
    .word lbl_8006834C
    .word lbl_80068354
    .word lbl_8006835C
    .word lbl_8006835C
    .word lbl_8006835C
    .word lbl_8006835C
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_800682CC
    .word lbl_80068320
    .word lbl_80068360
    .word lbl_80068360
    .word lbl_8006835C
    .word lbl_8006835C
    .word lbl_8006835C
    .word lbl_8006835C
