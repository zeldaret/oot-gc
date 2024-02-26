glabel PopReadedBuffer2
/* 00C3C8 80011968 7C0802A6 */  mflr    r0
/* 00C3CC 8001196C 3C608010 */  lis     r3, ReadedBufferQueue2@ha
/* 00C3D0 80011970 90010004 */  stw     r0, 4(r1)
/* 00C3D4 80011974 3863B200 */  addi    r3, r3, ReadedBufferQueue2@l
/* 00C3D8 80011978 38A00001 */  li      r5, 1
/* 00C3DC 8001197C 9421FFF0 */  stwu    r1, -0x10(r1)
/* 00C3E0 80011980 38810008 */  addi    r4, r1, 8
/* 00C3E4 80011984 4808DD25 */  bl      OSReceiveMessage
/* 00C3E8 80011988 80010014 */  lwz     r0, 0x14(r1)
/* 00C3EC 8001198C 80610008 */  lwz     r3, 8(r1)
/* 00C3F0 80011990 38210010 */  addi    r1, r1, 0x10
/* 00C3F4 80011994 7C0803A6 */  mtlr    r0
/* 00C3F8 80011998 4E800020 */  blr     
