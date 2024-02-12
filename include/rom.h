#ifndef _ROM_H
#define _ROM_H

#include "xlFileGCN.h"

// __anon_0x4CF87
// size: 0x4
typedef enum RomModeLoad {
    RLM_NONE = -1,
    RLM_PART = 0,
    RLM_FULL = 1,
    RLM_COUNT_ = 2
} RomModeLoad;

// __anon_0x4CFE6
// size: 0x10
typedef struct RomBlock {
    int iCache; // 0x0
    u32 nSize; // 0x4
    u32 nTickUsed; // 0x8
    char keep; // 0xC
} RomBlock;

// size: 0x14
typedef struct __anon_0x4D0FA {
    int bWait; // 0x0
    int (*pCallback)(); // 0x4
    u8* pTarget; // 0x8
    u32 nSize; // 0xC
    u32 nOffset; // 0x10
} __anon_0x4D0FA;

// size: 0x30
typedef struct __anon_0x4D1DA {
    int bWait; // 0x0
    int bDone; // 0x4
    int nResult; // 0x8
    u8* anData; // 0xC
    int (*pCallback)(); // 0x10
    int iCache; // 0x14
    int iBlock; // 0x18
    int nOffset; // 0x1C
    u32 nOffset0; // 0x20
    u32 nOffset1; // 0x24
    u32 nSize; // 0x28
    u32 nSizeRead; // 0x2C
} __anon_0x4D1DA;

// __anon_0x4D873
// size: 0x10EF8
typedef struct Rom {
    void* pHost; // 0x0
    void* pBuffer; // 0x4
    int bFlip; // 0x8
    int bLoad; // 0xC
    char acNameFile[513]; // 0x10
    u32 nSize; // 0x214
    RomModeLoad eModeLoad; // 0x218
    RomBlock aBlock[4096]; // 0x21C
    u32 nTick; // 0x1021C
    u8* pCacheRAM; // 0x10220
    u8 anBlockCachedRAM[1024]; // 0x10224
    u8 anBlockCachedARAM[2046]; // 0x10624
    __anon_0x4D0FA copy; // 0x10E24
    __anon_0x4D1DA load; // 0x10E38
    int nCountBlockRAM; // 0x10E68
    int nSizeCacheRAM; // 0x10E6C
    u8 acHeader[64]; // 0x10E70
    u32* anOffsetBlock; // 0x10EB0
    int nCountOffsetBlocks; // 0x10EB4
    DVDFileInfo fileInfo; // 0x10EB8
    int offsetToRom; // 0x10EF4
} Rom;

int romEvent(Rom* pROM, int nEvent, void* pArgument);
int romGetImage(Rom* pROM, char* acNameFile);
int romSetImage(Rom* pROM, char* szNameFile);
int romSetCacheSize(Rom* pROM, int nSize);
int romUpdate(Rom* pROM);
int romCopyImmediate(Rom* pROM, void* pTarget, int nOffsetROM, u32 nSize);
int romCopy(Rom* pROM, void* pTarget, int nOffset, u32 nSize, int (*pCallback)());
int romTestCode(Rom* pROM, char* acCode);
int romGetCode(Rom* pROM, char* acCode);
int romGetPC(Rom* pROM, u64* pnPC);

#endif
