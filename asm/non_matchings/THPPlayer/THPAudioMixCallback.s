glabel THPAudioMixCallback
/* 00B2E8 80010888 7C0802A6 */  mflr    r0
/* 00B2EC 8001088C 3C608010 */  lis     r3, WorkBuffer@ha
/* 00B2F0 80010890 90010004 */  stw     r0, 4(r1)
/* 00B2F4 80010894 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00B2F8 80010898 93E1000C */  stw     r31, 0xc(r1)
/* 00B2FC 8001089C 3BE396E0 */  addi    r31, r3, WorkBuffer@l
/* 00B300 800108A0 93C10008 */  stw     r30, 8(r1)
/* 00B304 800108A4 800D8954 */  lwz     r0, AudioSystem@sda21(r13)
/* 00B308 800108A8 2C000000 */  cmpwi   r0, 0
/* 00B30C 800108AC 40820070 */  bne     lbl_8001091C
/* 00B310 800108B0 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B314 800108B4 38800280 */  li      r4, 0x280
/* 00B318 800108B8 68000001 */  xori    r0, r0, 1
/* 00B31C 800108BC 900D8944 */  stw     r0, SoundBufferIndex@sda21(r13)
/* 00B320 800108C0 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B324 800108C4 1C000280 */  mulli   r0, r0, 0x280
/* 00B328 800108C8 7C7F0214 */  add     r3, r31, r0
/* 00B32C 800108CC 386300A0 */  addi    r3, r3, 0xa0
/* 00B330 800108D0 480A76F9 */  bl      AIInitDMA
/* 00B334 800108D4 4808E43D */  bl      OSEnableInterrupts
/* 00B338 800108D8 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B33C 800108DC 3BC30000 */  addi    r30, r3, 0
/* 00B340 800108E0 38800000 */  li      r4, 0
/* 00B344 800108E4 1C000280 */  mulli   r0, r0, 0x280
/* 00B348 800108E8 7C7F0214 */  add     r3, r31, r0
/* 00B34C 800108EC 38A000A0 */  li      r5, 0xa0
/* 00B350 800108F0 386300A0 */  addi    r3, r3, 0xa0
/* 00B354 800108F4 4800010D */  bl      MixAudio
/* 00B358 800108F8 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B35C 800108FC 38800280 */  li      r4, 0x280
/* 00B360 80010900 1C000280 */  mulli   r0, r0, 0x280
/* 00B364 80010904 7C7F0214 */  add     r3, r31, r0
/* 00B368 80010908 386300A0 */  addi    r3, r3, 0xa0
/* 00B36C 8001090C 4808CE71 */  bl      DCFlushRange
/* 00B370 80010910 7FC3F378 */  mr      r3, r30
/* 00B374 80010914 4808E411 */  bl      OSRestoreInterrupts
/* 00B378 80010918 480000D0 */  b       lbl_800109E8
lbl_8001091C:
/* 00B37C 8001091C 2C000001 */  cmpwi   r0, 1
/* 00B380 80010920 40820030 */  bne     lbl_80010950
/* 00B384 80010924 800D894C */  lwz     r0, LastAudioBuffer@sda21(r13)
/* 00B388 80010928 28000000 */  cmplwi  r0, 0
/* 00B38C 8001092C 41820008 */  beq     lbl_80010934
/* 00B390 80010930 900D8950 */  stw     r0, CurAudioBuffer@sda21(r13)
lbl_80010934:
/* 00B394 80010934 818D8948 */  lwz     r12, OldAIDCallback@sda21(r13)
/* 00B398 80010938 7D8803A6 */  mtlr    r12
/* 00B39C 8001093C 4E800021 */  blrl    
/* 00B3A0 80010940 480A7761 */  bl      AIGetDMAStartAddr
/* 00B3A4 80010944 3C038000 */  addis   r0, r3, 0x8000
/* 00B3A8 80010948 900D894C */  stw     r0, LastAudioBuffer@sda21(r13)
/* 00B3AC 8001094C 4800001C */  b       lbl_80010968
lbl_80010950:
/* 00B3B0 80010950 818D8948 */  lwz     r12, OldAIDCallback@sda21(r13)
/* 00B3B4 80010954 7D8803A6 */  mtlr    r12
/* 00B3B8 80010958 4E800021 */  blrl    
/* 00B3BC 8001095C 480A7745 */  bl      AIGetDMAStartAddr
/* 00B3C0 80010960 3C038000 */  addis   r0, r3, 0x8000
/* 00B3C4 80010964 900D8950 */  stw     r0, CurAudioBuffer@sda21(r13)
lbl_80010968:
/* 00B3C8 80010968 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B3CC 8001096C 38800280 */  li      r4, 0x280
/* 00B3D0 80010970 68000001 */  xori    r0, r0, 1
/* 00B3D4 80010974 900D8944 */  stw     r0, SoundBufferIndex@sda21(r13)
/* 00B3D8 80010978 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B3DC 8001097C 1C000280 */  mulli   r0, r0, 0x280
/* 00B3E0 80010980 7C7F0214 */  add     r3, r31, r0
/* 00B3E4 80010984 386300A0 */  addi    r3, r3, 0xa0
/* 00B3E8 80010988 480A7641 */  bl      AIInitDMA
/* 00B3EC 8001098C 4808E385 */  bl      OSEnableInterrupts
/* 00B3F0 80010990 800D8950 */  lwz     r0, CurAudioBuffer@sda21(r13)
/* 00B3F4 80010994 3BC30000 */  addi    r30, r3, 0
/* 00B3F8 80010998 28000000 */  cmplwi  r0, 0
/* 00B3FC 8001099C 41820010 */  beq     lbl_800109AC
/* 00B400 800109A0 7C030378 */  mr      r3, r0
/* 00B404 800109A4 38800280 */  li      r4, 0x280
/* 00B408 800109A8 4808CDA9 */  bl      DCInvalidateRange
lbl_800109AC:
/* 00B40C 800109AC 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B410 800109B0 38A000A0 */  li      r5, 0xa0
/* 00B414 800109B4 808D8950 */  lwz     r4, CurAudioBuffer@sda21(r13)
/* 00B418 800109B8 1C000280 */  mulli   r0, r0, 0x280
/* 00B41C 800109BC 7C7F0214 */  add     r3, r31, r0
/* 00B420 800109C0 386300A0 */  addi    r3, r3, 0xa0
/* 00B424 800109C4 4800003D */  bl      MixAudio
/* 00B428 800109C8 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00B42C 800109CC 38800280 */  li      r4, 0x280
/* 00B430 800109D0 1C000280 */  mulli   r0, r0, 0x280
/* 00B434 800109D4 7C7F0214 */  add     r3, r31, r0
/* 00B438 800109D8 386300A0 */  addi    r3, r3, 0xa0
/* 00B43C 800109DC 4808CDA1 */  bl      DCFlushRange
/* 00B440 800109E0 7FC3F378 */  mr      r3, r30
/* 00B444 800109E4 4808E341 */  bl      OSRestoreInterrupts
lbl_800109E8:
/* 00B448 800109E8 80010014 */  lwz     r0, 0x14(r1)
/* 00B44C 800109EC 83E1000C */  lwz     r31, 0xc(r1)
/* 00B450 800109F0 83C10008 */  lwz     r30, 8(r1)
/* 00B454 800109F4 7C0803A6 */  mtlr    r0
/* 00B458 800109F8 38210010 */  addi    r1, r1, 0x10
/* 00B45C 800109FC 4E800020 */  blr     
