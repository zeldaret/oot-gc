#ifndef _XL_FILE_GCN_H
#define _XL_FILE_GCN_H

#include "dolphin.h"

typedef bool (*DVDOpenCallback)(char*, DVDFileInfo*);
typedef bool (*DVDReadCallback)(DVDFileInfo*, void*, s32, s32, DVDCallback);

// __anon_0x2757
typedef enum XlFileType {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1,
} XlFileType;

typedef struct tXL_FILE {
    /* 0x00 */ s32 iBuffer;
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ s32 nAttributes;
    /* 0x10 */ s32 nSize;
    /* 0x14 */ s32 nOffset;
    /* 0x18 */ XlFileType eType;
    /* 0x1C */ DVDFileInfo info;
} tXL_FILE; // size = 0x58

bool xlFileSetOpen(DVDOpenCallback pfOpen);
bool xlFileSetRead(DVDReadCallback pfRead);
bool xlFileGetSize(s32* pnSize, char* szFileName);
bool xlFileOpen(tXL_FILE** ppFile, XlFileType eType, char* szFileName);
bool xlFileClose(tXL_FILE** ppFile);
bool xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes);
bool xlFileSetPosition(tXL_FILE* pFile, s32 nOffset);
bool xlFileEvent(tXL_FILE* pFile, s32 nEvent, void* pArgument);

#endif
