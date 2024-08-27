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

#if IS_EU
typedef struct tXL_SAVE {
    /* 0x0 */ s32 nPosition;
    /* 0x4 */ s32 nLineNumber;
} tXL_SAVE; // size = 0x8

typedef struct tXL_FILE {
    /* 0x00 */ void* pData;
    /* 0x04 */ char* acLine;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ s32 nAttributes;
    /* 0x10 */ s32 nSize;
    /* 0x14 */ s32 nOffset;
    /* 0x18 */ XlFileType eType;
    /* 0x1C */ s32 iLine;
    /* 0x20 */ s32 nLineNumber;
    /* 0x24 */ DVDFileInfo info;
} tXL_FILE; // size = 0x60
#else
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
#endif

bool xlFileSetOpen(DVDOpenCallback pfOpen);
bool xlFileSetRead(DVDReadCallback pfRead);
bool xlFileGetSize(s32* pnSize, char* szFileName);
bool xlFileOpen(tXL_FILE** ppFile, XlFileType eType, char* szFileName);
bool xlFileClose(tXL_FILE** ppFile);
bool xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes);
bool xlFileSetPosition(tXL_FILE* pFile, s32 nOffset);
bool xlFileEvent(tXL_FILE* pFile, s32 nEvent, void* pArgument);

#endif
