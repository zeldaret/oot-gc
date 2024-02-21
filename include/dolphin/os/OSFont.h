#ifndef _DOLPHIN_OS_OSFONT_H_
#define _DOLPHIN_OS_OSFONT_H_

#include "dolphin/types.h"

#define OS_FONT_ENCODE_ANSI 0u
#define OS_FONT_ENCODE_SJIS 1u

u16 OSGetFontEncode(void);

#endif
