#include "emulator/xlFileGCN.h"
#include "dolphin.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"

#if IS_EU
extern _XL_OBJECTTYPE gTypeFile;
#else
// this is inside xlFile.c on the european versions
_XL_OBJECTTYPE gTypeFile = {
    "FILE",
    sizeof(tXL_FILE),
    NULL,
    (EventFunc)xlFileEvent,
};
#endif

static DVDOpenCallback gpfOpen;
static DVDReadCallback gpfRead;

bool xlFileSetOpen(DVDOpenCallback pfOpen) {
    gpfOpen = pfOpen;
    return true;
}

bool xlFileSetRead(DVDReadCallback pfRead) {
    gpfRead = pfRead;
    return true;
}

#if !IS_EU
// this function is inside xlFile.c on the european versions
bool xlFileGetSize(s32* pnSize, char* szFileName) {
    tXL_FILE* pFile;

    if (xlFileOpen(&pFile, XLFT_BINARY, szFileName)) {
        if (pnSize != NULL) {
            *pnSize = pFile->nSize;
        }

        if (!xlFileClose(&pFile)) {
            return false;
        }

        return true;
    }

    return false;
}
#endif

static inline bool xlFileGetFile(tXL_FILE** ppFile, char* szFileName) {
    if (gpfOpen != NULL) {
        return gpfOpen(szFileName, &(*ppFile)->info);
    } else {
        return DVDOpen(szFileName, &(*ppFile)->info);
    }
}

bool xlFileOpen(tXL_FILE** ppFile, XlFileType eType, char* szFileName) {
    if (!xlObjectMake((void**)ppFile, NULL, &gTypeFile)) {
        return false;
    }

    if (xlFileGetFile(ppFile, szFileName)) {
        (*ppFile)->eType = eType;
        (*ppFile)->nSize = (*ppFile)->info.length;
        (*ppFile)->pData = &(*ppFile)->info;

        return true;
    }

    xlObjectFree((void**)ppFile);
    return false;
}

bool xlFileClose(tXL_FILE** ppFile) {
    if (!xlObjectFree((void**)ppFile)) {
        return false;
    }

    return true;
}

bool xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes) {
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
        return false;
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
            return false;
        }
        pTarget = (void*)((s32)pTarget + nSizeUsed);
        nSizeBytes -= nSizeUsed;
        pFile->nOffset += nSizeUsed;
    }
    return true;
}

bool xlFileSetPosition(tXL_FILE* pFile, s32 nOffset) {
    if ((nOffset >= 0) && (nOffset < pFile->nSize)) {
        pFile->nOffset = nOffset;
        return true;
    }

    return false;
}

#if IS_EU
bool xlFileGetPosition(tXL_FILE* pFile, s32* pnOffset) {
    if (pnOffset != NULL) {
        *pnOffset = pFile->nOffset;
    }

    return true;
}
#endif

bool xlFileEvent(tXL_FILE* pFile, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pFile->nSize = 0;
            pFile->nOffset = 0;
            pFile->pData = NULL;
#if IS_EU
            pFile->acLine = NULL;
#endif
            if (!xlHeapTake(&pFile->pBuffer, 0x1024 | 0x30000000)) {
                return false;
            }
            break;
        case 3:
#if IS_EU
            if (pFile->acLine != NULL) {
                if (!xlHeapFree(&pFile->acLine)) {
                    return false;
                }
            }
#endif
            DVDClose(&pFile->info);
            if (!xlHeapFree(&pFile->pBuffer)) {
                return false;
            }
            break;
        case 0:
        case 1:
        case 4:
            break;
        default:
            return false;
    }

    return true;
}
