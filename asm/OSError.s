# OSError.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel OSPanic
/* 0990D8 8009E678 7C0802A6 */  mflr    r0
/* 0990DC 8009E67C 90010004 */  stw     r0, 4(r1)
/* 0990E0 8009E680 9421FF70 */  stwu    r1, -0x90(r1)
/* 0990E4 8009E684 93E1008C */  stw     r31, 0x8c(r1)
/* 0990E8 8009E688 93C10088 */  stw     r30, 0x88(r1)
/* 0990EC 8009E68C 93A10084 */  stw     r29, 0x84(r1)
/* 0990F0 8009E690 93810080 */  stw     r28, 0x80(r1)
/* 0990F4 8009E694 40860024 */  bne     cr1, lbl_8009E6B8
/* 0990F8 8009E698 D8210028 */  stfd    f1, 0x28(r1)
/* 0990FC 8009E69C D8410030 */  stfd    f2, 0x30(r1)
/* 099100 8009E6A0 D8610038 */  stfd    f3, 0x38(r1)
/* 099104 8009E6A4 D8810040 */  stfd    f4, 0x40(r1)
/* 099108 8009E6A8 D8A10048 */  stfd    f5, 0x48(r1)
/* 09910C 8009E6AC D8C10050 */  stfd    f6, 0x50(r1)
/* 099110 8009E6B0 D8E10058 */  stfd    f7, 0x58(r1)
/* 099114 8009E6B4 D9010060 */  stfd    f8, 0x60(r1)
lbl_8009E6B8:
/* 099118 8009E6B8 90610008 */  stw     r3, 8(r1)
/* 09911C 8009E6BC 3B830000 */  addi    r28, r3, 0
/* 099120 8009E6C0 3BC40000 */  addi    r30, r4, 0
/* 099124 8009E6C4 9081000C */  stw     r4, 0xc(r1)
/* 099128 8009E6C8 3BA50000 */  addi    r29, r5, 0
/* 09912C 8009E6CC 90A10010 */  stw     r5, 0x10(r1)
/* 099130 8009E6D0 90C10014 */  stw     r6, 0x14(r1)
/* 099134 8009E6D4 3CC0800F */  lis     r6, D_800F1050@ha
/* 099138 8009E6D8 3BE61050 */  addi    r31, r6, D_800F1050@l
/* 09913C 8009E6DC 90E10018 */  stw     r7, 0x18(r1)
/* 099140 8009E6E0 9101001C */  stw     r8, 0x1c(r1)
/* 099144 8009E6E4 91210020 */  stw     r9, 0x20(r1)
/* 099148 8009E6E8 91410024 */  stw     r10, 0x24(r1)
/* 09914C 8009E6EC 48000611 */  bl      OSDisableInterrupts
/* 099150 8009E6F0 3C000300 */  lis     r0, 0x300
/* 099154 8009E6F4 90010074 */  stw     r0, 0x74(r1)
/* 099158 8009E6F8 38010098 */  addi    r0, r1, 0x98
/* 09915C 8009E6FC 38810074 */  addi    r4, r1, 0x74
/* 099160 8009E700 90010078 */  stw     r0, 0x78(r1)
/* 099164 8009E704 38010008 */  addi    r0, r1, 8
/* 099168 8009E708 387D0000 */  addi    r3, r29, 0
/* 09916C 8009E70C 9001007C */  stw     r0, 0x7c(r1)
/* 099170 8009E710 48030779 */  bl      vprintf
/* 099174 8009E714 387F0000 */  addi    r3, r31, 0
/* 099178 8009E718 4CC63182 */  crclr   6
/* 09917C 8009E71C 389C0000 */  addi    r4, r28, 0
/* 099180 8009E720 38BE0000 */  addi    r5, r30, 0
/* 099184 8009E724 4BFFFED5 */  bl      OSReport
/* 099188 8009E728 387F0018 */  addi    r3, r31, 0x18
/* 09918C 8009E72C 4CC63182 */  crclr   6
/* 099190 8009E730 4BFFFEC9 */  bl      OSReport
/* 099194 8009E734 3BC00000 */  li      r30, 0
/* 099198 8009E738 4BFFFA65 */  bl      OSGetStackPointer
/* 09919C 8009E73C 7C7D1B78 */  mr      r29, r3
/* 0991A0 8009E740 48000020 */  b       lbl_8009E760
lbl_8009E744:
/* 0991A4 8009E744 80BD0000 */  lwz     r5, 0(r29)
/* 0991A8 8009E748 7FA4EB78 */  mr      r4, r29
/* 0991AC 8009E74C 80DD0004 */  lwz     r6, 4(r29)
/* 0991B0 8009E750 387F0040 */  addi    r3, r31, 0x40
/* 0991B4 8009E754 4CC63182 */  crclr   6
/* 0991B8 8009E758 4BFFFEA1 */  bl      OSReport
/* 0991BC 8009E75C 83BD0000 */  lwz     r29, 0(r29)
lbl_8009E760:
/* 0991C0 8009E760 281D0000 */  cmplwi  r29, 0
/* 0991C4 8009E764 4182001C */  beq     lbl_8009E780
/* 0991C8 8009E768 3C1D0001 */  addis   r0, r29, 1
/* 0991CC 8009E76C 2800FFFF */  cmplwi  r0, 0xffff
/* 0991D0 8009E770 41820010 */  beq     lbl_8009E780
/* 0991D4 8009E774 281E0010 */  cmplwi  r30, 0x10
/* 0991D8 8009E778 3BDE0001 */  addi    r30, r30, 1
/* 0991DC 8009E77C 4180FFC8 */  blt     lbl_8009E744
lbl_8009E780:
/* 0991E0 8009E780 4BFFD37D */  bl      PPCHalt
/* 0991E4 8009E784 80010094 */  lwz     r0, 0x94(r1)
/* 0991E8 8009E788 83E1008C */  lwz     r31, 0x8c(r1)
/* 0991EC 8009E78C 83C10088 */  lwz     r30, 0x88(r1)
/* 0991F0 8009E790 83A10084 */  lwz     r29, 0x84(r1)
/* 0991F4 8009E794 83810080 */  lwz     r28, 0x80(r1)
/* 0991F8 8009E798 38210090 */  addi    r1, r1, 0x90
/* 0991FC 8009E79C 7C0803A6 */  mtlr    r0
/* 099200 8009E7A0 4E800020 */  blr     

glabel OSSetErrorHandler
/* 099204 8009E7A4 7C0802A6 */  mflr    r0
/* 099208 8009E7A8 90010004 */  stw     r0, 4(r1)
/* 09920C 8009E7AC 9421FFD0 */  stwu    r1, -0x30(r1)
/* 099210 8009E7B0 93E1002C */  stw     r31, 0x2c(r1)
/* 099214 8009E7B4 93C10028 */  stw     r30, 0x28(r1)
/* 099218 8009E7B8 93A10024 */  stw     r29, 0x24(r1)
/* 09921C 8009E7BC 3BA30000 */  addi    r29, r3, 0
/* 099220 8009E7C0 93810020 */  stw     r28, 0x20(r1)
/* 099224 8009E7C4 3B840000 */  addi    r28, r4, 0
/* 099228 8009E7C8 48000535 */  bl      OSDisableInterrupts
/* 09922C 8009E7CC 3C808013 */  lis     r4, __OSErrorTable@ha
/* 099230 8009E7D0 57A513BA */  rlwinm  r5, r29, 2, 0xe, 0x1d
/* 099234 8009E7D4 38040F70 */  addi    r0, r4, __OSErrorTable@l
/* 099238 8009E7D8 57A6043E */  clrlwi  r6, r29, 0x10
/* 09923C 8009E7DC 7C802A14 */  add     r4, r0, r5
/* 099240 8009E7E0 83C40000 */  lwz     r30, 0(r4)
/* 099244 8009E7E4 28060010 */  cmplwi  r6, 0x10
/* 099248 8009E7E8 7C7D1B78 */  mr      r29, r3
/* 09924C 8009E7EC 93840000 */  stw     r28, 0(r4)
/* 099250 8009E7F0 408201A0 */  bne     lbl_8009E990
/* 099254 8009E7F4 4BFFD2C9 */  bl      PPCMfmsr
/* 099258 8009E7F8 3BE30000 */  addi    r31, r3, 0
/* 09925C 8009E7FC 63E32000 */  ori     r3, r31, 0x2000
/* 099260 8009E800 4BFFD2C5 */  bl      PPCMtmsr
/* 099264 8009E804 4BFFD33D */  bl      PPCMffpscr
/* 099268 8009E808 281C0000 */  cmplwi  r28, 0
/* 09926C 8009E80C 41820118 */  beq     lbl_8009E924
/* 099270 8009E810 3CA08000 */  lis     r5, 0x8000
/* 099274 8009E814 3C806006 */  lis     r4, 0x6006
/* 099278 8009E818 80C500DC */  lwz     r6, 0xdc(r5)
/* 09927C 8009E81C 3884F8FF */  addi    r4, r4, -1793
/* 099280 8009E820 480000E8 */  b       lbl_8009E908
lbl_8009E824:
/* 099284 8009E824 8006019C */  lwz     r0, 0x19c(r6)
/* 099288 8009E828 60000900 */  ori     r0, r0, 0x900
/* 09928C 8009E82C 9006019C */  stw     r0, 0x19c(r6)
/* 099290 8009E830 A0A601A2 */  lhz     r5, 0x1a2(r6)
/* 099294 8009E834 54A007FF */  clrlwi. r0, r5, 0x1f
/* 099298 8009E838 408200AC */  bne     lbl_8009E8E4
/* 09929C 8009E83C 60A50001 */  ori     r5, r5, 1
/* 0992A0 8009E840 38000004 */  li      r0, 4
/* 0992A4 8009E844 B0A601A2 */  sth     r5, 0x1a2(r6)
/* 0992A8 8009E848 7C0903A6 */  mtctr   r0
/* 0992AC 8009E84C 38A60000 */  addi    r5, r6, 0
lbl_8009E850:
/* 0992B0 8009E850 3800FFFF */  li      r0, -1
/* 0992B4 8009E854 90050094 */  stw     r0, 0x94(r5)
/* 0992B8 8009E858 90050090 */  stw     r0, 0x90(r5)
/* 0992BC 8009E85C 900501CC */  stw     r0, 0x1cc(r5)
/* 0992C0 8009E860 900501C8 */  stw     r0, 0x1c8(r5)
/* 0992C4 8009E864 9005009C */  stw     r0, 0x9c(r5)
/* 0992C8 8009E868 90050098 */  stw     r0, 0x98(r5)
/* 0992CC 8009E86C 900501D4 */  stw     r0, 0x1d4(r5)
/* 0992D0 8009E870 900501D0 */  stw     r0, 0x1d0(r5)
/* 0992D4 8009E874 900500A4 */  stw     r0, 0xa4(r5)
/* 0992D8 8009E878 900500A0 */  stw     r0, 0xa0(r5)
/* 0992DC 8009E87C 900501DC */  stw     r0, 0x1dc(r5)
/* 0992E0 8009E880 900501D8 */  stw     r0, 0x1d8(r5)
/* 0992E4 8009E884 900500AC */  stw     r0, 0xac(r5)
/* 0992E8 8009E888 900500A8 */  stw     r0, 0xa8(r5)
/* 0992EC 8009E88C 900501E4 */  stw     r0, 0x1e4(r5)
/* 0992F0 8009E890 900501E0 */  stw     r0, 0x1e0(r5)
/* 0992F4 8009E894 900500B4 */  stw     r0, 0xb4(r5)
/* 0992F8 8009E898 900500B0 */  stw     r0, 0xb0(r5)
/* 0992FC 8009E89C 900501EC */  stw     r0, 0x1ec(r5)
/* 099300 8009E8A0 900501E8 */  stw     r0, 0x1e8(r5)
/* 099304 8009E8A4 900500BC */  stw     r0, 0xbc(r5)
/* 099308 8009E8A8 900500B8 */  stw     r0, 0xb8(r5)
/* 09930C 8009E8AC 900501F4 */  stw     r0, 0x1f4(r5)
/* 099310 8009E8B0 900501F0 */  stw     r0, 0x1f0(r5)
/* 099314 8009E8B4 900500C4 */  stw     r0, 0xc4(r5)
/* 099318 8009E8B8 900500C0 */  stw     r0, 0xc0(r5)
/* 09931C 8009E8BC 900501FC */  stw     r0, 0x1fc(r5)
/* 099320 8009E8C0 900501F8 */  stw     r0, 0x1f8(r5)
/* 099324 8009E8C4 900500CC */  stw     r0, 0xcc(r5)
/* 099328 8009E8C8 900500C8 */  stw     r0, 0xc8(r5)
/* 09932C 8009E8CC 90050204 */  stw     r0, 0x204(r5)
/* 099330 8009E8D0 90050200 */  stw     r0, 0x200(r5)
/* 099334 8009E8D4 38A50040 */  addi    r5, r5, 0x40
/* 099338 8009E8D8 4200FF78 */  bdnz    lbl_8009E850
/* 09933C 8009E8DC 38000004 */  li      r0, 4
/* 099340 8009E8E0 90060194 */  stw     r0, 0x194(r6)
lbl_8009E8E4:
/* 099344 8009E8E4 800D8750 */  lwz     r0, __OSFpscrEnableBits-_SDA_BASE_(r13)
/* 099348 8009E8E8 80A60194 */  lwz     r5, 0x194(r6)
/* 09934C 8009E8EC 54000638 */  rlwinm  r0, r0, 0, 0x18, 0x1c
/* 099350 8009E8F0 7CA00378 */  or      r0, r5, r0
/* 099354 8009E8F4 90060194 */  stw     r0, 0x194(r6)
/* 099358 8009E8F8 80060194 */  lwz     r0, 0x194(r6)
/* 09935C 8009E8FC 7C002038 */  and     r0, r0, r4
/* 099360 8009E900 90060194 */  stw     r0, 0x194(r6)
/* 099364 8009E904 80C602FC */  lwz     r6, 0x2fc(r6)
lbl_8009E908:
/* 099368 8009E908 28060000 */  cmplwi  r6, 0
/* 09936C 8009E90C 4082FF18 */  bne     lbl_8009E824
/* 099370 8009E910 800D8750 */  lwz     r0, __OSFpscrEnableBits-_SDA_BASE_(r13)
/* 099374 8009E914 63FF0900 */  ori     r31, r31, 0x900
/* 099378 8009E918 54000638 */  rlwinm  r0, r0, 0, 0x18, 0x1c
/* 09937C 8009E91C 7C630378 */  or      r3, r3, r0
/* 099380 8009E920 48000058 */  b       lbl_8009E978
lbl_8009E924:
/* 099384 8009E924 3CA08000 */  lis     r5, 0x8000
/* 099388 8009E928 3C806006 */  lis     r4, 0x6006
/* 09938C 8009E92C 80C500DC */  lwz     r6, 0xdc(r5)
/* 099390 8009E930 3884F8FF */  addi    r4, r4, -1793
/* 099394 8009E934 38A0F6FF */  li      r5, -2305
/* 099398 8009E938 4800002C */  b       lbl_8009E964
lbl_8009E93C:
/* 09939C 8009E93C 8006019C */  lwz     r0, 0x19c(r6)
/* 0993A0 8009E940 7C002838 */  and     r0, r0, r5
/* 0993A4 8009E944 9006019C */  stw     r0, 0x19c(r6)
/* 0993A8 8009E948 80060194 */  lwz     r0, 0x194(r6)
/* 0993AC 8009E94C 5400076E */  rlwinm  r0, r0, 0, 0x1d, 0x17
/* 0993B0 8009E950 90060194 */  stw     r0, 0x194(r6)
/* 0993B4 8009E954 80060194 */  lwz     r0, 0x194(r6)
/* 0993B8 8009E958 7C002038 */  and     r0, r0, r4
/* 0993BC 8009E95C 90060194 */  stw     r0, 0x194(r6)
/* 0993C0 8009E960 80C602FC */  lwz     r6, 0x2fc(r6)
lbl_8009E964:
/* 0993C4 8009E964 28060000 */  cmplwi  r6, 0
/* 0993C8 8009E968 4082FFD4 */  bne     lbl_8009E93C
/* 0993CC 8009E96C 3800F6FF */  li      r0, -2305
/* 0993D0 8009E970 5463076E */  rlwinm  r3, r3, 0, 0x1d, 0x17
/* 0993D4 8009E974 7FFF0038 */  and     r31, r31, r0
lbl_8009E978:
/* 0993D8 8009E978 3C806006 */  lis     r4, 0x6006
/* 0993DC 8009E97C 3804F8FF */  addi    r0, r4, -1793
/* 0993E0 8009E980 7C630038 */  and     r3, r3, r0
/* 0993E4 8009E984 4BFFD1DD */  bl      PPCMtfpscr
/* 0993E8 8009E988 7FE3FB78 */  mr      r3, r31
/* 0993EC 8009E98C 4BFFD139 */  bl      PPCMtmsr
lbl_8009E990:
/* 0993F0 8009E990 7FA3EB78 */  mr      r3, r29
/* 0993F4 8009E994 48000391 */  bl      OSRestoreInterrupts
/* 0993F8 8009E998 7FC3F378 */  mr      r3, r30
/* 0993FC 8009E99C 80010034 */  lwz     r0, 0x34(r1)
/* 099400 8009E9A0 83E1002C */  lwz     r31, 0x2c(r1)
/* 099404 8009E9A4 83C10028 */  lwz     r30, 0x28(r1)
/* 099408 8009E9A8 83A10024 */  lwz     r29, 0x24(r1)
/* 09940C 8009E9AC 83810020 */  lwz     r28, 0x20(r1)
/* 099410 8009E9B0 38210030 */  addi    r1, r1, 0x30
/* 099414 8009E9B4 7C0803A6 */  mtlr    r0
/* 099418 8009E9B8 4E800020 */  blr     

glabel __OSUnhandledException
/* 09941C 8009E9BC 7C0802A6 */  mflr    r0
/* 099420 8009E9C0 3D008013 */  lis     r8, __OSErrorTable@ha
/* 099424 8009E9C4 90010004 */  stw     r0, 4(r1)
/* 099428 8009E9C8 3CE0800F */  lis     r7, D_800F1050@ha
/* 09942C 8009E9CC 9421FFC0 */  stwu    r1, -0x40(r1)
/* 099430 8009E9D0 BEC10018 */  stmw    r22, 0x18(r1)
/* 099434 8009E9D4 3B030000 */  addi    r24, r3, 0
/* 099438 8009E9D8 3B240000 */  addi    r25, r4, 0
/* 09943C 8009E9DC 3B450000 */  addi    r26, r5, 0
/* 099440 8009E9E0 3B660000 */  addi    r27, r6, 0
/* 099444 8009E9E4 3BC80F70 */  addi    r30, r8, __OSErrorTable@l
/* 099448 8009E9E8 3BE71050 */  addi    r31, r7, D_800F1050@l
/* 09944C 8009E9EC 480038BD */  bl      OSGetTime
/* 099450 8009E9F0 80B9019C */  lwz     r5, 0x19c(r25)
/* 099454 8009E9F4 3B840000 */  addi    r28, r4, 0
/* 099458 8009E9F8 3BA30000 */  addi    r29, r3, 0
/* 09945C 8009E9FC 54A007BD */  rlwinm. r0, r5, 0, 0x1e, 0x1e
/* 099460 8009EA00 40820018 */  bne     lbl_8009EA18
/* 099464 8009EA04 387F005C */  addi    r3, r31, 0x5c
/* 099468 8009EA08 4CC63182 */  crclr   6
/* 09946C 8009EA0C 5704063E */  clrlwi  r4, r24, 0x18
/* 099470 8009EA10 4BFFFBE9 */  bl      OSReport
/* 099474 8009EA14 48000154 */  b       lbl_8009EB68
lbl_8009EA18:
/* 099478 8009EA18 5700063E */  clrlwi  r0, r24, 0x18
/* 09947C 8009EA1C 28000006 */  cmplwi  r0, 6
/* 099480 8009EA20 408200D8 */  bne     lbl_8009EAF8
/* 099484 8009EA24 54A002D7 */  rlwinm. r0, r5, 0, 0xb, 0xb
/* 099488 8009EA28 418200D0 */  beq     lbl_8009EAF8
/* 09948C 8009EA2C 801E0040 */  lwz     r0, 0x40(r30)
/* 099490 8009EA30 28000000 */  cmplwi  r0, 0
/* 099494 8009EA34 418200C4 */  beq     lbl_8009EAF8
/* 099498 8009EA38 3B000010 */  li      r24, 0x10
/* 09949C 8009EA3C 4BFFD081 */  bl      PPCMfmsr
/* 0994A0 8009EA40 3AE30000 */  addi    r23, r3, 0
/* 0994A4 8009EA44 62E32000 */  ori     r3, r23, 0x2000
/* 0994A8 8009EA48 4BFFD07D */  bl      PPCMtmsr
/* 0994AC 8009EA4C 3C608000 */  lis     r3, 0x8000
/* 0994B0 8009EA50 806300D8 */  lwz     r3, 0xd8(r3)
/* 0994B4 8009EA54 28030000 */  cmplwi  r3, 0
/* 0994B8 8009EA58 41820008 */  beq     lbl_8009EA60
/* 0994BC 8009EA5C 4BFFF579 */  bl      OSSaveFPUContext
lbl_8009EA60:
/* 0994C0 8009EA60 4BFFD0E1 */  bl      PPCMffpscr
/* 0994C4 8009EA64 3C806006 */  lis     r4, 0x6006
/* 0994C8 8009EA68 3AC4F8FF */  addi    r22, r4, -1793
/* 0994CC 8009EA6C 7C63B038 */  and     r3, r3, r22
/* 0994D0 8009EA70 4BFFD0F1 */  bl      PPCMtfpscr
/* 0994D4 8009EA74 7EE3BB78 */  mr      r3, r23
/* 0994D8 8009EA78 4BFFD04D */  bl      PPCMtmsr
/* 0994DC 8009EA7C 3EE08000 */  lis     r23, 0x8000
/* 0994E0 8009EA80 801700D8 */  lwz     r0, 0xd8(r23)
/* 0994E4 8009EA84 7C00C840 */  cmplw   r0, r25
/* 0994E8 8009EA88 40820054 */  bne     lbl_8009EADC
/* 0994EC 8009EA8C 480027C5 */  bl      OSDisableScheduler
/* 0994F0 8009EA90 819E0040 */  lwz     r12, 0x40(r30)
/* 0994F4 8009EA94 38990000 */  addi    r4, r25, 0
/* 0994F8 8009EA98 38BA0000 */  addi    r5, r26, 0
/* 0994FC 8009EA9C 4CC63182 */  crclr   6
/* 099500 8009EAA0 7D8803A6 */  mtlr    r12
/* 099504 8009EAA4 38DB0000 */  addi    r6, r27, 0
/* 099508 8009EAA8 38600010 */  li      r3, 0x10
/* 09950C 8009EAAC 4E800021 */  blrl    
/* 099510 8009EAB0 8079019C */  lwz     r3, 0x19c(r25)
/* 099514 8009EAB4 38000000 */  li      r0, 0
/* 099518 8009EAB8 546304E2 */  rlwinm  r3, r3, 0, 0x13, 0x11
/* 09951C 8009EABC 9079019C */  stw     r3, 0x19c(r25)
/* 099520 8009EAC0 901700D8 */  stw     r0, 0xd8(r23)
/* 099524 8009EAC4 80190194 */  lwz     r0, 0x194(r25)
/* 099528 8009EAC8 7C00B038 */  and     r0, r0, r22
/* 09952C 8009EACC 90190194 */  stw     r0, 0x194(r25)
/* 099530 8009EAD0 480027C1 */  bl      OSEnableScheduler
/* 099534 8009EAD4 48002C89 */  bl      __OSReschedule
/* 099538 8009EAD8 48000018 */  b       lbl_8009EAF0
lbl_8009EADC:
/* 09953C 8009EADC 8079019C */  lwz     r3, 0x19c(r25)
/* 099540 8009EAE0 38000000 */  li      r0, 0
/* 099544 8009EAE4 546304E2 */  rlwinm  r3, r3, 0, 0x13, 0x11
/* 099548 8009EAE8 9079019C */  stw     r3, 0x19c(r25)
/* 09954C 8009EAEC 901700D8 */  stw     r0, 0xd8(r23)
lbl_8009EAF0:
/* 099550 8009EAF0 7F23CB78 */  mr      r3, r25
/* 099554 8009EAF4 4BFFF5D1 */  bl      OSLoadContext
lbl_8009EAF8:
/* 099558 8009EAF8 5717063E */  clrlwi  r23, r24, 0x18
/* 09955C 8009EAFC 570015BA */  rlwinm  r0, r24, 2, 0x16, 0x1d
/* 099560 8009EB00 7EDE0214 */  add     r22, r30, r0
/* 099564 8009EB04 80160000 */  lwz     r0, 0(r22)
/* 099568 8009EB08 28000000 */  cmplwi  r0, 0
/* 09956C 8009EB0C 41820038 */  beq     lbl_8009EB44
/* 099570 8009EB10 48002741 */  bl      OSDisableScheduler
/* 099574 8009EB14 81960000 */  lwz     r12, 0(r22)
/* 099578 8009EB18 38770000 */  addi    r3, r23, 0
/* 09957C 8009EB1C 38990000 */  addi    r4, r25, 0
/* 099580 8009EB20 4CC63182 */  crclr   6
/* 099584 8009EB24 7D8803A6 */  mtlr    r12
/* 099588 8009EB28 38BA0000 */  addi    r5, r26, 0
/* 09958C 8009EB2C 38DB0000 */  addi    r6, r27, 0
/* 099590 8009EB30 4E800021 */  blrl    
/* 099594 8009EB34 4800275D */  bl      OSEnableScheduler
/* 099598 8009EB38 48002C25 */  bl      __OSReschedule
/* 09959C 8009EB3C 7F23CB78 */  mr      r3, r25
/* 0995A0 8009EB40 4BFFF585 */  bl      OSLoadContext
lbl_8009EB44:
/* 0995A4 8009EB44 5700063E */  clrlwi  r0, r24, 0x18
/* 0995A8 8009EB48 28000008 */  cmplwi  r0, 8
/* 0995AC 8009EB4C 4082000C */  bne     lbl_8009EB58
/* 0995B0 8009EB50 7F23CB78 */  mr      r3, r25
/* 0995B4 8009EB54 4BFFF571 */  bl      OSLoadContext
lbl_8009EB58:
/* 0995B8 8009EB58 387F007C */  addi    r3, r31, 0x7c
/* 0995BC 8009EB5C 4CC63182 */  crclr   6
/* 0995C0 8009EB60 5704063E */  clrlwi  r4, r24, 0x18
/* 0995C4 8009EB64 4BFFFA95 */  bl      OSReport
lbl_8009EB68:
/* 0995C8 8009EB68 386D8754 */  addi    r3, r13, D_80135434-_SDA_BASE_
/* 0995CC 8009EB6C 4CC63182 */  crclr   6
/* 0995D0 8009EB70 4BFFFA89 */  bl      OSReport
/* 0995D4 8009EB74 7F23CB78 */  mr      r3, r25
/* 0995D8 8009EB78 4BFFF70D */  bl      OSDumpContext
/* 0995DC 8009EB7C 389A0000 */  addi    r4, r26, 0
/* 0995E0 8009EB80 4CC63182 */  crclr   6
/* 0995E4 8009EB84 38BB0000 */  addi    r5, r27, 0
/* 0995E8 8009EB88 387F0094 */  addi    r3, r31, 0x94
/* 0995EC 8009EB8C 4BFFFA6D */  bl      OSReport
/* 0995F0 8009EB90 38DC0000 */  addi    r6, r28, 0
/* 0995F4 8009EB94 4CC63182 */  crclr   6
/* 0995F8 8009EB98 38BD0000 */  addi    r5, r29, 0
/* 0995FC 8009EB9C 387F00C8 */  addi    r3, r31, 0xc8
/* 099600 8009EBA0 4BFFFA59 */  bl      OSReport
/* 099604 8009EBA4 5700063E */  clrlwi  r0, r24, 0x18
/* 099608 8009EBA8 2800000F */  cmplwi  r0, 0xf
/* 09960C 8009EBAC 418100C4 */  bgt     lbl_8009EC70
/* 099610 8009EBB0 3C60800F */  lis     r3, jtbl_800F132C@ha
/* 099614 8009EBB4 3863132C */  addi    r3, r3, jtbl_800F132C@l
/* 099618 8009EBB8 5400103A */  slwi    r0, r0, 2
/* 09961C 8009EBBC 7C03002E */  lwzx    r0, r3, r0
/* 099620 8009EBC0 7C0903A6 */  mtctr   r0
/* 099624 8009EBC4 4E800420 */  bctr    
glabel lbl_8009EBC8
/* 099628 8009EBC8 80990198 */  lwz     r4, 0x198(r25)
/* 09962C 8009EBCC 38BB0000 */  addi    r5, r27, 0
/* 099630 8009EBD0 387F00D8 */  addi    r3, r31, 0xd8
/* 099634 8009EBD4 4CC63182 */  crclr   6
/* 099638 8009EBD8 4BFFFA21 */  bl      OSReport
/* 09963C 8009EBDC 48000094 */  b       lbl_8009EC70
glabel lbl_8009EBE0
/* 099640 8009EBE0 80990198 */  lwz     r4, 0x198(r25)
/* 099644 8009EBE4 387F0138 */  addi    r3, r31, 0x138
/* 099648 8009EBE8 4CC63182 */  crclr   6
/* 09964C 8009EBEC 4BFFFA0D */  bl      OSReport
/* 099650 8009EBF0 48000080 */  b       lbl_8009EC70
glabel lbl_8009EBF4
/* 099654 8009EBF4 80990198 */  lwz     r4, 0x198(r25)
/* 099658 8009EBF8 38BB0000 */  addi    r5, r27, 0
/* 09965C 8009EBFC 387F0184 */  addi    r3, r31, 0x184
/* 099660 8009EC00 4CC63182 */  crclr   6
/* 099664 8009EC04 4BFFF9F5 */  bl      OSReport
/* 099668 8009EC08 48000068 */  b       lbl_8009EC70
glabel lbl_8009EC0C
/* 09966C 8009EC0C 80990198 */  lwz     r4, 0x198(r25)
/* 099670 8009EC10 38BB0000 */  addi    r5, r27, 0
/* 099674 8009EC14 387F01E8 */  addi    r3, r31, 0x1e8
/* 099678 8009EC18 4CC63182 */  crclr   6
/* 09967C 8009EC1C 4BFFF9DD */  bl      OSReport
/* 099680 8009EC20 48000050 */  b       lbl_8009EC70
glabel lbl_8009EC24
/* 099684 8009EC24 386D8754 */  addi    r3, r13, D_80135434-_SDA_BASE_
/* 099688 8009EC28 4CC63182 */  crclr   6
/* 09968C 8009EC2C 4BFFF9CD */  bl      OSReport
/* 099690 8009EC30 3F20CC00 */  lis     r25, 0xcc00
/* 099694 8009EC34 4CC63182 */  crclr   6
/* 099698 8009EC38 3B195000 */  addi    r24, r25, 0x5000
/* 09969C 8009EC3C A0995030 */  lhz     r4, 0x5030(r25)
/* 0996A0 8009EC40 387F0248 */  addi    r3, r31, 0x248
/* 0996A4 8009EC44 A0B95032 */  lhz     r5, 0x5032(r25)
/* 0996A8 8009EC48 4BFFF9B1 */  bl      OSReport
/* 0996AC 8009EC4C A0980020 */  lhz     r4, 0x20(r24)
/* 0996B0 8009EC50 387F0268 */  addi    r3, r31, 0x268
/* 0996B4 8009EC54 A0B80022 */  lhz     r5, 0x22(r24)
/* 0996B8 8009EC58 4CC63182 */  crclr   6
/* 0996BC 8009EC5C 4BFFF99D */  bl      OSReport
/* 0996C0 8009EC60 80996014 */  lwz     r4, 0x6014(r25)
/* 0996C4 8009EC64 4CC63182 */  crclr   6
/* 0996C8 8009EC68 387F0288 */  addi    r3, r31, 0x288
/* 0996CC 8009EC6C 4BFFF98D */  bl      OSReport
glabel lbl_8009EC70
/* 0996D0 8009EC70 A88D8B38 */  lha     r4, __OSLastInterrupt-_SDA_BASE_(r13)
/* 0996D4 8009EC74 387F02A4 */  addi    r3, r31, 0x2a4
/* 0996D8 8009EC78 4CC63182 */  crclr   6
/* 0996DC 8009EC7C 80AD8B34 */  lwz     r5, __OSLastInterruptSrr0-_SDA_BASE_(r13)
/* 0996E0 8009EC80 80ED8B40 */  lwz     r7, __OSLastInterruptTime-_SDA_BASE_(r13)
/* 0996E4 8009EC84 810D8B44 */  lwz     r8, (__OSLastInterruptTime + 4)-_SDA_BASE_(r13)
/* 0996E8 8009EC88 4BFFF971 */  bl      OSReport
/* 0996EC 8009EC8C 4BFFCE71 */  bl      PPCHalt
/* 0996F0 8009EC90 BAC10018 */  lmw     r22, 0x18(r1)
/* 0996F4 8009EC94 80010044 */  lwz     r0, 0x44(r1)
/* 0996F8 8009EC98 38210040 */  addi    r1, r1, 0x40
/* 0996FC 8009EC9C 7C0803A6 */  mtlr    r0
/* 099700 8009ECA0 4E800020 */  blr     


.section .data, "wa"

.balign 8

/* 000EE0D0 800F1050 0016 */
D_800F1050:
    .asciz " in \"%s\" on line %d.\n"

.balign 4

/* 000EE0E8 800F1068 0026 */
D_800F1068:
    .asciz "\nAddress:      Back Chain    LR Save\n"

.balign 4

/* 000EE110 800F1090 001C */
D_800F1090:
    .asciz "0x%08x:   0x%08x    0x%08x\n"

.balign 4

/* 000EE12C 800F10AC 001D */
D_800F10AC:
    .asciz "Non-recoverable Exception %d"

.balign 4

/* 000EE14C 800F10CC 0017 */
D_800F10CC:
    .asciz "Unhandled Exception %d"

.balign 4

/* 000EE164 800F10E4 0031 */
D_800F10E4:
    .asciz "\nDSISR = 0x%08x                   DAR  = 0x%08x\n"

.balign 4

/* 000EE198 800F1118 0010 */
D_800F1118:
    .asciz "TB = 0x%016llx\n"

.balign 4

/* 000EE1A8 800F1128 0060 */
D_800F1128:
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n"

.balign 4

/* 000EE208 800F1188 004C */
D_800F1188:
    .asciz "\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n"

.balign 4

/* 000EE254 800F11D4 0062 */
D_800F11D4:
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n"

.balign 4

/* 000EE2B8 800F1238 0060 */
D_800F1238:
    .asciz "\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n"

.balign 4

/* 000EE318 800F1298 001F */
D_800F1298:
    .asciz "AI DMA Address =   0x%04x%04x\n"

.balign 4

/* 000EE338 800F12B8 001F */
D_800F12B8:
    .asciz "ARAM DMA Address = 0x%04x%04x\n"

.balign 4

/* 000EE358 800F12D8 001B */
D_800F12D8:
    .asciz "DI DMA Address =   0x%08x\n"

.balign 4

/* 000EE374 800F12F4 0035 */
D_800F12F4:
    .asciz "\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n"

.balign 4

/* 000EE3AC 800F132C 0040 */
jtbl_800F132C:
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EBC8
    .long lbl_8009EBE0
    .long lbl_8009EC70
    .long lbl_8009EBF4
    .long lbl_8009EC0C
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC70
    .long lbl_8009EC24


.section .bss, "wa"

.balign 4

/* 0012DFF0 80130F70 0044 */
glabel __OSErrorTable
    .skip 68


.section .sdata, "wa"

.balign 8

/* 000F16B0 80135430 0004 */
glabel __OSFpscrEnableBits
    .long 0x000000F8

.balign 4

/* 000F16B4 80135434 0002 */
D_80135434:
    .asciz "\n"


