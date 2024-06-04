#include "dolphin/card.h"

u16 __CARDVendorID = 0xFFFF;

#if VERSION == CE_J || VERSION == CE_U || VERSION == CE_E
u8 __CARDPermMask = 0x1C;
#endif
