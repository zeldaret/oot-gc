#ifndef _DOLPHIN_DEMOPUTS_H_
#define _DOLPHIN_DEMOPUTS_H_

void/*int*/ DEMORFPrintf(s16 x, s16 y, s16 z, char *fmt, ...);
int DEMOGetRFTextWidth(char *string);
void DEMOInitCaption(s32, s32, s32);
OSFontHeader *DEMOInitROMFont(void);
void DEMOSetROMFontSize(s16 size, s16 space);

#endif
