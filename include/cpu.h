#ifndef _CPU_H
#define _CPU_H

#include "types.h"

typedef int (*pfPut8_func)(struct Rom* pROM, u32 nAddress, s8* pData);
typedef int (*pfPut16_func)(struct Rom* pROM, u32 nAddress, s16* pData);
typedef int (*pfPut32_func)(struct Rom* pROM, u32 nAddress, s32* pData);
typedef int (*pfPut64_func)(struct Rom* pROM, u32 nAddress, s64* pData);

typedef int (*pfGet8_func)(struct Rom* pROM, u32 nAddress, s8* pData);
typedef int (*pfGet16_func)(struct Rom* pROM, u32 nAddress, s16* pData);
typedef int (*pfGet32_func)(struct Rom* pROM, u32 nAddress, s32* pData);
typedef int (*pfGet64_func)(struct Rom* pROM, u32 nAddress, s64* pData);

typedef struct __anon_0x3EB4F {
    /* 0x00 */ int nType;
    /* 0x04 */ void* pObject;
    /* 0x08 */ int nOffsetAddress;
    /* 0x0C */ pfGet8_func pfGet8;
    /* 0x10 */ pfGet16_func pfGet16;
    /* 0x14 */ pfGet32_func pfGet32;
    /* 0x18 */ pfGet64_func pfGet64;
    /* 0x1C */ pfPut8_func pfPut8;
    /* 0x20 */ pfPut16_func pfPut16;
    /* 0x24 */ pfPut32_func pfPut32;
    /* 0x28 */ pfPut64_func pfPut64;
    /* 0x2C */ u32 nAddressPhysical0;
    /* 0x30 */ u32 nAddressPhysical1;
} __anon_0x3EB4F; // size = 0x34

typedef struct unknownDeviceStruct {
    /* 0x00 */ int unk;
    /* 0x00 */ char unk2[0x20];
    /* 0x24 */ __anon_0x3EB4F* pDevice;
} unknownDeviceStruct;

int cpuSetDevicePut(__anon_0x3EB4F* pDevice, void* pArgument, 
    pfPut8_func pfPut8, pfPut16_func pfPut16, pfPut32_func pfPut32, pfPut64_func pfPut64);

int cpuSetDeviceGet(__anon_0x3EB4F* pDevice, void* pArgument, 
    pfGet8_func pfGet8, pfGet16_func pfGet16, pfGet32_func pfGet32, pfGet64_func pfGet64);

#endif
