#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "intrinsics.h"
#include "string.h"

#include "dolphin/private/__gx.h"

// GXTexObj internal data
typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

// GXTexRegion internal data
typedef struct __GXTexRegionInt_struct {
    u32 image1;
    u32 image2;
    u16 sizeEven;
    u16 sizeOdd;
    u8 is32bMipmap;
    u8 isCached;
} __GXTexRegionInt;

// GXTlutObj internal data
typedef struct __GXTlutObjInt_struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} __GXTlutObjInt;

// GXTlutRegion internal data
typedef struct __GXTlutRegionInt_struct {
    u32 loadTlut1;
    __GXTlutObjInt tlutObj;
} __GXTlutRegionInt;

static u8 GXTexMode0Ids[8] = {0x80, 0x81, 0x82, 0x83, 0xA0, 0xA1, 0xA2, 0xA3};
static u8 GXTexMode1Ids[8] = {0x84, 0x85, 0x86, 0x87, 0xA4, 0xA5, 0xA6, 0xA7};
static u8 GXTexImage0Ids[8] = {0x88, 0x89, 0x8A, 0x8B, 0xA8, 0xA9, 0xAa, 0xAb};
static u8 GXTexImage1Ids[8] = {0x8C, 0x8D, 0x8E, 0x8F, 0xAc, 0xAd, 0xAe, 0xAf};
static u8 GXTexImage2Ids[8] = {0x90, 0x91, 0x92, 0x93, 0xB0, 0xB1, 0xB2, 0xB3};
static u8 GXTexImage3Ids[8] = {0x94, 0x95, 0x96, 0x97, 0xB4, 0xB5, 0xB6, 0xB7};
static u8 GXTexTlutIds[8] = {0x98, 0x99, 0x9A, 0x9B, 0xB8, 0xB9, 0xBa, 0xBb};

static u8 GX2HWFiltConv[8] = {0x00, 0x04, 0x01, 0x05, 0x02, 0x06, 0, 0};

#define GET_TILE_COUNT(a, b) (((a) + (1 << (b)) - 1) >> (b))

static inline void __GXGetTexTileShift(GXTexFmt fmt, u32* rowTileS, u32* colTileS) {
    switch (fmt) {
        case GX_TF_I4:
        case 0x8:
        case GX_TF_CMPR:
        case GX_CTF_R4:
        case GX_CTF_Z4:
            *rowTileS = 3;
            *colTileS = 3;
            break;
        case GX_TF_I8:
        case GX_TF_IA4:
        case 0x9:
        case GX_TF_Z8:
        case GX_CTF_RA4:
        case GX_TF_A8:
        case GX_CTF_R8:
        case GX_CTF_G8:
        case GX_CTF_B8:
        case GX_CTF_Z8M:
        case GX_CTF_Z8L:
            *rowTileS = 3;
            *colTileS = 2;
            break;
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3:
        case GX_TF_RGBA8:
        case 0xA:
        case GX_TF_Z16:
        case GX_TF_Z24X8:
        case GX_CTF_RA8:
        case GX_CTF_RG8:
        case GX_CTF_GB8:
        case GX_CTF_Z16L:
            *rowTileS = 2;
            *colTileS = 2;
            break;
        default:
            *rowTileS = *colTileS = 0;
            ASSERTMSGLINEV(444, 0, "%s: invalid texture format", "GX");
            break;
    }
}

void __GetImageTileCount(GXTexFmt fmt, u16 wd, u16 ht, u32* rowTiles, u32* colTiles, u32* cmpTiles) {
    u32 texRowShift;
    u32 texColShift;

    __GXGetTexTileShift(fmt, &texRowShift, &texColShift);
    if (wd == 0) {
        wd = 1;
    }
    if (ht == 0) {
        ht = 1;
    }
    *rowTiles = (wd + (1 << texRowShift) - 1) >> texRowShift;
    *colTiles = (ht + (1 << texColShift) - 1) >> texColShift;
    *cmpTiles = (fmt == GX_TF_RGBA8 || fmt == GX_TF_Z24X8) ? 2 : 1;
}

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s,
                  GXTexWrapMode wrap_t, GXBool mipmap) {
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    __GXTexObjInt* t = (__GXTexObjInt*)obj;

    ASSERTMSGLINE(565, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(567, "GXInitTexObj");
    ASSERTMSGLINEV(568, width <= 1024, "%s: width too large", "GXInitTexObj");
    ASSERTMSGLINEV(569, height <= 1024, "%s: height too large", "GXInitTexObj");
    ASSERTMSGLINEV(571, !(format & _GX_TF_CTF), "%s: invalid texture format", "GXInitTexObj");

#if DEBUG
    if (wrap_s != GX_CLAMP || mipmap) {
        u32 mask = 1 << (31 - __cntlzw(width));
        ASSERTMSGLINEV(581, width == mask, "%s: width must be a power of 2", "GXInitTexObj");
    }
    if (wrap_t != GX_CLAMP || mipmap) {
        u32 mask = 1 << (31 - __cntlzw(height));
        ASSERTMSGLINEV(586, height == mask, "%s: height must be a power of 2", "GXInitTexObj");
    }
#endif

    memset(t, 0, 0x20);
    SET_REG_FIELD(t->mode0, 2, 0, wrap_s);
    SET_REG_FIELD(t->mode0, 2, 2, wrap_t);
    SET_REG_FIELD(t->mode0, 1, 4, 1);

    if (mipmap) {
        u8 lmax;
        t->flags |= 1;

        if (format == 8 || format == 9 || format == 10) {
            SET_REG_FIELD(t->mode0, 3, 5, 5);
        } else {
            SET_REG_FIELD(t->mode0, 3, 5, 6);
        }

        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }

        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(t->mode1, 8, 8, lmax);
    } else {
        SET_REG_FIELD(t->mode0, 3, 5, 4);
    }

    t->fmt = format;
    SET_REG_FIELD(t->image0, 10, 0, width - 1);
    SET_REG_FIELD(t->image0, 10, 10, height - 1);
    SET_REG_FIELD(t->image0, 4, 20, format & 0xF);
    ASSERTMSGLINEV(654, ((u32)image_ptr & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexObj", "image");
    imageBase = (u32)((u32)image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(t->image3, 21, 0, imageBase);

    switch (format & 0xF) {
        case GX_TF_I4:
        case 8:
            t->loadFmt = 1;
            rowT = 3;
            colT = 3;
            break;
        case GX_TF_I8:
        case GX_TF_IA4:
        case 9:
            t->loadFmt = 2;
            rowT = 3;
            colT = 2;
            break;
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3:
        case 10:
            t->loadFmt = 2;
            rowT = 2;
            colT = 2;
            break;
        case GX_TF_RGBA8:
            t->loadFmt = 3;
            rowT = 2;
            colT = 2;
            break;
        case GX_TF_CMPR:
            t->loadFmt = 0;
            rowT = 3;
            colT = 3;
            break;
        default:
            ASSERTMSGLINEV(699, 0, "%s: invalid texture format", "GXPreLoadEntireTexture");
            t->loadFmt = 2;
            rowT = 2;
            colT = 2;
            break;
    }

    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    t->loadCnt = (rowC * colC) & 0x7FFF;
    t->flags |= 2;
}

void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s,
                    GXTexWrapMode wrap_t, GXBool mipmap, u32 tlut_name) {
    __GXTexObjInt* t = (__GXTexObjInt*)obj;

    ASSERTMSGLINE(737, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(739, "GXInitTexObjCI");
    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t, mipmap);
    t->flags &= 0xFFFFFFFD;
    t->tlutName = tlut_name;
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias,
                     u8 bias_clamp, u8 do_edge_lod, GXAnisotropy max_aniso) {
    u8 lbias;
    u8 lmin;
    u8 lmax;
    __GXTexObjInt* t = (__GXTexObjInt*)obj;

    ASSERTMSGLINE(776, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(778, "GXInitTexObjLOD");

    if (lod_bias < -4.0f) {
        lod_bias = -4.0f;
    } else if (lod_bias >= 4.0f) {
        lod_bias = 3.99f;
    }

    lbias = 32.0f * lod_bias;
    SET_REG_FIELD(t->mode0, 8, 9, lbias);
    ASSERTMSG1LINE(791, (u32)mag_filt <= 1, "%s: invalid mag_filt value", "GXInitTexObjLOD");
    SET_REG_FIELD(t->mode0, 1, 4, (mag_filt == GX_LINEAR) ? 1 : 0);
    ASSERTMSG1LINE(795, (u32)min_filt <= 5, "%s: invalid min_filt value", "GXInitTexObjLOD");
    SET_REG_FIELD(t->mode0, 3, 5, GX2HWFiltConv[min_filt]);
    SET_REG_FIELD(t->mode0, 1, 8, do_edge_lod ? 0 : 1);
    SET_REG_FIELD(t->mode0, 1, 17, 0);
    SET_REG_FIELD(t->mode0, 1, 18, 0);
    SET_REG_FIELD(t->mode0, 2, 19, max_aniso);
    SET_REG_FIELD(t->mode0, 1, 21, bias_clamp);

    if (min_lod < 0.0f) {
        min_lod = 0.0f;
    } else if (min_lod > 10.0f) {
        min_lod = 10.0f;
    }
    lmin = 16.0f * min_lod;
    if (max_lod < 0.0f) {
        max_lod = 0.0f;
    } else if (max_lod > 10.0f) {
        max_lod = 10.0f;
    }
    lmax = 16.0f * max_lod;
    SET_REG_FIELD(t->mode1, 8, 0, lmin);
    SET_REG_FIELD(t->mode1, 8, 8, lmax);
}

void* GXGetTexObjData(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1108, to, "Texture Object Pointer is null");
    return (void*)(GET_REG_FIELD(t->image3, 21, 0) << 5);
}

GXTexFmt GXGetTexObjFmt(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1126, to, "Texture Object Pointer is null");
    return t->fmt;
}

GXBool GXGetTexObjMipMap(const GXTexObj* to) {
    const __GXTexObjInt* t = (const __GXTexObjInt*)to;

    ASSERTMSGLINE(1144, to, "Texture Object Pointer is null");
    return (t->flags & 1) == 1;
}

void GXLoadTexObjPreLoaded(GXTexObj* obj, GXTexRegion* region, GXTexMapID id) {
#if IS_CE
    u32 pad[6];
#endif
    __GXTlutRegionInt* tlr;
    __GXTexObjInt* t = (__GXTexObjInt*)obj;
    __GXTexRegionInt* r = (__GXTexRegionInt*)region;

    ASSERTMSGLINE(0x3FE, obj, "Texture Object Pointer is null");
    ASSERTMSGLINE(0x3FE, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x400, "GXLoadTexObjPreLoaded");
    ASSERTMSGLINEV(0x401, id < 8, "%s: invalid texture map ID", "GXLoadTexObj");

    SET_REG_FIELD(t->mode0, 8, 24, GXTexMode0Ids[id]);
    SET_REG_FIELD(t->mode1, 8, 24, GXTexMode1Ids[id]);
    SET_REG_FIELD(t->image0, 8, 24, GXTexImage0Ids[id]);
    SET_REG_FIELD(r->image1, 8, 24, GXTexImage1Ids[id]);
    SET_REG_FIELD(r->image2, 8, 24, GXTexImage2Ids[id]);
    SET_REG_FIELD(t->image3, 8, 24, GXTexImage3Ids[id]);

    GX_WRITE_RAS_REG(t->mode0);
    GX_WRITE_RAS_REG(t->mode1);
    GX_WRITE_RAS_REG(t->image0);
    GX_WRITE_RAS_REG(r->image1);
    GX_WRITE_RAS_REG(r->image2);
    GX_WRITE_RAS_REG(t->image3);

    if (!(t->flags & 2)) {
        ASSERTMSGLINEV(0x413, __GXData->tlutRegionCallback, "%s: Tex/Tlut Region Callback not set",
                       "GXLoadTexObj/PreLoaded");
        tlr = (__GXTlutRegionInt*)__GXData->tlutRegionCallback(t->tlutName);
        ASSERTMSGLINEV(0x415, tlr, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTexObj/PreLoaded");

        SET_REG_FIELD(tlr->tlutObj.tlut, 8, 24, GXTexTlutIds[id]);
        GX_WRITE_RAS_REG(tlr->tlutObj.tlut);
    }
    __GXData->tImage0[id] = t->image0;
    __GXData->tMode0[id] = t->mode0;
    __GXData->dirtyState |= 1;
    __GXData->bpSentNot = 0;
}

void GXLoadTexObj(GXTexObj* obj, GXTexMapID id) {
    GXTexRegion* r;

    CHECK_GXBEGIN(1318, "GXLoadTexObj");
    ASSERTMSGLINEV(1319, id < 8, "%s: invalid texture map ID", "GXLoadTexObj");
    ASSERTMSGLINEV(1324, __GXData->texRegionCallback, "%s: Tex/Tlut Region Callback not set", "GXLoadTexObj");
    r = __GXData->texRegionCallback(obj, id);
    ASSERTMSGLINEV(1326, r, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTexObj");
    GXLoadTexObjPreLoaded(obj, r, id);
}

void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries) {
    __GXTlutObjInt* t = (__GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1350, tlut_obj, "TLut Object Pointer is null");
    CHECK_GXBEGIN(1351, "GXInitTlutObj");
    ASSERTMSGLINEV(1354, n_entries <= 0x4000, "%s: number of entries exceeds maximum", "GXInitTlutObj");
    ASSERTMSGLINEV(1356, ((u32)lut & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTlutObj", "Tlut");
    t->tlut = 0;
    SET_REG_FIELD(t->tlut, 2, 10, fmt);
    SET_REG_FIELD(t->loadTlut0, 21, 0, ((u32)lut & 0x3FFFFFFF) >> 5);
    SET_REG_FIELD(t->loadTlut0, 8, 24, 0x64);
    t->numEntries = n_entries;
}

void GXLoadTlut(GXTlutObj* tlut_obj, u32 tlut_name) {
    __GXTlutRegionInt* r;
    u32 tlut_offset;
    __GXTlutObjInt* t = (__GXTlutObjInt*)tlut_obj;

    ASSERTMSGLINE(1432, tlut_obj, "TLut Object Pointer is null");
    CHECK_GXBEGIN(1434, "GXLoadTlut");
    ASSERTMSGLINEV(1435, __GXData->tlutRegionCallback, "%s: Tex/Tlut Region Callback not set", "GXLoadTlut");
    r = (__GXTlutRegionInt*)__GXData->tlutRegionCallback(tlut_name);
    ASSERTMSGLINEV(1437, r, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTlut");

    __GXFlushTextureState();
    GX_WRITE_RAS_REG(t->loadTlut0);
    GX_WRITE_RAS_REG(r->loadTlut1);
    __GXFlushTextureState();
    tlut_offset = r->loadTlut1 & 0x3FF;
    SET_REG_FIELD(t->tlut, 10, 0, tlut_offset);
    r->tlutObj = *t;
}

void GXInitTexCacheRegion(GXTexRegion* region, u8 is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even, u32 tmem_odd,
                          GXTexCacheSize size_odd) {
    u32 WidthExp2;
    __GXTexRegionInt* t = (__GXTexRegionInt*)region;

    ASSERTMSGLINE(1484, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(1486, "GXInitTexCacheRegion");
    ASSERTMSGLINEV(1488, (tmem_even & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexCacheRegion",
                   "tmem even");
    ASSERTMSGLINEV(1490, (tmem_odd & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexCacheRegion",
                   "tmem odd");

    switch (size_even) {
        case GX_TEXCACHE_32K:
            WidthExp2 = 3;
            break;
        case GX_TEXCACHE_128K:
            WidthExp2 = 4;
            break;
        case GX_TEXCACHE_512K:
            WidthExp2 = 5;
            break;
        default:
            ASSERTMSGLINEV(1498, 0, "%s: Invalid %s size", "GXInitTexCacheRegion", "tmem even");
            break;
    }

    t->image1 = 0;
    SET_REG_FIELD(t->image1, 15, 0, tmem_even >> 5);
    SET_REG_FIELD(t->image1, 3, 15, WidthExp2);
    SET_REG_FIELD(t->image1, 3, 18, WidthExp2);
    SET_REG_FIELD(t->image1, 1, 21, 0);

    switch (size_odd) {
        case GX_TEXCACHE_32K:
            WidthExp2 = 3;
            break;
        case GX_TEXCACHE_128K:
            WidthExp2 = 4;
            break;
        case GX_TEXCACHE_512K:
            WidthExp2 = 5;
            break;
        case GX_TEXCACHE_NONE:
            WidthExp2 = 0;
            break;
        default:
            ASSERTMSGLINEV(1514, 0, "%s: Invalid %s size", "GXInitTexCacheRegion", "tmem odd");
            break;
    }

    t->image2 = 0;
    SET_REG_FIELD(t->image2, 15, 0, tmem_odd >> 5);
    SET_REG_FIELD(t->image2, 3, 15, WidthExp2);
    SET_REG_FIELD(t->image2, 3, 18, WidthExp2);
    t->is32bMipmap = is_32b_mipmap;
    t->isCached = 1;
}

void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size) {
    __GXTlutRegionInt* t = (__GXTlutRegionInt*)region;

    ASSERTMSGLINE(1652, region, "TLutRegion Object Pointer is null");
    CHECK_GXBEGIN(1654, "GXInitTlutRegion");
    ASSERTMSGLINEV(1655, (tmem_addr & 0x1FF) == 0, "%s: tmem pointer is not aligned to 512B", "GXInitTlutRegion");
    ASSERTMSGLINEV(1656, tlut_size <= 0x400, "%s: tlut size exceeds 16K", "GXInitTlutRegion");
    t->loadTlut1 = 0;
    tmem_addr -= 0x80000;
    SET_REG_FIELD(t->loadTlut1, 10, 0, tmem_addr >> 9);
    SET_REG_FIELD(t->loadTlut1, 11, 10, tlut_size);
    SET_REG_FIELD(t->loadTlut1, 8, 24, 0x65);
}

void GXInvalidateTexAll(void) {
    u32 reg0;
    u32 reg1;

    CHECK_GXBEGIN(1755, "GXInvalidateTexAll");
    reg0 = 0x66001000;
    reg1 = 0x66001100;
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(reg0);
    GX_WRITE_RAS_REG(reg1);
    __GXFlushTextureState();
}

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f) {
    GXTexRegionCallback oldcb = __GXData->texRegionCallback;

    __GXData->texRegionCallback = f;
    return oldcb;
}

GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f) {
    GXTlutRegionCallback oldcb = __GXData->tlutRegionCallback;

    __GXData->tlutRegionCallback = f;
    return oldcb;
}

static void __SetSURegs(u32 tmap, u32 tcoord) {
    u32 w;
    u32 h;
    u8 s_bias;
    u8 t_bias;

    w = GET_REG_FIELD(__GXData->tImage0[tmap], 10, 0);
    h = GET_REG_FIELD(__GXData->tImage0[tmap], 10, 10);
    SET_REG_FIELD(__GXData->suTs0[tcoord], 16, 0, w);
    SET_REG_FIELD(__GXData->suTs1[tcoord], 16, 0, h);
    s_bias = GET_REG_FIELD(__GXData->tMode0[tmap], 2, 0) == 1;
    t_bias = GET_REG_FIELD(__GXData->tMode0[tmap], 2, 2) == 1;
    SET_REG_FIELD(__GXData->suTs0[tcoord], 1, 16, s_bias);
    SET_REG_FIELD(__GXData->suTs1[tcoord], 1, 16, t_bias);
    GX_WRITE_RAS_REG(__GXData->suTs0[tcoord]);
    GX_WRITE_RAS_REG(__GXData->suTs1[tcoord]);
    __GXData->bpSentNot = 0;
}

void __GXSetSUTexRegs(void) {
    u32 nStages;
    u32 nIndStages;
    u32 i;
    u32 map;
    u32 tmap;
    u32 coord;
    u32* ptref;

    if (__GXData->tcsManEnab != 0xFF) {
        nStages = GET_REG_FIELD(__GXData->genMode, 4, 10) + 1;
        nIndStages = GET_REG_FIELD(__GXData->genMode, 3, 16);
        for (i = 0; i < nIndStages; i++) {
            switch (i) {
                case 0:
                    tmap = GET_REG_FIELD(__GXData->iref, 3, 0);
                    coord = GET_REG_FIELD(__GXData->iref, 3, 3);
                    break;
                case 1:
                    tmap = GET_REG_FIELD(__GXData->iref, 3, 6);
                    coord = GET_REG_FIELD(__GXData->iref, 3, 9);
                    break;
                case 2:
                    tmap = GET_REG_FIELD(__GXData->iref, 3, 12);
                    coord = GET_REG_FIELD(__GXData->iref, 3, 15);
                    break;
                case 3:
                    tmap = GET_REG_FIELD(__GXData->iref, 3, 18);
                    coord = GET_REG_FIELD(__GXData->iref, 3, 21);
                    break;
            }
            if (!(__GXData->tcsManEnab & (1 << coord))) {
                __SetSURegs(tmap, coord);
            }
        }

        i = 0;
        for (i = 0; i < nStages; i++) {
            ptref = &__GXData->tref[i / 2];
            map = __GXData->texmapId[i];
            tmap = map & 0xFFFFFEFF;
            if (i & 1) {
                coord = GET_REG_FIELD(*ptref, 3, 15);
            } else {
                coord = GET_REG_FIELD(*ptref, 3, 3);
            }
            if ((tmap != 0xFF) && !(__GXData->tcsManEnab & (1 << coord)) && (__GXData->tevTcEnab & (1 << i))) {
                __SetSURegs(tmap, coord);
            }
        }
    }
}

void __GXSetTmemConfig(u32 config) {
    switch (config) {
#if IS_CE
        case 2:
            GX_WRITE_RAS_REG(0x8c0d8000);
            GX_WRITE_RAS_REG(0x900dc000);

            GX_WRITE_RAS_REG(0x8d0d8800);
            GX_WRITE_RAS_REG(0x910dc800);

            GX_WRITE_RAS_REG(0x8e0d9000);
            GX_WRITE_RAS_REG(0x920dd000);

            GX_WRITE_RAS_REG(0x8f0d9800);
            GX_WRITE_RAS_REG(0x930dd800);

            GX_WRITE_RAS_REG(0xac0da000);
            GX_WRITE_RAS_REG(0xb00dc400);

            GX_WRITE_RAS_REG(0xad0da800);
            GX_WRITE_RAS_REG(0xb10dcc00);

            GX_WRITE_RAS_REG(0xae0db000);
            GX_WRITE_RAS_REG(0xb20dd400);

            GX_WRITE_RAS_REG(0xaf0db800);
            GX_WRITE_RAS_REG(0xb30ddc00);
            break;
#endif
        case 1:
            GX_WRITE_RAS_REG(0x8c0d8000);
            GX_WRITE_RAS_REG(0x900dc000);

            GX_WRITE_RAS_REG(0x8d0d8800);
            GX_WRITE_RAS_REG(0x910dc800);

            GX_WRITE_RAS_REG(0x8e0d9000);
            GX_WRITE_RAS_REG(0x920dd000);

            GX_WRITE_RAS_REG(0x8f0d9800);
            GX_WRITE_RAS_REG(0x930dd800);

            GX_WRITE_RAS_REG(0xac0da000);
            GX_WRITE_RAS_REG(0xb00de000);

            GX_WRITE_RAS_REG(0xad0da800);
            GX_WRITE_RAS_REG(0xb10de800);

            GX_WRITE_RAS_REG(0xae0db000);
            GX_WRITE_RAS_REG(0xb20df000);

            GX_WRITE_RAS_REG(0xaf0db800);
            GX_WRITE_RAS_REG(0xb30df800);

            break;
        case 0:
        default:
            GX_WRITE_RAS_REG(0x8c0d8000);
            GX_WRITE_RAS_REG(0x900dc000);

            GX_WRITE_RAS_REG(0x8d0d8400);
            GX_WRITE_RAS_REG(0x910dc400);

            GX_WRITE_RAS_REG(0x8e0d8800);
            GX_WRITE_RAS_REG(0x920dc800);

            GX_WRITE_RAS_REG(0x8f0d8c00);
            GX_WRITE_RAS_REG(0x930dcc00);

            GX_WRITE_RAS_REG(0xac0d9000);
            GX_WRITE_RAS_REG(0xb00dd000);

            GX_WRITE_RAS_REG(0xad0d9400);
            GX_WRITE_RAS_REG(0xb10dd400);

            GX_WRITE_RAS_REG(0xae0d9800);
            GX_WRITE_RAS_REG(0xb20dd800);

            GX_WRITE_RAS_REG(0xaf0d9c00);
            GX_WRITE_RAS_REG(0xb30ddc00);

            break;
    }
}
