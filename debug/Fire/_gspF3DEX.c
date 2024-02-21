/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_gspF3DEX.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80074454 -> 0x80077850
*/

#include "dolphin/types.h"

// Erased
static s32 MulMatrices(f32 (*aOutMatrix)[4], f32 (*aLeftMatrix)[4], f32 (*aRightMatrix)[4]) {
    // Parameters
    // f32 (* aOutMatrix)[4]; // r3
    // f32 (* aLeftMatrix)[4]; // r4
    // f32 (* aRightMatrix)[4]; // r5

    // Local variables
    s32 i; // r8
    s32 j; // r1+0x0
}

// Range: 0x80077790 -> 0x80077850
static s32 rspSetGeometryMode1(struct __anon_0x5845E* pRSP, s32 nMode) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nMode; // r1+0xC

    // Local variables
    s32 nModeFrame; // r5
}

// Range: 0x8007610C -> 0x80077790
static s32 rspParseGBI_F3DEX1(struct __anon_0x5845E* pRSP, u64** ppnGBI, s32* pbDone) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u64** ppnGBI; // r27
    // s32* pbDone; // r24

    // Local variables
    f32 matrix[4][4]; // r1+0x3B0
    struct __anon_0x5EBE0 primitive; // r1+0xAC
    u32 iVertex; // r4
    u32 bDone; // r24
    u64* pnGBI; // r28
    u32 nCommandLo; // r6
    u32 nCommandHi; // r7
    struct __anon_0x5A89F* pFrame; // r30
    s32 nAddress; // r5
    s32 nAddress; // r24
    s32 nAddress; // r24
    s32 nAddress; // r24
    s32 bPush; // r24
    u8 nSid2D; // r1+0x8
    u32 nDLAdrs; // r7
    u32 nFlag2D; // r1+0x8
    union __anon_0x5F2FB bg; // r1+0x80
    s32 nAddress; // r4
    s32 nMode; // r24
    s32 nAddress; // r26
    s32 nMode; // r1+0x78
    s32 nAddress; // r5
    s32 nAddress; // r5
    void* pData; // r1+0x74
    s32 nAddress; // r5
    void* pData; // r1+0x6C
    s32 nAddress; // r5
    void* pData; // r1+0x68
    s32 nAddress; // r5
    char* pData; // r1+0x64
    s32 iLight; // r24
    s32 nAddress; // r5
    s32 nAddress; // r24
    s32 nAddress; // r5
    void* pBuffer; // r1+0x60
    s32 nCount; // r6
    s32 iVertex0; // r5
    s32 nAddress; // r5
    s32 nAddress; // r5
    s32 nAddress; // r5
    u32 nVertexStart; // r4
    u32 nVertexEnd; // r5
    s32 nWhere; // r1+0x8
    s32 nData1; // r8
    s32 nData2; // r1+0x8
    s32 iRow; // r3
    s32 iCol; // r4
    u32 nSid; // r1+0x8
    s32 nLight; // r1+0x8
    u32 nData; // r1+0x8
    u32 nSize; // r3
    u32 nMove; // r5
    u32 nData; // r1+0x8
    u32 nSize; // r3
    u32 nMove; // r5
    u32 nValue; // r1+0x8
    struct __anon_0x575BD* pTask; // r4
    s32 nAddress; // r5
    s32 iVertex; // r4
    s32 nVal; // r1+0x8

    // References
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}

// Range: 0x80076024 -> 0x8007610C
static s32 rspGeometryMode(struct __anon_0x5845E* pRSP, s32 nSet, s32 nClr) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 nSet; // r1+0xC
    // s32 nClr; // r1+0x10

    // Local variables
    s32 nMode; // r6
}

// Range: 0x80074454 -> 0x80076024
static s32 rspParseGBI_F3DEX2(struct __anon_0x5845E* pRSP, u64** ppnGBI, s32* pbDone) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r31
    // u64** ppnGBI; // r27
    // s32* pbDone; // r25

    // Local variables
    s32 iVertex; // r4
    s32 bDone; // r25
    f32 matrix[4][4]; // r1+0x410
    struct __anon_0x5EBE0 primitive; // r1+0x10C
    u64* pnGBI; // r28
    u32 nCommandLo; // r6
    u32 nCommandHi; // r1+0x8
    struct __anon_0x5A89F* pFrame; // r30
    u32 nData; // r1+0x8
    u32 nSize; // r6
    u32 nMove; // r5
    u32 nData; // r1+0x8
    u32 nSize; // r6
    u32 nMove; // r5
    u32 nValue; // r1+0x8
    struct __anon_0x575BD* pTask; // r4
    s32 nAddress; // r5
    s32 nAddress; // r5
    s32 nLength; // r27
    s32 nOffset; // r28
    s32 nId; // r25
    s32 nFlag; // r26
    s32 nAddress; // r29
    void* pData; // r1+0x104
    u16* pnData16; // r3
    s16 nFogStart; // r1+0x8
    s16 nFogEnd; // r1+0x8
    s32 nDelta; // r3
    s32 nStart; // r4
    char* pLight; // r1+0x100
    u32 iIndex; // r25
    s32 bFound; // r5
    void* pData; // r1+0xFC
    s32 nAddress; // r5
    void* pData; // r1+0xF4
    s32 iLight; // r25
    s32 nAddress; // r5
    s32 nAddress; // r25
    u32 nSid; // r1+0x8
    s32 nLight; // r1+0x8
    s32 nAddress; // r5
    s32 nMode; // r25
    s32 nAddress; // r27
    s32 nSet; // r4
    s32 nClr; // r5
    s32 iMatrix; // r25
    s32 nCount; // r26
    s32 nVertices; // r26
    s32 nSrcAdrs; // r1+0x8
    s32 nDestAdrs; // r27
    s32 iCount; // r28
    s32 bFound; // r9
    u32 iVtxIndex; // r10
    struct __anon_0x5EC3E destVtx; // r1+0x9C
    s32 nAddress; // r5
    char* pBuffer; // r1+0x94
    s32 nCount; // r25
    s32 iVertex0; // r26
    s32 nAddress; // r5
    s32 nAddress; // r5
    s32 iVertex; // r4
    s32 nVal; // r1+0x8
    u32 nVertexStart; // r4
    u32 nVertexEnd; // r5
    s32 nAddress; // r5
    s32 nAddress; // r25
    s32 nAddress; // r25
    s32 nAddress; // r25
    s32 nAddress; // r25
    union __anon_0x5F2FB bg; // r1+0x68
    union __anon_0x5F2FB bg; // r1+0x40
    char cTempAlpha; // r25
    s32 nAddress; // r5
    char cTempAlpha; // r25
    s32 bPush; // r27
    u8 nSid2D; // r1+0x8
    u32 nDLAdrs; // r6
    u32 nFlag2D; // r1+0x8

    // References
    // -> struct __anon_0x5E98D* gpSystem;
    // -> static u8 flagBilerp;
    // -> static u16 scissorY1;
    // -> static u16 scissorX1;
    // -> static u16 scissorY0;
    // -> static u16 scissorX0;
}
