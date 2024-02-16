#include "types.h"
#include "cpu.h"

int simulatorWriteSRAM(unsigned int address, unsigned char *data, int size);
int simulatorReadSRAM(unsigned int address, unsigned char *data, int size);

typedef struct _XL_OBJECTTYPE
{
	char *szName; // 0x0
	int nSizeObject; // 0x4
	struct _XL_OBJECTTYPE *pClassBase; // 0x8
	int (*pfEvent)(void */* unknown0 */, int /* unknown1 */, void */* unknown2 */); // 0xC
}_XL_OBJECTTYPE;

typedef struct __anon_0x74AB9
{
	struct sramHost *pHost; // 0x0
} __anon_0x74AB9;

typedef struct __anon_0x4BFE7
{
	void *pHost; // 0x0
	void *pBuffer; // 0x4
	unsigned int nSize; // 0x8
}__anon_0x4BFE7;

typedef struct sramHost{
    char unk_0[0x24];
    __anon_0x3EB4F* device;
    char unk_28[4];
    __anon_0x4BFE7* pRam;
};

int sramEvent(__anon_0x74AB9* pSram, s32 nEvent, void* pArgument);

static int sramGet64(void*, unsigned int nAddress, signed long long *pData);
static int sramGet32(void*, unsigned int nAddress, int *pData);
static int sramGet16(void*, unsigned int nAddress, signed short *pData);
static int sramGet8(void*, unsigned int nAddress, char *pData);
static int sramPut64(void*, unsigned int nAddress, signed long long *pData);
static int sramPut32(void*, unsigned int nAddress, int *pData);
static int sramPut16(void*, unsigned int nAddress, signed short *pData);
static int sramPut8(void*, unsigned int nAddress, char *pData);

extern int ramGetBuffer(__anon_0x4BFE7 *pRAM, void *ppRAM, unsigned int nOffset, unsigned int *pnSize);
extern int simulatorWriteSRAM(unsigned int address, unsigned char *data, int size);

// Location: 0x68E70E80
_XL_OBJECTTYPE gClassSram = {
    "SRAM", sizeof("SRAM") - 1, NULL, (void*)sramEvent 
};


int sramEvent(__anon_0x74AB9* pSram, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pSram->pHost = pArgument;
        case 0:
        case 1:
        case 3:
            break;

        case 0x1002:
            if (cpuSetDevicePut(pSram->pHost->device, pArgument, sramPut8, sramPut16, sramPut32, sramPut64) == 0) {
                return 0;
            }
            if (cpuSetDeviceGet(pSram->pHost->device, pArgument, sramGet8, sramGet16, sramGet32, sramGet64) == 0) {
                return 0;
            }
        case 0x1003:
            break;

        default:
            return 0;
    }
    return 1;
}

int sramGet64(void* arg0, unsigned int nAddress, signed long long *pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(long long));
    return 1;
}

int sramGet32(void* arg0, unsigned int nAddress, signed int *pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(int));
    return 1;
}

int sramGet16(void* arg0, unsigned int nAddress, signed short *pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(short));
    return 1;
}
int sramGet8(void* arg0, unsigned int nAddress, char *pData) {
    simulatorReadSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(char));
    return 1;
}

int sramPut64(void* arg0, unsigned int nAddress, signed long long *pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(long long));
    return 1;
}

int sramPut32(void* arg0, unsigned int nAddress, signed int *pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(int));
    return 1;
}

int sramPut16(void* arg0, unsigned int nAddress, signed short *pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(short));
    return 1;
}
int sramPut8(void* arg0, unsigned int nAddress, char *pData) {
    simulatorWriteSRAM(nAddress & 0x7FFF, (unsigned char*)pData, sizeof(char));
    return 1;
}


s32 sramTransferSRAM(__anon_0x74AB9* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* sp18;

    if (ramGetBuffer(pSRAM->pHost->pRam, &sp18, nOffsetRAM, &nSize) == 0) {
        return 0;
    }
    if (simulatorWriteSRAM(nOffsetSRAM & 0x7FFF, sp18, nSize) == 0) {
        return 0;
    }
    return 1;
}
//#pragma GLOBAL_ASM("asm/non_matchings/sram/sramCopySRAM.s")

s32 sramCopySRAM(__anon_0x74AB9* pSRAM, u32 nOffsetRAM, u32 nOffsetSRAM, u32 nSize) {
    void* sp18;

    if (ramGetBuffer(pSRAM->pHost->pRam, &sp18, nOffsetRAM, &nSize) == 0) {
        return 0;
    }
    if (simulatorReadSRAM(nOffsetSRAM & 0x7FFF, sp18, nSize) == 0) {
        return 0;
    }
    return 1;
}
