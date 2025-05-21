#include "emulator/rsp.h"

static bool rspSetGeometryMode1(Rsp* pRSP, s32 nMode) {
    s32 nModeFrame = 0;

    pRSP->nGeometryMode = nMode;
    if (nMode & 1) {
        nModeFrame |= 1;
    }
    if (nMode & 4) {
        nModeFrame |= 2;
    }
    if (nMode & 0x200) {
        nModeFrame |= 0x200;
    }
    if (nMode & 0x1000) {
        nModeFrame |= 4;
    }
    if (nMode & 0x2000) {
        nModeFrame |= 8;
    }
    if (nMode & 0x10000) {
        nModeFrame |= 0x10;
    }
    if (nMode & 0x20000) {
        nModeFrame |= 0x20;
    }
    if (nMode & 0x40000) {
        nModeFrame |= 0x80;
    }
    if (nMode & 0x80000) {
        nModeFrame |= 0x100;
    }
    if (nMode & 0x800000) {
        nModeFrame |= 0x400;
    }

    if (!frameSetMode(SYSTEM_FRAME(pRSP->pHost), FMT_GEOMETRY, nModeFrame)) {
        return false;
    }

    return true;
}

static bool rspParseGBI_F3DEX1(Rsp* pRSP, u64** ppnGBI, bool* pbDone) {
    Mtx44 matrix;
    Primitive primitive;
    u32 iVertex;
    u32 bDone;
    u64* pnGBI;
    u32 nCommandLo;
    u32 nCommandHi;
    Frame* pFrame;

    !ppnGBI; // fake?

    pnGBI = *ppnGBI;
    pFrame = SYSTEM_FRAME(pRSP->pHost);
    nCommandHi = GBI_COMMAND_HI(pnGBI);
    nCommandLo = GBI_COMMAND_LO(pnGBI);

    *ppnGBI = ++pnGBI;
    pFrame->pnGBI = pnGBI;

    switch (nCommandHi >> 24) {
        case 0xC1: { // S2DEX1: G_OBJ_LOADTXTR
            s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

            if (!rspObjLoadTxtr(pRSP, pFrame, nAddress)) {
                return false;
            }
            break;
        }
        case 0xC2: { // S2DEX1: G_OBJ_LDTX_SPRITE
            s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

            if (!rspObjLoadTxSprite(pRSP, pFrame, nAddress)) {
                return false;
            }
            break;
        }
        case 0xC3: { // S2DEX1: G_OBJ_LDTX_RECT
            s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

            if (!rspObjLoadTxRect(pRSP, pFrame, nAddress)) {
                return false;
            }
            break;
        }
        case 0xC4: { // S2DEX1: G_OBJ_LDTX_RECT_R
            s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

            if (!rspObjLoadTxRectR(pRSP, pFrame, nAddress)) {
                return false;
            }
            break;
        }
        case 0xE4: { // S2DEX1: G_RDPHALF_0
            if (pRSP->eTypeUCode == RUT_S2DEX1 && ((*pnGBI >> 56) & 0xFF) == 0xB0) { // G_SELECT_DL
                bool bPush;
                u8 nSid2D;
                u32 nDLAdrs;
                u32 nFlag2D;
                s32 pad;

                nSid2D = (s32)((nCommandHi >> 16) & 0xFF) / 4;
                nDLAdrs = nCommandHi & 0xFFFF;
                nFlag2D = nCommandLo;

                nCommandHi = GBI_COMMAND_HI(pnGBI);
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                *ppnGBI = ++pnGBI;

                bPush = (nCommandHi >> 16) & 0xFF;
                nDLAdrs |= ((nCommandHi & 0xFFFF) << 16);

                if (nFlag2D != (pRSP->aStatus[nSid2D] & nCommandLo)) {
                    pRSP->aStatus[nSid2D] = (pRSP->aStatus[nSid2D] & ~nCommandLo) | (nFlag2D & nCommandLo);
                    if (!rspSetDL(pRSP, nDLAdrs, bPush ? false : true)) {
                        return false;
                    }
                }
            } else {
                return false;
            }
            break;
        }
        case 0x00: // F3DEX1: G_SPNOOP
            break;
        case 0x01:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_BG_1CYC
                uObjBg bg;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                rspFillObjBgScale(pRSP, nAddress, &bg);
                guS2DEmuSetScissor(0, 0, N64_FRAME_WIDTH << 2, N64_FRAME_HEIGHT << 2, 0);
                if (!guS2DEmuBgRect1Cyc(pRSP, pFrame, &bg)) {
                    return false;
                }
            } else { // F3DEX1: G_MTX
                s32 nMode = (nCommandHi >> 16) & 0xFF;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                    return false;
                }
                if (!frameSetMatrix(pFrame, matrix, nMode & 1 ? FMT_PROJECTION : FMT_MODELVIEW,
                                    nMode & 2 ? true : false, nMode & 4 ? true : false, nAddress)) {
                    return false;
                }
            }
            break;
        case 0x02:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_BG_COPY
                s32 nMode;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspBgRectCopy(pRSP, pFrame, nAddress)) {
                    return false;
                }
                frameGetMode(pFrame, FMT_OTHER0, (u32*)&nMode);
                frameGetMode(pFrame, FMT_OTHER1, (u32*)&nMode);
            } else { // F3DEX1: G_RESERVED0
            }
            break;
        case 0x03:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_OBJ_RECTANGLE
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjRectangle(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX1: G_MOVEMEM
                switch ((nCommandHi >> 16) & 0xFF) {
                    case 0x80: { // G_MV_VIEWPORT
                        void* pData;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);
                        s32 pad;

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                            return false;
                        }
                        if (!frameSetViewport(pFrame, pData)) {
                            return false;
                        }
                        break;
                    }
                    case 0x82: { // G_MV_LOOKATY
                        void* pData;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                            return false;
                        }
                        if (!frameSetLookAt(pFrame, 1, pData)) {
                            return false;
                        }
                        break;
                    }
                    case 0x84: { // G_MV_LOOKATX
                        void* pData;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                            return false;
                        }
                        if (!frameSetLookAt(pFrame, 0, pData)) {
                            return false;
                        }
                        break;
                    }
                    case 0x86: // G_MV_L0
                    case 0x88: // G_MV_L1
                    case 0x8A: // G_MV_L2
                    case 0x8C: // G_MV_L3
                    case 0x8E: // G_MV_L4
                    case 0x90: // G_MV_L5
                    case 0x92: // G_MV_L6
                    case 0x94: // G_MV_L7
                    {
                        s8* pData;
                        s32 iLight = (((nCommandHi >> 16) & 0xFF) - 0x86) >> 1;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pData, nAddress, NULL)) {
                            return false;
                        }
                        if (!frameSetLight(pFrame, iLight, pData)) {
                            return false;
                        }
                        break;
                    }
                    case 0x96: // G_MV_TXTATT
                        break;
                    case 0x9E: { // G_MV_MATRIX_1
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                            return false;
                        }
                        if (!frameSetMatrix(pFrame, matrix, FMT_GEOMETRY, true, false, nAddress)) {
                            return false;
                        }
                        break;
                    }
                    case 0x98: // G_MV_MATRIX_2
                    case 0x9A: // G_MV_MATRIX_3
                    case 0x9C: // G_MV_MATRIX_4
                        break;
                    default:
                        return false;
                }
            }
            break;
        case 0x04:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_OBJ_SPRITE
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjSprite(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX1: G_VTX
                void* pBuffer;
                s32 nCount;
                s32 iVertex0;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);
                s32 pad[9];

                if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pBuffer, nAddress, NULL)) {
                    return false;
                }
                if (pRSP->eTypeUCode == RUT_FAST3D) {
                    if (pRSP->nVersionUCode == 1) {
                        iVertex0 = ((nCommandHi >> 16) & 0xFF) / 5;
                        nCount = ((nCommandHi & 0xFFFF) + 1) / 528;
                    } else {
                        iVertex0 = (nCommandHi >> 16) & 0xF;
                        nCount = ((nCommandHi >> 20) & 0xF) + 1;
                    }
                } else {
                    iVertex0 = (nCommandHi >> 17) & 0x7F;
                    nCount = (nCommandHi >> 10) & 0x3F;
                }
                if (!frameLoadVertex(pFrame, pBuffer, iVertex0, nCount)) {
                    return false;
                }
            }
            break;
        case 0x05:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_OBJ_MOVEMEM
                if (((nCommandHi >> 16) & 0xFF) == 7 && (nCommandHi & 0xFFFF) == 2) {
                    s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                    if (!rspObjSubMatrix(pRSP, pFrame, nAddress)) {
                        return false;
                    }
                } else if (((nCommandHi >> 16) & 0xFF) == 0x17 && (nCommandHi & 0xFFFF) == 0) {
                    s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                    if (!rspObjMatrix(pRSP, pFrame, nAddress)) {
                        return false;
                    }
                }
            }
            break;
        case 0x06: // F3DEX1: G_DL
            if (!rspSetDL(pRSP, nCommandLo, (nCommandHi >> 16) & 0xFF ? false : true)) {
                return false;
            }
            break;
        case 0x07: // F3DEX1: G_RESERVED2
            break;
        case 0x08: // F3DEX1: G_RESERVED3
            break;
        case 0x09: // F3DEX1: G_SPRITE2D_BASE
            break;
        case 0xBF: // F3DEX1: G_TRI1
            bDone = false;
            while (!bDone) {
                iVertex = 0;
                while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 3) {
                    if (pRSP->eTypeUCode == RUT_FAST3D) {
                        if (pRSP->nVersionUCode == 1) {
                            primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) / 5;
                            primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) / 5;
                            primitive.anData[iVertex + 2] = ((nCommandLo >> 0) & 0xFF) / 5;
                        } else {
                            primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) / 10;
                            primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) / 10;
                            primitive.anData[iVertex + 2] = ((nCommandLo >> 0) & 0xFF) / 10;
                        }
                    } else {
                        primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = ((nCommandLo >> 0) & 0xFF) >> 1;
                    }

                    if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                        primitive.anData[iVertex + 2] >= 80) {
                        return false;
                    }

                    nCommandHi = GBI_COMMAND_HI(pnGBI);
                    nCommandLo = GBI_COMMAND_LO(pnGBI);
                    iVertex += 3;
                    if (((nCommandHi >> 24) & 0xFF) == 0xBF) { // G_TRI1
                        *ppnGBI = ++pnGBI;
                    } else {
                        bDone = true;
                    }
                }

                primitive.nCount = iVertex;
                if (!pFrame->aDraw[1](pFrame, &primitive)) {
                    return false;
                }
            }
            break;
        case 0xBE: { // F3DEX1: G_CULLDL
            u32 nVertexStart = (nCommandHi & 0xFFFF) >> 1;
            u32 nVertexEnd = (nCommandLo & 0xFFFF) >> 1;

            if (frameCullDL(pFrame, nVertexStart, nVertexEnd)) {
                if (!rspPopDL(pRSP)) {
                    *pbDone = true;
                }
            }
            break;
        }
        case 0xBD: // F3DEX1: G_POPMTX
            if (!frameGetMatrix(pFrame, NULL, FMT_MODELVIEW, true)) {
                return false;
            }
            break;
        case 0xBC: // G_MOVEWORD
            switch (nCommandHi & 0xFF) {
                case 0x00: { // G_MW_MATRIX
                    s32 nWhere = (nCommandHi >> 5) & 1;
                    s32 nData1 = (nCommandLo >> 16) & 0xFFFF;
                    s32 nData2 = nCommandLo & 0xFFFF;
                    s32 iRow = (nCommandHi >> 3) & 3;
                    s32 iCol = (nCommandHi >> 1) & 3;

                    // bug? matrix is never used
                    if (nWhere) {
                        matrix[iRow][iCol + 0] = ((s32)matrix[iRow][iCol + 0] & 0xFFFF0000) | nData1;
                        matrix[iRow][iCol + 1] = ((s32)matrix[iRow][iCol + 1] & 0xFFFF0000) | nData2;
                    } else {
                        matrix[iRow][iCol + 0] = ((s32)matrix[iRow][iCol + 0] & 0xFFFF) | (nData1 << 16);
                        matrix[iRow][iCol + 1] = ((s32)matrix[iRow][iCol + 1] & 0xFFFF) | (nData2 << 16);
                    }
                    break;
                }
                case 0x02: // G_MW_NUMLIGHT
                    if ((nCommandLo & 0xFF) == 0) {
                        if (!frameSetLightCount(pFrame, (nCommandLo >> 8) & 0xFF)) {
                            return false;
                        }
                    } else {
                        if (!frameSetLightCount(pFrame, ((s32)(nCommandLo & 0xFF) / 32) - 1)) {
                            return false;
                        }
                    }
                    break;
                case 0x04: // G_MW_CLIP
                    break;
                case 0x06: // G_MW_SEGMENT
                    pRSP->anBaseSegment[(nCommandHi >> 10) & 0xF] = nCommandLo;
                    break;
                case 0x08:
                    if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_MW_GENSTAT
                        u32 nSid = (nCommandHi >> 8) & 0xFF;

                        if (nSid == 0 || nSid == 4 || nSid == 8 || nSid == 12) {
                            pRSP->aStatus[nSid >> 2] = nCommandLo;
                        }
                    } else { // F3DEX1: G_MW_FOG
                        if (!frameSetMode(pFrame, FMT_FOG, nCommandLo)) {
                            return false;
                        }
                    }
                    break;
                case 0x0A: { // G_MW_LIGHTCOL
                    // bug? nLight should be (nCommandHi >> 13) & 7
                    int nLight = (nCommandHi >> 5) & 0xF;

                    nLight = nLight & 0xFF; // fake
                    pFrame->aLight[nLight].rColorR = (s32)((nCommandLo >> 24) & 0xFF);
                    pFrame->aLight[nLight].rColorG = (s32)((nCommandLo >> 16) & 0xFF);
                    pFrame->aLight[nLight].rColorB = (s32)((nCommandLo >> 8) & 0xFF);
                    break;
                }
                case 0x0C: // G_MW_POINTS
                case 0x0E: // G_MW_PERSPNORM
                    break;
                default:
                    return false;
            }
            break;
        case 0xBB: // F3DEX1: G_TEXTURE
            if (!frameSetMode(pFrame, FMT_TEXTURE1, nCommandLo)) {
                return false;
            }
            if (!frameSetMode(pFrame, FMT_TEXTURE2, nCommandHi & 0xFFFFFF)) {
                return false;
            }
            break;
        case 0xBA: { // F3DEX1: G_SETOTHERMODE_H
            u32 nData = nCommandLo;
            u32 nSize = nCommandHi & 0xFF;
            u32 nMove = (nCommandHi >> 8) & 0xFF;

            if (!frameSetMode(pFrame, FMT_OTHER1,
                              nData | (pFrame->aMode[FMT_OTHER1] & ~(((1 << nSize) - 1) << nMove)))) {
                return false;
            }
            break;
        }
        case 0xB9: { // F3DEX1: G_SETOTHERMODE_L
            u32 nData = nCommandLo;
            u32 nSize = nCommandHi & 0xFF;
            u32 nMove = (nCommandHi >> 8) & 0xFF;

            if (!frameSetMode(pFrame, FMT_OTHER0,
                              nData | (pFrame->aMode[FMT_OTHER0] & ~(((1 << nSize) - 1) << nMove)))) {
                return false;
            }
            break;
        }
        case 0xB8: // F3DEX1: G_ENDDL
            if (!rspPopDL(pRSP)) {
                *pbDone = true;
            }
            break;
        case 0xB7: // F3DEX1: G_SETGEOMETRYMODE
            if (!rspSetGeometryMode1(pRSP, pRSP->nGeometryMode | (nCommandLo & 0xFFFFFF))) {
                return false;
            }
            break;
        case 0xB6: // F3DEX1: G_CLEARGEOMETRYMODE
            if (!rspSetGeometryMode1(pRSP, pRSP->nGeometryMode & (~nCommandLo & 0xFFFFFF))) {
                return false;
            }
            break;
        case 0xB5: // F3DEX1: G_LINE3D
            if (pRSP->eTypeUCode == RUT_FAST3D || pRSP->eTypeUCode == RUT_F3DEX1) {
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 6) {
                        if (pRSP->nVersionUCode == 1) {
                            primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) / 5;
                            primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) / 5;
                            primitive.anData[iVertex + 2] = ((nCommandLo >> 0) & 0xFF) / 5;
                            primitive.anData[iVertex + 3] = ((nCommandLo >> 0) & 0xFF) / 5;
                            primitive.anData[iVertex + 4] = ((nCommandLo >> 24) & 0xFF) / 5;
                            primitive.anData[iVertex + 5] = ((nCommandLo >> 16) & 0xFF) / 5;
                        } else {
                            primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) >> 1;
                            primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) >> 1;
                            primitive.anData[iVertex + 2] = ((nCommandLo >> 0) & 0xFF) >> 1;
                            primitive.anData[iVertex + 3] = ((nCommandLo >> 0) & 0xFF) >> 1;
                            primitive.anData[iVertex + 4] = ((nCommandLo >> 24) & 0xFF) >> 1;
                            primitive.anData[iVertex + 5] = ((nCommandLo >> 16) & 0xFF) >> 1;
                        }

                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                            primitive.anData[iVertex + 2] >= 80 || primitive.anData[iVertex + 3] >= 80 ||
                            primitive.anData[iVertex + 4] >= 80 || primitive.anData[iVertex + 5] >= 80) {
                            return false;
                        }

                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        iVertex += 6;
                        if (((nCommandHi >> 24) & 0xFF) == 0xB5) { // G_LINE3D
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[1](pFrame, &primitive)) {
                        return false;
                    }
                }
            } else {
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 3) {
                        primitive.anData[iVertex + 0] = ((nCommandLo >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandLo >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = (nCommandLo & 0xFF) + 3;
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80) {
                            return false;
                        }

                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        iVertex += 3;
                        if (((nCommandHi >> 24) & 0xFF) == 0xB5) { // G_LINE3D
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[0](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0xB4: { // F3DEX1: G_RDPHALF_1
            u32 nValue = nCommandLo;

            nCommandHi = GBI_COMMAND_HI(pnGBI);
            nCommandLo = GBI_COMMAND_LO(pnGBI);
            switch ((nCommandHi >> 24) & 0xFF) {
                case 0xB0: { // G_BRANCH_Z
                    *ppnGBI = ++pnGBI;
                    if (!rspSetDL(pRSP, nValue, false)) {
                        return false;
                    }
                    break;
                }
                case 0xAF: { // G_LOAD_UCODE
                    RspTask* pTask;

                    pRSP->apDL[pRSP->iDL] = pnGBI + 1;

                    pTask = (RspTask*)((u8*)pRSP->pDMEM + 0xFC0);
                    pTask->nOffsetCode = nCommandLo;
                    pTask->nOffsetData = nValue;
                    pTask->nLengthData = nCommandHi & 0xFFFF;

                    if (!rspFindUCode(pRSP, pTask)) {
                        return false;
                    }

                    if (!frameResetUCode(pFrame, FRT_WARM)) {
                        return false;
                    }
                    break;
                }
            }
            break;
        }
        case 0xB3: // F3DEX1: G_RDPHALF_2
            return false;
        case 0xB2:
            if (pRSP->eTypeUCode == RUT_TURBO || pRSP->eTypeUCode == RUT_FAST3D) {
                break;
            }
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_OBJ_RECTANGLE_R
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjRectangleR(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX1: G_MODIFYVTX
                s32 iVertex = (nCommandHi >> 1) & 0x7FFF;
                s32 nVal = (nCommandHi >> 16) & 0xFF;

                switch (nVal) {
                    case 0x10: // G_MWO_POINT_RGBA
                        pFrame->aVertex[iVertex].anColor[0] = (nCommandLo >> 24) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[1] = (nCommandLo >> 16) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[2] = (nCommandLo >> 8) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[3] = nCommandLo & 0xFF;
                        break;
                    case 0x14: // G_MWO_POINT_ST
                        pFrame->aVertex[iVertex].rS = (s32)(nCommandLo >> 16) / 32.0f;
                        pFrame->aVertex[iVertex].rT = (s32)(nCommandLo & 0xFFFF) / 32.0f;
                        break;
                    case 0x18: // G_MWO_POINT_XYSCREEN
                        break;
                    case 0x1C: // G_MWO_POINT_ZSCREEN
                        break;
                }
            }
            break;
        case 0xB1:
            if (pRSP->eTypeUCode == RUT_S2DEX1) { // S2DEX1: G_OBJ_RENDERMODE
                pRSP->nMode2D = nCommandLo & 0xFFFF;
            } else { // F3DEX1: G_TRI2
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < pRSP->n2TriMult * (ARRAY_COUNT(primitive.anData) - 6)) {
                        if (pRSP->eTypeUCode == RUT_FAST3D) {
                            if (pRSP->nVersionUCode == 1) {
                                primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) / 5;
                                primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) / 5;
                                primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) / 5;
                                primitive.anData[iVertex + 3] = ((nCommandLo >> 16) & 0xFF) / 5;
                                primitive.anData[iVertex + 4] = ((nCommandLo >> 8) & 0xFF) / 5;
                                primitive.anData[iVertex + 5] = ((nCommandLo >> 0) & 0xFF) / 5;
                            } else if (pRSP->nVersionUCode == 5) {
                                primitive.anData[iVertex + 0] = (nCommandLo >> 4) & 0xF;
                                primitive.anData[iVertex + 1] = (nCommandHi >> 0) & 0xF;
                                primitive.anData[iVertex + 2] = (nCommandLo >> 0) & 0xF;
                                primitive.anData[iVertex + 3] = (nCommandLo >> 12) & 0xF;
                                primitive.anData[iVertex + 4] = (nCommandHi >> 4) & 0xF;
                                primitive.anData[iVertex + 5] = (nCommandLo >> 8) & 0xF;
                                primitive.anData[iVertex + 6] = (nCommandLo >> 20) & 0xF;
                                primitive.anData[iVertex + 7] = (nCommandHi >> 8) & 0xF;
                                primitive.anData[iVertex + 8] = (nCommandLo >> 16) & 0xF;
                                primitive.anData[iVertex + 9] = (nCommandLo >> 28) & 0xF;
                                primitive.anData[iVertex + 10] = (nCommandHi >> 12) & 0xF;
                                primitive.anData[iVertex + 11] = (nCommandLo >> 24) & 0xF;
                            } else {
                                primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) / 10;
                                primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) / 10;
                                primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) / 10;
                                primitive.anData[iVertex + 3] = ((nCommandLo >> 16) & 0xFF) / 10;
                                primitive.anData[iVertex + 4] = ((nCommandLo >> 8) & 0xFF) / 10;
                                primitive.anData[iVertex + 5] = ((nCommandLo >> 0) & 0xFF) / 10;
                            }
                        } else {
                            primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) >> 1;
                            primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) >> 1;
                            primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) >> 1;
                            primitive.anData[iVertex + 3] = ((nCommandLo >> 16) & 0xFF) >> 1;
                            primitive.anData[iVertex + 4] = ((nCommandLo >> 8) & 0xFF) >> 1;
                            primitive.anData[iVertex + 5] = ((nCommandLo >> 0) & 0xFF) >> 1;
                        }
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                            primitive.anData[iVertex + 2] >= 80 || primitive.anData[iVertex + 3] >= 80 ||
                            primitive.anData[iVertex + 4] >= 80 || primitive.anData[iVertex + 5] >= 80) {
                            return false;
                        }

                        iVertex += pRSP->n2TriMult * 6;
                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        if (((nCommandHi >> 24) & 0xFF) == 0xB1) { // G_TRI2
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[1](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0xB0: // F3DEX1: G_BRANCH_Z
            return false;
        case 0xAF: // F3DEX1: G_LOAD_UCODE
            return false;
        default:
            return false;
    }

    !pRSP; // fake
    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}

static bool rspGeometryMode(Rsp* pRSP, s32 nSet, s32 nClr) {
    s32 nMode = 0;

    pRSP->nGeometryMode &= nClr;
    pRSP->nGeometryMode |= nSet;
    if (pRSP->nGeometryMode & 1) {
        nMode |= 1;
    }
    if (pRSP->nGeometryMode & 4) {
        nMode |= 2;
    }
    if (pRSP->nGeometryMode & 0x200) {
        nMode |= 4;
    }
    if (pRSP->nGeometryMode & 0x400) {
        nMode |= 8;
    }
    if (pRSP->nGeometryMode & 0x10000) {
        nMode |= 0x10;
    }
    if (pRSP->nGeometryMode & 0x20000) {
        nMode |= 0x20;
    }
    if (pRSP->nGeometryMode & 0x40000) {
        nMode |= 0x80;
    }
    if (pRSP->nGeometryMode & 0x80000) {
        nMode |= 0x100;
    }
    if (pRSP->nGeometryMode & 0x200000) {
        nMode |= 0x200;
    }
    if (pRSP->nGeometryMode & 0x800000) {
        nMode |= 0x400;
    }
    if (pRSP->nGeometryMode & 0x400000) {
        nMode |= 0x800;
    }

    if (!frameSetMode(SYSTEM_FRAME(pRSP->pHost), FMT_GEOMETRY, nMode)) {
        return false;
    }

    return true;
}

static bool rspParseGBI_F3DEX2(Rsp* pRSP, u64** ppnGBI, bool* pbDone) {
    s32 iVertex;
    bool bDone = false;
    Mtx44 matrix;
    Primitive primitive;
    u64* pnGBI;
    u32 nCommandLo;
    u32 nCommandHi;
    Frame* pFrame;
    u32 c;

    !ppnGBI; // fake?

    pnGBI = *ppnGBI;
    pFrame = SYSTEM_FRAME(pRSP->pHost);
    nCommandHi = GBI_COMMAND_HI(pnGBI);
    nCommandLo = GBI_COMMAND_LO(pnGBI);

    c = (nCommandHi >> 24) & 0xFF; // fake?

    *ppnGBI = ++pnGBI;
    pFrame->pnGBI = pnGBI;

    switch (c) {
        case 0x00: // G_NOOP
        case 0x80:
        case 0x81:
            break;
        case 0xB1:
            return false;
        case 0xF1: // G_RDPHALF_2
            return false;
        case 0xE3: { // G_SETOTHERMODE_H
            u32 nData = nCommandLo;
            u32 nSize = (nCommandHi & 0xFF) + 1;
            u32 nMove = (32 - nSize) - ((nCommandHi >> 8) & 0xFF);

            if (!frameSetMode(pFrame, FMT_OTHER1,
                              nData | (pFrame->aMode[FMT_OTHER1] & ~(((1 << nSize) - 1) << nMove)))) {
                return false;
            }
            break;
        }
        case 0xE2: { // G_SETOTHERMODE_L
            u32 nData = nCommandLo;
            u32 nSize = (nCommandHi & 0xFF) + 1;
            u32 nMove = (32 - nSize) - ((nCommandHi >> 8) & 0xFF);

            if (!frameSetMode(pFrame, FMT_OTHER0,
                              nData | (pFrame->aMode[FMT_OTHER0] & ~(((1 << nSize) - 1) << nMove)))) {
                return false;
            }
            break;
        }
        case 0xE1: { // G_RDPHALF_1
            u32 nValue = nCommandLo;

            nCommandHi = GBI_COMMAND_HI(pnGBI);
            nCommandLo = GBI_COMMAND_LO(pnGBI);
            switch ((nCommandHi >> 24) & 0xFF) {
                case 0x4: { // G_BRANCH_Z
                    *ppnGBI = ++pnGBI;
                    if (!rspSetDL(pRSP, nValue, false)) {
                        return false;
                    }
                    break;
                }
                case 0xDD: { // G_LOAD_UCODE
                    RspTask* pTask;

                    pRSP->apDL[pRSP->iDL] = pnGBI + 1;

                    pTask = (RspTask*)((u8*)pRSP->pDMEM + 0xFC0);
                    pTask->nOffsetCode = nCommandLo;
                    pTask->nOffsetData = nValue;
                    pTask->nLengthData = nCommandHi & 0xFFFF;

                    if (!rspFindUCode(pRSP, pTask)) {
                        return false;
                    }

                    if (!frameResetUCode(pFrame, FRT_WARM)) {
                        return false;
                    }
                    break;
                }
            }
            break;
        }
        case 0xE0: // G_SPNOOP
            break;
        case 0xDF: // G_ENDDL
            if (!rspPopDL(pRSP)) {
                *pbDone = true;
            }
            if (pRSP->nStatusSubDL == 1) {
                pRSP->nStatusSubDL = 0;
                pRSP->nZSortSubDL = 0;
            }
            break;
        case 0xDE: // G_DL
            if (!rspSetDL(pRSP, nCommandLo, (nCommandHi >> 16) & 0xFF ? false : true)) {
                return false;
            }
            break;
        case 0xDD: // G_LOAD_UCODE
            return false;
        case 0xDC:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_MOVEMEM
                if (((nCommandHi >> 16) & 0xFF) == 7 && (nCommandHi & 0xFFFF) == 2) {
                    s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                    if (!rspObjSubMatrix(pRSP, pFrame, nAddress)) {
                        return false;
                    }
                } else if (((nCommandHi >> 16) & 0xFF) == 0x17 && (nCommandHi & 0xFFFF) == 0) {
                    s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                    if (!rspObjMatrix(pRSP, pFrame, nAddress)) {
                        return false;
                    }
                }
            } else if (pRSP->eTypeUCode == RUT_ZSORT) { // ZSORT: G_ZS_MOVEMEM
                s32 nLength;
                s32 nOffset;
                s32 nId;
                s32 nFlag;
                s32 nAddress;
                void* pData;

                nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);
                nLength = (((nCommandHi >> 15) & 0x1FF) + 1) << 3;
                nOffset = ((nCommandHi >> 6) & 0x1FF) << 3;
                nId = nCommandHi & 0x3E;
                nFlag = nCommandHi & 1;

                if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                    return false;
                }
                switch (nId) {
                    case 0x0C: { // GZM_VIEWPORT
                        u16* pnData16;
                        s16 nFogStart;
                        s16 nFogEnd;
                        s32 nDelta;
                        s32 nStart;

                        if (!frameSetViewport(pFrame, pData)) {
                            return false;
                        }

                        pnData16 = (u16*)pData;
                        nFogStart = pnData16[3];
                        nFogEnd = pnData16[7];
                        if (nFogEnd - nFogStart == 0) {
                            nDelta = 0;
                            nStart = 500 - nFogStart;
                        } else {
                            nDelta = 128000 / (nFogEnd - nFogStart);
                            nStart = ((500 - nFogStart) << 8) / (nFogEnd - nFogStart);
                        }

                        // bug? (nDelta << 16) has no effect due to & 0xFFFF
                        if (!frameSetMode(pFrame, FMT_FOG, ((nDelta << 16) | nStart) & 0xFFFF)) {
                            return false;
                        }
                        break;
                    }
                    case 0x00: { // GZF_LOAD
                        if (nFlag == 0) {
                            if (nLength == 8) {
                                pRSP->nAmbientLightAddress = nAddress;
                            } else if (nLength == 16) {
                                s8* pLight;
                                u32 iIndex;
                                bool bFound = false;

                                if (((u8*)pData)[0] != 0 || ((u8*)pData)[1] != 0 || ((u8*)pData)[2] != 0) {
                                    for (iIndex = 0; iIndex < pRSP->nNumZSortLights; iIndex++) {
                                        // bug? should be aLightAddresses[iIndex]
                                        if (nAddress == pRSP->aLightAddresses[pRSP->nNumZSortLights]) {
                                            bFound = true;
                                            break;
                                        }
                                    }

                                    if (bFound) {
                                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pLight, nAddress, NULL)) {
                                            return false;
                                        }
                                        if (!frameSetLight(pFrame, iIndex, pLight)) {
                                            return false;
                                        }
                                    } else if (pRSP->nNumZSortLights < 7 && pRSP->nAmbientLightAddress != 0) {
                                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pLight, nAddress, NULL)) {
                                            return false;
                                        }
                                        if (!frameSetLight(pFrame, pRSP->nNumZSortLights, pLight)) {
                                            return false;
                                        }
                                        pRSP->aLightAddresses[pRSP->nNumZSortLights] = nAddress;
                                        pRSP->nNumZSortLights++;
                                    }

                                    if (pRSP->nAmbientLightAddress != 0) {
                                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pLight,
                                                          pRSP->nAmbientLightAddress, NULL)) {
                                            return false;
                                        }
                                        if (!frameSetLight(pFrame, pRSP->nNumZSortLights, pLight)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                            xlHeapCopy((u8*)pRSP->pDMEM + nOffset, pData, nLength);
                        } else {
                            xlHeapCopy(pData, (u8*)pRSP->pDMEM + nOffset, nLength);
                        }
                        break;
                    }
                    case 0x04: // GZM_MMTX
                        if (nFlag == 0) {
                            if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                                return false;
                            }
                            xlHeapCopy((u8*)pRSP->pDMEM + (nOffset + 0x840), pData, nLength);
                        } else {
                            xlHeapCopy(pData, (u8*)pRSP->pDMEM + (nOffset + 0x840), nLength);
                        }
                        break;
                    case 0x06: // GZM_PMTX
                        if (nFlag == 0) {
                            if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                                return false;
                            }
                            xlHeapCopy((u8*)pRSP->pDMEM + (nOffset + 0x880), pData, nLength);
                        } else {
                            xlHeapCopy(pData, (u8*)pRSP->pDMEM + (nOffset + 0x880), nLength);
                        }
                        break;
                    case 0x02: // GZM_USER1
                    case 0x08: // GZM_MPMTX
                    case 0x0A: // GZM_OTHERMODE
                        break;
                    default:
                        return false;
                }
            } else { // F3DEX2: G_MOVEMEM
                switch (nCommandHi & 0xFF) {
                    case 0x08: { // G_MV_VIEWPORT
                        void* pData;
                        s32 pad;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                            return false;
                        }
                        if (!frameSetViewport(pFrame, pData)) {
                            return false;
                        }
                        break;
                    }
                    case 0x0A: { // G_MV_LIGHT
                        void* pData;
                        s32 iLight = ((s32)(((nCommandHi >> 8) & 0xFF) * 8) - 24) / 24;
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
                            return false;
                        }
                        if (iLight == -1) {
                            if (!frameSetLookAt(pFrame, 0, pData)) {
                                return false;
                            }
                        } else if (iLight == 0) {
                            if (!frameSetLookAt(pFrame, 1, pData)) {
                                return false;
                            }
                        } else {
                            if (!frameSetLight(pFrame, iLight - 1, pData)) {
                                return false;
                            }
                        }
                        break;
                    }
                    case 0x0E: { // G_MV_MATRIX
                        s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                        if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                            return false;
                        }
                        if (!frameSetMatrix(pFrame, matrix, FMT_PROJECTION, true, false, nAddress)) {
                            return false;
                        }
                        break;
                    }
                    case 0x02: // G_MV_MMTX
                    case 0x06: // G_MV_PMTX
                    case 0x0C: // G_MV_POINT
                        break;
                    case 0x00: // G_MVO_LOOKATX
                    case 0x18: // G_MVO_LOOKATY
                    case 0x30: // G_MVO_L0
                    case 0x48: // G_MVO_L1
                    case 0x60: // G_MVO_L2
                    case 0x78: // G_MVO_L3
                    case 0x90: // G_MVO_L4
                    case 0xA8: // G_MVO_L5
                    case 0xC0: // G_MVO_L6
                    case 0xD8: // G_MVO_L7
                        break;
                    default:
                        return false;
                }
            }
            break;
        case 0xDB: // G_MOVEWORD
            switch ((nCommandHi >> 16) & 0xFF) {
                case 0x02: // G_MW_NUMLIGHT
                    if (!frameSetLightCount(pFrame, (nCommandLo & 0xFF) / 24)) {
                        return false;
                    }
                    break;
                case 0x06: // G_MW_SEGMENT
                    pRSP->anBaseSegment[(nCommandHi >> 2) & 0xF] = nCommandLo & 0x0FFFFFFF;
                    break;
                case 0x08: // G_MW_FOG
                    if (pRSP->eTypeUCode == RUT_S2DEX1) {
                        u32 nSid = (nCommandHi >> 8) & 0xFF;

                        if (nSid == 0 || nSid == 4 || nSid == 8 || nSid == 12) {
                            pRSP->aStatus[nSid >> 2] = nCommandLo;
                        }
                    } else {
                        if (!frameSetMode(pFrame, FMT_FOG, nCommandLo)) {
                            return false;
                        }
                    }
                    break;
                case 0x0A: { // G_MW_LIGHTCOL
                    s32 nLight = (nCommandHi & 0xFF) >> 4;

                    nLight -= nLight / 3;
                    pFrame->aLight[nLight].rColorR = (s32)((nCommandLo >> 24) & 0xFF);
                    pFrame->aLight[nLight].rColorG = (s32)((nCommandLo >> 16) & 0xFF);
                    pFrame->aLight[nLight].rColorB = (s32)((nCommandLo >> 8) & 0xFF);
                    break;
                }
                case 0x00: // G_MW_MATRIX
                case 0x04: // G_MW_CLIP
                case 0x0C: // G_MW_FORCEMTX
                case 0x0E: // G_MW_PERSPNORM
                    break;
                default:
                    return false;
            }
            break;
        case 0xDA: {
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_RECTANGLE_R
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjRectangleR(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else if (pRSP->eTypeUCode == RUT_ZSORT) { // ZSORT: G_ZS_SENDSIGNAL
                pRSP->nStatus |= nCommandLo | (nCommandHi & 0xFFFFFF);
                xlObjectEvent(pRSP->pHost, 0x1000, (void*)5);
            } else { // F3DEX2: G_MTX
                s32 nMode = nCommandHi & 0xFF;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspLoadMatrix(pRSP, nAddress, matrix)) {
                    return false;
                }
                if (!frameSetMatrix(pFrame, matrix, nMode & 4 ? FMT_PROJECTION : FMT_MODELVIEW,
                                    nMode & 2 ? true : false, nMode & 1 ? false : true, nAddress)) {
                    return false;
                }
            }
            break;
        }
        case 0xD9:
            if (pRSP->eTypeUCode != RUT_ZSORT) { // ZSORT: G_ZS_WAITSIGNAL
                s32 nSet = nCommandLo & 0xFFFFFF;
                s32 nClr = nCommandHi & 0xFFFFFF;

                rspGeometryMode(pRSP, nSet, nClr);
            }
            break;
        case 0xD8:
            if (pRSP->eTypeUCode == RUT_ZSORT) { // ZSORT: G_ZS_SETSUBDL
                pRSP->nZSortSubDL = SEGMENT_ADDRESS(pRSP, nCommandLo);
            } else { // F3DEX2: G_POPMTX
                s32 iMatrix;
                s32 nCount = (nCommandLo & 0xFFFF) >> 6;

                for (iMatrix = 0; iMatrix < nCount; iMatrix++) {
                    if (!frameGetMatrix(pFrame, NULL, FMT_MODELVIEW, true)) {
                        return false;
                    }
                }
            }
            break;
        case 0xD7:
            if (pRSP->eTypeUCode == RUT_ZSORT) { // ZSORT: G_ZS_LINKSUBDL
                if (pRSP->nZSortSubDL != 0 && pRSP->nStatusSubDL != 1) {
                    if (!rspSetDL(pRSP, pRSP->nZSortSubDL, true)) {
                        return false;
                    }
                    pRSP->nStatusSubDL = 1;
                }
            } else { // F3DEX2: G_TEXTURE
                if (!frameSetMode(pFrame, FMT_TEXTURE1, nCommandLo)) {
                    return false;
                }
                if (!frameSetMode(pFrame, FMT_TEXTURE2, ((nCommandHi & ~3) | ((nCommandHi >> 1) & 1 & 3)) & 0xFFFFFF)) {
                    return false;
                }
            }
            break;
        case 0xD6:
            if (pRSP->eTypeUCode == RUT_ZSORT) { // ZSORT: G_ZS_MULT_MPMTX
                s32 nVertices = (nCommandLo >> 24) + 1;
                s32 nSrcAdrs = ((nCommandLo >> 12) & 0xFFF) - 1024;
                s32 nDestAdrs = (nCommandLo & 0xFFF) - 1024;
                s32 iCount;

                if (pRSP->nNumZSortVertices < 127) {
                    for (iCount = 0; iCount < nVertices; iCount++) {
                        bool bFound;
                        u32 iVtxIndex;
                        s16 vertex[3];
                        s32 pad1[16];
                        zVtxDest destVtx;
                        s32 pad2;

                        vertex[0] = ((s16*)pRSP->pDMEM)[nSrcAdrs / 2 + 0];
                        vertex[1] = ((s16*)pRSP->pDMEM)[nSrcAdrs / 2 + 1];
                        vertex[2] = ((s16*)pRSP->pDMEM)[nSrcAdrs / 2 + 2];

                        bFound = false;
                        for (iVtxIndex = 0; iVtxIndex < pRSP->nNumZSortVertices; iVtxIndex++) {
                            if (vertex[0] == pRSP->aZSortVertex[iVtxIndex].nX &&
                                vertex[1] == pRSP->aZSortVertex[iVtxIndex].nY &&
                                vertex[2] == pRSP->aZSortVertex[iVtxIndex].nZ) {
                                bFound = true;
                                break;
                            }
                        }

                        if (bFound) {
                            destVtx.sx = *((s8*)pRSP->pDMEM + 0x8C0);
                            destVtx.sy = iVtxIndex;
                        } else {
                            pRSP->aZSortVertex[pRSP->nNumZSortVertices].nX = vertex[0];
                            pRSP->aZSortVertex[pRSP->nNumZSortVertices].nY = vertex[1];
                            pRSP->aZSortVertex[pRSP->nNumZSortVertices].nZ = vertex[2];
                            destVtx.sx = *((s8*)pRSP->pDMEM + 0x8C0);
                            destVtx.sy = pRSP->nNumZSortVertices;
                            pRSP->nNumZSortVertices++;
                        }

                        destVtx.cc = 0;
                        destVtx.invw = pRSP->aZSortInvW[pRSP->nTotalZSortVertices];
                        destVtx.wi = pRSP->aZSortWiVal[pRSP->nTotalZSortVertices];
                        pRSP->nTotalZSortVertices++;

                        xlHeapCopy((u8*)pRSP->pDMEM + nDestAdrs, &destVtx, sizeof(zVtxDest));

                        nSrcAdrs += 6;
                        nDestAdrs += 16;
                        if (pRSP->nNumZSortVertices > 127) {
                            break;
                        }
                    }
                }
            }
            break;
        case 0xD5:
            break;
        case 0xD4:
            break;
        case 0xD3:
            if (pRSP->eTypeUCode == RUT_ZSORT && pRSP->nVersionUCode == 3) { // ZSORT: G_ZS_LIGHTING_L
                if (!rspSetGeometryMode1(pRSP, pRSP->nGeometryMode | (nCommandLo & 0xFFFFFF))) {
                    return false;
                }
            }
            break;
        case 0xD2:
            break;
        case 0xD1:
            break;
        case 0xD0:
            break;
        case 0x01:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_RECTANGLE
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjRectangle(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_VTX
                s8* pBuffer;
                s32 nCount = (nCommandHi >> 12) & 0xFF;
                s32 iVertex0 = ((nCommandHi & 0xFF) >> 1) - nCount;
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pBuffer, nAddress, NULL)) {
                    return false;
                }
                if (!frameLoadVertex(pFrame, pBuffer, iVertex0, nCount)) {
                    return false;
                }
            }
            break;
        case 0x02:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_SPRITE
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjSprite(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_MODIFYVTX
                s32 iVertex = (nCommandHi & 0xFFFF) >> 1;
                s32 nVal = (nCommandHi >> 16) & 0xFF;

                switch (nVal) {
                    case 0x10: // G_MWO_POINT_RGBA
                        pFrame->aVertex[iVertex].anColor[0] = (nCommandLo >> 24) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[1] = (nCommandLo >> 16) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[2] = (nCommandLo >> 8) & 0xFF;
                        pFrame->aVertex[iVertex].anColor[3] = nCommandLo & 0xFF;
                        break;
                    case 0x14: // G_MWO_POINT_ST
                        if (pFrame->aMode[6] != 0x1F041F01 && pFrame->aMode[8] != 0x01070707 &&
                            pFrame->aMode[7] != 0x1F001F03 && pFrame->aMode[9] != 0x07050700) {
                            pFrame->aVertex[iVertex].rS = (s32)(nCommandLo >> 16) / 32.0f;
                            pFrame->aVertex[iVertex].rT = (s32)(nCommandLo & 0xFFFF) / 32.0f;
                        }
                        break;
                    case 0x18: // G_MWO_POINT_XYSCREEN
                        break;
                    case 0x1C: // G_MWO_POINT_ZSCREEN
                        break;
                }
            }
            break;
        case 0x03: { // F3DEX2: G_SELECT_DL
            u32 nVertexStart = (nCommandHi & 0xFFFF) >> 1;
            u32 nVertexEnd = (nCommandLo & 0xFFFF) >> 1;

            if (frameCullDL(pFrame, nVertexStart, nVertexEnd)) {
                if (!rspPopDL(pRSP)) {
                    *pbDone = true;
                }
            }
            break;
        }
        case 0x04:
            return false;
        case 0x05:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_LOADTXTR
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjLoadTxtr(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_TRI1
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 3) {
                        primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) >> 1;
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                            primitive.anData[iVertex + 2] >= 80) {
                            return false;
                        }

                        iVertex += 3;
                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        if (((nCommandHi >> 24) & 0xFF) == 0x05) {
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[1](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0x06:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_LDTX_SPRITE
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjLoadTxSprite(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_TRI2
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 6) {
                        primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) >> 1;
                        primitive.anData[iVertex + 3] = ((nCommandLo >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 4] = ((nCommandLo >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 5] = ((nCommandLo >> 0) & 0xFF) >> 1;
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                            primitive.anData[iVertex + 2] >= 80 || primitive.anData[iVertex + 3] >= 80 ||
                            primitive.anData[iVertex + 4] >= 80 || primitive.anData[iVertex + 5] >= 80) {
                            return false;
                        }

                        iVertex += 6;
                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        if (((nCommandHi >> 24) & 0xFF) == 0x06) {
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[1](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0x07:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_LDTX_RECT
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjLoadTxRect(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_QUAD
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 6) {
                        primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = ((nCommandHi >> 0) & 0xFF) >> 1;
                        primitive.anData[iVertex + 3] = ((nCommandLo >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 4] = ((nCommandLo >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 5] = ((nCommandLo >> 0) & 0xFF) >> 1;
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80 ||
                            primitive.anData[iVertex + 2] >= 80 || primitive.anData[iVertex + 3] >= 80 ||
                            primitive.anData[iVertex + 4] >= 80 || primitive.anData[iVertex + 5] >= 80) {
                            return false;
                        }

                        iVertex += 6;
                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        if (((nCommandHi >> 24) & 0xFF) == 0x07) {
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[1](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0x08:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_LDTX_RECT_R
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (!rspObjLoadTxRectR(pRSP, pFrame, nAddress)) {
                    return false;
                }
            } else { // F3DEX2: G_LINE3d
                bDone = false;
                while (!bDone) {
                    iVertex = 0;
                    while (!bDone && iVertex < ARRAY_COUNT(primitive.anData) - 3) {
                        primitive.anData[iVertex + 0] = ((nCommandHi >> 16) & 0xFF) >> 1;
                        primitive.anData[iVertex + 1] = ((nCommandHi >> 8) & 0xFF) >> 1;
                        primitive.anData[iVertex + 2] = (nCommandHi & 0xFF) + 3;
                        if (primitive.anData[iVertex + 0] >= 80 || primitive.anData[iVertex + 1] >= 80) {
                            return false;
                        }

                        iVertex += 3;
                        nCommandHi = GBI_COMMAND_HI(pnGBI);
                        nCommandLo = GBI_COMMAND_LO(pnGBI);
                        if (((nCommandHi >> 24) & 0xFF) == 0x08) {
                            *ppnGBI = ++pnGBI;
                        } else {
                            bDone = true;
                        }
                    }

                    primitive.nCount = iVertex;
                    if (!pFrame->aDraw[0](pFrame, &primitive)) {
                        return false;
                    }
                }
            }
            break;
        case 0x09: {
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_BG_1CYC
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);
                uObjBg bg;

                rspFillObjBgScale(pRSP, nAddress, &bg);
                if (gpSystem->eTypeROM != SRT_ZELDA2) {
                    guS2DEmuSetScissor(0, 0, N64_FRAME_WIDTH << 2, N64_FRAME_HEIGHT << 2, 0);
                    if (!guS2DEmuBgRect1Cyc(pRSP, pFrame, &bg)) {
                        return false;
                    }
                } else if (gpSystem->eTypeROM == SRT_ZELDA2 &&
                           (bg.b.imagePtr == 0x07000000 || bg.b.imagePtr == 0x07012C00)) {
                    guS2DEmuSetScissor(0, 0, N64_FRAME_WIDTH << 2, N64_FRAME_HEIGHT << 2, 0);
                    if (!guS2DEmuBgRect1Cyc(pRSP, pFrame, &bg)) {
                        return false;
                    }
                } else {
                    uObjBg bg;

                    rspFillObjBgScale(pRSP, nAddress, &bg);
                    if (pFrame->bInBomberNotes) {
                        pFrame->bCameFromBomberNotes = true;
                    }
                    if (pFrame->bBlurOn) {
                        if (pFrame->aColor[4].a != 0xFF) {
                            pFrame->cBlurAlpha = pFrame->aColor[4].a;
                        }
                    } else {
                        if ((pFrame->bPauseThisFrame || pFrame->nLastFrameZSets == 0) && !pFrame->bUsingLens) {
                            u8 cTempAlpha = pFrame->cBlurAlpha;

                            pFrame->cBlurAlpha = 220;
                            ZeldaDrawFrame(pFrame, COPY_BUFFER);
                            pFrame->cBlurAlpha = cTempAlpha;
                            pFrame->bPauseBGDrawn = true;
                        }
                    }
                }
            } else {
                return false;
            }
            break;
        }
        case 0x0A: {
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_BG_COPY
                s32 nAddress = SEGMENT_ADDRESS(pRSP, nCommandLo);

                if (gpSystem->eTypeROM != SRT_ZELDA2) {
                    if (!rspBgRectCopy(pRSP, pFrame, nAddress)) {
                        return false;
                    }
                } else {
                    if (pFrame->bInBomberNotes) {
                        pFrame->bCameFromBomberNotes = true;
                    }
                    if (pFrame->bBlurOn) {
                        if (pFrame->aColor[4].a != 0xFF) {
                            pFrame->cBlurAlpha = pFrame->aColor[4].a;
                        }
                    } else {
                        if ((pFrame->bPauseThisFrame || pFrame->nLastFrameZSets == 0) && !pFrame->bUsingLens) {
                            u8 cTempAlpha = pFrame->cBlurAlpha;

                            pFrame->cBlurAlpha = 220;
                            ZeldaDrawFrame(pFrame, COPY_BUFFER);
                            pFrame->cBlurAlpha = cTempAlpha;
                            pFrame->bPauseBGDrawn = true;
                        }

                        if (pFrame->bUsingLens) {
                            GXSetColorUpdate(GX_FALSE);
                            GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
                            GXSetColorUpdate(GX_TRUE);
                        }
                    }
                }
            } else {
                return false;
            }
            break;
        }
        case 0x0B:
            if (pRSP->eTypeUCode == RUT_S2DEX2) { // S2DEX2: G_OBJ_RENDERMODE
                pRSP->nMode2D = nCommandLo & 0xFFFF;
            } else {
                return false;
            }
            break;
        case 0xE4: // S2DEX2: G_RDPHALF_0
            if (pRSP->eTypeUCode == RUT_S2DEX2 && ((*pnGBI >> 56) & 0xFF) == 0x04) { // G_SELECT_DL
                bool bPush;
                u8 nSid2D;
                u32 nDLAdrs;
                u32 nFlag2D;

                nSid2D = ((nCommandHi >> 16) & 0xFF) >> 2;
                nDLAdrs = nCommandHi & 0xFFFF;
                nFlag2D = nCommandLo;

                nCommandHi = GBI_COMMAND_HI(pnGBI);
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                *ppnGBI = ++pnGBI;

                bPush = (nCommandHi >> 16) & 0xFF;
                nDLAdrs |= (nCommandHi & 0xFFFF) << 16;
                if (nFlag2D != (pRSP->aStatus[nSid2D] & nCommandLo)) {
                    pRSP->aStatus[nSid2D] = (pRSP->aStatus[nSid2D] & ~nCommandLo) | (nFlag2D & nCommandLo);
                    if (!rspSetDL(pRSP, nDLAdrs, bPush ? false : true)) {
                        return false;
                    }
                }
            } else {
                return false;
            }
            break;
        default:
            return false;
    }

    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}
