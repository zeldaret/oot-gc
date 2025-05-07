#ifndef _SNDDVDTRK_H
#define _SNDDVDTRK_H

#include "dolphin.h"

void InitDVDTrackList(void);
s32 AddDVDTrack(char* filename);
void PlayDVDTrack(s32 songID, s32 volume, s32 fadeTime, s32 flags);
void UpdateDVDTrackList(void);

#endif
