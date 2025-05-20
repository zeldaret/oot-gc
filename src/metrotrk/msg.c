#include "metrotrk/msg.h"
#include "metrotrk/dolphin_trk_glue.h"

DSError TRKMessageSend(MessageBuffer* msg) { return TRK_WriteUARTN(msg->fData, msg->fLength); }
