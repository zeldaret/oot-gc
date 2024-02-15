#ifndef _ROM_H
#define _ROM_H

#include "xlFileGCN.h"

typedef s32 pCallback_func(void);
typedef s32 pProgressCallback_func(f32);

// __anon_0x4CF87
typedef enum RomModeLoad {
    /* -1 */ RLM_NONE = -1,
    /*  0 */ RLM_PART,
    /*  1 */ RLM_FULL,
    /*  2 */ RLM_COUNT
} RomModeLoad;

// __anon_0x5219D
typedef enum RomCacheType {
    /* -1 */ RCT_NONE = -1,
    /*  0 */ RCT_RAM,
    /*  1 */ RCT_ARAM
} RomCacheType;

// __anon_0x4CFE6 
typedef struct RomBlock {
    /* 0x00 */ u32 iCache;
    /* 0x04 */ u32 nSize;
    /* 0x08 */ u32 nTickUsed;
    /* 0x0C */ char keep;
} RomBlock; // size = 0x10

typedef struct __anon_0x4D0FA {
    /* 0x00 */ int bWait;
    /* 0x04 */ pCallback_func* pCallback;
    /* 0x08 */ u8* pTarget;
    /* 0x0C */ u32 nSize;
    /* 0x10 */ u32 nOffset;
} __anon_0x4D0FA; // size = 0x14

typedef struct __anon_0x4D1DA {
    /* 0x00 */ int bWait;
    /* 0x04 */ int bDone;
    /* 0x08 */ int nResult;
    /* 0x0C */ u8* anData;
    /* 0x10 */ pCallback_func* pCallback;
    /* 0x14 */ int iCache;
    /* 0x18 */ int iBlock;
    /* 0x1C */ int nOffset;
    /* 0x20 */ u32 nOffset0;
    /* 0x24 */ u32 nOffset1;
    /* 0x28 */ u32 nSize;
    /* 0x2C */ u32 nSizeRead;
} __anon_0x4D1DA; // size = 0x30

// __anon_0x4D873
typedef struct Rom {
    /* 0x00000 */ struct unknownDeviceStruct* pHost;
    /* 0x00004 */ void* pBuffer;
    /* 0x00008 */ int bFlip;
    /* 0x0000C */ int bLoad;
    /* 0x00010 */ char acNameFile[513];
    /* 0x00214 */ u32 nSize;
    /* 0x00218 */ RomModeLoad eModeLoad;
    /* 0x0021C */ RomBlock aBlock[0x1000];
    /* 0x1021C */ u32 nTick;
    /* 0x10220 */ u8* pCacheRAM;
    /* 0x10224 */ u8 anBlockCachedRAM[1024];
    /* 0x10624 */ u8 anBlockCachedARAM[2046];
    /* 0x10E24 */ __anon_0x4D0FA copy;
    /* 0x10E38 */ __anon_0x4D1DA load;
    /* 0x10E68 */ int nCountBlockRAM;
    /* 0x10E6C */ int nSizeCacheRAM;
    /* 0x10E70 */ u8 acHeader[64];
    /* 0x10EB0 */ u32* anOffsetBlock;
    /* 0x10EB4 */ int nCountOffsetBlocks;
    /* 0x10EB8 */ DVDFileInfo fileInfo;
    /* 0x10EF4 */ int offsetToRom;
} Rom; // size = 0x10EF8

int romEvent(Rom* pROM, s32 nEvent, unknownDeviceStruct* pArgument);
int romGetImage(Rom* pROM, char* acNameFile);
int romSetImage(Rom* pROM, char* szNameFile);
int romSetCacheSize(Rom* pROM, int nSize);
int romUpdate(Rom* pROM);
int romCopyImmediate(Rom* pROM, void* pTarget, int nOffsetROM, int nSize);
s32 romCopy(Rom* pROM, void* pTarget, s32 nOffset, s32 nSize, pCallback_func* pCallback);
int romTestCode(Rom* pROM, char* acCode);
int romGetCode(Rom* pROM, char* acCode);
int romGetPC(Rom* pROM, u64* pnPC);

static int romPut8(Rom* pROM, u32 nAddress, s8* pData);
static int romPut16(Rom* pROM, u32 nAddress, s16* pData);
static int romPut32(Rom* pROM, u32 nAddress, s32* pData);
static int romPut64(Rom* pROM, u32 nAddress, s64* pData);

static int romGet8(Rom* pROM, u32 nAddress, s8* pData);
static int romGet16(Rom* pROM, u32 nAddress, s16* pData);
static int romGet32(Rom* pROM, u32 nAddress, s32* pData);
static int romGet64(Rom* pROM, u32 nAddress, s64* pData);

static int romPutDebug8(Rom* pROM, u32 nAddress, s8* pData);
static int romPutDebug16(Rom* pROM, u32 nAddress, s16* pData);
static int romPutDebug32(Rom* pROM, u32 nAddress, s32* pData);
static int romPutDebug64(Rom* pROM, u32 nAddress, s64* pData);

static int romGetDebug8(Rom* pROM, u32 nAddress, s8* pData);
static int romGetDebug16(Rom* pROM, u32 nAddress, s16* pData);
static int romGetDebug32(Rom* pROM, u32 nAddress, s32* pData);
static int romGetDebug64(Rom* pROM, u32 nAddress, s64* pData);

#endif
