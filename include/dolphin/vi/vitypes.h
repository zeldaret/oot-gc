#ifndef _DOLPHIN_VITYPES_H_
#define _DOLPHIN_VITYPES_H_

#include "dolphin/types.h"

#define VI_TVMODE(format, interlace) (((format) << 2) + (interlace))

#define VI_INTERLACE 0
#define VI_NON_INTERLACE 1
#define VI_PROGRESSIVE 2
#define VI_3D 3

#define VI_NTSC 0
#define VI_PAL 1
#define VI_MPAL 2
#define VI_DEBUG 3
#define VI_DEBUG_PAL 4
#define VI_EURGB60 5
#define VI_GCA 6

typedef void (*VIRetraceCallback)(u32 retraceCount);
typedef void (*VIPositionCallback)(s16 x, s16 y);

typedef enum VITVMode {
    VI_TVMODE_NTSC_INT = 0, // VI_TVMODE(VI_NTSC, VI_INTERLACE)
    VI_TVMODE_NTSC_DS = 1, // VI_TVMODE(VI_NTSC, VI_NON_INTERLACE)
    VI_TVMODE_NTSC_PROG = 2, // VI_TVMODE(VI_NTSC, VI_PROGRESSIVE)
    VI_TVMODE_NTSC_3D = 3, // VI_TVMODE(VI_NTSC, VI_3D)
    VI_TVMODE_PAL_INT = 4, // VI_TVMODE(VI_PAL, VI_INTERLACE)
    VI_TVMODE_PAL_DS = 5, // VI_TVMODE(VI_PAL, VI_NON_INTERLACE)
    VI_TVMODE_EURGB60_INT = 20, // VI_TVMODE(VI_EURGB60, VI_INTERLACE)
    VI_TVMODE_EURGB60_DS = 21, // VI_TVMODE(VI_EURGB60, VI_NON_INTERLACE)
    VI_TVMODE_MPAL_INT = 8, // VI_TVMODE(VI_MPAL, VI_INTERLACE)
    VI_TVMODE_MPAL_DS = 9, // VI_TVMODE(VI_MPAL, VI_NON_INTERLACE)
    VI_TVMODE_DEBUG_INT = 12, // VI_TVMODE(VI_DEBUG, VI_INTERLACE)
    VI_TVMODE_DEBUG_PAL_INT = 16, // VI_TVMODE(VI_DEBUG_PAL, VI_INTERLACE)
    VI_TVMODE_DEBUG_PAL_DS = 17, // VI_TVMODE(VI_DEBUG_PAL, VI_NON_INTERLACE)
    VI_TVMODE_GCA_INT = 24, // VI_TVMODE(VI_GCA, VI_INTERLACE)
    VI_TVMODE_GCA_DS = 25, // VI_TVMODE(VI_GCA, VI_NON_INTERLACE)
    VI_TVMODE_GCA_PROG = 26, // VI_TVMODE(VI_GCA, VI_PROGRESSIVE)
} VITVMode;

typedef enum VIXFBMode {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF
} VIXFBMode;

typedef struct VITimingInfo {
    /* 0x00 */ u8 equ;
    /* 0x02 */ u16 acv;
    /* 0x04 */ u16 prbOdd;
    /* 0x06 */ u16 prbEven;
    /* 0x08 */ u16 psbOdd;
    /* 0x0A */ u16 psbEven;
    /* 0x0C */ u8 bs1;
    /* 0x0D */ u8 bs2;
    /* 0x0E */ u8 bs3;
    /* 0x0F */ u8 bs4;
    /* 0x10 */ u16 be1;
    /* 0x12 */ u16 be2;
    /* 0x14 */ u16 be3;
    /* 0x16 */ u16 be4;
    /* 0x18 */ u16 numHalfLines;
    /* 0x1A */ u16 hlw;
    /* 0x1C */ u8 hsy;
    /* 0x1D */ u8 hcs;
    /* 0x1E */ u8 hce;
    /* 0x1F */ u8 hbe640;
    /* 0x20 */ u16 hbs640;
    /* 0x24 */ u8 hbeCCIR656;
    /* 0x26 */ u16 hbsCCIR656;
} VITimingInfo; // size = 0x28

typedef struct VIPositionInfo {
    /* 0x00 */ u16 dispPosX;
    /* 0x02 */ u16 dispPosY;
    /* 0x04 */ u16 dispSizeX;
    /* 0x06 */ u16 dispSizeY;
    /* 0x08 */ u16 adjDispPosX;
    /* 0x0A */ u16 adjDispPosY;
    /* 0x0C */ u16 adjDispSizeY;
    /* 0x0E */ u16 adjPanPosY;
    /* 0x10 */ u16 adjPanSizeY;
    /* 0x12 */ u16 fbSizeX;
    /* 0x14 */ u16 fbSizeY;
    /* 0x16 */ u16 panPosX;
    /* 0x18 */ u16 panPosY;
    /* 0x1A */ u16 panSizeX;
    /* 0x1C */ u16 panSizeY;
    /* 0x20 */ VIXFBMode xfbMode;
    /* 0x24 */ u32 nonInter;
    /* 0x28 */ u32 tv;
    /* 0x2C */ u8 wordPerLine;
    /* 0x2D */ u8 std;
    /* 0x2E */ u8 wpl;
    /* 0x30 */ u32 bufAddr;
    /* 0x34 */ u32 tfbb;
    /* 0x38 */ u32 bfbb;
    /* 0x3C */ u8 xof;
    /* 0x40 */ bool isBlack;
    /* 0x44 */ bool is3D;
    /* 0x48 */ u32 rbufAddr;
    /* 0x4C */ u32 rtfbb;
    /* 0x50 */ u32 rbfbb;
    /* 0x54 */ VITimingInfo* timing;
} VIPositionInfo; // size = 0x58

#endif
