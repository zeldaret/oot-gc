glabel cpuGetRegisterCP0
/* 02FD28 800352C8 9421FFE0 */  stwu    r1, -0x20(r1)
/* 02FD2C 800352CC 2804001F */  cmplwi  r4, 0x1f
/* 02FD30 800352D0 38000000 */  li      r0, 0
/* 02FD34 800352D4 93E1001C */  stw     r31, 0x1c(r1)
/* 02FD38 800352D8 93C10018 */  stw     r30, 0x18(r1)
/* 02FD3C 800352DC 41810240 */  bgt     lbl_8003551C
/* 02FD40 800352E0 3CC0800F */  lis     r6, jtbl_800ED574@ha
/* 02FD44 800352E4 38E6D574 */  addi    r7, r6, jtbl_800ED574@l
/* 02FD48 800352E8 5486103A */  slwi    r6, r4, 2
/* 02FD4C 800352EC 7CC7302E */  lwzx    r6, r7, r6
/* 02FD50 800352F0 7CC903A6 */  mtctr   r6
/* 02FD54 800352F4 4E800420 */  bctr    
glabel lbl_800352F8
/* 02FD58 800352F8 38C00006 */  li      r6, 6
/* 02FD5C 800352FC 39800000 */  li      r12, 0
/* 02FD60 80035300 7CC903A6 */  mtctr   r6
/* 02FD64 80035304 3BEC0000 */  addi    r31, r12, 0
/* 02FD68 80035308 3BC30000 */  addi    r30, r3, 0
/* 02FD6C 8003530C 394C0000 */  addi    r10, r12, 0
/* 02FD70 80035310 392C0000 */  addi    r9, r12, 0
/* 02FD74 80035314 390C0000 */  addi    r8, r12, 0
/* 02FD78 80035318 39600002 */  li      r11, 2
lbl_8003531C:
/* 02FD7C 8003531C 80DE0250 */  lwz     r6, 0x250(r30)
/* 02FD80 80035320 80FE0254 */  lwz     r7, 0x254(r30)
/* 02FD84 80035324 7CC65038 */  and     r6, r6, r10
/* 02FD88 80035328 7CE75838 */  and     r7, r7, r11
/* 02FD8C 8003532C 7CE74A78 */  xor     r7, r7, r9
/* 02FD90 80035330 7CC64278 */  xor     r6, r6, r8
/* 02FD94 80035334 7CE63379 */  or.     r6, r7, r6
/* 02FD98 80035338 40820008 */  bne     lbl_80035340
/* 02FD9C 8003533C 398C0001 */  addi    r12, r12, 1
lbl_80035340:
/* 02FDA0 80035340 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FDA4 80035344 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FDA8 80035348 3BDE0028 */  addi    r30, r30, 0x28
/* 02FDAC 8003534C 7CC65038 */  and     r6, r6, r10
/* 02FDB0 80035350 7CE75838 */  and     r7, r7, r11
/* 02FDB4 80035354 7CE74A78 */  xor     r7, r7, r9
/* 02FDB8 80035358 7CC64278 */  xor     r6, r6, r8
/* 02FDBC 8003535C 7CE63379 */  or.     r6, r7, r6
/* 02FDC0 80035360 40820008 */  bne     lbl_80035368
/* 02FDC4 80035364 398C0001 */  addi    r12, r12, 1
lbl_80035368:
/* 02FDC8 80035368 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FDCC 8003536C 3BFF0001 */  addi    r31, r31, 1
/* 02FDD0 80035370 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FDD4 80035374 3BDE0028 */  addi    r30, r30, 0x28
/* 02FDD8 80035378 7CC65038 */  and     r6, r6, r10
/* 02FDDC 8003537C 7CE75838 */  and     r7, r7, r11
/* 02FDE0 80035380 7CE74A78 */  xor     r7, r7, r9
/* 02FDE4 80035384 7CC64278 */  xor     r6, r6, r8
/* 02FDE8 80035388 7CE63379 */  or.     r6, r7, r6
/* 02FDEC 8003538C 40820008 */  bne     lbl_80035394
/* 02FDF0 80035390 398C0001 */  addi    r12, r12, 1
lbl_80035394:
/* 02FDF4 80035394 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FDF8 80035398 3BFF0001 */  addi    r31, r31, 1
/* 02FDFC 8003539C 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FE00 800353A0 3BDE0028 */  addi    r30, r30, 0x28
/* 02FE04 800353A4 7CC65038 */  and     r6, r6, r10
/* 02FE08 800353A8 7CE75838 */  and     r7, r7, r11
/* 02FE0C 800353AC 7CE74A78 */  xor     r7, r7, r9
/* 02FE10 800353B0 7CC64278 */  xor     r6, r6, r8
/* 02FE14 800353B4 7CE63379 */  or.     r6, r7, r6
/* 02FE18 800353B8 40820008 */  bne     lbl_800353C0
/* 02FE1C 800353BC 398C0001 */  addi    r12, r12, 1
lbl_800353C0:
/* 02FE20 800353C0 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FE24 800353C4 3BFF0001 */  addi    r31, r31, 1
/* 02FE28 800353C8 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FE2C 800353CC 3BDE0028 */  addi    r30, r30, 0x28
/* 02FE30 800353D0 7CC65038 */  and     r6, r6, r10
/* 02FE34 800353D4 7CE75838 */  and     r7, r7, r11
/* 02FE38 800353D8 7CE74A78 */  xor     r7, r7, r9
/* 02FE3C 800353DC 7CC64278 */  xor     r6, r6, r8
/* 02FE40 800353E0 7CE63379 */  or.     r6, r7, r6
/* 02FE44 800353E4 40820008 */  bne     lbl_800353EC
/* 02FE48 800353E8 398C0001 */  addi    r12, r12, 1
lbl_800353EC:
/* 02FE4C 800353EC 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FE50 800353F0 3BFF0001 */  addi    r31, r31, 1
/* 02FE54 800353F4 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FE58 800353F8 3BDE0028 */  addi    r30, r30, 0x28
/* 02FE5C 800353FC 7CC65038 */  and     r6, r6, r10
/* 02FE60 80035400 7CE75838 */  and     r7, r7, r11
/* 02FE64 80035404 7CE74A78 */  xor     r7, r7, r9
/* 02FE68 80035408 7CC64278 */  xor     r6, r6, r8
/* 02FE6C 8003540C 7CE63379 */  or.     r6, r7, r6
/* 02FE70 80035410 40820008 */  bne     lbl_80035418
/* 02FE74 80035414 398C0001 */  addi    r12, r12, 1
lbl_80035418:
/* 02FE78 80035418 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FE7C 8003541C 3BFF0001 */  addi    r31, r31, 1
/* 02FE80 80035420 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FE84 80035424 3BDE0028 */  addi    r30, r30, 0x28
/* 02FE88 80035428 7CC65038 */  and     r6, r6, r10
/* 02FE8C 8003542C 7CE75838 */  and     r7, r7, r11
/* 02FE90 80035430 7CE74A78 */  xor     r7, r7, r9
/* 02FE94 80035434 7CC64278 */  xor     r6, r6, r8
/* 02FE98 80035438 7CE63379 */  or.     r6, r7, r6
/* 02FE9C 8003543C 40820008 */  bne     lbl_80035444
/* 02FEA0 80035440 398C0001 */  addi    r12, r12, 1
lbl_80035444:
/* 02FEA4 80035444 80DE0278 */  lwz     r6, 0x278(r30)
/* 02FEA8 80035448 3BFF0001 */  addi    r31, r31, 1
/* 02FEAC 8003544C 80FE027C */  lwz     r7, 0x27c(r30)
/* 02FEB0 80035450 3BDE0028 */  addi    r30, r30, 0x28
/* 02FEB4 80035454 7CC65038 */  and     r6, r6, r10
/* 02FEB8 80035458 7CE75838 */  and     r7, r7, r11
/* 02FEBC 8003545C 7CE74A78 */  xor     r7, r7, r9
/* 02FEC0 80035460 7CC64278 */  xor     r6, r6, r8
/* 02FEC4 80035464 7CE63379 */  or.     r6, r7, r6
/* 02FEC8 80035468 40820008 */  bne     lbl_80035470
/* 02FECC 8003546C 398C0001 */  addi    r12, r12, 1
lbl_80035470:
/* 02FED0 80035470 3BDE0028 */  addi    r30, r30, 0x28
/* 02FED4 80035474 3BFF0001 */  addi    r31, r31, 1
/* 02FED8 80035478 4200FEA4 */  bdnz    lbl_8003531C
/* 02FEDC 8003547C 91850004 */  stw     r12, 4(r5)
/* 02FEE0 80035480 7D86FE70 */  srawi   r6, r12, 0x1f
/* 02FEE4 80035484 90C50000 */  stw     r6, 0(r5)
/* 02FEE8 80035488 48000098 */  b       lbl_80035520
glabel lbl_8003548C
/* 02FEEC 8003548C 38000001 */  li      r0, 1
/* 02FEF0 80035490 48000090 */  b       lbl_80035520
glabel lbl_80035494
/* 02FEF4 80035494 38000001 */  li      r0, 1
/* 02FEF8 80035498 48000088 */  b       lbl_80035520
glabel lbl_8003549C
/* 02FEFC 8003549C 38000001 */  li      r0, 1
/* 02FF00 800354A0 48000080 */  b       lbl_80035520
glabel lbl_800354A4
/* 02FF04 800354A4 38C00000 */  li      r6, 0
/* 02FF08 800354A8 90C50004 */  stw     r6, 4(r5)
/* 02FF0C 800354AC 90C50000 */  stw     r6, 0(r5)
/* 02FF10 800354B0 48000070 */  b       lbl_80035520
glabel lbl_800354B4
/* 02FF14 800354B4 38000001 */  li      r0, 1
/* 02FF18 800354B8 48000068 */  b       lbl_80035520
glabel lbl_800354BC
/* 02FF1C 800354BC 38C00000 */  li      r6, 0
/* 02FF20 800354C0 90C50004 */  stw     r6, 4(r5)
/* 02FF24 800354C4 90C50000 */  stw     r6, 0(r5)
/* 02FF28 800354C8 48000058 */  b       lbl_80035520
glabel lbl_800354CC
/* 02FF2C 800354CC 38C00000 */  li      r6, 0
/* 02FF30 800354D0 90C50004 */  stw     r6, 4(r5)
/* 02FF34 800354D4 90C50000 */  stw     r6, 0(r5)
/* 02FF38 800354D8 48000048 */  b       lbl_80035520
glabel lbl_800354DC
/* 02FF3C 800354DC 38C00000 */  li      r6, 0
/* 02FF40 800354E0 90C50004 */  stw     r6, 4(r5)
/* 02FF44 800354E4 90C50000 */  stw     r6, 0(r5)
/* 02FF48 800354E8 48000038 */  b       lbl_80035520
glabel lbl_800354EC
/* 02FF4C 800354EC 38C00000 */  li      r6, 0
/* 02FF50 800354F0 90C50004 */  stw     r6, 4(r5)
/* 02FF54 800354F4 90C50000 */  stw     r6, 0(r5)
/* 02FF58 800354F8 48000028 */  b       lbl_80035520
glabel lbl_800354FC
/* 02FF5C 800354FC 38C00000 */  li      r6, 0
/* 02FF60 80035500 90C50004 */  stw     r6, 4(r5)
/* 02FF64 80035504 90C50000 */  stw     r6, 0(r5)
/* 02FF68 80035508 48000018 */  b       lbl_80035520
glabel lbl_8003550C
/* 02FF6C 8003550C 38C00000 */  li      r6, 0
/* 02FF70 80035510 90C50004 */  stw     r6, 4(r5)
/* 02FF74 80035514 90C50000 */  stw     r6, 0(r5)
/* 02FF78 80035518 48000008 */  b       lbl_80035520
glabel lbl_8003551C
/* 02FF7C 8003551C 38000001 */  li      r0, 1
lbl_80035520:
/* 02FF80 80035520 2C000000 */  cmpwi   r0, 0
/* 02FF84 80035524 41820038 */  beq     lbl_8003555C
/* 02FF88 80035528 3CC0800F */  lis     r6, ganMaskGetCP0@ha
/* 02FF8C 8003552C 54871838 */  slwi    r7, r4, 3
/* 02FF90 80035530 7C833A14 */  add     r4, r3, r7
/* 02FF94 80035534 3806BB88 */  addi    r0, r6, ganMaskGetCP0@l
/* 02FF98 80035538 80C40A44 */  lwz     r6, 0xa44(r4)
/* 02FF9C 8003553C 7C603A14 */  add     r3, r0, r7
/* 02FFA0 80035540 80840A40 */  lwz     r4, 0xa40(r4)
/* 02FFA4 80035544 80030004 */  lwz     r0, 4(r3)
/* 02FFA8 80035548 80630000 */  lwz     r3, 0(r3)
/* 02FFAC 8003554C 7CC00038 */  and     r0, r6, r0
/* 02FFB0 80035550 90050004 */  stw     r0, 4(r5)
/* 02FFB4 80035554 7C801838 */  and     r0, r4, r3
/* 02FFB8 80035558 90050000 */  stw     r0, 0(r5)
lbl_8003555C:
/* 02FFBC 8003555C 83E1001C */  lwz     r31, 0x1c(r1)
/* 02FFC0 80035560 38600001 */  li      r3, 1
/* 02FFC4 80035564 83C10018 */  lwz     r30, 0x18(r1)
/* 02FFC8 80035568 38210020 */  addi    r1, r1, 0x20
/* 02FFCC 8003556C 4E800020 */  blr     
