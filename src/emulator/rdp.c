#include "emulator/rdp.h"
#include "dolphin.h"
#include "emulator/frame.h"
#include "emulator/ram.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "macros.h"

_XL_OBJECTTYPE gClassRDP = {
    "RDP",
    sizeof(Rdp),
    NULL,
    (EventFunc)rdpEvent,
};

bool rdpParseGBI(Rdp* pRDP, u64** ppnGBI, RspUCodeType eTypeUCode) {
    u32 nA;
    u32 nB;
    u32 nC;
    u32 nD;
    u64* pnGBI;
    u32 nCommandLo;
    u32 nCommandHi;
    Frame* pFrame;

    pnGBI = *ppnGBI;
    pFrame = SYSTEM_FRAME(pRDP->pHost);
    nCommandHi = GBI_COMMAND_HI(pnGBI);
    nCommandLo = GBI_COMMAND_LO(pnGBI);

    *ppnGBI = ++pnGBI;
    pFrame->pnGBI = pnGBI;

    switch (nCommandHi >> 24) {
        case 0xC0: // G_NOOP
            break;
        case 0xFF: { // G_SETCIMG
            bool nFound = false;
            s32 i;
            u32 nAddress;
            bool nSetLens = false;
            FrameBuffer* pBuffer = &pFrame->aBuffer[FBT_COLOR_DRAW];

            pBuffer->nFormat = (nCommandHi >> 21) & 7;
            pBuffer->nSize = (nCommandHi >> 19) & 3;
            pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;

            nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
            pBuffer->nAddress = nAddress;

            if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                return false;
            }
            if (!frameSetBuffer(pFrame, FBT_COLOR_DRAW)) {
                return false;
            }

            for (i = 0; i < pFrame->nNumCIMGAddresses && i < 8; i++) {
                if (nAddress == pFrame->anCIMGAddresses[i]) {
                    nFound = true;
                    break;
                }
            }
            if (!nFound) {
                pFrame->anCIMGAddresses[i] = nAddress;
                pFrame->nNumCIMGAddresses++;
            }
            switch (gpSystem->eTypeROM) {
                case SRT_ZELDA1:
                    if (!frameHackCIMG_Zelda(pFrame, pBuffer, pnGBI, nCommandLo, nCommandHi)) {
                        return false;
                    }
                    break;
                case SRT_ZELDA2: {
                    static s32 nCount;
                    static s32 nBlurCount;
                    static s32 nNoteCount;
                    static s32 nZCount;
                    static s32 nZBufferCount;

                    if (nAddress == 0x0042EEC0 || nAddress == 0x003A9480 || nAddress == 0x003A92C0) {
                        nBlurCount = nCount;
                    }
                    if (nAddress == 0x00780000) {
                        nNoteCount = nCount;
                    }
                    if (!(nAddress == 0x004096C0 || nAddress == 0x00383C80 || nAddress == 0x00383AC0) &&
                        pFrame->bCameFromBomberNotes) {
                        nZCount += 1;
                    } else {
                        nZCount = 0;
                        pFrame->bCameFromBomberNotes = false;
                    }
                    if (nAddress == 0x004096C0 || nAddress == 0x00383C80 || nAddress == 0x00383AC0) {
                        nZBufferCount = nCount;
                        pFrame->nZBufferSets++;
                    }
                    if (nAddress == 0x00784600) {
                        static u32 sCommandCodes[] = {
                            0xED000000,
                            0x005003C0,
                            0xDE010000,
                        };
                        s32 i;
                        u32* pGBI = (u32*)pnGBI;

                        for (i = 0; i < ARRAY_COUNT(sCommandCodes); i++) {
                            if (pGBI[i] != sCommandCodes[i]) {
                                break;
                            }
                        }

                        if (i == 3) {
                            pFrame->bUsingLens = true;
                            nSetLens = true;
                        }
                        if (pGBI[0] == 0xFD900000) {
                            nSetLens = true;
                        }
                    }
                    if (nZCount > 11) {
                        pFrame->bPauseThisFrame = true;
                    }
                    if (nCount - nNoteCount < 11) {
                        pFrame->bInBomberNotes = true;
                    } else {
                        pFrame->bInBomberNotes = false;
                    }
                    if (nCount - nBlurCount < 11) {
                        pFrame->bBlurOn = true;
                    } else {
                        pFrame->bBlurOn = false;
                    }
                    nCount += 1;
                    if (!frameHackCIMG_Zelda2(pFrame, pBuffer, pnGBI, nCommandLo, nCommandHi)) {
                        return false;
                    }
                    frameHackCIMG_Zelda2_Shrink(pRDP, pFrame, ppnGBI);
                    if (nSetLens == 0) {
                        frameHackCIMG_Zelda2_Camera(pFrame, pBuffer, 0, 0);
                    }
                    break;
                }
                case SRT_PANEL:
                    if (nAddress == 0x0023E800 || nAddress == 0x00245D00 || nAddress == 0x00358800) {
                        frameHackCIMG_Panel(pRDP, pFrame, pBuffer, ppnGBI);
                    }
                    /* fallthrough */
                case SRT_DRMARIO:
                    if (!(nAddress == 0x003B5000 || nAddress == 0x003DA800)) {
                        pFrame->bGrabbedFrame = true;
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        case 0xFE: { // G_SETZIMG
            s32 nAddress;
            FrameBuffer* pBuffer = &pFrame->aBuffer[FBT_DEPTH];

            pBuffer->nFormat = (nCommandHi >> 21) & 7;
            pBuffer->nSize = (nCommandHi >> 19) & 3;
            pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;

            nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
            pBuffer->nAddress = nAddress;

            if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                return false;
            }
            if (!frameSetBuffer(pFrame, FBT_DEPTH)) {
                return false;
            }
            break;
        }
        case 0xFD: { // G_SETTIMG
            s32 nAddress;
            FrameBuffer* pBuffer = &pFrame->aBuffer[FBT_IMAGE];

            switch (gpSystem->eTypeROM) {
                case SRT_ZELDA1:
                    if (!frameHackTIMG_Zelda(pFrame, &pnGBI, &nCommandLo, &nCommandHi)) {
                        return false;
                    }
                    break;
                case SRT_ZELDA2:
                    if (!frameHackTIMG_Zelda(pFrame, &pnGBI, &nCommandLo, &nCommandHi)) {
                        return false;
                    }
                    break;
                default:
                    break;
            }
            pBuffer->nFormat = (nCommandHi >> 21) & 7;
            pBuffer->nSize = (nCommandHi >> 19) & 3;
            pBuffer->nWidth = (nCommandHi & 0xFFF) + 1;
            pBuffer->nAddress = nCommandLo;

            nAddress = SEGMENT_ADDRESS(SYSTEM_RSP(pRDP->pHost), nCommandLo);
            if (!ramGetBuffer(SYSTEM_RAM(pRDP->pHost), &pBuffer->pData, nAddress, NULL)) {
                return false;
            }
            if (!frameSetBuffer(pFrame, FBT_IMAGE)) {
                return false;
            }
            switch (gpSystem->eTypeROM) {
                case SRT_PANEL:
                    frameHackTIMG_Panel(pFrame, pBuffer);
                    break;
                default:
                    break;
            }
            break;
        }
        case 0xFC: // G_SETCOMBINE
            if ((nA = (nCommandHi >> 20) & 0xF) == 0xF) {
                nA = 0x1F;
            }
            if ((nB = (nCommandLo >> 28) & 0xF) == 0xF) {
                nB = 0x1F;
            }
            if ((nC = (nCommandHi >> 15) & 0x1F) == 0x1F) {
                nC = 0x1F;
            }
            if ((nD = (nCommandLo >> 15) & 7) == 7) {
                nD = 0x1F;
            }
            if (!frameSetMode(pFrame, FMT_COMBINE_COLOR1, nA | (nB << 8) | (nC << 16) | (nD << 24))) {
                return false;
            }

            if ((nA = (nCommandHi >> 12) & 7) == 7) {
                nA = 7;
            }
            if ((nB = (nCommandLo >> 12) & 7) == 7) {
                nB = 7;
            }
            if ((nC = (nCommandHi >> 9) & 7) == 7) {
                nC = 7;
            }
            if ((nD = (nCommandLo >> 9) & 7) == 7) {
                nD = 7;
            }
            if (!frameSetMode(pFrame, FMT_COMBINE_ALPHA1, nA | (nB << 8) | (nC << 16) | (nD << 24))) {
                return false;
            }

            if ((nA = (nCommandHi >> 5) & 0xF) == 0xF) {
                nA = 0x1F;
            }
            if ((nB = (nCommandLo >> 24) & 0xF) == 0xF) {
                nB = 0x1F;
            }
            if ((nC = (nCommandHi >> 0) & 0x1F) == 0x1F) {
                nC = 0x1F;
            }
            if ((nD = (nCommandLo >> 6) & 7) == 7) {
                nD = 0x1F;
            }
            if (!frameSetMode(pFrame, FMT_COMBINE_COLOR2, nA | (nB << 8) | (nC << 16) | (nD << 24))) {
                return false;
            }

            if ((nA = (nCommandLo >> 21) & 7) == 7) {
                nA = 7;
            }
            if ((nB = (nCommandLo >> 3) & 7) == 7) {
                nB = 7;
            }
            if ((nC = (nCommandLo >> 18) & 7) == 7) {
                nC = 7;
            }
            if ((nD = (nCommandLo >> 0) & 7) == 7) {
                nD = 7;
            }
            if (!frameSetMode(pFrame, FMT_COMBINE_ALPHA2, nA | (nB << 8) | (nC << 16) | (nD << 24))) {
                return false;
            }
            break;
        case 0xFB: // G_SETENVCOLOR
            if (!frameSetColor(pFrame, FCT_ENVIRONMENT, nCommandLo)) {
                return false;
            }
            break;
        case 0xFA: // G_SETPRIMCOLOR
            pFrame->primLODfrac = nCommandHi & 0xFF;
            pFrame->primLODmin = (nCommandHi >> 8) & 0xFF;
            if (!frameSetColor(pFrame, FCT_PRIMITIVE, nCommandLo)) {
                return false;
            }
            break;
        case 0xF9: // G_SETBLENDCOLOR
            if (!frameSetColor(pFrame, FCT_BLEND, nCommandLo)) {
                return false;
            }
            break;
        case 0xF8: // G_SETFOGCOLOR
            if (!frameSetColor(pFrame, FCT_FOG, nCommandLo)) {
                return false;
            }
            break;
        case 0xF7: { // G_SETFILLCOLOR
            u32 nColor = ((nCommandLo >> 11) & 0x1F) << 27 | ((nCommandLo >> 6) & 0x1F) << 19 |
                         ((nCommandLo >> 1) & 0x1F) << 11 | ((nCommandLo & 1) << 7);

            if (!frameSetColor(pFrame, FCT_FILL, nColor)) {
                return false;
            }
            break;
        }
        case 0xF6: { // G_FILLRECT
            Rectangle primitive;

            primitive.nX1 = (nCommandHi >> 14) & 0x3FF;
            primitive.nY1 = (nCommandHi >> 2) & 0x3FF;
            primitive.nX0 = (nCommandLo >> 14) & 0x3FF;
            primitive.nY0 = (nCommandLo >> 2) & 0x3FF;
            if (gpSystem->eTypeROM == SRT_ZELDA2) {
                if (primitive.nY1 == N64_FRAME_HEIGHT - 1 && primitive.nY0 > 0) {
                    primitive.nY0 -= 1;
                }
                frameHackCIMG_Zelda2_Camera(pFrame, NULL, nCommandHi, nCommandLo);
            }
            if (!pFrame->aDraw[2](pFrame, &primitive)) {
                return false;
            }
            break;
        }
        case 0xF5: { // G_SETTILE
            s32 iTile = (nCommandLo >> 24) & 7;
            Tile* pTile = &pFrame->aTile[iTile];

            pTile->nSize = (nCommandHi >> 19) & 3;
            pTile->nTMEM = nCommandHi & 0x1FF;
            pTile->iTLUT = (nCommandLo >> 20) & 0xF;
            pTile->nSizeX = (nCommandHi >> 9) & 0x1FF;
            pTile->nFormat = (nCommandHi >> 21) & 7;
            pTile->nMaskS = (nCommandLo >> 4) & 0xF;
            pTile->nMaskT = (nCommandLo >> 14) & 0xF;
            pTile->nModeS = (nCommandLo >> 8) & 3;
            pTile->nModeT = (nCommandLo >> 18) & 3;
            pTile->nShiftS = (nCommandLo >> 0) & 0xF;
            pTile->nShiftT = (nCommandLo >> 10) & 0xF;
            pTile->nCodePixel = pFrame->nCodePixel;

            pFrame->lastTile = iTile;
            if (!frameDrawReset(pFrame, 1)) {
                return false;
            }
            break;
        }
        case 0xF4: { // G_LOADTILE
            s32 iTile = (nCommandLo >> 24) & 7;

            pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
            pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
            pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
            pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;

            pFrame->n2dLoadTexType = G_OBJLT_TXTRTILE;
            pFrame->nLastX0 = pFrame->aTile[iTile].nX0;
            pFrame->nLastY0 = pFrame->aTile[iTile].nY0;
            pFrame->nLastX1 = pFrame->aTile[iTile].nX1;
            pFrame->nLastY1 = pFrame->aTile[iTile].nY1;
            if (!frameLoadTMEM(pFrame, FLT_TILE, iTile)) {
                return false;
            }
            pFrame->aTile[pFrame->lastTile].nCodePixel = pFrame->nCodePixel;
            break;
        }
        case 0xF3: { // G_LOADBLOCK
            s32 iTile = (nCommandLo >> 24) & 7;

            pFrame->aTile[iTile].nX0 = (nCommandHi >> 12) & 0xFFF;
            pFrame->aTile[iTile].nY0 = nCommandHi & 0xFFF;
            pFrame->aTile[iTile].nX1 = (nCommandLo >> 12) & 0xFFF;
            pFrame->aTile[iTile].nY1 = nCommandLo & 0xFFF;
            pFrame->n2dLoadTexType = G_OBJLT_TXTRBLOCK;
            if (!frameLoadTMEM(pFrame, FLT_BLOCK, iTile)) {
                return false;
            }
            break;
        }
        case 0xF2: { // G_SETTILESIZE
            s32 iTile = (nCommandLo >> 24) & 7;
            Tile* pTile = &pFrame->aTile[iTile];

            pTile->nX0 = (nCommandHi >> 12) & 0xFFF;
            pTile->nY0 = nCommandHi & 0xFFF;
            pTile->nX1 = (nCommandLo >> 12) & 0xFFF;
            pTile->nY1 = nCommandLo & 0xFFF;
            if (!frameDrawReset(pFrame, 1)) {
                return false;
            }
            break;
        }
        case 0xF0: { // G_LOADTLUT
            s32 iTile = (nCommandLo >> 24) & 7;
            s32 nCount = (nCommandLo >> 14) & 0x3FF;

            if (!frameLoadTLUT(pFrame, nCount, iTile)) {
                return false;
            }
            break;
        }
        case 0xEF: // G_RDPSETOTHERMODE
            if (!frameSetMode(pFrame, FMT_OTHER0, nCommandLo)) {
                return false;
            }
            if (!frameSetMode(pFrame, FMT_OTHER1, nCommandHi)) {
                return false;
            }
            break;
        case 0xEE: { // G_SETPRIMDEPTH
            f32 rDepth = ((nCommandLo >> 16) & 0x7FFF) / 32768.0f;
            f32 rDelta = (nCommandLo & 0xFFFF) / 65536.0f;

            if (!frameSetDepth(pFrame, rDepth, rDelta)) {
                return false;
            }
            break;
        }
        case 0xED: { // G_SETSCISSOR
            Rectangle rectangle;
            s32 pad;

            rectangle.nX0 = (nCommandHi >> 12) & 0xFFF;
            rectangle.nY0 = nCommandHi & 0xFFF;
            rectangle.nX1 = (nCommandLo >> 12) & 0xFFF;
            rectangle.nY1 = nCommandLo & 0xFFF;
            if (!frameSetScissor(pFrame, &rectangle)) {
                return false;
            }
            break;
        }
        case 0xEC: // G_SETCONVERT
        case 0xEB: // G_SETKEYR
        case 0xEA: // G_SETKEYGB
        case 0xE9: // G_RDPFULLSYNC
        case 0xE8: // G_RDPTILESYNC
        case 0xE7: // G_RDPPIPESYNC
        case 0xE6: // G_RDPLOADSYNC
            break;
        case 0xE5: // G_TEXRECTFLIP
        case 0xE4: // G_TEXRECT
        {
            Rectangle primitive;
            f32 rX0;
            f32 rY0;
            f32 rX1;
            f32 rY1;
            u32* pGBI;

            primitive.nX0 = (nCommandLo >> 12) & 0xFFF;
            primitive.nY0 = nCommandLo & 0xFFF;
            primitive.nX1 = (nCommandHi >> 12) & 0xFFF;
            primitive.nY1 = nCommandHi & 0xFFF;

            rX0 = (primitive.nX0 + 3) >> 2;
            rX1 = (primitive.nX1 + 3) >> 2;
            rY0 = (primitive.nY0 + 3) >> 2;
            rY1 = (primitive.nY1 + 3) >> 2;

            primitive.iTile = (nCommandLo >> 24) & 7;
            primitive.bFlip = nCommandHi >> 24 == 0xE5 ? true : false;

            if (gpSystem->eTypeROM == SRT_ZELDA2 && (pFrame->bSnapShot & 0xF) != 0 && (s32)nCommandHi == 0xE43C023C &&
                nCommandLo == 0x0014021C) {
                pFrame->bSnapShot |= 0x100;
            }

            nCommandHi = GBI_COMMAND_HI(pnGBI);
            nCommandLo = GBI_COMMAND_LO(pnGBI);
            *ppnGBI = ++pnGBI;

            // TODO: translate commands to enum
            if (nCommandHi >> 24 == 0xB4 || nCommandHi >> 24 == 0xE1 || nCommandHi >> 24 == 0xB3) {
                primitive.rS = (s16)(nCommandLo >> 16) / 32.0f;
                primitive.rT = (s16)(nCommandLo & 0xFFFF) / 32.0f;

                nCommandHi = GBI_COMMAND_HI(pnGBI);
                nCommandLo = GBI_COMMAND_LO(pnGBI);
                *ppnGBI = ++pnGBI;

                primitive.rDeltaS = (s16)(nCommandLo >> 16) / 1024.0f;
                primitive.rDeltaT = (s16)(nCommandLo & 0xFFFF) / 1024.0f;

                rX0 = (primitive.nX0 + 3) >> 2;
                rX1 = (primitive.nX1 + 3) >> 2;
                rY0 = (primitive.nY0 + 3) >> 2;
                rY1 = (primitive.nY1 + 3) >> 2;
            } else {
                primitive.rS = (s16)(nCommandHi >> 16) / 32.0f;
                primitive.rT = (s16)(nCommandHi & 0xFFFF) / 32.0f;
                primitive.rDeltaS = (s16)(nCommandLo >> 16) / 1024.0f;
                primitive.rDeltaT = (s16)(nCommandLo & 0xFFFF) / 1024.0f;
            }
            if (pFrame->iTileDrawn != primitive.iTile) {
                frameDrawReset(pFrame, 1);
            }
            pFrame->iTileDrawn = primitive.iTile;
            if (gpSystem->eTypeROM == SRT_ZELDA2 && rX0 == 0.0f && rX1 == N64_FRAME_WIDTH && rY0 == 0.0f &&
                rY1 == N64_FRAME_HEIGHT && pFrame->bUsingLens) {
                u32* pGBI = (u32*)pnGBI;

                if (pGBI[4] == 0xF8000000) {
                    GXSetCopyFilter(GX_FALSE, NULL, GX_FALSE, NULL);
                    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
                    GXSetColorUpdate(GX_FALSE);
                    pFrame->bModifyZBuffer = true;
                }
                if (pGBI[4] == 0xF9000000) {
                    GXSetColorUpdate(GX_FALSE);
                    if (pFrame->aMode[FMT_COMBINE_COLOR1] == 0x1F031F01 &&
                        pFrame->aMode[FMT_COMBINE_ALPHA1] == 0x07030701 &&
                        pFrame->aMode[FMT_COMBINE_COLOR2] == 0x1F031F01 &&
                        pFrame->aMode[FMT_COMBINE_ALPHA2] == 0x7030701) {
                        pFrame->aMode[FMT_COMBINE_COLOR1] = 0x1F030106;
                        pFrame->aMode[FMT_COMBINE_ALPHA1] = 0x07030106;
                        pFrame->aMode[FMT_COMBINE_COLOR2] = 0x1F030106;
                        pFrame->aMode[FMT_COMBINE_ALPHA2] = 0x07030106;
                    } else if (pFrame->aMode[FMT_COMBINE_COLOR1] == 0x1F030106 &&
                               pFrame->aMode[FMT_COMBINE_ALPHA1] == 0x07030106 &&
                               pFrame->aMode[FMT_COMBINE_COLOR2] == 0x1F030106 &&
                               pFrame->aMode[FMT_COMBINE_ALPHA2] == 0x07030106) {
                        pFrame->aMode[FMT_COMBINE_COLOR1] = 0x1F031F01;
                        pFrame->aMode[FMT_COMBINE_ALPHA1] = 0x07030701;
                        pFrame->aMode[FMT_COMBINE_COLOR2] = 0x1F031F01;
                        pFrame->aMode[FMT_COMBINE_ALPHA2] = 0x07030701;
                    }
                    if (!frameSetColor(pFrame, FCT_PRIMITIVE, 0x000000FF)) {
                        return false;
                    }
                    if (!frameSetColor(pFrame, FCT_BLEND, 0x00000008)) {
                        return false;
                    }
                    pFrame->primLODfrac = 0;
                    pFrame->primLODmin = 0;
                    pFrame->aMode[FMT_OTHER0] = 0xAF504365;
                    pFrame->aMode[FMT_OTHER1] = 0xEF002C30;
                    pFrame->aMode[FMT_FOG] = 0;
                    pFrame->aMode[FMT_GEOMETRY] = 0;
                    pFrame->aMode[FMT_TEXTURE1] = 0;
                    pFrame->aMode[FMT_TEXTURE2] = 0;
                    pFrame->bOverrideDepth = true;
                    pFrame->bModifyZBuffer = true;
                    pFrame->nMode = 0x0C1203F0;
                }
            }

            if (!pFrame->aDraw[3](pFrame, &primitive)) {
                return false;
            }

            pGBI = (u32*)pnGBI;
            if (gpSystem->eTypeROM == SRT_ZELDA2 && rX0 == 0.0f && rX1 == N64_FRAME_WIDTH && rY0 == 0.0f &&
                rY1 == N64_FRAME_HEIGHT && pFrame->bUsingLens) {

                if (pGBI[4] == 0xF8000000) {
                    pFrame->bOverrideDepth = false;
                } else if (pGBI[4] == 0xF9000000) {
                    pFrame->bOverrideDepth = false;
                }
            }
            GXSetColorUpdate(GX_TRUE);
            break;
        }
        case 0xC8: // G_TRI_FILL
        case 0xCC: // G_TRI_SHADE
        case 0xCA: // G_TRI_TXTR
        case 0xCE: // G_TRI_SHADE_TXTR
        case 0xC9: // G_TRI_FILL_ZBUFF
        case 0xCD: // G_TRI_SHADE_ZBUFF
        case 0xCB: // G_TRI_TXTR_ZBUFF
        case 0xCF: // G_TRI_SHADE_TXTR_ZBUFF
            break;
        default:
            return false;
    }

    return true;
}

static bool rdpPut8(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpPut16(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpPut32(Rdp* pRDP, u32 nAddress, s32* pData) {
    s32 nData;

    switch (nAddress & 0x1F) {
        case 0x00:
            pRDP->nAddress0 = *pData & 0xFFFFFF;
            break;
        case 0x04:
            pRDP->nAddress1 = *pData & 0xFFFFFF;
            xlObjectEvent(pRDP->pHost, 0x1000, (void*)10);
            break;
        case 0x08:
            break;
        case 0x0C:
            nData = *pData & 0x3FF;
            if (nData & 1) {
                pRDP->nStatus &= ~1;
            }
            if (nData & 0x10) {
                pRDP->nStatus &= ~0x4;
            }
            if (nData & 0x20) {
                pRDP->nStatus |= 4;
            }
            if (nData & 0x40) {
                pRDP->nClockTMEM = 0;
            }
            if (nData & 0x80) {
                pRDP->nClockPipe = 0;
            }
            if (nData & 0x100) {
                pRDP->nClockCmd = 0;
            }
            if (nData & 0x200) {
                pRDP->nClock = 0;
            }
            break;
        case 0x10:
        case 0x14:
        case 0x18:
        case 0x1C:
            break;
        default:
            return false;
    }

    return true;
}

static bool rdpPut64(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGet8(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGet16(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGet32(Rdp* pRDP, u32 nAddress, s32* pData) {
    switch (nAddress & 0x1F) {
        case 0x00:
            *pData = pRDP->nAddress0;
            break;
        case 0x04:
            *pData = pRDP->nAddress1;
            break;
        case 0x08:
            *pData = pRDP->nAddress1;
            break;
        case 0x0C:
            *pData = pRDP->nStatus;
            break;
        case 0x10:
            *pData = pRDP->nClock & 0xFFFFFF;
            break;
        case 0x14:
            *pData = pRDP->nClockCmd & 0xFFFFFF;
            break;
        case 0x18:
            *pData = pRDP->nClockPipe & 0xFFFFFF;
            break;
        case 0x1C:
            *pData = pRDP->nClockTMEM & 0xFFFFFF;
            break;
        default:
            return false;
    }

    return true;
}

static bool rdpGet64(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpPutSpan8(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpPutSpan16(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpPutSpan32(Rdp* pRDP, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x00:
            pRDP->nBIST = *pData & 0x7FF;
            break;
        case 0x04:
            pRDP->nModeTest = *pData & 1;
            break;
        case 0x08:
            pRDP->nAddressTest = *pData & 0x7F;
            break;
        case 0x0C:
            pRDP->nDataTest = *pData;
            break;
        default:
            break;
    }

    return true;
}

static bool rdpPutSpan64(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGetSpan8(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGetSpan16(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

static bool rdpGetSpan32(Rdp* pRDP, u32 nAddress, s32* pData) {
    switch (nAddress & 0xF) {
        case 0x00:
            *pData = pRDP->nBIST & 0x7FF;
            break;
        case 0x04:
            *pData = pRDP->nModeTest & 1;
            break;
        case 0x08:
            *pData = pRDP->nAddressTest & 0x7F;
            break;
        case 0x0C:
            *pData = pRDP->nDataTest;
            break;
        default:
            return false;
    }

    return true;
}

static bool rdpGetSpan64(Rdp* pRDP, u32 nAddress, s32* pData) { return false; }

bool rdpEvent(Rdp* pRDP, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pRDP->pHost = pArgument;
            pRDP->nStatus = 0;
            break;
        case 0x1002:
            switch (((CpuDevice*)pArgument)->nType) {
                case 0:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pRDP->pHost), (CpuDevice*)pArgument, (Put8Func)rdpPut8,
                                         (Put16Func)rdpPut16, (Put32Func)rdpPut32, (Put64Func)rdpPut64)) {
                        return false;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pRDP->pHost), (CpuDevice*)pArgument, (Get8Func)rdpGet8,
                                         (Get16Func)rdpGet16, (Get32Func)rdpGet32, (Get64Func)rdpGet64)) {
                        return false;
                    }
                    break;
                case 1:
                    if (!cpuSetDevicePut(SYSTEM_CPU(pRDP->pHost), (CpuDevice*)pArgument, (Put8Func)rdpPutSpan8,
                                         (Put16Func)rdpPutSpan16, (Put32Func)rdpPutSpan32, (Put64Func)rdpPutSpan64)) {
                        return false;
                    }
                    if (!cpuSetDeviceGet(SYSTEM_CPU(pRDP->pHost), (CpuDevice*)pArgument, (Get8Func)rdpGetSpan8,
                                         (Get16Func)rdpGetSpan16, (Get32Func)rdpGetSpan32, (Get64Func)rdpGetSpan64)) {
                        return false;
                    }
                    break;
            }
            break;
        case 0:
        case 1:
        case 3:
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
