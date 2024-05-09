#ifndef _DOLPHIN_VITYPES_H_
#define _DOLPHIN_VITYPES_H_

#include "dolphin/types.h"

#define VI_TVMODE(format, interlace) (((format) << 2) + (interlace))

#define VI_INTERLACE 0
#define VI_NON_INTERLACE 1
#define VI_PROGRESSIVE 2

#define VI_NTSC 0
#define VI_PAL 1
#define VI_MPAL 2
#define VI_DEBUG 3
#define VI_DEBUG_PAL 4
#define VI_EURGB60 5

typedef void (*VIRetraceCallback)(u32 retraceCount);

typedef enum VITVMode {
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
} VITVMode;

typedef enum VIXFBMode {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF
} VIXFBMode;

#endif
