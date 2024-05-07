#include "emulator/simGCN.h"
#include "dolphin.h"
#include "emulator/THPPlayer.h"
#include "emulator/THPRead.h"
#include "emulator/codeGCN.h"
#include "emulator/frame.h"
#include "emulator/mcardGCN.h"
#include "emulator/movie.h"
#include "emulator/pif.h"
#include "emulator/rom.h"
#include "emulator/soundGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "string.h"

u8 gcoverOpen[0x28C1] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000D8880, 0x28C1)
};

u8 gnoDisk[0x1F01] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DB160, 0x1F01)
};

u8 gretryErr[0x2441] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DD080, 0x2441)
};

u8 gfatalErr[0x32E1] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000DF4E0, 0x32E1)
};

u8 gwrongDisk[0x1F01] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E27E0, 0x1F01)
};

u8 greadingDisk[0x0C41] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E4700, 0x0C41)
};

u8 gbar[0x0741] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E5360, 0x0741)
};

u8 gyes[0x05C1] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E5AC0, 0x05C1)
};

u8 gno[0x05C1] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E60A0, 0x05C1)
};

u8 gmesgOK[0x0341] ALIGNAS(32) = {
#pragma INCBIN("SIM_original.elf", 0x000E6680, 0x0341)
};

s16 Vert_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertTitle_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertYes_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 VertNo_s16[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

s16 Vert_s16Bar[12] ALIGNAS(32) = {
    0x0000, 0x0000, 0xFFFF, 0x00C8, 0x0000, 0xFFFF, 0x00C8, 0x00C8, 0xFFFF, 0x0000, 0x00C8, 0xFFFF,
};

u32 Colors_u32[3] ALIGNAS(32) = {
    0x000000FF,
    0x000000FF,
    0x000000FF,
};

u8 TexCoords_u8[] ALIGNAS(32) = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01,
};

char D_800E9A28[] = "Play Delay";
char D_800E9A34[] = "Silence Count";
char D_800E9A44[] = "Fade Up Count";
char D_800E9A54[] = "How many audio frames the\ngame must be playing before it\nconsiders the sound stable";
char D_800E9AA8[] = "How many audio frames the\ngame must NOT play before it\nconsiders itself unstable";
char D_800E9AFC[] = "How many audio frames to\nperform a fade up on the audio";

static f32 gOrthoMtx[4][4] ALIGNAS(32);
static u32 gContMap[4][GCN_BTN_COUNT];
static char* gaszArgument[8];

u32 gmsg_ld01Size = 0x00003E20;
u32 gmsg_ld02Size = 0x00003E20;
u32 gmsg_ld03Size = 0x00003E20;
u32 gmsg_ld04Size = 0x00003E20;
u32 gmsg_ld05_1Size = 0x00003E20;
u32 gmsg_ld05_2Size = 0x00003E20;
u32 gmsg_ld06_1Size = 0x00003E20;
u32 gmsg_ld06_2Size = 0x00003E20;
u32 gmsg_ld06_3Size = 0x00003E20;
u32 gmsg_ld06_4Size = 0x00003E20;
u32 gmsg_ld07Size = 0x00003E20;
u32 gmsg_gf01Size = 0x00003E20;
u32 gmsg_gf02Size = 0x00003E20;
u32 gmsg_gf03Size = 0x00003E20;
u32 gmsg_gf04Size = 0x00003E20;
u32 gmsg_gf05Size = 0x00003E20;
u32 gmsg_gf06Size = 0x00003E20;
u32 gmsg_in01Size = 0x00003E20;
u32 gmsg_in02Size = 0x00003E20;
u32 gmsg_in03Size = 0x00003E20;
u32 gmsg_in04Size = 0x00003E20;
u32 gmsg_in05Size = 0x00003E20;
u32 gmsg_sv01Size = 0x00003E20;
u32 gmsg_sv01_2Size = 0x00003E20;
u32 gmsg_sv02Size = 0x00003E20;
u32 gmsg_sv03Size = 0x00003E20;
u32 gmsg_sv04Size = 0x00003E20;
u32 gmsg_sv05_1Size = 0x00003E20;
u32 gmsg_sv06_1Size = 0x00003E20;
u32 gmsg_sv06_2Size = 0x00003E20;
u32 gmsg_sv06_3Size = 0x00003E20;
u32 gmsg_sv06_4Size = 0x00003E20;
u32 gmsg_sv06_5Size = 0x00003E20;
u32 gmsg_sv07Size = 0x00003E20;
u32 gmsg_sv08Size = 0x00003E20;
u32 gmsg_sv09Size = 0x00003E20;
u32 gmsg_sv10Size = 0x00003E20;
u32 gmsg_sv11Size = 0x00003E20;
u32 gmsg_sv12Size = 0x00003E20;
u32 gmsg_sv_shareSize = 0x00003E20;
u32 gz_bnrSize = 0x00001840;
u32 gz_iconSize = 0x00001840;

s32 gHighlightChoice = 0x00000001;
__anon_0x61D7 simulatorMessageCurrent = S_M_NONE;
s32 gResetBeginFlag = true;

static Code* gpCode;

void* gpFrame;
void* gpSound;
System* gpSystem;

char gpErrorMessageBuffer[20480];
bool gbDisplayedError;
bool gPreviousAllowResetSetting;
bool gPreviousForceMenuSetting;
bool gPreviousIPLSetting;

u32 gnTickReset;
bool gbReset;



bool simulatorGXInit(void) {
    s32 i;
    GXColor GX_DEFAULT_BG = {0};
    GXColor BLACK = {0};
    GXColor WHITE = {0};
    f32 identity_mtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };

    // possible bug? GX_TG_MTX3x4 vs GX_TG_MTX2x4 (see identity_mtx)
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, 0x3C, GX_FALSE, 0x7D);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);

    GXEnableTexOffsets(GX_TEXCOORD0, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_DISABLE, GX_DISABLE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_DISABLE, GX_DISABLE);

    GXLoadPosMtxImm(identity_mtx, 0);
    GXLoadNrmMtxImm(identity_mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, 0);

    GXSetCoPlanar(GX_DISABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissorBoxOffset(0, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, BLACK);
    GXSetChanMatColor(GX_COLOR0A0, WHITE);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, BLACK);
    GXSetChanMatColor(GX_COLOR1A1, WHITE);
    GXInvalidateTexAll();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = 0; i < 0x10; i++) {
        GXSetTevKColorSel(i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel(i, GX_TEV_KASEL_1);
        GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect(i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.10000000149011612f, 1.0f, BLACK);
    GXSetFogRangeAdj(GX_DISABLE, 0, NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetZCompLoc(GX_ENABLE);
    GXSetDither(GX_ENABLE);
    GXSetDstAlpha(GX_DISABLE, 0);
    GXSetPixelFmt(GX_DISABLE, GX_ZC_LINEAR);
    GXSetFieldMask(GX_ENABLE, GX_ENABLE);

    GXSetCopyClear(GX_DEFAULT_BG, 0xFFFFFF);
    GXSetCopyClamp(3); // missing enum?
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();
    GXPokeColorUpdate(GX_ENABLE);
    GXPokeAlphaUpdate(GX_ENABLE);
    GXPokeDither(GX_DISABLE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_DISABLE, 0);
    GXPokeZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
    GXClearGPMetric();

    return true;
}

void simulatorUnpackTexPalette(TEXPalettePtr pal) {
    u16 i;

    pal->descriptorArray = (TEXDescriptorPtr)((char*)pal->descriptorArray + (u32)pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader) {
            pal->descriptorArray[i].textureHeader = (TEXHeaderPtr)((char*)pal + (u32)pal->descriptorArray[i].textureHeader);
            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                pal->descriptorArray[i].textureHeader->data = (char*)pal + (u32)pal->descriptorArray[i].textureHeader->data;
                pal->descriptorArray[i].textureHeader->unpacked = true;
            }
        }
        if (pal->descriptorArray[i].CLUTHeader) {
            pal->descriptorArray[i].CLUTHeader = (CLUTHeaderPtr)((u8 *)pal + (u32)pal->descriptorArray[i].CLUTHeader);
            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                pal->descriptorArray[i].CLUTHeader->data = (char*)pal + (u32)pal->descriptorArray[i].CLUTHeader->data;
                pal->descriptorArray[i].CLUTHeader->unpacked = true;
            }
        }
    }
}
bool simulatorDrawErrorMessage(__anon_0x61D7 simulatorErrorMessage, s32 drawBar, s32 percent);


bool gDVDResetToggle = false;
bool gButtonDownToggle = false;

bool simulatorDVDShowError(s32 nStatus, void* anData, s32 nSizeRead, u32 nOffset) {

    static s32 toggle;

    s32 continueToggle;
    __anon_0x61D7 nMessage = S_M_NONE; 

    do {
        if ((nStatus != 1) && (nStatus != 0) && (nStatus != 2) && (nStatus != 3) && (nStatus != 7) && (nStatus != 8) &&
            (nStatus != 0xA)) {
            continueToggle = 1;
        } else {
            continueToggle = 0;
        }

        switch (nStatus) {
            case -1:
                nMessage = S_M_DISK_FATAL_ERROR;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                nMessage = S_M_DISK_NO_DISK;
                break;
            case 5:
                nMessage = S_M_DISK_COVER_OPEN;
                break;
            case 6:
                nMessage = S_M_DISK_WRONG_DISK;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
                break;
            case 11:
                nMessage = S_M_DISK_RETRY_ERROR;
                break;
            default:
                nMessage = S_M_DISK_DEFAULT_ERROR;
                xlPostText("ShowError: Unknown FileInfoStatus: %d", "simGCN.c", 763, nStatus);
                break;
        }

        if ((nStatus != 1) && (nStatus != 0) && (nStatus != 2) && (nStatus != 3) && (nStatus != 7) && (nStatus != 8) &&
            (nStatus != 0xA)) {
            toggle = 1;
        } else if (toggle == 1) {
            toggle = 0;
            nMessage = S_M_DISK_READING_DISK;
        }

        if ((gDVDResetToggle == 1) && ((nStatus <= 3U) || ((nStatus - 7) <= 1U) || (nStatus == 10))) {
            if (simulatorTestReset(0, 0, 1, 0) == 0) {
                return false;;
            }
        } else if ((nStatus != -1) && (simulatorTestReset(1, 0, 1, 0) == 0)) {
            return false;;
        }

        if (nMessage != S_M_NONE) {
            while (frameBeginOK(gpSystem->pFrame) == 0)
                ;
            PADControlMotor(PAD_MOTOR_STOP, 0);
            simulatorDrawErrorMessage(nMessage, 0, 0);
        }

        nStatus = DVDGetDriveStatus();
    } while (continueToggle == 1);

    return true;
}

bool simulatorDVDOpen(char* szNameFile, DVDFileInfo* pFileInfo) {
    s32 nStatus;

    while ((nStatus = DVDGetDriveStatus()) != 0) {
        if (!simulatorDVDShowError(nStatus, NULL, 0, 0)) {
            return false;
        }
    }

    return DVDOpen(szNameFile, pFileInfo);
}

bool simulatorDVDRead(DVDFileInfo* pFileInfo, void* anData, s32 nSizeRead, s32 nOffset, DVDCallback callback) {
    s32 nStatus;
    bool bRetry;

    if (callback == NULL) {
        do {
            bRetry = false;
            DVDReadAsyncPrio(pFileInfo, anData, nSizeRead, nOffset, NULL, 2);

            while ((nStatus = DVDGetCommandBlockStatus(&pFileInfo->cb)) != 0) {
                if (!simulatorDVDShowError(nStatus, anData, nSizeRead, nOffset)) {
                    return false;
                }

                if ((nStatus == 11) || (nStatus == -1)) {
                    DVDCancel(&pFileInfo->cb);
                    bRetry = true;
                    break;
                }
            }
        } while (bRetry);
    } else {
        DVDReadAsyncPrio(pFileInfo, anData, nSizeRead, nOffset, callback, 2);
        return true;
    }

    return true;
}

bool simulatorPlayMovie(void) {
    simulatorResetAndPlayMovie();
    return true;
}

s32 simulatorDrawImage(TEXPalettePtr tpl, s32 nX0, s32 nY0, s32 drawBar, s32 percent) {
    GXTexObj texObj;
    GXTexObj texObj2;
    u32 pad2;
    GXColor color;
    f32 identity_mtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };  // r1+0x84
    f32 g2DviewMtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };

    f32 g2[3][4];

    do {
    } while (frameBeginOK(gpFrame) != 1);

    simulatorGXInit();
    xlCoreBeforeRender();
    GXSetZMode(0U, GX_LEQUAL, 0U);
    GXSetZCompLoc(1U);
    GXSetNumTevStages(1U);
    GXSetNumChans(1U);
    GXSetNumTexGens(0U);

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2, 0);
    GXLoadTexMtxImm(identity_mtx, 60, 0);

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0U, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0U, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = N64_FRAME_WIDTH;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = N64_FRAME_WIDTH;
    GXWGFifo.f32 = N64_FRAME_HEIGHT;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = N64_FRAME_HEIGHT;
    GXWGFifo.f32 = 0.0f;

    Vert_s16[0] = nX0;
    Vert_s16[1] = nY0;
    Vert_s16[3] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[4] = nY0;
    Vert_s16[6] = nX0 + tpl->descriptorArray->textureHeader->width;
    Vert_s16[7] = nY0 + tpl->descriptorArray->textureHeader->height;
    Vert_s16[9] = nX0;
    Vert_s16[10] = nY0 + tpl->descriptorArray->textureHeader->height;
    DCStoreRange(Vert_s16, sizeof(Vert_s16));

    simulatorGXInit();
    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);
    GXLoadPosMtxImm(g2, 0);
    GXLoadTexMtxImm(identity_mtx, 0x3C, GX_MTX3x4);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);

    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXLoadTexObj(&texObj, 0);
    GXSetTevOp(0, 1);
    GXBegin(0x80, 0, 4);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;

    if (drawBar == true) {
        GXLoadPosMtxImm(g2DviewMtx, false);

        Vert_s16Bar[0] = N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[1] = (nY0 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[3] = ((N64_FRAME_WIDTH / 2 - (((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[4] = (nY0 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[6] = ((N64_FRAME_WIDTH / 2 - (((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[7] = (nY0 + tpl->descriptorArray->textureHeader->height +
                          ((TEXPalettePtr)gbar)->descriptorArray->textureHeader->height);
        Vert_s16Bar[9] = N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[10] = (nY0 + tpl->descriptorArray->textureHeader->height +
                           ((TEXPalettePtr)gbar)->descriptorArray->textureHeader->height);

        DCStoreRange(Vert_s16Bar, sizeof(Vert_s16Bar));
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXSetArray(GX_VA_POS, Vert_s16Bar, 6);
        GXSetArray(GX_VA_CLR0, Colors_u32, 4);
        GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
        TEXGetGXTexObjFromPalette((void*)gbar, &texObj2, 0U);
        GXLoadTexObj(&texObj2, GX_TEXMAP0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 1;
        GXWGFifo.u8 = 1;
        GXWGFifo.u8 = 1;
        GXWGFifo.u8 = 2;
        GXWGFifo.u8 = 2;
        GXWGFifo.u8 = 2;
        GXWGFifo.u8 = 3;
        GXWGFifo.u8 = 3;
        GXWGFifo.u8 = 3;
    }
    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(1U, GX_LEQUAL, 1U);
    GXSetColorUpdate(1U);
    GXCopyDisp(DemoCurrentBuffer, 1U);
    GXDrawDone();
    VISetNextFrameBuffer(DemoCurrentBuffer);
    VIFlush();
    VIWaitForRetrace();

    if ((void*)DemoCurrentBuffer == (void*)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();
    return 1;
}

s32 simulatorDrawYesNoImage(TEXPalettePtr tplMessage, s32 nX0Message, s32 nY0Message,
                            TEXPalettePtr tplYes, s32 nX0Yes, s32 nY0Yes, TEXPalettePtr tplNo,
                            s32 nX0No, s32 nY0No)  {

    GXTexObj texObj;
    u32 pad;
    GXColor color0;
    GXColor color1;

    f32 identity_mtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };
    f32 g2DviewMtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };

    do {
    } while (frameBeginOK(gpFrame) != 1);

    Vert_s16[0] = nX0Message;
    Vert_s16[1] = nY0Message;
    Vert_s16[3] = nX0Message + tplMessage->descriptorArray->textureHeader->width;
    Vert_s16[4] = nY0Message;
    Vert_s16[6] = nX0Message + tplMessage->descriptorArray->textureHeader->width;
    Vert_s16[7] = nY0Message + tplMessage->descriptorArray->textureHeader->height;
    Vert_s16[9] = nX0Message;
    Vert_s16[10] = nY0Message + tplMessage->descriptorArray->textureHeader->height;

    DCStoreRange(Vert_s16, sizeof(Vert_s16));

    simulatorGXInit();

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2DviewMtx, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2DviewMtx, g2DviewMtx, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2DviewMtx, 0);
    GXLoadTexMtxImm(identity_mtx, 60, 0);

    GXSetNumChans(1U);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);

    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);

    TEXGetGXTexObjFromPalette(tplMessage, &texObj, 0U);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    xlCoreBeforeRender();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;

    VertYes_s16[0] = nX0Yes;
    VertYes_s16[1] = nY0Yes;
    VertYes_s16[3] = nX0Yes + tplYes->descriptorArray->textureHeader->width;
    VertYes_s16[4] = nY0Yes;
    VertYes_s16[6] = nX0Yes + tplYes->descriptorArray->textureHeader->width;
    VertYes_s16[7] = nY0Yes + tplYes->descriptorArray->textureHeader->height;
    VertYes_s16[9] = nX0Yes;
    VertYes_s16[10] = nY0Yes + tplYes->descriptorArray->textureHeader->height;

    DCStoreRange(VertYes_s16, sizeof(VertYes_s16));

    GXClearVtxDesc(); 
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, VertYes_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
    TEXGetGXTexObjFromPalette(tplYes, &texObj, 0U);
    GXLoadTexObj(&texObj, 0);
    
    if(gHighlightChoice == 1){
        color0.r = 0;
        color0.g = 0;
        color0.b = 0;
        color0.a = 255; 
    
        color1.r = 255;
        color1.g = 255;
        color1.b = 0;
        color1.a = 255;
     
        GXSetTevColor(GX_TEVREG0, color0);
        GXSetTevColor(GX_TEVREG1, color1);
    
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
    }
    else{
        GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    }

    xlCoreBeforeRender();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;

    VertNo_s16[0] = nX0No;
    VertNo_s16[1] = nY0No;
    VertNo_s16[3] = nX0No + tplNo->descriptorArray->textureHeader->width;
    VertNo_s16[4] = nY0No;
    VertNo_s16[6] = nX0No + tplNo->descriptorArray->textureHeader->width;
    VertNo_s16[7] = nY0No + tplNo->descriptorArray->textureHeader->height;
    VertNo_s16[9] = nX0No;
    VertNo_s16[10] = nY0No + tplNo->descriptorArray->textureHeader->height;

    DCStoreRange(VertNo_s16, sizeof(VertNo_s16));

    GXClearVtxDesc(); 
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, VertNo_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
    TEXGetGXTexObjFromPalette(tplNo, &texObj, 0U);
    GXLoadTexObj(&texObj, 0);

    if(gHighlightChoice == 1){
        GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    }
    else{
        color0.r = 0;
        color0.g = 0;
        color0.b = 0;
        color0.a = 255; 
    
        color1.r = 255;
        color1.g = 255;
        color1.b = 0;
        color1.a = 255;
     
        GXSetTevColor(GX_TEVREG0, color0);
        GXSetTevColor(GX_TEVREG1, color1);
    
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
    }
    

    xlCoreBeforeRender();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    

    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(1U, GX_LEQUAL, 1U);
    GXSetColorUpdate(1U);
    GXCopyDisp(DemoCurrentBuffer, 1U);
    GXDrawDone();
    VISetNextFrameBuffer(DemoCurrentBuffer);
    VIFlush();
    VIWaitForRetrace();

    if ((void*)DemoCurrentBuffer == (void*)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();
    PAD_STACK();

    return 1;
}

s32 simulatorDrawOKImage(TEXPalettePtr tplMessage, s32 nX0Message, s32 nY0Message, TEXPalettePtr tplOK, s32 nX0OK,
                         s32 nY0OK) {
    GXTexObj texObj;
    GXColor color0;
    GXColor color1;
    u32 pad;
    f32 identity_mtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };  // r1+0x84
    f32 g2DviewMtx[3][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, -1.0},
    };  // r1+0x54


    do {
    } while (frameBeginOK(gpFrame) != 1);

    Vert_s16[0] = nX0Message;
    Vert_s16[1] = nY0Message;
    Vert_s16[3] = nX0Message + tplMessage->descriptorArray->textureHeader->width;
    Vert_s16[4] = nY0Message;
    Vert_s16[6] = nX0Message + tplMessage->descriptorArray->textureHeader->width;
    Vert_s16[7] = nY0Message + tplMessage->descriptorArray->textureHeader->height;
    Vert_s16[9] = nX0Message;
    Vert_s16[10] = nY0Message + tplMessage->descriptorArray->textureHeader->height;

    DCStoreRange(Vert_s16, sizeof(Vert_s16));

    simulatorGXInit();

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.10000000149011612f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2DviewMtx, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2DviewMtx, g2DviewMtx, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2DviewMtx, 0);
    GXLoadTexMtxImm(identity_mtx, 60, 0);

    GXSetNumChans(1U);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);

    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);

    TEXGetGXTexObjFromPalette(tplMessage, &texObj, 0U);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    xlCoreBeforeRender();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;

    VertYes_s16[0] = nX0OK;
    VertYes_s16[1] = nY0OK;
    VertYes_s16[3] = nX0OK + tplOK->descriptorArray->textureHeader->width;
    VertYes_s16[4] = nY0OK;
    VertYes_s16[6] = nX0OK + tplOK->descriptorArray->textureHeader->width;
    VertYes_s16[7] = nY0OK + tplOK->descriptorArray->textureHeader->height;
    VertYes_s16[9] = nX0OK;
    VertYes_s16[10] = nY0OK + tplOK->descriptorArray->textureHeader->height;

    DCStoreRange(VertYes_s16, sizeof(VertYes_s16));

    GXClearVtxDesc(); 
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, VertYes_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGB8, 0U);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
    TEXGetGXTexObjFromPalette(tplOK, &texObj, 0U);

    color0.r = 0;
    color0.g = 0;
    color0.b = 0;
    color0.a = 255;

    color1.r = 255;
    color1.g = 255;
    color1.b = 0;
    color1.a = 255;
 
    GXSetTevColor(GX_TEVREG0, color0);
    GXSetTevColor(GX_TEVREG1, color1);

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1U, GX_TEVPREV);
    
    
    GXLoadTexObj(&texObj, 0);
    xlCoreBeforeRender();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);

    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 1;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 2;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;
    GXWGFifo.u8 = 3;

    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(1U, GX_LEQUAL, 1U);
    GXSetColorUpdate(1U);
    GXCopyDisp(DemoCurrentBuffer, 1U);
    GXDrawDone();
    VISetNextFrameBuffer(DemoCurrentBuffer);
    VIFlush();
    VIWaitForRetrace();

    if ((void*)DemoCurrentBuffer == (void*)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();

    return 1;
}

bool simulatorDrawErrorMessage(__anon_0x61D7 simulatorErrorMessage, s32 drawBar, s32 percent) {

    PADControlMotor(0, PAD_MOTOR_STOP);
    switch (simulatorErrorMessage) {
        case S_M_DISK_COVER_OPEN:
            simulatorDrawImage(
                (TEXPalettePtr)gcoverOpen,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gcoverOpen)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gcoverOpen)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_WRONG_DISK:
            simulatorDrawImage(
                (TEXPalettePtr)gwrongDisk,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gwrongDisk)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gwrongDisk)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_READING_DISK:
            simulatorDrawImage(
                (TEXPalettePtr)greadingDisk,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)greadingDisk)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)greadingDisk)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_RETRY_ERROR:
            simulatorDrawImage(
                (TEXPalettePtr)gretryErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gretryErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gretryErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_FATAL_ERROR:
            simulatorDrawImage(
                (TEXPalettePtr)gfatalErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gfatalErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gfatalErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_NO_DISK:
            simulatorDrawImage(
                (TEXPalettePtr)gnoDisk,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gnoDisk)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gnoDisk)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_DEFAULT_ERROR:
            simulatorDrawImage(
                (TEXPalettePtr)gfatalErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gfatalErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gfatalErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
    }
    gbDisplayedError = 1;
    return true;
}


s32 simulatorPrepareMessage(__anon_0x61D7 simulatorErrorMessage) {
    DVDFileInfo fileInfo;
    switch(simulatorErrorMessage){
        
        case S_M_CARD_IN02:

            if(simulatorMessageCurrent != simulatorErrorMessage){
                simulatorMessageCurrent = simulatorErrorMessage;
                if(DVDOpen("TPL/msg_in02.tpl", &fileInfo) == 1){
                    simulatorDVDRead(&fileInfo,gpErrorMessageBuffer,((gmsg_in02Size + 0x1F) &~ 0x1F),0,NULL);
                }
                DVDClose(&fileInfo);  
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            break; 

        case S_M_CARD_SV09:
            if(simulatorMessageCurrent != simulatorErrorMessage){
                simulatorMessageCurrent = simulatorErrorMessage;
                if(DVDOpen("TPL/msg_sv09.tpl", &fileInfo)== 1){
                    simulatorDVDRead(&fileInfo,gpErrorMessageBuffer,((gmsg_sv09Size + 0x1F) &~ 0x1F),0,NULL);
                }
                DVDClose(&fileInfo);  
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            break; 

        case S_M_CARD_GF02:
            if(simulatorMessageCurrent != simulatorErrorMessage){
                simulatorMessageCurrent = simulatorErrorMessage;
                if(DVDOpen("TPL/msg_gf02.tpl", &fileInfo)== 1){
                    simulatorDVDRead(&fileInfo,gpErrorMessageBuffer,((gmsg_gf02Size + 0x1F) &~ 0x1F),0,NULL);
                }
                DVDClose(&fileInfo);  
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            break; 
    }
    return true;
}


bool simulatorDrawYesNoMessageLoop(TEXPalettePtr simulatorQuestion, s32* yes) {
    TEXDescriptorPtr* pNo;
    TEXDescriptorPtr* pYes;
    TEXDescriptorPtr* pQuestion;
    s32 pad[2];

    if (*yes == 1) {
        gHighlightChoice = 1;
    } else {
        gHighlightChoice = 0;
    }

    pNo = &((TEXPalettePtr)gno)->descriptorArray;
    pYes = &((TEXPalettePtr)gyes)->descriptorArray;
    pQuestion = &simulatorQuestion->descriptorArray;
    simulatorDrawYesNoImage(
        simulatorQuestion,
        N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2,
        (TEXPalettePtr)gyes,
        120 - (*pYes)->textureHeader->width / 2,
        180 - (*pYes)->textureHeader->height / 2,
        (TEXPalettePtr)gno,
        200 - (*pNo)->textureHeader->width / 2,
        180 - (*pNo)->textureHeader->height / 2); 

    if (gButtonDownToggle == 1) {
        DEMOPadRead();
        if (DemoPad->pst.button != 0) {
            return false;
        }
    }

    gButtonDownToggle = 0;
    DEMOPadRead(); 
    if (*yes == 1) {
        gHighlightChoice = 1;
    } else {
        gHighlightChoice = 0;
    }
    
    simulatorDrawYesNoImage(
        simulatorQuestion,
        N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2,
        (TEXPalettePtr)gyes,
        120 - (*pYes)->textureHeader->width / 2,
        180 - (*pYes)->textureHeader->height / 2,
        (TEXPalettePtr)gno,
        200 - (*pNo)->textureHeader->width / 2,
        180 - (*pNo)->textureHeader->height / 2); 

    if (DemoPad->pst.err == 0) {
        if (DemoPad->pst.button & 0x1100) {
            if ((s32) *yes == 1) {
                soundPlayBeep(gpSystem->pSound, 0);
            } else {
                soundPlayBeep(gpSystem->pSound, 1);
            }
            gButtonDownToggle = 1;
            return true;
        }
        if (DemoPad->pst.button & 0x200) {
            soundPlayBeep(gpSystem->pSound, 1);
            gButtonDownToggle = 1;
            *yes = 0;
            return true;
        } 
        if (((s8) (u8) DemoPad->pst.stickX < 0) && ((s32) *yes == 0)) {
            soundPlayBeep(gpSystem->pSound, 2);
            *yes = 1;
        } else if (((s8) (u8) DemoPad->pst.stickX > 0) && ((s32) *yes == 1)) {
            soundPlayBeep(gpSystem->pSound, 2);
            *yes = 0;
        }
    }

    return false;
}

bool simulatorDrawYesNoMessage(__anon_0x61D7 simulatorMessage, s32* yes) {
    DVDFileInfo fileInfo;
    switch (simulatorMessage) {
        case S_M_CARD_LD05_2:

            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld05_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld05_2Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD06_4:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld06_4.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld06_4Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD07:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld07.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld07Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);
        case S_M_CARD_GF01:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_gf01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_gf01Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);

        case S_M_CARD_IN01:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_in01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_in01Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV06_4:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv06_4.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv06_4Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);
        case S_M_CARD_SV06_5:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv06_5.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv06_5Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);
        case S_M_CARD_SV08:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv08.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv08Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }

            return simulatorDrawYesNoMessageLoop((TEXPalettePtr)gpErrorMessageBuffer, yes);
    }

    return false; 
}

static inline s32 simulatorDrawOKMessageLoop(TEXPalettePtr simulatorMessage) {
    simulatorDrawOKImage(
        (TEXPalettePtr)gpErrorMessageBuffer,
        N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2,
        simulatorMessage,
        N64_FRAME_WIDTH / 2 - simulatorMessage->descriptorArray->textureHeader->width / 2,
        180 - ((TEXPalettePtr)gyes)->descriptorArray->textureHeader->height / 2);

    if (gButtonDownToggle == 1) {
        DEMOPadRead();
        if (DemoPad->pst.button != 0) {
            return 0;
        }
    }

    gButtonDownToggle = 0;
    DEMOPadRead();

    simulatorDrawOKImage(
        (TEXPalettePtr)gpErrorMessageBuffer,
        N64_FRAME_WIDTH / 2 - ((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - ((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2,
        simulatorMessage,
        N64_FRAME_WIDTH / 2 - simulatorMessage->descriptorArray->textureHeader->width / 2,
        180 - ((TEXPalettePtr)gyes)->descriptorArray->textureHeader->height / 2);

    if ((DemoPad->pst.err == 0) && (DemoPad->pst.button & 0x1100)) {
        soundPlayBeep(gpSystem->pSound, 0);
        gButtonDownToggle = 1;
        return 1;
    }

    PAD_STACK();
    return 0;
}


bool simulatorDrawErrorMessageWait(__anon_0x61D7 simulatorErrorMessage) {
    // Local variables
    DVDFileInfo fileInfo;  // r1+0x80

    switch (simulatorErrorMessage) {
        case 7:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld01Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 8:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld02Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 9:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld03Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 10:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld04Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);

        case 11:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld05_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld05_1Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 13:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld06_1Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 14:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld06_2Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 15:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_3.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_ld06_3Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 20:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_gf03Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 21:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_gf04Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 22:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf05.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_gf05Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 23:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf06.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_gf06Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 26:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_in03Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 27:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_in04Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 28:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in05.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_in05Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 29:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv01Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 30:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv01_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv01_2Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 31:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv02Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 32:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv03Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 33:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv04Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 34:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv05_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv05_1Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 35:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv06_1Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 36:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv06_2Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 37:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_3.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv06_3Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 40:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv07.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv07Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 43:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv10.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv10Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 44:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv11.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv11Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 45:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv12.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv12Size + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);
        case 46:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv_share.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, ((gmsg_sv_shareSize + 0x1F) & ~0x1F), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalettePtr)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalettePtr)gmesgOK);

        default:
            break;
    }

    return true;
}


static inline void simulatorResetInit(void) {
    mcardWriteGameDataReset(&mCard);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    PADRecalibrate(0xF0000000);
    GXAbortFrame();
    LCDisable();
    VIWaitForRetrace();
}

void simulatorReset(bool IPL, bool forceMenu) {
    simulatorResetInit();

    if (IPL == true) {
        if (forceMenu == true) {
            OSResetSystem(OS_RESET_HOTRESET, 0, true);
        } else {
            OSResetSystem(OS_RESET_HOTRESET, 0, false);
        }
    } else {
        OSResetSystem(OS_RESET_RESTART, 0, false);
    }
    NO_INLINE();
}

static inline void simulatorUnknownInline(void) {
    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
    GXDrawDone();
    VISetNextFrameBuffer(DemoCurrentBuffer);
    VIFlush();
    VIWaitForRetrace();

    if (DemoCurrentBuffer == DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
}

void simulatorResetAndPlayMovie(void) {
    int pad1;
    GXColor color;
    GXRenderModeObj* simrmode;
    int pad2;

    simrmode = rmode;
    simulatorResetInit();
    xlCoreReset();
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 1;
    DEMOInit(NULL);
    rmode = simrmode;
    VISetBlack(1);
    AIInit(NULL);
    GXSetCopyClear(color, 0);
    MovieInit();

    while (true) {
        OSGetTick();

        if (gMovieErrorToggle == true) {
            continue;
        }

        DEMOBeforeRender();
        MovieDraw();
        simulatorUnknownInline();
        VISetBlack(false);
        GXSetCopyClear(color, 0);
        movieTestReset(false, false);
    }
}

bool simulatorSetControllerMap(u32* mapData, s32 channel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gContMap[channel]); i++) {
        gContMap[channel][i] = mapData[i];
    }

    return true;
}

bool simulatorCopyControllerMap(u32* mapDataOutput, u32* mapDataInput) {
    int i;

    for (i = 0; i < 20; i++) {
        mapDataOutput[i] = mapDataInput[i];
    }

    return true;
}

inline void UnkInlineReadController(s32 stickValue, s32* val) {
    s32 ret;
    if (((stickValue >= 0) && (stickValue < 0x28)) || ((stickValue < 0) && (stickValue > -0x28))) {
        ret = (stickValue * 0x43) / 40;
    } else if ((stickValue >= 0x28) && (stickValue < 0x48)) {
        ret = (((0x48 - stickValue) * 0x43) / 32) + (((stickValue - 0x28) * 0x5A) / 32);
    } else if ((stickValue <= -0x28) && (stickValue > -0x48)) {
        ret = (((-0x28 - stickValue) * -0x5A) / 32) + (((stickValue + 0x48) * -0x43) / 32);
    } else if (stickValue >= 0x48) {
        ret = 0x5A;
    } else {
        ret = -0x5AU;
    }

    *val = ret; 
}

s32 simulatorReadController(s32 channel, u32* anData, u32 unused) {
    static u32 nCurrButton;
    static u32 nPrevButton;

    f32 subStickTest;
    s32 stickX;
    s32 stickY;
    s32 subStickX;
    s32 subStickY;
    s32 nDirButton;


    nPrevButton = nCurrButton;

    DEMOPadRead();

    *anData = 0;

    if(DemoPad[channel].pst.err == 0){
        UnkInlineReadController(DemoPad[channel].pst.stickX,&stickX);
        *anData |= (stickX & 0xFF) << 8;
        UnkInlineReadController(DemoPad[channel].pst.stickY,&stickY);
        *anData |= stickY & 0xFF; 

        nDirButton = DemoPad[channel].dirs;
        subStickX = DemoPad[channel].pst.substickX;
        subStickY = DemoPad[channel].pst.substickY;
        if (gButtonDownToggle == 1) {
            if (DemoPad->pst.button != 0) {
                return 1;
            }
            else{
                gButtonDownToggle = 0;
            }
        }
        nCurrButton = DemoPad[channel].pst.button; 

        if((nCurrButton & 0x1600) == 0x1600){
            gButtonDownToggle = 1;
            return 1;
        }
        if ((subStickX != 0) && (subStickY != 0)) {
            subStickTest = (f32) subStickX / (f32) subStickY;
        } else {
            subStickTest = 0.0f;
        }
        if (subStickTest < 0.0f) {
            subStickTest *= -1.0f;
        }
        if ((subStickTest > 1.1f) || (subStickTest < 0.9090908765792847f)) {
            if (nDirButton & 0x100) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_UP];
            }
            if (nDirButton & 0x200) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_DOWN];
            }
            if (nDirButton & 0x400) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_LEFT];
            }
            if (nDirButton & 0x800) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_RIGHT];
            }
        }
        if (nCurrButton & 0x1000) {
            *anData |= gContMap[channel][GCN_BTN_START];
        }
        if (nCurrButton & 0x10) {
            *anData |= gContMap[channel][GCN_BTN_Z];
        }
        if (DemoPad[channel].pst.triggerRight > 30) {
            *anData |= gContMap[channel][GCN_BTN_R];
        }
        if (DemoPad[channel].pst.triggerLeft > 30) {
            *anData |= gContMap[channel][GCN_BTN_L];
        }
        if (nCurrButton & 0x100) {
            *anData |= gContMap[channel][GCN_BTN_A]; 
        }
        if (nCurrButton & 0x200) {
            *anData |= gContMap[channel][GCN_BTN_B];
        }
        if (nCurrButton & 0x400) {
            *anData |= gContMap[channel][GCN_BTN_X];
        }
        if (nCurrButton & 0x800) {
            *anData |= gContMap[channel][GCN_BTN_Y]; 
            return true;
        }
        if (nCurrButton & 8) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_UP];
        }
        if (nCurrButton & 4) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_DOWN];
        }
        if (nCurrButton & 1) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_LEFT];
        }
        if (nCurrButton & 2) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_RIGHT];
        }
    }
    return true;
} 

bool simulatorShowLoad(s32 unknown, char* szNameFile, f32 rProgress) { return true; }

bool simulatorDetectController(s32 channel) {
    PADStatus status[4];

    PADRead(status);

    if (status[channel].err == -1) {
        return false;
    }

    return true;
}

bool simulatorReadPak(s32 channel, u16 address, u8* data) {
    ControllerType type;

    pifGetEControllerType(SYSTEM_PIF(gpSystem), channel, &type);

    if (type == CT_CONTROLLER_W_RPAK) {
        pifReadRumble(SYSTEM_PIF(gpSystem), channel, address, data);
    }

    return true;
}

bool simulatorWritePak(s32 channel, u16 address, u8* data) {
    ControllerType type;

    pifGetEControllerType(SYSTEM_PIF(gpSystem), channel, &type);

    if (type == CT_CONTROLLER_W_RPAK) {
        pifWriteRumble(SYSTEM_PIF(gpSystem), channel, address, data);
    }

    return true;
}

bool simulatorReadEEPROM(u8 address, u8* data) {
    s32 size;

    if (!pifGetEEPROMSize(SYSTEM_PIF(gpSystem), (u32*)&size)) {
        return false;
    }

    mcardRead(&mCard, (address * 8) & 0x7F8, 8, (char*)data);
    return true;
}

bool simulatorWriteEEPROM(u8 address, u8* data) {
    s32 size;

    if (!pifGetEEPROMSize(SYSTEM_PIF(gpSystem), (u32*)&size)) {
        return false;
    }

    mcardWrite(&mCard, (address * 8) & 0x7F8, 8, (char*)data);
    return true;
}

bool simulatorReadSRAM(u32 address, u8* data, s32 size) {
    mcardRead(&mCard, address, size, (char*)data);
    return true;
}

bool simulatorWriteSRAM(u32 address, u8* data, s32 size) {
    mcardWrite(&mCard, address, size, (char*)data);
    return true;
}

bool simulatorReadFLASH(u32 address, u8* data, s32 size) {
    mcardRead(&mCard, address, size, (char*)data);
    return true;
}

bool simulatorWriteFLASH(u32 address, u8* data, s32 size) {
    mcardWrite(&mCard, address, size, (char*)data);
    return true;
}

bool simulatorRumbleStart(s32 channel) {
    PADControlMotor(channel, 1);
    return true;
}

bool simulatorRumbleStop(s32 channel) {
    PADControlMotor(channel, 0);
    return true;
}

bool simulatorTestReset(bool IPL, bool forceMenu, bool allowReset, bool usePreviousSettings) {
    u32 bFlag;
    u32 nTick;
    bool prevIPLSetting;
    bool prevForceMenuSetting;
    bool prevAllowResetSetting;
    s32 pad;

    nTick = OSGetTick();
    prevAllowResetSetting = gPreviousAllowResetSetting;
    prevIPLSetting = gPreviousIPLSetting;
    prevForceMenuSetting = gPreviousForceMenuSetting;

    if (usePreviousSettings == 1) {
        IPL = gPreviousIPLSetting;
        forceMenu = gPreviousForceMenuSetting;
        allowReset = gPreviousAllowResetSetting;
    } else {
        gPreviousIPLSetting = IPL;
        gPreviousForceMenuSetting = forceMenu;
        gPreviousAllowResetSetting = allowReset;
    }

    DEMOPadRead();
    bFlag = OSGetResetButtonState();

    if ((gResetBeginFlag == true) && ((DemoPad[0].pst.button & 0x1600) == 0x1600)) {
        if (!gbReset || bFlag) {
            gbReset = bFlag;
            return true;
        }

        if (allowReset == 1) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        gResetBeginFlag = false;
    }

    if ((DemoPad[0].pst.button & 0x1600) != 0x1600) {
        gnTickReset = nTick;
        if (!gbReset || bFlag) {
            gbReset = bFlag;
            return true;
        }

        if (allowReset == 1) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        if (((nTick - gnTickReset) >= OSSecondsToTicks(0.5f)) && (allowReset == 1)) {
            if (prevAllowResetSetting == 1) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    }

    return true;
}

bool simulatorDrawMCardText() {
    if ((s32)(((TEXPalettePtr)gpErrorMessageBuffer)->versionNumber) == 0) {
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c", 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
    simulatorDrawImage((TEXPalettePtr)gpErrorMessageBuffer,
                       160 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
        120 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2),0,0);
    return true;
}

s32 simulatorMCardPollDrawBar() {
    // Local variables
    f32 rate; // r1+0x8
    s32 nBytes; // r1+0x8

    nBytes = CARDGetXferredBytes(mCard.slot) - mCard.pollPrevBytes;
    rate = nBytes / (f32) mCard.pollSize;

    rate = (rate > 1.0f) ? 1.0f : rate;

    rate  = (rate < 0.0f) ? 0.0f : rate;
    
    if ((s32)(((TEXPalettePtr)gpErrorMessageBuffer)->versionNumber) == 0) {
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c", 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
    simulatorDrawImage((TEXPalettePtr)gpErrorMessageBuffer,
                       160 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
        120 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2),1,100.0f * rate);
    return true;
} 

s32 simulatorMCardPollDrawFormatBar() {
    // Local variables
    f32 rate; // r1+0x8
    s32 nBytes; // r1+0x8

    nBytes = CARDGetXferredBytes(mCard.slot) - mCard.pollPrevBytes;
    rate = nBytes / (f32) mCard.pollSize;

    rate = (rate > 1.0f) ? 1.0f : rate;

    rate  = (rate < 0.0f) ? 0.0f : rate;
    
    if ((s32)(((TEXPalettePtr)gpErrorMessageBuffer)->versionNumber) == 0) {
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c", 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
    simulatorDrawImage((TEXPalettePtr)gpErrorMessageBuffer,
                       160 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
        120 - (((TEXPalettePtr)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2),0,100.0f * rate);
    return true;
} 

static bool simulatorDrawCursor(s32 nX, s32 nY) {
    GXColor color;
    s32 nTick;
    u8 var_r5;
    s32 pad;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    nTick = OSGetTick() >> 14;
    if (nTick & 0x100) {
        var_r5 = (u8)nTick ^ 0xFF;
    } else {
        var_r5 = (u8)nTick;
    }

    color.r = color.g = color.b = 0;

    switch ((nTick >> 9) % 7) {
        case 0:
            color.r = var_r5;
            break;
        case 1:
            color.g = var_r5;
            break;
        case 2:
            color.b = var_r5;
            break;
        case 3:
            color.g = var_r5;
            color.r = var_r5;
            break;
        case 4:
            color.b = var_r5;
            color.r = var_r5;
            break;
        case 5:
            color.b = var_r5;
            color.g = var_r5;
            break;
        case 6:
            color.b = var_r5;
            color.g = var_r5;
            color.r = var_r5;
            break;
    }

    GXSetTevColor(GX_TEVREG0, color);
    GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);

    GXWGFifo.s16 = nX;
    GXWGFifo.s16 = nY;
    GXWGFifo.s16 = nX + 8;
    GXWGFifo.s16 = nY + 4;
    GXWGFifo.s16 = nX;
    GXWGFifo.s16 = nY + 8;

    return true;
}

static bool simulatorParseArguments(void) {
    s32 iArgument;
    char* szText;
    char* szValue;
    s32 pad1;
    s32 pad2;

    (void) "Play Delay";
    (void) "Silence Count";
    (void) "Fade Up Count";
    (void) "How many audio frames the\ngame must be playing before it\nconsiders the sound stable";
    (void) "How many audio frames the\ngame must NOT play before it\nconsiders itself unstable";
    (void) "How many audio frames to\nperform a fade up on the audio";

    gaszArgument[SAT_NAME] = NULL;
    gaszArgument[SAT_PROGRESSIVE] = NULL;
    gaszArgument[SAT_VIBRATION] = NULL;
    gaszArgument[SAT_CONTROLLER] = NULL;
    gaszArgument[SAT_XTRA] = NULL;
    gaszArgument[SAT_MEMORYCARD] = NULL;
    gaszArgument[SAT_MOVIE] = NULL;
    gaszArgument[SAT_RESET] = NULL;

    iArgument = 0;
    while (iArgument < xlCoreGetArgumentCount()) {
        xlCoreGetArgument(iArgument, &szText);
        iArgument += 1;
        if (szText[0] == '-' || szText[0] == '/' || szText[0] == '\\') {
            if (szText[2] == '\0') {
                xlCoreGetArgument(iArgument, &szValue);
                iArgument += 1;
            } else {
                szValue = &szText[2];
            }

            switch (szText[1]) {
                case 'V':
                case 'v':
                    gaszArgument[SAT_VIBRATION] = szValue;
                    break;
                case 'P':
                case 'p':
                    gaszArgument[SAT_PROGRESSIVE] = szValue;
                    break;
                case 'G':
                case 'g':
                    gaszArgument[SAT_CONTROLLER] = szValue;
                    break;
                case 'C':
                case 'c':
                    gaszArgument[SAT_MEMORYCARD] = szValue;
                    break;
                case 'M':
                case 'm':
                    gaszArgument[SAT_MOVIE] = szValue;
                    break;
                case 'R':
                case 'r':
                    gaszArgument[SAT_RESET] = szValue;
                    break;
                case 'X':
                case 'x':
                    gaszArgument[SAT_XTRA] = szValue;
                    break;
            }
        } else {
            gaszArgument[SAT_NAME] = szText;
        }
    }
    return true;
}

bool simulatorGetArgument(SimArgumentType eType, char** pszArgument) {
    if (eType != SAT_NONE && pszArgument != NULL && gaszArgument[eType] != NULL) {
        *pszArgument = gaszArgument[eType];
        return true;
    }

    return false;
}

static inline s32 simulatorRun(SystemMode* peMode) {
    int nResult;

    while (systemGetMode(gpSystem, peMode) && *peMode == SM_RUNNING) {
        nResult = systemExecute(gpSystem, 100000);
        if (!nResult) {
            return nResult;
        }
    }

    return 1;
}

bool xlMain(void) {
    GXColor color;
    SystemMode eMode;
    s32 nSize0;
    s32 nSize1;
    s32 iName;
    char* szNameROM;
    char acNameROM[32];
    // s32 rumbleYes;

    simulatorParseArguments();
    gDVDResetToggle = false;

    if (!xlHeapGetFree(&nSize0)) {
        return false;
    }
    if (nSize0 > 0x01800000) {
        OSReport("\n\nERROR: This program MUST be run on a system with 24MB (or less) memory!\n");
        OSReport("       Please reduce memory-size to 24MB (using 'setsmemsize 0x1800000')...\n");
        while (true) {}
    }

#ifdef __MWERKS__
    asm {
        li      r3, 0x706
        oris    r3, r3, 0x706
        mtspr   GQR6, r3
        li      r3, 0x507
        oris    r3, r3, 0x507
        mtspr   GQR7, r3
    }
#endif

    color.r = color.g = color.b = 0;
    color.a = 0xFF;

    gbDisplayedError = false;
    gButtonDownToggle = false;
    gResetBeginFlag = true;

    GXSetCopyClear(color, 0xFFFFFF);
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();

    xlCoreBeforeRender();
    simulatorUnknownInline();

    xlCoreBeforeRender();
    simulatorUnknownInline();

    VIWaitForRetrace();
    VISetBlack(0);
    VIFlush();

    simulatorUnpackTexPalette((TEXPalettePtr)gcoverOpen);
    simulatorUnpackTexPalette((TEXPalettePtr)gnoDisk);
    simulatorUnpackTexPalette((TEXPalettePtr)gretryErr);
    simulatorUnpackTexPalette((TEXPalettePtr)gfatalErr);
    simulatorUnpackTexPalette((TEXPalettePtr)gwrongDisk);
    simulatorUnpackTexPalette((TEXPalettePtr)greadingDisk);
    simulatorUnpackTexPalette((TEXPalettePtr)gbar);
    simulatorUnpackTexPalette((TEXPalettePtr)gyes);
    simulatorUnpackTexPalette((TEXPalettePtr)gno);
    simulatorUnpackTexPalette((TEXPalettePtr)gmesgOK);

    gbReset = 0;
    gnTickReset = OSGetTick();

    if (!xlHeapGetFree(&nSize0)) {
        return false;
    }

    mCard.bufferCreated = 0;
    mCard.isBroken = 0;
    mcardInit(&mCard);

    if (simulatorGetArgument(SAT_NAME, &szNameROM)) {
        strcpy(acNameROM, szNameROM);
    } else {
        strcpy(acNameROM, "zlj_f.n64");
    }

    iName = strlen(acNameROM) - 1;
    while (iName >= 0 && acNameROM[iName] != '.') {
        iName--;
    }

    if (iName < 0) {
        iName = strlen(acNameROM);
        acNameROM[iName + 0] = '.';
        acNameROM[iName + 1] = 'N';
        acNameROM[iName + 2] = '6';
        acNameROM[iName + 3] = '4';
        acNameROM[iName + 4] = '\0';
    }

    gpSystem = NULL;

    if (!xlObjectMake(&gpCode, NULL, &gClassCode)) {
        return false;
    }
    if (!xlObjectMake(&gpFrame, NULL, &gClassFrame)) {
        return false;
    }
    if (!xlObjectMake(&gpSound, NULL, &gClassSound)) {
        return false;
    }
    if (!xlObjectMake(&gpSystem, NULL, &gClassSystem)) {
        return false;
    }

    if (!xlFileSetOpen(&simulatorDVDOpen)) {
        return false;
    }
    if (!xlFileSetRead(&simulatorDVDRead)) {
        return false;
    }

    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_ACCEPT, "yes.raw");
    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_DECLINE, "no.raw");
    soundLoadBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_SELECT, "cursor.raw");

    if (!romSetImage(SYSTEM_ROM(gpSystem), acNameROM)) {
        return false;
    }
    if (!systemReset(gpSystem)) {
        return false;
    }
    if (!frameShow(gpFrame)) {
        return false;
    }
    if (!xlHeapGetFree(&nSize1)) {
        return false;
    }
    if (!systemSetMode(gpSystem, SM_RUNNING)) {
        return false;
    }

    simulatorRun(&eMode);

    if (!xlObjectFree(&gpSystem)) {
        return false;
    }
    if (!xlObjectFree(&gpSound)) {
        return false;
    }
    if (!xlObjectFree(&gpFrame)) {
        return false;
    }
    if (!xlObjectFree(&gpCode)) {
        return false;
    }

    return true;
}
