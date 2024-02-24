#include "audio.h"
#include "dolphin.h"
#include "ram.h"
#include "rsp.h"
#include "soundGCN.h"
#include "system.h"
#include "xlObject.h"
#include "xlPostGCN.h"

_XL_OBJECTTYPE gClassAudio = {
    "AUDIO",
    sizeof(Audio),
    NULL,
    (EventFunc)audioEvent,
};

s32 audioPut8(Audio* pAudio, u32 nAddress, s8* pData) { return 0; }

s32 audioPut16(Audio* pAudio, u32 nAddress, s16* pData) { return 0; }

s32 audioPut32(Audio* pAudio, u32 nAddress, s32* pData) {
    void* pBuffer;

    switch (nAddress & 0x1F) {
        case 0x0:
            if (pAudio->nAddress = (*pData & 0xFFFFFF)) {
                if (!ramGetBuffer(SYSTEM_RAM(pAudio->pHost), &pBuffer, pAudio->nAddress, NULL)) {
                    return 0;
                }
                if (pAudio->bEnable) {
                    soundSetAddress(SYSTEM_SOUND(pAudio->pHost), pBuffer);
                }
                break;
            }
            break;
        case 0x4:
            pAudio->nSize = *pData & 0x3FFF8;
            if ((pAudio->nControl != 0) && pAudio->bEnable) {
                soundSetLength(SYSTEM_SOUND(pAudio->pHost), pAudio->nSize);
            }
            break;
        case 0x8:
            pAudio->nControl = *pData & 1;
            break;
        case 0xC:
            xlObjectEvent(pAudio->pHost, 0x1001, (void*)7);
            break;
        case 0x10:
            pAudio->nRateDAC = *pData & 0x3FFF;
            if (pAudio->bEnable) {
                soundSetDACRate(SYSTEM_SOUND(pAudio->pHost), pAudio->nRateDAC);
            }
            break;
        case 0x14:
            pAudio->nRateBit = *pData & 0xF;
            break;
        default:
            return 0;
    }

    return 1;
}

s32 audioPut64(Audio* pAudio, u32 nAddress, s64* pData) { return 0; }

s32 audioGet8(Audio* pAudio, u32 nAddress, s8* pData) { return 0; }

s32 audioGet16(Audio* pAudio, u32 nAddress, s16* pData) { return 0; }

s32 audioGet32(Audio* pAudio, u32 nAddress, s32* pData) {
    switch (nAddress & 0x1F) {
        case 0:
            *pData = pAudio->nAddress;
            xlPostText("Get: DRAM Address: WRITE-ONLY?", "audio.c", 0xDA);
            break;
        case 4:
            if (!soundGetDMABuffer(SYSTEM_SOUND(pAudio->pHost), pData)) {
                *pData = pAudio->nSize;
            }
            break;
        case 8:
            *pData = pAudio->nControl;
            xlPostText("Get: CONTROL: WRITE-ONLY?", "audio.c", 0xE4);
            break;
        case 12:
            *pData = AIGetDMABytesLeft() ? 0x40000000 : 0;
            break;
        case 16:
            *pData = pAudio->nRateDAC;
            break;
        case 20:
            *pData = pAudio->nRateBit;
            break;
        default:
            return 0;
    }

    return 1;
}

s32 audioGet64(Audio* pAudio, u32 nAddress, s64* pData) { return 0; }

s32 audioEnable(Audio* pAudio, s32 bEnable) {
    pAudio->bEnable = bEnable ? 1 : 0;

    if (!rspEnableABI(SYSTEM_RSP(pAudio->pHost), pAudio->bEnable)) {
        return 0;
    }

    return 1;
}

s32 audioEvent(Audio* pAudio, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pAudio->nSize = 0;
            pAudio->nControl = 1;
            pAudio->nAddress = 0;
            pAudio->nRateBit = 0;
            pAudio->nRateDAC = 0;
            pAudio->pHost = pArgument;
            pAudio->bEnable = 1;
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pAudio->pHost), pArgument, (Put8Func)audioPut8, (Put16Func)audioPut16,
                                 (Put32Func)audioPut32, (Put64Func)audioPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pAudio->pHost), pArgument, (Put8Func)audioGet8, (Put16Func)audioGet16,
                                 (Put32Func)audioGet32, (Put64Func)audioGet64)) {
                return 0;
            }
            break;
        case 0:
        case 1:
        case 3:
        case 0x1003:
            break;
        default:
            return 0;
    }

    return 1;
}
