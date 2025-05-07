#include "metrotrk/msghndlr.h"
#include "metrotrk/dolphin_trk_glue.h"
#include "metrotrk/mem_TRK.h"
#include "metrotrk/msg.h"
#include "metrotrk/msgbuf.h"
// #include "metrotrk/msgxtrct.h"
#include "dolphin/os.h"
#include "macros.h"
#include "metrotrk/nubevent.h"
#include "metrotrk/target_options.h"

extern void __TRK_copy_vectors();
extern void __TRKreset();

static bool IsTRKConnected;
static u32 g_CurrentSequence;

bool GetTRKConnected() { return IsTRKConnected; }

void SetTRKConnected(bool value) { IsTRKConnected = value; }

static DSError TRKSendACK(MessageBuffer* b) { return TRK_MessageSend(b); }

static DSError TRKStandardACK(MessageBuffer* b, MessageCommandID commandId, DSReplyError replyError) {
    msgbuf_t reply;
    u32 nextSequence;

    TRK_memset((void*)&reply, 0, sizeof(msgbuf_t));
    reply.unk0C = g_CurrentSequence;
    nextSequence = ++g_CurrentSequence;
    reply.commandId = commandId;
    reply.msgLength = sizeof(msgbuf_t);
    reply.replyError = replyError;
    g_CurrentSequence = nextSequence + 1;
    reply.unk0C = nextSequence;
    TRK_WriteUARTN((void*)&reply, sizeof(msgbuf_t));

    NO_INLINE();
    return kNoError;
}

DSError TRKDoConnect(MessageBuffer* b) { return TRKStandardACK(b, kDSReplyACK, kDSReplyNoError); }

DSError TRKDoDisconnect(MessageBuffer* b) {
    NubEvent event;

    IsTRKConnected = false;
    TRKStandardACK(b, 0x80, kDSReplyNoError);
    TRKConstructEvent(&event, 1);
    TRKPostEvent(&event);
    return kNoError;
}

DSError TRKDoReset(MessageBuffer* b) {
    TRKStandardACK(b, 0x80, kDSReplyNoError);
    __TRKreset();
    return kNoError;
}

DSError TRKDoOverride(MessageBuffer* b) {
    TRKStandardACK(b, 0x80, kDSReplyNoError);
    __TRK_copy_vectors();
    return kNoError;
}

DSError TRKDoVersions(MessageBuffer* b) { return kNoError; }

DSError TRKDoSupportMask(MessageBuffer* b) { return kNoError; }

/*
Message parameters:
0x4: command (u8)
0x8: options (u8)
0xc: length (u16)
0x10: start (u16)
0x14: register data (void*)
*/
DSError TRKDoReadMemory(MessageBuffer* b) {
    DSError result;
    DSReplyError replyError;
    u8 options;
    u32 test;
    u32 start;
    unsigned int length;
    msgbuf_t reply3;

    options = b->fData[8];
    start = *(u32*)(b->fData + 16);
    length = *(u16*)(b->fData + 12);

    if (options & DS_MSG_MEMORY_EXTENDED) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedOptionError);
    }

    {
        u8 buf[0x820] ATTRIBUTE_ALIGN(32);
        unsigned int tempLength = length;

        result = TRKTargetAccessMemory(buf, start, &tempLength, options & DS_MSG_MEMORY_USERVIEW ? 0 : 1, true);
        TRKResetBuffer(b, 0);

        if (result == kNoError) {
            u32 nextSequence;

            TRK_memset(&reply3, 0, sizeof(msgbuf_t));
            reply3.msgLength = tempLength + sizeof(msgbuf_t);
            reply3.replyError = result;
            reply3.commandId = kDSReplyACK;
            reply3.unk0C = g_CurrentSequence++;
            TRK_AppendBuffer(b, (u8*)&reply3, sizeof(msgbuf_t));

            if (options & DS_MSG_MEMORY_SPACE_DATA) {
                result = TRK_AppendBuffer(b, buf + (start & 0x1F), tempLength);
            } else {
                result = TRK_AppendBuffer(b, buf, tempLength);
            }
        }
    }

    if (result != kNoError) {
        switch (result) {
            case kCWDSException:
                replyError = kDSReplyCWDSException;
                break;
            case kInvalidMemory:
                replyError = kDSReplyInvalidMemoryRange;
                break;
            case kInvalidProcessId:
                replyError = kDSReplyInvalidProcessId;
                break;
            case kInvalidThreadId:
                replyError = kDSReplyInvalidThreadId;
                break;
            case kOsError:
                replyError = kDSReplyOsError;
                break;
            default:
                replyError = kDSReplyCWDSError;
                break;
        }

        return TRKStandardACK(b, kDSReplyACK, replyError);
    }

    return TRKSendACK(b);
}

/*
Message parameters:
0x4: command (u8)
0x8: options (u8)
0xc: first register (u16)
0x10: last register (u16)
0x14: register data (void*)
*/
DSError TRKDoWriteMemory(MessageBuffer* b) {
    DSError result;
    DSReplyError replyError;
    u8 options;
    u32 start;
    u32 length;
    msgbuf_t reply3;

    options = b->fData[8];
    start = *(u32*)(b->fData + 16);
    length = *(u16*)(b->fData + 12);

    if (options & DS_MSG_MEMORY_EXTENDED) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedOptionError);
    }

    {
        u8 buf[0x820] ATTRIBUTE_ALIGN(32);

        size_t tempLength = length;

        TRK_SetBufferPosition(b, 0x40);
        result = TRK_ReadBuffer(b, buf, tempLength);
        result = TRKTargetAccessMemory(buf, start, &tempLength, options & DS_MSG_MEMORY_USERVIEW ? 0 : 1, false);
        TRKResetBuffer(b, 0);

        if (result == kNoError) {
            TRK_memset(&reply3, 0, sizeof(msgbuf_t));
            reply3.msgLength = sizeof(msgbuf_t);
            reply3.commandId = kDSReplyACK;
            reply3.replyError = result;
            reply3.unk0C = g_CurrentSequence++;
            result = TRK_AppendBuffer(b, (u8*)&reply3, sizeof(msgbuf_t));
        }
    }

    if (result != kNoError) {
        switch (result) {
            case kCWDSException:
                replyError = kDSReplyCWDSException;
                break;
            case kInvalidMemory:
                replyError = kDSReplyInvalidMemoryRange;
                break;
            case kInvalidProcessId:
                replyError = kDSReplyInvalidProcessId;
                break;
            case kInvalidThreadId:
                replyError = kDSReplyInvalidThreadId;
                break;
            case kOsError:
                replyError = kDSReplyOsError;
                break;
            default:
                replyError = kDSReplyCWDSError;
                break;
        }

        return TRKStandardACK(b, kDSReplyACK, replyError);
    }

    return TRKSendACK(b);
}

/*
Message parameters:
0x4: command (u8)
0x8: options (u8)
0xC: first register (u16)
0x10: last register (u16)
0x14: register data (u32[])
*/
DSError TRKDoReadRegisters(MessageBuffer* b) {
    DSError error;
    DSReplyError replyError;
    u8 options;
    u16 firstRegister;
    u16 lastRegister;
    size_t registersLength;
    msgbuf_t local_50;

    options = b->fData[8];
    firstRegister = *(u16*)(b->fData + 12);
    lastRegister = *(u16*)(b->fData + 16);

    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyInvalidRegisterRange);
    }

    local_50.commandId = kDSReplyACK;
    local_50.msgLength = 0x468;
    local_50.unk0C = g_CurrentSequence++;

    TRKResetBuffer(b, 0);
    TRKAppendBuffer_ui8(b, (u8*)&local_50, sizeof(msgbuf_t));

    //???
    error = TRKTargetAccessDefault(0, 36, b, &registersLength, true);

    if (error == kNoError) {
        error = TRKTargetAccessFP(0, 33, b, &registersLength, true);
    }
    if (error == kNoError) {
        error = TRKTargetAccessExtended1(0, 0x60, b, &registersLength, true);
    }
    if (error == kNoError) {
        error = TRKTargetAccessExtended2(0, 31, b, &registersLength, true);
    }

    // Check if there was an error, and respond accordingly
    if (error != kNoError) {
        switch (error) {
            case kUnsupportedError:
                replyError = kDSReplyUnsupportedOptionError;
                break;
            case kInvalidRegister:
                replyError = kDSReplyInvalidRegisterRange;
                break;
            case kCWDSException:
                replyError = kDSReplyCWDSException;
                break;
            case kInvalidProcessId:
                replyError = kDSReplyInvalidProcessId;
                break;
            case kInvalidThreadId:
                replyError = kDSReplyInvalidThreadId;
                break;
            case kOsError:
                replyError = kDSReplyOsError;
                break;
            default:
                replyError = kDSReplyCWDSError;
        }

        return TRKStandardACK(b, kDSReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}

/*
Message parameters:
0x4: command (u8)
0x8: options (u8)
0xC: first register (u16)
0x10: last register (u16)
0x14: register data (u32[])
*/
DSError TRKDoWriteRegisters(MessageBuffer* b) {
    DSError error;
    DSReplyError replyError;
    u8 options;
    u16 firstRegister;
    u16 lastRegister;
    size_t registersLength;
    msgbuf_t local_50;

    options = b->fData[8];
    firstRegister = *(u16*)(b->fData + 12);
    lastRegister = *(u16*)(b->fData + 16);

    TRK_SetBufferPosition(b, 0);

    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyInvalidRegisterRange);
    }

    TRK_SetBufferPosition(b, 0x40);

    switch (options) {
        case kDSRegistersDefault:
            error = TRKTargetAccessDefault(firstRegister, lastRegister, b, &registersLength, false);
            break;
        case kDSRegistersFP:
            error = TRKTargetAccessFP(firstRegister, lastRegister, b, &registersLength, false);
            break;
        case kDSRegistersExtended1:
            error = TRKTargetAccessExtended1(firstRegister, lastRegister, b, &registersLength, false);
            break;
        case kDSRegistersExtended2:
            error = TRKTargetAccessExtended2(firstRegister, lastRegister, b, &registersLength, false);
            break;
        default:
            // invalid option
            error = kUnsupportedError;
            break;
    }

    TRKResetBuffer(b, 0);

    if (error == kDSReplyNoError) {
        TRK_memset(&local_50, 0, sizeof(msgbuf_t));
        local_50.msgLength = sizeof(msgbuf_t);
        local_50.commandId = kDSReplyACK;
        local_50.replyError = error;
        local_50.unk0C = g_CurrentSequence++;
        error = TRK_AppendBuffer(b, (u8*)&local_50, sizeof(msgbuf_t));
    }

    // Check if there was an error, and respond accordingly
    if (error != kNoError) {
        switch (error) {
            case kUnsupportedError:
                replyError = kDSReplyUnsupportedOptionError;
                break;
            case kInvalidRegister:
                replyError = kDSReplyInvalidRegisterRange;
                break;
            case kMessageBufferReadError:
                replyError = kDSReplyPacketSizeError;
                break;
            case kCWDSException:
                replyError = kDSReplyCWDSException;
                break;
            case kInvalidProcessId:
                replyError = kDSReplyInvalidProcessId;
                break;
            case kInvalidThreadId:
                replyError = kDSReplyInvalidThreadId;
                break;
            case kOsError:
                replyError = kDSReplyOsError;
                break;
            default:
                replyError = kDSReplyCWDSError;
        }

        return TRKStandardACK(b, kDSReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}

DSError TRKDoContinue(MessageBuffer* b) {
    DSError result;

    if (!TRKTargetStopped()) {
        result = TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    } else {
        TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
        result = TRKTargetContinue();
    }

    return result;
}

/*
Message parameters:
0x4: command (u8)
0x8: options (u8, DSMessageStepOptions enum value)
If kDSStepIntoCount/kDSStepOverCount:
0xC: count (u8, instructions to step over)
If kDSStepIntoRange/kDSStepOverRange:
0x10: range start (u32)
0x14: range end (u32)
*/
DSError TRKDoStep(MessageBuffer* b) {
    DSError result;
    u8 options;
    u8 count;
    u32 rangeStart;
    u32 rangeEnd;
    u32 pc;

    TRK_SetBufferPosition(b, 0);

    options = b->fData[8];
    rangeStart = *(u32*)(b->fData + 16);
    rangeEnd = *(u32*)(b->fData + 20);

    switch (options) {
        // Count step
        case kDSStepIntoCount:
        case kDSStepOverCount:
            // Continue if the step count is at least 1
            count = b->fData[12];
            if (count >= 1) {
                break;
            }
            return TRKStandardACK(b, kDSReplyACK, kDSReplyParameterError);
        // Range step
        case kDSStepIntoRange:
        case kDSStepOverRange:
            pc = TRKTargetGetPC();
            // Continue if the current pc is within the step range
            if (pc >= rangeStart && pc <= rangeEnd) {
                break;
            }
            return TRKStandardACK(b, kDSReplyACK, kDSReplyParameterError);
        default:
            // Invalid option value
            return TRKStandardACK(b, kDSReplyACK, kDSReplyUnsupportedOptionError);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, kDSReplyACK, kDSReplyNotStopped);
    } else {
        result = TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);

        switch (options) {
            // Count step
            case kDSStepIntoCount:
            case kDSStepOverCount:
                result = TRKTargetSingleStep(count, options == kDSStepOverCount);
                break;
            // Range step
            case kDSStepIntoRange:
            case kDSStepOverRange:
                result = TRKTargetStepOutOfRange(rangeStart, rangeEnd, options == kDSStepOverRange);
                break;
        }
    }

    return result;
}

DSError TRKDoStop(MessageBuffer* b) {
    msgbuf_t reply;
    u8 replyError;

    switch (TRKTargetStop()) {
        case kNoError:
            replyError = 0;
            break;
        case kInvalidProcessId:
            replyError = kDSReplyInvalidProcessId;
            break;
        case kInvalidThreadId:
            replyError = kDSReplyInvalidThreadId;
            break;
        case kOsError:
            replyError = kDSReplyOsError;
            break;
        default:
            replyError = kDSReplyError;
            break;
    }

    return TRKStandardACK(b, kDSReplyACK, replyError);
}

/*
Doesn't exist in standard MetroTRK, might be GC/Wii exclusive
Message parameters:
0x4: command? (u8?)
0x8:
0xC: options? (u8?)
*/
DSError TRKDoSetOption(MessageBuffer* b) {
    u8 options = DSFetch_u8(&b->fData[12]);

    if (b->fData[8] == 1) {
        usr_puts_serial("\nMetroTRK Option : SerialIO - ");

        if (options != 0) {
            usr_puts_serial("Enable\n");
        } else {
            usr_puts_serial("Disable\n");
        }

        SetUseSerialIO(options);
    }

    return TRKStandardACK(b, kDSReplyACK, kDSReplyNoError);
}
