#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "intrinsics.h"
#include "string.h"

static u8 GXTexMode0Ids[8] = {0x80, 0x81, 0x82, 0x83, 0xA0, 0xA1, 0xA2, 0xA3};
static u8 GXTexMode1Ids[8] = {0x84, 0x85, 0x86, 0x87, 0xA4, 0xA5, 0xA6, 0xA7};
static u8 GXTexImage0Ids[8] = {0x88, 0x89, 0x8A, 0x8B, 0xA8, 0xA9, 0xAa, 0xAb};
static u8 GXTexImage1Ids[8] = {0x8C, 0x8D, 0x8E, 0x8F, 0xAc, 0xAd, 0xAe, 0xAf};
static u8 GXTexImage2Ids[8] = {0x90, 0x91, 0x92, 0x93, 0xB0, 0xB1, 0xB2, 0xB3};
static u8 GXTexImage3Ids[8] = {0x94, 0x95, 0x96, 0x97, 0xB4, 0xB5, 0xB6, 0xB7};
static u8 GXTexTlutIds[8] = {0x98, 0x99, 0x9A, 0x9B, 0xB8, 0xB9, 0xBa, 0xBb};

static u8 GX2HWFiltConv[8] = {0x00, 0x04, 0x01, 0x05, 0x02, 0x06, 0, 0};

#define GET_TILE_COUNT(a, b) (((a) + (1 << (b)) - 1) >> (b))

static inline void __GXGetTexTileShift(GXTexFmt format, u32* widthTiles, u32* heightTiles) {
    switch (format) {
        case GX_TF_I4:
        case 0x8:
        case GX_TF_CMPR:
        case GX_CTF_R4:
        case GX_CTF_Z4:
            *widthTiles = 3;
            *heightTiles = 3;
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
            *widthTiles = 3;
            *heightTiles = 2;
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
            *widthTiles = 2;
            *heightTiles = 2;
            break;
        default:
            *widthTiles = *heightTiles = 0;
            break;
    }
}

void __GetImageTileCount(GXTexFmt format, u16 width, u16 height, u32* a, u32* b, u32* c) {
    u32 widthTiles, heightTiles;

    __GXGetTexTileShift(format, &widthTiles, &heightTiles);

    if (width <= 0) {
        width = 1;
    }

    if (height <= 0) {
        height = 1;
    }

    *a = GET_TILE_COUNT(width, widthTiles);
    *b = GET_TILE_COUNT(height, heightTiles);
    *c = (format == GX_TF_RGBA8 || format == GX_TF_Z24X8) ? 2 : 1;
}

void GXInitTexObj(GXTexObj* obj, void* imagePtr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode sWrap,
                  GXTexWrapMode tWrap, GXBool useMIPmap) {
#if IS_MQ
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    GXTexObjPriv* internal = (GXTexObjPriv*)obj;

    memset(internal, 0, 0x20);
    SET_REG_FIELD(internal->mode0, 2, 0, sWrap);
    SET_REG_FIELD(internal->mode0, 2, 2, tWrap);
    SET_REG_FIELD(internal->mode0, 1, 4, 1);
    if (useMIPmap != 0) {
        u8 lmax;
        internal->flags |= 1;

        if (format == 8 || format == 9 || format == 10) {
            internal->mode0 = (internal->mode0 & 0xFFFFFF1F) | 0xA0;
        } else {
            internal->mode0 = (internal->mode0 & 0xFFFFFF1F) | 0xC0;
        }

        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }
        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(internal->mode1, 8, 8, lmax);
    } else {
        internal->mode0 = (internal->mode0 & 0xFFFFFF1F) | 0x80;
    }
    internal->format = format;

    SET_REG_FIELD(internal->image0, 10, 0, width - 1);
    SET_REG_FIELD(internal->image0, 10, 10, height - 1);
    SET_REG_FIELD(internal->image0, 4, 20, format & 0xF);

    imageBase = (u32)((u32)imagePtr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(internal->image3, 21, 0, imageBase);

    switch (format & 0xF) {
        case 0:
        case 8:
            internal->loadFormat = 1;
            rowT = 3;
            colT = 3;
            break;
        case 1:
        case 2:
        case 9:
            internal->loadFormat = 2;
            rowT = 3;
            colT = 2;
            break;
        case 3:
        case 4:
        case 5:
        case 10:
            internal->loadFormat = 2;
            rowT = 2;
            colT = 2;
            break;
        case 6:
            internal->loadFormat = 3;
            rowT = 2;
            colT = 2;
            break;
        case 14:
            internal->loadFormat = 0;
            rowT = 3;
            colT = 3;
            break;
        default:
            internal->loadFormat = 2;
            rowT = 2;
            colT = 2;
            break;
    }

    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    internal->loadCount = (rowC * colC) & 0x7FFF;
    internal->flags |= 2;
#else
    u32 imageBase;
    u16 a, b;
    u32 c, d;

    GXTexObjPriv* internal = (GXTexObjPriv*)obj;
    memset(internal, 0, sizeof(*internal));

    GX_SET_REG(internal->mode0, sWrap, 30, 31);
    GX_SET_REG(internal->mode0, tWrap, 28, 29);
    GX_SET_REG(internal->mode0, GX_TRUE, 27, 27);

    if (useMIPmap) {
        u32 maxDimSize;
        internal->flags |= 1;
        if (format == 8 || format == 9 || format == 10) {
            GX_SET_REG(internal->mode0, 5, 24, 26);
        } else {
            GX_SET_REG(internal->mode0, 6, 24, 26);
        }

        maxDimSize = width > height ? 31 - __cntlzw(width) : 31 - __cntlzw(height);

        GX_SET_REG(internal->mode1, (maxDimSize) * 16.f, 16, 23);
    } else {
        GX_SET_REG(internal->mode0, 4, 24, 26);
    }

    internal->format = format;
    GX_SET_REG(internal->image0, width - 1, 22, 31);
    GX_SET_REG(internal->image0, height - 1, 12, 21);

    GX_SET_REG(internal->image0, format & 0xF, 8, 11);
    imageBase = (u32)imagePtr >> 5;
    GX_SET_REG(internal->image3, imageBase, 11, 31);

    switch (format & 0xF) {
        case 0:
        case 8:
            internal->loadFormat = 1;
            a = 3;
            b = 3;
            break;
        case 1:
        case 2:
        case 9:
            internal->loadFormat = 2;
            a = 3;
            b = 2;
            break;
        case 3:
        case 4:
        case 5:
        case 10:
            internal->loadFormat = 2;
            a = 2;
            b = 2;
            break;
        case 6:
            internal->loadFormat = 3;
            a = 2;
            b = 2;
            break;
        case 0xE:
            internal->loadFormat = 0;
            a = 3;
            b = 3;
            break;
        default:
            internal->loadFormat = 2;
            a = 2;
            b = 2;
            break;
    }

    internal->loadCount = (GET_TILE_COUNT(width, a) * GET_TILE_COUNT(height, b)) & 0x7FFF;

    internal->flags |= 2;
#endif
}

void GXInitTexObjCI(GXTexObj* obj, void* imagePtr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode sWrap,
                    GXTexWrapMode tWrap, GXBool useMIPmap, u32 tlutName) {
    GXTexObjPriv* internal = (GXTexObjPriv*)obj;

    GXInitTexObj(obj, imagePtr, width, height, format, sWrap, tWrap, useMIPmap);

    internal->flags &= ~2;
    internal->tlutName = tlutName;
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter minFilter, GXTexFilter maxFilter, f32 minLOD, f32 maxLOD, f32 lodBias,
                     GXBool doBiasClamp, GXBool doEdgeLOD, GXAnisotropy maxAniso) {
    GXTexObjPriv* internal = (GXTexObjPriv*)obj;
    u8 reg1;
    u8 reg2;

    if (lodBias < -4.0f) {
        lodBias = -4.0f;
    } else if (lodBias >= 4.0f) {
        lodBias = 3.99f;
    }

    GX_SET_REG(internal->mode0, (u8)(lodBias * 32.0f), 15, 22);

#if IS_MQ
    SET_REG_FIELD(internal->mode0, 1, 4, (maxFilter == GX_LINEAR) ? 1 : 0);
    SET_REG_FIELD(internal->mode0, 3, 5, GX2HWFiltConv[minFilter]);
    SET_REG_FIELD(internal->mode0, 1, 8, doEdgeLOD ? 0 : 1);
    internal->mode0 &= 0xFFFDFFFF;
    internal->mode0 &= 0xFFFBFFFF;
    SET_REG_FIELD(internal->mode0, 2, 19, maxAniso);
    SET_REG_FIELD(internal->mode0, 1, 21, doBiasClamp);
#else
    GX_SET_REG(internal->mode0, maxFilter == 1 ? 1 : 0, 27, 27);
    GX_SET_REG(internal->mode0, GX2HWFiltConv[minFilter], 24, 26);
    GX_SET_REG(internal->mode0, doEdgeLOD ? 0 : 1, 23, 23);
    GX_SET_REG(internal->mode0, 0, 14, 14);
    GX_SET_REG(internal->mode0, 0, 13, 13);
    GX_SET_REG(internal->mode0, maxAniso, 11, 12);
    GX_SET_REG(internal->mode0, doBiasClamp, 10, 10);
#endif

    if (minLOD < 0.0f) {
        minLOD = 0.0f;
    } else if (minLOD > 10.0f) {
        minLOD = 10.0f;
    }
    reg1 = minLOD * 16.0f;

    if (maxLOD < 0.0f) {
        maxLOD = 0.0f;
    } else if (maxLOD > 10.0f) {
        maxLOD = 10.0f;
    }
    reg2 = maxLOD * 16.0f;

    GX_SET_REG(internal->mode1, reg1, 24, 31);
    GX_SET_REG(internal->mode1, reg2, 16, 23);
}

void* GXGetTexObjData(GXTexObj* tex_obj) {
    GXTexObjPriv* t = (GXTexObjPriv*)tex_obj;
    return (void*)(GET_REG_FIELD(t->image3, 21, 0) << 5);
}

GXTexFmt GXGetTexObjFmt(GXTexObj* obj) {
    GXTexObjPriv* pObj = (GXTexObjPriv*)obj;
    return pObj->format;
}

GXBool GXGetTexObjMipMap(GXTexObj* obj) {
    GXTexObjPriv* internal = (GXTexObjPriv*)obj;
    return (internal->flags & 1) == 1;
}

void GXLoadTexObjPreLoaded(GXTexObj* obj, GXTexRegion* region, GXTexMapID map) {
#if IS_CE
    u8 stackManipulation[0x18];
#endif

    GXTexObjPriv* internalObj = (GXTexObjPriv*)obj;
    GXTexRegionPriv* internalRegion = (GXTexRegionPriv*)region;

    GX_SET_REG(internalObj->mode0, GXTexMode0Ids[map], 0, 7);
    GX_SET_REG(internalObj->mode1, GXTexMode1Ids[map], 0, 7);
    GX_SET_REG(internalObj->image0, GXTexImage0Ids[map], 0, 7);

    GX_SET_REG(internalRegion->unk0, GXTexImage1Ids[map], 0, 7);
    GX_SET_REG(internalRegion->unk4, GXTexImage2Ids[map], 0, 7);

    GX_SET_REG(internalObj->image3, GXTexImage3Ids[map], 0, 7);

    GX_BP_LOAD_REG(internalObj->mode0);
    GX_BP_LOAD_REG(internalObj->mode1);
    GX_BP_LOAD_REG(internalObj->image0);
    GX_BP_LOAD_REG(internalRegion->unk0);
    GX_BP_LOAD_REG(internalRegion->unk4);
    GX_BP_LOAD_REG(internalObj->image3);

    if ((internalObj->flags & 2) == 0) {
        GXTlutObjPriv* tlut = (GXTlutObjPriv*)gx->tlutRegionCallback(internalObj->tlutName);
        GX_SET_REG(tlut->unk4, GXTexTlutIds[map], 0, 7);

        GX_BP_LOAD_REG(tlut->unk4);
    }

    gx->tImage0[map] = internalObj->image0;
    gx->tMode0[map] = internalObj->mode0;

    gx->dirtyState |= GX_DIRTY_SU_TEX;
    gx->bpSentNot = GX_FALSE;
}

void GXLoadTexObj(GXTexObj* obj, GXTexMapID map) {
    GXTexRegion* ret = (GXTexRegion*)gx->texRegionCallback(obj, map);

    GXLoadTexObjPreLoaded(obj, ret, map);
}

void GXInitTlutObj(GXTlutObj* obj, void* table, GXTlutFmt format, u16 numEntries) {
    GXTlutObjPriv* internal = (GXTlutObjPriv*)obj;

    internal->unk0 = 0;

    GX_SET_REG(internal->unk0, format, 20, 21);
    GX_SET_REG(internal->unk4, ((u32)table & 0x3FFFFFFF) >> 5, 11, 31);
    GX_SET_REG(internal->unk4, 100, 0, 7);

    internal->numEntries = numEntries;
}

void GXLoadTlut(GXTlutObj* obj, u32 tlutName) {
    GXTlutObjPriv* internal = (GXTlutObjPriv*)obj;
    GXTlutRegionPriv* ret = (GXTlutRegionPriv*)gx->tlutRegionCallback(tlutName);
    u32 reg;

    __GXFlushTextureState();

    GX_BP_LOAD_REG(internal->unk4);
    GX_BP_LOAD_REG(ret->unk0);

    __GXFlushTextureState();

    reg = ret->unk0 & 0x3FF;
    GX_SET_REG(internal->unk0, reg, 22, 31);

    ret->tlutObj = *internal;
}

void GXInitTexCacheRegion(GXTexRegion* region, GXBool is32bMIPmap, u32 memEven, GXTexCacheSize sizeEven, u32 memOdd,
                          GXTexCacheSize sizeOdd) {
    GXTexRegionPriv* internal = (GXTexRegionPriv*)region;

    u32 reg;
    switch (sizeEven) {
        case 0:
            reg = 3;
            break;
        case 1:
            reg = 4;
            break;
        case 2:
            reg = 5;
            break;
    }

    internal->unk0 = 0;

    GX_SET_REG(internal->unk0, memEven >> 5, 17, 31);
    GX_SET_REG(internal->unk0, reg, 14, 16);
    GX_SET_REG(internal->unk0, reg, 11, 13);
    GX_SET_REG(internal->unk0, 0, 10, 10);

    switch (sizeOdd) {
        case 0:
            reg = 3;
            break;
        case 1:
            reg = 4;
            break;
        case 2:
            reg = 5;
            break;
        case 3:
            reg = 0;
            break;
    }

    internal->unk4 = 0;
    GX_SET_REG(internal->unk4, memOdd >> 5, 17, 31);
    GX_SET_REG(internal->unk4, reg, 14, 16);
    GX_SET_REG(internal->unk4, reg, 11, 13);

    internal->unkC = is32bMIPmap;
    internal->unkD = 1;
}

void GXInitTlutRegion(GXTlutRegion* region, u32 memAddr, GXTlutSize tlutSize) {
    GXTlutRegionPriv* internal = (GXTlutRegionPriv*)region;

    internal->unk0 = 0;
    GX_SET_REG(internal->unk0, (memAddr - 0x80000) >> 9, 22, 31);
    GX_SET_REG(internal->unk0, tlutSize, 11, 21);
    GX_SET_REG(internal->unk0, 0x65, 0, 7);
}

void GXInvalidateTexAll(void) {
    __GXFlushTextureState();
    GX_BP_LOAD_REG(0x66001000);
    GX_BP_LOAD_REG(0x66001100);
    __GXFlushTextureState();
}

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback func) {
    GXTexRegionCallback oldFunc = gx->texRegionCallback;

    gx->texRegionCallback = func;

    return oldFunc;
}

GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback func) {
    GXTlutRegionCallback oldFunc = gx->tlutRegionCallback;

    gx->tlutRegionCallback = func;

    return oldFunc;
}

void __SetSURegs(u32 texImgIndex, u32 setUpRegIndex) {
    u32 a1;
    u32 a2;
    GXBool b;
    GXBool c;

    a1 = GX_GET_REG(gx->tImage0[texImgIndex], 22, 31);
    a2 = (gx->tImage0[texImgIndex] & (0x3FF << 10)) >> 10;

    GX_SET_REG(gx->suTs0[setUpRegIndex], a1, 16, 31);
    GX_SET_REG(gx->suTs1[setUpRegIndex], a2, 16, 31);

    b = GX_GET_REG(gx->tMode0[texImgIndex], 30, 31) == 1;
    c = GX_GET_REG(gx->tMode0[texImgIndex], 28, 29) == 1;

    GX_SET_REG(gx->suTs0[setUpRegIndex], b, 15, 15);
    GX_SET_REG(gx->suTs1[setUpRegIndex], c, 15, 15);

    GX_BP_LOAD_REG(gx->suTs0[setUpRegIndex]);
    GX_BP_LOAD_REG(gx->suTs1[setUpRegIndex]);

    gx->bpSentNot = GX_FALSE;
}

#pragma dont_inline on
void __GXSetSUTexRegs(void) {
    u32 i;
    u32 b;
    u32 a;
    u32 c;
    u32 d;
    u32 stackFiller;
    if (gx->tcsManEnab != 0xFf) {
        a = GX_GET_REG(gx->genMode, 18, 21) + 1;
        b = GX_GET_REG(gx->genMode, 13, 15);
        for (i = 0; i < b; i++) {
            switch (i) {
                case 0:
                    c = GX_GET_REG(gx->iref, 29, 31);
                    d = GX_GET_REG(gx->iref, 26, 28);
                    break;
                case 1:
                    c = GX_GET_REG(gx->iref, 23, 25);
                    d = GX_GET_REG(gx->iref, 20, 22);
                    break;
                case 2:
                    c = GX_GET_REG(gx->iref, 17, 19);
                    d = GX_GET_REG(gx->iref, 14, 16);
                    break;
                case 3:
                    c = GX_GET_REG(gx->iref, 11, 13);
                    d = GX_GET_REG(gx->iref, 8, 10);
                    break;
            }

            if (!(gx->tcsManEnab & (1 << d))) {
                __SetSURegs(c, d);
            }
        }

        for (i = 0; i < a; i++) {
            u32* g = &gx->tref[i / 2];

            c = gx->texmapId[i] & ~0x100;

            if (i & 1) {
                d = GX_GET_REG(*g, 14, 16);
            } else {
                d = GX_GET_REG(*g, 26, 28);
            }

            if (c != 0xFf && !(gx->tcsManEnab & (1 << d)) && gx->tevTcEnab & (1 << i)) {
                __SetSURegs(c, d);
            }
        }
    }
}
#pragma dont_inline reset

void __GXSetTmemConfig(u32 config) {
    switch (config) {

#if IS_CE
        case 2:
            GX_BP_LOAD_REG(0x8C0d8000);
            GX_BP_LOAD_REG(0x900DC000);

            GX_BP_LOAD_REG(0x8D0d8800);
            GX_BP_LOAD_REG(0x910DC800);

            GX_BP_LOAD_REG(0x8E0d9000);
            GX_BP_LOAD_REG(0x920DD000);

            GX_BP_LOAD_REG(0x8F0d9800);
            GX_BP_LOAD_REG(0x930DD800);

            GX_BP_LOAD_REG(0xAC0DA000);
            GX_BP_LOAD_REG(0xB00DC400);

            GX_BP_LOAD_REG(0xAD0DA800);
            GX_BP_LOAD_REG(0xB10DCC00);

            GX_BP_LOAD_REG(0xAE0DB000);
            GX_BP_LOAD_REG(0xB20DD400);

            GX_BP_LOAD_REG(0xAF0DB800);
            GX_BP_LOAD_REG(0xB30DDC00);
            break;
#endif

        case 1:
            GX_BP_LOAD_REG(0x8C0d8000);
            GX_BP_LOAD_REG(0x900DC000);

            GX_BP_LOAD_REG(0x8D0d8800);
            GX_BP_LOAD_REG(0x910DC800);

            GX_BP_LOAD_REG(0x8E0d9000);
            GX_BP_LOAD_REG(0x920DD000);

            GX_BP_LOAD_REG(0x8F0d9800);
            GX_BP_LOAD_REG(0x930DD800);

            GX_BP_LOAD_REG(0xAC0DA000);
            GX_BP_LOAD_REG(0xB00DE000);

            GX_BP_LOAD_REG(0xAD0DA800);
            GX_BP_LOAD_REG(0xB10DE800);

            GX_BP_LOAD_REG(0xAE0DB000);
            GX_BP_LOAD_REG(0xB20DF000);

            GX_BP_LOAD_REG(0xAF0DB800);
            GX_BP_LOAD_REG(0xB30DF800);

            break;
        case 0:
        default:
            GX_BP_LOAD_REG(0x8C0d8000);
            GX_BP_LOAD_REG(0x900DC000);

            GX_BP_LOAD_REG(0x8D0d8400);
            GX_BP_LOAD_REG(0x910DC400);

            GX_BP_LOAD_REG(0x8E0d8800);
            GX_BP_LOAD_REG(0x920DC800);

            GX_BP_LOAD_REG(0x8F0d8c00);
            GX_BP_LOAD_REG(0x930DCC00);

            GX_BP_LOAD_REG(0xAC0D9000);
            GX_BP_LOAD_REG(0xB00DD000);

            GX_BP_LOAD_REG(0xAD0D9400);
            GX_BP_LOAD_REG(0xB10DD400);

            GX_BP_LOAD_REG(0xAE0D9800);
            GX_BP_LOAD_REG(0xB20DD800);

            GX_BP_LOAD_REG(0xAF0D9C00);
            GX_BP_LOAD_REG(0xB30DDC00);

            break;
    }
}
