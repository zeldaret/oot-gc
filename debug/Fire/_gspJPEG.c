/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_gspJPEG.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8007AC6C -> 0x80080AA4
*/

#include "dolphin/types.h"

// Range: 0x800801C0 -> 0x80080AA4
static s32 rspCreateJPEGArrays(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static s32 rspDestroyJPEGArrays() {}

// Erased
static void rspConvertBufferToRGBA(u8* buf, struct __anon_0x58360* rgba) {
    // Parameters
    // u8* buf; // r1+0x4
    // struct __anon_0x58360* rgba; // r1+0x8
}

// Range: 0x80080028 -> 0x800801C0
static void rspConvertRGBAtoYUV(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 i; // r30
    s32 j; // r1+0x8
    s32 Y; // r20
    s32 U; // r20
    s32 V; // r12
}

// Range: 0x8007F938 -> 0x80080028
static void rspYUVtoDCTBuf(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0

    // Local variables
    s32 i; // r1+0x0
}

// Range: 0x8007F668 -> 0x8007F938
static void rspDCT(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 c; // r1+0xA4
    s32 i; // r1+0xA0
    s32 j; // r1+0x8
    s32 dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007F4EC -> 0x8007F668
static void rspQuantize(struct __anon_0x5845E* pRSP, s32 scale) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 scale; // r1+0xC

    // Local variables
    s32 c; // r29
    s32 i; // r28
    s32 j; // r27
    s16 q; // r6
    s16 s; // r1+0x8
}

// Erased
static void rspZigzagData(struct __anon_0x5845E* pRSP, u8** databuf, s32 n, s32* preDc) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u8** databuf; // r1+0xC
    // s32 n; // r1+0x10
    // s32* preDc; // r1+0x14

    // Local variables
    s16 Ac; // r30
    s32 i; // r6
    s32 z; // r7
}

// Erased
static void rspUndoZigzagData(struct __anon_0x5845E* pRSP, u8** databuf, s32 n, s32* preDc) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u8** databuf; // r1+0xC
    // s32 n; // r1+0x10
    // s32* preDc; // r1+0x14

    // Local variables
    s16 Dc; // r12
    s16 Ac; // r12
    s32 i; // r7
    s32 z; // r31
}

// Range: 0x8007F368 -> 0x8007F4EC
void rspUndoQuantize(struct __anon_0x5845E* pRSP, s32 scale) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s32 scale; // r1+0xC

    // Local variables
    s32 c; // r29
    s32 i; // r28
    s32 j; // r27
    s16 q; // r6
    s16 s; // r1+0x8
}

// Range: 0x8007F07C -> 0x8007F368
void rspUndoDCT(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 c; // r1+0xA4
    s32 i; // r1+0xA0
    s32 j; // r5
    s32 dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007E8F4 -> 0x8007F07C
void rspUndoYUVtoDCTBuf(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 i; // r1+0x8
    s32 j; // r1+0x8
}

// Range: 0x8007E744 -> 0x8007E8F4
void rspFormatYUV(struct __anon_0x5845E* pRSP, char* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // char* imgBuf; // r4

    // Local variables
    s32 i; // r10
    s32 j; // r11
}

// Range: 0x8007DD0C -> 0x8007E744
static s32 rspParseJPEG_Encode(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r19
    // struct __anon_0x575BD* pTask; // r16

    // Local variables
    u8* temp; // r24
    u8* temp2; // r23
    s32 i; // r10
    s32 j; // r11
    s32 x; // r22
    s32 y; // r21
    u8* system_imb; // r1+0x30
    u8* system_cfb; // r1+0x2C
    s32 scale; // r20
}

// Range: 0x8007D4C0 -> 0x8007DD0C
static s32 rspParseJPEG_Decode(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x575BD* pTask; // r20

    // Local variables
    s32 i; // r3
    s32 y; // r25
    u8* temp; // r31
    u8* temp2; // r26
    u64* system_imb; // r1+0x1C
    s32 size; // r21
    s32 scale; // r22
}

// Range: 0x8007D1C8 -> 0x8007D4C0
static s32 rspCreateJPEGArraysZ(struct __anon_0x5845E* pRSP, s32 qYAddress, s32 qCbAddress, s32 qCrAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r24
    // s32 qYAddress; // r4
    // s32 qCbAddress; // r25
    // s32 qCrAddress; // r26
}

// Erased
static s32 rspDestroyJPEGArraysZ() {}

// Range: 0x8007CEF8 -> 0x8007D1C8
static void rspDCTZ(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 c; // r1+0xA4
    s32 i; // r1+0xA0
    s32 j; // r1+0x8
    s32 dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007C8CC -> 0x8007CEF8
static void rspQuantizeZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r1+0xC

    // Local variables
    s32 c; // r12
    s32 i; // r1+0x8
}

// Range: 0x8007C3A4 -> 0x8007C8CC
void rspZigzagDataZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r4

    // Local variables
    s32 c; // r1+0x8
}

// Range: 0x8007BDD8 -> 0x8007C3A4
void rspUndoQuantizeZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r1+0xC

    // Local variables
    s32 c; // r12
    s32 i; // r1+0x8
}

// Range: 0x8007B9B0 -> 0x8007BDD8
void rspUndoZigzagDataZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r4

    // Local variables
    s32 c; // r1+0x8
}

// Range: 0x8007B6E0 -> 0x8007B9B0
void rspUndoDCTZ(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    s32 c; // r1+0xA4
    s32 i; // r1+0xA0
    s32 j; // r5
    s32 dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007B64C -> 0x8007B6E0
s32 rspUndoLoadColorBufferZ(s32 r, s32 g, s32 b, s16* imgBuf, s32 index) {
    // Parameters
    // s32 r; // r3
    // s32 g; // r1+0x8
    // s32 b; // r4
    // s16* imgBuf; // r1+0x10
    // s32 index; // r1+0x14
}

// Range: 0x8007B244 -> 0x8007B64C
s32 rspUndoRecon420Z(struct __anon_0x5845E* pRSP, s16* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // s16* imgBuf; // r29

    // Local variables
    s32 i; // r1+0x8
    s32 j; // r24
    s32 r; // r1+0x8
    s32 g; // r1+0x8
    s32 b; // r1+0x8
    s32 y; // r7
    s32 u; // r5
    s32 v; // r1+0x8
}

// Erased
static s32 rspLoadColorBufferZ(s32* r, s32* g, s32* b, s16* imgBuf, s32 index) {
    // Parameters
    // s32* r; // r1+0x4
    // s32* g; // r1+0x8
    // s32* b; // r1+0xC
    // s16* imgBuf; // r1+0x10
    // s32 index; // r1+0x14
}

// Range: 0x8007AE64 -> 0x8007B244
s32 rspRecon420Z(struct __anon_0x5845E* pRSP, s16* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* imgBuf; // r1+0xC

    // Local variables
    s32 i; // r1+0x10
    s32 j; // r26
    s32 r; // r10
    s32 g; // r7
    s32 b; // r11
    s32 y; // r6
    s32 u; // r9
    s32 v; // r1+0x8
}

// Range: 0x8007AD68 -> 0x8007AE64
static s32 rspParseJPEG_EncodeZ(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r4

    // Local variables
    s32 y; // r31
    s16* temp; // r1+0x8
    s16* temp2; // r30
    u64* system_imb; // r1+0x20
    u32* infoStruct; // r1+0x1C
    s32 size; // r29
}

// Range: 0x8007AC6C -> 0x8007AD68
static s32 rspParseJPEG_DecodeZ(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r4

    // Local variables
    s32 y; // r31
    s16* temp; // r1+0x8
    s16* temp2; // r30
    u64* system_imb; // r1+0x20
    u32* infoStruct; // r1+0x1C
    s32 size; // r29
}
