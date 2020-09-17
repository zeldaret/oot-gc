# video.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel videoEvent
/* 089300 8008E8A0 7C0802A6 */  mflr    r0
/* 089304 8008E8A4 2C040005 */  cmpwi   r4, 5
/* 089308 8008E8A8 90010004 */  stw     r0, 4(r1)
/* 08930C 8008E8AC 9421FFE0 */  stwu    r1, -0x20(r1)
/* 089310 8008E8B0 93E1001C */  stw     r31, 0x1c(r1)
/* 089314 8008E8B4 3BE50000 */  addi    r31, r5, 0
/* 089318 8008E8B8 93C10018 */  stw     r30, 0x18(r1)
/* 08931C 8008E8BC 3BC30000 */  addi    r30, r3, 0
/* 089320 8008E8C0 41820118 */  beq     lbl_8008E9D8
/* 089324 8008E8C4 40800028 */  bge     lbl_8008E8EC
/* 089328 8008E8C8 2C040002 */  cmpwi   r4, 2
/* 08932C 8008E8CC 41820038 */  beq     lbl_8008E904
/* 089330 8008E8D0 40800010 */  bge     lbl_8008E8E0
/* 089334 8008E8D4 2C040000 */  cmpwi   r4, 0
/* 089338 8008E8D8 40800100 */  bge     lbl_8008E9D8
/* 08933C 8008E8DC 480000F4 */  b       lbl_8008E9D0
lbl_8008E8E0:
/* 089340 8008E8E0 2C040004 */  cmpwi   r4, 4
/* 089344 8008E8E4 408000EC */  bge     lbl_8008E9D0
/* 089348 8008E8E8 480000F0 */  b       lbl_8008E9D8
lbl_8008E8EC:
/* 08934C 8008E8EC 2C041003 */  cmpwi   r4, 0x1003
/* 089350 8008E8F0 418200E8 */  beq     lbl_8008E9D8
/* 089354 8008E8F4 408000DC */  bge     lbl_8008E9D0
/* 089358 8008E8F8 2C041002 */  cmpwi   r4, 0x1002
/* 08935C 8008E8FC 40800054 */  bge     lbl_8008E950
/* 089360 8008E900 480000D0 */  b       lbl_8008E9D0
lbl_8008E904:
/* 089364 8008E904 38600000 */  li      r3, 0
/* 089368 8008E908 907E0000 */  stw     r3, 0(r30)
/* 08936C 8008E90C 3C000001 */  lis     r0, 1
/* 089370 8008E910 907E0008 */  stw     r3, 8(r30)
/* 089374 8008E914 907E000C */  stw     r3, 0xc(r30)
/* 089378 8008E918 907E0014 */  stw     r3, 0x14(r30)
/* 08937C 8008E91C 907E0018 */  stw     r3, 0x18(r30)
/* 089380 8008E920 907E001C */  stw     r3, 0x1c(r30)
/* 089384 8008E924 907E0024 */  stw     r3, 0x24(r30)
/* 089388 8008E928 907E0028 */  stw     r3, 0x28(r30)
/* 08938C 8008E92C 907E002C */  stw     r3, 0x2c(r30)
/* 089390 8008E930 907E0030 */  stw     r3, 0x30(r30)
/* 089394 8008E934 907E0034 */  stw     r3, 0x34(r30)
/* 089398 8008E938 907E0038 */  stw     r3, 0x38(r30)
/* 08939C 8008E93C 907E003C */  stw     r3, 0x3c(r30)
/* 0893A0 8008E940 907E0004 */  stw     r3, 4(r30)
/* 0893A4 8008E944 901E0020 */  stw     r0, 0x20(r30)
/* 0893A8 8008E948 93FE0010 */  stw     r31, 0x10(r30)
/* 0893AC 8008E94C 4800008C */  b       lbl_8008E9D8
lbl_8008E950:
/* 0893B0 8008E950 807E0010 */  lwz     r3, 0x10(r30)
/* 0893B4 8008E954 3CA08009 */  lis     r5, videoPut8@ha
/* 0893B8 8008E958 3CC08009 */  lis     r6, videoPut16@ha
/* 0893BC 8008E95C 3CE08009 */  lis     r7, videoPut32@ha
/* 0893C0 8008E960 80630024 */  lwz     r3, 0x24(r3)
/* 0893C4 8008E964 3C808009 */  lis     r4, videoPut64@ha
/* 0893C8 8008E968 3904EB94 */  addi    r8, r4, videoPut64@l
/* 0893CC 8008E96C 38A5EE18 */  addi    r5, r5, videoPut8@l
/* 0893D0 8008E970 38C6EE10 */  addi    r6, r6, videoPut16@l
/* 0893D4 8008E974 38E7EB9C */  addi    r7, r7, videoPut32@l
/* 0893D8 8008E978 389F0000 */  addi    r4, r31, 0
/* 0893DC 8008E97C 4BFA66BD */  bl      cpuSetDevicePut
/* 0893E0 8008E980 2C030000 */  cmpwi   r3, 0
/* 0893E4 8008E984 4082000C */  bne     lbl_8008E990
/* 0893E8 8008E988 38600000 */  li      r3, 0
/* 0893EC 8008E98C 48000050 */  b       lbl_8008E9DC
lbl_8008E990:
/* 0893F0 8008E990 807E0010 */  lwz     r3, 0x10(r30)
/* 0893F4 8008E994 3CA08009 */  lis     r5, videoGet8@ha
/* 0893F8 8008E998 3CC08009 */  lis     r6, videoGet16@ha
/* 0893FC 8008E99C 3CE08009 */  lis     r7, videoGet32@ha
/* 089400 8008E9A0 80630024 */  lwz     r3, 0x24(r3)
/* 089404 8008E9A4 3C808009 */  lis     r4, videoGet64@ha
/* 089408 8008E9A8 3904EA60 */  addi    r8, r4, videoGet64@l
/* 08940C 8008E9AC 38A5EB8C */  addi    r5, r5, videoGet8@l
/* 089410 8008E9B0 38C6EB84 */  addi    r6, r6, videoGet16@l
/* 089414 8008E9B4 38E7EA68 */  addi    r7, r7, videoGet32@l
/* 089418 8008E9B8 389F0000 */  addi    r4, r31, 0
/* 08941C 8008E9BC 4BFA6695 */  bl      cpuSetDeviceGet
/* 089420 8008E9C0 2C030000 */  cmpwi   r3, 0
/* 089424 8008E9C4 40820014 */  bne     lbl_8008E9D8
/* 089428 8008E9C8 38600000 */  li      r3, 0
/* 08942C 8008E9CC 48000010 */  b       lbl_8008E9DC
lbl_8008E9D0:
/* 089430 8008E9D0 38600000 */  li      r3, 0
/* 089434 8008E9D4 48000008 */  b       lbl_8008E9DC
lbl_8008E9D8:
/* 089438 8008E9D8 38600001 */  li      r3, 1
lbl_8008E9DC:
/* 08943C 8008E9DC 80010024 */  lwz     r0, 0x24(r1)
/* 089440 8008E9E0 83E1001C */  lwz     r31, 0x1c(r1)
/* 089444 8008E9E4 83C10018 */  lwz     r30, 0x18(r1)
/* 089448 8008E9E8 7C0803A6 */  mtlr    r0
/* 08944C 8008E9EC 38210020 */  addi    r1, r1, 0x20
/* 089450 8008E9F0 4E800020 */  blr     

glabel videoForceRetrace
/* 089454 8008E9F4 7C0802A6 */  mflr    r0
/* 089458 8008E9F8 38800008 */  li      r4, 8
/* 08945C 8008E9FC 90010004 */  stw     r0, 4(r1)
/* 089460 8008EA00 9421FFE8 */  stwu    r1, -0x18(r1)
/* 089464 8008EA04 93E10014 */  stw     r31, 0x14(r1)
/* 089468 8008EA08 7C7F1B78 */  mr      r31, r3
/* 08946C 8008EA0C 80630010 */  lwz     r3, 0x10(r3)
/* 089470 8008EA10 4BF9E8DD */  bl      systemExceptionPending
/* 089474 8008EA14 2C030000 */  cmpwi   r3, 0
/* 089478 8008EA18 40820030 */  bne     lbl_8008EA48
/* 08947C 8008EA1C 801F0014 */  lwz     r0, 0x14(r31)
/* 089480 8008EA20 540007BF */  clrlwi. r0, r0, 0x1e
/* 089484 8008EA24 41820024 */  beq     lbl_8008EA48
/* 089488 8008EA28 801F0020 */  lwz     r0, 0x20(r31)
/* 08948C 8008EA2C 38801000 */  li      r4, 0x1000
/* 089490 8008EA30 38A00008 */  li      r5, 8
/* 089494 8008EA34 901F0000 */  stw     r0, 0(r31)
/* 089498 8008EA38 807F0010 */  lwz     r3, 0x10(r31)
/* 08949C 8008EA3C 4BF79231 */  bl      xlObjectEvent
/* 0894A0 8008EA40 38600001 */  li      r3, 1
/* 0894A4 8008EA44 48000008 */  b       lbl_8008EA4C
lbl_8008EA48:
/* 0894A8 8008EA48 38600000 */  li      r3, 0
lbl_8008EA4C:
/* 0894AC 8008EA4C 8001001C */  lwz     r0, 0x1c(r1)
/* 0894B0 8008EA50 83E10014 */  lwz     r31, 0x14(r1)
/* 0894B4 8008EA54 38210018 */  addi    r1, r1, 0x18
/* 0894B8 8008EA58 7C0803A6 */  mtlr    r0
/* 0894BC 8008EA5C 4E800020 */  blr     

glabel videoGet64
/* 0894C0 8008EA60 38600000 */  li      r3, 0
/* 0894C4 8008EA64 4E800020 */  blr     

glabel videoGet32
/* 0894C8 8008EA68 7C0802A6 */  mflr    r0
/* 0894CC 8008EA6C 90010004 */  stw     r0, 4(r1)
/* 0894D0 8008EA70 548006BE */  clrlwi  r0, r4, 0x1a
/* 0894D4 8008EA74 28000034 */  cmplwi  r0, 0x34
/* 0894D8 8008EA78 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0894DC 8008EA7C 93E1001C */  stw     r31, 0x1c(r1)
/* 0894E0 8008EA80 3BE50000 */  addi    r31, r5, 0
/* 0894E4 8008EA84 93C10018 */  stw     r30, 0x18(r1)
/* 0894E8 8008EA88 3BC30000 */  addi    r30, r3, 0
/* 0894EC 8008EA8C 418100D4 */  bgt     lbl_8008EB60
/* 0894F0 8008EA90 3C60800F */  lis     r3, jtbl_800EE880@ha
/* 0894F4 8008EA94 3863E880 */  addi    r3, r3, jtbl_800EE880@l
/* 0894F8 8008EA98 5400103A */  slwi    r0, r0, 2
/* 0894FC 8008EA9C 7C03002E */  lwzx    r0, r3, r0
/* 089500 8008EAA0 7C0903A6 */  mtctr   r0
/* 089504 8008EAA4 4E800420 */  bctr    
glabel lbl_8008EAA8
/* 089508 8008EAA8 801E0014 */  lwz     r0, 0x14(r30)
/* 08950C 8008EAAC 901F0000 */  stw     r0, 0(r31)
/* 089510 8008EAB0 480000B8 */  b       lbl_8008EB68
glabel lbl_8008EAB4
/* 089514 8008EAB4 801E001C */  lwz     r0, 0x1c(r30)
/* 089518 8008EAB8 901F0000 */  stw     r0, 0(r31)
/* 08951C 8008EABC 480000AC */  b       lbl_8008EB68
glabel lbl_8008EAC0
/* 089520 8008EAC0 801E000C */  lwz     r0, 0xc(r30)
/* 089524 8008EAC4 901F0000 */  stw     r0, 0(r31)
/* 089528 8008EAC8 480000A0 */  b       lbl_8008EB68
glabel lbl_8008EACC
/* 08952C 8008EACC 801E0020 */  lwz     r0, 0x20(r30)
/* 089530 8008EAD0 5400043E */  clrlwi  r0, r0, 0x10
/* 089534 8008EAD4 901F0000 */  stw     r0, 0(r31)
/* 089538 8008EAD8 48000090 */  b       lbl_8008EB68
glabel lbl_8008EADC
/* 08953C 8008EADC 48018E89 */  bl      VIGetCurrentLine
/* 089540 8008EAE0 5460083C */  slwi    r0, r3, 1
/* 089544 8008EAE4 901E0000 */  stw     r0, 0(r30)
/* 089548 8008EAE8 801E0000 */  lwz     r0, 0(r30)
/* 08954C 8008EAEC 901F0000 */  stw     r0, 0(r31)
/* 089550 8008EAF0 48000078 */  b       lbl_8008EB68
glabel lbl_8008EAF4
/* 089554 8008EAF4 801E0018 */  lwz     r0, 0x18(r30)
/* 089558 8008EAF8 901F0000 */  stw     r0, 0(r31)
/* 08955C 8008EAFC 4800006C */  b       lbl_8008EB68
glabel lbl_8008EB00
/* 089560 8008EB00 801E0038 */  lwz     r0, 0x38(r30)
/* 089564 8008EB04 901F0000 */  stw     r0, 0(r31)
/* 089568 8008EB08 48000060 */  b       lbl_8008EB68
glabel lbl_8008EB0C
/* 08956C 8008EB0C 801E0034 */  lwz     r0, 0x34(r30)
/* 089570 8008EB10 901F0000 */  stw     r0, 0(r31)
/* 089574 8008EB14 48000054 */  b       lbl_8008EB68
glabel lbl_8008EB18
/* 089578 8008EB18 801E003C */  lwz     r0, 0x3c(r30)
/* 08957C 8008EB1C 901F0000 */  stw     r0, 0(r31)
/* 089580 8008EB20 48000048 */  b       lbl_8008EB68
glabel lbl_8008EB24
/* 089584 8008EB24 801E002C */  lwz     r0, 0x2c(r30)
/* 089588 8008EB28 901F0000 */  stw     r0, 0(r31)
/* 08958C 8008EB2C 4800003C */  b       lbl_8008EB68
glabel lbl_8008EB30
/* 089590 8008EB30 801E0030 */  lwz     r0, 0x30(r30)
/* 089594 8008EB34 901F0000 */  stw     r0, 0(r31)
/* 089598 8008EB38 48000030 */  b       lbl_8008EB68
glabel lbl_8008EB3C
/* 08959C 8008EB3C 801E0008 */  lwz     r0, 8(r30)
/* 0895A0 8008EB40 901F0000 */  stw     r0, 0(r31)
/* 0895A4 8008EB44 48000024 */  b       lbl_8008EB68
glabel lbl_8008EB48
/* 0895A8 8008EB48 801E0024 */  lwz     r0, 0x24(r30)
/* 0895AC 8008EB4C 901F0000 */  stw     r0, 0(r31)
/* 0895B0 8008EB50 48000018 */  b       lbl_8008EB68
glabel lbl_8008EB54
/* 0895B4 8008EB54 801E0028 */  lwz     r0, 0x28(r30)
/* 0895B8 8008EB58 901F0000 */  stw     r0, 0(r31)
/* 0895BC 8008EB5C 4800000C */  b       lbl_8008EB68
glabel lbl_8008EB60
/* 0895C0 8008EB60 38600000 */  li      r3, 0
/* 0895C4 8008EB64 48000008 */  b       lbl_8008EB6C
lbl_8008EB68:
/* 0895C8 8008EB68 38600001 */  li      r3, 1
lbl_8008EB6C:
/* 0895CC 8008EB6C 80010024 */  lwz     r0, 0x24(r1)
/* 0895D0 8008EB70 83E1001C */  lwz     r31, 0x1c(r1)
/* 0895D4 8008EB74 83C10018 */  lwz     r30, 0x18(r1)
/* 0895D8 8008EB78 7C0803A6 */  mtlr    r0
/* 0895DC 8008EB7C 38210020 */  addi    r1, r1, 0x20
/* 0895E0 8008EB80 4E800020 */  blr     

glabel videoGet16
/* 0895E4 8008EB84 38600000 */  li      r3, 0
/* 0895E8 8008EB88 4E800020 */  blr     

glabel videoGet8
/* 0895EC 8008EB8C 38600000 */  li      r3, 0
/* 0895F0 8008EB90 4E800020 */  blr     

glabel videoPut64
/* 0895F4 8008EB94 38600000 */  li      r3, 0
/* 0895F8 8008EB98 4E800020 */  blr     

glabel videoPut32
/* 0895FC 8008EB9C 7C0802A6 */  mflr    r0
/* 089600 8008EBA0 90010004 */  stw     r0, 4(r1)
/* 089604 8008EBA4 548006BE */  clrlwi  r0, r4, 0x1a
/* 089608 8008EBA8 28000034 */  cmplwi  r0, 0x34
/* 08960C 8008EBAC 9421FFD8 */  stwu    r1, -0x28(r1)
/* 089610 8008EBB0 93E10024 */  stw     r31, 0x24(r1)
/* 089614 8008EBB4 3BE30000 */  addi    r31, r3, 0
/* 089618 8008EBB8 93C10020 */  stw     r30, 0x20(r1)
/* 08961C 8008EBBC 93A1001C */  stw     r29, 0x1c(r1)
/* 089620 8008EBC0 41810228 */  bgt     lbl_8008EDE8
/* 089624 8008EBC4 3C60800F */  lis     r3, jtbl_800EE954@ha
/* 089628 8008EBC8 3863E954 */  addi    r3, r3, jtbl_800EE954@l
/* 08962C 8008EBCC 5400103A */  slwi    r0, r0, 2
/* 089630 8008EBD0 7C03002E */  lwzx    r0, r3, r0
/* 089634 8008EBD4 7C0903A6 */  mtctr   r0
/* 089638 8008EBD8 4E800420 */  bctr    
glabel lbl_8008EBDC
/* 08963C 8008EBDC 80050000 */  lwz     r0, 0(r5)
/* 089640 8008EBE0 5400043E */  clrlwi  r0, r0, 0x10
/* 089644 8008EBE4 901F0014 */  stw     r0, 0x14(r31)
/* 089648 8008EBE8 48000208 */  b       lbl_8008EDF0
glabel lbl_8008EBEC
/* 08964C 8008EBEC 80050000 */  lwz     r0, 0(r5)
/* 089650 8008EBF0 38810014 */  addi    r4, r1, 0x14
/* 089654 8008EBF4 38C00000 */  li      r6, 0
/* 089658 8008EBF8 5400023E */  clrlwi  r0, r0, 8
/* 08965C 8008EBFC 901F001C */  stw     r0, 0x1c(r31)
/* 089660 8008EC00 807F0010 */  lwz     r3, 0x10(r31)
/* 089664 8008EC04 80BF001C */  lwz     r5, 0x1c(r31)
/* 089668 8008EC08 80E30000 */  lwz     r7, 0(r3)
/* 08966C 8008EC0C 8063002C */  lwz     r3, 0x2c(r3)
/* 089670 8008EC10 3BC70000 */  addi    r30, r7, 0
/* 089674 8008EC14 3BA700F0 */  addi    r29, r7, 0xf0
/* 089678 8008EC18 4BFDE489 */  bl      ramGetBuffer
/* 08967C 8008EC1C 2C030000 */  cmpwi   r3, 0
/* 089680 8008EC20 4082000C */  bne     lbl_8008EC2C
/* 089684 8008EC24 38600000 */  li      r3, 0
/* 089688 8008EC28 480001CC */  b       lbl_8008EDF4
lbl_8008EC2C:
/* 08968C 8008EC2C 807D000C */  lwz     r3, 0xc(r29)
/* 089690 8008EC30 80010014 */  lwz     r0, 0x14(r1)
/* 089694 8008EC34 7C030040 */  cmplw   r3, r0
/* 089698 8008EC38 418201B8 */  beq     lbl_8008EDF0
/* 08969C 8008EC3C 38000000 */  li      r0, 0
/* 0896A0 8008EC40 901D0008 */  stw     r0, 8(r29)
/* 0896A4 8008EC44 38000002 */  li      r0, 2
/* 0896A8 8008EC48 387E0000 */  addi    r3, r30, 0
/* 0896AC 8008EC4C 901D0000 */  stw     r0, 0(r29)
/* 0896B0 8008EC50 38800002 */  li      r4, 2
/* 0896B4 8008EC54 801F000C */  lwz     r0, 0xc(r31)
/* 0896B8 8008EC58 901D0004 */  stw     r0, 4(r29)
/* 0896BC 8008EC5C 80010014 */  lwz     r0, 0x14(r1)
/* 0896C0 8008EC60 901D000C */  stw     r0, 0xc(r29)
/* 0896C4 8008EC64 4BF8EB95 */  bl      frameSetBuffer
/* 0896C8 8008EC68 2C030000 */  cmpwi   r3, 0
/* 0896CC 8008EC6C 40820184 */  bne     lbl_8008EDF0
/* 0896D0 8008EC70 38600000 */  li      r3, 0
/* 0896D4 8008EC74 48000180 */  b       lbl_8008EDF4
glabel lbl_8008EC78
/* 0896D8 8008EC78 80050000 */  lwz     r0, 0(r5)
/* 0896DC 8008EC7C 5400053E */  clrlwi  r0, r0, 0x14
/* 0896E0 8008EC80 901F000C */  stw     r0, 0xc(r31)
/* 0896E4 8008EC84 4800016C */  b       lbl_8008EDF0
glabel lbl_8008EC88
/* 0896E8 8008EC88 80050000 */  lwz     r0, 0(r5)
/* 0896EC 8008EC8C 540005BE */  clrlwi  r0, r0, 0x16
/* 0896F0 8008EC90 901F0020 */  stw     r0, 0x20(r31)
/* 0896F4 8008EC94 4800015C */  b       lbl_8008EDF0
glabel lbl_8008EC98
/* 0896F8 8008EC98 807F0010 */  lwz     r3, 0x10(r31)
/* 0896FC 8008EC9C 38801001 */  li      r4, 0x1001
/* 089700 8008ECA0 38A00008 */  li      r5, 8
/* 089704 8008ECA4 4BF78FC9 */  bl      xlObjectEvent
/* 089708 8008ECA8 3C000001 */  lis     r0, 1
/* 08970C 8008ECAC 901F0020 */  stw     r0, 0x20(r31)
/* 089710 8008ECB0 48000140 */  b       lbl_8008EDF0
glabel lbl_8008ECB4
/* 089714 8008ECB4 80050000 */  lwz     r0, 0(r5)
/* 089718 8008ECB8 901F0018 */  stw     r0, 0x18(r31)
/* 08971C 8008ECBC 48000134 */  b       lbl_8008EDF0
glabel lbl_8008ECC0
/* 089720 8008ECC0 80050000 */  lwz     r0, 0(r5)
/* 089724 8008ECC4 540005BE */  clrlwi  r0, r0, 0x16
/* 089728 8008ECC8 901F0038 */  stw     r0, 0x38(r31)
/* 08972C 8008ECCC 48000124 */  b       lbl_8008EDF0
glabel lbl_8008ECD0
/* 089730 8008ECD0 80050000 */  lwz     r0, 0(r5)
/* 089734 8008ECD4 540002FE */  clrlwi  r0, r0, 0xb
/* 089738 8008ECD8 901F0034 */  stw     r0, 0x34(r31)
/* 08973C 8008ECDC 48000114 */  b       lbl_8008EDF0
glabel lbl_8008ECE0
/* 089740 8008ECE0 80050000 */  lwz     r0, 0(r5)
/* 089744 8008ECE4 5400013E */  clrlwi  r0, r0, 4
/* 089748 8008ECE8 901F003C */  stw     r0, 0x3c(r31)
/* 08974C 8008ECEC 48000104 */  b       lbl_8008EDF0
glabel lbl_8008ECF0
/* 089750 8008ECF0 3C6003FF */  lis     r3, 0x3ff
/* 089754 8008ECF4 80850000 */  lwz     r4, 0(r5)
/* 089758 8008ECF8 380303FF */  addi    r0, r3, 0x3ff
/* 08975C 8008ECFC 7C800039 */  and.    r0, r4, r0
/* 089760 8008ED00 901F002C */  stw     r0, 0x2c(r31)
/* 089764 8008ED04 4082001C */  bne     lbl_8008ED20
/* 089768 8008ED08 801F0004 */  lwz     r0, 4(r31)
/* 08976C 8008ED0C 2C000001 */  cmpwi   r0, 1
/* 089770 8008ED10 418200E0 */  beq     lbl_8008EDF0
/* 089774 8008ED14 38000001 */  li      r0, 1
/* 089778 8008ED18 901F0004 */  stw     r0, 4(r31)
/* 08977C 8008ED1C 480000D4 */  b       lbl_8008EDF0
lbl_8008ED20:
/* 089780 8008ED20 801F0004 */  lwz     r0, 4(r31)
/* 089784 8008ED24 2C000000 */  cmpwi   r0, 0
/* 089788 8008ED28 418200C8 */  beq     lbl_8008EDF0
/* 08978C 8008ED2C 38000000 */  li      r0, 0
/* 089790 8008ED30 901F0004 */  stw     r0, 4(r31)
/* 089794 8008ED34 480000BC */  b       lbl_8008EDF0
glabel lbl_8008ED38
/* 089798 8008ED38 3C6003FF */  lis     r3, 0x3ff
/* 08979C 8008ED3C 80850000 */  lwz     r4, 0(r5)
/* 0897A0 8008ED40 380303FF */  addi    r0, r3, 0x3ff
/* 0897A4 8008ED44 7C800038 */  and     r0, r4, r0
/* 0897A8 8008ED48 901F0030 */  stw     r0, 0x30(r31)
/* 0897AC 8008ED4C 480000A4 */  b       lbl_8008EDF0
glabel lbl_8008ED50
/* 0897B0 8008ED50 3C6003FF */  lis     r3, 0x3ff
/* 0897B4 8008ED54 80850000 */  lwz     r4, 0(r5)
/* 0897B8 8008ED58 380303FF */  addi    r0, r3, 0x3ff
/* 0897BC 8008ED5C 7C800038 */  and     r0, r4, r0
/* 0897C0 8008ED60 901F0008 */  stw     r0, 8(r31)
/* 0897C4 8008ED64 4800008C */  b       lbl_8008EDF0
glabel lbl_8008ED68
/* 0897C8 8008ED68 80050000 */  lwz     r0, 0(r5)
/* 0897CC 8008ED6C 38800000 */  li      r4, 0
/* 0897D0 8008ED70 5400053E */  clrlwi  r0, r0, 0x14
/* 0897D4 8008ED74 901F0024 */  stw     r0, 0x24(r31)
/* 0897D8 8008ED78 801F0028 */  lwz     r0, 0x28(r31)
/* 0897DC 8008ED7C 807F0010 */  lwz     r3, 0x10(r31)
/* 0897E0 8008ED80 1C0000F0 */  mulli   r0, r0, 0xf0
/* 0897E4 8008ED84 80BF000C */  lwz     r5, 0xc(r31)
/* 0897E8 8008ED88 80630000 */  lwz     r3, 0(r3)
/* 0897EC 8008ED8C 7C065670 */  srawi   r6, r0, 0xa
/* 0897F0 8008ED90 7CC60194 */  addze   r6, r6
/* 0897F4 8008ED94 4BF91415 */  bl      frameSetSize
/* 0897F8 8008ED98 2C030000 */  cmpwi   r3, 0
/* 0897FC 8008ED9C 40820054 */  bne     lbl_8008EDF0
/* 089800 8008EDA0 38600000 */  li      r3, 0
/* 089804 8008EDA4 48000050 */  b       lbl_8008EDF4
glabel lbl_8008EDA8
/* 089808 8008EDA8 80050000 */  lwz     r0, 0(r5)
/* 08980C 8008EDAC 38800000 */  li      r4, 0
/* 089810 8008EDB0 5400053E */  clrlwi  r0, r0, 0x14
/* 089814 8008EDB4 901F0028 */  stw     r0, 0x28(r31)
/* 089818 8008EDB8 801F0028 */  lwz     r0, 0x28(r31)
/* 08981C 8008EDBC 807F0010 */  lwz     r3, 0x10(r31)
/* 089820 8008EDC0 1C0000F0 */  mulli   r0, r0, 0xf0
/* 089824 8008EDC4 80BF000C */  lwz     r5, 0xc(r31)
/* 089828 8008EDC8 80630000 */  lwz     r3, 0(r3)
/* 08982C 8008EDCC 7C065670 */  srawi   r6, r0, 0xa
/* 089830 8008EDD0 7CC60194 */  addze   r6, r6
/* 089834 8008EDD4 4BF913D5 */  bl      frameSetSize
/* 089838 8008EDD8 2C030000 */  cmpwi   r3, 0
/* 08983C 8008EDDC 40820014 */  bne     lbl_8008EDF0
/* 089840 8008EDE0 38600000 */  li      r3, 0
/* 089844 8008EDE4 48000010 */  b       lbl_8008EDF4
glabel lbl_8008EDE8
/* 089848 8008EDE8 38600000 */  li      r3, 0
/* 08984C 8008EDEC 48000008 */  b       lbl_8008EDF4
lbl_8008EDF0:
/* 089850 8008EDF0 38600001 */  li      r3, 1
lbl_8008EDF4:
/* 089854 8008EDF4 8001002C */  lwz     r0, 0x2c(r1)
/* 089858 8008EDF8 83E10024 */  lwz     r31, 0x24(r1)
/* 08985C 8008EDFC 83C10020 */  lwz     r30, 0x20(r1)
/* 089860 8008EE00 7C0803A6 */  mtlr    r0
/* 089864 8008EE04 83A1001C */  lwz     r29, 0x1c(r1)
/* 089868 8008EE08 38210028 */  addi    r1, r1, 0x28
/* 08986C 8008EE0C 4E800020 */  blr     

glabel videoPut16
/* 089870 8008EE10 38600000 */  li      r3, 0
/* 089874 8008EE14 4E800020 */  blr     

glabel videoPut8
/* 089878 8008EE18 38600000 */  li      r3, 0
/* 08987C 8008EE1C 4E800020 */  blr     


.section .data, "wa"

.balign 8

/* 000EB8F0 800EE870 0010 */
glabel gClassVideo
    .long D_80135318, 0x00000040, 0x00000000, videoEvent

.balign 4

/* 000EB900 800EE880 00D4 */
jtbl_800EE880:
    .long lbl_8008EAA8
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EAB4
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EAC0
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EACC
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EADC
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EAF4
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB00
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB0C
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB18
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB24
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB30
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB3C
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB48
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB60
    .long lbl_8008EB54

.balign 4

/* 000EB9D4 800EE954 00D4 */
jtbl_800EE954:
    .long lbl_8008EBDC
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EBEC
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EC78
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EC88
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EC98
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ECB4
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ECC0
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ECD0
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ECE0
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ECF0
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ED38
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ED50
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008ED68
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDE8
    .long lbl_8008EDA8


.section .sdata, "wa"

.balign 8

/* 000F1598 80135318 0006 */
D_80135318:
    .asciz "VIDEO"


