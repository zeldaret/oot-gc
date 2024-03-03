#include "rsp.h"
#include "rsp_jumptables.h"

_XL_OBJECTTYPE gClassRSP = {
    "RSP",
    sizeof(Rsp),
    NULL,
    (EventFunc)rspEvent,
};

s32 cmask_tab[8] = {
    0x00000007, 0x0000000E, 0x0000000C, 0x0000000C, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

s32 emask_tab[8] = {
    0x00000000, 0x00000001, 0x00000003, 0x00000003, 0x00000007, 0x00000007, 0x00000007, 0x00000007,
};

static s16 TMEMSIZE[5] = {
    0x0200, 0x0200, 0x0100, 0x0200, 0x0200,
};

char D_800EE27C[40] = "FrameComplete: Yielded task pending...\n";

void* jtbl_800EE2A4[] = {
    &lbl_800721A4, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_800721B0, &lbl_80072218,
    &lbl_80072218, &lbl_80072218, &lbl_800721BC, &lbl_80072218, &lbl_80072218, &lbl_80072218,
    &lbl_800721C8, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_800721D4, &lbl_80072218,
    &lbl_80072218, &lbl_80072218, &lbl_800721E4, &lbl_80072218, &lbl_80072218, &lbl_80072218,
    &lbl_800721F4, &lbl_80072218, &lbl_80072218, &lbl_80072218, &lbl_80072204,
};

void* jtbl_800EE318[] = {
    &lbl_80072718, &lbl_80072580, &lbl_800725B4, &lbl_800725E8,
    &lbl_80072608, &lbl_80072670, &lbl_800726D8, &lbl_800726F8,
};

void* jtbl_800EE338[] = {
    &lbl_8007241C, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_8007242C, &lbl_80072948,
    &lbl_80072948, &lbl_80072948, &lbl_8007243C, &lbl_80072948, &lbl_80072948, &lbl_80072948,
    &lbl_800724AC, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_80072534, &lbl_80072948,
    &lbl_80072948, &lbl_80072948, &lbl_80072998, &lbl_80072948, &lbl_80072948, &lbl_80072948,
    &lbl_80072998, &lbl_80072948, &lbl_80072948, &lbl_80072948, &lbl_8007293C,
};

void* jtbl_800EE3AC[] = {
    &lbl_80072AC0, &lbl_80072AC0, &lbl_80072AC0, &lbl_80072AD4, &lbl_80072AE8, &lbl_80072AC0,
    &lbl_80072AD4, &lbl_80072AC0, &lbl_80072AD4, &lbl_80072AC0, &lbl_80072AD4,
};

void* jtbl_800EE3D8[] = {
    &lbl_80075608, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_80075630, &lbl_8007600C, &lbl_8007600C,
    &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C, &lbl_8007600C,
};

void* jtbl_800EE40C[] = {
    &lbl_8007600C, &lbl_800750A4, &lbl_80074F84, &lbl_800750A4, &lbl_8007600C,
    &lbl_800750A4, &lbl_80074FB0, &lbl_800750A4, &lbl_80074FC4, &lbl_800750A4,
    &lbl_80075020, &lbl_800750A4, &lbl_8007600C, &lbl_800750A4, &lbl_8007600C,
};

void* jtbl_800EE448[] = {
    &lbl_80074A78, &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_80074C44, &lbl_80074D04, &lbl_80074CA4,
    &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_8007600C, &lbl_80074D04, &lbl_800749F0,
};

void* jtbl_800EE47C[] = {
    &lbl_80077440, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077468, &lbl_80077778, &lbl_80077778,
    &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778, &lbl_80077778,
};

void* jtbl_800EE4B0[] = {
    &lbl_80076D14, &lbl_80076F5C, &lbl_80076E3C, &lbl_80076F5C, &lbl_80077778,
    &lbl_80076F5C, &lbl_80076E84, &lbl_80076F5C, &lbl_80076E94, &lbl_80076F5C,
    &lbl_80076EF0, &lbl_80076F5C, &lbl_80077778, &lbl_80076F5C, &lbl_80077778,
};

void* jtbl_800EE4EC[] = {
    &lbl_80076698, &lbl_8007685C, &lbl_800766EC, &lbl_8007685C, &lbl_80076744, &lbl_8007685C, &lbl_8007679C,
    &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C,
    &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C, &lbl_8007685C, &lbl_8007679C,
    &lbl_8007685C, &lbl_80077778, &lbl_8007685C, &lbl_80077778, &lbl_8007685C, &lbl_80077778, &lbl_8007685C,
    &lbl_80077778, &lbl_8007685C, &lbl_800767FC,
};

void* jtbl_800EE568[] = {
    &lbl_8008118C, &lbl_80080B40, &lbl_80080B50, &lbl_8008117C, &lbl_80080B6C, &lbl_80080B7C, &lbl_80080B8C,
    &lbl_8008117C, &lbl_80080CF4, &lbl_8008117C, &lbl_80080D20, &lbl_80080D4C, &lbl_80080DB0, &lbl_80080DC0,
    &lbl_80080E2C, &lbl_80080E3C, &lbl_80080E58, &lbl_80080E98, &lbl_80080FFC, &lbl_80081048, &lbl_80081058,
    &lbl_800810A4, &lbl_800810F0, &lbl_8008111C, &lbl_8008112C, &lbl_8008118C, &lbl_8008113C,
};

void* jtbl_800EE5D4[] = {
    &lbl_80082B60, &lbl_800826C0, &lbl_800826D0, &lbl_80082B50, &lbl_80082B50, &lbl_80082764,
    &lbl_80082B50, &lbl_800827D0, &lbl_800827E4, &lbl_80082B50, &lbl_800827F4, &lbl_80082830,
    &lbl_80082894, &lbl_800828A4, &lbl_8008291C, &lbl_8008292C, &lbl_80082948, &lbl_80082990,
    &lbl_80082B04, &lbl_800826F8, &lbl_80082708, &lbl_80082774, &lbl_80082B40,
};

void* jtbl_800EE630[] = {
    &lbl_80084950, &lbl_80084338, &lbl_80084360, &lbl_8008437C, &lbl_8008438C, &lbl_8008439C,
    &lbl_800843AC, &lbl_80084514, &lbl_80084524, &lbl_80084550, &lbl_80084590, &lbl_800845BC,
    &lbl_80084620, &lbl_80084630, &lbl_80084640, &lbl_80084650, &lbl_8008466C, &lbl_800846AC,
    &lbl_80084810, &lbl_8008485C, &lbl_8008486C, &lbl_800848B8, &lbl_80084904, &lbl_80084930,
};

void* jtbl_800EE690[] = {
    &lbl_80088B18, &lbl_80088890, &lbl_8008889C, &lbl_80088AD8, &lbl_800888C4, &lbl_80088AE4,
    &lbl_80088914, &lbl_80088970, &lbl_80088984, &lbl_80088AF0, &lbl_80088990, &lbl_800889CC,
    &lbl_80088A38, &lbl_80088A44, &lbl_80088AFC, &lbl_80088ABC,
};

static s32 nFirstTime_2148 = 0x00000001;
static s32 nFirstTime_2648 = 0x00000001;
static s32 nFirstTime_2757 = 0x00000001;
static s32 nFirstTime_2796 = 0x00000001;

static u16 scissorX1 = 0x500;
static u16 scissorY1 = 0x3C0;

static s16 TMEMMASK[4] = {
    0x01FF,
    0x00FF,
    0x007F,
    0x003F,
};

static s16 TMEMSHIFT[4] = {
    0x0200,
    0x0100,
    0x0080,
    0x0040,
};

static s32 counter;
static u16 scissorX0;
static u16 scissorY0;
static u8 flagBilerp;
static u32 rdpSetTimg_w0;
static u32 rdpSetTile_w0;
static u16 tmemSliceWmax;
static u16 imageSrcWsize;
static u16 flagSplit;
static u16 imagePtrX0;
static s32 imageTop;
static u16 tmemSrcLines;

const f32 D_80136038 = 0.25;
const f32 D_8013603C = 1024.0;
const f32 D_80136040 = 0.03125;
const f64 D_80136048 = 4503601774854144.0;
const f64 D_80136050 = 4503599627370496.0;
const f32 D_80136058 = 1.0;
const f32 D_8013605C = 0.0;
const f32 D_80136060 = 0.5;
const f32 D_80136064 = 2.0;
const f32 D_80136068 = -1.0;
const f32 D_8013606C = 65536.0;
const f32 D_80136070 = 0.0009765625;
const f32 D_80136074 = 1.52587890625e-05;

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspVMUDN.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspVMADN.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspInitAudioDMEM1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspDotProduct8x15MatrixBy15x1Vector.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspMultPolef.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspLoadADPCMCoefTable1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspLoadADPCMCoefTable2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAADPCMDec1Fast.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAPoleFilter1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAMix1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAResample1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspASetBuffer1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspASetVolume1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspInitAudioDMEM2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAADPCMDec2Fast.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspANoise2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspANMix2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAResample2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAFirFilter2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAMix2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAInterleave2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspADistFilter2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAPCM8Dec2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspInitAudioDMEM3.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAEnvMixer3.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspAMix3.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI3.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspInitAudioDMEM4.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseABI4.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspCreateJPEGArrays.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspConvertRGBAtoYUV.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspYUVtoDCTBuf.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspDCT.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspQuantize.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoQuantize.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoDCT.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoYUVtoDCTBuf.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFormatYUV.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_Encode.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_Decode.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspCreateJPEGArraysZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspDCTZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspQuantizeZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspZigzagDataZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoQuantizeZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoZigzagDataZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoDCTZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoLoadColorBufferZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUndoRecon420Z.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspRecon420Z.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_EncodeZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseJPEG_DecodeZ.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/Matrix4by4Identity.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFillObjSprite.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFillObjBgScale.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFillObjBg.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspSetImage.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/tmemLoad_B.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/tmemLoad_A.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/tmemLoad.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/guS2DEmuBgRect1Cyc.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFillObjTxtr.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjLoadTxtr.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjRectangle.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjSprite.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjRectangleR.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspBgRectCopy.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspObjMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspSetupS2DEX.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspSetGeometryMode1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI_F3DEX1.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGeometryMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI_F3DEX2.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspLoadMatrix.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFindUCode.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspSaveYield.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspLoadYield.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI_Setup.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspParseGBI.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspPut8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspPut16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspPut32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspPut64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGet8.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGet16.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGet32.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspGet64.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspInvalidateCache.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspEnableABI.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspFrameComplete.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspUpdate.s")

#pragma GLOBAL_ASM("asm/non_matchings/rsp/rspEvent.s")
