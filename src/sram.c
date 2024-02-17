#include "types.h"
#include "xlObject.h"

int simulatorWriteSRAM(unsigned int address, unsigned char* data, int size);
int simulatorReadSRAM(unsigned int address, unsigned char* data, int size);

#define OBJ_NAME "SRAM"

typedef struct Sram {
    struct sramHost* pHost; // 0x0
} Sram;
// __anon_0x74AB9

struct Cpu;
struct Ram;

typedef struct sramHost {
    char unk_0[0x24];
    struct Cpu*
        pCpu; // TODO the debug info said this was __anon_0x74AB9 (CpuDevice) but the function called takes a CPU
    char unk_28[4];
    struct Ram* pRam;
};

int sramEvent(void* pSram, s32 nEvent, void* pArgument);

static int sramGet64(void* pObject, u32 nAddress, s64* pData);
static int sramGet32(void* pObject, u32 nAddress, s32* pData);
static int sramGet16(void* pObject, u32 nAddress, s16* pData);
static int sramGet8(void* pObject, u32 nAddress, s8* pData);
static int sramPut64(void* pObject, u32 nAddress, s64* pData);
static int sramPut32(void* pObject, u32 nAddress, s32* pData);
static int sramPut16(void* pObject, u32 nAddress, s16* pData);
static int sramPut8(void* pObject, u32 nAddress, s8* pData);

extern int ramGetBuffer(struct Ram* pRAM, void* ppRAM, u32 nOffset, u32* pnSize);
extern int simulatorWriteSRAM(unsigned int address, unsigned char* data, int size);

_XL_OBJECTTYPE gClassSram = {OBJ_NAME, sizeof(Sram), NULL, sramEvent};

int sramEvent(void* pObject, s32 nEvent, void* pArgument) {
    Sram* pSram = (Sram*)pObject;

    switch (nEvent) {
        case 2:
            pSram->pHost = pArgument;
        case 0:
        case 1:
        case 3:
            break;

        case 0x1002:
            if (cpuSetDevicePut(pSram->pHost->pCpu, pArgument, sramPut8, sramPut16, sramPut32, sramPut64) == 0) {
                return 0;
            }
            if (cpuSetDeviceGet(pSram->pHost->pCpu, pArgument, sramGet8, sramGet16, sramGet32, sramGet64) == 0) {
                return 0;
            }
        case 0x1003:
            break;

        default:
            return 0;
    }
    return 1;
}

// TODO uintptr_t?
static int sramGet64(void* pObject, u32 nAddress, s64* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(long long));
    return 1;
}

static int sramGet32(void* pObject, u32 nAddress, s32* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(int));
    return 1;
}

static int sramGet16(void* pObject, u32 nAddress, s16* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(short));
    return 1;
}
static int sramGet8(void* pObject, u32 nAddress, s8* pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(char));
    return 1;
}

static int sramPut64(void* pObject, u32 nAddress, s64* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(long long));
    return 1;
}

static int sramPut32(void* pObject, u32 nAddress, s32* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(int));
    return 1;
}

static int sramPut16(void* pObject, u32 nAddress, s16* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(short));
    return 1;
}
static int sramPut8(void* pObject, u32 nAddress, s8* pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(char));
    return 1;
}

s32 sramTransferSRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (ramGetBuffer(pSRAM->pHost->pRam, &pTarget, nOffsetRAM, &nSize) == 0) {
        return 0;
    }
    if (simulatorWriteSRAM(nOffsetSRAM & 0x7FFF, pTarget, nSize) == 0) {
        return 0;
    }
    return 1;
}

s32 sramCopySRAM(Sram* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* pTarget;

    if (ramGetBuffer(pSRAM->pHost->pRam, &pTarget, nOffsetRAM, &nSize) == 0) {
        return 0;
    }
    if (simulatorReadSRAM(nOffsetSRAM & 0x7FFF, pTarget, nSize) == 0) {
        return 0;
    }
    return 1;
}
