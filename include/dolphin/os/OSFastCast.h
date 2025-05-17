#ifndef _DOLPHIN_OS_OSFASTCAST_H
#define _DOLPHIN_OS_OSFASTCAST_H

#define OS_GQR_F32 0x0000
#define OS_GQR_U8 0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8 0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8 2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8 4
#define OS_FASTCAST_S16 5

static inline void OSInitFastCast(void) {
#ifdef __MWERKS__
    // clang-format off
    asm {
        li      r3, OS_GQR_U8
        oris    r3, r3, OS_GQR_U8
        mtspr   GQR2, r3

        li      r3, OS_GQR_U16
        oris    r3, r3, OS_GQR_U16
        mtspr   GQR3, r3

        li      r3, OS_GQR_S8
        oris    r3, r3, OS_GQR_S8
        mtspr   GQR4, r3

        li      r3, OS_GQR_S16
        oris    r3, r3, OS_GQR_S16
        mtspr   GQR5, r3
    }
    // clang-format off
#endif
}

static inline f32 __OSu8tof32(register u8* arg) {
    register f32 ret;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_U8
    }
    // clang-format on
#else
    ret = (f32)*arg;
#endif

    return ret;
}

static inline f32 __OSu16tof32(register u16* arg) {
    register f32 ret;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_U16
    }
    // clang-format on
#else
    ret = (f32)*arg;
#endif

    return ret;
}

static inline f32 __OSs8tof32(register s8* arg) {
    register f32 ret;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_S8
    }
    // clang-format on
#else
    ret = (f32)*arg;
#endif

    return ret;
}

static inline f32 __OSs16tof32(register s16* arg) {
    register f32 ret;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_S16
    }
    // clang-format on
#else
    ret = (f32)*arg;
#endif

    return ret;
}

static inline void OSu8tof32(u8* in, f32* out) { *out = __OSu8tof32(in); }
static inline void OSu16tof32(u16* in, f32* out) { *out = __OSu16tof32(in); }
static inline void OSs8tof32(s8* in, f32* out) { *out = __OSs8tof32(in); }
static inline void OSs16tof32(s16* in, f32* out) { *out = __OSs16tof32(in); }

static inline u8 __OSf32tou8(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    u8 r;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_st arg, 0(ptr), 1, OS_FASTCAST_U8
    }
    // clang-format on
    r = *(u8*)ptr;
#else
    r = (u8)arg;
#endif

    return r;
}

static inline u16 __OSf32tou16(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    u16 r;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_st arg, 0(ptr), 1, OS_FASTCAST_U16
    }
    // clang-format on
    r = *(u16*)ptr;
#else
    r = (u16)arg;
#endif

    return r;
}

static inline s8 __OSf32tos8(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    s8 r;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_st arg, 0(ptr), 1, OS_FASTCAST_S8
    }
    // clang-format on
    r = *(s8*)ptr;
#else
    r = (s8)arg;
#endif

    return r;
}

static inline s16 __OSf32tos16(register f32 arg) {
    f32 a;
    register f32* ptr = &a;
    s16 r;

#ifdef __MWERKS__
    // clang-format off
    asm {
        psq_st arg, 0(ptr), 1, OS_FASTCAST_S16
    }
    // clang-format on
    r = *(s16*)ptr;
#else
    r = (s16)arg;
#endif

    return r;
}

static inline void OSf32tou8(f32* in, u8* out) { *out = __OSf32tou8(*in); }
static inline void OSf32tou16(f32* in, u16* out) { *out = __OSf32tou16(*in); }
static inline void OSf32tos8(f32* in, s8* out) { *out = __OSf32tos8(*in); }
static inline void OSf32tos16(f32* in, s16* out) { *out = __OSf32tos16(*in); }

#endif // _DOLPHIN_OSFASTCAST
