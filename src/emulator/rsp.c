#include "emulator/rsp.h"
#include "emulator/cpu.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/rdp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlHeap.h"
#include "emulator/xlList.h"
#include "string.h"

_XL_OBJECTTYPE gClassRSP = {
    "RSP",
    sizeof(Rsp),
    NULL,
    (EventFunc)rspEvent,
};

#if VERSION == MQ_J
u16 gnTempBuffer[N64_FRAME_WIDTH * N64_FRAME_HEIGHT];
u16 gnCopyBuffer[N64_FRAME_WIDTH * N64_FRAME_HEIGHT];
u16 gnCameraBuffer[ZELDA2_CAMERA_WIDTH * ZELDA2_CAMERA_HEIGHT];
#endif

static bool rspLoadMatrix(Rsp* pRSP, s32 nAddress, Mtx44 matrix) {
    s32* pMtx;
    s32 nDataA;
    s32 nDataB;
    f32 rScale;
    f32 rUpper;
    f32 rLower;
    u16 nUpper;
    u16 nLower;

    rScale = 1.0f / 65536.0f;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pMtx, nAddress, NULL)) {
        return false;
    }

    nDataA = pMtx[0];
    nDataB = pMtx[8];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][1] = rUpper + rLower * rScale;

    nDataA = pMtx[1];
    nDataB = pMtx[9];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[0][3] = rUpper + rLower * rScale;

    nDataA = pMtx[2];
    nDataB = pMtx[10];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][1] = rUpper + rLower * rScale;

    nDataA = pMtx[3];
    nDataB = pMtx[11];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[1][3] = rUpper + rLower * rScale;

    nDataA = pMtx[4];
    nDataB = pMtx[12];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][1] = rUpper + rLower * rScale;

    nDataA = pMtx[5];
    nDataB = pMtx[13];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[2][3] = rUpper + rLower * rScale;

    nDataA = pMtx[6];
    nDataB = pMtx[14];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][0] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][1] = rUpper + rLower * rScale;

    nDataA = pMtx[7];
    nDataB = pMtx[15];
    nUpper = nDataA >> 16;
    nLower = nDataB >> 16;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][2] = rUpper + rLower * rScale;
    nUpper = nDataA & 0xFFFF;
    nLower = nDataB & 0xFFFF;
    OSs16tof32((s16*)&nUpper, &rUpper);
    OSu16tof32(&nLower, &rLower);
    matrix[3][3] = rUpper + rLower * rScale;

    return true;
}

inline bool rspSetDL(Rsp* pRSP, s32 nOffsetRDRAM, bool bPush) {
    s32 nAddress;
    s32* pDL;

    nAddress = SEGMENT_ADDRESS(pRSP, nOffsetRDRAM);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pDL, nAddress, NULL)) {
        return false;
    }

    if (bPush && ++pRSP->iDL >= ARRAY_COUNT(pRSP->apDL)) {
        return false;
    }

    pRSP->apDL[pRSP->iDL] = (u64*)pDL;
    return true;
}

inline bool rspPopDL(Rsp* pRSP) {
    if (pRSP->iDL == 0) {
        return false;
    } else {
        pRSP->iDL--;
        return true;
    }
}

static inline bool rspSetupUCode(Rsp* pRSP) {
    Frame* pFrame;

    pFrame = SYSTEM_FRAME(pRSP->pHost);
    if (pRSP->eTypeUCode == RUT_L3DEX1 || pRSP->eTypeUCode == RUT_L3DEX2) {
        frameSetFill(pFrame, false);
    } else {
        frameSetFill(pFrame, true);
    }
    return true;
}

static bool rspFindUCode(Rsp* pRSP, RspTask* pTask) {
    s32 nCountVertex;
    RspUCode* pUCode;
    RspUCodeType eType;
    void* pListNode;
    s32 nOffsetCode;
    s32 nOffsetData;
    u64 nFUData;
    u64* pFUData;
    u64* pFUCode;
    u64 nCheckSum;
    u32 nLengthData;
    u32 i;
    u32 j;
    u32 nLengthCode;
    s32 pad2[6];
    char aBigBuffer[4096];
    char acUCodeName[64];
    char temp_r22;
    char temp_r15;

    nOffsetCode = pTask->nOffsetCode & 0x7FFFFF;
    nOffsetData = pTask->nOffsetData & 0x7FFFFF;
    pListNode = pRSP->pListUCode->pNodeHead;
    nCheckSum = 0;

    while (pListNode != NULL) {
        pUCode = (RspUCode*)NODE_DATA(pListNode);
        if (pUCode->nOffsetCode == nOffsetCode && pUCode->nOffsetData == nOffsetData) {
            pRSP->eTypeUCode = pUCode->eType;
            pRSP->nCountVertex = pUCode->nCountVertex;
            rspSetupUCode(pRSP);
            return true;
        }
        pListNode = NODE_NEXT(pListNode);
    }

    nLengthData = pTask->nLengthData;
    nLengthCode = pTask->nLengthCode;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pFUData, nOffsetData, NULL)) {
        return false;
    }
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pFUCode, nOffsetCode, NULL)) {
        return false;
    }

    eType = RUT_NONE;
    for (i = 0; i < (nLengthCode >> 3); i++) {
        nCheckSum += pFUCode[i];
    }

    for (i = 0; i < (nLengthData >> 3); i++) {
        nFUData = pFUData[i];
        for (j = 0; j < 8; j++) {
            aBigBuffer[i * 8 + j] = nFUData >> (int)(56 - j * 8);
        }

        if (((nFUData >> 32) & 0xFFFFFFFF) != 'RSP ') {
            continue;
        }

        if (((nFUData >> 8) & 0xFFFFFF) == 'Gfx') {
            nFUData = pFUData[i + 1];
            if ((nFUData & 0xFFFF) == 'F3') {
                nFUData = pFUData[i + 2];
                temp_r22 = (nFUData >> 48) & 0xFF;
                acUCodeName[0] = 'F';
                acUCodeName[1] = '3';
                acUCodeName[2] = (nFUData >> 56) & 0xFF;
                acUCodeName[3] = (nFUData >> 48) & 0xFF;
                acUCodeName[4] = (nFUData >> 40) & 0xFF;
                acUCodeName[5] = (nFUData >> 32) & 0xFF;

                nFUData = pFUData[i + 3];
                if (((nFUData >> 24) & 0xFF) == '0' || ((nFUData >> 24) & 0xFF) == '1') {
                    temp_r15 = (nFUData >> 24) & 0xFF;
                    acUCodeName[6] = (nFUData >> 24) & 0xFF;
                    acUCodeName[7] = (nFUData >> 16) & 0xFF;
                    acUCodeName[8] = (nFUData >> 8) & 0xFF;
                    acUCodeName[9] = (nFUData >> 0) & 0xFF;
                    acUCodeName[10] = '\0';

                    if (temp_r22 == 'Z') {
                        pRSP->nVersionUCode = 0;
                        eType = RUT_ZSORT;
                        nCountVertex = 64;
                    } else {
                        if (temp_r15 == '0') {
                            pRSP->nVersionUCode = 2;
                        } else {
                            pRSP->nVersionUCode = 0;
                        }
                        eType = RUT_F3DEX1;
                        nCountVertex = 32;
                    }
                    break;
                } else if ((nFUData & 0xFF) == '2') {
                    acUCodeName[6] = nFUData & 0xFF;

                    nFUData = pFUData[i + 4];
                    acUCodeName[7] = (nFUData >> 56) & 0xFF;
                    acUCodeName[8] = (nFUData >> 48) & 0xFF;
                    acUCodeName[9] = (nFUData >> 40) & 0xFF;
                    acUCodeName[10] = '\0';

                    if (temp_r22 == 'Z') {
                        pRSP->nVersionUCode = 4;
                        eType = RUT_F3DEX2;
                        nCountVertex = 64;
                    } else {
                        pRSP->nVersionUCode = 0;
                        eType = RUT_F3DEX2;
                        nCountVertex = 64;
                    }
                    break;
                } else {
                    continue;
                }
            } else if ((nFUData & 0xFFFF) == 'L3') {
                nFUData = pFUData[i + 2];
                acUCodeName[0] = 'L';
                acUCodeName[1] = '3';
                acUCodeName[2] = (nFUData >> 56) & 0xFF;
                acUCodeName[3] = (nFUData >> 48) & 0xFF;
                acUCodeName[4] = (nFUData >> 40) & 0xFF;
                acUCodeName[5] = (nFUData >> 32) & 0xFF;

                nFUData = pFUData[i + 3];
                if (((nFUData >> 24) & 0xFF) == '0' || ((nFUData >> 24) & 0xFF) == '1') {
                    acUCodeName[6] = (nFUData >> 24) & 0xFF;
                    acUCodeName[7] = (nFUData >> 16) & 0xFF;
                    acUCodeName[8] = (nFUData >> 8) & 0xFF;
                    acUCodeName[9] = (nFUData >> 0) & 0xFF;
                    acUCodeName[10] = '\0';

                    pRSP->nVersionUCode = 0;
                    eType = RUT_L3DEX1;
                    nCountVertex = 32;
                    break;
                } else if ((nFUData & 0xFF) == '2') {
                    acUCodeName[6] = nFUData & 0xFF;

                    nFUData = pFUData[i + 4];
                    acUCodeName[7] = (nFUData >> 56) & 0xFF;
                    acUCodeName[8] = (nFUData >> 48) & 0xFF;
                    acUCodeName[9] = (nFUData >> 40) & 0xFF;
                    acUCodeName[10] = '\0';

                    pRSP->nVersionUCode = 0;
                    eType = RUT_L3DEX2;
                    nCountVertex = 32;
                    break;
                } else if ((nFUData & 0xFF) == 'Z') {
                    nFUData = pFUData[i + 2];
                    if (((nFUData >> 32) & 0xFFFFFFFF) == 'Sort') {
                        acUCodeName[6] = (nFUData >> 8) & 0xFF;
                        acUCodeName[7] = (nFUData >> 0) & 0xFF;

                        nFUData = pFUData[i + 3];
                        acUCodeName[8] = (nFUData >> 56) & 0xFF;
                        acUCodeName[9] = (nFUData >> 48) & 0xFF;
                        acUCodeName[10] = '\0';

                        pRSP->nVersionUCode = 3;
                        eType = RUT_ZSORT;
                        nCountVertex = 64;
                        // bug? missing "break;"
                    }
                } else {
                    continue;
                }
            }
        }

        if (((nFUData >> 16) & 0xFFFF) == 'SW') {
            nFUData = pFUData[i + 2];

            acUCodeName[0] = 'F';
            acUCodeName[1] = 'a';
            acUCodeName[2] = 's';
            acUCodeName[3] = 't';
            acUCodeName[4] = '3';
            acUCodeName[5] = 'D';
            acUCodeName[6] = ' ';
            acUCodeName[7] = (nFUData >> 56) & 0xFF;
            acUCodeName[8] = (nFUData >> 48) & 0xFF;
            acUCodeName[9] = (nFUData >> 40) & 0xFF;
            acUCodeName[10] = (nFUData >> 32) & 0xFF;
            acUCodeName[11] = '\0';

            if (nCheckSum == 0x3DDCC2B9DE351A0A) {
                pRSP->nVersionUCode = 1;
            } else if (nCheckSum == 0x8B9D7CFA7270C5A4) {
                pRSP->nVersionUCode = 5;
            } else {
                pRSP->nVersionUCode = 0;
            }

            eType = RUT_FAST3D;
            nCountVertex = 32;
            break;
        } else if ((pFUData[i + 1] & 0xFFFF) == 'S2') {
            acUCodeName[0] = 'S';
            acUCodeName[1] = '2';
            acUCodeName[2] = 'D';
            acUCodeName[3] = 'E';
            acUCodeName[4] = 'X';
            acUCodeName[5] = '2';
            acUCodeName[6] = '\0';

            pRSP->nVersionUCode = 0;
            eType = RUT_S2DEX2;
            nCountVertex = 0;
            break;
        }
    }

    if (eType == RUT_NONE) {
        for (i = 0; i < nLengthData - 34; i++) {
            if (!(aBigBuffer[i + 0] == 'R' && aBigBuffer[i + 1] == 'S' && aBigBuffer[i + 2] == 'P')) {
                continue;
            }

            if (aBigBuffer[i + 4] == 'S' && aBigBuffer[i + 5] == 'W') {
                acUCodeName[0] = 'F';
                acUCodeName[1] = 'A';
                acUCodeName[2] = 'S';
                acUCodeName[3] = 'T';
                acUCodeName[4] = '3';
                acUCodeName[5] = 'D';
                acUCodeName[6] = ' ';
                acUCodeName[7] = aBigBuffer[i + 16];
                acUCodeName[8] = aBigBuffer[i + 17];
                acUCodeName[9] = aBigBuffer[i + 18];
                acUCodeName[10] = aBigBuffer[i + 19];
                acUCodeName[11] = '\0';

                if (nCheckSum == 0x3DDCC2B9DE351A0A) {
                    pRSP->nVersionUCode = 1;
                } else if (nCheckSum == 0x8B9D7CFA7270C5A4) {
                    pRSP->nVersionUCode = 5;
                } else {
                    pRSP->nVersionUCode = 1;
                }
                eType = RUT_FAST3D;
                nCountVertex = 32;
                break;
            } else if (aBigBuffer[i + 4] == 'G' && aBigBuffer[i + 5] == 'f' && aBigBuffer[i + 6] == 'x') {
                if (aBigBuffer[i + 14] == 'F' && aBigBuffer[i + 15] == '3') {
                    acUCodeName[0] = 'F';
                    acUCodeName[1] = '3';
                    acUCodeName[2] = aBigBuffer[i + 16];
                    acUCodeName[3] = aBigBuffer[i + 17];
                    acUCodeName[4] = aBigBuffer[i + 18];
                    acUCodeName[5] = aBigBuffer[i + 19];
                    acUCodeName[6] = ' ';

                    if (aBigBuffer[i + 28] == '0' || aBigBuffer[i + 28] == '1') {
                        acUCodeName[7] = aBigBuffer[i + 28];
                        acUCodeName[8] = aBigBuffer[i + 29];
                        acUCodeName[9] = aBigBuffer[i + 30];
                        acUCodeName[10] = aBigBuffer[i + 31];
                        acUCodeName[11] = '\0';

                        if (aBigBuffer[i + 17] == 'Z') {
                            pRSP->nVersionUCode = 0;
                            eType = RUT_ZSORT;
                            nCountVertex = 64;
                        } else {
                            if (aBigBuffer[i + 28] == '0') {
                                pRSP->nVersionUCode = 2;
                            } else {
                                pRSP->nVersionUCode = 0;
                            }
                            eType = RUT_F3DEX1;
                            nCountVertex = 32;
                        }
                        break;
                    } else if (aBigBuffer[i + 31] == '2') {
                        acUCodeName[7] = aBigBuffer[i + 31];
                        acUCodeName[8] = aBigBuffer[i + 32];
                        acUCodeName[9] = aBigBuffer[i + 33];
                        acUCodeName[10] = aBigBuffer[i + 34];
                        acUCodeName[11] = '\0';

                        if (aBigBuffer[i + 17] == 'Z') {
                            pRSP->nVersionUCode = 4;
                            eType = RUT_F3DEX2;
                            nCountVertex = 64;
                        } else {
                            pRSP->nVersionUCode = 0;
                            eType = RUT_F3DEX2;
                            nCountVertex = 64;
                        }
                        break;
                    }
                } else if (aBigBuffer[i + 14] == 'L' && aBigBuffer[i + 15] == '3') {
                    acUCodeName[0] = 'L';
                    acUCodeName[1] = '3';
                    acUCodeName[2] = aBigBuffer[i + 16];
                    acUCodeName[3] = aBigBuffer[i + 17];
                    acUCodeName[4] = aBigBuffer[i + 18];
                    acUCodeName[5] = ' ';

                    if (aBigBuffer[i + 28] == '0' || aBigBuffer[i + 28] == '1') {
                        acUCodeName[6] = aBigBuffer[i + 28];
                        acUCodeName[7] = aBigBuffer[i + 29];
                        acUCodeName[8] = aBigBuffer[i + 30];
                        acUCodeName[9] = aBigBuffer[i + 31];
                        acUCodeName[10] = '\0';

                        pRSP->nVersionUCode = 0;
                        eType = RUT_L3DEX1;
                        nCountVertex = 32;
                        break;
                    } else if (aBigBuffer[i + 31] == '2') {
                        acUCodeName[6] = aBigBuffer[i + 31];
                        acUCodeName[7] = aBigBuffer[i + 32];
                        acUCodeName[8] = aBigBuffer[i + 33];
                        acUCodeName[9] = aBigBuffer[i + 34];
                        acUCodeName[10] = '\0';

                        pRSP->nVersionUCode = 0;
                        eType = RUT_L3DEX2;
                        nCountVertex = 32;
                        break;
                    }
                } else if (aBigBuffer[i + 14] == 'S' && aBigBuffer[i + 15] == '2' && aBigBuffer[i + 16] == 'D' &&
                           aBigBuffer[i + 17] == 'E' && aBigBuffer[i + 18] == 'X') {
                    acUCodeName[0] = 'S';
                    acUCodeName[1] = '2';
                    acUCodeName[2] = 'D';
                    acUCodeName[3] = 'E';
                    acUCodeName[4] = 'X';
                    acUCodeName[5] = ' ';

                    if (aBigBuffer[i + 21] == '0' || aBigBuffer[i + 21] == '1') {
                        acUCodeName[6] = aBigBuffer[i + 21];
                        acUCodeName[7] = aBigBuffer[i + 22];
                        acUCodeName[8] = aBigBuffer[i + 23];
                        acUCodeName[9] = aBigBuffer[i + 24];
                        acUCodeName[10] = '\0';

                        pRSP->nVersionUCode = 0;
                        eType = RUT_S2DEX1;
                        nCountVertex = 0;
                        break;
                    } else if (aBigBuffer[i + 31] == '2') {
                        acUCodeName[6] = aBigBuffer[i + 31];
                        acUCodeName[7] = aBigBuffer[i + 32];
                        acUCodeName[8] = aBigBuffer[i + 33];
                        acUCodeName[9] = aBigBuffer[i + 34];
                        acUCodeName[10] = '\0';

                        pRSP->nVersionUCode = 0;
                        eType = RUT_S2DEX2;
                        nCountVertex = 0;
                        break;
                    }
                }

                if (aBigBuffer[i + 14] == 'Z' && aBigBuffer[i + 15] == 'S' && aBigBuffer[i + 16] == 'o' &&
                    aBigBuffer[i + 17] == 'r' && aBigBuffer[i + 18] == 't') {
                    acUCodeName[0] = 'Z';
                    acUCodeName[1] = 'S';
                    acUCodeName[2] = 'o';
                    acUCodeName[3] = 'r';
                    acUCodeName[4] = 't';
                    acUCodeName[5] = ' ';
                    acUCodeName[6] = aBigBuffer[i + 22];
                    acUCodeName[7] = aBigBuffer[i + 23];
                    acUCodeName[8] = aBigBuffer[i + 24];
                    acUCodeName[9] = aBigBuffer[i + 25];
                    acUCodeName[10] = '\0';

                    pRSP->nVersionUCode = 3;
                    eType = RUT_ZSORT;
                    nCountVertex = 64;
                    // bug? missing "break;"
                }
            }
        }
    }

    if (eType == RUT_NONE) {
        if (nCheckSum == 0x3DDCC2B9DE351A0A) {
            pRSP->nVersionUCode = 1;
        } else if (nCheckSum == 0x8B9D7CFA7270C5A4) {
            pRSP->nVersionUCode = 5;
        } else {
            pRSP->nVersionUCode = 0;
        }
        acUCodeName[0] = 'F';
        acUCodeName[1] = 'A';
        acUCodeName[2] = 'S';
        acUCodeName[3] = 'T';
        acUCodeName[4] = '3';
        acUCodeName[5] = 'D';
        acUCodeName[6] = '?';
        acUCodeName[7] = '\0';

        eType = RUT_FAST3D;
        nCountVertex = 32;
    }

    if (!xlListMakeItem(pRSP->pListUCode, (void**)&pUCode)) {
        return false;
    }

    pUCode->eType = eType;
    pUCode->nCountVertex = nCountVertex;
    pUCode->nOffsetCode = nOffsetCode;
    pUCode->nLengthCode = nLengthCode;
    pUCode->nOffsetData = nOffsetData;
    pUCode->nLengthData = nLengthData;

    pRSP->eTypeUCode = pUCode->eType;
    pRSP->nCountVertex = pUCode->nCountVertex;
    if (pRSP->nVersionUCode == 5) {
        pRSP->n2TriMult = 2;
    } else {
        pRSP->n2TriMult = 1;
    }

    strcpy(pUCode->acUCodeName, acUCodeName);
    pUCode->nUCodeCheckSum = nCheckSum;
    rspSetupUCode(pRSP);

    return true;
}

// clang-format off
#include "emulator/rspASM.c"
#include "emulator/_aspMain.c"
#include "emulator/_gspJPEG.c"
#include "emulator/_gspS2DEX.c"
#include "emulator/_gspF3DEX.c"
// clang-format on

static bool rspSaveYield(Rsp* pRSP) {
    int iData;
    RspTask* pTask;

    pRSP->yield.bValid = true;
    pRSP->yield.iDL = pRSP->iDL;
    pRSP->yield.n2TriMult = pRSP->n2TriMult;
    pRSP->yield.nCountVertex = pRSP->nCountVertex;
    pRSP->yield.eTypeUCode = pRSP->eTypeUCode;
    pRSP->yield.nVersionUCode = pRSP->nVersionUCode;

    for (iData = 0; iData < 16; iData++) {
        pRSP->yield.anBaseSegment[iData] = pRSP->anBaseSegment[iData];
    }

    for (iData = 0; iData < 16; iData++) {
        pRSP->yield.apDL[iData] = pRSP->apDL[iData];
    }

    pTask = RSP_TASK(pRSP);
    if (!xlHeapCopy(&pRSP->yield.task, pTask, sizeof(RspTask))) {
        return false;
    }

    return true;
}

static bool rspLoadYield(Rsp* pRSP) {
    int iData;
    RspTask* pTask;

    pRSP->iDL = pRSP->yield.iDL;
    pRSP->n2TriMult = pRSP->yield.n2TriMult;
    pRSP->nCountVertex = pRSP->yield.nCountVertex;
    pRSP->eTypeUCode = pRSP->yield.eTypeUCode;
    pRSP->nVersionUCode = pRSP->yield.nVersionUCode;

    for (iData = 0; iData < 16; iData++) {
        pRSP->anBaseSegment[iData] = pRSP->yield.anBaseSegment[iData];
    }

    for (iData = 0; iData < 16; iData++) {
        pRSP->apDL[iData] = pRSP->yield.apDL[iData];
    }

    pTask = RSP_TASK(pRSP);
    if (!xlHeapCopy(pTask, &pRSP->yield.task, sizeof(RspTask))) {
        return false;
    }

    pRSP->yield.bValid = false;
    return true;
}

static bool rspParseGBI_Setup(Rsp* pRSP, RspTask* pTask) {
    s32 iSegment;

    if (pRSP->yield.bValid) {
        pRSP->yield.bValid = false;
    }

    pRSP->nGeometryMode = 0;
    pRSP->iDL = 0;

    if (!rspSetDL(pRSP, pTask->nOffsetMBI & 0x7FFFFF, false)) {
        return false;
    }

    for (iSegment = 0; iSegment < ARRAY_COUNT(pRSP->anBaseSegment); iSegment++) {
        pRSP->anBaseSegment[iSegment] = 0;
    }

    if (!rspFindUCode(pRSP, pTask)) {
        return false;
    }

    if (pRSP->eTypeUCode != RUT_ZSORT || pRSP->nPass == 1) {
        if (!frameBegin(SYSTEM_FRAME(pRSP->pHost), pRSP->nCountVertex)) {
            return false;
        }
    }

    PAD_STACK();
    return true;
}

static bool rspParseGBI(Rsp* pRSP, bool* pbDone, s32 nCount) {
    bool bDone;
    s32 nStatus;
    u64* pDL;
    Cpu* pCPU;

    pCPU = SYSTEM_CPU(pRSP->pHost);
    bDone = false;

    while (!bDone) {
        pDL = pRSP->apDL[pRSP->iDL];
        switch (pRSP->eTypeUCode) {
            case RUT_TURBO:
            case RUT_SPRITE2D:
            case RUT_FAST3D:
            case RUT_F3DEX1:
            case RUT_S2DEX1:
            case RUT_L3DEX1:
                nStatus = rspParseGBI_F3DEX1(pRSP, &pRSP->apDL[pRSP->iDL], &bDone);
                break;
            case RUT_ZSORT:
            case RUT_F3DEX2:
            case RUT_S2DEX2:
            case RUT_L3DEX2:
                nStatus = rspParseGBI_F3DEX2(pRSP, &pRSP->apDL[pRSP->iDL], &bDone);
                break;
            default:
                return false;
        }

        if (nStatus == 0) {
            pRSP->apDL[pRSP->iDL] = pDL;
            if (!rdpParseGBI(SYSTEM_RDP(pRSP->pHost), &pRSP->apDL[pRSP->iDL], pRSP->eTypeUCode)) {
                if (!rspPopDL(pRSP)) {
                    bDone = true;
                }
            }
        }

        if (nCount == -1) {
            if (pCPU->nRetrace != pCPU->nRetraceUsed) {
                break;
            }
        } else if (nCount != 0) {
            if (--nCount == 0) {
                break;
            }
        }
    }

    if (pRSP->eTypeUCode == RUT_ZSORT) {
        if (pRSP->nPass == 1) {
            pRSP->nPass = 2;
        } else {
            pRSP->nPass = 1;
        }
    } else {
        pRSP->nPass = 2;
    }

    if (bDone) {
        pRSP->nMode |= 8;
    }

    if (pbDone != NULL) {
        *pbDone = bDone;
    }

    return true;
}

bool rspPut8(Rsp* pRSP, u32 nAddress, s8* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s8*)pRSP->pDMEM + (nAddress & 0xFFF)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s8*)pRSP->pIMEM + (nAddress & 0xFFF)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

bool rspPut16(Rsp* pRSP, u32 nAddress, s16* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s16*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 1)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s16*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 1)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

bool rspPut32(Rsp* pRSP, u32 nAddress, s32* pData) {
    RspTask* pTask;
    s32 nData;
    s32 nSize;
    void* pTarget;
    void* pSource;
    s32 nLength;

    switch ((nAddress >> 12) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s32*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 2)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s32*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 2)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_BASE_REG):
            switch (nAddress & 0x1F) {
                case RSP_REG_ADDR_LO(SP_MEM_ADDR_REG):
                    pRSP->nAddressSP = *pData & 0x1FFF;
                    break;
                case RSP_REG_ADDR_LO(SP_DRAM_ADDR_REG):
                    pRSP->nAddressRDRAM = *pData & 0x03FFFFFF;
                    break;
                case RSP_REG_ADDR_LO(SP_RD_LEN_REG):
                    pRSP->nSizeGet = *pData;
                    nLength = pRSP->nSizeGet & 0xFFF;
                    if (pRSP->nAddressSP & 0x1000) {
                        pTarget = (u8*)pRSP->pIMEM + (pRSP->nAddressSP & 0xFFF);
                    } else {
                        pTarget = (u8*)pRSP->pDMEM + (pRSP->nAddressSP & 0xFFF);
                    }
                    if (!xlHeapCopy(pTarget, (s8*)SYSTEM_RAM(pRSP->pHost)->pBuffer + pRSP->nAddressRDRAM,
                                    nLength + 1)) {
                        return false;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_WR_LEN_REG):
                    pRSP->nSizePut = *pData;
                    nLength = pRSP->nSizePut & 0xFFF;
                    if (pRSP->nAddressSP & 0x1000) {
                        pSource = (u8*)pRSP->pIMEM + (pRSP->nAddressSP & 0xFFF);
                    } else {
                        pSource = (u8*)pRSP->pDMEM + (pRSP->nAddressSP & 0xFFF);
                    }
                    nSize = nLength + 1;
                    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pTarget, pRSP->nAddressRDRAM, (u32*)&nSize)) {
                        return false;
                    }
                    if (!xlHeapCopy(pTarget, pSource, nSize)) {
                        return false;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_STATUS_REG):
                    nData = *pData & 0xFFFF;
                    if (nData & 1) {
                        OSGetTick();
                        pRSP->nStatus &= ~0x1;
                        pTask = RSP_TASK(pRSP);
                        switch (pTask->nType) {
                            case 1:
                                if (pRSP->yield.bValid) {
                                    if (!rspLoadYield(pRSP)) {
                                        return false;
                                    }
                                    break;
                                }
                                pRSP->nMode |= 2;
                                break;
                            case 2:
                                if (pRSP->eTypeAudioUCode != RUT_UNKNOWN) {
                                    rspParseABI(pRSP, pTask);
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 3:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 4:
                                if (pTask->nOffsetYield == 0) {
                                    if (!rspParseJPEG_Decode(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                } else {
                                    if (!rspParseJPEG_DecodeZ(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 5:
                                if (pTask->nOffsetYield == 0) {
                                    if (!rspParseJPEG_Encode(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                } else {
                                    if (!rspParseJPEG_EncodeZ(pRSP, pTask)) {
                                        __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                                    }
                                }
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 6:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            case 7:
                                pRSP->nStatus |= 0x201;
                                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                                break;
                            default:
                                return false;
                        }
                    }
                    if (nData & 2) {
                        pRSP->nStatus |= 1;
                    }
                    if (nData & 4) {
                        pRSP->nStatus &= ~0x2;
                    }
                    if (nData & 8) {
                        xlObjectEvent(pRSP->pHost, 0x1001, (void*)5);
                    }
                    if (nData & 0x10) {
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                    }
                    if (nData & 0x20) {
                        pRSP->nStatus &= ~0x20;
                    }
                    if (nData & 0x40) {
                        pRSP->nStatus |= 0x20;
                    }
                    if (nData & 0x80) {
                        pRSP->nStatus &= ~0x40;
                    }
                    if (nData & 0x100) {
                        pRSP->nStatus |= 0x40;
                    }
                    if (nData & 0x200) {
                        pRSP->nStatus &= ~0x180;
                    }
                    if (nData & 0x400) {
                        if (!(pRSP->nStatus & 1)) {
                            pRSP->nStatus = pRSP->nStatus | 0x101;
                            if (!rspSaveYield(pRSP)) {
                                return false;
                            }
                            xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                        }
                    }
                    if (nData & 0x800) {
                        pRSP->nStatus &= ~0x100;
                    }
                    if (nData & 0x1000) {
                        pRSP->nStatus |= 0x100;
                    }
                    if (nData & 0x2000) {
                        pRSP->nStatus &= ~0x200;
                    }
                    if (nData & 0x4000) {
                        pRSP->nStatus |= 0x200;
                    }
                    if (nData & 0x8000) {
                        pRSP->nStatus &= ~0x400;
                    }
                    if (nData & 0x10000) {
                        pRSP->nStatus |= 0x400;
                    }
                    if (nData & 0x20000) {
                        pRSP->nStatus &= ~0x800;
                    }
                    if (nData & 0x40000) {
                        pRSP->nStatus |= 0x800;
                    }
                    if (nData & 0x80000) {
                        pRSP->nStatus &= ~0x1000;
                    }
                    if (nData & 0x100000) {
                        pRSP->nStatus |= 0x1000;
                    }
                    if (nData & 0x200000) {
                        pRSP->nStatus &= ~0x2000;
                    }
                    if (nData & 0x400000) {
                        pRSP->nStatus |= 0x2000;
                    }
                    if (nData & 0x800000) {
                        pRSP->nStatus &= ~0x4000;
                    }
                    if (nData & 0x01000000) {
                        pRSP->nStatus |= 0x4000;
                    }
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_FULL_REG):
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_BUSY_REG):
                    break;
                case RSP_REG_ADDR_LO(SP_SEMAPHORE_REG):
                    pRSP->nSemaphore = 0;
                    break;
                default:
                    return false;
            }
            break;
        case RSP_REG_ADDR_HI(SP_PC_REG):
            switch (nAddress & 0xF) {
                case RSP_REG_ADDR_LO(SP_PC_REG):
                    pRSP->nPC = *pData;
                    break;
                case RSP_REG_ADDR_LO(SP_IBIST_REG):
                    pRSP->nBIST = *pData & 0xFF;
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }

    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}

bool rspPut64(Rsp* pRSP, u32 nAddress, s64* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *((s64*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 3)) = *pData;
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *((s64*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 3)) = *pData;
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet8(Rsp* pRSP, u32 nAddress, s8* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s8*)pRSP->pDMEM + (nAddress & 0xFFF));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s8*)pRSP->pIMEM + (nAddress & 0xFFF));
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet16(Rsp* pRSP, u32 nAddress, s16* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s16*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 1));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s16*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 1));
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet32(Rsp* pRSP, u32 nAddress, s32* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s32*)pRSP->pDMEM + ((nAddress & 0xFFC) >> 2));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s32*)pRSP->pIMEM + ((nAddress & 0xFFC) >> 2));
            break;
        case RSP_REG_ADDR_HI(SP_BASE_REG):
            switch (nAddress & 0x1F) {
                case RSP_REG_ADDR_LO(SP_MEM_ADDR_REG):
                    *pData = pRSP->nAddressSP;
                    break;
                case RSP_REG_ADDR_LO(SP_DRAM_ADDR_REG):
                    *pData = pRSP->nAddressRDRAM;
                    break;
                case RSP_REG_ADDR_LO(SP_RD_LEN_REG):
                    *pData = pRSP->nSizeGet;
                    break;
                case RSP_REG_ADDR_LO(SP_WR_LEN_REG):
                    *pData = pRSP->nSizePut;
                    break;
                case RSP_REG_ADDR_LO(SP_STATUS_REG):
                    *pData = pRSP->nStatus & 0xFFFF;
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_FULL_REG):
                    *pData = pRSP->nFullDMA & 1;
                    break;
                case RSP_REG_ADDR_LO(SP_DMA_BUSY_REG):
                    *pData = pRSP->nBusyDMA & 1;
                    break;
                case RSP_REG_ADDR_LO(SP_SEMAPHORE_REG):
                    pRSP->nSemaphore = 1;
                    *pData = 0;
                    break;
                default:
                    return false;
            }
            break;
        case RSP_REG_ADDR_HI(SP_PC_REG):
            switch (nAddress & 0xF) {
                case RSP_REG_ADDR_LO(SP_PC_REG):
                    *pData = pRSP->nPC;
                    break;
                case RSP_REG_ADDR_LO(SP_IBIST_REG):
                    *pData = pRSP->nBIST & 0xFF;
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }

    return true;
}

bool rspGet64(Rsp* pRSP, u32 nAddress, s64* pData) {
    switch ((nAddress >> 0xC) & 0xFFF) {
        case RSP_REG_ADDR_HI(SP_DMEM_START):
            *pData = *((s64*)pRSP->pDMEM + ((nAddress & 0xFFF) >> 3));
            break;
        case RSP_REG_ADDR_HI(SP_IMEM_START):
            *pData = *((s64*)pRSP->pIMEM + ((nAddress & 0xFFF) >> 3));
            break;
        default:
            return false;
    }

    return true;
}

bool rspInvalidateCache(Rsp* pRSP, s32 nOffset0, s32 nOffset1) {
    RspUCode* pUCode;
    void* pListNode;
    s32 nOffsetUCode0;
    s32 nOffsetUCode1;

    nOffsetUCode0 = nOffset1 & 0x7FFFFF;
    nOffsetUCode1 = nOffset0 & 0x7FFFFF;
    pListNode = pRSP->pListUCode->pNodeHead;

    while (pListNode != NULL) {
        s32 offset0;
        s32 offset1;

        pUCode = (RspUCode*)NODE_DATA(pListNode);
        pListNode = NODE_NEXT(pListNode);

        if (pUCode->nOffsetCode < pUCode->nOffsetData) {
            offset0 = pUCode->nOffsetCode;
            offset1 = pUCode->nOffsetData + pUCode->nLengthData;
        } else {
            offset0 = pUCode->nOffsetData;
            offset1 = pUCode->nOffsetCode + pUCode->nLengthCode;
        }

        if ((nOffsetUCode1 <= offset0 && offset0 <= nOffsetUCode0) ||
            (nOffsetUCode1 <= offset1 && offset1 <= nOffsetUCode0)) {
            if (!xlListFreeItem(pRSP->pListUCode, (void**)&pUCode)) {
                return false;
            }
        }
    }

    return true;
}

bool rspEnableABI(Rsp* pRSP, bool bFlag) {
    pRSP->eTypeAudioUCode = bFlag ? RUT_NOCODE : RUT_UNKNOWN;
    return true;
}

bool rspFrameComplete(Rsp* pRSP) {
    if (pRSP->yield.bValid) {
        OSReport("FrameComplete: Yielded task pending...\n");
    }

    pRSP->nMode |= 4;
    return true;
}

bool rspUpdate(Rsp* pRSP, RspUpdateMode eMode) {
    RspTask* pTask;
    bool bDone;
    s32 nCount = 0;
    Frame* pFrame = SYSTEM_FRAME(pRSP->pHost);

    if ((pRSP->nMode & 4) && (pRSP->nMode & 8)) {
        if (pRSP->nMode & 0x10) {
            gNoSwapBuffer = true;
            pRSP->nMode |= 0x20;
        }
        if (!frameEnd(pFrame)) {
            return false;
        }
        pRSP->nMode &= ~0xC;
    }

    if (!(pRSP->nStatus & 1)) {
        if (pRSP->nMode & 0x20) {
            pRSP->nMode &= ~0x30;
            pRSP->nStatus |= 0x201;
            xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
            xlObjectEvent(pRSP->pHost, 0x1000, (void*)10);
        } else {
            if (pRSP->nMode & 2) {
                if (frameBeginOK(pFrame) && eMode == RUM_IDLE) {
                    pRSP->nMode &= ~0x2;
                    pRSP->nMode |= 0x10;

                    pTask = RSP_TASK(pRSP);
                    if (!rspParseGBI_Setup(pRSP, pTask)) {
                        return false;
                    }
                } else {
                    return true;
                }
            }

            if (eMode == RUM_IDLE) {
                nCount = -1;
            }

            if (nCount != 0) {
                if (rspParseGBI(pRSP, &bDone, nCount)) {
                    if (bDone) {
                        pRSP->nMode &= ~0x10;
                        pRSP->nStatus |= 0x201;
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
                        xlObjectEvent(pRSP->pHost, 0x1000, (void*)10);
                    }
                } else {
                    __cpuBreak(SYSTEM_CPU(pRSP->pHost));
                }
                pRSP->nTickLast = OSGetTick();
            }
        }
    }

    return true;
}

bool rspEvent(Rsp* pRSP, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRSP->nPC = 0;
            pRSP->pHost = pArgument;
            pRSP->nPass = 1;
            pRSP->nMode = 0;
            pRSP->yield.bValid = false;
            pRSP->nStatus = 1;
            pRSP->pfUpdateWaiting = NULL;
            if (!xlListMake(&pRSP->pListUCode, 0x60)) {
                return false;
            }
            if (!xlHeapTake(&pRSP->pDMEM, 0x1000)) {
                return false;
            }
            if (!xlHeapTake(&pRSP->pIMEM, 0x1000)) {
                return false;
            }
            if (!rspSetupS2DEX(pRSP)) {
                return false;
            }
            if (!rspInitAudioDMEM1(pRSP)) {
                return false;
            }
            pRSP->eTypeAudioUCode = RUT_NOCODE;
            break;
        case 3:
            xlHeapFree(&pRSP->pIMEM);
            xlHeapFree(&pRSP->pDMEM);
            if (!xlListFree(&pRSP->pListUCode)) {
                return false;
            }
            break;
        case 0x1002:
            if (!cpuSetDevicePut(SYSTEM_CPU(pRSP->pHost), pArgument, (Put8Func)rspPut8, (Put16Func)rspPut16,
                                 (Put32Func)rspPut32, (Put64Func)rspPut64)) {
                return false;
            }
            if (!cpuSetDeviceGet(SYSTEM_CPU(pRSP->pHost), pArgument, (Get8Func)rspGet8, (Get16Func)rspGet16,
                                 (Get32Func)rspGet32, (Get64Func)rspGet64)) {
                return false;
            }
            break;
        case 0:
        case 1:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}
