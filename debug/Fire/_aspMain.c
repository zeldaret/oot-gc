/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_aspMain.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80080AA4 -> 0x8008CF0C
*/

#include "dolphin/types.h"

// Range: 0x8008BBDC -> 0x8008CF0C
static int rspInitAudioDMEM1(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Range: 0x8008B768 -> 0x8008BBDC
int rspDotProduct8x15MatrixBy15x1Vector(s16* matrix, s16* vectorIn, s16* vectorOut) {
    // Parameters
    // s16* matrix; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14

    // Local variables
    int sum; // r12
    int vec1; // r1+0x8
    int vec2; // r1+0x8
    int vec3; // r1+0x8
    int vec4; // r1+0x8
    int vec5; // r1+0x8
    int vec6; // r1+0x8
    int vec7; // r1+0x8
    int vec8; // r31
    int vec9; // r30
    int vec10; // r29
    int vec11; // r28
    int vec12; // r27
    int vec13; // r26
    int vec14; // r5
}

// Erased
static int rspMultADPCMCoef1(struct __anon_0x5845E* pRSP, int* matrix, s16* vectorIn, s16* vectorOut, int nOptPred) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // int* matrix; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14
    // int nOptPred; // r1+0x18

    // Local variables
    int sum; // r12
    int vec0; // r1+0x8
    int vec1; // r1+0x8
    int vec2; // r26
    int vec3; // r25
    int vec4; // r24
    int vec5; // r23
    int vec6; // r22
    int vec7; // r21
    int vec8; // r20
}

// Range: 0x8008B378 -> 0x8008B768
int rspMultPolef(s16 (*matrix)[8], s16* vectorIn, s16* vectorOut) {
    // Parameters
    // s16 (* matrix)[8]; // r1+0xC
    // s16* vectorIn; // r1+0x10
    // s16* vectorOut; // r1+0x14

    // Local variables
    int sum; // r22
    int vec0; // r1+0x8
    int vec1; // r1+0x8
    int vec2; // r8
    int vec3; // r9
    int vec4; // r10
    int vec5; // r11
    int vec6; // r12
    int vec7; // r31
    int vec8; // r5
    int vec9; // r1+0x8
}

// Erased
static int rspDumpDMEMToFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28

    // Local variables
    struct tXL_FILE* fp; // r1+0x50
    int i; // r30
    unsigned int nStartAddress; // r29
    unsigned int nSize; // r1+0x4C
    char acDMEMLine[64]; // r1+0xC
}

// Erased
static int rspDumpMotorolaSDMEMTOFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r27

    // Local variables
    struct tXL_FILE* fp; // r1+0x220
    int i; // r29
    unsigned int nStartAddress; // r28
    unsigned int nSize; // r1+0x21C
    char acDMEMLine[512]; // r1+0x1C
}

// Erased
static int rspDumpBinaryDMEMToFile(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29

    // Local variables
    struct tXL_FILE* fp; // r1+0x10
    int i; // r30
    unsigned int nSize; // r1+0xC
}

// Erased
static int rspLoadADPCMCoefRow(struct __anon_0x5845E* pRSP, unsigned int nCoefIndex, unsigned int nOptPred) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCoefIndex; // r6
    // unsigned int nOptPred; // r1+0x10
}

// Range: 0x8008B1FC -> 0x8008B378
static int rspLoadADPCMCoefTable1(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r3

    // Local variables
    unsigned int j; // r1+0x8
    unsigned int nCoefIndex; // r5
}

// Range: 0x8008B080 -> 0x8008B1FC
static int rspLoadADPCMCoefTable2(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r3

    // Local variables
    unsigned int j; // r1+0x8
    unsigned int nCoefIndex; // r5
}

// Erased
static int rspALoadBuffer1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC

    // Local variables
    void* pData; // r1+0x14
    int nAddress; // r5
}

// Range: 0x8008A7E0 -> 0x8008B080
static int rspAADPCMDec1Fast(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r21
    u8 ucControl; // r6
    char* pHeader; // r31
    s16* pStateAddress; // r1+0x60
    s16 anIData0; // r23
    int nDMEMOut; // r30
    int nCount; // r29
    int nSrcAddress; // r5
    int nOptPred; // r7
    int nVScale; // r1+0x8
    int i; // r1+0x8
    unsigned int dwDecodeSelect; // r1+0x8
    unsigned int n; // r1+0x8
    int nA; // r8
    int nB; // r9
    s16 nSamp1; // r10
    s16 nSamp2; // r1+0x8
    s16* pTempStateAddr; // r1+0x4C
    int nOutput; // r10
}

// Erased
static int rspAADPCMDec1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r20
    char* pDMEM8; // r27
    char* pHeader; // r1+0xD8
    int anCoef[8]; // r1+0xAC
    s16 anIData0[8]; // r1+0x8C
    s16 anOData0[8]; // r1+0x7C
    s16* pStateAddress; // r1+0x78
    s16* pDMEM16; // r4
    s16 anInputVec[10]; // r1+0x64
    int nDMEMOut; // r30
    int nCount; // r14
    int nSrcAddress; // r1+0x8
    int nOptPred; // r1+0x8
    int nVScale; // r1+0x8
    int nScaleI; // r4
    int i; // r1+0x8
    int nHeader; // r23
    int nToggle; // r1+0xD4
    int nTIndex; // r1+0x8
    s16* pTempStateAddr; // r1+0x60
}

// Range: 0x80089E7C -> 0x8008A7E0
static int rspAPoleFilter1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r25
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

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
    int nDMEMIn; // r28
    int nDMEMOut; // r27
    int nCount; // r26
    int nSrcAddress; // r5
}

// Erased
static int rspAClearBuffer1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r1+0x10
}

// Range: 0x800892A4 -> 0x80089E7C
static int rspAEnvMixer1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r23
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r1+0x104
    unsigned int s; // r1+0x8
    s16* pStateAddress; // r1+0x100
    u16 anRamp[8]; // r1+0xA8
    int envVolRateL; // r1+0xFC
    int envVolRateR; // r1+0xF8
    int envVolFinalL; // r16
    int envVolFinalR; // r18
    int volVecL[8]; // r1+0x88
    int volVecR[8]; // r1+0x68
    s16 anOutL; // r24
    s16 anOutR; // r20
    s16 anAuxL; // r24
    s16 anAuxR; // r1+0x8
    s16 anIn; // r1+0x8
    unsigned int nInptr; // r1+0xF4
    unsigned int nOutptrL; // r1+0xF0
    unsigned int nOutptrR; // r1+0xEC
    unsigned int nAuxptrL; // r1+0xE8
    unsigned int nAuxptrR; // r1+0xE4
    unsigned int i; // r4
    unsigned int nSrcAddress; // r1+0x8
    unsigned int nLoopCtl; // r1+0xE0
    int nUpDownVolL; // r1+0x8
    int nUpDownVolR; // r1+0x8
    void* pData; // r1+0x58
    int* dataP; // r5
    s64 tempL; // r1+0xD8
    s64 tempR; // r1+0xD0
    s64 totalL; // r1+0xC8
    s64 totalR; // r30
    s64 resultL; // r1+0x8
    s64 resultR; // r6
    int volL; // r1+0x8
    int volR; // r27
    s64 temp; // r0
    int* dataP; // r3
}

// Erased
static int rspAInterleave1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4

    // Local variables
    u16 nLeft; // r1+0x0
    unsigned int iIndex; // r1+0x0
    unsigned int iIndex2; // r9
}

// Range: 0x8008920C -> 0x800892A4
static int rspAMix1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    unsigned int i; // r1+0x0
    unsigned int nCount; // r8
    s16* srcP; // r4
    int outData32; // r6
}

// Range: 0x80088F14 -> 0x8008920C
static int rspAResample1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r26
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    s16* srcP; // r30
    s16* dstP; // r29
    s16 lastValue; // r7
    u16 nCount; // r28
    u16 i; // r10
    int nSrcStep; // r1+0x8
    int nCursorPos; // r8
    int nExtra; // r3
    unsigned int scratch; // r1+0x8
    u8 flags; // r27
    s16* pData; // r1+0x34
}

// Erased
static int rspASaveBuffer1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC

    // Local variables
    unsigned int nSize; // r1+0x18
    unsigned int* pData; // r1+0x14
    int nAddress; // r5
}

// Erased
static int rspASegment1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
}

// Range: 0x80088E0C -> 0x80088F14
static int rspASetBuffer1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    u16 nDMEMIn; // r5
    u16 nDMEMOut; // r6
    u16 nCount; // r4
}

// Range: 0x80088D74 -> 0x80088E0C
static int rspASetVolume1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    u16 nFlags; // r1+0x0
    u16 v; // r5
    u16 t; // r7
    u16 r; // r8
}

// Erased
static int rspASetLoop1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
}

// Erased
static int rspADMEMMove1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u16 nDMEMOut; // r1+0x8
    u16 nCount; // r5
    unsigned int nDMEMIn; // r1+0x8
}

// Erased
static int rspALoadADPCM1(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    void* pData; // r1+0x20
    unsigned int nCount; // r25
    int nAddress; // r5
}

// Range: 0x80088B48 -> 0x80088D74
static int rspParseABI(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x575BD* pTask; // r31

    // Local variables
    u8* pFUCode; // r1+0x1C
    unsigned int nCheckSum; // r4
}

// Range: 0x800887E8 -> 0x80088B48
static int rspParseABI1(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r29
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    unsigned int nCommandLo; // r4
    unsigned int nCommandHi; // r5
    unsigned int* pABI32; // r1+0x28
    unsigned int* pABILast32; // r30
    unsigned int nSize; // r28

    // References
    // -> static int nFirstTime$2148;
}

// Range: 0x80087520 -> 0x800887E8
static int rspInitAudioDMEM2(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Range: 0x80086BE8 -> 0x80087520
static int rspAADPCMDec2Fast(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r19
    u8 ucControl; // r6
    char* pHeader; // r31
    s16* pStateAddress; // r1+0x60
    s16 anIData0; // r19
    int nDMEMOut; // r30
    int nCount; // r29
    int nSrcAddress; // r5
    int nOptPred; // r7
    int nVScale; // r19
    int i; // r1+0x8
    unsigned int dwDecodeSelect; // r1+0x8
    unsigned int n; // r10
    int nA; // r11
    int nB; // r12
    s16 nSamp1; // r27
    s16 nSamp2; // r26
    s16* pTempStateAddr; // r1+0x50
    s16 nibble[4]; // r1+0x48
    int nOutput; // r19
}

// Erased
static int rspAADPCMDec2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u8 nFlags; // r23
    char* pDMEM8; // r1+0x110
    int anCoef[8]; // r1+0xF0
    s16 anIData1[8]; // r1+0xC0
    s16 anOData0[8]; // r1+0xB0
    s16* pStateAddress; // r1+0xAC
    s16* pDMEM16; // r3
    s16 anOData1[8]; // r1+0x9C
    s16 anIData0[8]; // r1+0x8C
    s16 anInputVec[10]; // r1+0x78
    int nDMEMIn8; // r18
    int nDMEMOut; // r30
    int nCount; // r19
    int nSrcAddress; // r1+0x8
    int nOptPred; // r23
    int nHeaderBase8; // r1+0x8
    int nVScale; // r29
    int nScaleI; // r22
    int i; // r1+0x8
    int nHeader; // r25
    int nTIndex; // r1+0x8
    s16* pTempStateAddr; // r1+0x74
}

// Erased
static int rspAClearBuffer2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r1+0x10
}

// Range: 0x8008691C -> 0x80086BE8
static int rspANoise2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r23
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    unsigned int nDest; // r26
    unsigned int nSource; // r25
    unsigned int nCount; // r24
    unsigned int i; // r12
    unsigned int j; // r5
    s16 vIn[16]; // r1+0x78
    s16 vOut[16]; // r1+0x58
    s64 accumulator[8]; // r1+0x18
}

// Range: 0x800868B0 -> 0x8008691C
static int rspANMix2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    unsigned int nCount; // r5
    unsigned int i; // r1+0x0
    s16* inP; // r6
    int out; // r5
}

// Range: 0x80086680 -> 0x800868B0
static int rspAResample2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    s16* srcP; // r30
    s16* dstP; // r29
    s16 lastValue; // r6
    u16 nCount; // r28
    u16 i; // r7
    int nSrcStep; // r1+0x8
    int nCursorPos; // r8
    unsigned int scratch; // r1+0x8
    u8 flags; // r27
    s16* pData; // r1+0x30
}

// Erased
static int rspASResample2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    int outp; // r7
    int outCount; // r6
    int pitchSpeed; // r8
    int i; // r9
    int mainCounter; // r10
}

// Range: 0x800858D0 -> 0x80086680
static int rspAFirFilter2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r16

    // Local variables
    int filterState; // r1+0x8
    int filterTable; // r27
    int i; // r1+0x8
    int pointer; // r19
    void* pData; // r1+0x114
    s16* pStateAddress; // r29
    s16 flag; // r1+0x8
    s16 vANS[8]; // r1+0x104
    s16 vOLD[8]; // r1+0xF4
    s16 vTP1[8]; // r1+0xE4
    s16 vT0[8]; // r1+0xD4
    int accumulator[8]; // r1+0xB4
    int temp32[8]; // r1+0x94
    int stateAddr; // r1+0x8
    s16 anMatrix[8]; // r1+0x84
    s16 anInputVec[15]; // r1+0x64

    // References
    // -> static int counter$2409;
}

// Erased
static int rspASetBuffer2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    u16 nDMEMIn; // r1+0x0
    u16 nDMEMOut; // r5
    u16 nCount; // r1+0x0
}

// Erased
static int rspAWMEMCopy2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10
}

// Erased
static int rspADMEMMove2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r1+0x10
}

// Erased
static int rspALoadADPCM2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r25

    // Local variables
    void* pData; // r1+0x20
}

// Range: 0x80085848 -> 0x800858D0
static int rspAMix2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    unsigned int i; // r1+0x0
    unsigned int nCount; // r7
    s16* srcP; // r8
    int outData32; // r6
}

// Range: 0x800855FC -> 0x80085848
static int rspAInterleave2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    int outp; // r6
    int inpr; // r1+0x8
    int inpl; // r1+0x8
    int count; // r7
    int i; // r1+0x8
}

// Range: 0x800854F0 -> 0x800855FC
static int rspADistFilter2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r26
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    s16 dpow; // r7
    int i; // r27
    s64 mult; // r3
}

// Erased
static int rspASetLoop2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
}

// Erased
static int rspADMEMCopy2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10
}

// Erased
static int rspAHalfCut2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    int count; // r1+0x8
    int outp; // r1+0x8
    int inpp; // r7
    int i; // r8
}

// Erased
static int rspASetEnvParam2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    s16 temp; // r7
}

// Erased
static int rspASetEnvParam22(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4

    // Local variables
    s16 tmp; // r6
}

// Range: 0x80085218 -> 0x800854F0
static int rspAEnvMixer2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    s16 vStep[8]; // r1+0x3C
    u16 vParams[8]; // r1+0x2C
    int i; // r28
    int j; // r27
    int inpp; // r26
    int outL; // r25
    int outR; // r24
    int outFL; // r23
    int outFR; // r22
    int count; // r21
    int temp; // r1+0x8
    s32 id; // r1+0x8
    int waveL; // r20
    int waveR; // r19
    int waveI; // r15
    int srcL; // r18
    int srcR; // r17
    int srcFXL; // r16
    int srcFXR; // r10
}

// Erased
static int rspALoadBuffer2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Erased
static int rspASaveBuffer2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Range: 0x80084984 -> 0x80085218
static int rspAPCM8Dec2(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r25

    // Local variables
    int inpp; // r31
    int outp; // r30
    int count; // r26
    s16 flags; // r1+0x8
    s16 vtmp0[8]; // r1+0x60
    s16 vtmp1[8]; // r1+0x50
    int i; // r1+0x8
    int j; // r1+0x8
    int stateAddr; // r5
    int s; // r1+0x8
    void* pData; // r1+0x4C
    s16* pStateAddress; // r29
    s16* pTempStateAddr; // r7
}

// Range: 0x8008429C -> 0x80084984
static int rspParseABI2(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    unsigned int nCommandLo; // r4
    unsigned int nCommandHi; // r30
    unsigned int* pABI32; // r1+0x40
    unsigned int* pABILast32; // r29
    unsigned int nSize; // r23

    // References
    // -> static int nFirstTime$2648;
}

// Range: 0x80082E60 -> 0x8008429C
static int rspInitAudioDMEM3(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static int rspASetEnvParam3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8
}

// Erased
static int rspASetEnvParam32(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
}

// Erased
static int rspALoadBuffer3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Erased
static int rspASaveBuffer3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // unsigned int nCommandLo; // r4
    // unsigned int nCommandHi; // r31

    // Local variables
    void* pData; // r1+0x14
}

// Range: 0x80082C2C -> 0x80082E60
static int rspAEnvMixer3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u16 vParams[8]; // r1+0x20
    int i; // r27
    int j; // r1+0x8
    int inpp; // r26
    int outL; // r25
    int outR; // r24
    int outFL; // r23
    int outFR; // r22
    int count; // r21
    s32 id; // r1+0x8
    int waveL; // r20
    int waveR; // r19
    int waveI; // r19
    int srcL; // r18
    int srcR; // r17
    int srcFXL; // r16
    int srcFXR; // r12
}

// Erased
static int rspAHalfCut3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    int count; // r1+0x8
    int outp; // r1+0x8
    int inpp; // r7
    int i; // r8
}

// Range: 0x80082B94 -> 0x80082C2C
static int rspAMix3(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4
    // unsigned int nCommandHi; // r1+0x8

    // Local variables
    unsigned int i; // r1+0x0
    unsigned int nCount; // r8
    s16* srcP; // r4
    int outData32; // r6
}

// Erased
static int rspADMEMCopy(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10
}

// Range: 0x80082624 -> 0x80082B94
static int rspParseABI3(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    unsigned int nCommandLo; // r4
    unsigned int nCommandHi; // r30
    unsigned int* pABI32; // r1+0x38
    unsigned int* pABILast32; // r29
    unsigned int nSize; // r23

    // References
    // -> static int nFirstTime$2757;
}

// Range: 0x800811C0 -> 0x80082624
static int rspInitAudioDMEM4(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static int rspARingFilter4() {}

// Erased
static int rspAInterleave4(struct __anon_0x5845E* pRSP, unsigned int nCommandLo) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0
    // unsigned int nCommandLo; // r1+0x4

    // Local variables
    unsigned int iIndex; // r1+0x0
    unsigned int iIndex2; // r9
}

// Erased
static int rspADMEMMove4(struct __anon_0x5845E* pRSP, unsigned int nCommandLo, unsigned int nCommandHi) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // unsigned int nCommandLo; // r1+0xC
    // unsigned int nCommandHi; // r1+0x10

    // Local variables
    u16 nDMEMOut; // r1+0x8
    u16 nCount; // r4
    unsigned int nDMEMIn; // r1+0x8
}

// Range: 0x80080AA4 -> 0x800811C0
static int rspParseABI4(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r5

    // Local variables
    unsigned int nCommandLo; // r4
    unsigned int nCommandHi; // r30
    unsigned int* pABI32; // r1+0x40
    unsigned int* pABILast32; // r29
    unsigned int nSize; // r23

    // References
    // -> static int nFirstTime$2796;
}
