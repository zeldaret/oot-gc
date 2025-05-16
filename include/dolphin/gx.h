#ifndef _DOLPHIN_GX_H
#define _DOLPHIN_GX_H

#include "dolphin/gx/GXBump.h"
#include "dolphin/gx/GXCommandList.h"
#include "dolphin/gx/GXCpu2Efb.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXDispList.h"
#include "dolphin/gx/GXDraw.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXFifo.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXGet.h"
#include "dolphin/gx/GXLighting.h"
#include "dolphin/gx/GXManage.h"
#include "dolphin/gx/GXPerf.h"
#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GXVerify.h"
#include "dolphin/gx/GXVert.h"

// unsorted GX externs

#ifdef __cplusplus
extern "C" {
#endif

// GXMisc
void (*GXSetDrawSyncCallback(void (*cb)(u16)))(u16);
void GXSetDrawSync(u16 token);

#ifdef __cplusplus
}
#endif

#endif
