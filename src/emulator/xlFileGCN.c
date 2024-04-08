#include "emulator/xlFileGCN.h"
#include "dolphin.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"

_XL_OBJECTTYPE gTypeFile = {
    "FILE",
    sizeof(tXL_FILE),
    NULL,
    (EventFunc)xlFileEvent,
};

static DVDOpenCallback gpfOpen;
static DVDReadCallback gpfRead;

s32 xlFileSetOpen(DVDOpenCallback pfOpen) {
    gpfOpen = pfOpen;
    return 1;
}

s32 xlFileSetRead(DVDReadCallback pfRead) {
    gpfRead = pfRead;
    return 1;
}

s32 xlFileGetSize(s32* pnSize, char* szFileName) {
    tXL_FILE* pFile;

    if (xlFileOpen(&pFile, XLFT_BINARY, szFileName)) {
        if (pnSize != NULL) {
            *pnSize = pFile->nSize;
        }

        if (!xlFileClose(&pFile)) {
            return 0;
        }

        return 1;
    }

    return 0;
}

inline s32 xlFileGetFile(tXL_FILE** ppFile, char* szFileName) {
    if (gpfOpen != NULL) {
        return gpfOpen(szFileName, &(*ppFile)->info);
    } else {
        return DVDOpen(szFileName, &(*ppFile)->info);
    }
}

s32 xlFileOpen(tXL_FILE** ppFile, XlFileType eType, char* szFileName) {
    if (!xlObjectMake(ppFile, NULL, &gTypeFile)) {
        return 0;
    }

    if (xlFileGetFile(ppFile, szFileName)) {
        (*ppFile)->eType = eType;
        (*ppFile)->nSize = (*ppFile)->info.length;
        (*ppFile)->pData = &(*ppFile)->info;

        return 1;
    }

    xlObjectFree(ppFile);
    return 0;
}

s32 xlFileClose(tXL_FILE** ppFile) {
    if (!xlObjectFree(ppFile)) {
        return 0;
    }

    return 1;
}

s32 xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes) {
    s32 nOffset;
    s32 nOffsetExtra;
    s32 nSize;
    s32 nSizeUsed;

    nOffset = pFile->nOffset;
    nSize = pFile->nSize;
    if (nOffset + nSizeBytes > nSize) {
        nSizeBytes = nSize - nOffset;
    }
    if (nSizeBytes == 0) {
        *(s8*)pTarget = 0xFF;
        return 0;
    }

    while (nSizeBytes != 0) {
        nSizeUsed = nSizeBytes;
        if (nSizeUsed > 0x1000) {
            nSizeUsed = 0x1000;
        }
        nOffset = pFile->nOffset & 0xFFFFFFFC;
        nOffsetExtra = pFile->nOffset & 0x3;
        nSize = (nSizeUsed + nOffsetExtra + 0x1F) & 0xFFFFFFE0;
        if (gpfRead != NULL) {
            gpfRead(pFile->pData, pFile->pBuffer, nSize, nOffset, NULL);
        } else {
            DVDReadPrio(pFile->pData, pFile->pBuffer, nSize, nOffset, 2);
        }
        if (!xlHeapCopy(pTarget, (void*)((u8*)pFile->pBuffer + nOffsetExtra), nSizeUsed)) {
            return 0;
        }
        pTarget = (void*)((s32)pTarget + nSizeUsed);
        nSizeBytes -= nSizeUsed;
        pFile->nOffset += nSizeUsed;
    }
    return 1;
}

s32 xlFileSetPosition(tXL_FILE* pFile, s32 nOffset) {
    if ((nOffset >= 0) && (nOffset < pFile->nSize)) {
        pFile->nOffset = nOffset;
        return 1;
    }

    return 0;
}

s32 xlFileEvent(tXL_FILE* pFile, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pFile->nSize = 0;
            pFile->nOffset = 0;
            pFile->pData = NULL;
            if (!xlHeapTake(&pFile->pBuffer, 0x1024 | 0x30000000)) {
                return 0;
            }
            break;
        case 3:
            DVDClose(&pFile->info);
            if (!xlHeapFree(&pFile->pBuffer)) {
                return 0;
            }
            break;
        case 0:
        case 1:
        case 4:
            break;
        default:
            return 0;
    }

    return 1;
}
