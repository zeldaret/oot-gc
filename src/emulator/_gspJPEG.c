#include "emulator/rsp.h"

static bool rspCreateJPEGArrays(Rsp* pRSP) {
    pRSP->Coeff = (s32*)pRSP->pDMEM;
    pRSP->Coeff[0] = 0x1000;
    pRSP->Coeff[1] = 0x1000;
    pRSP->Coeff[2] = 0x1000;
    pRSP->Coeff[3] = 0x1000;
    pRSP->Coeff[4] = 0x1000;
    pRSP->Coeff[5] = 0x1000;
    pRSP->Coeff[6] = 0x1000;
    pRSP->Coeff[7] = 0x1000;
    pRSP->Coeff[8] = 0x1631;
    pRSP->Coeff[9] = 0x12D0;
    pRSP->Coeff[10] = 0xC92;
    pRSP->Coeff[11] = 0x46A;
    pRSP->Coeff[12] = -0x46A;
    pRSP->Coeff[13] = -0xC92;
    pRSP->Coeff[14] = -0x12D0;
    pRSP->Coeff[15] = -0x1631;
    pRSP->Coeff[16] = 0x14E8;
    pRSP->Coeff[17] = 0x8A9;
    pRSP->Coeff[18] = -0x8A9;
    pRSP->Coeff[19] = -0x14E8;
    pRSP->Coeff[20] = -0x14E8;
    pRSP->Coeff[21] = -0x8A9;
    pRSP->Coeff[22] = 0x8A9;
    pRSP->Coeff[23] = 0x14E8;
    pRSP->Coeff[24] = 0x12D0;
    pRSP->Coeff[25] = -0x46A;
    pRSP->Coeff[26] = -0x1631;
    pRSP->Coeff[27] = -0xC92;
    pRSP->Coeff[28] = 0xC92;
    pRSP->Coeff[29] = 0x1631;
    pRSP->Coeff[30] = 0x46A;
    pRSP->Coeff[31] = -0x12D0;
    pRSP->Coeff[32] = 0x1000;
    pRSP->Coeff[33] = -0x1000;
    pRSP->Coeff[34] = -0x1000;
    pRSP->Coeff[35] = 0x1000;
    pRSP->Coeff[36] = 0x1000;
    pRSP->Coeff[37] = -0x1000;
    pRSP->Coeff[38] = -0x1000;
    pRSP->Coeff[39] = 0x1000;
    pRSP->Coeff[40] = 0xC92;
    pRSP->Coeff[41] = -0x1631;
    pRSP->Coeff[42] = 0x46A;
    pRSP->Coeff[43] = 0x12D0;
    pRSP->Coeff[44] = -0x12D0;
    pRSP->Coeff[45] = -0x46A;
    pRSP->Coeff[46] = 0x1631;
    pRSP->Coeff[47] = -0xC92;
    pRSP->Coeff[48] = 0x8A9;
    pRSP->Coeff[49] = -0x14E8;
    pRSP->Coeff[50] = 0x14E8;
    pRSP->Coeff[51] = -0x8A9;
    pRSP->Coeff[52] = -0x8A9;
    pRSP->Coeff[53] = 0x14E8;
    pRSP->Coeff[54] = -0x14E8;
    pRSP->Coeff[55] = 0x8A9;
    pRSP->Coeff[56] = 0x46A;
    pRSP->Coeff[57] = -0xC92;
    pRSP->Coeff[58] = 0x12D0;
    pRSP->Coeff[59] = -0x1631;
    pRSP->Coeff[60] = 0x1631;
    pRSP->Coeff[61] = -0x12D0;
    pRSP->Coeff[62] = 0xC92;
    pRSP->Coeff[63] = -0x46A;

    pRSP->QTable = (s16*)((u8*)pRSP->Coeff + 0x100);
    pRSP->QTable[0] = 0x10;
    pRSP->QTable[1] = 0x0B;
    pRSP->QTable[2] = 0x0A;
    pRSP->QTable[3] = 0x10;
    pRSP->QTable[4] = 0x18;
    pRSP->QTable[5] = 0x28;
    pRSP->QTable[6] = 0x33;
    pRSP->QTable[7] = 0x3D;
    pRSP->QTable[8] = 0x0C;
    pRSP->QTable[9] = 0x0C;
    pRSP->QTable[10] = 0x0E;
    pRSP->QTable[11] = 0x13;
    pRSP->QTable[12] = 0x1A;
    pRSP->QTable[13] = 0x3A;
    pRSP->QTable[14] = 0x3C;
    pRSP->QTable[15] = 0x37;
    pRSP->QTable[16] = 0x0E;
    pRSP->QTable[17] = 0x0D;
    pRSP->QTable[18] = 0x10;
    pRSP->QTable[19] = 0x18;
    pRSP->QTable[20] = 0x28;
    pRSP->QTable[21] = 0x39;
    pRSP->QTable[22] = 0x45;
    pRSP->QTable[23] = 0x38;
    pRSP->QTable[24] = 0x0E;
    pRSP->QTable[25] = 0x11;
    pRSP->QTable[26] = 0x16;
    pRSP->QTable[27] = 0x1D;
    pRSP->QTable[28] = 0x33;
    pRSP->QTable[29] = 0x57;
    pRSP->QTable[30] = 0x50;
    pRSP->QTable[31] = 0x3E;
    pRSP->QTable[32] = 0x12;
    pRSP->QTable[33] = 0x16;
    pRSP->QTable[34] = 0x25;
    pRSP->QTable[35] = 0x38;
    pRSP->QTable[36] = 0x44;
    pRSP->QTable[37] = 0x6D;
    pRSP->QTable[38] = 0x67;
    pRSP->QTable[39] = 0x4D;
    pRSP->QTable[40] = 0x18;
    pRSP->QTable[41] = 0x23;
    pRSP->QTable[42] = 0x37;
    pRSP->QTable[43] = 0x40;
    pRSP->QTable[44] = 0x51;
    pRSP->QTable[45] = 0x68;
    pRSP->QTable[46] = 0x71;
    pRSP->QTable[47] = 0x5C;
    pRSP->QTable[48] = 0x31;
    pRSP->QTable[49] = 0x40;
    pRSP->QTable[50] = 0x4E;
    pRSP->QTable[51] = 0x57;
    pRSP->QTable[52] = 0x67;
    pRSP->QTable[53] = 0x79;
    pRSP->QTable[54] = 0x78;
    pRSP->QTable[55] = 0x65;
    pRSP->QTable[56] = 0x48;
    pRSP->QTable[57] = 0x5C;
    pRSP->QTable[58] = 0x5F;
    pRSP->QTable[59] = 0x62;
    pRSP->QTable[60] = 0x70;
    pRSP->QTable[61] = 0x64;
    pRSP->QTable[62] = 0x67;
    pRSP->QTable[63] = 0x63;

    pRSP->Zigzag = (int*)((u8*)pRSP->QTable + 0x80);
    pRSP->Zigzag[0] = 0x00;
    pRSP->Zigzag[1] = 0x01;
    pRSP->Zigzag[2] = 0x08;
    pRSP->Zigzag[3] = 0x10;
    pRSP->Zigzag[4] = 0x09;
    pRSP->Zigzag[5] = 0x02;
    pRSP->Zigzag[6] = 0x03;
    pRSP->Zigzag[7] = 0x0A;
    pRSP->Zigzag[8] = 0x11;
    pRSP->Zigzag[9] = 0x18;
    pRSP->Zigzag[10] = 0x20;
    pRSP->Zigzag[11] = 0x19;
    pRSP->Zigzag[12] = 0x12;
    pRSP->Zigzag[13] = 0x0B;
    pRSP->Zigzag[14] = 0x04;
    pRSP->Zigzag[15] = 0x05;
    pRSP->Zigzag[16] = 0x0C;
    pRSP->Zigzag[17] = 0x13;
    pRSP->Zigzag[18] = 0x1A;
    pRSP->Zigzag[19] = 0x21;
    pRSP->Zigzag[20] = 0x28;
    pRSP->Zigzag[21] = 0x30;
    pRSP->Zigzag[22] = 0x29;
    pRSP->Zigzag[23] = 0x22;
    pRSP->Zigzag[24] = 0x1B;
    pRSP->Zigzag[25] = 0x14;
    pRSP->Zigzag[26] = 0x0D;
    pRSP->Zigzag[27] = 0x06;
    pRSP->Zigzag[28] = 0x07;
    pRSP->Zigzag[29] = 0x0E;
    pRSP->Zigzag[30] = 0x15;
    pRSP->Zigzag[31] = 0x1C;
    pRSP->Zigzag[32] = 0x23;
    pRSP->Zigzag[33] = 0x2A;
    pRSP->Zigzag[34] = 0x31;
    pRSP->Zigzag[35] = 0x38;
    pRSP->Zigzag[36] = 0x39;
    pRSP->Zigzag[37] = 0x32;
    pRSP->Zigzag[38] = 0x2B;
    pRSP->Zigzag[39] = 0x24;
    pRSP->Zigzag[40] = 0x1D;
    pRSP->Zigzag[41] = 0x16;
    pRSP->Zigzag[42] = 0x0F;
    pRSP->Zigzag[43] = 0x17;
    pRSP->Zigzag[44] = 0x1E;
    pRSP->Zigzag[45] = 0x25;
    pRSP->Zigzag[46] = 0x2C;
    pRSP->Zigzag[47] = 0x33;
    pRSP->Zigzag[48] = 0x3A;
    pRSP->Zigzag[49] = 0x3B;
    pRSP->Zigzag[50] = 0x34;
    pRSP->Zigzag[51] = 0x2D;
    pRSP->Zigzag[52] = 0x26;
    pRSP->Zigzag[53] = 0x1F;
    pRSP->Zigzag[54] = 0x27;
    pRSP->Zigzag[55] = 0x2E;
    pRSP->Zigzag[56] = 0x35;
    pRSP->Zigzag[57] = 0x3C;
    pRSP->Zigzag[58] = 0x3D;
    pRSP->Zigzag[59] = 0x36;
    pRSP->Zigzag[60] = 0x2F;
    pRSP->Zigzag[61] = 0x37;
    pRSP->Zigzag[62] = 0x3E;
    pRSP->Zigzag[63] = 0x3F;

    pRSP->rgbaBuf = (__anon_0x58360*)(u8*)pRSP->pIMEM;
    pRSP->yuvBuf = (__anon_0x583EE*)((u8*)pRSP->rgbaBuf + 0x800);
    pRSP->dctBuf = (int*)((u8*)pRSP->yuvBuf + 0x600);

    return true;
}

static inline void rspConvertBufferToRGBA(u8* buf, struct __anon_0x58360* rgba) {
    rgba->a = 1;
    rgba->r = (buf[0] >> 3) & 0x1F;
    rgba->g = ((buf[0] << 2) | (buf[1] >> 6)) & 0x1F;
    rgba->b = (buf[1] >> 1) & 0x1F;
}

static void rspConvertRGBAtoYUV(Rsp* pRSP) {
    int i;
    int j;
    int Y;
    int U;
    int V;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            Y = 0x21CBF * pRSP->rgbaBuf[i * 16 + j].r + 0x42599 * pRSP->rgbaBuf[i * 16 + j].g +
                0xCE2C * pRSP->rgbaBuf[i * 16 + j].b;
            Y >>= 16;

            U = -0x137E0 * pRSP->rgbaBuf[i * 16 + j].r - 0x26478 * pRSP->rgbaBuf[i * 16 + j].g +
                0x39C59 * pRSP->rgbaBuf[i * 16 + j].b;
            U >>= 16;

            V = 0x39C88 * pRSP->rgbaBuf[i * 16 + j].r - 0x30624 * pRSP->rgbaBuf[i * 16 + j].g -
                0x9663 * pRSP->rgbaBuf[i * 16 + j].b;
            V >>= 16;

            pRSP->yuvBuf[i * 16 + j].y = Y + 0x10;
            pRSP->yuvBuf[i * 16 + j].u = U + 0x80;
            pRSP->yuvBuf[i * 16 + j].v = V + 0x80;
        }
    }
}

static void rspYUVtoDCTBuf(Rsp* pRSP) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[i * 8 + j] = pRSP->yuvBuf[i * 16 + j].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x40 + i * 8 + j] = pRSP->yuvBuf[i * 16 + (j + 8)].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x80 + i * 8 + j] = pRSP->yuvBuf[(i + 8) * 16 + j].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0xC0 + i * 8 + j] = pRSP->yuvBuf[(i + 8) * 16 + (j + 8)].y;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x100 + i * 8 + j] = pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].u;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->dctBuf[0x140 + i * 8 + j] = pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].v;
        }
    }
}

static void rspDCT(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[j * 8 + k] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[j * 8 + k];
                }
                pRSP->dctBuf[c * 0x40 + j * 8 + i] = (dd + 0x4000) >> 15;
            }
        }
    }
}

static void rspQuantize(Rsp* pRSP, s32 scale) {
    s32 c;
    s32 i;
    s32 j;
    s16 q;
    s16 s;

    switch (scale) {
        case -2:
            s = 1;
            break;
        case -1:
            s = 2;
            break;
        case 0:
            return;
        default:
            s = scale * 4;
            break;
    }

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                q = (((4 * pRSP->QTable[i * 8 + j] * s) >> 2) + 2) >> 2;
                if (pRSP->dctBuf[c * 0x40 + i * 8 + j] >= 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = (pRSP->dctBuf[c * 0x40 + i * 8 + j] + (q >> 1)) / q;
                } else {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = (pRSP->dctBuf[c * 0x40 + i * 8 + j] - (q >> 1)) / q;
                }
            }
        }
    }
}

static inline void rspZigzagData(Rsp* pRSP, u8** databuf, int n, int* preDc) {
    s16 Dc;
    s16 Ac;
    int i;
    int z;

    Dc = pRSP->dctBuf[n * 64] - preDc[0];
    preDc[0] += Dc;
    *(*databuf)++ = (Dc >> 8) & 0xFF;
    *(*databuf)++ = Dc & 0xFF;

    for (z = 1; z < 64; z++) {
        i = pRSP->Zigzag[z];
        Ac = pRSP->dctBuf[n * 64 + (i & 7) * 8 + (i >> 3)];
        *(*databuf)++ = (Ac >> 8) & 0xFF;
        *(*databuf)++ = Ac & 0xFF;
    }
}

static inline void rspUndoZigzagData(Rsp* pRSP, u8** databuf, int n, int* preDc) {
    s16 Dc;
    s16 Ac;
    int i;
    int z;

    Dc = (*(*databuf)++ << 8) | *(*databuf)++;
    pRSP->dctBuf[n * 64] = Dc + preDc[0];
    preDc[0] += Dc;

    for (z = 1; z < 64; z++) {
        i = pRSP->Zigzag[z];
        Ac = ((*(*databuf)++ & 0xFF) << 8) | *(*databuf)++;
        pRSP->dctBuf[n * 64 + (i & 7) * 8 + (i >> 3)] = Ac;
    }
}

void rspUndoQuantize(Rsp* pRSP, s32 scale) {
    s32 c;
    s32 i;
    s32 j;
    s16 q;
    s16 s;

    switch (scale) {
        case -2:
            s = 1;
            break;
        case -1:
            s = 2;
            break;
        case 0:
            return;
        default:
            s = scale * 4;
            break;
    }

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                q = (((4 * pRSP->QTable[i * 8 + j] * s) >> 2) + 2) >> 2;
                if (pRSP->dctBuf[c * 0x40 + i * 8 + j] > 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = pRSP->dctBuf[c * 0x40 + i * 8 + j] * q - (q >> 1);
                } else if (pRSP->dctBuf[c * 0x40 + i * 8 + j] < 0) {
                    pRSP->dctBuf[c * 0x40 + i * 8 + j] = pRSP->dctBuf[c * 0x40 + i * 8 + j] * q + (q >> 1);
                }
            }
        }
    }
}

void rspUndoDCT(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[k * 8 + j] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[k * 8 + j];
                }
                pRSP->dctBuf[c * 0x40 + j * 8 + i] = (dd + 0x4000) >> 15;
                if (pRSP->dctBuf[c * 0x40 + j * 8 + i] < 0) {
                    pRSP->dctBuf[c * 0x40 + j * 8 + i] = 0;
                }
            }
        }
    }
}

void rspUndoYUVtoDCTBuf(Rsp* pRSP) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[i * 16 + j].y = pRSP->dctBuf[i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[i * 16 + (j + 8)].y = pRSP->dctBuf[0x40 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i + 8) * 16 + j].y = pRSP->dctBuf[0x80 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i + 8) * 16 + (j + 8)].y = pRSP->dctBuf[0xC0 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + (j << 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[(i << 1) * 16 + ((j << 1) + 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + ((j << 1) + 1)].u = pRSP->dctBuf[0x100 + i * 8 + j];
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            pRSP->yuvBuf[(i << 1) * 16 + (j << 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + (j << 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[(i << 1) * 16 + ((j << 1) + 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
            pRSP->yuvBuf[((i << 1) + 1) * 16 + ((j << 1) + 1)].v = pRSP->dctBuf[0x140 + i * 8 + j];
        }
    }
}

void rspFormatYUV(Rsp* pRSP, char* imgBuf) {
    int i;
    int j;

    for (j = 0; j < 16; j++) {
        for (i = 0; i < 16; i += 8) {
            // fake?
            imgBuf[j * 32 + i * 2 + 0] = pRSP->yuvBuf[j * 16 + (i + 8) + 0 - 8].u;
            imgBuf[j * 32 + i * 2 + 1] = pRSP->yuvBuf[j * 16 + (i + 8) + 0 - 8].y;
            imgBuf[j * 32 + i * 2 + 2] = pRSP->yuvBuf[j * 16 + (i + 8) + 0 - 8].v;
            imgBuf[j * 32 + i * 2 + 3] = pRSP->yuvBuf[j * 16 + (i + 8) + 1 - 8].y;
            imgBuf[j * 32 + i * 2 + 4] = pRSP->yuvBuf[j * 16 + (i + 8) + 2 - 8].u;
            imgBuf[j * 32 + i * 2 + 5] = pRSP->yuvBuf[j * 16 + (i + 8) + 2 - 8].y;
            imgBuf[j * 32 + i * 2 + 6] = pRSP->yuvBuf[j * 16 + (i + 8) + 2 - 8].v;
            imgBuf[j * 32 + i * 2 + 7] = pRSP->yuvBuf[j * 16 + (i + 8) + 3 - 8].y;
            imgBuf[j * 32 + i * 2 + 8] = pRSP->yuvBuf[j * 16 + (i + 8) + 4 - 8].u;
            imgBuf[j * 32 + i * 2 + 9] = pRSP->yuvBuf[j * 16 + (i + 8) + 4 - 8].y;
            imgBuf[j * 32 + i * 2 + 10] = pRSP->yuvBuf[j * 16 + (i + 8) + 4 - 8].v;
            imgBuf[j * 32 + i * 2 + 11] = pRSP->yuvBuf[j * 16 + (i + 8) + 5 - 8].y;
            imgBuf[j * 32 + i * 2 + 12] = pRSP->yuvBuf[j * 16 + (i + 8) + 6 - 8].u;
            imgBuf[j * 32 + i * 2 + 13] = pRSP->yuvBuf[j * 16 + (i + 8) + 6 - 8].y;
            imgBuf[j * 32 + i * 2 + 14] = pRSP->yuvBuf[j * 16 + (i + 8) + 6 - 8].v;
            imgBuf[j * 32 + i * 2 + 15] = pRSP->yuvBuf[j * 16 + (i + 8) + 7 - 8].y;
        }
    }
}

static bool rspParseJPEG_Encode(Rsp* pRSP, RspTask* pTask) {
    int preDc[3];
    u8* temp;
    u8* temp2;
    int i;
    int j;
    int x;
    int y;
    u8* system_imb;
    u8* system_cfb;
    int scale;
    int width;
    int height;

    preDc[0] = 0;
    preDc[1] = 0;
    preDc[2] = 0;

    rspCreateJPEGArrays(pRSP);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&system_imb, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&system_cfb, pTask->nOffsetBuffer, NULL)) {
        return false;
    }

    width = pTask->nLengthMBI + 1;
    height = pTask->nLengthYield + 1;
    scale = pTask->nLengthStack;
    temp = system_imb;
    temp2 = system_cfb;

    for (y = 0; y < height * 16; y += 16) {
        for (x = 0; x < width * 16; x += 16) {
            for (i = 0; i < 16; i++) {
                for (j = 0; j < 16; j++) {
                    rspConvertBufferToRGBA(&temp2[((y + i) * (width << 4) + (x + j)) * 2], &pRSP->rgbaBuf[i * 16 + j]);
                }
            }
            rspConvertRGBAtoYUV(pRSP);
            rspYUVtoDCTBuf(pRSP);
            rspDCT(pRSP);
            rspQuantize(pRSP, scale);
            for (i = 0; i < 4; i++) {
                rspZigzagData(pRSP, &temp, i, &preDc[0]);
            }
            rspZigzagData(pRSP, &temp, i++, &preDc[1]);
            rspZigzagData(pRSP, &temp, i++, &preDc[2]);
        }
    }

    return true;
}

static bool rspParseJPEG_Decode(Rsp* pRSP, RspTask* pTask) {
    int preDc[3];
    int i;
    int y;
    u8* temp;
    u8* temp2;
    u64* system_imb;
    int size;
    int scale;

    rspCreateJPEGArrays(pRSP);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&system_imb, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    preDc[0] = 0;
    preDc[1] = 0;
    preDc[2] = 0;

    temp2 = temp = (u8*)system_imb;
    size = pTask->nLengthMBI;
    scale = pTask->nLengthYield;

    for (y = 0; y < size; y++) {
        for (i = 0; i < 4; i++) {
            rspUndoZigzagData(pRSP, &temp, i, &preDc[0]);
        }
        rspUndoZigzagData(pRSP, &temp, i++, &preDc[1]);
        rspUndoZigzagData(pRSP, &temp, i++, &preDc[2]);
        rspUndoQuantize(pRSP, scale);
        rspUndoDCT(pRSP);
        rspUndoYUVtoDCTBuf(pRSP);
        rspFormatYUV(pRSP, (char*)temp2);
        temp2 += 0x300;
    }

    return true;
}

static bool rspCreateJPEGArraysZ(Rsp* pRSP, s32 qYAddress, s32 qCbAddress, s32 qCrAddress) {
    pRSP->Coeff = (s32*)pRSP->pDMEM;
    pRSP->Coeff[0] = 0x1000;
    pRSP->Coeff[1] = 0x1000;
    pRSP->Coeff[2] = 0x1000;
    pRSP->Coeff[3] = 0x1000;
    pRSP->Coeff[4] = 0x1000;
    pRSP->Coeff[5] = 0x1000;
    pRSP->Coeff[6] = 0x1000;
    pRSP->Coeff[7] = 0x1000;
    pRSP->Coeff[8] = 0x1631;
    pRSP->Coeff[9] = 0x12D0;
    pRSP->Coeff[10] = 0xC92;
    pRSP->Coeff[11] = 0x46A;
    pRSP->Coeff[12] = -0x46A;
    pRSP->Coeff[13] = -0xC92;
    pRSP->Coeff[14] = -0x12D0;
    pRSP->Coeff[15] = -0x1631;
    pRSP->Coeff[16] = 0x14E8;
    pRSP->Coeff[17] = 0x8A9;
    pRSP->Coeff[18] = -0x8A9;
    pRSP->Coeff[19] = -0x14E8;
    pRSP->Coeff[20] = -0x14E8;
    pRSP->Coeff[21] = -0x8A9;
    pRSP->Coeff[22] = 0x8A9;
    pRSP->Coeff[23] = 0x14E8;
    pRSP->Coeff[24] = 0x12D0;
    pRSP->Coeff[25] = -0x46A;
    pRSP->Coeff[26] = -0x1631;
    pRSP->Coeff[27] = -0xC92;
    pRSP->Coeff[28] = 0xC92;
    pRSP->Coeff[29] = 0x1631;
    pRSP->Coeff[30] = 0x46A;
    pRSP->Coeff[31] = -0x12D0;
    pRSP->Coeff[32] = 0x1000;
    pRSP->Coeff[33] = -0x1000;
    pRSP->Coeff[34] = -0x1000;
    pRSP->Coeff[35] = 0x1000;
    pRSP->Coeff[36] = 0x1000;
    pRSP->Coeff[37] = -0x1000;
    pRSP->Coeff[38] = -0x1000;
    pRSP->Coeff[39] = 0x1000;
    pRSP->Coeff[40] = 0xC92;
    pRSP->Coeff[41] = -0x1631;
    pRSP->Coeff[42] = 0x46A;
    pRSP->Coeff[43] = 0x12D0;
    pRSP->Coeff[44] = -0x12D0;
    pRSP->Coeff[45] = -0x46A;
    pRSP->Coeff[46] = 0x1631;
    pRSP->Coeff[47] = -0xC92;
    pRSP->Coeff[48] = 0x8A9;
    pRSP->Coeff[49] = -0x14E8;
    pRSP->Coeff[50] = 0x14E8;
    pRSP->Coeff[51] = -0x8A9;
    pRSP->Coeff[52] = -0x8A9;
    pRSP->Coeff[53] = 0x14E8;
    pRSP->Coeff[54] = -0x14E8;
    pRSP->Coeff[55] = 0x8A9;
    pRSP->Coeff[56] = 0x46A;
    pRSP->Coeff[57] = -0xC92;
    pRSP->Coeff[58] = 0x12D0;
    pRSP->Coeff[59] = -0x1631;
    pRSP->Coeff[60] = 0x1631;
    pRSP->Coeff[61] = -0x12D0;
    pRSP->Coeff[62] = 0xC92;
    pRSP->Coeff[63] = -0x46A;

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QYTable, (u32)qYAddress, NULL)) {
        return false;
    }
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QCbTable, (u32)qCbAddress, NULL)) {
        return false;
    }
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pRSP->QCrTable, (u32)qCrAddress, NULL)) {
        return false;
    }

    pRSP->dctBuf = (int*)((u8*)pRSP->Coeff + 0x100);
    return true;
}

static void rspDCTZ(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[j * 8 + k] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[j * 8 + k];
                }
                pRSP->dctBuf[c * 0x40 + i * 8 + j] = (dd + 0x4000) >> 15;
            }
        }
    }
}

static void rspQuantizeZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;
    s32 i;
    s32 j;

    for (c = 0; c < 4; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dataBuf[c * 0x40 + i * 8 + j] >>= 4;
                dataBuf[c * 0x40 + i * 8 + j] /= pRSP->QYTable[i * 8 + j];
            }
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x100 + i * 8 + j] >>= 4;
            dataBuf[0x100 + i * 8 + j] /= pRSP->QCbTable[i * 8 + j];
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x140 + i * 8 + j] >>= 4;
            dataBuf[0x140 + i * 8 + j] /= pRSP->QCrTable[i * 8 + j];
        }
    }
}

void rspZigzagDataZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;

    for (c = 0; c < 6; c++, dataBuf += 0x40) {
        dataBuf[0] = pRSP->dctBuf[c * 0x40 + 0];
        dataBuf[1] = pRSP->dctBuf[c * 0x40 + 8];
        dataBuf[2] = pRSP->dctBuf[c * 0x40 + 1];
        dataBuf[3] = pRSP->dctBuf[c * 0x40 + 2];
        dataBuf[4] = pRSP->dctBuf[c * 0x40 + 9];
        dataBuf[5] = pRSP->dctBuf[c * 0x40 + 16];
        dataBuf[6] = pRSP->dctBuf[c * 0x40 + 24];
        dataBuf[7] = pRSP->dctBuf[c * 0x40 + 17];
        dataBuf[8] = pRSP->dctBuf[c * 0x40 + 10];
        dataBuf[9] = pRSP->dctBuf[c * 0x40 + 3];
        dataBuf[10] = pRSP->dctBuf[c * 0x40 + 4];
        dataBuf[11] = pRSP->dctBuf[c * 0x40 + 11];
        dataBuf[12] = pRSP->dctBuf[c * 0x40 + 18];
        dataBuf[13] = pRSP->dctBuf[c * 0x40 + 25];
        dataBuf[14] = pRSP->dctBuf[c * 0x40 + 32];
        dataBuf[15] = pRSP->dctBuf[c * 0x40 + 40];
        dataBuf[16] = pRSP->dctBuf[c * 0x40 + 33];
        dataBuf[17] = pRSP->dctBuf[c * 0x40 + 26];
        dataBuf[18] = pRSP->dctBuf[c * 0x40 + 19];
        dataBuf[19] = pRSP->dctBuf[c * 0x40 + 12];
        dataBuf[20] = pRSP->dctBuf[c * 0x40 + 5];
        dataBuf[21] = pRSP->dctBuf[c * 0x40 + 6];
        dataBuf[22] = pRSP->dctBuf[c * 0x40 + 13];
        dataBuf[23] = pRSP->dctBuf[c * 0x40 + 20];
        dataBuf[24] = pRSP->dctBuf[c * 0x40 + 27];
        dataBuf[25] = pRSP->dctBuf[c * 0x40 + 34];
        dataBuf[26] = pRSP->dctBuf[c * 0x40 + 41];
        dataBuf[27] = pRSP->dctBuf[c * 0x40 + 48];
        dataBuf[28] = pRSP->dctBuf[c * 0x40 + 56];
        dataBuf[29] = pRSP->dctBuf[c * 0x40 + 49];
        dataBuf[30] = pRSP->dctBuf[c * 0x40 + 42];
        dataBuf[31] = pRSP->dctBuf[c * 0x40 + 35];
        dataBuf[32] = pRSP->dctBuf[c * 0x40 + 28];
        dataBuf[33] = pRSP->dctBuf[c * 0x40 + 21];
        dataBuf[34] = pRSP->dctBuf[c * 0x40 + 14];
        dataBuf[35] = pRSP->dctBuf[c * 0x40 + 7];
        dataBuf[36] = pRSP->dctBuf[c * 0x40 + 15];
        dataBuf[37] = pRSP->dctBuf[c * 0x40 + 22];
        dataBuf[38] = pRSP->dctBuf[c * 0x40 + 29];
        dataBuf[39] = pRSP->dctBuf[c * 0x40 + 36];
        dataBuf[40] = pRSP->dctBuf[c * 0x40 + 43];
        dataBuf[41] = pRSP->dctBuf[c * 0x40 + 50];
        dataBuf[42] = pRSP->dctBuf[c * 0x40 + 57];
        dataBuf[43] = pRSP->dctBuf[c * 0x40 + 58];
        dataBuf[44] = pRSP->dctBuf[c * 0x40 + 51];
        dataBuf[45] = pRSP->dctBuf[c * 0x40 + 44];
        dataBuf[46] = pRSP->dctBuf[c * 0x40 + 37];
        dataBuf[47] = pRSP->dctBuf[c * 0x40 + 30];
        dataBuf[48] = pRSP->dctBuf[c * 0x40 + 23];
        dataBuf[49] = pRSP->dctBuf[c * 0x40 + 31];
        dataBuf[50] = pRSP->dctBuf[c * 0x40 + 38];
        dataBuf[51] = pRSP->dctBuf[c * 0x40 + 45];
        dataBuf[52] = pRSP->dctBuf[c * 0x40 + 52];
        dataBuf[53] = pRSP->dctBuf[c * 0x40 + 59];
        dataBuf[54] = pRSP->dctBuf[c * 0x40 + 60];
        dataBuf[55] = pRSP->dctBuf[c * 0x40 + 53];
        dataBuf[56] = pRSP->dctBuf[c * 0x40 + 46];
        dataBuf[57] = pRSP->dctBuf[c * 0x40 + 39];
        dataBuf[58] = pRSP->dctBuf[c * 0x40 + 47];
        dataBuf[59] = pRSP->dctBuf[c * 0x40 + 54];
        dataBuf[60] = pRSP->dctBuf[c * 0x40 + 61];
        dataBuf[61] = pRSP->dctBuf[c * 0x40 + 62];
        dataBuf[62] = pRSP->dctBuf[c * 0x40 + 55];
        dataBuf[63] = pRSP->dctBuf[c * 0x40 + 63];
    }
}

void rspUndoQuantizeZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;
    s32 i;
    s32 j;

    for (c = 0; c < 4; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dataBuf[c * 0x40 + i * 8 + j] *= pRSP->QYTable[i * 8 + j];
                dataBuf[c * 0x40 + i * 8 + j] <<= 4;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x100 + i * 8 + j] *= pRSP->QCbTable[i * 8 + j];
            dataBuf[0x100 + i * 8 + j] <<= 4;
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            dataBuf[0x140 + i * 8 + j] *= pRSP->QCrTable[i * 8 + j];
            dataBuf[0x140 + i * 8 + j] <<= 4;
        }
    }
}

void rspUndoZigzagDataZ(Rsp* pRSP, s16* dataBuf) {
    s32 c;

    for (c = 0; c < 6; c++, dataBuf += 0x40) {
        pRSP->dctBuf[c * 0x40 + 0] = dataBuf[0];
        pRSP->dctBuf[c * 0x40 + 8] = dataBuf[1];
        pRSP->dctBuf[c * 0x40 + 1] = dataBuf[2];
        pRSP->dctBuf[c * 0x40 + 2] = dataBuf[3];
        pRSP->dctBuf[c * 0x40 + 9] = dataBuf[4];
        pRSP->dctBuf[c * 0x40 + 16] = dataBuf[5];
        pRSP->dctBuf[c * 0x40 + 24] = dataBuf[6];
        pRSP->dctBuf[c * 0x40 + 17] = dataBuf[7];
        pRSP->dctBuf[c * 0x40 + 10] = dataBuf[8];
        pRSP->dctBuf[c * 0x40 + 3] = dataBuf[9];
        pRSP->dctBuf[c * 0x40 + 4] = dataBuf[10];
        pRSP->dctBuf[c * 0x40 + 11] = dataBuf[11];
        pRSP->dctBuf[c * 0x40 + 18] = dataBuf[12];
        pRSP->dctBuf[c * 0x40 + 25] = dataBuf[13];
        pRSP->dctBuf[c * 0x40 + 32] = dataBuf[14];
        pRSP->dctBuf[c * 0x40 + 40] = dataBuf[15];
        pRSP->dctBuf[c * 0x40 + 33] = dataBuf[16];
        pRSP->dctBuf[c * 0x40 + 26] = dataBuf[17];
        pRSP->dctBuf[c * 0x40 + 19] = dataBuf[18];
        pRSP->dctBuf[c * 0x40 + 12] = dataBuf[19];
        pRSP->dctBuf[c * 0x40 + 5] = dataBuf[20];
        pRSP->dctBuf[c * 0x40 + 6] = dataBuf[21];
        pRSP->dctBuf[c * 0x40 + 13] = dataBuf[22];
        pRSP->dctBuf[c * 0x40 + 20] = dataBuf[23];
        pRSP->dctBuf[c * 0x40 + 27] = dataBuf[24];
        pRSP->dctBuf[c * 0x40 + 34] = dataBuf[25];
        pRSP->dctBuf[c * 0x40 + 41] = dataBuf[26];
        pRSP->dctBuf[c * 0x40 + 48] = dataBuf[27];
        pRSP->dctBuf[c * 0x40 + 56] = dataBuf[28];
        pRSP->dctBuf[c * 0x40 + 49] = dataBuf[29];
        pRSP->dctBuf[c * 0x40 + 42] = dataBuf[30];
        pRSP->dctBuf[c * 0x40 + 35] = dataBuf[31];
        pRSP->dctBuf[c * 0x40 + 28] = dataBuf[32];
        pRSP->dctBuf[c * 0x40 + 21] = dataBuf[33];
        pRSP->dctBuf[c * 0x40 + 14] = dataBuf[34];
        pRSP->dctBuf[c * 0x40 + 7] = dataBuf[35];
        pRSP->dctBuf[c * 0x40 + 15] = dataBuf[36];
        pRSP->dctBuf[c * 0x40 + 22] = dataBuf[37];
        pRSP->dctBuf[c * 0x40 + 29] = dataBuf[38];
        pRSP->dctBuf[c * 0x40 + 36] = dataBuf[39];
        pRSP->dctBuf[c * 0x40 + 43] = dataBuf[40];
        pRSP->dctBuf[c * 0x40 + 50] = dataBuf[41];
        pRSP->dctBuf[c * 0x40 + 57] = dataBuf[42];
        pRSP->dctBuf[c * 0x40 + 58] = dataBuf[43];
        pRSP->dctBuf[c * 0x40 + 51] = dataBuf[44];
        pRSP->dctBuf[c * 0x40 + 44] = dataBuf[45];
        pRSP->dctBuf[c * 0x40 + 37] = dataBuf[46];
        pRSP->dctBuf[c * 0x40 + 30] = dataBuf[47];
        pRSP->dctBuf[c * 0x40 + 23] = dataBuf[48];
        pRSP->dctBuf[c * 0x40 + 31] = dataBuf[49];
        pRSP->dctBuf[c * 0x40 + 38] = dataBuf[50];
        pRSP->dctBuf[c * 0x40 + 45] = dataBuf[51];
        pRSP->dctBuf[c * 0x40 + 52] = dataBuf[52];
        pRSP->dctBuf[c * 0x40 + 59] = dataBuf[53];
        pRSP->dctBuf[c * 0x40 + 60] = dataBuf[54];
        pRSP->dctBuf[c * 0x40 + 53] = dataBuf[55];
        pRSP->dctBuf[c * 0x40 + 46] = dataBuf[56];
        pRSP->dctBuf[c * 0x40 + 39] = dataBuf[57];
        pRSP->dctBuf[c * 0x40 + 47] = dataBuf[58];
        pRSP->dctBuf[c * 0x40 + 54] = dataBuf[59];
        pRSP->dctBuf[c * 0x40 + 61] = dataBuf[60];
        pRSP->dctBuf[c * 0x40 + 62] = dataBuf[61];
        pRSP->dctBuf[c * 0x40 + 55] = dataBuf[62];
        pRSP->dctBuf[c * 0x40 + 63] = dataBuf[63];
    }
}

void rspUndoDCTZ(Rsp* pRSP) {
    s32 c;
    s32 i;
    s32 j;
    s32 k;
    s32 dd;
    s16 t[8][8];

    for (c = 0; c < 6; c++) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += pRSP->Coeff[k * 8 + j] * pRSP->dctBuf[c * 0x40 + i * 8 + k];
                }
                t[i][j] = (dd + 0x800) >> 12;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                dd = 0;
                for (k = 0; k < 8; k++) {
                    dd += t[k][i] * pRSP->Coeff[k * 8 + j];
                }
                pRSP->dctBuf[c * 0x40 + i * 8 + j] = (dd + 0x4000) >> 15;
            }
        }
    }
}

bool rspUndoLoadColorBufferZ(Rsp* pRSP, s32 r, s32 g, s32 b, s16* imgBuf, s32 index) {
    if (r <= 0) {
        r = 0;
    } else if (r > 0xFF0) {
        r = 31;
    } else {
        r = (r >> 7) & 0x1F;
    }

    if (g <= 0) {
        g = 0;
    } else if (g > 0xFF0) {
        g = 31;
    } else {
        g = (g >> 7) & 0x1F;
    }

    if (b <= 0) {
        b = 0;
    } else if (b > 0xFF0) {
        b = 31;
    } else {
        b = (b >> 7) & 0x1F;
    }

    imgBuf[index] = (r << 11) | (g << 6) | (b << 1) | 1;
    return true;
}

bool rspUndoRecon420Z(Rsp* pRSP, s16* imgBuf) {
    s32 i;
    s32 j;
    s32 r;
    s32 g;
    s32 b;
    s32 y;
    s32 u;
    s32 v;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            imgBuf[i * 32 + j + 0] = 0;
            imgBuf[i * 32 + j + 8] = 0;
            imgBuf[i * 32 + j + 16] = 0;
            imgBuf[i * 32 + j + 24] = 0;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            y = pRSP->dctBuf[0x000 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x100 + (i >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x140 + (i >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j);

            y = pRSP->dctBuf[0x080 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x100 + ((i + 8) >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x140 + ((i + 8) >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j + 0x80);

            y = pRSP->dctBuf[0x040 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x104 + (i >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x144 + (i >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + 8 + j);

            y = pRSP->dctBuf[0x0C0 + i * 8 + j] + 0x800;
            u = pRSP->dctBuf[0x104 + ((i + 8) >> 1) * 8 + (j >> 1)];
            v = pRSP->dctBuf[0x144 + ((i + 8) >> 1) * 8 + (j >> 1)];
            r = y + ((v * 0x670A) >> 16) + v;
            g = y - (((u * 0x5824) >> 16) + ((v * 0xB6E3) >> 16));
            b = y + ((u * 0xC5E3) >> 16) + u;
            rspUndoLoadColorBufferZ(pRSP, r, g, b, imgBuf, i * 16 + j + 0x88);
        }
    }

    return true;
}

static inline bool rspLoadColorBufferZ(Rsp* pRSP, s32* r, s32* g, s32* b, s16* imgBuf, s32 index) {
    *r = (imgBuf[index] >> 11) & 0x1F;
    *g = (imgBuf[index] >> 6) & 0x1F;
    *b = (imgBuf[index] >> 1) & 0x1F;
    return true;
}

bool rspRecon420Z(Rsp* pRSP, s16* imgBuf) {
    s32 i;
    s32 j;
    s32 r;
    s32 g;
    s32 b;
    s32 y;
    s32 u;
    s32 v;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x000 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x100 + (i >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x140 + (i >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j + 0x80);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x080 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x100 + ((i + 8) >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x140 + ((i + 8) >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + 8 + j);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x040 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x104 + (i >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x144 + (i >> 1) * 8 + (j >> 1)] = v;

            rspLoadColorBufferZ(pRSP, &r, &g, &b, imgBuf, i * 16 + j + 0x88);
            y = g + (b << 16) / 116195 + (r << 16) / 91914;
            u = ((b - y) << 16) / 116195;
            v = ((r - y) << 16) / 91914;
            pRSP->dctBuf[0x0C0 + 8 * i + j] = y - 0x800;
            pRSP->dctBuf[0x104 + ((i + 8) >> 1) * 8 + (j >> 1)] = u;
            pRSP->dctBuf[0x144 + ((i + 8) >> 1) * 8 + (j >> 1)] = v;
        }
    }
    return true;
}

static bool rspParseJPEG_EncodeZ(Rsp* pRSP, RspTask* pTask) {
    s32 y;
    s32 pad;
    s16* temp;
    s16* temp2;
    u64* system_imb;
    u32* infoStruct;
    s32 size;
    s32 pad2[3];

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&infoStruct, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&system_imb, infoStruct[0], NULL)) {
        return false;
    }

    size = infoStruct[1];
    rspCreateJPEGArraysZ(pRSP, infoStruct[3], infoStruct[4], infoStruct[5]);
    temp2 = (s16*)system_imb;

    for (y = 0; y < size; y++) {
        rspRecon420Z(pRSP, temp2);
        rspDCTZ(pRSP);
        rspZigzagDataZ(pRSP, temp2);
        rspQuantizeZ(pRSP, temp2);
        temp2 += 0x180;
    }

    return true;
}

static bool rspParseJPEG_DecodeZ(Rsp* pRSP, RspTask* pTask) {
    s32 y;
    s32 pad;
    s16* temp;
    s16* temp2;
    u64* system_imb;
    u32* infoStruct;
    s32 size;
    s32 pad2[3];

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&infoStruct, pTask->nOffsetMBI, NULL)) {
        return false;
    }

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&system_imb, infoStruct[0], NULL)) {
        return false;
    }

    size = infoStruct[1];
    rspCreateJPEGArraysZ(pRSP, infoStruct[3], infoStruct[4], infoStruct[5]);
    temp2 = (s16*)system_imb;

    for (y = 0; y < size; y++) {
        rspUndoQuantizeZ(pRSP, temp2);
        rspUndoZigzagDataZ(pRSP, temp2);
        rspUndoDCTZ(pRSP);
        rspUndoRecon420Z(pRSP, temp2);
        temp2 += 0x180;
    }

    return true;
}
