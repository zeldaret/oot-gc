# sram.c
.include "macros.inc"

.section .text, "ax"

.balign 4

glabel sramEvent
/* 088B98 8008E138 7C0802A6 */  mflr    r0
/* 088B9C 8008E13C 2C040003 */  cmpwi   r4, 3
/* 088BA0 8008E140 90010004 */  stw     r0, 4(r1)
/* 088BA4 8008E144 9421FFE0 */  stwu    r1, -0x20(r1)
/* 088BA8 8008E148 93E1001C */  stw     r31, 0x1c(r1)
/* 088BAC 8008E14C 3BE50000 */  addi    r31, r5, 0
/* 088BB0 8008E150 93C10018 */  stw     r30, 0x18(r1)
/* 088BB4 8008E154 3BC30000 */  addi    r30, r3, 0
/* 088BB8 8008E158 418200C4 */  beq     lbl_8008E21C
/* 088BBC 8008E15C 40800018 */  bge     lbl_8008E174
/* 088BC0 8008E160 2C040002 */  cmpwi   r4, 2
/* 088BC4 8008E164 40800028 */  bge     lbl_8008E18C
/* 088BC8 8008E168 2C040000 */  cmpwi   r4, 0
/* 088BCC 8008E16C 408000B0 */  bge     lbl_8008E21C
/* 088BD0 8008E170 480000A4 */  b       lbl_8008E214
lbl_8008E174:
/* 088BD4 8008E174 2C041003 */  cmpwi   r4, 0x1003
/* 088BD8 8008E178 418200A4 */  beq     lbl_8008E21C
/* 088BDC 8008E17C 40800098 */  bge     lbl_8008E214
/* 088BE0 8008E180 2C041002 */  cmpwi   r4, 0x1002
/* 088BE4 8008E184 40800010 */  bge     lbl_8008E194
/* 088BE8 8008E188 4800008C */  b       lbl_8008E214
lbl_8008E18C:
/* 088BEC 8008E18C 93FE0000 */  stw     r31, 0(r30)
/* 088BF0 8008E190 4800008C */  b       lbl_8008E21C
lbl_8008E194:
/* 088BF4 8008E194 807E0000 */  lwz     r3, 0(r30)
/* 088BF8 8008E198 3CA08009 */  lis     r5, sramPut8@ha
/* 088BFC 8008E19C 3CC08009 */  lis     r6, sramPut16@ha
/* 088C00 8008E1A0 3CE08009 */  lis     r7, sramPut32@ha
/* 088C04 8008E1A4 80630024 */  lwz     r3, 0x24(r3)
/* 088C08 8008E1A8 3C808009 */  lis     r4, sramPut64@ha
/* 088C0C 8008E1AC 3904E2F8 */  addi    r8, r4, sramPut64@l
/* 088C10 8008E1B0 38A5E388 */  addi    r5, r5, sramPut8@l
/* 088C14 8008E1B4 38C6E358 */  addi    r6, r6, sramPut16@l
/* 088C18 8008E1B8 38E7E328 */  addi    r7, r7, sramPut32@l
/* 088C1C 8008E1BC 389F0000 */  addi    r4, r31, 0
/* 088C20 8008E1C0 4BFA6E79 */  bl      cpuSetDevicePut
/* 088C24 8008E1C4 2C030000 */  cmpwi   r3, 0
/* 088C28 8008E1C8 4082000C */  bne     lbl_8008E1D4
/* 088C2C 8008E1CC 38600000 */  li      r3, 0
/* 088C30 8008E1D0 48000050 */  b       lbl_8008E220
lbl_8008E1D4:
/* 088C34 8008E1D4 807E0000 */  lwz     r3, 0(r30)
/* 088C38 8008E1D8 3CA08009 */  lis     r5, sramGet8@ha
/* 088C3C 8008E1DC 3CC08009 */  lis     r6, sramGet16@ha
/* 088C40 8008E1E0 3CE08009 */  lis     r7, sramGet32@ha
/* 088C44 8008E1E4 80630024 */  lwz     r3, 0x24(r3)
/* 088C48 8008E1E8 3C808009 */  lis     r4, sramGet64@ha
/* 088C4C 8008E1EC 3904E238 */  addi    r8, r4, sramGet64@l
/* 088C50 8008E1F0 38A5E2C8 */  addi    r5, r5, sramGet8@l
/* 088C54 8008E1F4 38C6E298 */  addi    r6, r6, sramGet16@l
/* 088C58 8008E1F8 38E7E268 */  addi    r7, r7, sramGet32@l
/* 088C5C 8008E1FC 389F0000 */  addi    r4, r31, 0
/* 088C60 8008E200 4BFA6E51 */  bl      cpuSetDeviceGet
/* 088C64 8008E204 2C030000 */  cmpwi   r3, 0
/* 088C68 8008E208 40820014 */  bne     lbl_8008E21C
/* 088C6C 8008E20C 38600000 */  li      r3, 0
/* 088C70 8008E210 48000010 */  b       lbl_8008E220
lbl_8008E214:
/* 088C74 8008E214 38600000 */  li      r3, 0
/* 088C78 8008E218 48000008 */  b       lbl_8008E220
lbl_8008E21C:
/* 088C7C 8008E21C 38600001 */  li      r3, 1
lbl_8008E220:
/* 088C80 8008E220 80010024 */  lwz     r0, 0x24(r1)
/* 088C84 8008E224 83E1001C */  lwz     r31, 0x1c(r1)
/* 088C88 8008E228 83C10018 */  lwz     r30, 0x18(r1)
/* 088C8C 8008E22C 7C0803A6 */  mtlr    r0
/* 088C90 8008E230 38210020 */  addi    r1, r1, 0x20
/* 088C94 8008E234 4E800020 */  blr     

sramGet64:
/* 088C98 8008E238 7C0802A6 */  mflr    r0
/* 088C9C 8008E23C 5483047E */  clrlwi  r3, r4, 0x11
/* 088CA0 8008E240 90010004 */  stw     r0, 4(r1)
/* 088CA4 8008E244 38850000 */  addi    r4, r5, 0
/* 088CA8 8008E248 38A00008 */  li      r5, 8
/* 088CAC 8008E24C 9421FFF8 */  stwu    r1, -8(r1)
/* 088CB0 8008E250 4BF7AC59 */  bl      simulatorReadSRAM
/* 088CB4 8008E254 8001000C */  lwz     r0, 0xc(r1)
/* 088CB8 8008E258 38600001 */  li      r3, 1
/* 088CBC 8008E25C 38210008 */  addi    r1, r1, 8
/* 088CC0 8008E260 7C0803A6 */  mtlr    r0
/* 088CC4 8008E264 4E800020 */  blr     

sramGet32:
/* 088CC8 8008E268 7C0802A6 */  mflr    r0
/* 088CCC 8008E26C 5483047E */  clrlwi  r3, r4, 0x11
/* 088CD0 8008E270 90010004 */  stw     r0, 4(r1)
/* 088CD4 8008E274 38850000 */  addi    r4, r5, 0
/* 088CD8 8008E278 38A00004 */  li      r5, 4
/* 088CDC 8008E27C 9421FFF8 */  stwu    r1, -8(r1)
/* 088CE0 8008E280 4BF7AC29 */  bl      simulatorReadSRAM
/* 088CE4 8008E284 8001000C */  lwz     r0, 0xc(r1)
/* 088CE8 8008E288 38600001 */  li      r3, 1
/* 088CEC 8008E28C 38210008 */  addi    r1, r1, 8
/* 088CF0 8008E290 7C0803A6 */  mtlr    r0
/* 088CF4 8008E294 4E800020 */  blr     

sramGet16:
/* 088CF8 8008E298 7C0802A6 */  mflr    r0
/* 088CFC 8008E29C 5483047E */  clrlwi  r3, r4, 0x11
/* 088D00 8008E2A0 90010004 */  stw     r0, 4(r1)
/* 088D04 8008E2A4 38850000 */  addi    r4, r5, 0
/* 088D08 8008E2A8 38A00002 */  li      r5, 2
/* 088D0C 8008E2AC 9421FFF8 */  stwu    r1, -8(r1)
/* 088D10 8008E2B0 4BF7ABF9 */  bl      simulatorReadSRAM
/* 088D14 8008E2B4 8001000C */  lwz     r0, 0xc(r1)
/* 088D18 8008E2B8 38600001 */  li      r3, 1
/* 088D1C 8008E2BC 38210008 */  addi    r1, r1, 8
/* 088D20 8008E2C0 7C0803A6 */  mtlr    r0
/* 088D24 8008E2C4 4E800020 */  blr     

sramGet8:
/* 088D28 8008E2C8 7C0802A6 */  mflr    r0
/* 088D2C 8008E2CC 5483047E */  clrlwi  r3, r4, 0x11
/* 088D30 8008E2D0 90010004 */  stw     r0, 4(r1)
/* 088D34 8008E2D4 38850000 */  addi    r4, r5, 0
/* 088D38 8008E2D8 38A00001 */  li      r5, 1
/* 088D3C 8008E2DC 9421FFF8 */  stwu    r1, -8(r1)
/* 088D40 8008E2E0 4BF7ABC9 */  bl      simulatorReadSRAM
/* 088D44 8008E2E4 8001000C */  lwz     r0, 0xc(r1)
/* 088D48 8008E2E8 38600001 */  li      r3, 1
/* 088D4C 8008E2EC 38210008 */  addi    r1, r1, 8
/* 088D50 8008E2F0 7C0803A6 */  mtlr    r0
/* 088D54 8008E2F4 4E800020 */  blr     

sramPut64:
/* 088D58 8008E2F8 7C0802A6 */  mflr    r0
/* 088D5C 8008E2FC 5483047E */  clrlwi  r3, r4, 0x11
/* 088D60 8008E300 90010004 */  stw     r0, 4(r1)
/* 088D64 8008E304 38850000 */  addi    r4, r5, 0
/* 088D68 8008E308 38A00008 */  li      r5, 8
/* 088D6C 8008E30C 9421FFF8 */  stwu    r1, -8(r1)
/* 088D70 8008E310 4BF7AB65 */  bl      simulatorWriteSRAM
/* 088D74 8008E314 8001000C */  lwz     r0, 0xc(r1)
/* 088D78 8008E318 38600001 */  li      r3, 1
/* 088D7C 8008E31C 38210008 */  addi    r1, r1, 8
/* 088D80 8008E320 7C0803A6 */  mtlr    r0
/* 088D84 8008E324 4E800020 */  blr     

sramPut32:
/* 088D88 8008E328 7C0802A6 */  mflr    r0
/* 088D8C 8008E32C 5483047E */  clrlwi  r3, r4, 0x11
/* 088D90 8008E330 90010004 */  stw     r0, 4(r1)
/* 088D94 8008E334 38850000 */  addi    r4, r5, 0
/* 088D98 8008E338 38A00004 */  li      r5, 4
/* 088D9C 8008E33C 9421FFF8 */  stwu    r1, -8(r1)
/* 088DA0 8008E340 4BF7AB35 */  bl      simulatorWriteSRAM
/* 088DA4 8008E344 8001000C */  lwz     r0, 0xc(r1)
/* 088DA8 8008E348 38600001 */  li      r3, 1
/* 088DAC 8008E34C 38210008 */  addi    r1, r1, 8
/* 088DB0 8008E350 7C0803A6 */  mtlr    r0
/* 088DB4 8008E354 4E800020 */  blr     

sramPut16:
/* 088DB8 8008E358 7C0802A6 */  mflr    r0
/* 088DBC 8008E35C 5483047E */  clrlwi  r3, r4, 0x11
/* 088DC0 8008E360 90010004 */  stw     r0, 4(r1)
/* 088DC4 8008E364 38850000 */  addi    r4, r5, 0
/* 088DC8 8008E368 38A00002 */  li      r5, 2
/* 088DCC 8008E36C 9421FFF8 */  stwu    r1, -8(r1)
/* 088DD0 8008E370 4BF7AB05 */  bl      simulatorWriteSRAM
/* 088DD4 8008E374 8001000C */  lwz     r0, 0xc(r1)
/* 088DD8 8008E378 38600001 */  li      r3, 1
/* 088DDC 8008E37C 38210008 */  addi    r1, r1, 8
/* 088DE0 8008E380 7C0803A6 */  mtlr    r0
/* 088DE4 8008E384 4E800020 */  blr     

sramPut8:
/* 088DE8 8008E388 7C0802A6 */  mflr    r0
/* 088DEC 8008E38C 5483047E */  clrlwi  r3, r4, 0x11
/* 088DF0 8008E390 90010004 */  stw     r0, 4(r1)
/* 088DF4 8008E394 38850000 */  addi    r4, r5, 0
/* 088DF8 8008E398 38A00001 */  li      r5, 1
/* 088DFC 8008E39C 9421FFF8 */  stwu    r1, -8(r1)
/* 088E00 8008E3A0 4BF7AAD5 */  bl      simulatorWriteSRAM
/* 088E04 8008E3A4 8001000C */  lwz     r0, 0xc(r1)
/* 088E08 8008E3A8 38600001 */  li      r3, 1
/* 088E0C 8008E3AC 38210008 */  addi    r1, r1, 8
/* 088E10 8008E3B0 7C0803A6 */  mtlr    r0
/* 088E14 8008E3B4 4E800020 */  blr     

glabel sramTransferSRAM
/* 088E18 8008E3B8 7C0802A6 */  mflr    r0
/* 088E1C 8008E3BC 90010004 */  stw     r0, 4(r1)
/* 088E20 8008E3C0 9421FFD8 */  stwu    r1, -0x28(r1)
/* 088E24 8008E3C4 93E10024 */  stw     r31, 0x24(r1)
/* 088E28 8008E3C8 7CBF2B78 */  mr      r31, r5
/* 088E2C 8008E3CC 38A40000 */  addi    r5, r4, 0
/* 088E30 8008E3D0 90C10014 */  stw     r6, 0x14(r1)
/* 088E34 8008E3D4 38810018 */  addi    r4, r1, 0x18
/* 088E38 8008E3D8 38C10014 */  addi    r6, r1, 0x14
/* 088E3C 8008E3DC 80630000 */  lwz     r3, 0(r3)
/* 088E40 8008E3E0 8063002C */  lwz     r3, 0x2c(r3)
/* 088E44 8008E3E4 4BFDECBD */  bl      ramGetBuffer
/* 088E48 8008E3E8 2C030000 */  cmpwi   r3, 0
/* 088E4C 8008E3EC 4082000C */  bne     lbl_8008E3F8
/* 088E50 8008E3F0 38600000 */  li      r3, 0
/* 088E54 8008E3F4 48000028 */  b       lbl_8008E41C
lbl_8008E3F8:
/* 088E58 8008E3F8 80810018 */  lwz     r4, 0x18(r1)
/* 088E5C 8008E3FC 57E3047E */  clrlwi  r3, r31, 0x11
/* 088E60 8008E400 80A10014 */  lwz     r5, 0x14(r1)
/* 088E64 8008E404 4BF7AA71 */  bl      simulatorWriteSRAM
/* 088E68 8008E408 2C030000 */  cmpwi   r3, 0
/* 088E6C 8008E40C 4082000C */  bne     lbl_8008E418
/* 088E70 8008E410 38600000 */  li      r3, 0
/* 088E74 8008E414 48000008 */  b       lbl_8008E41C
lbl_8008E418:
/* 088E78 8008E418 38600001 */  li      r3, 1
lbl_8008E41C:
/* 088E7C 8008E41C 8001002C */  lwz     r0, 0x2c(r1)
/* 088E80 8008E420 83E10024 */  lwz     r31, 0x24(r1)
/* 088E84 8008E424 38210028 */  addi    r1, r1, 0x28
/* 088E88 8008E428 7C0803A6 */  mtlr    r0
/* 088E8C 8008E42C 4E800020 */  blr     

glabel sramCopySRAM
/* 088E90 8008E430 7C0802A6 */  mflr    r0
/* 088E94 8008E434 90010004 */  stw     r0, 4(r1)
/* 088E98 8008E438 9421FFD8 */  stwu    r1, -0x28(r1)
/* 088E9C 8008E43C 93E10024 */  stw     r31, 0x24(r1)
/* 088EA0 8008E440 7CBF2B78 */  mr      r31, r5
/* 088EA4 8008E444 38A40000 */  addi    r5, r4, 0
/* 088EA8 8008E448 90C10014 */  stw     r6, 0x14(r1)
/* 088EAC 8008E44C 38810018 */  addi    r4, r1, 0x18
/* 088EB0 8008E450 38C10014 */  addi    r6, r1, 0x14
/* 088EB4 8008E454 80630000 */  lwz     r3, 0(r3)
/* 088EB8 8008E458 8063002C */  lwz     r3, 0x2c(r3)
/* 088EBC 8008E45C 4BFDEC45 */  bl      ramGetBuffer
/* 088EC0 8008E460 2C030000 */  cmpwi   r3, 0
/* 088EC4 8008E464 4082000C */  bne     lbl_8008E470
/* 088EC8 8008E468 38600000 */  li      r3, 0
/* 088ECC 8008E46C 48000028 */  b       lbl_8008E494
lbl_8008E470:
/* 088ED0 8008E470 80810018 */  lwz     r4, 0x18(r1)
/* 088ED4 8008E474 57E3047E */  clrlwi  r3, r31, 0x11
/* 088ED8 8008E478 80A10014 */  lwz     r5, 0x14(r1)
/* 088EDC 8008E47C 4BF7AA2D */  bl      simulatorReadSRAM
/* 088EE0 8008E480 2C030000 */  cmpwi   r3, 0
/* 088EE4 8008E484 4082000C */  bne     lbl_8008E490
/* 088EE8 8008E488 38600000 */  li      r3, 0
/* 088EEC 8008E48C 48000008 */  b       lbl_8008E494
lbl_8008E490:
/* 088EF0 8008E490 38600001 */  li      r3, 1
lbl_8008E494:
/* 088EF4 8008E494 8001002C */  lwz     r0, 0x2c(r1)
/* 088EF8 8008E498 83E10024 */  lwz     r31, 0x24(r1)
/* 088EFC 8008E49C 38210028 */  addi    r1, r1, 0x28
/* 088F00 8008E4A0 7C0803A6 */  mtlr    r0
/* 088F04 8008E4A4 4E800020 */  blr     

.section .data, "wa"

.balign 8

/* 000EB7E8 800EE768 0010 */
glabel gClassSram
    .long D_80135300, 0x00000004, 0x00000000, sramEvent

.section .sdata, "wa"

.balign 8

/* 000F1580 80135300 0005 */
D_80135300:
    .asciz "SRAM"
    .balign 4
