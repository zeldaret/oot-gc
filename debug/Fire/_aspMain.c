/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_aspMain.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80080AA4 -> 0x8008CF0C
*/

#include "dolphin/types.h"

// Range: 0x8008BBDC -> 0x8008CF0C
static s32 rspInitAudioDMEM1(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Range: 0x8008B768 -> 0x8008BBDC
s32 rspDotProduct8x15MatrixBy15x1Vector(s16* matrix, s16* vectorIn, s16* vectorOut) {
    // Parameters
    // s16* matrix; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14

    // Local variables
    s32 sum; // r12
    s32 vec1; // r1+0x8
    s32 vec2; // r1+0x8
    s32 vec3; // r1+0x8
    s32 vec4; // r1+0x8
    s32 vec5; // r1+0x8
    s32 vec6; // r1+0x8
    s32 vec7; // r1+0x8
    s32 vec8; // r31
    s32 vec9; // r30
    s32 vec10; // r29
    s32 vec11; // r28
    s32 vec12; // r27
    s32 vec13; // r26
    s32 vec14; // r5
}

// Erased
static s32 rspMultADPCMCoef1(struct __anon_0x5845E* pRSP, s32* matrix, s16* vectorIn, s16* vectorOut, s32 nOptPred) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32* matrix; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14
    // s32 nOptPred; // r1+0x18

    // Local variables
    s32 sum; // r12
    s32 vec0; // r1+0x8
    s32 vec1; // r1+0x8
    s32 vec2; // r26
    s32 vec3; // r25
    s32 vec4; // r24
    s32 vec5; // r23
    s32 vec6; // r22
    s32 vec7; // r21
    s32 vec8; // r20
}

// Range: 0x8008B378 -> 0x8008B768
s32 rspMultPolef(s16 (*matrix)[8], s16* vectorIn, s16* vectorOut) {
    // Parameters
    // s16 (* matrix)[8]; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14

    // Local variables
    s32 sum; // r22
    s32 vec0; // r1+0x8
    s32 vec1; // r1+0x8
    s32 vec2; // r8
    s32 vec3; // r9
    s32 vec4; // r10
    s32 vec5; // r11
    s32 vec6; // r12
    s32 vec7; // r31
    s32 vec8; // r5
    s32 vec9; // r1+0x8
}

// Erased
static s32 rspDumpDMEMToFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28

    // Local variables
    struct tXL_FILE* fp; // r1+0x50
    s32 i; // r30
    u32 nStartAddress; // r29
    u32 nSize; // r1+0x4C
    char acDMEMLine[64]; // r1+0xC
}

// Erased
static s32 rspDumpMotorolaSDMEMTOFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r27

    // Local variables
    struct tXL_FILE* fp; // r1+0x220
    s32 i; // r29
    u32 nStartAddress; // r28
    u32 nSize; // r1+0x21C
    char acDMEMLine[512]; // r1+0x1C
}

// Erased
static s32 rspDumpBinaryDMEMToFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29

    // Local variables
    struct tXL_FILE* fp; // r1+0x10
    s32 i; // r30
    u32 nSize; // r1+0xC
}

// Erased
static s32 rspLoadADPCMCoefRow(struct __anon_0x5845E* pRSP, u32 nCoefIndex, u32 nOptPred) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCoefIndex; // r6
    // u32 nOptPred; // r1+0x10
}

// Range: 0x8008B1FC -> 0x8008B378
static s32 rspLoadADPCMCoefTable1(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r3

    // Local variables
    u32 j; // r1+0x8
    u32 nCoefIndex; // r5
}

// Range: 0x8008B080 -> 0x8008B1FC
static s32 rspLoadADPCMCoefTable2(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r3

    // Local variables
    u32 j; // r1+0x8
    u32 nCoefIndex; // r5
}

// Erased
static s32 rspALoadBuffer1(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC

    // Local variables
    void* pData; // r1+0x14
    s32 nAddress; // r5
}

// Range: 0x8008A7E0 -> 0x8008B080
static s32 rspAADPCMDec1Fast(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r21
    u8 ucControl; // r6
    char* pHeader; // r31
    s16* pStateAddress; // r1+0x60
    s16 anIData0; // r23
    s32 nDMEMOut; // r30
    s32 nCount; // r29
    s32 nSrcAddress; // r5
    s32 nOptPred; // r7
    s32 nVScale; // r1+0x8
    s32 i; // r1+0x8
    u32 dwDecodeSelect; // r1+0x8
    u32 n; // r1+0x8
    s32 nA; // r8
    s32 nB; // r9
    s16 nSamp1; // r10
    s16 nSamp2; // r1+0x8
    s16* pTempStateAddr; // r1+0x4C
    s32 nOutput; // r10
}

// Erased
static s32 rspAADPCMDec1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r20
    char* pDMEM8; // r27
    char* pHeader; // r1+0xD8
    s32 anCoef[8]; // r1+0xAC
    s16 anIData0[8]; // r1+0x8C
    s16 anOData0[8]; // r1+0x7C
    s16* pStateAddress; // r1+0x78
    s16* pDMEM16; // r4
    s16 anInputVec[10]; // r1+0x64
    s32 nDMEMOut; // r30
    s32 nCount; // r14
    s32 nSrcAddress; // r1+0x8
    s32 nOptPred; // r1+0x8
    s32 nVScale; // r1+0x8
    s32 nScaleI; // r4
    s32 i; // r1+0x8
    s32 nHeader; // r23
    s32 nToggle; // r1+0xD4
    s32 nTIndex; // r1+0x8
    s16* pTempStateAddr; // r1+0x60
}

// Range: 0x80089E7C -> 0x8008A7E0
static s32 rspAPoleFilter1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r25
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r24
    u16 nScale; // r30
    s16 anCoef[10][8]; // r1+0xC0
    s16 anEntries[8]; // r1+0xB0
    s16 nVTemp[8]; // r1+0xA0
    s16 nTempScale; // r4
    s16 anIData0[8]; // r1+0x90
    s16 anOData0[8]; // r1+0x80
    s16 anInputVec[10]; // r1+0x6C
    s16* pStateAddress; // r1+0x68
    s16* pDMEM16; // r29
    s32 nDMEMIn; // r28
    s32 nDMEMOut; // r27
    s32 nCount; // r26
    s32 nSrcAddress; // r5
}

// Erased
static s32 rspAClearBuffer1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r1+0x10
}

// Range: 0x800892A4 -> 0x80089E7C
static s32 rspAEnvMixer1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r23
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r1+0x104
    u32 s; // r1+0x8
    s16* pStateAddress; // r1+0x100
    u16 anRamp[8]; // r1+0xA8
    s32 envVolRateL; // r1+0xFC
    s32 envVolRateR; // r1+0xF8
    s32 envVolFinalL; // r16
    s32 envVolFinalR; // r18
    s32 volVecL[8]; // r1+0x88
    s32 volVecR[8]; // r1+0x68
    s16 anOutL; // r24
    s16 anOutR; // r20
    s16 anAuxL; // r24
    s16 anAuxR; // r1+0x8
    s16 anIn; // r1+0x8
    u32 nInptr; // r1+0xF4
    u32 nOutptrL; // r1+0xF0
    u32 nOutptrR; // r1+0xEC
    u32 nAuxptrL; // r1+0xE8
    u32 nAuxptrR; // r1+0xE4
    u32 i; // r4
    u32 nSrcAddress; // r1+0x8
    u32 nLoopCtl; // r1+0xE0
    s32 nUpDownVolL; // r1+0x8
    s32 nUpDownVolR; // r1+0x8
    void* pData; // r1+0x58
    s32* dataP; // r5
    s64 tempL; // r1+0xD8
    s64 tempR; // r1+0xD0
    s64 totalL; // r1+0xC8
    s64 totalR; // r30
    s64 resultL; // r1+0x8
    s64 resultR; // r6
    s32 volL; // r1+0x8
    s32 volR; // r27
    s64 temp; // r0
    s32* dataP; // r3
}

// Erased
static s32 rspAInterleave1(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4

    // Local variables
    u16 nLeft; // r1+0x0
    u32 iIndex; // r1+0x0
    u32 iIndex2; // r9
}

// Range: 0x8008920C -> 0x800892A4
static s32 rspAMix1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u32 i; // r1+0x0
    u32 nCount; // r8
    s16* srcP; // r4
    s32 outData32; // r6
}

// Range: 0x80088F14 -> 0x8008920C
static s32 rspAResample1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r26
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s16* srcP; // r30
    s16* dstP; // r29
    s16 lastValue; // r7
    u16 nCount; // r28
    u16 i; // r10
    s32 nSrcStep; // r1+0x8
    s32 nCursorPos; // r8
    s32 nExtra; // r3
    u32 scratch; // r1+0x8
    u8 flags; // r27
    s16* pData; // r1+0x34
}

// Erased
static s32 rspASaveBuffer1(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC

    // Local variables
    u32 nSize; // r1+0x18
    u32* pData; // r1+0x14
    s32 nAddress; // r5
}

// Erased
static s32 rspASegment1(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
}

// Range: 0x80088E0C -> 0x80088F14
static s32 rspASetBuffer1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u16 nDMEMIn; // r5
    u16 nDMEMOut; // r6
    u16 nCount; // r4
}

// Range: 0x80088D74 -> 0x80088E0C
static s32 rspASetVolume1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u16 nFlags; // r1+0x0
    u16 v; // r5
    u16 t; // r7
    u16 r; // r8
}

// Erased
static s32 rspASetLoop1(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
}

// Erased
static s32 rspADMEMMove1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u16 nDMEMOut; // r1+0x8
    u16 nCount; // r5
    u32 nDMEMIn; // r1+0x8
}

// Erased
static s32 rspALoadADPCM1(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    void* pData; // r1+0x20
    u32 nCount; // r25
    s32 nAddress; // r5
}

// Range: 0x80088B48 -> 0x80088D74
static s32 rspParseABI(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x575BD* pTask; // r31

    // Local variables
    u8* pFUCode; // r1+0x1C
    u32 nCheckSum; // r4
}

// Range: 0x800887E8 -> 0x80088B48
static s32 rspParseABI1(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    u32 nCommandLo; // r4
    u32 nCommandHi; // r5
    u32* pABI32; // r1+0x28
    u32* pABILast32; // r30
    u32 nSize; // r28

    // References
    // -> static s32 nFirstTime$2148;
}

// Range: 0x80087520 -> 0x800887E8
static s32 rspInitAudioDMEM2(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Range: 0x80086BE8 -> 0x80087520
static s32 rspAADPCMDec2Fast(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r19
    u8 ucControl; // r6
    char* pHeader; // r31
    s16* pStateAddress; // r1+0x60
    s16 anIData0; // r19
    s32 nDMEMOut; // r30
    s32 nCount; // r29
    s32 nSrcAddress; // r5
    s32 nOptPred; // r7
    s32 nVScale; // r19
    s32 i; // r1+0x8
    u32 dwDecodeSelect; // r1+0x8
    u32 n; // r10
    s32 nA; // r11
    s32 nB; // r12
    s16 nSamp1; // r27
    s16 nSamp2; // r26
    s16* pTempStateAddr; // r1+0x50
    s16 nibble[4]; // r1+0x48
    s32 nOutput; // r19
}

// Erased
static s32 rspAADPCMDec2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r23
    char* pDMEM8; // r1+0x110
    s32 anCoef[8]; // r1+0xF0
    s16 anIData1[8]; // r1+0xC0
    s16 anOData0[8]; // r1+0xB0
    s16* pStateAddress; // r1+0xAC
    s16* pDMEM16; // r3
    s16 anOData1[8]; // r1+0x9C
    s16 anIData0[8]; // r1+0x8C
    s16 anInputVec[10]; // r1+0x78
    s32 nDMEMIn8; // r18
    s32 nDMEMOut; // r30
    s32 nCount; // r19
    s32 nSrcAddress; // r1+0x8
    s32 nOptPred; // r23
    s32 nHeaderBase8; // r1+0x8
    s32 nVScale; // r29
    s32 nScaleI; // r22
    s32 i; // r1+0x8
    s32 nHeader; // r25
    s32 nTIndex; // r1+0x8
    s16* pTempStateAddr; // r1+0x74
}

// Erased
static s32 rspAClearBuffer2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r1+0x10
}

// Range: 0x8008691C -> 0x80086BE8
static s32 rspANoise2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r23
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u32 nDest; // r26
    u32 nSource; // r25
    u32 nCount; // r24
    u32 i; // r12
    u32 j; // r5
    s16 vIn[16]; // r1+0x78
    s16 vOut[16]; // r1+0x58
    s64 accumulator[8]; // r1+0x18
}

// Range: 0x800868B0 -> 0x8008691C
static s32 rspANMix2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u32 nCount; // r5
    u32 i; // r1+0x0
    s16* inP; // r6
    s32 out; // r5
}

// Range: 0x80086680 -> 0x800868B0
static s32 rspAResample2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s16* srcP; // r30
    s16* dstP; // r29
    s16 lastValue; // r6
    u16 nCount; // r28
    u16 i; // r7
    s32 nSrcStep; // r1+0x8
    s32 nCursorPos; // r8
    u32 scratch; // r1+0x8
    u8 flags; // r27
    s16* pData; // r1+0x30
}

// Erased
static s32 rspASResample2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    s32 outp; // r7
    s32 outCount; // r6
    s32 pitchSpeed; // r8
    s32 i; // r9
    s32 mainCounter; // r10
}

// Range: 0x800858D0 -> 0x80086680
static s32 rspAFirFilter2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r16

    // Local variables
    s32 filterState; // r1+0x8
    s32 filterTable; // r27
    s32 i; // r1+0x8
    s32 pointer; // r19
    void* pData; // r1+0x114
    s16* pStateAddress; // r29
    s16 flag; // r1+0x8
    s16 vANS[8]; // r1+0x104
    s16 vOLD[8]; // r1+0xF4
    s16 vTP1[8]; // r1+0xE4
    s16 vT0[8]; // r1+0xD4
    s32 accumulator[8]; // r1+0xB4
    s32 temp32[8]; // r1+0x94
    s32 stateAddr; // r1+0x8
    s16 anMatrix[8]; // r1+0x84
    s16 anInputVec[15]; // r1+0x64

    // References
    // -> static s32 counter$2409;
}

// Erased
static s32 rspASetBuffer2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u16 nDMEMIn; // r1+0x0
    u16 nDMEMOut; // r5
    u16 nCount; // r1+0x0
}

// Erased
static s32 rspAWMEMCopy2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10
}

// Erased
static s32 rspADMEMMove2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r1+0x10
}

// Erased
static s32 rspALoadADPCM2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r25

    // Local variables
    void* pData; // r1+0x20
}

// Range: 0x80085848 -> 0x800858D0
static s32 rspAMix2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u32 i; // r1+0x0
    u32 nCount; // r7
    s16* srcP; // r8
    s32 outData32; // r6
}

// Range: 0x800855FC -> 0x80085848
static s32 rspAInterleave2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s32 outp; // r6
    s32 inpr; // r1+0x8
    s32 inpl; // r1+0x8
    s32 count; // r7
    s32 i; // r1+0x8
}

// Range: 0x800854F0 -> 0x800855FC
static s32 rspADistFilter2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r26
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s16 dpow; // r7
    s32 i; // r27
    s64 mult; // r3
}

// Erased
static s32 rspASetLoop2(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
}

// Erased
static s32 rspADMEMCopy2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10
}

// Erased
static s32 rspAHalfCut2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s32 count; // r1+0x8
    s32 outp; // r1+0x8
    s32 inpp; // r7
    s32 i; // r8
}

// Erased
static s32 rspASetEnvParam2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    s16 temp; // r7
}

// Erased
static s32 rspASetEnvParam22(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4

    // Local variables
    s16 tmp; // r6
}

// Range: 0x80085218 -> 0x800854F0
static s32 rspAEnvMixer2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s16 vStep[8]; // r1+0x3C
    u16 vParams[8]; // r1+0x2C
    s32 i; // r28
    s32 j; // r27
    s32 inpp; // r26
    s32 outL; // r25
    s32 outR; // r24
    s32 outFL; // r23
    s32 outFR; // r22
    s32 count; // r21
    s32 temp; // r1+0x8
    s32 id; // r1+0x8
    s32 waveL; // r20
    s32 waveR; // r19
    s32 waveI; // r15
    s32 srcL; // r18
    s32 srcR; // r17
    s32 srcFXL; // r16
    s32 srcFXR; // r10
}

// Erased
static s32 rspALoadBuffer2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Erased
static s32 rspASaveBuffer2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Range: 0x80084984 -> 0x80085218
static s32 rspAPCM8Dec2(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r25

    // Local variables
    s32 inpp; // r31
    s32 outp; // r30
    s32 count; // r26
    s16 flags; // r1+0x8
    s16 vtmp0[8]; // r1+0x60
    s16 vtmp1[8]; // r1+0x50
    s32 i; // r1+0x8
    s32 j; // r1+0x8
    s32 stateAddr; // r5
    s32 s; // r1+0x8
    void* pData; // r1+0x4C
    s16* pStateAddress; // r29
    s16* pTempStateAddr; // r7
}

// Range: 0x8008429C -> 0x80084984
static s32 rspParseABI2(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    u32 nCommandLo; // r4
    u32 nCommandHi; // r30
    u32* pABI32; // r1+0x40
    u32* pABILast32; // r29
    u32 nSize; // r23

    // References
    // -> static s32 nFirstTime$2648;
}

// Range: 0x80082E60 -> 0x8008429C
static s32 rspInitAudioDMEM3(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static s32 rspASetEnvParam3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8
}

// Erased
static s32 rspASetEnvParam32(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
}

// Erased
static s32 rspALoadBuffer3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Erased
static s32 rspASaveBuffer3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // u32 nCommandLo; // r4
    // u32 nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Range: 0x80082C2C -> 0x80082E60
static s32 rspAEnvMixer3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u16 vParams[8]; // r1+0x20
    s32 i; // r27
    s32 j; // r1+0x8
    s32 inpp; // r26
    s32 outL; // r25
    s32 outR; // r24
    s32 outFL; // r23
    s32 outFR; // r22
    s32 count; // r21
    s32 id; // r1+0x8
    s32 waveL; // r20
    s32 waveR; // r19
    s32 waveI; // r19
    s32 srcL; // r18
    s32 srcR; // r17
    s32 srcFXL; // r16
    s32 srcFXR; // r12
}

// Erased
static s32 rspAHalfCut3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    s32 count; // r1+0x8
    s32 outp; // r1+0x8
    s32 inpp; // r7
    s32 i; // r8
}

// Range: 0x80082B94 -> 0x80082C2C
static s32 rspAMix3(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4
    // u32 nCommandHi; // r1+0x8

    // Local variables
    u32 i; // r1+0x0
    u32 nCount; // r8
    s16* srcP; // r4
    s32 outData32; // r6
}

// Erased
static s32 rspADMEMCopy(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10
}

// Range: 0x80082624 -> 0x80082B94
static s32 rspParseABI3(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    u32 nCommandLo; // r4
    u32 nCommandHi; // r30
    u32* pABI32; // r1+0x38
    u32* pABILast32; // r29
    u32 nSize; // r23

    // References
    // -> static s32 nFirstTime$2757;
}

// Range: 0x800811C0 -> 0x80082624
static s32 rspInitAudioDMEM4(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static s32 rspARingFilter4() {}

// Erased
static s32 rspAInterleave4(struct __anon_0x5845E* pRSP, u32 nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // u32 nCommandLo; // r1+0x4

    // Local variables
    u32 iIndex; // r1+0x0
    u32 iIndex2; // r9
}

// Erased
static s32 rspADMEMMove4(struct __anon_0x5845E* pRSP, u32 nCommandLo, u32 nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u32 nCommandLo; // r1+0xC
    // u32 nCommandHi; // r1+0x10

    // Local variables
    u16 nDMEMOut; // r1+0x8
    u16 nCount; // r4
    u32 nDMEMIn; // r1+0x8
}

// Range: 0x80080AA4 -> 0x800811C0
static s32 rspParseABI4(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    u32 nCommandLo; // r4
    u32 nCommandHi; // r30
    u32* pABI32; // r1+0x40
    u32* pABILast32; // r29
    u32 nSize; // r23

    // References
    // -> static s32 nFirstTime$2796;
}
