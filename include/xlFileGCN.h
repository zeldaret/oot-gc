#ifndef _XL_FILE_GCN_H
#define _XL_FILE_GCN_H

#include "dolphin/dvd.h"
#include "dolphin/types.h"

typedef enum __anon_0x2757 {
    XLFT_NONE = -1,
    XLFT_TEXT = 0,
    XLFT_BINARY = 1,
} __anon_0x2757;

typedef struct tXL_FILE {
    /* 0x00 */ s32 iBuffer;
    /* 0x04 */ void* pData;
    /* 0x08 */ void* pBuffer;
    /* 0x0C */ s32 nAttributes;
    /* 0x10 */ s32 nSize;
    /* 0x14 */ s32 nOffset;
    /* 0x18 */ __anon_0x2757 eType;
    /* 0x1C */ DVDFileInfo info;
} tXL_FILE; // size = 0x58

s32 xlFileEvent(tXL_FILE* pFile, s32 nEvent);
s32 xlFileSetPosition(tXL_FILE* pFile, s32 nOffset);
s32 xlFileGet(tXL_FILE* pFile, void* pTarget, s32 nSizeBytes);
s32 xlFileClose(tXL_FILE** ppFile);
s32 xlFileOpen(tXL_FILE** ppFile, __anon_0x2757 eType, char* szFileName);
s32 xlFileGetSize(s32* pnSize, char* szFileName);
s32 xlFileSetRead(s32 (*pfRead)(DVDFileInfo* /* unknown0 */, void* /* unknown1 */, s32 /* unknown2 */,
                                s32 /* unknown3 */,
                                void (* /* unknown4 */)(long /* unknown0 */, DVDFileInfo* /* unknown1 */)));
s32 xlFileSetOpen(s32 (*pfOpen)(char* /* unknown0 */, DVDFileInfo* /* unknown1 */));

#endif
