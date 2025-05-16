#include "metrotrk/support.h"
#include "dolphin/os.h"
#include "metrotrk/msgcmd.h"

DSError TRK_SuppAccessFile(u32 file_handle, u8* data, size_t* count, u8* io_result, bool need_reply, bool read) {
    DSError error;
    int replyBufferId;
    MessageBuffer* replyBuffer;
    int bufferId;
    MessageBuffer* buffer;
    u32 length;
    u32 done;
    u8 replyIOResult;
    u16 replyLength;
    bool exit;
    DSError var_r5;
    int var_r6;

    if (data == NULL || *count == 0) {
        return kParameterError;
    }

    exit = false;
    *io_result = kDSIONoError;
    done = 0;
    error = kNoError;
    while (!exit && done < *count && error == kNoError && *io_result == 0) {
        if (*count - done > 0x800) {
            length = 0x800;
        } else {
            length = *count - done;
        }

        error = TRK_GetFreeBuffer(&bufferId, &buffer);

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui8(buffer, read != 0 ? 0xD1 : 0xD0);
        }

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui32(buffer, file_handle);
        }

        if (error == kNoError) {
            error = TRKAppendBuffer1_ui16(buffer, length);
        }

        if (!read && error == kNoError) {
            error = TRKAppendBuffer_ui8(buffer, data + done, length);
        }

        if (error == kNoError) {
            if (need_reply) {
                replyLength = 0;
                replyIOResult = 0;

                error = TRK_RequestSend(buffer, &replyBufferId, read ? 5 : 5, 3, !(read && file_handle == 0));
                if (error == kNoError) {
                    replyBuffer = (MessageBuffer*)TRKGetBuffer(replyBufferId);
                    TRK_SetBufferPosition(replyBuffer, 2);
                }

                if (error == kNoError) {
                    error = TRKReadBuffer1_ui8(replyBuffer, &replyIOResult);
                }

                if (error == kNoError) {
                    error = TRKReadBuffer1_ui16(replyBuffer, &replyLength);
                }

                if (read && error == kNoError) {
                    if (replyBuffer->fLength != replyLength + 5) {
                        replyLength = replyBuffer->fLength - 5;
                        if (replyIOResult == 0) {
                            replyIOResult = 1;
                        }
                    }

                    if (replyLength <= length) {
                        error = TRKReadBuffer_ui8(replyBuffer, data + done, replyLength);
                    }
                }

                if (replyLength != length) {
                    if ((!read || replyLength >= length) && replyIOResult == 0) {
                        replyIOResult = 1;
                    }
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
        done += length;
    }

    *count = done;
    return error;
}

DSError TRK_RequestSend(MessageBuffer* msgBuf, int* bufferId, u32 p1, u32 p2, int p3) {
    int error = kNoError;
    MessageBuffer* buffer;
    u32 timer;
    int tries;
    u8 msg_command;
    u8 msg_error;
    bool badReply = true;

    *bufferId = -1;

    for (tries = p2 + 1; tries != 0 && *bufferId == -1 && error == kNoError; tries--) {
        error = TRK_MessageSend(msgBuf);
        if (error == kNoError) {
            if (p3) {
                timer = 0;
            }

            while (true) {
                do {
                    *bufferId = TRKTestForPacket();
                    if (*bufferId != -1) {
                        break;
                    }
                } while (!p3 || ++timer < 79999980);

                if (*bufferId == -1) {
                    break;
                }

                badReply = false;

                buffer = TRKGetBuffer(*bufferId);
                TRK_SetBufferPosition(buffer, 0);

                if ((error = TRKReadBuffer1_ui8(buffer, &msg_command)) != kNoError) {
                    break;
                }

                if (msg_command >= kDSReplyACK) {
                    break;
                }

                TRKProcessInput(*bufferId);
                *bufferId = -1;
            }

            if (*bufferId != -1) {
                if (buffer->fLength < p1) {
                    badReply = true;
                }
                if (error == kNoError && !badReply) {
                    error = TRKReadBuffer1_ui8(buffer, &msg_error);
                }
                if (error == kNoError && !badReply) {
                    if (msg_command != kDSReplyACK || msg_error != kDSReplyNoError) {
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
