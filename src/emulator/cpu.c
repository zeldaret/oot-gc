#include "emulator/cpu.h"
#include "dolphin.h"
#include "emulator/cpu_jumptable.h"
#include "emulator/frame.h"
#include "emulator/library.h"
#include "emulator/ram.h"
#include "emulator/rom.h"
#include "emulator/rsp.h"
#include "emulator/simGCN.h"
#include "emulator/system.h"
#include "emulator/video.h"
#include "emulator/xlHeap.h"
#include "emulator/xlObject.h"
#include "emulator/xlPostGCN.h"
#include "macros.h"
#include "math.h"

static inline bool cpuMakeCachedAddress(Cpu* pCPU, s32 nAddressN64, s32 nAddressHost, CpuFunction* pFunction);
static bool cpuFindCachedAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressHost);
static bool cpuSetTLB(Cpu* pCPU, s32 iEntry);
static bool cpuHeapReset(u32* array, s32 count);
static bool cpuDMAUpdateFunction(Cpu* pCPU, s32 start, s32 end);
static void treeCallerInit(CpuCallerID* block, s32 total);
static bool treeInit(Cpu* pCPU, s32 root_address);
static bool treeKill(Cpu* pCPU);
static bool treeKillNodes(Cpu* pCPU, CpuFunction* tree);
static bool treeAdjustRoot(Cpu* pCPU, s32 new_start, s32 new_end);
static inline bool treeSearch(Cpu* pCPU, s32 target, CpuFunction** node);
static bool treeSearchNode(CpuFunction* tree, s32 target, CpuFunction** node);
bool treeInsert(Cpu* pCPU, s32 start, s32 end);
static bool treeInsertNode(CpuFunction** tree, s32 start, s32 end, CpuFunction** ppFunction);
static bool treeBalance(CpuTreeRoot* root);
static bool treeKillReason(Cpu* pCPU, s32* value);
static bool treeKillRange(Cpu* pCPU, CpuFunction* tree, s32 start, s32 end);
static bool treeTimerCheck(Cpu* pCPU);
static bool treeCleanUp(Cpu* pCPU, CpuTreeRoot* root);
static bool treeCleanNodes(Cpu* pCPU, CpuFunction* top);
static inline bool treeForceCleanUp(Cpu* pCPU, CpuFunction* tree, s32 kill_limit);
static bool treeForceCleanNodes(Cpu* pCPU, CpuFunction* tree, s32 kill_limit);
static bool treePrintNode(Cpu* pCPU, CpuFunction* tree, s32 print_flag, s32* left, s32* right);
static inline s32 treeMemory(Cpu* pCPU);

_XL_OBJECTTYPE gClassCPU = {
    "CPU",
    sizeof(Cpu),
    NULL,
    (EventFunc)cpuEvent,
};

char* gaszNameGPR[] = {
    "ZERO", "AT", "V0", "V1", "A0", "A1", "A2", "A3", "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7",
    "S0",   "S1", "S2", "S3", "S4", "S5", "S6", "S7", "T8", "T9", "K0", "K1", "GP", "SP", "S8", "RA",
};

char* gaszNameFPR[] = {
    "F0",  "F1",  "F2",  "F3",  "F4",  "F5",  "F6",  "F7",  "F8",  "F9",  "F10",
    "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21",
    "F22", "F23", "F24", "F25", "F26", "F27", "F28", "F29", "F30", "F21", // bug, should be "F31"
};

char* gaszNameCP0[] = {
    "INDEX",         "RANDOM",        "ENTRY-LO0",     "ENTRY-LO1",     "CONTEXT",       "PAGE-MASK", "WIRED",
    "(RESERVED-7)",  "BAD-VADDR",     "COUNT",         "ENTRY-HI",      "COMPARE",       "STATUS",    "CAUSE",
    "EPC",           "uPC-ID",        "CONFIG",        "LLADDR",        "WATCH-LO",      "WATCH-HI",  "X-CONTEXT",
    "(RESERVED-21)", "(RESERVED-22)", "(RESERVED-23)", "(RESERVED-24)", "(RESERVED-25)", "ECC",       "CACHE-ERROR",
    "TAG-LO",        "TAG-HI",        "ERROR-EPC",     "(RESERVED-31)",
};

char* gaszNameCP1[] = {
    "FCR0",
    "FCR1 (RESERVED)",
    "FCR2 (RESERVED)",
    "FCR3 (RESERVED)",
    "FCR4 (RESERVED)",
    "FCR5 (RESERVED)",
    "FCR6 (RESERVED)",
    "FCR7 (RESERVED)",
    "FCR8 (RESERVED)",
    "FCR9 (RESERVED)",
    "FCR10 (RESERVED)",
    "FCR11 (RESERVED)",
    "FCR12 (RESERVED)",
    "FCR13 (RESERVED)",
    "FCR14 (RESERVED)",
    "FCR15 (RESERVED)",
    "FCR16 (RESERVED)",
    "FCR17 (RESERVED)",
    "FCR18 (RESERVED)",
    "FCR19 (RESERVED)",
    "FCR20 (RESERVED)",
    "FCR21 (RESERVED)",
    "FCR22 (RESERVED)",
    "FCR23 (RESERVED)",
    "FCR24 (RESERVED)",
    "FCR25 (RESERVED)",
    "FCR26 (RESERVED)",
    "FCR27 (RESERVED)",
    "FCR28 (RESERVED)",
    "FCR29 (RESERVED)",
    "FCR30 (RESERVED)",
    "FCR31",
};

s64 ganMaskGetCP0[] = {
    0x000000008000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF, 0xFFFFFFFFFFFFFFF0,
    0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF,
    0x00000000FFFFE0FF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFF, 0x00000000F000FF7C, 0xFFFFFFFFFFFFFFFF,
    0x000000000000FFFF, 0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF, 0x00000000FFFFFFFF, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

s64 ganMaskSetCP0[] = {
    0x000000000000003F, 0x000000000000003F, 0x000000003FFFFFFF, 0x000000003FFFFFFF, 0xFFFFFFFFFFFFFFF0,
    0x0000000001FFE000, 0x000000000000001F, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x00000000FFFFFFFF,
    0x00000000FFFFE0FF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFF, 0x0000000000000300, 0xFFFFFFFFFFFFFFFF,
    0x000000000000FFFF, 0x00000000FFFFEFFF, 0x00000000FFFFFFFF, 0x00000000FFFFFFFB, 0x000000000000000F,
    0x00000000FFFFFFF0, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x00000000000000FF, 0x00000000FFBFFFFF, 0x00000000FFFFFFFF, 0x0000000000000000,
    0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
};

u8 Opcode[] = {
    true, true, true, true,  true, true, true, true, true, true, true, true,  true,  true,  true,  true,
    true, true, true, false, true, true, true, true, true, true, true, true,  false, false, false, true,
    true, true, true, true,  true, true, true, true, true, true, true, true,  true,  true,  true,  true,
    true, true, true, false, true, true, true, true, true, true, true, false, true,  true,  true,  true,
};

u8 SpecialOpcode[] = {
    true, false, true, true, true, false, true, true,  true,  true,  false, false, true, true,  false, true,
    true, true,  true, true, true, false, true, true,  true,  true,  true,  true,  true, true,  true,  true,
    true, true,  true, true, true, true,  true, true,  false, false, true,  true,  true, true,  true,  true,
    true, true,  true, true, true, false, true, false, true,  false, true,  true,  true, false, true,  true,
};

u8 RegimmOpcode[] = {
    true, true, true, true, false, false, false, false, true,  true,  true,  true,  true,  false, true,  false,
    true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false,
};

s32 ganOpcodeSaveFP1[] = {
    0x8F480018, 0x11000014, 0x00000000, 0x4448F800, 0x00000000,
};

s32 ganOpcodeSaveFP2_0[] = {
    0x8CBB0018, 0x1360000A, 0x00000000, 0x445BF800, 0x00000000,
};

s32 ganOpcodeSaveFP2_1[] = {
    0x13600009,
    0xACBF011C,
    0x445BF800,
};

s32 ganOpcodeLoadFP[] = {
    0x8F5B0018, 0x13600013, 0x00000000, 0x8F5B012C, 0x44DBF800,
};

/**
 * @brief Mapping of VR4300 to PPC registers.
 *
 * If bit 0x100 is set the VR4300 register is not directly mapped to any PPC register,
 * Instead the register will use the emulated VR4300 object for saving/loading register values.
 */
s32 ganMapGPR[] = {
    0x0000000A, 0x0000000B, 0x0000000C, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011, 0x00000012,
    0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018, 0x00000019, 0x0000001A,
    0x00000110, 0x00000111, 0x00000112, 0x00000113, 0x00000114, 0x00000115, 0x00000116, 0x00000117,
    0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000011C, 0x0000001F, 0x0000011E, 0x0000011F,
};

#ifndef NON_MATCHING
// cpuOpcodeChecksum
void* jtbl_800EBEF0[25] = {
    &lbl_80030EFC, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030F7C, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030F7C, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC,
    &lbl_80030EFC, &lbl_80030EFC, &lbl_80030EFC, &lbl_80030F7C,
};
#else
void* jtbl_800EBEF0[25] = {0};
#endif

#ifndef NON_MATCHING
// cpuOpcodeChecksum
void* jtbl_800EBF54[64] = {
    &lbl_80030F7C, &lbl_80030EA8, &lbl_80030F58, &lbl_80030F60, &lbl_80030F68, &lbl_80030F68, &lbl_80030F68,
    &lbl_80030F68, &lbl_80030F7C, &lbl_80030F70, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F70,
    &lbl_80030F7C, &lbl_80030F70, &lbl_80030ED8, &lbl_80030F2C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F68,
    &lbl_80030F68, &lbl_80030F68, &lbl_80030F68, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F78, &lbl_80030F78,
    &lbl_80030F78, &lbl_80030F78, &lbl_80030F78, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F78,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C,
    &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F78,
    &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F7C, &lbl_80030F78, &lbl_80030F7C,
    &lbl_80030F78,
};
#else
void* jtbl_800EBF54[64] = {0};
#endif

char D_800EC054[] = "start=%p, end=%p (%d) (size: %d)\n";
char D_800EC078[] = "tree range (%p - %p)\n";
char D_800EC090[] = "total nodes: %d (tree height: %d %d)\n";
char D_800EC0B8[] = "total memory: %d\n";

#ifndef NON_MATCHING
// cpuFindFunction
void* jtbl_800EC0CC[25] = {
    &lbl_8003381C, &lbl_80033A68, &lbl_80033A68, &lbl_8003381C, &lbl_8003381C, &lbl_80033A68, &lbl_8003381C,
    &lbl_8003381C, &lbl_80033A68, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C,
    &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_8003381C,
    &lbl_8003381C, &lbl_8003381C, &lbl_8003381C, &lbl_800337F0,
};
#else
void* jtbl_800EC0CC[25] = {0};
#endif

#ifndef NON_MATCHING
// cpuFindFunction
void* jtbl_800EC130[44] = {
    &lbl_800334D8, &lbl_800335A0, &lbl_80033564, &lbl_80033A5C, &lbl_80033644, &lbl_80033768, &lbl_80033768,
    &lbl_80033768, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_800337D0, &lbl_800338AC, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033644,
    &lbl_80033768, &lbl_80033768, &lbl_80033768, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_8003394C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C, &lbl_80033A5C,
    &lbl_80033A5C, &lbl_80033938,
};
#else
void* jtbl_800EC130[44] = {0};
#endif

char D_800EC1E0[] = "_cpuGCN.c";

#ifndef NON_MATCHING
// cpuExecuteLoadStoreF
void* jtbl_800EC1EC[15] = {
    &lbl_8003789C, &lbl_80038010, &lbl_80038010, &lbl_80038010, &lbl_80037AF0,
    &lbl_80038010, &lbl_80037D08, &lbl_80038010, &lbl_800379D8, &lbl_80038010,
    &lbl_80038010, &lbl_80038010, &lbl_80037BF8, &lbl_80038010, &lbl_80037E90,
};
#else
void* jtbl_800EC1EC[15] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteLoadStore
void* jtbl_800EC228[12] = {
    &lbl_800383F4, &lbl_800386AC, &lbl_80038E70, &lbl_80038964, &lbl_80038560, &lbl_80038818,
    &lbl_80038E70, &lbl_80038E70, &lbl_80038AB0, &lbl_80038BF0, &lbl_80038E70, &lbl_80038D30,
};
#else
void* jtbl_800EC228[12] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC258[64] = {
    &lbl_8003C690, &lbl_8003C6CC, &lbl_8003C708, &lbl_8003C754, &lbl_8003C78C, &lbl_8003C85C, &lbl_8003C88C,
    &lbl_8003C8B0, &lbl_8003C8DC, &lbl_8003C900, &lbl_8003C924, &lbl_8003C954, &lbl_8003C984, &lbl_8003C9A0,
    &lbl_8003C9BC, &lbl_8003C9F0, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003CA24, &lbl_8003CA48, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003CA6C, &lbl_8003CA88, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003CAAC,
    &lbl_8003CABC, &lbl_8003CACC, &lbl_8003CB1C, &lbl_8003CB6C, &lbl_8003CBC8, &lbl_8003CC24, &lbl_8003CC80,
    &lbl_8003CCDC, &lbl_8003CCEC, &lbl_8003CD48, &lbl_8003CD98, &lbl_8003CDE8, &lbl_8003CE44, &lbl_8003CEA0,
    &lbl_8003CEFC,
};
#else
void* jtbl_800EC258[64] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC358[64] = {
    &lbl_8003BEA4, &lbl_8003BED0, &lbl_8003BEFC, &lbl_8003BF28, &lbl_8003BF54, &lbl_8003C030, &lbl_8003C078,
    &lbl_8003C094, &lbl_8003C0B4, &lbl_8003C0D8, &lbl_8003C0FC, &lbl_8003C140, &lbl_8003C184, &lbl_8003C1A0,
    &lbl_8003C1BC, &lbl_8003C204, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003C24C, &lbl_8003C284, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003C2BC, &lbl_8003C2D8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003C2FC,
    &lbl_8003C30C, &lbl_8003C31C, &lbl_8003C35C, &lbl_8003C39C, &lbl_8003C3DC, &lbl_8003C41C, &lbl_8003C45C,
    &lbl_8003C49C, &lbl_8003C4AC, &lbl_8003C4EC, &lbl_8003C52C, &lbl_8003C56C, &lbl_8003C5AC, &lbl_8003C5EC,
    &lbl_8003C62C,
};
#else
void* jtbl_800EC358[64] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC458[64] = {
    &lbl_8003B774, &lbl_8003B7A0, &lbl_8003B7CC, &lbl_8003B7F8, &lbl_8003B824, &lbl_8003B8C8, &lbl_8003B8E8,
    &lbl_8003B904, &lbl_8003B924, &lbl_8003B950, &lbl_8003B974, &lbl_8003B99C, &lbl_8003B9C4, &lbl_8003B9F4,
    &lbl_8003BA1C, &lbl_8003BA48, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003BA74, &lbl_8003BA94, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003BAB0, &lbl_8003BAD8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003BAFC,
    &lbl_8003BB0C, &lbl_8003BB1C, &lbl_8003BB5C, &lbl_8003BB9C, &lbl_8003BBDC, &lbl_8003BC1C, &lbl_8003BC60,
    &lbl_8003BCA4, &lbl_8003BCB4, &lbl_8003BCF8, &lbl_8003BD38, &lbl_8003BD78, &lbl_8003BDB8, &lbl_8003BDF8,
    &lbl_8003BE3C,
};
#else
void* jtbl_800EC458[64] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC558[64] = {
    &lbl_8003B040, &lbl_8003B06C, &lbl_8003B098, &lbl_8003B0C4, &lbl_8003B0F0, &lbl_8003B198, &lbl_8003B1BC,
    &lbl_8003B1D8, &lbl_8003B1F8, &lbl_8003B224, &lbl_8003B248, &lbl_8003B270, &lbl_8003B298, &lbl_8003B2C8,
    &lbl_8003B2F0, &lbl_8003B31C, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003B348, &lbl_8003B364, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003B380, &lbl_8003B3A8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003B3CC,
    &lbl_8003B3DC, &lbl_8003B3EC, &lbl_8003B42C, &lbl_8003B46C, &lbl_8003B4AC, &lbl_8003B4EC, &lbl_8003B530,
    &lbl_8003B574, &lbl_8003B584, &lbl_8003B5C8, &lbl_8003B608, &lbl_8003B648, &lbl_8003B688, &lbl_8003B6C8,
    &lbl_8003B70C,
};
#else
void* jtbl_800EC558[64] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC658[7] = {
    &lbl_8003AD84, &lbl_8003ADD4, &lbl_8003ADF8, &lbl_8003DEAC, &lbl_8003AE14, &lbl_8003AE98, &lbl_8003AEBC,
};
#else
void* jtbl_800EC658[7] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC674[9] = {
    &lbl_8003AC94, &lbl_8003ACD8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003AD0C,
    &lbl_8003AD2C, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
};
#else
void* jtbl_800EC674[9] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC698[25] = {
    &lbl_8003AC70, &lbl_8003A824, &lbl_8003A87C, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003A894, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AA30, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70,
    &lbl_8003AC70, &lbl_8003AC70, &lbl_8003AC70, &lbl_8003ABD8,
};
#else
void* jtbl_800EC698[25] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC6FC[20] = {
    &lbl_8003A1A8, &lbl_8003A1D8, &lbl_8003A208, &lbl_8003A254, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_8003DEAC, &lbl_8003A2A0, &lbl_8003A2D0, &lbl_8003A300, &lbl_8003A330, &lbl_8003A360, &lbl_8003DEAC,
    &lbl_8003A390, &lbl_8003DEAC, &lbl_8003A3C0, &lbl_8003A400, &lbl_8003A440, &lbl_8003A498,
};
#else
void* jtbl_800EC6FC[20] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC74C[64] = {
    &lbl_80039680, &lbl_8003DEAC, &lbl_800396A4, &lbl_800396C8, &lbl_800396EC, &lbl_8003DEAC, &lbl_8003971C,
    &lbl_8003974C, &lbl_8003977C, &lbl_80039790, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_800397C0, &lbl_800397D4,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_800397E8, &lbl_80039804, &lbl_80039820, &lbl_8003983C, &lbl_80039858,
    &lbl_8003DEAC, &lbl_80039894, &lbl_800398D0, &lbl_8003990C, &lbl_80039984, &lbl_800399F8, &lbl_80039A50,
    &lbl_80039AA8, &lbl_80039B24, &lbl_80039BA0, &lbl_80039C08, &lbl_80039C70, &lbl_80039C9C, &lbl_80039CC8,
    &lbl_80039CF4, &lbl_80039D20, &lbl_80039D4C, &lbl_80039D78, &lbl_80039DA4, &lbl_8003DEAC, &lbl_8003DEAC,
    &lbl_80039DD0, &lbl_80039E0C, &lbl_80039E48, &lbl_80039E84, &lbl_80039EC0, &lbl_80039EFC, &lbl_80039F38,
    &lbl_80039F6C, &lbl_80039FA0, &lbl_80039FD4, &lbl_8003A008, &lbl_8003DEAC, &lbl_8003A03C, &lbl_8003DEAC,
    &lbl_8003A070, &lbl_8003DEAC, &lbl_8003A09C, &lbl_8003A0C8, &lbl_8003A0F4, &lbl_8003DEAC, &lbl_8003A124,
    &lbl_8003A154,
};
#else
void* jtbl_800EC74C[64] = {0};
#endif

#ifndef NON_MATCHING
// cpuExecuteOpcode
void* jtbl_800EC84C[64] = {
    &lbl_8003965C, &lbl_8003A184, &lbl_8003A4F0, &lbl_8003A558, &lbl_8003A58C, &lbl_8003A61C, &lbl_8003A658,
    &lbl_8003A688, &lbl_8003A6B8, &lbl_8003A6E0, &lbl_8003A708, &lbl_8003A740, &lbl_8003A778, &lbl_8003A79C,
    &lbl_8003A7C0, &lbl_8003A7E4, &lbl_8003A800, &lbl_8003AD4C, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003CF58,
    &lbl_8003CFB0, &lbl_8003D008, &lbl_8003D054, &lbl_8003D0A0, &lbl_8003D0D8, &lbl_8003D138, &lbl_8003D210,
    &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003D110, &lbl_8003D350, &lbl_8003D3B4, &lbl_8003D414,
    &lbl_8003D4A8, &lbl_8003D508, &lbl_8003D568, &lbl_8003D5F8, &lbl_8003D2E8, &lbl_8003D68C, &lbl_8003D6DC,
    &lbl_8003D72C, &lbl_8003D79C, &lbl_8003D7EC, &lbl_8003D86C, &lbl_8003D8EC, &lbl_8003D95C, &lbl_8003DA20,
    &lbl_8003DA80, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DB40, &lbl_8003DBA8, &lbl_8003DEAC, &lbl_8003DC10,
    &lbl_8003DC78, &lbl_8003DCE8, &lbl_8003DEAC, &lbl_8003DEAC, &lbl_8003DD6C, &lbl_8003DDF0, &lbl_8003DEAC,
    &lbl_8003DE50,
};
#else
void* jtbl_800EC84C[64] = {0};
#endif

char D_800EC94C[] = "ERROR in cpuNextInstruction() with opcode %p at %p\n";
char D_800EC980[] = "CALLED: ceil_w single (%p)\n";
char D_800EC99C[] = "CALLED: floor_w single (%p)\n";
char D_800EC9BC[] = "ERROR: CVT_S_S\n";
char D_800EC9CC[] = "CALLED: ceil_w double (%p)\n";
char D_800EC9E8[] = "CALLED: floor_w double (%p)\n";
char D_800ECA08[] = "ERROR: CVT_S_D\n";
char D_800ECA18[] = "ERROR: ADD_W\n";
char D_800ECA28[] = "ERROR: SUB_W\n";
char D_800ECA38[] = "ERROR: MUL_W\n";
char D_800ECA48[] = "ERROR: DIV_W\n";
char D_800ECA58[] = "ERROR: SQRT_W\n";
char D_800ECA68[] = "ERROR: ABS_W\n";
char D_800ECA78[] = "ERROR: MOVE_W\n";
char D_800ECA88[] = "ERROR: NEG_W\n";
char D_800ECA98[] = "ERROR: ROUND_W_W\n";
char D_800ECAAC[] = "ERROR: TRUNC_W_W\n";
char D_800ECAC0[] = "ERROR: CEIL_W_W\n";
char D_800ECAD4[] = "ERROR: FLOOR_W_W\n";
char D_800ECAE8[] = "ERROR: CVT_W_W\n";
char D_800ECAF8[] = "ERROR: C.F_W\n";
char D_800ECB08[] = "ERROR: C.UN_W\n";
char D_800ECB18[] = "ERROR: C.EQ_W\n";
char D_800ECB28[] = "ERROR: C.UEQ_W\n";
char D_800ECB38[] = "ERROR: C.OLT_W\n";
char D_800ECB48[] = "ERROR: C.ULT_W\n";
char D_800ECB58[] = "ERROR: C.OLE_W\n";
char D_800ECB68[] = "ERROR: C.ULE_W\n";
char D_800ECB78[] = "ERROR: C.SF_W\n";
char D_800ECB88[] = "ERROR: C.NGLE_W\n";
char D_800ECB9C[] = "ERROR: C.SEQ_W\n";
char D_800ECBAC[] = "ERROR: C.NGL_W\n";
char D_800ECBBC[] = "ERROR: C.LT_W\n";
char D_800ECBCC[] = "ERROR: C.NGE_W\n";
char D_800ECBDC[] = "ERROR: C.LE_W\n";
char D_800ECBEC[] = "ERROR: C.NGT_W\n";
char D_800ECBFC[] = "ERROR: ADD_L\n";
char D_800ECC0C[] = "ERROR: SUB_L\n";
char D_800ECC1C[] = "ERROR: MUL_L\n";
char D_800ECC2C[] = "ERROR: DIV_L\n";
char D_800ECC3C[] = "ERROR: SQRT_L\n";
char D_800ECC4C[] = "ERROR: ABS_L\n";
char D_800ECC5C[] = "ERROR: MOVE_L\n";
char D_800ECC6C[] = "ERROR: NEG_L\n";
char D_800ECC7C[] = "ERROR: ROUND_W_L\n";
char D_800ECC90[] = "ERROR: TRUNC_W_L\n";
char D_800ECCA4[] = "ERROR: CEIL_W_L\n";
char D_800ECCB8[] = "ERROR: FLOOR_W_L\n";
char D_800ECCCC[] = "ERROR: CVT_W_L\n";
char D_800ECCDC[] = "ERROR: C.F_L\n";
char D_800ECCEC[] = "ERROR: C.UN_L\n";
char D_800ECCFC[] = "ERROR: C.EQ_L\n";
char D_800ECD0C[] = "ERROR: C.UEQ_L\n";
char D_800ECD1C[] = "ERROR: C.OLT_L\n";
char D_800ECD2C[] = "ERROR: C.ULT_L\n";
char D_800ECD3C[] = "ERROR: C.OLE_L\n";
char D_800ECD4C[] = "ERROR: C.ULE_L\n";
char D_800ECD5C[] = "ERROR: C.SF_L\n";
char D_800ECD6C[] = "ERROR: C.NGLE_L\n";
char D_800ECD80[] = "ERROR: C.SEQ_L\n";
char D_800ECD90[] = "ERROR: C.NGL_L\n";
char D_800ECDA0[] = "ERROR: C.LT_L\n";
char D_800ECDB0[] = "ERROR: C.NGE_L\n";
char D_800ECDC0[] = "ERROR: C.LE_L\n";
char D_800ECDD0[] = "ERROR: C.NGT_L\n";

void* jtbl_800ECDE0[64] = {
    &lbl_8005A1E0, &lbl_8005A204, &lbl_8005A228, &lbl_8005A24C, &lbl_8005A270, &lbl_8005A280, &lbl_8005A2A4,
    &lbl_8005A2B4, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_8005A2D8, &lbl_8005A2E8,
    &lbl_8005A2F8, &lbl_8005A308, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A318, &lbl_8005A464, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A578, &lbl_80067F34, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688,
    &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A688, &lbl_8005A588,
    &lbl_8005A598, &lbl_8005A5A8, &lbl_8005A5B8, &lbl_8005A5C8, &lbl_8005A5D8, &lbl_8005A5E8, &lbl_8005A5F8,
    &lbl_8005A608, &lbl_8005A618, &lbl_8005A628, &lbl_8005A638, &lbl_8005A648, &lbl_8005A658, &lbl_8005A668,
    &lbl_8005A678,
};

void* jtbl_800ECEE0[64] = {
    &lbl_80059DC0, &lbl_80059DE4, &lbl_80059E08, &lbl_80059E2C, &lbl_80059E50, &lbl_80059E60, &lbl_80059E84,
    &lbl_80059E94, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80059EB8, &lbl_80059EC8,
    &lbl_80059ED8, &lbl_80059EE8, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_80059EF8, &lbl_80059FD0, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A0A4, &lbl_80067F34, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4,
    &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A1B4, &lbl_8005A0B4,
    &lbl_8005A0C4, &lbl_8005A0D4, &lbl_8005A0E4, &lbl_8005A0F4, &lbl_8005A104, &lbl_8005A114, &lbl_8005A124,
    &lbl_8005A134, &lbl_8005A144, &lbl_8005A154, &lbl_8005A164, &lbl_8005A174, &lbl_8005A184, &lbl_8005A194,
    &lbl_8005A1A4,
};

void* jtbl_800ECFE0[64] = {
    &lbl_80054BD4, &lbl_80054EF0, &lbl_80055204, &lbl_80055520, &lbl_80055834, &lbl_800559F0, &lbl_80055BC8,
    &lbl_80055C54, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80055E2C, &lbl_80055FEC,
    &lbl_800561AC, &lbl_8005637C, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_8005654C, &lbl_800565DC, &lbl_80059D94,
    &lbl_80059D94, &lbl_800565EC, &lbl_80067F34, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94,
    &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_80059D94, &lbl_800567AC,
    &lbl_80056854, &lbl_800568FC, &lbl_80056CE4, &lbl_800570CC, &lbl_800574B8, &lbl_800578A4, &lbl_80057CC4,
    &lbl_800580E4, &lbl_8005818C, &lbl_800585AC, &lbl_80058994, &lbl_80058D7C, &lbl_80059168, &lbl_80059554,
    &lbl_80059974,
};

void* jtbl_800ED0E0[64] = {
    &lbl_8004F91C, &lbl_8004FC44, &lbl_8004FF64, &lbl_8005028C, &lbl_800505AC, &lbl_80050770, &lbl_80050950,
    &lbl_800509E4, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80050BC4, &lbl_80050D88,
    &lbl_80050F4C, &lbl_80051120, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_800512F4, &lbl_80051304, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80051394, &lbl_80067F34, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8,
    &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80054BA8, &lbl_80051558,
    &lbl_80051600, &lbl_800516A8, &lbl_80051A98, &lbl_80051E88, &lbl_8005227C, &lbl_80052670, &lbl_80052A98,
    &lbl_80052EC0, &lbl_80052F68, &lbl_80053390, &lbl_80053780, &lbl_80053B70, &lbl_80053F64, &lbl_80054358,
    &lbl_80054780,
};

void* jtbl_800ED1E0[7] = {
    &lbl_8004E8E8, &lbl_8004EA44, &lbl_8004EBC0, &lbl_8004F0A8, &lbl_8004ECB0, &lbl_8004EE70, &lbl_8004EFE4,
};

void* jtbl_800ED1FC[25] = {
    &lbl_8004E810, &lbl_80067F34, &lbl_80067F34, &lbl_8004E810, &lbl_8004E810, &lbl_80067F34, &lbl_8004E810,
    &lbl_8004E810, &lbl_80067F34, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810,
    &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_8004E810,
    &lbl_8004E810, &lbl_8004E810, &lbl_8004E810, &lbl_80067F34,
};

void* jtbl_800ED260[20] = {
    &lbl_800496CC, &lbl_80049998, &lbl_80049C64, &lbl_80049F5C, &lbl_8004B55C, &lbl_8004B55C, &lbl_8004B55C,
    &lbl_8004B55C, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_8004B55C,
    &lbl_80067F34, &lbl_8004B55C, &lbl_8004A254, &lbl_8004A700, &lbl_8004ABAC, &lbl_8004B084,
};

void* jtbl_800ED2B0[64] = {
    &lbl_8003F290, &lbl_800496A0, &lbl_8003F524, &lbl_8003F780, &lbl_8003F9D0, &lbl_800496A0, &lbl_8003FDBC,
    &lbl_800401A8, &lbl_80040594, &lbl_800407BC, &lbl_800496A0, &lbl_800496A0, &lbl_80067F34, &lbl_80067F34,
    &lbl_800496A0, &lbl_80067F34, &lbl_80040D64, &lbl_80040F68, &lbl_80041154, &lbl_80041358, &lbl_80041544,
    &lbl_800496A0, &lbl_8004180C, &lbl_80041AD4, &lbl_80041D9C, &lbl_80041F68, &lbl_80042134, &lbl_80042330,
    &lbl_8004252C, &lbl_80042B04, &lbl_80042F8C, &lbl_80043564, &lbl_800439EC, &lbl_80044464, &lbl_80044EDC,
    &lbl_800452C8, &lbl_800456B4, &lbl_80045AA0, &lbl_80046518, &lbl_80046904, &lbl_800496A0, &lbl_800496A0,
    &lbl_80046CF0, &lbl_80047164, &lbl_800475DC, &lbl_800479F4, &lbl_80047E0C, &lbl_80048224, &lbl_80067F34,
    &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_80067F34, &lbl_800496A0, &lbl_80067F34, &lbl_800496A0,
    &lbl_8004863C, &lbl_800496A0, &lbl_800488E0, &lbl_80048B8C, &lbl_80048E2C, &lbl_800496A0, &lbl_800490FC,
    &lbl_800493D4,
};

void* jtbl_800ED3B0[64] = {
    &lbl_8003F268, &lbl_800496A8, &lbl_8004B564, &lbl_8004B80C, &lbl_8004BD30, &lbl_8004C2FC, &lbl_8004C730,
    &lbl_8004C9FC, &lbl_8004CCC8, &lbl_8004D2D4, &lbl_8004D900, &lbl_8004DC14, &lbl_8004DF58, &lbl_8004E1A0,
    &lbl_8004E430, &lbl_8004E69C, &lbl_8004E7EC, &lbl_8004E8B0, &lbl_8005A690, &lbl_8005A698, &lbl_8005A6A0,
    &lbl_8005ABFC, &lbl_8005B05C, &lbl_8005B354, &lbl_8005B64C, &lbl_8005BAE8, &lbl_8005BFBC, &lbl_8005BFDC,
    &lbl_80067F30, &lbl_80067F30, &lbl_80067F30, &lbl_8005BF84, &lbl_8005C01C, &lbl_8005CC14, &lbl_8005D80C,
    &lbl_8005DBF4, &lbl_8005E9B0, &lbl_8005F568, &lbl_80060120, &lbl_8005BFFC, &lbl_80060508, &lbl_80061264,
    &lbl_80061FC0, &lbl_800622F4, &lbl_80067F34, &lbl_80067F34, &lbl_8006342C, &lbl_8006375C, &lbl_80063790,
    &lbl_800637B0, &lbl_80067F30, &lbl_80067F30, &lbl_80064660, &lbl_80064680, &lbl_80067F30, &lbl_80065444,
    &lbl_80067F34, &lbl_80065A94, &lbl_80067F30, &lbl_80067F30, &lbl_800669E0, &lbl_80066A00, &lbl_80067F30,
    &lbl_800678FC,
};

#ifndef NON_MATCHING
// cpuCheckDelaySlot
void* jtbl_800ED4B0[25] = {
    &lbl_800682F0, &lbl_80068360, &lbl_80068360, &lbl_800682F0, &lbl_800682F0, &lbl_80068360, &lbl_800682F0,
    &lbl_800682F0, &lbl_80068360, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0,
    &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_800682F0,
    &lbl_800682F0, &lbl_800682F0, &lbl_800682F0, &lbl_80068360,
};
#else
void* jtbl_800ED4B0[25] = {0};
#endif

#ifndef NON_MATCHING
// cpuCheckDelaySlot
void* jtbl_800ED514[24] = {
    &lbl_80068270, &lbl_8006829C, &lbl_8006834C, &lbl_80068354, &lbl_8006835C, &lbl_8006835C,
    &lbl_8006835C, &lbl_8006835C, &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_80068360,
    &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_80068360, &lbl_800682CC, &lbl_80068320,
    &lbl_80068360, &lbl_80068360, &lbl_8006835C, &lbl_8006835C, &lbl_8006835C, &lbl_8006835C,
};
#else
void* jtbl_800ED514[24] = {0};
#endif

#ifndef NON_MATCHING
// cpuGetRegisterCP0
void* jtbl_800ED574[32] = {
    &lbl_8003551C, &lbl_800352F8, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C,
    &lbl_800354A4, &lbl_800354B4, &lbl_8003548C, &lbl_8003551C, &lbl_80035494, &lbl_8003551C, &lbl_8003551C,
    &lbl_8003549C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003551C,
    &lbl_800354BC, &lbl_800354CC, &lbl_800354DC, &lbl_800354EC, &lbl_800354FC, &lbl_8003551C, &lbl_8003551C,
    &lbl_8003551C, &lbl_8003551C, &lbl_8003551C, &lbl_8003550C,
};
#else
void* jtbl_800ED574[32] = {0};
#endif

#ifndef NON_MATCHING
// cpuSetRegisterCP0
void* jtbl_800ED5F4[32] = {
    &lbl_800356F4, &lbl_800356F8, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4,
    &lbl_800356F8, &lbl_800356F8, &lbl_800355BC, &lbl_800356F4, &lbl_800355C4, &lbl_8003562C, &lbl_80035654,
    &lbl_800356CC, &lbl_800356F8, &lbl_800356D4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F4,
    &lbl_800356F8, &lbl_800356F8, &lbl_800356F8, &lbl_800356F8, &lbl_800356F8, &lbl_800356F4, &lbl_800356F8,
    &lbl_800356F4, &lbl_800356F4, &lbl_800356F4, &lbl_800356F8,
};
#else
void* jtbl_800ED5F4[32] = {0};
#endif

char D_800ED674[] = "Exception: #### INTERNAL ERROR #### Cannot match exception-handler!";

u32 aHeapTreeFlag[125];

static char D_8013522C[] = "CFZE";
static char D_80135234[] = "NYLJ";
static char D_8013523C[] = "NM3E";
static char D_80135244[] = "CLBE";
static char D_8013524C[] = "NN6J";
static char D_80135254[] = "NN6E";
static char D_8013525C[] = "";
static char D_80135260[] = "cpu.c";

static void* gHeapTree;

static s32 cpuCompile_DSLLV_function;
static s32 cpuCompile_DSRLV_function;
static s32 cpuCompile_DSRAV_function;
static s32 cpuCompile_DMULT_function;
static s32 cpuCompile_DMULTU_function;
static s32 cpuCompile_DDIV_function;
static s32 cpuCompile_DDIVU_function;
static s32 cpuCompile_DADD_function;
static s32 cpuCompile_DADDU_function;
static s32 cpuCompile_DSUB_function;
static s32 cpuCompile_DSUBU_function;
static s32 cpuCompile_S_SQRT_function;
static s32 cpuCompile_D_SQRT_function;
static s32 cpuCompile_W_CVT_SD_function;
static s32 cpuCompile_L_CVT_SD_function;
static s32 cpuCompile_CEIL_W_function;
static s32 cpuCompile_FLOOR_W_function;
static s32 cpuCompile_ROUND_W_function;
static s32 cpuCompile_TRUNC_W_function;
static s32 cpuCompile_LB_function;
static s32 cpuCompile_LH_function;
static s32 cpuCompile_LW_function;
static s32 cpuCompile_LBU_function;
static s32 cpuCompile_LHU_function;
static s32 cpuCompile_SB_function;
static s32 cpuCompile_SH_function;
static s32 cpuCompile_SW_function;
static s32 cpuCompile_LDC_function;
static s32 cpuCompile_SDC_function;
static s32 cpuCompile_LWL_function;
static s32 cpuCompile_LWR_function;

const f64 D_80135FA0 = 0.0;
const f64 D_80135FA8 = 0.5;
const f64 D_80135FB0 = 3.0;
const f32 D_80135FB8 = 0.5f;
const f64 D_80135FC0 = 4503601774854144.0;

static bool cpuCompile_DSLLV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 16;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CA53830; // slw     r5,r5,r7
    compile[count++] = 0x7CC84C30; // srw     r8,r6,r9
    compile[count++] = 0x7CA54378; // or      r5,r5,r8
    compile[count++] = 0x3927FFE0; // addi    r9,r7,-32
    compile[count++] = 0x7CC84830; // slw     r8,r6,r9
    compile[count++] = 0x7CA54378; // or      r5,r5,r8
    compile[count++] = 0x7CC63830; // slw     r6,r6,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DSRLV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 16;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CC63C30; // srw     r6,r6,r7
    compile[count++] = 0x7CA84830; // slw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x3927FFE0; // addi    r9,r7,-32
    compile[count++] = 0x7CA84C30; // srw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x7CA53C30; // srw     r5,r5,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DSRAV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 17;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE8; // stwu    r1,-24(r1)
    compile[count++] = 0x70E7003F; // andi.   r7,r7,63
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x21270020; // subfic  r9,r7,32
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x7CC63C30; // srw     r6,r6,r7
    compile[count++] = 0x7CA84830; // slw     r8,r5,r9
    compile[count++] = 0x7CC64378; // or      r6,r6,r8
    compile[count++] = 0x3527FFE0; // addic.  r9,r7,-32
    compile[count++] = 0x7CA84E30; // sraw    r8,r5,r9
    compile[count++] = 0x40810008; // ble-    0x8
    compile[count++] = 0x61060000; // ori     r6,r8,0
    compile[count++] = 0x7CA53E30; // sraw    r5,r5,r7
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x38210018; // addi    r1,r1,24
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DMULT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 53;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x39200000; // li      r9,0
    compile[count++] = 0x39400000; // li      r10,0
    compile[count++] = 0x39800040; // li      r12,64
    compile[count++] = 0x39600001; // li      r11,1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7CC630F8; // not     r6,r6
    compile[count++] = 0x7CA528F8; // not     r5,r5
    compile[count++] = 0x7CC65814; // addc    r6,r6,r11
    compile[count++] = 0x7CA54914; // adde    r5,r5,r9
    compile[count++] = 0x2C070000; // cmpwi   r7,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7CE738F8; // not     r7,r7
    compile[count++] = 0x7D085814; // addc    r8,r8,r11
    compile[count++] = 0x7CE74914; // adde    r7,r7,r9
    compile[count++] = 0x710B0001; // andi.   r11,r8,1
    compile[count++] = 0x41820018; // beq-    0x18
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x7D4A3014; // addc    r10,r10,r6
    compile[count++] = 0x7D292914; // adde    r9,r9,r5
    compile[count++] = 0x7D6B5914; // adde    r11,r11,r11
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x5508F87E; // srwi    r8,r8,1
    compile[count++] = 0x50E8F800; // rlwimi  r8,r7,31,0,0
    compile[count++] = 0x54E7F87E; // srwi    r7,r7,1
    compile[count++] = 0x5147F800; // rlwimi  r7,r10,31,0,0
    compile[count++] = 0x554AF87E; // srwi    r10,r10,1
    compile[count++] = 0x512AF800; // rlwimi  r10,r9,31,0,0
    compile[count++] = 0x5529F87E; // srwi    r9,r9,1
    compile[count++] = 0x5169F800; // rlwimi  r9,r11,31,0,0
    compile[count++] = 0x556BF87E; // srwi    r11,r11,1
    compile[count++] = 0x398CFFFF; // addi    r12,r12,-1
    compile[count++] = 0x2C0C0000; // cmpwi   r12,0
    compile[count++] = 0x4082FFB4; // bne+    0xFFFFFFB4
    compile[count++] = 0x39600001; // li      r11,1
    compile[count++] = 0x7DCE7A78; // xor     r14,r14,r15
    compile[count++] = 0x2C0E0000; // cmpwi   r14,0
    compile[count++] = 0x40800024; // bge-    0x24
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7CE738F8; // not     r7,r7
    compile[count++] = 0x7D4A50F8; // not     r10,r10
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D085814; // addc    r8,r8,r11
    compile[count++] = 0x7CE76114; // adde    r7,r7,r12
    compile[count++] = 0x7D4A6114; // adde    r10,r10,r12
    compile[count++] = 0x7D296114; // adde    r9,r9,r12
    compile[count++] = 0x91030004 + OFFSETOF(pCPU, nLo); // stw     r8,4(r3)
    compile[count++] = 0x90E30000 + OFFSETOF(pCPU, nLo); // stw     r7,0(r3)
    compile[count++] = 0x91430004 + OFFSETOF(pCPU, nHi); // stw     r10,4(r3)
    compile[count++] = 0x91230000 + OFFSETOF(pCPU, nHi); // stw     r9,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DMULTU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 28;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x39200000; // li      r9,0
    compile[count++] = 0x39400000; // li      r10,0
    compile[count++] = 0x39800040; // li      r12,64
    compile[count++] = 0x710B0001; // andi.   r11,r8,1
    compile[count++] = 0x41820018; // beq-    0x18
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x7D4A3014; // addc    r10,r10,r6
    compile[count++] = 0x7D292914; // adde    r9,r9,r5
    compile[count++] = 0x7D6B5914; // adde    r11,r11,r11
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x39600000; // li      r11,0
    compile[count++] = 0x5508F87E; // srwi    r8,r8,1
    compile[count++] = 0x50E8F800; // rlwimi  r8,r7,31,0,0
    compile[count++] = 0x54E7F87E; // srwi    r7,r7,1
    compile[count++] = 0x5147F800; // rlwimi  r7,r10,31,0,0
    compile[count++] = 0x554AF87E; // srwi    r10,r10,1
    compile[count++] = 0x512AF800; // rlwimi  r10,r9,31,0,0
    compile[count++] = 0x5529F87E; // srwi    r9,r9,1
    compile[count++] = 0x5169F800; // rlwimi  r9,r11,31,0,0
    compile[count++] = 0x556BF87E; // srwi    r11,r11,1
    compile[count++] = 0x398CFFFF; // addi    r12,r12,-1
    compile[count++] = 0x2C0C0000; // cmpwi   r12,0
    compile[count++] = 0x4082FFB4; // bne+    0xFFFFFFB4
    compile[count++] = 0x91030004 + OFFSETOF(pCPU, nLo); // stw     r8,4(r3)
    compile[count++] = 0x90E30000 + OFFSETOF(pCPU, nLo); // stw     r7,0(r3)
    compile[count++] = 0x91430004 + OFFSETOF(pCPU, nHi); // stw     r10,4(r3)
    compile[count++] = 0x91230000 + OFFSETOF(pCPU, nHi); // stw     r9,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DDIV(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 64;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38A00040; // li      r5,64
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x38E00000; // li      r7,0
    compile[count++] = 0x39800001; // li      r12,1
    compile[count++] = 0x2C080000; // cmpwi   r8,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7D296014; // addc    r9,r9,r12
    compile[count++] = 0x7D083114; // adde    r8,r8,r6
    compile[count++] = 0x2C0A0000; // cmpwi   r10,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D6B58F8; // not     r11,r11
    compile[count++] = 0x7D4A50F8; // not     r10,r10
    compile[count++] = 0x7D6B6014; // addc    r11,r11,r12
    compile[count++] = 0x7D4A3114; // adde    r10,r10,r6
    compile[count++] = 0x3D80FFFF; // lis     r12,-1
    compile[count++] = 0x618CFFFE; // ori     r12,r12,65534
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180002C; // blt-    0x2C
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CEB3810; // subfc   r7,r11,r7
    compile[count++] = 0x7CCA3110; // subfe   r6,r10,r6
    compile[count++] = 0x42800028; // bc      20,lt,0x28
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x61290001; // ori     r9,r9,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x7D296038; // and     r9,r9,r12
    compile[count++] = 0x38A5FFFF; // addi    r5,r5,-1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x4082FF90; // bne+    0xFFFFFF90
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4080000C; // bge-    0xC
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x39800001; // li      r12,1
    compile[count++] = 0x7DCE7A78; // xor     r14,r14,r15
    compile[count++] = 0x2C0E0000; // cmpwi   r14,0
    compile[count++] = 0x40800014; // bge-    0x14
    compile[count++] = 0x7D2948F8; // not     r9,r9
    compile[count++] = 0x7D0840F8; // not     r8,r8
    compile[count++] = 0x7D296014; // addc    r9,r9,r12
    compile[count++] = 0x7D082914; // adde    r8,r8,r5
    compile[count++] = 0x91030000 + OFFSETOF(pCPU, nLo); // stw     r8,0(r3)
    compile[count++] = 0x91230004 + OFFSETOF(pCPU, nLo); // stw     r9,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, nHi); // stw     r6,0(r3)
    compile[count++] = 0x90E30004 + OFFSETOF(pCPU, nHi); // stw     r7,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_DDIVU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 43;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38A00040; // li      r5,64
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x38E00000; // li      r7,0
    compile[count++] = 0x3D80FFFF; // lis     r12,-1
    compile[count++] = 0x618CFFFE; // ori     r12,r12,65534
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180002C; // blt-    0x2C
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CEB3810; // subfc   r7,r11,r7
    compile[count++] = 0x7CCA3110; // subfe   r6,r10,r6
    compile[count++] = 0x42800028; // bc      20,lt,0x28
    compile[count++] = 0x54C6083C; // slwi    r6,r6,1
    compile[count++] = 0x50E60FFE; // rlwimi  r6,r7,1,31,31
    compile[count++] = 0x54E7083C; // slwi    r7,r7,1
    compile[count++] = 0x51070FFE; // rlwimi  r7,r8,1,31,31
    compile[count++] = 0x5508083C; // slwi    r8,r8,1
    compile[count++] = 0x51280FFE; // rlwimi  r8,r9,1,31,31
    compile[count++] = 0x5529083C; // slwi    r9,r9,1
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x61290001; // ori     r9,r9,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x7D296038; // and     r9,r9,r12
    compile[count++] = 0x38A5FFFF; // addi    r5,r5,-1
    compile[count++] = 0x2C050000; // cmpwi   r5,0
    compile[count++] = 0x4082FF90; // bne+    0xFFFFFF90
    compile[count++] = 0x2C060000; // cmpwi   r6,0
    compile[count++] = 0x4080000C; // bge-    0xC
    compile[count++] = 0x7CE75814; // addc    r7,r7,r11
    compile[count++] = 0x7CC65114; // adde    r6,r6,r10
    compile[count++] = 0x91030000 + OFFSETOF(pCPU, nLo); // stw     r8,0(r3)
    compile[count++] = 0x91230004 + OFFSETOF(pCPU, nLo); // stw     r9,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, nHi); // stw     r6,0(r3)
    compile[count++] = 0x90E30004 + OFFSETOF(pCPU, nHi); // stw     r7,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DADD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA53814; // addc    r5,r5,r7
    compile[count++] = 0x7CC64114; // adde    r6,r6,r8
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DADDU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA53814; // addc    r5,r5,r7
    compile[count++] = 0x7CC64114; // adde    r6,r6,r8
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DSUB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA72914; // adde    r5,r7,r5
    compile[count++] = 0x7CC83014; // addc    r6,r8,r6
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_DSUBU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x7CA72914; // adde    r5,r7,r5
    compile[count++] = 0x7CC83014; // addc    r6,r8,r6
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_S_SQRT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 36;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xC0030000 + (OFFSETOF(pCPU, aGPR) + 4); // lfs     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x40810078; // ble-    0x78
    compile[count++] = 0xFC400834; // frsqrte f2,f1
    compile[count++] = 0x3CA03FE0; // lis     r5,16352
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8830000 + OFFSETOF(pCPU, aGPR); // lfd     f4,0(r3)
    compile[count++] = 0x3CA04008; // lis     r5,16392
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8630000 + OFFSETOF(pCPU, aGPR); // lfd     f3,0(r3)
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCA400B2; // fmul    f5,f4,f2
    compile[count++] = 0xFCC200B2; // fmul    f6,f2,f2
    compile[count++] = 0xFCC101B2; // fmul    f6,f1,f6
    compile[count++] = 0xFCC33028; // fsub    f6,f3,f6
    compile[count++] = 0xFC4501B2; // fmul    f2,f5,f6
    compile[count++] = 0xFCC100B2; // fmul    f6,f1,f2
    compile[count++] = 0xFC203018; // frsp    f1,f6
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30000 + (OFFSETOF(pCPU, aGPR) + 4); // stw     r5,0(r3)
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_D_SQRT(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 48;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xC8030000 + OFFSETOF(pCPU, aGPR); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x40810068; // ble-    0x68
    compile[count++] = 0xFC400834; // frsqrte f2,f1
    compile[count++] = 0x3CA03FE0; // lis     r5,16352
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8830000 + OFFSETOF(pCPU, aGPR); // lfd     f4,0(r3)
    compile[count++] = 0x3CA04008; // lis     r5,16392
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC8630000 + OFFSETOF(pCPU, aGPR); // lfd     f3,0(r3)
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC420032; // fmul    f2,f2,f0
    compile[count++] = 0xFC0200B2; // fmul    f0,f2,f2
    compile[count++] = 0xFC4400B2; // fmul    f2,f4,f2
    compile[count++] = 0xFC01183C; // fnmsub  f0,f1,f0,f3
    compile[count++] = 0xFC020032; // fmul    f0,f2,f0
    compile[count++] = 0xFC210032; // fmul    f1,f1,f0
    compile[count++] = 0x42800044; // bc      20,lt,0x44
    compile[count++] = 0xFC010000; // fcmpu   cr0,f1,f0
    compile[count++] = 0x4082000C; // bne-    0xC
    compile[count++] = 0xFC200090; // fmr     f1,f0
    compile[count++] = 0x42800034; // bc      20,lt,0x34
    compile[count++] = 0xFC010000; // fcmpu   cr0,f1,f0
    compile[count++] = 0x41820020; // beq-    0x20
    compile[count++] = 0x3CA07FFF; // lis     r5,32767
    compile[count++] = 0x60A5FFFF; // ori     r5,r5,65535
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x3CA0E000; // lis     r5,-8192
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0xC0230000 + OFFSETOF(pCPU, aGPR); // lfs     f1,0(r3)
    compile[count++] = 0x42800010; // bc      20,lt,0x10
    compile[count++] = 0x3CA07FF0; // lis     r5,32752
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0xC0230000 + OFFSETOF(pCPU, aGPR); // lfs     f1,0(r3)
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_W_CVT_SD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 14;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x6CA58000; // xoris   r5,r5,32768
    compile[count++] = 0x3CC04330; // lis     r6,17200
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, aGPR); // stw     r6,0(r3)
    compile[count++] = 0xC8030000 + OFFSETOF(pCPU, aGPR); // lfd     f0,0(r3)
    compile[count++] = 0x90C30000 + OFFSETOF(pCPU, aGPR); // stw     r6,0(r3)
    compile[count++] = 0x3CA08000; // lis     r5,-32768
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0xC8230000 + OFFSETOF(pCPU, aGPR); // lfd     f1,0(r3)
    compile[count++] = 0xFC200828; // fsub    f1,f0,f1
    compile[count++] = 0x38A00000; // li      r5,0
    compile[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR); // stw     r5,0(r3)
    compile[count++] = 0x90A30004 + OFFSETOF(pCPU, aGPR); // stw     r5,4(r3)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_L_CVT_SD(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 56;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFD0; // stwu    r1,-48(r1)
    compile[count++] = 0x91010008; // stw     r8,8(r1)
    compile[count++] = 0x91210010; // stw     r9,16(r1)
    compile[count++] = 0x91410018; // stw     r10,24(r1)
    compile[count++] = 0x91610020; // stw     r11,32(r1)
    compile[count++] = 0x91810028; // stw     r12,40(r1)
    compile[count++] = 0x9421FFF0; // stwu    r1,-16(r1)
    compile[count++] = 0x54A70001; // clrrwi. r7,r5,31
    compile[count++] = 0x4182000C; // beq-    0xC
    compile[count++] = 0x20C60000; // subfic  r6,r6,0
    compile[count++] = 0x7CA50190; // subfze  r5,r5
    compile[count++] = 0x7CA93379; // or.     r9,r5,r6
    compile[count++] = 0x39000000; // li      r8,0
    compile[count++] = 0x41820080; // beq-    0x80
    compile[count++] = 0x7CA90034; // cntlzw  r9,r5
    compile[count++] = 0x7CCA0034; // cntlzw  r10,r6
    compile[count++] = 0x552BD008; // rlwinm  r11,r9,26,0,4
    compile[count++] = 0x7D6BFE70; // srawi   r11,r11,31
    compile[count++] = 0x7D6B5038; // and     r11,r11,r10
    compile[count++] = 0x7D295A14; // add     r9,r9,r11
    compile[count++] = 0x21490020; // subfic  r10,r9,32
    compile[count++] = 0x3169FFE0; // addic   r11,r9,-32
    compile[count++] = 0x7CA54830; // slw     r5,r5,r9
    compile[count++] = 0x7CCC5430; // srw     r12,r6,r10
    compile[count++] = 0x7CA56378; // or      r5,r5,r12
    compile[count++] = 0x7CCC5830; // slw     r12,r6,r11
    compile[count++] = 0x7CA56378; // or      r5,r5,r12
    compile[count++] = 0x7CC64830; // slw     r6,r6,r9
    compile[count++] = 0x7D094050; // subf    r8,r9,r8
    compile[count++] = 0x54C9057E; // clrlwi  r9,r6,21
    compile[count++] = 0x2C090400; // cmpwi   r9,1024
    compile[count++] = 0x3908043E; // addi    r8,r8,1086
    compile[count++] = 0x4180001C; // blt-    0x1C
    compile[count++] = 0x4181000C; // bgt-    0xC
    compile[count++] = 0x54C90529; // rlwinm. r9,r6,0,20,20
    compile[count++] = 0x41820010; // beq-    0x10
    compile[count++] = 0x30C60800; // addic   r6,r6,2048
    compile[count++] = 0x7CA50194; // addze   r5,r5
    compile[count++] = 0x7D080194; // addze   r8,r8
    compile[count++] = 0x54C6A83E; // rotlwi  r6,r6,21
    compile[count++] = 0x50A6A814; // rlwimi  r6,r5,21,0,10
    compile[count++] = 0x54A5AB3E; // rlwinm  r5,r5,21,12,31
    compile[count++] = 0x5508A016; // slwi    r8,r8,20
    compile[count++] = 0x7D052B78; // or      r5,r8,r5
    compile[count++] = 0x7CE52B78; // or      r5,r7,r5
    compile[count++] = 0x90A10008; // stw     r5,8(r1)
    compile[count++] = 0x90C1000C; // stw     r6,12(r1)
    compile[count++] = 0xC8210008; // lfd     f1,8(r1)
    compile[count++] = 0x38210010; // addi    r1,r1,16
    compile[count++] = 0x81010008; // lwz     r8,8(r1)
    compile[count++] = 0x81210010; // lwz     r9,16(r1)
    compile[count++] = 0x81410018; // lwz     r10,24(r1)
    compile[count++] = 0x81610020; // lwz     r11,32(r1)
    compile[count++] = 0x81810028; // lwz     r12,40(r1)
    compile[count++] = 0x38210030; // addi    r1,r1,48
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_CEIL_W(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 13;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE0; // stwu    r1,-32(r1)
    compile[count++] = 0xC8030000 + (OFFSETOF(pCPU, aFPR) & 0xFFFF); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x4081000C; // ble-    0xC
    compile[count++] = 0x38C00001; // li      r6,1
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0xFC20081E; // fctiwz  f1,f1
    compile[count++] = 0xD8210010; // stfd    f1,16(r1)
    compile[count++] = 0x80A10014; // lwz     r5,20(r1)
    compile[count++] = 0x7CA62A14; // add     r5,r6,r5
    compile[count++] = 0x38210020; // addi    r1,r1,32
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_FLOOR_W(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 13;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x9421FFE0; // stwu    r1,-32(r1)
    compile[count++] = 0xC8030000 + (OFFSETOF(pCPU, aFPR) & 0xFFFF); // lfd     f0,0(r3)
    compile[count++] = 0xFC010040; // fcmpo   cr0,f1,f0
    compile[count++] = 0x4180000C; // blt-    0xC
    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x42800008; // bc      20,lt,0x8
    compile[count++] = 0x38C00001; // li      r6,1
    compile[count++] = 0xFC20081E; // fctiwz  f1,f1
    compile[count++] = 0xD8210010; // stfd    f1,16(r1)
    compile[count++] = 0x80A10014; // lwz     r5,20(r1)
    compile[count++] = 0x7CA62850; // subf    r5,r6,r5
    compile[count++] = 0x38210020; // addi    r1,r1,32
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_ROUND_W(s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xFC00081C; // fctiw   f0,f1
    compile[count++] = 0x7C051FAE; // stfiwx  f0,r5,r3
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static inline bool cpuCompile_TRUNC_W(s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 3;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0xFC00081E; // fctiwz  f0,f1
    compile[count++] = 0x7C051FAE; // stfiwx  f0,r5,r3
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 11;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA538AE; // lbzx    r5,r5,r7
    compile[count++] = 0x7CA50774; // extsb   r5,r5
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LH(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 11;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA53A2E; // lhzx    r5,r5,r7
    compile[count++] = 0x7CA50734; // extsh   r5,r5
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LW(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA5382E; // lwzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LBU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA538AE; // lbzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LHU(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CA53A2E; // lhzx    r5,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SB(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D0539AE; // stbx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SH(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D053B2E; // sthx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SW(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 10;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7D05392E; // stwx    r8,r5,r7
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LDC(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CE53A14; // add     r7,r5,r7
    compile[count++] = 0x80A70000; // lwz     r5,0(r7)
    compile[count++] = 0x80C70004; // lwz     r6,4(r7)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_SDC(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x54C6103A; // slwi    r6,r6,2
    compile[count++] = 0x38E30000 + OFFSETOF(pCPU, apDevice); // addi    r7,r3,0
    compile[count++] = 0x7CC6382E; // lwzx    r6,r6,r7
    compile[count++] = 0x80E60008; // lwz     r7,8(r6)
    compile[count++] = 0x7CA53A14; // add     r5,r5,r7
    compile[count++] = 0x80E60004; // lwz     r7,4(r6)
    compile[count++] = 0x80E70004; // lwz     r7,4(r7)
    compile[count++] = 0x7CE53A14; // add     r7,r5,r7
    compile[count++] = 0x91070000; // stw     r8,0(r7)
    compile[count++] = 0x91270004; // stw     r9,4(r7)
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LWL(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38C00018; // li      r6,24
    compile[count++] = 0x88A70000; // lbz     r5,0(r7)
    compile[count++] = 0x7CA53030; // slw     r5,r5,r6
    compile[count++] = 0x394000FF; // li      r10,255
    compile[count++] = 0x7D4A3030; // slw     r10,r10,r6
    compile[count++] = 0x7D295078; // andc    r9,r9,r10
    compile[count++] = 0x7D292B78; // or      r9,r9,r5
    compile[count++] = 0x38C6FFF8; // addi    r6,r6,-8
    compile[count++] = 0x54E507BF; // clrlwi. r5,r7,30
    compile[count++] = 0x38E70001; // addi    r7,r7,1
    compile[count++] = 0x4082FFDC; // bne+    0xFFFFFFDC
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

static bool cpuCompile_LWR(Cpu* pCPU, s32* addressGCN) {
    s32* compile;
    s32 count = 0;
    s32 nSize = 12;

    if (!xlHeapTake((void**)&compile, (nSize * sizeof(s32)) | 0x30000000)) {
        return false;
    }
    *addressGCN = (s32)compile;

    compile[count++] = 0x38C00000; // li      r6,0
    compile[count++] = 0x88A70000; // lbz     r5,0(r7)
    compile[count++] = 0x7CA53030; // slw     r5,r5,r6
    compile[count++] = 0x394000FF; // li      r10,255
    compile[count++] = 0x7D4A3030; // slw     r10,r10,r6
    compile[count++] = 0x7D295078; // andc    r9,r9,r10
    compile[count++] = 0x7D292B78; // or      r9,r9,r5
    compile[count++] = 0x38C60008; // addi    r6,r6,8
    compile[count++] = 0x54E507BF; // clrlwi. r5,r7,30
    compile[count++] = 0x38E7FFFF; // addi    r7,r7,-1
    compile[count++] = 0x4082FFDC; // bne+    0xFFFFFFDC
    compile[count++] = 0x4E800020; // blr

    nSize = count;
    DCStoreRange(compile, nSize * sizeof(s32));
    ICInvalidateRange(compile, nSize * sizeof(s32));

    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuCheckDelaySlot.s")
#else
/**
 * @brief Checks the type of delay an instruction has.
 *
 * @param opcode The instruction to determine the delay type for.
 * @return s32 The type of delay the instruction has.
 */
static s32 cpuCheckDelaySlot(u32 opcode) {
    s32 flag = 0;

    if (opcode == 0) {
        return 0;
    }

    switch (MIPS_OP(opcode)) {
        case 0x00: // special
            switch (MIPS_FUNCT(opcode)) {
                case 0x08: // jr
                    flag = 0xD05;
                    break;
                case 0x09: // jalr
                    flag = 0x8AE;
                    break;
            }
            break;
        case 0x01: // regimm
            switch (MIPS_RT(opcode)) {
                case 0x00: // bltz
                case 0x01: // bgez
                case 0x02: // bltzl
                case 0x03: // bgezl
                case 0x10: // bltzal
                case 0x11: // bgezal
                case 0x12: // bltzall
                case 0x13: // bgezall
                    flag = 0x457;
                    break;
            }
            break;
        case 0x10: // cop0
            switch (MIPS_FUNCT(opcode)) {
                case 0x01:
                case 0x02:
                case 0x05:
                case 0x08:
                case 0x18:
                    break;
                default:
                case 0x00:
                case 0x03:
                case 0x04:
                case 0x06:
                case 0x07:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                    switch (MIPS_RS(opcode)) {
                        case 0x08:
                            switch (MIPS_RT(opcode)) {
                                case 0x00:
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                    flag = 0x457;
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 0x11: // cop1
            if (MIPS_RS(opcode) == 0x08) {
                switch (MIPS_RT(opcode)) {
                    case 0x00: // bc1f
                    case 0x01: // bc1t
                    case 0x02: // bc1fl
                    case 0x03: // bc1tl
                        flag = 0x457;
                        break;
                }
            }
            break;
        case 0x02: // j
            flag = 0xD05;
            break;
        case 0x03: // jal
            flag = 0x8AE;
            break;
        case 0x04: // beq
        case 0x05: // bne
        case 0x06: // blez
        case 0x07: // bgtz
        case 0x14: // beql
        case 0x15: // bnel
        case 0x16: // blezl
        case 0x17: // bgtzl
            flag = 0x457;
            break;
    }

    return flag;
}
#endif

/**
 * @brief Fills a code section of NOPs
 *
 * @param anCode Pointer to fill nops to.
 * @param iCode Position in @code to start filling.
 * @param number The amount of NOPs to fill.
 */
static inline void cpuCompileNOP(s32* anCode, s32* iCode, s32 number) {
    while (*iCode != number) {
        anCode[(*iCode)++] = 0x60000000;
    }
}

/**
 * @brief The main MIPS->PPC Dynamic recompiler.
 * Largely unfinished.
 *
 * @param pCPU The emulated VR4300.
 * @param pnAddress The address to recompile.
 * @param pFunction The function that is being recompiled.
 * @param anCode Pointer to the recompiled code.
 * @param piCode Pointer to the current position in the recompiled code.
 * @param bSlot true if we are recompiling a delay slot.
 * @return bool true on success, false otherwise.
 */
static bool cpuGetPPC(Cpu* pCPU, s32* pnAddress, CpuFunction* pFunction, s32* anCode, s32* piCode, bool bSlot);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetPPC.s")

/**
 * @brief Creates a new recompiled function block.
 *
 * @param pCPU The emulated VR4300.
 * @param ppFunction A pointer to an already recompiled function, or one that has been created.
 * @param nAddressN64 The N64 address of the function to find or create.
 * @return bool true on success, false otherwise.
 */
bool cpuMakeFunction(Cpu* pCPU, CpuFunction** ppFunction, s32 nAddressN64) {
    s32 iCode;
    s32 iCode0;
    s32 pad;
    s32 iJump;
    s32 iCheck;
    s32 firstTime;
    s32 kill_value;
    s32 memory_used;
    s32 codeMemory;
    s32 blockMemory;
    s32* chunkMemory;
    s32* anCode;
    s32 nAddress;
    CpuFunction* pFunction;
    CpuJump aJump[1024];

    firstTime = 1;
    if (!cpuFindFunction(pCPU, nAddressN64, &pFunction)) {
        return false;
    }

    if (pFunction->pfCode == NULL) {
        libraryTestFunction(SYSTEM_LIBRARY(pCPU->pHost), pFunction);
        pFunction->nCountJump = 0;
        pFunction->aJump = aJump;
        pCPU->nFlagRAM = 0x20000000;
        pCPU->nFlagCODE = 0;
        pFunction->callerID_total = 0;
        pFunction->callerID_flag = 0xB;
        pCPU->nOptimize.validCheck = 1;
        pCPU->nOptimize.checkNext = 0;

        iCode = 0;
        nAddress = pFunction->nAddress0;
        while (nAddress <= pFunction->nAddress1) {
            if (!cpuGetPPC(pCPU, &nAddress, pFunction, NULL, &iCode, false)) {
                return false;
            }
        }

        iCode0 = iCode;
        codeMemory = iCode * sizeof(s32);
        memory_used = codeMemory;

        iCheck = pFunction->callerID_total;
        if (iCheck != 0) {
            blockMemory = iCheck * sizeof(CpuCallerID);
            memory_used += blockMemory;
        } else {
            blockMemory = 0;
        }

        if (pFunction->nCountJump > 0) {
            memory_used += pFunction->nCountJump * sizeof(CpuJump);
        }

        while (true) {
            if (cpuHeapTake(&chunkMemory, pCPU, pFunction, memory_used)) {
                break;
            }

            if (firstTime) {
                firstTime = 0;
                kill_value = pCPU->survivalTimer - 300;
            } else {
                kill_value += 95;
                if (kill_value > pCPU->survivalTimer - 10) {
                    kill_value = pCPU->survivalTimer - 10;
                }
            }

            treeForceCleanUp(pCPU, pFunction, kill_value);
        }

        anCode = chunkMemory;
        if (blockMemory != 0) {
            pFunction->block = (CpuCallerID*)((u8*)chunkMemory + codeMemory);
            treeCallerInit(pFunction->block, iCheck);
        }

        pCPU->nFlagRAM = 0x20000000;
        pCPU->nFlagCODE = 0;
        pFunction->callerID_total = 0;
        pFunction->callerID_flag = 0x16;
        pCPU->nOptimize.checkNext = 0;
        pCPU->nOptimize.destGPR_check = 0;
        pCPU->nOptimize.destFPR_check = 0;

        iCode = 0;
        nAddress = pFunction->nAddress0;
        while (nAddress <= pFunction->nAddress1) {
            if (!cpuGetPPC(pCPU, &nAddress, pFunction, anCode, &iCode, false)) {
                return false;
            }
        }
        cpuCompileNOP(anCode, &iCode, iCode0);

        pFunction->callerID_flag = 0x21;
        pFunction->pfCode = anCode;
        DCStoreRange(pFunction->pfCode, iCode * 4);
        ICInvalidateRange(pFunction->pfCode, iCode * 4);

        if (pFunction->nCountJump > 0) {
            if (pFunction->nCountJump >= 0x400) {
                return false;
            }

            pFunction->aJump = (CpuJump*)((u8*)chunkMemory + codeMemory + blockMemory);
            for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
                pFunction->aJump[iJump].nOffsetHost = aJump[iJump].nOffsetHost;
                pFunction->aJump[iJump].nAddressN64 = aJump[iJump].nAddressN64;
            }
        } else {
            pFunction->aJump = NULL;
        }

        pFunction->memory_size = memory_used;
        pCPU->gTree->total_memory += memory_used;
    }

    if (ppFunction != NULL) {
        *ppFunction = pFunction;
    }

    return true;
}

/**
 * @brief Searches the recompiled block cache for an address, or creates a new block if one cannot be found.
 *
 * @param pCPU The emulated VR4300.
 * @param nAddressN64 N64 code address to search for.
 * @param pnAddressGCN A pointer to set the found PPC code to.
 * @return bool true on success, false otherwise.
 */
static bool cpuFindAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressGCN) {
    s32 iJump;
    s32 iCode;
    s32 nAddress;
    CpuFunction* pFunction;
    s32 pad;

    if (pCPU->nMode & 0x20) {
        pCPU->nMode &= ~0x20;
    }

    if (cpuFindCachedAddress(pCPU, nAddressN64, pnAddressGCN)) {
        return true;
    }

    if ((pFunction = pCPU->pFunctionLast) == NULL || nAddressN64 < pFunction->nAddress0 ||
        pFunction->nAddress1 < nAddressN64) {
        if (!cpuMakeFunction(pCPU, &pFunction, nAddressN64)) {
            return false;
        }
    }

    for (iJump = 0; iJump < pFunction->nCountJump; iJump++) {
        if (pFunction->aJump[iJump].nAddressN64 == nAddressN64) {
            *pnAddressGCN = (s32)((s32*)pFunction->pfCode + pFunction->aJump[iJump].nOffsetHost);
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }
            cpuMakeCachedAddress(pCPU, nAddressN64, *pnAddressGCN, pFunction);
            return true;
        }
    }

    pCPU->nFlagRAM = 0x20000000;
    pCPU->nFlagCODE = 0;
    pFunction->callerID_flag = 0x21;
    iCode = 0;
    if (pFunction->nAddress0 != nAddressN64) {
        pFunction->timeToLive = 0;
    }

    nAddress = pFunction->nAddress0;
    while (nAddress <= pFunction->nAddress1) {
        if (nAddress == nAddressN64) {
            *pnAddressGCN = (s32)((s32*)pFunction->pfCode + iCode);
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }
            cpuMakeCachedAddress(pCPU, nAddressN64, *pnAddressGCN, pFunction);
            return true;
        }
        if (!cpuGetPPC(pCPU, &nAddress, pFunction, NULL, &iCode, false)) {
            return false;
        }
    }

    return false;
}

static inline bool cpuNoBranchTo(CpuFunction* pFunction, s32 addressN64) {
    s32 i;

    for (i = 0; i < pFunction->nCountJump; i++) {
        if (pFunction->aJump[i].nAddressN64 == addressN64) {
            return false;
        }
    }

    return true;
}

static bool cpuNextInstruction(Cpu* pCPU, s32 addressN64, s32 opcode, s32* anCode, s32* iCode) {
    if (anCode == NULL) {
        return false;
    }
    if (pCPU->nOptimize.validCheck == 0) {
        return false;
    }
    if (pCPU->nOptimize.checkNext != addressN64 - 4) {
        pCPU->nOptimize.checkNext = 0;
        return false;
    }
    pCPU->nOptimize.checkNext = 0;

    if (!cpuNoBranchTo(pCPU->pFunctionLast, addressN64)) {
        return false;
    }

    switch (MIPS_OP(opcode)) {
        case 0x0D: // ori
            if (pCPU->nOptimize.destGPR == MIPS_RS(opcode) && MIPS_RS(opcode) == MIPS_RT(opcode)) {
                if (pCPU->nOptimize.checkType != 0x3E8) {
                    return false;
                }
                anCode[*iCode - 1] = 0x60000000;
                anCode[(*iCode)++] = 0x60000000 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                     (pCPU->nOptimize.destGPR_mapping << 16) | MIPS_IMM_U16(opcode);
                anCode[(*iCode)++] = 0x60000000;
                anCode[(*iCode)++] = (0x90030000 | (pCPU->nOptimize.destGPR_mapping << 21)) +
                                     (OFFSETOF(pCPU, aGPR[MIPS_RT(opcode)]) + 4);
                pCPU->nOptimize.destGPR_check = 2;
                return true;
            }
            return false;
        case 0x09: // addiu
            if (pCPU->nOptimize.destGPR == MIPS_RS(opcode) && MIPS_RS(opcode) == MIPS_RT(opcode)) {
                if (pCPU->nOptimize.checkType != 0x3E8) {
                    return false;
                }
                anCode[*iCode - 1] = 0x60000000;
                anCode[(*iCode)++] = 0x38000000 | (pCPU->nOptimize.destGPR_mapping << 21) |
                                     (pCPU->nOptimize.destGPR_mapping << 16) | MIPS_IMM_U16(opcode);
                anCode[(*iCode)++] = 0x60000000;
                anCode[(*iCode)++] = (0x90030000 | (pCPU->nOptimize.destGPR_mapping << 21)) +
                                     (OFFSETOF(pCPU, aGPR[MIPS_RT(opcode)]) + 4);
                pCPU->nOptimize.destGPR_check = 2;
                return true;
            }
            return false;
        default:
            OSReport(D_800EC94C, opcode, addressN64);
            OSPanic(D_800EC1E0, 3621, D_8013525C);
            break;
    }

    return false;
}

void cpuRetraceCallback(u32 nCount) { SYSTEM_CPU(gpSystem)->nRetrace = nCount; }

static bool cpuExecuteUpdate(Cpu* pCPU, s32* pnAddressGCN, u32 nCount) {
    RspUpdateMode eModeUpdate;
    System* pSystem;
    s32 nDelta;
    u32 nCounter;
    u32 nCompare;

    u32 nCounterDelta;
    CpuTreeRoot* root;

    pSystem = (System*)pCPU->pHost;

    if (!romUpdate(SYSTEM_ROM(pSystem))) {
        return false;
    }

    if (pSystem->eTypeROM == SRT_DRMARIO) {
        eModeUpdate = pSystem->bException ? RUM_NONE : RUM_IDLE;
    } else {
        eModeUpdate = ((pCPU->nMode & 0x80) && !pSystem->bException) ? RUM_IDLE : RUM_NONE;
    }
    if (!rspUpdate(SYSTEM_RSP(pSystem), eModeUpdate)) {
        return false;
    }

    root = pCPU->gTree;
    treeTimerCheck(pCPU);
    if (pCPU->nRetrace == pCPU->nRetraceUsed && root->kill_number < 12) {
        if (treeKillReason(pCPU, &root->kill_limit)) {
            pCPU->survivalTimer++;
        }
        if (root->kill_limit != 0) {
            treeCleanUp(pCPU, root);
        }
    }

    if (nCount > pCPU->nTickLast) {
        nCounterDelta = fTickScale * ((nCount - pCPU->nTickLast) << nTickMultiplier);
    } else {
        nCounterDelta = fTickScale * ((-1 - pCPU->nTickLast + nCount) << nTickMultiplier);
    }
    if ((pCPU->nMode & 0x40) && pCPU->nRetraceUsed != pCPU->nRetrace) {
        if (videoForceRetrace(SYSTEM_VIDEO(pSystem), true)) {
            nDelta = pCPU->nRetrace - pCPU->nRetraceUsed;
            if (nDelta < 0) {
                nDelta = -nDelta;
            }

            if (nDelta < 4) {
                pCPU->nRetraceUsed++;
            } else {
                pCPU->nRetraceUsed = ((Cpu*)pCPU)->nRetrace;
            }
        }
    }

    if (pCPU->nMode & 1) {
        nCounter = pCPU->anCP0[9];
        nCompare = pCPU->anCP0[11];
        if ((nCounter <= nCompare && nCounter + nCounterDelta >= nCompare) ||
            (nCounter >= nCompare && nCounter + nCounterDelta >= nCompare && nCounter + nCounterDelta < nCounter)) {
            pCPU->nMode &= ~1;
            xlObjectEvent(pCPU->pHost, 0x1000, (void*)3);
        }
    }
    pCPU->anCP0[9] += nCounterDelta;

    if ((pCPU->nMode & 8) && !(pCPU->nMode & 4) && gpSystem->bException) {
        if (!systemCheckInterrupts(gpSystem)) {
            return false;
        }
    }

    if (pCPU->nMode & 4) {
        pCPU->nMode &= ~0x84;
        if (!cpuFindAddress(pCPU, pCPU->nPC, pnAddressGCN)) {
            return false;
        }
    }
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
static s32 cpuExecuteOpcode(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteOpcode.s")
#else
static inline bool cpuCheckInterrupts(Cpu* pCPU) {
    System* pSystem;

    pSystem = (System*)pCPU->pHost;
    if (pSystem->bException) {
        if (!systemCheckInterrupts(pSystem)) {
            return false;
        }
    } else {
        videoForceRetrace(SYSTEM_VIDEO(pSystem), false);
    }

    return true;
}

static inline bool cpuTLBRandom(Cpu* pCPU) {
    s32 iEntry;
    s32 nCount;

    nCount = 0;
    for (iEntry = 0; iEntry < 48; iEntry++) {
        if (!(pCPU->aTLB[iEntry][2] & 2)) {
            nCount++;
        }
    }

    return nCount;
}

static inline bool cpuExecuteCacheInstruction(Cpu* pCPU) {
    s32* pBuffer;

    if (!cpuGetAddressBuffer(pCPU, (void**)&pBuffer, pCPU->nPC)) {
        return false;
    }
    pBuffer[-1] = 0;
    pBuffer -= (pCPU->nPC - pCPU->nCallLast) >> 2;
    pBuffer[0] = 0x03E00008;
    pBuffer[1] = 0;

    return true;
}

static s32 cpuExecuteOpcode(Cpu* pCPU, s32 nCount0, s32 nAddressN64, s32 nAddressGCN) {
    s32 pad1[2];
    u64 save;
    s32 restore;
    u32 nOpcode;
    u32* opcode;
    s32 pad2;
    CpuDevice** apDevice;
    u8* aiDevice;
    s32 iEntry;
    s32 nCount;
    s8 nData8;
    s16 nData16;
    s32 nData32;
    s64 nData64;
    s32 nAddress;
    CpuFunction* pFunction;
    s32 nTick;
    s32 pad3[3];

    restore = 0;
    nTick = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    aiDevice = pCPU->aiDevice;
    apDevice = pCPU->apDevice;

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), &opcode, nAddressN64, NULL);
    nOpcode = *opcode;
    pCPU->nPC = nAddressN64 + 4;
    if (nOpcode == 0xACBF011C) { // sw $ra,0x11C($a1)
        save = pCPU->aGPR[31].u64;
        restore = 1;
        pCPU->aGPR[31].s32 = pCPU->nReturnAddrLast;
    }

    switch (MIPS_OP(nOpcode)) {
        case 0x00: // special
            switch (MIPS_FUNCT(nOpcode)) {
                case 0x00: // sll
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32 << MIPS_SA(nOpcode);
                    break;
                case 0x02: // srl
                    pCPU->aGPR[MIPS_RD(nOpcode)].u32 = pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> MIPS_SA(nOpcode);
                    break;
                case 0x03: // sra
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32 >> MIPS_SA(nOpcode);
                    break;
                case 0x04: // sllv
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32
                                                       << (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                    break;
                case 0x06: // srlv
                    pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                        pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                    break;
                case 0x07: // srav
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RT(nOpcode)].s32 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s32 & 0x1F);
                    break;
                case 0x08: // jr
                    pCPU->nWaitPC = pCPU->aGPR[MIPS_RS(nOpcode)].u32;
                    break;
                case 0x09: // jalr
                    pCPU->nWaitPC = pCPU->aGPR[MIPS_RS(nOpcode)].u32;
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nPC + 4;
                    break;
                case 0x0C: // syscall
                    cpuException(pCPU, CEC_SYSCALL, 0);
                    break;
                case 0x0D: // break
                    cpuException(pCPU, CEC_BREAK, 0);
                    break;
                case 0x10: // mfhi
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nHi;
                    break;
                case 0x11: // mthi
                    pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s64;
                    break;
                case 0x12: // mflo
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->nLo;
                    break;
                case 0x13: // mtlo
                    pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64;
                    break;
                case 0x14: // dsllv
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64
                                                       << (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                    break;
                case 0x16: // dsrlv
                    pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                        pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                    break;
                case 0x17: // dsrav
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                        pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> (pCPU->aGPR[MIPS_RS(nOpcode)].s64 & 0x3F);
                    break;
                case 0x18: // mult
                    nData64 = (s64)pCPU->aGPR[MIPS_RS(nOpcode)].s32 * (s64)pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    pCPU->nLo = (s32)(nData64 & 0xFFFFFFFF);
                    pCPU->nHi = (s32)(nData64 >> 32);
                    break;
                case 0x19: // multu
                    nData64 = (u64)pCPU->aGPR[MIPS_RS(nOpcode)].u32 * (u64)pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                    pCPU->nLo = (s32)(nData64 & 0xFFFFFFFF);
                    pCPU->nHi = (s32)(nData64 >> 32);
                    break;
                case 0x1A: // div
                    if (pCPU->aGPR[MIPS_RT(nOpcode)].s32 != 0) {
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s32 / pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s32 % pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    }
                    break;
                case 0x1B: // divu
                    if (pCPU->aGPR[MIPS_RT(nOpcode)].u32 != 0) {
                        pCPU->nLo = (s32)(pCPU->aGPR[MIPS_RS(nOpcode)].u32 / pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                        pCPU->nHi = (s32)(pCPU->aGPR[MIPS_RS(nOpcode)].u32 % pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                    }
                    break;
                case 0x1C: // dmult
                    pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64 * pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                    pCPU->nHi = (pCPU->nLo < 0) ? -1 : 0;
                    break;
                case 0x1D: // dmultu
                    pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].u64 * pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                    pCPU->nHi = (pCPU->nLo < 0) ? -1 : 0;
                    break;
                case 0x1E: // ddiv
                    if (pCPU->aGPR[MIPS_RT(nOpcode)].s64 != 0) {
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].s64 / pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].s64 % pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                    }
                    break;
                case 0x1F: // ddivu
                    if (pCPU->aGPR[MIPS_RT(nOpcode)].u64 != 0) {
                        pCPU->nLo = pCPU->aGPR[MIPS_RS(nOpcode)].u64 / pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                        pCPU->nHi = pCPU->aGPR[MIPS_RS(nOpcode)].u64 % pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                    }
                    break;
                case 0x20: // add
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s32 + pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    break;
                case 0x21: // addu
                    pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].u32 + pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                    break;
                case 0x22: // sub
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s32 - pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    break;
                case 0x23: // subu
                    pCPU->aGPR[MIPS_RD(nOpcode)].u32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].u32 - pCPU->aGPR[MIPS_RT(nOpcode)].u32;
                    break;
                case 0x24: // and
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s32 & pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    break;
                case 0x25: // or
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s32 | pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    break;
                case 0x26: // xor
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s32 ^ pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                    break;
                case 0x27: // nor
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        ~(pCPU->aGPR[MIPS_RS(nOpcode)].s32 | pCPU->aGPR[MIPS_RT(nOpcode)].s32);
                    break;
                case 0x2A: // slt
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < pCPU->aGPR[MIPS_RT(nOpcode)].s32) ? 1 : 0;
                    break;
                case 0x2B: // sltu
                    pCPU->aGPR[MIPS_RD(nOpcode)].s32 =
                        (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < pCPU->aGPR[MIPS_RT(nOpcode)].u32) ? 1 : 0;
                    break;
                case 0x2C: // dadd
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s64 + pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                    break;
                case 0x2D: // daddu
                    pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].u64 + pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                    break;
                case 0x2E: // dsub
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].s64 - pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                    break;
                case 0x2F: // dsubu
                    pCPU->aGPR[MIPS_RD(nOpcode)].u64 =
                        pCPU->aGPR[MIPS_RS(nOpcode)].u64 - pCPU->aGPR[MIPS_RT(nOpcode)].u64;
                    break;
                case 0x30: // tge
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x31: // tgeu
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 >= pCPU->aGPR[MIPS_RT(nOpcode)].u32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x32: // tlt
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x33: // tltu
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < pCPU->aGPR[MIPS_RT(nOpcode)].u32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x34: // teq
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x36: // tne
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x38: // dsll
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 << MIPS_SA(nOpcode);
                    break;
                case 0x3A: // dsrl
                    pCPU->aGPR[MIPS_RD(nOpcode)].u64 = pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> MIPS_SA(nOpcode);
                    break;
                case 0x3B: // dsra
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> MIPS_SA(nOpcode);
                    break;
                case 0x3C: // dsll32
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 << (MIPS_SA(nOpcode) + 32);
                    break;
                case 0x3E: // dsrl32
                    pCPU->aGPR[MIPS_RD(nOpcode)].u64 = pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> (MIPS_SA(nOpcode) + 32);
                    break;
                case 0x3F: // dsra32
                    pCPU->aGPR[MIPS_RD(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64 >> (MIPS_SA(nOpcode) + 32);
                    break;
            }
            break;
        case 0x01: // regimm
            switch (MIPS_RT(nOpcode)) {
                case 0x00: // bltz
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    }
                    break;
                case 0x01: // bgez
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    }
                    break;
                case 0x02: // bltzl
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    } else {
                        pCPU->nMode |= 4;
                        pCPU->nPC += 4;
                    }
                    break;
                case 0x03: // bgezl
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    } else {
                        pCPU->nMode |= 4;
                        pCPU->nPC += 4;
                    }
                    break;
                case 0x08: // tgei
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x09: // tgeiu
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 >= MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x0A: // tlti
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x0B: // tltiu
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x0C: // teqi
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x0E: // tnei
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != MIPS_IMM_S16(nOpcode)) {
                        cpuException(pCPU, CEC_TRAP, 0);
                    }
                    break;
                case 0x10: // bltzal
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                        pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                        pCPU->nWaitPC = pCPU->nCallLast = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    }
                    break;
                case 0x11: // bgezal
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                        pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                        pCPU->nWaitPC = pCPU->nCallLast = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    }
                    break;
                case 0x12: // bltzall
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < 0) {
                        pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    } else {
                        pCPU->nMode |= 4;
                        pCPU->nPC = pCPU->nPC + 4;
                    }
                    break;
                case 0x13: // bgezall
                    if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 >= 0) {
                        pCPU->aGPR[31].s32 = pCPU->nPC + 4;
                        pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                    } else {
                        pCPU->nMode |= 4;
                        pCPU->nPC = pCPU->nPC + 4;
                    }
                    break;
            }
            break;
        case 0x02: // j
            pCPU->nWaitPC = (pCPU->nPC & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            if (pCPU->nWaitPC == pCPU->nPC - 4) {
                if (!cpuCheckInterrupts(pCPU)) {
                    return 0;
                }
            }
            break;
        case 0x03: // jal
            pCPU->aGPR[31].s32 = pCPU->nPC + 4;
            pCPU->nWaitPC = pCPU->nCallLast = (pCPU->nPC & 0xF0000000) | (MIPS_TARGET(nOpcode) << 2);
            cpuFindFunction(pCPU, pCPU->nWaitPC, &pFunction);
            break;
        case 0x04: // beq
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            }
            if (pCPU->nWaitPC == pCPU->nPC - 4) {
                if (!cpuCheckInterrupts(pCPU)) {
                    return 0;
                }
                break;
            }
            break;
        case 0x05: // bne
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            }
            break;
        case 0x06: // blez
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 <= 0) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            }
            break;
        case 0x07: // bgtz
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 > 0) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            }
            break;
        case 0x08: // addi
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            break;
        case 0x09: // addiu
            pCPU->aGPR[MIPS_RT(nOpcode)].u32 = pCPU->aGPR[MIPS_RS(nOpcode)].u32 + MIPS_IMM_S16(nOpcode);
            break;
        case 0x0A: // slti
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (pCPU->aGPR[MIPS_RS(nOpcode)].s32 < MIPS_IMM_S16(nOpcode)) ? 1 : 0;
            break;
        case 0x0B: // sltiu
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (pCPU->aGPR[MIPS_RS(nOpcode)].u32 < MIPS_IMM_S16(nOpcode)) ? 1 : 0;
            break;
        case 0x0C: // andi
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 & MIPS_IMM_U16(nOpcode);
            break;
        case 0x0D: // ori
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 | MIPS_IMM_U16(nOpcode);
            break;
        case 0x0E: // xori
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aGPR[MIPS_RS(nOpcode)].s32 ^ MIPS_IMM_U16(nOpcode);
            break;
        case 0x0F: // lui
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = MIPS_IMM_S16(nOpcode) << 16;
            break;
        case 0x10: // cop0
            switch (MIPS_FUNCT(nOpcode)) {
                case 0x01: // tlbr
                    iEntry = pCPU->anCP0[0] & 0x3F;
                    pCPU->anCP0[2] = pCPU->aTLB[iEntry][0];
                    pCPU->anCP0[3] = pCPU->aTLB[iEntry][1];
                    pCPU->anCP0[10] = pCPU->aTLB[iEntry][2];
                    pCPU->anCP0[5] = pCPU->aTLB[iEntry][3];
                    break;
                case 0x02: // tlbwi
                    iEntry = pCPU->anCP0[0] & 0x3F;
                    cpuSetTLB(pCPU, iEntry);
                    break;
                case 0x05: // tlbwr
                    iEntry = cpuTLBRandom(pCPU);
                    pCPU->anCP0[1] = iEntry;
                    cpuSetTLB(pCPU, iEntry);
                    break;
                case 0x08: // tlbp
                    pCPU->anCP0[0] |= 0x80000000;
                    for (iEntry = 0; iEntry < 48; iEntry++) {
                        if ((pCPU->aTLB[iEntry][0] & 2) && pCPU->aTLB[iEntry][2] == pCPU->anCP0[10]) {
                            pCPU->anCP0[0] = iEntry;
                            break;
                        }
                    }
                    break;
                case 0x18: // eret
                    if (pCPU->anCP0[12] & 4) {
                        pCPU->nPC = pCPU->anCP0[30];
                        pCPU->anCP0[12] &= ~4;
                    } else {
                        pCPU->nPC = pCPU->anCP0[14];
                        pCPU->anCP0[12] &= ~2;
                    }
                    pCPU->nMode |= 4;
                    pCPU->nMode |= 0x20;
                    break;
                default:
                    switch (MIPS_RS(nOpcode)) {
                        case 0x00: // mfc0
                            if (cpuGetRegisterCP0(pCPU, MIPS_RD(nOpcode), &nData64)) {
                                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64 & 0xFFFFFFFF;
                            }
                            break;
                        case 0x01: // dmfc0
                            if (cpuGetRegisterCP0(pCPU, MIPS_RD(nOpcode), &nData64)) {
                                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
                            }
                            break;
                        case 0x02:
                            break;
                        case 0x04: // mtc0
                            cpuSetRegisterCP0(pCPU, MIPS_RD(nOpcode), pCPU->aGPR[MIPS_RT(nOpcode)].u32);
                            break;
                        case 0x05: // dmtc0
                            cpuSetRegisterCP0(pCPU, MIPS_RD(nOpcode), pCPU->aGPR[MIPS_RT(nOpcode)].u64);
                            break;
                        case 0x08:
                            break;
                    }
                    break;
            }
            break;
        case 0x11: // cop1
            if ((nOpcode & 0x7FF) == 0 && MIPS_FMT(nOpcode) < 0x10) {
                switch ((u8)MIPS_FMT(nOpcode)) {
                    case 0x00: // mfc1
                        if (MIPS_FS(nOpcode) & 1) {
                            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode) - 1].u64 >> 32;
                        } else {
                            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                        }
                        break;
                    case 0x01: // dmfc1
                        pCPU->aGPR[MIPS_RT(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                        break;
                    case 0x02: // cfc1
                        pCPU->aGPR[MIPS_RT(nOpcode)].s32 = pCPU->anFCR[MIPS_FS(nOpcode)];
                        break;
                    case 0x04: // mtc1
                        if (MIPS_FS(nOpcode) & 1) {
                            pCPU->aFPR[MIPS_FS(nOpcode) - 1].s64 &= 0xFFFFFFFF;
                            pCPU->aFPR[MIPS_FS(nOpcode) - 1].s64 |= (u64)pCPU->aGPR[MIPS_RT(nOpcode)].u32 << 32;
                        } else {
                            pCPU->aFPR[MIPS_FS(nOpcode)].s32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        }
                        break;
                    case 0x05: // dmtc1
                        pCPU->aFPR[MIPS_FS(nOpcode)].s64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
                        break;
                    case 0x06: // ctc1
                        pCPU->anFCR[MIPS_FS(nOpcode)] = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
                        break;
                }
            } else if (MIPS_FMT(nOpcode) == 0x08) {
                switch (MIPS_FT(nOpcode)) {
                    case 0x00: // bc1f
                        if (!(pCPU->anFCR[31] & 0x800000)) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x01: // bc1t
                        if (pCPU->anFCR[31] & 0x800000) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        }
                        break;
                    case 0x02: // bc1fl
                        if (!(pCPU->anFCR[31] & 0x800000)) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC += 4;
                        }
                        break;
                    case 0x03: // bc1tl
                        if (pCPU->anFCR[31] & 0x800000) {
                            pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
                        } else {
                            pCPU->nMode |= 4;
                            pCPU->nPC += 4;
                        }
                        break;
                }
            } else {
                switch ((u8)MIPS_FMT(nOpcode)) {
                    case 0x10: // s
                        switch (MIPS_FUNCT(nOpcode)) {
                            case 0x00: // add.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f32 + pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                break;
                            case 0x01: // sub.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f32 - pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                break;
                            case 0x02: // mul.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f32 * pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                break;
                            case 0x03: // div.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f32 / pCPU->aFPR[MIPS_FT(nOpcode)].f32;
                                break;
                            case 0x04: // sqrt.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x05: // abs.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x06: // mov.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x07: // neg.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = -pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x08: // round.l.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32 + 0.5f;
                                break;
                            case 0x09: // trunc.l.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x0A: // ceil.l.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x0B: // floor.l.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x0C: // round.w.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32 + 0.5f;
                                break;
                            case 0x0D: // trunc.w.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x0E: // ceil.w.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x0F: // floor.w.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f32);
                                break;
                            case 0x20: // cvt.s.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x21: // cvt.d.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x24: // cvt.w.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x25: // cvt.l.s
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f32;
                                break;
                            case 0x30: // c.f.s
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x31: // c.un.s
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x32: // c.eq.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x33: // c.ueq.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x34: // c.olt.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x35: // c.ult.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x36: // c.ole.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x37: // c.ule.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x38: // c.sf.s
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x39: // c.ngle.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3A: // c.seq.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3B: // c.ngl.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 == pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3C: // c.lt.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3D: // c.nge.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 < pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3E: // c.le.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3F: // c.ngt.s
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f32 <= pCPU->aFPR[MIPS_FT(nOpcode)].f32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                        }
                        break;
                    case 0x11: // d
                        switch (MIPS_FUNCT(nOpcode)) {
                            case 0x00: // add.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f64 + pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                break;
                            case 0x01: // sub.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f64 - pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                break;
                            case 0x02: // mul.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f64 * pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                break;
                            case 0x03: // div.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].f64 / pCPU->aFPR[MIPS_FT(nOpcode)].f64;
                                break;
                            case 0x04: // sqrt.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x05: // abs.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x06: // mov.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x07: // neg.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = -pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x08: // round.l.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64 + 0.5f;
                                break;
                            case 0x09: // trunc.l.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x0A: // ceil.l.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x0B: // floor.l.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x0C: // round.w.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64 + 0.5f;
                                break;
                            case 0x0D: // trunc.w.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x0E: // ceil.w.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x0F: // floor.w.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].f64);
                                break;
                            case 0x20: // cvt.s.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x21: // cvt.d.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x24: // cvt.w.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x25: // cvt.l.d
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].f64;
                                break;
                            case 0x30: // c.f.d
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x31: // c.un.d
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x32: // c.eq.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x33: // c.ueq.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x34: // c.olt.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x35: // c.ult.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x36: // c.ole.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x37: // c.ule.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x38: // c.sf.d
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x39: // c.ngle.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3A: // c.seq.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3B: // c.ngl.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 == pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3C: // c.lt.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3D: // c.nge.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 < pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3E: // c.le.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3F: // c.ngt.d
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].f64 <= pCPU->aFPR[MIPS_FT(nOpcode)].f64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                        }
                        break;
                    case 0x14: // w
                        switch (MIPS_FUNCT(nOpcode)) {
                            case 0x00: // add.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s32 + pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                break;
                            case 0x01: // sub.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s32 - pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                break;
                            case 0x02: // mul.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s32 * pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                break;
                            case 0x03: // div.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s32 / pCPU->aFPR[MIPS_FT(nOpcode)].s32;
                                break;
                            case 0x04: // sqrt.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x05: // abs.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x06: // mov.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x07: // neg.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = -pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x08: // round.l.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x09: // trunc.l.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x0A: // ceil.l.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x0B: // floor.l.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x0C: // round.w.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x0D: // trunc.w.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x0E: // ceil.w.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x0F: // floor.w.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s32);
                                break;
                            case 0x20: // cvt.s.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x21: // cvt.d.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x24: // cvt.w.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x25: // cvt.l.w
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s32;
                                break;
                            case 0x30: // c.f.w
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x31: // c.un.w
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x32: // c.eq.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x33: // c.ueq.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x34: // c.olt.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x35: // c.ult.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x36: // c.ole.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x37: // c.ule.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x38: // c.sf.w
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x39: // c.ngle.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3A: // c.seq.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3B: // c.ngl.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 == pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3C: // c.lt.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3D: // c.nge.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 < pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3E: // c.le.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3F: // c.ngt.w
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s32 <= pCPU->aFPR[MIPS_FT(nOpcode)].s32) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                        }
                        break;
                    case 0x15: // l
                        switch (MIPS_FUNCT(nOpcode)) {
                            case 0x00: // add.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s64 + pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                break;
                            case 0x01: // sub.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s64 - pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                break;
                            case 0x02: // mul.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s64 * pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                break;
                            case 0x03: // div.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 =
                                    pCPU->aFPR[MIPS_FS(nOpcode)].s64 / pCPU->aFPR[MIPS_FT(nOpcode)].s64;
                                break;
                            case 0x04: // sqrt.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = sqrt(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x05: // abs.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = fabs(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x06: // mov.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x07: // neg.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = -pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x08: // round.l.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x09: // trunc.l.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x0A: // ceil.l.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x0B: // floor.l.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x0C: // round.w.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x0D: // trunc.w.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x0E: // ceil.w.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = ceil(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x0F: // floor.w.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = floor(pCPU->aFPR[MIPS_FS(nOpcode)].s64);
                                break;
                            case 0x20: // cvt.s.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].f32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x21: // cvt.d.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].f64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x24: // cvt.w.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s32 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x25: // cvt.l.l
                                pCPU->aFPR[MIPS_FD(nOpcode)].s64 = pCPU->aFPR[MIPS_FS(nOpcode)].s64;
                                break;
                            case 0x30: // c.f.l
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x31: // c.un.l
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x32: // c.eq.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x33: // c.ueq.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x34: // c.olt.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x35: // c.ult.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x36: // c.ole.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x37: // c.ule.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x38: // c.sf.l
                                pCPU->anFCR[31] &= ~0x800000;
                                break;
                            case 0x39: // c.ngle.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3A: // c.seq.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3B: // c.ngl.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 == pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3C: // c.lt.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3D: // c.nge.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 < pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3E: // c.le.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                            case 0x3F: // c.ngt.l
                                if (pCPU->aFPR[MIPS_FS(nOpcode)].s64 <= pCPU->aFPR[MIPS_FT(nOpcode)].s64) {
                                    pCPU->anFCR[31] |= 0x800000;
                                } else {
                                    pCPU->anFCR[31] &= ~0x800000;
                                }
                                break;
                        }
                        break;
                }
            }
            break;
        case 0x14: // beq
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 == (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            } else {
                pCPU->nMode |= 4;
                pCPU->nPC += 4;
            }
            break;
        case 0x15: // bne
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 != (s32)pCPU->aGPR[MIPS_RT(nOpcode)].s32) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            } else {
                pCPU->nMode |= 4;
                pCPU->nPC += 4;
            }
            break;
        case 0x16: // blez
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 <= 0) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            } else {
                pCPU->nMode |= 4;
                pCPU->nPC += 4;
            }
            break;
        case 0x17: // bgtz
            if (pCPU->aGPR[MIPS_RS(nOpcode)].s32 > 0) {
                pCPU->nWaitPC = pCPU->nPC + MIPS_IMM_S16(nOpcode) * 4;
            } else {
                pCPU->nMode |= 4;
                pCPU->nPC += 4;
            }
            break;
        case 0x18: // daddi
            pCPU->aGPR[MIPS_RT(nOpcode)].s64 = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            break;
        case 0x19: // daddiu
            pCPU->aGPR[MIPS_RT(nOpcode)].u64 = pCPU->aGPR[MIPS_RS(nOpcode)].u64 + MIPS_IMM_S16(nOpcode);
            break;
        case 0x1F: // library call
            if (!libraryCall(SYSTEM_LIBRARY(pCPU->pHost), pCPU, MIPS_IMM_S16(nOpcode))) {
                return false;
            }
            break;
        case 0x1A: // ldl
            nCount = 0x38;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            do {
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    nData64 = ((s64)nData8 & 0xFF) << nCount;
                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 =
                        nData64 | (pCPU->aGPR[MIPS_RT(nOpcode)].s64 & ~((s64)0xFF << nCount));
                }
                nCount -= 8;
            } while ((nAddress++ & 7) != 0);
            break;
        case 0x1B: // ldr
            nCount = 0;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            do {
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    nData64 = ((s64)nData8 & 0xFF) << nCount;
                    pCPU->aGPR[MIPS_RT(nOpcode)].s64 =
                        nData64 | (pCPU->aGPR[MIPS_RT(nOpcode)].s64 & ~((s64)0xFF << nCount));
                }
                nCount += 8;
            } while ((nAddress-- & 7) != 0);
            break;
        case 0x27: // lwu
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].u64 = (u32)nData32;
            }
            break;
        case 0x20: // lb
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData8;
            }
            break;
        case 0x21: // lh
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET16(apDevice, aiDevice, nAddress, &nData16)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData16;
            }
            break;
        case 0x22: // lwl
            nCount = 0x18;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            do {
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    nData32 = ((u32)nData8 & 0xFF) << nCount;
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32 | (pCPU->aGPR[MIPS_RT(nOpcode)].s32 & ~(0xFF << nCount));
                }
                nCount -= 8;
            } while ((nAddress++ & 3) != 0);
            break;
        case 0x23: // lw
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32;
            }
            break;
        case 0x24: // lbu
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u8)nData8;
            }
            break;
        case 0x25: // lhu
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (frameGetDepth(SYSTEM_FRAME(pCPU->pHost), (u16*)&nData16, nAddress)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u16)nData16;
            } else {
                if (CPU_DEVICE_GET16(apDevice, aiDevice, nAddress, &nData16)) {
                    pCPU->aGPR[MIPS_RT(nOpcode)].u32 = (u16)nData16;
                }
            }
            break;
        case 0x26: // lwr
            nCount = 0;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            do {
                if (CPU_DEVICE_GET8(apDevice, aiDevice, nAddress, &nData8)) {
                    nData32 = ((u32)nData8 & 0xFF) << nCount;
                    pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32 | (pCPU->aGPR[MIPS_RT(nOpcode)].s32 & ~(0xFF << nCount));
                }
                nCount += 8;
            } while ((nAddress-- & 3) != 0);
            break;
        case 0x28: // sb
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s8);
            break;
        case 0x29: // sh
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            CPU_DEVICE_PUT16(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s16);
            break;
        case 0x2A: // swl
            nCount = 0x18;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            do {
                nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> nCount) & 0xFF;
                CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                nCount -= 8;
            } while ((nAddress++ & 3) != 0);
            break;
        case 0x2B: // sw
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &pCPU->aGPR[MIPS_RT(nOpcode)].s32);
            break;
        case 0x2C: // sdl
            nCount = 0x38;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            do {
                nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> nCount) & 0xFF;
                CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                nCount -= 8;
            } while ((nAddress++ & 7) != 0);
            break;
        case 0x2D: // sdr
            nCount = 0;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            do {
                nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u64 >> nCount) & 0xFF;
                CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                nCount += 8;
            } while ((nAddress-- & 7) != 0);
            break;
        case 0x2E: // swr
            nCount = 0;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            do {
                nData8 = (pCPU->aGPR[MIPS_RT(nOpcode)].u32 >> nCount) & 0xFF;
                CPU_DEVICE_PUT8(apDevice, aiDevice, nAddress, &nData8);
                nCount += 8;
            } while ((nAddress-- & 3) != 0);
            break;
        case 0x2F: // cache
            if (!cpuExecuteCacheInstruction(pCPU)) {
                return false;
            }
            break;
        case 0x30: // ll
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s32 = nData32;
            }
            break;
        case 0x31: // lwc1
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET32(apDevice, aiDevice, nAddress, &nData32)) {
                if (MIPS_RT(nOpcode) & 1) {
                    pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 &= 0xFFFFFFFF;
                    pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 |= (s64)nData32 << 32;
                } else {
                    pCPU->aFPR[MIPS_RT(nOpcode)].s32 = nData32;
                }
            }
            break;
        case 0x34: // lld
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
            }
            break;
        case 0x35: // ldc1
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                pCPU->aFPR[MIPS_RT(nOpcode)].s64 = nData64;
            }
            break;
        case 0x37: // ld
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (CPU_DEVICE_GET64(apDevice, aiDevice, nAddress, &nData64)) {
                pCPU->aGPR[MIPS_RT(nOpcode)].s64 = nData64;
            }
            break;
        case 0x38: // sc
            nData32 = pCPU->aGPR[MIPS_RT(nOpcode)].s32;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            pCPU->aGPR[MIPS_RT(nOpcode)].s32 = (CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &nData32)) ? 1 : 0;
            break;
        case 0x39: // swc1
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            if (MIPS_RT(nOpcode) & 1) {
                nData32 = pCPU->aFPR[MIPS_RT(nOpcode) - 1].u64 >> 32;
            } else {
                nData32 = pCPU->aFPR[MIPS_RT(nOpcode)].s32;
            }
            CPU_DEVICE_PUT32(apDevice, aiDevice, nAddress, &nData32);
            break;
        case 0x3C: // scd
            nData64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s64 + MIPS_IMM_S16(nOpcode);
            pCPU->aGPR[MIPS_RT(nOpcode)].s64 = (CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64)) ? 1 : 0;
            break;
        case 0x3D: // sdc1
            nData64 = pCPU->aFPR[MIPS_RT(nOpcode)].s64;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64);
            break;
        case 0x3F: // sd
            nData64 = pCPU->aGPR[MIPS_RT(nOpcode)].s64;
            nAddress = pCPU->aGPR[MIPS_RS(nOpcode)].s32 + MIPS_IMM_S16(nOpcode);
            CPU_DEVICE_PUT64(apDevice, aiDevice, nAddress, &nData64);
            break;
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nTick + 1)) {
        return 0;
    }
    if (restore) {
        pCPU->aGPR[31].u64 = save;
    }
    pCPU->nWaitPC = -1;
    pCPU->nTickLast = OSGetTick();

    PAD_STACK();
    PAD_STACK();
    return nAddressGCN;
}
#endif

static s32 cpuExecuteIdle(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    Rom* pROM;

    pROM = SYSTEM_ROM(pCPU->pHost);

#if VERSION != MQ_J
    if (!simulatorTestReset(false, false, false, true)) {
        return 0;
    }
#endif

    nCount = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 0x80;
    pCPU->nPC = nAddressN64;
    if (!(pCPU->nMode & 0x40) && pROM->copy.nSize == 0) {
        videoForceRetrace(SYSTEM_VIDEO(pCPU->pHost), false);
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    pCPU->nTickLast = OSGetTick();
    return nAddressGCN;
}

static s32 cpuExecuteJump(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    nCount = OSGetTick();

    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nAddressN64;

    if (gpSystem->eTypeROM == SRT_ZELDA1 && pCPU->nPC == 0x81000000) {
        simulatorPlayMovie();
    }

    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    pCPU->nTickLast = OSGetTick();
    return nAddressGCN;
}

/**
 * @brief Executes a call from the dynamic recompiler environment
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Latest tick count
 * @param nAddressN64 The N64 address of the call.
 * @param nAddressGCN The GameCube address after the call has completed.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteCall(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    s32 pad;
    s32 nReg;
    s32 count;
    s32* anCode;
    s32 saveGCN;
    CpuFunction* node;
    CpuCallerID* block;
    s32 nDeltaAddress;

    nCount = OSGetTick();
    if (pCPU->nWaitPC != 0) {
        pCPU->nMode |= 8;
    } else {
        pCPU->nMode &= ~8;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nAddressN64;

    pCPU->aGPR[31].s32 = nAddressGCN;
    saveGCN = nAddressGCN - 4;

    pCPU->survivalTimer++;

    cpuFindFunction(pCPU, pCPU->nReturnAddrLast - 8, &node);

    block = node->block;
    for (count = 0; count < node->callerID_total; count++) {
        if (block[count].N64address == nAddressN64 && block[count].GCNaddress == 0) {
            block[count].GCNaddress = saveGCN;
            break;
        }
    }

    saveGCN = (ganMapGPR[31] & 0x100) ? true : false;
    anCode = (s32*)nAddressGCN - (saveGCN ? 4 : 3);
    if (saveGCN) {
        anCode[0] = 0x3CA00000 | ((u32)nAddressGCN >> 16); // lis r5,nAddressGCN@h
        anCode[1] = 0x60A50000 | ((u32)nAddressGCN & 0xFFFF); // ori r5,r5,nAddressGCN@l
        DCStoreRange(anCode, 8);
        ICInvalidateRange(anCode, 8);
    } else {
        nReg = ganMapGPR[31];
        anCode[0] = 0x3C000000 | ((u32)nAddressGCN >> 16) | (nReg << 21); // lis ri,nAddressGCN@h
        anCode[1] = 0x60000000 | ((u32)nAddressGCN & 0xFFFF) | (nReg << 21) | (nReg << 16); // ori ri,ri,nAddressGCN@l
        DCStoreRange(anCode, 8);
        ICInvalidateRange(anCode, 8);
    }

    //! @bug: If cpuExecuteUpdate decides to delete the function we're trying to
    //! call here, our lis/ori will be reverted by treeCallerCheck since we've
    //! already marked this call site in the callerID for-loop above. The
    //! reverted lis/ori will store the return N64 address instead of a GCN
    //! address, so the next time this recompiled call is executed, the CPU will
    //! jump to that N64 return address in GCN address space and bad things
    //! happen (usually an invalid instruction or invalid load/store). This is
    //! known as a "VC crash".
    //!
    //! For more details, see https://pastebin.com/V6ANmXt8
    if (!cpuExecuteUpdate(pCPU, &nAddressGCN, nCount)) {
        return 0;
    }

    nDeltaAddress = (u8*)nAddressGCN - (u8*)&anCode[3];
    if (saveGCN) {
        anCode[3] = 0x48000000 | (nDeltaAddress & 0x03FFFFFC); // b nDeltaAddress
        DCStoreRange(anCode, 16);
        ICInvalidateRange(anCode, 16);
    } else {
        anCode[2] = 0x48000000 | (nDeltaAddress & 0x03FFFFFC); // b nDeltaAddress
        DCStoreRange(anCode, 12);
        ICInvalidateRange(anCode, 12);
    }

    pCPU->nTickLast = OSGetTick();

    return nAddressGCN;
}

// Matches but data doesn't
#ifndef NON_MATCHING
static s32 cpuExecuteLoadStore(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteLoadStore.s")
#else
/**
 * @brief Recompiles a VR4300 load/store instruction
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressN64 The address of the Load/Store instruction.
 * @param nAddressGCN A pointer to the location where recompiled code should be stored.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteLoadStore(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    u32* opcode;
    s32 address;
    s32 iRegisterA;
    s32 iRegisterB;
    u8 device;
    s32 total;
    s32 count;
    s32 save;
    s32 interpret;
    s32* before;
    s32* after;
    s32 check2;
    s32* anCode;
    s32 pad;

    count = 0;
    save = 0;
    interpret = 0;
    check2 = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), &opcode, nAddressN64, NULL);

    address = pCPU->aGPR[MIPS_RS(*opcode)].s32 + MIPS_IMM_S16(*opcode);
    device = pCPU->aiDevice[(u32)(address) >> 16];

    if (pCPU->nCompileFlag & 0x100) {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 3;
    } else {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 2;
    }

    if (((u32)address >> 28) < 0x08) {
        interpret = 1;
    }

    if (!interpret && device >= 0x80) {
        switch (MIPS_OP(*opcode)) {
            case 0x20: // lb
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                anCode[count++] = 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x7C000774 | (iRegisterA << 21) | (iRegisterA << 16);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x24: // lbu
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x88070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x21: // lh
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x7C000734 | (iRegisterA << 21) | (iRegisterA << 16);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x25: // lhu
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0xA0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x23: // lw
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000214 | (7 << 21) | (iRegisterB << 16) | (8 << 11);
                anCode[count++] = 0x80070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                if (ganMapGPR[MIPS_RT(*opcode)] & 0x100) {
                    anCode[count++] = 0x90A30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                break;
            case 0x28: // sb
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE00000 | (iRegisterB << 16) | 0x4214;
                anCode[count++] = 0x98070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            case 0x29: // sh
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE00000 | (iRegisterB << 16) | 0x4214;
                anCode[count++] = 0xB0070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            case 0x2B: // sw
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4) & 0xFFFF);
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }
                anCode[count++] = 0x7CE00000 | (iRegisterB << 16) | 0x4214;
                anCode[count++] = 0x90070000 | (iRegisterA << 21) | MIPS_IMM_U16(*opcode);
                break;
            default:
                OSPanic(D_800EC1E0, 4725, D_8013525C);
                break;
        }
    } else {
        interpret = 1;
        anCode[count++] = 0x3CA00000 | ((u32)nAddressN64 >> 16);
        anCode[count++] = 0x60A50000 | ((u32)nAddressN64 & 0xFFFF);
        anCode[count++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[count]) & 0x03FFFFFC) | 1;
    }

    if (pCPU->nCompileFlag & 0x100) {
        if (6 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[6] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 5) {
            anCode[count++] = 0x60000000;
        }
        total = 6;
    } else {
        if (5 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[5] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 4) {
            anCode[count++] = 0x60000000;
        }
        total = 5;
    }

    if (!interpret && before[0] == 0x38C00000 && before[1] == check2) {
        before[0] = 0x48000000 | (((u32)&before[2] - (u32)&before[0]) & 0xFFFF);
        before[1] = 0x60000000;
        DCStoreRange(before, 8);
        ICInvalidateRange(before, 8);

        if (save != 0) {
            anCode[save] = 0x48000000 | (((u32)&after[2] - (u32)&anCode[save]) & 0xFFFF);
        }
        after[0] = 0x60000000;
        after[1] = 0x60000000;

        total += 2;
        pCPU->nWaitPC = -1;
    }

    DCStoreRange(anCode, total * 4);
    ICInvalidateRange(anCode, total * 4);
    return (s32)anCode;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
static s32 cpuExecuteLoadStoreF(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuExecuteLoadStoreF.s")
#else
/**
 * @brief Recompiles a VR4300 load/store instruction on COP1 or doubleword load/store.
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressN64 The address of the Load/Store instruction.
 * @param nAddressGCN A pointer to the location where recompiled code should be stored.
 * @return s32 The address of the recompiled called function.
 */
static s32 cpuExecuteLoadStoreF(Cpu* pCPU, s32 nCount, s32 nAddressN64, s32 nAddressGCN) {
    u32* opcode;
    s32 address;
    s32 iRegisterA;
    s32 iRegisterB;
    u8 device;
    s32 total;
    s32 count;
    s32 save;
    s32 interpret;
    s32* before;
    s32* after;
    s32 check2;
    s32* anCode;
    s32 rt;
    s32 pad;

    count = 0;
    save = 0;
    interpret = 0;
    check2 = 0x90C30000 + OFFSETOF(pCPU, nWaitPC);

    ramGetBuffer(SYSTEM_RAM(pCPU->pHost), &opcode, nAddressN64, NULL);

    address = pCPU->aGPR[MIPS_RS(*opcode)].s32 + MIPS_IMM_S16(*opcode);
    device = pCPU->aiDevice[(u32)(address) >> 16];

    if (pCPU->nCompileFlag & 0x100) {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 4;
    } else {
        anCode = (s32*)nAddressGCN - 3;
        before = anCode - 2;
        after = (s32*)nAddressGCN + 3;
    }

    if (((u32)address >> 28) < 0x08) {
        interpret = 1;
    }

    if (!interpret && device >= 0x80) {
        rt = MIPS_RT(*opcode);
        switch (MIPS_OP(*opcode)) {
            case 0x31: // lwc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;

                if (rt % 2 == 1) {
                    anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                    anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aFPR[rt - 1]);
                } else {
                    anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                    anCode[count++] = 0x90A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                }
                break;
            case 0x39: // swc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                if (rt % 2 == 1) {
                    anCode[count++] = 0x80A30000 + OFFSETOF(pCPU, aFPR[rt - 1]);
                } else {
                    anCode[count++] = 0x80A30000 + OFFSETOF(pCPU, aFPR[rt]) + 4;
                }
                anCode[count++] = 0x90A70000 | MIPS_IMM_U16(*opcode);
                break;
            case 0x35: // ldc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aFPR[rt]);
                anCode[count++] = 0x80A70000 | (MIPS_IMM_U16(*opcode) + 4);
                anCode[count++] = 0x90A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                break;
            case 0x3D: // sdc1
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if ((pCPU->nCompileFlag & 0x100) && ((u32)address >> 28) >= 10) {
                    anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                anCode[count++] = 0x80A30000 + OFFSETOF(pCPU, aFPR[rt]);
                anCode[count++] = 0x90A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x80A30000 + (OFFSETOF(pCPU, aFPR[rt]) + 4);
                anCode[count++] = 0x90A70000 | (MIPS_IMM_U16(*opcode) + 4);
                break;
            case 0x37: // ld
                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 5;
                }
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 6;
                    anCode[count++] = 0x80C30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                anCode[count++] = 0x80A70000 | MIPS_IMM_U16(*opcode);
                anCode[count++] = 0x90A30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]);
                anCode[count++] = 0x80070000 | (iRegisterA << 21) | (MIPS_IMM_U16(*opcode) + 4);
                anCode[count++] = (0x90030000 | (iRegisterA << 21)) + (OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4);
                break;
            case 0x3F: // sd
                if ((iRegisterB = ganMapGPR[MIPS_RS(*opcode)]) & 0x100) {
                    iRegisterB = 7;
                    anCode[count++] = 0x80E30000 + ((OFFSETOF(pCPU, aGPR[MIPS_RS(*opcode)]) + 4) & 0xFFFF);
                }

                if (pCPU->nCompileFlag & 0x100) {
                    if (pCPU->nCompileFlag & 0x1000) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    } else if (((u32)address >> 28) >= 10) {
                        anCode[count++] = 0x7C000038 | (iRegisterB << 21) | (iRegisterB << 16) | (9 << 11);
                    }
                }

                anCode[count++] = 0x7C000000 | (7 << 21) | (iRegisterB << 16) | (8 << 11) | 0x214;
                anCode[count++] = 0x80C30000 + OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]);
                anCode[count++] = 0x90C70000 | MIPS_IMM_U16(*opcode);

                if ((iRegisterA = ganMapGPR[MIPS_RT(*opcode)]) & 0x100) {
                    iRegisterA = 6;
                    anCode[count++] = 0x80C30000 + (OFFSETOF(pCPU, aGPR[MIPS_RT(*opcode)]) + 4);
                }
                anCode[count++] = 0x90070000 | (iRegisterA << 21) | (MIPS_IMM_U16(*opcode) + 4);
                break;
            default:
                OSPanic(D_800EC1E0, 5181, D_8013525C);
                break;
        }
    } else {
        interpret = 1;
        anCode[count++] = 0x3CA00000 | ((u32)nAddressN64 >> 16);
        anCode[count++] = 0x60A50000 | ((u32)nAddressN64 & 0xFFFF);
        anCode[count++] = 0x48000000 | (((u32)pCPU->pfStep - (u32)&anCode[count]) & 0x03FFFFFC) | 1;
    }

    if (pCPU->nCompileFlag & 0x100) {
        if (7 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[7] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 6) {
            anCode[count++] = 0x60000000;
        }
        total = 7;
    } else {
        if (6 - count >= 2) {
            save = count;
            anCode[count++] = 0x48000000 | (((u32)&anCode[6] - (u32)&anCode[count]) & 0xFFFF);
        }
        while (count <= 5) {
            anCode[count++] = 0x60000000;
        }
        total = 6;
    }

    if (!interpret && before[0] == 0x38C00000 && before[1] == check2) {
        before[0] = 0x48000000 | (((u32)&before[2] - (u32)&before[0]) & 0xFFFF);
        before[1] = 0x60000000;
        DCStoreRange(before, 8);
        ICInvalidateRange(before, 8);

        if (save != 0) {
            anCode[save] = 0x48000000 | (((u32)&after[2] - (u32)&anCode[save]) & 0xFFFF);
        }
        after[0] = 0x60000000;
        after[1] = 0x60000000;

        total += 2;
        pCPU->nWaitPC = -1;
    }

    DCStoreRange(anCode, total * 4);
    ICInvalidateRange(anCode, total * 4);
    return (s32)anCode;
}
#endif

/**
 * @brief Generates a call to a virtual-console function from within the dynarec envrionment
 * Dedicated PPC registers are saved to the cpu object, and restored once the virtual-console function has finished.
 * Jump to the return value of the virtual-console function
 *
 * @param pCPU The emulated VR4300.
 * @param ppfLink A pointer to store the generated PPC code.
 * @param pfFunction The virtual-console function to call.
 * @return bool true on success, false otherwise.
 */
static bool cpuMakeLink(Cpu* pCPU, CpuExecuteFunc* ppfLink, CpuExecuteFunc pfFunction) {
    s32 iGPR;
    s32* pnCode;
    s32 nData;
    s32 pad;

    if (!xlHeapTake((void**)&pnCode, 0x200 | 0x30000000)) {
        return false;
    }
    *ppfLink = (CpuExecuteFunc)pnCode;

    *pnCode++ = 0x7CC802A6;

    for (iGPR = 1; iGPR < 32; iGPR++) {
        if (!(ganMapGPR[iGPR] & 0x100)) {
            nData = OFFSETOF(pCPU, aGPR[iGPR]) + 4;
            *pnCode++ = 0x90030000 | (ganMapGPR[iGPR] << 21) | nData; // lwz ri,(aGPR[i] + 4)(r3)
        }
    }

    *pnCode++ = 0x48000000 | (((u8*)pfFunction - (u8*)pnCode) & 0x03FFFFFC) | 1; // bl pfFunction
    *pnCode++ = 0x7C6803A6; // mtlr r3
    *pnCode++ = 0x3C600000 | ((u32)pCPU >> 16); // lis r3,pCPU@h
    *pnCode++ = 0x60630000 | ((u32)pCPU & 0xFFFF); // ori r3,r3,pCPU@l
    *pnCode++ = 0x80830000 + OFFSETOF(pCPU, survivalTimer); // lwz r4,survivalTimer(r3)

    nData = (u32)(SYSTEM_RAM(pCPU->pHost)->pBuffer) - 0x80000000;
    *pnCode++ = 0x3D000000 | ((u32)nData >> 16); // lis r8,ramOffset@h
    if (pCPU->nCompileFlag & 0x100) {
        *pnCode++ = 0x3D20DFFF; // lis r9,0xDFFF
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l
        *pnCode++ = 0x6129FFFF; // ori r9,r9,0xFFFF
    } else if (pCPU->nCompileFlag & 1) {
        *pnCode++ = 0x39230000 + OFFSETOF(pCPU, aiDevice); // addi r9,r3,aiDevice
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l
    }

    *pnCode++ = 0x38000000 | (ganMapGPR[0] << 21); // li r0,0
    for (iGPR = 1; iGPR < 32; iGPR++) {
        if (!(ganMapGPR[iGPR] & 0x100)) {
            nData = OFFSETOF(pCPU, aGPR[iGPR]) + 4;
            *pnCode++ = 0x80030000 | (ganMapGPR[iGPR] << 21) | nData; // stw ri,(aGPR[i] + 4)(r3)
        }
    }

    *pnCode++ = 0x4E800020; // blr

    DCStoreRange(*ppfLink, 0x200);
    ICInvalidateRange(*ppfLink, 0x200);
    return true;
}

static inline bool cpuFreeLink(Cpu* pCPU, CpuExecuteFunc* ppfLink) {
    if (!xlHeapFree((void**)&ppfLink)) {
        return false;
    } else {
        *ppfLink = NULL;
        return true;
    }
}

/**
 * @brief Begins execution of the emulated VR4300
 *
 * @param pCPU The emulated VR4300.
 * @param nCount Unused.
 * @param nAddressBreak Unused.
 * @return bool true on success, false otherwise.
 */
bool cpuExecute(Cpu* pCPU, s32 nCount, u64 nAddressBreak) {
    s32 pad1;
    s32 iGPR;
    s32* pnCode;
    s32 nData;
    s32 pad2;
    CpuFunction* pFunction;
    void (*pfCode)(void);

    if (pCPU->nCompileFlag & 0x1000) {
        pCPU->nCompileFlag |= 0x100;
    }

    if (!cpuMakeLink(pCPU, &pCPU->pfStep, &cpuExecuteOpcode)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfJump, &cpuExecuteJump)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfCall, &cpuExecuteCall)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfIdle, &cpuExecuteIdle)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfRam, &cpuExecuteLoadStore)) {
        return false;
    }
    if (!cpuMakeLink(pCPU, &pCPU->pfRamF, &cpuExecuteLoadStoreF)) {
        return false;
    }

    cpuCompile_DSLLV(pCPU, &cpuCompile_DSLLV_function);
    cpuCompile_DSRLV(pCPU, &cpuCompile_DSRLV_function);
    cpuCompile_DSRAV(pCPU, &cpuCompile_DSRAV_function);
    cpuCompile_DMULT(pCPU, &cpuCompile_DMULT_function);
    cpuCompile_DMULTU(pCPU, &cpuCompile_DMULTU_function);
    cpuCompile_DDIV(pCPU, &cpuCompile_DDIV_function);
    cpuCompile_DDIVU(pCPU, &cpuCompile_DDIVU_function);
    cpuCompile_DADD(pCPU, &cpuCompile_DADD_function);
    cpuCompile_DADDU(pCPU, &cpuCompile_DADDU_function);
    cpuCompile_DSUB(pCPU, &cpuCompile_DSUB_function);
    cpuCompile_DSUBU(pCPU, &cpuCompile_DSUBU_function);
    cpuCompile_S_SQRT(pCPU, &cpuCompile_S_SQRT_function);
    cpuCompile_D_SQRT(pCPU, &cpuCompile_D_SQRT_function);
    cpuCompile_W_CVT_SD(pCPU, &cpuCompile_W_CVT_SD_function);
    cpuCompile_L_CVT_SD(pCPU, &cpuCompile_L_CVT_SD_function);
    cpuCompile_CEIL_W(pCPU, &cpuCompile_CEIL_W_function);
    cpuCompile_FLOOR_W(pCPU, &cpuCompile_FLOOR_W_function);
    cpuCompile_ROUND_W(&cpuCompile_ROUND_W_function);
    cpuCompile_TRUNC_W(&cpuCompile_TRUNC_W_function);
    cpuCompile_LB(pCPU, &cpuCompile_LB_function);
    cpuCompile_LH(pCPU, &cpuCompile_LH_function);
    cpuCompile_LW(pCPU, &cpuCompile_LW_function);
    cpuCompile_LBU(pCPU, &cpuCompile_LBU_function);
    cpuCompile_LHU(pCPU, &cpuCompile_LHU_function);
    cpuCompile_SB(pCPU, &cpuCompile_SB_function);
    cpuCompile_SH(pCPU, &cpuCompile_SH_function);
    cpuCompile_SW(pCPU, &cpuCompile_SW_function);
    cpuCompile_LDC(pCPU, &cpuCompile_LDC_function);
    cpuCompile_SDC(pCPU, &cpuCompile_SDC_function);
    cpuCompile_LWL(pCPU, &cpuCompile_LWL_function);
    cpuCompile_LWR(pCPU, &cpuCompile_LWR_function);

    if (cpuMakeFunction(pCPU, &pFunction, pCPU->nPC)) {
        if (!xlHeapTake((void**)&pnCode, 0x100 | 0x30000000)) {
            return false;
        }

        pfCode = (void (*)(void))pnCode;

        *pnCode++ = 0x3C600000 | ((u32)pCPU >> 0x10); // lis r3,pCPU@h
        *pnCode++ = 0x60630000 | ((u32)pCPU & 0xFFFF); // ori r3,r3,pCPU@l

        *pnCode++ = 0x80830000 + OFFSETOF(pCPU, survivalTimer); // lwz r4,survivalTimer(r3)

        nData = (u32)(SYSTEM_RAM(pCPU->pHost)->pBuffer) - 0x80000000;
        *pnCode++ = 0x3D000000 | ((u32)nData >> 16); // lis r8,ramOffset@h
        *pnCode++ = 0x61080000 | ((u32)nData & 0xFFFF); // ori r8,r8,ramOffset@l

        if (pCPU->nCompileFlag & 0x100) {
            *pnCode++ = 0x3D20DFFF; // lis r9,0xDFFF
            *pnCode++ = 0x6129FFFF; // ori r9,r9,0xFFFF
        } else if (pCPU->nCompileFlag & 1) {
            *pnCode++ = 0x39230000 + OFFSETOF(pCPU, aiDevice); // addi r9,r3,aiDevice
        }

        for (iGPR = 0; iGPR < ARRAY_COUNT(ganMapGPR); iGPR++) {
            if (!(ganMapGPR[iGPR] & 0x100)) {
                nData = OFFSETOF(pCPU, aGPR[iGPR]) + 4;
                *pnCode++ = 0x80030000 | (ganMapGPR[iGPR] << 21) | nData; // lwz ri,(aGPR[i] + 4)(r3)
            }
        }

        *pnCode++ = 0x48000000 | (((u32)pFunction->pfCode - (u32)pnCode) & 0x03FFFFFC); // b pFunction->pfCode

        DCStoreRange(pfCode, 0x100);
        ICInvalidateRange(pfCode, 0x100);

        pCPU->nRetrace = pCPU->nRetraceUsed = 0;

        VIWaitForRetrace();
        VISetPostRetraceCallback(&cpuRetraceCallback);

        pfCode();

        if (!xlHeapFree((void**)&pfCode)) {
            return false;
        }

        if (!cpuFreeLink(pCPU, &pCPU->pfIdle)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfCall)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfJump)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfStep)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfRam)) {
            return false;
        }
        if (!cpuFreeLink(pCPU, &pCPU->pfRamF)) {
            return false;
        }

        if (!xlHeapFree((void**)&cpuCompile_DSLLV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSRLV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSRAV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DMULT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DMULTU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DDIV_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DDIVU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DADD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DADDU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSUB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_DSUBU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_S_SQRT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_D_SQRT_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_W_CVT_SD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_L_CVT_SD_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_CEIL_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_FLOOR_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_TRUNC_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_ROUND_W_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LH_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LW_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LBU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LHU_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SB_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SH_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SW_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LDC_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_SDC_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LWL_function)) {
            return false;
        }
        if (!xlHeapFree((void**)&cpuCompile_LWR_function)) {
            return false;
        }
    }

    return true;
}

static bool cpuHackHandler(Cpu* pCPU) {
    u32 nSize;
    u32* pnCode;
    s32 iCode;
    s32 iSave1;
    s32 iSave2;
    s32 iLoad;

    iSave1 = iSave2 = iLoad = 0;

    if (xlObjectTest(SYSTEM_RAM(pCPU->pHost), &gClassRAM) &&
        ramGetBuffer(SYSTEM_RAM(pCPU->pHost), (void**)&pnCode, 0, NULL)) {
        if (!ramGetSize(SYSTEM_RAM(pCPU->pHost), (s32*)&nSize)) {
            return false;
        }

        for (iCode = 0; iCode < (nSize >> 2) && (iSave1 != -1 || iSave2 != -1 || iLoad != -1); iCode++) {
            if (iSave1 != -1) {
                if (pnCode[iCode] == ganOpcodeSaveFP1[iSave1]) {
                    iSave1 += 1;
                    if (iSave1 == 5U) {
                        pnCode[iCode - 3] = 0;
                        iSave1 = -1;
                    }
                } else {
                    iSave1 = 0;
                }
            }

            if (iSave2 != -1) {
                if (pnCode[iCode] == ganOpcodeSaveFP2_0[iSave2]) {
                    iSave2 += 1;
                    if (iSave2 == 5U) {
                        pnCode[iCode - 3] = 0;
                        iSave2 = -1;
                    }
                } else if (pnCode[iCode] == ganOpcodeSaveFP2_1[iSave2]) {
                    iSave2 += 1;
                    if (iSave2 == 3U) {
                        pnCode[iCode - 2] = 0;
                        iSave2 = -1;
                    }
                } else {
                    iSave2 = 0;
                }
            }

            if (iLoad != -1) {
                if (pnCode[iCode] == ganOpcodeLoadFP[iLoad]) {
                    iLoad += 1;
                    if (iLoad == 5U) {
                        pnCode[iCode - 3] = 0;
                        iLoad = -1;
                    }
                } else {
                    iLoad = 0;
                }
            }
        }
    }

    return (iSave1 == -1 && iSave2 == -1 && iLoad == -1) ? true : false;
}

static inline bool cpuMakeCachedAddress(Cpu* pCPU, s32 nAddressN64, s32 nAddressHost, CpuFunction* pFunction) {
    s32 iAddress;
    CpuAddress* aAddressCache;

    aAddressCache = pCPU->aAddressCache;
    if ((iAddress = pCPU->nCountAddress) == ARRAY_COUNT(pCPU->aAddressCache)) {
        iAddress -= 1;
    } else {
        pCPU->nCountAddress++;
    }

    for (; iAddress > 0; iAddress--) {
        aAddressCache[iAddress] = aAddressCache[iAddress - 1];
    }

    aAddressCache[0].nN64 = nAddressN64;
    aAddressCache[0].nHost = nAddressHost;
    aAddressCache[0].pFunction = pFunction;
    return true;
}

bool cpuFreeCachedAddress(Cpu* pCPU, s32 nAddress0, s32 nAddress1) {
    s32 iAddress;
    s32 iAddressNext;
    s32 nAddressN64;
    CpuAddress* aAddressCache = pCPU->aAddressCache;

    iAddress = 0;
    while (iAddress < pCPU->nCountAddress) {
        nAddressN64 = aAddressCache[iAddress].nN64;
        if (nAddress0 <= nAddressN64 && nAddressN64 <= nAddress1) {
            for (iAddressNext = iAddress; iAddressNext < pCPU->nCountAddress - 1; iAddressNext++) {
                aAddressCache[iAddressNext] = aAddressCache[iAddressNext + 1];
            }
            pCPU->nCountAddress--;
        } else {
            iAddress++;
        }
    }

    return true;
}

static bool cpuFindCachedAddress(Cpu* pCPU, s32 nAddressN64, s32* pnAddressHost) {
    s32 iAddress;
    CpuFunction* pFunction;
    CpuAddress addressFound;
    CpuAddress* aAddressCache = pCPU->aAddressCache;

    for (iAddress = 0; iAddress < pCPU->nCountAddress; iAddress++) {
        if (nAddressN64 == aAddressCache[iAddress].nN64) {
            if (iAddress > ARRAY_COUNT(pCPU->aAddressCache) / 2) {
                addressFound = aAddressCache[iAddress];
                for (; iAddress > 0; iAddress--) {
                    aAddressCache[iAddress] = aAddressCache[iAddress - 1];
                }
                aAddressCache[iAddress] = addressFound;
            }

            pFunction = aAddressCache[iAddress].pFunction;
            if (pFunction->timeToLive > 0) {
                pFunction->timeToLive = pCPU->survivalTimer;
            }

            *pnAddressHost = aAddressCache[iAddress].nHost;
            return true;
        }
    }

    return false;
}

bool cpuTestInterrupt(Cpu* pCPU, s32 nMaskIP) {
    pCPU->anCP0[13] |= (nMaskIP & 0xFF) << 8;
    if ((pCPU->anCP0[12] & 6) != 0) {
        return false;
    }
    if ((pCPU->anCP0[12] & 1) == 0) {
        return false;
    }
    if ((((pCPU->anCP0[12] & 0xFF00) >> 8) & (nMaskIP & 0xFF)) == 0) {
        return false;
    }
    return true;
}

bool cpuException(Cpu* pCPU, CpuExceptionCode eCode, s32 nMaskIP) {
    s32 pad[2];

    if ((pCPU->anCP0[12] & 6) != 0) {
        return false;
    }
    nMaskIP &= 0xFF;
    if (eCode == CEC_NONE) {
        return false;
    }
    if ((eCode >= CEC_RESERVED_16 && eCode <= CEC_RESERVED_22) ||
        (eCode >= CEC_RESERVED_24 && eCode <= CEC_RESERVED_30)) {
        return false;
    }
    if (eCode == CEC_RESERVED) {
        return false;
    }

    if (eCode == CEC_INTERRUPT) {
        if (!cpuTestInterrupt(pCPU, nMaskIP)) {
            return false;
        }
    } else {
        pCPU->nPC -= 4;
        pCPU->nMode |= 4;
    }

    pCPU->nMode &= ~8;
    if (!(pCPU->nMode & 0x10)) {
        if (!cpuHackHandler(pCPU)) {
            xlPostText(D_800ED674, D_80135260, 923);
        }
        pCPU->nMode |= 0x10;
    }
    if (pCPU->nWaitPC != 0xFFFFFFFF) {
        pCPU->nWaitPC = -1;
        pCPU->anCP0[14] = pCPU->nPC - 4;
        pCPU->anCP0[13] |= 0x80000000;
    } else {
        pCPU->anCP0[14] = pCPU->nPC;
    }

    pCPU->nMode &= ~0x80;
    pCPU->anCP0[12] |= 2;
    pCPU->anCP0[13] = (pCPU->anCP0[13] & ~0x7C) | (eCode << 2);

    if (eCode - 1 <= 2U) {
        pCPU->nPC = 0x80000000;
    } else {
        pCPU->nPC = 0x80000180;
    }

    pCPU->nMode |= 4;
    pCPU->nMode |= 0x20;

    if (!libraryCall(SYSTEM_LIBRARY(pCPU->pHost), pCPU, -1)) {
        return false;
    }

    return true;
}

/**
 * @brief Creates a new device and registers memory space for that device.
 *
 * @param pCPU The emulated VR4300.
 * @param piDevice A pointer to the index in the cpu->devices array which the device was created.
 * @param pObject The object which will handle reuqests for this device.
 * @param nOffset Starting address of the device's address space.
 * @param nAddress Starting physical address of the device's address space.
 * @param nAddress1 Ending physical address of the device's address space.
 * @param nType An argument which will be passed back to the device's event handler.
 * @return bool true on success, false otherwise.
 */
static bool cpuMakeDevice(Cpu* pCPU, s32* piDevice, void* pObject, s32 nOffset, u32 nAddress0, u32 nAddress1,
                          s32 nType) {
    CpuDevice* pDevice;
    s32 iDevice;
    s32 pad;

    iDevice = (nType & 0x100) ? (ARRAY_COUNT(pCPU->apDevice) / 2) : 0;
    for (; iDevice < ARRAY_COUNT(pCPU->apDevice); iDevice++) {
        if (pCPU->apDevice[iDevice] == NULL) {
            break;
        }
    }
    if (iDevice == ARRAY_COUNT(pCPU->apDevice)) {
        return false;
    }

    *piDevice = iDevice;
    if (!xlHeapTake((void**)&pDevice, sizeof(CpuDevice))) {
        return false;
    }

    pCPU->apDevice[iDevice] = pDevice;
    pDevice->nType = nType;
    pDevice->pObject = pObject;
    pDevice->nOffsetAddress = nOffset;
    pDevice->nAddressPhysical0 = nAddress0;
    pDevice->nAddressPhysical1 = nAddress1;

    if (!xlObjectEvent(pObject, 0x1002, pDevice)) {
        return false;
    }

    return true;
}

bool cpuFreeDevice(Cpu* pCPU, s32 iDevice) {
    if (!xlHeapFree((void**)&pCPU->apDevice[iDevice])) {
        return false;
    } else {
        s32 iAddress;

        pCPU->apDevice[iDevice] = NULL;
        for (iAddress = 0; iAddress < ARRAY_COUNT(pCPU->aiDevice); iAddress++) {
            if (pCPU->aiDevice[iAddress] == iDevice) {
                pCPU->aiDevice[iAddress] = pCPU->iDeviceDefault;
            }
        }
        return true;
    }
}

static bool cpuMapAddress(Cpu* pCPU, s32* piDevice, u32 nVirtual, u32 nPhysical, s32 nSize) {
    s32 iDeviceTarget;
    s32 iDeviceSource;
    u32 nAddressVirtual0;
    u32 nAddressVirtual1;

    for (iDeviceSource = 0; iDeviceSource < ARRAY_COUNT(pCPU->apDevice); iDeviceSource++) {
        if (iDeviceSource != pCPU->iDeviceDefault && pCPU->apDevice[iDeviceSource] != NULL &&
            pCPU->apDevice[iDeviceSource]->nAddressPhysical0 <= nPhysical &&
            nPhysical <= pCPU->apDevice[iDeviceSource]->nAddressPhysical1) {
            break;
        }
    }

    if (iDeviceSource == ARRAY_COUNT(pCPU->apDevice)) {
        iDeviceSource = pCPU->iDeviceDefault;
    }

    if (!cpuMakeDevice(pCPU, &iDeviceTarget, pCPU->apDevice[iDeviceSource]->pObject, nPhysical - nVirtual,
                       pCPU->apDevice[iDeviceSource]->nAddressPhysical0,
                       pCPU->apDevice[iDeviceSource]->nAddressPhysical1, pCPU->apDevice[iDeviceSource]->nType)) {
        return false;
    }

    nAddressVirtual0 = nVirtual;
    nAddressVirtual1 = nVirtual + nSize - 1;
    while (nAddressVirtual0 < nAddressVirtual1) {
        pCPU->aiDevice[nAddressVirtual0 >> 16] = iDeviceTarget;
        nAddressVirtual0 += 0x10000;
    }

    if (piDevice != NULL) {
        *piDevice = iDeviceTarget;
    }

    return true;
}

static bool cpuSetTLB(Cpu* pCPU, s32 iEntry) {
    s32 iDevice;
    u32 nMask;
    u32 nVirtual;
    u32 nPhysical;

    if ((pCPU->anCP0[10] & 0xFFFFE000) == 0x80000000) {
        pCPU->aTLB[iEntry][0] &= ~2;
        ;
        if ((iDevice = pCPU->aTLB[iEntry][4]) != -1) {
            if (!cpuFreeDevice(pCPU, iDevice)) {
                return false;
            }
            pCPU->aTLB[iEntry][4] = -1;
        }

        return true;
    }

    if ((iDevice = pCPU->aTLB[iEntry][4]) != -1) {
        if (!cpuFreeDevice(pCPU, iDevice)) {
            return false;
        }
    }

    pCPU->aTLB[iEntry][0] = pCPU->anCP0[2] | 2;
    pCPU->aTLB[iEntry][1] = pCPU->anCP0[3];
    pCPU->aTLB[iEntry][2] = pCPU->anCP0[10];
    pCPU->aTLB[iEntry][3] = pCPU->anCP0[5];

    nMask = pCPU->aTLB[iEntry][3] | 0x1FFF;
    nVirtual = pCPU->aTLB[iEntry][2] & 0xFFFFE000;
    nPhysical = ((s32)(pCPU->aTLB[iEntry][0] & 0xFFFFFFC0) << 6) + (nVirtual & nMask);
    if (nVirtual == 0xC0000000 && nPhysical == 0x80000000) {
        nPhysical = 0x04900000;
    }
    if (nVirtual < 0x80000000 || 0xC0000000 <= nVirtual) {
        if (!cpuMapAddress(pCPU, &iDevice, nVirtual, nPhysical, nMask + 1)) {
            return false;
        }
        if (nVirtual == 0x70000000 && nPhysical == 0 && nMask == 0x007FFFFF) {
            if (!cpuMapAddress(pCPU, NULL, 0x7F000000, 0x10034B30, 0x01000000)) {
                return false;
            }
        }
    } else {
        iDevice = -1;
    }

    pCPU->aTLB[iEntry][4] = iDevice;
    return true;
}

/**
 * @brief Gets the operating mode of the VR4300
 *
 * @param nStatus The status bits to determine the mode for.
 * @param peMode A pointer to the mode determined.
 * @return bool true on success, false otherwise.
 */
static bool cpuGetMode(u64 nStatus, CpuMode* peMode) {
    if (nStatus & 2) {
        *peMode = CM_KERNEL;
        return true;
    }

    if (!(nStatus & 4)) {
        switch (nStatus & 0x18) {
            case 0x10:
                *peMode = CM_USER;
                break;
            case 8:
                *peMode = CM_SUPER;
                break;
            case 0:
                *peMode = CM_KERNEL;
                break;
            default:
                return false;
        }
        return true;
    }

    NO_INLINE();
    return false;
}

/**
 * @brief Determines the register size that the VR4300 is using.
 *
 * @param nStatus Status bits for determining the register size.
 * @param peSize A pointer to the size determined.
 * @param peMode A pointer to the mode determined.
 * @return bool
 */
static bool cpuGetSize(u64 nStatus, CpuSize* peSize, CpuMode* peMode) {
    CpuMode eMode;

    *peSize = CS_NONE;
    if (peMode != NULL) {
        *peMode = CM_NONE;
    }

    if (cpuGetMode(nStatus, &eMode)) {
        switch (eMode) {
            case CM_USER:
                *peSize = nStatus & 0x20 ? CS_64BIT : CS_32BIT;
                break;
            case CM_SUPER:
                *peSize = nStatus & 0x40 ? CS_64BIT : CS_32BIT;
                break;
            case CM_KERNEL:
                *peSize = nStatus & 0x80 ? CS_64BIT : CS_32BIT;
                break;
            default:
                return false;
        }

        if (peMode != NULL) {
            *peMode = eMode;
        }

        return true;
    }

    return false;
}

/**
 * @brief Sets the status bits of the VR4300
 *
 * @param pCPU The emulated VR4300
 * @param nStatus New status.
 * @param unknown Unused.
 * @return bool true on success, false otherwise.
 */
static bool cpuSetCP0_Status(Cpu* pCPU, u64 nStatus, u32 unknown) {
    CpuMode eMode;
    CpuMode eModeLast;
    CpuSize eSize;
    CpuSize eSizeLast;

    if (!cpuGetSize(nStatus, &eSize, &eMode)) {
        return false;
    }
    if (!cpuGetSize(pCPU->anCP0[12], &eSizeLast, &eModeLast)) {
        return false;
    }

    pCPU->anCP0[12] = nStatus;

    NO_INLINE();
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
bool cpuSetRegisterCP0(Cpu* pCPU, s32 iRegister, s64 nData);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuSetRegisterCP0.s")
#else
bool cpuSetRegisterCP0(Cpu* pCPU, s32 iRegister, s64 nData) {
    s32 pad;
    s32 bFlag = false;

    switch (iRegister) {
        case 1:
        case 7:
        case 8:
            break;
        case 9:
            bFlag = true;
            break;
        case 11:
            bFlag = true;
            xlObjectEvent(pCPU->pHost, 0x1001, (void*)3);
            if (pCPU->nMode & 1 || (nData & ganMaskSetCP0[iRegister]) == 0) {
                pCPU->nMode &= ~1;
            } else {
                pCPU->nMode |= 1;
            }
            break;
        case 12:
            cpuSetCP0_Status(pCPU, nData & ganMaskSetCP0[iRegister], 0);
            break;
        case 13:
            xlObjectEvent(pCPU->pHost, (nData & 0x100) ? 0x1000 : 0x1001, (void*)0);
            xlObjectEvent(pCPU->pHost, (nData & 0x200) ? 0x1000 : 0x1001, (void*)1);
            bFlag = true;
            break;
        case 14:
            bFlag = true;
            break;
        case 16:
            pCPU->anCP0[16] = (u32)(nData & ganMaskSetCP0[iRegister]);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 27:
        case 31:
            break;
        default:
            bFlag = true;
            break;
    }

    if (bFlag) {
        pCPU->anCP0[iRegister] = nData & ganMaskSetCP0[iRegister];
    }

    return true;
}
#endif

// Matches but data doesn't
#ifndef NON_MATCHING
bool cpuGetRegisterCP0(Cpu* pCPU, s32 iRegister, s64* pnData);
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuGetRegisterCP0.s")
#else
bool cpuGetRegisterCP0(Cpu* pCPU, s32 iRegister, s64* pnData) {
    s32 bFlag = false;

    switch (iRegister) {
        case 1:
            *pnData = cpuTLBRandom(pCPU);
            break;
        case 9:
            bFlag = true;
            break;
        case 11:
            bFlag = true;
            break;
        case 14:
            bFlag = true;
            break;
        case 7:
            *pnData = 0;
            break;
        case 8:
            bFlag = true;
            break;
        case 21:
            *pnData = 0;
            break;
        case 22:
            *pnData = 0;
            break;
        case 23:
            *pnData = 0;
            break;
        case 24:
            *pnData = 0;
            break;
        case 25:
            *pnData = 0;
            break;
        case 31:
            *pnData = 0;
            break;
        default:
            bFlag = true;
            break;
    }

    if (bFlag) {
        *pnData = pCPU->anCP0[iRegister] & ganMaskGetCP0[iRegister];
    }

    return true;
}
#endif

/**
 * @brief Sets CP0 values for returnning from an exception.
 *
 * @param pCPU The emulated VR4300.
 * @return bool true on success, false otherwise
 */
bool __cpuERET(Cpu* pCPU) {
    if (pCPU->anCP0[12] & 4) {
        pCPU->nPC = pCPU->anCP0[30];
        pCPU->anCP0[12] &= ~4;
    } else {
        pCPU->nPC = pCPU->anCP0[14];
        pCPU->anCP0[12] &= ~2;
    }

    pCPU->nMode |= 4;
    pCPU->nMode |= 0x20;

    return true;
}

/**
 * @brief Sets flags for handling cpu breakpoints.
 *
 * @param pCPU The emulated VR4300.
 * @return bool true on success, false otherwise
 */
bool __cpuBreak(Cpu* pCPU) {
    pCPU->nMode |= 2;
    return true;
}

/**
 * @brief Maps an object to a cpu device.
 *
 * @param pCPU The emulated VR4300.
 * @param pObject The device that will handle requests for this memory space.
 * @param nAddress0 The start of the memory space for which the device will be responsible.
 * @param nAddress1 The end of the memory space for which the device will be responsible.
 * @param nType An argument which will be passed back to the device on creation.
 * @return bool true on success, false otherwise.
 */
bool cpuMapObject(Cpu* pCPU, void* pObject, u32 nAddress0, u32 nAddress1, s32 nType) {
    s32 iDevice;
    s32 iAddress;
    u32 nAddressVirtual0;
    u32 nAddressVirtual1;

    if (nAddress0 == 0 && nAddress1 == 0xFFFFFFFF) {
        if (!cpuMakeDevice(pCPU, &iDevice, pObject, 0, nAddress0, nAddress1, nType)) {
            return false;
        }

        pCPU->iDeviceDefault = iDevice;
        for (iAddress = 0; iAddress < ARRAY_COUNT(pCPU->aiDevice); iAddress++) {
            pCPU->aiDevice[iAddress] = iDevice;
        }
    } else {
        if (!cpuMakeDevice(pCPU, &iDevice, pObject, nAddress0 + 0x80000000, nAddress0, nAddress1, nType)) {
            return false;
        }

        nAddressVirtual0 = nAddress0 | 0x80000000;
        nAddressVirtual1 = nAddress1 | 0x80000000;
        iAddress = nAddressVirtual0 >> 16;
        while (nAddressVirtual0 < nAddressVirtual1) {
            pCPU->aiDevice[iAddress] = iDevice;
            nAddressVirtual0 += 0x10000;
            iAddress++;
        }

        if (!cpuMakeDevice(pCPU, &iDevice, pObject, nAddress0 + 0x60000000, nAddress0, nAddress1, nType)) {
            return false;
        }

        nAddressVirtual0 = nAddress0 | 0xA0000000;
        nAddressVirtual1 = nAddress1 | 0xA0000000;
        iAddress = nAddressVirtual0 >> 16;
        while (nAddressVirtual0 < nAddressVirtual1) {
            pCPU->aiDevice[iAddress] = iDevice;
            nAddressVirtual0 += 0x10000;
            iAddress++;
        }
    }

    return true;
}

/**
 * @brief Sets load handlers for a device.
 *
 * @param pCPU The emulated VR4300.
 * @param pDevice The device which handles the load operations.
 * @param pfGet8 byte handler.
 * @param pfGet16 halfword handler.
 * @param pfGet32 word handler.
 * @param pfGet64 doubleword handler.
 * @return bool true on success, false otherwise.
 */
bool cpuSetDeviceGet(Cpu* pCPU, CpuDevice* pDevice, Get8Func pfGet8, Get16Func pfGet16, Get32Func pfGet32,
                     Get64Func pfGet64) {
    pDevice->pfGet8 = pfGet8;
    pDevice->pfGet16 = pfGet16;
    pDevice->pfGet32 = pfGet32;
    pDevice->pfGet64 = pfGet64;
    return true;
}

/**
 * @brief Sets store handlers for a device.
 *
 * @param pCPU The emulated VR4300.
 * @param pDevice The device which handles the store operations.
 * @param pfPut8 byte handler.
 * @param pfPut16 halfword handler.
 * @param pfPut32 word handler.
 * @param pfPut64 doubleword handler.
 * @return bool true on success, false otherwise.
 */
bool cpuSetDevicePut(Cpu* pCPU, CpuDevice* pDevice, Put8Func pfPut8, Put16Func pfPut16, Put32Func pfPut32,
                     Put64Func pfPut64) {
    pDevice->pfPut8 = pfPut8;
    pDevice->pfPut16 = pfPut16;
    pDevice->pfPut32 = pfPut32;
    pDevice->pfPut64 = pfPut64;
    return true;
}

bool cpuSetCodeHack(Cpu* pCPU, s32 nAddress, s32 nOpcodeOld, s32 nOpcodeNew) {
    s32 iHack;

    for (iHack = 0; iHack < pCPU->nCountCodeHack; iHack++) {
        if (pCPU->aCodeHack[iHack].nAddress == nAddress) {
            return false;
        }
    }

    pCPU->aCodeHack[iHack].nAddress = nAddress;
    pCPU->aCodeHack[iHack].nOpcodeOld = nOpcodeOld;
    pCPU->aCodeHack[iHack].nOpcodeNew = nOpcodeNew;
    pCPU->nCountCodeHack++;
    return true;
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuReset.s")
#else
bool cpuReset(Cpu* pCPU) {
    s32 iRegister;
    s32 iTLB;

    pCPU->nTick = 0;
    pCPU->nCountCodeHack = 0;
    pCPU->nMode = 0x40;
    pCPU->pfStep = NULL;

    for (iTLB = 0; iTLB < ARRAY_COUNT(pCPU->aTLB); iTLB++) {
        for (iRegister = 0; iRegister < 5; iRegister++) {
            pCPU->aTLB[iTLB][iRegister] = 0;
        }
        pCPU->aTLB[iTLB][4] = -1;
    }

    pCPU->nLo = 0;
    pCPU->nHi = 0;
    pCPU->nPC = 0x80000400;
    pCPU->nWaitPC = -1;

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->aGPR); iRegister++) {
        pCPU->aGPR[iRegister].u64 = 0;
    }

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->aFPR); iRegister++) {
        pCPU->aFPR[iRegister].f64 = 0.0;
    }

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->anFCR); iRegister++) {
        pCPU->anFCR[iRegister] = 0;
    }

    pCPU->aGPR[20].u64 = 1;
    pCPU->aGPR[22].u64 = 0x3F;
    pCPU->aGPR[29].u64 = 0xA4001FF0;

    for (iRegister = 0; iRegister < ARRAY_COUNT(pCPU->anCP0); iRegister++) {
        pCPU->anCP0[iRegister] = 0;
    }

    pCPU->anCP0[15] = 0xB00;
    pCPU->anCP0[9] = 0x10000000;
    cpuSetCP0_Status(pCPU, 0x2000FF01, 1);
    pCPU->anCP0[16] = 0x6E463;

    pCPU->nCountAddress = 0;
    if (cpuHackHandler(pCPU)) {
        pCPU->nMode |= 0x10;
    }

    if (!cpuHeapReset(pCPU->aHeap1Flag, ARRAY_COUNT(pCPU->aHeap1Flag))) {
        return false;
    }
    if (pCPU->gHeap1 == NULL && !xlHeapTake(&pCPU->gHeap1, 0x300000 | 0x30000000)) {
        return false;
    }

    if (!cpuHeapReset(pCPU->aHeap2Flag, ARRAY_COUNT(pCPU->aHeap2Flag))) {
        return false;
    }
    if (pCPU->gHeap2 == NULL && !xlHeapTake(&pCPU->gHeap2, 0x104000 | 0x30000000)) {
        return false;
    }

    if (!cpuHeapReset(aHeapTreeFlag, ARRAY_COUNT(aHeapTreeFlag))) {
        return false;
    }
    if (gHeapTree == NULL && !xlHeapTake(&gHeapTree, 0x46500 | 0x30000000)) {
        return false;
    }

    if (pCPU->gTree != NULL) {
        treeKill(pCPU);
    }

    pCPU->nCompileFlag = 1;
    return true;
}
#endif

bool cpuSetXPC(Cpu* pCPU, s64 nPC, s64 nLo, s64 nHi) {
    if (!xlObjectTest(pCPU, &gClassCPU)) {
        return false;
    }

    pCPU->nMode |= 4;
    pCPU->nPC = nPC;
    pCPU->nLo = nLo;
    pCPU->nHi = nHi;

    return true;
}

static inline bool cpuInitAllDevices(Cpu* pCPU) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pCPU->apDevice); i++) {
        pCPU->apDevice[i] = NULL;
    }

    return true;
}

static inline bool cpuFreeAllDevices(Cpu* pCPU) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(pCPU->apDevice); i++) {
        if (pCPU->apDevice[i] != NULL) {
            if (!cpuFreeDevice(pCPU, i)) {
                return false;
            }
        } else {
            pCPU->apDevice[i] = NULL;
        }
    }

    return true;
}

bool cpuEvent(Cpu* pCPU, s32 nEvent, void* pArgument) {
    switch (nEvent) {
        case 2:
            pCPU->pHost = pArgument;
            cpuInitAllDevices(pCPU);
            if (!cpuReset(pCPU)) {
                return false;
            }
            break;
        case 3:
            if (!cpuFreeAllDevices(pCPU)) {
                return false;
            }
            break;
        case 0:
        case 1:
            break;
#if VERSION != MQ_J
        case 0x1003:
            break;
#endif
        default:
            return false;
    }

    return true;
}

bool cpuGetAddressOffset(Cpu* pCPU, s32* pnOffset, u32 nAddress) {
    s32 iDevice;

    if (0x80000000 <= nAddress && nAddress < 0xC0000000) {
        *pnOffset = nAddress & 0x7FFFFF;
    } else {
        iDevice = pCPU->aiDevice[nAddress >> 0x10];

        if (pCPU->apDevice[iDevice]->nType & 0x100) {
            *pnOffset = (nAddress + pCPU->apDevice[iDevice]->nOffsetAddress) & 0x7FFFFF;
        } else {
            return false;
        }
    }

    return true;
}

bool cpuGetAddressBuffer(Cpu* pCPU, void** ppBuffer, u32 nAddress) {
    CpuDevice* pDevice = pCPU->apDevice[pCPU->aiDevice[nAddress >> 0x10]];

    if ((Ram*)pDevice->pObject == SYSTEM_RAM(pCPU->pHost)) {
        if (!ramGetBuffer(SYSTEM_RAM(pCPU->pHost), ppBuffer, nAddress + pDevice->nOffsetAddress, NULL)) {
            return false;
        }
        return true;
    }

    return false;
}

bool cpuGetOffsetAddress(Cpu* pCPU, u32* anAddress, s32* pnCount, u32 nOffset, u32 nSize) {
    s32 iEntry;
    s32 iAddress = 0;
    u32 nAddress;
    u32 nMask;
    u32 nSizeMapped;

    anAddress[iAddress++] = nOffset | 0x80000000;
    anAddress[iAddress++] = nOffset | 0xA0000000;

    for (iEntry = 0; iEntry < ARRAY_COUNT(pCPU->aTLB); iEntry++) {
        if (pCPU->aTLB[iEntry][0] & 2) {
            nMask = pCPU->aTLB[iEntry][3] | 0x1FFF;

            switch (nMask) {
                case 0x1FFF:
                    nSizeMapped = 4 * 1024;
                    break;
                case 0x7FFF:
                    nSizeMapped = 16 * 1024;
                    break;
                case 0x1FFFF:
                    nSizeMapped = 64 * 1024;
                    break;
                case 0x7FFFF:
                    nSizeMapped = 256 * 1024;
                    break;
                case 0x1FFFFF:
                    nSizeMapped = 1 * 1024 * 1024;
                    break;
                case 0x7FFFFF:
                    nSizeMapped = 4 * 1024 * 1024;
                    break;
                case 0x1FFFFFF:
                    nSizeMapped = 16 * 1024 * 1024;
                    break;
                default:
                    return false;
            }

            nAddress = ((u32)(pCPU->aTLB[iEntry][0] & ~0x3F) << 6) + (nOffset & nMask);
            if (nAddress < (nOffset + nSize - 1) && (nAddress + nSizeMapped - 1) >= nOffset) {
                nAddress = pCPU->aTLB[iEntry][2] & 0xFFFFE000;
                anAddress[iAddress++] = ((nAddress) & ~nMask) | (nOffset & nMask);
            }
        }
    }

    *pnCount = iAddress;
    return true;
}

bool cpuInvalidateCache(Cpu* pCPU, s32 nAddress0, s32 nAddress1) {
    if ((nAddress0 & 0xF0000000) == 0xA0000000) {
        return true;
    }

    if (!cpuFreeCachedAddress(pCPU, nAddress0, nAddress1)) {
        return false;
    }

    cpuDMAUpdateFunction(pCPU, nAddress0, nAddress1);
    return true;
}

bool cpuGetFunctionChecksum(Cpu* pCPU, u32* pnChecksum, CpuFunction* pFunction) {
    s32 nSize;
    u32* pnBuffer;
    u32 nChecksum;
    u32 nData;
    u32 pad;

    if (pFunction->nChecksum != 0) {
        *pnChecksum = pFunction->nChecksum;
        return true;
    }

    if (!cpuGetAddressBuffer(pCPU, (void**)&pnBuffer, pFunction->nAddress0)) {
        return false;
    }

    nChecksum = 0;
    nSize = ((pFunction->nAddress1 - pFunction->nAddress0) >> 2) + 1;

    while (nSize > 0) {
        nSize--;
        nData = *pnBuffer;
        nData = nData >> 0x1A;
        nData = nData << ((nSize % 5) * 6);
        nChecksum += nData;
        pnBuffer++;
    }

    *pnChecksum = nChecksum;
    pFunction->nChecksum = nChecksum;

    return true;
}

static bool cpuHeapReset(u32* array, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        array[i] = 0;
    }

    NO_INLINE();
    return true;
}

bool cpuHeapTake(void* heap, Cpu* pCPU, CpuFunction* pFunction, int memory_size) {
    s32 done;
    s32 second;
    u32* anPack;
    s32 nPackCount;
    int nBlockCount;
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    done = 0;
    second = 0;
    for (;;) {
        if (pFunction->heapID == -1) {
            if (memory_size > 0x3200) {
                pFunction->heapID = 2;
            } else {
                pFunction->heapID = 1;
            }
        } else if (pFunction->heapID == 1) {
            pFunction->heapID = 2;
            second = 1;
        } else if (pFunction->heapID == 2) {
            pFunction->heapID = 1;
            second = 1;
        }

        if (pFunction->heapID == 1) {
            pFunction->heapID = 1;
            nBlockCount = (memory_size + 0x1FF) / 0x200;
            nPackCount = ARRAY_COUNT(pCPU->aHeap1Flag);
            anPack = pCPU->aHeap1Flag;

            if (second && nBlockCount >= 32) {
                pFunction->heapID = 3;
                pFunction->heapWhere = -1;
                if (!xlHeapTake(heap, memory_size)) {
                    return false;
                }
                return true;
            }
        } else if (pFunction->heapID == 2) {
            pFunction->heapID = 2;
            nBlockCount = (memory_size + 0x9FF) / 0xA00;
            nPackCount = ARRAY_COUNT(pCPU->aHeap2Flag);
            anPack = pCPU->aHeap2Flag;
        }

        if (nBlockCount >= 32) {
            pFunction->heapID = 3;
            pFunction->heapWhere = -1;
            if (!xlHeapTake(heap, memory_size)) {
                return false;
            }
            return true;
        }

        nCount = 33 - nBlockCount;
        nMask0 = (1 << nBlockCount) - 1;
        for (iPack = 0; iPack < nPackCount; iPack++) {
            if ((nPack = anPack[iPack]) != -1) {
                nMask = nMask0;
                nOffset = nCount;
                do {
                    if (!(nPack & nMask)) {
                        anPack[iPack] |= nMask;
                        pFunction->heapWhere = (nBlockCount << 16) | ((iPack << 5) + (nCount - nOffset));
                        done = 1;
                        break;
                    }
                    nMask = nMask << 1;
                    nOffset--;
                } while (nOffset != 0);
            }

            if (done) {
                break;
            }
        }

        if (done) {
            break;
        }

        if (second) {
            pFunction->heapID = -1;
            pFunction->heapWhere = -1;
            return false;
        }
    }

    if (pFunction->heapID == 1) {
        *((s32*)heap) = (s32)pCPU->gHeap1 + (pFunction->heapWhere & 0xFFFF) * 0x200;
    } else {
        *((s32*)heap) = (s32)pCPU->gHeap2 + (pFunction->heapWhere & 0xFFFF) * 0xA00;
    }

    return true;
}

bool cpuHeapFree(Cpu* pCPU, CpuFunction* pFunction) {
    u32* anPack;
    s32 iPack;
    u32 nMask;

    if (pFunction->heapID == 1) {
        anPack = pCPU->aHeap1Flag;
    } else if (pFunction->heapID == 2) {
        anPack = pCPU->aHeap2Flag;
    } else {
        if (pFunction->pnBase != NULL) {
            if (!xlHeapFree(&pFunction->pnBase)) {
                return false;
            }
        } else {
            if (!xlHeapFree(&pFunction->pfCode)) {
                return false;
            }
        }

        return true;
    }

    if (pFunction->heapWhere == -1) {
        return false;
    }

    nMask = ((1 << (pFunction->heapWhere >> 16)) - 1) << (pFunction->heapWhere & 0x1F);
    iPack = ((pFunction->heapWhere & 0xFFFF) >> 5);

    if ((anPack[iPack] & nMask) == nMask) {
        anPack[iPack] &= ~nMask;
        pFunction->heapID = -1;
        pFunction->heapWhere = -1;
        return true;
    }

    return false;
}

static bool cpuTreeTake(void* heap, s32* where, s32 size) {
    bool done;
    s32 nOffset;
    s32 nCount;
    s32 iPack;
    u32 nPack;
    u32 nMask;
    u32 nMask0;

    done = false;
    for (iPack = 0; iPack < 125; iPack++) {
        if ((nPack = aHeapTreeFlag[iPack]) != -1) {
            nMask = 1;
            nOffset = 32;
            do {
                if (!(nPack & nMask)) {
                    aHeapTreeFlag[iPack] |= nMask;
                    *where = (1 << 16) | ((iPack << 5) + (32 - nOffset));
                    done = true;
                    break;
                }
                nMask = nMask << 1;
                nOffset--;
            } while (nOffset != 0);
        }

        if (done) {
            break;
        }
    }

    if (!done) {
        *where = -1;
        return false;
    }

    *((s32*)heap) = (s32)gHeapTree + ((*where & 0xFFFF) * sizeof(CpuFunction));

    return true;
}

static inline bool cpuTreeFree(CpuFunction* pFunction) {
    u32* anPack;
    s32 iPack;
    u32 nMask;

    if (pFunction->treeheapWhere == -1) {
        return false;
    }

    anPack = aHeapTreeFlag;
    nMask = ((1 << (pFunction->treeheapWhere >> 16)) - 1) << (pFunction->treeheapWhere & 0x1F);
    iPack = (pFunction->treeheapWhere & 0xFFFF) >> 5;
    if ((anPack[iPack] & nMask) == nMask) {
        anPack[iPack] &= ~nMask;
        return true;
    }

    return false;
}

#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuFindFunction.s")
#else
bool cpuFindFunction(Cpu* pCPU, s32 theAddress, CpuFunction** tree_node) {
    CpuDevice** apDevice;
    u8* aiDevice;
    u32 opcode;
    u8 follow;
    u8 valid;
    u8 check;
    u8 end_flag;
    u8 save_restore;
    u8 alert;
    s32 beginAddress;
    s32 cheat_address;
    s32 current_address;
    s32 temp_address;
    s32 branch;
    int anAddr[3];
    s32 pad;

    save_restore = false;
    alert = false;
    cheat_address = 0;
    if (pCPU->gTree == NULL) {
        check = 0;
        pCPU->survivalTimer = 1;
        if (!xlHeapTake(&pCPU->gTree, sizeof(CpuTreeRoot))) {
            return false;
        }
        treeInit(pCPU, 0x80150002);
    } else {
        check = 1;
        if (treeSearch(pCPU, theAddress, tree_node)) {
            pCPU->pFunctionLast = *tree_node;
            return true;
        }
    }

    anAddr[0] = 0;
    anAddr[1] = 0;
    anAddr[2] = 0;
    aiDevice = pCPU->aiDevice;
    apDevice = pCPU->apDevice;
    beginAddress = branch = theAddress;
    current_address = theAddress;

    do {
        CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
        follow = true;

        if (check == 0) {
            if (opcode != 0 && anAddr[0] == 0) {
                anAddr[0] = current_address;
            }
        } else {
            if (anAddr[0] == 0) {
                anAddr[0] = current_address;
            }
        }

        valid = true;
        end_flag = 0;

        switch ((u8)MIPS_OP(opcode)) {
            case 0x00: { // special
                switch ((u8)MIPS_FUNCT(opcode)) {
                    case 0x08: // jr
                        if (!save_restore && (anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 111;
                        }
                        break;
                    case 0x0D: // break
                        if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 111;
                            save_restore = false;
                        }
                        break;
                    default:
                        valid = SpecialOpcode[MIPS_FUNCT(opcode)];
                        break;
                }
                break;
            }
            case 0x02: // j
                if ((branch = (MIPS_TARGET(opcode) << 2) | (current_address & 0xF0000000)) >= current_address &&
                    branch - current_address <= 0x1000) {
                    if (anAddr[2] == 0) {
                        anAddr[2] = branch;
                    } else if (branch > anAddr[2]) {
                        anAddr[2] = branch;
                    }
                }
                break;
            case 0x01: // regimm
                switch ((u8)MIPS_RT(opcode)) {
                    case 0x00: // bltz
                    case 0x01: // bgez
                    case 0x02: // bltzl
                    case 0x03: // bgezl
                    case 0x10: // bltzal
                    case 0x11: // bgezal
                    case 0x12: // bltzall
                    case 0x13: // bgezall
                        branch = MIPS_IMM_S16(opcode) * 4;
                        if (branch < 0) {
                            if (check == 1 && current_address + branch + 4 < beginAddress) {
                                anAddr[0] = 0;
                                anAddr[1] = 0;
                                anAddr[2] = 0;
                                beginAddress = current_address + branch + 4;
                                current_address = current_address + branch + 4;
                                alert = true;
                                continue;
                            }
                        } else {
                            if (anAddr[1] == 0) {
                                anAddr[1] = current_address + branch;
                            } else if (current_address + branch > anAddr[1]) {
                                anAddr[1] = current_address + branch;
                            }
                        }
                        break;
                    default:
                        valid = RegimmOpcode[MIPS_RT(opcode)];
                        break;
                }
                break;
            case 0x04: // beq
            case 0x14: // beql
                branch = MIPS_IMM_S16(opcode) * 4;
                if (branch < 0) {
                    if (check == 1 && current_address + branch + 4 < beginAddress) {
                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        beginAddress = current_address + branch + 4;
                        current_address = current_address + branch + 4;
                        alert = true;
                        continue;
                    }

                    temp_address = current_address + 8;
                    CPU_DEVICE_GET32(apDevice, aiDevice, temp_address, &opcode);
                    if (opcode == 0) {
                        do {
                            temp_address += 4;
                            CPU_DEVICE_GET32(apDevice, aiDevice, temp_address, &opcode);
                        } while (opcode == 0);

                        if (MIPS_OP(opcode) != 0x23) { // lw
                            current_address = temp_address - 8;
                            if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                                (anAddr[2] == 0 || current_address >= anAddr[2])) {
                                end_flag = 111;
                                save_restore = false;
                            }
                        } else {
                            current_address = temp_address - 4;
                        }
                    }
                } else {
                    if (anAddr[1] == 0) {
                        anAddr[1] = current_address + branch;
                    } else if (current_address + branch > anAddr[1]) {
                        anAddr[1] = current_address + branch;
                    }
                }
                break;
            case 0x05: // bne
            case 0x06: // blez
            case 0x07: // bgtz
            case 0x15: // bnel
            case 0x16: // blezl
            case 0x17: // bgtzl
                branch = MIPS_IMM_S16(opcode) * 4;
                if (branch < 0) {
                    if (check == 1 && current_address + branch + 4 < beginAddress) {
                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        beginAddress = current_address + branch + 4;
                        current_address = current_address + branch + 4;
                        alert = true;
                        continue;
                    }
                } else {
                    if (anAddr[1] == 0) {
                        anAddr[1] = current_address + branch;
                    } else if (current_address + branch > anAddr[1]) {
                        anAddr[1] = current_address + branch;
                    }
                }
                break;
            case 0x10: // cop0
                switch ((u8)MIPS_FUNCT(opcode)) {
                    case 0x01: // tlbr
                    case 0x02: // tlbwi
                    case 0x05: // tlbwr
                    case 0x08: // tlbp
                        break;
                    case 0x18: // eret
                        if ((anAddr[1] == 0 || current_address > anAddr[1]) &&
                            (anAddr[2] == 0 || current_address >= anAddr[2])) {
                            end_flag = 222;
                            save_restore = false;
                        }
                        break;
                    default:
                        switch ((u8)MIPS_FMT(opcode)) {
                            case 0x08:
                                switch (MIPS_FT(opcode)) {
                                    case 0x00:
                                    case 0x01:
                                    case 0x02:
                                    case 0x03:
                                        branch = MIPS_IMM_S16(opcode) * 4;
                                        if (branch < 0) {
                                            if (check == 1 && current_address + branch + 4 < beginAddress) {
                                                anAddr[0] = 0;
                                                anAddr[1] = 0;
                                                anAddr[2] = 0;
                                                beginAddress = current_address + branch + 4;
                                                current_address = current_address + branch + 4;
                                                alert = true;
                                                continue;
                                            }
                                        } else {
                                            if (anAddr[1] == 0) {
                                                anAddr[1] = current_address + branch;
                                            } else if (current_address + branch > anAddr[1]) {
                                                anAddr[1] = current_address + branch;
                                            }
                                        }
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;
            case 0x11: // cop1
                if (MIPS_FMT(opcode) == 0x08) {
                    switch ((u8)MIPS_FT(opcode)) {
                        case 0x00:
                        case 0x01:
                        case 0x02:
                        case 0x03:
                            branch = MIPS_IMM_S16(opcode) * 4;
                            if (branch < 0) {
                                if (check == 1 && current_address + branch + 4 < beginAddress) {
                                    anAddr[0] = 0;
                                    anAddr[1] = 0;
                                    anAddr[2] = 0;
                                    beginAddress = current_address + branch + 4;
                                    current_address = current_address + branch + 4;
                                    alert = true;
                                    continue;
                                }
                            } else {
                                if (anAddr[1] == 0) {
                                    anAddr[1] = current_address + branch;
                                } else if (current_address + branch > anAddr[1]) {
                                    anAddr[1] = current_address + branch;
                                }
                            }
                            break;
                    }
                }
                break;
            case 0x2B: // sw
                if (MIPS_RT(opcode) == 31) {
                    save_restore = true;
                }
                break;
            case 0x23: // lw
                if (MIPS_RT(opcode) == 31) {
                    save_restore = false;
                    if (check == 1 && alert) {
                        current_address = beginAddress;

                        while (true) {
                            CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
                            if (MIPS_OP(opcode) == 0x2B && MIPS_RT(opcode) == 31) { // sw ra, ...
                                break;
                            }
                            current_address -= 4;
                        }

                        do {
                            current_address -= 4;
                            CPU_DEVICE_GET32(apDevice, aiDevice, current_address, &opcode);
                            if (opcode != 0 && treeSearch(pCPU, current_address - 4, tree_node)) {
                                break;
                            }
                        } while (opcode != 0);

                        anAddr[0] = 0;
                        anAddr[1] = 0;
                        anAddr[2] = 0;
                        current_address = beginAddress = current_address + 4;
                        alert = false;
                        continue;
                    }
                }
                break;
            default:
                valid = Opcode[MIPS_OP(opcode)];
                break;
        }

        if (end_flag != 0) {
            if (end_flag == 111) {
                anAddr[2] = current_address + 4;
                current_address += 8;
            } else {
                anAddr[2] = current_address;
                current_address += 4;
            }

            if (check == 0) {
                if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_8013522C)) {
                    if (current_address == 0x800BB62C) {
                        current_address = 0x800BB9B0;
                    } else if (current_address == 0x800CC010) {
                        valid = false;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_80135234)) {
                    if (anAddr[2] == 0x800A9D40) {
                        anAddr[0] = 0x800A9CF0;
                        cheat_address = anAddr[0];
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_8013523C)) {
                    if (current_address == 0x80000470) {
                        current_address = 0x80000870;
                    } else if (anAddr[2] == 0x80001248) {
                        anAddr[2] = 0x80001884;
                        current_address = 0x80001890;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_80135244)) {
                    if (current_address == 0x800829CC) {
                        current_address = 0x80082D60;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_8013524C)) {
                    if (current_address == 0x8000E1C8) {
                        if (!treeInsert(pCPU, 0x8007ED94, 0x8007F55C)) {
                            return false;
                        }
                        treeSearch(pCPU, 0x8007ED94, tree_node);
                        (*tree_node)->timeToLive = 0;
                    }
                } else if (romTestCode(SYSTEM_ROM(pCPU->pHost), D_80135254)) {
                    if (current_address == 0x8000E1C8) {
                        if (!treeInsert(pCPU, 0x8007EC54, 0x8007F41C)) {
                            return false;
                        }
                        treeSearch(pCPU, 0x8007EC54, tree_node);
                        (*tree_node)->timeToLive = 0;
                    }
                }
            }

            if (!treeInsert(pCPU, anAddr[0], anAddr[2])) {
                return false;
            }

            if (cheat_address != 0) {
                treeSearch(pCPU, cheat_address, tree_node);
                cheat_address = 0;
                (*tree_node)->timeToLive = 0;
            }

            if (check == 1) {
                if (treeSearch(pCPU, theAddress, tree_node)) {
                    pCPU->pFunctionLast = *tree_node;
                    return true;
                } else {
                    return false;
                }
            }

            follow = false;
            anAddr[0] = 0;
            anAddr[1] = 0;
            anAddr[2] = 0;
            if (check == 0 && pCPU->gTree->total > 3970) {
                valid = false;
            }
        }

        if (follow) {
            current_address += 4;
        }
    } while (valid);

    if (check == 0) {
        treeInsert(pCPU, 0x80000180, 0x8000018C);
        treeSearch(pCPU, 0x80000180, tree_node);
        (*tree_node)->timeToLive = 0;

        if (treeSearch(pCPU, theAddress, tree_node)) {
            pCPU->pFunctionLast = *tree_node;
            return true;
        } else {
            return false;
        }
    }

    return false;
}
#endif

static bool cpuDMAUpdateFunction(Cpu* pCPU, s32 start, s32 end) {
    CpuTreeRoot* root = pCPU->gTree;
    s32 count;
    bool cancel;

    if (root == NULL) {
        return true;
    }

    if ((start < root->root_address) && (end > root->root_address)) {
        treeAdjustRoot(pCPU, start, end);
    }

    if (root->kill_limit != 0) {
        if (root->restore != NULL) {
            cancel = false;
            if (start <= root->restore->nAddress0) {
                if ((end >= root->restore->nAddress1) || (end >= root->restore->nAddress0)) {
                    cancel = true;
                }
            } else {
                if ((end >= root->restore->nAddress1) &&
                    ((start <= root->restore->nAddress0) || (start <= root->restore->nAddress1))) {
                    cancel = true;
                }
            }
            if (cancel) {
                root->restore = NULL;
                root->restore_side = 0;
            }
        }
    }

    if (start < root->root_address) {
        do {
            count = treeKillRange(pCPU, root->left, start, end);
            root->total = root->total - count;
        } while (count != 0);
    } else {
        do {
            count = treeKillRange(pCPU, root->right, start, end);
            root->total = root->total - count;
        } while (count != 0);
    }

    return true;
}

static inline void treeCallerInit(CpuCallerID* block, s32 total) {
    s32 count;

    for (count = 0; count < total; count++) {
        block[count].N64address = 0;
        block[count].GCNaddress = 0;
    }
}

static inline bool treeCallerKill(Cpu* pCPU, CpuFunction* kill) {
    s32 left;
    s32 right;
    CpuTreeRoot* root;

    if (kill->pfCode != NULL) {
        root = pCPU->gTree;
        left = kill->nAddress0;
        right = kill->nAddress1;

        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x10, &left, &right);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x10, &left, &right);
        }
    }

    pCPU->gTree->total_memory -= kill->memory_size + sizeof(CpuFunction);
    return true;
}

static bool treeCallerCheck(Cpu* pCPU, CpuFunction* tree, bool flag, s32 nAddress0, s32 nAddress1) {
    s32 count;
    s32 saveGCN;
    s32 saveN64;
    s32* addr_function;
    s32* addr_call;
    s32 pad;

    if (tree->callerID_total == 0) {
        return false;
    }

    if (tree->block != NULL) {
        CpuCallerID* block = tree->block;

        for (count = 0; count < tree->callerID_total; count++) {
            saveN64 = block[count].N64address;
            saveGCN = block[count].GCNaddress;
            if (saveN64 >= nAddress0 && saveN64 <= nAddress1 && saveGCN != 0) {
                addr_function = (s32*)saveGCN;
                addr_call = addr_function - (flag ? 3 : 2);

                addr_call[0] = 0x3CA00000 | ((u32)saveN64 >> 16);
                addr_call[1] = 0x60A50000 | ((u32)saveN64 & 0xFFFF);
                addr_function[0] = 0x48000000 | (((u32)pCPU->pfCall - saveGCN) & 0x03FFFFFC) | 1;

                block[count].GCNaddress = 0;
                DCStoreRange(addr_call, 16);
                ICInvalidateRange(addr_call, 16);
            }
        }
    }

    return true;
}

static bool treeInit(Cpu* pCPU, s32 root_address) {
    CpuTreeRoot* root = pCPU->gTree;

    if (root == NULL) {
        return false;
    }

    root->total = 0;
    root->total_memory = 0;
    root->root_address = root_address;
    root->start_range = 0;
    root->end_range = 0x80000000;
    root->left = NULL;
    root->right = NULL;
    root->kill_limit = 0;
    root->kill_number = 0;
    root->side = 0;
    root->restore = NULL;
    root->restore_side = 0;
    return true;
}

static bool treeInitNode(CpuFunction** tree, CpuFunction* prev, s32 start, s32 end) {
    CpuFunction* node;
    s32 where;

    if (!cpuTreeTake(&node, &where, sizeof(CpuFunction))) {
        return false;
    }

    node->nAddress0 = start;
    node->nAddress1 = end;
    node->block = NULL;
    node->callerID_total = 0;
    node->callerID_flag = 0x21;
    node->pnBase = NULL;
    node->pfCode = NULL;
    node->nCountJump = 0;
    node->aJump = NULL;
    node->nChecksum = 0;
    node->timeToLive = 1;
    node->memory_size = 0;
    node->heapID = -1;
    node->heapWhere = -1;
    node->treeheapWhere = where;
    node->prev = prev;
    node->left = NULL;
    node->right = NULL;

    *tree = node;
    return true;
}

static bool treeKill(Cpu* pCPU) {
    CpuTreeRoot* root;
    s32 count;

    count = 0;
    root = pCPU->gTree;
    if (root->left != NULL) {
        count += treeKillNodes(pCPU, root->left);
        treeCallerKill(pCPU, root->left);
        if (root->left->pfCode != NULL) {
            cpuHeapFree(pCPU, root->left);
        }
        if (!cpuTreeFree(root->left)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    if (root->right != NULL) {
        count += treeKillNodes(pCPU, root->right);
        treeCallerKill(pCPU, root->right);
        if (root->right->pfCode != NULL) {
            cpuHeapFree(pCPU, root->right);
        }
        if (!cpuTreeFree(root->right)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    root->total -= count;
    if (!xlHeapFree((void**)&pCPU->gTree)) {
        return false;
    }

    pCPU->gTree = NULL;
    return true;
}

static bool treeKillNodes(Cpu* pCPU, CpuFunction* tree) {
    CpuFunction* current;
    CpuFunction* kill;
    s32 count;

    count = 0;
    if (tree == NULL) {
        return false;
    }
    current = tree;

    do {
        while (current->left != NULL) {
            current = current->left;
        }

        do {
            if (current->right != NULL) {
                current = current->right;
                break;
            }

            if (current == tree) {
                return count;
            }

            while (current != current->prev->left) {
                kill = current;
                current = current->prev;

                treeCallerKill(pCPU, kill);
                if (kill->pfCode != NULL) {
                    cpuHeapFree(pCPU, kill);
                }

                // TODO: regalloc hacks
                (void)kill->treeheapWhere;
                if (!cpuTreeFree(kill)) {
                    return false;
                }
                PAD_STACK();
                PAD_STACK();

                count += 1;
                if (current == tree) {
                    return count;
                }
            }

            kill = current;
            current = current->prev;

            treeCallerKill(pCPU, kill);
            if (kill->pfCode != NULL) {
                cpuHeapFree(pCPU, kill);
            }
            // TODO: regalloc hacks
            (void)kill->treeheapWhere;
            if (!cpuTreeFree(kill)) {
                return false;
            }
            PAD_STACK();
            PAD_STACK();

            count += 1;
        } while (current != NULL);
    } while (current != NULL);

    return count;
}

static bool treeDeleteNode(Cpu* pCPU, CpuFunction** top, CpuFunction* kill) {
    CpuTreeRoot* root;
    CpuFunction* save1;
    CpuFunction* save2;
    CpuFunction* connect;

    root = pCPU->gTree;
    if (kill == NULL) {
        return false;
    }

    root->total--;
    connect = kill->prev;
    save1 = kill->left;
    save2 = kill->right;

    if (connect != NULL) {
        if (save1 != NULL) {
            if (connect->left == kill) {
                connect->left = save1;
            } else {
                connect->right = save1;
            }
            save1->prev = connect;
            if (save2 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                save1->right = save2;
                save2->prev = save1;
            }
        } else if (save2 != NULL) {
            if (connect->left == kill) {
                connect->left = save2;
            } else {
                connect->right = save2;
            }
            save2->prev = connect;
        } else if (connect->left == kill) {
            connect->left = NULL;
        } else {
            connect->right = NULL;
        }
    } else if (save1 != NULL) {
        *top = save1;
        if (root->left == kill) {
            root->left = save1;
        } else {
            root->right = save1;
        }
        save1->prev = NULL;
        if (save2 != NULL) {
            while (save1->right != NULL) {
                save1 = save1->right;
            }
            save1->right = save2;
            save2->prev = save1;
        }
    } else if (save2 != NULL) {
        *top = save2;
        if (root->left == kill) {
            root->left = save2;
        } else {
            root->right = save2;
        }
        save2->prev = NULL;
    } else {
        *top = NULL;
        if (root->left == kill) {
            root->left = NULL;
        } else {
            root->right = NULL;
        }
    }

    if (root->start_range == kill->nAddress0) {
        if (save2 != NULL) {
            while (save2->left != NULL) {
                save2 = save2->left;
            }
            root->start_range = save2->nAddress0;
        } else if (connect != NULL) {
            root->start_range = connect->nAddress0;
        } else {
            root->start_range = root->root_address;
        }
    }

    if (root->end_range == kill->nAddress1) {
        if (save1 != NULL) {
            while (save1->right != NULL) {
                save1 = save1->right;
            }
            root->end_range = save1->nAddress1;
        } else if (connect != NULL) {
            root->end_range = connect->nAddress1;
        } else {
            root->end_range = root->root_address;
        }
    }

    treeCallerKill(pCPU, kill);
    if (kill->pfCode != NULL) {
        cpuHeapFree(pCPU, kill);
    }
    // TODO: regalloc hacks
    (void)kill->treeheapWhere;
    if (!cpuTreeFree(kill)) {
        return false;
    }
    PAD_STACK();
    PAD_STACK();

    return true;
}

bool treeInsert(Cpu* pCPU, s32 start, s32 end) {
    CpuTreeRoot* root;
    CpuFunction* current;
    s32 flag;

    root = pCPU->gTree;
    if (root == NULL) {
        return false;
    }
    if (start < root->root_address && end > root->root_address) {
        treeAdjustRoot(pCPU, start, end);
    }
    root->total++;
    root->total_memory += sizeof(CpuFunction);
    if (start != 0x80000180) {
        if (start < root->start_range) {
            root->start_range = start;
        }
        if (end > root->end_range) {
            root->end_range = end;
        }
    }
    if (start < root->root_address) {
        flag = treeInsertNode(&root->left, start, end, &current);
    } else if (start > root->root_address) {
        flag = treeInsertNode(&root->right, start, end, &current);
    } else {
        return false;
    }

    if (flag != 0) {
        return treeBalance(root);
    }
    return false;
}

static bool treeInsertNode(CpuFunction** tree, s32 start, s32 end, CpuFunction** ppFunction) {
    CpuFunction** current;
    CpuFunction* prev;

    current = tree;
    if (*tree == NULL) {
        if (treeInitNode(current, NULL, start, end)) {
            *ppFunction = *current;
            return true;
        }
        return false;
    }

    do {
        if (start < (*current)->nAddress0) {
            prev = *current;
            current = &(*current)->left;
        } else if (start > (*current)->nAddress0) {
            prev = *current;
            current = &(*current)->right;
        } else {
            return false;
        }
    } while (*current != NULL);

    if (treeInitNode(current, prev, start, end)) {
        *ppFunction = *current;
        return true;
    }
    return false;
}

static bool treeBalance(CpuTreeRoot* root) {
    CpuFunction* tree;
    CpuFunction* current;
    CpuFunction* save;
    s32 total;
    s32 count;

    for (total = 0; total < 2; total++) {
        if (total == 0) {
            tree = root->left;
        } else {
            tree = root->right;
        }

        if (tree != NULL) {
            current = tree;
            count = 0;

            while (current->right != NULL) {
                current = current->right;
                count++;
            }

            if (count >= 12) {
                current = tree;
                save = tree->right;
                count = count / 2;

                while (count-- != 0) {
                    current = current->right;
                }

                current->prev->right = NULL;
                tree->right = current;
                current->prev = tree;

                while (current->left != NULL) {
                    current = current->left;
                }

                current->left = save;
                save->prev = current;
            }

            current = tree;
            count = 0;

            while (current->left != NULL) {
                current = current->left;
                count++;
            }

            if (count >= 12) {
                current = tree;
                save = tree->left;
                count = count / 2;

                while (count-- != 0) {
                    current = current->left;
                }

                current->prev->left = NULL;
                tree->left = current;
                current->prev = tree;

                while (current->right != NULL) {
                    current = current->right;
                }

                current->right = save;
                save->prev = current;
            }
        }
    }

    return true;
}

static bool treeAdjustRoot(Cpu* pCPU, s32 new_start, s32 new_end) {
    s32 old_root;
    s32 new_root = new_end + 2;
    s32 kill_start = 0;
    s32 check1 = 0;
    s32 check2 = 0;
    u16 total;
    s32 total_memory;
    s32 address;
    CpuTreeRoot* root = pCPU->gTree;
    CpuFunction* node = NULL;
    CpuFunction* change = NULL;

    old_root = root->root_address;
    total = root->total;
    total_memory = root->total_memory;
    address = old_root + 2;

    do {
        node = NULL;
        treeSearchNode(root->right, address, &node);
        if (node != NULL) {
            if (kill_start == 0) {
                kill_start = address;
            }

            root->root_address = new_root;
            if (!treeInsert(pCPU, node->nAddress0, node->nAddress1)) {
                return false;
            }
            if (!treeSearchNode(root->left, address, &change)) {
                return false;
            }

            change->timeToLive = node->timeToLive;
            change->memory_size = node->memory_size;
            if (node->pfCode != NULL) {
                change->pfCode = node->pfCode;
                node->pfCode = NULL;
            }
            change->nCountJump = node->nCountJump;
            if (node->aJump != NULL) {
                change->aJump = node->aJump;
                node->aJump = NULL;
            }
            change->nChecksum = node->nChecksum;
            change->callerID_flag = node->callerID_flag;
            change->callerID_total = node->callerID_total;
            if (node->callerID_total != 0) {
                change->block = node->block;
                node->block = NULL;
            }

            address = node->nAddress1;
            root->root_address = old_root;
            check2 += treeKillRange(pCPU, root->right, node->nAddress0, node->nAddress1 - 4);
        }

        address += 4;
    } while (address <= new_end);

    root->root_address = new_root;
    root->total = total;
    root->total_memory = total_memory;
    return true;
}

static inline bool treeSearch(Cpu* pCPU, s32 target, CpuFunction** node) {
    CpuTreeRoot* root = pCPU->gTree;
    bool flag;

    if (target < root->root_address) {
        flag = treeSearchNode(root->left, target, node);
    } else {
        flag = treeSearchNode(root->right, target, node);
    }
    return flag;
}

static bool treeSearchNode(CpuFunction* tree, s32 target, CpuFunction** node) {
    CpuFunction* current;

    current = tree;
    if (current == NULL) {
        return false;
    }

    do {
        if (target >= current->nAddress0 && target < current->nAddress1) {
            *node = current;
            return true;
        }
        if (target < current->nAddress0) {
            current = current->left;
        } else if (target > current->nAddress0) {
            current = current->right;
        } else {
            current = NULL;
        }
    } while (current != NULL);

    return false;
}

static bool treeKillRange(Cpu* pCPU, CpuFunction* tree, s32 start, s32 end) {
    CpuTreeRoot* root = pCPU->gTree;
    CpuFunction* node1 = NULL;
    CpuFunction* node2 = NULL;
    CpuFunction* save1;
    CpuFunction* save2;
    CpuFunction* connect;
    bool update = false;
    s32 count = 0;

    if (start < root->start_range && end < root->start_range) {
        return false;
    }
    if (start > root->end_range && end > root->end_range) {
        return false;
    }

    do {
        treeSearchNode(tree, start, &node1);
        if (node1 != NULL) {
            break;
        }
        start += 4;
    } while (start < end);

    if (node1 != NULL) {
        connect = node1->prev;
        node1->prev = NULL;
        save1 = node1->left;
        node1->left = NULL;
        save2 = node1->right;

        while (save2 != NULL) {
            if (save2->nAddress0 < end) {
                if (save2->nAddress1 == root->end_range) {
                    update = true;
                }
                save2 = save2->right;
            } else if (save2 == NULL) {
                break;
            } else {
                save2->prev->right = NULL;
                break;
            }
        }

        if (connect != NULL) {
            if (save1 != NULL) {
                if (connect->left == node1) {
                    connect->left = save1;
                } else {
                    connect->right = save1;
                }
                save1->prev = connect;
                if (save2 != NULL) {
                    while (save1->right != NULL) {
                        save1 = save1->right;
                    }
                    save1->right = save2;
                    save2->prev = save1;
                }
            } else if (save2 != NULL) {
                if (connect->left == node1) {
                    connect->left = save2;
                } else {
                    connect->right = save2;
                }
                save2->prev = connect;
            } else if (connect->left == node1) {
                connect->left = NULL;
            } else {
                connect->right = NULL;
            }
        } else if (save1 != NULL) {
            tree = save1;
            if (root->left == node1) {
                root->left = save1;
            } else {
                root->right = save1;
            }
            save1->prev = NULL;
            if (save2 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                save1->right = save2;
                save2->prev = save1;
            }
        } else if (save2 != NULL) {
            tree = save2;
            if (root->left == node1) {
                root->left = save2;
            } else {
                root->right = save2;
            }
            save2->prev = NULL;
        } else {
            tree = NULL;
            if (root->left == node1) {
                root->left = NULL;
            } else {
                root->right = NULL;
            }
        }
        if (root->start_range == node1->nAddress0) {
            if (save2 != NULL) {
                while (save2->left != NULL) {
                    save2 = save2->left;
                }
                root->start_range = save2->nAddress0;
            } else if (connect != NULL) {
                root->start_range = connect->nAddress0;
            } else {
                root->start_range = root->root_address;
            }
        }

        if (update) {
            if (save1 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                root->end_range = save1->nAddress1;
            } else if (connect != NULL) {
                root->end_range = connect->nAddress1;
            } else {
                root->end_range = root->root_address;
            }
        }

        count += treeKillNodes(pCPU, node1);
        treeCallerKill(pCPU, node1);
        if (node1->pfCode != NULL) {
            cpuHeapFree(pCPU, node1);
        }
        if (!cpuTreeFree(node1)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    do {
        treeSearchNode(tree, end, &node2);
        if (node2 != NULL) {
            break;
        }
        end -= 4;
    } while (start < end);

    if (node2 != NULL) {
        connect = node2->prev;
        node2->prev = NULL;
        save1 = node2->left;
        save2 = node2->right;
        node2->right = NULL;

        while (save1 != NULL) {
            if (save1->nAddress0 > start) {
                save1 = save1->left;
            } else if (save1 != NULL) {
                save1->prev->left = NULL;
                break;
            } else {
                break;
            }
        }

        if (connect != NULL) {
            if (save2 != NULL) {
                if (connect->left == node2) {
                    connect->left = save2;
                } else {
                    connect->right = save2;
                }
                save2->prev = connect;
                if (save1 != NULL) {
                    while (save2->left != NULL) {
                        save2 = save2->left;
                    }
                    save2->left = save1;
                    save1->prev = save2;
                }
            } else if (save1 != NULL) {
                if (connect->left == node2) {
                    connect->left = save1;
                } else {
                    connect->right = save1;
                }
                save1->prev = connect;
            } else if (connect->left == node2) {
                connect->left = NULL;
            } else {
                connect->right = NULL;
            }
        } else if (save2 != NULL) {
            if (root->left == node2) {
                root->left = save2;
            } else {
                root->right = save2;
            }
            save2->prev = NULL;
            if (save1 != NULL) {
                while (save2->left != NULL) {
                    save2 = save2->left;
                }
                save2->left = save1;
                save1->prev = save2;
            }
        } else if (save1 != NULL) {
            if (root->left == node2) {
                root->left = save1;
            } else {
                root->right = save1;
            }
            save1->prev = NULL;
        } else if (root->left == node2) {
            root->left = NULL;
        } else {
            root->right = NULL;
        }

        if (root->end_range == node2->nAddress1) {
            if (save1 != NULL) {
                while (save1->right != NULL) {
                    save1 = save1->right;
                }
                root->end_range = save1->nAddress1;
            } else if (connect != NULL) {
                root->end_range = connect->nAddress1;
            } else {
                root->end_range = root->root_address;
            }
        }

        count += treeKillNodes(pCPU, node2);
        treeCallerKill(pCPU, node2);
        if (node2->pfCode != NULL) {
            cpuHeapFree(pCPU, node2);
        }
        if (!cpuTreeFree(node2)) {
            return false;
        }
        PAD_STACK();
        PAD_STACK();

        count++;
    }

    return count;
}

static bool treeKillReason(Cpu* pCPU, s32* value) {
    if (pCPU->survivalTimer < 300) {
        return false;
    }
    if (pCPU->survivalTimer == 300) {
        *value = 1;
        return true;
    }
    if (pCPU->survivalTimer % 400 == 0 && treeMemory(pCPU) > 3250000) {
        *value = pCPU->survivalTimer - 200;
        return true;
    }

    NO_INLINE();
    return false;
}

static bool treeTimerCheck(Cpu* pCPU) {
    CpuTreeRoot* root;
    s32 begin;
    s32 end;

    if (pCPU->survivalTimer > 0x7FFFF000) {
        root = pCPU->gTree;
        if (root->kill_limit != 0) {
            return false;
        }
        begin = 0;
        end = 0x7FFFF000;
        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x100, &begin, &end);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x100, &begin, &end);
        }
        begin = end - 3;
        if (root->left != NULL) {
            treePrintNode(pCPU, root->left, 0x1000, &begin, &end);
        }
        if (root->right != NULL) {
            treePrintNode(pCPU, root->right, 0x1000, &begin, &end);
        }
        pCPU->survivalTimer -= begin;
        return true;
    }
    return false;
}

static bool treeCleanUp(Cpu* pCPU, CpuTreeRoot* root) {
    bool done = false;
    bool complete = false;
    s32 pad;

    if (root->side == 0) {
        done = treeCleanNodes(pCPU, root->left);
    }
    if ((root->side != 0 || done) && treeCleanNodes(pCPU, root->right)) {
        complete = true;
    }
    if (!complete) {
        return false;
    }

    if (treeMemory(pCPU) > 0x400000) {
        root->kill_limit = pCPU->survivalTimer - 10;
    } else if (treeMemory(pCPU) > 3250000) {
        root->kill_limit += 95;
        if (root->kill_limit > pCPU->survivalTimer - 10) {
            root->kill_limit = pCPU->survivalTimer - 10;
        }
    } else {
        root->kill_limit = 0;
        root->restore = NULL;
        root->restore_side = 0;
    }

    return true;
}

static bool treeCleanNodes(Cpu* pCPU, CpuFunction* top) {
    CpuFunction** current;
    CpuFunction* kill = NULL;
    CpuTreeRoot* root = pCPU->gTree;
    s32 kill_limit = root->kill_limit;
    CpuFunction* temp;

    if (top == NULL) {
        root->side ^= 1;
        return true;
    }

    current = &root->restore;
    if (root->restore == NULL) {
        *current = top;
    }

    while (*current != NULL) {
        if (pCPU->nRetrace != pCPU->nRetraceUsed || root->kill_number >= 12) {
            break;
        }

        if (root->restore_side == 0) {
            while ((*current)->left != NULL) {
                *current = (*current)->left;
            }
            root->restore_side = 1;
        }

        while (*current != NULL) {
            if (pCPU->nRetrace != pCPU->nRetraceUsed || root->kill_number >= 12) {
                break;
            }

            if (kill != NULL) {
                if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                    return false;
                }
                if (!treeDeleteNode(pCPU, &top, kill)) {
                    return false;
                }
                kill = NULL;
                root->kill_number++;
            }

            temp = *current;
            if (temp->timeToLive > 0 && temp->timeToLive <= kill_limit) {
                kill = *current;
            }

            if ((*current)->right != NULL) {
                *current = (*current)->right;
                root->restore_side = 0;
                break;
            }

            if (*current == top) {
                if (kill != NULL) {
                    if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                        return false;
                    }
                    if (!treeDeleteNode(pCPU, &top, kill)) {
                        return false;
                    }
                }

                root->side ^= 1;
                *current = NULL;
                root->restore_side = 0;
                return true;
            }

            while (*current != (*current)->prev->left) {
                *current = (*current)->prev;
                if (*current == top) {
                    if (kill != NULL) {
                        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                            return false;
                        }
                        if (!treeDeleteNode(pCPU, &top, kill)) {
                            return false;
                        }
                    }

                    root->side ^= 1;
                    *current = NULL;
                    root->restore_side = 0;
                    return true;
                }
            }

            *current = (*current)->prev;
            root->restore_side = 1;
        }
    }

    if (kill != NULL) {
        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
            return false;
        }
        if (!treeDeleteNode(pCPU, &top, kill)) {
            return false;
        }
    }
    return false;
}

static inline bool treeForceCleanUp(Cpu* pCPU, CpuFunction* tree, s32 kill_limit) {
    CpuTreeRoot* root = pCPU->gTree;

    root->kill_limit = 0;
    root->restore = NULL;
    root->restore_side = 0;
    if (tree != NULL && tree->timeToLive > 0) {
        tree->timeToLive = pCPU->survivalTimer;
    }
    if (root->side == 0) {
        if (root->left != NULL) {
            treeForceCleanNodes(pCPU, root->left, kill_limit);
        }
    } else {
        if (root->right != NULL) {
            treeForceCleanNodes(pCPU, root->right, kill_limit);
        }
    }
    root->side ^= 1;
    return true;
}

static bool treeForceCleanNodes(Cpu* pCPU, CpuFunction* tree, s32 kill_limit) {
    CpuFunction* current;
    CpuFunction* kill = NULL;

    if (tree == NULL) {
        return false;
    }
    current = tree;

    do {
        while (current->left != NULL) {
            current = current->left;
        }

        do {
            if (kill != NULL) {
                if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                    return false;
                }
                if (!treeDeleteNode(pCPU, &tree, kill)) {
                    return false;
                }
                kill = NULL;
            }

            if (current->timeToLive > 0 && current->timeToLive <= kill_limit) {
                kill = current;
            }

            if (current->right != NULL) {
                current = current->right;
                break;
            }

            if (current == tree) {
                if (kill != NULL) {
                    if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                        return false;
                    }
                    if (!treeDeleteNode(pCPU, &tree, kill)) {
                        return false;
                    }
                }
                return true;
            }

            while (current != current->prev->left) {
                current = current->prev;
                if (current == tree) {
                    if (kill != NULL) {
                        if (!cpuFreeCachedAddress(pCPU, kill->nAddress0, kill->nAddress1)) {
                            return false;
                        }
                        if (!treeDeleteNode(pCPU, &tree, kill)) {
                            return false;
                        }
                    }
                    return true;
                }
            }

            current = current->prev;
        } while (current != NULL);
    } while (current != NULL);

    return false;
}

static bool treePrintNode(Cpu* pCPU, CpuFunction* tree, s32 print_flag, s32* left, s32* right) {
    CpuFunction* current;
    bool flag;
    s32 level;

    level = 0;
    if (tree == NULL) {
        return false;
    }

    flag = ganMapGPR[31] & 0x100 ? true : false;
    current = tree;

    while (true) {
        while (current->left != NULL) {
            current = current->left;
            level++;
            if (print_flag & 1) {
                if (level > *left) {
                    (*left)++;
                }
            }
        }

        do {
            if (print_flag & 0x10) {
                treeCallerCheck(pCPU, current, flag, *left, *right);
            } else if (print_flag & 0x100) {
                if (current->timeToLive > 0) {
                    if (current->timeToLive > *left) {
                        *left = current->timeToLive;
                    }
                    if (current->timeToLive < *right) {
                        *right = current->timeToLive;
                    }
                }
            } else if (print_flag & 0x1000) {
                if (current->timeToLive > 0) {
                    current->timeToLive -= *left;
                }
            } else if (print_flag & 1) {
                OSReport(D_800EC054, current->nAddress0, current->nAddress1, current->timeToLive, current->memory_size);
            }

            if (current->right != NULL) {
                current = current->right;
                level++;
                if (print_flag & 1) {
                    if (level > *right) {
                        (*right)++;
                    }
                }
                break;
            }

            if (current == tree) {
                return true;
            }

            while (current != current->prev->left) {
                current = current->prev;
                level -= 1;
                if (current == tree) {
                    return true;
                }
            }

            current = current->prev;
        } while (current != NULL);

        if (current == NULL) {
            return false;
        }
    }

    return false;
}

static inline s32 treeMemory(Cpu* pCPU) {
    if (pCPU->gTree == NULL) {
        return 0;
    } else {
        return pCPU->gTree->total_memory;
    }
}

// Matches but data doesn't
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/non_matchings/cpu/cpuOpcodeChecksum.s")
#else
s32 cpuOpcodeChecksum(u32 opcode) {
    s32 nChecksum = 0x20;

    if (opcode == 0) {
        return 0;
    }

    switch (MIPS_OP(opcode)) {
        case 0x01:
            switch (MIPS_RT(opcode)) {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                    nChecksum = 4;
                    break;
            }
            break;
        case 0x10:
            switch (MIPS_FUNCT(opcode)) {
                case 0x01:
                case 0x02:
                case 0x05:
                case 0x08:
                case 0x18:
                    break;
                default:
                case 0x00:
                case 0x03:
                case 0x04:
                case 0x06:
                case 0x07:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                    switch (MIPS_FMT(opcode)) {
                        case 8:
                            switch (MIPS_FT(opcode)) {
                                case 0x00:
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                    nChecksum = 4;
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 0x11:
            if (MIPS_RS(opcode) == 0x08) {
                switch (MIPS_RT(opcode)) {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                        nChecksum = 4;
                        break;
                }
            }
            break;
        case 0x02:
            nChecksum = 1;
            break;
        case 0x03:
            nChecksum = 1;
            break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            nChecksum = 4;
            break;
        case 0x09:
        case 0x0D:
        case 0x0F:
            nChecksum = 0x10;
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x28:
        case 0x29:
        case 0x2B:
        case 0x31:
        case 0x35:
        case 0x37:
        case 0x39:
        case 0x3D:
        case 0x3F:
            nChecksum = 0x10;
            break;
    }

    return nChecksum;
}
#endif
