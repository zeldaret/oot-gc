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

// clang-format off
#include "gcoverOpen.inc"
#include "gnoDisk.inc"
#include "gretryErr.inc"
#include "gfatalErr.inc"
#include "gwrongDisk.inc"
#include "greadingDisk.inc"

#if IS_EU
#include "gyes.inc"
#include "gno.inc"
#include "gmesgOK.inc"
#include "gfrench_coverOpen.inc"
#include "gfrench_noDisk.inc"
#include "gfrench_retryErr.inc"
#include "gfrench_fatalErr.inc"
#include "gfrench_wrongDisk.inc"
#include "gfrench_readingDisk.inc"
#include "gfrench_yes.inc"
#include "gfrench_no.inc"
#include "gfrench_mesgOK.inc"
#include "ggerman_coverOpen.inc"
#include "ggerman_noDisk.inc"
#include "ggerman_retryErr.inc"
#include "ggerman_fatalErr.inc"
#include "ggerman_wrongDisk.inc"
#include "ggerman_readingDisk.inc"
#include "ggerman_yes.inc"
#include "ggerman_no.inc"
#include "ggerman_mesgOK.inc"

#if VERSION == CE_E
#include "gspanish_coverOpen.inc"
#include "gspanish_noDisk.inc"
#include "gspanish_retryErr.inc"
#include "gspanish_fatalErr.inc"
#include "gspanish_wrongDisk.inc"
#include "gspanish_readingDisk.inc"
#include "gspanish_yes.inc"
#include "gspanish_no.inc"
#include "gspanish_mesgOK.inc"
#include "gitalian_coverOpen.inc"
#include "gitalian_noDisk.inc"
#include "gitalian_retryErr.inc"
#include "gitalian_fatalErr.inc"
#include "gitalian_wrongDisk.inc"
#include "gitalian_readingDisk.inc"
#include "gitalian_yes.inc"
#include "gitalian_no.inc"
#include "gitalian_mesgOK.inc"
#endif

#include "gbar.inc"

#else

#include "gbar.inc"
#include "gyes.inc"
#include "gno.inc"
#include "gmesgOK.inc"

#endif
// clang-format on

#if VERSION == MQ_J
#define DEFAULT_ROM_NAME "urazlj_f.n64"
#elif VERSION == MQ_U
#define DEFAULT_ROM_NAME "urazle_f.n64"
#elif VERSION == CE_J || IS_EU
#define DEFAULT_ROM_NAME "zlj_f.n64"
#elif VERSION == CE_U
#define DEFAULT_ROM_NAME "zle_f.n64"
#endif

s16 Vert_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 VertTitle_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 VertYes_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 VertNo_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 Vert_s16Bar[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

// rgba
u32 Colors_u32[3] ATTRIBUTE_ALIGN(32) = {
    0x000000FF,
    0x000000FF,
    0x000000FF,
};

u8 TexCoords_u8[] ATTRIBUTE_ALIGN(32) = {
    0, 0, 1, 0, 1, 1, 0, 1,
};

static f32 gOrthoMtx[4][4] ATTRIBUTE_ALIGN(32);
static u32 gContMap[4][GCN_BTN_COUNT];
static char* gaszArgument[8];

u32 gmsg_ld01Size = 0x3E20;
u32 gmsg_ld02Size = 0x3E20;
u32 gmsg_ld03Size = 0x3E20;
u32 gmsg_ld04Size = 0x3E20;
u32 gmsg_ld05_1Size = 0x3E20;
u32 gmsg_ld05_2Size = 0x3E20;
u32 gmsg_ld06_1Size = 0x3E20;
u32 gmsg_ld06_2Size = 0x3E20;
u32 gmsg_ld06_3Size = 0x3E20;
u32 gmsg_ld06_4Size = 0x3E20;
u32 gmsg_ld07Size = 0x3E20;
u32 gmsg_gf01Size = 0x3E20;
u32 gmsg_gf02Size = 0x3E20;
u32 gmsg_gf03Size = 0x3E20;
u32 gmsg_gf04Size = 0x3E20;
u32 gmsg_gf05Size = 0x3E20;
u32 gmsg_gf06Size = 0x3E20;
u32 gmsg_in01Size = 0x3E20;
u32 gmsg_in02Size = 0x3E20;
u32 gmsg_in03Size = 0x3E20;
u32 gmsg_in04Size = 0x3E20;
u32 gmsg_in05Size = 0x3E20;
u32 gmsg_sv01Size = 0x3E20;
u32 gmsg_sv01_2Size = 0x3E20;
u32 gmsg_sv02Size = 0x3E20;
u32 gmsg_sv03Size = 0x3E20;
u32 gmsg_sv04Size = 0x3E20;
u32 gmsg_sv05_1Size = 0x3E20;
u32 gmsg_sv06_1Size = 0x3E20;
u32 gmsg_sv06_2Size = 0x3E20;
u32 gmsg_sv06_3Size = 0x3E20;
u32 gmsg_sv06_4Size = 0x3E20;
u32 gmsg_sv06_5Size = 0x3E20;
u32 gmsg_sv07Size = 0x3E20;
u32 gmsg_sv08Size = 0x3E20;
u32 gmsg_sv09Size = 0x3E20;
u32 gmsg_sv10Size = 0x3E20;
u32 gmsg_sv11Size = 0x3E20;
u32 gmsg_sv12Size = 0x3E20;
u32 gmsg_sv_shareSize = 0x3E20;
u32 gz_bnrSize = 0x1840;
u32 gz_iconSize = 0x1840;

bool gHighlightChoice = true;
SimulatorMessage simulatorMessageCurrent = S_M_NONE;
bool gResetBeginFlag = true;

static Code* gpCode;

void* gpFrame;
void* gpSound;
System* gpSystem;

char gpErrorMessageBuffer[20480];
bool gbDisplayedError;

#if VERSION != MQ_J
bool gPreviousAllowResetSetting;
bool gPreviousForceMenuSetting;
bool gPreviousIPLSetting;
#endif

u32 gnTickReset;
bool gbReset;

bool simulatorGXInit(void) {
    s32 i;
    GXColor GX_DEFAULT_BG = {0};
    GXColor BLACK = {0};
    GXColor WHITE = {0};
    Mtx identity_mtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

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

    GXLoadPosMtxImm(identity_mtx, GX_PNMTX0);
    GXLoadNrmMtxImm(identity_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);

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

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
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

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, BLACK);
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
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
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

void simulatorUnpackTexPalette(TEXPalette* pal) {
    u16 i;

    pal->descriptorArray = (TEXDescriptor*)((char*)pal->descriptorArray + (u32)pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader) {
            pal->descriptorArray[i].textureHeader =
                (TEXHeader*)((char*)pal + (u32)pal->descriptorArray[i].textureHeader);
            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                pal->descriptorArray[i].textureHeader->data =
                    (char*)pal + (u32)pal->descriptorArray[i].textureHeader->data;
                pal->descriptorArray[i].textureHeader->unpacked = true;
            }
        }
        if (pal->descriptorArray[i].CLUTHeader) {
            pal->descriptorArray[i].CLUTHeader = (CLUTHeader*)((u8*)pal + (u32)pal->descriptorArray[i].CLUTHeader);
            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                pal->descriptorArray[i].CLUTHeader->data = (char*)pal + (u32)pal->descriptorArray[i].CLUTHeader->data;
                pal->descriptorArray[i].CLUTHeader->unpacked = true;
            }
        }
    }
}

bool gButtonDownToggle = false;
bool gDVDResetToggle = false;

bool simulatorDVDShowError(s32 nStatus, void* anData, s32 nSizeRead, u32 nOffset) {
    static bool toggle;

#if VERSION == MQ_J
#define continueToggle false
#else
    bool continueToggle;
#endif

    SimulatorMessage nMessage = S_M_NONE;

    do {

#if VERSION != MQ_J
        if ((nStatus != 1) && (nStatus != 0) && (nStatus != 2) && (nStatus != 3) && (nStatus != 7) && (nStatus != 8) &&
            (nStatus != 10)) {
            continueToggle = true;
        } else {
            continueToggle = false;
        }
#endif

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
                xlPostText("ShowError: Unknown FileInfoStatus: %d", "simGCN.c",
                           VERSION == MQ_J ? 750
                           : IS_EU         ? 865
                                           : 763,
                           nStatus);
                break;
        }

        if ((nStatus != 1) && (nStatus != 0) && (nStatus != 2) && (nStatus != 3) && (nStatus != 7) && (nStatus != 8) &&
            (nStatus != 10)) {
            toggle = true;
        } else if (toggle == true) {
            toggle = false;
            nMessage = S_M_DISK_READING_DISK;
        }

#if VERSION == MQ_J
        if (nStatus == 5) {
            if (!simulatorTestReset(true, true, true)) {
                return false;
            }
        } else if (nStatus != -1) {
            if (gDVDResetToggle == 1 && (((u32)nStatus <= 3) || (((u32)nStatus - 7) <= 1) || (nStatus == 10))) {
                if (!simulatorTestReset(false, false, true)) {
                    return false;
                }
            } else if (!simulatorTestReset(true, false, true)) {
                return false;
            }
        }
#else
        if ((gDVDResetToggle == 1) && ((nStatus <= 3U) || ((nStatus - 7) <= 1U) || (nStatus == 10))) {
            if (!simulatorTestReset(false, false, true, false)) {
                return false;
            }
        } else if ((nStatus != -1) && (!simulatorTestReset(true, false, true, false))) {
            return false;
        }
#endif

        if (nMessage != S_M_NONE) {
            while (!(frameBeginOK(gpSystem->pFrame))) {}
            PADControlMotor(0, PAD_MOTOR_STOP);
            simulatorDrawErrorMessage(nMessage, false, 0);
        }

#if VERSION != MQ_J
        nStatus = DVDGetDriveStatus();
#endif

    } while (continueToggle == true);

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

            while ((nStatus = DVDGetCommandBlockStatus(&pFileInfo->cb)) != DVD_STATE_END) {
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
        DVDReadAsync(pFileInfo, anData, nSizeRead, nOffset, callback);
        return true;
    }

    return true;
}

bool simulatorPlayMovie(void) {
    simulatorResetAndPlayMovie();
    return true;
}

bool simulatorDrawImage(TEXPalette* tpl, s32 nX0, s32 nY0, bool drawBar, s32 percent) {
    GXTexObj texObj;
    GXTexObj texObj2;
    u32 pad2;
    GXColor color;
    Mtx identity_mtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };
    Mtx g2DviewMtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };

    Mtx g2;

    while (frameBeginOK(gpFrame) != true) {}

    simulatorGXInit();
    xlCoreBeforeRender();
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.1f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2, GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

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
    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.1f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2, g2, 0.5f, 0.5f, 1.0f);
    GXLoadPosMtxImm(g2, GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);
    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXLoadTexObj(&texObj, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

    if (drawBar == true) {
        GXLoadPosMtxImm(g2DviewMtx, false);

        Vert_s16Bar[0] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[1] = (nY0 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[3] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[4] = (nY0 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[6] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[7] = (nY0 + tpl->descriptorArray->textureHeader->height +
                          ((TEXPalette*)gbar)->descriptorArray->textureHeader->height);
        Vert_s16Bar[9] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[10] = (nY0 + tpl->descriptorArray->textureHeader->height +
                           ((TEXPalette*)gbar)->descriptorArray->textureHeader->height);

        DCStoreRange(Vert_s16Bar, sizeof(Vert_s16Bar));
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        GXSetArray(GX_VA_POS, Vert_s16Bar, 6);
        GXSetArray(GX_VA_CLR0, Colors_u32, 4);
        GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        TEXGetGXTexObjFromPalette((TEXPalette*)gbar, &texObj2, 0);
        GXLoadTexObj(&texObj2, GX_TEXMAP0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition1x8(0);
        GXColor1x8(0);
        GXTexCoord1x8(0);
        GXPosition1x8(1);
        GXColor1x8(1);
        GXTexCoord1x8(1);
        GXPosition1x8(2);
        GXColor1x8(2);
        GXTexCoord1x8(2);
        GXPosition1x8(3);
        GXColor1x8(3);
        GXTexCoord1x8(3);
        GXEnd();
    }
    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetColorUpdate(GX_ENABLE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
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
    return true;
}

bool simulatorDrawYesNoImage(TEXPalette* tplMessage, s32 nX0Message, s32 nY0Message, TEXPalette* tplYes, s32 nX0Yes,
                             s32 nY0Yes, TEXPalette* tplNo, s32 nX0No, s32 nY0No) {

    GXTexObj texObj;
    u32 pad;
    GXColor color0;
    GXColor color1;

    Mtx identity_mtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };
    Mtx g2DviewMtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };

    while (frameBeginOK(gpFrame) != true) {}

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

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.1f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2DviewMtx, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2DviewMtx, g2DviewMtx, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2DviewMtx, GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);

    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);

    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette(tplMessage, &texObj, 0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    xlCoreBeforeRender();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette(tplYes, &texObj, 0);
    GXLoadTexObj(&texObj, 0);

    if (gHighlightChoice == 1) {
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
    } else {
        GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    }

    xlCoreBeforeRender();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0);
    TEXGetGXTexObjFromPalette(tplNo, &texObj, 0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    if (gHighlightChoice == true) {
        GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    } else {
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

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetColorUpdate(GX_ENABLE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
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

    return true;
}

bool simulatorDrawOKImage(TEXPalette* tplMessage, s32 nX0Message, s32 nY0Message, TEXPalette* tplOK, s32 nX0OK,
                          s32 nY0OK) {
    GXTexObj texObj;
    GXColor color0;
    GXColor color1;
    u32 pad;
    Mtx identity_mtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };
    Mtx g2DviewMtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };

    while (frameBeginOK(gpFrame) != true) {}

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

    C_MTXOrtho(gOrthoMtx, 0.0f, N64_FRAME_HEIGHT, 0.0f, N64_FRAME_WIDTH, 0.1f, 10000.0f);
    GXSetProjection(gOrthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);

    PSMTXTransApply(g2DviewMtx, g2DviewMtx, N64_FRAME_WIDTH / 2, N64_FRAME_HEIGHT / 2, 0.0f);
    PSMTXScaleApply(g2DviewMtx, g2DviewMtx, 0.5f, 0.5f, 1.0f);

    GXLoadPosMtxImm(g2DviewMtx, GX_PNMTX0);
    GXLoadTexMtxImm(identity_mtx, GX_IDENTITY, GX_MTX3x4);

    GXSetNumChans(1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);

    GXSetArray(GX_VA_POS, Vert_s16, 6);
    GXSetArray(GX_VA_CLR0, Colors_u32, 4);
    GXSetArray(GX_VA_TEX0, TexCoords_u8, 2);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    TEXGetGXTexObjFromPalette(tplMessage, &texObj, 0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetTevOp(GX_TEVSTAGE0, GX_DECAL);
    xlCoreBeforeRender();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
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
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXLoadTexObj(&texObj, 0);
    xlCoreBeforeRender();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXTexCoord1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXTexCoord1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXTexCoord1x8(2);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXTexCoord1x8(3);
    GXEnd();

    if (DemoStatEnable != 0) {
        GXDrawDone();
        DEMOUpdateStats(1);
        DEMOPrintStats();
        GXDrawDone();
        DEMOUpdateStats(0);
    }
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetColorUpdate(GX_ENABLE);
    GXCopyDisp(DemoCurrentBuffer, GX_TRUE);
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

    return true;
}

bool simulatorDrawErrorMessage(SimulatorMessage simulatorErrorMessage, bool drawBar, s32 percent) {
    PADControlMotor(0, PAD_MOTOR_STOP);

    switch (simulatorErrorMessage) {
        case S_M_DISK_COVER_OPEN:
            simulatorDrawImage(
                (TEXPalette*)gcoverOpen,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)gcoverOpen)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gcoverOpen)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_WRONG_DISK:
            simulatorDrawImage(
                (TEXPalette*)gwrongDisk,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)gwrongDisk)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gwrongDisk)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_READING_DISK:
            simulatorDrawImage(
                (TEXPalette*)greadingDisk,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)greadingDisk)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)greadingDisk)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_RETRY_ERROR:
            simulatorDrawImage(
                (TEXPalette*)gretryErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)gretryErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gretryErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_FATAL_ERROR:
            simulatorDrawImage(
                (TEXPalette*)gfatalErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)gfatalErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gfatalErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        case S_M_DISK_NO_DISK:
            simulatorDrawImage((TEXPalette*)gnoDisk,
                               N64_FRAME_WIDTH / 2 - ((TEXPalette*)gnoDisk)->descriptorArray->textureHeader->width / 2,
                               N64_FRAME_HEIGHT / 2 -
                                   ((TEXPalette*)gnoDisk)->descriptorArray->textureHeader->height / 2,
                               drawBar, percent);
            break;
        case S_M_DISK_DEFAULT_ERROR:
            simulatorDrawImage(
                (TEXPalette*)gfatalErr,
                N64_FRAME_WIDTH / 2 - ((TEXPalette*)gfatalErr)->descriptorArray->textureHeader->width / 2,
                N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gfatalErr)->descriptorArray->textureHeader->height / 2, drawBar,
                percent);
            break;
        default:
            break;
    }
    gbDisplayedError = true;
    return true;
}

bool simulatorPrepareMessage(SimulatorMessage simulatorErrorMessage) {
    DVDFileInfo fileInfo;
    switch (simulatorErrorMessage) {
        case S_M_CARD_IN02:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_in02Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            break;

        case S_M_CARD_SV09:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv09.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv09Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            break;

        case S_M_CARD_GF02:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf02Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            break;

        default:
            break;
    }
    return true;
}

bool simulatorDrawYesNoMessageLoop(TEXPalette* simulatorQuestion, bool* yes) {
    TEXDescriptor** pNo;
    TEXDescriptor** pYes;
    TEXDescriptor** pQuestion;
    s32 pad[2];

    if (*yes == true) {
        gHighlightChoice = true;
    } else {
        gHighlightChoice = false;
    }

    pNo = &((TEXPalette*)gno)->descriptorArray;
    pYes = &((TEXPalette*)gyes)->descriptorArray;
    pQuestion = &simulatorQuestion->descriptorArray;
    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - (*pYes)->textureHeader->width / 2, 180 - (*pYes)->textureHeader->height / 2,
                            (TEXPalette*)gno, 200 - (*pNo)->textureHeader->width / 2,
                            180 - (*pNo)->textureHeader->height / 2);

    if (gButtonDownToggle == true) {
        DEMOPadRead();
        if (DemoPad->pst.button != 0) {
            return false;
        }
    }

    gButtonDownToggle = false;
    DEMOPadRead();
    if (*yes == true) {
        gHighlightChoice = true;
    } else {
        gHighlightChoice = false;
    }

    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - (*pYes)->textureHeader->width / 2, 180 - (*pYes)->textureHeader->height / 2,
                            (TEXPalette*)gno, 200 - (*pNo)->textureHeader->width / 2,
                            180 - (*pNo)->textureHeader->height / 2);

    if (DemoPad->pst.err == 0) {
        if (DemoPad->pst.button & 0x1100) {
            if (*yes == true) {
                soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_ACCEPT);
            } else {
                soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_DECLINE);
            }
            gButtonDownToggle = true;
            return true;
        }
        if (DemoPad->pst.button & 0x200) {
            soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_DECLINE);
            gButtonDownToggle = true;
            *yes = false;
            return true;
        }
        if (DemoPad->pst.stickX < 0 && *yes == false) {
            soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_SELECT);
            *yes = true;
        } else if (DemoPad->pst.stickX > 0 && *yes == true) {
            soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_SELECT);
            *yes = false;
        }
    }

    return false;
}

bool simulatorDrawYesNoMessage(SimulatorMessage simulatorMessage, bool* yes) {
    DVDFileInfo fileInfo;
    switch (simulatorMessage) {
        case S_M_CARD_LD05_2:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld05_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld05_2Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD06_4:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld06_4.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld06_4Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD07:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_ld07.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld07Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_GF01:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_gf01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf01Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_IN01:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_in01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_in01Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV06_4:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv06_4.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv06_4Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV06_5:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv06_5.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv06_5Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV08:
            if (simulatorMessageCurrent != simulatorMessage) {
                simulatorMessageCurrent = simulatorMessage;
                if (DVDOpen("TPL/msg_sv08.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv08Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        default:
            break;
    }

    return false;
}

#if IS_EU
static bool simulatorDrawOKMessageLoop(TEXPalette* simulatorMessage)
#else
static inline bool simulatorDrawOKMessageLoop(TEXPalette* simulatorMessage)
#endif
{
    simulatorDrawOKImage(
        (TEXPalette*)gpErrorMessageBuffer,
        N64_FRAME_WIDTH / 2 - ((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2,
        simulatorMessage, N64_FRAME_WIDTH / 2 - simulatorMessage->descriptorArray->textureHeader->width / 2,
        180 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->height / 2); // bug, copy paste error?

    if (gButtonDownToggle == true) {
        DEMOPadRead();
        if (DemoPad->pst.button != 0) {
            return false;
        }
    }

    gButtonDownToggle = false;
    DEMOPadRead();

    simulatorDrawOKImage(
        (TEXPalette*)gpErrorMessageBuffer,
        N64_FRAME_WIDTH / 2 - ((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2,
        N64_FRAME_HEIGHT / 2 - ((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2,
        simulatorMessage, N64_FRAME_WIDTH / 2 - simulatorMessage->descriptorArray->textureHeader->width / 2,
        180 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->height / 2); // bug, copy paste error?

    if ((DemoPad->pst.err == PAD_ERR_NONE) && (DemoPad->pst.button & (PAD_BUTTON_START | PAD_BUTTON_A))) {
        soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_ACCEPT);
        gButtonDownToggle = true;
        return true;
    }

    PAD_STACK();

    //! PAL TODO: check if this is really needed
#if IS_EU
    NO_INLINE();
#endif
    return false;
}

bool simulatorDrawErrorMessageWait(SimulatorMessage simulatorErrorMessage) {
    DVDFileInfo fileInfo;

    switch (simulatorErrorMessage) {
        case S_M_CARD_LD01:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld01Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD02:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld02Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD03:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld03Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD04:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld04Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD05_1:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld05_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld05_1Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD06_1:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld06_1Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD06_2:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld06_2Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_LD06_3:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_ld06_3.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_ld06_3Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_GF03:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf03Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_GF04:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf04Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_GF05:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf05.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf05Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_GF06:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_gf06.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_gf06Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_IN03:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_in03Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_IN04:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_in04Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_IN05:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_in05.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_in05Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV01:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv01.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv01Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV01_2:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv01_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv01_2Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV02:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv02.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv02Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV03:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv03.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv03Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV04:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv04.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv04Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV05_1:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv05_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv05_1Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV06_1:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_1.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv06_1Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV06_2:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_2.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv06_2Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV06_3:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv06_3.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv06_3Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV07:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv07.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv07Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV10:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv10.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv10Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV11:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv11.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv11Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV12:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv12.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv12Size), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        case S_M_CARD_SV_SHARE:
            if (simulatorMessageCurrent != simulatorErrorMessage) {
                simulatorMessageCurrent = simulatorErrorMessage;
                if (DVDOpen("TPL/msg_sv_share.tpl", &fileInfo) == 1) {
                    simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(gmsg_sv_shareSize), 0, NULL);
                }
                DVDClose(&fileInfo);
                simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);
            }
            return simulatorDrawOKMessageLoop((TEXPalette*)gmesgOK);
        default:
            break;
    }

    return false;
}

static inline void simulatorResetInit(void) {
    mcardWriteGameDataReset(&mCard);
    VISetBlack(true);
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

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetColorUpdate(GX_ENABLE);
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
    s32 result;

    if ((stickValue >= 0 && stickValue < 40) || (stickValue < 0 && stickValue > -40)) {
        result = (stickValue * 67) / 40;
    } else if (stickValue >= 40 && stickValue < 72) {
        result = ((72 - stickValue) * 67) / 32 + ((stickValue - 40) * 90) / 32;
    } else if (stickValue <= -40 && stickValue > -72) {
        result = ((-40 - stickValue) * -90) / 32 + ((stickValue + 72) * -67) / 32;
    } else if (stickValue >= 72) {
        result = 90;
    } else {
        result = -90;
    }

    *val = result;
}

bool simulatorReadController(s32 channel, u32* anData, u8* ptx) {
    static u32 nPrevButton;
    static u32 nCurrButton;

    f32 subStickTest;
    s32 stickX;
    s32 stickY;
    s32 subStickX;
    s32 subStickY;
    s32 nDirButton;

    nPrevButton = nCurrButton;

    DEMOPadRead();

    *anData = 0;

    if (DemoPad[channel].pst.err == PAD_ERR_NONE) {
        UnkInlineReadController(DemoPad[channel].pst.stickX, &stickX);
        *anData |= (stickX & 0xFF) << 8;
        UnkInlineReadController(DemoPad[channel].pst.stickY, &stickY);
        *anData |= stickY & 0xFF;

        nDirButton = DemoPad[channel].dirs;
        subStickX = DemoPad[channel].pst.substickX;
        subStickY = DemoPad[channel].pst.substickY;
        if (gButtonDownToggle == true) {
            if (DemoPad->pst.button != 0) {
                return true;
            } else {
                gButtonDownToggle = false;
            }
        }
        nCurrButton = DemoPad[channel].pst.button;

        if ((nCurrButton & (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) ==
            (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) {
            gButtonDownToggle = true;
            return true;
        }
        if ((subStickX != 0) && (subStickY != 0)) {
            subStickTest = (f32)subStickX / (f32)subStickY;
        } else {
            subStickTest = 0.0f;
        }
        if (subStickTest < 0.0f) {
            subStickTest *= -1.0f;
        }
        if ((subStickTest > 1.1f) || (subStickTest < (1.0f / 1.1f))) {
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
        if (nCurrButton & PAD_BUTTON_START) {
            *anData |= gContMap[channel][GCN_BTN_START];
        }
        if (nCurrButton & PAD_TRIGGER_Z) {
            *anData |= gContMap[channel][GCN_BTN_Z];
        }
        if (DemoPad[channel].pst.triggerRight > 30) {
            *anData |= gContMap[channel][GCN_BTN_R];
        }
        if (DemoPad[channel].pst.triggerLeft > 30) {
            *anData |= gContMap[channel][GCN_BTN_L];
        }
        if (nCurrButton & PAD_BUTTON_A) {
            *anData |= gContMap[channel][GCN_BTN_A];
        }
        if (nCurrButton & PAD_BUTTON_B) {
            *anData |= gContMap[channel][GCN_BTN_B];
        }
        if (nCurrButton & PAD_BUTTON_X) {
            *anData |= gContMap[channel][GCN_BTN_X];
        }
        if (nCurrButton & PAD_BUTTON_Y) {
            *anData |= gContMap[channel][GCN_BTN_Y];
            return true;
        }
        if (nCurrButton & PAD_BUTTON_UP) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_UP];
        }
        if (nCurrButton & PAD_BUTTON_DOWN) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_DOWN];
        }
        if (nCurrButton & PAD_BUTTON_LEFT) {
            *anData |= gContMap[channel][GCN_BTN_DPAD_LEFT];
        }
        if (nCurrButton & PAD_BUTTON_RIGHT) {
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
    PADControlMotor(channel, PAD_MOTOR_RUMBLE);
    return true;
}

bool simulatorRumbleStop(s32 channel) {
    PADControlMotor(channel, PAD_MOTOR_STOP);
    return true;
}

#if VERSION == MQ_J
bool simulatorTestReset(bool IPL, bool forceMenu, bool allowReset)
#define usePreviousSettings false
#else
bool simulatorTestReset(bool IPL, bool forceMenu, bool allowReset, bool usePreviousSettings)
#endif
{
    u32 bFlag;
    u32 nTick;

#if VERSION == MQ_J
#define prevIPLSetting false
#define prevForceMenuSetting false
#define prevAllowResetSetting true
#else
    bool prevIPLSetting;
    bool prevForceMenuSetting;
    bool prevAllowResetSetting;
    s32 pad;
#endif

    nTick = OSGetTick();

#if VERSION != MQ_J
    prevAllowResetSetting = gPreviousAllowResetSetting;
    prevIPLSetting = gPreviousIPLSetting;
    prevForceMenuSetting = gPreviousForceMenuSetting;

    if (usePreviousSettings == true) {
        IPL = gPreviousIPLSetting;
        forceMenu = gPreviousForceMenuSetting;
        allowReset = gPreviousAllowResetSetting;
    } else {
        gPreviousIPLSetting = IPL;
        gPreviousForceMenuSetting = forceMenu;
        gPreviousAllowResetSetting = allowReset;
    }
#endif

    DEMOPadRead();
    bFlag = OSGetResetButtonState();

    if (gResetBeginFlag == true && (DemoPad[0].pst.button & (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) ==
                                       (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) {
        if (!gbReset || bFlag) {
            gbReset = bFlag;
            return true;
        }

        if (allowReset == true) {
            if (prevAllowResetSetting == true) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        gResetBeginFlag = false;
    }

    if ((DemoPad[0].pst.button & (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) !=
        (PAD_BUTTON_START | PAD_BUTTON_B | PAD_BUTTON_X)) {
        gnTickReset = nTick;
        if (!gbReset || bFlag) {
            gbReset = bFlag;
            return true;
        }

        if (allowReset == true) {
            if (prevAllowResetSetting == true) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    } else {
        if (nTick - gnTickReset >= OSSecondsToTicks(0.5f) && allowReset == true) {
            if (prevAllowResetSetting == true) {
                simulatorReset(IPL, forceMenu);
            } else {
                simulatorReset(prevIPLSetting, prevForceMenuSetting);
            }
        }
    }

    return true;
}

bool simulatorDrawMCardText(void) {
#if VERSION != MQ_J
    if ((s32)(((TEXPalette*)gpErrorMessageBuffer)->versionNumber) == 0) {
        //! TODO: this should be an inline function
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c",
                   VERSION == CE_E   ? 1924
                   : VERSION == MQ_E ? 1836
                                     : 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
#endif

    simulatorDrawImage((TEXPalette*)gpErrorMessageBuffer,
                       160 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
                       120 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2), false,
                       0);
    return true;
}

bool simulatorMCardPollDrawBar(void) {
    f32 rate;
    s32 nBytes;

    nBytes = CARDGetXferredBytes(mCard.slot) - mCard.pollPrevBytes;
    rate = nBytes / (f32)mCard.pollSize;

    rate = (rate > 1.0f) ? 1.0f : rate;
    rate = (rate < 0.0f) ? 0.0f : rate;

#if VERSION != MQ_J
    if ((s32)(((TEXPalette*)gpErrorMessageBuffer)->versionNumber) == 0) {
        //! TODO: this should be an inline function
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c",
                   VERSION == CE_E   ? 1924
                   : VERSION == MQ_E ? 1836
                                     : 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
#endif

    simulatorDrawImage((TEXPalette*)gpErrorMessageBuffer,
                       160 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
                       120 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2), true,
                       100.0f * rate);
    return true;
}

bool simulatorMCardPollDrawFormatBar(void) {
    f32 rate;
    s32 nBytes;

    nBytes = CARDGetXferredBytes(mCard.slot) - mCard.pollPrevBytes;
    rate = nBytes / (f32)mCard.pollSize;

    rate = (rate > 1.0f) ? 1.0f : rate;
    rate = (rate < 0.0f) ? 0.0f : rate;

#if VERSION != MQ_J
    if ((s32)(((TEXPalette*)gpErrorMessageBuffer)->versionNumber) == 0) {
        //! TODO: this should be an inline function
        xlPostText("Invalid Message Image Data - Assuming SV09", "simGCN.c",
                   VERSION == CE_E   ? 1924
                   : VERSION == MQ_E ? 1836
                                     : 1623);
        simulatorPrepareMessage(S_M_CARD_SV09);
    }
#endif

    simulatorDrawImage((TEXPalette*)gpErrorMessageBuffer,
                       160 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->width / 2),
                       120 - (((TEXPalette*)gpErrorMessageBuffer)->descriptorArray->textureHeader->height / 2), false,
                       100.0f * rate);
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
    GXPosition2s16(nX, nY);
    GXPosition2s16(nX + 8, nY + 4);
    GXPosition2s16(nX, nY + 8);
    GXEnd();

    return true;
}

static bool simulatorParseArguments(void) {
    s32 iArgument;
    char* szText;
    char* szValue;
    s32 pad1;
    s32 pad2;

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

bool simulatorGetArgument(SimulatorArgumentType eType, char** pszArgument) {
    if (eType != SAT_NONE && pszArgument != NULL && gaszArgument[eType] != NULL) {
        *pszArgument = gaszArgument[eType];
        return true;
    }

    return false;
}

static inline s32 simulatorRun(SystemMode* peMode) {
    // TODO: fake match?
    int nResult;

    while (systemGetMode(gpSystem, peMode) && *peMode == SM_RUNNING) {
        nResult = systemExecute(gpSystem, 100000);
        if (!nResult) {
            return nResult;
        }
    }

    return 1;
}

char _dummy0[] = "Play Delay";
char _dummy1[] = "Silence Count";
char _dummy2[] = "Fade Up Count";
char _dummy3[] = "How many audio frames the\ngame must be playing before it\nconsiders the sound stable";
char _dummy4[] = "How many audio frames the\ngame must NOT play before it\nconsiders itself unstable";
char _dummy5[] = "How many audio frames to\nperform a fade up on the audio";

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

    // Necessary to match .sdata2 usage order
    (void)0.0f;
    (void)1.0f;
    (void)0.1f;

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
    color.a = 255;

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
    VISetBlack(false);
    VIFlush();

#if IS_EU
    gLanguage = OSGetLanguage();

    switch (gLanguage) {
        case 0:
            simulatorUnpackTexPalette((TEXPalette*)gcoverOpen);
            simulatorUnpackTexPalette((TEXPalette*)gnoDisk);
            simulatorUnpackTexPalette((TEXPalette*)gretryErr);
            simulatorUnpackTexPalette((TEXPalette*)gfatalErr);
            simulatorUnpackTexPalette((TEXPalette*)gwrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)greadingDisk);
            simulatorUnpackTexPalette((TEXPalette*)gbar);
            simulatorUnpackTexPalette((TEXPalette*)gyes);
            simulatorUnpackTexPalette((TEXPalette*)gno);
            simulatorUnpackTexPalette((TEXPalette*)gmesgOK);
            break;
        case 1:
            simulatorUnpackTexPalette((TEXPalette*)ggerman_coverOpen);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_noDisk);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_retryErr);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_fatalErr);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_wrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_readingDisk);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_bar);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_yes);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_no);
            simulatorUnpackTexPalette((TEXPalette*)ggerman_mesgOK);
            break;
        case 2:
            simulatorUnpackTexPalette((TEXPalette*)gfrench_coverOpen);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_noDisk);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_retryErr);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_fatalErr);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_wrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_readingDisk);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_bar);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_yes);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_no);
            simulatorUnpackTexPalette((TEXPalette*)gfrench_mesgOK);
            break;
#if VERSION == CE_E
        case 3:
            simulatorUnpackTexPalette((TEXPalette*)gspanish_coverOpen);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_noDisk);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_retryErr);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_fatalErr);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_wrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_readingDisk);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_bar);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_yes);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_no);
            simulatorUnpackTexPalette((TEXPalette*)gspanish_mesgOK);
            break;
        case 4:
            simulatorUnpackTexPalette((TEXPalette*)gitalian_coverOpen);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_noDisk);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_retryErr);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_fatalErr);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_wrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_readingDisk);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_bar);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_yes);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_no);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_mesgOK);
            break;
#endif
        default:
            simulatorUnpackTexPalette((TEXPalette*)gcoverOpen);
            simulatorUnpackTexPalette((TEXPalette*)gnoDisk);
            simulatorUnpackTexPalette((TEXPalette*)gretryErr);
            simulatorUnpackTexPalette((TEXPalette*)gfatalErr);
            simulatorUnpackTexPalette((TEXPalette*)gwrongDisk);
            simulatorUnpackTexPalette((TEXPalette*)greadingDisk);
            simulatorUnpackTexPalette((TEXPalette*)gbar);
            simulatorUnpackTexPalette((TEXPalette*)gyes);
            simulatorUnpackTexPalette((TEXPalette*)gno);
            simulatorUnpackTexPalette((TEXPalette*)gmesgOK);
            break;
    }
#else
    simulatorUnpackTexPalette((TEXPalette*)gcoverOpen);
    simulatorUnpackTexPalette((TEXPalette*)gnoDisk);
    simulatorUnpackTexPalette((TEXPalette*)gretryErr);
    simulatorUnpackTexPalette((TEXPalette*)gfatalErr);
    simulatorUnpackTexPalette((TEXPalette*)gwrongDisk);
    simulatorUnpackTexPalette((TEXPalette*)greadingDisk);
    simulatorUnpackTexPalette((TEXPalette*)gbar);
    simulatorUnpackTexPalette((TEXPalette*)gyes);
    simulatorUnpackTexPalette((TEXPalette*)gno);
    simulatorUnpackTexPalette((TEXPalette*)gmesgOK);
#endif

    gbReset = false;
    gnTickReset = OSGetTick();

    if (!xlHeapGetFree(&nSize0)) {
        return false;
    }

    mCard.bufferCreated = 0;
#if VERSION != MQ_J
    mCard.isBroken = 0;
#endif
    mcardInit(&mCard);

    if (simulatorGetArgument(SAT_NAME, &szNameROM)) {
        strcpy(acNameROM, szNameROM);
    } else {
        strcpy(acNameROM, DEFAULT_ROM_NAME);
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

    if (!xlObjectMake((void**)&gpCode, NULL, &gClassCode)) {
        return false;
    }
    if (!xlObjectMake((void**)&gpFrame, NULL, &gClassFrame)) {
        return false;
    }
    if (!xlObjectMake((void**)&gpSound, NULL, &gClassSound)) {
        return false;
    }
    if (!xlObjectMake((void**)&gpSystem, NULL, &gClassSystem)) {
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

    if (!xlObjectFree((void**)&gpSystem)) {
        return false;
    }
    if (!xlObjectFree((void**)&gpSound)) {
        return false;
    }
    if (!xlObjectFree((void**)&gpFrame)) {
        return false;
    }
    if (!xlObjectFree((void**)&gpCode)) {
        return false;
    }

    return true;
}
