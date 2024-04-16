glabel frameDrawReset
/* 01AD5C 800202FC 8003007C */  lwz     r0, 0x7c(r3)
/* 01AD60 80020300 3CA08002 */  lis     r5, frameDrawLine_Setup@ha
/* 01AD64 80020304 3CC08002 */  lis     r6, frameDrawTriangle_Setup@ha
/* 01AD68 80020308 7C002378 */  or      r0, r0, r4
/* 01AD6C 8002030C 9003007C */  stw     r0, 0x7c(r3)
/* 01AD70 80020310 38056D30 */  addi    r0, r5, frameDrawLine_Setup@l
/* 01AD74 80020314 3CA08002 */  lis     r5, frameDrawRectFill_Setup@ha
/* 01AD78 80020318 9003012C */  stw     r0, 0x12c(r3)
/* 01AD7C 8002031C 38067900 */  addi    r0, r6, frameDrawTriangle_Setup@l
/* 01AD80 80020320 3C808002 */  lis     r4, frameDrawRectTexture_Setup@ha
/* 01AD84 80020324 90030130 */  stw     r0, 0x130(r3)
/* 01AD88 80020328 38A569EC */  addi    r5, r5, frameDrawRectFill_Setup@l
/* 01AD8C 8002032C 38046124 */  addi    r0, r4, frameDrawRectTexture_Setup@l
/* 01AD90 80020330 90A30134 */  stw     r5, 0x134(r3)
/* 01AD94 80020334 90030138 */  stw     r0, 0x138(r3)
/* 01AD98 80020338 38600001 */  li      r3, 1
/* 01AD9C 8002033C 4E800020 */  blr     
