#ifndef _ROM_H
#define _ROM_H

#include "dolphin.h"
#include "emulator/xlFileGCN.h"
#include "emulator/xlObject.h"

typedef bool UnknownCallbackFunc(void);
typedef bool ProgressCallbackFunc(f32 progressPercent);

// __anon_0x4CF87
typedef enum RomModeLoad {
    RLM_NONE = -1,
    RLM_PART = 0,
    RLM_FULL = 1,
    RLM_COUNT = 2,
} RomModeLoad;

// __anon_0x5219D
typedef enum RomCacheType {
    RCT_NONE = -1,
    RCT_RAM = 0,
    RCT_ARAM = 1,
} RomCacheType;

// __anon_0x4CFE6
typedef struct RomBlock {
    /* 0x00 */ s32 iCache; // Stores cache index `i` if the block is in RAM, or `-(i + 1)` if the block is in ARAM
    /* 0x04 */ u32 nSize;
    /* 0x08 */ u32 nTickUsed;
    /* 0x0C */ s8 keep;
} RomBlock; // size = 0x10

// __anon_0x4D0FA
typedef struct RomCopyState {
    /* 0x00 */ bool bWait;
    /* 0x04 */ UnknownCallbackFunc* pCallback;
    /* 0x08 */ u8* pTarget;
    /* 0x0C */ u32 nSize;
    /* 0x10 */ u32 nOffset;
} RomCopyState; // size = 0x14

// __anon_0x4D1DA
typedef struct RomLoadState {
    /* 0x00 */ bool bWait;
    /* 0x04 */ bool bDone;
    /* 0x08 */ s32 nResult;
    /* 0x0C */ u8* anData;
    /* 0x10 */ UnknownCallbackFunc* pCallback;
    /* 0x14 */ s32 iCache;
    /* 0x18 */ s32 iBlock;
    /* 0x1C */ s32 nOffset;
    /* 0x20 */ u32 nOffset0;
    /* 0x24 */ u32 nOffset1;
    /* 0x28 */ u32 nSize;
    /* 0x2C */ u32 nSizeRead;
} RomLoadState; // size = 0x30

// __anon_0x4D873
typedef struct Rom {
    /* 0x00000 */ void* pHost;
    /* 0x00004 */ void* pBuffer;
    /* 0x00008 */ bool bFlip;
    /* 0x0000C */ bool bLoad;
    /* 0x00010 */ char acNameFile[513];
    /* 0x00214 */ u32 nSize;
    /* 0x00218 */ RomModeLoad eModeLoad;
    /* 0x0021C */ RomBlock aBlock[4096];
    /* 0x1021C */ u32 nTick;
    /* 0x10220 */ u8* pCacheRAM;
    /* 0x10224 */ u8 anBlockCachedRAM[1024]; // Bitfield, one bit per block
    /* 0x10624 */ u8 anBlockCachedARAM[2046]; // Bitfield, one bit per block
    /* 0x10E24 */ RomCopyState copy;
    /* 0x10E38 */ RomLoadState load;
    /* 0x10E68 */ s32 nCountBlockRAM;
    /* 0x10E6C */ s32 nSizeCacheRAM;
    /* 0x10E70 */ u8 acHeader[64];
    /* 0x10EB0 */ u32* anOffsetBlock;
    /* 0x10EB4 */ s32 nCountOffsetBlocks;
    /* 0x10EB8 */ DVDFileInfo fileInfo;
    /* 0x10EF4 */ s32 offsetToRom;
} Rom; // size = 0x10EF8

bool romGetPC(Rom* pROM, u64* pnPC);
bool romGetCode(Rom* pROM, char* acCode);
bool romTestCode(Rom* pROM, char* acCode);

//! NOTE: The debug informations indicates that `nSize` is unsigned, but the
//! generated code seems to treat it as signed.
bool romCopy(Rom* pROM, void* pTarget, s32 nOffset, s32 nSize, UnknownCallbackFunc* pCallback);
bool romCopyImmediate(Rom* pROM, void* pTarget, s32 nOffsetROM, s32 nSize);

bool romUpdate(Rom* pROM);
bool romSetCacheSize(Rom* pROM, s32 nSize);
bool romSetImage(Rom* pROM, char* szNameFile);
bool romGetImage(Rom* pROM, char* acNameFile);
bool romEvent(Rom* pROM, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassROM;

#endif
