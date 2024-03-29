#ifndef _BUILDTEV_H
#define _BUILDTEV_H

#include "dolphin.h"

// __anon_0x89C77
typedef struct TevOrder {
    /* 0x0 */ GXTexCoordID coordID;
    /* 0x4 */ GXTexMapID mapID;
    /* 0x8 */ GXChannelID chanID;
} TevOrder; // size = 0xC

// __anon_0x896E8
typedef struct TevColorOp {
    /* 0x00 */ GXTevOp op;
    /* 0x04 */ GXTevBias bias;
    /* 0x08 */ GXTevScale scale;
    /* 0x0C */ u8 clamp;
    /* 0x10 */ GXTevRegID out_reg;
} TevColorOp; // size = 0x14

// __anon_0x89DF5
typedef struct CombineModeTev {
    /* 0x000 */ u32 ccCodes[2][2];
    /* 0x010 */ u8 numCycles;
    /* 0x011 */ u8 numStages;
    /* 0x012 */ u8 numTexGen;
    /* 0x013 */ u8 numChan;
    /* 0x014 */ u32 flags;
    /* 0x018 */ TevOrder tevOrder[8];
    /* 0x078 */ TevColorOp tevColorOpP[8][2];
    /* 0x1B8 */ GXTevColorArg tevColorArg[8][4];
    /* 0x238 */ GXTevAlphaArg tevAlphaArg[8][4];
} CombineModeTev; // size = 0x2B8

extern GXTevAlphaArg gAlphaArgs[10];
extern GXTevColorArg gColorArgs[16];

#endif
