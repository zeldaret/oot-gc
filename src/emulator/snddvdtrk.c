#include "emulator/snddvdtrk.h"
#include "emulator/simGCN.h"
#include "macros.h"

static bool CheckForStopDVDTrack(void);
static void CheckErrorStatus(s32 result, DVDCommandBlock* block);
static void DVDTrackStopCallback(s32 result, DVDCommandBlock* block);
static void DVDTrackPrepareStreamCallback(s32 result, DVDFileInfo* fileInfo);
static void DVDTrackCancelStreamCallback(s32 result, DVDCommandBlock* block);
static void DVDTrackFadeOutUpdate(void);
static void DVDTrackFadeOutPauseUpdate(void);
static void DVDTrackFadeInUpdate(void);
static void ErrorCallBack(s32 result, DVDFileInfo* pdfi);
static bool HandleDVDTrackListError(void);
static void StopDVDTrack(s32 fadeTime);
static void SetDVDTrackVolume(void);
static bool IsDVDTrackPaused(void);

s32 gBGMVolume = 127;
s32* gDVDVolumeP = &gBGMVolume;
static s32 vErrReadDone;
static DVDFileInfo sErrorDFI;
DVDTrackList gDVDTrackList;

static bool CheckForStopDVDTrack(void) {
    if (gDVDTrackList.stopTrack == 1) {
        gDVDTrackList.fadeTime = gDVDTrackList.stopFadeTime;
        gDVDTrackList.curState.fadeTime = gDVDTrackList.stopFadeTime;
        gDVDTrackList.state = TRACK_FADE_OUT_STREAM;
        return true;
    }

    if (gDVDTrackList.stopTrack == 2) {
        gDVDTrackList.fadeTime = gDVDTrackList.stopFadeTime;
        gDVDTrackList.curState.fadeTime = gDVDTrackList.stopFadeTime;
        gDVDTrackList.state = TRACK_FADE_OUT_PAUSE;
        gDVDTrackList.stopTrack = 0;
        return true;
    }

    if (gDVDTrackList.nextState.trackID >= 0) {
        gDVDTrackList.curState.fadeTime = 0;
        gDVDTrackList.fadeTime = 0;
        gDVDTrackList.state = TRACK_FADE_OUT_STREAM;
        return true;
    }

    return false;
}

static void CheckErrorStatus(s32 result, DVDCommandBlock* block) {
    s32* pResult = &result;

    // bug? it was probably intended to be `if (*pResult < 0) { ... };`
    if (*pResult < 0)
        ;

    gDVDTrackList.error.code = *pResult;
    gDVDTrackList.errorState = ERROR_RETRIEVED;
}

static void DVDTrackStopCallback(s32 result, DVDCommandBlock* block) {}

static void DVDTrackPrepareStreamCallback(s32 result, DVDFileInfo* fileInfo) {
    DVDTrackState lastState;

    if (result == 0) {
        if (gDVDTrackList.waitTime >= 30) {
            StopDVDTrack(gDVDTrackList.stopFadeTime);
        } else {

            if (gDVDTrackList.state != TRACK_FADE_OUT_STREAM) {
                lastState = gDVDTrackList.state;
                gDVDTrackList.fadeInOutVolume = 0;
                gDVDTrackList.volume = gDVDTrackList.curState.volume;
                gDVDTrackList.state = TRACK_FADE_IN_STREAM;

                if (gDVDTrackList.fadeTime >= gDVDTrackList.curState.fadeTime) {
                    gDVDTrackList.fadeInOutVolume = 128;
                    gDVDTrackList.state = TRACK_PLAYING_STREAM;
                } else {
                    gDVDTrackList.fadeTime++;
                    gDVDTrackList.fadeInOutVolume = (gDVDTrackList.fadeTime * 128) / gDVDTrackList.curState.fadeTime;
                }

                SetDVDTrackVolume();

                if (!(gDVDTrackList.curState.flags & 0x4000) && lastState != TRACK_PAUSING_STREAM) {
                    AISetStreamPlayState(1);
                } else {
                    PauseDVDTrack();
                }

                gDVDTrackList.curState.flags &= 0xFFFFBFFF;

                if (!(gDVDTrackList.curState.flags & 1)) {
                    DVDStopStreamAtEndAsync(&fileInfo->cb, &DVDTrackStopCallback);
                }
            }
        }

        gDVDTrackList.curState.flags &= 0xFFFFBFFF;
    }
}

static void DVDTrackCancelStreamCallback(s32 result, DVDCommandBlock* block) {
    if (result == DVD_STATE_END) {
        DVDClose(&gDVDTrackList.playingFileInfo);
        AISetStreamPlayState(0);
        gDVDTrackList.state = TRACK_NOTHING;
        gDVDTrackList.curState.trackID = -1;
    }
}

static void DVDTrackFadeOutUpdate(void) {
    s32 pad;

    if (gDVDTrackList.fadeTime <= 0) {
        gDVDTrackList.error.code = DVD_STATE_END;
        gDVDTrackList.error.bytes[3] = 1;

        if (gDVDTrackList.fadeTime < 0 && gDVDTrackList.fadeTime == -1) {
            gDVDTrackList.fadeTime = 0;
            gDVDTrackList.error.code = DVDGetStreamErrorStatus(&gDVDTrackList.playingFileInfo.cb);
        }

        gDVDTrackList.fadeInOutVolume = 0;
        SetDVDTrackVolume();
        gDVDTrackList.state = TRACK_STOPPING_STREAM;

        if (gDVDTrackList.error.bytes[0] != 0 || gDVDTrackList.error.bytes[1] != 0 ||
            gDVDTrackList.error.bytes[3] == 0) {
            DVDClose(&gDVDTrackList.playingFileInfo);
            AISetStreamPlayState(0);
            gDVDTrackList.state = TRACK_NOTHING;
            gDVDTrackList.curState.trackID = -1;
        } else if (!DVDCancelStreamAsync(&gDVDTrackList.playingFileInfo.cb, DVDTrackCancelStreamCallback)) {
            DVDClose(&gDVDTrackList.playingFileInfo);
            AISetStreamPlayState(0);
            gDVDTrackList.state = TRACK_NOTHING;
            gDVDTrackList.curState.trackID = -1;
        }
    } else {
        gDVDTrackList.fadeTime--;
        gDVDTrackList.fadeInOutVolume = (gDVDTrackList.fadeTime * 128) / gDVDTrackList.curState.fadeTime;
        SetDVDTrackVolume();
    }
}

static void DVDTrackFadeOutPauseUpdate(void) {
    if (gDVDTrackList.fadeTime <= 0) {
        AISetStreamPlayState(0);
        gDVDTrackList.state = TRACK_FADE_OUT_HOLD_PAUSE;
    } else {
        gDVDTrackList.fadeTime--;
        gDVDTrackList.fadeInOutVolume = (gDVDTrackList.fadeTime * 128) / gDVDTrackList.curState.fadeTime;
        SetDVDTrackVolume();
    }
}

static void DVDTrackFadeInUpdate(void) {
    if (gDVDTrackList.fadeTime >= gDVDTrackList.curState.fadeTime) {
        gDVDTrackList.fadeInOutVolume = 128;
        gDVDTrackList.state = TRACK_PLAYING_STREAM;
    } else {
        gDVDTrackList.fadeTime++;
        gDVDTrackList.fadeInOutVolume = (gDVDTrackList.fadeTime * 128) / gDVDTrackList.curState.fadeTime;
    }

    SetDVDTrackVolume();
}

void InitDVDTrackList(void) {
    int i;

    memset(&gDVDTrackList, 0, sizeof(DVDTrackList));
    gDVDTrackList.nextState.trackID = -1;
    gDVDTrackList.curState.trackID = -1;
    gDVDTrackList.state = TRACK_NOTHING;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);

    for (i = 0; i < ARRAY_COUNT(gDVDTrackList.playOrder); i++) {
        gDVDTrackList.playOrder[i] = i;
    }
}

s32 AddDVDTrack(char* filename) {
    if (gDVDTrackList.numTracks >= ARRAY_COUNT(gDVDTrackList.playOrder)) {
        return -1;
    }

    strncpy(gDVDTrackList.filenames[gDVDTrackList.numTracks], filename, 0x20);
    gDVDTrackList.fileIDs[gDVDTrackList.numTracks] =
        DVDConvertPathToEntrynum(gDVDTrackList.filenames[gDVDTrackList.numTracks]);

    return gDVDTrackList.numTracks++;
}

void PlayDVDTrack(s32 songID, s32 volume, s32 fadeTime, s32 flags) {
    if (songID < 0 || songID >= gDVDTrackList.numTracks) {
        return;
    }

    songID = gDVDTrackList.playOrder[songID];

    if (gDVDTrackList.fileIDs[songID] >= 0) {
        if (volume < 0) {
            volume = 255;
        }

        if ((((gDVDTrackList.nextState.trackID >= 0 || songID != gDVDTrackList.curState.trackID) ||
              volume != gDVDTrackList.curState.volume) ||
             (((gDVDTrackList.state < TRACK_PREPARE_STREAM || (gDVDTrackList.state > TRACK_FADE_IN_STREAM)) &&
               gDVDTrackList.state != TRACK_PAUSING_STREAM))) ||
            gDVDTrackList.stopTrack != 0) {

            gDVDTrackList.nextState.flags = flags;
            gDVDTrackList.nextState.trackID = songID;
            gDVDTrackList.nextState.fadeTime = fadeTime;
            gDVDTrackList.nextState.volume = volume;
            gDVDTrackList.fadeInfo.startVol = 127;
            gDVDTrackList.fadeInfo.nextVol = 127;
            gDVDTrackList.fadeInfo.curVol = 127;

            if (gDVDTrackList.state == TRACK_PAUSING_STREAM || gDVDTrackList.state == TRACK_PAUSE_STREAM) {
                CheckForStopDVDTrack();
            }
        }
    }
}

static void ErrorCallBack(s32 result, DVDFileInfo* pdfi) {
    if (result != -1) {
        DVDClose(pdfi);
        vErrReadDone--;
    }
}

static bool HandleDVDTrackListError(void) {
    s32 status = DVDGetDriveStatus();
    bool flag = status == 4 || status == 5 || status == 6 || status == 11 || status == -1;

    if (!flag && DVDCheckDisk() != 1 && vErrReadDone == 0) {
        vErrReadDone = 1;
        DVDOpen("yes.raw", &sErrorDFI);
        DVDSeekAsyncPrio(&sErrorDFI, 0, ErrorCallBack, 2);

        status = DVDGetDriveStatus();
        flag = status == 4 || status == 5 || status == 6 || status == 11 || status == -1;
    }

    if (!flag) {
        return false;
    }

    simulatorDVDShowError(status, NULL, 0, 0);
    return true;
}

void UpdateDVDTrackList(void) {
    s32 updateVolume;
    s32 error;

    static s32 counter = 0;

    updateVolume = false;
    error = false;

    UpdateSpecial();

    if (gDVDTrackList.state != TRACK_NOTHING) {
        error = HandleDVDTrackListError();
    }

    switch (gDVDTrackList.state) {
        case TRACK_NOTHING:
            if (gDVDTrackList.nextState.trackID >= 0) {
                gDVDTrackList.stopTrack = 0;
                gDVDTrackList.stopFadeTime = 0;
                gDVDTrackList.curState = gDVDTrackList.nextState;
                gDVDTrackList.nextState.trackID = -1;
                gDVDTrackList.fadeTime = 0;
                gDVDTrackList.volume = 0;
                gDVDTrackList.nextState.flags = 0;
                gDVDTrackList.waitTime = 0;
                DVDFastOpen(gDVDTrackList.fileIDs[gDVDTrackList.curState.trackID], &gDVDTrackList.playingFileInfo);
                gDVDTrackList.state = TRACK_PREPARE_STREAM;
                DVDPrepareStreamAsync(&gDVDTrackList.playingFileInfo, 0, 0, &DVDTrackPrepareStreamCallback);
            }
            break;
        case TRACK_PLAYING_STREAM:
            updateVolume = true;

            if (gDVDTrackList.errorState != ERROR_RETRIEVED || !CheckForStopDVDTrack()) {
                counter++;

                if (gDVDTrackList.errorState == ERROR_RETRIEVED) {
                    if (gDVDTrackList.error.code < 0 || gDVDTrackList.error.bytes[3] == 0 ||
                        gDVDTrackList.error.bytes[0] != 0 || gDVDTrackList.error.bytes[1] != 0) {
                        if (!(gDVDTrackList.curState.flags & 1)) {
                            DVDClose(&gDVDTrackList.playingFileInfo);
                            AISetStreamPlayState(0);
                            gDVDTrackList.state = TRACK_NOTHING;
                            gDVDTrackList.curState.trackID = -1;
                        } else {
                            gDVDTrackList.nextState = gDVDTrackList.curState;
                            gDVDTrackList.nextState.fadeTime = 0;
                            DVDClose(&gDVDTrackList.playingFileInfo);
                            AISetStreamPlayState(0x0);
                            gDVDTrackList.state = TRACK_NOTHING;
                            gDVDTrackList.curState.trackID = -1;
                        }
                    }

                    gDVDTrackList.errorState = NO_ERROR_RETRIEVING;
                } else if (!(counter & 0xF) && gDVDTrackList.state == TRACK_PLAYING_STREAM &&
                           gDVDTrackList.errorState == NO_ERROR_RETRIEVING) {
                    gDVDTrackList.errorState = RETRIEVING_ERROR;
                    DVDGetStreamErrorStatusAsync(&gDVDTrackList.playingFileInfo.cb, &CheckErrorStatus);
                }
            }
            break;
        case TRACK_FADE_IN_STREAM:
            updateVolume = true;
            DVDTrackFadeInUpdate();
            break;
        case TRACK_FADE_OUT_PAUSE:
            updateVolume = true;
            DVDTrackFadeOutPauseUpdate();
            break;
        case TRACK_FADE_OUT_STREAM:
            updateVolume = true;
            DVDTrackFadeOutUpdate();
            break;
        case TRACK_PAUSING_STREAM:
            PauseDVDTrack();
            break;
        case TRACK_PREPARE_STREAM:
            if (error) {
                gDVDTrackList.waitTime = 30;
            }

            if (gDVDTrackList.waitTime < 30) {
                gDVDTrackList.waitTime++;
            }
            break;
        default:
            break;
    }

    if (gDVDTrackList.state != TRACK_PAUSE_STREAM) {
        if (gDVDTrackList.fadeInfo.curTime < gDVDTrackList.fadeInfo.fadeTime) {
            gDVDTrackList.fadeInfo.curVol =
                gDVDTrackList.fadeInfo.startVol +
                (gDVDTrackList.fadeInfo.curTime * (gDVDTrackList.fadeInfo.nextVol - gDVDTrackList.fadeInfo.startVol)) /
                    gDVDTrackList.fadeInfo.fadeTime;
            gDVDTrackList.fadeInfo.curTime++;
        } else {
            gDVDTrackList.fadeInfo.curVol = gDVDTrackList.fadeInfo.nextVol;
        }

        if (updateVolume) {
            SetDVDTrackVolume();
        }
    }

    PAD_STACK();
}

void PauseDVDTrack(void) {
    bool enabled;

    if (gDVDTrackList.state != TRACK_PAUSE_STREAM) {
        enabled = OSDisableInterrupts();

        if (gDVDTrackList.state == TRACK_PREPARE_STREAM || gDVDTrackList.state == TRACK_STOPPING_STREAM) {
            gDVDTrackList.state = TRACK_PAUSING_STREAM;
        }

        OSRestoreInterrupts(enabled);

        if ((gDVDTrackList.state != TRACK_PAUSING_STREAM) && (gDVDTrackList.state > 1) && (gDVDTrackList.state < 9)) {
            gDVDTrackList.lastState = gDVDTrackList.state;
            gDVDTrackList.state = TRACK_PAUSE_STREAM;
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            AISetStreamPlayState(0);
        }
    }

    NO_INLINE();
}

static void StopDVDTrack(s32 fadeTime) {
    bool enabled = OSDisableInterrupts();

    if (gDVDTrackList.state > TRACK_NOTHING && gDVDTrackList.state < TRACK_FADE_OUT_STREAM) {
        gDVDTrackList.stopTrack = 1;

        if (!(gDVDTrackList.curState.flags & 1)) {
            gDVDTrackList.stopFadeTime = 0;
        } else {
            gDVDTrackList.stopFadeTime = 0;
        }
    }

    OSRestoreInterrupts(enabled);

    if (gDVDTrackList.state == TRACK_PAUSING_STREAM || gDVDTrackList.state == TRACK_PAUSE_STREAM) {
        CheckForStopDVDTrack();
    }

    gDVDTrackList.state = TRACK_FADE_OUT_STREAM;
}

static void SetDVDTrackVolume(void) {
    s32 volume;

    volume = (gDVDTrackList.volume * *gDVDVolumeP) >> 7;
    volume = (volume * gDVDTrackList.fadeInOutVolume) >> 7;
    volume = (volume * gDVDTrackList.fadeInfo.curVol) >> 7;

    AISetStreamVolLeft(volume);
    AISetStreamVolRight(volume);
}

static bool IsDVDTrackPaused(void) {
    if (gDVDTrackList.state == TRACK_PAUSING_STREAM || gDVDTrackList.state == TRACK_PAUSE_STREAM) {
        CheckForStopDVDTrack();
    }
}
