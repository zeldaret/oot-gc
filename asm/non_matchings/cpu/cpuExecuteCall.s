glabel cpuExecuteCall
/* 033BB8 80039158 7C0802A6 */  mflr    r0
/* 033BBC 8003915C 90010004 */  stw     r0, 4(r1)
/* 033BC0 80039160 9421FFC8 */  stwu    r1, -0x38(r1)
/* 033BC4 80039164 93E10034 */  stw     r31, 0x34(r1)
/* 033BC8 80039168 93C10030 */  stw     r30, 0x30(r1)
/* 033BCC 8003916C 3BC50000 */  addi    r30, r5, 0
/* 033BD0 80039170 93A1002C */  stw     r29, 0x2c(r1)
/* 033BD4 80039174 93810028 */  stw     r28, 0x28(r1)
/* 033BD8 80039178 3B830000 */  addi    r28, r3, 0
/* 033BDC 8003917C 90C10014 */  stw     r6, 0x14(r1)
/* 033BE0 80039180 48069141 */  bl      OSGetTick
/* 033BE4 80039184 801C002C */  lwz     r0, 0x2c(r28)
/* 033BE8 80039188 3BA30000 */  addi    r29, r3, 0
/* 033BEC 8003918C 28000000 */  cmplwi  r0, 0
/* 033BF0 80039190 41820014 */  beq     lbl_800391A4
/* 033BF4 80039194 801C0000 */  lwz     r0, 0(r28)
/* 033BF8 80039198 60000008 */  ori     r0, r0, 8
/* 033BFC 8003919C 901C0000 */  stw     r0, 0(r28)
/* 033C00 800391A0 48000010 */  b       lbl_800391B0
lbl_800391A4:
/* 033C04 800391A4 801C0000 */  lwz     r0, 0(r28)
/* 033C08 800391A8 54000776 */  rlwinm  r0, r0, 0, 0x1d, 0x1b
/* 033C0C 800391AC 901C0000 */  stw     r0, 0(r28)
lbl_800391B0:
/* 033C10 800391B0 801C0000 */  lwz     r0, 0(r28)
/* 033C14 800391B4 387C0000 */  addi    r3, r28, 0
/* 033C18 800391B8 38A10018 */  addi    r5, r1, 0x18
/* 033C1C 800391BC 60000004 */  ori     r0, r0, 4
/* 033C20 800391C0 901C0000 */  stw     r0, 0(r28)
/* 033C24 800391C4 93DC0028 */  stw     r30, 0x28(r28)
/* 033C28 800391C8 80010014 */  lwz     r0, 0x14(r1)
/* 033C2C 800391CC 901C013C */  stw     r0, 0x13c(r28)
/* 033C30 800391D0 809C003C */  lwz     r4, 0x3c(r28)
/* 033C34 800391D4 80C10014 */  lwz     r6, 0x14(r1)
/* 033C38 800391D8 38040001 */  addi    r0, r4, 1
/* 033C3C 800391DC 901C003C */  stw     r0, 0x3c(r28)
/* 033C40 800391E0 3BE6FFFC */  addi    r31, r6, -4
/* 033C44 800391E4 809C0038 */  lwz     r4, 0x38(r28)
/* 033C48 800391E8 3884FFF8 */  addi    r4, r4, -8
/* 033C4C 800391EC 4BFFA119 */  bl      cpuFindFunction
/* 033C50 800391F0 80610018 */  lwz     r3, 0x18(r1)
/* 033C54 800391F4 38800000 */  li      r4, 0
/* 033C58 800391F8 8003001C */  lwz     r0, 0x1c(r3)
/* 033C5C 800391FC 80A30018 */  lwz     r5, 0x18(r3)
/* 033C60 80039200 2C000000 */  cmpwi   r0, 0
/* 033C64 80039204 7C0903A6 */  mtctr   r0
/* 033C68 80039208 38650000 */  addi    r3, r5, 0
/* 033C6C 8003920C 40810038 */  ble     lbl_80039244
lbl_80039210:
/* 033C70 80039210 80030000 */  lwz     r0, 0(r3)
/* 033C74 80039214 7C1E0000 */  cmpw    r30, r0
/* 033C78 80039218 40820020 */  bne     lbl_80039238
/* 033C7C 8003921C 80030004 */  lwz     r0, 4(r3)
/* 033C80 80039220 2C000000 */  cmpwi   r0, 0
/* 033C84 80039224 40820014 */  bne     lbl_80039238
/* 033C88 80039228 54801838 */  slwi    r0, r4, 3
/* 033C8C 8003922C 7C650214 */  add     r3, r5, r0
/* 033C90 80039230 93E30004 */  stw     r31, 4(r3)
/* 033C94 80039234 48000010 */  b       lbl_80039244
lbl_80039238:
/* 033C98 80039238 38630008 */  addi    r3, r3, 8
/* 033C9C 8003923C 38840001 */  addi    r4, r4, 1
/* 033CA0 80039240 4200FFD0 */  bdnz    lbl_80039210
lbl_80039244:
/* 033CA4 80039244 3C60800F */  lis     r3, ganMapGPR@ha
/* 033CA8 80039248 3863BE70 */  addi    r3, r3, ganMapGPR@l
/* 033CAC 8003924C 8083007C */  lwz     r4, 0x7c(r3)
/* 033CB0 80039250 548005EF */  rlwinm. r0, r4, 0, 0x17, 0x17
/* 033CB4 80039254 4182000C */  beq     lbl_80039260
/* 033CB8 80039258 3BE00001 */  li      r31, 1
/* 033CBC 8003925C 48000008 */  b       lbl_80039264
lbl_80039260:
/* 033CC0 80039260 3BE00000 */  li      r31, 0
lbl_80039264:
/* 033CC4 80039264 2C1F0000 */  cmpwi   r31, 0
/* 033CC8 80039268 4182000C */  beq     lbl_80039274
/* 033CCC 8003926C 38000004 */  li      r0, 4
/* 033CD0 80039270 48000008 */  b       lbl_80039278
lbl_80039274:
/* 033CD4 80039274 38000003 */  li      r0, 3
lbl_80039278:
/* 033CD8 80039278 2C1F0000 */  cmpwi   r31, 0
/* 033CDC 8003927C 80610014 */  lwz     r3, 0x14(r1)
/* 033CE0 80039280 5400103A */  slwi    r0, r0, 2
/* 033CE4 80039284 7FC01850 */  subf    r30, r0, r3
/* 033CE8 80039288 4182003C */  beq     lbl_800392C4
/* 033CEC 8003928C 5460843E */  srwi    r0, r3, 0x10
/* 033CF0 80039290 64003CA0 */  oris    r0, r0, 0x3ca0
/* 033CF4 80039294 901E0000 */  stw     r0, 0(r30)
/* 033CF8 80039298 387E0000 */  addi    r3, r30, 0
/* 033CFC 8003929C 38800008 */  li      r4, 8
/* 033D00 800392A0 80010014 */  lwz     r0, 0x14(r1)
/* 033D04 800392A4 5400043E */  clrlwi  r0, r0, 0x10
/* 033D08 800392A8 640060A5 */  oris    r0, r0, 0x60a5
/* 033D0C 800392AC 901E0004 */  stw     r0, 4(r30)
/* 033D10 800392B0 480644FD */  bl      DCStoreRange
/* 033D14 800392B4 387E0000 */  addi    r3, r30, 0
/* 033D18 800392B8 38800008 */  li      r4, 8
/* 033D1C 800392BC 48064579 */  bl      ICInvalidateRange
/* 033D20 800392C0 4800004C */  b       lbl_8003930C
lbl_800392C4:
/* 033D24 800392C4 5460843E */  srwi    r0, r3, 0x10
/* 033D28 800392C8 64003C00 */  oris    r0, r0, 0x3c00
/* 033D2C 800392CC 5486A814 */  slwi    r6, r4, 0x15
/* 033D30 800392D0 7C003378 */  or      r0, r0, r6
/* 033D34 800392D4 901E0000 */  stw     r0, 0(r30)
/* 033D38 800392D8 5485801E */  slwi    r5, r4, 0x10
/* 033D3C 800392DC 387E0000 */  addi    r3, r30, 0
/* 033D40 800392E0 80010014 */  lwz     r0, 0x14(r1)
/* 033D44 800392E4 38800008 */  li      r4, 8
/* 033D48 800392E8 5400043E */  clrlwi  r0, r0, 0x10
/* 033D4C 800392EC 64006000 */  oris    r0, r0, 0x6000
/* 033D50 800392F0 7C003378 */  or      r0, r0, r6
/* 033D54 800392F4 7CA00378 */  or      r0, r5, r0
/* 033D58 800392F8 901E0004 */  stw     r0, 4(r30)
/* 033D5C 800392FC 480644B1 */  bl      DCStoreRange
/* 033D60 80039300 387E0000 */  addi    r3, r30, 0
/* 033D64 80039304 38800008 */  li      r4, 8
/* 033D68 80039308 4806452D */  bl      ICInvalidateRange
lbl_8003930C:
/* 033D6C 8003930C 387C0000 */  addi    r3, r28, 0
/* 033D70 80039310 38BD0000 */  addi    r5, r29, 0
/* 033D74 80039314 38810014 */  addi    r4, r1, 0x14
/* 033D78 80039318 48004BF1 */  bl      cpuExecuteUpdate
/* 033D7C 8003931C 2C030000 */  cmpwi   r3, 0
/* 033D80 80039320 4082000C */  bne     lbl_8003932C
/* 033D84 80039324 38600000 */  li      r3, 0
/* 033D88 80039328 48000070 */  b       lbl_80039398
lbl_8003932C:
/* 033D8C 8003932C 2C1F0000 */  cmpwi   r31, 0
/* 033D90 80039330 80010014 */  lwz     r0, 0x14(r1)
/* 033D94 80039334 387E000C */  addi    r3, r30, 0xc
/* 033D98 80039338 7C030050 */  subf    r0, r3, r0
/* 033D9C 8003933C 4182002C */  beq     lbl_80039368
/* 033DA0 80039340 540001BA */  rlwinm  r0, r0, 0, 6, 0x1d
/* 033DA4 80039344 64004800 */  oris    r0, r0, 0x4800
/* 033DA8 80039348 901E000C */  stw     r0, 0xc(r30)
/* 033DAC 8003934C 387E0000 */  addi    r3, r30, 0
/* 033DB0 80039350 38800010 */  li      r4, 0x10
/* 033DB4 80039354 48064459 */  bl      DCStoreRange
/* 033DB8 80039358 387E0000 */  addi    r3, r30, 0
/* 033DBC 8003935C 38800010 */  li      r4, 0x10
/* 033DC0 80039360 480644D5 */  bl      ICInvalidateRange
/* 033DC4 80039364 48000028 */  b       lbl_8003938C
lbl_80039368:
/* 033DC8 80039368 540001BA */  rlwinm  r0, r0, 0, 6, 0x1d
/* 033DCC 8003936C 64004800 */  oris    r0, r0, 0x4800
/* 033DD0 80039370 901E0008 */  stw     r0, 8(r30)
/* 033DD4 80039374 387E0000 */  addi    r3, r30, 0
/* 033DD8 80039378 3880000C */  li      r4, 0xc
/* 033DDC 8003937C 48064431 */  bl      DCStoreRange
/* 033DE0 80039380 387E0000 */  addi    r3, r30, 0
/* 033DE4 80039384 3880000C */  li      r4, 0xc
/* 033DE8 80039388 480644AD */  bl      ICInvalidateRange
lbl_8003938C:
/* 033DEC 8003938C 48068F35 */  bl      OSGetTick
/* 033DF0 80039390 907C0B58 */  stw     r3, 0xb58(r28)
/* 033DF4 80039394 80610014 */  lwz     r3, 0x14(r1)
lbl_80039398:
/* 033DF8 80039398 8001003C */  lwz     r0, 0x3c(r1)
/* 033DFC 8003939C 83E10034 */  lwz     r31, 0x34(r1)
/* 033E00 800393A0 83C10030 */  lwz     r30, 0x30(r1)
/* 033E04 800393A4 7C0803A6 */  mtlr    r0
/* 033E08 800393A8 83A1002C */  lwz     r29, 0x2c(r1)
/* 033E0C 800393AC 83810028 */  lwz     r28, 0x28(r1)
/* 033E10 800393B0 38210038 */  addi    r1, r1, 0x38
/* 033E14 800393B4 4E800020 */  blr     
