/*
    Compile unit: C:\HOMEBOY\STEPHEN\Japanese Ocarina\Fire\THPDraw.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80011138 -> 0x80011938
*/

#include "dolphin/types.h"

typedef enum __anon_0x14611 {
    VI_TVMODE_NTSC_INT = 0,
    VI_TVMODE_NTSC_DS = 1,
    VI_TVMODE_NTSC_PROG = 2,
    VI_TVMODE_PAL_INT = 4,
    VI_TVMODE_PAL_DS = 5,
    VI_TVMODE_EURGB60_INT = 20,
    VI_TVMODE_EURGB60_DS = 21,
    VI_TVMODE_MPAL_INT = 8,
    VI_TVMODE_MPAL_DS = 9,
    VI_TVMODE_DEBUG_INT = 12,
    VI_TVMODE_DEBUG_PAL_INT = 16,
    VI_TVMODE_DEBUG_PAL_DS = 17,
} __anon_0x14611;

typedef enum __anon_0x1475B {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
} __anon_0x1475B;

typedef struct _GXRenderModeObj {
    /* 0x00 */ enum __anon_0x14611 viTVmode;
    /* 0x04 */ u16 fbWidth;
    /* 0x06 */ u16 efbHeight;
    /* 0x08 */ u16 xfbHeight;
    /* 0x0A */ u16 viXOrigin;
    /* 0x0C */ u16 viYOrigin;
    /* 0x0E */ u16 viWidth;
    /* 0x10 */ u16 viHeight;
    /* 0x14 */ enum __anon_0x1475B xFBmode;
    /* 0x18 */ u8 field_rendering;
    /* 0x19 */ u8 aa;
    /* 0x1A */ u8 sample_pattern[12][2];
    /* 0x32 */ u8 vfilter[7];
} __anon_0x1480C; // size = 0x3C

typedef struct _GXTexObj {
    /* 0x0 */ u32 dummy[8];
} __anon_0x14BBE; // size = 0x20

// Range: 0x80011754 -> 0x80011938
void THPGXYuv2RgbDraw(u8* y_data, u8* u_data, u8* v_data, s16 x, s16 y, s16 textureWidth, s16 textureHeight,
                      s16 polygonWidth, s16 polygonHeight) {
    // Parameters
    // u8* y_data; // r3
    // u8* u_data; // r24
    // u8* v_data; // r25
    // s16 x; // r30
    // s16 y; // r31
    // s16 textureWidth; // r28
    // s16 textureHeight; // r29
    // s16 polygonWidth; // r26
    // s16 polygonHeight; // r27

    // Local variables
    struct _GXTexObj tobj0; // r1+0x60
    struct _GXTexObj tobj1; // r1+0x40
    struct _GXTexObj tobj2; // r1+0x20
}

// Range: 0x80011250 -> 0x80011754
void THPGXYuv2RgbSetup(struct _GXRenderModeObj* rmode) {
    // Parameters
    // struct _GXRenderModeObj* rmode; // r1+0x8

    // Local variables
    s32 scrWidth; // r28
    s32 scrHeight; // r27
    f32 pMtx[4][4]; // r1+0x74
    f32 mMtx[3][4]; // r1+0x44
}

// Range: 0x80011138 -> 0x80011250
void THPGXRestore() {}
