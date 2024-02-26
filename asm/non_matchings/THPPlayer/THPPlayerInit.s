glabel THPPlayerInit
/* 00A2F0 8000F890 7C0802A6 */  mflr    r0
/* 00A2F4 8000F894 3C808010 */  lis     r4, WorkBuffer@ha
/* 00A2F8 8000F898 90010004 */  stw     r0, 4(r1)
/* 00A2FC 8000F89C 38A001D0 */  li      r5, 0x1d0
/* 00A300 8000F8A0 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00A304 8000F8A4 93E10014 */  stw     r31, 0x14(r1)
/* 00A308 8000F8A8 3BE496E0 */  addi    r31, r4, WorkBuffer@l
/* 00A30C 8000F8AC 38800000 */  li      r4, 0
/* 00A310 8000F8B0 93C10010 */  stw     r30, 0x10(r1)
/* 00A314 8000F8B4 3BC30000 */  addi    r30, r3, 0
/* 00A318 8000F8B8 387F05A0 */  addi    r3, r31, 0x5a0
/* 00A31C 8000F8BC 4BFF5B15 */  bl      memset
/* 00A320 8000F8C0 4808E099 */  bl      LCEnable
/* 00A324 8000F8C4 387F0060 */  addi    r3, r31, 0x60
/* 00A328 8000F8C8 389F0080 */  addi    r4, r31, 0x80
/* 00A32C 8000F8CC 38A00003 */  li      r5, 3
/* 00A330 8000F8D0 4808FCB1 */  bl      OSInitMessageQueue
/* 00A334 8000F8D4 480B90B9 */  bl      THPInit
/* 00A338 8000F8D8 2C030000 */  cmpwi   r3, 0
/* 00A33C 8000F8DC 4082000C */  bne     lbl_8000F8E8
/* 00A340 8000F8E0 38600000 */  li      r3, 0
/* 00A344 8000F8E4 480000CC */  b       lbl_8000F9B0
lbl_8000F8E8:
/* 00A348 8000F8E8 4808F415 */  bl      OSDisableInterrupts
/* 00A34C 8000F8EC 38A00000 */  li      r5, 0
/* 00A350 8000F8F0 93CD8954 */  stw     r30, AudioSystem@sda21(r13)
/* 00A354 8000F8F4 3C808001 */  lis     r4, THPAudioMixCallback@ha
/* 00A358 8000F8F8 90AD8944 */  stw     r5, SoundBufferIndex@sda21(r13)
/* 00A35C 8000F8FC 38040888 */  addi    r0, r4, THPAudioMixCallback@l
/* 00A360 8000F900 3BC30000 */  addi    r30, r3, 0
/* 00A364 8000F904 90AD894C */  stw     r5, LastAudioBuffer@sda21(r13)
/* 00A368 8000F908 7C030378 */  mr      r3, r0
/* 00A36C 8000F90C 90AD8950 */  stw     r5, CurAudioBuffer@sda21(r13)
/* 00A370 8000F910 480A8675 */  bl      AIRegisterDMACallback
/* 00A374 8000F914 906D8948 */  stw     r3, OldAIDCallback@sda21(r13)
/* 00A378 8000F918 800D8948 */  lwz     r0, OldAIDCallback@sda21(r13)
/* 00A37C 8000F91C 28000000 */  cmplwi  r0, 0
/* 00A380 8000F920 40820038 */  bne     lbl_8000F958
/* 00A384 8000F924 800D8954 */  lwz     r0, AudioSystem@sda21(r13)
/* 00A388 8000F928 2C000000 */  cmpwi   r0, 0
/* 00A38C 8000F92C 4182002C */  beq     lbl_8000F958
/* 00A390 8000F930 38600000 */  li      r3, 0
/* 00A394 8000F934 480A8651 */  bl      AIRegisterDMACallback
/* 00A398 8000F938 7FC3F378 */  mr      r3, r30
/* 00A39C 8000F93C 4808F3E9 */  bl      OSRestoreInterrupts
/* 00A3A0 8000F940 3C60800F */  lis     r3, D_800EA2E8@ha
/* 00A3A4 8000F944 4CC63182 */  crclr   6
/* 00A3A8 8000F948 3863A2E8 */  addi    r3, r3, D_800EA2E8@l
/* 00A3AC 8000F94C 4808ECAD */  bl      OSReport
/* 00A3B0 8000F950 38600000 */  li      r3, 0
/* 00A3B4 8000F954 4800005C */  b       lbl_8000F9B0
lbl_8000F958:
/* 00A3B8 8000F958 7FC3F378 */  mr      r3, r30
/* 00A3BC 8000F95C 4808F3C9 */  bl      OSRestoreInterrupts
/* 00A3C0 8000F960 800D8954 */  lwz     r0, AudioSystem@sda21(r13)
/* 00A3C4 8000F964 2C000000 */  cmpwi   r0, 0
/* 00A3C8 8000F968 4082003C */  bne     lbl_8000F9A4
/* 00A3CC 8000F96C 387F00A0 */  addi    r3, r31, 0xa0
/* 00A3D0 8000F970 38800000 */  li      r4, 0
/* 00A3D4 8000F974 38A00500 */  li      r5, 0x500
/* 00A3D8 8000F978 4BFF5A59 */  bl      memset
/* 00A3DC 8000F97C 387F00A0 */  addi    r3, r31, 0xa0
/* 00A3E0 8000F980 38800500 */  li      r4, 0x500
/* 00A3E4 8000F984 4808DDF9 */  bl      DCFlushRange
/* 00A3E8 8000F988 800D8944 */  lwz     r0, SoundBufferIndex@sda21(r13)
/* 00A3EC 8000F98C 38800280 */  li      r4, 0x280
/* 00A3F0 8000F990 1C000280 */  mulli   r0, r0, 0x280
/* 00A3F4 8000F994 7C7F0214 */  add     r3, r31, r0
/* 00A3F8 8000F998 386300A0 */  addi    r3, r3, 0xa0
/* 00A3FC 8000F99C 480A862D */  bl      AIInitDMA
/* 00A400 8000F9A0 480A86C1 */  bl      AIStartDMA
lbl_8000F9A4:
/* 00A404 8000F9A4 38000001 */  li      r0, 1
/* 00A408 8000F9A8 900D8938 */  stw     r0, Initialized@sda21(r13)
/* 00A40C 8000F9AC 38600001 */  li      r3, 1
lbl_8000F9B0:
/* 00A410 8000F9B0 8001001C */  lwz     r0, 0x1c(r1)
/* 00A414 8000F9B4 83E10014 */  lwz     r31, 0x14(r1)
/* 00A418 8000F9B8 83C10010 */  lwz     r30, 0x10(r1)
/* 00A41C 8000F9BC 7C0803A6 */  mtlr    r0
/* 00A420 8000F9C0 38210018 */  addi    r1, r1, 0x18
/* 00A424 8000F9C4 4E800020 */  blr     
