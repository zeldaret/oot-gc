#include "emulator/mcardGCN.h"
#include "emulator/mcardGCN_jumptables.h"

// ゼルダの伝説：時のオカリナ
char D_800EA548[] =
    "\x83\x5b\x83\x8b\x83\x5f\x82\xcc\x93\x60\x90\xe0\x81\x46\x8e\x9e\x82\xcc\x83\x49\x83\x4a\x83\x8a\x83\x69";

char D_800EA564[] = "Invalid Memory Card Command %d - Assuming Go To Game";
char D_800EA59C[] = "mcardGCN.c";

#ifndef NON_MATCHING
void* jtbl_800EA5A8[24] = {
    &lbl_80016D74, &lbl_80016D74, &lbl_80016D08, &lbl_80016CE8, &lbl_80016D48, &lbl_80016CF8,
    &lbl_80016D28, &lbl_80016D74, &lbl_80016D74, &lbl_80016D74, &lbl_80016D74, &lbl_80016D74,
    &lbl_80016D74, &lbl_80016D28, &lbl_80016D74, &lbl_80016D74, &lbl_80016D18, &lbl_80016D74,
    &lbl_80016D54, &lbl_80016D38, &lbl_80016D38, &lbl_80016D74, &lbl_80016D74, &lbl_80016D64,
};
#else
void* jtbl_800EA5A8[24] = {0};
#endif

void* jtbl_800EA608[24] = {
    &lbl_80016E54, &lbl_80016E54, &lbl_80016DE8, &lbl_80016DC8, &lbl_80016E28, &lbl_80016DD8,
    &lbl_80016E08, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54,
    &lbl_80016E54, &lbl_80016E08, &lbl_80016E54, &lbl_80016E54, &lbl_80016DF8, &lbl_80016E54,
    &lbl_80016E44, &lbl_80016E18, &lbl_80016E18, &lbl_80016E54, &lbl_80016E54, &lbl_80016E34,
};

void* jtbl_800EA668[50] = {
    &lbl_800177EC, &lbl_80016EF8, &lbl_80016F24, &lbl_80016F54, &lbl_80016F80, &lbl_80016FAC, &lbl_80016FD8,
    &lbl_80017020, &lbl_80017054, &lbl_80017074, &lbl_8001709C, &lbl_800170E8, &lbl_80017134, &lbl_80017158,
    &lbl_80017180, &lbl_800171A8, &lbl_800171CC, &lbl_800171F0, &lbl_8001721C, &lbl_80017264, &lbl_80017288,
    &lbl_800172A8, &lbl_800172D0, &lbl_80017320, &lbl_8001736C, &lbl_80017398, &lbl_800173B0, &lbl_800173F4,
    &lbl_8001740C, &lbl_80017458, &lbl_8001748C, &lbl_800174AC, &lbl_800174DC, &lbl_80017504, &lbl_80017548,
    &lbl_800177EC, &lbl_80017590, &lbl_800175BC, &lbl_800175E8, &lbl_80017614, &lbl_8001763C, &lbl_80017654,
    &lbl_8001769C, &lbl_800176B4, &lbl_800177EC, &lbl_800176FC, &lbl_80017734, &lbl_80017768, &lbl_8001779C,
    &lbl_800177C4,
};

char D_800EA730[] = "Accessing Card";
char D_800EA740[] = "Writing Game Data";
char D_800EA754[] = "Creating File";
char D_800EA764[] = "Reading Game Data";
char D_800EA778[] = "Reading Card Header";
char D_800EA78C[] = "Writing Card Header";
char D_800EA7A0[] = "Writing File Header";
char D_800EA7B4[] = "Reading File Header";

static char gMCardCardWorkArea[40960];
MemCard mCard;
s32 bNoWriteInCurrentFrame[10];
OSCalendarTime gDate;

static s32 toggle = 0x00000001;
static s32 currentIdx;
static s32 yes;
static __anon_0x1A5F0 prevMenuEntry;
static __anon_0x1A5F0 nextMenuEntry;
static s32 toggle2;
static s32 checkFailCount;
static s32 bWrite2Card;

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGCErrorHandler.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksum.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksumFileBlock1.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksumFileBlock2.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardSaveChecksumFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReplaceFileBlock.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCheckChecksumFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardVerifyChecksumFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardPoll.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadyCard.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadAnywhere.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteAnywhere.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteAnywherePartial.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadFileHeaderInitial.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteFileHeaderInitial.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteBufferAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadBufferAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteConfigAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteTimeAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadGameData.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteGameDataReset.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileCreate.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameCreate.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCardErase.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileErase.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameErase.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameRelease.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardRead.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardMenu.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenError.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenDuringGameError.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWrite.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenDuringGame.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardStore.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardUpdate.s")
