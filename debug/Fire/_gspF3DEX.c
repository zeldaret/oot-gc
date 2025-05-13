/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_gspF3DEX.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80074454 -> 0x80077850
*/

#include "dolphin/types.h"

// Erased
static int MulMatrices(f32 (*aOutMatrix)[4], f32 (*aLeftMatrix)[4], f32 (*aRightMatrix)[4]) {
    // Parameters
    // f32 (* aOutMatrix)[4]; // r3
    // f32 (* aLeftMatrix)[4]; // r4
    // f32 (* aRightMatrix)[4]; // r5

    // Local variables
    int i; // r8
    int j; // r1+0x0
}

// Range: 0x80077790 -> 0x80077850
static int rspSetGeometryMode1(struct __anon_0x5845E* pRSP, int nMode) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // int nMode; // r1+0xC

    // Local variables
    int nModeFrame; // r5
}

// Range: 0x8007610C -> 0x80077790
static int rspParseGBI_F3DEX1(struct __anon_0x5845E* pRSP, u64** ppnGBI, int* pbDone) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u64** ppnGBI; // r27
    // int* pbDone; // r24

    // Local variables
    f32 matrix[4][4]; // r1+0x3B0
    struct __anon_0x5EBE0 primitive; // r1+0xAC
    unsigned int iVertex; // r4
    unsigned int bDone; // r24
    u64* pnGBI; // r28
    unsigned int nCommandLo; // r6
    unsigned int nCommandHi; // r7
    struct __anon_0x5A89F* pFrame; // r30
    int nAddress; // r5
    int nAddress; // r24
    int nAddress; // r24
    int nAddress; // r24
    int bPush; // r24
    u8 nSid2D; // r1+0x8
    unsigned int nDLAdrs; // r7
    unsigned int nFlag2D; // r1+0x8
    union __anon_0x5F2FB bg; // r1+0x80
    int nAddress; // r4
    int nMode; // r24
    int nAddress; // r26
    int nMode; // r1+0x78
    int nAddress; // r5
    int nAddress; // r5
    void* pData; // r1+0x74
    int nAddress; // r5
    void* pData; // r1+0x6C
    int nAddress; // r5
    void* pData; // r1+0x68
    int nAddress; // r5
    char* pData; // r1+0x64
    int iLight; // r24
    int nAddress; // r5
    int nAddress; // r24
    int nAddress; // r5
    void* pBuffer; // r1+0x60
    int nCount; // r6
    int iVertex0; // r5
    int nAddress; // r5
    int nAddress; // r5
    int nAddress; // r5
    unsigned int nVertexStart; // r4
    unsigned int nVertexEnd; // r5
    int nWhere; // r1+0x8
    int nData1; // r8
    int nData2; // r1+0x8
    int iRow; // r3
    int iCol; // r4
    unsigned int nSid; // r1+0x8
    int nLight; // r1+0x8
    unsigned int nData; // r1+0x8
    unsigned int nSize; // r3
    unsigned int nMove; // r5
    unsigned int nData; // r1+0x8
    unsigned int nSize; // r3
    unsigned int nMove; // r5
    unsigned int nValue; // r1+0x8
    struct __anon_0x575BD* pTask; // r4
    int nAddress; // r5
    int iVertex; // r4
    int nVal; // r1+0x8

    // References
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}

// Range: 0x80076024 -> 0x8007610C
static int rspGeometryMode(struct __anon_0x5845E* pRSP, int nSet, int nClr) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // int nSet; // r1+0xC
    // int nClr; // r1+0x10

    // Local variables
    int nMode; // r6
}

// Range: 0x80074454 -> 0x80076024
static int rspParseGBI_F3DEX2(struct __anon_0x5845E* pRSP, u64** ppnGBI, int* pbDone) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u64** ppnGBI; // r27
    // int* pbDone; // r25

    // Local variables
    int iVertex; // r4
    int bDone; // r25
    f32 matrix[4][4]; // r1+0x410
    struct __anon_0x5EBE0 primitive; // r1+0x10C
    u64* pnGBI; // r28
    unsigned int nCommandLo; // r6
    unsigned int nCommandHi; // r1+0x8
    struct __anon_0x5A89F* pFrame; // r30
    unsigned int nData; // r1+0x8
    unsigned int nSize; // r6
    unsigned int nMove; // r5
    unsigned int nData; // r1+0x8
    unsigned int nSize; // r6
    unsigned int nMove; // r5
    unsigned int nValue; // r1+0x8
    struct __anon_0x575BD* pTask; // r4
    int nAddress; // r5
    int nAddress; // r5
    int nLength; // r27
    int nOffset; // r28
    int nId; // r25
    int nFlag; // r26
    int nAddress; // r29
    void* pData; // r1+0x104
    u16* pnData16; // r3
    s16 nFogStart; // r1+0x8
    s16 nFogEnd; // r1+0x8
    int nDelta; // r3
    int nStart; // r4
    char* pLight; // r1+0x100
    unsigned int iIndex; // r25
    int bFound; // r5
    void* pData; // r1+0xFC
    int nAddress; // r5
    void* pData; // r1+0xF4
    int iLight; // r25
    int nAddress; // r5
    int nAddress; // r25
    unsigned int nSid; // r1+0x8
    int nLight; // r1+0x8
    int nAddress; // r5
    int nMode; // r25
    int nAddress; // r27
    int nSet; // r4
    int nClr; // r5
    int iMatrix; // r25
    int nCount; // r26
    int nVertices; // r26
    int nSrcAdrs; // r1+0x8
    int nDestAdrs; // r27
    int iCount; // r28
    int bFound; // r9
    unsigned int iVtxIndex; // r10
    struct __anon_0x5EC3E destVtx; // r1+0x9C
    int nAddress; // r5
    char* pBuffer; // r1+0x94
    int nCount; // r25
    int iVertex0; // r26
    int nAddress; // r5
    int nAddress; // r5
    int iVertex; // r4
    int nVal; // r1+0x8
    unsigned int nVertexStart; // r4
    unsigned int nVertexEnd; // r5
    int nAddress; // r5
    int nAddress; // r25
    int nAddress; // r25
    int nAddress; // r25
    int nAddress; // r25
    union __anon_0x5F2FB bg; // r1+0x68
    union __anon_0x5F2FB bg; // r1+0x40
    char cTempAlpha; // r25
    int nAddress; // r5
    char cTempAlpha; // r25
    int bPush; // r27
    u8 nSid2D; // r1+0x8
    unsigned int nDLAdrs; // r6
    unsigned int nFlag2D; // r1+0x8

    // References
    // -> struct __anon_0x5E98D* gpSystem;
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}
