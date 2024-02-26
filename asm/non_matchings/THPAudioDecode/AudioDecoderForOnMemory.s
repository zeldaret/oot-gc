glabel AudioDecoderForOnMemory
/* 00B938 80010ED8 7C0802A6 */  mflr    r0
/* 00B93C 80010EDC 3C808010 */  lis     r4, ActivePlayer@ha
/* 00B940 80010EE0 90010004 */  stw     r0, 4(r1)
/* 00B944 80010EE4 9421FFD0 */  stwu    r1, -0x30(r1)
/* 00B948 80010EE8 93E1002C */  stw     r31, 0x2c(r1)
/* 00B94C 80010EEC 3BE00000 */  li      r31, 0
/* 00B950 80010EF0 93C10028 */  stw     r30, 0x28(r1)
/* 00B954 80010EF4 93A10024 */  stw     r29, 0x24(r1)
/* 00B958 80010EF8 3BA49C80 */  addi    r29, r4, ActivePlayer@l
/* 00B95C 80010EFC 3C808010 */  lis     r4, AudioDecodeThread@ha
/* 00B960 80010F00 93810020 */  stw     r28, 0x20(r1)
/* 00B964 80010F04 3BC49E50 */  addi    r30, r4, AudioDecodeThread@l
/* 00B968 80010F08 839D00BC */  lwz     r28, 0xbc(r29)
/* 00B96C 80010F0C 90610010 */  stw     r3, 0x10(r1)
lbl_80010F10:
/* 00B970 80010F10 93E10014 */  stw     r31, 0x14(r1)
/* 00B974 80010F14 38610010 */  addi    r3, r1, 0x10
/* 00B978 80010F18 48000071 */  bl      AudioDecode
/* 00B97C 80010F1C 801D00C0 */  lwz     r0, 0xc0(r29)
/* 00B980 80010F20 809D0050 */  lwz     r4, 0x50(r29)
/* 00B984 80010F24 7C7F0214 */  add     r3, r31, r0
/* 00B988 80010F28 7C032396 */  divwu   r0, r3, r4
/* 00B98C 80010F2C 7C0021D6 */  mullw   r0, r0, r4
/* 00B990 80010F30 7C601850 */  subf    r3, r0, r3
/* 00B994 80010F34 3804FFFF */  addi    r0, r4, -1
/* 00B998 80010F38 7C030040 */  cmplw   r3, r0
/* 00B99C 80010F3C 40820030 */  bne     lbl_80010F6C
/* 00B9A0 80010F40 881D00A6 */  lbz     r0, 0xa6(r29)
/* 00B9A4 80010F44 540007FF */  clrlwi. r0, r0, 0x1f
/* 00B9A8 80010F48 41820018 */  beq     lbl_80010F60
/* 00B9AC 80010F4C 80610010 */  lwz     r3, 0x10(r1)
/* 00B9B0 80010F50 801D00B4 */  lwz     r0, 0xb4(r29)
/* 00B9B4 80010F54 83830000 */  lwz     r28, 0(r3)
/* 00B9B8 80010F58 90010010 */  stw     r0, 0x10(r1)
/* 00B9BC 80010F5C 48000024 */  b       lbl_80010F80
lbl_80010F60:
/* 00B9C0 80010F60 7FC3F378 */  mr      r3, r30
/* 00B9C4 80010F64 48090F39 */  bl      OSSuspendThread
/* 00B9C8 80010F68 48000018 */  b       lbl_80010F80
lbl_80010F6C:
/* 00B9CC 80010F6C 80610010 */  lwz     r3, 0x10(r1)
/* 00B9D0 80010F70 80830000 */  lwz     r4, 0(r3)
/* 00B9D4 80010F74 7C03E214 */  add     r0, r3, r28
/* 00B9D8 80010F78 90010010 */  stw     r0, 0x10(r1)
/* 00B9DC 80010F7C 7C9C2378 */  mr      r28, r4
lbl_80010F80:
/* 00B9E0 80010F80 3BFF0001 */  addi    r31, r31, 1
/* 00B9E4 80010F84 4BFFFF8C */  b       lbl_80010F10
