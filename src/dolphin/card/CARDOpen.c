#include "dolphin/card.h"

bool __CARDCompareFileName(CARDDir* entry, const char* fileName) {
    char* entName;
    char c1;
    char c2;
    int n;

    entName = (char*)entry->fileName;
    n = CARD_FILENAME_MAX;
    while (0 <= --n) {
        if ((c1 = *entName++) != (c2 = *fileName++)) {
            return false;
        } else if (c2 == '\0') {
            return true;
        }
    }

    if (*fileName == '\0') {
        return true;
    }

    return false;
}

s32 __CARDAccess(CARDControl* card, CARDDir* entry) {
#if IS_MQ
#define DISK_ID card->diskID
#else
    const DVDDiskID* diskID = card->diskID;
#define DISK_ID diskID
#endif

    if (entry->gameName[0] == 0xFF) {
        return CARD_RESULT_NOFILE;
    }

    if (DISK_ID == &__CARDDiskNone ||
        (memcmp(entry->gameName, DISK_ID->gameName, 4) == 0 && memcmp(entry->company, DISK_ID->company, 2) == 0)) {
        return CARD_RESULT_READY;
    }

    return CARD_RESULT_NOPERM;
}

#if IS_MQ
s32 __CARDIsPublic(CARDDir* entry) {
    if (entry->gameName[0] == 0xFF) {
        return CARD_RESULT_NOFILE;
    }

    if (entry->permission & CARD_ATTR_PUBLIC) {
        return CARD_RESULT_READY;
    }

    return CARD_RESULT_NOPERM;
}
#else
s32 __CARDIsWritable(CARDControl* card, CARDDir* entry) {
    const DVDDiskID* diskID = card->diskID;
    s32 result;
    u8 perm;

    result = __CARDAccess(card, entry);
    if (result == CARD_RESULT_NOPERM) {
        perm = (u8)(entry->permission & __CARDPermMask);

        if ((perm & 0x20) && (memcmp(entry->gameName, __CARDDiskNone.gameName, 4) == 0 &&
                              memcmp(entry->company, __CARDDiskNone.company, 2) == 0)) {
            return CARD_RESULT_READY;
        }

        if ((perm & 0x40) && (memcmp(entry->gameName, __CARDDiskNone.gameName, 4) == 0 &&
                              memcmp(entry->company, diskID->company, 2) == 0)) {
            return CARD_RESULT_READY;
        }
    }
    return result;
}

s32 __CARDIsReadable(CARDControl* card, CARDDir* entry) {
    s32 result = __CARDIsWritable(card, entry);

    if (result == CARD_RESULT_NOPERM && (entry->permission & 0x4)) {
        return CARD_RESULT_READY;
    }

    return result;
}
#endif

s32 __CARDGetFileNo(CARDControl* card, char* fileName, s32* outFileNo) {
    CARDDir* dir;
    CARDDir* entry;
    s32 fileNo;
    s32 result;

    if (!card->attached) {
        return CARD_RESULT_NOCARD;
    }

    dir = __CARDGetDirBlock(card);
    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        entry = &dir[fileNo];
        result = __CARDAccess(card, entry);
        if (result < 0) {
            continue;
        }
        if (__CARDCompareFileName(entry, fileName)) {
            *outFileNo = fileNo;
            return CARD_RESULT_READY;
        }
    }

    return CARD_RESULT_NOFILE;
}

s32 CARDOpen(s32 chan, char* fileName, CARDFileInfo* fileInfo) {
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;
    s32 fileNo;

    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (0 <= result) {
        dir = __CARDGetDirBlock(card);
        ent = &dir[fileNo];
        if (!CARDIsValidBlockNo(card, ent->startBlock)) {
            result = CARD_RESULT_BROKEN;
        } else {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}

s32 CARDClose(CARDFileInfo* fileInfo) {
    CARDControl* card;
    s32 result;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    fileInfo->chan = -1;
    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

bool __CARDIsOpened(CARDControl* card, s32 fileNo) { return false; }
