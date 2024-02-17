#ifndef _XL_FILE_GCN_H
#define _XL_FILE_GCN_H

#include "types.h"

//! TODO: Move DVDDiskID etc. to Dolphin SDK headers

typedef struct DVDDiskID {
    /* 0x0 */ char gameName[4];
    /* 0x4 */ char company[2];
    /* 0x6 */ u8 diskNumber;
    /* 0x7 */ u8 gameVersion;
    /* 0x8 */ u8 streaming;
    /* 0x9 */ u8 streamingBufSize;
    /* 0xA */ u8 padding[22];
} DVDDiskID; // size = 0x20

typedef struct DVDCommandBlock DVDCommandBlock;

struct DVDCommandBlock {
    /* 0x00 */ DVDCommandBlock* next;
    /* 0x04 */ DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ long state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* addr;
    /* 0x1C */ u32 currTransferSize;
    /* 0x20 */ u32 transferredSize;
    /* 0x24 */ DVDDiskID* id;
    /* 0x28 */ void (*callback)(long /* unknown0 */, DVDCommandBlock* /* unknown1 */);
    /* 0x2C */ void* userData;
}; // size = 0x30

typedef struct DVDFileInfo DVDFileInfo;

struct DVDFileInfo {
    /* 0x00 */ DVDCommandBlock cb;
    /* 0x30 */ u32 startAddr;
    /* 0x34 */ u32 length;
    /* 0x38 */ void (*callback)(long /* unknown0 */, DVDFileInfo* /* unknown1 */);
}; // size = 0x3C

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
