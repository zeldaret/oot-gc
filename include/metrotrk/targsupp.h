#ifndef _METROTRK_TARGSUPP_H
#define _METROTRK_TARGSUPP_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u32 TRKAccessFile(u32, u32, u32*, u8*);
extern u32 TRKOpenFile(u32, u32, u32*, u8*);
extern u32 TRKCloseFile(u32, u32);
extern u32 TRKPositionFile(u32, u32, u32*, u8*);

#ifdef __cplusplus
}
#endif

#endif
