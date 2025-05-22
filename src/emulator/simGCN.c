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
#include "emulator/snddvdtrk.h"
#include "emulator/soundGCN.h"
#include "emulator/system.h"
#include "emulator/xlCoreGCN.h"
#include "emulator/xlHeap.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "string.h"

// clang-format off
#if VERSION != MM_E
#include "gcoverOpen.inc"
#include "gnoDisk.inc"
#include "gretryErr.inc"
#include "gfatalErr.inc"
#include "gwrongDisk.inc"
#include "greadingDisk.inc"
#endif

#if IS_OOT_EU
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

#elif IS_MM_EU

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
#elif VERSION == MQ_E
#define DEFAULT_ROM_NAME "urazlp_f.n64"
#elif VERSION == CE_J || IS_MQ_EU
#define DEFAULT_ROM_NAME "zlj_f.n64"
#elif VERSION == CE_U
#define DEFAULT_ROM_NAME "zle_f.n64"
#elif VERSION == CE_E
#define DEFAULT_ROM_NAME "zlp_f.n64"
#elif IS_MM_JP
#define DEFAULT_ROM_NAME "zelda2j.n64"
#elif IS_MM_US
#define DEFAULT_ROM_NAME "zelda2e.n64"
#elif IS_MM_EU
#define DEFAULT_ROM_NAME "zelda2p.n64"
#endif

s16 Vert_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

#if IS_OOT
s16 VertTitle_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 VertYes_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};

s16 VertNo_s16[12] ATTRIBUTE_ALIGN(32) = {
    0, 0, -1, 200, 0, -1, 200, 200, -1, 0, 200, -1,
};
#endif

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

#if IS_EU
u8 gLanguage = 0;
#endif

#if IS_MM_EU
u8* gcoverOpen = NULL;
u8* gnoDisk = NULL;
u8* gretryErr = NULL;
u8* gfatalErr = NULL;
u8* gwrongDisk = NULL;
u8* greadingDisk = NULL;
u8* gyes = NULL;
u8* gno = NULL;
u8* gmesgOK = NULL;
#endif

Frame* gpFrame;
Sound* gpSound;
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

#if IS_MM || IS_OOT_EU
#define TPL_DIR

#define simulatorOpenMessage(msg, fileName, size, fileInfo, buffer)                             \
    {                                                                                           \
        if (simulatorMessageCurrent != msg) {                                                   \
            simulatorMessageCurrent = msg;                                                      \
            strcat(buffer, fileName);                                                           \
            if (DVDOpen(buffer, &fileInfo) == 1) {                                              \
                simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(size), 0, NULL); \
            }                                                                                   \
            DVDClose(&fileInfo);                                                                \
            simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);                       \
        }                                                                                       \
    }
#else
#define TPL_DIR "TPL/"

#define simulatorOpenMessage(msg, fileName, size, fileInfo, buffer)                             \
    {                                                                                           \
        if (simulatorMessageCurrent != msg) {                                                   \
            simulatorMessageCurrent = msg;                                                      \
            if (DVDOpen(fileName, &fileInfo) == 1) {                                            \
                simulatorDVDRead(&fileInfo, gpErrorMessageBuffer, OSRoundUp32B(size), 0, NULL); \
            }                                                                                   \
            DVDClose(&fileInfo);                                                                \
            simulatorUnpackTexPalette((TEXPalette*)gpErrorMessageBuffer);                       \
        }                                                                                       \
    }
#endif

#if IS_OOT
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
#endif

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

static void simulatorDEMOSwapBuffers(void) {
    if ((void*)DemoCurrentBuffer == (void*)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
    } else {
        DemoCurrentBuffer = DemoFrameBuffer1;
    }
}

void simulatorDEMODoneRender(void) {
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
    simulatorDEMOSwapBuffers();
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
                           VERSION == MQ_J                      ? 750
                           : VERSION == MQ_E                    ? 845
                           : VERSION == CE_E                    ? 865
                           : VERSION == MM_J || VERSION == MM_E ? 899
                           : VERSION == MM_U                    ? 885
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
        } else if (nStatus != -1) {
            if (!simulatorTestReset(true, false, true, false)) {
                return false;
            }
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
#if IS_OOT
    simulatorResetAndPlayMovie();
#else
    switch (gpSystem->eTypeROM) {
        case SRT_ZELDA1:
            simulatorResetAndPlayMovie();
            break;
        case SRT_ZELDA2:
            InitDVDTrackList();
            AddDVDTrack("/majora_audio.adp");
            PlayDVDTrack(0, -1, 0, 0);
            break;
    }
#endif
    return true;
}

#if IS_OOT
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

    simulatorDEMODoneRender();
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();
    return true;
}
#else
bool simulatorDrawImage(TEXPalette* tpl, s32 nX0, s32 nY0, bool drawBar, s32 percent) {
    static GXTexObj texObj;
    static GXTexObj texObj2;
    GXColor color;
    Mtx matrix;
    s32 width;
    s32 height;
    s32 pad;
    Mtx g2DviewMtx = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, -1.0f},
    };

    while (frameBeginOK(gpFrame) != true) {}

    xlCoreBeforeRender();
    frameDrawSetup2D(gpFrame);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);

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

    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tpl, &texObj, 0);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tpl->descriptorArray->textureHeader->width / 2;
    height = tpl->descriptorArray->textureHeader->height / 2;
    nX0 = (N64_FRAME_WIDTH - width) / 2;
    nY0 = (N64_FRAME_HEIGHT - height) / 2;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0, nY0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0 + width, nY0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0 + width, nY0 + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0, nY0 + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    if (drawBar == true) {
        GXLoadPosMtxImm(g2DviewMtx, false);

        Vert_s16Bar[0] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[1] = (nY0 - 20 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[3] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[4] = (nY0 - 20 + tpl->descriptorArray->textureHeader->height);
        Vert_s16Bar[6] = ((N64_FRAME_WIDTH / 2 - (((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2)) +
                          ((((TEXPalette*)gbar)->descriptorArray->textureHeader->width * percent) / 100));
        Vert_s16Bar[7] = (nY0 - 20 + tpl->descriptorArray->textureHeader->height +
                          ((TEXPalette*)gbar)->descriptorArray->textureHeader->height);
        Vert_s16Bar[9] = N64_FRAME_WIDTH / 2 - ((TEXPalette*)gbar)->descriptorArray->textureHeader->width / 2;
        Vert_s16Bar[10] = (nY0 - 20 + tpl->descriptorArray->textureHeader->height +
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

    gpFrame->nMode = 0;
    gpFrame->nModeVtx = -1;
    frameDrawReset(gpFrame, 0x5FFED);
    simulatorDEMODoneRender();

    PAD_STACK();
    return true;
}
#endif

#if IS_OOT
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

    simulatorDEMODoneRender();
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();
    PAD_STACK();
    return true;
}
#else
bool simulatorDrawYesNoImage(TEXPalette* tplMessage, s32 nX0Message, s32 nY0Message, TEXPalette* tplYes, s32 nX0Yes,
                             s32 nY0Yes, TEXPalette* tplNo, s32 nX0No, s32 nY0No) {
    static GXTexObj texObj1;
    static GXTexObj texObj2;
    static GXTexObj texObj3;
    GXColor color;
    Mtx matrix;
    s32 width;
    s32 height;

    while (frameBeginOK(gpFrame) != true) {}
    xlCoreBeforeRender();
    frameDrawSetup2D(gpFrame);
    GXSetZMode(0U, GX_LEQUAL, 0U);
    GXSetZCompLoc(1U);
    GXSetNumTevStages(1U);
    GXSetNumChans(1U);
    GXSetNumTexGens(0U);
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_F32, 0U);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    GXPixModeSync();
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tplMessage, &texObj1, 0);
    GXInitTexObjLOD(&texObj1, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj1, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tplMessage->descriptorArray->textureHeader->width / 2;
    height = tplMessage->descriptorArray->textureHeader->height / 2;
    nX0Message = ((N64_FRAME_WIDTH - width) / 2);
    nY0Message = ((N64_FRAME_HEIGHT - height - 20) / 2);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0Message, nY0Message, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0Message + width, nY0Message, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0Message + width, nY0Message + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0Message, nY0Message + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    if (gHighlightChoice == 1) {
        color.r = 255;
        color.g = 255;
        color.b = 0;
        color.a = 255;
    } else {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
    }

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tplYes, &texObj2, 0);
    GXInitTexObjLOD(&texObj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj2, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tplYes->descriptorArray->textureHeader->width / 2;
    height = tplYes->descriptorArray->textureHeader->height / 2;
    nX0Yes = nX0Message + (tplMessage->descriptorArray->textureHeader->width / 2 / 2) - width - 30;
    nY0Yes = nY0Message + tplMessage->descriptorArray->textureHeader->height / 2 + 10;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0Yes, nY0Yes, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0Yes + width, nY0Yes, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0Yes + width, nY0Yes + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0Yes, nY0Yes + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    if (gHighlightChoice == 1) {
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
    } else {
        color.r = 255;
        color.g = 255;
        color.b = 0;
        color.a = 255;
    }

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tplNo, &texObj3, 0);
    GXInitTexObjLOD(&texObj3, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj3, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tplNo->descriptorArray->textureHeader->width / 2;
    height = tplNo->descriptorArray->textureHeader->height / 2;
    nX0No = nX0Message + (tplMessage->descriptorArray->textureHeader->width / 2 / 2) + 30;
    nY0No = nY0Message + tplMessage->descriptorArray->textureHeader->height / 2 + 10;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0No, nY0No, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0No + width, nY0No, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0No + width, nY0No + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0No, nY0No + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    gpFrame->nMode = 0;
    gpFrame->nModeVtx = -1;
    frameDrawReset(gpFrame, 0x5FFED);
    simulatorDEMODoneRender();
    return true;
}
#endif

#if IS_OOT
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

    simulatorDEMODoneRender();
    frameDrawReset(gpFrame, 0x5FFED);

    PAD_STACK();
    return true;
}
#else
bool simulatorDrawOKImage(TEXPalette* tplMessage, s32 nX0Message, s32 nY0Message, TEXPalette* tplOK, s32 nX0OK,
                          s32 nY0OK) {
    static GXTexObj texObj1;
    static GXTexObj texObj2;
    static GXTexObj texObj3;

    GXColor color;
    Mtx matrix;
    s32 width;
    s32 height;

    while (frameBeginOK(gpFrame) != true) {}

    xlCoreBeforeRender();
    frameDrawSetup2D(gpFrame);
    GXSetZMode(0U, GX_LEQUAL, 0U);
    GXSetZCompLoc(1U);
    GXSetNumTevStages(1U);
    GXSetNumChans(1U);
    GXSetNumTexGens(0U);
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_F32, 0U);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, 0.0f, 0.0f);
    GXPosition3f32(N64_FRAME_WIDTH, N64_FRAME_HEIGHT, 0.0f);
    GXPosition3f32(0.0f, N64_FRAME_HEIGHT, 0.0f);
    GXEnd();

    GXPixModeSync();
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tplMessage, &texObj1, 0);
    GXInitTexObjLOD(&texObj1, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj1, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tplMessage->descriptorArray->textureHeader->width / 2;
    height = tplMessage->descriptorArray->textureHeader->height / 2;
    nX0Message = (N64_FRAME_WIDTH - width) / 2;
    nY0Message = (N64_FRAME_HEIGHT - height - 20) / 2;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0Message, nY0Message, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0Message + width, nY0Message, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0Message + width, nY0Message + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0Message, nY0Message + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    color.r = 255;
    color.g = 255;
    color.b = 0;
    color.a = 255;

    GXSetNumTevStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    PSMTXIdentity(matrix);
    GXLoadTexMtxImm(matrix, 0x1E, GX_MTX2x4);
    TEXGetGXTexObjFromPalette(tplOK, &texObj2, 0);
    GXInitTexObjLOD(&texObj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj2, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    width = tplOK->descriptorArray->textureHeader->width / 2;
    height = tplOK->descriptorArray->textureHeader->height / 2;
    nX0OK = (N64_FRAME_WIDTH - width) / 2;
    nY0OK = nY0Message + (tplMessage->descriptorArray->textureHeader->height / 2) + 20;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(nX0OK, nY0OK, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(nX0OK + width, nY0OK, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(nX0OK + width, nY0OK + height, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(nX0OK, nY0OK + height, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXPixModeSync();

    gpFrame->nMode = 0;
    gpFrame->nModeVtx = -1;
    frameDrawReset(gpFrame, 0x5FFED);
    simulatorDEMODoneRender();
    return true;
}
#endif

#define simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, coverOpen, wrongDisk, readingDisk,      \
                                      retryErr, fatalErr, noDisk)                                                      \
    {                                                                                                                  \
        switch (simulatorErrorMessage) {                                                                               \
            case S_M_DISK_COVER_OPEN:                                                                                  \
                simulatorDrawImage(                                                                                    \
                    coverOpen, N64_FRAME_WIDTH / 2 - coverOpen->descriptorArray->textureHeader->width / 2,             \
                    N64_FRAME_HEIGHT / 2 - coverOpen->descriptorArray->textureHeader->height / 2, drawBar, percent);   \
                break;                                                                                                 \
            case S_M_DISK_WRONG_DISK:                                                                                  \
                simulatorDrawImage(                                                                                    \
                    wrongDisk, N64_FRAME_WIDTH / 2 - wrongDisk->descriptorArray->textureHeader->width / 2,             \
                    N64_FRAME_HEIGHT / 2 - wrongDisk->descriptorArray->textureHeader->height / 2, drawBar, percent);   \
                break;                                                                                                 \
            case S_M_DISK_READING_DISK:                                                                                \
                simulatorDrawImage(                                                                                    \
                    readingDisk, N64_FRAME_WIDTH / 2 - readingDisk->descriptorArray->textureHeader->width / 2,         \
                    N64_FRAME_HEIGHT / 2 - readingDisk->descriptorArray->textureHeader->height / 2, drawBar, percent); \
                break;                                                                                                 \
            case S_M_DISK_RETRY_ERROR:                                                                                 \
                simulatorDrawImage(                                                                                    \
                    retryErr, N64_FRAME_WIDTH / 2 - retryErr->descriptorArray->textureHeader->width / 2,               \
                    N64_FRAME_HEIGHT / 2 - retryErr->descriptorArray->textureHeader->height / 2, drawBar, percent);    \
                break;                                                                                                 \
            case S_M_DISK_FATAL_ERROR:                                                                                 \
                simulatorDrawImage(                                                                                    \
                    fatalErr, N64_FRAME_WIDTH / 2 - fatalErr->descriptorArray->textureHeader->width / 2,               \
                    N64_FRAME_HEIGHT / 2 - fatalErr->descriptorArray->textureHeader->height / 2, drawBar, percent);    \
                break;                                                                                                 \
            case S_M_DISK_NO_DISK:                                                                                     \
                simulatorDrawImage(noDisk, N64_FRAME_WIDTH / 2 - noDisk->descriptorArray->textureHeader->width / 2,    \
                                   N64_FRAME_HEIGHT / 2 - noDisk->descriptorArray->textureHeader->height / 2, drawBar, \
                                   percent);                                                                           \
                break;                                                                                                 \
            case S_M_DISK_DEFAULT_ERROR:                                                                               \
                simulatorDrawImage(                                                                                    \
                    fatalErr, N64_FRAME_WIDTH / 2 - fatalErr->descriptorArray->textureHeader->width / 2,               \
                    N64_FRAME_HEIGHT / 2 - fatalErr->descriptorArray->textureHeader->height / 2, drawBar, percent);    \
                break;                                                                                                 \
            default:                                                                                                   \
                break;                                                                                                 \
        }                                                                                                              \
    }

bool simulatorDrawErrorMessage(SimulatorMessage simulatorErrorMessage, bool drawBar, s32 percent) {
    PADControlMotor(0, PAD_MOTOR_STOP);

#if IS_OOT_EU
    if (gLanguage == 1) {
        simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, ((TEXPalette*)ggerman_coverOpen),
                                      ((TEXPalette*)ggerman_wrongDisk), ((TEXPalette*)ggerman_readingDisk),
                                      ((TEXPalette*)ggerman_retryErr), ((TEXPalette*)ggerman_fatalErr),
                                      ((TEXPalette*)ggerman_noDisk));
    } else if (gLanguage == 2) {
        simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, ((TEXPalette*)gfrench_coverOpen),
                                      ((TEXPalette*)gfrench_wrongDisk), ((TEXPalette*)gfrench_readingDisk),
                                      ((TEXPalette*)gfrench_retryErr), ((TEXPalette*)gfrench_fatalErr),
                                      ((TEXPalette*)gfrench_noDisk));
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, ((TEXPalette*)gspanish_coverOpen),
                                      ((TEXPalette*)gspanish_wrongDisk), ((TEXPalette*)gspanish_readingDisk),
                                      ((TEXPalette*)gspanish_retryErr), ((TEXPalette*)gspanish_fatalErr),
                                      ((TEXPalette*)gspanish_noDisk));
    } else if (gLanguage == 4) {
        simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, ((TEXPalette*)gitalian_coverOpen),
                                      ((TEXPalette*)gitalian_wrongDisk), ((TEXPalette*)gitalian_readingDisk),
                                      ((TEXPalette*)gitalian_retryErr), ((TEXPalette*)gitalian_fatalErr),
                                      ((TEXPalette*)gitalian_noDisk));
#endif

    } else
#endif
    {
        simulatorDrawErrorMessageImpl(simulatorErrorMessage, drawBar, percent, ((TEXPalette*)gcoverOpen),
                                      ((TEXPalette*)gwrongDisk), ((TEXPalette*)greadingDisk), ((TEXPalette*)gretryErr),
                                      ((TEXPalette*)gfatalErr), ((TEXPalette*)gnoDisk));
    }

    gbDisplayedError = true;
    NO_INLINE();
    return true;
}

bool simulatorPrepareMessage(SimulatorMessage simulatorErrorMessage) {
    DVDFileInfo fileInfo;
#if VERSION == MM_J || VERSION == MM_U
    char buf[30] = "TPL/";
#elif IS_OOT_EU || IS_MM_EU
    char buf[30];

    if (gLanguage == 1) {
        strcpy(buf, "TPL/GERMAN/");
    } else if (gLanguage == 2) {
        strcpy(buf, "TPL/FRENCH/");
#if IS_MM_EU
    } else if (gLanguage == 3) {
        strcpy(buf, "TPL/SPANISH/");
#endif
    } else {
        strcpy(buf, "TPL/ENGLISH/");
    }
#endif

    switch (simulatorErrorMessage) {
        case S_M_CARD_IN02:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_in02.tpl", gmsg_in02Size, fileInfo, buf);
            break;

        case S_M_CARD_SV09:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv09.tpl", gmsg_sv09Size, fileInfo, buf);
            break;

        case S_M_CARD_GF02:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_gf02.tpl", gmsg_gf02Size, fileInfo, buf);
            break;

        default:
            break;
    }
    return true;
}

#define simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, yes, no)                                                 \
    {                                                                                                                 \
        simulatorDrawYesNoImage(simulatorQuestion,                                                                    \
                                N64_FRAME_WIDTH / 2 - simulatorQuestion->descriptorArray->textureHeader->width / 2,   \
                                N64_FRAME_HEIGHT / 2 - simulatorQuestion->descriptorArray->textureHeader->height / 2, \
                                yes, 120 - yes->descriptorArray->textureHeader->width / 2,                            \
                                180 - yes->descriptorArray->textureHeader->height / 2, no,                            \
                                200 - no->descriptorArray->textureHeader->width / 2,                                  \
                                180 - no->descriptorArray->textureHeader->height / 2);                                \
    }

bool simulatorDrawYesNoMessageLoop(TEXPalette* simulatorQuestion, bool* yes) {
#if IS_MM_EU
    TEXDescriptor** descriptor;
#elif !IS_OOT_EU
    TEXDescriptor** pNo;
    TEXDescriptor** pYes;
    TEXDescriptor** pQuestion;
#endif
    s32 pad[2];

    if (*yes == true) {
        gHighlightChoice = true;
    } else {
        gHighlightChoice = false;
    }

#if IS_OOT_EU
    if (gLanguage == 1) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)ggerman_yes), ((TEXPalette*)ggerman_no));
    } else if (gLanguage == 2) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gfrench_yes), ((TEXPalette*)gfrench_no));
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gspanish_yes), ((TEXPalette*)gspanish_no));
    } else if (gLanguage == 4) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gitalian_yes), ((TEXPalette*)gitalian_no));
#endif
    } else {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gyes), ((TEXPalette*)gno));
    }
#elif IS_MM_EU
    descriptor = &simulatorQuestion->descriptorArray;
    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*descriptor)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*descriptor)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->width / 2,
                            180 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->height / 2, (TEXPalette*)gno,
                            200 - ((TEXPalette*)gno)->descriptorArray->textureHeader->width / 2,
                            180 - ((TEXPalette*)gno)->descriptorArray->textureHeader->height / 2);
#else
    pNo = &((TEXPalette*)gno)->descriptorArray;
    pYes = &((TEXPalette*)gyes)->descriptorArray;
    pQuestion = &simulatorQuestion->descriptorArray;

    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - (*pYes)->textureHeader->width / 2, 180 - (*pYes)->textureHeader->height / 2,
                            (TEXPalette*)gno, 200 - (*pNo)->textureHeader->width / 2,
                            180 - (*pNo)->textureHeader->height / 2);
#endif

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

#if IS_OOT_EU
    if (gLanguage == 1) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)ggerman_yes), ((TEXPalette*)ggerman_no));
    } else if (gLanguage == 2) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gfrench_yes), ((TEXPalette*)gfrench_no));
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gspanish_yes), ((TEXPalette*)gspanish_no));
    } else if (gLanguage == 4) {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gitalian_yes), ((TEXPalette*)gitalian_no));
#endif
    } else {
        simulatorDrawYesNoMessageLoopImpl(simulatorQuestion, ((TEXPalette*)gyes), ((TEXPalette*)gno));
    }
#elif IS_MM_EU
    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*descriptor)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*descriptor)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->width / 2,
                            180 - ((TEXPalette*)gyes)->descriptorArray->textureHeader->height / 2, (TEXPalette*)gno,
                            200 - ((TEXPalette*)gno)->descriptorArray->textureHeader->width / 2,
                            180 - ((TEXPalette*)gno)->descriptorArray->textureHeader->height / 2);
#else
    simulatorDrawYesNoImage(simulatorQuestion, N64_FRAME_WIDTH / 2 - (*pQuestion)->textureHeader->width / 2,
                            N64_FRAME_HEIGHT / 2 - (*pQuestion)->textureHeader->height / 2, (TEXPalette*)gyes,
                            120 - (*pYes)->textureHeader->width / 2, 180 - (*pYes)->textureHeader->height / 2,
                            (TEXPalette*)gno, 200 - (*pNo)->textureHeader->width / 2,
                            180 - (*pNo)->textureHeader->height / 2);
#endif

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
#if VERSION == MM_J || VERSION == MM_U
    char buf[30] = "TPL/";
#elif IS_OOT_EU || IS_MM_EU
    char buf[30];

    if (gLanguage == 1) {
        strcpy(buf, "TPL/GERMAN/");
    } else if (gLanguage == 2) {
        strcpy(buf, "TPL/FRENCH/");
#if IS_MM_EU
    } else if (gLanguage == 3) {
        strcpy(buf, "TPL/SPANISH/");
#endif
    } else {
        strcpy(buf, "TPL/ENGLISH/");
    }
#endif

    switch (simulatorMessage) {
        case S_M_CARD_LD05_2:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_ld05_2.tpl", gmsg_ld05_2Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD06_4:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_ld06_4.tpl", gmsg_ld06_4Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_LD07:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_ld07.tpl", gmsg_ld07Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_GF01:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_gf01.tpl", gmsg_gf01Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_IN01:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_in01.tpl", gmsg_in01Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV06_4:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_sv06_4.tpl", gmsg_sv06_4Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV06_5:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_sv06_5.tpl", gmsg_sv06_5Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        case S_M_CARD_SV08:
            simulatorOpenMessage(simulatorMessage, TPL_DIR "msg_sv08.tpl", gmsg_sv08Size, fileInfo, buf);
            return simulatorDrawYesNoMessageLoop((TEXPalette*)gpErrorMessageBuffer, yes);

        default:
            break;
    }

    return false;
}

#define simulatorDrawOKMessageLoopImpl(simulatorMessage, yes, mesgOK)                                             \
    {                                                                                                             \
        simulatorDrawOKImage(simulatorMessage,                                                                    \
                             N64_FRAME_WIDTH / 2 - simulatorMessage->descriptorArray->textureHeader->width / 2,   \
                             N64_FRAME_HEIGHT / 2 - simulatorMessage->descriptorArray->textureHeader->height / 2, \
                             mesgOK, N64_FRAME_WIDTH / 2 - mesgOK->descriptorArray->textureHeader->width / 2,     \
                             180 - yes->descriptorArray->textureHeader->height / 2);                              \
    } // bug, copy paste error?

static bool simulatorDrawOKMessageLoop(TEXPalette* simulatorMessage) {
#if IS_OOT_EU
    if (gLanguage == 1) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)ggerman_yes), ((TEXPalette*)ggerman_mesgOK));
    } else if (gLanguage == 2) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gfrench_yes), ((TEXPalette*)gfrench_mesgOK));
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gspanish_yes), ((TEXPalette*)gspanish_mesgOK));
    } else if (gLanguage == 4) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gitalian_yes), ((TEXPalette*)gitalian_mesgOK));
#endif
    } else
#endif
    {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gyes), ((TEXPalette*)gmesgOK));
    }

    if (gButtonDownToggle == true) {
        DEMOPadRead();
        if (DemoPad->pst.button != 0) {
            return false;
        }
    }

    gButtonDownToggle = false;
    DEMOPadRead();

#if IS_OOT_EU
    if (gLanguage == 1) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)ggerman_yes), ((TEXPalette*)ggerman_mesgOK));
    } else if (gLanguage == 2) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gfrench_yes), ((TEXPalette*)gfrench_mesgOK));
#if VERSION == CE_E
    } else if (gLanguage == 3) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gspanish_yes), ((TEXPalette*)gspanish_mesgOK));
    } else if (gLanguage == 4) {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gitalian_yes), ((TEXPalette*)gitalian_mesgOK));
#endif
    } else
#endif
    {
        simulatorDrawOKMessageLoopImpl(simulatorMessage, ((TEXPalette*)gyes), ((TEXPalette*)gmesgOK));
    }

    if ((DemoPad->pst.err == PAD_ERR_NONE) && (DemoPad->pst.button & (PAD_BUTTON_START | PAD_BUTTON_A))) {
        soundPlayBeep(SYSTEM_SOUND(gpSystem), SOUND_BEEP_ACCEPT);
        gButtonDownToggle = true;
        return true;
    }

    PAD_STACK();
    return false;
}

bool simulatorDrawErrorMessageWait(SimulatorMessage simulatorErrorMessage) {
    DVDFileInfo fileInfo;
#if VERSION == MM_J || VERSION == MM_U
    char buf[30] = "TPL/";
#elif IS_OOT_EU || IS_MM_EU
    char buf[30];

    if (gLanguage == 1) {
        strcpy(buf, "TPL/GERMAN/");
    } else if (gLanguage == 2) {
        strcpy(buf, "TPL/FRENCH/");
#if IS_MM_EU
    } else if (gLanguage == 3) {
        strcpy(buf, "TPL/SPANISH/");
#endif
    } else {
        strcpy(buf, "TPL/ENGLISH/");
    }
#endif

    switch (simulatorErrorMessage) {
        case S_M_CARD_LD01:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld01.tpl", gmsg_ld01Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD02:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld02.tpl", gmsg_ld02Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD03:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld03.tpl", gmsg_ld03Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD04:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld04.tpl", gmsg_ld04Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD05_1:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld05_1.tpl", gmsg_ld05_1Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD06_1:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld06_1.tpl", gmsg_ld06_1Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD06_2:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld06_2.tpl", gmsg_ld06_2Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_LD06_3:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_ld06_3.tpl", gmsg_ld06_3Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_GF03:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_gf03.tpl", gmsg_gf03Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_GF04:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_gf04.tpl", gmsg_gf04Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_GF05:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_gf05.tpl", gmsg_gf05Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_GF06:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_gf06.tpl", gmsg_gf06Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_IN03:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_in03.tpl", gmsg_in03Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_IN04:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_in04.tpl", gmsg_in04Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_IN05:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_in05.tpl", gmsg_in05Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV01:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv01.tpl", gmsg_sv01Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV01_2:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv01_2.tpl", gmsg_sv01_2Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV02:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv02.tpl", gmsg_sv02Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV03:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv03.tpl", gmsg_sv03Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV04:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv04.tpl", gmsg_sv04Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV05_1:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv05_1.tpl", gmsg_sv05_1Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV06_1:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv06_1.tpl", gmsg_sv06_1Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV06_2:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv06_2.tpl", gmsg_sv06_2Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV06_3:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv06_3.tpl", gmsg_sv06_3Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV07:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv07.tpl", gmsg_sv07Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV10:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv10.tpl", gmsg_sv10Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV11:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv11.tpl", gmsg_sv11Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV12:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv12.tpl", gmsg_sv12Size, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

        case S_M_CARD_SV_SHARE:
            simulatorOpenMessage(simulatorErrorMessage, TPL_DIR "msg_sv_share.tpl", gmsg_sv_shareSize, fileInfo, buf);
            return simulatorDrawOKMessageLoop((TEXPalette*)gpErrorMessageBuffer);

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
        simulatorDEMODoneRender();
        VISetBlack(false);
        GXSetCopyClear(color, 0);
        movieTestReset(false, false);
    }
}

static u32 gContMap[PAD_MAX_CONTROLLERS][GCN_BTN_COUNT];

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
            if (nDirButton & DEMO_SUBSTICK_UP) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_UP];
            }
            if (nDirButton & DEMO_SUBSTICK_DOWN) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_DOWN];
            }
            if (nDirButton & DEMO_SUBSTICK_LEFT) {
                *anData |= gContMap[channel][GCN_BTN_CSTICK_LEFT];
            }
            if (nDirButton & DEMO_SUBSTICK_RIGHT) {
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

#if IS_MM
        if (gpSystem->eTypeROM == SRT_ZELDA2) {
            if (nCurrButton & PAD_BUTTON_UP && !(nCurrButton & (PAD_TRIGGER_Z | PAD_BUTTON_A | PAD_BUTTON_X))) {
                if (!(nDirButton & DEMO_SUBSTICK_ALL)) {
                    *anData |= gContMap[channel][GCN_BTN_DPAD_UP];
                }
            }
            if (nCurrButton & PAD_BUTTON_DOWN && !(nCurrButton & (PAD_TRIGGER_Z | PAD_BUTTON_A | PAD_BUTTON_X))) {
                if (!(nDirButton & DEMO_SUBSTICK_ALL)) {
                    *anData |= gContMap[channel][GCN_BTN_DPAD_DOWN];
                }
            }
            if (nCurrButton & PAD_BUTTON_LEFT && !(nCurrButton & (PAD_TRIGGER_Z | PAD_BUTTON_A | PAD_BUTTON_X))) {
                if (!(nDirButton & DEMO_SUBSTICK_ALL)) {
                    *anData |= gContMap[channel][GCN_BTN_DPAD_LEFT];
                }
            }
            if (nCurrButton & PAD_BUTTON_RIGHT && !(nCurrButton & (PAD_TRIGGER_Z | PAD_BUTTON_A | PAD_BUTTON_X))) {
                if (!(nDirButton & DEMO_SUBSTICK_ALL)) {
                    *anData |= gContMap[channel][GCN_BTN_DPAD_RIGHT];
                }
            }
        } else
#endif
        {
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

    mcardRead(&mCard, address * 8, 8, (char*)data);
    return true;
}

bool simulatorWriteEEPROM(u8 address, u8* data) {
    s32 size;

    if (!pifGetEEPROMSize(SYSTEM_PIF(gpSystem), (u32*)&size)) {
        return false;
    }

    mcardWrite(&mCard, address * 8, 8, (char*)data);
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
                   VERSION == CE_E                      ? 1924
                   : VERSION == MQ_E                    ? 1836
                   : VERSION == MM_J || VERSION == MM_E ? 2073
                   : VERSION == MM_U                    ? 2047
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
                   VERSION == CE_E                      ? 1924
                   : VERSION == MQ_E                    ? 1836
                   : VERSION == MM_J || VERSION == MM_E ? 2073
                   : VERSION == MM_U                    ? 2047
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
                   VERSION == CE_E                      ? 1924
                   : VERSION == MQ_E                    ? 1836
                   : VERSION == MM_J || VERSION == MM_E ? 2073
                   : VERSION == MM_U                    ? 2047
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

#if IS_MM_EU
bool simulatorPreloadDiskMessages(void) {
    char path_coverOpen[40];
    char path_noDisk[40];
    char path_retryErr[40];
    char path_fatalErr[40];
    char path_wrongDisk[40];
    char path_readingDisk[40];
    char path_yes[40];
    char path_no[40];
    char path_mesgOK[40];
    struct DVDFileInfo fileInfo;
    u32 size;

    simulatorUnpackTexPalette((TEXPalette*)gbar);

    switch (gLanguage) {
        case 1:
            strcpy(path_coverOpen, "TPL/GERMAN/german_coverOpen.tpl");
            strcpy(path_noDisk, "TPL/GERMAN/german_noDisk.tpl");
            strcpy(path_retryErr, "TPL/GERMAN/german_retryErr.tpl");
            strcpy(path_fatalErr, "TPL/GERMAN/german_fatalErr.tpl");
            strcpy(path_wrongDisk, "TPL/GERMAN/german_wrongDisk.tpl");
            strcpy(path_readingDisk, "TPL/GERMAN/german_readingDisk.tpl");
            strcpy(path_yes, "TPL/GERMAN/german_yes.tpl");
            strcpy(path_no, "TPL/GERMAN/german_no.tpl");
            strcpy(path_mesgOK, "TPL/GERMAN/german_mesgOK.tpl");
            break;
        case 2:
            strcpy(path_coverOpen, "TPL/FRENCH/french_coverOpen.tpl");
            strcpy(path_noDisk, "TPL/FRENCH/french_noDisk.tpl");
            strcpy(path_retryErr, "TPL/FRENCH/french_retryErr.tpl");
            strcpy(path_fatalErr, "TPL/FRENCH/french_fatalErr.tpl");
            strcpy(path_wrongDisk, "TPL/FRENCH/french_wrongDisk.tpl");
            strcpy(path_readingDisk, "TPL/FRENCH/french_readingDisk.tpl");
            strcpy(path_yes, "TPL/FRENCH/french_yes.tpl");
            strcpy(path_no, "TPL/FRENCH/french_no.tpl");
            strcpy(path_mesgOK, "TPL/FRENCH/french_mesgOK.tpl");
            break;
        case 3:
            strcpy(path_coverOpen, "TPL/SPANISH/spanish_coverOpen.tpl");
            strcpy(path_noDisk, "TPL/SPANISH/spanish_noDisk.tpl");
            strcpy(path_retryErr, "TPL/SPANISH/spanish_retryErr.tpl");
            strcpy(path_fatalErr, "TPL/SPANISH/spanish_fatalErr.tpl");
            strcpy(path_wrongDisk, "TPL/SPANISH/spanish_wrongDisk.tpl");
            strcpy(path_readingDisk, "TPL/SPANISH/spanish_readingDisk.tpl");
            strcpy(path_yes, "TPL/SPANISH/spanish_yes.tpl");
            strcpy(path_no, "TPL/SPANISH/spanish_no.tpl");
            strcpy(path_mesgOK, "TPL/SPANISH/spanish_mesgOK.tpl");
            break;
        case 4:
            strcpy(path_coverOpen, "TPL/ITALIAN/italian_coverOpen.tpl");
            strcpy(path_noDisk, "TPL/ITALIAN/italian_noDisk.tpl");
            strcpy(path_retryErr, "TPL/ITALIAN/italian_retryErr.tpl");
            strcpy(path_fatalErr, "TPL/ITALIAN/italian_fatalErr.tpl");
            strcpy(path_wrongDisk, "TPL/ITALIAN/italian_wrongDisk.tpl");
            strcpy(path_readingDisk, "TPL/ITALIAN/italian_readingDisk.tpl");
            strcpy(path_yes, "TPL/ITALIAN/italian_yes.tpl");
            strcpy(path_no, "TPL/ITALIAN/italian_no.tpl");
            strcpy(path_mesgOK, "TPL/ITALIAN/italian_mesgOK.tpl");
            break;
        case 0:
        default:
            strcpy(path_coverOpen, "TPL/ENGLISH/coverOpen.tpl");
            strcpy(path_noDisk, "TPL/ENGLISH/noDisk.tpl");
            strcpy(path_retryErr, "TPL/ENGLISH/retryErr.tpl");
            strcpy(path_fatalErr, "TPL/ENGLISH/fatalErr.tpl");
            strcpy(path_wrongDisk, "TPL/ENGLISH/wrongDisk.tpl");
            strcpy(path_readingDisk, "TPL/ENGLISH/readingDisk.tpl");
            strcpy(path_yes, "TPL/ENGLISH/yes.tpl");
            strcpy(path_no, "TPL/ENGLISH/no.tpl");
            strcpy(path_mesgOK, "TPL/ENGLISH/mesgOK.tpl");
            break;
    }

    if (DVDOpen(path_coverOpen, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gcoverOpen != NULL) {
            if (!xlHeapFree((void**)&gcoverOpen)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gcoverOpen, size | 0x30000000)) {
            return false;
        }

        DVDReadPrio(&fileInfo, gcoverOpen, size, 0, 2);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gcoverOpen);
    } else {
        return false;
    }

    if (DVDOpen(path_readingDisk, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (greadingDisk != NULL) {
            if (!xlHeapFree((void**)&greadingDisk)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&greadingDisk, size | 0x30000000)) {
            return false;
        }

        DVDReadPrio(&fileInfo, greadingDisk, size, 0, 2);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)greadingDisk);
    } else {
        return false;
    }

    if (DVDOpen(path_wrongDisk, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gwrongDisk != NULL) {
            if (!xlHeapFree((void**)&gwrongDisk)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gwrongDisk, size | 0x30000000)) {
            return false;
        }

        DVDReadPrio(&fileInfo, gwrongDisk, size, 0, 2);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gwrongDisk);
    } else {
        return false;
    }

    if (DVDOpen(path_noDisk, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gnoDisk != NULL) {
            if (!xlHeapFree((void**)&gnoDisk)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gnoDisk, size | 0x30000000)) {
            return false;
        }

        DVDReadPrio(&fileInfo, gnoDisk, size, 0, 2);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gnoDisk);
    } else {
        return false;
    }

    if (DVDOpen(path_retryErr, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gretryErr != NULL) {
            if (!xlHeapFree((void**)&gretryErr)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gretryErr, size | 0x30000000)) {
            return false;
        }

        simulatorDVDRead(&fileInfo, gretryErr, size, 0, NULL);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gretryErr);
    } else {
        return false;
    }

    if (DVDOpen(path_fatalErr, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gfatalErr != NULL) {
            if (!xlHeapFree((void**)&gfatalErr)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gfatalErr, size | 0x30000000)) {
            return false;
        }

        simulatorDVDRead(&fileInfo, gfatalErr, size, 0, NULL);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gfatalErr);
    } else {
        return false;
    }

    if (DVDOpen(path_yes, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gyes != NULL) {
            if (!xlHeapFree((void**)&gyes)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gyes, size | 0x30000000)) {
            return false;
        }

        simulatorDVDRead(&fileInfo, gyes, size, 0, NULL);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gyes);
    } else {
        return false;
    }

    if (DVDOpen(path_no, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gno != NULL) {
            if (!xlHeapFree((void**)&gno)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gno, size | 0x30000000)) {
            return false;
        }

        simulatorDVDRead(&fileInfo, gno, size, 0, NULL);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gno);
    } else {
        return false;
    }

    if (DVDOpen(path_mesgOK, &fileInfo)) {
        size = (fileInfo.length + 0x1F) & ~0x1F;

        if (gmesgOK != NULL) {
            if (!xlHeapFree((void**)&gmesgOK)) {
                return false;
            }
        }

        if (!xlHeapTake((void**)&gmesgOK, size | 0x30000000)) {
            return false;
        }

        simulatorDVDRead(&fileInfo, gmesgOK, size, 0, NULL);
        DVDClose(&fileInfo);
        simulatorUnpackTexPalette((TEXPalette*)gmesgOK);
    } else {
        return false;
    }

    return true;
}
#endif

static char* gaszArgument[8];

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

#if IS_MM
    InitDVDTrackList();
#endif

    if (!xlHeapGetFree(&nSize0)) {
        return false;
    }

    // Necessary to match .sdata2 usage order
    (void)0.0f;
#if IS_OOT
    (void)1.0f;
    (void)0.1f;
#endif

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
    simulatorDEMODoneRender();

    xlCoreBeforeRender();
    simulatorDEMODoneRender();

    VIWaitForRetrace();
    VISetBlack(false);
    VIFlush();

#if IS_EU
    gLanguage = OSGetLanguage();
#endif

#if IS_OOT_EU
    switch (gLanguage) {
        case 0:
#if IS_MQ_EU
        case 4:
        case 5:
#endif
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
            simulatorUnpackTexPalette((TEXPalette*)gbar);
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
            simulatorUnpackTexPalette((TEXPalette*)gbar);
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
            simulatorUnpackTexPalette((TEXPalette*)gbar);
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
            simulatorUnpackTexPalette((TEXPalette*)gbar);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_yes);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_no);
            simulatorUnpackTexPalette((TEXPalette*)gitalian_mesgOK);
            break;
        case 5:
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
#elif VERSION != MM_E
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

    mCard.bufferCreated = false;

#if VERSION != MQ_J
    mCard.isBroken = false;
#endif

#if IS_MM
    if (!xlHeapTake((void**)&mCard.file.game.writtenBlocks, 0x0064 | 0x30000000)) {
        return false;
    }
    memset(mCard.file.game.writtenBlocks, 0, 0x64);
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

#if IS_MM_EU
    while (!simulatorPreloadDiskMessages()) {}
#endif

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
