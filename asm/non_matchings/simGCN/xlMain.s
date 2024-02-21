glabel xlMain
/* 0029E0 80007F80 7C0802A6 */  mflr    r0
/* 0029E4 80007F84 3C80800E */  lis     r4, gcoverOpen@ha
/* 0029E8 80007F88 90010004 */  stw     r0, 4(r1)
/* 0029EC 80007F8C 9421FFB8 */  stwu    r1, -0x48(r1)
/* 0029F0 80007F90 93E10044 */  stw     r31, 0x44(r1)
/* 0029F4 80007F94 3BE4B800 */  addi    r31, r4, gcoverOpen@l
/* 0029F8 80007F98 93C10040 */  stw     r30, 0x40(r1)
/* 0029FC 80007F9C 480005DD */  bl      simulatorParseArguments
/* 002A00 80007FA0 3BC00000 */  li      r30, 0
/* 002A04 80007FA4 93CD88F8 */  stw     r30, gDVDResetToggle@sda21(r13)
/* 002A08 80007FA8 38610034 */  addi    r3, r1, 0x34
/* 002A0C 80007FAC 4BFFE8C5 */  bl      xlHeapGetFree
/* 002A10 80007FB0 2C030000 */  cmpwi   r3, 0
/* 002A14 80007FB4 4082000C */  bne     lbl_80007FC0
/* 002A18 80007FB8 38600000 */  li      r3, 0
/* 002A1C 80007FBC 48000564 */  b       lbl_80008520
lbl_80007FC0:
/* 002A20 80007FC0 80810034 */  lwz     r4, 0x34(r1)
/* 002A24 80007FC4 3C000180 */  lis     r0, 0x180
/* 002A28 80007FC8 7C040000 */  cmpw    r4, r0
/* 002A2C 80007FCC 40810028 */  ble     lbl_80007FF4
/* 002A30 80007FD0 3C7F0001 */  addis   r3, r31, 1
/* 002A34 80007FD4 4CC63182 */  crclr   6
/* 002A38 80007FD8 3863E334 */  addi    r3, r3, -7372
/* 002A3C 80007FDC 4809661D */  bl      OSReport
/* 002A40 80007FE0 3C7F0001 */  addis   r3, r31, 1
/* 002A44 80007FE4 4CC63182 */  crclr   6
/* 002A48 80007FE8 3863E380 */  addi    r3, r3, -7296
/* 002A4C 80007FEC 4809660D */  bl      OSReport
lbl_80007FF0:
/* 002A50 80007FF0 48000000 */  b       lbl_80007FF0
lbl_80007FF4:
/* 002A54 80007FF4 38600706 */  li      r3, 0x706
/* 002A58 80007FF8 64630706 */  oris    r3, r3, 0x706
/* 002A5C 80007FFC 7C76E3A6 */  mtspr   0x396, r3
/* 002A60 80008000 38600507 */  li      r3, 0x507
/* 002A64 80008004 64630507 */  oris    r3, r3, 0x507
/* 002A68 80008008 7C77E3A6 */  mtspr   0x397, r3
/* 002A6C 8000800C 9BC1003E */  stb     r30, 0x3e(r1)
/* 002A70 80008010 38A00001 */  li      r5, 1
/* 002A74 80008014 9BC1003D */  stb     r30, 0x3d(r1)
/* 002A78 80008018 3C800100 */  lis     r4, 0x100
/* 002A7C 8000801C 380000FF */  li      r0, 0xff
/* 002A80 80008020 9BC1003C */  stb     r30, 0x3c(r1)
/* 002A84 80008024 38610008 */  addi    r3, r1, 8
/* 002A88 80008028 3884FFFF */  addi    r4, r4, -1
/* 002A8C 8000802C 9801003F */  stb     r0, 0x3f(r1)
/* 002A90 80008030 8001003C */  lwz     r0, 0x3c(r1)
/* 002A94 80008034 93CD891C */  stw     r30, gbDisplayedError@sda21(r13)
/* 002A98 80008038 93CD88F4 */  stw     r30, gButtonDownToggle@sda21(r13)
/* 002A9C 8000803C 90AD80B8 */  stw     r5, gResetBeginFlag@sda21(r13)
/* 002AA0 80008040 90010008 */  stw     r0, 8(r1)
/* 002AA4 80008044 480A3DF9 */  bl      GXSetCopyClear
/* 002AA8 80008048 38600001 */  li      r3, 1
/* 002AAC 8000804C 4809F75D */  bl      VISetBlack
/* 002AB0 80008050 4809F5BD */  bl      VIFlush
/* 002AB4 80008054 4809E8C9 */  bl      VIWaitForRetrace
/* 002AB8 80008058 4BFFD549 */  bl      xlCoreBeforeRender
/* 002ABC 8000805C 880D8DC8 */  lbz     r0, DemoStatEnable@sda21(r13)
/* 002AC0 80008060 28000000 */  cmplwi  r0, 0
/* 002AC4 80008064 41820020 */  beq     lbl_80008084
/* 002AC8 80008068 480A2FAD */  bl      GXDrawDone
/* 002ACC 8000806C 38600001 */  li      r3, 1
/* 002AD0 80008070 480AF551 */  bl      DEMOUpdateStats
/* 002AD4 80008074 480AF5A5 */  bl      DEMOPrintStats
/* 002AD8 80008078 480A2F9D */  bl      GXDrawDone
/* 002ADC 8000807C 38600000 */  li      r3, 0
/* 002AE0 80008080 480AF541 */  bl      DEMOUpdateStats
lbl_80008084:
/* 002AE4 80008084 38600001 */  li      r3, 1
/* 002AE8 80008088 38800003 */  li      r4, 3
/* 002AEC 8000808C 38A00001 */  li      r5, 1
/* 002AF0 80008090 480A6455 */  bl      GXSetZMode
/* 002AF4 80008094 38600001 */  li      r3, 1
/* 002AF8 80008098 480A63F5 */  bl      GXSetColorUpdate
/* 002AFC 8000809C 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 002B00 800080A0 38800001 */  li      r4, 1
/* 002B04 800080A4 480A402D */  bl      GXCopyDisp
/* 002B08 800080A8 480A2F6D */  bl      GXDrawDone
/* 002B0C 800080AC 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 002B10 800080B0 4809F68D */  bl      VISetNextFrameBuffer
/* 002B14 800080B4 4809F559 */  bl      VIFlush
/* 002B18 800080B8 4809E865 */  bl      VIWaitForRetrace
/* 002B1C 800080BC 808D8DAC */  lwz     r4, DemoCurrentBuffer@sda21(r13)
/* 002B20 800080C0 800D8DB4 */  lwz     r0, DemoFrameBuffer1@sda21(r13)
/* 002B24 800080C4 7C040040 */  cmplw   r4, r0
/* 002B28 800080C8 40820010 */  bne     lbl_800080D8
/* 002B2C 800080CC 800D8DB0 */  lwz     r0, DemoFrameBuffer2@sda21(r13)
/* 002B30 800080D0 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
/* 002B34 800080D4 48000008 */  b       lbl_800080DC
lbl_800080D8:
/* 002B38 800080D8 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
lbl_800080DC:
/* 002B3C 800080DC 4BFFD4C5 */  bl      xlCoreBeforeRender
/* 002B40 800080E0 880D8DC8 */  lbz     r0, DemoStatEnable@sda21(r13)
/* 002B44 800080E4 28000000 */  cmplwi  r0, 0
/* 002B48 800080E8 41820020 */  beq     lbl_80008108
/* 002B4C 800080EC 480A2F29 */  bl      GXDrawDone
/* 002B50 800080F0 38600001 */  li      r3, 1
/* 002B54 800080F4 480AF4CD */  bl      DEMOUpdateStats
/* 002B58 800080F8 480AF521 */  bl      DEMOPrintStats
/* 002B5C 800080FC 480A2F19 */  bl      GXDrawDone
/* 002B60 80008100 38600000 */  li      r3, 0
/* 002B64 80008104 480AF4BD */  bl      DEMOUpdateStats
lbl_80008108:
/* 002B68 80008108 38600001 */  li      r3, 1
/* 002B6C 8000810C 38800003 */  li      r4, 3
/* 002B70 80008110 38A00001 */  li      r5, 1
/* 002B74 80008114 480A63D1 */  bl      GXSetZMode
/* 002B78 80008118 38600001 */  li      r3, 1
/* 002B7C 8000811C 480A6371 */  bl      GXSetColorUpdate
/* 002B80 80008120 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 002B84 80008124 38800001 */  li      r4, 1
/* 002B88 80008128 480A3FA9 */  bl      GXCopyDisp
/* 002B8C 8000812C 480A2EE9 */  bl      GXDrawDone
/* 002B90 80008130 806D8DAC */  lwz     r3, DemoCurrentBuffer@sda21(r13)
/* 002B94 80008134 4809F609 */  bl      VISetNextFrameBuffer
/* 002B98 80008138 4809F4D5 */  bl      VIFlush
/* 002B9C 8000813C 4809E7E1 */  bl      VIWaitForRetrace
/* 002BA0 80008140 808D8DAC */  lwz     r4, DemoCurrentBuffer@sda21(r13)
/* 002BA4 80008144 800D8DB4 */  lwz     r0, DemoFrameBuffer1@sda21(r13)
/* 002BA8 80008148 7C040040 */  cmplw   r4, r0
/* 002BAC 8000814C 40820010 */  bne     lbl_8000815C
/* 002BB0 80008150 800D8DB0 */  lwz     r0, DemoFrameBuffer2@sda21(r13)
/* 002BB4 80008154 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
/* 002BB8 80008158 48000008 */  b       lbl_80008160
lbl_8000815C:
/* 002BBC 8000815C 900D8DAC */  stw     r0, DemoCurrentBuffer@sda21(r13)
lbl_80008160:
/* 002BC0 80008160 4809E7BD */  bl      VIWaitForRetrace
/* 002BC4 80008164 38600000 */  li      r3, 0
/* 002BC8 80008168 4809F641 */  bl      VISetBlack
/* 002BCC 8000816C 4809F4A1 */  bl      VIFlush
/* 002BD0 80008170 7FE3FB78 */  mr      r3, r31
/* 002BD4 80008174 48006EAD */  bl      simulatorUnpackTexPalette
/* 002BD8 80008178 387F28E0 */  addi    r3, r31, 0x28e0
/* 002BDC 8000817C 48006EA5 */  bl      simulatorUnpackTexPalette
/* 002BE0 80008180 387F4800 */  addi    r3, r31, 0x4800
/* 002BE4 80008184 48006E9D */  bl      simulatorUnpackTexPalette
/* 002BE8 80008188 387F6C60 */  addi    r3, r31, 0x6c60
/* 002BEC 8000818C 48006E95 */  bl      simulatorUnpackTexPalette
/* 002BF0 80008190 3C7F0001 */  addis   r3, r31, 1
/* 002BF4 80008194 38639F60 */  addi    r3, r3, -24736
/* 002BF8 80008198 48006E89 */  bl      simulatorUnpackTexPalette
/* 002BFC 8000819C 3C7F0001 */  addis   r3, r31, 1
/* 002C00 800081A0 3863BE80 */  addi    r3, r3, -16768
/* 002C04 800081A4 48006E7D */  bl      simulatorUnpackTexPalette
/* 002C08 800081A8 3C7F0001 */  addis   r3, r31, 1
/* 002C0C 800081AC 3863CAE0 */  addi    r3, r3, -13600
/* 002C10 800081B0 48006E71 */  bl      simulatorUnpackTexPalette
/* 002C14 800081B4 3C7F0001 */  addis   r3, r31, 1
/* 002C18 800081B8 3863D240 */  addi    r3, r3, -11712
/* 002C1C 800081BC 48006E65 */  bl      simulatorUnpackTexPalette
/* 002C20 800081C0 3C7F0001 */  addis   r3, r31, 1
/* 002C24 800081C4 3863D820 */  addi    r3, r3, -10208
/* 002C28 800081C8 48006E59 */  bl      simulatorUnpackTexPalette
/* 002C2C 800081CC 3C7F0001 */  addis   r3, r31, 1
/* 002C30 800081D0 3863DE00 */  addi    r3, r3, -8704
/* 002C34 800081D4 48006E4D */  bl      simulatorUnpackTexPalette
/* 002C38 800081D8 3BC00000 */  li      r30, 0
/* 002C3C 800081DC 93CD8908 */  stw     r30, gbReset@sda21(r13)
/* 002C40 800081E0 4809A0E1 */  bl      OSGetTick
/* 002C44 800081E4 906D890C */  stw     r3, gnTickReset@sda21(r13)
/* 002C48 800081E8 38610034 */  addi    r3, r1, 0x34
/* 002C4C 800081EC 4BFFE685 */  bl      xlHeapGetFree
/* 002C50 800081F0 2C030000 */  cmpwi   r3, 0
/* 002C54 800081F4 4082000C */  bne     lbl_80008200
/* 002C58 800081F8 38600000 */  li      r3, 0
/* 002C5C 800081FC 48000324 */  b       lbl_80008520
lbl_80008200:
/* 002C60 80008200 3C808010 */  lis     r4, mCard@ha
/* 002C64 80008204 388479B0 */  addi    r4, r4, mCard@l
/* 002C68 80008208 93C407A4 */  stw     r30, 0x7a4(r4)
/* 002C6C 8000820C 7C832378 */  mr      r3, r4
/* 002C70 80008210 93C407B0 */  stw     r30, 0x7b0(r4)
/* 002C74 80008214 48011269 */  bl      mcardInit
/* 002C78 80008218 3801002C */  addi    r0, r1, 0x2c
/* 002C7C 8000821C 7C00F040 */  cmplw   r0, r30
/* 002C80 80008220 41820020 */  beq     lbl_80008240
/* 002C84 80008224 3C80800F */  lis     r4, gaszArgument@ha
/* 002C88 80008228 800446C0 */  lwz     r0, gaszArgument@l(r4)
/* 002C8C 8000822C 7C00F040 */  cmplw   r0, r30
/* 002C90 80008230 41820010 */  beq     lbl_80008240
/* 002C94 80008234 9001002C */  stw     r0, 0x2c(r1)
/* 002C98 80008238 38000001 */  li      r0, 1
/* 002C9C 8000823C 48000008 */  b       lbl_80008244
lbl_80008240:
/* 002CA0 80008240 38000000 */  li      r0, 0
lbl_80008244:
/* 002CA4 80008244 2C000000 */  cmpwi   r0, 0
/* 002CA8 80008248 41820014 */  beq     lbl_8000825C
/* 002CAC 8000824C 3861000C */  addi    r3, r1, 0xc
/* 002CB0 80008250 8081002C */  lwz     r4, 0x2c(r1)
/* 002CB4 80008254 480C8755 */  bl      strcpy
/* 002CB8 80008258 48000014 */  b       lbl_8000826C
lbl_8000825C:
/* 002CBC 8000825C 3C9F0001 */  addis   r4, r31, 1
/* 002CC0 80008260 3861000C */  addi    r3, r1, 0xc
/* 002CC4 80008264 3884E3D0 */  addi    r4, r4, -7216
/* 002CC8 80008268 480C8741 */  bl      strcpy
lbl_8000826C:
/* 002CCC 8000826C 3861000C */  addi    r3, r1, 0xc
/* 002CD0 80008270 480C87ED */  bl      strlen
/* 002CD4 80008274 38A3FFFF */  addi    r5, r3, -1
/* 002CD8 80008278 3801000C */  addi    r0, r1, 0xc
/* 002CDC 8000827C 7C802A14 */  add     r4, r0, r5
/* 002CE0 80008280 4800000C */  b       lbl_8000828C
lbl_80008284:
/* 002CE4 80008284 38A5FFFF */  addi    r5, r5, -1
/* 002CE8 80008288 3884FFFF */  addi    r4, r4, -1
lbl_8000828C:
/* 002CEC 8000828C 2C050000 */  cmpwi   r5, 0
/* 002CF0 80008290 41800010 */  blt     lbl_800082A0
/* 002CF4 80008294 88040000 */  lbz     r0, 0(r4)
/* 002CF8 80008298 2C00002E */  cmpwi   r0, 0x2e
/* 002CFC 8000829C 4082FFE8 */  bne     lbl_80008284
lbl_800082A0:
/* 002D00 800082A0 2C050000 */  cmpwi   r5, 0
/* 002D04 800082A4 40800048 */  bge     lbl_800082EC
/* 002D08 800082A8 3861000C */  addi    r3, r1, 0xc
/* 002D0C 800082AC 480C87B1 */  bl      strlen
/* 002D10 800082B0 3881000C */  addi    r4, r1, 0xc
/* 002D14 800082B4 3800002E */  li      r0, 0x2e
/* 002D18 800082B8 7C0419AE */  stbx    r0, r4, r3
/* 002D1C 800082BC 3881000D */  addi    r4, r1, 0xd
/* 002D20 800082C0 3800004E */  li      r0, 0x4e
/* 002D24 800082C4 7C0419AE */  stbx    r0, r4, r3
/* 002D28 800082C8 3881000E */  addi    r4, r1, 0xe
/* 002D2C 800082CC 38000036 */  li      r0, 0x36
/* 002D30 800082D0 7C0419AE */  stbx    r0, r4, r3
/* 002D34 800082D4 3881000F */  addi    r4, r1, 0xf
/* 002D38 800082D8 38000034 */  li      r0, 0x34
/* 002D3C 800082DC 7C0419AE */  stbx    r0, r4, r3
/* 002D40 800082E0 38810010 */  addi    r4, r1, 0x10
/* 002D44 800082E4 38000000 */  li      r0, 0
/* 002D48 800082E8 7C0419AE */  stbx    r0, r4, r3
lbl_800082EC:
/* 002D4C 800082EC 38000000 */  li      r0, 0
/* 002D50 800082F0 3C80800F */  lis     r4, gClassCode@ha
/* 002D54 800082F4 900D8920 */  stw     r0, gpSystem@sda21(r13)
/* 002D58 800082F8 38A4A7C8 */  addi    r5, r4, gClassCode@l
/* 002D5C 800082FC 386D88F0 */  addi    r3, r13, gpCode@sda21
/* 002D60 80008300 38800000 */  li      r4, 0
/* 002D64 80008304 4BFFFB21 */  bl      xlObjectMake
/* 002D68 80008308 2C030000 */  cmpwi   r3, 0
/* 002D6C 8000830C 4082000C */  bne     lbl_80008318
/* 002D70 80008310 38600000 */  li      r3, 0
/* 002D74 80008314 4800020C */  b       lbl_80008520
lbl_80008318:
/* 002D78 80008318 3C80800F */  lis     r4, gClassFrame@ha
/* 002D7C 8000831C 38A4A848 */  addi    r5, r4, gClassFrame@l
/* 002D80 80008320 386D8928 */  addi    r3, r13, gpFrame@sda21
/* 002D84 80008324 38800000 */  li      r4, 0
/* 002D88 80008328 4BFFFAFD */  bl      xlObjectMake
/* 002D8C 8000832C 2C030000 */  cmpwi   r3, 0
/* 002D90 80008330 4082000C */  bne     lbl_8000833C
/* 002D94 80008334 38600000 */  li      r3, 0
/* 002D98 80008338 480001E8 */  b       lbl_80008520
lbl_8000833C:
/* 002D9C 8000833C 3C80800F */  lis     r4, gClassSound@ha
/* 002DA0 80008340 38A4A7D8 */  addi    r5, r4, gClassSound@l
/* 002DA4 80008344 386D8924 */  addi    r3, r13, gpSound@sda21
/* 002DA8 80008348 38800000 */  li      r4, 0
/* 002DAC 8000834C 4BFFFAD9 */  bl      xlObjectMake
/* 002DB0 80008350 2C030000 */  cmpwi   r3, 0
/* 002DB4 80008354 4082000C */  bne     lbl_80008360
/* 002DB8 80008358 38600000 */  li      r3, 0
/* 002DBC 8000835C 480001C4 */  b       lbl_80008520
lbl_80008360:
/* 002DC0 80008360 3C80800F */  lis     r4, gClassSystem@ha
/* 002DC4 80008364 38A4B310 */  addi    r5, r4, gClassSystem@l
/* 002DC8 80008368 386D8920 */  addi    r3, r13, gpSystem@sda21
/* 002DCC 8000836C 38800000 */  li      r4, 0
/* 002DD0 80008370 4BFFFAB5 */  bl      xlObjectMake
/* 002DD4 80008374 2C030000 */  cmpwi   r3, 0
/* 002DD8 80008378 4082000C */  bne     lbl_80008384
/* 002DDC 8000837C 38600000 */  li      r3, 0
/* 002DE0 80008380 480001A0 */  b       lbl_80008520
lbl_80008384:
/* 002DE4 80008384 3C808001 */  lis     r4, simulatorDVDOpen@ha
/* 002DE8 80008388 3864EDA8 */  addi    r3, r4, simulatorDVDOpen@l
/* 002DEC 8000838C 4BFFDEE9 */  bl      xlFileSetOpen
/* 002DF0 80008390 2C030000 */  cmpwi   r3, 0
/* 002DF4 80008394 4082000C */  bne     lbl_800083A0
/* 002DF8 80008398 38600000 */  li      r3, 0
/* 002DFC 8000839C 48000184 */  b       lbl_80008520
lbl_800083A0:
/* 002E00 800083A0 3C808001 */  lis     r4, simulatorDVDRead@ha
/* 002E04 800083A4 3864ECC4 */  addi    r3, r4, simulatorDVDRead@l
/* 002E08 800083A8 4BFFDEC1 */  bl      xlFileSetRead
/* 002E0C 800083AC 2C030000 */  cmpwi   r3, 0
/* 002E10 800083B0 4082000C */  bne     lbl_800083BC
/* 002E14 800083B4 38600000 */  li      r3, 0
/* 002E18 800083B8 48000168 */  b       lbl_80008520
lbl_800083BC:
/* 002E1C 800083BC 80CD8920 */  lwz     r6, gpSystem@sda21(r13)
/* 002E20 800083C0 38800000 */  li      r4, 0
/* 002E24 800083C4 38AD80BC */  addi    r5, r13, D_80134D9C@sda21
/* 002E28 800083C8 80660004 */  lwz     r3, 4(r6)
/* 002E2C 800083CC 48014341 */  bl      soundLoadBeep
/* 002E30 800083D0 80CD8920 */  lwz     r6, gpSystem@sda21(r13)
/* 002E34 800083D4 38800001 */  li      r4, 1
/* 002E38 800083D8 38AD80C4 */  addi    r5, r13, D_80134DA4@sda21
/* 002E3C 800083DC 80660004 */  lwz     r3, 4(r6)
/* 002E40 800083E0 4801432D */  bl      soundLoadBeep
/* 002E44 800083E4 808D8920 */  lwz     r4, gpSystem@sda21(r13)
/* 002E48 800083E8 3CBF0001 */  addis   r5, r31, 1
/* 002E4C 800083EC 38A5E3DC */  addi    r5, r5, -7204
/* 002E50 800083F0 80640004 */  lwz     r3, 4(r4)
/* 002E54 800083F4 38800002 */  li      r4, 2
/* 002E58 800083F8 48014315 */  bl      soundLoadBeep
/* 002E5C 800083FC 80AD8920 */  lwz     r5, gpSystem@sda21(r13)
/* 002E60 80008400 3881000C */  addi    r4, r1, 0xc
/* 002E64 80008404 80650030 */  lwz     r3, 0x30(r5)
/* 002E68 80008408 48065219 */  bl      romSetImage
/* 002E6C 8000840C 2C030000 */  cmpwi   r3, 0
/* 002E70 80008410 4082000C */  bne     lbl_8000841C
/* 002E74 80008414 38600000 */  li      r3, 0
/* 002E78 80008418 48000108 */  b       lbl_80008520
lbl_8000841C:
/* 002E7C 8000841C 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 002E80 80008420 48025159 */  bl      systemReset
/* 002E84 80008424 2C030000 */  cmpwi   r3, 0
/* 002E88 80008428 4082000C */  bne     lbl_80008434
/* 002E8C 8000842C 38600000 */  li      r3, 0
/* 002E90 80008430 480000F0 */  b       lbl_80008520
lbl_80008434:
/* 002E94 80008434 806D8928 */  lwz     r3, gpFrame@sda21(r13)
/* 002E98 80008438 4801DCE5 */  bl      frameShow
/* 002E9C 8000843C 2C030000 */  cmpwi   r3, 0
/* 002EA0 80008440 4082000C */  bne     lbl_8000844C
/* 002EA4 80008444 38600000 */  li      r3, 0
/* 002EA8 80008448 480000D8 */  b       lbl_80008520
lbl_8000844C:
/* 002EAC 8000844C 38610030 */  addi    r3, r1, 0x30
/* 002EB0 80008450 4BFFE421 */  bl      xlHeapGetFree
/* 002EB4 80008454 2C030000 */  cmpwi   r3, 0
/* 002EB8 80008458 4082000C */  bne     lbl_80008464
/* 002EBC 8000845C 38600000 */  li      r3, 0
/* 002EC0 80008460 480000C0 */  b       lbl_80008520
lbl_80008464:
/* 002EC4 80008464 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 002EC8 80008468 38800000 */  li      r4, 0
/* 002ECC 8000846C 48025429 */  bl      systemSetMode
/* 002ED0 80008470 2C030000 */  cmpwi   r3, 0
/* 002ED4 80008474 40820024 */  bne     lbl_80008498
/* 002ED8 80008478 38600000 */  li      r3, 0
/* 002EDC 8000847C 480000A4 */  b       lbl_80008520
lbl_80008480:
/* 002EE0 80008480 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 002EE4 80008484 389F86A0 */  addi    r4, r31, -31072
/* 002EE8 80008488 48024FF5 */  bl      systemExecute
/* 002EEC 8000848C 2C030000 */  cmpwi   r3, 0
/* 002EF0 80008490 4082000C */  bne     lbl_8000849C
/* 002EF4 80008494 48000028 */  b       lbl_800084BC
lbl_80008498:
/* 002EF8 80008498 3FE00002 */  lis     r31, 2
lbl_8000849C:
/* 002EFC 8000849C 806D8920 */  lwz     r3, gpSystem@sda21(r13)
/* 002F00 800084A0 38810038 */  addi    r4, r1, 0x38
/* 002F04 800084A4 48025389 */  bl      systemGetMode
/* 002F08 800084A8 2C030000 */  cmpwi   r3, 0
/* 002F0C 800084AC 41820010 */  beq     lbl_800084BC
/* 002F10 800084B0 80010038 */  lwz     r0, 0x38(r1)
/* 002F14 800084B4 2C000000 */  cmpwi   r0, 0
/* 002F18 800084B8 4182FFC8 */  beq     lbl_80008480
lbl_800084BC:
/* 002F1C 800084BC 386D8920 */  addi    r3, r13, gpSystem@sda21
/* 002F20 800084C0 4BFFF8CD */  bl      xlObjectFree
/* 002F24 800084C4 2C030000 */  cmpwi   r3, 0
/* 002F28 800084C8 4082000C */  bne     lbl_800084D4
/* 002F2C 800084CC 38600000 */  li      r3, 0
/* 002F30 800084D0 48000050 */  b       lbl_80008520
lbl_800084D4:
/* 002F34 800084D4 386D8924 */  addi    r3, r13, gpSound@sda21
/* 002F38 800084D8 4BFFF8B5 */  bl      xlObjectFree
/* 002F3C 800084DC 2C030000 */  cmpwi   r3, 0
/* 002F40 800084E0 4082000C */  bne     lbl_800084EC
/* 002F44 800084E4 38600000 */  li      r3, 0
/* 002F48 800084E8 48000038 */  b       lbl_80008520
lbl_800084EC:
/* 002F4C 800084EC 386D8928 */  addi    r3, r13, gpFrame@sda21
/* 002F50 800084F0 4BFFF89D */  bl      xlObjectFree
/* 002F54 800084F4 2C030000 */  cmpwi   r3, 0
/* 002F58 800084F8 4082000C */  bne     lbl_80008504
/* 002F5C 800084FC 38600000 */  li      r3, 0
/* 002F60 80008500 48000020 */  b       lbl_80008520
lbl_80008504:
/* 002F64 80008504 386D88F0 */  addi    r3, r13, gpCode@sda21
/* 002F68 80008508 4BFFF885 */  bl      xlObjectFree
/* 002F6C 8000850C 2C030000 */  cmpwi   r3, 0
/* 002F70 80008510 4082000C */  bne     lbl_8000851C
/* 002F74 80008514 38600000 */  li      r3, 0
/* 002F78 80008518 48000008 */  b       lbl_80008520
lbl_8000851C:
/* 002F7C 8000851C 38600001 */  li      r3, 1
lbl_80008520:
/* 002F80 80008520 8001004C */  lwz     r0, 0x4c(r1)
/* 002F84 80008524 83E10044 */  lwz     r31, 0x44(r1)
/* 002F88 80008528 83C10040 */  lwz     r30, 0x40(r1)
/* 002F8C 8000852C 7C0803A6 */  mtlr    r0
/* 002F90 80008530 38210048 */  addi    r1, r1, 0x48
/* 002F94 80008534 4E800020 */  blr     
