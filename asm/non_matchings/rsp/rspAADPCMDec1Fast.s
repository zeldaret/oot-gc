glabel rspAADPCMDec1Fast
/* 085240 8008A7E0 7C0802A6 */  mflr    r0
/* 085244 8008A7E4 90010004 */  stw     r0, 4(r1)
/* 085248 8008A7E8 548056BA */  rlwinm  r0, r4, 0xa, 0x1a, 0x1d
/* 08524C 8008A7EC 9421FF68 */  stwu    r1, -0x98(r1)
/* 085250 8008A7F0 BEA1006C */  stmw    r21, 0x6c(r1)
/* 085254 8008A7F4 3B830000 */  addi    r28, r3, 0
/* 085258 8008A7F8 7CDC0214 */  add     r6, r28, r0
/* 08525C 8008A7FC 5480023E */  clrlwi  r0, r4, 8
/* 085260 8008A800 54B5863E */  rlwinm  r21, r5, 0x10, 0x18, 0x1f
/* 085264 8008A804 806338E8 */  lwz     r3, 0x38e8(r3)
/* 085268 8008A808 80863254 */  lwz     r4, 0x3254(r6)
/* 08526C 8008A80C 80FC3294 */  lwz     r7, 0x3294(r28)
/* 085270 8008A810 A0DC334C */  lhz     r6, 0x334c(r28)
/* 085274 8008A814 7CA40214 */  add     r5, r4, r0
/* 085278 8008A818 A3DC334E */  lhz     r30, 0x334e(r28)
/* 08527C 8008A81C 38810060 */  addi    r4, r1, 0x60
/* 085280 8008A820 7FE73214 */  add     r31, r7, r6
/* 085284 8008A824 A3BC3344 */  lhz     r29, 0x3344(r28)
/* 085288 8008A828 38C00000 */  li      r6, 0
/* 08528C 8008A82C 8063002C */  lwz     r3, 0x2c(r3)
/* 085290 8008A830 4BFE2871 */  bl      ramGetBuffer
/* 085294 8008A834 2C030000 */  cmpwi   r3, 0
/* 085298 8008A838 4082000C */  bne     lbl_8008A844
/* 08529C 8008A83C 38600000 */  li      r3, 0
/* 0852A0 8008A840 4800082C */  b       lbl_8008B06C
lbl_8008A844:
/* 0852A4 8008A844 56A007FF */  clrlwi. r0, r21, 0x1f
/* 0852A8 8008A848 40820184 */  bne     lbl_8008A9CC
/* 0852AC 8008A84C 80610060 */  lwz     r3, 0x60(r1)
/* 0852B0 8008A850 56A007BD */  rlwinm. r0, r21, 0, 0x1e, 0x1e
/* 0852B4 8008A854 9061004C */  stw     r3, 0x4c(r1)
/* 0852B8 8008A858 4182002C */  beq     lbl_8008A884
/* 0852BC 8008A85C 807C38E8 */  lwz     r3, 0x38e8(r28)
/* 0852C0 8008A860 3881004C */  addi    r4, r1, 0x4c
/* 0852C4 8008A864 80BC3354 */  lwz     r5, 0x3354(r28)
/* 0852C8 8008A868 38C00000 */  li      r6, 0
/* 0852CC 8008A86C 8063002C */  lwz     r3, 0x2c(r3)
/* 0852D0 8008A870 4BFE2831 */  bl      ramGetBuffer
/* 0852D4 8008A874 2C030000 */  cmpwi   r3, 0
/* 0852D8 8008A878 4082000C */  bne     lbl_8008A884
/* 0852DC 8008A87C 38600000 */  li      r3, 0
/* 0852E0 8008A880 480007EC */  b       lbl_8008B06C
lbl_8008A884:
/* 0852E4 8008A884 80A1004C */  lwz     r5, 0x4c(r1)
/* 0852E8 8008A888 3B1E0001 */  addi    r24, r30, 1
/* 0852EC 8008A88C 397E0003 */  addi    r11, r30, 3
/* 0852F0 8008A890 809C3294 */  lwz     r4, 0x3294(r28)
/* 0852F4 8008A894 A8C50000 */  lha     r6, 0(r5)
/* 0852F8 8008A898 57C3083C */  slwi    r3, r30, 1
/* 0852FC 8008A89C 7CC41B2E */  sthx    r6, r4, r3
/* 085300 8008A8A0 393E0004 */  addi    r9, r30, 4
/* 085304 8008A8A4 391E0005 */  addi    r8, r30, 5
/* 085308 8008A8A8 A8C50002 */  lha     r6, 2(r5)
/* 08530C 8008A8AC 5536083C */  slwi    r22, r9, 1
/* 085310 8008A8B0 807C3294 */  lwz     r3, 0x3294(r28)
/* 085314 8008A8B4 5700083C */  slwi    r0, r24, 1
/* 085318 8008A8B8 3ABE0002 */  addi    r21, r30, 2
/* 08531C 8008A8BC 7CC3032E */  sthx    r6, r3, r0
/* 085320 8008A8C0 550C083C */  slwi    r12, r8, 1
/* 085324 8008A8C4 393E0006 */  addi    r9, r30, 6
/* 085328 8008A8C8 A8050004 */  lha     r0, 4(r5)
/* 08532C 8008A8CC 56B8083C */  slwi    r24, r21, 1
/* 085330 8008A8D0 807C3294 */  lwz     r3, 0x3294(r28)
/* 085334 8008A8D4 391E0007 */  addi    r8, r30, 7
/* 085338 8008A8D8 389E0008 */  addi    r4, r30, 8
/* 08533C 8008A8DC 7C03C32E */  sthx    r0, r3, r24
/* 085340 8008A8E0 5577083C */  slwi    r23, r11, 1
/* 085344 8008A8E4 552A083C */  slwi    r10, r9, 1
/* 085348 8008A8E8 A8050006 */  lha     r0, 6(r5)
/* 08534C 8008A8EC 5507083C */  slwi    r7, r8, 1
/* 085350 8008A8F0 807C3294 */  lwz     r3, 0x3294(r28)
/* 085354 8008A8F4 3B040001 */  addi    r24, r4, 1
/* 085358 8008A8F8 3AA40002 */  addi    r21, r4, 2
/* 08535C 8008A8FC 7C03BB2E */  sthx    r0, r3, r23
/* 085360 8008A900 39640003 */  addi    r11, r4, 3
/* 085364 8008A904 5700083C */  slwi    r0, r24, 1
/* 085368 8008A908 A9250008 */  lha     r9, 8(r5)
/* 08536C 8008A90C 56B8083C */  slwi    r24, r21, 1
/* 085370 8008A910 811C3294 */  lwz     r8, 0x3294(r28)
/* 085374 8008A914 5577083C */  slwi    r23, r11, 1
/* 085378 8008A918 5483083C */  slwi    r3, r4, 1
/* 08537C 8008A91C 7D28B32E */  sthx    r9, r8, r22
/* 085380 8008A920 39240004 */  addi    r9, r4, 4
/* 085384 8008A924 39040005 */  addi    r8, r4, 5
/* 085388 8008A928 5536083C */  slwi    r22, r9, 1
/* 08538C 8008A92C AAA5000A */  lha     r21, 0xa(r5)
/* 085390 8008A930 817C3294 */  lwz     r11, 0x3294(r28)
/* 085394 8008A934 39240006 */  addi    r9, r4, 6
/* 085398 8008A938 38C50010 */  addi    r6, r5, 0x10
/* 08539C 8008A93C 7EAB632E */  sthx    r21, r11, r12
/* 0853A0 8008A940 550C083C */  slwi    r12, r8, 1
/* 0853A4 8008A944 39040007 */  addi    r8, r4, 7
/* 0853A8 8008A948 A965000C */  lha     r11, 0xc(r5)
/* 0853AC 8008A94C 809C3294 */  lwz     r4, 0x3294(r28)
/* 0853B0 8008A950 7D64532E */  sthx    r11, r4, r10
/* 0853B4 8008A954 552A083C */  slwi    r10, r9, 1
/* 0853B8 8008A958 A925000E */  lha     r9, 0xe(r5)
/* 0853BC 8008A95C 809C3294 */  lwz     r4, 0x3294(r28)
/* 0853C0 8008A960 7D243B2E */  sthx    r9, r4, r7
/* 0853C4 8008A964 5507083C */  slwi    r7, r8, 1
/* 0853C8 8008A968 A8C60000 */  lha     r6, 0(r6)
/* 0853CC 8008A96C 809C3294 */  lwz     r4, 0x3294(r28)
/* 0853D0 8008A970 7CC41B2E */  sthx    r6, r4, r3
/* 0853D4 8008A974 A8C50012 */  lha     r6, 0x12(r5)
/* 0853D8 8008A978 807C3294 */  lwz     r3, 0x3294(r28)
/* 0853DC 8008A97C 7CC3032E */  sthx    r6, r3, r0
/* 0853E0 8008A980 A8050014 */  lha     r0, 0x14(r5)
/* 0853E4 8008A984 807C3294 */  lwz     r3, 0x3294(r28)
/* 0853E8 8008A988 7C03C32E */  sthx    r0, r3, r24
/* 0853EC 8008A98C A8050016 */  lha     r0, 0x16(r5)
/* 0853F0 8008A990 807C3294 */  lwz     r3, 0x3294(r28)
/* 0853F4 8008A994 7C03BB2E */  sthx    r0, r3, r23
/* 0853F8 8008A998 A9250018 */  lha     r9, 0x18(r5)
/* 0853FC 8008A99C 811C3294 */  lwz     r8, 0x3294(r28)
/* 085400 8008A9A0 7D28B32E */  sthx    r9, r8, r22
/* 085404 8008A9A4 AAA5001A */  lha     r21, 0x1a(r5)
/* 085408 8008A9A8 817C3294 */  lwz     r11, 0x3294(r28)
/* 08540C 8008A9AC 7EAB632E */  sthx    r21, r11, r12
/* 085410 8008A9B0 A965001C */  lha     r11, 0x1c(r5)
/* 085414 8008A9B4 809C3294 */  lwz     r4, 0x3294(r28)
/* 085418 8008A9B8 7D64532E */  sthx    r11, r4, r10
/* 08541C 8008A9BC A925001E */  lha     r9, 0x1e(r5)
/* 085420 8008A9C0 809C3294 */  lwz     r4, 0x3294(r28)
/* 085424 8008A9C4 7D243B2E */  sthx    r9, r4, r7
/* 085428 8008A9C8 48000104 */  b       lbl_8008AACC
lbl_8008A9CC:
/* 08542C 8008A9CC 807C3294 */  lwz     r3, 0x3294(r28)
/* 085430 8008A9D0 38DE0001 */  addi    r6, r30, 1
/* 085434 8008A9D4 57D5083C */  slwi    r21, r30, 1
/* 085438 8008A9D8 38000000 */  li      r0, 0
/* 08543C 8008A9DC 7C03AB2E */  sthx    r0, r3, r21
/* 085440 8008A9E0 397E0002 */  addi    r11, r30, 2
/* 085444 8008A9E4 395E0003 */  addi    r10, r30, 3
/* 085448 8008A9E8 80BC3294 */  lwz     r5, 0x3294(r28)
/* 08544C 8008A9EC 54CC083C */  slwi    r12, r6, 1
/* 085450 8008A9F0 387E0008 */  addi    r3, r30, 8
/* 085454 8008A9F4 7C05632E */  sthx    r0, r5, r12
/* 085458 8008A9F8 556B083C */  slwi    r11, r11, 1
/* 08545C 8008A9FC 554A083C */  slwi    r10, r10, 1
/* 085460 8008AA00 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085464 8008AA04 393E0004 */  addi    r9, r30, 4
/* 085468 8008AA08 5529083C */  slwi    r9, r9, 1
/* 08546C 8008AA0C 7C055B2E */  sthx    r0, r5, r11
/* 085470 8008AA10 38DE0005 */  addi    r6, r30, 5
/* 085474 8008AA14 54C8083C */  slwi    r8, r6, 1
/* 085478 8008AA18 80DC3294 */  lwz     r6, 0x3294(r28)
/* 08547C 8008AA1C 38BE0006 */  addi    r5, r30, 6
/* 085480 8008AA20 54A7083C */  slwi    r7, r5, 1
/* 085484 8008AA24 7C06532E */  sthx    r0, r6, r10
/* 085488 8008AA28 38BE0007 */  addi    r5, r30, 7
/* 08548C 8008AA2C 54A4083C */  slwi    r4, r5, 1
/* 085490 8008AA30 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085494 8008AA34 38C30001 */  addi    r6, r3, 1
/* 085498 8008AA38 39630002 */  addi    r11, r3, 2
/* 08549C 8008AA3C 7C054B2E */  sthx    r0, r5, r9
/* 0854A0 8008AA40 39430003 */  addi    r10, r3, 3
/* 0854A4 8008AA44 39230004 */  addi    r9, r3, 4
/* 0854A8 8008AA48 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0854AC 8008AA4C 5475083C */  slwi    r21, r3, 1
/* 0854B0 8008AA50 54CC083C */  slwi    r12, r6, 1
/* 0854B4 8008AA54 7C05432E */  sthx    r0, r5, r8
/* 0854B8 8008AA58 38C30005 */  addi    r6, r3, 5
/* 0854BC 8008AA5C 556B083C */  slwi    r11, r11, 1
/* 0854C0 8008AA60 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0854C4 8008AA64 554A083C */  slwi    r10, r10, 1
/* 0854C8 8008AA68 5529083C */  slwi    r9, r9, 1
/* 0854CC 8008AA6C 7C053B2E */  sthx    r0, r5, r7
/* 0854D0 8008AA70 38A30006 */  addi    r5, r3, 6
/* 0854D4 8008AA74 54C8083C */  slwi    r8, r6, 1
/* 0854D8 8008AA78 80DC3294 */  lwz     r6, 0x3294(r28)
/* 0854DC 8008AA7C 54A7083C */  slwi    r7, r5, 1
/* 0854E0 8008AA80 38A30007 */  addi    r5, r3, 7
/* 0854E4 8008AA84 7C06232E */  sthx    r0, r6, r4
/* 0854E8 8008AA88 54A4083C */  slwi    r4, r5, 1
/* 0854EC 8008AA8C 807C3294 */  lwz     r3, 0x3294(r28)
/* 0854F0 8008AA90 7C03AB2E */  sthx    r0, r3, r21
/* 0854F4 8008AA94 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0854F8 8008AA98 7C05632E */  sthx    r0, r5, r12
/* 0854FC 8008AA9C 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085500 8008AAA0 7C055B2E */  sthx    r0, r5, r11
/* 085504 8008AAA4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085508 8008AAA8 7C06532E */  sthx    r0, r6, r10
/* 08550C 8008AAAC 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085510 8008AAB0 7C054B2E */  sthx    r0, r5, r9
/* 085514 8008AAB4 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085518 8008AAB8 7C05432E */  sthx    r0, r5, r8
/* 08551C 8008AABC 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085520 8008AAC0 7C053B2E */  sthx    r0, r5, r7
/* 085524 8008AAC4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085528 8008AAC8 7C06232E */  sthx    r0, r6, r4
lbl_8008AACC:
/* 08552C 8008AACC 2C1D0000 */  cmpwi   r29, 0
/* 085530 8008AAD0 3BDE0010 */  addi    r30, r30, 0x10
/* 085534 8008AAD4 40820154 */  bne     lbl_8008AC28
/* 085538 8008AAD8 381EFFF0 */  addi    r0, r30, -16
/* 08553C 8008AADC 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085540 8008AAE0 5400083C */  slwi    r0, r0, 1
/* 085544 8008AAE4 80810060 */  lwz     r4, 0x60(r1)
/* 085548 8008AAE8 7C0602AE */  lhax    r0, r6, r0
/* 08554C 8008AAEC 38DEFFF1 */  addi    r6, r30, -15
/* 085550 8008AAF0 399EFFF2 */  addi    r12, r30, -14
/* 085554 8008AAF4 B0040000 */  sth     r0, 0(r4)
/* 085558 8008AAF8 5597083C */  slwi    r23, r12, 1
/* 08555C 8008AAFC 395EFFF3 */  addi    r10, r30, -13
/* 085560 8008AB00 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085564 8008AB04 54D8083C */  slwi    r24, r6, 1
/* 085568 8008AB08 5556083C */  slwi    r22, r10, 1
/* 08556C 8008AB0C 7C05C2AE */  lhax    r0, r5, r24
/* 085570 8008AB10 387E0008 */  addi    r3, r30, 8
/* 085574 8008AB14 38C3FFF1 */  addi    r6, r3, -15
/* 085578 8008AB18 B0040002 */  sth     r0, 2(r4)
/* 08557C 8008AB1C 391EFFF4 */  addi    r8, r30, -12
/* 085580 8008AB20 5515083C */  slwi    r21, r8, 1
/* 085584 8008AB24 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085588 8008AB28 399EFFF5 */  addi    r12, r30, -11
/* 08558C 8008AB2C 558B083C */  slwi    r11, r12, 1
/* 085590 8008AB30 7C05BAAE */  lhax    r0, r5, r23
/* 085594 8008AB34 395EFFF6 */  addi    r10, r30, -10
/* 085598 8008AB38 5549083C */  slwi    r9, r10, 1
/* 08559C 8008AB3C B0040004 */  sth     r0, 4(r4)
/* 0855A0 8008AB40 391EFFF7 */  addi    r8, r30, -9
/* 0855A4 8008AB44 5507083C */  slwi    r7, r8, 1
/* 0855A8 8008AB48 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0855AC 8008AB4C 3803FFF0 */  addi    r0, r3, -16
/* 0855B0 8008AB50 3983FFF2 */  addi    r12, r3, -14
/* 0855B4 8008AB54 7CA5B2AE */  lhax    r5, r5, r22
/* 0855B8 8008AB58 5597083C */  slwi    r23, r12, 1
/* 0855BC 8008AB5C 3943FFF3 */  addi    r10, r3, -13
/* 0855C0 8008AB60 B0A40006 */  sth     r5, 6(r4)
/* 0855C4 8008AB64 54D8083C */  slwi    r24, r6, 1
/* 0855C8 8008AB68 5556083C */  slwi    r22, r10, 1
/* 0855CC 8008AB6C 80DC3294 */  lwz     r6, 0x3294(r28)
/* 0855D0 8008AB70 5400083C */  slwi    r0, r0, 1
/* 0855D4 8008AB74 3903FFF4 */  addi    r8, r3, -12
/* 0855D8 8008AB78 7CC6AAAE */  lhax    r6, r6, r21
/* 0855DC 8008AB7C 5515083C */  slwi    r21, r8, 1
/* 0855E0 8008AB80 3983FFF5 */  addi    r12, r3, -11
/* 0855E4 8008AB84 B0C40008 */  sth     r6, 8(r4)
/* 0855E8 8008AB88 3943FFF6 */  addi    r10, r3, -10
/* 0855EC 8008AB8C 3903FFF7 */  addi    r8, r3, -9
/* 0855F0 8008AB90 80DC3294 */  lwz     r6, 0x3294(r28)
/* 0855F4 8008AB94 38600001 */  li      r3, 1
/* 0855F8 8008AB98 7CC65AAE */  lhax    r6, r6, r11
/* 0855FC 8008AB9C 558B083C */  slwi    r11, r12, 1
/* 085600 8008ABA0 B0C4000A */  sth     r6, 0xa(r4)
/* 085604 8008ABA4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085608 8008ABA8 7CC64AAE */  lhax    r6, r6, r9
/* 08560C 8008ABAC 5549083C */  slwi    r9, r10, 1
/* 085610 8008ABB0 B0C4000C */  sth     r6, 0xc(r4)
/* 085614 8008ABB4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085618 8008ABB8 7CC63AAE */  lhax    r6, r6, r7
/* 08561C 8008ABBC 5507083C */  slwi    r7, r8, 1
/* 085620 8008ABC0 B0C4000E */  sth     r6, 0xe(r4)
/* 085624 8008ABC4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085628 8008ABC8 7C0602AE */  lhax    r0, r6, r0
/* 08562C 8008ABCC B0040010 */  sth     r0, 0x10(r4)
/* 085630 8008ABD0 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085634 8008ABD4 7C05C2AE */  lhax    r0, r5, r24
/* 085638 8008ABD8 B0040012 */  sth     r0, 0x12(r4)
/* 08563C 8008ABDC 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085640 8008ABE0 7C05BAAE */  lhax    r0, r5, r23
/* 085644 8008ABE4 B0040014 */  sth     r0, 0x14(r4)
/* 085648 8008ABE8 80BC3294 */  lwz     r5, 0x3294(r28)
/* 08564C 8008ABEC 7CA5B2AE */  lhax    r5, r5, r22
/* 085650 8008ABF0 B0A40016 */  sth     r5, 0x16(r4)
/* 085654 8008ABF4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085658 8008ABF8 7CC6AAAE */  lhax    r6, r6, r21
/* 08565C 8008ABFC B0C40018 */  sth     r6, 0x18(r4)
/* 085660 8008AC00 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085664 8008AC04 7CC65AAE */  lhax    r6, r6, r11
/* 085668 8008AC08 B0C4001A */  sth     r6, 0x1a(r4)
/* 08566C 8008AC0C 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085670 8008AC10 7CC64AAE */  lhax    r6, r6, r9
/* 085674 8008AC14 B0C4001C */  sth     r6, 0x1c(r4)
/* 085678 8008AC18 80DC3294 */  lwz     r6, 0x3294(r28)
/* 08567C 8008AC1C 7CC63AAE */  lhax    r6, r6, r7
/* 085680 8008AC20 B0C4001E */  sth     r6, 0x1e(r4)
/* 085684 8008AC24 48000448 */  b       lbl_8008B06C
lbl_8008AC28:
/* 085688 8008AC28 3C600001 */  lis     r3, 1
/* 08568C 8008AC2C 57C5083C */  slwi    r5, r30, 1
/* 085690 8008AC30 38638000 */  addi    r3, r3, -32768
/* 085694 8008AC34 480002E4 */  b       lbl_8008AF18
lbl_8008AC38:
/* 085698 8008AC38 88DF0000 */  lbz     r6, 0(r31)
/* 08569C 8008AC3C 3BFF0001 */  addi    r31, r31, 1
/* 0856A0 8008AC40 54C42DF5 */  rlwinm. r4, r6, 5, 0x17, 0x1a
/* 0856A4 8008AC44 4082000C */  bne     lbl_8008AC50
/* 0856A8 8008AC48 38E00000 */  li      r7, 0
/* 0856AC 8008AC4C 48000188 */  b       lbl_8008ADD4
lbl_8008AC50:
/* 0856B0 8008AC50 28040020 */  cmplwi  r4, 0x20
/* 0856B4 8008AC54 4082000C */  bne     lbl_8008AC60
/* 0856B8 8008AC58 38E00001 */  li      r7, 1
/* 0856BC 8008AC5C 48000178 */  b       lbl_8008ADD4
lbl_8008AC60:
/* 0856C0 8008AC60 28040040 */  cmplwi  r4, 0x40
/* 0856C4 8008AC64 4082000C */  bne     lbl_8008AC70
/* 0856C8 8008AC68 38E00002 */  li      r7, 2
/* 0856CC 8008AC6C 48000168 */  b       lbl_8008ADD4
lbl_8008AC70:
/* 0856D0 8008AC70 28040060 */  cmplwi  r4, 0x60
/* 0856D4 8008AC74 4082000C */  bne     lbl_8008AC80
/* 0856D8 8008AC78 38E00003 */  li      r7, 3
/* 0856DC 8008AC7C 48000158 */  b       lbl_8008ADD4
lbl_8008AC80:
/* 0856E0 8008AC80 A01C38D6 */  lhz     r0, 0x38d6(r28)
/* 0856E4 8008AC84 5484F87E */  srwi    r4, r4, 1
/* 0856E8 8008AC88 811C3294 */  lwz     r8, 0x3294(r28)
/* 0856EC 8008AC8C 38E00004 */  li      r7, 4
/* 0856F0 8008AC90 7C000E70 */  srawi   r0, r0, 1
/* 0856F4 8008AC94 7C000194 */  addze   r0, r0
/* 0856F8 8008AC98 7C840214 */  add     r4, r4, r0
/* 0856FC 8008AC9C 5480083C */  slwi    r0, r4, 1
/* 085700 8008ACA0 7D2802AE */  lhax    r9, r8, r0
/* 085704 8008ACA4 38040008 */  addi    r0, r4, 8
/* 085708 8008ACA8 39040001 */  addi    r8, r4, 1
/* 08570C 8008ACAC B13C3318 */  sth     r9, 0x3318(r28)
/* 085710 8008ACB0 3AC40009 */  addi    r22, r4, 9
/* 085714 8008ACB4 3AE40002 */  addi    r23, r4, 2
/* 085718 8008ACB8 815C3294 */  lwz     r10, 0x3294(r28)
/* 08571C 8008ACBC 5409083C */  slwi    r9, r0, 1
/* 085720 8008ACC0 3804000A */  addi    r0, r4, 0xa
/* 085724 8008ACC4 7D2A4AAE */  lhax    r9, r10, r9
/* 085728 8008ACC8 3B040003 */  addi    r24, r4, 3
/* 08572C 8008ACCC 3B24000B */  addi    r25, r4, 0xb
/* 085730 8008ACD0 B13C3328 */  sth     r9, 0x3328(r28)
/* 085734 8008ACD4 3B640004 */  addi    r27, r4, 4
/* 085738 8008ACD8 3B44000C */  addi    r26, r4, 0xc
/* 08573C 8008ACDC 813C3294 */  lwz     r9, 0x3294(r28)
/* 085740 8008ACE0 5508083C */  slwi    r8, r8, 1
/* 085744 8008ACE4 39840005 */  addi    r12, r4, 5
/* 085748 8008ACE8 7D0942AE */  lhax    r8, r9, r8
/* 08574C 8008ACEC 3964000D */  addi    r11, r4, 0xd
/* 085750 8008ACF0 39440006 */  addi    r10, r4, 6
/* 085754 8008ACF4 B11C331A */  sth     r8, 0x331a(r28)
/* 085758 8008ACF8 3924000E */  addi    r9, r4, 0xe
/* 08575C 8008ACFC 39040007 */  addi    r8, r4, 7
/* 085760 8008AD00 82BC3294 */  lwz     r21, 0x3294(r28)
/* 085764 8008AD04 56D6083C */  slwi    r22, r22, 1
/* 085768 8008AD08 3884000F */  addi    r4, r4, 0xf
/* 08576C 8008AD0C 7ED5B2AE */  lhax    r22, r21, r22
/* 085770 8008AD10 56F7083C */  slwi    r23, r23, 1
/* 085774 8008AD14 5400083C */  slwi    r0, r0, 1
/* 085778 8008AD18 B2DC332A */  sth     r22, 0x332a(r28)
/* 08577C 8008AD1C 5718083C */  slwi    r24, r24, 1
/* 085780 8008AD20 5739083C */  slwi    r25, r25, 1
/* 085784 8008AD24 82DC3294 */  lwz     r22, 0x3294(r28)
/* 085788 8008AD28 577B083C */  slwi    r27, r27, 1
/* 08578C 8008AD2C 575A083C */  slwi    r26, r26, 1
/* 085790 8008AD30 7EF6BAAE */  lhax    r23, r22, r23
/* 085794 8008AD34 558C083C */  slwi    r12, r12, 1
/* 085798 8008AD38 556B083C */  slwi    r11, r11, 1
/* 08579C 8008AD3C B2FC331C */  sth     r23, 0x331c(r28)
/* 0857A0 8008AD40 554A083C */  slwi    r10, r10, 1
/* 0857A4 8008AD44 5529083C */  slwi    r9, r9, 1
/* 0857A8 8008AD48 82FC3294 */  lwz     r23, 0x3294(r28)
/* 0857AC 8008AD4C 5508083C */  slwi    r8, r8, 1
/* 0857B0 8008AD50 5484083C */  slwi    r4, r4, 1
/* 0857B4 8008AD54 7C1702AE */  lhax    r0, r23, r0
/* 0857B8 8008AD58 B01C332C */  sth     r0, 0x332c(r28)
/* 0857BC 8008AD5C 82FC3294 */  lwz     r23, 0x3294(r28)
/* 0857C0 8008AD60 7C17C2AE */  lhax    r0, r23, r24
/* 0857C4 8008AD64 B01C331E */  sth     r0, 0x331e(r28)
/* 0857C8 8008AD68 831C3294 */  lwz     r24, 0x3294(r28)
/* 0857CC 8008AD6C 7C18CAAE */  lhax    r0, r24, r25
/* 0857D0 8008AD70 B01C332E */  sth     r0, 0x332e(r28)
/* 0857D4 8008AD74 833C3294 */  lwz     r25, 0x3294(r28)
/* 0857D8 8008AD78 7C19DAAE */  lhax    r0, r25, r27
/* 0857DC 8008AD7C B01C3320 */  sth     r0, 0x3320(r28)
/* 0857E0 8008AD80 837C3294 */  lwz     r27, 0x3294(r28)
/* 0857E4 8008AD84 7C1BD2AE */  lhax    r0, r27, r26
/* 0857E8 8008AD88 B01C3330 */  sth     r0, 0x3330(r28)
/* 0857EC 8008AD8C 835C3294 */  lwz     r26, 0x3294(r28)
/* 0857F0 8008AD90 7C1A62AE */  lhax    r0, r26, r12
/* 0857F4 8008AD94 B01C3322 */  sth     r0, 0x3322(r28)
/* 0857F8 8008AD98 819C3294 */  lwz     r12, 0x3294(r28)
/* 0857FC 8008AD9C 7C0C5AAE */  lhax    r0, r12, r11
/* 085800 8008ADA0 B01C3332 */  sth     r0, 0x3332(r28)
/* 085804 8008ADA4 817C3294 */  lwz     r11, 0x3294(r28)
/* 085808 8008ADA8 7C0B52AE */  lhax    r0, r11, r10
/* 08580C 8008ADAC B01C3324 */  sth     r0, 0x3324(r28)
/* 085810 8008ADB0 815C3294 */  lwz     r10, 0x3294(r28)
/* 085814 8008ADB4 7C0A4AAE */  lhax    r0, r10, r9
/* 085818 8008ADB8 B01C3334 */  sth     r0, 0x3334(r28)
/* 08581C 8008ADBC 813C3294 */  lwz     r9, 0x3294(r28)
/* 085820 8008ADC0 7C0942AE */  lhax    r0, r9, r8
/* 085824 8008ADC4 B01C3326 */  sth     r0, 0x3326(r28)
/* 085828 8008ADC8 811C3294 */  lwz     r8, 0x3294(r28)
/* 08582C 8008ADCC 7C0822AE */  lhax    r0, r8, r4
/* 085830 8008ADD0 B01C3336 */  sth     r0, 0x3336(r28)
lbl_8008ADD4:
/* 085834 8008ADD4 801C3294 */  lwz     r0, 0x3294(r28)
/* 085838 8008ADD8 54E42834 */  slwi    r4, r7, 5
/* 08583C 8008ADDC 7CFC2214 */  add     r7, r28, r4
/* 085840 8008ADE0 7D402A14 */  add     r10, r0, r5
/* 085844 8008ADE4 A9073298 */  lha     r8, 0x3298(r7)
/* 085848 8008ADE8 7CC42670 */  srawi   r4, r6, 4
/* 08584C 8008ADEC A92732A8 */  lha     r9, 0x32a8(r7)
/* 085850 8008ADF0 38000008 */  li      r0, 8
/* 085854 8008ADF4 AACAFFFC */  lha     r22, -4(r10)
/* 085858 8008ADF8 2084000C */  subfic  r4, r4, 0xc
/* 08585C 8008ADFC 7C0903A6 */  mtctr   r0
/* 085860 8008AE00 A8CAFFFE */  lha     r6, -2(r10)
/* 085864 8008AE04 3804FFFF */  addi    r0, r4, -1
/* 085868 8008AE08 57CB083C */  slwi    r11, r30, 1
lbl_8008AE0C:
/* 08586C 8008AE0C 88FF0000 */  lbz     r7, 0(r31)
/* 085870 8008AE10 7C6A0630 */  sraw    r10, r3, r0
/* 085874 8008AE14 2C040000 */  cmpwi   r4, 0
/* 085878 8008AE18 7CE70774 */  extsb   r7, r7
/* 08587C 8008AE1C 54EC4426 */  rlwinm  r12, r7, 8, 0x10, 0x13
/* 085880 8008AE20 54E76426 */  rlwinm  r7, r7, 0xc, 0x10, 0x13
/* 085884 8008AE24 7D8C0734 */  extsh   r12, r12
/* 085888 8008AE28 7CE70734 */  extsh   r7, r7
/* 08588C 8008AE2C 5555043E */  clrlwi  r21, r10, 0x10
/* 085890 8008AE30 3BFF0001 */  addi    r31, r31, 1
/* 085894 8008AE34 40810014 */  ble     lbl_8008AE48
/* 085898 8008AE38 7D4CA9D6 */  mullw   r10, r12, r21
/* 08589C 8008AE3C 7D4A8670 */  srawi   r10, r10, 0x10
/* 0858A0 8008AE40 7D570734 */  extsh   r23, r10
/* 0858A4 8008AE44 48000008 */  b       lbl_8008AE4C
lbl_8008AE48:
/* 0858A8 8008AE48 7D976378 */  mr      r23, r12
lbl_8008AE4C:
/* 0858AC 8008AE4C 7CCC0734 */  extsh   r12, r6
/* 0858B0 8008AE50 7ECA0734 */  extsh   r10, r22
/* 0858B4 8008AE54 7F4C49D6 */  mullw   r26, r12, r9
/* 0858B8 8008AE58 7D4A41D6 */  mullw   r10, r10, r8
/* 0858BC 8008AE5C 7EEC0734 */  extsh   r12, r23
/* 0858C0 8008AE60 558C5828 */  slwi    r12, r12, 0xb
/* 0858C4 8008AE64 7D4AD214 */  add     r10, r10, r26
/* 0858C8 8008AE68 7D4C5214 */  add     r10, r12, r10
/* 0858CC 8008AE6C 7D4A8670 */  srawi   r10, r10, 0x10
/* 0858D0 8008AE70 554A2834 */  slwi    r10, r10, 5
/* 0858D4 8008AE74 2C0A7FFF */  cmpwi   r10, 0x7fff
/* 0858D8 8008AE78 4081000C */  ble     lbl_8008AE84
/* 0858DC 8008AE7C 39407FFF */  li      r10, 0x7fff
/* 0858E0 8008AE80 48000010 */  b       lbl_8008AE90
lbl_8008AE84:
/* 0858E4 8008AE84 2C0A8000 */  cmpwi   r10, -32768
/* 0858E8 8008AE88 40800008 */  bge     lbl_8008AE90
/* 0858EC 8008AE8C 39408000 */  li      r10, -32768
lbl_8008AE90:
/* 0858F0 8008AE90 819C3294 */  lwz     r12, 0x3294(r28)
/* 0858F4 8008AE94 7D4A0734 */  extsh   r10, r10
/* 0858F8 8008AE98 2C040000 */  cmpwi   r4, 0
/* 0858FC 8008AE9C 7D4C5B2E */  sthx    r10, r12, r11
/* 085900 8008AEA0 40810010 */  ble     lbl_8008AEB0
/* 085904 8008AEA4 7CE7A9D6 */  mullw   r7, r7, r21
/* 085908 8008AEA8 7CE78670 */  srawi   r7, r7, 0x10
/* 08590C 8008AEAC 7CE70734 */  extsh   r7, r7
lbl_8008AEB0:
/* 085910 8008AEB0 7CC60734 */  extsh   r6, r6
/* 085914 8008AEB4 7D8A49D6 */  mullw   r12, r10, r9
/* 085918 8008AEB8 7CC641D6 */  mullw   r6, r6, r8
/* 08591C 8008AEBC 7CE70734 */  extsh   r7, r7
/* 085920 8008AEC0 54E75828 */  slwi    r7, r7, 0xb
/* 085924 8008AEC4 7CC66214 */  add     r6, r6, r12
/* 085928 8008AEC8 7CC73214 */  add     r6, r7, r6
/* 08592C 8008AECC 7CC68670 */  srawi   r6, r6, 0x10
/* 085930 8008AED0 54C62834 */  slwi    r6, r6, 5
/* 085934 8008AED4 2C067FFF */  cmpwi   r6, 0x7fff
/* 085938 8008AED8 4081000C */  ble     lbl_8008AEE4
/* 08593C 8008AEDC 38C07FFF */  li      r6, 0x7fff
/* 085940 8008AEE0 48000010 */  b       lbl_8008AEF0
lbl_8008AEE4:
/* 085944 8008AEE4 2C068000 */  cmpwi   r6, -32768
/* 085948 8008AEE8 40800008 */  bge     lbl_8008AEF0
/* 08594C 8008AEEC 38C08000 */  li      r6, -32768
lbl_8008AEF0:
/* 085950 8008AEF0 819C3294 */  lwz     r12, 0x3294(r28)
/* 085954 8008AEF4 38EB0002 */  addi    r7, r11, 2
/* 085958 8008AEF8 7CC60734 */  extsh   r6, r6
/* 08595C 8008AEFC 7CCC3B2E */  sthx    r6, r12, r7
/* 085960 8008AF00 3ACA0000 */  addi    r22, r10, 0
/* 085964 8008AF04 396B0004 */  addi    r11, r11, 4
/* 085968 8008AF08 4200FF04 */  bdnz    lbl_8008AE0C
/* 08596C 8008AF0C 38A50020 */  addi    r5, r5, 0x20
/* 085970 8008AF10 3BDE0010 */  addi    r30, r30, 0x10
/* 085974 8008AF14 3BBDFFF0 */  addi    r29, r29, -16
lbl_8008AF18:
/* 085978 8008AF18 2C1D0000 */  cmpwi   r29, 0
/* 08597C 8008AF1C 4181FD1C */  bgt     lbl_8008AC38
/* 085980 8008AF20 381EFFF0 */  addi    r0, r30, -16
/* 085984 8008AF24 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085988 8008AF28 5400083C */  slwi    r0, r0, 1
/* 08598C 8008AF2C 80810060 */  lwz     r4, 0x60(r1)
/* 085990 8008AF30 7C0602AE */  lhax    r0, r6, r0
/* 085994 8008AF34 38DEFFF1 */  addi    r6, r30, -15
/* 085998 8008AF38 399EFFF2 */  addi    r12, r30, -14
/* 08599C 8008AF3C B0040000 */  sth     r0, 0(r4)
/* 0859A0 8008AF40 559B083C */  slwi    r27, r12, 1
/* 0859A4 8008AF44 395EFFF3 */  addi    r10, r30, -13
/* 0859A8 8008AF48 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0859AC 8008AF4C 54DA083C */  slwi    r26, r6, 1
/* 0859B0 8008AF50 555F083C */  slwi    r31, r10, 1
/* 0859B4 8008AF54 7C05D2AE */  lhax    r0, r5, r26
/* 0859B8 8008AF58 387E0008 */  addi    r3, r30, 8
/* 0859BC 8008AF5C 38C3FFF1 */  addi    r6, r3, -15
/* 0859C0 8008AF60 B0040002 */  sth     r0, 2(r4)
/* 0859C4 8008AF64 391EFFF4 */  addi    r8, r30, -12
/* 0859C8 8008AF68 551D083C */  slwi    r29, r8, 1
/* 0859CC 8008AF6C 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0859D0 8008AF70 399EFFF5 */  addi    r12, r30, -11
/* 0859D4 8008AF74 558B083C */  slwi    r11, r12, 1
/* 0859D8 8008AF78 7C05DAAE */  lhax    r0, r5, r27
/* 0859DC 8008AF7C 395EFFF6 */  addi    r10, r30, -10
/* 0859E0 8008AF80 5549083C */  slwi    r9, r10, 1
/* 0859E4 8008AF84 B0040004 */  sth     r0, 4(r4)
/* 0859E8 8008AF88 391EFFF7 */  addi    r8, r30, -9
/* 0859EC 8008AF8C 5507083C */  slwi    r7, r8, 1
/* 0859F0 8008AF90 80BC3294 */  lwz     r5, 0x3294(r28)
/* 0859F4 8008AF94 3803FFF0 */  addi    r0, r3, -16
/* 0859F8 8008AF98 3983FFF2 */  addi    r12, r3, -14
/* 0859FC 8008AF9C 7CA5FAAE */  lhax    r5, r5, r31
/* 085A00 8008AFA0 559B083C */  slwi    r27, r12, 1
/* 085A04 8008AFA4 3943FFF3 */  addi    r10, r3, -13
/* 085A08 8008AFA8 B0A40006 */  sth     r5, 6(r4)
/* 085A0C 8008AFAC 54DA083C */  slwi    r26, r6, 1
/* 085A10 8008AFB0 555F083C */  slwi    r31, r10, 1
/* 085A14 8008AFB4 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085A18 8008AFB8 5400083C */  slwi    r0, r0, 1
/* 085A1C 8008AFBC 3903FFF4 */  addi    r8, r3, -12
/* 085A20 8008AFC0 7CC6EAAE */  lhax    r6, r6, r29
/* 085A24 8008AFC4 551D083C */  slwi    r29, r8, 1
/* 085A28 8008AFC8 3983FFF5 */  addi    r12, r3, -11
/* 085A2C 8008AFCC B0C40008 */  sth     r6, 8(r4)
/* 085A30 8008AFD0 3943FFF6 */  addi    r10, r3, -10
/* 085A34 8008AFD4 3903FFF7 */  addi    r8, r3, -9
/* 085A38 8008AFD8 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085A3C 8008AFDC 38600001 */  li      r3, 1
/* 085A40 8008AFE0 7CC65AAE */  lhax    r6, r6, r11
/* 085A44 8008AFE4 558B083C */  slwi    r11, r12, 1
/* 085A48 8008AFE8 B0C4000A */  sth     r6, 0xa(r4)
/* 085A4C 8008AFEC 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085A50 8008AFF0 7CC64AAE */  lhax    r6, r6, r9
/* 085A54 8008AFF4 5549083C */  slwi    r9, r10, 1
/* 085A58 8008AFF8 B0C4000C */  sth     r6, 0xc(r4)
/* 085A5C 8008AFFC 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085A60 8008B000 7CC63AAE */  lhax    r6, r6, r7
/* 085A64 8008B004 5507083C */  slwi    r7, r8, 1
/* 085A68 8008B008 B0C4000E */  sth     r6, 0xe(r4)
/* 085A6C 8008B00C 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085A70 8008B010 7C0602AE */  lhax    r0, r6, r0
/* 085A74 8008B014 B0040010 */  sth     r0, 0x10(r4)
/* 085A78 8008B018 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085A7C 8008B01C 7C05D2AE */  lhax    r0, r5, r26
/* 085A80 8008B020 B0040012 */  sth     r0, 0x12(r4)
/* 085A84 8008B024 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085A88 8008B028 7C05DAAE */  lhax    r0, r5, r27
/* 085A8C 8008B02C B0040014 */  sth     r0, 0x14(r4)
/* 085A90 8008B030 80BC3294 */  lwz     r5, 0x3294(r28)
/* 085A94 8008B034 7CA5FAAE */  lhax    r5, r5, r31
/* 085A98 8008B038 B0A40016 */  sth     r5, 0x16(r4)
/* 085A9C 8008B03C 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085AA0 8008B040 7CC6EAAE */  lhax    r6, r6, r29
/* 085AA4 8008B044 B0C40018 */  sth     r6, 0x18(r4)
/* 085AA8 8008B048 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085AAC 8008B04C 7CC65AAE */  lhax    r6, r6, r11
/* 085AB0 8008B050 B0C4001A */  sth     r6, 0x1a(r4)
/* 085AB4 8008B054 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085AB8 8008B058 7CC64AAE */  lhax    r6, r6, r9
/* 085ABC 8008B05C B0C4001C */  sth     r6, 0x1c(r4)
/* 085AC0 8008B060 80DC3294 */  lwz     r6, 0x3294(r28)
/* 085AC4 8008B064 7CC63AAE */  lhax    r6, r6, r7
/* 085AC8 8008B068 B0C4001E */  sth     r6, 0x1e(r4)
lbl_8008B06C:
/* 085ACC 8008B06C BAA1006C */  lmw     r21, 0x6c(r1)
/* 085AD0 8008B070 8001009C */  lwz     r0, 0x9c(r1)
/* 085AD4 8008B074 38210098 */  addi    r1, r1, 0x98
/* 085AD8 8008B078 7C0803A6 */  mtlr    r0
/* 085ADC 8008B07C 4E800020 */  blr     
