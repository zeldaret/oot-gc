glabel osEepromLongRead
/* 08B8EC 80090E8C 7C0802A6 */  mflr    r0
/* 08B8F0 80090E90 90010004 */  stw     r0, 4(r1)
/* 08B8F4 80090E94 9421FFE0 */  stwu    r1, -0x20(r1)
/* 08B8F8 80090E98 93E1001C */  stw     r31, 0x1c(r1)
/* 08B8FC 80090E9C 3881000C */  addi    r4, r1, 0xc
/* 08B900 80090EA0 93C10018 */  stw     r30, 0x18(r1)
/* 08B904 80090EA4 3BC00000 */  li      r30, 0
/* 08B908 80090EA8 93A10014 */  stw     r29, 0x14(r1)
/* 08B90C 80090EAC 93810010 */  stw     r28, 0x10(r1)
/* 08B910 80090EB0 7C7C1B78 */  mr      r28, r3
/* 08B914 80090EB4 8BA3006F */  lbz     r29, 0x6f(r3)
/* 08B918 80090EB8 80BC0074 */  lwz     r5, 0x74(r28)
/* 08B91C 80090EBC 4BFA38C5 */  bl      cpuGetAddressBuffer
/* 08B920 80090EC0 2C030000 */  cmpwi   r3, 0
/* 08B924 80090EC4 4082000C */  bne     lbl_80090ED0
/* 08B928 80090EC8 38600000 */  li      r3, 0
/* 08B92C 80090ECC 4800004C */  b       lbl_80090F18
lbl_80090ED0:
/* 08B930 80090ED0 83FC007C */  lwz     r31, 0x7c(r28)
/* 08B934 80090ED4 48000034 */  b       lbl_80090F08
lbl_80090ED8:
/* 08B938 80090ED8 7FA3EB78 */  mr      r3, r29
/* 08B93C 80090EDC 8081000C */  lwz     r4, 0xc(r1)
/* 08B940 80090EE0 4BF7806D */  bl      simulatorReadEEPROM
/* 08B944 80090EE4 2C030000 */  cmpwi   r3, 0
/* 08B948 80090EE8 4082000C */  bne     lbl_80090EF4
/* 08B94C 80090EEC 3BC0FFFF */  li      r30, -1
/* 08B950 80090EF0 48000020 */  b       lbl_80090F10
lbl_80090EF4:
/* 08B954 80090EF4 8061000C */  lwz     r3, 0xc(r1)
/* 08B958 80090EF8 3BFFFFF8 */  addi    r31, r31, -8
/* 08B95C 80090EFC 3BBD0001 */  addi    r29, r29, 1
/* 08B960 80090F00 38030008 */  addi    r0, r3, 8
/* 08B964 80090F04 9001000C */  stw     r0, 0xc(r1)
lbl_80090F08:
/* 08B968 80090F08 2C1F0000 */  cmpwi   r31, 0
/* 08B96C 80090F0C 4181FFCC */  bgt     lbl_80090ED8
lbl_80090F10:
/* 08B970 80090F10 93DC0054 */  stw     r30, 0x54(r28)
/* 08B974 80090F14 38600001 */  li      r3, 1
lbl_80090F18:
/* 08B978 80090F18 80010024 */  lwz     r0, 0x24(r1)
/* 08B97C 80090F1C 83E1001C */  lwz     r31, 0x1c(r1)
/* 08B980 80090F20 83C10018 */  lwz     r30, 0x18(r1)
/* 08B984 80090F24 7C0803A6 */  mtlr    r0
/* 08B988 80090F28 83A10014 */  lwz     r29, 0x14(r1)
/* 08B98C 80090F2C 83810010 */  lwz     r28, 0x10(r1)
/* 08B990 80090F30 38210020 */  addi    r1, r1, 0x20
/* 08B994 80090F34 4E800020 */  blr     
