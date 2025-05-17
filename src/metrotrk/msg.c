#include "metrotrk/msg.h"

DSError TRKMessageSend(MessageBuffer* msg) { TRK_WriteUARTN(msg->fData, msg->fLength); }
