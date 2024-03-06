#ifndef _RSP_H
#define _RSP_H

#include "dolphin.h"
#include "xlObject.h"

typedef enum __anon_0x581E7 {
    RUT_NOCODE = -1,
    RUT_ABI1 = 0,
    RUT_ABI2 = 1,
    RUT_ABI3 = 2,
    RUT_ABI4 = 3,
    RUT_UNKNOWN = 4,
} __anon_0x581E7;

typedef enum __anon_0x60B3F {
    RUT_NONE = -1,
    RUT_TURBO = 0,
    RUT_SPRITE2D = 1,
    RUT_FAST3D = 2,
    RUT_ZSORT = 3,
    RUT_LINE3D = 4,
    RUT_F3DEX1 = 5,
    RUT_F3DEX2 = 6,
    RUT_S2DEX1 = 7,
    RUT_S2DEX2 = 8,
    RUT_L3DEX1 = 9,
    RUT_L3DEX2 = 10,
    RUT_AUDIO1 = 11,
    RUT_AUDIO2 = 12,
    RUT_JPEG = 13,
} __anon_0x60B3F;

// __anon_0x44829
typedef enum RspUpdateMode {
    RUM_NONE = 0,
    RUM_IDLE = 1,
} RspUpdateMode;

typedef struct __anon_0x575BD {
    /* 0x00 */ s32 nType;
    /* 0x04 */ s32 nFlag;
    /* 0x08 */ s32 nOffsetBoot;
    /* 0x0C */ s32 nLengthBoot;
    /* 0x10 */ s32 nOffsetCode;
    /* 0x14 */ s32 nLengthCode;
    /* 0x18 */ s32 nOffsetData;
    /* 0x1C */ s32 nLengthData;
    /* 0x20 */ s32 nOffsetStack;
    /* 0x24 */ s32 nLengthStack;
    /* 0x28 */ s32 nOffsetBuffer;
    /* 0x2C */ s32 nLengthBuffer;
    /* 0x30 */ s32 nOffsetMBI;
    /* 0x34 */ s32 nLengthMBI;
    /* 0x38 */ s32 nOffsetYield;
    /* 0x3C */ s32 nLengthYield;
} __anon_0x575BD; // size = 0x40

typedef struct __anon_0x57890 {
    /* 0x00 */ s32 iDL;
    /* 0x04 */ s32 bValid;
    /* 0x08 */ struct __anon_0x575BD task;
    /* 0x48 */ s32 nCountVertex;
    /* 0x4C */ __anon_0x60B3F eTypeUCode;
    /* 0x50 */ u32 n2TriMult;
    /* 0x54 */ u32 nVersionUCode;
    /* 0x58 */ s32 anBaseSegment[16];
    /* 0x98 */ u64* apDL[16];
} __anon_0x57890; // size = 0xD8

typedef struct __anon_0x57AB1 {
    /* 0x00 */ f32 aRotations[2][2];
    /* 0x10 */ f32 fX;
    /* 0x14 */ f32 fY;
    /* 0x18 */ f32 fBaseScaleX;
    /* 0x1C */ f32 fBaseScaleY;
} __anon_0x57AB1; // size = 0x20

typedef struct __anon_0x57BBE {
    /* 0x0 */ f32 rS;
    /* 0x4 */ f32 rT;
    /* 0x8 */ s16 nX;
    /* 0xA */ s16 nY;
    /* 0xC */ s16 nZ;
    /* 0xE */ u8 anData[4];
} __anon_0x57BBE; // size = 0x14

typedef struct __anon_0x57CD6 {
    /* 0x0 */ char anNormal[3];
} __anon_0x57CD6; // size = 0x3

typedef struct __anon_0x57D55 {
    /* 0x0 */ u8 anMaterial[4];
} __anon_0x57D55; // size = 0x4

typedef struct __anon_0x57DF8 {
    /* 0x0 */ f32 aMatrix[4][4];
} __anon_0x57DF8; // size = 0x40

typedef struct __anon_0x57E56 {
    /* 0x0 */ u8 nRed;
    /* 0x1 */ u8 nGreen;
    /* 0x2 */ u8 nBlue;
    /* 0x3 */ char rVectorX;
    /* 0x4 */ char rVectorY;
    /* 0x5 */ char rVectorZ;
} __anon_0x57E56; // size = 0x6

typedef struct __anon_0x58107 {
    /* 0x0 */ s16 anSlice[8];
} __anon_0x58107; // size = 0x10

// __anon_0x5845E
typedef struct Rsp {
    /* 0x0000 */ s32 nMode;
    /* 0x0004 */ struct __anon_0x57890 yield;
    /* 0x00DC */ u32 nTickLast;
    /* 0x00E0 */ s32 (*pfUpdateWaiting)();
    /* 0x00E4 */ u32 n2TriMult;
    /* 0x00E8 */ s32 aStatus[4];
    /* 0x00F8 */ f32 aMatrixOrtho[4][4];
    /* 0x0138 */ u32 nMode2D;
    /* 0x013C */ struct __anon_0x57AB1 twoDValues;
    /* 0x015C */ s32 nPass;
    /* 0x0160 */ u32 nZSortSubDL;
    /* 0x0164 */ u32 nStatusSubDL;
    /* 0x0168 */ u32 nNumZSortLights;
    /* 0x016C */ s32 aLightAddresses[8];
    /* 0x018C */ s32 nAmbientLightAddress;
    /* 0x0190 */ struct __anon_0x57BBE aZSortVertex[128];
    /* 0x0B90 */ struct __anon_0x57CD6 aZSortNormal[128];
    /* 0x0D10 */ struct __anon_0x57D55 aZSortMaterial[128];
    /* 0x0F10 */ struct __anon_0x57DF8 aZSortMatrix[128];
    /* 0x2F10 */ struct __anon_0x57E56 aZSortLight[8];
    /* 0x2F40 */ s32 aZSortInvW[128];
    /* 0x3140 */ s16 aZSortWiVal[128];
    /* 0x3240 */ u32 nNumZSortMatrices;
    /* 0x3244 */ u32 nNumZSortVertices;
    /* 0x3248 */ u32 nTotalZSortVertices;
    /* 0x324C */ u32 nNumZSortNormals;
    /* 0x3250 */ u32 nNumZSortMaterials;
    /* 0x3254 */ s32 anAudioBaseSegment[16];
    /* 0x3294 */ s16* anAudioBuffer;
    /* 0x3298 */ s16 anADPCMCoef[5][2][8];
    /* 0x3338 */ u16 nAudioDMOutR[2];
    /* 0x333C */ u16 nAudioDMauxL[2];
    /* 0x3340 */ u16 nAudioDMauxR[2];
    /* 0x3344 */ u16 nAudioCount[2];
    /* 0x3348 */ u16 nAudioFlags;
    /* 0x334A */ u16 nAudioDMEMIn[2];
    /* 0x334E */ u16 nAudioDMEMOut[2];
    /* 0x3354 */ u32 nAudioLoopAddress;
    /* 0x3358 */ u32 nAudioDryAmt;
    /* 0x335C */ u32 nAudioWetAmt;
    /* 0x3360 */ u32 nAudioVolL;
    /* 0x3364 */ u32 nAudioVolR;
    /* 0x3368 */ u32 nAudioVolTGTL;
    /* 0x336C */ u32 nAudioVolRateLM;
    /* 0x3370 */ u32 nAudioVolRateLL;
    /* 0x3374 */ u32 nAudioVolTGTR;
    /* 0x3378 */ u32 nAudioVolRateRM;
    /* 0x337C */ u32 nAudioVolRateRL;
    /* 0x3380 */ struct __anon_0x58107 vParams;
    /* 0x3390 */ s16 stepF;
    /* 0x3392 */ s16 stepL;
    /* 0x3394 */ s16 stepR;
    /* 0x3398 */ s32 anGenReg[32];
    /* 0x3418 */ struct __anon_0x58107 aVectorReg[32];
    /* 0x3618 */ s32 anCP0Reg[32];
    /* 0x3698 */ struct __anon_0x58107 anCP2Reg[32];
    /* 0x3898 */ s16 anAcc[24];
    /* 0x38C8 */ s16 nVCC;
    /* 0x38CA */ s16 nVC0;
    /* 0x38CC */ char nVCE;
    /* 0x38D0 */ __anon_0x581E7 eTypeAudioUCode;
    /* 0x38D4 */ u16 nAudioMemOffset;
    /* 0x38D6 */ u16 nAudioADPCMOffset;
    /* 0x38D8 */ u16 nAudioScratchOffset;
    /* 0x38DA */ u16 nAudioParBase;
    /* 0x38DC */ s32 nPC;
    /* 0x38E0 */ s32 iDL;
    /* 0x38E4 */ s32 nBIST;
    /* 0x38E8 */ void* pHost;
    /* 0x38EC */ void* pDMEM;
    /* 0x38F0 */ void* pIMEM;
    /* 0x38F4 */ s32 nStatus;
    /* 0x38F8 */ s32 nFullDMA;
    /* 0x38FC */ s32 nBusyDMA;
    /* 0x3900 */ s32 nSizeGet;
    /* 0x3904 */ s32 nSizePut;
    /* 0x3908 */ s32 nSemaphore;
    /* 0x390C */ s32 nAddressSP;
    /* 0x3910 */ s32 nGeometryMode;
    /* 0x3914 */ s32 nAddressRDRAM;
    /* 0x3918 */ struct tXL_LIST* pListUCode;
    /* 0x391C */ s32 nCountVertex;
    /* 0x3920 */ enum __anon_0x60B3F eTypeUCode;
    /* 0x3924 */ u32 nVersionUCode;
    /* 0x3928 */ s32 anBaseSegment[16];
    /* 0x3968 */ u64* apDL[16];
    /* 0x39A8 */ s32* Coeff;
    /* 0x39AC */ s16* QTable;
    /* 0x39B0 */ s16* QYTable;
    /* 0x39B4 */ s16* QCbTable;
    /* 0x39B8 */ s16* QCrTable;
    /* 0x39BC */ s32* Zigzag;
    /* 0x39C0 */ struct __anon_0x58360* rgbaBuf;
    /* 0x39C4 */ struct __anon_0x583EE* yuvBuf;
    /* 0x39C8 */ s32* dctBuf;
} Rsp; // size = 0x39CC

s32 rspEnableABI(Rsp* pRSP, s32 bFlag);
s32 rspUpdate(Rsp* pRSP, RspUpdateMode eMode);
s32 rspEvent(Rsp* pRSP, s32 nEvent, void* pArgument);

extern _XL_OBJECTTYPE gClassRSP;

#endif
