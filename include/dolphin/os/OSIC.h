#ifndef _DOLPHIN_OS_OSIC_H
#define _DOLPHIN_OS_OSIC_H

#ifdef __cplusplus
extern "C" {
#endif

void ICFlashInvalidate(void);
void ICEnable(void);
void ICDisable(void);
void ICFreeze(void);
void ICUnfreeze(void);
void ICBlockInvalidate(void* addr);
void ICSync(void);

#ifdef __cplusplus
}
#endif

#endif
