glabel libraryFunctionReplaced
/* 089D8C 8008F32C 1C04004C */  mulli   r0, r4, 0x4c
/* 089D90 8008F330 3C60800F */  lis     r3, gaFunction@ha
/* 089D94 8008F334 3863EF2C */  addi    r3, r3, gaFunction@l
/* 089D98 8008F338 7C830214 */  add     r4, r3, r0
/* 089D9C 8008F33C 3C608009 */  lis     r3, send_mesg@ha
/* 089DA0 8008F340 80840004 */  lwz     r4, 4(r4)
/* 089DA4 8008F344 38036728 */  addi    r0, r3, send_mesg@l
/* 089DA8 8008F348 7C040040 */  cmplw   r4, r0
/* 089DAC 8008F34C 4082000C */  bne     lbl_8008F358
/* 089DB0 8008F350 38600000 */  li      r3, 0
/* 089DB4 8008F354 4E800020 */  blr     
lbl_8008F358:
/* 089DB8 8008F358 3C608009 */  lis     r3, __osEnqueueAndYield@ha
/* 089DBC 8008F35C 3803643C */  addi    r0, r3, __osEnqueueAndYield@l
/* 089DC0 8008F360 7C040040 */  cmplw   r4, r0
/* 089DC4 8008F364 4082000C */  bne     lbl_8008F370
/* 089DC8 8008F368 38600000 */  li      r3, 0
/* 089DCC 8008F36C 4E800020 */  blr     
lbl_8008F370:
/* 089DD0 8008F370 3C608009 */  lis     r3, __osEnqueueThread@ha
/* 089DD4 8008F374 38036214 */  addi    r0, r3, __osEnqueueThread@l
/* 089DD8 8008F378 7C040040 */  cmplw   r4, r0
/* 089DDC 8008F37C 4082000C */  bne     lbl_8008F388
/* 089DE0 8008F380 38600000 */  li      r3, 0
/* 089DE4 8008F384 4E800020 */  blr     
lbl_8008F388:
/* 089DE8 8008F388 3C608009 */  lis     r3, __osPopThread@ha
/* 089DEC 8008F38C 38036140 */  addi    r0, r3, __osPopThread@l
/* 089DF0 8008F390 7C040040 */  cmplw   r4, r0
/* 089DF4 8008F394 4082000C */  bne     lbl_8008F3A0
/* 089DF8 8008F398 38600000 */  li      r3, 0
/* 089DFC 8008F39C 4E800020 */  blr     
lbl_8008F3A0:
/* 089E00 8008F3A0 3C608009 */  lis     r3, __osDispatchThread@ha
/* 089E04 8008F3A4 38035B9C */  addi    r0, r3, __osDispatchThread@l
/* 089E08 8008F3A8 7C040040 */  cmplw   r4, r0
/* 089E0C 8008F3AC 4082000C */  bne     lbl_8008F3B8
/* 089E10 8008F3B0 38600000 */  li      r3, 0
/* 089E14 8008F3B4 4E800020 */  blr     
lbl_8008F3B8:
/* 089E18 8008F3B8 3C608009 */  lis     r3, __sinf@ha
/* 089E1C 8008F3BC 380358EC */  addi    r0, r3, __sinf@l
/* 089E20 8008F3C0 7C040040 */  cmplw   r4, r0
/* 089E24 8008F3C4 4082000C */  bne     lbl_8008F3D0
/* 089E28 8008F3C8 38600000 */  li      r3, 0
/* 089E2C 8008F3CC 4E800020 */  blr     
lbl_8008F3D0:
/* 089E30 8008F3D0 3C608009 */  lis     r3, osViSwapBuffer_Entry@ha
/* 089E34 8008F3D4 38030AD8 */  addi    r0, r3, osViSwapBuffer_Entry@l
/* 089E38 8008F3D8 7C040040 */  cmplw   r4, r0
/* 089E3C 8008F3DC 4082000C */  bne     lbl_8008F3E8
/* 089E40 8008F3E0 38600000 */  li      r3, 0
/* 089E44 8008F3E4 4E800020 */  blr     
lbl_8008F3E8:
/* 089E48 8008F3E8 3C608009 */  lis     r3, zeldaLoadSZS_Entry@ha
/* 089E4C 8008F3EC 38030AC4 */  addi    r0, r3, zeldaLoadSZS_Entry@l
/* 089E50 8008F3F0 7C040040 */  cmplw   r4, r0
/* 089E54 8008F3F4 4082000C */  bne     lbl_8008F400
/* 089E58 8008F3F8 38600000 */  li      r3, 0
/* 089E5C 8008F3FC 4E800020 */  blr     
lbl_8008F400:
/* 089E60 8008F400 3C608009 */  lis     r3, zeldaLoadSZS_Exit@ha
/* 089E64 8008F404 38030AB0 */  addi    r0, r3, zeldaLoadSZS_Exit@l
/* 089E68 8008F408 7C040040 */  cmplw   r4, r0
/* 089E6C 8008F40C 4082000C */  bne     lbl_8008F418
/* 089E70 8008F410 38600000 */  li      r3, 0
/* 089E74 8008F414 4E800020 */  blr     
lbl_8008F418:
/* 089E78 8008F418 38600001 */  li      r3, 1
/* 089E7C 8008F41C 4E800020 */  blr     
