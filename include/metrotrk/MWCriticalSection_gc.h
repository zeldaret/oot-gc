#ifndef _METROTRK_MW_CRITICAL_SECTION_GC_H
#define _METROTRK_MW_CRITICAL_SECTION_GC_H

#ifdef __cplusplus
extern "C" {
#endif

void MWInitializeCriticalSection(unsigned int* section);
void MWEnterCriticalSection(unsigned int* section);
void MWExitCriticalSection(unsigned int* section);
void MWTerminateCriticalSection(unsigned int* section);

#ifdef __cplusplus
}
#endif

#endif
