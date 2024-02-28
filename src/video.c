#include "video.h"
#include "frame.h"
#include "ram.h"
#include "system.h"

_XL_OBJECTTYPE gClassVideo = {
    "VIDEO",
    sizeof(Video),
    NULL,
    (EventFunc)videoEvent,
};

s32 videoPut8(Video* pVideo, u32 nAddress, s8* pData) { return 0; }

s32 videoPut16(Video* pVideo, u32 nAddress, s16* pData) { return 0; }

s32 videoPut32(Video* pVideo, u32 nAddress, s32* pData) {
    void* pRAM;
    Frame* pFrame;
    FrameBuffer* pBuffer;

    switch (nAddress & 0x3F) {
        case 0x0:
            pVideo->nStatus = *pData & 0xFFFF;
            break;
        case 0x4:
            pVideo->nAddress = *pData & 0xFFFFFF;
            pFrame = SYSTEM_FRAME(pVideo->pHost);
            pBuffer = &pFrame->aBuffer[2];

            if (!ramGetBuffer(SYSTEM_RAM(pVideo->pHost), &pRAM, pVideo->nAddress, NULL)) {
                return 0;
            }

            if (pBuffer->pData != pRAM) {
                pBuffer->nFormat = 0;
                pBuffer->nSize = 2;
                pBuffer->nWidth = pVideo->nSizeX;
                pBuffer->pData = pRAM;

                if (!frameSetBuffer(pFrame, 2)) {
                    return 0;
                }
            }
            break;
        case 0x8:
            pVideo->nSizeX = *pData & 0xFFF;
            break;
        case 0xC:
            pVideo->nScanInterrupt = *pData & 0x3FF;
            break;
        case 0x10:
            xlObjectEvent(pVideo->pHost, 0x1001, (void*)8);
            pVideo->nScanInterrupt = 0x10000;
            break;
        case 0x14:
            pVideo->nTiming = *pData;
            break;
        case 0x18:
            pVideo->nSyncV = *pData & 0x3FF;
            break;
        case 0x1C:
            pVideo->nSyncH = *pData & 0x1FFFFF;
            break;
        case 0x20:
            pVideo->nSyncLeap = *pData & 0x0FFFFFFF;
            break;
        case 0x24:
            if ((pVideo->nStartH = *pData & 0x03FF03FF) == 0) {
                if (pVideo->bBlack != 1) {
                    pVideo->bBlack = 1;
                }
            } else {
                if (pVideo->bBlack != 0) {
                    pVideo->bBlack = 0;
                }
            }
            break;
        case 0x28:
            pVideo->nStartV = *pData & 0x03FF03FF;
            break;
        case 0x2C:
            pVideo->nBurst = *pData & 0x03FF03FF;
            break;
        case 0x30:
            pVideo->nScaleX = *pData & 0xFFF;
            if (!frameSetSize(SYSTEM_FRAME(pVideo->pHost), 0, pVideo->nSizeX, (s32)(pVideo->nScaleY * 240) / 1024)) {
                return 0;
            }
            break;
        case 0x34:
            pVideo->nScaleY = *pData & 0xFFF;
            if (!frameSetSize(SYSTEM_FRAME(pVideo->pHost), 0, pVideo->nSizeX, (s32)(pVideo->nScaleY * 240) / 1024)) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}

s32 videoPut64(Video* pVideo, u32 nAddress, s64* pData) { return 0; }

s32 videoGet8(Video* pVideo, u32 nAddress, s8* pData) { return 0; }

s32 videoGet16(Video* pVideo, u32 nAddress, s16* pData) { return 0; }

s32 videoGet32(Video* pVideo, u32 nAddress, s32* pData) {
    switch (nAddress & 0x3F) {
        case 0x0:
            *pData = pVideo->nStatus;
            break;
        case 0x4:
            *pData = pVideo->nAddress;
            break;
        case 0x8:
            *pData = pVideo->nSizeX;
            break;
        case 0xC:
            *pData = pVideo->nScanInterrupt & 0xFFFF;
            break;
        case 0x10:
            pVideo->nScan = VIGetCurrentLine() * 2;
            *pData = pVideo->nScan;
            break;
        case 0x14:
            *pData = pVideo->nTiming;
            break;
        case 0x18:
            *pData = pVideo->nSyncV;
            break;
        case 0x1C:
            *pData = pVideo->nSyncH;
            break;
        case 0x20:
            *pData = pVideo->nSyncLeap;
            break;
        case 0x24:
            *pData = pVideo->nStartH;
            break;
        case 0x28:
            *pData = pVideo->nStartV;
            break;
        case 0x2C:
            *pData = pVideo->nBurst;
            break;
        case 0x30:
            *pData = pVideo->nScaleX;
            break;
        case 0x34:
            *pData = pVideo->nScaleY;
            break;
        default:
            return 0;
    }

    return 1;
}

s32 videoGet64(Video* pVideo, u32 nAddress, s64* pData) { return 0; }

s32 videoForceRetrace(Video* pVideo) {
    if (!systemExceptionPending(pVideo->pHost, SIT_VI) && (pVideo->nStatus & 3)) {
        pVideo->nScan = pVideo->nScanInterrupt;
        xlObjectEvent(pVideo->pHost, 0x1000, (void*)8);
        return 1;
    }

    return 0;
}

s32 videoEvent(Video* pVideo, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pVideo->nScan = 0;
            pVideo->nBurst = 0;
            pVideo->nSizeX = 0;
            pVideo->nStatus = 0;
            pVideo->nTiming = 0;
            pVideo->nAddress = 0;
            pVideo->nScaleX = 0;
            pVideo->nScaleY = 0;
            pVideo->nStartH = 0;
            pVideo->nStartV = 0;
            pVideo->nSyncH = 0;
            pVideo->nSyncV = 0;
            pVideo->nSyncLeap = 0;
            pVideo->bBlack = 0;
            pVideo->nScanInterrupt = 0x10000;
            pVideo->pHost = pArgument;
        case 0:
        case 1:
        case 3:
        case 5:
        case 0x1003:
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pVideo->pHost), pArgument, (Put8Func)videoPut8, (Put16Func)videoPut16,
                                 (Put32Func)videoPut32, (Put64Func)videoPut64)) {
                return 0;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pVideo->pHost), pArgument, (Get8Func)videoGet8, (Get16Func)videoGet16,
                                 (Get32Func)videoGet32, (Get64Func)videoGet64)) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}
