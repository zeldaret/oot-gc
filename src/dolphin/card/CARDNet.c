#include "dolphin/card.h"

#include "dolphin/private/__card.h"

u16 __CARDVendorID = 0xFFFF;

#if IS_CE
u8 __CARDPermMask = 0x1C;
#endif
