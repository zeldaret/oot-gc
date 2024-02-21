#ifndef _DOLPHIN_OS_OSSTOPWATCH_H_
#define _DOLPHIN_OS_OSSTOPWATCH_H_

struct OSStopwatch {
    char* name;
    long long total;
    unsigned long hits;
    long long min;
    long long max;
    long long last;
    int running;
};

void OSInitStopwatch(struct OSStopwatch* sw, char* name);
void OSStartStopwatch(struct OSStopwatch* sw);
void OSStopStopwatch(struct OSStopwatch* sw);
long long OSCheckStopwatch(struct OSStopwatch* sw);
void OSResetStopwatch(struct OSStopwatch* sw);
void OSDumpStopwatch(struct OSStopwatch* sw);

#endif
