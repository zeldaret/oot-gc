#ifndef _DOLPHIN_AR_H_
#define _DOLPHIN_AR_H_

#include <dolphin/types.h>

#define ARAM_DIR_MRAM_TO_ARAM 0x00
#define ARAM_DIR_ARAM_TO_MRAM 0x01

u32 ARInit(u32 *stack_index_addr, u32 num_entries);
u32 ARGetBaseAddress(void);
u32 ARGetSize(void);
u32 ARGetDMAStatus(void);
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);

#define ARStartDMARead(mmem, aram, len) \
    ARStartDMA(ARAM_DIR_ARAM_TO_MRAM, mmem, aram, len)
#define ARStartDMAWrite(mmem, aram, len) \
    ARStartDMA(ARAM_DIR_MRAM_TO_ARAM, mmem, aram, len)

#endif
