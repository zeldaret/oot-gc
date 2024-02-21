#include "xlFileGCN.h"
#include "xlObject.h"

//! TODO: missing from the sdk?
s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);

_XL_OBJECTTYPE gTypeFile = {
    "FILE",
    sizeof(tXL_FILE),
    NULL,
    (EventFunc)xlFileEvent,
};

static FileGcnOpenCallback gpfOpen;
static FileGcnReadCallback gpfRead;

s32 xlFileSetOpen(FileGcnOpenCallback pfOpen) {
    gpfOpen = pfOpen;
    return 1;
}

s32 xlFileSetRead(FileGcnReadCallback pfRead) {
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

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/xlFileGCN/xlFileGet.s")
#else
s32 xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes) {
    // Parameters
    // struct tXL_FILE* pFile; // r27
    // void* pTarget; // r28
    // s32 nSizeBytes; // r29

    s32 nOffset; // r6
    s32 nOffsetExtra; // r1+0x8
    s32 nSize; // r5
    s32 nSizeUsed; // r30

    nSizeBytes = nSizeBytes;
    nOffsetExtra = pFile->nOffset;
    nSize = pFile->nSize;

    if ((nOffsetExtra + nSizeBytes) > nSize) {
        nSizeBytes = nSize - nOffsetExtra;
    }

    if (nSizeBytes == 0) {
        *(s8*)(pTarget) = -1;
        return 0;
    }

    for (; nSizeBytes != 0;) {
        nSizeUsed = nSizeBytes;

        if (nSizeUsed > 0x1000) {
            nSizeUsed = 0x1000;
        }

        nOffset = pFile->nOffset & 0xFFFFFFFC;
        // nSizeBytes = nSizeBytes & 0xFFFFFFFC;

        if (gpfRead != NULL) {
            gpfRead(&pFile->info, pFile->pData, nSizeBytes, ((s32)pFile->pBuffer + nOffset), NULL);
        } else {
            DVDReadPrio(&pFile->info, pFile->pData, nSizeBytes, ((s32)pFile->pBuffer + nOffset), 2);
        }

        if (!xlHeapCopy(pTarget, (void*)((s32)pFile->pBuffer + nOffset), nSizeUsed)) {
            return 0;
        }

        *(s32*)(pTarget) += nSizeUsed;
        nSizeBytes -= nSizeUsed;
        pFile->nOffset += nSizeUsed;
    }

    return 1;
}
#endif

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
