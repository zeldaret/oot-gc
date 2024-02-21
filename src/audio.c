#include "audio.h"
#include "xlObject.h"
#include "ram.h"
#include "system.h"

s32 audioEvent(Audio* pAudio, s32 nEvent, void* pArgument);

_XL_OBJECTTYPE gClassAudio = {
    "AUDIO",
    sizeof(Audio),
    NULL,
    (EventFunc)audioEvent,
};

char D_800EE788[] = "Get: DRAM Address: WRITE-ONLY?";
char D_800EE7A8[] = "Get: CONTROL: WRITE-ONLY?";

void* jtbl_800EE7C4[] = {
    (void*)0x8008E668,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E68C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6B0,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6D4,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E6F4,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E70C,
    (void*)0x8008E700,
};

void* jtbl_800EE818[] = {
    (void*)0x8008E780,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E7D8,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E810,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E820,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E834,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E870,
    (void*)0x8008E860,
};

char D_80135310[8] = "audio.c";

static s32 audioPut8(Audio* pAudio, u32 nAddress, s8* pData) { return 0; }

static s32 audioPut16(Audio* pAudio, u32 nAddress, s16* pData) { return 0; }

#ifdef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/audio/audioPut32.s")
#else
s32 audioPut32(Audio* pAudio, u32 nAddress, s32* pData) {
    // Parameters
    // struct __anon_0x753E7* pAudio; // r31
    // u32 nAddress; // r1+0xC
    // s32* pData; // r1+0x10

    // Local variables
    void* pBuffer; // r1+0x14

    switch (nAddress & 0x1F) {
        case 0x0:
            pAudio->nAddress = nAddress;
            if (*pData & 0xFFFFFF != 0) {
                if (!ramGetBuffer(((System*)pAudio->pHost)->apObject[SOT_RAM], &pBuffer, pAudio->nAddress, NULL)) {
                    return 0;
                }
                if (pAudio->bEnable) {
                    soundSetAddress(((System*)pAudio->pHost)->pSound, pBuffer);
                }
                break;
            }
            break;
        case 0x4:
            pAudio->nSize = *pData & 0x3FFF8;
            if ((pAudio->nControl != 0) && pAudio->bEnable) {
                soundSetLength(((System*)pAudio->pHost)->pSound, pAudio->nSize);
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
                soundSetDACRate(((System*)pAudio->pHost)->pSound, pAudio->nRateDAC);
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
#endif

static s32 audioPut64(Audio* pAudio, u32 nAddress, s64* pData) { return 0; }

static s32 audioGet8(Audio* pAudio, u32 nAddress, s8* pData) { return 0; }

static s32 audioGet16(Audio* pAudio, u32 nAddress, s16* pData) { return 0; }

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioGet32.s")

static s32 audioGet64(Audio* pAudio, u32 nAddress, s64* pData) { return 0; }

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioEnable.s")

#pragma GLOBAL_ASM("asm/non_matchings/audio/audioEvent.s")
