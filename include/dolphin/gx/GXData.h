#ifndef _DOLPHIN_GX_DATA_H
#define _DOLPHIN_GX_DATA_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/types.h"
#include "intrinsics.h"
#include "macros.h"

#define GX_CP_ADDR 0x0C000000
#define GX_PE_ADDR 0x0C001000
#define GX_PI_ADDR 0x0C003000
#define GX_MEM_ADDR 0x0C004000

#define GX_GET_MEM_REG(offset) (*(vu16*)((vu16*)(__memReg) + (offset)))
#define GX_GET_CP_REG(offset) (*(vu16*)((vu16*)(__cpReg) + (offset)))
#define GX_GET_PE_REG(offset) (*(vu16*)((vu16*)(__peReg) + (offset)))
#define GX_GET_PI_REG(offset) (*(vu32*)((vu32*)(__piReg) + (offset)))

#define GX_SET_MEM_REG(offset, val) (*(vu16*)((vu16*)(__memReg) + (offset)) = val)
#define GX_SET_CP_REG(offset, val) (*(vu16*)((vu16*)(__cpReg) + (offset)) = val)
#define GX_SET_PE_REG(offset, val) (*(vu16*)((vu16*)(__peReg) + (offset)) = val)
#define GX_SET_PI_REG(offset, val) (*(vu32*)((vu32*)(__piReg) + (offset)) = val)

#define GX_CHECK_FLUSH() (!(*(u32*)(&gx->vNumNot)))
#define GX_COLOR_AS_U32(color) (*((u32*)&(color)))

#define FAST_FLAG_SET(regOrg, newFlag, shift, size)                                                                \
    do {                                                                                                           \
        (regOrg) = (u32)__rlwimi((int)(regOrg), (int)(newFlag), (shift), (32 - (shift) - (size)), (31 - (shift))); \
    } while (0);

#define gx __GXData

typedef enum _CPStatus {
    GX_FIFO_OVERFLOW = 0x1,
    GX_FIFO_UNDERFLOW = 0x2,
    GP_IS_IDLE_FOR_READING = 0x4,
    GP_IS_IDLE_FOR_COMMANDS = 0x8,
    BP_INTERRUPT = 0x10,
} CPStatus;

typedef enum _CPControl {
    GP_FIFO_READ_ENABLE = 0x1,
    CP_IRQ_ENABLE_MAYBE = 0x2,
    FIFO_OVERFLOW_IRQ_ENABLE_MAYBE = 0x4,
    FIFO_UNDERFLOW_IRQ_ENABLE_MAYBE = 0x8,
    GP_LINK_ENABLE = 0x10,
    BP_ENABLE = 0x20,
} CPControl;

typedef enum _CPClear {
    CLEAR_FIFO_OVERFLOW = 0x1,
    CLEAR_FIFO_UNDERFLOW = 0x2,
} CPClear;

typedef struct _GXData {
    /* [MQ Offset] [CE Offset] type name */

    // Bypass and vertex info
    /* 0x000 0x000 */ u16 vNumNot; // !(# flush verts to send)
    /* 0x002 0x002 */ u16 bpSentNot; // !(bypass reg sent last?)
    /* 0x004 0x004 */ u16 vNum; // # flush verts to send
    /* 0x006 0x006 */ u16 vLim; // max vert size

    // Command process (CP) regs
    /* 0x008 0x008 */ u32 cpEnable;
    /* 0x00C 0x00C */ u32 cpStatus;
    /* 0x010 0x010 */ u32 cpClr;
    /* 0x014 0x014 */ u32 vcdLo;
    /* 0x018 0x018 */ u32 vcdHi;
    /* 0x01C 0x01C */ u32 vatA[8];
    /* 0x03C 0x03C */ u32 vatB[8];
    /* 0x05C 0x05C */ u32 vatC[8];
    /* 0x07C 0x07C */ u32 lpSize;
    /* 0x080 0x080 */ u32 matIdxA;
    /* 0x084 0x084 */ u32 matIdxB;

    // Index loading base/stride regs (pos, nrm, tex, light)
    /* 0x088 0x088 */ u32 indexBase[4];
    /* 0x098 0x098 */ u32 indexStride[4];

    // Transform and lighting regs
    /* 0x0A8 0x0A8 */ u32 ambColor[2];
    /* 0x0B0 0x0B0 */ u32 matColor[2];

    // Setup regs
    /* 0x0B8 0x0B8 */ u32 suTs0[8];
    /* 0x0D8 0x0D8 */ u32 suTs1[8];
    /* 0x0F8 0x0F8 */ u32 suScis0;
    /* 0x0FC 0x0FC */ u32 suScis1;

    // Raster regs
    /* 0x100 0x100 */ u32 tref[8];
    /* 0x120 0x120 */ u32 iref;

    // Bump/Indirect texture regs
    /* 0x124 0x124 */ u32 bpMask;
    /* 0x128 0x128 */ u32 IndTexScale0;
    /* 0x12C 0x12C */ u32 IndTexScale1;

    // Tev regs
    /* 0x130 0x130 */ u32 tevc[16];
    /* 0x170 0x170 */ u32 teva[16];
    /* 0x1B0 0x1B0 */ u32 tevKsel[8];

    // Performance regs
    /* 0x1D0 0x1D0 */ u32 cmode0;
    /* 0x1D4 0x1D4 */ u32 cmode1;
    /* 0x1D8 0x1D8 */ u32 zmode;
    /* 0x1DC 0x1DC */ u32 peCtrl;

    // Display copy regs
    /* 0x1E0 0x1E0 */ u32 cpDispSrc;
    /* 0x1E4 0x1E4 */ u32 cpDispSize;
    /* 0x1E8 0x1E8 */ u32 cpDispStride;
    /* 0x1EC 0x1EC */ u32 cpDisp;

    // Texture copy regs
    /* 0x1F0 0x1F0 */ u32 cpTexSrc;
    /* 0x1F4 0x1F4 */ u32 cpTexSize;
    /* 0x1F8 0x1F8 */ u32 cpTexStride;
    /* 0x1FC 0x1FC */ u32 cpTex;
    /* 0x200 0x200 */ GXBool cpTexZ;

    // General raster mode
    /* 0x204 0x204 */ u32 genMode;

    // Texture regions
    /* 0x208 0x208 */ GXTexRegion TexRegions0[GX_MAX_TEXMAP];

#if IS_MQ
    /* 0x288  N/A  */ GXTexRegion TexRegionsCI[4];
    /* 0x2C8  N/A  */ u32 nextTexRgn;
    /* 0x2CC  N/A  */ u32 nextTexRgnCI;
#else
    /*  N/A  0x288 */ GXTexRegion TexRegions1[GX_MAX_TEXMAP];
    /*  N/A  0x308 */ GXTexRegion TexRegions2[GX_MAX_TEXMAP];
#endif

    // Texture lookup table regions
    /* 0x2D0 0x388 */ GXTlutRegion TlutRegions[GX_MAX_TLUT_ALL];
    /* 0x410 0x4C8 */ GXTexRegionCallback texRegionCallback;
    /* 0x414 0x4CC */ GXTlutRegionCallback tlutRegionCallback;

    // Command processor vars
    /* 0x418 0x4D0 */ GXAttrType nrmType;
    /* 0x41C 0x4D4 */ GXBool hasNrms;
    /* 0x41D 0x4D5 */ GXBool hasBiNrms;
    /* 0x420 0x4D8 */ u32 projType;
    /* 0x424 0x4DC */ f32 projMtx[6];

    // Viewport parms
    /* 0x43C 0x4F4 */ f32 vpLeft;
    /* 0x440 0x4F8 */ f32 vpTop;
    /* 0x444 0x4FC */ f32 vpWd;
    /* 0x448 0x500 */ f32 vpHt;
    /* 0x44C 0x504 */ f32 vpNearz;
    /* 0x450 0x508 */ f32 vpFarz;

#if IS_MQ
    /* 0x454  N/A  */ u8 fgRange;
    /* 0x458  N/A  */ f32 fgSideX;
#else
    /*  N/A  0x50C */ f32 zOffset;
    /*  N/A  0x510 */ f32 zScale;
#endif

    // Texture regs
    /* 0x45C 0x514 */ u32 tImage0[8];
    /* 0x47C 0x534 */ u32 tMode0[8];
    /* 0x49C 0x554 */ u32 texmapId[16];
    /* 0x4DC 0x594 */ u32 tcsManEnab;
    /* 0x4E0 0x598 */ u32 tevTcEnab;

    // Performance metrics
    /* 0x4E4 0x59C */ GXPerf0 perf0;
    /* 0x4E8 0x5A0 */ GXPerf1 perf1;
    /* 0x4EC 0x5A4 */ u32 perfSel;

    // Flags
    /* 0x4F0 0x5A8 */ GXBool inDispList;
    /* 0x4F1 0x5A9 */ GXBool dlSaveContext;
#if IS_CE
    /*  N/A  0x5AA */ GXBool abtWaitPECopy;
#endif
    /* 0x4F2 0x5AB */ u8 dirtyVAT;
    /* 0x4F4 0x5AC */ u32 dirtyState;
} GXData;

typedef struct _GXVtxDescList {
    /* 0x00 */ GXAttr mAttr;
    /* 0x04 */ GXAttrType mType;
} GXVtxDescList;

typedef struct _GXVtxAttrFmtList {
    /* 0x00 */ GXAttr mAttr;
    /* 0x04 */ GXCompCnt mCount;
    /* 0x08 */ GXCompType mType;
    /* 0x0C */ u8 mFrac;
} GXVtxAttrFmtList;

typedef struct __GXLightObjPriv {
    /* 0x00 */ u32 reserved[3]; //
    /* 0x0C */ GXColor color; // light color
    /* 0x10 */ f32 a[3]; // angle-attenuation coefficients
    /* 0x1C */ f32 k[3]; // distance-attenuation coefficients
    /* 0x28 */ f32 lpos[3]; // diffuse: position;  specular: direction
    /* 0x34 */ f32 ldir[3]; // diffuse: direction; specular: half-angle
} GXLightObjPriv;

// Internal struct for texture objects.
typedef struct _GXTexObjPriv {
    /* 0x00 */ u32 mode0;
    /* 0x04 */ u32 mode1;
    /* 0x08 */ u32 image0;
    /* 0x0C */ u32 image3;
    /* 0x10 */ void* userData;
    /* 0x14 */ GXTexFmt format;
    /* 0x18 */ u32 tlutName;
    /* 0x1C */ u16 loadCount;
    /* 0x1E */ u8 loadFormat;
    /* 0x1F */ u8 flags;
} GXTexObjPriv;

typedef struct _GXTexRegionPriv {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padding[2];
} GXTexRegionPriv;

typedef struct _GXTlutObjPriv {
    /* 0x00*/ u32 unk0;
    /* 0x04*/ u32 unk4;
    /* 0x08*/ u16 numEntries;
    /* 0x0A*/ u8 padding[0x2];
} GXTlutObjPriv;

typedef struct _GXTlutRegionPriv {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ GXTlutObjPriv tlutObj;
} GXTlutRegionPriv;

extern GXData* const __GXData;
extern void* __cpReg;
extern void* __piReg;
extern void* __memReg;
extern void* __peReg;

// Useful reading register inlines
static inline u32 GXReadMEMReg(u32 addrLo, u32 addrHi) {
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_MEM_REG(addrHi);
    do {
        hiNew = hiStart;
        lo = GX_GET_MEM_REG(addrLo);
        hiStart = GX_GET_MEM_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadCPReg(u32 addrLo, u32 addrHi) {
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_CP_REG(addrHi);
    do {
        hiNew = hiStart;
        lo = GX_GET_CP_REG(addrLo);
        hiStart = GX_GET_CP_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadPEReg(u32 addrLo, u32 addrHi) {
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_PE_REG(addrHi);
    do {
        hiNew = hiStart;
        lo = GX_GET_PE_REG(addrLo);
        hiStart = GX_GET_PE_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadPIReg(u32 addrLo, u32 addrHi) {
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_PI_REG(addrHi);
    do {
        hiNew = hiStart;
        lo = GX_GET_PI_REG(addrLo);
        hiStart = GX_GET_PI_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

#endif
