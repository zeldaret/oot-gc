glabel __osEnqueueThread
/* 090C74 80096214 7C0802A6 */  mflr    r0
/* 090C78 80096218 90010004 */  stw     r0, 4(r1)
/* 090C7C 8009621C 9421FFE0 */  stwu    r1, -0x20(r1)
/* 090C80 80096220 93E1001C */  stw     r31, 0x1c(r1)
/* 090C84 80096224 93C10018 */  stw     r30, 0x18(r1)
/* 090C88 80096228 93A10014 */  stw     r29, 0x14(r1)
/* 090C8C 8009622C 7C7D1B78 */  mr      r29, r3
/* 090C90 80096230 3BDD0F64 */  addi    r30, r29, 0xf64
/* 090C94 80096234 80030064 */  lwz     r0, 0x64(r3)
/* 090C98 80096238 3BFD0B64 */  addi    r31, r29, 0xb64
/* 090C9C 8009623C 38BD0104 */  addi    r5, r29, 0x104
/* 090CA0 80096240 9003010C */  stw     r0, 0x10c(r3)
/* 090CA4 80096244 80830064 */  lwz     r4, 0x64(r3)
/* 090CA8 80096248 5480843E */  srwi    r0, r4, 0x10
/* 090CAC 8009624C 7C1E00AE */  lbzx    r0, r30, r0
/* 090CB0 80096250 5400103A */  slwi    r0, r0, 2
/* 090CB4 80096254 7C7F002E */  lwzx    r3, r31, r0
/* 090CB8 80096258 81830014 */  lwz     r12, 0x14(r3)
/* 090CBC 8009625C 80030008 */  lwz     r0, 8(r3)
/* 090CC0 80096260 7D8803A6 */  mtlr    r12
/* 090CC4 80096264 80630004 */  lwz     r3, 4(r3)
/* 090CC8 80096268 7C840214 */  add     r4, r4, r0
/* 090CCC 8009626C 4E800021 */  blrl    
/* 090CD0 80096270 807D006C */  lwz     r3, 0x6c(r29)
/* 090CD4 80096274 38BD00BC */  addi    r5, r29, 0xbc
/* 090CD8 80096278 38830004 */  addi    r4, r3, 4
/* 090CDC 8009627C 5480843E */  srwi    r0, r4, 0x10
/* 090CE0 80096280 7C1E00AE */  lbzx    r0, r30, r0
/* 090CE4 80096284 5400103A */  slwi    r0, r0, 2
/* 090CE8 80096288 7C7F002E */  lwzx    r3, r31, r0
/* 090CEC 8009628C 81830014 */  lwz     r12, 0x14(r3)
/* 090CF0 80096290 80030008 */  lwz     r0, 8(r3)
/* 090CF4 80096294 7D8803A6 */  mtlr    r12
/* 090CF8 80096298 80630004 */  lwz     r3, 4(r3)
/* 090CFC 8009629C 7C840214 */  add     r4, r4, r0
/* 090D00 800962A0 4E800021 */  blrl    
/* 090D04 800962A4 807D0104 */  lwz     r3, 0x104(r29)
/* 090D08 800962A8 38BD00B4 */  addi    r5, r29, 0xb4
/* 090D0C 800962AC 38830004 */  addi    r4, r3, 4
/* 090D10 800962B0 5480843E */  srwi    r0, r4, 0x10
/* 090D14 800962B4 7C1E00AE */  lbzx    r0, r30, r0
/* 090D18 800962B8 5400103A */  slwi    r0, r0, 2
/* 090D1C 800962BC 7C7F002E */  lwzx    r3, r31, r0
/* 090D20 800962C0 81830014 */  lwz     r12, 0x14(r3)
/* 090D24 800962C4 80030008 */  lwz     r0, 8(r3)
/* 090D28 800962C8 7D8803A6 */  mtlr    r12
/* 090D2C 800962CC 80630004 */  lwz     r3, 4(r3)
/* 090D30 800962D0 7C840214 */  add     r4, r4, r0
/* 090D34 800962D4 4E800021 */  blrl    
/* 090D38 800962D8 48000070 */  b       lbl_80096348
lbl_800962DC:
/* 090D3C 800962DC 801D0104 */  lwz     r0, 0x104(r29)
/* 090D40 800962E0 38BD0104 */  addi    r5, r29, 0x104
/* 090D44 800962E4 901D010C */  stw     r0, 0x10c(r29)
/* 090D48 800962E8 809D0104 */  lwz     r4, 0x104(r29)
/* 090D4C 800962EC 5480843E */  srwi    r0, r4, 0x10
/* 090D50 800962F0 7C1E00AE */  lbzx    r0, r30, r0
/* 090D54 800962F4 5400103A */  slwi    r0, r0, 2
/* 090D58 800962F8 7C7F002E */  lwzx    r3, r31, r0
/* 090D5C 800962FC 81830014 */  lwz     r12, 0x14(r3)
/* 090D60 80096300 80030008 */  lwz     r0, 8(r3)
/* 090D64 80096304 7D8803A6 */  mtlr    r12
/* 090D68 80096308 80630004 */  lwz     r3, 4(r3)
/* 090D6C 8009630C 7C840214 */  add     r4, r4, r0
/* 090D70 80096310 4E800021 */  blrl    
/* 090D74 80096314 807D0104 */  lwz     r3, 0x104(r29)
/* 090D78 80096318 38BD00B4 */  addi    r5, r29, 0xb4
/* 090D7C 8009631C 38830004 */  addi    r4, r3, 4
/* 090D80 80096320 5480843E */  srwi    r0, r4, 0x10
/* 090D84 80096324 7C1E00AE */  lbzx    r0, r30, r0
/* 090D88 80096328 5400103A */  slwi    r0, r0, 2
/* 090D8C 8009632C 7C7F002E */  lwzx    r3, r31, r0
/* 090D90 80096330 81830014 */  lwz     r12, 0x14(r3)
/* 090D94 80096334 80030008 */  lwz     r0, 8(r3)
/* 090D98 80096338 7D8803A6 */  mtlr    r12
/* 090D9C 8009633C 80630004 */  lwz     r3, 4(r3)
/* 090DA0 80096340 7C840214 */  add     r4, r4, r0
/* 090DA4 80096344 4E800021 */  blrl    
lbl_80096348:
/* 090DA8 80096348 807D00B4 */  lwz     r3, 0xb4(r29)
/* 090DAC 8009634C 801D00BC */  lwz     r0, 0xbc(r29)
/* 090DB0 80096350 7C030000 */  cmpw    r3, r0
/* 090DB4 80096354 4080FF88 */  bge     lbl_800962DC
/* 090DB8 80096358 809D010C */  lwz     r4, 0x10c(r29)
/* 090DBC 8009635C 38BD0104 */  addi    r5, r29, 0x104
/* 090DC0 80096360 5480843E */  srwi    r0, r4, 0x10
/* 090DC4 80096364 7C1E00AE */  lbzx    r0, r30, r0
/* 090DC8 80096368 5400103A */  slwi    r0, r0, 2
/* 090DCC 8009636C 7C7F002E */  lwzx    r3, r31, r0
/* 090DD0 80096370 81830014 */  lwz     r12, 0x14(r3)
/* 090DD4 80096374 80030008 */  lwz     r0, 8(r3)
/* 090DD8 80096378 7D8803A6 */  mtlr    r12
/* 090DDC 8009637C 80630004 */  lwz     r3, 4(r3)
/* 090DE0 80096380 7C840214 */  add     r4, r4, r0
/* 090DE4 80096384 4E800021 */  blrl    
/* 090DE8 80096388 809D006C */  lwz     r4, 0x6c(r29)
/* 090DEC 8009638C 38BD0104 */  addi    r5, r29, 0x104
/* 090DF0 80096390 5480843E */  srwi    r0, r4, 0x10
/* 090DF4 80096394 7C1E00AE */  lbzx    r0, r30, r0
/* 090DF8 80096398 5400103A */  slwi    r0, r0, 2
/* 090DFC 8009639C 7C7F002E */  lwzx    r3, r31, r0
/* 090E00 800963A0 81830024 */  lwz     r12, 0x24(r3)
/* 090E04 800963A4 80030008 */  lwz     r0, 8(r3)
/* 090E08 800963A8 7D8803A6 */  mtlr    r12
/* 090E0C 800963AC 80630004 */  lwz     r3, 4(r3)
/* 090E10 800963B0 7C840214 */  add     r4, r4, r0
/* 090E14 800963B4 4E800021 */  blrl    
/* 090E18 800963B8 809D010C */  lwz     r4, 0x10c(r29)
/* 090E1C 800963BC 38BD006C */  addi    r5, r29, 0x6c
/* 090E20 800963C0 5480843E */  srwi    r0, r4, 0x10
/* 090E24 800963C4 7C1E00AE */  lbzx    r0, r30, r0
/* 090E28 800963C8 5400103A */  slwi    r0, r0, 2
/* 090E2C 800963CC 7C7F002E */  lwzx    r3, r31, r0
/* 090E30 800963D0 81830024 */  lwz     r12, 0x24(r3)
/* 090E34 800963D4 80030008 */  lwz     r0, 8(r3)
/* 090E38 800963D8 7D8803A6 */  mtlr    r12
/* 090E3C 800963DC 80630004 */  lwz     r3, 4(r3)
/* 090E40 800963E0 7C840214 */  add     r4, r4, r0
/* 090E44 800963E4 4E800021 */  blrl    
/* 090E48 800963E8 807D006C */  lwz     r3, 0x6c(r29)
/* 090E4C 800963EC 38BD0064 */  addi    r5, r29, 0x64
/* 090E50 800963F0 38830008 */  addi    r4, r3, 8
/* 090E54 800963F4 5480843E */  srwi    r0, r4, 0x10
/* 090E58 800963F8 7C1E00AE */  lbzx    r0, r30, r0
/* 090E5C 800963FC 5400103A */  slwi    r0, r0, 2
/* 090E60 80096400 7C7F002E */  lwzx    r3, r31, r0
/* 090E64 80096404 81830024 */  lwz     r12, 0x24(r3)
/* 090E68 80096408 80030008 */  lwz     r0, 8(r3)
/* 090E6C 8009640C 7D8803A6 */  mtlr    r12
/* 090E70 80096410 80630004 */  lwz     r3, 4(r3)
/* 090E74 80096414 7C840214 */  add     r4, r4, r0
/* 090E78 80096418 4E800021 */  blrl    
/* 090E7C 8009641C 80010024 */  lwz     r0, 0x24(r1)
/* 090E80 80096420 38600001 */  li      r3, 1
/* 090E84 80096424 83E1001C */  lwz     r31, 0x1c(r1)
/* 090E88 80096428 83C10018 */  lwz     r30, 0x18(r1)
/* 090E8C 8009642C 7C0803A6 */  mtlr    r0
/* 090E90 80096430 83A10014 */  lwz     r29, 0x14(r1)
/* 090E94 80096434 38210020 */  addi    r1, r1, 0x20
/* 090E98 80096438 4E800020 */  blr     
