#include "metrotrk/msg.h"

DSError TRK_MessageSend(MessageBuffer* msg) { TRK_WriteUARTN(msg->fData, msg->fLength); }
