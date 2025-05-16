#ifndef _DOLPHIN_OS_OSLC_H
#define _DOLPHIN_OS_OSLC_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void LCAllocOneTag(bool invalidate, void* tag);
void LCAllocTags(bool invalidate, void* startTag, u32 numBlocks);
void LCAlloc(void* addr, u32 nBytes);
void LCAllocNoInvalidate(void* addr, u32 nBytes);

#ifdef __cplusplus
}
#endif

#endif
