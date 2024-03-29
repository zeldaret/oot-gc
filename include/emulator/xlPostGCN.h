#ifndef _XL_POST_GCN_H
#define _XL_POST_GCN_H

#include "dolphin.h"

s32 xlPostText(const char* fmt, const char* file, s32 line, ...);
s32 xlPostSetup(void);
s32 xlPostReset(void);

#endif
