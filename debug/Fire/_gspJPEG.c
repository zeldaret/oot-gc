/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\_gspJPEG.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8007AC6C -> 0x80080AA4
*/

#include "dolphin/types.h"

// Range: 0x800801C0 -> 0x80080AA4
static int rspCreateJPEGArrays(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
}

// Erased
static int rspDestroyJPEGArrays() {}

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
    int i; // r30
    int j; // r1+0x8
    s32 Y; // r20
    s32 U; // r20
    s32 V; // r12
}

// Range: 0x8007F938 -> 0x80080028
static void rspYUVtoDCTBuf(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x0

    // Local variables
    int i; // r1+0x0
}

// Range: 0x8007F668 -> 0x8007F938
static void rspDCT(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    int c; // r1+0xA4
    int i; // r1+0xA0
    int j; // r1+0x8
    int dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007F4EC -> 0x8007F668
static void rspQuantize(struct __anon_0x5845E* pRSP, int scale) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // int scale; // r1+0xC

    // Local variables
    int c; // r29
    int i; // r28
    int j; // r27
    s16 q; // r6
    s16 s; // r1+0x8
}

// Erased
static void rspZigzagData(struct __anon_0x5845E* pRSP, u8** databuf, int n, int* preDc) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u8** databuf; // r1+0xC
    // int n; // r1+0x10
    // int* preDc; // r1+0x14

    // Local variables
    s16 Ac; // r30
    int i; // r6
    int z; // r7
}

// Erased
static void rspUndoZigzagData(struct __anon_0x5845E* pRSP, u8** databuf, int n, int* preDc) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // u8** databuf; // r1+0xC
    // int n; // r1+0x10
    // int* preDc; // r1+0x14

    // Local variables
    s16 Dc; // r12
    s16 Ac; // r12
    int i; // r7
    int z; // r31
}

// Range: 0x8007F368 -> 0x8007F4EC
void rspUndoQuantize(struct __anon_0x5845E* pRSP, int scale) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // int scale; // r1+0xC

    // Local variables
    int c; // r29
    int i; // r28
    int j; // r27
    s16 q; // r6
    s16 s; // r1+0x8
}

// Range: 0x8007F07C -> 0x8007F368
void rspUndoDCT(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    int c; // r1+0xA4
    int i; // r1+0xA0
    int j; // r5
    int dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007E8F4 -> 0x8007F07C
void rspUndoYUVtoDCTBuf(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    int i; // r1+0x8
    int j; // r1+0x8
}

// Range: 0x8007E744 -> 0x8007E8F4
void rspFormatYUV(struct __anon_0x5845E* pRSP, char* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // char* imgBuf; // r4

    // Local variables
    int i; // r10
    int j; // r11
}

// Range: 0x8007DD0C -> 0x8007E744
static int rspParseJPEG_Encode(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r19
    // struct __anon_0x575BD* pTask; // r16

    // Local variables
    u8* temp; // r24
    u8* temp2; // r23
    int i; // r10
    int j; // r11
    int x; // r22
    int y; // r21
    u8* system_imb; // r1+0x30
    u8* system_cfb; // r1+0x2C
    int scale; // r20
}

// Range: 0x8007D4C0 -> 0x8007DD0C
static int rspParseJPEG_Decode(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // struct __anon_0x575BD* pTask; // r20

    // Local variables
    int i; // r3
    int y; // r25
    u8* temp; // r31
    u8* temp2; // r26
    u64* system_imb; // r1+0x1C
    int size; // r21
    int scale; // r22
}

// Range: 0x8007D1C8 -> 0x8007D4C0
static int rspCreateJPEGArraysZ(struct __anon_0x5845E* pRSP, int qYAddress, int qCbAddress, int qCrAddress) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r24
    // int qYAddress; // r4
    // int qCbAddress; // r25
    // int qCrAddress; // r26
}

// Erased
static int rspDestroyJPEGArraysZ() {}

// Range: 0x8007CEF8 -> 0x8007D1C8
static void rspDCTZ(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    int c; // r1+0xA4
    int i; // r1+0xA0
    int j; // r1+0x8
    int dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007C8CC -> 0x8007CEF8
static void rspQuantizeZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r1+0xC

    // Local variables
    int c; // r12
    int i; // r1+0x8
}

// Range: 0x8007C3A4 -> 0x8007C8CC
void rspZigzagDataZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r4

    // Local variables
    int c; // r1+0x8
}

// Range: 0x8007BDD8 -> 0x8007C3A4
void rspUndoQuantizeZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r1+0xC

    // Local variables
    int c; // r12
    int i; // r1+0x8
}

// Range: 0x8007B9B0 -> 0x8007BDD8
void rspUndoZigzagDataZ(struct __anon_0x5845E* pRSP, s16* dataBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* dataBuf; // r4

    // Local variables
    int c; // r1+0x8
}

// Range: 0x8007B6E0 -> 0x8007B9B0
void rspUndoDCTZ(struct __anon_0x5845E* pRSP) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8

    // Local variables
    int c; // r1+0xA4
    int i; // r1+0xA0
    int j; // r5
    int dd; // r6
    s16 t[8][8]; // r1+0x1C
}

// Range: 0x8007B64C -> 0x8007B6E0
int rspUndoLoadColorBufferZ(int r, int g, int b, s16* imgBuf, int index) {
    // Parameters
    // int r; // r3
    // int g; // r1+0x8
    // int b; // r4
    // s16* imgBuf; // r1+0x10
    // int index; // r1+0x14
}

// Range: 0x8007B244 -> 0x8007B64C
int rspUndoRecon420Z(struct __anon_0x5845E* pRSP, s16* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r30
    // s16* imgBuf; // r29

    // Local variables
    int i; // r1+0x8
    int j; // r24
    int r; // r1+0x8
    int g; // r1+0x8
    int b; // r1+0x8
    int y; // r7
    int u; // r5
    int v; // r1+0x8
}

// Erased
static int rspLoadColorBufferZ(int* r, int* g, int* b, s16* imgBuf, int index) {
    // Parameters
    // int* r; // r1+0x4
    // int* g; // r1+0x8
    // int* b; // r1+0xC
    // s16* imgBuf; // r1+0x10
    // int index; // r1+0x14
}

// Range: 0x8007AE64 -> 0x8007B244
int rspRecon420Z(struct __anon_0x5845E* pRSP, s16* imgBuf) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r1+0x8
    // s16* imgBuf; // r1+0xC

    // Local variables
    int i; // r1+0x10
    int j; // r26
    int r; // r10
    int g; // r7
    int b; // r11
    int y; // r6
    int u; // r9
    int v; // r1+0x8
}

// Range: 0x8007AD68 -> 0x8007AE64
static int rspParseJPEG_EncodeZ(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r4

    // Local variables
    int y; // r31
    s16* temp; // r1+0x8
    s16* temp2; // r30
    u64* system_imb; // r1+0x20
    unsigned int* infoStruct; // r1+0x1C
    int size; // r29
}

// Range: 0x8007AC6C -> 0x8007AD68
static int rspParseJPEG_DecodeZ(struct __anon_0x5845E* pRSP, struct __anon_0x575BD* pTask) {
    // Parameters
    // struct __anon_0x5845E* pRSP; // r28
    // struct __anon_0x575BD* pTask; // r4

    // Local variables
    int y; // r31
    s16* temp; // r1+0x8
    s16* temp2; // r30
    u64* system_imb; // r1+0x20
    unsigned int* infoStruct; // r1+0x1C
    int size; // r29
}
