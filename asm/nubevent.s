# nubevent.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel TRKInitializeEventQueue
/* 0C3C08 800C91A8 7C0802A6 */  mflr    r0
/* 0C3C0C 800C91AC 3C608013 */  lis     r3, gTRKEventQueue@ha
/* 0C3C10 800C91B0 90010004 */  stw     r0, 4(r1)
/* 0C3C14 800C91B4 9421FFF0 */  stwu    r1, -0x10(r1)
/* 0C3C18 800C91B8 93E1000C */  stw     r31, 0xc(r1)
/* 0C3C1C 800C91BC 3BE32B50 */  addi    r31, r3, gTRKEventQueue@l
/* 0C3C20 800C91C0 387F0000 */  addi    r3, r31, 0
/* 0C3C24 800C91C4 48002591 */  bl      TRKInitializeMutex
/* 0C3C28 800C91C8 7FE3FB78 */  mr      r3, r31
/* 0C3C2C 800C91CC 48002591 */  bl      TRKAcquireMutex
/* 0C3C30 800C91D0 38600000 */  li      r3, 0
/* 0C3C34 800C91D4 907F0004 */  stw     r3, 4(r31)
/* 0C3C38 800C91D8 38000100 */  li      r0, 0x100
/* 0C3C3C 800C91DC 907F0008 */  stw     r3, 8(r31)
/* 0C3C40 800C91E0 7FE3FB78 */  mr      r3, r31
/* 0C3C44 800C91E4 901F0024 */  stw     r0, 0x24(r31)
/* 0C3C48 800C91E8 4800257D */  bl      TRKReleaseMutex
/* 0C3C4C 800C91EC 38600000 */  li      r3, 0
/* 0C3C50 800C91F0 83E1000C */  lwz     r31, 0xc(r1)
/* 0C3C54 800C91F4 38210010 */  addi    r1, r1, 0x10
/* 0C3C58 800C91F8 80010004 */  lwz     r0, 4(r1)
/* 0C3C5C 800C91FC 7C0803A6 */  mtlr    r0
/* 0C3C60 800C9200 4E800020 */  blr     

glabel TRKCopyEvent
/* 0C3C64 800C9204 7C0802A6 */  mflr    r0
/* 0C3C68 800C9208 38A0000C */  li      r5, 0xc
/* 0C3C6C 800C920C 90010004 */  stw     r0, 4(r1)
/* 0C3C70 800C9210 9421FFF8 */  stwu    r1, -8(r1)
/* 0C3C74 800C9214 4BF3A245 */  bl      TRK_memcpy
/* 0C3C78 800C9218 38210008 */  addi    r1, r1, 8
/* 0C3C7C 800C921C 80010004 */  lwz     r0, 4(r1)
/* 0C3C80 800C9220 7C0803A6 */  mtlr    r0
/* 0C3C84 800C9224 4E800020 */  blr     

glabel TRKGetNextEvent
/* 0C3C88 800C9228 7C0802A6 */  mflr    r0
/* 0C3C8C 800C922C 3C808013 */  lis     r4, gTRKEventQueue@ha
/* 0C3C90 800C9230 90010004 */  stw     r0, 4(r1)
/* 0C3C94 800C9234 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0C3C98 800C9238 93E10014 */  stw     r31, 0x14(r1)
/* 0C3C9C 800C923C 3BE42B50 */  addi    r31, r4, gTRKEventQueue@l
/* 0C3CA0 800C9240 93C10010 */  stw     r30, 0x10(r1)
/* 0C3CA4 800C9244 93A1000C */  stw     r29, 0xc(r1)
/* 0C3CA8 800C9248 3BA00000 */  li      r29, 0
/* 0C3CAC 800C924C 93810008 */  stw     r28, 8(r1)
/* 0C3CB0 800C9250 3B830000 */  addi    r28, r3, 0
/* 0C3CB4 800C9254 387F0000 */  addi    r3, r31, 0
/* 0C3CB8 800C9258 48002505 */  bl      TRKAcquireMutex
/* 0C3CBC 800C925C 3BDF0004 */  addi    r30, r31, 4
/* 0C3CC0 800C9260 801F0004 */  lwz     r0, 4(r31)
/* 0C3CC4 800C9264 2C000000 */  cmpwi   r0, 0
/* 0C3CC8 800C9268 40810050 */  ble     lbl_800C92B8
/* 0C3CCC 800C926C 3BBF0008 */  addi    r29, r31, 8
/* 0C3CD0 800C9270 801F0008 */  lwz     r0, 8(r31)
/* 0C3CD4 800C9274 387C0000 */  addi    r3, r28, 0
/* 0C3CD8 800C9278 1C00000C */  mulli   r0, r0, 0xc
/* 0C3CDC 800C927C 7C9F0214 */  add     r4, r31, r0
/* 0C3CE0 800C9280 3884000C */  addi    r4, r4, 0xc
/* 0C3CE4 800C9284 4BFFFF81 */  bl      TRKCopyEvent
/* 0C3CE8 800C9288 807E0000 */  lwz     r3, 0(r30)
/* 0C3CEC 800C928C 3803FFFF */  addi    r0, r3, -1
/* 0C3CF0 800C9290 901E0000 */  stw     r0, 0(r30)
/* 0C3CF4 800C9294 807D0000 */  lwz     r3, 0(r29)
/* 0C3CF8 800C9298 38030001 */  addi    r0, r3, 1
/* 0C3CFC 800C929C 901D0000 */  stw     r0, 0(r29)
/* 0C3D00 800C92A0 801D0000 */  lwz     r0, 0(r29)
/* 0C3D04 800C92A4 2C000002 */  cmpwi   r0, 2
/* 0C3D08 800C92A8 4082000C */  bne     lbl_800C92B4
/* 0C3D0C 800C92AC 38000000 */  li      r0, 0
/* 0C3D10 800C92B0 901D0000 */  stw     r0, 0(r29)
lbl_800C92B4:
/* 0C3D14 800C92B4 3BA00001 */  li      r29, 1
lbl_800C92B8:
/* 0C3D18 800C92B8 3C608013 */  lis     r3, gTRKEventQueue@ha
/* 0C3D1C 800C92BC 38632B50 */  addi    r3, r3, gTRKEventQueue@l
/* 0C3D20 800C92C0 480024A5 */  bl      TRKReleaseMutex
/* 0C3D24 800C92C4 7FA3EB78 */  mr      r3, r29
/* 0C3D28 800C92C8 83E10014 */  lwz     r31, 0x14(r1)
/* 0C3D2C 800C92CC 83C10010 */  lwz     r30, 0x10(r1)
/* 0C3D30 800C92D0 83A1000C */  lwz     r29, 0xc(r1)
/* 0C3D34 800C92D4 83810008 */  lwz     r28, 8(r1)
/* 0C3D38 800C92D8 38210018 */  addi    r1, r1, 0x18
/* 0C3D3C 800C92DC 80010004 */  lwz     r0, 4(r1)
/* 0C3D40 800C92E0 7C0803A6 */  mtlr    r0
/* 0C3D44 800C92E4 4E800020 */  blr     

glabel TRKPostEvent
/* 0C3D48 800C92E8 7C0802A6 */  mflr    r0
/* 0C3D4C 800C92EC 3C808013 */  lis     r4, gTRKEventQueue@ha
/* 0C3D50 800C92F0 90010004 */  stw     r0, 4(r1)
/* 0C3D54 800C92F4 9421FFE8 */  stwu    r1, -0x18(r1)
/* 0C3D58 800C92F8 93E10014 */  stw     r31, 0x14(r1)
/* 0C3D5C 800C92FC 3BE30000 */  addi    r31, r3, 0
/* 0C3D60 800C9300 93C10010 */  stw     r30, 0x10(r1)
/* 0C3D64 800C9304 3BC42B50 */  addi    r30, r4, gTRKEventQueue@l
/* 0C3D68 800C9308 387E0000 */  addi    r3, r30, 0
/* 0C3D6C 800C930C 93A1000C */  stw     r29, 0xc(r1)
/* 0C3D70 800C9310 93810008 */  stw     r28, 8(r1)
/* 0C3D74 800C9314 3B800000 */  li      r28, 0
/* 0C3D78 800C9318 48002445 */  bl      TRKAcquireMutex
/* 0C3D7C 800C931C 3BBE0004 */  addi    r29, r30, 4
/* 0C3D80 800C9320 807E0004 */  lwz     r3, 4(r30)
/* 0C3D84 800C9324 2C030002 */  cmpwi   r3, 2
/* 0C3D88 800C9328 4082000C */  bne     lbl_800C9334
/* 0C3D8C 800C932C 3B800100 */  li      r28, 0x100
/* 0C3D90 800C9330 48000068 */  b       lbl_800C9398
lbl_800C9334:
/* 0C3D94 800C9334 801E0008 */  lwz     r0, 8(r30)
/* 0C3D98 800C9338 389F0000 */  addi    r4, r31, 0
/* 0C3D9C 800C933C 7C001A14 */  add     r0, r0, r3
/* 0C3DA0 800C9340 7C030E70 */  srawi   r3, r0, 1
/* 0C3DA4 800C9344 7C630194 */  addze   r3, r3
/* 0C3DA8 800C9348 5463083C */  slwi    r3, r3, 1
/* 0C3DAC 800C934C 7C630010 */  subfc   r3, r3, r0
/* 0C3DB0 800C9350 1C03000C */  mulli   r0, r3, 0xc
/* 0C3DB4 800C9354 7FFE0214 */  add     r31, r30, r0
/* 0C3DB8 800C9358 387F000C */  addi    r3, r31, 0xc
/* 0C3DBC 800C935C 4BFFFEA9 */  bl      TRKCopyEvent
/* 0C3DC0 800C9360 389E0024 */  addi    r4, r30, 0x24
/* 0C3DC4 800C9364 801E0024 */  lwz     r0, 0x24(r30)
/* 0C3DC8 800C9368 901F0010 */  stw     r0, 0x10(r31)
/* 0C3DCC 800C936C 807E0024 */  lwz     r3, 0x24(r30)
/* 0C3DD0 800C9370 38030001 */  addi    r0, r3, 1
/* 0C3DD4 800C9374 901E0024 */  stw     r0, 0x24(r30)
/* 0C3DD8 800C9378 801E0024 */  lwz     r0, 0x24(r30)
/* 0C3DDC 800C937C 28000100 */  cmplwi  r0, 0x100
/* 0C3DE0 800C9380 4080000C */  bge     lbl_800C938C
/* 0C3DE4 800C9384 38000100 */  li      r0, 0x100
/* 0C3DE8 800C9388 90040000 */  stw     r0, 0(r4)
lbl_800C938C:
/* 0C3DEC 800C938C 807D0000 */  lwz     r3, 0(r29)
/* 0C3DF0 800C9390 38030001 */  addi    r0, r3, 1
/* 0C3DF4 800C9394 901D0000 */  stw     r0, 0(r29)
lbl_800C9398:
/* 0C3DF8 800C9398 3C608013 */  lis     r3, gTRKEventQueue@ha
/* 0C3DFC 800C939C 38632B50 */  addi    r3, r3, gTRKEventQueue@l
/* 0C3E00 800C93A0 480023C5 */  bl      TRKReleaseMutex
/* 0C3E04 800C93A4 7F83E378 */  mr      r3, r28
/* 0C3E08 800C93A8 83E10014 */  lwz     r31, 0x14(r1)
/* 0C3E0C 800C93AC 83C10010 */  lwz     r30, 0x10(r1)
/* 0C3E10 800C93B0 83A1000C */  lwz     r29, 0xc(r1)
/* 0C3E14 800C93B4 83810008 */  lwz     r28, 8(r1)
/* 0C3E18 800C93B8 38210018 */  addi    r1, r1, 0x18
/* 0C3E1C 800C93BC 80010004 */  lwz     r0, 4(r1)
/* 0C3E20 800C93C0 7C0803A6 */  mtlr    r0
/* 0C3E24 800C93C4 4E800020 */  blr     

glabel TRKConstructEvent
/* 0C3E28 800C93C8 98830000 */  stb     r4, 0(r3)
/* 0C3E2C 800C93CC 38800000 */  li      r4, 0
/* 0C3E30 800C93D0 3800FFFF */  li      r0, -1
/* 0C3E34 800C93D4 90830004 */  stw     r4, 4(r3)
/* 0C3E38 800C93D8 90030008 */  stw     r0, 8(r3)
/* 0C3E3C 800C93DC 4E800020 */  blr     

glabel TRKDestructEvent
/* 0C3E40 800C93E0 7C0802A6 */  mflr    r0
/* 0C3E44 800C93E4 90010004 */  stw     r0, 4(r1)
/* 0C3E48 800C93E8 9421FFF8 */  stwu    r1, -8(r1)
/* 0C3E4C 800C93EC 80630008 */  lwz     r3, 8(r3)
/* 0C3E50 800C93F0 48000319 */  bl      TRKReleaseBuffer
/* 0C3E54 800C93F4 38210008 */  addi    r1, r1, 8
/* 0C3E58 800C93F8 80010004 */  lwz     r0, 4(r1)
/* 0C3E5C 800C93FC 7C0803A6 */  mtlr    r0
/* 0C3E60 800C9400 4E800020 */  blr     


.section .bss, "wa"

.balign 4

/* 0012FBD0 80132B50 0028 */
glabel gTRKEventQueue
    .skip 40


