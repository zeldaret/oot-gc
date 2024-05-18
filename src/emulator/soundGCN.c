#include "emulator/soundGCN.h"
#include "emulator/simGCN.h"
#include "emulator/xlFileGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"

_XL_OBJECTTYPE gClassSound = {
    "SOUND",
    sizeof(Sound),
    NULL,
    (EventFunc)soundEvent,
};

char D_800EA7E8[62] = "SetBufferSize: ERROR: 'nSize' must be a multiple of 32! (%d)\n";
char D_800EA828[11] = "soundGCN.c";

s32 gVolumeCurve[257] ALIGNAS(32);

s32 D_80134DD0 = 10;

const f32 D_80135DD8 = 65536.0f;
const f32 D_80135DDC = 20.0f;
const f32 D_80135DE0 = 256.0f;
const f64 D_80135DE8 = 256.0;
const f64 D_80135DF0 = 4503601774854144.0;
const f32 D_80135DF8 = 0.5f;

bool soundWipeBuffers(Sound* pSound) {
    s32 iBuffer;

    if (pSound->pBufferZero != NULL && !xlHeapFree(&pSound->pBufferZero)) {
        return false;
    }

    if (pSound->pBufferHold != NULL && !xlHeapFree(&pSound->pBufferHold)) {
        return false;
    }

    if (pSound->pBufferRampUp != NULL && !xlHeapFree(&pSound->pBufferRampUp)) {
        return false;
    }

    if (pSound->pBufferRampDown != NULL && !xlHeapFree(&pSound->pBufferRampDown)) {
        return false;
    }

    for (iBuffer = 0; iBuffer < 16; iBuffer++) {
        if (pSound->apBuffer[iBuffer] != NULL && !xlHeapFree(&pSound->apBuffer[iBuffer])) {
            return false;
        }
    }

    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundMakeRamp.s")

static inline bool soundMakeZero(Sound* pSound) {
    int iData;

    for (iData = 0; iData < (pSound->nSizeZero >> 1); iData++) {
        ((s16*)pSound->pBufferZero)[iData] = 0;
    }

    DCStoreRange(pSound->pBufferZero, pSound->nSizeZero);
    return true;
}

bool soundPlayBuffer(Sound* pSound) {
    void* pData;
    s32 iBufferPlay; // iBuffer
    int iBufferMake;
    s32 nSize;

    iBufferMake = pSound->iBufferMake;
    iBufferPlay = pSound->iBufferPlay;

    if (iBufferMake != iBufferPlay) {
        if (pSound->eMode == SPM_RAMPPLAYED) {
            nSize = pSound->nSizeRamp;
            pData = pSound->pBufferRampUp;
        } else {
            nSize = pSound->anSizeBuffer[iBufferPlay];
            pData = pSound->apBuffer[iBufferPlay];
            pSound->iBufferPlay = (iBufferPlay + 1) % 16;
        }
        pSound->eMode = SPM_PLAY;
    } else if ((*((volatile SoundPlayMode*)&pSound->eMode) == SPM_RAMPQUEUED) || (pSound->eMode == SPM_RAMPPLAYED)) {
        //! TODO: fake match?
        pData = pSound->pBufferZero;
        nSize = pSound->nSizeZero;
        pSound->eMode = SPM_RAMPPLAYED;
    } else {
        pData = pSound->pBufferRampDown;
        nSize = pSound->nSizeRamp;
        pSound->eMode = SPM_RAMPQUEUED;
    }

    AIInitDMA((u32)pData, nSize);
    return true;
}

static void soundCallbackDMA(void) { soundPlayBuffer(SYSTEM_SOUND(gpSystem)); }

static s32 soundMakeBuffer(Sound* pSound);
#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundMakeBuffer.s")

bool soundSetLength(Sound* pSound, s32 nSize) {
    pSound->nSndLen = nSize;

    if (!soundMakeBuffer(pSound)) {
        return false;
    }

    return true;
}

bool soundSetDACRate(Sound* pSound, s32 nDacRate) {
    pSound->nDacrate = nDacRate;
    pSound->nFrequency = 0x02E6D354 / (nDacRate + 1);
    return true;
}

bool soundSetAddress(Sound* pSound, void* pData) {
    pSound->pSrcData = pData;
    return true;
}

bool soundGetDMABuffer(Sound* pSound, u32* pnSize) {
    *pnSize = AIGetDMABytesLeft();
    return true;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundSetBufferSize.s")
#else
bool soundSetBufferSize(Sound* pSound, s32 nSize) {
    int iBuffer;

    if (nSize % 32) {
        xlPostText("SetBufferSize: ERROR: 'nSize' must be a multiple of 32! (%d)\n", "soundGCN.c", 674, nSize);
        nSize = (nSize + 0x1F) & ~0x1F;
    }

    pSound->nSizePlay = nSize;
    pSound->nSizeHold = pSound->nSizeZero = nSize >> 4;
    pSound->nSizeRamp = nSize >> 2;

    if (!soundWipeBuffers(pSound)) {
        return false;
    }

    for (iBuffer = 0; iBuffer < 16; iBuffer++) {
        if (!xlHeapTake(&pSound->apBuffer[iBuffer], pSound->nSizePlay | 0x30000000)) {
            return false;
        }
    }

    if (!xlHeapTake(&pSound->pBufferZero, pSound->nSizeZero | 0x30000000)) {
        return false;
    }

    soundMakeZero(pSound);

    if (!xlHeapTake(&pSound->pBufferHold, pSound->nSizeHold | 0x30000000)) {
        return false;
    }

    if (!xlHeapTake(&pSound->pBufferRampUp, pSound->nSizeRamp | 0x30000000)) {
        return false;
    }

    if (!xlHeapTake(&pSound->pBufferRampDown, pSound->nSizeRamp | 0x30000000)) {
        return false;
    }

    return true;
}
#endif

static inline void InitVolumeCurve(void) {
    s32 i;
    f64 value;

    gVolumeCurve[0] = 0;
    for (i = 1; i < ARRAY_COUNT(gVolumeCurve); i++) {
        value = pow(D_80134DD0, (20.0f * log10f(SQ(256 - i) / 65536.0f)) / 20.0f);
        gVolumeCurve[i] = (256.0f * (f32) - ((value * 256.0) - 256.0));
    }
}

void soundCallbackBeep(void) {
    Sound* pSound;

    pSound = SYSTEM_SOUND(gpSystem);
    AIInitDMA((u32)pSound->pBufferZero, pSound->nSizeZero);

    if (++pSound->nCountBeep == 2) {
        AIStopDMA();
        AIRegisterDMACallback(soundCallbackDMA);
    }
}

bool soundLoadBeep(Sound* pSound, SoundBeep iBeep, char* szNameFile) {
    tXL_FILE* pFile;

    if ((iBeep >= SOUND_BEEP_ACCEPT) && (iBeep < SOUND_BEEP_COUNT)) {
        if (pSound->apDataBeep[iBeep] == NULL && xlFileOpen(&pFile, XLFT_BINARY, szNameFile)) {
            pSound->anSizeBeep[iBeep] = (pFile->nSize + 0x1F) & ~0x1F;

            if (!xlHeapTake(&pSound->apDataBeep[iBeep], pSound->anSizeBeep[iBeep] | 0x30000000)) {
                return false;
            }

            if (!xlHeapFill32(pSound->apDataBeep[iBeep], pSound->anSizeBeep[iBeep], 0)) {
                return false;
            }

            if (!xlFileGet(pFile, pSound->apDataBeep[iBeep], pFile->nSize)) {
                return false;
            }

            if (!xlFileClose(&pFile)) {
                return false;
            }

            return true;
        }
    }

    return false;
}

bool soundPlayBeep(Sound* pSound, SoundBeep iBeep) {
    if (pSound->apDataBeep[iBeep] != NULL) {
        AIStopDMA();
        pSound->nCountBeep = 0;
        AIRegisterDMACallback(soundCallbackBeep);
        AIInitDMA((u32)pSound->apDataBeep[iBeep], pSound->anSizeBeep[iBeep]);
        AIStartDMA();
    }

    return true;
}

// matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/soundGCN/soundEvent.s")
#else
bool soundEvent(Sound* pSound, s32 nEvent, void* pArgument) {
    int iBuffer;
    s32 pad[8];

    switch (nEvent) {
        case 0:
            AIInit(NULL);
            AISetDSPSampleRate(AI_SAMPLERATE_32KHZ);
            AIStopDMA();
            AIRegisterDMACallback(soundCallbackDMA);
            break;
        case 1:
            AIStopDMA();
            break;
        case 2:
            pSound->eMode = SPM_NONE;
            pSound->iBufferMake = 0;
            pSound->iBufferPlay = 0;

            pSound->anSizeBeep[SOUND_BEEP_ACCEPT] = 0;
            pSound->apDataBeep[SOUND_BEEP_ACCEPT] = NULL;

            pSound->anSizeBeep[SOUND_BEEP_DECLINE] = 0;
            pSound->apDataBeep[SOUND_BEEP_DECLINE] = NULL;

            pSound->anSizeBeep[SOUND_BEEP_SELECT] = 0;
            pSound->apDataBeep[SOUND_BEEP_SELECT] = NULL;

            for (iBuffer = 0; iBuffer < 16; iBuffer++) {
                pSound->apBuffer[iBuffer] = NULL;
            }

            pSound->pBufferZero = NULL;
            pSound->pBufferHold = NULL;
            pSound->pBufferRampUp = NULL;
            pSound->pBufferRampDown = NULL;

            InitVolumeCurve();
            break;
        case 3:
            if (!soundWipeBuffers(pSound)) {
                return false;
            }
            break;
        case 0x1003:
            break;
        default:
            return false;
    }

    return true;
}
#endif
