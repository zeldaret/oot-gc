glabel AudioDecoder
/* 00B910 80010EB0 7C0802A6 */  mflr    r0
/* 00B914 80010EB4 90010004 */  stw     r0, 4(r1)
/* 00B918 80010EB8 9421FFE8 */  stwu    r1, -0x18(r1)
/* 00B91C 80010EBC 93E10014 */  stw     r31, 0x14(r1)
lbl_80010EC0:
/* 00B920 80010EC0 48000B0D */  bl      PopReadedBuffer
/* 00B924 80010EC4 7C7F1B78 */  mr      r31, r3
/* 00B928 80010EC8 480000C1 */  bl      AudioDecode
/* 00B92C 80010ECC 7FE3FB78 */  mr      r3, r31
/* 00B930 80010ED0 48000A69 */  bl      PushReadedBuffer2
/* 00B934 80010ED4 4BFFFFEC */  b       lbl_80010EC0
