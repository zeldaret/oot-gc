#ifndef _CPU_H
#define _CPU_H

#include "types.h"

typedef s32 (*Put8Func)(struct Rom* pROM, u32 nAddress, s8* pData);
typedef s32 (*Put16Func)(struct Rom* pROM, u32 nAddress, s16* pData);
typedef s32 (*Put32Func)(struct Rom* pROM, u32 nAddress, s32* pData);
typedef s32 (*Put64Func)(struct Rom* pROM, u32 nAddress, s64* pData);

typedef s32 (*Get8Func)(struct Rom* pROM, u32 nAddress, s8* pData);
typedef s32 (*Get16Func)(struct Rom* pROM, u32 nAddress, s16* pData);
typedef s32 (*Get32Func)(struct Rom* pROM, u32 nAddress, s32* pData);
typedef s32 (*Get64Func)(struct Rom* pROM, u32 nAddress, s64* pData);

typedef struct __anon_0x3EB4F {
    /* 0x00 */ s32 nType;
    /* 0x04 */ void* pObject;
    /* 0x08 */ s32 nOffsetAddress;
    /* 0x0C */ Get8Func pfGet8;
    /* 0x10 */ Get16Func pfGet16;
    /* 0x14 */ Get32Func pfGet32;
    /* 0x18 */ Get64Func pfGet64;
    /* 0x1C */ Put8Func pfPut8;
    /* 0x20 */ Put16Func pfPut16;
    /* 0x24 */ Put32Func pfPut32;
    /* 0x28 */ Put64Func pfPut64;
    /* 0x2C */ u32 nAddressPhysical0;
    /* 0x30 */ u32 nAddressPhysical1;
} __anon_0x3EB4F; // size = 0x34

s32 cpuSetDevicePut(__anon_0x3EB4F* pDevice, void* pArgument, Put8Func pfPut8, Put16Func pfPut16, Put32Func pfPut32,
                    Put64Func pfPut64);

s32 cpuSetDeviceGet(__anon_0x3EB4F* pDevice, void* pArgument, Get8Func pfGet8, Get16Func pfGet16, Get32Func pfGet32,
                    Get64Func pfGet64);

#endif
