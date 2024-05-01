#ifndef _DOLPHIN_THP_H_
#define _DOLPHIN_THP_H_

#include "dolphin/types.h"

s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work);
bool THPInit(void);
u32 THPAudioDecode(s16* buffer, u8* audioFrame, s32 flag);

#endif
