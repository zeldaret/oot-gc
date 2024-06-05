#include "dolphin.h"
#include "dolphin/demo.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "stdarg.h"

extern u32 DEMOFontBitmap[];
static GXTexObj fontTexObj;
static s32 fontShift;

void DEMOSetFontType(DMFontType attr) {
    switch (attr) {
        case DM_FT_RVS:
            GXSetBlendMode(GX_BM_LOGIC, GX_BL_ZERO, GX_BL_ZERO, GX_LO_INVCOPY);
            break;
        case DM_FT_XLU:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
            break;
        case DM_FT_OPQ:
        default:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
            break;
    }
}

void DEMOLoadFont(enum _GXTexMapID texMap, enum _GXTexMtx texMtx, DMTexFlt texFlt) {
    Mtx fontTMtx;
    u16 width;
    u16 height;

    width = 64;
    height = 0x1800 / width;
    GXInitTexObj(&fontTexObj, (void*)DEMOFontBitmap, width, (u16)height, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    if (texFlt == DMTF_POINTSAMPLE) {
        GXInitTexObjLOD(&fontTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_FALSE, GX_ANISO_1);
        fontShift = 0;
    } else {
        fontShift = 1;
    }
    GXLoadTexObj(&fontTexObj, texMap);
    PSMTXScale(fontTMtx, 1.0f / (f32)width, 1.0f / (f32)height, 1.0f);
    GXLoadTexMtxImm(fontTMtx, texMtx, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtx);
}

void DEMOSetupScrnSpc(s32 width, s32 height, f32 depth) {
    Mtx44 pMtx;
    Mtx mMtx;
    f32 top = 0.0f;

#if IS_CE
    if (DEMOGetRenderModeObj()->field_rendering && !VIGetNextField()) {
        top = -0.667f;
    } else {
        top = 0.0f;
    }
#endif

    C_MTXOrtho(pMtx, top, (f32)height, 0.0f, (f32)width, 0.0f, -depth);
    GXSetProjection(pMtx, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mMtx);
    GXLoadPosMtxImm(mMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

void DEMOInitCaption(s32 font_type, s32 width, s32 height) {
    DEMOSetupScrnSpc(width, height, 100.0f);
    GXSetZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    DEMOLoadFont(GX_TEXMAP0, GX_TEXMTX0, DMTF_POINTSAMPLE);
    DEMOSetFontType(font_type);
}

void DEMOPuts(s16 x, s16 y, s16 z, char* string) {
    char* str;
    s32 s;
    s32 t;
    s32 c;
    s32 w;
    s32 len;
    s32 i;

    str = string;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);

    len = 0;
    while (1) {
        c = *(str++);
        if ((c >= 0x20) && (c <= 0x7F)) {
            len++;
            continue;
        }

        if (len > 0) {
            GXBegin(GX_QUADS, GX_VTXFMT0, len * 4);
            for (i = 0; i < len; i++) {
                w = string[i] - 0x20;
                s = fontShift + ((w % 8) * 0x10);
                t = fontShift + ((w / 8) * 0x10);
                GXPosition3s16(x + (i * 8), y, z);
                GXTexCoord2s16(s, t);
                GXPosition3s16(x + (i * 8) + 8, y, z);
                GXTexCoord2s16(s + 0x10, t);
                GXPosition3s16(x + (i * 8) + 8, y + 8, z);
                GXTexCoord2s16(s + 0x10, t + 0x10);
                GXPosition3s16(x + (i * 8), y + 8, z);
                GXTexCoord2s16(s, t + 0x10);
            }
            GXEnd();
            len = 0;
        }

        string = str;
        if (c == '\n') {
            y += 0x8;
        } else {
            break;
        }
    }
}

void DEMOPrintf(s16 x, s16 y, s16 z, char* fmt, ...) {
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    DEMOPuts(x, y, z, buf);
    va_end(vlist);
}
