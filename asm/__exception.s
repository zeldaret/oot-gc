# __exception.s
.include "macros.inc"

.section .init

.balign 4

glabel gTRKInterruptVectorTable
/* 00037C 8000347C 4D657472 */  .string "Metrowerks Target Resident Kernel for PowerPC"
                                .balign 4

    .skip 208

/* 00047C 8000357C 48001E34 */  b       __TRK_reset

    .skip 252

/* 00057C 8000367C 7C5143A6 */  mtspr   0x111, r2
/* 000580 80003680 7C5A02A6 */  mfspr   r2, 0x1a
/* 000584 80003684 7C0017AC */  icbi    0, r2
/* 000588 80003688 7C5302A6 */  mfdar   r2
/* 00058C 8000368C 7C0013AC */  dcbi    0, r2
/* 000590 80003690 7C5142A6 */  mfspr   r2, 0x111
/* 000594 80003694 7C5143A6 */  mtspr   0x111, r2
/* 000598 80003698 7C7243A6 */  mtspr   0x112, r3
/* 00059C 8000369C 7C9343A6 */  mtspr   0x113, r4
/* 0005A0 800036A0 7C5A02A6 */  mfspr   r2, 0x1a
/* 0005A4 800036A4 7C9B02A6 */  mfspr   r4, 0x1b
/* 0005A8 800036A8 7C6000A6 */  mfmsr   r3
/* 0005AC 800036AC 60630030 */  ori     r3, r3, 0x30
/* 0005B0 800036B0 7C7B03A6 */  mtspr   0x1b, r3
/* 0005B4 800036B4 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0005B8 800036B8 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0005BC 800036BC 7C7A03A6 */  mtspr   0x1a, r3
/* 0005C0 800036C0 38600200 */  li      r3, 0x200
/* 0005C4 800036C4 4C000064 */  rfi     

    .skip 180

/* 00067C 8000377C 7C5143A6 */  mtspr   0x111, r2
/* 000680 80003780 7C7243A6 */  mtspr   0x112, r3
/* 000684 80003784 7C9343A6 */  mtspr   0x113, r4
/* 000688 80003788 7C5A02A6 */  mfspr   r2, 0x1a
/* 00068C 8000378C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000690 80003790 7C6000A6 */  mfmsr   r3
/* 000694 80003794 60630030 */  ori     r3, r3, 0x30
/* 000698 80003798 7C7B03A6 */  mtspr   0x1b, r3
/* 00069C 8000379C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0006A0 800037A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0006A4 800037A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0006A8 800037A8 38600300 */  li      r3, 0x300
/* 0006AC 800037AC 4C000064 */  rfi     

    .skip 204

/* 00077C 8000387C 7C5143A6 */  mtspr   0x111, r2
/* 000780 80003880 7C7243A6 */  mtspr   0x112, r3
/* 000784 80003884 7C9343A6 */  mtspr   0x113, r4
/* 000788 80003888 7C5A02A6 */  mfspr   r2, 0x1a
/* 00078C 8000388C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000790 80003890 7C6000A6 */  mfmsr   r3
/* 000794 80003894 60630030 */  ori     r3, r3, 0x30
/* 000798 80003898 7C7B03A6 */  mtspr   0x1b, r3
/* 00079C 8000389C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0007A0 800038A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0007A4 800038A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0007A8 800038A8 38600400 */  li      r3, 0x400
/* 0007AC 800038AC 4C000064 */  rfi     

    .skip 204

/* 00087C 8000397C 7C5143A6 */  mtspr   0x111, r2
/* 000880 80003980 7C7243A6 */  mtspr   0x112, r3
/* 000884 80003984 7C9343A6 */  mtspr   0x113, r4
/* 000888 80003988 7C5A02A6 */  mfspr   r2, 0x1a
/* 00088C 8000398C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000890 80003990 7C6000A6 */  mfmsr   r3
/* 000894 80003994 60630030 */  ori     r3, r3, 0x30
/* 000898 80003998 7C7B03A6 */  mtspr   0x1b, r3
/* 00089C 8000399C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0008A0 800039A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0008A4 800039A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0008A8 800039A8 38600500 */  li      r3, 0x500
/* 0008AC 800039AC 4C000064 */  rfi     

    .skip 204

/* 00097C 80003A7C 7C5143A6 */  mtspr   0x111, r2
/* 000980 80003A80 7C7243A6 */  mtspr   0x112, r3
/* 000984 80003A84 7C9343A6 */  mtspr   0x113, r4
/* 000988 80003A88 7C5A02A6 */  mfspr   r2, 0x1a
/* 00098C 80003A8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000990 80003A90 7C6000A6 */  mfmsr   r3
/* 000994 80003A94 60630030 */  ori     r3, r3, 0x30
/* 000998 80003A98 7C7B03A6 */  mtspr   0x1b, r3
/* 00099C 80003A9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0009A0 80003AA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0009A4 80003AA4 7C7A03A6 */  mtspr   0x1a, r3
/* 0009A8 80003AA8 38600600 */  li      r3, 0x600
/* 0009AC 80003AAC 4C000064 */  rfi     

    .skip 204

/* 000A7C 80003B7C 7C5143A6 */  mtspr   0x111, r2
/* 000A80 80003B80 7C7243A6 */  mtspr   0x112, r3
/* 000A84 80003B84 7C9343A6 */  mtspr   0x113, r4
/* 000A88 80003B88 7C5A02A6 */  mfspr   r2, 0x1a
/* 000A8C 80003B8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000A90 80003B90 7C6000A6 */  mfmsr   r3
/* 000A94 80003B94 60630030 */  ori     r3, r3, 0x30
/* 000A98 80003B98 7C7B03A6 */  mtspr   0x1b, r3
/* 000A9C 80003B9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 000AA0 80003BA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 000AA4 80003BA4 7C7A03A6 */  mtspr   0x1a, r3
/* 000AA8 80003BA8 38600700 */  li      r3, 0x700
/* 000AAC 80003BAC 4C000064 */  rfi     

    .skip 204

/* 000B7C 80003C7C 7C5143A6 */  mtspr   0x111, r2
/* 000B80 80003C80 7C7243A6 */  mtspr   0x112, r3
/* 000B84 80003C84 7C9343A6 */  mtspr   0x113, r4
/* 000B88 80003C88 7C5A02A6 */  mfspr   r2, 0x1a
/* 000B8C 80003C8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000B90 80003C90 7C6000A6 */  mfmsr   r3
/* 000B94 80003C94 60630030 */  ori     r3, r3, 0x30
/* 000B98 80003C98 7C7B03A6 */  mtspr   0x1b, r3
/* 000B9C 80003C9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 000BA0 80003CA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 000BA4 80003CA4 7C7A03A6 */  mtspr   0x1a, r3
/* 000BA8 80003CA8 38600800 */  li      r3, 0x800
/* 000BAC 80003CAC 4C000064 */  rfi     

    .skip 204

/* 000C7C 80003D7C 7C5143A6 */  mtspr   0x111, r2
/* 000C80 80003D80 7C7243A6 */  mtspr   0x112, r3
/* 000C84 80003D84 7C9343A6 */  mtspr   0x113, r4
/* 000C88 80003D88 7C5A02A6 */  mfspr   r2, 0x1a
/* 000C8C 80003D8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000C90 80003D90 7C6000A6 */  mfmsr   r3
/* 000C94 80003D94 60630030 */  ori     r3, r3, 0x30
/* 000C98 80003D98 7C7B03A6 */  mtspr   0x1b, r3
/* 000C9C 80003D9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 000CA0 80003DA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 000CA4 80003DA4 7C7A03A6 */  mtspr   0x1a, r3
/* 000CA8 80003DA8 38600900 */  li      r3, 0x900
/* 000CAC 80003DAC 4C000064 */  rfi     

    .skip 716

/* 000F7C 8000407C 7C5143A6 */  mtspr   0x111, r2
/* 000F80 80004080 7C7243A6 */  mtspr   0x112, r3
/* 000F84 80004084 7C9343A6 */  mtspr   0x113, r4
/* 000F88 80004088 7C5A02A6 */  mfspr   r2, 0x1a
/* 000F8C 8000408C 7C9B02A6 */  mfspr   r4, 0x1b
/* 000F90 80004090 7C6000A6 */  mfmsr   r3
/* 000F94 80004094 60630030 */  ori     r3, r3, 0x30
/* 000F98 80004098 7C7B03A6 */  mtspr   0x1b, r3
/* 000F9C 8000409C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 000FA0 800040A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 000FA4 800040A4 7C7A03A6 */  mtspr   0x1a, r3
/* 000FA8 800040A8 38600C00 */  li      r3, 0xc00
/* 000FAC 800040AC 4C000064 */  rfi     

    .skip 204

/* 00107C 8000417C 7C5143A6 */  mtspr   0x111, r2
/* 001080 80004180 7C7243A6 */  mtspr   0x112, r3
/* 001084 80004184 7C9343A6 */  mtspr   0x113, r4
/* 001088 80004188 7C5A02A6 */  mfspr   r2, 0x1a
/* 00108C 8000418C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001090 80004190 7C6000A6 */  mfmsr   r3
/* 001094 80004194 60630030 */  ori     r3, r3, 0x30
/* 001098 80004198 7C7B03A6 */  mtspr   0x1b, r3
/* 00109C 8000419C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0010A0 800041A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0010A4 800041A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0010A8 800041A8 38600D00 */  li      r3, 0xd00
/* 0010AC 800041AC 4C000064 */  rfi     

    .skip 204

/* 00117C 8000427C 7C5143A6 */  mtspr   0x111, r2
/* 001180 80004280 7C7243A6 */  mtspr   0x112, r3
/* 001184 80004284 7C9343A6 */  mtspr   0x113, r4
/* 001188 80004288 7C5A02A6 */  mfspr   r2, 0x1a
/* 00118C 8000428C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001190 80004290 7C6000A6 */  mfmsr   r3
/* 001194 80004294 60630030 */  ori     r3, r3, 0x30
/* 001198 80004298 7C7B03A6 */  mtspr   0x1b, r3
/* 00119C 8000429C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0011A0 800042A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0011A4 800042A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0011A8 800042A8 38600E00 */  li      r3, 0xe00
/* 0011AC 800042AC 4C000064 */  rfi     

    .skip 204

/* 00127C 8000437C 48000054 */  b       lbl_800043D0

    .skip 28

/* 00129C 8000439C 7C5143A6 */  mtspr   0x111, r2
/* 0012A0 800043A0 7C7243A6 */  mtspr   0x112, r3
/* 0012A4 800043A4 7C9343A6 */  mtspr   0x113, r4
/* 0012A8 800043A8 7C5A02A6 */  mfspr   r2, 0x1a
/* 0012AC 800043AC 7C9B02A6 */  mfspr   r4, 0x1b
/* 0012B0 800043B0 7C6000A6 */  mfmsr   r3
/* 0012B4 800043B4 60630030 */  ori     r3, r3, 0x30
/* 0012B8 800043B8 7C7B03A6 */  mtspr   0x1b, r3
/* 0012BC 800043BC 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0012C0 800043C0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0012C4 800043C4 7C7A03A6 */  mtspr   0x1a, r3
/* 0012C8 800043C8 38600F20 */  li      r3, 0xf20
/* 0012CC 800043CC 4C000064 */  rfi     

lbl_800043D0:
/* 0012D0 800043D0 7C5143A6 */  mtspr   0x111, r2
/* 0012D4 800043D4 7C7243A6 */  mtspr   0x112, r3
/* 0012D8 800043D8 7C9343A6 */  mtspr   0x113, r4
/* 0012DC 800043DC 7C5A02A6 */  mfspr   r2, 0x1a
/* 0012E0 800043E0 7C9B02A6 */  mfspr   r4, 0x1b
/* 0012E4 800043E4 7C6000A6 */  mfmsr   r3
/* 0012E8 800043E8 60630030 */  ori     r3, r3, 0x30
/* 0012EC 800043EC 7C7B03A6 */  mtspr   0x1b, r3
/* 0012F0 800043F0 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0012F4 800043F4 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0012F8 800043F8 7C7A03A6 */  mtspr   0x1a, r3
/* 0012FC 800043FC 38600F00 */  li      r3, 0xf00
/* 001300 80004400 4C000064 */  rfi     

    .skip 120

/* 00137C 8000447C 7C5143A6 */  mtspr   0x111, r2
/* 001380 80004480 7C400026 */  mfcr    r2
/* 001384 80004484 7C5243A6 */  mtspr   0x112, r2
/* 001388 80004488 7C4000A6 */  mfmsr   r2
/* 00138C 8000448C 74420002 */  andis.  r2, r2, 2
/* 001390 80004490 4182001C */  beq     lbl_800044AC
/* 001394 80004494 7C4000A6 */  mfmsr   r2
/* 001398 80004498 6C420002 */  xoris   r2, r2, 2
/* 00139C 8000449C 7C0004AC */  sync    0
/* 0013A0 800044A0 7C400124 */  mtmsr   r2
/* 0013A4 800044A4 7C0004AC */  sync    0
/* 0013A8 800044A8 7C5143A6 */  mtspr   0x111, r2
lbl_800044AC:
/* 0013AC 800044AC 7C5242A6 */  mfspr   r2, 0x112
/* 0013B0 800044B0 7C4FF120 */  mtcrf   0xff, r2
/* 0013B4 800044B4 7C5142A6 */  mfspr   r2, 0x111
/* 0013B8 800044B8 7C5143A6 */  mtspr   0x111, r2
/* 0013BC 800044BC 7C7243A6 */  mtspr   0x112, r3
/* 0013C0 800044C0 7C9343A6 */  mtspr   0x113, r4
/* 0013C4 800044C4 7C5A02A6 */  mfspr   r2, 0x1a
/* 0013C8 800044C8 7C9B02A6 */  mfspr   r4, 0x1b
/* 0013CC 800044CC 7C6000A6 */  mfmsr   r3
/* 0013D0 800044D0 60630030 */  ori     r3, r3, 0x30
/* 0013D4 800044D4 7C7B03A6 */  mtspr   0x1b, r3
/* 0013D8 800044D8 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0013DC 800044DC 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0013E0 800044E0 7C7A03A6 */  mtspr   0x1a, r3
/* 0013E4 800044E4 38601000 */  li      r3, 0x1000
/* 0013E8 800044E8 4C000064 */  rfi     

    .skip 144

/* 00147C 8000457C 7C5143A6 */  mtspr   0x111, r2
/* 001480 80004580 7C400026 */  mfcr    r2
/* 001484 80004584 7C5243A6 */  mtspr   0x112, r2
/* 001488 80004588 7C4000A6 */  mfmsr   r2
/* 00148C 8000458C 74420002 */  andis.  r2, r2, 2
/* 001490 80004590 4182001C */  beq     lbl_800045AC
/* 001494 80004594 7C4000A6 */  mfmsr   r2
/* 001498 80004598 6C420002 */  xoris   r2, r2, 2
/* 00149C 8000459C 7C0004AC */  sync    0
/* 0014A0 800045A0 7C400124 */  mtmsr   r2
/* 0014A4 800045A4 7C0004AC */  sync    0
/* 0014A8 800045A8 7C5143A6 */  mtspr   0x111, r2
lbl_800045AC:
/* 0014AC 800045AC 7C5242A6 */  mfspr   r2, 0x112
/* 0014B0 800045B0 7C4FF120 */  mtcrf   0xff, r2
/* 0014B4 800045B4 7C5142A6 */  mfspr   r2, 0x111
/* 0014B8 800045B8 7C5143A6 */  mtspr   0x111, r2
/* 0014BC 800045BC 7C7243A6 */  mtspr   0x112, r3
/* 0014C0 800045C0 7C9343A6 */  mtspr   0x113, r4
/* 0014C4 800045C4 7C5A02A6 */  mfspr   r2, 0x1a
/* 0014C8 800045C8 7C9B02A6 */  mfspr   r4, 0x1b
/* 0014CC 800045CC 7C6000A6 */  mfmsr   r3
/* 0014D0 800045D0 60630030 */  ori     r3, r3, 0x30
/* 0014D4 800045D4 7C7B03A6 */  mtspr   0x1b, r3
/* 0014D8 800045D8 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0014DC 800045DC 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0014E0 800045E0 7C7A03A6 */  mtspr   0x1a, r3
/* 0014E4 800045E4 38601100 */  li      r3, 0x1100
/* 0014E8 800045E8 4C000064 */  rfi     

    .skip 144

/* 00157C 8000467C 7C5143A6 */  mtspr   0x111, r2
/* 001580 80004680 7C400026 */  mfcr    r2
/* 001584 80004684 7C5243A6 */  mtspr   0x112, r2
/* 001588 80004688 7C4000A6 */  mfmsr   r2
/* 00158C 8000468C 74420002 */  andis.  r2, r2, 2
/* 001590 80004690 4182001C */  beq     lbl_800046AC
/* 001594 80004694 7C4000A6 */  mfmsr   r2
/* 001598 80004698 6C420002 */  xoris   r2, r2, 2
/* 00159C 8000469C 7C0004AC */  sync    0
/* 0015A0 800046A0 7C400124 */  mtmsr   r2
/* 0015A4 800046A4 7C0004AC */  sync    0
/* 0015A8 800046A8 7C5143A6 */  mtspr   0x111, r2
lbl_800046AC:
/* 0015AC 800046AC 7C5242A6 */  mfspr   r2, 0x112
/* 0015B0 800046B0 7C4FF120 */  mtcrf   0xff, r2
/* 0015B4 800046B4 7C5142A6 */  mfspr   r2, 0x111
/* 0015B8 800046B8 7C5143A6 */  mtspr   0x111, r2
/* 0015BC 800046BC 7C7243A6 */  mtspr   0x112, r3
/* 0015C0 800046C0 7C9343A6 */  mtspr   0x113, r4
/* 0015C4 800046C4 7C5A02A6 */  mfspr   r2, 0x1a
/* 0015C8 800046C8 7C9B02A6 */  mfspr   r4, 0x1b
/* 0015CC 800046CC 7C6000A6 */  mfmsr   r3
/* 0015D0 800046D0 60630030 */  ori     r3, r3, 0x30
/* 0015D4 800046D4 7C7B03A6 */  mtspr   0x1b, r3
/* 0015D8 800046D8 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0015DC 800046DC 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0015E0 800046E0 7C7A03A6 */  mtspr   0x1a, r3
/* 0015E4 800046E4 38601200 */  li      r3, 0x1200
/* 0015E8 800046E8 4C000064 */  rfi     

    .skip 144

/* 00167C 8000477C 7C5143A6 */  mtspr   0x111, r2
/* 001680 80004780 7C7243A6 */  mtspr   0x112, r3
/* 001684 80004784 7C9343A6 */  mtspr   0x113, r4
/* 001688 80004788 7C5A02A6 */  mfspr   r2, 0x1a
/* 00168C 8000478C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001690 80004790 7C6000A6 */  mfmsr   r3
/* 001694 80004794 60630030 */  ori     r3, r3, 0x30
/* 001698 80004798 7C7B03A6 */  mtspr   0x1b, r3
/* 00169C 8000479C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0016A0 800047A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0016A4 800047A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0016A8 800047A8 38601300 */  li      r3, 0x1300
/* 0016AC 800047AC 4C000064 */  rfi     

    .skip 204

/* 00177C 8000487C 7C5143A6 */  mtspr   0x111, r2
/* 001780 80004880 7C7243A6 */  mtspr   0x112, r3
/* 001784 80004884 7C9343A6 */  mtspr   0x113, r4
/* 001788 80004888 7C5A02A6 */  mfspr   r2, 0x1a
/* 00178C 8000488C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001790 80004890 7C6000A6 */  mfmsr   r3
/* 001794 80004894 60630030 */  ori     r3, r3, 0x30
/* 001798 80004898 7C7B03A6 */  mtspr   0x1b, r3
/* 00179C 8000489C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0017A0 800048A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0017A4 800048A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0017A8 800048A8 38601400 */  li      r3, 0x1400
/* 0017AC 800048AC 4C000064 */  rfi     

    .skip 460

/* 00197C 80004A7C 7C5143A6 */  mtspr   0x111, r2
/* 001980 80004A80 7C7243A6 */  mtspr   0x112, r3
/* 001984 80004A84 7C9343A6 */  mtspr   0x113, r4
/* 001988 80004A88 7C5A02A6 */  mfspr   r2, 0x1a
/* 00198C 80004A8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001990 80004A90 7C6000A6 */  mfmsr   r3
/* 001994 80004A94 60630030 */  ori     r3, r3, 0x30
/* 001998 80004A98 7C7B03A6 */  mtspr   0x1b, r3
/* 00199C 80004A9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0019A0 80004AA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0019A4 80004AA4 7C7A03A6 */  mtspr   0x1a, r3
/* 0019A8 80004AA8 38601600 */  li      r3, 0x1600
/* 0019AC 80004AAC 4C000064 */  rfi     

    .skip 204

/* 001A7C 80004B7C 7C5143A6 */  mtspr   0x111, r2
/* 001A80 80004B80 7C7243A6 */  mtspr   0x112, r3
/* 001A84 80004B84 7C9343A6 */  mtspr   0x113, r4
/* 001A88 80004B88 7C5A02A6 */  mfspr   r2, 0x1a
/* 001A8C 80004B8C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001A90 80004B90 7C6000A6 */  mfmsr   r3
/* 001A94 80004B94 60630030 */  ori     r3, r3, 0x30
/* 001A98 80004B98 7C7B03A6 */  mtspr   0x1b, r3
/* 001A9C 80004B9C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 001AA0 80004BA0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 001AA4 80004BA4 7C7A03A6 */  mtspr   0x1a, r3
/* 001AA8 80004BA8 38601700 */  li      r3, 0x1700
/* 001AAC 80004BAC 4C000064 */  rfi     

    .skip 1228

/* 001F7C 8000507C 7C5143A6 */  mtspr   0x111, r2
/* 001F80 80005080 7C7243A6 */  mtspr   0x112, r3
/* 001F84 80005084 7C9343A6 */  mtspr   0x113, r4
/* 001F88 80005088 7C5A02A6 */  mfspr   r2, 0x1a
/* 001F8C 8000508C 7C9B02A6 */  mfspr   r4, 0x1b
/* 001F90 80005090 7C6000A6 */  mfmsr   r3
/* 001F94 80005094 60630030 */  ori     r3, r3, 0x30
/* 001F98 80005098 7C7B03A6 */  mtspr   0x1b, r3
/* 001F9C 8000509C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 001FA0 800050A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 001FA4 800050A4 7C7A03A6 */  mtspr   0x1a, r3
/* 001FA8 800050A8 38601C00 */  li      r3, 0x1c00
/* 001FAC 800050AC 4C000064 */  rfi     

    .skip 204

/* 00207C 8000517C 7C5143A6 */  mtspr   0x111, r2
/* 002080 80005180 7C7243A6 */  mtspr   0x112, r3
/* 002084 80005184 7C9343A6 */  mtspr   0x113, r4
/* 002088 80005188 7C5A02A6 */  mfspr   r2, 0x1a
/* 00208C 8000518C 7C9B02A6 */  mfspr   r4, 0x1b
/* 002090 80005190 7C6000A6 */  mfmsr   r3
/* 002094 80005194 60630030 */  ori     r3, r3, 0x30
/* 002098 80005198 7C7B03A6 */  mtspr   0x1b, r3
/* 00209C 8000519C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0020A0 800051A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0020A4 800051A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0020A8 800051A8 38601D00 */  li      r3, 0x1d00
/* 0020AC 800051AC 4C000064 */  rfi     

    .skip 204

/* 00217C 8000527C 7C5143A6 */  mtspr   0x111, r2
/* 002180 80005280 7C7243A6 */  mtspr   0x112, r3
/* 002184 80005284 7C9343A6 */  mtspr   0x113, r4
/* 002188 80005288 7C5A02A6 */  mfspr   r2, 0x1a
/* 00218C 8000528C 7C9B02A6 */  mfspr   r4, 0x1b
/* 002190 80005290 7C6000A6 */  mfmsr   r3
/* 002194 80005294 60630030 */  ori     r3, r3, 0x30
/* 002198 80005298 7C7B03A6 */  mtspr   0x1b, r3
/* 00219C 8000529C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0021A0 800052A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0021A4 800052A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0021A8 800052A8 38601E00 */  li      r3, 0x1e00
/* 0021AC 800052AC 4C000064 */  rfi     

    .skip 204

/* 00227C 8000537C 7C5143A6 */  mtspr   0x111, r2
/* 002280 80005380 7C7243A6 */  mtspr   0x112, r3
/* 002284 80005384 7C9343A6 */  mtspr   0x113, r4
/* 002288 80005388 7C5A02A6 */  mfspr   r2, 0x1a
/* 00228C 8000538C 7C9B02A6 */  mfspr   r4, 0x1b
/* 002290 80005390 7C6000A6 */  mfmsr   r3
/* 002294 80005394 60630030 */  ori     r3, r3, 0x30
/* 002298 80005398 7C7B03A6 */  mtspr   0x1b, r3
/* 00229C 8000539C 3C60800C */  lis     r3, TRKInterruptHandler@h
/* 0022A0 800053A0 6063C21C */  ori     r3, r3, TRKInterruptHandler@l
/* 0022A4 800053A4 7C7A03A6 */  mtspr   0x1a, r3
/* 0022A8 800053A8 38601F00 */  li      r3, 0x1f00
/* 0022AC 800053AC 4C000064 */  rfi     
