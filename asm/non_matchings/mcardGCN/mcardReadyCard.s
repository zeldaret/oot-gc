glabel mcardReadyCard
/* 015A34 8001AFD4 7C0802A6 */  mflr    r0
/* 015A38 8001AFD8 3C808010 */  lis     r4, mCard@ha
/* 015A3C 8001AFDC 90010004 */  stw     r0, 4(r1)
/* 015A40 8001AFE0 388479B0 */  addi    r4, r4, mCard@l
/* 015A44 8001AFE4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 015A48 8001AFE8 93E10014 */  stw     r31, 0x14(r1)
/* 015A4C 8001AFEC 93C10010 */  stw     r30, 0x10(r1)
/* 015A50 8001AFF0 3BC30000 */  addi    r30, r3, 0
/* 015A54 8001AFF4 80040470 */  lwz     r0, 0x470(r4)
/* 015A58 8001AFF8 2C000001 */  cmpwi   r0, 1
/* 015A5C 8001AFFC 40820150 */  bne     lbl_8001B14C
/* 015A60 8001B000 807E0360 */  lwz     r3, 0x360(r30)
/* 015A64 8001B004 389E07A8 */  addi    r4, r30, 0x7a8
/* 015A68 8001B008 38A1000C */  addi    r5, r1, 0xc
/* 015A6C 8001B00C 480A3BC9 */  bl      CARDProbeEx
/* 015A70 8001B010 38830000 */  addi    r4, r3, 0
/* 015A74 8001B014 387E0000 */  addi    r3, r30, 0
/* 015A78 8001B018 48001289 */  bl      mcardGCErrorHandler
/* 015A7C 8001B01C 801E07B0 */  lwz     r0, 0x7b0(r30)
/* 015A80 8001B020 2C000001 */  cmpwi   r0, 1
/* 015A84 8001B024 40820040 */  bne     lbl_8001B064
/* 015A88 8001B028 801E035C */  lwz     r0, 0x35c(r30)
/* 015A8C 8001B02C 2C000003 */  cmpwi   r0, 3
/* 015A90 8001B030 41820034 */  beq     lbl_8001B064
/* 015A94 8001B034 38000005 */  li      r0, 5
/* 015A98 8001B038 901E035C */  stw     r0, 0x35c(r30)
/* 015A9C 8001B03C 38600000 */  li      r3, 0
/* 015AA0 8001B040 48000110 */  b       lbl_8001B150
/* 015AA4 8001B044 48000020 */  b       lbl_8001B064
lbl_8001B048:
/* 015AA8 8001B048 807E0360 */  lwz     r3, 0x360(r30)
/* 015AAC 8001B04C 389E07A8 */  addi    r4, r30, 0x7a8
/* 015AB0 8001B050 38A1000C */  addi    r5, r1, 0xc
/* 015AB4 8001B054 480A3B81 */  bl      CARDProbeEx
/* 015AB8 8001B058 38830000 */  addi    r4, r3, 0
/* 015ABC 8001B05C 387E0000 */  addi    r3, r30, 0
/* 015AC0 8001B060 48001241 */  bl      mcardGCErrorHandler
lbl_8001B064:
/* 015AC4 8001B064 801E035C */  lwz     r0, 0x35c(r30)
/* 015AC8 8001B068 2C000001 */  cmpwi   r0, 1
/* 015ACC 8001B06C 4182FFDC */  beq     lbl_8001B048
/* 015AD0 8001B070 2C000000 */  cmpwi   r0, 0
/* 015AD4 8001B074 41820048 */  beq     lbl_8001B0BC
/* 015AD8 8001B078 3BE00000 */  li      r31, 0
lbl_8001B07C:
/* 015ADC 8001B07C 807E0360 */  lwz     r3, 0x360(r30)
/* 015AE0 8001B080 389E07A8 */  addi    r4, r30, 0x7a8
/* 015AE4 8001B084 38A1000C */  addi    r5, r1, 0xc
/* 015AE8 8001B088 480A3B4D */  bl      CARDProbeEx
/* 015AEC 8001B08C 38830000 */  addi    r4, r3, 0
/* 015AF0 8001B090 387E0000 */  addi    r3, r30, 0
/* 015AF4 8001B094 4800120D */  bl      mcardGCErrorHandler
/* 015AF8 8001B098 2C030001 */  cmpwi   r3, 1
/* 015AFC 8001B09C 41820010 */  beq     lbl_8001B0AC
/* 015B00 8001B0A0 3BFF0001 */  addi    r31, r31, 1
/* 015B04 8001B0A4 2C1F000A */  cmpwi   r31, 0xa
/* 015B08 8001B0A8 4180FFD4 */  blt     lbl_8001B07C
lbl_8001B0AC:
/* 015B0C 8001B0AC 2C1F000A */  cmpwi   r31, 0xa
/* 015B10 8001B0B0 4082000C */  bne     lbl_8001B0BC
/* 015B14 8001B0B4 38600000 */  li      r3, 0
/* 015B18 8001B0B8 48000098 */  b       lbl_8001B150
lbl_8001B0BC:
/* 015B1C 8001B0BC 8001000C */  lwz     r0, 0xc(r1)
/* 015B20 8001B0C0 2C002000 */  cmpwi   r0, 0x2000
/* 015B24 8001B0C4 41820014 */  beq     lbl_8001B0D8
/* 015B28 8001B0C8 38000010 */  li      r0, 0x10
/* 015B2C 8001B0CC 901E035C */  stw     r0, 0x35c(r30)
/* 015B30 8001B0D0 38600000 */  li      r3, 0
/* 015B34 8001B0D4 4800007C */  b       lbl_8001B150
lbl_8001B0D8:
/* 015B38 8001B0D8 3C808010 */  lis     r4, gMCardCardWorkArea@ha
/* 015B3C 8001B0DC 807E0360 */  lwz     r3, 0x360(r30)
/* 015B40 8001B0E0 3884D960 */  addi    r4, r4, gMCardCardWorkArea@l
/* 015B44 8001B0E4 38A00000 */  li      r5, 0
/* 015B48 8001B0E8 480A4351 */  bl      CARDMount
/* 015B4C 8001B0EC 38830000 */  addi    r4, r3, 0
/* 015B50 8001B0F0 387E0000 */  addi    r3, r30, 0
/* 015B54 8001B0F4 480011AD */  bl      mcardGCErrorHandler
/* 015B58 8001B0F8 801E035C */  lwz     r0, 0x35c(r30)
/* 015B5C 8001B0FC 2C000000 */  cmpwi   r0, 0
/* 015B60 8001B100 41820024 */  beq     lbl_8001B124
/* 015B64 8001B104 2C000006 */  cmpwi   r0, 6
/* 015B68 8001B108 4182001C */  beq     lbl_8001B124
/* 015B6C 8001B10C 2C00000D */  cmpwi   r0, 0xd
/* 015B70 8001B110 41820014 */  beq     lbl_8001B124
/* 015B74 8001B114 807E0360 */  lwz     r3, 0x360(r30)
/* 015B78 8001B118 480A4405 */  bl      CARDUnmount
/* 015B7C 8001B11C 38600000 */  li      r3, 0
/* 015B80 8001B120 48000030 */  b       lbl_8001B150
lbl_8001B124:
/* 015B84 8001B124 807E0360 */  lwz     r3, 0x360(r30)
/* 015B88 8001B128 480A398D */  bl      CARDCheck
/* 015B8C 8001B12C 38830000 */  addi    r4, r3, 0
/* 015B90 8001B130 387E0000 */  addi    r3, r30, 0
/* 015B94 8001B134 4800116D */  bl      mcardGCErrorHandler
/* 015B98 8001B138 801E035C */  lwz     r0, 0x35c(r30)
/* 015B9C 8001B13C 2C000000 */  cmpwi   r0, 0
/* 015BA0 8001B140 4182000C */  beq     lbl_8001B14C
/* 015BA4 8001B144 38600000 */  li      r3, 0
/* 015BA8 8001B148 48000008 */  b       lbl_8001B150
lbl_8001B14C:
/* 015BAC 8001B14C 38600001 */  li      r3, 1
lbl_8001B150:
/* 015BB0 8001B150 8001001C */  lwz     r0, 0x1c(r1)
/* 015BB4 8001B154 83E10014 */  lwz     r31, 0x14(r1)
/* 015BB8 8001B158 83C10010 */  lwz     r30, 0x10(r1)
/* 015BBC 8001B15C 7C0803A6 */  mtlr    r0
/* 015BC0 8001B160 38210018 */  addi    r1, r1, 0x18
/* 015BC4 8001B164 4E800020 */  blr     
