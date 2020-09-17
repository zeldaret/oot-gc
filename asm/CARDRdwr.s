# CARDRdwr.c
.include "macros.inc"

.section .text, "ax"

.balign 4

BlockReadCallback:
/* 0B7D00 800BD2A0 7C0802A6 */  mflr    r0
/* 0B7D04 800BD2A4 90010004 */  stw     r0, 4(r1)
/* 0B7D08 800BD2A8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0B7D0C 800BD2AC 93E1001C */  stw     r31, 0x1c(r1)
/* 0B7D10 800BD2B0 3BE30000 */  addi    r31, r3, 0
/* 0B7D14 800BD2B4 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B7D18 800BD2B8 93C10018 */  stw     r30, 0x18(r1)
/* 0B7D1C 800BD2BC 1CBF0110 */  mulli   r5, r31, 0x110
/* 0B7D20 800BD2C0 93A10014 */  stw     r29, 0x14(r1)
/* 0B7D24 800BD2C4 380327D0 */  addi    r0, r3, __CARDBlock@l
/* 0B7D28 800BD2C8 7C9D2379 */  or.     r29, r4, r4
/* 0B7D2C 800BD2CC 7FC02A14 */  add     r30, r0, r5
/* 0B7D30 800BD2D0 41800050 */  blt     lbl_800BD320
/* 0B7D34 800BD2D4 807E00B8 */  lwz     r3, 0xb8(r30)
/* 0B7D38 800BD2D8 38030200 */  addi    r0, r3, 0x200
/* 0B7D3C 800BD2DC 901E00B8 */  stw     r0, 0xb8(r30)
/* 0B7D40 800BD2E0 807E00B0 */  lwz     r3, 0xb0(r30)
/* 0B7D44 800BD2E4 38030200 */  addi    r0, r3, 0x200
/* 0B7D48 800BD2E8 901E00B0 */  stw     r0, 0xb0(r30)
/* 0B7D4C 800BD2EC 807E00B4 */  lwz     r3, 0xb4(r30)
/* 0B7D50 800BD2F0 38030200 */  addi    r0, r3, 0x200
/* 0B7D54 800BD2F4 901E00B4 */  stw     r0, 0xb4(r30)
/* 0B7D58 800BD2F8 807E00AC */  lwz     r3, 0xac(r30)
/* 0B7D5C 800BD2FC 3403FFFF */  addic.  r0, r3, -1
/* 0B7D60 800BD300 901E00AC */  stw     r0, 0xac(r30)
/* 0B7D64 800BD304 4081001C */  ble     lbl_800BD320
/* 0B7D68 800BD308 3C60800C */  lis     r3, BlockReadCallback@ha
/* 0B7D6C 800BD30C 3883D2A0 */  addi    r4, r3, BlockReadCallback@l
/* 0B7D70 800BD310 387F0000 */  addi    r3, r31, 0
/* 0B7D74 800BD314 4BFFE58D */  bl      __CARDReadSegment
/* 0B7D78 800BD318 7C7D1B79 */  or.     r29, r3, r3
/* 0B7D7C 800BD31C 40800044 */  bge     lbl_800BD360
lbl_800BD320:
/* 0B7D80 800BD320 801E00D0 */  lwz     r0, 0xd0(r30)
/* 0B7D84 800BD324 28000000 */  cmplwi  r0, 0
/* 0B7D88 800BD328 40820010 */  bne     lbl_800BD338
/* 0B7D8C 800BD32C 387E0000 */  addi    r3, r30, 0
/* 0B7D90 800BD330 389D0000 */  addi    r4, r29, 0
/* 0B7D94 800BD334 4BFFEA41 */  bl      __CARDPutControlBlock
lbl_800BD338:
/* 0B7D98 800BD338 801E00D4 */  lwz     r0, 0xd4(r30)
/* 0B7D9C 800BD33C 28000000 */  cmplwi  r0, 0
/* 0B7DA0 800BD340 7C0C0378 */  mr      r12, r0
/* 0B7DA4 800BD344 4182001C */  beq     lbl_800BD360
/* 0B7DA8 800BD348 38000000 */  li      r0, 0
/* 0B7DAC 800BD34C 7D8803A6 */  mtlr    r12
/* 0B7DB0 800BD350 901E00D4 */  stw     r0, 0xd4(r30)
/* 0B7DB4 800BD354 387F0000 */  addi    r3, r31, 0
/* 0B7DB8 800BD358 389D0000 */  addi    r4, r29, 0
/* 0B7DBC 800BD35C 4E800021 */  blrl    
lbl_800BD360:
/* 0B7DC0 800BD360 80010024 */  lwz     r0, 0x24(r1)
/* 0B7DC4 800BD364 83E1001C */  lwz     r31, 0x1c(r1)
/* 0B7DC8 800BD368 83C10018 */  lwz     r30, 0x18(r1)
/* 0B7DCC 800BD36C 83A10014 */  lwz     r29, 0x14(r1)
/* 0B7DD0 800BD370 38210020 */  addi    r1, r1, 0x20
/* 0B7DD4 800BD374 7C0803A6 */  mtlr    r0
/* 0B7DD8 800BD378 4E800020 */  blr     

glabel __CARDRead
/* 0B7DDC 800BD37C 7C0802A6 */  mflr    r0
/* 0B7DE0 800BD380 1D230110 */  mulli   r9, r3, 0x110
/* 0B7DE4 800BD384 90010004 */  stw     r0, 4(r1)
/* 0B7DE8 800BD388 3D008013 */  lis     r8, __CARDBlock@ha
/* 0B7DEC 800BD38C 9421FFF8 */  stwu    r1, -8(r1)
/* 0B7DF0 800BD390 380827D0 */  addi    r0, r8, __CARDBlock@l
/* 0B7DF4 800BD394 7D004A14 */  add     r8, r0, r9
/* 0B7DF8 800BD398 80080000 */  lwz     r0, 0(r8)
/* 0B7DFC 800BD39C 2C000000 */  cmpwi   r0, 0
/* 0B7E00 800BD3A0 4082000C */  bne     lbl_800BD3AC
/* 0B7E04 800BD3A4 3860FFFD */  li      r3, -3
/* 0B7E08 800BD3A8 48000028 */  b       lbl_800BD3D0
lbl_800BD3AC:
/* 0B7E0C 800BD3AC 90E800D4 */  stw     r7, 0xd4(r8)
/* 0B7E10 800BD3B0 54A0BA7E */  srwi    r0, r5, 9
/* 0B7E14 800BD3B4 3CA0800C */  lis     r5, BlockReadCallback@ha
/* 0B7E18 800BD3B8 900800AC */  stw     r0, 0xac(r8)
/* 0B7E1C 800BD3BC 3805D2A0 */  addi    r0, r5, BlockReadCallback@l
/* 0B7E20 800BD3C0 908800B0 */  stw     r4, 0xb0(r8)
/* 0B7E24 800BD3C4 7C040378 */  mr      r4, r0
/* 0B7E28 800BD3C8 90C800B4 */  stw     r6, 0xb4(r8)
/* 0B7E2C 800BD3CC 4BFFE4D5 */  bl      __CARDReadSegment
lbl_800BD3D0:
/* 0B7E30 800BD3D0 8001000C */  lwz     r0, 0xc(r1)
/* 0B7E34 800BD3D4 38210008 */  addi    r1, r1, 8
/* 0B7E38 800BD3D8 7C0803A6 */  mtlr    r0
/* 0B7E3C 800BD3DC 4E800020 */  blr     

BlockWriteCallback:
/* 0B7E40 800BD3E0 7C0802A6 */  mflr    r0
/* 0B7E44 800BD3E4 90010004 */  stw     r0, 4(r1)
/* 0B7E48 800BD3E8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0B7E4C 800BD3EC 93E1001C */  stw     r31, 0x1c(r1)
/* 0B7E50 800BD3F0 3BE30000 */  addi    r31, r3, 0
/* 0B7E54 800BD3F4 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B7E58 800BD3F8 93C10018 */  stw     r30, 0x18(r1)
/* 0B7E5C 800BD3FC 1CBF0110 */  mulli   r5, r31, 0x110
/* 0B7E60 800BD400 93A10014 */  stw     r29, 0x14(r1)
/* 0B7E64 800BD404 380327D0 */  addi    r0, r3, __CARDBlock@l
/* 0B7E68 800BD408 7C9D2379 */  or.     r29, r4, r4
/* 0B7E6C 800BD40C 7FC02A14 */  add     r30, r0, r5
/* 0B7E70 800BD410 41800050 */  blt     lbl_800BD460
/* 0B7E74 800BD414 807E00B8 */  lwz     r3, 0xb8(r30)
/* 0B7E78 800BD418 38030080 */  addi    r0, r3, 0x80
/* 0B7E7C 800BD41C 901E00B8 */  stw     r0, 0xb8(r30)
/* 0B7E80 800BD420 807E00B0 */  lwz     r3, 0xb0(r30)
/* 0B7E84 800BD424 38030080 */  addi    r0, r3, 0x80
/* 0B7E88 800BD428 901E00B0 */  stw     r0, 0xb0(r30)
/* 0B7E8C 800BD42C 807E00B4 */  lwz     r3, 0xb4(r30)
/* 0B7E90 800BD430 38030080 */  addi    r0, r3, 0x80
/* 0B7E94 800BD434 901E00B4 */  stw     r0, 0xb4(r30)
/* 0B7E98 800BD438 807E00AC */  lwz     r3, 0xac(r30)
/* 0B7E9C 800BD43C 3403FFFF */  addic.  r0, r3, -1
/* 0B7EA0 800BD440 901E00AC */  stw     r0, 0xac(r30)
/* 0B7EA4 800BD444 4081001C */  ble     lbl_800BD460
/* 0B7EA8 800BD448 3C60800C */  lis     r3, BlockWriteCallback@ha
/* 0B7EAC 800BD44C 3883D3E0 */  addi    r4, r3, BlockWriteCallback@l
/* 0B7EB0 800BD450 387F0000 */  addi    r3, r31, 0
/* 0B7EB4 800BD454 4BFFE581 */  bl      __CARDWritePage
/* 0B7EB8 800BD458 7C7D1B79 */  or.     r29, r3, r3
/* 0B7EBC 800BD45C 40800044 */  bge     lbl_800BD4A0
lbl_800BD460:
/* 0B7EC0 800BD460 801E00D0 */  lwz     r0, 0xd0(r30)
/* 0B7EC4 800BD464 28000000 */  cmplwi  r0, 0
/* 0B7EC8 800BD468 40820010 */  bne     lbl_800BD478
/* 0B7ECC 800BD46C 387E0000 */  addi    r3, r30, 0
/* 0B7ED0 800BD470 389D0000 */  addi    r4, r29, 0
/* 0B7ED4 800BD474 4BFFE901 */  bl      __CARDPutControlBlock
lbl_800BD478:
/* 0B7ED8 800BD478 801E00D4 */  lwz     r0, 0xd4(r30)
/* 0B7EDC 800BD47C 28000000 */  cmplwi  r0, 0
/* 0B7EE0 800BD480 7C0C0378 */  mr      r12, r0
/* 0B7EE4 800BD484 4182001C */  beq     lbl_800BD4A0
/* 0B7EE8 800BD488 38000000 */  li      r0, 0
/* 0B7EEC 800BD48C 7D8803A6 */  mtlr    r12
/* 0B7EF0 800BD490 901E00D4 */  stw     r0, 0xd4(r30)
/* 0B7EF4 800BD494 387F0000 */  addi    r3, r31, 0
/* 0B7EF8 800BD498 389D0000 */  addi    r4, r29, 0
/* 0B7EFC 800BD49C 4E800021 */  blrl    
lbl_800BD4A0:
/* 0B7F00 800BD4A0 80010024 */  lwz     r0, 0x24(r1)
/* 0B7F04 800BD4A4 83E1001C */  lwz     r31, 0x1c(r1)
/* 0B7F08 800BD4A8 83C10018 */  lwz     r30, 0x18(r1)
/* 0B7F0C 800BD4AC 83A10014 */  lwz     r29, 0x14(r1)
/* 0B7F10 800BD4B0 38210020 */  addi    r1, r1, 0x20
/* 0B7F14 800BD4B4 7C0803A6 */  mtlr    r0
/* 0B7F18 800BD4B8 4E800020 */  blr     

glabel __CARDWrite
/* 0B7F1C 800BD4BC 7C0802A6 */  mflr    r0
/* 0B7F20 800BD4C0 1D230110 */  mulli   r9, r3, 0x110
/* 0B7F24 800BD4C4 90010004 */  stw     r0, 4(r1)
/* 0B7F28 800BD4C8 3D008013 */  lis     r8, __CARDBlock@ha
/* 0B7F2C 800BD4CC 9421FFF8 */  stwu    r1, -8(r1)
/* 0B7F30 800BD4D0 380827D0 */  addi    r0, r8, __CARDBlock@l
/* 0B7F34 800BD4D4 7D004A14 */  add     r8, r0, r9
/* 0B7F38 800BD4D8 80080000 */  lwz     r0, 0(r8)
/* 0B7F3C 800BD4DC 2C000000 */  cmpwi   r0, 0
/* 0B7F40 800BD4E0 4082000C */  bne     lbl_800BD4EC
/* 0B7F44 800BD4E4 3860FFFD */  li      r3, -3
/* 0B7F48 800BD4E8 48000028 */  b       lbl_800BD510
lbl_800BD4EC:
/* 0B7F4C 800BD4EC 90E800D4 */  stw     r7, 0xd4(r8)
/* 0B7F50 800BD4F0 54A0C9FE */  srwi    r0, r5, 7
/* 0B7F54 800BD4F4 3CA0800C */  lis     r5, BlockWriteCallback@ha
/* 0B7F58 800BD4F8 900800AC */  stw     r0, 0xac(r8)
/* 0B7F5C 800BD4FC 3805D3E0 */  addi    r0, r5, BlockWriteCallback@l
/* 0B7F60 800BD500 908800B0 */  stw     r4, 0xb0(r8)
/* 0B7F64 800BD504 7C040378 */  mr      r4, r0
/* 0B7F68 800BD508 90C800B4 */  stw     r6, 0xb4(r8)
/* 0B7F6C 800BD50C 4BFFE4C9 */  bl      __CARDWritePage
lbl_800BD510:
/* 0B7F70 800BD510 8001000C */  lwz     r0, 0xc(r1)
/* 0B7F74 800BD514 38210008 */  addi    r1, r1, 8
/* 0B7F78 800BD518 7C0803A6 */  mtlr    r0
/* 0B7F7C 800BD51C 4E800020 */  blr     

glabel CARDGetXferredBytes
/* 0B7F80 800BD520 1C030110 */  mulli   r0, r3, 0x110
/* 0B7F84 800BD524 3C608013 */  lis     r3, __CARDBlock@ha
/* 0B7F88 800BD528 386327D0 */  addi    r3, r3, __CARDBlock@l
/* 0B7F8C 800BD52C 7C630214 */  add     r3, r3, r0
/* 0B7F90 800BD530 806300B8 */  lwz     r3, 0xb8(r3)
/* 0B7F94 800BD534 4E800020 */  blr     


