#include "metrotrk/support.h"
#include "dolphin/os.h"
#include "metrotrk/msgcmd.h"

// Custom structure used as temporary buffer for message data transmission
typedef struct msgbuf_s {
    u32 msg_length;
    u8 command[4];
    u8 handle[4];
    u16 length[2];
    u8 data[4];

    // most likely used for padding to 64 bytes
    // (as this is the length of the whole message)
    u8 unknown[0x2C];
} msgbuf_t;

DSError TRK_SuppAccessFile(u32 file_handle, u8* data, size_t* count, DSIOResult* io_result, bool need_reply,
                           bool read) {
    DSError error;
    int replyBufferId;
    MessageBuffer* replyBuffer;
    u32 length;
    int bufferId;
    MessageBuffer* buffer;
    u32 i;
    u8 replyIOResult;
    u32 replyLength;
    bool exit;
    msgbuf_t reply;

    if (data == NULL || *count == 0) {
        return kParameterError;
    }

    exit = false;
    *io_result = kDSIONoError;
    i = 0;
    error = kNoError;
    while (!exit && i < *count && error == kNoError && *io_result == 0) {
        TRK_memset(&reply, 0, sizeof(msgbuf_t));

        if (*count - i <= 0x800) {
            length = *count - i;
        } else {
            length = 0x800;
        }

        reply.command[0] = read ? kDSReadFile : kDSWriteFile;

        if (read) {
            reply.msg_length = 0x40;
        } else {
            reply.msg_length = length + 0x40;
        }

        *(DSFileHandle*)reply.handle = file_handle;
        *(u16*)&reply.length = length;

        TRK_GetFreeBuffer(&bufferId, &buffer);
        error = TRKAppendBuffer_ui8(buffer, (u8*)&reply, 0x40);

        if (!read && error == kNoError) {
            error = TRKAppendBuffer_ui8(buffer, data + i, length);
        }

        if (error == kNoError) {
            if (need_reply) {
                bool b = read && file_handle == 0;

                error = TRK_RequestSend(buffer, &replyBufferId, read ? 5 : 5, 3, !b);
                if (error == kNoError) {
                    replyBuffer = (MessageBuffer*)TRKGetBuffer(replyBufferId);
                }
                replyIOResult = *(u32*)(replyBuffer->fData + 0x10);
                replyLength = *(u16*)(replyBuffer->fData + 0x14);
                if (read && error == kNoError && replyLength <= length) {
                    TRK_SetBufferPosition(replyBuffer, 0x40);
                    error = TRKReadBuffer_ui8(replyBuffer, data + i, replyLength);
                    if (error == kMessageBufferReadError) {
                        error = kNoError;
                    }
                }

                if (replyLength != length) {
                    length = replyLength;
                    exit = true;
                }

                *io_result = (DSIOResult)replyIOResult;
                TRK_ReleaseBuffer(replyBufferId);
            } else {
                error = TRK_MessageSend(buffer);
            }
        }

        TRK_ReleaseBuffer(bufferId);
        i += length;
    }

    *count = i;
    return error;
}

DSError TRK_RequestSend(MessageBuffer* msgBuf, int* bufferId, int p1, int p2, int p3) {
    int error = kNoError;
    MessageBuffer* buffer;
    u32 counter;
    int count;
    u8 msgCmd;
    int msgReplyError;
    bool badReply = true;

    *bufferId = -1;

    for (count = p2 + 1; count != 0 && *bufferId == -1 && error == kNoError; count--) {
        error = TRK_MessageSend(msgBuf);
        if (error == kNoError) {

            if (p3) {
                counter = 0;
            }

            while (true) {
                do {
                    *bufferId = TRKTestForPacket();
                    if (*bufferId != -1) {
                        break;
                    }
                } while (!p3 || ++counter < 79999980);

                if (*bufferId == -1) {
                    break;
                }

                badReply = 0;

                buffer = TRKGetBuffer(*bufferId);
                TRK_SetBufferPosition(buffer, 0);
                OutputData(&buffer->fData[0], buffer->fLength);
                msgCmd = buffer->fData[4];

                if (msgCmd >= kDSReplyACK) {
                    break;
                }

                TRKProcessInput(*bufferId);
                *bufferId = -1;
            }

            if (*bufferId != -1) {
                if (buffer->fLength < 0x40) {
                    badReply = true;
                }
                if (error == kNoError && !badReply) {
                    msgReplyError = buffer->fData[8];
                }
                if (error == kNoError && !badReply) {
                    if ((int)msgCmd != kDSReplyACK || msgReplyError != kNoError) {
                        badReply = true;
                    }
                }
                if (error != kNoError || badReply) {
                    TRK_ReleaseBuffer(*bufferId);
                    *bufferId = -1;
                }
            }
        }
    }

    if (*bufferId == -1) {
        error = kWaitACKError;
    }

    return error;
}

DSError HandleOpenFileSupportRequest(const char* path, u8 replyError, u32* param_3, DSIOResult* ioResult) {
    DSError error;
    int bufferId2;
    int bufferId1;
    MessageBuffer* tempBuffer;
    MessageBuffer* buffer;
    msgbuf_t reply;

    TRK_memset(&reply, 0, sizeof(msgbuf_t));
    *param_3 = 0;
    reply.command[0] = kDSOpenFile;
    reply.msg_length = TRK_strlen(path) + TRK_MSG_REPLY_HEADER_LENGTH;
    reply.handle[0] = replyError;
    reply.length[0] = (u16)(TRK_strlen(path) + 1);
    TRK_GetFreeBuffer(&bufferId1, &buffer);
    error = TRKAppendBuffer_ui8(buffer, (u8*)&reply, 0x40);

    if (error == kNoError) {
        error = TRKAppendBuffer_ui8(buffer, (u8*)path, TRK_strlen(path) + 1);
    }

    if (error == kNoError) {
        *ioResult = kDSIONoError;
        error = TRK_RequestSend(buffer, &bufferId2, 7, 3, 0);

        if (error == kNoError) {
            tempBuffer = TRKGetBuffer(bufferId2);
        }

        *ioResult = *(u32*)(tempBuffer->fData + 0x10);
        *param_3 = *(u32*)(tempBuffer->fData + 0x8);
        TRK_ReleaseBuffer(bufferId2);
    }
    TRK_ReleaseBuffer(bufferId1);
    return error;
}

DSError HandleCloseFileSupportRequest(int replyError, DSIOResult* ioResult) {
    DSError error;
    int replyBufferId;
    int bufferId;
    MessageBuffer* buffer1;
    MessageBuffer* buffer2;
    msgbuf_t reply;

    TRK_memset(&reply, 0, TRK_MSG_HEADER_LENGTH);
    reply.command[0] = kDSCloseFile;
    reply.msg_length = TRK_MSG_HEADER_LENGTH;
    *(DSFileHandle*)reply.handle = replyError;
    error = TRK_GetFreeBuffer(&bufferId, &buffer1);

    if (error == kNoError) {
        error = TRKAppendBuffer_ui8(buffer1, (u8*)&reply, sizeof(msgbuf_t));
    }

    if (error == kNoError) {
        *ioResult = kDSIONoError;
        error = TRK_RequestSend(buffer1, &replyBufferId, 3, 3, 0);

        if (error == kNoError) {
            buffer2 = TRKGetBuffer(replyBufferId);
        }

        if (error == kNoError) {
            *ioResult = *(u32*)(buffer2->fData + 0x10);
        }

        TRK_ReleaseBuffer(replyBufferId);
    }

    TRK_ReleaseBuffer(bufferId);
    return error;
}

DSError HandlePositionFileSupportRequest(u32 param_1, u32* param_2, u8 param_3, DSIOResult* ioResult) {
    DSError error;
    int bufferId2;
    int bufferId1;
    MessageBuffer* buffer1;
    MessageBuffer* buffer2;
    msgbuf_t reply;

    TRK_memset(&reply, 0, TRK_MSG_HEADER_LENGTH);
    reply.command[0] = kDSPositionFile;
    reply.msg_length = TRK_MSG_HEADER_LENGTH;
    *(DSFileHandle*)reply.handle = param_1;
    *(int*)reply.length = *param_2;
    reply.data[0] = param_3;
    error = TRK_GetFreeBuffer(&bufferId1, &buffer1);

    if (error == kNoError) {
        error = TRKAppendBuffer_ui8(buffer1, (u8*)&reply, sizeof(msgbuf_t));
    }

    if (error == kNoError) {
        *ioResult = kDSIONoError;
        *param_2 = -1;
        error = TRK_RequestSend(buffer1, &bufferId2, 3, 3, 0);

        if (error == kNoError) {
            buffer2 = TRKGetBuffer(bufferId2);

            if (buffer2 != NULL) {
                *ioResult = *(u32*)(buffer2->fData + 0x10);
                *param_2 = *(u32*)(buffer2->fData + 0x18);
            }
        }

        TRK_ReleaseBuffer(bufferId2);
    }

    TRK_ReleaseBuffer(bufferId1);
    return error;
}
