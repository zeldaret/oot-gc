/**
 * @file mcardGCN.c
 *
 * The memory card file can hold data for up to 16 games at once (although in practice at most 2 games are used,
 * for Master Quest). The file starts with a 3 block header, where the first 2 blocks contain the following data:
 *
 *   offset   size    description
 *   -----------------------------
 *   +0x0000  0x0028  timestamp, as an OSCalendarTime
 *   +0x0028  0x0004  checksum of the first block
 *   +0x002C  0x0020  comment string
 *   +0x004C  0x0020  "date string", always "ゼルダの伝説：時のオカリナ" ("The Legend of Zelda: Ocarina of Time")
 *   +0x006C  0x1800  banner TPL data
 *   +0x186C  0x1800  icon TPL data
 *   +0x306C  0x0004  checksum of the second block
 *   +0x3070  0x0040  game sizes, 4 bytes per game
 *   +0x30B0  0x0201  game names, 33 bytes per game (note that the space is too small for all 16 game names)
 *   +0x32B1  0x0040  game controller configuration, 4 bytes per game
 *
 * The third block is used as a temporary space for writing data to the file header. Before writing a header
 * block, the block data is first written to +0x4000 and read back to verify the card is working correctly.
 *
 * After the header, the file contains a sequence of games, where each game has a sequence of game data blocks
 * followed by 1 extra block. Each game data block contains a 4-byte checksum followed by 0x2000 - 4 = BLOCK_DATA_SIZE
 * bytes of data. The extra block is used as temporary space when writing similar to extra the header block above.
 *
 * Checksums are a simple sum of all 32-bit words in the block, with the exception of the checksum field itself.
 * If the checksum is 0, it is replaced with 1 to avoid having a valid block with all 0s.
 */
#include "emulator/mcardGCN.h"
#include "dolphin/card.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "stdio.h"
#include "string.h"

// Line numbers for different versions
#if VERSION == MQ_J
#define LN(mq_j, ce_j, mm_j, mm_u) mq_j
#elif VERSION == MQ_U
#define LN(mq_j, ce_j, mm_j, mm_u) (ce_j - 7)
#elif VERSION == MQ_E
#define LN(mq_j, ce_j, mm_j, mm_u) (ce_j + 16)
#elif VERSION == CE_J
#define LN(mq_j, ce_j, mm_j, mm_u) ce_j
#elif VERSION == CE_U
#define LN(mq_j, ce_j, mm_j, mm_u) ce_j
#elif VERSION == CE_E
#define LN(mq_j, ce_j, mm_j, mm_u) (ce_j + 22)
#elif VERSION == MM_J
#define LN(mq_j, ce_j, mm_j, mm_u) (mm_j)
#elif VERSION == MM_U
#define LN(mq_j, ce_j, mm_j, mm_u) (mm_u)
#elif VERSION == MM_E
#define LN(mq_j, ce_j, mm_j, mm_u) (mm_u + 75)
#endif

#if IS_MQ
#define ICON_SPEED 2
#else
#define ICON_SPEED 3
#endif

// Same as CARD_SYSTEM_BLOCK_SIZE (but signed instead of unsigned)
#define BLOCK_SIZE 0x2000
#define HEADER_SIZE (3 * BLOCK_SIZE)

#define CHECKSUM_SIZE sizeof(s32)
#define CHECKSUM1_OFFSET 0x28
#define CHECKSUM2_OFFSET 0x306C

#define TIMESTAMP_OFFSET 0
#define TIMESTAMP_SIZE 0x28

#define COMMENT_OFFSET 0x2C
#define COMMENT_SIZE 0x20

#if VERSION == MQ_J
// "This is the save data from MM/DD"
#define DATE_STRING "%d月%d日のセーブデータです"
#elif VERSION == MQ_U || VERSION == MQ_E
#define DATE_STRING "%d/%d Save Data\0"
#elif VERSION == CE_J
// "The Legend of Zelda: Ocarina of Time"
#define DATE_STRING "ゼルダの伝説：時のオカリナ"
#elif VERSION == CE_U || VERSION == CE_E
#define DATE_STRING "OCARINA OF TIME\0"
#elif IS_MM_US || IS_MM_EU
#define DATE_STRING "MAJORA'S MASK\0"
#endif

#define DATE_STRING_OFFSET 0x4C
#define DATE_STRING_SIZE 0x20

#define BANNER_TPL_OFFSET 0x6C
#define BANNER_TPL_SIZE 0x1800

#define ICON_TPL_OFFSET 0x186C
#define ICON_TPL_SIZE 0x1800

#define GAME_SIZES_OFFSET 0x3070
#define GAME_SIZES_SIZE 0x40

//! @bug The total size of all game names should be 0x210, not 0x201. This is probably a typo
//! because the next field is weirdly aligned as a result.
#define GAME_NAMES_OFFSET 0x30B0
#define GAME_NAMES_SIZE 0x0201

#define GAME_CONTROLLER_CONFIG_OFFSET 0x32B1
#define GAME_CONTROLLER_CONFIG_SIZE 0x0040

#define BLOCK_DATA_OFFSET CHECKSUM_SIZE
#define BLOCK_DATA_SIZE (0x2000 - BLOCK_DATA_OFFSET)
#define NUM_DATA_BLOCKS(gameSize) ((u32)((gameSize) + BLOCK_DATA_SIZE - 1) / BLOCK_DATA_SIZE)

// Helpers for aligning stack buffers
#define BUFFER_ALIGNMENT 0x20
#define ALIGN_BUFFER(buffer) \
    (char*)((buffer) + (BUFFER_ALIGNMENT - (s32)(buffer) % BUFFER_ALIGNMENT) % BUFFER_ALIGNMENT)

static char gMCardCardWorkArea[CARD_WORKAREA_SIZE];

MemCard mCard;
bool bNoWriteInCurrentFrame[10];
OSCalendarTime gDate;
s32 currentIdx = 0;
bool bWrite2Card;

#if VERSION == MQ_U
static MemCardError sPrevMemCardError = MC_E_NONE;
#endif

static inline bool mcardReadyFile(MemCard* pMCard);
static inline bool mcardFinishCard(MemCard* pMCard);
static inline bool mcardReadAnywhereNoTime(MemCard* pMCard, s32 offset, s32 size, char* buffer);
static inline bool mcardWriteAnywhereNoTime(MemCard* pMCard, s32 offset, u32 size, char* buffer);
static inline bool mcardFileRelease(MemCard* pMCard);

static bool mcardGCErrorHandler(MemCard* pMCard, s32 gcError) {
    switch (gcError) {
        case CARD_RESULT_READY:
            pMCard->error = MC_E_NONE;
            return true;
        case CARD_RESULT_BUSY:
            pMCard->error = MC_E_BUSY;
            return false;
        case CARD_RESULT_WRONGDEVICE:
            pMCard->error = MC_E_WRONGDEVICE;
            return false;
        case CARD_RESULT_NOCARD:
            pMCard->error = MC_E_NOCARD;
#if VERSION != MQ_J
            pMCard->isBroken = false;
#endif
            return false;
        case CARD_RESULT_NOFILE:
            pMCard->error = MC_E_NOFILE;
            return false;
        case CARD_RESULT_IOERROR:
            pMCard->error = MC_E_IOERROR;
#if VERSION != MQ_J
            pMCard->isBroken = true;
#endif
            return false;
        case CARD_RESULT_BROKEN:
            pMCard->error = MC_E_BROKEN;
            return false;
        case CARD_RESULT_EXIST:
            pMCard->error = MC_E_EXIST;
            return false;
        case CARD_RESULT_NOENT:
            pMCard->error = MC_E_NOENT;
            return false;
        case CARD_RESULT_INSSPACE:
            pMCard->error = MC_E_INSSPACE;
            return false;
        case CARD_RESULT_NOPERM:
            pMCard->error = MC_E_NOPERM;
            return false;
        case CARD_RESULT_LIMIT:
            pMCard->error = MC_E_LIMIT;
            return false;
        case CARD_RESULT_NAMETOOLONG:
            pMCard->error = MC_E_NAMETOOLONG;
            return false;
        case CARD_RESULT_ENCODING:
            pMCard->error = MC_E_ENCODING;
            return false;
        case CARD_RESULT_CANCELED:
            pMCard->error = MC_E_CANCELED;
            return false;
        case CARD_RESULT_FATAL_ERROR:
            pMCard->error = MC_E_FATAL;
            return false;
        default:
            pMCard->error = MC_E_UNKNOWN;
            return false;
    }
}

static bool mcardCalculateChecksum(MemCard* pMCard, s32* checksum) {
    s32 i;

    if (mCard.saveToggle == true) {
        *checksum = 0;
        for (i = 1; i != BLOCK_SIZE / sizeof(s32); i++) {
            *checksum += ((s32*)pMCard->writeBuffer)[i];
        }

        if (*checksum == 0) {
            *checksum = 1;
        }
    }

    return true;
}

static bool mcardCalculateChecksumFileBlock1(MemCard* pMCard, s32* checksum) {
    s32 i;

    if (mCard.saveToggle == true) {
        *checksum = 0;

        for (i = 0; i != BLOCK_SIZE / sizeof(s32); i++) {
            if (i != CHECKSUM1_OFFSET / sizeof(s32)) {
                *checksum += ((s32*)pMCard->writeBuffer)[i];
            }
        }

        if (*checksum == 0) {
            *checksum = 1;
        }
    }

    return true;
}

static bool mcardCalculateChecksumFileBlock2(MemCard* pMCard, s32* checksum) {
    s32 i;

    if (mCard.saveToggle == true) {
        *checksum = 0;

        for (i = 0; i != BLOCK_SIZE / sizeof(s32); i++) {
            if (i != (CHECKSUM2_OFFSET - BLOCK_SIZE) / sizeof(s32)) {
                *checksum += ((s32*)pMCard->writeBuffer)[i];
            }
        }

        if (*checksum == 0) {
            *checksum = 1;
        }
    }

    return true;
}

static bool mcardSaveChecksumFileHeader(MemCard* pMCard, char* buffer) {
    char buffer2[BLOCK_SIZE];
    s32 checksum;
    s32 pad[2];

    memcpy(buffer2, pMCard->writeBuffer, BLOCK_SIZE);

    memcpy(pMCard->writeBuffer, buffer, BLOCK_SIZE);
    mcardCalculateChecksumFileBlock1(pMCard, &checksum);
    memcpy(buffer + CHECKSUM1_OFFSET, &checksum, CHECKSUM_SIZE);

    memcpy(pMCard->writeBuffer, buffer + BLOCK_SIZE, BLOCK_SIZE);
    mcardCalculateChecksumFileBlock2(pMCard, &checksum);
    memcpy(buffer + CHECKSUM2_OFFSET, &checksum, CHECKSUM_SIZE);

    memcpy(pMCard->writeBuffer, buffer2, BLOCK_SIZE);

    return true;
}

static inline bool mcardGetFileTime(MemCard* pMCard, OSCalendarTime* time) {
    char buffer[0x200 + BUFFER_ALIGNMENT];

    if (pMCard->saveToggle == true) {
        if (mcardGCErrorHandler(pMCard, CARDRead(&pMCard->file.fileInfo, ALIGN_BUFFER(buffer), 0x200, 0)) != true) {
            return false;
        }

        memcpy(time, ALIGN_BUFFER(buffer) + TIMESTAMP_OFFSET, TIMESTAMP_SIZE);
    }

    return true;
}

static bool mcardReplaceFileBlock(MemCard* pMCard, s32 index) {
    s32 checksum1;
    s32 checksum2;
    char buffer[BLOCK_SIZE];
    s32 pad[2];

    memcpy(buffer, pMCard->writeBuffer, BLOCK_SIZE);

    if (!mcardReadAnywhereNoTime(pMCard, 2 * BLOCK_SIZE, BLOCK_SIZE, pMCard->writeBuffer)) {
        return false;
    }

    if (index == 0) {
        memcpy(&checksum1, pMCard->writeBuffer + CHECKSUM1_OFFSET, CHECKSUM_SIZE);
        mcardCalculateChecksumFileBlock1(pMCard, &checksum2);
    } else {
        memcpy(&checksum1, pMCard->writeBuffer + CHECKSUM2_OFFSET - BLOCK_SIZE, CHECKSUM_SIZE);
        mcardCalculateChecksumFileBlock2(pMCard, &checksum2);
    }

    if (checksum1 != checksum2) {
        pMCard->error = MC_E_CHECKSUM;
        memcpy(pMCard->writeBuffer, buffer, BLOCK_SIZE);
        return false;
    }

#if VERSION != MQ_J
    simulatorPrepareMessage(S_M_CARD_SV09);
#endif

    if (!mcardWriteAnywhereNoTime(pMCard, index * BLOCK_SIZE, BLOCK_SIZE, pMCard->writeBuffer)) {
        memcpy(pMCard->writeBuffer, buffer, BLOCK_SIZE);
        return false;
    }

#if VERSION != MQ_J
    if (index == 0) {
        mcardGetFileTime(pMCard, &pMCard->file.time);
    }
#endif

    return true;
}

static bool mcardCheckChecksumFileHeader(MemCard* pMCard, char* buffer) {
    s32 pad2;
    s32 checksum;
    char buffer2[BLOCK_SIZE];
    bool toggle = true;
    s32 pad[2];

    memcpy(buffer2, pMCard->writeBuffer, BLOCK_SIZE);
    memcpy(pMCard->writeBuffer, buffer, BLOCK_SIZE);

    mcardCalculateChecksumFileBlock1(pMCard, &checksum);

    if (checksum != *(s32*)(pMCard->writeBuffer + CHECKSUM1_OFFSET)) {
        toggle = false;
        if (!mcardReplaceFileBlock(pMCard, 0)) {
            return false;
        }
    }
    memcpy(pMCard->writeBuffer, buffer + BLOCK_SIZE, BLOCK_SIZE);

    mcardCalculateChecksumFileBlock2(pMCard, &checksum);

    if (checksum != *(s32*)(pMCard->writeBuffer + CHECKSUM2_OFFSET - BLOCK_SIZE)) {
        if (toggle == true) {
            if (!mcardReplaceFileBlock(pMCard, 1)) {
                return false;
            }
        } else {
            pMCard->error = MC_E_CHECKSUM;
            return false;
        }
    }
    memcpy(pMCard->writeBuffer, buffer2, BLOCK_SIZE);

    return true;
}

static bool mcardVerifyChecksumFileHeader(MemCard* pMCard) {
    char* buffer;

    if (!mcardReadyFile(pMCard)) {
        return false;
    }
    if (!xlHeapTake((void**)&buffer, HEADER_SIZE | 0x30000000)) {
        return false;
    }

    if (!mcardReadAnywhereNoTime(pMCard, 0, HEADER_SIZE, buffer)) {
        if (!xlHeapFree((void**)&buffer)) {
            return false;
        }
        mcardFinishCard(pMCard);
        return false;
    }

    DCInvalidateRange(buffer, HEADER_SIZE);

    if (!mcardCheckChecksumFileHeader(pMCard, buffer)) {
        if (!xlHeapFree((void**)&buffer)) {
            return false;
        }
        mcardFinishCard(pMCard);
        return false;
    }

    if (!xlHeapFree((void**)&buffer)) {
        return false;
    }
    mcardFinishCard(pMCard);
    return true;
}

static inline bool mcardCompareName(char* name1, char* name2) {
    if (strcmp(name1, name2) == 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool mcardCopyName(char* name1, char* name2) {
    if (mCard.saveToggle == true) {
        strcpy(name1, name2);
    }
}

static bool mcardPoll(MemCard* pMCard) {
    if (mCard.saveToggle == true) {
        mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
        if (pMCard->error != MC_E_BUSY && pMCard->error != MC_E_NONE) {
            return false;
        }
        while (pMCard->error == MC_E_BUSY) {
            mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
            if (pMCard->error != MC_E_BUSY && pMCard->error != MC_E_NONE) {
                return false;
            }

            if (pMCard->pPollFunction != NULL) {
#if VERSION != MQ_J
                if (!SIMULATOR_TEST_RESET(false, false, false, false)) {
                    return false;
                }
#endif
                pMCard->pPollFunction();
            }
        }
    }

    return true;
}

static bool mcardReadyCard(MemCard* pMCard) {
    s32 i;
    s32 sectorSize;

    if (mCard.saveToggle == true) {
        mcardGCErrorHandler(pMCard, CARDProbeEx(pMCard->slot, &pMCard->cardSize, &sectorSize));

#if VERSION != MQ_J
        if (pMCard->isBroken == true && pMCard->error != MC_E_NOCARD) {
            pMCard->error = MC_E_IOERROR;
            return false;
        }
#endif

        while (pMCard->error == MC_E_BUSY) {
            mcardGCErrorHandler(pMCard, CARDProbeEx(pMCard->slot, &pMCard->cardSize, &sectorSize));
        }

        if (pMCard->error != MC_E_NONE) {
            for (i = 0; i < 10; i++) {
                if (mcardGCErrorHandler(pMCard, CARDProbeEx(pMCard->slot, &pMCard->cardSize, &sectorSize)) == true) {
                    break;
                }
            }
            if (i == 10) {
                return false;
            }
        }

        if (sectorSize != BLOCK_SIZE) {
            pMCard->error = MC_E_SECTOR_SIZE_INVALID;
            return false;
        }

        mcardGCErrorHandler(pMCard, CARDMount(pMCard->slot, gMCardCardWorkArea, NULL));
        if (pMCard->error != MC_E_NONE && pMCard->error != MC_E_BROKEN && pMCard->error != MC_E_ENCODING) {
            CARDUnmount(pMCard->slot);
            return false;
        }

        mcardGCErrorHandler(pMCard, CARDCheck(pMCard->slot));
        if (pMCard->error != MC_E_NONE) {
            return false;
        }
    }

    return true;
}

static inline bool mcardTimeCheck(MemCard* pMCard) {
    OSCalendarTime time;

    if (pMCard->saveToggle == true) {
        if (!mcardGetFileTime(pMCard, &time)) {
            return false;
        }

        if (memcmp(&time, &pMCard->file.time, TIMESTAMP_SIZE) != 0) {
            pMCard->error = MC_E_TIME_WRONG;
            return false;
        }
    }

    return true;
}

static inline bool mcardFinishCard(MemCard* pMCard) {
    if (pMCard->saveToggle == true) {
        if (pMCard->file.fileInfo.chan != -1) {
            CARDClose(&pMCard->file.fileInfo);
        }
        CARDUnmount(pMCard->slot);
    }

    return true;
}

static inline bool mcardReadyFile(MemCard* pMCard) {
    if (pMCard->saveToggle == true) {
        if (!mcardReadyCard(pMCard)) {
            return false;
        }
        if (mcardGCErrorHandler(pMCard, CARDOpen(pMCard->slot, pMCard->file.name, &pMCard->file.fileInfo)) != true) {
            CARDUnmount(pMCard->slot);
            return false;
        }
    }

    return true;
}

static inline void mcardFinishFile(MemCard* pMCard) {
    pMCard->writeToggle = true;
    pMCard->writeStatus = false;

    mcardFinishCard(pMCard);

    if (pMCard->writeIndex < NUM_DATA_BLOCKS(pMCard->file.game.size)) {
        pMCard->file.game.writtenBlocks[pMCard->writeIndex] = true;
    } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 1) {
        pMCard->file.changedDate = true;
    } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 2) {
        pMCard->file.game.writtenConfig = true;
    }
}

static inline bool mcardReadAnywhereNoTime(MemCard* pMCard, s32 offset, s32 size, char* buffer) {
    if (mCard.saveToggle == true) {
        if (mcardGCErrorHandler(pMCard, CARDReadAsync(&pMCard->file.fileInfo, buffer, size, offset, NULL)) != true) {
            return false;
        }
        if (mcardPoll(pMCard) != true) {
            return false;
        }
        DCInvalidateRange(buffer, size);
    }

    return true;
}

static inline bool mcardWriteAnywhereNoTime(MemCard* pMCard, s32 offset, u32 size, char* buffer) {
    if (mCard.saveToggle == true) {
        DCStoreRange(buffer, size);
        if (mcardGCErrorHandler(pMCard, CARDWriteAsync(&pMCard->file.fileInfo, buffer, size, offset, NULL)) != true) {
            return false;
        }
        pMCard->pollSize = size;
        pMCard->pPollFunction = simulatorMCardPollDrawBar;
        pMCard->pollPrevBytes = CARDGetXferredBytes(pMCard->slot);
        if (mcardPoll(pMCard) != true) {
            pMCard->pPollFunction = NULL;
            return false;
        }
        pMCard->pPollFunction = NULL;
    }

    return true;
}

static bool mcardReadAnywhere(MemCard* pMCard, s32 offset, s32 size, char* buffer) {
    if (mCard.saveToggle == true) {
        if (!mcardTimeCheck(pMCard)) {
            return false;
        }
        if (mcardGCErrorHandler(pMCard, CARDReadAsync(&pMCard->file.fileInfo, buffer, size, offset, NULL)) != true) {
            return false;
        }
        if (mcardPoll(pMCard) != true) {
            return false;
        }
        DCInvalidateRange(buffer, size);
    }

    return true;
}

static bool mcardWriteAnywhere(MemCard* pMCard, s32 offset, u32 size, char* buffer) {
    if (mCard.saveToggle == true) {
        if (!mcardTimeCheck(pMCard)) {
            return false;
        }
        DCStoreRange(buffer, size);
        if (mcardGCErrorHandler(pMCard, CARDWriteAsync(&pMCard->file.fileInfo, buffer, size, offset, NULL)) != true) {
            return false;
        }
        pMCard->pollSize = size;
        pMCard->pPollFunction = simulatorMCardPollDrawBar;
        pMCard->pollPrevBytes = CARDGetXferredBytes(pMCard->slot);
        if (mcardPoll(pMCard) != true) {
            pMCard->pPollFunction = NULL;
            return false;
        }
        pMCard->pPollFunction = NULL;
    }

    return true;
}

static bool mcardWriteAnywherePartial(MemCard* pMCard, s32 offset, s32 size, char* buffer, s32 partialOffset,
                                      s32 totalSize) {
    if (mCard.saveToggle == true) {
        if (!mcardTimeCheck(pMCard)) {
            return false;
        }
        DCStoreRange(buffer, size);
        if (mcardGCErrorHandler(pMCard, CARDWriteAsync(&pMCard->file.fileInfo, buffer, size, offset, NULL)) != true) {
            return false;
        }
        pMCard->pollSize = totalSize;
        pMCard->pPollFunction = simulatorMCardPollDrawBar;
        if (partialOffset == 0) {
            pMCard->pollPrevBytes = CARDGetXferredBytes(pMCard->slot);
        }
        if (mcardPoll(pMCard) != true) {
            pMCard->pPollFunction = NULL;
            return false;
        }
        pMCard->pPollFunction = NULL;
    }

    return true;
}

static bool mcardReadFileHeader(MemCard* pMCard) {
    char buffer[HEADER_SIZE + BUFFER_ALIGNMENT];

    if (pMCard->saveToggle == true) {
        strcpy(pMCard->pollMessage, "Reading File Header");

        if (!mcardReadAnywhere(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer))) {
            return false;
        }

        memcpy(pMCard->file.gameSize, ALIGN_BUFFER(buffer) + GAME_SIZES_OFFSET, GAME_SIZES_SIZE);
        memcpy(pMCard->file.gameName, ALIGN_BUFFER(buffer) + GAME_NAMES_OFFSET, GAME_NAMES_SIZE);
        memcpy(pMCard->file.gameConfigIndex, ALIGN_BUFFER(buffer) + GAME_CONTROLLER_CONFIG_OFFSET,
               GAME_CONTROLLER_CONFIG_SIZE);
    }

    return true;
}

static bool mcardWriteFileHeader(MemCard* pMCard) {
    char buffer[HEADER_SIZE + BUFFER_ALIGNMENT];

    if (pMCard->saveToggle == true) {
        strcpy(pMCard->pollMessage, "Reading File Header");

        if (!mcardReadAnywhere(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer))) {
            return false;
        }

        memcpy(ALIGN_BUFFER(buffer) + GAME_SIZES_OFFSET, pMCard->file.gameSize, GAME_SIZES_SIZE);
        memcpy(ALIGN_BUFFER(buffer) + GAME_NAMES_OFFSET, pMCard->file.gameName, GAME_NAMES_SIZE);
        memcpy(ALIGN_BUFFER(buffer) + GAME_CONTROLLER_CONFIG_OFFSET, pMCard->file.gameConfigIndex,
               GAME_CONTROLLER_CONFIG_SIZE);

        mcardSaveChecksumFileHeader(pMCard, ALIGN_BUFFER(buffer));
        strcpy(pMCard->pollMessage, "Writing File Header");

        if (!mcardWriteAnywherePartial(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer), 0, HEADER_SIZE)) {
            return false;
        }
    }

    return true;
}

static bool mcardReadFileHeaderInitial(MemCard* pMCard) {
    char buffer[HEADER_SIZE + BUFFER_ALIGNMENT];

    if (pMCard->saveToggle == true) {
        if (!mcardReadAnywhereNoTime(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer))) {
            return false;
        }

        memcpy(pMCard->file.gameSize, ALIGN_BUFFER(buffer) + GAME_SIZES_OFFSET, GAME_SIZES_SIZE);
        memcpy(pMCard->file.gameName, ALIGN_BUFFER(buffer) + GAME_NAMES_OFFSET, GAME_NAMES_SIZE);
        memcpy(pMCard->file.gameConfigIndex, ALIGN_BUFFER(buffer) + GAME_CONTROLLER_CONFIG_OFFSET,
               GAME_CONTROLLER_CONFIG_SIZE);
        memcpy(&pMCard->file.time, ALIGN_BUFFER(buffer) + TIMESTAMP_OFFSET, TIMESTAMP_SIZE);
    }

    return true;
}

static bool mcardWriteFileHeaderInitial(MemCard* pMCard) {
    char buffer[HEADER_SIZE + BUFFER_ALIGNMENT];

    if (pMCard->saveToggle == true) {
        strcpy(pMCard->pollMessage, "Writing File Header");

        if (!mcardReadAnywhereNoTime(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer))) {
            return false;
        }

        memcpy(ALIGN_BUFFER(buffer) + GAME_SIZES_OFFSET, pMCard->file.gameSize, GAME_SIZES_SIZE);
        memcpy(ALIGN_BUFFER(buffer) + GAME_NAMES_OFFSET, pMCard->file.gameName, GAME_NAMES_SIZE);
        memcpy(ALIGN_BUFFER(buffer) + GAME_CONTROLLER_CONFIG_OFFSET, pMCard->file.gameConfigIndex,
               GAME_CONTROLLER_CONFIG_SIZE);
        memcpy(ALIGN_BUFFER(buffer) + TIMESTAMP_OFFSET, &pMCard->file.time, TIMESTAMP_SIZE);

        mcardSaveChecksumFileHeader(pMCard, ALIGN_BUFFER(buffer));

        if (!mcardWriteAnywhereNoTime(pMCard, 0, HEADER_SIZE, ALIGN_BUFFER(buffer))) {
            return false;
        }
    }

    return true;
}

static bool mcardWriteBufferAsynch(MemCard* pMCard, s32 offset) {
    OSCalendarTime date;

    // Unused strings that are probably part of mcardReadCardHeader and mcardWriteCardHeader,
    // put here for data ordering purposes
    (void)"Reading Card Header";
    (void)"Writing Card Header";

    if (mCard.saveToggle == true) {
        if (mCard.writeToggle == true) {
            OSTicksToCalendarTime(OSGetTime(), &date);
#if IS_OOT_EU || IS_MM
            pMCard->file.changedDate = true;
#else
            if (date.mon != pMCard->file.time.mon || date.mday != pMCard->file.time.mday) {
                pMCard->file.changedDate = true;
            }
#endif
            mCard.writeToggle = false;
            if (!mcardTimeCheck(pMCard)) {
                mCard.writeToggle = true;
                return false;
            }
            DCStoreRange(pMCard->writeBuffer, BLOCK_SIZE);
            if (mcardGCErrorHandler(pMCard, CARDWriteAsync(&pMCard->file.fileInfo, pMCard->writeBuffer, BLOCK_SIZE,
                                                           offset, NULL)) != true) {
                mCard.writeToggle = true;
                return false;
            }
        } else {
            mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
            if (pMCard->error != MC_E_BUSY) {
                mCard.writeToggle = true;
                if (pMCard->error != MC_E_NONE) {
                    return false;
                }
            }
        }
    }

    return true;
}

static bool mcardReadBufferAsynch(MemCard* pMCard, s32 offset) {
    if (mCard.saveToggle == true) {
        if (mCard.writeToggle == true) {
            mCard.writeToggle = false;
            if (!mcardTimeCheck(pMCard)) {
                mCard.writeToggle = true;
                return false;
            }
            if (mcardGCErrorHandler(pMCard, CARDReadAsync(&pMCard->file.fileInfo, pMCard->readBuffer, BLOCK_SIZE,
                                                          offset, NULL)) != true) {
                mCard.writeToggle = true;
                return false;
            }
        } else {
            mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
            if (pMCard->error != MC_E_BUSY) {
                mCard.writeToggle = true;
                if (pMCard->error != MC_E_NONE) {
                    return false;
                }
            }
        }
    }

    return true;
}

static inline bool mcardWriteConfigPrepareWriteBuffer(MemCard* pMCard) {
    s32 checksum;

    if (!mcardTimeCheck(pMCard)) {
        mCard.writeToggle = true;
        return false;
    }
    if (!mcardReadAnywhere(pMCard, BLOCK_SIZE, BLOCK_SIZE, pMCard->writeBuffer)) {
        mCard.writeToggle = true;
        return false;
    }

    DCInvalidateRange(pMCard->writeBuffer, BLOCK_SIZE);
    memcpy(pMCard->writeBuffer + GAME_CONTROLLER_CONFIG_OFFSET - BLOCK_SIZE, pMCard->file.gameConfigIndex,
           GAME_CONTROLLER_CONFIG_SIZE);
    mcardCalculateChecksumFileBlock2(pMCard, &checksum);
    memcpy(pMCard->writeBuffer + CHECKSUM2_OFFSET - BLOCK_SIZE, &checksum, CHECKSUM_SIZE);
    DCStoreRange(pMCard->writeBuffer, BLOCK_SIZE);

    return true;
}

static bool mcardWriteConfigAsynch(MemCard* pMCard) {
    if (mCard.saveToggle == true) {
        if (mCard.writeToggle == true) {
            mCard.writeToggle = false;
            if (!mcardTimeCheck(pMCard)) {
                mCard.writeToggle = true;
                return false;
            }
            DCStoreRange(pMCard->writeBuffer, BLOCK_SIZE);
            if (mcardGCErrorHandler(pMCard, CARDWriteAsync(&pMCard->file.fileInfo, pMCard->writeBuffer, BLOCK_SIZE,
                                                           BLOCK_SIZE, NULL)) != true) {
                mCard.writeToggle = true;
                return false;
            }
        } else {
            mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
            if (pMCard->error != MC_E_BUSY) {
                mCard.writeToggle = true;
                if (pMCard->error != MC_E_NONE) {
                    return false;
                }
            }
        }
    }

    return true;
}

static bool mcardWriteTimePrepareWriteBuffer(MemCard* pMCard) {
    char dateString[32];
    s32 checksum;

    if (!mcardTimeCheck(pMCard)) {
        mCard.writeToggle = true;
        return false;
    }
    if (!mcardReadAnywhere(pMCard, 0, BLOCK_SIZE, pMCard->writeBuffer)) {
        mCard.writeToggle = true;
        return false;
    }

    DCInvalidateRange(pMCard->writeBuffer, BLOCK_SIZE);

    OSTicksToCalendarTime(OSGetTime(), &gDate);

#if VERSION == MQ_J || VERSION == MQ_U
    sprintf(dateString, DATE_STRING, gDate.mon + 1, gDate.mday);
#elif VERSION == MQ_E
    if (gLanguage == 1) {
        sprintf(dateString, "%d/%d Speicherstand\0", gDate.mon + 1, gDate.mday);
    } else if (gLanguage == 2) {
        sprintf(dateString, "Sauvegarde du %d/%d\0", gDate.mday, gDate.mon + 1);
    } else if (gLanguage == 3) {
        sprintf(dateString, "Datos guardados el %d/%d\0", gDate.mday, gDate.mon + 1);
    } else if (gLanguage == 4) {
        sprintf(dateString, "Dati Salvati %d/%d\0", gDate.mday, gDate.mon + 1);
    } else {
        sprintf(dateString, DATE_STRING, gDate.mon + 1, gDate.mday);
    }
    PAD_STACK();
#elif IS_MM_JP
    switch (gpSystem->eTypeROM) {
        case SRT_ZELDA1:
            // "Ocarina of Time"
            sprintf(dateString, "時のオカリナ");
            break;
        case SRT_ZELDA2:
            // "The Legend of Zelda: Majora's Mask"
            sprintf(dateString, "ゼルダの伝説：ムジュラの仮面");
            break;
        default:
            // "This is the save data from %d month %d day"
            sprintf(dateString, "%d月%d日のセーブデータです", gDate.mon + 1, gDate.mday);
            break;
    }
#else
    sprintf(dateString, DATE_STRING);
#endif

    memcpy(pMCard->writeBuffer + TIMESTAMP_OFFSET, (void*)&gDate, TIMESTAMP_SIZE);
    memcpy(pMCard->writeBuffer + DATE_STRING_OFFSET, dateString, DATE_STRING_SIZE);

    mcardCalculateChecksumFileBlock1(pMCard, &checksum);
    memcpy(pMCard->writeBuffer + CHECKSUM1_OFFSET, &checksum, CHECKSUM_SIZE);

    DCStoreRange(pMCard->writeBuffer, BLOCK_SIZE);

#if IS_MM_JP
    NO_INLINE();
    PAD_STACK();
#endif
    return true;
}

static bool mcardWriteTimeAsynch(MemCard* pMCard) {
    if (mCard.saveToggle == true) {
        if (mCard.writeToggle == true) {
            mCard.writeToggle = false;
            if (!mcardTimeCheck(pMCard)) {
                mCard.writeToggle = true;
                return false;
            }

            pMCard->file.time = gDate;

            DCStoreRange(pMCard->writeBuffer, BLOCK_SIZE);
            if (mcardGCErrorHandler(
                    pMCard, CARDWriteAsync(&pMCard->file.fileInfo, pMCard->writeBuffer, BLOCK_SIZE, 0, NULL)) != true) {
                mCard.writeToggle = true;
                return false;
            }
        } else {
            mcardGCErrorHandler(pMCard, CARDGetResultCode(pMCard->slot));
            if (pMCard->error != MC_E_BUSY) {
                mCard.writeToggle = true;
                if (pMCard->error != MC_E_NONE) {
                    return false;
                }
            }
        }
    }

    return true;
}

static inline bool mcardReplaceBlock(MemCard* pMCard, s32 index) {
    s32 checksum1;
    s32 checksum2;

    if (!mcardReadAnywhere(
            pMCard, pMCard->file.game.offset + HEADER_SIZE + NUM_DATA_BLOCKS(pMCard->file.game.size) * BLOCK_SIZE,
            BLOCK_SIZE, pMCard->writeBuffer)) {
        return false;
    }

    memcpy(&checksum1, pMCard->writeBuffer, CHECKSUM_SIZE);
    mcardCalculateChecksum(pMCard, &checksum2);
    if (checksum1 != checksum2) {
        return false;
    }

    mCard.accessType = 2;
    simulatorPrepareMessage(S_M_CARD_SV09);

    if (!mcardWriteAnywhere(pMCard, pMCard->file.game.offset + HEADER_SIZE + index * BLOCK_SIZE, BLOCK_SIZE,
                            pMCard->writeBuffer)) {
        return false;
    }

    return true;
}

bool mcardReadGameData(MemCard* pMCard) {
    s32 checksum1;
    s32 checksum2;
    s32 i;
    bool toggle;
    s32 pad;

    toggle = true;
    if (pMCard->saveToggle == true) {
        strcpy(pMCard->pollMessage, "Reading Game Data");

        for (i = 0; i < NUM_DATA_BLOCKS(pMCard->file.game.size); i++) {
            if (!mcardReadAnywhere(pMCard, pMCard->file.game.offset + HEADER_SIZE + BLOCK_SIZE * i, BLOCK_SIZE,
                                   pMCard->writeBuffer)) {
                return false;
            }

            memcpy(&checksum1, pMCard->writeBuffer, CHECKSUM_SIZE);
            mcardCalculateChecksum(pMCard, &checksum2);
            if (checksum1 != checksum2) {
                if (toggle == true) {
                    toggle = false;
                    if (!mcardReplaceBlock(pMCard, i)) {
                        pMCard->error = MC_E_CHECKSUM;
                        return false;
                    }
                } else {
                    pMCard->error = MC_E_CHECKSUM;
                    return false;
                }
            }

            if (i < NUM_DATA_BLOCKS(pMCard->file.game.size) - 1) {
                memcpy(&pMCard->file.game.buffer[i * BLOCK_DATA_SIZE], pMCard->writeBuffer + BLOCK_DATA_OFFSET,
                       BLOCK_DATA_SIZE);
            } else {
                memcpy(&pMCard->file.game.buffer[i * BLOCK_DATA_SIZE], pMCard->writeBuffer + BLOCK_DATA_OFFSET,
                       pMCard->file.game.size - i * BLOCK_DATA_SIZE);
            }
        }
    }

    return true;
}

static inline bool mcardWriteGameData(MemCard* pMCard, s32 offset) {
    if (pMCard->saveToggle == true) {
        if (!mcardWriteBufferAsynch(pMCard, HEADER_SIZE + pMCard->file.game.offset + offset)) {
            return false;
        }
    }

    return true;
}

static inline bool mcardWriteGameDataWait(MemCard* pMCard) {
    s32 checksum;
    s32 i;

    if (pMCard->saveToggle == true) {
        strcpy(pMCard->pollMessage, "Writing Game Data");

        for (i = 0; i < NUM_DATA_BLOCKS(pMCard->file.game.size); i++) {
            if (i < NUM_DATA_BLOCKS(pMCard->file.game.size) - 1) {
                memcpy(pMCard->writeBuffer + BLOCK_DATA_OFFSET, &pMCard->file.game.buffer[i * BLOCK_DATA_SIZE],
                       BLOCK_DATA_SIZE);
            } else {
                memcpy(pMCard->writeBuffer + BLOCK_DATA_OFFSET, &pMCard->file.game.buffer[i * BLOCK_DATA_SIZE],
                       pMCard->file.game.size - i * BLOCK_DATA_SIZE);
            }
            mcardCalculateChecksum(pMCard, &checksum);
            memcpy(pMCard->writeBuffer, &checksum, CHECKSUM_SIZE);
            if (!mcardWriteAnywherePartial(pMCard, pMCard->file.game.offset + HEADER_SIZE + i * BLOCK_SIZE, BLOCK_SIZE,
                                           pMCard->writeBuffer, i * BLOCK_SIZE,
                                           NUM_DATA_BLOCKS(pMCard->file.game.size) * BLOCK_SIZE)) {
                return false;
            }
        }
    }

    return true;
}

bool mcardWriteGameDataReset(MemCard* pMCard) {
    if (pMCard->saveToggle == true) {
        while (!mCard.writeToggle) {
            mcardWriteBufferAsynch(pMCard, pMCard->file.game.offset + HEADER_SIZE);
        }
    }

    return true;
}

bool mcardReInit(MemCard* pMCard) {
    pMCard->saveToggle = true;
    mcardFileRelease(pMCard);
    mcardGameRelease(pMCard);

    pMCard->error = MC_E_NONE;
    pMCard->slot = 0;
    pMCard->wait = false;
    pMCard->pPollFunction = NULL;
    pMCard->writeToggle = true;

    if (pMCard->writeBuffer != NULL) {
        if (!xlHeapFree((void**)&pMCard->writeBuffer)) {
            return false;
        }
    }

    if (pMCard->readBuffer != NULL) {
        if (!xlHeapFree((void**)&pMCard->readBuffer)) {
            return false;
        }
    }

    if (!xlHeapTake((void**)&pMCard->writeBuffer, BLOCK_SIZE | 0x30000000)) {
        return false;
    }

    if (!xlHeapTake((void**)&pMCard->readBuffer, BLOCK_SIZE | 0x30000000)) {
        return false;
    }

    return true;
}

bool mcardInit(MemCard* pMCard) {
    CARDInit();

    if (!pMCard->bufferCreated) {
        pMCard->file.game.buffer = NULL;
    }

#if IS_OOT
    pMCard->file.game.writtenBlocks = NULL;
#endif
    pMCard->writeBuffer = NULL;
    pMCard->readBuffer = NULL;
    mcardReInit(pMCard);

    return true;
}

bool mcardFileSet(MemCard* pMCard, char* name) {
    s32 i;

    if (pMCard->saveToggle == true) {
        mcardCopyName(pMCard->file.name, name);

        pMCard->file.changedDate = false;
        pMCard->file.fileSize = HEADER_SIZE;
        if (mcardReadyFile(pMCard) == true) {
            if (!pMCard->gameIsLoaded) {
                if (!mcardReadFileHeaderInitial(pMCard)) {
                    mcardFinishCard(pMCard);

#if VERSION == MQ_U
                    if (pMCard->error == MC_E_NOCARD || sPrevMemCardError != pMCard->error) {
                        sPrevMemCardError = pMCard->error;
                        mCard.isBroken = false;
                    } else if (pMCard->isBroken == true) {
                        sPrevMemCardError = pMCard->error;
                        pMCard->error = MC_E_IOERROR;
                        return false;
                    }
#elif VERSION > MQ_U
                    if (pMCard->error == MC_E_NOCARD) {
                        mCard.isBroken = false;
                    } else if (pMCard->isBroken == true) {
                        pMCard->error = MC_E_IOERROR;
                        return false;
                    }
#endif
                    return false;
                }
            } else if (!mcardReadFileHeader(pMCard)) {
                mcardFinishCard(pMCard);
                if (pMCard->error == MC_E_TIME_WRONG) {
                    mcardVerifyChecksumFileHeader(pMCard);
                    if (pMCard->error == MC_E_NONE) {
                        pMCard->error = MC_E_TIME_WRONG;
                    }
                }

#if VERSION == MQ_U
                if (pMCard->error == MC_E_NOCARD || sPrevMemCardError != pMCard->error) {
                    sPrevMemCardError = pMCard->error;
                    mCard.isBroken = false;
                } else if (pMCard->isBroken == true) {
                    sPrevMemCardError = pMCard->error;
                    pMCard->error = MC_E_IOERROR;
                    return false;
                }
#elif VERSION > MQ_U
                if (pMCard->error == MC_E_NOCARD) {
                    mCard.isBroken = false;
                } else if (pMCard->isBroken == true) {
                    pMCard->error = MC_E_IOERROR;
                    return false;
                }
#endif
                return false;
            }

            pMCard->file.gameOffset[0] = 0;
            pMCard->file.numberOfGames = 0;
            if (pMCard->file.gameSize[0] != 0) {
                pMCard->file.numberOfGames = 1;
            }

            for (i = 1; i < 16; i++) {
                if (pMCard->file.gameSize[i] != 0) {
                    pMCard->file.numberOfGames++;
                    pMCard->file.gameOffset[i] = NUM_DATA_BLOCKS(pMCard->file.gameSize[i - 1]) * BLOCK_SIZE +
                                                 BLOCK_SIZE + pMCard->file.gameOffset[i - 1];
                    pMCard->file.fileSize += NUM_DATA_BLOCKS(pMCard->file.gameSize[i]) * BLOCK_SIZE + BLOCK_SIZE;
                }
            }

            pMCard->file.currentGame = 16;
            mcardFinishCard(pMCard);

#if VERSION == MQ_U
            if (pMCard->isBroken == true) {
                sPrevMemCardError = pMCard->error;
                pMCard->error = MC_E_IOERROR;
                return false;
            }
#elif VERSION > MQ_U
            if (pMCard->isBroken == true) {
                pMCard->error = MC_E_IOERROR;
                return false;
            }
#endif

            return true;
        }
    }

#if VERSION == MQ_U
    if (pMCard->error == MC_E_NOCARD || sPrevMemCardError != pMCard->error) {
        sPrevMemCardError = pMCard->error;
        mCard.isBroken = false;
    } else if (pMCard->isBroken == true) {
        sPrevMemCardError = pMCard->error;
        pMCard->error = MC_E_IOERROR;
        return false;
    }
#elif VERSION > MQ_U
    if (pMCard->error == MC_E_NOCARD) {
        mCard.isBroken = false;
    } else if (pMCard->isBroken == true) {
        pMCard->error = MC_E_IOERROR;
        return false;
    }
#endif

    return false;
}

static bool mcardGameSetNoSave(MemCard* pMCard, s32 size) {
    pMCard->file.game.size = size;

#if IS_OOT
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        pMCard->soundToggle = true;
    }
#endif

    pMCard->bufferCreated = true;

    if (pMCard->file.game.buffer != NULL) {
        if (!xlHeapFree((void**)&pMCard->file.game.buffer)) {
            return false;
        }
    }

    if (!xlHeapTake((void**)&pMCard->file.game.buffer, size)) {
        return false;
    }

    memset(pMCard->file.game.buffer, 0, size);

#if IS_MM
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        pMCard->soundToggle = true;
    } else if (gpSystem->eTypeROM == SRT_ZELDA2) {
        s32* testInt = (s32*)(pMCard->file.game.buffer + 0x18000);
#if IS_MM_JP || IS_MM_EU
        char testChar;
#endif

#if IS_MM_EU
        testInt = (s32*)(pMCard->file.game.buffer + 0x18000);
        testChar = *testInt & 0xF;
        *testInt = 0xA51D0000;

        if (gLanguage > 3) {
            *testInt |= 0x100;
        } else {
            *testInt |= (gLanguage + 1) * 0x100;
        }

        if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
            testChar = 1;
        } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
            testChar = 0;
        }

        *testInt |= testChar;
#else
        if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
            *testInt = 0xA51D0101;
        } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
            *testInt = 0xA51D0100;
        }
#endif
    }

    NO_INLINE();
#endif

    return true;
}

bool mcardGameSet(MemCard* pMCard, char* name) {
    s32 i;
#if IS_MM
    s32* testInt;
#endif
#if IS_MM_JP || IS_MM_EU
    char testChar;
#endif

    if (pMCard->saveToggle == true) {
        for (i = 0; i < 16; i++) {
            if (mcardCompareName(name, pMCard->file.gameName[i]) == true) {
                break;
            }
        }
        if (i == 16) {
            pMCard->error = MC_E_GAME_NOT_FOUND;
            return false;
        }

        pMCard->file.currentGame = i;
        pMCard->file.game.size = pMCard->file.gameSize[pMCard->file.currentGame];
        pMCard->file.game.offset = pMCard->file.gameOffset[pMCard->file.currentGame];
        pMCard->file.game.configuration = pMCard->file.gameConfigIndex[pMCard->file.currentGame];
        pMCard->file.game.writtenConfig = false;

        if (!pMCard->bufferCreated) {
            if (pMCard->file.game.buffer != NULL) {
                if (!xlHeapFree((void**)&pMCard->file.game.buffer)) {
                    return false;
                }
            }
            if (!xlHeapTake((void**)&pMCard->file.game.buffer, pMCard->file.game.size | 0x30000000)) {
                return false;
            }

            if (mcardReadyFile(pMCard) == true) {
                if (!mcardReadGameData(pMCard)) {
                    mcardFinishCard(pMCard);
#if IS_OOT
                    if (!xlHeapFree((void**)&pMCard->file.game.buffer)) {
                        return false;
                    }
                    if (!xlHeapFree((void**)&pMCard->file.game.writtenBlocks)) {
                        return false;
                    }
#endif
                    return false;
                }
                mcardFinishCard(pMCard);
            }
            pMCard->bufferCreated = true;
        }

#if IS_OOT
        if (pMCard->file.game.writtenBlocks != NULL) {
            if (!xlHeapFree((void**)&pMCard->file.game.writtenBlocks)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&pMCard->file.game.writtenBlocks,
                        (NUM_DATA_BLOCKS(pMCard->file.game.size) * sizeof(bool)) | 0x30000000)) {
            return false;
        }

        memset(pMCard->file.game.writtenBlocks, 0, NUM_DATA_BLOCKS(pMCard->file.game.size) * sizeof(bool));
#endif
        pMCard->writeStatus = 0;
        pMCard->writeIndex = 0;

        if (gpSystem->eTypeROM == SRT_ZELDA1) {
            for (i = 0; i < pMCard->file.game.size; i++) {
                if (pMCard->file.game.buffer[i] != 0) {
                    break;
                }
            }
            if (i == pMCard->file.game.size) {
                pMCard->soundToggle = true;
            } else {
                pMCard->soundToggle = false;
            }
            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                pMCard->file.game.buffer[0] &= 0xFC;
                pMCard->file.game.buffer[0] |= 1;
            } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
                if ((pMCard->file.game.buffer[0] & 0xF) == 1) {
                    pMCard->file.game.buffer[0] &= 0xFC;
                }
            }
            pMCard->file.game.writtenBlocks[0] = true;
#if IS_MM_JP || IS_MM_US
        } else if (gpSystem->eTypeROM == SRT_ZELDA2) {
            testInt = (s32*)(pMCard->file.game.buffer + 0x18000);

            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                *testInt = 0xA51D0101;
            }
#elif IS_MM_EU
        } else if (gpSystem->eTypeROM == SRT_ZELDA2) {
            testInt = (s32*)(pMCard->file.game.buffer + 0x18000);
            testChar = *testInt & 0xF;
            *testInt = 0xA51D0000;

            if (gLanguage > 3) {
                *testInt |= 0x100;
            } else {
                *testInt |= (gLanguage + 1) * 0x100;
            }

            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                testChar = 1;
            } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO && testChar == 1) {
                testChar = 0;
            }

            *testInt |= testChar;
#endif
        }
    } else {
#if VERSION != MQ_J
        if (gpSystem->eTypeROM == SRT_ZELDA1)
#endif
        {
            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                pMCard->file.game.buffer[0] &= 0xFC;
                pMCard->file.game.buffer[0] |= 1;
            } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
                if ((pMCard->file.game.buffer[0] & 0xF) == 1) {
                    pMCard->file.game.buffer[0] &= 0xFC;
                }
            }
#if IS_MM_JP || IS_MM_US
        } else if (gpSystem->eTypeROM == SRT_ZELDA2) {
            testInt = (s32*)(pMCard->file.game.buffer + 0x18000);

            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                *testInt = 0xA51D0101;
            }
#elif IS_MM_EU
        }
        else if (gpSystem->eTypeROM == SRT_ZELDA2) {
            testInt = (s32*)(pMCard->file.game.buffer + 0x18000);
            testChar = *testInt & 0xF;
            *testInt = 0xA51D0000;

            if (gLanguage > 3) {
                *testInt |= 0x100;
            } else {
                *testInt |= (gLanguage + 1) * 0x100;
            }

            if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                testChar = 1;
            } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO && testChar == 1) {
                testChar = 0;
            }

            *testInt |= testChar;
#endif
        }
    }

    return true;
}

bool mcardFileCreate(MemCard* pMCard, char* name, char* comment, char* icon, char* banner, s32 size) {
    s32 freeBytes;
    s32 freeFiles;
    s32 totalSize;
    s32 i;
    char* buffer;
    GXTexObj texObj;
    void* dataP;
    CARDStat cardStatus;
    s32 fileNo;
    OSCalendarTime date;
    char dateString[32];
#if IS_OOT
    s32 pad[2];
#else
    s32 pad[6];
#endif

    totalSize = size + HEADER_SIZE;
    if (pMCard->saveToggle == true) {
        if (mcardFileSet(pMCard, name) == true) {
            mcardFileRelease(pMCard);
            pMCard->error = MC_E_FILE_EXISTS;
            return false;
        }

        mcardFileRelease(pMCard);

        if (!mcardReadyCard(pMCard)) {
            return false;
        }
        pMCard->file.changedDate = false;
        if (!mcardGCErrorHandler(pMCard, CARDFreeBlocks(pMCard->slot, &freeBytes, &freeFiles))) {
            return false;
        }
        if (freeBytes < totalSize) {
            pMCard->error = MC_E_NO_FREE_SPACE;
            return false;
        }
        if (freeFiles <= 0) {
            pMCard->error = MC_E_NO_FREE_FILES;
            return false;
        }

        mcardCopyName(pMCard->file.name, name);

        pMCard->file.numberOfGames = 0;
        pMCard->file.currentGame = 16;
        pMCard->file.fileSize = HEADER_SIZE;

        for (i = 0; i < 16; i++) {
            pMCard->file.gameSize[i] = 0;
            pMCard->file.gameOffset[i] = 0;
            memset(pMCard->file.gameName[i], 0, sizeof(pMCard->file.gameName[i]));
        }

        OSTicksToCalendarTime(OSGetTime(), &pMCard->file.time);
        if (!mcardGCErrorHandler(
                pMCard, CARDCreateAsync(pMCard->slot, pMCard->file.name, totalSize, &pMCard->file.fileInfo, NULL))) {
            return false;
        }

        pMCard->pPollFunction = simulatorDrawMCardText;
        strcpy(pMCard->pollMessage, "Accessing Card");
        if (mcardPoll(pMCard) != true) {
            pMCard->pPollFunction = NULL;
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->pPollFunction = NULL;
        CARDUnmount(pMCard->slot);

        if (!mcardReadyFile(pMCard)) {
            return false;
        }
        if (!xlHeapTake((void**)&buffer, totalSize | 0x30000000)) {
            return false;
        }
        memset(buffer, 0, totalSize);

        memcpy(buffer + COMMENT_OFFSET, comment, strlen(comment));

        OSTicksToCalendarTime(OSGetTime(), &date);

#if VERSION == MQ_J || VERSION == MQ_U
        sprintf(dateString, DATE_STRING, date.mon + 1, date.mday);
#elif VERSION == MQ_E
        if (gLanguage == 1) {
            sprintf(dateString, "%d/%d Speicherstand\0", date.mon + 1, date.mday);
        } else if (gLanguage == 2) {
            sprintf(dateString, "Sauvegarde du %d/%d\0", date.mday, date.mon + 1);
        } else if (gLanguage == 3) {
            sprintf(dateString, "Datos guardados el %d/%d\0", date.mday, date.mon + 1);
        } else if (gLanguage == 4) {
            sprintf(dateString, "Dati Salvati %d/%d\0", date.mday, date.mon + 1);
        } else {
            sprintf(dateString, DATE_STRING, date.mon + 1, date.mday);
        }
#elif IS_MM_JP
        switch (gpSystem->eTypeROM) {
            case SRT_ZELDA1:
                // "Ocarina of Time"
                sprintf(dateString, "時のオカリナ");
                break;
            case SRT_ZELDA2:
                // "The Legend of Zelda: Majora's Mask"
                sprintf(dateString, "ゼルダの伝説：ムジュラの仮面");
                break;
            default:
                // "This is the save data from %d month %d day"
                sprintf(dateString, "%d月%d日のセーブデータです", date.mon + 1, date.mday);
                break;
        }
#else
        sprintf(dateString, DATE_STRING);
#endif

        memcpy(buffer + DATE_STRING_OFFSET, dateString, strlen(dateString));

        TEXGetGXTexObjFromPalette((TEXPalette*)banner, &texObj, 0);
        dataP = (u8*)GXGetTexObjData(&texObj) + 0x80000000;
        memcpy(buffer + BANNER_TPL_OFFSET, dataP, BANNER_TPL_SIZE);

        TEXGetGXTexObjFromPalette((TEXPalette*)icon, &texObj, 0);
        dataP = (u8*)GXGetTexObjData(&texObj) + 0x80000000;
        memcpy(buffer + ICON_TPL_OFFSET, dataP, ICON_TPL_SIZE);

        fileNo = pMCard->file.fileInfo.fileNo;
        if (!mcardGCErrorHandler(pMCard, CARDGetStatus(pMCard->slot, fileNo, &cardStatus))) {
            CARDUnmount(pMCard->slot);
            return false;
        }

        CARDSetCommentAddress(&cardStatus, COMMENT_OFFSET);
        CARDSetIconAddress(&cardStatus, BANNER_TPL_OFFSET);
        CARDSetBannerFormat(&cardStatus, 2);

#if IS_OOT
        CARDSetIconFormat(&cardStatus, 0, 2);
        CARDSetIconSpeed(&cardStatus, 0, ICON_SPEED);
        CARDSetIconFormat(&cardStatus, 1, 2);
        CARDSetIconSpeed(&cardStatus, 1, ICON_SPEED);
        CARDSetIconFormat(&cardStatus, 2, 2);
        CARDSetIconSpeed(&cardStatus, 2, ICON_SPEED);
        CARDSetIconAnim(&cardStatus, CARD_STAT_ANIM_BOUNCE);
#else
        switch (gpSystem->eTypeROM) {
            case SRT_ZELDA1:
                CARDSetIconFormat(&cardStatus, 0, 2);
                CARDSetIconSpeed(&cardStatus, 0, 2);
                CARDSetIconFormat(&cardStatus, 1, 2);
                CARDSetIconSpeed(&cardStatus, 1, 2);
                CARDSetIconFormat(&cardStatus, 2, 2);
                CARDSetIconSpeed(&cardStatus, 2, 2);
                CARDSetIconAnim(&cardStatus, CARD_STAT_ANIM_BOUNCE);
                break;
            case SRT_ZELDA2:
                CARDSetIconFormat(&cardStatus, 0, 2);
                CARDSetIconSpeed(&cardStatus, 0, 3);
                CARDSetIconFormat(&cardStatus, 1, 2);
                CARDSetIconSpeed(&cardStatus, 1, 3);
                CARDSetIconFormat(&cardStatus, 2, 2);
                CARDSetIconSpeed(&cardStatus, 2, 3);
                CARDSetIconAnim(&cardStatus, CARD_STAT_ANIM_BOUNCE);
                break;
            default:
                CARDSetIconFormat(&cardStatus, 0, 2);
                CARDSetIconSpeed(&cardStatus, 0, 2);
                CARDSetIconFormat(&cardStatus, 1, 2);
                CARDSetIconSpeed(&cardStatus, 1, 2);
                CARDSetIconFormat(&cardStatus, 2, 2);
                CARDSetIconSpeed(&cardStatus, 2, 2);
                CARDSetIconAnim(&cardStatus, CARD_STAT_ANIM_BOUNCE);
                break;
        }
#endif

        if (!mcardGCErrorHandler(pMCard, CARDSetStatusAsync(pMCard->slot, fileNo, &cardStatus, NULL))) {
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->pPollFunction = simulatorDrawMCardText;
        strcpy(pMCard->pollMessage, "Accessing Card");
        if (mcardPoll(pMCard) != true) {
            pMCard->pPollFunction = NULL;
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->pPollFunction = NULL;
        strcpy(pMCard->pollMessage, "Creating File");
        if (!mcardWriteAnywhereNoTime(pMCard, 0, totalSize, buffer)) {
            mcardFinishCard(pMCard);
            return false;
        }

        if (!mcardWriteFileHeaderInitial(pMCard)) {
            mcardFinishCard(pMCard);
            return false;
        }

        if (!xlHeapFree((void**)&buffer)) {
            return false;
        }

        CARDUnmount(pMCard->slot);
    }

    return true;
}

bool mcardGameCreate(MemCard* pMCard, char* name, s32 defaultConfiguration, s32 size) {
    s32 i;

    if (pMCard->saveToggle == true) {
        if (mcardGameSet(pMCard, name) == true) {
            mcardGameRelease(pMCard);
            pMCard->error = MC_E_GAME_EXISTS;
            return false;
        }
        mcardGameRelease(pMCard);

        for (i = 0; i < 16; i++) {
            if (pMCard->file.gameSize[i] == 0) {
                break;
            }
        }

        pMCard->file.game.size = size;
        if (i == 0) {
            pMCard->file.game.offset = 0;
        } else {
            pMCard->file.game.offset = NUM_DATA_BLOCKS(pMCard->file.gameSize[i - 1]) * BLOCK_SIZE + BLOCK_SIZE +
                                       pMCard->file.gameOffset[i - 1];
        }

#if IS_OOT
        if (pMCard->file.game.writtenBlocks != NULL) {
            if (!xlHeapFree((void**)&pMCard->file.game.writtenBlocks)) {
                return false;
            }
        }
#endif
        if (!pMCard->bufferCreated) {
            if (pMCard->file.game.buffer != NULL) {
                if (!xlHeapFree((void**)&pMCard->file.game.buffer)) {
                    return false;
                }
            }
            if (!xlHeapTake((void**)&pMCard->file.game.buffer, pMCard->file.game.size | 0x30000000)) {
                return false;
            }
            memset(pMCard->file.game.buffer, 0, size);
        }

#if IS_OOT
        if (!xlHeapTake((void**)&pMCard->file.game.writtenBlocks,
                        (NUM_DATA_BLOCKS(pMCard->file.game.size) * sizeof(bool)) | 0x30000000)) {
            return false;
        }
#endif

        pMCard->file.gameSize[i] = pMCard->file.game.size;
        pMCard->file.gameOffset[i] = pMCard->file.game.offset;
        pMCard->file.gameConfigIndex[i] = defaultConfiguration;
        pMCard->file.game.writtenConfig = false;

        mcardCopyName(pMCard->file.gameName[i], name);

        pMCard->file.numberOfGames += 1;
        pMCard->file.fileSize += NUM_DATA_BLOCKS(pMCard->file.gameSize[i]) * BLOCK_SIZE + BLOCK_SIZE;

        if (!mcardReadyFile(pMCard)) {
            pMCard->file.numberOfGames -= 1;
            pMCard->file.fileSize -= NUM_DATA_BLOCKS(pMCard->file.gameSize[i]) * BLOCK_SIZE + BLOCK_SIZE;
            pMCard->file.gameSize[i] = 0;
            pMCard->file.gameOffset[i] = 0;
            memset(pMCard->file.gameName[i], 0, sizeof(pMCard->file.gameName[i]));
            mcardGameRelease(pMCard);
            return false;
        }

        if (!mcardWriteGameDataWait(pMCard)) {
            pMCard->file.numberOfGames -= 1;
            pMCard->file.fileSize -= NUM_DATA_BLOCKS(pMCard->file.gameSize[i]) * BLOCK_SIZE + BLOCK_SIZE;
            pMCard->file.gameSize[i] = 0;
            pMCard->file.gameOffset[i] = 0;
            memset(pMCard->file.gameName[i], 0, sizeof(pMCard->file.gameName[i]));
            mcardGameRelease(pMCard);
            mcardFinishCard(pMCard);
            return false;
        }
        if (mcardWriteFileHeader(pMCard) == 0) {
            pMCard->file.numberOfGames -= 1;
            pMCard->file.fileSize -= NUM_DATA_BLOCKS(pMCard->file.gameSize[i]) * BLOCK_SIZE + BLOCK_SIZE;
            pMCard->file.gameSize[i] = 0;
            pMCard->file.gameOffset[i] = 0;
            memset(pMCard->file.gameName[i], 0, sizeof(pMCard->file.gameName[i]));
            mcardGameRelease(pMCard);
            mcardFinishCard(pMCard);
            return false;
        }
        mcardGameRelease(pMCard);
        mcardFinishCard(pMCard);
    }

    return true;
}

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
    pMCard->pollSize = pMCard->cardSize << 17;
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

    if (!pMCard->bufferCreated) {
        pMCard->file.game.buffer = NULL;
    }

#if IS_OOT
    pMCard->file.game.writtenBlocks = NULL;
#endif
    pMCard->writeBuffer = NULL;
    pMCard->readBuffer = NULL;
    mcardReInit(pMCard);
    pMCard->slot = slot;
    CARDUnmount(pMCard->slot);

    return true;
}

bool mcardFileErase(MemCard* pMCard) {
    if (pMCard->saveToggle == true) {
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
            mcardFileRelease(pMCard);
            CARDUnmount(pMCard->slot);
            return false;
        }

        pMCard->accessType = 0;
        pMCard->pPollFunction = NULL;
        mcardFileRelease(pMCard);
        CARDUnmount(pMCard->slot);
    }

    return true;
}

bool mcardGameErase(MemCard* pMCard, s32 index) {
    if (pMCard->saveToggle == true) {
        pMCard->accessType = 2;
        simulatorPrepareMessage(S_M_CARD_SV09);
        pMCard->file.fileSize -= NUM_DATA_BLOCKS(pMCard->file.gameSize[index]) * BLOCK_SIZE + BLOCK_SIZE;
        pMCard->file.gameSize[index] = 0;
        pMCard->file.gameOffset[index] = 0;
        memset(pMCard->file.gameName[index], 0, sizeof(pMCard->file.gameName[index]));
        pMCard->file.numberOfGames -= 1;

        if (!mcardReadyFile(pMCard)) {
            pMCard->accessType = 0;
            return false;
        }

        if (!mcardWriteFileHeader(pMCard)) {
            pMCard->accessType = 0;
            mcardFinishCard(pMCard);
            return false;
        }

        pMCard->accessType = 0;
        mcardFinishCard(pMCard);
    }

    return true;
}

static inline bool mcardFileRelease(MemCard* pMCard) {
    mcardGameRelease(pMCard);

    pMCard->file.changedDate = false;
    memset(pMCard->file.name, 0, ARRAY_COUNT(pMCard->file.name));
    pMCard->file.numberOfGames = 0;
    memset(pMCard->file.gameSize, 0, ARRAY_COUNT(pMCard->file.gameSize));
    memset(pMCard->file.gameOffset, 0, ARRAY_COUNT(pMCard->file.gameOffset));
    memset(pMCard->file.gameName, 0, GAME_NAMES_SIZE);
}

bool mcardGameRelease(MemCard* pMCard) {
    if (!pMCard->bufferCreated) {
        if (pMCard->file.game.buffer != NULL) {
            if (!xlHeapFree((void**)&pMCard->file.game.buffer)) {
                return false;
            }
        }

        pMCard->file.game.size = 0;
        memset(&pMCard->file.game.configuration, 0, sizeof(s32));
    }

#if IS_OOT
    if (pMCard->file.game.writtenBlocks != NULL) {
        if (!xlHeapFree((void**)&pMCard->file.game.writtenBlocks)) {
            return false;
        }
    }
#endif

    pMCard->file.game.writtenConfig = false;
    pMCard->file.currentGame = 16;

    return true;
}

bool mcardRead(MemCard* pMCard, s32 address, s32 size, char* data) {
    memcpy(data, &pMCard->file.game.buffer[address], size);
    return true;
}

bool mcardMenu(MemCard* pMCard, MemCardMessage menuEntry, MemCardCommand* pCommand) {
    static bool yes;
    static MemCardMessage prevMenuEntry;
    static MemCardMessage nextMenuEntry;

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
#if VERSION != MQ_J
                pMCard->isBroken = true;
#endif
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
#if VERSION != MQ_J
                pMCard->wait = false;
#endif
                nextMenuEntry = MC_M_LD07;
                prevMenuEntry = MC_M_NONE;
                if ((s32)yes == true) {
#if VERSION != MQ_J
                    pMCard->isBroken = false;
#endif
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
#if VERSION != MQ_J
                pMCard->isBroken = true;
#endif
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
            pMCard->wait = true;
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
            pMCard->wait = true;
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
            pMCard->wait = true;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN03) == true) {
                pMCard->wait = false;
                prevMenuEntry = MC_M_NONE;
                nextMenuEntry = MC_M_NONE;
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN04_L:
            pMCard->wait = true;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN04) == true) {
#if VERSION == MQ_J
                pMCard->wait = false;
                nextMenuEntry = prevMenuEntry = MC_M_NONE;
#else
                nextMenuEntry = MC_M_LD02;
#endif
                *pCommand = MC_C_CONTINUE;
            }
            break;
        case MC_M_IN04_S:
            pMCard->wait = true;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_IN04) == true) {
#if VERSION == MQ_J
                pMCard->wait = false;
                nextMenuEntry = prevMenuEntry = MC_M_NONE;
#else
                nextMenuEntry = MC_M_SV02;
#endif
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
            pMCard->wait = true;
            prevMenuEntry = menuEntry;
            nextMenuEntry = menuEntry;
            if (simulatorDrawErrorMessageWait(S_M_CARD_GF03) == true) {
                pMCard->wait = false;
                nextMenuEntry = MC_M_GF05;
                *pCommand = MC_C_GO_TO_GAME;
            }
            break;
        case MC_M_GF04_L:
            pMCard->wait = true;
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
            pMCard->wait = true;
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

#if IS_MM_JP
static bool mcardNewStart;
static s32 mcardEmpty;
static s32 mcardOneTime;
s32 mcardSaveDisplay = 0;
#elif IS_MM_US || IS_MM_EU
bool mcardNewStart = false;
s32 mcardSaveDisplay = 0;
s32 mcardOneTime = 0;
#endif

bool mcardWrite(MemCard* pMCard, s32 address, s32 size, char* data) {
    static bool toggle = true;
    static bool toggle2;
    s32 i;
    char testByte;

    testByte = pMCard->file.game.buffer[0];
    bWrite2Card = true;
    bNoWriteInCurrentFrame[currentIdx] = false;

    memcpy(&pMCard->file.game.buffer[address], data, size);

#if VERSION == MQ_J
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        if (address == 0) {
            if (toggle && pMCard->soundToggle == true) {
                if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                    pMCard->file.game.buffer[0] &= 0xFC;
                    pMCard->file.game.buffer[0] |= 1;
                } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
                    if ((pMCard->file.game.buffer[0] & 0xF) == 1) {
                        pMCard->file.game.buffer[0] &= 0xFC;
                    }
                }
                *data = pMCard->file.game.buffer[0];
                toggle = false;
            } else if (pMCard->file.game.buffer[0] != testByte) {
                if ((testByte & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_STEREO);
                } else if ((pMCard->file.game.buffer[0] & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_MONO);
                }
            }
        }
    }

    if (pMCard->saveToggle == true) {
        for (i = address / BLOCK_DATA_SIZE; i < (address + size - 1 + BLOCK_DATA_SIZE) / BLOCK_DATA_SIZE; i++) {
            pMCard->file.game.writtenBlocks[i] = true;
        }

        if (size == 0x1450 && gpSystem->eTypeROM == SRT_ZELDA1 && toggle2 == true) {
            toggle2 = 0;
            simulatorRumbleStop(0);
            if (!mcardUpdate()) {
                return false;
            }
        } else if (size == 0x1450 && gpSystem->eTypeROM == SRT_ZELDA1 && toggle2 == false) {
            toggle2 = true;
        }
    } else if (size == 0x1450 && gpSystem->eTypeROM == SRT_ZELDA1 && toggle2 == true) {
        toggle2 = false;
        pMCard->saveToggle = true;
        pMCard->wait = false;
        mcardOpenDuringGame(pMCard);
        if (pMCard->saveToggle == true) {
            if (!mcardUpdate()) {
                return false;
            }
        }
    } else if (size == 0x1450 && gpSystem->eTypeROM == SRT_ZELDA1 && toggle2 == false) {
        toggle2 = true;
    }
#else
    if (gpSystem->eTypeROM == SRT_ZELDA1) {
        if (address == 0) {
            if (toggle && pMCard->soundToggle == true) {
                if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                    pMCard->file.game.buffer[0] &= 0xFC;
                    pMCard->file.game.buffer[0] |= 1;
                } else if (OSGetSoundMode() == OS_SOUND_MODE_STEREO) {
                    if ((pMCard->file.game.buffer[0] & 0xF) == 1) {
                        pMCard->file.game.buffer[0] &= 0xFC;
                    }
                }
                *data = pMCard->file.game.buffer[0];
                toggle = false;
            } else if (pMCard->file.game.buffer[0] != testByte) {
                if ((testByte & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_STEREO);
                } else if ((pMCard->file.game.buffer[0] & 3) == 1) {
                    OSSetSoundMode(OS_SOUND_MODE_MONO);
                }
            }
        }

        if (pMCard->saveToggle == true) {
            for (i = address / BLOCK_DATA_SIZE; i < (address + size - 1 + BLOCK_DATA_SIZE) / BLOCK_DATA_SIZE; i++) {
                pMCard->file.game.writtenBlocks[i] = true;
            }

            if (size == 0x1450 && toggle2 == true) {
                toggle2 = 0;
                simulatorRumbleStop(0);
                if (!mcardUpdate()) {
                    return false;
                }
            } else if (size == 0x1450 && toggle2 == false) {
                toggle2 = true;
            }
        } else if (size == 0x1450 && toggle2 == true) {
            toggle2 = false;
            pMCard->saveToggle = true;
            pMCard->wait = false;
            mcardOpenDuringGame(pMCard);
            if (pMCard->saveToggle == true) {
                if (!mcardUpdate()) {
                    return false;
                }
            }
        } else if (size == 0x1450 && toggle2 == false) {
            toggle2 = true;
        }
#if IS_MM
    } else if (gpSystem->eTypeROM == SRT_ZELDA2) {
        for (i = address / BLOCK_DATA_SIZE; i < (address + size - 1 + BLOCK_DATA_SIZE) / BLOCK_DATA_SIZE; i++) {
            pMCard->file.game.writtenBlocks[i] = true;
        }

        if (size == 0x80) {
            bool var_r31 = 0;

            if (mcardSaveDisplay != 0 && mcardSaveDisplay != 0x17 && mcardSaveDisplay != 0x18) {
                mcardOneTime = 1;
            }

            if (address == 0x3F80 || address == 0x7F80) {
#if IS_MM_JP
                if (mcardSaveDisplay == 0x1A || mcardSaveDisplay == 0x11 || mcardSaveDisplay == 0x14 ||
                    mcardSaveDisplay == 0x15 || mcardSaveDisplay == 0x16 || mcardSaveDisplay == 0x17)
#elif IS_MM_EU
                if (mcardSaveDisplay == 0x11 || mcardSaveDisplay == 0x14 || mcardSaveDisplay == 0x15 ||
                    mcardSaveDisplay == 0x16)
#else
                if (mcardSaveDisplay == 0x11 || mcardSaveDisplay == 0x14 || mcardSaveDisplay == 0x15 ||
                    mcardSaveDisplay == 0x16 || mcardSaveDisplay == 0x17)
#endif
                {
                    var_r31 = 1;
                    if (mcardOneTime == 0 && mcardSaveDisplay == 0x17) {
                        var_r31 = 0;
                    }
                    mcardSaveDisplay = 0;
                }
#if IS_MM_JP
            } else if (address == 0x8000 || address == 0x10000) {
                if (mcardSaveDisplay == 0x12) {
                    ZeldaEraseCamera();
                    mcardLoadZelda2Camera(pMCard, address);
                }
#endif
#if IS_MM_EU
            } else if (address == 0xFF80 || address == 0x17F80) {
                if (mcardSaveDisplay == 0x10 || mcardSaveDisplay == 0x12) {
                    var_r31 = 1;
                    if (mcardSaveDisplay == 0x12) {
                        ZeldaEraseCamera();
                        mcardLoadZelda2Camera(pMCard, address - 0x7F80);
                    }
                    if ((mcardOneTime == 0) && (mcardSaveDisplay == 0x17)) {
                        var_r31 = 0;
                    }
                    mcardSaveDisplay = 0;
                }
#else
            } else if (address == 0xFF80 || address == 0x17F80) {
                if (mcardSaveDisplay == 0x10 || mcardSaveDisplay == 0x12 || mcardSaveDisplay == 0x17) {
                    var_r31 = 1;
                    if ((mcardOneTime == 0) && (mcardSaveDisplay == 0x17)) {
                        var_r31 = 0;
                    }
                    mcardSaveDisplay = 0;
                }
#endif
#if IS_MM_JP || IS_MM_EU
            } else if (address == 0xBF80 || address == 0x13F80) {
                if (mcardSaveDisplay == 0x10) {
                    mcardSaveDisplay = 0;
                    var_r31 = 1;
                    if (address == 0xBF80) {
#if IS_MM_JP
                        DCInvalidateRange(pMCard->file.game.buffer + 0xC000, 0x3FFFU);
#endif
                        memcpy(pMCard->file.game.buffer + 0xC000, pMCard->file.game.buffer + 0x8000, 0x3FFF);
                    } else {
#if IS_MM_JP
                        DCInvalidateRange(pMCard->file.game.buffer + 0x14000, 0x3FFFU);
#endif
                        memcpy(pMCard->file.game.buffer + 0x14000, pMCard->file.game.buffer + 0x10000, 0x3FFF);
                    }
                }
#endif
            } else if (address == 0x1F80 || address == 0x5F80) {
                if (mcardSaveDisplay == 0x19) {
                    mcardSaveDisplay = 0;
                    var_r31 = 1;
                }
            } else if (address == 0x18000 && mcardSaveDisplay == 0x18) {
                if (toggle2 == 0) {
                    toggle2 += 1;
                } else {
                    s32 value;

                    mcardSaveDisplay = 0;
                    var_r31 = 1;
#if IS_MM_US
                    value = ((s32*)pMCard->file.game.buffer)[0x6000] & 0x7;
#else
                    value = ((s32*)pMCard->file.game.buffer)[0x6000] & 0xF;
#endif
                    switch (value) {
                        case 0:
                            OSSetSoundMode(OS_SOUND_MODE_STEREO);
                            break;
                        case 1:
                            OSSetSoundMode(OS_SOUND_MODE_MONO);
                            break;
                        case 2:
                            OSSetSoundMode(OS_SOUND_MODE_STEREO);
                            break;
                        case 3:
                            OSSetSoundMode(OS_SOUND_MODE_STEREO);
                            break;
                    }
                    toggle2 = 0;
                }
            }

            if (var_r31 != 0) {
                pMCard->saveToggle = true;
                pMCard->wait = false;
                simulatorRumbleStop(0);
                mcardOpenDuringGame(pMCard);
                if (pMCard->saveToggle == true) {
                    if (!mcardUpdate()) {
                        return false;
                    }
                }
            }
        }
    } else if (gpSystem->eTypeROM == SRT_MARIO) {
        if (size == 8) {
            if (mcardNewStart && address == 0x1F8) {
                toggle2++;

                if (toggle2 == 5) {
                    mcardNewStart = 0;
                }
            }

            if (mcardNewStart == 0) {
#if IS_MM_JP
                if (mcardEmpty != 0) {
                    mcardEmpty = 0;
                } else
#endif
                {
                    switch (address) {
                        case 0x68:
                        case 0xD8:
                        case 0x148:
                        case 0x1B8:
                        case 0x1F8:
                            pMCard->saveToggle = true;
                            pMCard->wait = false;
                            simulatorRumbleStop(0);
                            mcardOpenDuringGame(pMCard);
                            if (pMCard->saveToggle == true) {
                                if (!mcardUpdate()) {
                                    return false;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (gpSystem->eTypeROM == SRT_MARIOKART) {
        if (size == 8) {
            if (mcardNewStart == 1 && address == 0x1F8) {
                mcardNewStart = 0;
            }

            if (mcardNewStart == 0) {
#if IS_MM_JP
                if (mcardEmpty != 0) {
                    mcardEmpty = 0;
                } else
#endif
                {
                    switch (address) {
                        case 0x1B8:
                        case 0x1F0:
                        case 0x1F8:
                            pMCard->saveToggle = true;
                            pMCard->wait = false;
                            simulatorRumbleStop(0);
                            mcardOpenDuringGame(pMCard);
                            if (pMCard->saveToggle == true) {
                                if (!mcardUpdate()) {
                                    return false;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (gpSystem->eTypeROM == SRT_STARFOX) {
        if (size == 8 && address == 0x1F8) {

#if IS_MM_JP
            if (mcardEmpty != 0) {
                mcardEmpty = 0;
            } else
#endif
            {
                pMCard->saveToggle = true;
                pMCard->wait = false;
                simulatorRumbleStop(0);
                mcardOpenDuringGame(pMCard);
                if (pMCard->saveToggle == true) {
                    if (!mcardUpdate()) {
                        return false;
                    }
                }
            }
        }
    } else if (gpSystem->eTypeROM == SRT_PILOTWING) {
        if (size == 8) {
            if (address == 0xF8 || address == 0x1F8) {

#if IS_MM_JP
                if (mcardEmpty != 0) {
                    mcardEmpty = 0;
                } else
#endif
                {
                    pMCard->saveToggle = true;
                    pMCard->wait = false;
                    simulatorRumbleStop(0);
                    mcardOpenDuringGame(pMCard);
                    if (pMCard->saveToggle == true) {
                        if (!mcardUpdate()) {
                            return false;
                        }
                    }
                }
            }
        }
#endif
    } else {
        if (pMCard->saveToggle == true) {
            simulatorRumbleStop(0);
            if (!mcardUpdate()) {
                return false;
            }
        } else {
            pMCard->saveToggle = true;
            pMCard->wait = false;
#if IS_MM
            simulatorRumbleStop(0);
#endif
            mcardOpenDuringGame(pMCard);
            if (pMCard->saveToggle == true) {
                if (!mcardUpdate()) {
                    return false;
                }
            }
        }
    }
#endif

#if IS_MM
    PAD_STACK();
#endif
    return true;
}

static inline bool mcardCheckSpace(MemCard* pMCard, s32 size) {
    s32 freeBytes;
    s32 freeFiles;

    if (!mcardReadyCard(pMCard)) {
        return false;
    }

    if (!mcardGCErrorHandler(pMCard, CARDFreeBlocks(pMCard->slot, &freeBytes, &freeFiles))) {
        return false;
    }

    if (freeBytes < size || freeFiles <= 0) {
        if (freeFiles <= 0) {
            pMCard->error = MC_E_NO_FREE_FILES;
        } else {
            pMCard->error = MC_E_NO_FREE_SPACE;
        }
        return false;
    }

    CARDUnmount(pMCard->slot);
    return true;
}

bool mcardOpen(MemCard* pMCard, char* fileName, char* comment, char* icon, char* banner, char* gameName,
               s32* defaultConfiguration, s32 fileSize, s32 gameSize) {
    s32 i;
    MemCardCommand command;

    strcpy(pMCard->saveFileName, fileName);
    strcpy(pMCard->saveComment, comment);
    strcpy(pMCard->saveGameName, gameName);

    pMCard->saveFileSize = fileSize;
    pMCard->saveGameSize = gameSize;
    pMCard->saveConfiguration = *defaultConfiguration;
    pMCard->bufferCreated = false;
    pMCard->gameIsLoaded = false;

    gButtonDownToggle = true;
    pMCard->wait = false;

    while (true) {
        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }
        pMCard->accessType = 0;
        if (!mcardFileSet(pMCard, fileName)) {
            mcardOpenError(pMCard, &command);
            if (command == MC_C_FORMAT_CARD) {
                if (!mcardCardErase(pMCard)) {
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(pMCard, MC_M_IN04_L, &command);
                    }
                } else {
                    mcardMenu(pMCard, MC_M_IN03, &command);
                }
                continue;
            } else if (command == MC_C_DELETE_GAME) {
                simulatorPrepareMessage(S_M_CARD_GF02);
                if (!mcardFileErase(pMCard)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3518, 3532, 4111, 3938), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }
                pMCard->accessType = 2;
                if (!mcardFileCreate(pMCard, fileName, comment, icon, banner, fileSize)) {
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(pMCard, MC_M_GF04_L, &command);
                    }
                    continue;
                }
                if (!mcardFileSet(pMCard, fileName)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3546, 3560, 4139, 3966), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }
                if (!mcardReadyFile(pMCard)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3567, 3581, 4160, 3987), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }
                mcardFinishCard(pMCard);
                mcardMenu(pMCard, MC_M_GF03, &command);
                continue;
            } else if (command == MC_C_CONTINUE) {
                continue;
            } else if (command == MC_C_GO_TO_GAME) {
#if IS_MM_JP
                mcardNewStart = true;
                mcardEmpty = true;
#endif
                pMCard->saveToggle = false;
                mcardGameSetNoSave(pMCard, gameSize);
                return true;
            } else if (command == MC_C_CREATE_GAME) {
#if IS_MM
                mcardNewStart = true;
                if (gSystemRomConfigurationList->storageDevice == SOT_RSP ||
                    gSystemRomConfigurationList->storageDevice == SOT_FLASH) {
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                }
#endif
                if (!mcardCheckSpace(pMCard, fileSize + (u32)HEADER_SIZE)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_IPL) {
                        simulatorReset(true, true);
                    } else if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3612, 3626, 4224, 4046), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }

                mcardMenu(pMCard, MC_M_GF01_L, &command);
                if (command == MC_C_CREATE_GAME) {
                    pMCard->accessType = 1;
                    simulatorPrepareMessage(S_M_CARD_GF02);
                    if (!mcardFileCreate(pMCard, fileName, comment, icon, banner, fileSize)) {
                        if (pMCard->error != MC_E_NOCARD) {
                            mcardMenu(pMCard, MC_M_GF04_L, &command);
                        }
                        continue;
                    }
                    if (!mcardFileSet(pMCard, fileName)) {
                        mcardOpenError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(3646, 3660, 4258, 4080), command);
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        }
                    }
                    if (!mcardReadyFile(pMCard)) {
                        mcardOpenError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(3667, 3681, 4279, 4101), command);
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        }
                    }
                    mcardFinishCard(pMCard);
                    mcardMenu(pMCard, MC_M_GF03, &command);
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                } else if (command == MC_C_CONTINUE) {
                    continue;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(3688, 3702, 4300, 4122), command);
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                }
            } else {
                xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                           LN(3696, 3710, 4308, 4130), command);
                pMCard->saveToggle = false;
                mcardGameSetNoSave(pMCard, gameSize);
                return true;
            }
        } else {
#if IS_MM
            mcardNewStart = false;
#endif
            if (!mcardVerifyChecksumFileHeader(pMCard)) {
                mcardOpenError(pMCard, &command);
                if (command == MC_C_DELETE_GAME) {
                    simulatorPrepareMessage(S_M_CARD_GF02);
                    if (!mcardFileErase(pMCard)) {
                        mcardOpenError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(3726, 3740, 4342, 4164), command);
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        }
                    }
                    pMCard->accessType = 2;
                    if (!mcardFileCreate(pMCard, fileName, comment, icon, banner, fileSize)) {
                        if (pMCard->error != MC_E_NOCARD) {
                            mcardMenu(pMCard, MC_M_GF04_L, &command);
                        }
                        continue;
                    }
                    if (!mcardFileSet(pMCard, fileName)) {
                        mcardOpenError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(3754, 3768, 4370, 4192), command);
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        }
                    }
                    if (!mcardReadyFile(pMCard)) {
                        mcardOpenError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(3775, 3789, 4391, 4213), command);
                            pMCard->saveToggle = false;
                            mcardGameSetNoSave(pMCard, gameSize);
                            return true;
                        }
                    }
                    mcardFinishCard(pMCard);
                    mcardMenu(pMCard, MC_M_GF03, &command);
                    continue;
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                } else if (command == MC_C_CONTINUE) {
                    continue;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(3797, 3811, 4413, 4235), command);
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                }
            }
        }

        if (pMCard->wait == true) {
            mcardMenu(pMCard, MC_M_NONE, &command);
            if (pMCard->wait == true) {
                continue;
            }
        }

        for (i = 0; i < 16; i++) {
            if (mcardCompareName(gameName, pMCard->file.gameName[i]) == true) {
                break;
            }
        }
        if (i == 16) {
            pMCard->accessType = 2;
            simulatorPrepareMessage(S_M_CARD_SV09);
            if (!mcardGameCreate(pMCard, gameName, *defaultConfiguration, gameSize)) {
#if VERSION != MQ_J
                pMCard->isBroken = true;
#endif
                continue;
            }
            if (!mcardGameSet(pMCard, gameName)) {
                mcardOpenError(pMCard, &command);
                if (command == MC_C_CONTINUE) {
                    continue;
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(3843, 3858, 4460, 4282), command);
                    pMCard->saveToggle = false;
                    mcardGameSetNoSave(pMCard, gameSize);
                    return true;
                }
            }
        } else if (!mcardGameSet(pMCard, gameName)) {
            mcardOpenError(pMCard, &command);
            if (command == MC_C_DELETE_GAME) {
                if (!mcardGameErase(pMCard, i)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3872, 3887, 4489, 4311), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }
#if VERSION != MQ_J
                pMCard->accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                if (!mcardGameCreate(pMCard, gameName, *defaultConfiguration, gameSize)) {
                    pMCard->isBroken = true;
                    continue;
                }
                if (!mcardGameSet(pMCard, gameName)) {
                    mcardOpenError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(UNK_LINE, 3920, 4522, 4344), command);
                        pMCard->saveToggle = false;
                        mcardGameSetNoSave(pMCard, gameSize);
                        return true;
                    }
                }
#endif
            } else if (command == MC_C_CONTINUE) {
                continue;
            } else if (command == MC_C_GO_TO_GAME) {
                pMCard->saveToggle = false;
                mcardGameSetNoSave(pMCard, gameSize);
                return true;
            } else {
                xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                           LN(3892, 3941, 4543, 4365), command);
                pMCard->saveToggle = false;
                mcardGameSetNoSave(pMCard, gameSize);
                return true;
            }
        }

        pMCard->gameIsLoaded = true;
        pMCard->accessType = 0;
        return true;
    }

    PAD_STACK();
}

bool mcardOpenDuringGame(MemCard* pMCard) {
    s32 i;
    MemCardCommand command;
    bool loadToggle;

    gButtonDownToggle = 1;
    if (!pMCard->gameIsLoaded) {
        memset(&pMCard->file.time, 0, TIMESTAMP_SIZE);
    }

    while (true) {
        if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
            return false;
        }

        pMCard->accessType = 0;
        loadToggle = pMCard->gameIsLoaded;
        pMCard->gameIsLoaded = true;
        if (!mcardFileSet(pMCard, pMCard->saveFileName)) {
            pMCard->gameIsLoaded = loadToggle;
            mcardOpenDuringGameError(pMCard, &command);
            if (command == MC_C_FORMAT_CARD) {
                if (!mcardCardErase(pMCard)) {
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(pMCard, MC_M_IN04_S, &command);
                    }
                } else {
                    mcardMenu(pMCard, MC_M_IN03, &command);
                }
                continue;
            } else if (command == MC_C_DELETE_GAME) {
                simulatorPrepareMessage(S_M_CARD_SV09);
                if (!mcardFileErase(pMCard)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3957, 4006, 4608, 4430), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                }
                pMCard->accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                if (!mcardFileCreate(pMCard, pMCard->saveFileName, pMCard->saveComment, pMCard->saveIcon,
                                     pMCard->saveBanner, pMCard->saveFileSize)) {
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(pMCard, MC_M_GF04_S, &command);
                    }
                    continue;
                }
                if (!mcardFileSet(pMCard, pMCard->saveFileName)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(3984, 4033, 4635, 4457), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                }
                if (!mcardReadyFile(pMCard)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(4003, 4052, 4654, 4476), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                }
                mcardFinishCard(pMCard);
                continue;
            } else if (command == MC_C_CONTINUE) {
                continue;
            } else if (command == MC_C_GO_TO_GAME) {
                pMCard->saveToggle = false;
                return true;
            } else if (command == MC_C_CREATE_GAME) {
                if (!mcardCheckSpace(pMCard, pMCard->saveFileSize + HEADER_SIZE)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_IPL) {
                        simulatorReset(true, true);
                    } else if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(4044, 4093, 4695, 4517), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                }
                mcardMenu(pMCard, MC_M_GF01_S, &command);
                if (command == MC_C_CREATE_GAME) {
                    pMCard->accessType = 1;
                    simulatorPrepareMessage(S_M_CARD_GF02);
                    if (!mcardFileCreate(pMCard, pMCard->saveFileName, pMCard->saveComment, pMCard->saveIcon,
                                         pMCard->saveBanner, pMCard->saveFileSize)) {
                        if (pMCard->error != MC_E_NOCARD) {
                            mcardMenu(pMCard, MC_M_GF04_S, &command);
                        }
                        continue;
                    }
                    if (!mcardFileSet(pMCard, pMCard->saveFileName)) {
                        mcardOpenDuringGameError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(4076, 4125, 4727, 4549), command);
                            pMCard->saveToggle = false;
                            return true;
                        }
                    }
                    if (!mcardReadyFile(pMCard)) {
                        mcardOpenDuringGameError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(4095, 4144, 4746, 4568), command);
                            pMCard->saveToggle = false;
                            return true;
                        }
                    }
                    mcardFinishCard(pMCard);
                    mcardMenu(pMCard, MC_M_GF03, &command);
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    return true;
                } else if (command == MC_C_CONTINUE) {
                    continue;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(4115, 4164, 4766, 4588), command);
                    pMCard->saveToggle = false;
                    return true;
                }
            } else {
                xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                           LN(4122, 4171, 4773, 4595), command);
                pMCard->saveToggle = false;
                return true;
            }
        } else {
            pMCard->gameIsLoaded = loadToggle;
            if (!mcardVerifyChecksumFileHeader(pMCard)) {
                mcardOpenDuringGameError(pMCard, &command);
                if (command == MC_C_DELETE_GAME) {
                    simulatorPrepareMessage(S_M_CARD_SV09);
                    if (!mcardFileErase(pMCard)) {
                        mcardOpenDuringGameError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(4151, 4200, 4802, 4624), command);
                            pMCard->saveToggle = false;
                            return true;
                        }
                    }
                    pMCard->accessType = 2;
                    simulatorPrepareMessage(S_M_CARD_SV09);
                    if (!mcardFileCreate(pMCard, pMCard->saveFileName, pMCard->saveComment, pMCard->saveIcon,
                                         pMCard->saveBanner, pMCard->saveFileSize)) {
                        if (pMCard->error != MC_E_NOCARD) {
                            mcardMenu(pMCard, MC_M_GF04_S, &command);
                        }
                        continue;
                    }
                    if (!mcardFileSet(pMCard, pMCard->saveFileName)) {
                        mcardOpenDuringGameError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(4178, 4227, 4829, 4651), command);
                            pMCard->saveToggle = false;
                            return true;
                        }
                    }
                    if (!mcardReadyFile(pMCard)) {
                        mcardOpenDuringGameError(pMCard, &command);
                        if (command == MC_C_CONTINUE) {
                            continue;
                        } else if (command == MC_C_GO_TO_GAME) {
                            pMCard->saveToggle = false;
                            return true;
                        } else {
                            xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                       LN(4197, 4246, 4848, 4670), command);
                            pMCard->saveToggle = false;
                            return true;
                        }
                    }
                    mcardFinishCard(pMCard);
                    continue;
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    return true;
                } else if (command == MC_C_CONTINUE) {
                    continue;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(4216, 4265, 4867, 4689), command);
                    pMCard->saveToggle = false;
                    return true;
                }
            }
        }

        if (pMCard->wait == true) {
            mcardMenu(pMCard, MC_M_NONE, &command);
            if (pMCard->wait == true) {
                continue;
            }
        }

        for (i = 0; i < 16; i++) {
            if (mcardCompareName(pMCard->saveGameName, pMCard->file.gameName[i]) == true) {
                break;
            }
        }

        if (i == 16) {
            pMCard->accessType = 2;
            simulatorPrepareMessage(S_M_CARD_SV09);
            if (!mcardGameCreate(pMCard, pMCard->saveGameName, pMCard->saveConfiguration, pMCard->saveGameSize)) {
#if VERSION == MQ_J
                mcardOpenDuringGameError(pMCard, &command);
                if (command == MC_C_CONTINUE) {
                    continue;
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    return true;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c", 4255, command);
                    pMCard->saveToggle = false;
                    return true;
                }
#else
                pMCard->isBroken = true;
                continue;
#endif
            }
            if (!mcardGameSet(pMCard, pMCard->saveGameName)) {
                mcardOpenDuringGameError(pMCard, &command);
                if (command == MC_C_CONTINUE) {
                    continue;
                } else if (command == MC_C_GO_TO_GAME) {
                    pMCard->saveToggle = false;
                    return true;
                } else {
                    xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                               LN(4275, 4310, 4912, 4734), command);
                    pMCard->saveToggle = false;
                    return true;
                }
            }
        } else if (!mcardGameSet(pMCard, pMCard->saveGameName)) {
            mcardOpenDuringGameError(pMCard, &command);
            if (command == MC_C_DELETE_GAME) {
                if (!mcardGameErase(pMCard, i)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(4302, 4337, 4939, 4761), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                    continue;
                }
#if VERSION != MQ_J
                pMCard->accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                if (!mcardGameCreate(pMCard, pMCard->saveGameName, pMCard->saveConfiguration, pMCard->saveGameSize)) {
                    pMCard->isBroken = true;
                    continue;
                }
                if (!mcardGameSet(pMCard, pMCard->saveGameName)) {
                    mcardOpenDuringGameError(pMCard, &command);
                    if (command == MC_C_CONTINUE) {
                        continue;
                    } else if (command == MC_C_GO_TO_GAME) {
                        pMCard->saveToggle = false;
                        return true;
                    } else {
                        xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                                   LN(UNK_LINE, 4368, 4970, 4792), command);
                        pMCard->saveToggle = false;
                        return true;
                    }
                }
#endif
            } else if (command == MC_C_CONTINUE) {
                continue;
            } else if (command == MC_C_GO_TO_GAME) {
                pMCard->saveToggle = false;
                return true;
            } else {
                xlPostText("Invalid Memory Card Command %d - Assuming Go To Game", "mcardGCN.c",
                           LN(4320, 4387, 4989, 4811), command);
                pMCard->saveToggle = false;
                return true;
            }
        }

        pMCard->gameIsLoaded = true;
        pMCard->accessType = 0;
        return true;
    }

    PAD_STACK();
}

bool mcardStore(MemCard* pMCard) {
    static s32 checkFailCount;
    s32 i;
    s32 checksum;
    s32 bufferOffset;
    s32 pad1[4];
    MemCardCommand command;
    s32 pad2;

    if (pMCard->writeToggle == true) {
        if (pMCard->writeStatus == 0) {
            for (i = 0; i < NUM_DATA_BLOCKS(pMCard->file.game.size); i++) {
                if (pMCard->file.game.writtenBlocks[i] == true) {
                    if (i < NUM_DATA_BLOCKS(pMCard->file.game.size) - 1) {
                        memcpy(pMCard->writeBuffer + BLOCK_DATA_OFFSET, &pMCard->file.game.buffer[i * BLOCK_DATA_SIZE],
                               BLOCK_DATA_SIZE);
                    } else {
                        memcpy(pMCard->writeBuffer + BLOCK_DATA_OFFSET, &pMCard->file.game.buffer[i * BLOCK_DATA_SIZE],
                               pMCard->file.game.size - i * BLOCK_DATA_SIZE);
                    }

                    mcardCalculateChecksum(pMCard, &checksum);
                    pMCard->file.game.writtenBlocks[i] = false;
                    pMCard->writeIndex = i;
                    memcpy(pMCard->writeBuffer, &checksum, CHECKSUM_SIZE);
                    break;
                }
            }

            if (i == NUM_DATA_BLOCKS(pMCard->file.game.size)) {
                if (pMCard->file.game.writtenConfig == true) {
                    pMCard->file.game.writtenConfig = false;
                    pMCard->writeIndex = NUM_DATA_BLOCKS(pMCard->file.game.size) + 2;
                    if (!mcardWriteConfigPrepareWriteBuffer(pMCard)) {
                        return false;
                    }
                } else if (pMCard->file.changedDate == true) {
                    pMCard->file.changedDate = false;
                    pMCard->writeIndex = NUM_DATA_BLOCKS(pMCard->file.game.size) + 1;
                    if (!mcardWriteTimePrepareWriteBuffer(pMCard)) {
                        return false;
                    }
                } else {
                    return true;
                }
            }

            pMCard->writeStatus = 1;
            if (!mcardReadyFile(pMCard)) {
                pMCard->saveToggle = false;
                mcardFinishFile(pMCard);
                return true;
            }

            if (pMCard->writeIndex < NUM_DATA_BLOCKS(pMCard->file.game.size)) {
                bufferOffset =
                    HEADER_SIZE + pMCard->file.game.offset + NUM_DATA_BLOCKS(pMCard->file.game.size) * BLOCK_SIZE;
            } else {
                bufferOffset = 2 * BLOCK_SIZE;
            }
            if (!mcardWriteBufferAsynch(pMCard, bufferOffset)) {
                pMCard->saveToggle = false;
                if (pMCard->error != MC_E_NOCARD) {
                    mcardMenu(&mCard, MC_M_SV10, &command);
                }
                mcardFinishFile(pMCard);
                return true;
            }
            return true;
        } else if (pMCard->writeStatus == 1) {
            pMCard->writeStatus = 2;
            if (pMCard->writeIndex < NUM_DATA_BLOCKS(pMCard->file.game.size)) {
                bufferOffset =
                    HEADER_SIZE + pMCard->file.game.offset + NUM_DATA_BLOCKS(pMCard->file.game.size) * BLOCK_SIZE;
            } else {
                bufferOffset = 2 * BLOCK_SIZE;
            }
            mcardReadBufferAsynch(pMCard, bufferOffset);
            return true;
        } else if (pMCard->writeStatus == 2) {
            if (memcmp(pMCard->readBuffer, pMCard->writeBuffer, BLOCK_SIZE) != 0) {
                pMCard->saveToggle = false;
                if (pMCard->error != MC_E_NOCARD) {
                    mcardMenu(&mCard, MC_M_SV10, &command);
                }
                mcardFinishFile(pMCard);
                return true;
            }
            pMCard->writeStatus = 3;
            if (pMCard->writeIndex < NUM_DATA_BLOCKS(pMCard->file.game.size)) {
                if (!mcardWriteGameData(pMCard, pMCard->writeIndex * BLOCK_SIZE)) {
                    simulatorRumbleStop(0);
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(&mCard, MC_M_SV10, &command);
                    }
                    mcardFinishFile(pMCard);
                    return true;
                }
            } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 1) {
                pMCard->file.changedDate = false;
                if (!mcardWriteTimeAsynch(pMCard)) {
                    pMCard->saveToggle = false;
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(&mCard, MC_M_SV10, &command);
                    }
                    mcardFinishFile(pMCard);
                    return true;
                }
            } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 2) {
                if (!mcardWriteConfigAsynch(pMCard)) {
                    pMCard->saveToggle = false;
                    if (pMCard->error != MC_E_NOCARD) {
                        mcardMenu(&mCard, MC_M_SV10, &command);
                    }
                    mcardFinishFile(pMCard);
                    return true;
                }
            }
            return true;
        } else if (pMCard->writeStatus == 3) {
            pMCard->writeStatus = 4;
            if (pMCard->writeIndex < NUM_DATA_BLOCKS(pMCard->file.game.size)) {
                mcardReadBufferAsynch(pMCard, HEADER_SIZE + pMCard->file.game.offset + pMCard->writeIndex * BLOCK_SIZE);
            } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 1) {
                mcardReadBufferAsynch(pMCard, 0);
            } else if (pMCard->writeIndex == NUM_DATA_BLOCKS(pMCard->file.game.size) + 2) {
                mcardReadBufferAsynch(pMCard, BLOCK_SIZE);
            }
            return true;
        } else if (pMCard->writeStatus == 4) {
            pMCard->writeStatus = 0;
            if (memcmp(pMCard->readBuffer, pMCard->writeBuffer, BLOCK_SIZE) != 0) {
                pMCard->saveToggle = false;
                if (pMCard->error != MC_E_NOCARD) {
                    mcardMenu(&mCard, MC_M_SV10, &command);
                }
                mcardFinishFile(pMCard);
                return true;
            }
            checkFailCount = 0;
            return true;
        }
    } else {
        if (!mcardWriteGameData(pMCard, 0)) {
            pMCard->saveToggle = false;
            mcardFinishFile(pMCard);
            return true;
        }
        if (pMCard->writeToggle == true) {
            DCInvalidateRange(pMCard->readBuffer, BLOCK_SIZE);
        }
        if (pMCard->writeToggle == true && pMCard->writeStatus == 0) {
            mcardFinishCard(pMCard);
        }
        return true;
    }

    return true;
}

bool mcardUpdate(void) {
    s32 j;
    s32 i;
    bool toggle;
    MemCardCommand command;
#if VERSION != MQ_J
    s32 prevIndex;
    s32 index;
    s32 counter;
#endif

    command = MC_C_NONE;
    mCard.saveToggle = true;
    mcardOpenDuringGame(&mCard);

    if (mCard.saveToggle == true) {
#if IS_MM_JP
        if (gSystemRomConfigurationList->storageDevice != SOT_RAM) {
            for (i = 0; i < NUM_DATA_BLOCKS(mCard.file.game.size); i++) {
                mCard.file.game.writtenBlocks[i] = true;
            }
        }
#elif IS_OOT
        for (i = 0; i < NUM_DATA_BLOCKS(mCard.file.game.size); i++) {
            mCard.file.game.writtenBlocks[i] = true;
        }
#endif

#if VERSION != MQ_J
        prevIndex = 100;
        counter = 0;
#endif

        while (true) {
            if (!SIMULATOR_TEST_RESET(false, false, false, false)) {
                return false;
            }

#if VERSION == MQ_J
            toggle = false;
            for (i = 0; i < NUM_DATA_BLOCKS(mCard.file.game.size); i++) {
                if (mCard.file.game.writtenBlocks[i] == true) {
                    toggle = true;
                    break;
                }
            }

            if (mCard.file.game.writtenConfig == true) {
                toggle = true;
            } else if (mCard.file.changedDate == true) {
                toggle = true;
            }

            mcardStore(&mCard);

            if (mCard.writeStatus != 0) {
                mCard.accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                simulatorDrawMCardText();
            }
#else
            mcardStore(&mCard);
            if (mCard.writeStatus != 0) {
                mCard.accessType = 2;
                simulatorPrepareMessage(S_M_CARD_SV09);
                simulatorDrawMCardText();
            }

            toggle = false;
            j = NUM_DATA_BLOCKS(mCard.file.game.size);
            for (i = 0; i < (u32)j; i++) {
                if (mCard.file.game.writtenBlocks[i] == true) {
                    index = i;
                    toggle = true;
                    break;
                }
            }

            if (toggle != true) {
                if (mCard.file.game.writtenConfig == true) {
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
#endif

            if (mCard.saveToggle == false) {
                mCard.saveToggle = true;
                mcardOpenDuringGame(&mCard);
            }

            if (toggle != true && mCard.writeStatus == 0 || mCard.saveToggle != true) {
                if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
                    return false;
                }

#if IS_OOT
#if VERSION != MQ_J
                if (gpSystem->eTypeROM == SRT_ZELDA1)
#endif
                {
                    if (mCard.saveToggle == true) {
                        do {
                            mcardMenu(&mCard, MC_M_SV12, &command);
                            if (!SIMULATOR_TEST_RESET(false, false, true, false)) {
                                return false;
                            }
                        } while (mCard.wait == true);
                    }
                }
#endif
                break;
            }
        }

        bWrite2Card = false;
        mCard.accessType = 0;
    }

    return true;
}

#if IS_MM
static void convert_i8i5(void* i8buf, void* i5buf, u32 num) {
    const u8* i8ptr;
    u8* i5ptr;
    s32 bitcnt;
    s32 bitcnt2;
    u32 bits;
    u32 i;
    u32 c1;

    i8ptr = i8buf;
    i5ptr = i5buf;
    bitcnt = 8;
    bits = 0;

    for (i = 0; i < num; i++) {
        c1 = (*i8ptr) * 0x1F;
        c1 = (c1 + 0x80) / 255;
        bitcnt2 = bitcnt - 5;
        i8ptr++;

        if (bitcnt2 > 0) {
            bits |= c1 << bitcnt2;
        } else {
            bits = (c1 >> (-bitcnt2)) | bits;
            bitcnt = bits;
            *i5ptr = bitcnt;
            bitcnt2 += 8;
            bits = c1 << bitcnt2;
            i5ptr++;
        }

        bitcnt = bitcnt2;
    }

    if (bitcnt < 8) {
        *i5ptr = bits;
    }
}

static void convert_i5i8(void* i5buf, void* i8buf, u32 num) {
    const u8* i5ptr;
    u8* i8ptr;
    s32 bitcnt;
    s32 bitcnt2;
    u32 bits;
    u32 i;
    u32 c1;

    i8ptr = i8buf;
    i5ptr = i5buf;
    bits = *i5ptr++;
    bitcnt = 8;

    for (i = 0; i < num; i++) {
        bitcnt2 = bitcnt - 5;

        if (bitcnt2 > 0) {
            c1 = bits >> bitcnt2;
        } else {
            c1 = bits << (-bitcnt2);
            bits = *i5ptr++;
            bitcnt2 += 8;
            c1 = c1 | (bits >> bitcnt2);
        }

        *i8ptr = (c1 & 0x1F) * 255 / 31;
        bitcnt = bitcnt2;
        i8ptr++;
    }
}

bool mcardSaveCamera(s32 value) {
    Frame* pFrame;
    void* i8Buffer;
    void* i5Buffer;
    u8* ptr;

    pFrame = SYSTEM_FRAME(gpSystem);

#if IS_MM_EU
    ptr = &((u8*)SYSTEM_RAM(gpSystem)->pBuffer)[0x001E6560];
#else
    ptr = &((u8*)SYSTEM_RAM(gpSystem)->pBuffer)[0x001EE900];
#endif

    if (!xlHeapTake(&i8Buffer, 0x4600)) {
        return false;
    }

    if (!xlHeapTake(&i5Buffer, 0x2BC0)) {
        return false;
    }

    if (xlHeapCopy(i8Buffer, pFrame->nCameraBuffer, 0x4600) == 0) {
        return false;
    }

    convert_i8i5(i8Buffer, i5Buffer, 0x4600);
    memcpy(ptr, i5Buffer, 0x2BC0);

    if (!xlHeapFree(&i5Buffer)) {
        return false;
    }

    if (!xlHeapFree(&i8Buffer)) {
        return false;
    }

    return true;
}

static bool mcardLoadZelda2Camera(MemCard* pMCard, u32 address) {
    Frame* pFrame;
    void* i8Buffer;
    void* i5Buffer;

    pFrame = gpSystem->pFrame;

    if (!xlHeapTake(&i8Buffer, 0x4600)) {
        return false;
    }

    if (!xlHeapTake(&i5Buffer, 0x2BC0)) {
        return false;
    }

    if (pMCard->file.game.buffer != NULL) {
        memcpy(i5Buffer, &pMCard->file.game.buffer[address + 0x10E0], 0x2BC0);
    }

    convert_i5i8(i5Buffer, i8Buffer, 0x4600);

    if (!xlHeapCopy(pFrame->nCameraBuffer, i8Buffer, 0x4600)) {
        return false;
    }

    if (!xlHeapFree(&i5Buffer)) {
        return false;
    }

    if (!xlHeapFree(&i8Buffer)) {
        return false;
    }

    NO_INLINE();
    return true;
}
#endif
