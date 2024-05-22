#ifndef _DOLPHIN_GX_GXFIFO_H_
#define _DOLPHIN_GX_GXFIFO_H_

#include "dolphin/gx/GXEnum.h"
#include "dolphin/os/OSContext.h"

#define GX_WRITE_U8(val) (GXWGFifo.u8 = val)
#define GX_WRITE_U16(val) (GXWGFifo.u16 = val)
#define GX_WRITE_U32(val) (GXWGFifo.u32 = (u32)val)
#define GX_WRITE_F32(val) (GXWGFifo.f32 = (f32)val)

#define GX_WRITE_RAS_REG(value) \
    do {                        \
        GX_WRITE_U8(0x61);      \
        GX_WRITE_U32(value);    \
    } while (0)

#define GX_WRITE_XF_REG(addr, value)   \
    do {                               \
        GX_WRITE_U8(0x10);             \
        GX_WRITE_U32(0x1000 + (addr)); \
        GX_WRITE_U32(value);           \
    } while (0)

typedef void (*GXBreakPtCallback)(void);

typedef struct {
    u8 pad[128];
} GXFifoObj;

// Internal struct for FIFO access.
typedef struct _GXFifoObjPriv {
    /* 0x00 */ void* base;
    /* 0x04 */ void* end;
    /* 0x08 */ u32 size;
    /* 0x0C */ u32 highWatermark;
    /* 0x10 */ u32 lowWatermark;
    /* 0x14 */ void* readPtr;
    /* 0x18 */ void* writePtr;
    /* 0x1C */ s32 rwDistance;
    /* 0x20 */ u8 _20[0x60];
} GXFifoObjPriv;

void GXCPInterruptHandler(s16 p1, OSContext* context);
void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
void GXInitFifoLimits(GXFifoObj* fifo, u32 highWatermark, u32 lowWatermark);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXSetGPFifo(GXFifoObj* fifo);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt);
void* GXGetFifoBase(const GXFifoObj* obj);
u32 GXGetFifoSize(const GXFifoObj* obj);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
void __GXFifoInit(void);
void __GXFifoReadEnable(void);
void __GXFifoReadDisable(void);
void __GXFifoLink(u8 link);
void __GXWriteFifoIntEnable(u32 p1, u32 p2);
void __GXWriteFifoIntReset(u32 p1, u32 p2);
void __GXCleanGPFifo(void);
GXFifoObj* GXGetCPUFifo(void);
GXFifoObj* GXGetGPFifo(void);

inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_CP_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_CP_REG(regAddrL);
        ctrH0 = GX_GET_CP_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

inline u32 __GXReadPECounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_PE_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_PE_REG(regAddrL);
        ctrH0 = GX_GET_PE_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

inline u32 __GXReadMEMCounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_MEM_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_MEM_REG(regAddrL);
        ctrH0 = GX_GET_MEM_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

#endif
