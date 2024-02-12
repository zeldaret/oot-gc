#ifndef _CPU_H
#define _CPU_H

#include "types.h"

// size: 0x34
typedef struct __anon_0x3EB4F {
    int nType; // 0x0
    void* pObject; // 0x4
    int nOffsetAddress; // 0x8
    int (*pfGet8)(void* /* unknown0 */, u32 /* unknown1 */, s8* /* unknown2 */); // 0xC
    int (*pfGet16)(void* /* unknown0 */, u32 /* unknown1 */, s16* /* unknown2 */); // 0x10
    int (*pfGet32)(void* /* unknown0 */, u32 /* unknown1 */, s32* /* unknown2 */); // 0x14
    int (*pfGet64)(void* /* unknown0 */, u32 /* unknown1 */, s64* /* unknown2 */); // 0x18
    int (*pfPut8)(void* /* unknown0 */, u32 /* unknown1 */, s8* /* unknown2 */); // 0x1C
    int (*pfPut16)(void* /* unknown0 */, u32 /* unknown1 */, s16* /* unknown2 */); // 0x20
    int (*pfPut32)(void* /* unknown0 */, u32 /* unknown1 */, s32* /* unknown2 */); // 0x24
    int (*pfPut64)(void* /* unknown0 */, u32 /* unknown1 */, s64* /* unknown2 */); // 0x28
    u32 nAddressPhysical0; // 0x2C
    u32 nAddressPhysical1; // 0x30
} __anon_0x3EB4F;

int cpuSetDevicePut(__anon_0x3EB4F* pDevice,
                    int (*pfPut8)(void* /* unknown0 */, u32 /* unknown1 */, s8* /* unknown2 */),
                    int (*pfPut16)(void* /* unknown0 */, u32 /* unknown1 */, s16* /* unknown2 */),
                    int (*pfPut32)(void* /* unknown0 */, u32 /* unknown1 */, s32* /* unknown2 */),
                    int (*pfPut64)(void* /* unknown0 */, u32 /* unknown1 */, s64* /* unknown2 */));
int cpuSetDeviceGet(__anon_0x3EB4F* pDevice,
                    int (*pfGet8)(void* /* unknown0 */, u32 /* unknown1 */, s8* /* unknown2 */),
                    int (*pfGet16)(void* /* unknown0 */, u32 /* unknown1 */, s16* /* unknown2 */),
                    int (*pfGet32)(void* /* unknown0 */, u32 /* unknown1 */, s32* /* unknown2 */),
                    int (*pfGet64)(void* /* unknown0 */, u32 /* unknown1 */, s64* /* unknown2 */));

#endif
