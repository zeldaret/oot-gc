#ifndef _XL_POST_GCN_H
#define _XL_POST_GCN_H

#include "dolphin.h"

bool xlPostText(const char* fmt, const char* file, s32 line, ...);
bool xlPostSetup(void);
bool xlPostReset(void);

#endif
