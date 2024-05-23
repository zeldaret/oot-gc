#include "dolphin/dvd.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "dolphin/tex.h"
#include "macros.h"

#define PALETTE_VERSION 0x20AF30

TEXDescriptor* TEXGet(TEXPalette* pal, u32 id) { return &pal->descriptorArray[id]; }

void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id) {
    TEXDescriptor* tdp;
    GXBool mipMap;

    tdp = TEXGet(pal, id);
    if (tdp->textureHeader->minLOD == tdp->textureHeader->maxLOD) {
        mipMap = GX_FALSE;
    } else {
        mipMap = GX_TRUE;
    }
    GXInitTexObj(to, tdp->textureHeader->data, tdp->textureHeader->width, tdp->textureHeader->height,
                 tdp->textureHeader->format, tdp->textureHeader->wrapS, tdp->textureHeader->wrapT, mipMap);
    GXInitTexObjLOD(to, tdp->textureHeader->minFilter, tdp->textureHeader->magFilter, tdp->textureHeader->minLOD,
                    tdp->textureHeader->maxLOD, tdp->textureHeader->LODBias, GX_DISABLE,
                    tdp->textureHeader->edgeLODEnable, GX_ANISO_1);
}
