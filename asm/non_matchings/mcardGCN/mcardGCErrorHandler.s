glabel mcardGCErrorHandler
/* 016D00 8001C2A0 2C04FFF8 */  cmpwi   r4, -8
/* 016D04 8001C2A4 41820110 */  beq     lbl_8001C3B4
/* 016D08 8001C2A8 40800040 */  bge     lbl_8001C2E8
/* 016D0C 8001C2AC 2C04FFF3 */  cmpwi   r4, -13
/* 016D10 8001C2B0 41820154 */  beq     lbl_8001C404
/* 016D14 8001C2B4 4080001C */  bge     lbl_8001C2D0
/* 016D18 8001C2B8 2C04FF80 */  cmpwi   r4, -128
/* 016D1C 8001C2BC 41820168 */  beq     lbl_8001C424
/* 016D20 8001C2C0 41800174 */  blt     lbl_8001C434
/* 016D24 8001C2C4 2C04FFF2 */  cmpwi   r4, -14
/* 016D28 8001C2C8 4080014C */  bge     lbl_8001C414
/* 016D2C 8001C2CC 48000168 */  b       lbl_8001C434
lbl_8001C2D0:
/* 016D30 8001C2D0 2C04FFF6 */  cmpwi   r4, -10
/* 016D34 8001C2D4 41820100 */  beq     lbl_8001C3D4
/* 016D38 8001C2D8 408000EC */  bge     lbl_8001C3C4
/* 016D3C 8001C2DC 2C04FFF5 */  cmpwi   r4, -11
/* 016D40 8001C2E0 40800104 */  bge     lbl_8001C3E4
/* 016D44 8001C2E4 48000110 */  b       lbl_8001C3F4
lbl_8001C2E8:
/* 016D48 8001C2E8 2C04FFFD */  cmpwi   r4, -3
/* 016D4C 8001C2EC 41820068 */  beq     lbl_8001C354
/* 016D50 8001C2F0 4080001C */  bge     lbl_8001C30C
/* 016D54 8001C2F4 2C04FFFB */  cmpwi   r4, -5
/* 016D58 8001C2F8 41820084 */  beq     lbl_8001C37C
/* 016D5C 8001C2FC 40800070 */  bge     lbl_8001C36C
/* 016D60 8001C300 2C04FFFA */  cmpwi   r4, -6
/* 016D64 8001C304 40800090 */  bge     lbl_8001C394
/* 016D68 8001C308 4800009C */  b       lbl_8001C3A4
lbl_8001C30C:
/* 016D6C 8001C30C 2C040000 */  cmpwi   r4, 0
/* 016D70 8001C310 41820014 */  beq     lbl_8001C324
/* 016D74 8001C314 40800120 */  bge     lbl_8001C434
/* 016D78 8001C318 2C04FFFF */  cmpwi   r4, -1
/* 016D7C 8001C31C 40800018 */  bge     lbl_8001C334
/* 016D80 8001C320 48000024 */  b       lbl_8001C344
lbl_8001C324:
/* 016D84 8001C324 38000000 */  li      r0, 0
/* 016D88 8001C328 9003035C */  stw     r0, 0x35c(r3)
/* 016D8C 8001C32C 38600001 */  li      r3, 1
/* 016D90 8001C330 4E800020 */  blr     
lbl_8001C334:
/* 016D94 8001C334 38000001 */  li      r0, 1
/* 016D98 8001C338 9003035C */  stw     r0, 0x35c(r3)
/* 016D9C 8001C33C 38600000 */  li      r3, 0
/* 016DA0 8001C340 4E800020 */  blr     
lbl_8001C344:
/* 016DA4 8001C344 38000002 */  li      r0, 2
/* 016DA8 8001C348 9003035C */  stw     r0, 0x35c(r3)
/* 016DAC 8001C34C 38600000 */  li      r3, 0
/* 016DB0 8001C350 4E800020 */  blr     
lbl_8001C354:
/* 016DB4 8001C354 38000003 */  li      r0, 3
/* 016DB8 8001C358 9003035C */  stw     r0, 0x35c(r3)
/* 016DBC 8001C35C 38000000 */  li      r0, 0
/* 016DC0 8001C360 900307B0 */  stw     r0, 0x7b0(r3)
/* 016DC4 8001C364 38600000 */  li      r3, 0
/* 016DC8 8001C368 4E800020 */  blr     
lbl_8001C36C:
/* 016DCC 8001C36C 38000004 */  li      r0, 4
/* 016DD0 8001C370 9003035C */  stw     r0, 0x35c(r3)
/* 016DD4 8001C374 38600000 */  li      r3, 0
/* 016DD8 8001C378 4E800020 */  blr     
lbl_8001C37C:
/* 016DDC 8001C37C 38000005 */  li      r0, 5
/* 016DE0 8001C380 9003035C */  stw     r0, 0x35c(r3)
/* 016DE4 8001C384 38000001 */  li      r0, 1
/* 016DE8 8001C388 900307B0 */  stw     r0, 0x7b0(r3)
/* 016DEC 8001C38C 38600000 */  li      r3, 0
/* 016DF0 8001C390 4E800020 */  blr     
lbl_8001C394:
/* 016DF4 8001C394 38000006 */  li      r0, 6
/* 016DF8 8001C398 9003035C */  stw     r0, 0x35c(r3)
/* 016DFC 8001C39C 38600000 */  li      r3, 0
/* 016E00 8001C3A0 4E800020 */  blr     
lbl_8001C3A4:
/* 016E04 8001C3A4 38000007 */  li      r0, 7
/* 016E08 8001C3A8 9003035C */  stw     r0, 0x35c(r3)
/* 016E0C 8001C3AC 38600000 */  li      r3, 0
/* 016E10 8001C3B0 4E800020 */  blr     
lbl_8001C3B4:
/* 016E14 8001C3B4 38000008 */  li      r0, 8
/* 016E18 8001C3B8 9003035C */  stw     r0, 0x35c(r3)
/* 016E1C 8001C3BC 38600000 */  li      r3, 0
/* 016E20 8001C3C0 4E800020 */  blr     
lbl_8001C3C4:
/* 016E24 8001C3C4 38000009 */  li      r0, 9
/* 016E28 8001C3C8 9003035C */  stw     r0, 0x35c(r3)
/* 016E2C 8001C3CC 38600000 */  li      r3, 0
/* 016E30 8001C3D0 4E800020 */  blr     
lbl_8001C3D4:
/* 016E34 8001C3D4 3800000A */  li      r0, 0xa
/* 016E38 8001C3D8 9003035C */  stw     r0, 0x35c(r3)
/* 016E3C 8001C3DC 38600000 */  li      r3, 0
/* 016E40 8001C3E0 4E800020 */  blr     
lbl_8001C3E4:
/* 016E44 8001C3E4 3800000B */  li      r0, 0xb
/* 016E48 8001C3E8 9003035C */  stw     r0, 0x35c(r3)
/* 016E4C 8001C3EC 38600000 */  li      r3, 0
/* 016E50 8001C3F0 4E800020 */  blr     
lbl_8001C3F4:
/* 016E54 8001C3F4 3800000C */  li      r0, 0xc
/* 016E58 8001C3F8 9003035C */  stw     r0, 0x35c(r3)
/* 016E5C 8001C3FC 38600000 */  li      r3, 0
/* 016E60 8001C400 4E800020 */  blr     
lbl_8001C404:
/* 016E64 8001C404 3800000D */  li      r0, 0xd
/* 016E68 8001C408 9003035C */  stw     r0, 0x35c(r3)
/* 016E6C 8001C40C 38600000 */  li      r3, 0
/* 016E70 8001C410 4E800020 */  blr     
lbl_8001C414:
/* 016E74 8001C414 3800000E */  li      r0, 0xe
/* 016E78 8001C418 9003035C */  stw     r0, 0x35c(r3)
/* 016E7C 8001C41C 38600000 */  li      r3, 0
/* 016E80 8001C420 4E800020 */  blr     
lbl_8001C424:
/* 016E84 8001C424 3800000F */  li      r0, 0xf
/* 016E88 8001C428 9003035C */  stw     r0, 0x35c(r3)
/* 016E8C 8001C42C 38600000 */  li      r3, 0
/* 016E90 8001C430 4E800020 */  blr     
lbl_8001C434:
/* 016E94 8001C434 38000019 */  li      r0, 0x19
/* 016E98 8001C438 9003035C */  stw     r0, 0x35c(r3)
/* 016E9C 8001C43C 38600000 */  li      r3, 0
/* 016EA0 8001C440 4E800020 */  blr     
