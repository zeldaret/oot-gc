glabel cpuEvent
/* 02F2C4 80034864 7C0802A6 */  mflr    r0
/* 02F2C8 80034868 2C040003 */  cmpwi   r4, 3
/* 02F2CC 8003486C 90010004 */  stw     r0, 4(r1)
/* 02F2D0 80034870 9421FFD0 */  stwu    r1, -0x30(r1)
/* 02F2D4 80034874 93E1002C */  stw     r31, 0x2c(r1)
/* 02F2D8 80034878 93C10028 */  stw     r30, 0x28(r1)
/* 02F2DC 8003487C 93A10024 */  stw     r29, 0x24(r1)
/* 02F2E0 80034880 93810020 */  stw     r28, 0x20(r1)
/* 02F2E4 80034884 3B830000 */  addi    r28, r3, 0
/* 02F2E8 80034888 4182015C */  beq     lbl_800349E4
/* 02F2EC 8003488C 40800018 */  bge     lbl_800348A4
/* 02F2F0 80034890 2C040002 */  cmpwi   r4, 2
/* 02F2F4 80034894 4080001C */  bge     lbl_800348B0
/* 02F2F8 80034898 2C040000 */  cmpwi   r4, 0
/* 02F2FC 8003489C 408001AC */  bge     lbl_80034A48
/* 02F300 800348A0 480001A0 */  b       lbl_80034A40
lbl_800348A4:
/* 02F304 800348A4 2C041003 */  cmpwi   r4, 0x1003
/* 02F308 800348A8 418201A0 */  beq     lbl_80034A48
/* 02F30C 800348AC 48000194 */  b       lbl_80034A40
lbl_800348B0:
/* 02F310 800348B0 38000004 */  li      r0, 4
/* 02F314 800348B4 90BC0008 */  stw     r5, 8(r28)
/* 02F318 800348B8 7C0903A6 */  mtctr   r0
/* 02F31C 800348BC 387C0000 */  addi    r3, r28, 0
/* 02F320 800348C0 38000000 */  li      r0, 0
lbl_800348C4:
/* 02F324 800348C4 90030B64 */  stw     r0, 0xb64(r3)
/* 02F328 800348C8 90030B68 */  stw     r0, 0xb68(r3)
/* 02F32C 800348CC 90030B6C */  stw     r0, 0xb6c(r3)
/* 02F330 800348D0 90030B70 */  stw     r0, 0xb70(r3)
/* 02F334 800348D4 90030B74 */  stw     r0, 0xb74(r3)
/* 02F338 800348D8 90030B78 */  stw     r0, 0xb78(r3)
/* 02F33C 800348DC 90030B7C */  stw     r0, 0xb7c(r3)
/* 02F340 800348E0 90030B80 */  stw     r0, 0xb80(r3)
/* 02F344 800348E4 90030B84 */  stw     r0, 0xb84(r3)
/* 02F348 800348E8 90030B88 */  stw     r0, 0xb88(r3)
/* 02F34C 800348EC 90030B8C */  stw     r0, 0xb8c(r3)
/* 02F350 800348F0 90030B90 */  stw     r0, 0xb90(r3)
/* 02F354 800348F4 90030B94 */  stw     r0, 0xb94(r3)
/* 02F358 800348F8 90030B98 */  stw     r0, 0xb98(r3)
/* 02F35C 800348FC 90030B9C */  stw     r0, 0xb9c(r3)
/* 02F360 80034900 90030BA0 */  stw     r0, 0xba0(r3)
/* 02F364 80034904 90030BA4 */  stw     r0, 0xba4(r3)
/* 02F368 80034908 90030BA8 */  stw     r0, 0xba8(r3)
/* 02F36C 8003490C 90030BAC */  stw     r0, 0xbac(r3)
/* 02F370 80034910 90030BB0 */  stw     r0, 0xbb0(r3)
/* 02F374 80034914 90030BB4 */  stw     r0, 0xbb4(r3)
/* 02F378 80034918 90030BB8 */  stw     r0, 0xbb8(r3)
/* 02F37C 8003491C 90030BBC */  stw     r0, 0xbbc(r3)
/* 02F380 80034920 90030BC0 */  stw     r0, 0xbc0(r3)
/* 02F384 80034924 90030BC4 */  stw     r0, 0xbc4(r3)
/* 02F388 80034928 90030BC8 */  stw     r0, 0xbc8(r3)
/* 02F38C 8003492C 90030BCC */  stw     r0, 0xbcc(r3)
/* 02F390 80034930 90030BD0 */  stw     r0, 0xbd0(r3)
/* 02F394 80034934 90030BD4 */  stw     r0, 0xbd4(r3)
/* 02F398 80034938 90030BD8 */  stw     r0, 0xbd8(r3)
/* 02F39C 8003493C 90030BDC */  stw     r0, 0xbdc(r3)
/* 02F3A0 80034940 90030BE0 */  stw     r0, 0xbe0(r3)
/* 02F3A4 80034944 90030BE4 */  stw     r0, 0xbe4(r3)
/* 02F3A8 80034948 90030BE8 */  stw     r0, 0xbe8(r3)
/* 02F3AC 8003494C 90030BEC */  stw     r0, 0xbec(r3)
/* 02F3B0 80034950 90030BF0 */  stw     r0, 0xbf0(r3)
/* 02F3B4 80034954 90030BF4 */  stw     r0, 0xbf4(r3)
/* 02F3B8 80034958 90030BF8 */  stw     r0, 0xbf8(r3)
/* 02F3BC 8003495C 90030BFC */  stw     r0, 0xbfc(r3)
/* 02F3C0 80034960 90030C00 */  stw     r0, 0xc00(r3)
/* 02F3C4 80034964 90030C04 */  stw     r0, 0xc04(r3)
/* 02F3C8 80034968 90030C08 */  stw     r0, 0xc08(r3)
/* 02F3CC 8003496C 90030C0C */  stw     r0, 0xc0c(r3)
/* 02F3D0 80034970 90030C10 */  stw     r0, 0xc10(r3)
/* 02F3D4 80034974 90030C14 */  stw     r0, 0xc14(r3)
/* 02F3D8 80034978 90030C18 */  stw     r0, 0xc18(r3)
/* 02F3DC 8003497C 90030C1C */  stw     r0, 0xc1c(r3)
/* 02F3E0 80034980 90030C20 */  stw     r0, 0xc20(r3)
/* 02F3E4 80034984 90030C24 */  stw     r0, 0xc24(r3)
/* 02F3E8 80034988 90030C28 */  stw     r0, 0xc28(r3)
/* 02F3EC 8003498C 90030C2C */  stw     r0, 0xc2c(r3)
/* 02F3F0 80034990 90030C30 */  stw     r0, 0xc30(r3)
/* 02F3F4 80034994 90030C34 */  stw     r0, 0xc34(r3)
/* 02F3F8 80034998 90030C38 */  stw     r0, 0xc38(r3)
/* 02F3FC 8003499C 90030C3C */  stw     r0, 0xc3c(r3)
/* 02F400 800349A0 90030C40 */  stw     r0, 0xc40(r3)
/* 02F404 800349A4 90030C44 */  stw     r0, 0xc44(r3)
/* 02F408 800349A8 90030C48 */  stw     r0, 0xc48(r3)
/* 02F40C 800349AC 90030C4C */  stw     r0, 0xc4c(r3)
/* 02F410 800349B0 90030C50 */  stw     r0, 0xc50(r3)
/* 02F414 800349B4 90030C54 */  stw     r0, 0xc54(r3)
/* 02F418 800349B8 90030C58 */  stw     r0, 0xc58(r3)
/* 02F41C 800349BC 90030C5C */  stw     r0, 0xc5c(r3)
/* 02F420 800349C0 90030C60 */  stw     r0, 0xc60(r3)
/* 02F424 800349C4 38630100 */  addi    r3, r3, 0x100
/* 02F428 800349C8 4200FEFC */  bdnz    lbl_800348C4
/* 02F42C 800349CC 7F83E378 */  mr      r3, r28
/* 02F430 800349D0 48000119 */  bl      cpuReset
/* 02F434 800349D4 2C030000 */  cmpwi   r3, 0
/* 02F438 800349D8 40820070 */  bne     lbl_80034A48
/* 02F43C 800349DC 38600000 */  li      r3, 0
/* 02F440 800349E0 4800006C */  b       lbl_80034A4C
lbl_800349E4:
/* 02F444 800349E4 3BC00000 */  li      r30, 0
/* 02F448 800349E8 3BBC0000 */  addi    r29, r28, 0
/* 02F44C 800349EC 3BFE0000 */  addi    r31, r30, 0
lbl_800349F0:
/* 02F450 800349F0 801D0B64 */  lwz     r0, 0xb64(r29)
/* 02F454 800349F4 28000000 */  cmplwi  r0, 0
/* 02F458 800349F8 41820020 */  beq     lbl_80034A18
/* 02F45C 800349FC 387C0000 */  addi    r3, r28, 0
/* 02F460 80034A00 389E0000 */  addi    r4, r30, 0
/* 02F464 80034A04 48001495 */  bl      cpuFreeDevice
/* 02F468 80034A08 2C030000 */  cmpwi   r3, 0
/* 02F46C 80034A0C 40820010 */  bne     lbl_80034A1C
/* 02F470 80034A10 38000000 */  li      r0, 0
/* 02F474 80034A14 4800001C */  b       lbl_80034A30
lbl_80034A18:
/* 02F478 80034A18 93FD0B64 */  stw     r31, 0xb64(r29)
lbl_80034A1C:
/* 02F47C 80034A1C 3BDE0001 */  addi    r30, r30, 1
/* 02F480 80034A20 2C1E0100 */  cmpwi   r30, 0x100
/* 02F484 80034A24 3BBD0004 */  addi    r29, r29, 4
/* 02F488 80034A28 4180FFC8 */  blt     lbl_800349F0
/* 02F48C 80034A2C 38000001 */  li      r0, 1
lbl_80034A30:
/* 02F490 80034A30 2C000000 */  cmpwi   r0, 0
/* 02F494 80034A34 40820014 */  bne     lbl_80034A48
/* 02F498 80034A38 38600000 */  li      r3, 0
/* 02F49C 80034A3C 48000010 */  b       lbl_80034A4C
lbl_80034A40:
/* 02F4A0 80034A40 38600000 */  li      r3, 0
/* 02F4A4 80034A44 48000008 */  b       lbl_80034A4C
lbl_80034A48:
/* 02F4A8 80034A48 38600001 */  li      r3, 1
lbl_80034A4C:
/* 02F4AC 80034A4C 80010034 */  lwz     r0, 0x34(r1)
/* 02F4B0 80034A50 83E1002C */  lwz     r31, 0x2c(r1)
/* 02F4B4 80034A54 83C10028 */  lwz     r30, 0x28(r1)
/* 02F4B8 80034A58 7C0803A6 */  mtlr    r0
/* 02F4BC 80034A5C 83A10024 */  lwz     r29, 0x24(r1)
/* 02F4C0 80034A60 83810020 */  lwz     r28, 0x20(r1)
/* 02F4C4 80034A64 38210030 */  addi    r1, r1, 0x30
/* 02F4C8 80034A68 4E800020 */  blr     
