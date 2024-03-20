#include "dolphin/os.h"

#define SHN_UNDEF 0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC 0xff00
#define SHN_HIPROC 0xff1f
#define SHN_ABS 0xfff1
#define SHN_COMMON 0xfff2
#define SHN_HIRESERVE 0xffff

#define ELF32_R_SYM(i) ((i) >> 8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF32_R_INFO(s, t) (((s) << 8) + (unsigned char)(t))

//      Name                    Value       Field   Calculation
#define R_PPC_NONE 0 //  none    none
#define R_PPC_ADDR32 1 //  word32  S + A
#define R_PPC_ADDR24 2 //  low24*  (S + A) >> 2
#define R_PPC_ADDR16 3 //  half16* S + A
#define R_PPC_ADDR16_LO 4 //  half16  #lo(S + A)
#define R_PPC_ADDR16_HI 5 //  half16  #hi(S + A)
#define R_PPC_ADDR16_HA 6 //  half16  #ha(S + A)
#define R_PPC_ADDR14 7 //  low14*  (S + A) >> 2
#define R_PPC_ADDR14_BRTAKEN 8 //  low14*  (S + A) >> 2
#define R_PPC_ADDR14_BRNTAKEN 9 //  low14*  (S + A) >> 2
#define R_PPC_REL24 10 //  low24*  (S + A - P) >> 2
#define R_PPC_REL14 11 //  low14*  (S + A - P) >> 2
#define R_PPC_REL14_BRTAKEN 12 //  low14*  (S + A - P) >> 2
#define R_PPC_REL14_BRNTAKEN 13 //  low14*  (S + A - P) >> 2

#define R_PPC_GOT16 14 //  half16* G + A
#define R_PPC_GOT16_LO 15 //  half16  #lo(G + A)
#define R_PPC_GOT16_HI 16 //  half16  #hi(G + A)
#define R_PPC_GOT16_HA 17 //  half16  #ha(G + A)
#define R_PPC_PLTREL24 18 //  low24*  (L + A - P) >> 2
#define R_PPC_COPY 19 //  none    none
#define R_PPC_GLOB_DAT 20 //  word32  S + A
#define R_PPC_JMP_SLOT 21 //  none
#define R_PPC_RELATIVE 22 //  word32  B + A

#define R_PPC_LOCAL24PC 23 //  low24*

#define R_PPC_UADDR32 24 //  word32  S + A
#define R_PPC_UADDR16 25 //  half16* S + A
#define R_PPC_REL32 26 //  word32  S + A - P

#define R_PPC_PLT32 27 //  word32  L + A
#define R_PPC_PLTREL32 28 //  word32  L + A - P
#define R_PPC_PLT16_LO 29 //  half16  #lo(L + A)
#define R_PPL_PLT16_HI 30 //  half16  #hi(L + A)
#define R_PPC_PLT16_HA 31 //  half16  #ha(L + A)

#define R_PPC_SDAREL16 32 //  half16* S + A - _SDA_BASE_
#define R_PPC_SECTOFF 33 //  half16* R + A
#define R_PPC_SECTOFF_LO 34 //  half16  #lo(R + A)
#define R_PPC_SECTOFF_HI 35 //  half16  #hi(R + A)
#define R_PPC_SECTOFF_HA 36 //  half16  #ha(R + A)
#define R_PPC_ADDR30 37 //  word30  (S + A - P) >> 2

#define R_PPC_EMB_NADDR32 101 //  uword32 N       (A - S)
#define R_PPC_EMB_NADDR16 102 //  uhalf16 Y       (A - S)
#define R_PPC_EMB_NADDR16_LO 103 //  uhalf16 N       #lo(A - S)
#define R_PPC_EMB_NADDR16_HI 104 //  uhalf16 N       #hi(A - S)
#define R_PPC_EMB_NADDR16_HA 105 //  uhalf16 N       #ha(A - S)
#define R_PPC_EMB_SDAI16 106 //  uhalf16 Y       T
#define R_PPC_EMB_SDA2I16 107 //  uhalf16 Y       U
#define R_PPC_EMB_SDA2REL 108 //  uhalf16 Y       S + A - _SDA2_BASE_
#define R_PPC_EMB_SDA21 109 //  ulow21  N
#define R_PPC_EMB_MRKREF 110 //  none    N
#define R_PPC_EMB_RELSEC16 111 //  uhalf16 Y       V + A
#define R_PPC_EMB_RELST_LO 112 //  uhalf16 N       #lo(W + A)
#define R_PPC_EMB_RELST_HI 113 //  uhalf16 N       #hi(W + A)
#define R_PPC_EMB_RELST_HA 114 //  uhalf16 N       #ha(W + A)
#define R_PPC_EMB_BIT_FLD 115 //  uword32 Y
#define R_PPC_EMB_RELSDA 116 //  uhalf16 Y

OSModuleQueue __OSModuleInfoList : (OS_BASE_CACHED | 0x30C8);
const void* __OSStringTable : (OS_BASE_CACHED | 0x30D0);

#define EnqueueTail(queue, moduleInfo, link)  \
    do {                                      \
        OSModuleInfo* __prev;                 \
                                              \
        __prev = (queue)->tail;               \
        if (__prev == NULL)                   \
            (queue)->head = (moduleInfo);     \
        else                                  \
            __prev->link.next = (moduleInfo); \
        (moduleInfo)->link.prev = __prev;     \
        (moduleInfo)->link.next = NULL;       \
        (queue)->tail = (moduleInfo);         \
    } while (0)

#define DequeueItem(queue, moduleInfo, link) \
    do {                                     \
        OSModuleInfo* __next;                \
        OSModuleInfo* __prev;                \
                                             \
        __next = (moduleInfo)->link.next;    \
        __prev = (moduleInfo)->link.prev;    \
                                             \
        if (__next == NULL)                  \
            (queue)->tail = __prev;          \
        else                                 \
            __next->link.prev = __prev;      \
                                             \
        if (__prev == NULL)                  \
            (queue)->head = __next;          \
        else                                 \
            __prev->link.next = __next;      \
    } while (0)

void __OSModuleInit(void) {
    __OSModuleInfoList.head = __OSModuleInfoList.tail = 0;
    __OSStringTable = 0;
}
