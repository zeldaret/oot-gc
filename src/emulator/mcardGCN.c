#include "emulator/mcardGCN.h"
#include "emulator/mcardGCN_jumptables.h"
#include "emulator/simGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlPostGCN.h"
#include "string.h"

// "The Legend of Zelda: Ocarina of Time"
char D_800EA548[] = "ゼルダの伝説：時のオカリナ";

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

#ifndef NON_MATCHING
void* jtbl_800EA608[24] = {
    &lbl_80016E54, &lbl_80016E54, &lbl_80016DE8, &lbl_80016DC8, &lbl_80016E28, &lbl_80016DD8,
    &lbl_80016E08, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54, &lbl_80016E54,
    &lbl_80016E54, &lbl_80016E08, &lbl_80016E54, &lbl_80016E54, &lbl_80016DF8, &lbl_80016E54,
    &lbl_80016E44, &lbl_80016E18, &lbl_80016E18, &lbl_80016E54, &lbl_80016E54, &lbl_80016E34,
};
#else
void* jtbl_800EA608[24] = {0};
#endif

#ifndef NON_MATCHING
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
#else
void* jtbl_800EA668[50] = {0};
#endif

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
static bool yes;
static MemCardMessage prevMenuEntry;
static MemCardMessage nextMenuEntry;
static s32 toggle2;
static s32 checkFailCount;
static s32 bWrite2Card;

static inline bool mcardFileRelease(MemCard* pMCard);

static bool mcardGCErrorHandler(MemCard* pMCard, s32 gcError);
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGCErrorHandler.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksum.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksumFileBlock1.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCalculateChecksumFileBlock2.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardSaveChecksumFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReplaceFileBlock.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardCheckChecksumFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardVerifyChecksumFileHeader.s")

static bool mcardPoll(MemCard* pMCard);
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardPoll.s")

static bool mcardReadyCard(MemCard* pMCard);
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadyCard.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadAnywhere.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteAnywhere.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteAnywherePartial.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadFileHeader.s")

static bool mcardWriteFileHeader(MemCard* pMCard);
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteFileHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadFileHeaderInitial.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteFileHeaderInitial.s")

static s32 mcardWriteBufferAsynch(MemCard* pMCard, s32 offset);
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteBufferAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadBufferAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteConfigAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardWriteTimeAsynch.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardReadGameData.s")

bool mcardWriteGameDataReset(MemCard* pMCard) {
    if (pMCard->saveToggle == true) {
        while (!mCard.writeToggle) {
            mcardWriteBufferAsynch(pMCard, pMCard->file.game.offset + 0x6000);
        }
    }

    return true;
}

bool mcardReInit(MemCard* pMCard) {
    pMCard->saveToggle = true;
    mcardGameRelease(pMCard);
    mcardFileRelease(pMCard);

    pMCard->error = MC_E_NONE;
    pMCard->slot = 0;
    pMCard->wait = false;
    pMCard->pPollFunction = NULL;
    pMCard->writeToggle = true;

    if (pMCard->writeBuffer != NULL && !xlHeapFree(&pMCard->writeBuffer)) {
        return false;
    }

    if (pMCard->readBuffer != NULL && !xlHeapFree(&pMCard->readBuffer)) {
        return false;
    }

    if (!xlHeapTake(&pMCard->writeBuffer, 0x2000 | 0x30000000)) {
        return false;
    }

    if (!xlHeapTake(&pMCard->readBuffer, 0x2000 | 0x30000000)) {
        return false;
    }

    return true;
}

bool mcardInit(MemCard* pMCard) {
    CARDInit();

    if (pMCard->bufferCreated == 0) {
        pMCard->file.game.buffer = NULL;
    }

    pMCard->file.game.writtenBlocks = NULL;
    pMCard->writeBuffer = NULL;
    pMCard->readBuffer = NULL;
    mcardReInit(pMCard);

    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameSet.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileCreate.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardGameCreate.s")

bool mcardCardErase(MemCard* pMCard) {
    s32 slot;

    if (!mcardReadyCard(pMCard)) {
        if (pMCard->error != MC_E_NONE && pMCard->error != MC_E_BROKEN && pMCard->error != MC_E_ENCODING) {
            CARDUnmount(pMCard->slot);
            return false;
        }
    }

    if (!mcardGCErrorHandler(pMCard, CARDFormatAsync(pMCard->slot, NULL))) {
        CARDUnmount(pMCard->slot);
        return false;
    }

    simulatorPrepareMessage(S_M_CARD_IN02);
    pMCard->pollSize = pMCard->cardSize << 0x11;
    pMCard->pPollFunction = simulatorMCardPollDrawFormatBar;
    pMCard->pollPrevBytes = CARDGetXferredBytes(pMCard->slot);

    if (mcardPoll(pMCard) != 1) {
        pMCard->pPollFunction = NULL;
        CARDUnmount(pMCard->slot);
        return false;
    }

    pMCard->pPollFunction = NULL;
    slot = pMCard->slot;
    CARDInit();

    if (pMCard->bufferCreated == 0) {
        pMCard->file.game.buffer = NULL;
    }

    pMCard->file.game.writtenBlocks = NULL;
    pMCard->writeBuffer = NULL;
    pMCard->readBuffer = NULL;
    mcardReInit(pMCard);
    pMCard->slot = slot;
    CARDUnmount(pMCard->slot);

    return true;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardFileErase.s")
#else
bool mcardFileErase(MemCard* pMCard) {
    if (pMCard->saveToggle == 1) {
        if (!mcardReadyCard(pMCard)) {
            return false;
        }

        if (!mcardGCErrorHandler(pMCard, CARDDeleteAsync(pMCard->slot, pMCard->file.name, NULL))) {
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->accessType = 2;
        pMCard->pPollFunction = simulatorDrawMCardText;
        strcpy(pMCard->pollMessage, "Accessing Card");

        if (mcardPoll(pMCard) != 1) {
            pMCard->pPollFunction = NULL;
            pMCard->accessType = 0;
            mcardGameRelease(pMCard);
            pMCard->file.changedDate = 0;
            memset(pMCard->file.name, 0, 0x21);
            pMCard->file.numberOfGames = 0;
            memset(pMCard->file.gameSize, 0, 0x10);
            memset(pMCard->file.gameOffset, 0, 0x10);
            memset(pMCard->file.gameName[0], 0, 0x201);
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->accessType = 0;
        pMCard->pPollFunction = NULL;
        mcardGameRelease(pMCard);
        pMCard->file.changedDate = 0;
        memset(pMCard->file.name, 0, 0x21);
        pMCard->file.numberOfGames = 0;
        memset(pMCard->file.gameSize, 0, 0x10);
        memset(pMCard->file.gameOffset, 0, 0x10);
        memset(pMCard->file.gameName[0], 0, 0x201);
        CARDUnmount(pMCard->slot);
    }

    return true;
}
#endif

static inline bool mcardGameEraseInline(MemCard* pMCard) {
    if (pMCard->saveToggle == 1) {
        if (!mcardReadyCard(pMCard)) {
            return false;
        }

        if (mcardGCErrorHandler(pMCard, CARDOpen(pMCard->slot, pMCard->file.name, &pMCard->file.fileInfo)) != 1) {
            CARDUnmount(pMCard->slot);
            return false;
        }
    }

    return true;
}

bool mcardGameErase(MemCard* pMCard, s32 index) {
    if (pMCard->saveToggle == 1) {
        pMCard->accessType = 2;
        simulatorPrepareMessage(S_M_CARD_SV09);
        pMCard->file.fileSize -= (((u32)(pMCard->file.gameSize[index] + 8187) / 8188) << 13) + 0x2000;
        pMCard->file.gameSize[index] = 0;
        pMCard->file.gameOffset[index] = 0;
        memset(pMCard->file.gameName[index], 0, sizeof(pMCard->file.gameName[index]));
        pMCard->file.numberOfGames -= 1;

        if (!mcardGameEraseInline(pMCard)) {
            pMCard->accessType = 0;
            return false;
        }

        if (!mcardWriteFileHeader(pMCard)) {
            pMCard->accessType = 0;
            if (pMCard->saveToggle == 1) {
                if (pMCard->file.fileInfo.chan != -1) {
                    CARDClose(&pMCard->file.fileInfo);
                }
                CARDUnmount(pMCard->slot);
            }
            return false;
        }

        pMCard->accessType = 0;

        if (pMCard->saveToggle == 1) {
            if (pMCard->file.fileInfo.chan != -1) {
                CARDClose(&pMCard->file.fileInfo);
            }
            CARDUnmount(pMCard->slot);
        }
    }

    return true;
}

static inline bool mcardFileRelease(MemCard* pMCard) {
    //! TODO: determine if this belongs to this function
    pMCard->file.changedDate = 0;
    memset(pMCard->file.name, 0, ARRAY_COUNT(pMCard->file.name));
    pMCard->file.numberOfGames = 0;
    memset(pMCard->file.gameSize, 0, ARRAY_COUNT(pMCard->file.gameSize));
    memset(pMCard->file.gameOffset, 0, ARRAY_COUNT(pMCard->file.gameOffset));
    memset(pMCard->file.gameName, 0, 0x201);

    if (!pMCard->bufferCreated) {
        if (pMCard->file.game.buffer != NULL) {
            if (!xlHeapFree(&pMCard->file.game.buffer)) {
                return false;
            }
        }

        pMCard->file.game.size = 0;
        memset(&pMCard->file.game.configuration, 0, sizeof(s32));
    }

    if ((pMCard->file.game.writtenBlocks == NULL) || xlHeapFree(&pMCard->file.game.writtenBlocks)) {
        pMCard->file.game.writtenConfig = 0;
        pMCard->file.currentGame = 16;
    }

    return true;
}

bool mcardGameRelease(MemCard* pMCard) {
    if (pMCard->bufferCreated == 0) {
        if (pMCard->file.game.buffer != NULL) {
            if (!xlHeapFree(&pMCard->file.game.buffer)) {
                return false;
            }
        }

        pMCard->file.game.size = 0;
        memset(&pMCard->file.game.configuration, 0, sizeof(s32));
    }

    if (pMCard->file.game.writtenBlocks != NULL) {
        if (!xlHeapFree(&pMCard->file.game.writtenBlocks)) {
            return false;
        }
    }

    pMCard->file.game.writtenConfig = 0;
    pMCard->file.currentGame = 16;

    NO_INLINE();
    return true;
}

bool mcardRead(MemCard* pMCard, s32 address, s32 size, char* data) {
    memcpy(data, &pMCard->file.game.buffer[address], size);
    return true;
}

// matches but data doesn't
//! TODO: define ``yes`` as a static variable inside this function
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardMenu.s")
#else
bool mcardMenu(MemCard* pMCard, MemCardMessage menuEntry, MemCardCommand* pCommand) {
    if (pMCard->wait == true && menuEntry != MC_M_LD01 && menuEntry != MC_M_SV01) {
        menuEntry = nextMenuEntry;
    } else {
        pMCard->wait = false;
        if (menuEntry == prevMenuEntry) {
            menuEntry = nextMenuEntry;
        }
        nextMenuEntry = menuEntry;
    }

    *pCommand = MC_C_CONTINUE;
    switch (menuEntry) {
        case MC_M_LD01:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD01) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD02:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD02) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                pMCard->isBroken = true;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD03:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD03) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD04:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD04) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD05:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD05_1) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD05_2;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD05_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_LD05_2, &yes) == true) {
                if ((s32)yes == true) {
                    yes = false;
                    nextMenuEntry = MC_M_IN01_L;
                    *pCommand = MC_C_CONTINUE;
                } else {
                    nextMenuEntry = MC_M_IN05;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_LD06:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD06_1) == true) {
                nextMenuEntry = MC_M_LD06_2;
                *pCommand = MC_C_CONTINUE;
            } else {
                nextMenuEntry = MC_M_LD06;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD06_2:
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD06_2) == true) {
                nextMenuEntry = MC_M_LD06_3;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD06_3:
            if (simulatorDrawErrorMessageWait(S_M_CARD_LD06_3) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD06_4;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_LD06_4:
            if (simulatorDrawYesNoMessage(S_M_CARD_LD06_4, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_IPL;
                } else {
                    yes = false;
                    nextMenuEntry = MC_M_LD07;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_LD07:
            if (simulatorDrawYesNoMessage(S_M_CARD_LD07, &yes) == true) {
                pMCard->wait = false;
                nextMenuEntry = MC_M_LD07;
                prevMenuEntry = MC_M_NONE;
                if ((s32)yes == true) {
                    pMCard->isBroken = 0;
                    *pCommand = MC_C_GO_TO_GAME;
                } else {
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV01:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV01) == true) {
                nextMenuEntry = MC_M_SV01_2;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV01_2:
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV01_2) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV02:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV02) == true) {
                nextMenuEntry = MC_M_SV_SHARE;
                pMCard->isBroken = true;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV03:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV03) == true) {
                nextMenuEntry = MC_M_SV_SHARE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV04:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV04) == true) {
                nextMenuEntry = MC_M_SV_SHARE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV05:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV05_1) == true) {
                yes = false;
                nextMenuEntry = MC_M_SV05_2;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV05_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_LD05_2, &yes) == true) {
                if ((s32)yes == true) {
                    yes = false;
                    nextMenuEntry = MC_M_IN01_S;
                    *pCommand = MC_C_CONTINUE;
                } else {
                    nextMenuEntry = MC_M_SV11;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV06:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV06_1) == true) {
                nextMenuEntry = MC_M_SV06_2;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV06_2:
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV06_2) == true) {
                nextMenuEntry = MC_M_SV06_3;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV06_3:
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV06_3) == true) {
                yes = false;
                nextMenuEntry = MC_M_SV06_4;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV06_4:
            if (simulatorDrawYesNoMessage(S_M_CARD_SV06_4, &yes) == true) {
                if ((s32)yes == true) {
                    yes = false;
                    nextMenuEntry = MC_M_SV06_5;
                    *pCommand = MC_C_CONTINUE;
                } else {
                    yes = false;
                    nextMenuEntry = MC_M_LD07;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV06_5:
            if (simulatorDrawYesNoMessage(S_M_CARD_SV06_5, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_IPL;
                } else {
                    yes = false;
                    prevMenuEntry = MC_M_NONE;
                    nextMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV07:
            prevMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV07) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV08_L:
            prevMenuEntry = menuEntry;
            nextMenuEntry = MC_M_SV08_L_2;
            yes = false;
            break;
        case MC_M_SV08_L_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_SV08, &yes) == true) {
                if ((s32)yes == true) {
                    *pCommand = MC_C_DELETE_GAME;
                } else {
                    yes = false;
                    nextMenuEntry = MC_M_LD07;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV08:
            prevMenuEntry = menuEntry;
            nextMenuEntry = MC_M_SV08_2;
            yes = false;
            break;
        case MC_M_SV08_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_SV08, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_DELETE_GAME;
                } else {
                    yes = false;
                    nextMenuEntry = MC_M_LD07;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_SV10:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV10) == true) {
                pMCard->wait = false;
                nextMenuEntry = MC_M_NONE;
                prevMenuEntry = MC_M_NONE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV11:
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV11) == true) {
                nextMenuEntry = MC_M_SV_SHARE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_SV12:
            prevMenuEntry = menuEntry;
            pMCard->wait = 1;
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV12) == true) {
                pMCard->wait = false;
                prevMenuEntry = MC_M_NONE;
                *pCommand = MC_C_GO_TO_GAME;
            }
            break;
        case MC_M_SV_SHARE:
            if (simulatorDrawErrorMessageWait(S_M_CARD_SV_SHARE) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN01_L:
            if (simulatorDrawYesNoMessage(S_M_CARD_IN01, &yes) == true) {
                if ((s32)yes == true) {
                    nextMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_FORMAT_CARD;
                } else {
                    nextMenuEntry = MC_M_IN05;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_IN01_S:
            if (simulatorDrawYesNoMessage(S_M_CARD_IN01, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    nextMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_FORMAT_CARD;
                } else {
                    nextMenuEntry = MC_M_SV11;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_IN03:
            pMCard->wait = 1;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN03) == true) {
                pMCard->wait = false;
                prevMenuEntry = MC_M_NONE;
                nextMenuEntry = MC_M_NONE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN04_L:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN04) == true) {
                nextMenuEntry = MC_M_LD02;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN04_S:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN04) == true) {
                nextMenuEntry = MC_M_SV02;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN05:
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN05) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_GF01_L:
            prevMenuEntry = menuEntry;
            yes = false;
            nextMenuEntry = MC_M_GF01_L_2;
            break;
        case MC_M_GF01_L_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_GF01, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    nextMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_CREATE_GAME;
                } else {
                    nextMenuEntry = MC_M_GF06;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_GF01_S:
            prevMenuEntry = menuEntry;
            yes = false;
            nextMenuEntry = MC_M_GF01_S_2;
            break;
        case MC_M_GF01_S_2:
            if (simulatorDrawYesNoMessage(S_M_CARD_GF01, &yes) == true) {
                if ((s32)yes == true) {
                    prevMenuEntry = MC_M_NONE;
                    nextMenuEntry = MC_M_NONE;
                    *pCommand = MC_C_CREATE_GAME;
                } else {
                    nextMenuEntry = MC_M_GF05;
                    *pCommand = MC_C_CONTINUE;
                }
            }
            break;
        case MC_M_GF03:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF03) == true) {
                pMCard->wait = false;
                nextMenuEntry = MC_M_GF05;
                *pCommand = MC_C_GO_TO_GAME;
            }
            break;
        case MC_M_GF04_L:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF04) == true) {
                pMCard->wait = false;
                prevMenuEntry = MC_M_NONE;
                nextMenuEntry = MC_M_NONE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_GF04_S:
            pMCard->wait = 1;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF04) == true) {
                pMCard->wait = false;
                prevMenuEntry = MC_M_NONE;
                nextMenuEntry = MC_M_NONE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_GF05:
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF05) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_GF06:
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF06) == true) {
                yes = false;
                nextMenuEntry = MC_M_LD07;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        default:
            return false;
    }

    return true;
}
#endif

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenError.s")
#else
bool mcardOpenError(MemCard* pMCard, MemCardCommand* pCommand) {
    *pCommand = MC_C_NONE;

    switch (pMCard->error) {
        case MC_E_NOCARD:
            mcardMenu(pMCard, MC_M_LD01, pCommand);
            break;
        case MC_E_IOERROR:
            mcardMenu(pMCard, MC_M_LD02, pCommand);
            break;
        case MC_E_WRONGDEVICE:
            mcardMenu(pMCard, MC_M_LD03, pCommand);
            break;
        case MC_E_SECTOR_SIZE_INVALID:
            mcardMenu(pMCard, MC_M_LD04, pCommand);
            break;
        case MC_E_BROKEN:
        case MC_E_ENCODING:
            mcardMenu(pMCard, MC_M_LD05, pCommand);
            break;
        case MC_E_NO_FREE_SPACE:
        case MC_E_NO_FREE_FILES:
            mcardMenu(pMCard, MC_M_LD06, pCommand);
            break;
        case MC_E_NOFILE:
            *pCommand = MC_C_CREATE_GAME;
            break;
        case MC_E_TIME_WRONG:
            mcardMenu(pMCard, MC_M_SV07, pCommand);
            break;
        case MC_E_CHECKSUM:
            mcardMenu(pMCard, MC_M_SV08_L, pCommand);
            break;
        default:
            return false;
    }

    return true;
}
#endif

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenDuringGameError.s")
#else
bool mcardOpenDuringGameError(MemCard* pMCard, MemCardCommand* pCommand) {
    *pCommand = MC_C_NONE;

    switch (pMCard->error) {
        case MC_E_NOCARD:
            mcardMenu(pMCard, MC_M_SV01, pCommand);
            break;
        case MC_E_IOERROR:
            mcardMenu(pMCard, MC_M_SV02, pCommand);
            break;
        case MC_E_WRONGDEVICE:
            mcardMenu(pMCard, MC_M_SV03, pCommand);
            break;
        case MC_E_SECTOR_SIZE_INVALID:
            mcardMenu(pMCard, MC_M_SV04, pCommand);
            break;
        case MC_E_BROKEN:
        case MC_E_ENCODING:
            mcardMenu(pMCard, MC_M_SV05, pCommand);
            break;
        case MC_E_NO_FREE_SPACE:
        case MC_E_NO_FREE_FILES:
            mcardMenu(pMCard, MC_M_SV06, pCommand);
            break;
        case MC_E_NOFILE:
            *pCommand = MC_C_CREATE_GAME;
            break;
        case MC_E_CHECKSUM:
            mcardMenu(pMCard, MC_M_SV08, pCommand);
            break;
        case MC_E_TIME_WRONG:
            mcardMenu(pMCard, MC_M_SV07, pCommand);
            break;
        default:
            return false;
    }

    return true;
}
#endif

bool mcardWrite(MemCard* pMCard, s32 address, s32 size, char* data) {
    s32 i;
    char testByte;

    testByte = pMCard->file.game.buffer[0];
    bWrite2Card = true;
    bNoWriteInCurrentFrame[currentIdx] = false;

    memcpy(&pMCard->file.game.buffer[address], data, size);

    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        if (address == 0) {
            if (toggle != 0 && pMCard->soundToggle == 1) {
                if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                    pMCard->file.game.buffer[0] &= 0xFC;
                    pMCard->file.game.buffer[0] |= 1;
                } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
                    if ((pMCard->file.game.buffer[0] & 0xF) == 1) {
                        pMCard->file.game.buffer[0] &= 0xFC;
                    }
                }
                *data = pMCard->file.game.buffer[0];
                toggle = 0;
            } else if (pMCard->file.game.buffer[0] != testByte) {
                if ((testByte & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_STEREO);
                } else if ((pMCard->file.game.buffer[0] & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_MONO);
                }
            }
        }
        if (pMCard->saveToggle == 1) {
            //! TODO: fake match
            for (i = (u64)((u32)address / 8188); i < (u32)(address + size + 8187) / 8188; i++) {
                pMCard->file.game.writtenBlocks[i] = 1;
            }

            if (size == 0x1450 && toggle2 == 1) {
                toggle2 = 0;
                simulatorRumbleStop(0);
                if (!mcardUpdate()) {
                    return false;
                }
            } else if (size == 0x1450 && toggle2 == 0) {
                toggle2 = 1;
            }
        } else if (size == 0x1450 && toggle2 == 1) {
            toggle2 = 0;
            pMCard->saveToggle = 1;
            pMCard->wait = 0;
            mcardOpenDuringGame(pMCard);
            if (pMCard->saveToggle == 1) {
                if (!mcardUpdate()) {
                    return false;
                }
            }
        } else if (size == 0x1450 && toggle2 == 0) {
            toggle2 = 1;
        }
    } else {
        if (pMCard->saveToggle == 1) {
            simulatorRumbleStop(0);
            if (!mcardUpdate()) {
                return false;
            }
        } else {
            pMCard->saveToggle = 1;
            pMCard->wait = 0;
            mcardOpenDuringGame(pMCard);
            if (pMCard->saveToggle == 1) {
                if (!mcardUpdate()) {
                    return false;
                }
            }
        }
    }
    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpen.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardOpenDuringGame.s")

#pragma GLOBAL_ASM("asm/non_matchings/mcardGCN/mcardStore.s")

bool mcardUpdate(void) {
    s32 j;
    s32 i;
    s32 toggle;
    MemCardCommand command;
    s32 prevIndex;
    s32 index;
    s32 counter;

    command = MC_C_NONE;
    mCard.saveToggle = true;
    mcardOpenDuringGame(&mCard);

    if (mCard.saveToggle == true) {
        for (i = 0; i < (u32)(mCard.file.game.size + 8187) / 8188; i++) {
            mCard.file.game.writtenBlocks[i] = 1;
        }

        prevIndex = 100;
        counter = 0;
        while (true) { // ?
            if (!simulatorTestReset(false, false, false, false)) {
                return false;
            }

            mcardStore(&mCard);

            if (mCard.writeStatus != 0) {
                mCard.accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                simulatorDrawMCardText();
            }

            toggle = 0;
            j = (u32)(mCard.file.game.size + 8187) / 8188;
            for (i = 0; i < (u32)j; i++) {
                if (mCard.file.game.writtenBlocks[i] == 1) {
                    index = i;
                    toggle = true;
                    break;
                }
            }

            if (toggle != 1) {
                if (mCard.file.game.writtenConfig == 1) {
                    index = j;
                    toggle = true;
                } else if (mCard.file.changedDate == true) {
                    toggle = true;
                    index = j + 1;
                }
            }

            if (mCard.writeStatus == 0) {
                if (index == prevIndex) {
                    counter += 1;
                } else {
                    counter = 0;
                }
                prevIndex = index;
            }

            if (counter == 3) {
                mCard.isBroken = true;
                counter = 0;
                mCard.saveToggle = false;
            }

            if (mCard.saveToggle == false) {
                mCard.saveToggle = true;
                mcardOpenDuringGame(&mCard);
            }

            if (toggle != true && mCard.writeStatus == 0 || mCard.saveToggle != true) {
                if (!simulatorTestReset(false, false, true, false)) {
                    return false;
                }

                if (gpSystem->eTypeROM == SRT_ZELDA1 && mCard.saveToggle == true) {
                    do {
                        mcardMenu(&mCard, MC_M_SV12, &command);
                        if (!simulatorTestReset(false, false, true, false)) {
                            return false;
                        }
                    } while (mCard.wait == true);
                }
                break;
            }
        }

        bWrite2Card = false;
        mCard.accessType = 0;
    }

    return true;
}
