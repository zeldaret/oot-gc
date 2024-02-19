#include "types.h"
#include "xlObject.h"
#include "cpu.h"
#include "system.h"

int simulatorWriteSRAM(unsigned int address, unsigned char* data, int size);
int simulatorReadSRAM(unsigned int address, unsigned char* data, int size);

// __anon_0x74AB9
typedef struct Sram {
    void* pHost; // 0x0
} Sram;

struct Ram;

int sramEvent(Sram* pSram, s32 nEvent, void* pArgument);

extern int ramGetBuffer(struct Ram* pRAM, void* ppRAM, u32 nOffset, u32* pnSize);
extern int simulatorWriteSRAM(unsigned int address, unsigned char* data, int size);

_XL_OBJECTTYPE gClassSram = {"SRAM", sizeof(Sram), NULL, (EventFunc)sramEvent};

s32 sramCopySRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(((System*)pSRAM->pHost)->apObject[SOT_RAM], &pTarget, nOffsetRAM, &nSize)) {
        return 0;
    }
    if (!simulatorReadSRAM(nOffsetSRAM & 0x7FFF, pTarget, nSize)) {
        return 0;
    }
    return 1;
}

s32 sramTransferSRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (!ramGetBuffer(((System*)pSRAM->pHost)->apObject[SOT_RAM], &pTarget, nOffsetRAM, &nSize)) {
        return 0;
    }
    if (!simulatorWriteSRAM(nOffsetSRAM & 0x7FFF, pTarget, nSize)) {
        return 0;
    }
    return 1;
}

static int sramPut8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s8));
    return 1;
}

static int sramPut16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s16));
    return 1;
}

static int sramPut32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s32));
    return 1;
}

static int sramPut64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s64));
    return 1;
}

static int sramGet8(Sram* pObject, u32 nAddress, s8* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s8));
    return 1;
}

static int sramGet16(Sram* pObject, u32 nAddress, s16* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s16));
    return 1;
}

static int sramGet32(Sram* pObject, u32 nAddress, s32* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s32));
    return 1;
}

static int sramGet64(Sram* pObject, u32 nAddress, s64* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(s64));
    return 1;
}

int sramEvent(Sram* pObject, s32 nEvent, void* pArgument) {
    Sram* pSram = (Sram*)pObject;

    switch (nEvent) {
        case 2:
            pSram->pHost = pArgument;
        case 0:
        case 1:
        case 3:
            break;

        case 0x1002:
            if (!cpuSetDevicePut(((System*)pSram->pHost)->apObject[SOT_CPU], pArgument, (Put8Func)sramPut8,
                                 (Put16Func)sramPut16, (Put32Func)sramPut32, (Put64Func)sramPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(((System*)pSram->pHost)->apObject[SOT_CPU], pArgument, (Get8Func)sramGet8,
                                 (Get16Func)sramGet16, (Get32Func)sramGet32, (Get64Func)sramGet64)) {
                return 0;
            }
        case 0x1003:
            break;

        default:
            return 0;
    }
    return 1;
}
