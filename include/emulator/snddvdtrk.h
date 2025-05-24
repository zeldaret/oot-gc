#ifndef _SNDDVDTRK_H
#define _SNDDVDTRK_H

#include "dolphin/dvd.h"
#include "dolphin/types.h"

// __anon_0x9466F
typedef enum DVDTrackState {
    TRACK_NOTHING = 0,
    TRACK_PREPARE_STREAM = 1,
    TRACK_PLAYING_STREAM = 2,
    TRACK_PAUSING_STREAM = 3,
    TRACK_PAUSE_STREAM = 4,
    TRACK_FADE_IN_STREAM = 5,
    TRACK_FADE_OUT_PAUSE = 6,
    TRACK_FADE_OUT_HOLD_PAUSE = 7,
    TRACK_FADE_OUT_STREAM = 8,
    TRACK_STOPPING_STREAM = 9,
    MAX_TRACK_STATES = 10,
} DVDTrackState;

// __anon_0x935DD
typedef enum ErrorRetreivalState {
    NO_ERROR_RETRIEVING = 0,
    RETRIEVING_ERROR = 1,
    ERROR_RETRIEVED = 2,
} ErrorRetreivalState;

// __anon_0x93582
typedef union __anon_0x93582 {
    /* 0x0 */ s32 code;
    /* 0x0 */ u8 bytes[4];
} __anon_0x93582;

// __anon_0x9364C
typedef struct DVDTrackInfo {
    /* 0x0 */ s32 fadeTime;
    /* 0x4 */ s32 volume;
    /* 0x8 */ s32 trackID;
    /* 0xC */ s32 flags;
} DVDTrackInfo; // size = 0x10

// __anon_0x936FF
typedef struct DVDFadeInfo {
    /* 0x00 */ s32 curTime;
    /* 0x04 */ s32 fadeTime;
    /* 0x08 */ s32 curVol;
    /* 0x0C */ s32 startVol;
    /* 0x10 */ s32 nextVol;
} DVDFadeInfo; // size = 0x14

// __anon_0x937D8
typedef struct DVDTrackList {
    /* 0x000 0x03C */ s32 fileIDs[60];
    /* 0x0F0 0x12C */ char filenames[60][32];
    /* 0x870 0x8AC */ u8 playOrder[60];
    /* 0x8AC 0x8E8 */ DVDFileInfo playingFileInfo;
    /* 0x8E8 0x924 */ __anon_0x93582 error;
    /* 0x8EC 0x928 */ volatile ErrorRetreivalState errorState;
    /* 0x8F0 0x92C */ s32 numTracks;
    /* 0x8F4 0x930 */ DVDTrackInfo curState;
    /* 0x904 0x940 */ DVDTrackInfo nextState;
    /* 0x914 0x950 */ DVDTrackInfo queueState;
    /* 0x924 0x960 */ s32 stopTrack;
    /* 0x928 0x964 */ s32 stopFadeTime;
    /* 0x92C 0x968 */ s32 fadeTime;
    /* 0x930 0x96C */ s32 waitTime;
    /* 0x934 0x970 */ DVDFadeInfo fadeInfo;
    /* 0x948 0x984 */ s32 volume;
    /* 0x94C 0x988 */ s32 fadeInOutVolume;
    /* 0x950 0x98C */ volatile DVDTrackState state;
    /* 0x954 0x990 */ DVDTrackState lastState;
} DVDTrackList; // size = 0x958

void InitDVDTrackList(void);
s32 AddDVDTrack(char* filename);
void PlayDVDTrack(s32 songID, s32 volume, s32 fadeTime, s32 flags);
void UpdateDVDTrackList(void);
void PauseDVDTrack(void);

#endif
