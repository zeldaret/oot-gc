#ifndef _DOLPHIN_DEMO_DEMOPAD_H
#define _DOLPHIN_DEMO_DEMOPAD_H

#include "dolphin/pad.h"

#define DEMO_STICK_UP 0x1000
#define DEMO_STICK_DOWN 0x2000
#define DEMO_STICK_LEFT 0x4000
#define DEMO_STICK_RIGHT 0x8000
#define DEMO_STICK_ALL (DEMO_STICK_UP | DEMO_STICK_DOWN | DEMO_STICK_LEFT | DEMO_STICK_RIGHT)

#define DEMO_SUBSTICK_UP 0x0100
#define DEMO_SUBSTICK_DOWN 0x0200
#define DEMO_SUBSTICK_LEFT 0x0400
#define DEMO_SUBSTICK_RIGHT 0x0800
#define DEMO_SUBSTICK_ALL (DEMO_SUBSTICK_UP | DEMO_SUBSTICK_DOWN | DEMO_SUBSTICK_LEFT | DEMO_SUBSTICK_RIGHT)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* 0x00 */ PADStatus pst;
    /* 0x0C */ u16 buttonDown;
    /* 0x0E */ u16 buttonUp;
    /* 0x10 */ u16 dirs;
    /* 0x12 */ u16 dirsNew;
    /* 0x14 */ u16 dirsReleased;
    /* 0x16 */ s16 stickDeltaX;
    /* 0x18 */ s16 stickDeltaY;
    /* 0x1A */ s16 substickDeltaX;
    /* 0x1C */ s16 substickDeltaY;
} DEMODMPad;

extern DEMODMPad DemoPad[4];
extern u32 DemoNumValidPads;

void DEMOPadRead(void);
void DEMOPadInit(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_DEMOPAD_H_
