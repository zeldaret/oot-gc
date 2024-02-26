glabel soundSetBufferSize
/* 0172E0 8001C880 7C0802A6 */  mflr    r0
/* 0172E4 8001C884 90010004 */  stw     r0, 4(r1)
/* 0172E8 8001C888 9421FFE0 */  stwu    r1, -0x20(r1)
/* 0172EC 8001C88C 93E1001C */  stw     r31, 0x1c(r1)
/* 0172F0 8001C890 3BE30000 */  addi    r31, r3, 0
/* 0172F4 8001C894 93C10018 */  stw     r30, 0x18(r1)
/* 0172F8 8001C898 93A10014 */  stw     r29, 0x14(r1)
/* 0172FC 8001C89C 3BA40000 */  addi    r29, r4, 0
/* 017300 8001C8A0 7FA02E70 */  srawi   r0, r29, 5
/* 017304 8001C8A4 7C000194 */  addze   r0, r0
/* 017308 8001C8A8 54002834 */  slwi    r0, r0, 5
/* 01730C 8001C8AC 7C00E811 */  subfc.  r0, r0, r29
/* 017310 8001C8B0 4182002C */  beq     lbl_8001C8DC
/* 017314 8001C8B4 3C60800F */  lis     r3, D_800EA7E8@ha
/* 017318 8001C8B8 4CC63182 */  crclr   6
/* 01731C 8001C8BC 3C80800F */  lis     r4, D_800EA828@ha
/* 017320 8001C8C0 3863A7E8 */  addi    r3, r3, D_800EA7E8@l
/* 017324 8001C8C4 3884A828 */  addi    r4, r4, D_800EA828@l
/* 017328 8001C8C8 38DD0000 */  addi    r6, r29, 0
/* 01732C 8001C8CC 38A002A2 */  li      r5, 0x2a2
/* 017330 8001C8D0 4BFE9545 */  bl      xlPostText
/* 017334 8001C8D4 381D001F */  addi    r0, r29, 0x1f
/* 017338 8001C8D8 541D0034 */  rlwinm  r29, r0, 0, 0, 0x1a
lbl_8001C8DC:
/* 01733C 8001C8DC 93BF00C8 */  stw     r29, 0xc8(r31)
/* 017340 8001C8E0 7FA42670 */  srawi   r4, r29, 4
/* 017344 8001C8E4 7FA01670 */  srawi   r0, r29, 2
/* 017348 8001C8E8 909F00CC */  stw     r4, 0xcc(r31)
/* 01734C 8001C8EC 7FE3FB78 */  mr      r3, r31
/* 017350 8001C8F0 909F00D0 */  stw     r4, 0xd0(r31)
/* 017354 8001C8F4 901F00D4 */  stw     r0, 0xd4(r31)
/* 017358 8001C8F8 48000959 */  bl      soundWipeBuffers
/* 01735C 8001C8FC 2C030000 */  cmpwi   r3, 0
/* 017360 8001C900 4082000C */  bne     lbl_8001C90C
/* 017364 8001C904 38600000 */  li      r3, 0
/* 017368 8001C908 480000FC */  b       lbl_8001CA04
lbl_8001C90C:
/* 01736C 8001C90C 3BA00000 */  li      r29, 0
/* 017370 8001C910 57A0103A */  slwi    r0, r29, 2
/* 017374 8001C914 7FDF0214 */  add     r30, r31, r0
lbl_8001C918:
/* 017378 8001C918 801F00C8 */  lwz     r0, 0xc8(r31)
/* 01737C 8001C91C 387E0010 */  addi    r3, r30, 0x10
/* 017380 8001C920 64043000 */  oris    r4, r0, 0x3000
/* 017384 8001C924 4BFEA891 */  bl      xlHeapTake
/* 017388 8001C928 2C030000 */  cmpwi   r3, 0
/* 01738C 8001C92C 4082000C */  bne     lbl_8001C938
/* 017390 8001C930 38600000 */  li      r3, 0
/* 017394 8001C934 480000D0 */  b       lbl_8001CA04
lbl_8001C938:
/* 017398 8001C938 3BBD0001 */  addi    r29, r29, 1
/* 01739C 8001C93C 2C1D0010 */  cmpwi   r29, 0x10
/* 0173A0 8001C940 3BDE0004 */  addi    r30, r30, 4
/* 0173A4 8001C944 4180FFD4 */  blt     lbl_8001C918
/* 0173A8 8001C948 801F00CC */  lwz     r0, 0xcc(r31)
/* 0173AC 8001C94C 387F00B8 */  addi    r3, r31, 0xb8
/* 0173B0 8001C950 64043000 */  oris    r4, r0, 0x3000
/* 0173B4 8001C954 4BFEA861 */  bl      xlHeapTake
/* 0173B8 8001C958 2C030000 */  cmpwi   r3, 0
/* 0173BC 8001C95C 4082000C */  bne     lbl_8001C968
/* 0173C0 8001C960 38600000 */  li      r3, 0
/* 0173C4 8001C964 480000A0 */  b       lbl_8001CA04
lbl_8001C968:
/* 0173C8 8001C968 38C00000 */  li      r6, 0
/* 0173CC 8001C96C 38E60000 */  addi    r7, r6, 0
/* 0173D0 8001C970 38A60000 */  addi    r5, r6, 0
/* 0173D4 8001C974 48000014 */  b       lbl_8001C988
lbl_8001C978:
/* 0173D8 8001C978 807F00B8 */  lwz     r3, 0xb8(r31)
/* 0173DC 8001C97C 38C60001 */  addi    r6, r6, 1
/* 0173E0 8001C980 7CA33B2E */  sthx    r5, r3, r7
/* 0173E4 8001C984 38E70002 */  addi    r7, r7, 2
lbl_8001C988:
/* 0173E8 8001C988 809F00CC */  lwz     r4, 0xcc(r31)
/* 0173EC 8001C98C 7C800E70 */  srawi   r0, r4, 1
/* 0173F0 8001C990 7C060000 */  cmpw    r6, r0
/* 0173F4 8001C994 4180FFE4 */  blt     lbl_8001C978
/* 0173F8 8001C998 807F00B8 */  lwz     r3, 0xb8(r31)
/* 0173FC 8001C99C 48080E11 */  bl      DCStoreRange
/* 017400 8001C9A0 801F00D0 */  lwz     r0, 0xd0(r31)
/* 017404 8001C9A4 387F00BC */  addi    r3, r31, 0xbc
/* 017408 8001C9A8 64043000 */  oris    r4, r0, 0x3000
/* 01740C 8001C9AC 4BFEA809 */  bl      xlHeapTake
/* 017410 8001C9B0 2C030000 */  cmpwi   r3, 0
/* 017414 8001C9B4 4082000C */  bne     lbl_8001C9C0
/* 017418 8001C9B8 38600000 */  li      r3, 0
/* 01741C 8001C9BC 48000048 */  b       lbl_8001CA04
lbl_8001C9C0:
/* 017420 8001C9C0 801F00D4 */  lwz     r0, 0xd4(r31)
/* 017424 8001C9C4 387F00C0 */  addi    r3, r31, 0xc0
/* 017428 8001C9C8 64043000 */  oris    r4, r0, 0x3000
/* 01742C 8001C9CC 4BFEA7E9 */  bl      xlHeapTake
/* 017430 8001C9D0 2C030000 */  cmpwi   r3, 0
/* 017434 8001C9D4 4082000C */  bne     lbl_8001C9E0
/* 017438 8001C9D8 38600000 */  li      r3, 0
/* 01743C 8001C9DC 48000028 */  b       lbl_8001CA04
lbl_8001C9E0:
/* 017440 8001C9E0 801F00D4 */  lwz     r0, 0xd4(r31)
/* 017444 8001C9E4 387F00C4 */  addi    r3, r31, 0xc4
/* 017448 8001C9E8 64043000 */  oris    r4, r0, 0x3000
/* 01744C 8001C9EC 4BFEA7C9 */  bl      xlHeapTake
/* 017450 8001C9F0 2C030000 */  cmpwi   r3, 0
/* 017454 8001C9F4 4082000C */  bne     lbl_8001CA00
/* 017458 8001C9F8 38600000 */  li      r3, 0
/* 01745C 8001C9FC 48000008 */  b       lbl_8001CA04
lbl_8001CA00:
/* 017460 8001CA00 38600001 */  li      r3, 1
lbl_8001CA04:
/* 017464 8001CA04 80010024 */  lwz     r0, 0x24(r1)
/* 017468 8001CA08 83E1001C */  lwz     r31, 0x1c(r1)
/* 01746C 8001CA0C 83C10018 */  lwz     r30, 0x18(r1)
/* 017470 8001CA10 7C0803A6 */  mtlr    r0
/* 017474 8001CA14 83A10014 */  lwz     r29, 0x14(r1)
/* 017478 8001CA18 38210020 */  addi    r1, r1, 0x20
/* 01747C 8001CA1C 4E800020 */  blr     
