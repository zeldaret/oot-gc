#ifndef _DOLPHIN_OSRTC_H_
#define _DOLPHIN_OSRTC_H_

// make the assert happy
#define OS_SOUND_MODE_MONO 0
#define OS_SOUND_MODE_STEREO 1

// make the asserts happy
#define OS_VIDEO_MODE_NTSC 0
#define OS_VIDEO_MODE_MPAL 2

struct SramControl {
    unsigned char sram[64];
    unsigned long offset;
    int enabled;
    int locked;
    int sync;
    void (* callback)();
};

struct OSSram {
    unsigned short checkSum;
    unsigned short checkSumInv;
    unsigned long ead0;
    unsigned long ead1;
    unsigned long counterBias;
    signed char displayOffsetH;
    unsigned char ntd;
    unsigned char language;
    unsigned char flags;
};

struct OSSramEx {
    unsigned char flashID[2][12];
    unsigned long wirelessKeyboardID;
    unsigned short wirelessPadID[4];
    unsigned short _padding0;
    unsigned char flashIDCheckSum[2];
    unsigned char _padding1[4];
};

int __OSGetRTC(unsigned long * rtc);
int __OSSetRTC(unsigned long rtc);
void __OSInitSram();
struct OSSram * __OSLockSram();
struct OSSramEx * __OSLockSramEx(void);
int __OSUnlockSram(int commit);
int __OSUnlockSramEx(int commit);
int __OSSyncSram();
int __OSCheckSram();
int __OSReadROM(void * buffer, long length, long offset);
unsigned long OSGetSoundMode();
void OSSetSoundMode(unsigned long mode);
unsigned long OSGetVideoMode();
void OSSetVideoMode(unsigned long mode);
unsigned char OSGetLanguage();
void OSSetLanguage(unsigned char language);
unsigned char __OSGetBootMode();
void __OSSetBootMode(unsigned char ntd);

#endif // _DOLPHIN_OSRTC_H_
