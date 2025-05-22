#include "emulator/rsp.h"

static bool rspInitAudioDMEM1(Rsp* pRSP);
static bool rspInitAudioDMEM2(Rsp* pRSP);
static bool rspInitAudioDMEM3(Rsp* pRSP);
static bool rspInitAudioDMEM4(Rsp* pRSP);

static bool rspParseABI1(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI2(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI3(Rsp* pRSP, RspTask* pTask);
static bool rspParseABI4(Rsp* pRSP, RspTask* pTask);

static bool rspInitAudioDMEM1(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x1470;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1B38;
    pRSP->anAudioBuffer[0x00C] = 0x1214;
    pRSP->anAudioBuffer[0x00D] = 0x187C;
    pRSP->anAudioBuffer[0x00E] = 0x1254;
    pRSP->anAudioBuffer[0x00F] = 0x12D0;
    pRSP->anAudioBuffer[0x010] = 0x12EC;
    pRSP->anAudioBuffer[0x011] = 0x1328;
    pRSP->anAudioBuffer[0x012] = 0x140C;
    pRSP->anAudioBuffer[0x013] = 0x1294;
    pRSP->anAudioBuffer[0x014] = 0x1E24;
    pRSP->anAudioBuffer[0x015] = 0x138C;
    pRSP->anAudioBuffer[0x016] = 0x170C;
    pRSP->anAudioBuffer[0x017] = 0x144C;
    pRSP->anAudioBuffer[0x018] = 0xF000;
    pRSP->anAudioBuffer[0x019] = 0x0F00;
    pRSP->anAudioBuffer[0x01A] = 0x00F0;
    pRSP->anAudioBuffer[0x01B] = 0x000F;
    pRSP->anAudioBuffer[0x01C] = 0x0001;
    pRSP->anAudioBuffer[0x01D] = 0x0010;
    pRSP->anAudioBuffer[0x01E] = 0x0100;
    pRSP->anAudioBuffer[0x01F] = 0x1000;
    pRSP->anAudioBuffer[0x020] = 0x0002;
    pRSP->anAudioBuffer[0x021] = 0x0004;
    pRSP->anAudioBuffer[0x022] = 0x0006;
    pRSP->anAudioBuffer[0x023] = 0x0008;
    pRSP->anAudioBuffer[0x024] = 0x000A;
    pRSP->anAudioBuffer[0x025] = 0x000C;
    pRSP->anAudioBuffer[0x026] = 0x000E;
    pRSP->anAudioBuffer[0x027] = 0x0010;
    pRSP->anAudioBuffer[0x028] = 0x0001;
    pRSP->anAudioBuffer[0x029] = 0x0001;
    pRSP->anAudioBuffer[0x02A] = 0x0001;
    pRSP->anAudioBuffer[0x02B] = 0x0001;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0001;
    pRSP->anAudioBuffer[0x02E] = 0x0001;
    pRSP->anAudioBuffer[0x02F] = 0x0001;
    pRSP->anAudioBuffer[0x030] = 0x0000;
    pRSP->anAudioBuffer[0x031] = 0x0001;
    pRSP->anAudioBuffer[0x032] = 0x0002;
    pRSP->anAudioBuffer[0x033] = 0x0004;
    pRSP->anAudioBuffer[0x034] = 0x0008;
    pRSP->anAudioBuffer[0x035] = 0x0010;
    pRSP->anAudioBuffer[0x036] = 0x0100;
    pRSP->anAudioBuffer[0x037] = 0x0200;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0000;
    pRSP->anAudioBuffer[0x03A] = 0x0000;
    pRSP->anAudioBuffer[0x03B] = 0x0000;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0000;
    pRSP->anAudioBuffer[0x03E] = 0x0000;
    pRSP->anAudioBuffer[0x03F] = 0x0000;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0000;
    pRSP->anAudioBuffer[0x043] = 0x0000;
    pRSP->anAudioBuffer[0x044] = 0x0000;
    pRSP->anAudioBuffer[0x045] = 0x0001;
    pRSP->anAudioBuffer[0x046] = 0x0000;
    pRSP->anAudioBuffer[0x047] = 0x0000;
    pRSP->anAudioBuffer[0x048] = 0x0000;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0001;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0000;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0001;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0000;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0001;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0000;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0001;
    pRSP->anAudioBuffer[0x058] = 0x2000;
    pRSP->anAudioBuffer[0x059] = 0x4000;
    pRSP->anAudioBuffer[0x05A] = 0x6000;
    pRSP->anAudioBuffer[0x05B] = 0x8000;
    pRSP->anAudioBuffer[0x05C] = 0xA000;
    pRSP->anAudioBuffer[0x05D] = 0xC000;
    pRSP->anAudioBuffer[0x05E] = 0xE000;
    pRSP->anAudioBuffer[0x05F] = 0xFFFF;
    pRSP->anAudioBuffer[0x060] = 0x0C39;
    pRSP->anAudioBuffer[0x061] = 0x66AD;
    pRSP->anAudioBuffer[0x062] = 0x0D46;
    pRSP->anAudioBuffer[0x063] = 0xFFDF;
    pRSP->anAudioBuffer[0x064] = 0x0B39;
    pRSP->anAudioBuffer[0x065] = 0x6696;
    pRSP->anAudioBuffer[0x066] = 0x0E5F;
    pRSP->anAudioBuffer[0x067] = 0xFFD8;
    pRSP->anAudioBuffer[0x068] = 0x0A44;
    pRSP->anAudioBuffer[0x069] = 0x6669;
    pRSP->anAudioBuffer[0x06A] = 0x0F83;
    pRSP->anAudioBuffer[0x06B] = 0xFFD0;
    pRSP->anAudioBuffer[0x06C] = 0x095A;
    pRSP->anAudioBuffer[0x06D] = 0x6626;
    pRSP->anAudioBuffer[0x06E] = 0x10B4;
    pRSP->anAudioBuffer[0x06F] = 0xFFC8;
    pRSP->anAudioBuffer[0x070] = 0x087D;
    pRSP->anAudioBuffer[0x071] = 0x65CD;
    pRSP->anAudioBuffer[0x072] = 0x11F0;
    pRSP->anAudioBuffer[0x073] = 0xFFBF;
    pRSP->anAudioBuffer[0x074] = 0x07AB;
    pRSP->anAudioBuffer[0x075] = 0x655E;
    pRSP->anAudioBuffer[0x076] = 0x1338;
    pRSP->anAudioBuffer[0x077] = 0xFFB6;
    pRSP->anAudioBuffer[0x078] = 0x06E4;
    pRSP->anAudioBuffer[0x079] = 0x64D9;
    pRSP->anAudioBuffer[0x07A] = 0x148C;
    pRSP->anAudioBuffer[0x07B] = 0xFFAC;
    pRSP->anAudioBuffer[0x07C] = 0x0628;
    pRSP->anAudioBuffer[0x07D] = 0x643F;
    pRSP->anAudioBuffer[0x07E] = 0x15EB;
    pRSP->anAudioBuffer[0x07F] = 0xFFA1;
    pRSP->anAudioBuffer[0x080] = 0x0577;
    pRSP->anAudioBuffer[0x081] = 0x638F;
    pRSP->anAudioBuffer[0x082] = 0x1756;
    pRSP->anAudioBuffer[0x083] = 0xFF96;
    pRSP->anAudioBuffer[0x084] = 0x04D1;
    pRSP->anAudioBuffer[0x085] = 0x62CB;
    pRSP->anAudioBuffer[0x086] = 0x18CB;
    pRSP->anAudioBuffer[0x087] = 0xFF8A;
    pRSP->anAudioBuffer[0x088] = 0x0435;
    pRSP->anAudioBuffer[0x089] = 0x61F3;
    pRSP->anAudioBuffer[0x08A] = 0x1A4C;
    pRSP->anAudioBuffer[0x08B] = 0xFF7E;
    pRSP->anAudioBuffer[0x08C] = 0x03A4;
    pRSP->anAudioBuffer[0x08D] = 0x6106;
    pRSP->anAudioBuffer[0x08E] = 0x1BD7;
    pRSP->anAudioBuffer[0x08F] = 0xFF71;
    pRSP->anAudioBuffer[0x090] = 0x031C;
    pRSP->anAudioBuffer[0x091] = 0x6007;
    pRSP->anAudioBuffer[0x092] = 0x1D6C;
    pRSP->anAudioBuffer[0x093] = 0xFF64;
    pRSP->anAudioBuffer[0x094] = 0x029F;
    pRSP->anAudioBuffer[0x095] = 0x5EF5;
    pRSP->anAudioBuffer[0x096] = 0x1F0B;
    pRSP->anAudioBuffer[0x097] = 0xFF56;
    pRSP->anAudioBuffer[0x098] = 0x022A;
    pRSP->anAudioBuffer[0x099] = 0x5DD0;
    pRSP->anAudioBuffer[0x09A] = 0x20B3;
    pRSP->anAudioBuffer[0x09B] = 0xFF48;
    pRSP->anAudioBuffer[0x09C] = 0x01BE;
    pRSP->anAudioBuffer[0x09D] = 0x5C9A;
    pRSP->anAudioBuffer[0x09E] = 0x2264;
    pRSP->anAudioBuffer[0x09F] = 0xFF3A;
    pRSP->anAudioBuffer[0x0A0] = 0x015B;
    pRSP->anAudioBuffer[0x0A1] = 0x5B53;
    pRSP->anAudioBuffer[0x0A2] = 0x241E;
    pRSP->anAudioBuffer[0x0A3] = 0xFF2C;
    pRSP->anAudioBuffer[0x0A4] = 0x0101;
    pRSP->anAudioBuffer[0x0A5] = 0x59FC;
    pRSP->anAudioBuffer[0x0A6] = 0x25E0;
    pRSP->anAudioBuffer[0x0A7] = 0xFF1E;
    pRSP->anAudioBuffer[0x0A8] = 0x00AE;
    pRSP->anAudioBuffer[0x0A9] = 0x5896;
    pRSP->anAudioBuffer[0x0AA] = 0x27A9;
    pRSP->anAudioBuffer[0x0AB] = 0xFF10;
    pRSP->anAudioBuffer[0x0AC] = 0x0063;
    pRSP->anAudioBuffer[0x0AD] = 0x5720;
    pRSP->anAudioBuffer[0x0AE] = 0x297A;
    pRSP->anAudioBuffer[0x0AF] = 0xFF02;
    pRSP->anAudioBuffer[0x0B0] = 0x001F;
    pRSP->anAudioBuffer[0x0B1] = 0x559D;
    pRSP->anAudioBuffer[0x0B2] = 0x2B50;
    pRSP->anAudioBuffer[0x0B3] = 0xFEF4;
    pRSP->anAudioBuffer[0x0B4] = 0xFFE2;
    pRSP->anAudioBuffer[0x0B5] = 0x540D;
    pRSP->anAudioBuffer[0x0B6] = 0x2D2C;
    pRSP->anAudioBuffer[0x0B7] = 0xFEE8;
    pRSP->anAudioBuffer[0x0B8] = 0xFFAC;
    pRSP->anAudioBuffer[0x0B9] = 0x5270;
    pRSP->anAudioBuffer[0x0BA] = 0x2F0D;
    pRSP->anAudioBuffer[0x0BB] = 0xFEDB;
    pRSP->anAudioBuffer[0x0BC] = 0xFF7C;
    pRSP->anAudioBuffer[0x0BD] = 0x50C7;
    pRSP->anAudioBuffer[0x0BE] = 0x30F3;
    pRSP->anAudioBuffer[0x0BF] = 0xFED0;
    pRSP->anAudioBuffer[0x0C0] = 0xFF53;
    pRSP->anAudioBuffer[0x0C1] = 0x4F14;
    pRSP->anAudioBuffer[0x0C2] = 0x32DC;
    pRSP->anAudioBuffer[0x0C3] = 0xFEC6;
    pRSP->anAudioBuffer[0x0C4] = 0xFF2E;
    pRSP->anAudioBuffer[0x0C5] = 0x4D57;
    pRSP->anAudioBuffer[0x0C6] = 0x34C8;
    pRSP->anAudioBuffer[0x0C7] = 0xFEBD;
    pRSP->anAudioBuffer[0x0C8] = 0xFF0F;
    pRSP->anAudioBuffer[0x0C9] = 0x4B91;
    pRSP->anAudioBuffer[0x0CA] = 0x36B6;
    pRSP->anAudioBuffer[0x0CB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0CC] = 0xFEF5;
    pRSP->anAudioBuffer[0x0CD] = 0x49C2;
    pRSP->anAudioBuffer[0x0CE] = 0x38A5;
    pRSP->anAudioBuffer[0x0CF] = 0xFEB0;
    pRSP->anAudioBuffer[0x0D0] = 0xFEDF;
    pRSP->anAudioBuffer[0x0D1] = 0x47ED;
    pRSP->anAudioBuffer[0x0D2] = 0x3A95;
    pRSP->anAudioBuffer[0x0D3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0D4] = 0xFECE;
    pRSP->anAudioBuffer[0x0D5] = 0x4611;
    pRSP->anAudioBuffer[0x0D6] = 0x3C85;
    pRSP->anAudioBuffer[0x0D7] = 0xFEAB;
    pRSP->anAudioBuffer[0x0D8] = 0xFEC0;
    pRSP->anAudioBuffer[0x0D9] = 0x4430;
    pRSP->anAudioBuffer[0x0DA] = 0x3E74;
    pRSP->anAudioBuffer[0x0DB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0DC] = 0xFEB6;
    pRSP->anAudioBuffer[0x0DD] = 0x424A;
    pRSP->anAudioBuffer[0x0DE] = 0x4060;
    pRSP->anAudioBuffer[0x0DF] = 0xFEAF;
    pRSP->anAudioBuffer[0x0E0] = 0xFEAF;
    pRSP->anAudioBuffer[0x0E1] = 0x4060;
    pRSP->anAudioBuffer[0x0E2] = 0x424A;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEAC;
    pRSP->anAudioBuffer[0x0E5] = 0x3E74;
    pRSP->anAudioBuffer[0x0E6] = 0x4430;
    pRSP->anAudioBuffer[0x0E7] = 0xFEC0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEAB;
    pRSP->anAudioBuffer[0x0E9] = 0x3C85;
    pRSP->anAudioBuffer[0x0EA] = 0x4611;
    pRSP->anAudioBuffer[0x0EB] = 0xFECE;
    pRSP->anAudioBuffer[0x0EC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0ED] = 0x3A95;
    pRSP->anAudioBuffer[0x0EE] = 0x47ED;
    pRSP->anAudioBuffer[0x0EF] = 0xFEDF;
    pRSP->anAudioBuffer[0x0F0] = 0xFEB0;
    pRSP->anAudioBuffer[0x0F1] = 0x38A5;
    pRSP->anAudioBuffer[0x0F2] = 0x49C2;
    pRSP->anAudioBuffer[0x0F3] = 0xFEF5;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x36B6;
    pRSP->anAudioBuffer[0x0F6] = 0x4B91;
    pRSP->anAudioBuffer[0x0F7] = 0xFF0F;
    pRSP->anAudioBuffer[0x0F8] = 0xFEBD;
    pRSP->anAudioBuffer[0x0F9] = 0x34C8;
    pRSP->anAudioBuffer[0x0FA] = 0x4D57;
    pRSP->anAudioBuffer[0x0FB] = 0xFF2E;
    pRSP->anAudioBuffer[0x0FC] = 0xFEC6;
    pRSP->anAudioBuffer[0x0FD] = 0x32DC;
    pRSP->anAudioBuffer[0x0FE] = 0x4F14;
    pRSP->anAudioBuffer[0x0FF] = 0xFF53;
    pRSP->anAudioBuffer[0x100] = 0xFED0;
    pRSP->anAudioBuffer[0x101] = 0x30F3;
    pRSP->anAudioBuffer[0x102] = 0x50C7;
    pRSP->anAudioBuffer[0x103] = 0xFF7C;
    pRSP->anAudioBuffer[0x104] = 0xFEDB;
    pRSP->anAudioBuffer[0x105] = 0x2F0D;
    pRSP->anAudioBuffer[0x106] = 0x5270;
    pRSP->anAudioBuffer[0x107] = 0xFFAC;
    pRSP->anAudioBuffer[0x108] = 0xFEE8;
    pRSP->anAudioBuffer[0x109] = 0x2D2C;
    pRSP->anAudioBuffer[0x10A] = 0x540D;
    pRSP->anAudioBuffer[0x10B] = 0xFFE2;
    pRSP->anAudioBuffer[0x10C] = 0xFEF4;
    pRSP->anAudioBuffer[0x10D] = 0x2B50;
    pRSP->anAudioBuffer[0x10E] = 0x559D;
    pRSP->anAudioBuffer[0x10F] = 0x001F;
    pRSP->anAudioBuffer[0x110] = 0xFF02;
    pRSP->anAudioBuffer[0x111] = 0x297A;
    pRSP->anAudioBuffer[0x112] = 0x5720;
    pRSP->anAudioBuffer[0x113] = 0x0063;
    pRSP->anAudioBuffer[0x114] = 0xFF10;
    pRSP->anAudioBuffer[0x115] = 0x27A9;
    pRSP->anAudioBuffer[0x116] = 0x5896;
    pRSP->anAudioBuffer[0x117] = 0x00AE;
    pRSP->anAudioBuffer[0x118] = 0xFF1E;
    pRSP->anAudioBuffer[0x119] = 0x25E0;
    pRSP->anAudioBuffer[0x11A] = 0x59FC;
    pRSP->anAudioBuffer[0x11B] = 0x0101;
    pRSP->anAudioBuffer[0x11C] = 0xFF2C;
    pRSP->anAudioBuffer[0x11D] = 0x241E;
    pRSP->anAudioBuffer[0x11E] = 0x5B53;
    pRSP->anAudioBuffer[0x11F] = 0x015B;
    pRSP->anAudioBuffer[0x120] = 0xFF3A;
    pRSP->anAudioBuffer[0x121] = 0x2264;
    pRSP->anAudioBuffer[0x122] = 0x5C9A;
    pRSP->anAudioBuffer[0x123] = 0x01BE;
    pRSP->anAudioBuffer[0x124] = 0xFF48;
    pRSP->anAudioBuffer[0x125] = 0x20B3;
    pRSP->anAudioBuffer[0x126] = 0x5DD0;
    pRSP->anAudioBuffer[0x127] = 0x022A;
    pRSP->anAudioBuffer[0x128] = 0xFF56;
    pRSP->anAudioBuffer[0x129] = 0x1F0B;
    pRSP->anAudioBuffer[0x12A] = 0x5EF5;
    pRSP->anAudioBuffer[0x12B] = 0x029F;
    pRSP->anAudioBuffer[0x12C] = 0xFF64;
    pRSP->anAudioBuffer[0x12D] = 0x1D6C;
    pRSP->anAudioBuffer[0x12E] = 0x6007;
    pRSP->anAudioBuffer[0x12F] = 0x031C;
    pRSP->anAudioBuffer[0x130] = 0xFF71;
    pRSP->anAudioBuffer[0x131] = 0x1BD7;
    pRSP->anAudioBuffer[0x132] = 0x6106;
    pRSP->anAudioBuffer[0x133] = 0x03A4;
    pRSP->anAudioBuffer[0x134] = 0xFF7E;
    pRSP->anAudioBuffer[0x135] = 0x1A4C;
    pRSP->anAudioBuffer[0x136] = 0x61F3;
    pRSP->anAudioBuffer[0x137] = 0x0435;
    pRSP->anAudioBuffer[0x138] = 0xFF8A;
    pRSP->anAudioBuffer[0x139] = 0x18CB;
    pRSP->anAudioBuffer[0x13A] = 0x62CB;
    pRSP->anAudioBuffer[0x13B] = 0x04D1;
    pRSP->anAudioBuffer[0x13C] = 0xFF96;
    pRSP->anAudioBuffer[0x13D] = 0x1756;
    pRSP->anAudioBuffer[0x13E] = 0x638F;
    pRSP->anAudioBuffer[0x13F] = 0x0577;
    pRSP->anAudioBuffer[0x140] = 0xFFA1;
    pRSP->anAudioBuffer[0x141] = 0x15EB;
    pRSP->anAudioBuffer[0x142] = 0x643F;
    pRSP->anAudioBuffer[0x143] = 0x0628;
    pRSP->anAudioBuffer[0x144] = 0xFFAC;
    pRSP->anAudioBuffer[0x145] = 0x148C;
    pRSP->anAudioBuffer[0x146] = 0x64D9;
    pRSP->anAudioBuffer[0x147] = 0x06E4;
    pRSP->anAudioBuffer[0x148] = 0xFFB6;
    pRSP->anAudioBuffer[0x149] = 0x1338;
    pRSP->anAudioBuffer[0x14A] = 0x655E;
    pRSP->anAudioBuffer[0x14B] = 0x07AB;
    pRSP->anAudioBuffer[0x14C] = 0xFFBF;
    pRSP->anAudioBuffer[0x14D] = 0x11F0;
    pRSP->anAudioBuffer[0x14E] = 0x65CD;
    pRSP->anAudioBuffer[0x14F] = 0x087D;
    pRSP->anAudioBuffer[0x150] = 0xFFC8;
    pRSP->anAudioBuffer[0x151] = 0x10B4;
    pRSP->anAudioBuffer[0x152] = 0x6626;
    pRSP->anAudioBuffer[0x153] = 0x095A;
    pRSP->anAudioBuffer[0x154] = 0xFFD0;
    pRSP->anAudioBuffer[0x155] = 0x0F83;
    pRSP->anAudioBuffer[0x156] = 0x6669;
    pRSP->anAudioBuffer[0x157] = 0x0A44;
    pRSP->anAudioBuffer[0x158] = 0xFFD8;
    pRSP->anAudioBuffer[0x159] = 0x0E5F;
    pRSP->anAudioBuffer[0x15A] = 0x6696;
    pRSP->anAudioBuffer[0x15B] = 0x0B39;
    pRSP->anAudioBuffer[0x15C] = 0xFFDF;
    pRSP->anAudioBuffer[0x15D] = 0x0D46;
    pRSP->anAudioBuffer[0x15E] = 0x66AD;
    pRSP->anAudioBuffer[0x15F] = 0x0C39;

    return true;
}

bool rspDotProduct8x15MatrixBy15x1Vector(Rsp* pRSP, s16* matrix, s16* vectorIn, s16* vectorOut) {
    s32 sum;
    s32 vec0 = vectorIn[0];
    s32 vec1 = vectorIn[1];
    s32 vec2 = vectorIn[2];
    s32 vec3 = vectorIn[3];
    s32 vec4 = vectorIn[4];
    s32 vec5 = vectorIn[5];
    s32 vec6 = vectorIn[6];
    s32 vec7 = vectorIn[7];
    s32 vec8 = vectorIn[8];
    s32 vec9 = vectorIn[9];
    s32 vec10 = vectorIn[10];
    s32 vec11 = vectorIn[11];
    s32 vec12 = vectorIn[12];
    s32 vec13 = vectorIn[13];
    s32 vec14 = vectorIn[14];

    sum = matrix[0] * vec0;
    sum += matrix[1] * vec1;
    sum += matrix[2] * vec2;
    sum += matrix[3] * vec3;
    sum += matrix[4] * vec4;
    sum += matrix[5] * vec5;
    sum += matrix[6] * vec6;
    sum += matrix[7] * vec7;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[0] = sum;

    sum = matrix[0] * vec1;
    sum += matrix[1] * vec2;
    sum += matrix[2] * vec3;
    sum += matrix[3] * vec4;
    sum += matrix[4] * vec5;
    sum += matrix[5] * vec6;
    sum += matrix[6] * vec7;
    sum += matrix[7] * vec8;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[1] = sum;

    sum = matrix[0] * vec2;
    sum += matrix[1] * vec3;
    sum += matrix[2] * vec4;
    sum += matrix[3] * vec5;
    sum += matrix[4] * vec6;
    sum += matrix[5] * vec7;
    sum += matrix[6] * vec8;
    sum += matrix[7] * vec9;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[2] = sum;

    sum = matrix[0] * vec3;
    sum += matrix[1] * vec4;
    sum += matrix[2] * vec5;
    sum += matrix[3] * vec6;
    sum += matrix[4] * vec7;
    sum += matrix[5] * vec8;
    sum += matrix[6] * vec9;
    sum += matrix[7] * vec10;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[3] = sum;

    sum = matrix[0] * vec4;
    sum += matrix[1] * vec5;
    sum += matrix[2] * vec6;
    sum += matrix[3] * vec7;
    sum += matrix[4] * vec8;
    sum += matrix[5] * vec9;
    sum += matrix[6] * vec10;
    sum += matrix[7] * vec11;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[4] = sum;

    sum = matrix[0] * vec5;
    sum += matrix[1] * vec6;
    sum += matrix[2] * vec7;
    sum += matrix[3] * vec8;
    sum += matrix[4] * vec9;
    sum += matrix[5] * vec10;
    sum += matrix[6] * vec11;
    sum += matrix[7] * vec12;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[5] = sum;

    sum = matrix[0] * vec6;
    sum += matrix[1] * vec7;
    sum += matrix[2] * vec8;
    sum += matrix[3] * vec9;
    sum += matrix[4] * vec10;
    sum += matrix[5] * vec11;
    sum += matrix[6] * vec12;
    sum += matrix[7] * vec13;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[6] = sum;

    sum = matrix[0] * vec7;
    sum += matrix[1] * vec8;
    sum += matrix[2] * vec9;
    sum += matrix[3] * vec10;
    sum += matrix[4] * vec11;
    sum += matrix[5] * vec12;
    sum += matrix[6] * vec13;
    sum += matrix[7] * vec14;
    sum >>= 15;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[7] = sum;

    return true;
}

bool rspMultPolef(Rsp* pRSP, s16 (*matrix)[8], s16* vectorIn, s16* vectorOut) {
    s32 sum;
    s32 vec0 = vectorIn[0];
    s32 vec1 = vectorIn[1];
    s32 vec2 = vectorIn[2];
    s32 vec3 = vectorIn[3];
    s32 vec4 = vectorIn[4];
    s32 vec5 = vectorIn[5];
    s32 vec6 = vectorIn[6];
    s32 vec7 = vectorIn[7];
    s32 vec8 = vectorIn[8];
    s32 vec9 = vectorIn[9];

    sum = matrix[0][0] * vec0;
    sum += matrix[1][0] * vec1;
    sum += matrix[9][0] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[0] = sum;

    sum = matrix[0][1] * vec0;
    sum += matrix[1][1] * vec1;
    sum += matrix[2][1] * vec2;
    sum += matrix[9][1] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[1] = sum;

    sum = matrix[0][2] * vec0;
    sum += matrix[1][2] * vec1;
    sum += matrix[2][2] * vec2;
    sum += matrix[3][2] * vec3;
    sum += matrix[9][2] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[2] = sum;

    sum = matrix[0][3] * vec0;
    sum += matrix[1][3] * vec1;
    sum += matrix[2][3] * vec2;
    sum += matrix[3][3] * vec3;
    sum += matrix[4][3] * vec4;
    sum += matrix[9][3] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[3] = sum;

    sum = matrix[0][4] * vec0;
    sum += matrix[1][4] * vec1;
    sum += matrix[2][4] * vec2;
    sum += matrix[3][4] * vec3;
    sum += matrix[4][4] * vec4;
    sum += matrix[5][4] * vec5;
    sum += matrix[9][4] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[4] = sum;

    sum = matrix[0][5] * vec0;
    sum += matrix[1][5] * vec1;
    sum += matrix[2][5] * vec2;
    sum += matrix[3][5] * vec3;
    sum += matrix[4][5] * vec4;
    sum += matrix[5][5] * vec5;
    sum += matrix[6][5] * vec6;
    sum += matrix[9][5] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[5] = sum;

    sum = matrix[0][6] * vec0;
    sum += matrix[1][6] * vec1;
    sum += matrix[2][6] * vec2;
    sum += matrix[3][6] * vec3;
    sum += matrix[4][6] * vec4;
    sum += matrix[5][6] * vec5;
    sum += matrix[6][6] * vec6;
    sum += matrix[7][6] * vec7;
    sum += matrix[9][6] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[6] = sum;

    sum = matrix[0][7] * vec0;
    sum += matrix[1][7] * vec1;
    sum += matrix[2][7] * vec2;
    sum += matrix[3][7] * vec3;
    sum += matrix[4][7] * vec4;
    sum += matrix[5][7] * vec5;
    sum += matrix[6][7] * vec6;
    sum += matrix[7][7] * vec7;
    sum += matrix[8][7] * vec8;
    sum += matrix[9][7] * vec9;
    sum >>= 16;
    sum <<= 2;
    if (sum > 0x7FFF) {
        sum = 0x7FFF;
    } else if (sum < -0x8000) {
        sum = -0x8000;
    }
    vectorOut[7] = sum;

    return true;
}

static bool rspLoadADPCMCoefTable1(Rsp* pRSP) {
    u32 i;
    u32 j;
    u32 nCoefIndex;

    nCoefIndex = (s32)pRSP->nAudioADPCMOffset / 2;
    for (j = 0; j < 4; j++, nCoefIndex += 16) {
        for (i = 0; i < 8; i++) {
            pRSP->anADPCMCoef[j][0][i] = pRSP->anAudioBuffer[nCoefIndex + 0 + i];
            pRSP->anADPCMCoef[j][1][i] = pRSP->anAudioBuffer[nCoefIndex + 8 + i];
        }
    }

    return true;
}

static bool rspLoadADPCMCoefTable2(Rsp* pRSP) {
    u32 i;
    u32 j;
    u32 nCoefIndex;

    nCoefIndex = (s32)pRSP->nAudioADPCMOffset / 2;
    for (j = 0; j < 4; j++, nCoefIndex += 16) {
        for (i = 0; i < 8; i++) {
            pRSP->anADPCMCoef[j][0][i] = pRSP->anAudioBuffer[nCoefIndex + 0 + i];
            pRSP->anADPCMCoef[j][1][i] = pRSP->anAudioBuffer[nCoefIndex + 8 + i];
        }
    }

    return true;
}

static inline bool rspALoadBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]], pData, pRSP->nAudioCount[1]);
    }

    return true;
}

static bool rspAADPCMDec1Fast(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u8 ucControl;
    s8* pHeader;
    s16* pStateAddress;
    s16 anIData0;
    s16 anIData1;
    s32 pad1[4];
    s32 nDMEMOut;
    s32 nCount;
    s32 nSrcAddress;
    s32 nOptPred;
    s32 nVScale;
    int i;
    u32 dwDecodeSelect;
    s32 nLogScale;
    s16 nInput0;
    s16 nInput1;
    u32 n;
    s32 nA;
    s32 nB;
    s16 nSamp1;
    s16 nSamp2;
    s16* pTempStateAddr;
    s32 nOutput;
    s32 pad2[4];

    nFlags = (nCommandHi >> 16) & 0xFF;
    pHeader = (s8*)pRSP->anAudioBuffer + pRSP->nAudioDMEMIn[1];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    nCount = pRSP->nAudioCount[0];
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    if (!(nFlags & 1)) {
        pTempStateAddr = pStateAddress;
        if (nFlags & 2) {
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pTempStateAddr, pRSP->nAudioLoopAddress, NULL)) {
                return false;
            }
        }

        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = pTempStateAddr[i];
        }
    } else {
        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = 0;
        }
    }

    nDMEMOut += 16;
    if (nCount == 0) {
        for (i = 0; i < 16; i++) {
            pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
        }
        return true;
    }

    while (nCount > 0) {
        ucControl = *pHeader;
        pHeader++;
        dwDecodeSelect = (ucControl & 0xF) << 5;
        if (dwDecodeSelect == 0x00) {
            nOptPred = 0;
        } else if (dwDecodeSelect == 0x20) {
            nOptPred = 1;
        } else if (dwDecodeSelect == 0x40) {
            nOptPred = 2;
        } else if (dwDecodeSelect == 0x60) {
            nOptPred = 3;
        } else {
            nOptPred = 4;
            dwDecodeSelect = (dwDecodeSelect / 2) + ((s32)pRSP->nAudioADPCMOffset / 2);
            for (i = 0; i < 8; i++) {
                pRSP->anADPCMCoef[4][0][i] = pRSP->anAudioBuffer[dwDecodeSelect + 0 + i];
                pRSP->anADPCMCoef[4][1][i] = pRSP->anAudioBuffer[dwDecodeSelect + 8 + i];
            }
        }

        nA = pRSP->anADPCMCoef[nOptPred][0][0];
        nB = pRSP->anADPCMCoef[nOptPred][1][0];
        nSamp2 = pRSP->anAudioBuffer[nDMEMOut - 2];
        nSamp1 = pRSP->anAudioBuffer[nDMEMOut - 1];

        for (n = 0; n < 16; n += 2) {
            nLogScale = 12 - (ucControl >> 4);
            nInput0 = ((*pHeader >> 4) & 0xF) << 12;
            nInput1 = ((*pHeader >> 0) & 0xF) << 12;
            pHeader++;

            nVScale = (0x8000 >> (nLogScale - 1)) & 0xFFFF;
            if (nLogScale > 0) {
                anIData0 = (nInput0 * nVScale) >> 16;
            } else {
                anIData0 = nInput0;
            }

            nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData0 << 11))) >> 16;
            nOutput <<= 5;
            if (nOutput > 0x7FFF) {
                nOutput = 0x7FFF;
            } else if (nOutput < -0x8000) {
                nOutput = -0x8000;
            }

            nSamp2 = nSamp1;
            nSamp1 = nOutput;
            pRSP->anAudioBuffer[nDMEMOut + n] = nOutput;

            nVScale = (0x8000 >> (nLogScale - 1)) & 0xFFFF;
            if (nLogScale > 0) {
                anIData1 = (nInput1 * nVScale) >> 16;
            } else {
                anIData1 = nInput1;
            }

            nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData1 << 11))) >> 16;
            nOutput <<= 5;
            if (nOutput > 0x7FFF) {
                nOutput = 0x7FFF;
            } else if (nOutput < -0x8000) {
                nOutput = -0x8000;
            }

            nSamp2 = nSamp1;
            nSamp1 = nOutput;
            pRSP->anAudioBuffer[nDMEMOut + n + 1] = nOutput;
        }

        nDMEMOut += 16;
        nCount -= 16;
    }

    for (i = 0; i < 16; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
    }

    return true;
}

static inline bool rspAClearBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    memset(&pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) + pRSP->nAudioMemOffset) / 2], 0, nCommandLo & 0xFFFF);
    return true;
}

static bool rspAPoleFilter1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u16 nScale;
    s16 anCoef[10][8];
    s16 anEntries[8];
    s16 nVTemp[8];
    s16 nTempScale;
    s16 anIData0[8];
    s16 anOData0[8];
    s16 anInputVec[10];
    s16* pStateAddress;
    s16* pDMEM16;
    s32 nDMEMIn;
    s32 nDMEMOut;
    int nCount;
    s32 nSrcAddress;
    int i;

    nCount = pRSP->nAudioCount[0];
    if (nCount == 0) {
        return true;
    }

    for (i = 0; i < 4; i++) {
        anOData0[i] = 0;
    }
    nFlags = (nCommandHi >> 16) & 0xFF;
    nScale = nCommandHi & 0xFFFF;
    nDMEMIn = pRSP->nAudioDMEMIn[0];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    pDMEM16 = pRSP->anAudioBuffer;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + 0] = 0;
    pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + 1] = 0;

    if (!(nFlags & 1)) {
        for (i = 0; i < 4; i++) {
            pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + i] = pStateAddress[i];
        }
    }

    nTempScale = (nScale & 0x3FFF) << 2;
    for (i = 0; i < 8; i++) {
        anCoef[1][i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i];
        nVTemp[i] = ((s32)anCoef[1][i] * (s32)nTempScale) >> 16;
    }

    for (i = 4; i < 8; i++) {
        anOData0[i] = pDMEM16[(s32)pRSP->nAudioScratchOffset / 2 + i - 4];
    }

    for (i = 0; i < 8; i++) {
        pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i] = nVTemp[i];
    }

    for (i = 0; i < 8; i++) {
        anCoef[0][i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 0 + i];
        anEntries[i] = pDMEM16[(s32)pRSP->nAudioADPCMOffset / 2 + 8 + i];
    }

    anCoef[2][0] = 0;
    anCoef[2][1] = anEntries[0];
    anCoef[2][2] = anEntries[1];
    anCoef[2][3] = anEntries[2];
    anCoef[2][4] = anEntries[3];
    anCoef[2][5] = anEntries[4];
    anCoef[2][6] = anEntries[5];
    anCoef[2][7] = anEntries[6];
    anCoef[3][0] = 0;
    anCoef[3][1] = 0;
    anCoef[3][2] = anEntries[0];
    anCoef[3][3] = anEntries[1];
    anCoef[3][4] = anEntries[2];
    anCoef[3][5] = anEntries[3];
    anCoef[3][6] = anEntries[4];
    anCoef[3][7] = anEntries[5];
    anCoef[4][0] = 0;
    anCoef[4][1] = 0;
    anCoef[4][2] = 0;
    anCoef[4][3] = anEntries[0];
    anCoef[4][4] = anEntries[1];
    anCoef[4][5] = anEntries[2];
    anCoef[4][6] = anEntries[3];
    anCoef[4][7] = anEntries[4];
    anCoef[5][0] = 0;
    anCoef[5][1] = 0;
    anCoef[5][2] = 0;
    anCoef[5][3] = 0;
    anCoef[5][4] = anEntries[0];
    anCoef[5][5] = anEntries[1];
    anCoef[5][6] = anEntries[2];
    anCoef[5][7] = anEntries[3];
    anCoef[6][0] = 0;
    anCoef[6][1] = 0;
    anCoef[6][2] = 0;
    anCoef[6][3] = 0;
    anCoef[6][4] = 0;
    anCoef[6][5] = anEntries[0];
    anCoef[6][6] = anEntries[1];
    anCoef[6][7] = anEntries[2];
    anCoef[7][0] = 0;
    anCoef[7][1] = 0;
    anCoef[7][2] = 0;
    anCoef[7][3] = 0;
    anCoef[7][4] = 0;
    anCoef[7][5] = 0;
    anCoef[7][6] = anEntries[0];
    anCoef[7][7] = anEntries[1];
    anCoef[8][0] = 0;
    anCoef[8][1] = 0;
    anCoef[8][2] = 0;
    anCoef[8][3] = 0;
    anCoef[8][4] = 0;
    anCoef[8][5] = 0;
    anCoef[8][6] = 0;
    anCoef[8][7] = anEntries[0];

    for (i = 0; i < 8; i++) {
        anIData0[i] = pDMEM16[nDMEMIn + i];
    }

    anInputVec[9] = nScale;

    while (nCount > 0) {
        for (i = 0; i < 8; i++) {
            anCoef[9][i] = anIData0[i];
        }

        anInputVec[0] = anOData0[6];
        anInputVec[1] = anOData0[7];
        anInputVec[2] = anIData0[0];
        anInputVec[3] = anIData0[1];
        anInputVec[4] = anIData0[2];
        anInputVec[5] = anIData0[3];
        anInputVec[6] = anIData0[4];
        anInputVec[7] = anIData0[5];
        anInputVec[8] = anIData0[6];

        rspMultPolef(pRSP, anCoef, anInputVec, anOData0);

        nDMEMIn += 8;
        for (i = 0; i < 8; i++) {
            pDMEM16[nDMEMOut + i] = anOData0[i];
            anIData0[i] = pDMEM16[nDMEMIn + i];
        }

        nDMEMOut += 8;
        nCount -= 8;
    }

    for (i = 0; i < 4; i++) {
        pStateAddress[i] = pDMEM16[nDMEMOut - 4 + i];
    }

    return true;
}

static bool rspAEnvMixer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 state[8];
    u8 nFlags;
    u32 s;
    s16* pStateAddress;
    u16 anRamp[8];
    s32 envVolRateL;
    s32 envVolRateR;
    s32 envVolFinalL;
    s32 envVolFinalR;
    s32 volVecL[8];
    s32 volVecR[8];
    s32 nStateOffset;
    s16 anOutL;
    s16 anOutR;
    s16 anAuxL;
    s16 anAuxR;
    s16 anIn;
    u32 nInptr;
    u32 nOutptrL;
    u32 nOutptrR;
    u32 nAuxptrL;
    u32 nAuxptrR;
    u32 i;
    u32 nSrcAddress;
    u32 nLoopCtl;
    s32 nUpDownVolL;
    s32 nUpDownVolR;
    void* pData;
    s32* dataP;
    s64 tempL;
    s64 tempR;
    s64 totalL;
    s64 totalR;
    s64 resultL;
    s64 resultR;
    s32 volL;
    s32 volR;
    s64 temp;
    s16 temp_sp10E;
    s16 temp_sp10C;
    s32 pad[3];

    nStateOffset = 0x7C8;
    nFlags = (nCommandHi >> 16) & 0xFF;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nSrcAddress, NULL)) {
        return false;
    }
    pStateAddress = pData;

    if (nFlags & 1) { // A_INIT
        for (s = 0; s < 8; s++) {
            pRSP->anAudioBuffer[0x7E8 + s] = pRSP->anAudioBuffer[0x1B8 + s];
        }
    } else {
        dataP = (s32*)&pRSP->anAudioBuffer[nStateOffset];

        for (i = 0; i < 40; i++) {
            pRSP->anAudioBuffer[nStateOffset + i] = pStateAddress[i];
        }

        for (s = 0; s < 8; s++) {
            volVecL[s] = dataP[2 * s + 0];
            volVecR[s] = dataP[2 * s + 1];
        }
    }

    for (s = 0; s < 8; s++) {
        state[s] = pRSP->anAudioBuffer[0x7E8 + s];
    }

    temp_sp10E = state[1];
    temp_sp10C = state[4];
    envVolRateL = (state[2] & 0xFFFF) + (state[1] << 16);
    envVolRateR = (state[5] & 0xFFFF) + (state[4] << 16);
    envVolFinalL = state[0] << 16;
    envVolFinalR = state[3] << 16;

    nInptr = pRSP->nAudioDMEMIn[0];
    nOutptrL = pRSP->nAudioDMEMOut[0];
    nOutptrR = pRSP->nAudioDMOutR[0];
    nAuxptrL = pRSP->nAudioDMauxL[0];
    nAuxptrR = pRSP->nAudioDMauxR[0];
    nLoopCtl = pRSP->nAudioCount[0];

    for (s = 0; s < 8; s++) {
        anRamp[s] = pRSP->anAudioBuffer[0x58 + s];
    }

    if (nFlags & 1) { // A_INIT
        totalL = pRSP->anAudioBuffer[0x1B3] << 16;
        tempL = (totalL >> 16) * envVolRateL - totalL;
        totalR = pRSP->anAudioBuffer[0x1B4] << 16;
        tempR = (totalR >> 16) * envVolRateR - totalR;

        for (s = 0; s < 8; s++) {
            resultL = (anRamp[s] * tempL) >> 16;
            resultR = (anRamp[s] * tempR) >> 16;

            resultL += totalL;
            resultR += totalR;

            if ((s32)temp_sp10E > 0) {
                if (resultL > envVolFinalL) {
                    volVecL[s] = envVolFinalL;
                } else {
                    volVecL[s] = resultL;
                }
            } else {
                if (resultL < envVolFinalL) {
                    volVecL[s] = envVolFinalL;
                } else {
                    volVecL[s] = resultL;
                }
            }

            if ((s32)temp_sp10C > 0) {
                if (resultR > envVolFinalR) {
                    volVecR[s] = envVolFinalR;
                } else {
                    volVecR[s] = resultR;
                }
            } else {
                if (resultR < envVolFinalR) {
                    volVecR[s] = envVolFinalR;
                } else {
                    volVecR[s] = resultR;
                }
            }
        }
    }

    do {
        for (s = 0; s < 8; s++) {
            volL = volVecL[s] >> 16;
            volR = volVecR[s] >> 16;

            anIn = pRSP->anAudioBuffer[nInptr];
            anOutL = pRSP->anAudioBuffer[nOutptrL];
            anOutR = pRSP->anAudioBuffer[nOutptrR];

            temp = anOutL + (((((s64)volL * (s64)state[6]) >> 15) * (s64)anIn) >> 15);
            if (temp > 0x7FFF) {
                anOutL = 0x7FFF;
            } else if (temp < -0x7FFF) {
                anOutL = -0x7FFF;
            } else {
                anOutL = temp;
            }

            temp = anOutR + (((((s64)volR * (s64)state[6]) >> 15) * (s64)anIn) >> 15);
            if (temp > 0x7FFF) {
                anOutR = 0x7FFF;
            } else if (temp < -0x7FFF) {
                anOutR = -0x7FFF;
            } else {
                anOutR = temp;
            }

            pRSP->anAudioBuffer[nOutptrL] = anOutL;
            pRSP->anAudioBuffer[nOutptrR] = anOutR;

            if (nFlags & 8) { // A_AUX
                anAuxL = pRSP->anAudioBuffer[nAuxptrL];
                anAuxR = pRSP->anAudioBuffer[nAuxptrR];

                temp = anAuxL + (((((s64)volL * (s64)state[7]) >> 15) * (s64)anIn) >> 15);
                if (temp > 0x7FFF) {
                    anAuxL = 0x7FFF;
                } else if (temp < -0x7FFF) {
                    anAuxL = -0x7FFF;
                } else {
                    anAuxL = temp;
                }

                // bug: anAuxR is not added here
                temp = (((((s64)volR * (s64)state[7]) >> 15) * (s64)anIn) >> 15);
                if (temp > 0x7FFF) {
                    anAuxR = 0x7FFF;
                } else if (temp < -0x7FFF) {
                    anAuxR = -0x7FFF;
                } else {
                    anAuxR = temp;
                }

                pRSP->anAudioBuffer[nAuxptrL] = anAuxL;
                pRSP->anAudioBuffer[nAuxptrR] = anAuxR;

                nAuxptrL++;
                nAuxptrR++;
            }

            resultL = volVecL[s];
            resultL = (resultL * envVolRateL) >> 16;
            if ((s32)temp_sp10E > 0) {
                if (resultL > envVolFinalL) {
                    volVecL[s] = envVolFinalL;
                } else {
                    volVecL[s] = resultL;
                }
            } else {
                if (resultL < envVolFinalL) {
                    volVecL[s] = envVolFinalL;
                } else {
                    volVecL[s] = resultL;
                }
            }

            resultR = volVecR[s];
            resultR = (resultR * envVolRateR) >> 16;
            if ((s32)temp_sp10C > 0) {
                if (resultR > envVolFinalR) {
                    volVecR[s] = envVolFinalR;
                } else {
                    volVecR[s] = resultR;
                }
            } else {
                if (resultR < envVolFinalR) {
                    volVecR[s] = envVolFinalR;
                } else {
                    volVecR[s] = resultR;
                }
            }

            nLoopCtl--;
            nInptr++;
            nOutptrL++;
            nOutptrR++;
        }
    } while (nLoopCtl != 0);

    dataP = (s32*)&pRSP->anAudioBuffer[nStateOffset];
    for (s = 0; s < 8; s++) {
        dataP[2 * s + 0] = volVecL[s];
        dataP[2 * s + 1] = volVecR[s];
    }

    for (i = 0; i < 40; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[nStateOffset + i];
    }

    return true;
}

static inline bool rspAInterleave1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nLeft = (s32)((nCommandLo >> 16) + pRSP->nAudioMemOffset) / 2;
    u16 nRight = (s32)((nCommandLo & 0xFFFF) + pRSP->nAudioMemOffset) / 2;
    u32 nDMEMOut = pRSP->nAudioDMEMOut[0];
    u32 iIndex;
    u32 iIndex2;

    for (iIndex = 0, iIndex2 = 0; iIndex < pRSP->nAudioCount[0]; iIndex++, iIndex2++) {
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 0] = pRSP->anAudioBuffer[nLeft + iIndex2];
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 1] = pRSP->anAudioBuffer[nRight + iIndex2];
    }

    return true;
}

static bool rspAMix1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = pRSP->nAudioCount[0];
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[(s32)(((nCommandLo >> 16) & 0xFFFF) + 0x5C0) / 2];
    dstP = &pRSP->anAudioBuffer[(s32)((nCommandLo & 0xFFFF) + 0x5C0) / 2];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static bool rspAResample1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSrcStep;
    s16* srcP;
    s16* dstP;
    s16 lastValue;
    u16 nCount;
    u16 i;
    s32 nCursorPos;
    s32 nExtra;
    u32 scratch;
    u8 flags;
    s16* pData;
    s32 nSrcAddress;
    s32 pad[7];

    srcP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]];
    dstP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]];
    nCount = pRSP->nAudioCount[0];
    nSrcStep = nCommandHi & 0xFFFF;
    flags = (nCommandHi >> 16) & 0xFF;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pData, nSrcAddress, NULL)) {
        return false;
    }

    if (flags & 1) {
        for (i = 0; i < 16; i++) {
            pData[i] = 0;
        }
    }

    if (flags & 2) {
        srcP[-8] = pData[8];
        srcP[-7] = pData[9];
        srcP[-6] = pData[10];
        srcP[-5] = pData[11];
        srcP[-4] = pData[12];
        srcP[-3] = pData[13];
        srcP[-2] = pData[14];
        srcP[-1] = pData[15];
        srcP -= pData[5] / 2;
    }

    srcP -= 4;
    srcP[0] = pData[0];
    srcP[1] = pData[1];
    srcP[2] = pData[2];
    srcP[3] = pData[3];

    nCursorPos = pData[4];
    for (i = 0; i < nCount; i++, nCursorPos += nSrcStep) {
        lastValue = srcP[nCursorPos >> 15];
        dstP[i] = lastValue + (((nCursorPos & 0x7FFF) * (srcP[(nCursorPos >> 15) + 1] - lastValue)) >> 15);
    }

    pData[4] = (nCursorPos & 0x7FFF);
    srcP += nCursorPos >> 15;

    pData[0] = srcP[0];
    pData[1] = srcP[1];
    pData[2] = srcP[2];
    pData[3] = srcP[3];

    scratch = ((srcP + 4 - &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]]) & 7) << 1;
    if (scratch != 0) {
        scratch -= 16;
    }
    pData[5] = scratch;

    pData[8] = srcP[4];
    pData[9] = srcP[5];
    pData[10] = srcP[6];
    pData[11] = srcP[7];
    pData[12] = srcP[8];
    pData[13] = srcP[9];
    pData[14] = srcP[10];
    pData[15] = srcP[11];

    return true;
}

static inline bool rspASaveBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nSize = pRSP->nAudioCount[0];
    u32* pData;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pData, nAddress, &nSize)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]], nSize * sizeof(s16));
    }

    return true;
}

static inline bool rspASegment1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->anAudioBaseSegment[(nCommandLo >> 24) & 0xF] = nCommandLo & 0xFFFFFF;
    return true;
}

static bool rspASetBuffer1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMIn = nCommandHi & 0xFFFF;
    u16 nDMEMOut = (nCommandLo >> 16) & 0xFFFF;
    u16 nCount = nCommandLo & 0xFFFF;

    if ((nCommandHi >> 16) & 8) {
        pRSP->nAudioDMauxR[1] = nCount + pRSP->nAudioMemOffset;
        pRSP->nAudioDMauxR[0] = (u16)((s32)pRSP->nAudioDMauxR[1] / 2);
        pRSP->anAudioBuffer[0x1B7] = (s16)pRSP->nAudioDMauxR[1];

        pRSP->nAudioDMOutR[1] = nDMEMIn + pRSP->nAudioMemOffset;
        pRSP->nAudioDMOutR[0] = (u16)((s32)pRSP->nAudioDMOutR[1] / 2);
        pRSP->anAudioBuffer[0x1B5] = (s16)pRSP->nAudioDMOutR[1];

        pRSP->nAudioDMauxL[1] = nDMEMOut + pRSP->nAudioMemOffset;
        pRSP->nAudioDMauxL[0] = (u16)((s32)pRSP->nAudioDMauxL[1] / 2);
        pRSP->anAudioBuffer[0x1B6] = (s16)pRSP->nAudioDMauxL[1];
    } else {
        pRSP->nAudioCount[1] = nCount;
        pRSP->nAudioCount[0] = (u16)((s32)pRSP->nAudioCount[1] / 2);
        pRSP->anAudioBuffer[0x1B2] = (s16)pRSP->nAudioCount[1];

        pRSP->nAudioDMEMIn[1] = nDMEMIn + pRSP->nAudioMemOffset;
        pRSP->nAudioDMEMIn[0] = (u16)((s32)pRSP->nAudioDMEMIn[1] / 2);
        pRSP->anAudioBuffer[0x1B0] = (s16)pRSP->nAudioDMEMIn[1];

        pRSP->nAudioDMEMOut[1] = nDMEMOut + pRSP->nAudioMemOffset;
        pRSP->nAudioDMEMOut[0] = (u16)((s32)pRSP->nAudioDMEMOut[1] / 2);
        pRSP->anAudioBuffer[0x1B1] = (s16)pRSP->nAudioDMEMOut[1];
    }

    return true;
}

static bool rspASetVolume1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nFlags = (nCommandHi >> 16) & 0xFF;
    u16 v = nCommandHi & 0xFFFF;
    u16 t = (nCommandLo >> 16) & 0xFFFF;
    u16 r = nCommandLo & 0xFFFF;

    if (nFlags & 8) {
        pRSP->anAudioBuffer[0x1BE] = v;
        pRSP->anAudioBuffer[0x1BF] = r;
    } else if (nFlags & 4) {
        if (nFlags & 2) {
            pRSP->anAudioBuffer[0x1B3] = v;
        } else {
            pRSP->anAudioBuffer[0x1B4] = v;
        }
    } else {
        if (nFlags & 2) {
            pRSP->anAudioBuffer[0x1B8] = v;
            pRSP->anAudioBuffer[0x1B9] = t;
            pRSP->anAudioBuffer[0x1BA] = r;
        } else {
            pRSP->anAudioBuffer[0x1BB] = v;
            pRSP->anAudioBuffer[0x1BC] = t;
            pRSP->anAudioBuffer[0x1BD] = r;
        }
    }

    return true;
}

static inline bool rspASetLoop1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->nAudioLoopAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    return true;
}

static inline bool rspADMEMMove1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nDMEMOut = ((nCommandHi & 0xFFFF) + pRSP->nAudioMemOffset) / 2;
    u16 nCount = nCommandLo & 0xFFFF;
    u16 nDMEMIn = (s32)((nCommandLo >> 16) + pRSP->nAudioMemOffset) / 2;

    xlHeapCopy(&pRSP->anAudioBuffer[nDMEMIn], &pRSP->anAudioBuffer[nDMEMOut], nCount);
    return true;
}

static inline bool rspALoadADPCM1(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;
    u32 nCount = nCommandHi & 0xFFFFFF;
    s32 nAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, nAddress, NULL)) {
        if (xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioADPCMOffset / 2], pData, nCount)) {
            rspLoadADPCMCoefTable1(pRSP);
        }
    }

    return true;
}

static bool rspParseABI(Rsp* pRSP, RspTask* pTask) {
    u8* pFUCode;
    u32 nCheckSum;
    s32 pad[3];

    if (!(pRSP->eTypeAudioUCode == RUT_ABI1 || pRSP->eTypeAudioUCode == RUT_ABI2 ||
          pRSP->eTypeAudioUCode == RUT_UNKNOWN)) {
        if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pFUCode, pTask->nOffsetCode, NULL)) {
            return false;
        }

        nCheckSum = 0;
        nCheckSum += pFUCode[0];
        nCheckSum += pFUCode[1];
        nCheckSum += pFUCode[2];
        nCheckSum += pFUCode[3];
        nCheckSum += pFUCode[4];
        nCheckSum += pFUCode[5];
        nCheckSum += pFUCode[6];
        nCheckSum += pFUCode[7];

        switch (nCheckSum) {
            case 0x171:
                pRSP->eTypeAudioUCode = RUT_ABI1;
                pRSP->nAudioMemOffset = 0x5C0;
                pRSP->nAudioADPCMOffset = 0x4C0;
                pRSP->nAudioParBase = 0x360;
                pRSP->nAudioScratchOffset = 0xF90;
                rspInitAudioDMEM1(pRSP);
                break;
            case 0x1F4:
                pRSP->eTypeAudioUCode = RUT_ABI2;
                pRSP->nAudioMemOffset = 0x3B0;
                pRSP->nAudioADPCMOffset = 0x330;
                pRSP->nAudioParBase = 0;
                pRSP->nAudioScratchOffset = 0xFB0;
                rspInitAudioDMEM2(pRSP);
                break;
            case 0x151:
                pRSP->eTypeAudioUCode = RUT_ABI3;
                pRSP->nAudioMemOffset = 0x450;
                pRSP->nAudioADPCMOffset = 0x3D0;
                pRSP->nAudioParBase = 0x330;
                pRSP->nAudioScratchOffset = 0xFA0;
                rspInitAudioDMEM3(pRSP);
                break;
            case 0x131:
                pRSP->eTypeAudioUCode = RUT_ABI4;
                pRSP->nAudioMemOffset = 0x450;
                pRSP->nAudioADPCMOffset = 0x3C0;
                pRSP->nAudioParBase = 0x320;
                pRSP->nAudioScratchOffset = 0xF90;
                rspInitAudioDMEM4(pRSP);
                break;
            default:
                pRSP->eTypeAudioUCode = RUT_UNKNOWN;
                break;
        }
    }

    switch (pRSP->eTypeAudioUCode) {
        case RUT_ABI1:
            rspParseABI1(pRSP, pTask);
            break;
        case RUT_ABI2:
            rspParseABI2(pRSP, pTask);
            break;
        case RUT_ABI3:
            rspParseABI3(pRSP, pTask);
            break;
        case RUT_ABI4:
            rspParseABI4(pRSP, pTask);
            break;
        default:
            break;
    }

    return true;
}

static bool rspParseABI1(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    static bool nFirstTime = true;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime) {
        nFirstTime = false;
    }

    while (pABI32 < pABILast32) {
        nCommandHi = pABI32[0];
        nCommandLo = pABI32[1];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 4:
                rspALoadBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 6:
                rspASaveBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 7:
                rspASegment1(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove1(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM1(pRSP, nCommandLo, nCommandHi);
                break;
            case 12:
                rspAMix1(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop1(pRSP, nCommandLo, nCommandHi);
                break;
            case 3:
                rspAEnvMixer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample1(pRSP, nCommandLo, nCommandHi);
                break;
            case 9:
                rspASetVolume1(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    return true;
}

static bool rspInitAudioDMEM2(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;

    pRSP->anAudioBuffer[0x020] = 0xF000;
    pRSP->anAudioBuffer[0x021] = 0x0F00;
    pRSP->anAudioBuffer[0x022] = 0x00F0;
    pRSP->anAudioBuffer[0x023] = 0x000F;
    pRSP->anAudioBuffer[0x024] = 0x0001;
    pRSP->anAudioBuffer[0x025] = 0x0010;
    pRSP->anAudioBuffer[0x026] = 0x0100;
    pRSP->anAudioBuffer[0x027] = 0x1000;
    pRSP->anAudioBuffer[0x028] = 0xC000;
    pRSP->anAudioBuffer[0x029] = 0x3000;
    pRSP->anAudioBuffer[0x02A] = 0x0C00;
    pRSP->anAudioBuffer[0x02B] = 0x0300;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0004;
    pRSP->anAudioBuffer[0x02E] = 0x0010;
    pRSP->anAudioBuffer[0x02F] = 0x0040;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;
    pRSP->anAudioBuffer[0x060] = 0x0000;
    pRSP->anAudioBuffer[0x061] = 0x0000;
    pRSP->anAudioBuffer[0x062] = 0x0000;
    pRSP->anAudioBuffer[0x063] = 0x0001;
    pRSP->anAudioBuffer[0x064] = 0x0000;
    pRSP->anAudioBuffer[0x065] = 0x0000;
    pRSP->anAudioBuffer[0x066] = 0x0000;
    pRSP->anAudioBuffer[0x067] = 0x0001;
    pRSP->anAudioBuffer[0x068] = 0x2000;
    pRSP->anAudioBuffer[0x069] = 0x4000;
    pRSP->anAudioBuffer[0x06A] = 0x6000;
    pRSP->anAudioBuffer[0x06B] = 0x8000;
    pRSP->anAudioBuffer[0x06C] = 0xA000;
    pRSP->anAudioBuffer[0x06D] = 0xC000;
    pRSP->anAudioBuffer[0x06E] = 0xE000;
    pRSP->anAudioBuffer[0x06F] = 0xFFFF;
    pRSP->anAudioBuffer[0x070] = 0x0C39;
    pRSP->anAudioBuffer[0x071] = 0x66AD;
    pRSP->anAudioBuffer[0x072] = 0x0D46;
    pRSP->anAudioBuffer[0x073] = 0xFFDF;
    pRSP->anAudioBuffer[0x074] = 0x0B39;
    pRSP->anAudioBuffer[0x075] = 0x6696;
    pRSP->anAudioBuffer[0x076] = 0x0E5F;
    pRSP->anAudioBuffer[0x077] = 0xFFD8;
    pRSP->anAudioBuffer[0x078] = 0x0A44;
    pRSP->anAudioBuffer[0x079] = 0x6669;
    pRSP->anAudioBuffer[0x07A] = 0x0F83;
    pRSP->anAudioBuffer[0x07B] = 0xFFD0;
    pRSP->anAudioBuffer[0x07C] = 0x095A;
    pRSP->anAudioBuffer[0x07D] = 0x6626;
    pRSP->anAudioBuffer[0x07E] = 0x10B4;
    pRSP->anAudioBuffer[0x07F] = 0xFFC8;
    pRSP->anAudioBuffer[0x080] = 0x087D;
    pRSP->anAudioBuffer[0x081] = 0x65CD;
    pRSP->anAudioBuffer[0x082] = 0x11F0;
    pRSP->anAudioBuffer[0x083] = 0xFFBF;
    pRSP->anAudioBuffer[0x084] = 0x07AB;
    pRSP->anAudioBuffer[0x085] = 0x655E;
    pRSP->anAudioBuffer[0x086] = 0x1338;
    pRSP->anAudioBuffer[0x087] = 0xFFB6;
    pRSP->anAudioBuffer[0x088] = 0x06E4;
    pRSP->anAudioBuffer[0x089] = 0x64D9;
    pRSP->anAudioBuffer[0x08A] = 0x148C;
    pRSP->anAudioBuffer[0x08B] = 0xFFAC;
    pRSP->anAudioBuffer[0x08C] = 0x0628;
    pRSP->anAudioBuffer[0x08D] = 0x643F;
    pRSP->anAudioBuffer[0x08E] = 0x15EB;
    pRSP->anAudioBuffer[0x08F] = 0xFFA1;
    pRSP->anAudioBuffer[0x090] = 0x0577;
    pRSP->anAudioBuffer[0x091] = 0x638F;
    pRSP->anAudioBuffer[0x092] = 0x1756;
    pRSP->anAudioBuffer[0x093] = 0xFF96;
    pRSP->anAudioBuffer[0x094] = 0x04D1;
    pRSP->anAudioBuffer[0x095] = 0x62CB;
    pRSP->anAudioBuffer[0x096] = 0x18CB;
    pRSP->anAudioBuffer[0x097] = 0xFF8A;
    pRSP->anAudioBuffer[0x098] = 0x0435;
    pRSP->anAudioBuffer[0x099] = 0x61F3;
    pRSP->anAudioBuffer[0x09A] = 0x1A4C;
    pRSP->anAudioBuffer[0x09B] = 0xFF7E;
    pRSP->anAudioBuffer[0x09C] = 0x03A4;
    pRSP->anAudioBuffer[0x09D] = 0x6106;
    pRSP->anAudioBuffer[0x09E] = 0x1BD7;
    pRSP->anAudioBuffer[0x09F] = 0xFF71;
    pRSP->anAudioBuffer[0x0A0] = 0x031C;
    pRSP->anAudioBuffer[0x0A1] = 0x6007;
    pRSP->anAudioBuffer[0x0A2] = 0x1D6C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF64;
    pRSP->anAudioBuffer[0x0A4] = 0x029F;
    pRSP->anAudioBuffer[0x0A5] = 0x5EF5;
    pRSP->anAudioBuffer[0x0A6] = 0x1F0B;
    pRSP->anAudioBuffer[0x0A7] = 0xFF56;
    pRSP->anAudioBuffer[0x0A8] = 0x022A;
    pRSP->anAudioBuffer[0x0A9] = 0x5DD0;
    pRSP->anAudioBuffer[0x0AA] = 0x20B3;
    pRSP->anAudioBuffer[0x0AB] = 0xFF48;
    pRSP->anAudioBuffer[0x0AC] = 0x01BE;
    pRSP->anAudioBuffer[0x0AD] = 0x5C9A;
    pRSP->anAudioBuffer[0x0AE] = 0x2264;
    pRSP->anAudioBuffer[0x0AF] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B0] = 0x015B;
    pRSP->anAudioBuffer[0x0B1] = 0x5B53;
    pRSP->anAudioBuffer[0x0B2] = 0x241E;
    pRSP->anAudioBuffer[0x0B3] = 0xFF2C;
    pRSP->anAudioBuffer[0x0B4] = 0x0101;
    pRSP->anAudioBuffer[0x0B5] = 0x59FC;
    pRSP->anAudioBuffer[0x0B6] = 0x25E0;
    pRSP->anAudioBuffer[0x0B7] = 0xFF1E;
    pRSP->anAudioBuffer[0x0B8] = 0x00AE;
    pRSP->anAudioBuffer[0x0B9] = 0x5896;
    pRSP->anAudioBuffer[0x0BA] = 0x27A9;
    pRSP->anAudioBuffer[0x0BB] = 0xFF10;
    pRSP->anAudioBuffer[0x0BC] = 0x0063;
    pRSP->anAudioBuffer[0x0BD] = 0x5720;
    pRSP->anAudioBuffer[0x0BE] = 0x297A;
    pRSP->anAudioBuffer[0x0BF] = 0xFF02;
    pRSP->anAudioBuffer[0x0C0] = 0x001F;
    pRSP->anAudioBuffer[0x0C1] = 0x559D;
    pRSP->anAudioBuffer[0x0C2] = 0x2B50;
    pRSP->anAudioBuffer[0x0C3] = 0xFEF4;
    pRSP->anAudioBuffer[0x0C4] = 0xFFE2;
    pRSP->anAudioBuffer[0x0C5] = 0x540D;
    pRSP->anAudioBuffer[0x0C6] = 0x2D2C;
    pRSP->anAudioBuffer[0x0C7] = 0xFEE8;
    pRSP->anAudioBuffer[0x0C8] = 0xFFAC;
    pRSP->anAudioBuffer[0x0C9] = 0x5270;
    pRSP->anAudioBuffer[0x0CA] = 0x2F0D;
    pRSP->anAudioBuffer[0x0CB] = 0xFEDB;
    pRSP->anAudioBuffer[0x0CC] = 0xFF7C;
    pRSP->anAudioBuffer[0x0CD] = 0x50C7;
    pRSP->anAudioBuffer[0x0CE] = 0x30F3;
    pRSP->anAudioBuffer[0x0CF] = 0xFED0;
    pRSP->anAudioBuffer[0x0D0] = 0xFF53;
    pRSP->anAudioBuffer[0x0D1] = 0x4F14;
    pRSP->anAudioBuffer[0x0D2] = 0x32DC;
    pRSP->anAudioBuffer[0x0D3] = 0xFEC6;
    pRSP->anAudioBuffer[0x0D4] = 0xFF2E;
    pRSP->anAudioBuffer[0x0D5] = 0x4D57;
    pRSP->anAudioBuffer[0x0D6] = 0x34C8;
    pRSP->anAudioBuffer[0x0D7] = 0xFEBD;
    pRSP->anAudioBuffer[0x0D8] = 0xFF0F;
    pRSP->anAudioBuffer[0x0D9] = 0x4B91;
    pRSP->anAudioBuffer[0x0DA] = 0x36B6;
    pRSP->anAudioBuffer[0x0DB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0DC] = 0xFEF5;
    pRSP->anAudioBuffer[0x0DD] = 0x49C2;
    pRSP->anAudioBuffer[0x0DE] = 0x38A5;
    pRSP->anAudioBuffer[0x0DF] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E0] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E1] = 0x47ED;
    pRSP->anAudioBuffer[0x0E2] = 0x3A95;
    pRSP->anAudioBuffer[0x0E3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0E4] = 0xFECE;
    pRSP->anAudioBuffer[0x0E5] = 0x4611;
    pRSP->anAudioBuffer[0x0E6] = 0x3C85;
    pRSP->anAudioBuffer[0x0E7] = 0xFEAB;
    pRSP->anAudioBuffer[0x0E8] = 0xFEC0;
    pRSP->anAudioBuffer[0x0E9] = 0x4430;
    pRSP->anAudioBuffer[0x0EA] = 0x3E74;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFEB6;
    pRSP->anAudioBuffer[0x0ED] = 0x424A;
    pRSP->anAudioBuffer[0x0EE] = 0x4060;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F0] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F1] = 0x4060;
    pRSP->anAudioBuffer[0x0F2] = 0x424A;
    pRSP->anAudioBuffer[0x0F3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F4] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F5] = 0x3E74;
    pRSP->anAudioBuffer[0x0F6] = 0x4430;
    pRSP->anAudioBuffer[0x0F7] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F9] = 0x3C85;
    pRSP->anAudioBuffer[0x0FA] = 0x4611;
    pRSP->anAudioBuffer[0x0FB] = 0xFECE;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3A95;
    pRSP->anAudioBuffer[0x0FE] = 0x47ED;
    pRSP->anAudioBuffer[0x0FF] = 0xFEDF;
    pRSP->anAudioBuffer[0x100] = 0xFEB0;
    pRSP->anAudioBuffer[0x101] = 0x38A5;
    pRSP->anAudioBuffer[0x102] = 0x49C2;
    pRSP->anAudioBuffer[0x103] = 0xFEF5;
    pRSP->anAudioBuffer[0x104] = 0xFEB6;
    pRSP->anAudioBuffer[0x105] = 0x36B6;
    pRSP->anAudioBuffer[0x106] = 0x4B91;
    pRSP->anAudioBuffer[0x107] = 0xFF0F;
    pRSP->anAudioBuffer[0x108] = 0xFEBD;
    pRSP->anAudioBuffer[0x109] = 0x34C8;
    pRSP->anAudioBuffer[0x10A] = 0x4D57;
    pRSP->anAudioBuffer[0x10B] = 0xFF2E;
    pRSP->anAudioBuffer[0x10C] = 0xFEC6;
    pRSP->anAudioBuffer[0x10D] = 0x32DC;
    pRSP->anAudioBuffer[0x10E] = 0x4F14;
    pRSP->anAudioBuffer[0x10F] = 0xFF53;
    pRSP->anAudioBuffer[0x110] = 0xFED0;
    pRSP->anAudioBuffer[0x111] = 0x30F3;
    pRSP->anAudioBuffer[0x112] = 0x50C7;
    pRSP->anAudioBuffer[0x113] = 0xFF7C;
    pRSP->anAudioBuffer[0x114] = 0xFEDB;
    pRSP->anAudioBuffer[0x115] = 0x2F0D;
    pRSP->anAudioBuffer[0x116] = 0x5270;
    pRSP->anAudioBuffer[0x117] = 0xFFAC;
    pRSP->anAudioBuffer[0x118] = 0xFEE8;
    pRSP->anAudioBuffer[0x119] = 0x2D2C;
    pRSP->anAudioBuffer[0x11A] = 0x540D;
    pRSP->anAudioBuffer[0x11B] = 0xFFE2;
    pRSP->anAudioBuffer[0x11C] = 0xFEF4;
    pRSP->anAudioBuffer[0x11D] = 0x2B50;
    pRSP->anAudioBuffer[0x11E] = 0x559D;
    pRSP->anAudioBuffer[0x11F] = 0x001F;
    pRSP->anAudioBuffer[0x120] = 0xFF02;
    pRSP->anAudioBuffer[0x121] = 0x297A;
    pRSP->anAudioBuffer[0x122] = 0x5720;
    pRSP->anAudioBuffer[0x123] = 0x0063;
    pRSP->anAudioBuffer[0x124] = 0xFF10;
    pRSP->anAudioBuffer[0x125] = 0x27A9;
    pRSP->anAudioBuffer[0x126] = 0x5896;
    pRSP->anAudioBuffer[0x127] = 0x00AE;
    pRSP->anAudioBuffer[0x128] = 0xFF1E;
    pRSP->anAudioBuffer[0x129] = 0x25E0;
    pRSP->anAudioBuffer[0x12A] = 0x59FC;
    pRSP->anAudioBuffer[0x12B] = 0x0101;
    pRSP->anAudioBuffer[0x12C] = 0xFF2C;
    pRSP->anAudioBuffer[0x12D] = 0x241E;
    pRSP->anAudioBuffer[0x12E] = 0x5B53;
    pRSP->anAudioBuffer[0x12F] = 0x015B;
    pRSP->anAudioBuffer[0x130] = 0xFF3A;
    pRSP->anAudioBuffer[0x131] = 0x2264;
    pRSP->anAudioBuffer[0x132] = 0x5C9A;
    pRSP->anAudioBuffer[0x133] = 0x01BE;
    pRSP->anAudioBuffer[0x134] = 0xFF48;
    pRSP->anAudioBuffer[0x135] = 0x20B3;
    pRSP->anAudioBuffer[0x136] = 0x5DD0;
    pRSP->anAudioBuffer[0x137] = 0x022A;
    pRSP->anAudioBuffer[0x138] = 0xFF56;
    pRSP->anAudioBuffer[0x139] = 0x1F0B;
    pRSP->anAudioBuffer[0x13A] = 0x5EF5;
    pRSP->anAudioBuffer[0x13B] = 0x029F;
    pRSP->anAudioBuffer[0x13C] = 0xFF64;
    pRSP->anAudioBuffer[0x13D] = 0x1D6C;
    pRSP->anAudioBuffer[0x13E] = 0x6007;
    pRSP->anAudioBuffer[0x13F] = 0x031C;
    pRSP->anAudioBuffer[0x140] = 0xFF71;
    pRSP->anAudioBuffer[0x141] = 0x1BD7;
    pRSP->anAudioBuffer[0x142] = 0x6106;
    pRSP->anAudioBuffer[0x143] = 0x03A4;
    pRSP->anAudioBuffer[0x144] = 0xFF7E;
    pRSP->anAudioBuffer[0x145] = 0x1A4C;
    pRSP->anAudioBuffer[0x146] = 0x61F3;
    pRSP->anAudioBuffer[0x147] = 0x0435;
    pRSP->anAudioBuffer[0x148] = 0xFF8A;
    pRSP->anAudioBuffer[0x149] = 0x18CB;
    pRSP->anAudioBuffer[0x14A] = 0x62CB;
    pRSP->anAudioBuffer[0x14B] = 0x04D1;
    pRSP->anAudioBuffer[0x14C] = 0xFF96;
    pRSP->anAudioBuffer[0x14D] = 0x1756;
    pRSP->anAudioBuffer[0x14E] = 0x638F;
    pRSP->anAudioBuffer[0x14F] = 0x0577;
    pRSP->anAudioBuffer[0x150] = 0xFFA1;
    pRSP->anAudioBuffer[0x151] = 0x15EB;
    pRSP->anAudioBuffer[0x152] = 0x643F;
    pRSP->anAudioBuffer[0x153] = 0x0628;
    pRSP->anAudioBuffer[0x154] = 0xFFAC;
    pRSP->anAudioBuffer[0x155] = 0x148C;
    pRSP->anAudioBuffer[0x156] = 0x64D9;
    pRSP->anAudioBuffer[0x157] = 0x06E4;
    pRSP->anAudioBuffer[0x158] = 0xFFB6;
    pRSP->anAudioBuffer[0x159] = 0x1338;
    pRSP->anAudioBuffer[0x15A] = 0x655E;
    pRSP->anAudioBuffer[0x15B] = 0x07AB;
    pRSP->anAudioBuffer[0x15C] = 0xFFBF;
    pRSP->anAudioBuffer[0x15D] = 0x11F0;
    pRSP->anAudioBuffer[0x15E] = 0x65CD;
    pRSP->anAudioBuffer[0x15F] = 0x087D;
    pRSP->anAudioBuffer[0x160] = 0xFFC8;
    pRSP->anAudioBuffer[0x161] = 0x10B4;
    pRSP->anAudioBuffer[0x162] = 0x6626;
    pRSP->anAudioBuffer[0x163] = 0x095A;
    pRSP->anAudioBuffer[0x164] = 0xFFD0;
    pRSP->anAudioBuffer[0x165] = 0x0F83;
    pRSP->anAudioBuffer[0x166] = 0x6669;
    pRSP->anAudioBuffer[0x167] = 0x0A44;
    pRSP->anAudioBuffer[0x168] = 0xFFD8;
    pRSP->anAudioBuffer[0x169] = 0x0E5F;
    pRSP->anAudioBuffer[0x16A] = 0x6696;
    pRSP->anAudioBuffer[0x16B] = 0x0B39;
    pRSP->anAudioBuffer[0x16C] = 0xFFDF;
    pRSP->anAudioBuffer[0x16D] = 0x0D46;
    pRSP->anAudioBuffer[0x16E] = 0x66AD;
    pRSP->anAudioBuffer[0x16F] = 0x0C39;

    return true;
}

static bool rspAADPCMDec2Fast(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u8 nFlags;
    u8 ucControl;
    s8* pHeader;
    s16* pStateAddress;
    s32 pad1[3];
    s16 anIData0;
    s32 nDMEMOut;
    s32 nCount;
    s32 nSrcAddress;
    s32 nOptPred;
    s32 nLogScale;
    s32 nVScale;
    int i;
    u32 dwDecodeSelect;
    u32 n;
    s32 nA;
    s32 nB;
    s16 nSamp1;
    s16 nSamp2;
    s16* pTempStateAddr;
    s16 nibble[4];
    s32 nOutput;
    s32 pad2[3];

    nFlags = (nCommandHi >> 16) & 0xFF;
    pHeader = (s8*)pRSP->anAudioBuffer + pRSP->nAudioDMEMIn[1];
    nDMEMOut = pRSP->nAudioDMEMOut[0];
    nCount = pRSP->nAudioCount[0];
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pStateAddress, nSrcAddress, NULL)) {
        return false;
    }

    if (!(nFlags & 1)) {
        pTempStateAddr = pStateAddress;
        if (nFlags & 2) {
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pTempStateAddr, pRSP->nAudioLoopAddress, NULL)) {
                return false;
            }
        }

        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = pTempStateAddr[i];
        }
    } else {
        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[nDMEMOut + i] = 0;
        }
    }

    nDMEMOut += 16;
    if (nCount == 0) {
        for (i = 0; i < 16; i++) {
            pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
        }
        return true;
    }

    while (nCount > 0) {
        ucControl = *pHeader;
        pHeader++;
        dwDecodeSelect = (ucControl & 0xF) << 5;
        if (dwDecodeSelect == 0x00) {
            nOptPred = 0;
        } else if (dwDecodeSelect == 0x20) {
            nOptPred = 1;
        } else if (dwDecodeSelect == 0x40) {
            nOptPred = 2;
        } else if (dwDecodeSelect == 0x60) {
            nOptPred = 3;
        } else {
            nOptPred = 4;
            dwDecodeSelect = (dwDecodeSelect / 2) + ((s32)pRSP->nAudioADPCMOffset / 2);
            for (i = 0; i < 8; i++) {
                pRSP->anADPCMCoef[4][0][i] = pRSP->anAudioBuffer[dwDecodeSelect + i];
                pRSP->anADPCMCoef[4][1][i] = pRSP->anAudioBuffer[dwDecodeSelect + 8 + i];
            }
        }

        nA = pRSP->anADPCMCoef[nOptPred][0][0];
        nB = pRSP->anADPCMCoef[nOptPred][1][0];
        nSamp2 = pRSP->anAudioBuffer[nDMEMOut - 2];
        nSamp1 = pRSP->anAudioBuffer[nDMEMOut - 1];

        for (n = 0; n < 16; n += 4) {
            nibble[0] = ((*pHeader >> 6) & 3) << 14;
            nibble[1] = ((*pHeader >> 4) & 3) << 14;
            nibble[2] = ((*pHeader >> 2) & 3) << 14;
            nibble[3] = ((*pHeader >> 0) & 3) << 14;
            pHeader++;

            for (i = 0; i < 4; i++) {
                nLogScale = 14 - (ucControl >> 4);
                nVScale = nLogScale == 0 ? 0x8000 : (0x8000 >> (nLogScale - 1)) & 0xFFFF;
                if (nLogScale > 0) {
                    anIData0 = (nibble[i] * nVScale) >> 16;
                } else {
                    anIData0 = nibble[i];
                }

                nOutput = (nSamp1 * nB + (nSamp2 * nA + (anIData0 << 11))) >> 16;
                nOutput <<= 5;
                if (nOutput > 0x7FFF) {
                    nOutput = 0x7FFF;
                } else if (nOutput < -0x8000) {
                    nOutput = -0x8000;
                }

                nSamp2 = nSamp1;
                nSamp1 = nOutput;
                pRSP->anAudioBuffer[nDMEMOut + n + i] = nOutput;
            }
        }

        nDMEMOut += 16;
        nCount -= 16;
    }

    for (i = 0; i < 16; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[nDMEMOut - 16 + i];
    }

    return true;
}

static inline bool rspAClearBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    memset(&pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], 0, nCommandLo & 0xFFFF);
    return true;
}

static bool rspANoise2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 pad[4];
    u32 nDest;
    u32 nSource;
    u32 nCount;
    u32 i;
    u32 j;
    s16 vIn[16];
    s16 vOut[16];
    s64 accumulator[8];

    nDest = (nCommandLo & 0xFFFF) >> 1;
    nSource = (nCommandLo >> 16) >> 1;
    nCount = (nCommandHi & 0xFFFF) >> 1;
    for (i = 0; i < 8; i++) {
        vIn[i + 0] = pRSP->anAudioBuffer[i + nSource + 0];
        vIn[i + 8] = pRSP->anAudioBuffer[i + nSource + 8];
        vOut[i + 0] = pRSP->anAudioBuffer[i + nDest + 0];
        vOut[i + 8] = pRSP->anAudioBuffer[i + nDest + 8];
    }

    for (i = 0; i < nCount; i += 16) {
        rspVMUDN(pRSP, &vIn[8], &vIn[0], &vOut[0], 0, accumulator);
        rspVMADN(pRSP, &vIn[8], &vIn[0], &vOut[8], 0, accumulator);
        for (j = 0; j < 8; j++) {
            // fake?
            s32 index0 = j + i + 0;
            s32 index8 = j + i + 8;

            pRSP->anAudioBuffer[nDest + index8] = vOut[j + 0];
            pRSP->anAudioBuffer[nDest + index0] = vOut[j + 8];
            vIn[j + 0] = pRSP->anAudioBuffer[nSource + 16 + index0];
            vIn[j + 8] = pRSP->anAudioBuffer[nSource + 16 + index8];
        }
    }

    return true;
}

static bool rspANMix2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 nCount;
    u32 i;
    s16* inP;
    s16* outP;
    s32 out;

    nCount = ((nCommandHi >> 16) & 0xFF) << 3;
    inP = &pRSP->anAudioBuffer[((nCommandLo >> 16) & 0xFFFF) >> 1];
    outP = &pRSP->anAudioBuffer[(nCommandLo & 0xFFFF) >> 1];

    for (i = 0; i < nCount; i++) {
        out = outP[i];
        out += inP[i];
        if (out > 0x7FFF) {
            out = 0x7FFF;
        } else if (out < -0x8000) {
            out = -0x8000;
        }
        outP[i] = out;
    }

    return true;
}

static bool rspAResample2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSrcStep;
    s16* srcP;
    s16* dstP;
    s16 lastValue;
    u16 nCount;
    u16 i;
    s32 nCursorPos;
    u32 scratch;
    u8 flags;
    s16* pData;
    s32 nSrcAddress;
    s32 pad[6];

    srcP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMIn[0]];
    dstP = &pRSP->anAudioBuffer[pRSP->nAudioDMEMOut[0]];
    nCount = pRSP->nAudioCount[0];
    nSrcStep = nCommandHi & 0xFFFF;
    flags = (nCommandHi >> 16) & 0xFF;
    nSrcAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pData, nSrcAddress, NULL)) {
        return false;
    }

    if (flags & 1) {
        for (i = 0; i < 5; i++) {
            pData[i] = 0;
        }
    }

    if (flags & 2) {
        srcP[-2] = pData[0];
        srcP[-1] = pData[2];
        srcP -= 2;
    } else if (flags & 4) {
        srcP[-8] = pData[0];
        srcP[-7] = pData[0];
        srcP[-6] = pData[1];
        srcP[-5] = pData[1];
        srcP[-4] = pData[2];
        srcP[-3] = pData[2];
        srcP[-2] = pData[3];
        srcP[-1] = pData[3];
        srcP -= 8;
    } else {
        srcP[-4] = pData[0];
        srcP[-3] = pData[1];
        srcP[-2] = pData[2];
        srcP[-1] = pData[3];
        srcP -= 4;
    }

    nCursorPos = pData[4];
    for (i = 0; i < nCount; i++, nCursorPos += nSrcStep) {
        lastValue = srcP[nCursorPos >> 15];
        dstP[i] = lastValue + (((nCursorPos & 0x7FFF) * (srcP[(nCursorPos >> 15) + 1] - lastValue)) >> 15);
    }

    pData[4] = nCursorPos & 0x7FFF;
    srcP += nCursorPos >> 15;

    pData[0] = srcP[0];
    pData[1] = srcP[1];
    pData[2] = srcP[2];
    pData[3] = srcP[3];

    return true;
}

static inline bool rspASResample2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 outp = pRSP->nAudioDMEMOut[0];
    s32 outCount = pRSP->nAudioCount[0];
    s32 pitchSpeed = (nCommandHi & 0xFFFF) * 4;
    int i;
    s32 mainCounter = (pRSP->nAudioDMEMIn[1] << 16) | (nCommandLo & 0xFFFF);

    for (i = 0; i < outCount; i++, mainCounter += pitchSpeed) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[(mainCounter >> 17) & 0x7FFF];
    }

    return true;
}

static bool rspAFirFilter2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 pad;
    s32 filterState;
    s32 filterTable;
    int i;
    s32 pointer;
    void* pData;
    s16* pStateAddress;
    // s16 flag;
    s16 vANS[8];
    s16 vOLD[8];
    s16 vTP1[8];
    s16 vT0[8];
    s32 accumulator[8];
    s32 temp32[8];
    s32 stateAddr;
    s16 anMatrix[8];
    s16 anInputVec[15];
    static s32 counter;

    filterState = (s32)pRSP->nAudioScratchOffset >> 1;
    filterTable = filterState + 16;

    for (i = 0; i < 16; i++) {
        pRSP->anAudioBuffer[filterState + i] = 0;
    }

    stateAddr = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, stateAddr, NULL)) {
        return false;
    }
    pStateAddress = pData;

    if (((nCommandHi >> 16) & 0xFF) == 0) {
        for (i = 0; i < 16; i++) {
            pRSP->anAudioBuffer[filterState + i] = pStateAddress[i];
        }
    } else if (((nCommandHi >> 16) & 0xFF) - 1 != 0) {
        counter = (nCommandHi & 0xFFFF) >> 1;
        for (i = 0; i < 8; i++) {
            pRSP->anAudioBuffer[filterTable + i + 8] = pStateAddress[i];
        }
        return true;
    }

    for (i = 0; i < 8; i++) {
        vT0[i] = pRSP->anAudioBuffer[filterTable + i + 8];
        vTP1[i] = pRSP->anAudioBuffer[filterState + i + 8];
        vANS[i] = 0;
        accumulator[i] = 0;
    }

    for (i = 0; i < 8; i++) {
        accumulator[i] = vT0[i] << 14;
        temp32[i] = accumulator[i] >> 15;
        if (temp32[i] > 0x7FFF) {
            temp32[i] = 0x7FFF;
        } else if (temp32[i] < -0x8000) {
            temp32[i] = -0x8000;
        }
        vANS[i] = temp32[i];
    }

    for (i = 0; i < 8; i++) {
        accumulator[i] += vTP1[i] << 14;
        accumulator[i] >>= 15;
        if (accumulator[i] > 0x7FFF) {
            accumulator[i] = 0x7FFF;
        } else if (accumulator[i] < -0x8000) {
            accumulator[i] = -0x8000;
        }
        vANS[i] = accumulator[i];
    }

    stateAddr = 0;
    pointer = (nCommandHi & 0xFFFF) >> 1;

    for (i = 0; i < 8; i++) {
        pRSP->anAudioBuffer[filterTable + i + 8] = vANS[i];
        pRSP->anAudioBuffer[filterState + i + 8] = vANS[i];
        vANS[i] = 0;
        accumulator[i] = 0;
    }

    for (i = 0; i < 8; i++) {
        anMatrix[i] = pRSP->anAudioBuffer[filterTable + i + 8];
        vOLD[i] = pRSP->anAudioBuffer[filterState + i];
    }

    do {
        for (i = 0; i < 8; i++) {
            anInputVec[i + 7] = pRSP->anAudioBuffer[stateAddr + pointer + i];
            accumulator[i] = 0;
        }

        anInputVec[0] = vOLD[1];
        anInputVec[1] = vOLD[2];
        anInputVec[2] = vOLD[3];
        anInputVec[3] = vOLD[4];
        anInputVec[4] = vOLD[5];
        anInputVec[5] = vOLD[6];
        anInputVec[6] = vOLD[7];

        rspDotProduct8x15MatrixBy15x1Vector(pRSP, anMatrix, anInputVec, vANS);
        for (i = 0; i < 8; i++) {
            pRSP->anAudioBuffer[stateAddr + pointer + i] = vANS[i];
            vOLD[i] = anInputVec[i + 7];
        }
        stateAddr += 8;
        counter -= 8;
    } while (counter > 0);

    for (i = 0; i < 8; i++) {
        pRSP->anAudioBuffer[filterState + i] = anInputVec[i + 7];
    }

    for (i = 0; i < 16; i++) {
        pStateAddress[i] = pRSP->anAudioBuffer[filterState + i];
    }

    return true;
}

static inline bool rspASetBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMIn = nCommandHi & 0xFFFF;
    u16 nDMEMOut = nCommandLo >> 16;
    u16 nCount = nCommandLo & 0xFFFF;

    pRSP->nAudioDMEMIn[1] = nDMEMIn;
    pRSP->nAudioDMEMIn[0] = (nCommandHi & 0xFFFF) >> 1;
    pRSP->nAudioDMEMOut[1] = nDMEMOut;
    pRSP->nAudioDMEMOut[0] = nDMEMOut >> 1;
    pRSP->nAudioCount[1] = nCount;
    pRSP->nAudioCount[0] = nCount >> 1;

    return true;
}

static inline bool rspAWMEMCopy2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 16) >> 1],
               &pRSP->anAudioBuffer[(s16)(nCommandHi & 0xFFFF) >> 1], (s16)((nCommandHi >> 16) & 0xFF) << 7);
    return true;
}

static inline bool rspADMEMMove2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 nSize = nCommandLo & 0xFFFF;

    xlHeapCopy(&pRSP->anAudioBuffer[(s32)(nCommandLo >> 16) / 2], &pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) / 2],
               nSize);
    return true;
}

static inline bool rspALoadADPCM2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        if (xlHeapCopy(&pRSP->anAudioBuffer[pRSP->nAudioADPCMOffset >> 1], pData, nCommandHi & 0xFFFF)) {
            rspLoadADPCMCoefTable2(pRSP);
        }
    }

    return true;
}

static bool rspAMix2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = (s32)((nCommandHi >> 12) & 0xFF0) >> 1;
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[(s32)((nCommandLo >> 16) & 0xFFFF) >> 1];
    dstP = &pRSP->anAudioBuffer[(s32)(nCommandLo & 0xFFFF) >> 1];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static bool rspAInterleave2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 outp;
    s32 inpr;
    s32 inpl;
    s32 count;
    s32 i;

    outp = (s32)(nCommandHi & 0xFFFF) >> 1;
    inpr = (s32)(nCommandLo & 0xFFFF) >> 1;
    inpl = (s32)(nCommandLo >> 16) >> 1;
    count = (nCommandHi >> 12) & 0xFF0;

    outp += 8;
    for (i = 0; i < count; i += 8) {
        pRSP->anAudioBuffer[outp - 8] = pRSP->anAudioBuffer[inpl + 0];
        pRSP->anAudioBuffer[outp - 7] = pRSP->anAudioBuffer[inpr + 0];
        pRSP->anAudioBuffer[outp - 6] = pRSP->anAudioBuffer[inpl + 1];
        pRSP->anAudioBuffer[outp - 5] = pRSP->anAudioBuffer[inpr + 1];
        pRSP->anAudioBuffer[outp - 4] = pRSP->anAudioBuffer[inpl + 2];
        pRSP->anAudioBuffer[outp - 3] = pRSP->anAudioBuffer[inpr + 2];
        pRSP->anAudioBuffer[outp - 2] = pRSP->anAudioBuffer[inpl + 3];
        pRSP->anAudioBuffer[outp - 1] = pRSP->anAudioBuffer[inpr + 3];
        outp += 8;
        inpl += 4;
        inpr += 4;
    }

    return true;
}

static bool rspADistFilter2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 dpow = ((nCommandHi >> 16) & 0x0F) << 12;
    s32 ipow = ((nCommandHi >> 16) & 0xF0) >> 4;
    s16 outp = (s16)(nCommandLo >> 16) >> 1;
    s16 nCount = (s16)(nCommandHi & 0xFFFF) >> 1;
    s32 i;
    s64 mult;
    s32 pad[2];

    for (i = 0; i < nCount; i++) {
        mult = (s16)dpow | ((s16)ipow << 16);
        mult = (mult * (s64)pRSP->anAudioBuffer[outp + i]) >> 16;
        if (mult > 0x7FFF) {
            mult = 0x7FFF;
        } else if (mult < -0x8000) {
            mult = -0x8000;
        }
        pRSP->anAudioBuffer[outp + i] = mult;
    }

    return true;
}

static inline bool rspASetLoop2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->nAudioLoopAddress = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    return true;
}

static inline bool rspADMEMCopy2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 16) >> 1],
               &pRSP->anAudioBuffer[(s16)(nCommandHi & 0xFFFF) >> 1], (s16)((nCommandHi >> 16) & 0xFF) * sizeof(s16));
    return true;
}

static inline bool rspAHalfCut2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 count = nCommandHi & 0xFFFF;
    s32 outp = (nCommandLo & 0xFFFF) >> 1;
    s32 inpp = (s32)(nCommandLo >> 16) >> 1;
    s32 i;

    for (i = 0; i < count; i++) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[inpp + i * 2];
    }
    return true;
}

static inline bool rspASetEnvParam2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 temp;

    pRSP->vParams.anSlice[0] = 0;
    pRSP->vParams.anSlice[1] = 0;
    pRSP->vParams.anSlice[2] = 0;
    pRSP->vParams.anSlice[3] = 0;
    pRSP->vParams.anSlice[4] = 0;
    pRSP->vParams.anSlice[5] = 0;
    pRSP->vParams.anSlice[6] = 0;
    pRSP->vParams.anSlice[7] = 0;

    pRSP->stepF = nCommandHi & 0xFFFF;
    pRSP->stepL = (nCommandLo >> 16) & 0xFFFF;
    pRSP->stepR = nCommandLo & 0xFFFF;

    temp = (nCommandHi >> 8) & 0xFF00;
    pRSP->vParams.anSlice[4] = temp;
    temp += pRSP->stepF;
    pRSP->vParams.anSlice[5] = temp;

    return true;
}

static inline bool rspASetEnvParam22(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 tmp;

    tmp = (nCommandLo >> 16) & 0xFFFF;
    pRSP->vParams.anSlice[0] = tmp;
    tmp += pRSP->stepL;
    pRSP->vParams.anSlice[1] = tmp;

    tmp = nCommandLo & 0xFFFF;
    pRSP->vParams.anSlice[2] = tmp;
    tmp += pRSP->stepR;
    pRSP->vParams.anSlice[3] = tmp;

    return true;
}

static bool rspAEnvMixer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 effects[4];
    s16 vStep[8];
    u16 vParams[8];
    int i;
    int j;
    s32 inpp;
    s32 outL;
    s32 outR;
    s32 outFL;
    s32 outFR;
    s32 count;
    s32 temp;
    s32 id;
    s32 waveL;
    s32 waveR;
    s32 waveI;
    s32 srcL;
    s32 srcR;
    s32 srcFXL;
    s32 srcFXR;
    s32 pad;

    for (i = 0; i < 6; i++) {
        vParams[i] = pRSP->vParams.anSlice[i];
    }

    inpp = (s32)((nCommandHi >> 12) & 0xFF0) >> 1;
    outL = (s32)((nCommandLo >> 20) & 0xFF0) >> 1;
    outR = (s32)((nCommandLo >> 12) & 0xFF0) >> 1;
    outFL = (s32)((nCommandLo >> 4) & 0xFF0) >> 1;
    outFR = (s32)((nCommandLo << 4) & 0xFF0) >> 1;
    count = (s32)((nCommandHi >> 8) & 0xFF) >> 1;

    effects[0] = -(((s32)nCommandHi & 2) >> 1);
    effects[1] = -(((s32)nCommandHi & 1) >> 0);
    effects[2] = -(((s32)nCommandHi & 8) >> 1);
    effects[3] = -(((s32)nCommandHi & 4) >> 1);

    pRSP->stepL += pRSP->stepL;
    pRSP->stepR += pRSP->stepR;
    pRSP->stepF += pRSP->stepF;

    vStep[0] = vStep[1] = pRSP->stepL;
    vStep[2] = vStep[3] = pRSP->stepR;
    vStep[4] = vStep[5] = pRSP->stepF;

    if (nCommandHi & 0x10) {
        temp = outFL;
        outFL = outFR;
        outFR = temp;
    }

    for (i = 0; i < count; i += 8) {
        for (j = 0; j < 16; j++) {
            id = pRSP->anAudioBuffer[inpp + (2 * i + j)];
            srcL = pRSP->anAudioBuffer[outL + (2 * i + j)];
            srcR = pRSP->anAudioBuffer[outR + (2 * i + j)];
            srcFXL = pRSP->anAudioBuffer[outFL + (2 * i + j)];
            srcFXR = pRSP->anAudioBuffer[outFR + (2 * i + j)];

            waveL = (id * vParams[(j >> 3) + 0]) >> 16;
            waveR = (id * vParams[(j >> 3) + 2]) >> 16;

            waveL ^= effects[0];
            waveR ^= effects[1];

            srcL += waveL;
            srcR += waveR;

            if (srcL > 0x7FFF) {
                srcL = 0x7FFF;
            } else if (srcL < -0x8000) {
                srcL = -0x8000;
            }
            if (srcR > 0x7FFF) {
                srcR = 0x7FFF;
            } else if (srcR < -0x8000) {
                srcR = -0x8000;
            }

            waveL = (waveL * vParams[(j >> 3) + 4]) >> 16;
            waveR = (waveR * vParams[(j >> 3) + 4]) >> 16;

            waveL ^= effects[2];
            waveR ^= effects[3];

            srcFXL += waveL;
            srcFXR += waveR;

            if (srcFXL > 0x7FFF) {
                srcFXL = 0x7FFF;
            } else if (srcFXL < -0x8000) {
                srcFXL = -0x8000;
            }
            if (srcFXR > 0x7FFF) {
                srcFXR = 0x7FFF;
            } else if (srcFXR < -0x8000) {
                srcFXR = -0x8000;
            }

            pRSP->anAudioBuffer[outL + (2 * i + j)] = srcL;
            pRSP->anAudioBuffer[outR + (2 * i + j)] = srcR;
            pRSP->anAudioBuffer[outFL + (2 * i + j)] = srcFXL;
            pRSP->anAudioBuffer[outFR + (2 * i + j)] = srcFXR;
        }

        for (j = 0; j < 6; j++) {
            vParams[j] += vStep[j];
        }
    }

    return true;
}

static inline bool rspALoadBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], pData, (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static inline bool rspASaveBuffer2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[(nCommandHi & 0xFFFF) >> 1], (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static bool rspAPCM8Dec2(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 inpp;
    s32 outp;
    s32 count;
    s16 flags;
    s16 vtmp0[8];
    s16 vtmp1[8];
    int i;
    int j;
    s32 stateAddr;
    int s;
    void* pData;
    s16* pStateAddress;
    s16* pTempStateAddr;

    for (i = 0; i < 8; i++) {
        vtmp0[i] = 0;
        vtmp1[i] = 0;
    }

    inpp = pRSP->nAudioDMEMIn[0];
    outp = pRSP->nAudioDMEMOut[0];
    count = pRSP->nAudioCount[0];

    stateAddr = AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo);
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, stateAddr, NULL)) {
        return false;
    }
    pStateAddress = pData;

    for (i = 0; i < 16; i++) {
        pRSP->anAudioBuffer[outp + i] = 0;
    }

    flags = (nCommandHi >> 16) & 0xFFFF;
    if (!(flags & 1)) {
        pTempStateAddr = pStateAddress;

        if (flags & 2) {
            if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, pRSP->nAudioLoopAddress, NULL)) {
                return false;
            }
            pTempStateAddr = pData;
        }

        for (j = 0; j < 16; j++) {
            pRSP->anAudioBuffer[outp + j] = pTempStateAddr[j];
        }
    }

    if (count == 0) {
        for (j = 0; j < 16; j++) {
            pStateAddress[j] = pRSP->anAudioBuffer[outp + j];
        }
        return true;
    }

    for (i = 0; i < count; i += 16) {
        for (s = 0; s < 8; s++) {
            // bug: only accesses even bytes of input
            vtmp0[s] = (u16)(*((char*)&pRSP->anAudioBuffer[(i / 2) + s + inpp + 0]) << 8);
            vtmp1[s] = (u16)(*((char*)&pRSP->anAudioBuffer[(i / 2) + s + inpp + 4]) << 8);
        }
        for (s = 0; s < 8; s++) {
            pRSP->anAudioBuffer[i + s + outp + 0] = vtmp0[s];
            pRSP->anAudioBuffer[i + s + outp + 8] = vtmp1[s];
        }
    }

    for (s = 0; s < 16; s++) {
        pStateAddress[s] = pRSP->anAudioBuffer[outp + s + i];
    }

    return true;
}

static bool rspParseABI2(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    s32 pad[4];
    static bool nFirstTime = true;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime) {
        nFirstTime = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0: // A_SPNOOP
                break;
            case 1: // A_ADPCM
                if (((nCommandHi >> 16) & 4) != 0) {
                    rspAADPCMDec2Fast(pRSP, nCommandLo, nCommandHi);
                } else {
                    rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                }
                break;
            case 2: // A_CLEARBUFF
                rspAClearBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 3: // A_UNK3
                rspANoise2(pRSP, nCommandLo, nCommandHi);
                break;
            case 4: // A_ADDMIXER
                rspANMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 5: // A_RESAMPLE
                rspAResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 6: // A_RESAMPLE_ZOH
                rspASResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 7: // A_FILTER
                rspAFirFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 8: // A_SETBUFF
                rspASetBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 9: // A_DUPLICATE
                rspAWMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 10: // A_DMEMMOVE
                rspADMEMMove2(pRSP, nCommandLo, nCommandHi);
                break;
            case 11: // A_LOADADPCM
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                PAD_STACK();
                break;
            case 12: // A_MIXER
                rspAMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 13: // A_INTERLEAVE
                rspAInterleave2(pRSP, nCommandLo, nCommandHi);
                break;
            case 14: // A_HILOGAIN
                rspADistFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 15: // A_SETLOOP
                rspASetLoop2(pRSP, nCommandLo, nCommandHi);
                break;
            case 16: // ???
                rspADMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 17: // A_INTERL
                rspAHalfCut2(pRSP, nCommandLo, nCommandHi);
                break;
            case 18: // A_ENVSETUP1
                rspASetEnvParam2(pRSP, nCommandLo, nCommandHi);
                break;
            case 19: // A_ENVMIXER
                rspAEnvMixer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 20: // A_LOADBUFF
                rspALoadBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 21: // A_SAVEBUFF
                rspASaveBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 22: // A_ENVSETUP2
                rspASetEnvParam22(pRSP, nCommandLo, nCommandHi);
                break;
            case 23: // A_S8DEC
                rspAPCM8Dec2(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    return true;
}

static bool rspInitAudioDMEM3(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x1350;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1118;
    pRSP->anAudioBuffer[0x00C] = 0x1118;
    pRSP->anAudioBuffer[0x00D] = 0x175C;
    pRSP->anAudioBuffer[0x00E] = 0x1118;
    pRSP->anAudioBuffer[0x00F] = 0x1214;
    pRSP->anAudioBuffer[0x010] = 0x1230;
    pRSP->anAudioBuffer[0x011] = 0x1118;
    pRSP->anAudioBuffer[0x012] = 0x12EC;
    pRSP->anAudioBuffer[0x013] = 0x1CD0;
    pRSP->anAudioBuffer[0x014] = 0x1A18;
    pRSP->anAudioBuffer[0x015] = 0x126C;
    pRSP->anAudioBuffer[0x016] = 0x15EC;
    pRSP->anAudioBuffer[0x017] = 0x132C;
    pRSP->anAudioBuffer[0x018] = 0x1A8C;
    pRSP->anAudioBuffer[0x019] = 0x1ADC;
    pRSP->anAudioBuffer[0x01A] = 0x1C28;
    pRSP->anAudioBuffer[0x01B] = 0x1B38;
    pRSP->anAudioBuffer[0x01C] = 0x1C94;
    pRSP->anAudioBuffer[0x01D] = 0x1CB8;
    pRSP->anAudioBuffer[0x01E] = 0x1C50;
    pRSP->anAudioBuffer[0x01F] = 0x1118;
    pRSP->anAudioBuffer[0x020] = 0x1118;
    pRSP->anAudioBuffer[0x021] = 0x1118;
    pRSP->anAudioBuffer[0x022] = 0x1118;
    pRSP->anAudioBuffer[0x023] = 0x1118;
    pRSP->anAudioBuffer[0x024] = 0x1118;
    pRSP->anAudioBuffer[0x025] = 0x1118;
    pRSP->anAudioBuffer[0x026] = 0x1118;
    pRSP->anAudioBuffer[0x027] = 0x1118;
    pRSP->anAudioBuffer[0x028] = 0xF000;
    pRSP->anAudioBuffer[0x029] = 0x0F00;
    pRSP->anAudioBuffer[0x02A] = 0x00F0;
    pRSP->anAudioBuffer[0x02B] = 0x000F;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0010;
    pRSP->anAudioBuffer[0x02E] = 0x0100;
    pRSP->anAudioBuffer[0x02F] = 0x1000;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;

    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;

    // bug? 0x058-0x05F initialized twice with different values
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0000;
    pRSP->anAudioBuffer[0x05B] = 0x0001;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0000;
    pRSP->anAudioBuffer[0x05F] = 0x0001;

    pRSP->anAudioBuffer[0x060] = 0x2000;
    pRSP->anAudioBuffer[0x061] = 0x4000;
    pRSP->anAudioBuffer[0x062] = 0x6000;
    pRSP->anAudioBuffer[0x063] = 0x8000;
    pRSP->anAudioBuffer[0x064] = 0xA000;
    pRSP->anAudioBuffer[0x065] = 0xC000;
    pRSP->anAudioBuffer[0x066] = 0xE000;
    pRSP->anAudioBuffer[0x067] = 0xFFFF;
    pRSP->anAudioBuffer[0x068] = 0x0000;
    pRSP->anAudioBuffer[0x069] = 0xFFFF;
    pRSP->anAudioBuffer[0x06A] = 0x0000;
    pRSP->anAudioBuffer[0x06B] = 0x0000;
    pRSP->anAudioBuffer[0x06C] = 0x0000;
    pRSP->anAudioBuffer[0x06D] = 0x0000;
    pRSP->anAudioBuffer[0x06E] = 0x0000;
    pRSP->anAudioBuffer[0x06F] = 0x0000;
    pRSP->anAudioBuffer[0x070] = 0x0000;
    pRSP->anAudioBuffer[0x071] = 0x0000;
    pRSP->anAudioBuffer[0x072] = 0x0000;
    pRSP->anAudioBuffer[0x073] = 0x0000;
    pRSP->anAudioBuffer[0x074] = 0x0000;
    pRSP->anAudioBuffer[0x075] = 0x0000;
    pRSP->anAudioBuffer[0x076] = 0x0000;
    pRSP->anAudioBuffer[0x077] = 0x0000;
    pRSP->anAudioBuffer[0x078] = 0x0C39;
    pRSP->anAudioBuffer[0x079] = 0x66AD;
    pRSP->anAudioBuffer[0x07A] = 0x0D46;
    pRSP->anAudioBuffer[0x07B] = 0xFFDF;
    pRSP->anAudioBuffer[0x07C] = 0x0B39;
    pRSP->anAudioBuffer[0x07D] = 0x6696;
    pRSP->anAudioBuffer[0x07E] = 0x0E5F;
    pRSP->anAudioBuffer[0x07F] = 0xFFD8;
    pRSP->anAudioBuffer[0x080] = 0x0A44;
    pRSP->anAudioBuffer[0x081] = 0x6669;
    pRSP->anAudioBuffer[0x082] = 0x0F83;
    pRSP->anAudioBuffer[0x083] = 0xFFD0;
    pRSP->anAudioBuffer[0x084] = 0x095A;
    pRSP->anAudioBuffer[0x085] = 0x6626;
    pRSP->anAudioBuffer[0x086] = 0x10B4;
    pRSP->anAudioBuffer[0x087] = 0xFFC8;
    pRSP->anAudioBuffer[0x088] = 0x087D;
    pRSP->anAudioBuffer[0x089] = 0x65CD;
    pRSP->anAudioBuffer[0x08A] = 0x11F0;
    pRSP->anAudioBuffer[0x08B] = 0xFFBF;
    pRSP->anAudioBuffer[0x08C] = 0x07AB;
    pRSP->anAudioBuffer[0x08D] = 0x655E;
    pRSP->anAudioBuffer[0x08E] = 0x1338;
    pRSP->anAudioBuffer[0x08F] = 0xFFB6;
    pRSP->anAudioBuffer[0x090] = 0x06E4;
    pRSP->anAudioBuffer[0x091] = 0x64D9;
    pRSP->anAudioBuffer[0x092] = 0x148C;
    pRSP->anAudioBuffer[0x093] = 0xFFAC;
    pRSP->anAudioBuffer[0x094] = 0x0628;
    pRSP->anAudioBuffer[0x095] = 0x643F;
    pRSP->anAudioBuffer[0x096] = 0x15EB;
    pRSP->anAudioBuffer[0x097] = 0xFFA1;
    pRSP->anAudioBuffer[0x098] = 0x0577;
    pRSP->anAudioBuffer[0x099] = 0x638F;
    pRSP->anAudioBuffer[0x09A] = 0x1756;
    pRSP->anAudioBuffer[0x09B] = 0xFF96;
    pRSP->anAudioBuffer[0x09C] = 0x04D1;
    pRSP->anAudioBuffer[0x09D] = 0x62CB;
    pRSP->anAudioBuffer[0x09E] = 0x18CB;
    pRSP->anAudioBuffer[0x09F] = 0xFF8A;
    pRSP->anAudioBuffer[0x0A0] = 0x0435;
    pRSP->anAudioBuffer[0x0A1] = 0x61F3;
    pRSP->anAudioBuffer[0x0A2] = 0x1A4C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF7E;
    pRSP->anAudioBuffer[0x0A4] = 0x03A4;
    pRSP->anAudioBuffer[0x0A5] = 0x6106;
    pRSP->anAudioBuffer[0x0A6] = 0x1BD7;
    pRSP->anAudioBuffer[0x0A7] = 0xFF71;
    pRSP->anAudioBuffer[0x0A8] = 0x031C;
    pRSP->anAudioBuffer[0x0A9] = 0x6007;
    pRSP->anAudioBuffer[0x0AA] = 0x1D6C;
    pRSP->anAudioBuffer[0x0AB] = 0xFF64;
    pRSP->anAudioBuffer[0x0AC] = 0x029F;
    pRSP->anAudioBuffer[0x0AD] = 0x5EF5;
    pRSP->anAudioBuffer[0x0AE] = 0x1F0B;
    pRSP->anAudioBuffer[0x0AF] = 0xFF56;
    pRSP->anAudioBuffer[0x0B0] = 0x022A;
    pRSP->anAudioBuffer[0x0B1] = 0x5DD0;
    pRSP->anAudioBuffer[0x0B2] = 0x20B3;
    pRSP->anAudioBuffer[0x0B3] = 0xFF48;
    pRSP->anAudioBuffer[0x0B4] = 0x01BE;
    pRSP->anAudioBuffer[0x0B5] = 0x5C9A;
    pRSP->anAudioBuffer[0x0B6] = 0x2264;
    pRSP->anAudioBuffer[0x0B7] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B8] = 0x015B;
    pRSP->anAudioBuffer[0x0B9] = 0x5B53;
    pRSP->anAudioBuffer[0x0BA] = 0x241E;
    pRSP->anAudioBuffer[0x0BB] = 0xFF2C;
    pRSP->anAudioBuffer[0x0BC] = 0x0101;
    pRSP->anAudioBuffer[0x0BD] = 0x59FC;
    pRSP->anAudioBuffer[0x0BE] = 0x25E0;
    pRSP->anAudioBuffer[0x0BF] = 0xFF1E;
    pRSP->anAudioBuffer[0x0C0] = 0x00AE;
    pRSP->anAudioBuffer[0x0C1] = 0x5896;
    pRSP->anAudioBuffer[0x0C2] = 0x27A9;
    pRSP->anAudioBuffer[0x0C3] = 0xFF10;
    pRSP->anAudioBuffer[0x0C4] = 0x0063;
    pRSP->anAudioBuffer[0x0C5] = 0x5720;
    pRSP->anAudioBuffer[0x0C6] = 0x297A;
    pRSP->anAudioBuffer[0x0C7] = 0xFF02;
    pRSP->anAudioBuffer[0x0C8] = 0x001F;
    pRSP->anAudioBuffer[0x0C9] = 0x559D;
    pRSP->anAudioBuffer[0x0CA] = 0x2B50;
    pRSP->anAudioBuffer[0x0CB] = 0xFEF4;
    pRSP->anAudioBuffer[0x0CC] = 0xFFE2;
    pRSP->anAudioBuffer[0x0CD] = 0x540D;
    pRSP->anAudioBuffer[0x0CE] = 0x2D2C;
    pRSP->anAudioBuffer[0x0CF] = 0xFEE8;
    pRSP->anAudioBuffer[0x0D0] = 0xFFAC;
    pRSP->anAudioBuffer[0x0D1] = 0x5270;
    pRSP->anAudioBuffer[0x0D2] = 0x2F0D;
    pRSP->anAudioBuffer[0x0D3] = 0xFEDB;
    pRSP->anAudioBuffer[0x0D4] = 0xFF7C;
    pRSP->anAudioBuffer[0x0D5] = 0x50C7;
    pRSP->anAudioBuffer[0x0D6] = 0x30F3;
    pRSP->anAudioBuffer[0x0D7] = 0xFED0;
    pRSP->anAudioBuffer[0x0D8] = 0xFF53;
    pRSP->anAudioBuffer[0x0D9] = 0x4F14;
    pRSP->anAudioBuffer[0x0DA] = 0x32DC;
    pRSP->anAudioBuffer[0x0DB] = 0xFEC6;
    pRSP->anAudioBuffer[0x0DC] = 0xFF2E;
    pRSP->anAudioBuffer[0x0DD] = 0x4D57;
    pRSP->anAudioBuffer[0x0DE] = 0x34C8;
    pRSP->anAudioBuffer[0x0DF] = 0xFEBD;
    pRSP->anAudioBuffer[0x0E0] = 0xFF0F;
    pRSP->anAudioBuffer[0x0E1] = 0x4B91;
    pRSP->anAudioBuffer[0x0E2] = 0x36B6;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEF5;
    pRSP->anAudioBuffer[0x0E5] = 0x49C2;
    pRSP->anAudioBuffer[0x0E6] = 0x38A5;
    pRSP->anAudioBuffer[0x0E7] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E9] = 0x47ED;
    pRSP->anAudioBuffer[0x0EA] = 0x3A95;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFECE;
    pRSP->anAudioBuffer[0x0ED] = 0x4611;
    pRSP->anAudioBuffer[0x0EE] = 0x3C85;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F0] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F1] = 0x4430;
    pRSP->anAudioBuffer[0x0F2] = 0x3E74;
    pRSP->anAudioBuffer[0x0F3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x424A;
    pRSP->anAudioBuffer[0x0F6] = 0x4060;
    pRSP->anAudioBuffer[0x0F7] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F9] = 0x4060;
    pRSP->anAudioBuffer[0x0FA] = 0x424A;
    pRSP->anAudioBuffer[0x0FB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3E74;
    pRSP->anAudioBuffer[0x0FE] = 0x4430;
    pRSP->anAudioBuffer[0x0FF] = 0xFEC0;
    pRSP->anAudioBuffer[0x100] = 0xFEAB;
    pRSP->anAudioBuffer[0x101] = 0x3C85;
    pRSP->anAudioBuffer[0x102] = 0x4611;
    pRSP->anAudioBuffer[0x103] = 0xFECE;
    pRSP->anAudioBuffer[0x104] = 0xFEAC;
    pRSP->anAudioBuffer[0x105] = 0x3A95;
    pRSP->anAudioBuffer[0x106] = 0x47ED;
    pRSP->anAudioBuffer[0x107] = 0xFEDF;
    pRSP->anAudioBuffer[0x108] = 0xFEB0;
    pRSP->anAudioBuffer[0x109] = 0x38A5;
    pRSP->anAudioBuffer[0x10A] = 0x49C2;
    pRSP->anAudioBuffer[0x10B] = 0xFEF5;
    pRSP->anAudioBuffer[0x10C] = 0xFEB6;
    pRSP->anAudioBuffer[0x10D] = 0x36B6;
    pRSP->anAudioBuffer[0x10E] = 0x4B91;
    pRSP->anAudioBuffer[0x10F] = 0xFF0F;
    pRSP->anAudioBuffer[0x110] = 0xFEBD;
    pRSP->anAudioBuffer[0x111] = 0x34C8;
    pRSP->anAudioBuffer[0x112] = 0x4D57;
    pRSP->anAudioBuffer[0x113] = 0xFF2E;
    pRSP->anAudioBuffer[0x114] = 0xFEC6;
    pRSP->anAudioBuffer[0x115] = 0x32DC;
    pRSP->anAudioBuffer[0x116] = 0x4F14;
    pRSP->anAudioBuffer[0x117] = 0xFF53;
    pRSP->anAudioBuffer[0x118] = 0xFED0;
    pRSP->anAudioBuffer[0x119] = 0x30F3;
    pRSP->anAudioBuffer[0x11A] = 0x50C7;
    pRSP->anAudioBuffer[0x11B] = 0xFF7C;
    pRSP->anAudioBuffer[0x11C] = 0xFEDB;
    pRSP->anAudioBuffer[0x11D] = 0x2F0D;
    pRSP->anAudioBuffer[0x11E] = 0x5270;
    pRSP->anAudioBuffer[0x11F] = 0xFFAC;
    pRSP->anAudioBuffer[0x120] = 0xFEE8;
    pRSP->anAudioBuffer[0x121] = 0x2D2C;
    pRSP->anAudioBuffer[0x122] = 0x540D;
    pRSP->anAudioBuffer[0x123] = 0xFFE2;
    pRSP->anAudioBuffer[0x124] = 0xFEF4;
    pRSP->anAudioBuffer[0x125] = 0x2B50;
    pRSP->anAudioBuffer[0x126] = 0x559D;
    pRSP->anAudioBuffer[0x127] = 0x001F;
    pRSP->anAudioBuffer[0x128] = 0xFF02;
    pRSP->anAudioBuffer[0x129] = 0x297A;
    pRSP->anAudioBuffer[0x12A] = 0x5720;
    pRSP->anAudioBuffer[0x12B] = 0x0063;
    pRSP->anAudioBuffer[0x12C] = 0xFF10;
    pRSP->anAudioBuffer[0x12D] = 0x27A9;
    pRSP->anAudioBuffer[0x12E] = 0x5896;
    pRSP->anAudioBuffer[0x12F] = 0x00AE;
    pRSP->anAudioBuffer[0x130] = 0xFF1E;
    pRSP->anAudioBuffer[0x131] = 0x25E0;
    pRSP->anAudioBuffer[0x132] = 0x59FC;
    pRSP->anAudioBuffer[0x133] = 0x0101;
    pRSP->anAudioBuffer[0x134] = 0xFF2C;
    pRSP->anAudioBuffer[0x135] = 0x241E;
    pRSP->anAudioBuffer[0x136] = 0x5B53;
    pRSP->anAudioBuffer[0x137] = 0x015B;
    pRSP->anAudioBuffer[0x138] = 0xFF3A;
    pRSP->anAudioBuffer[0x139] = 0x2264;
    pRSP->anAudioBuffer[0x13A] = 0x5C9A;
    pRSP->anAudioBuffer[0x13B] = 0x01BE;
    pRSP->anAudioBuffer[0x13C] = 0xFF48;
    pRSP->anAudioBuffer[0x13D] = 0x20B3;
    pRSP->anAudioBuffer[0x13E] = 0x5DD0;
    pRSP->anAudioBuffer[0x13F] = 0x022A;
    pRSP->anAudioBuffer[0x140] = 0xFF56;
    pRSP->anAudioBuffer[0x141] = 0x1F0B;
    pRSP->anAudioBuffer[0x142] = 0x5EF5;
    pRSP->anAudioBuffer[0x143] = 0x029F;
    pRSP->anAudioBuffer[0x144] = 0xFF64;
    pRSP->anAudioBuffer[0x145] = 0x1D6C;
    pRSP->anAudioBuffer[0x146] = 0x6007;
    pRSP->anAudioBuffer[0x147] = 0x031C;
    pRSP->anAudioBuffer[0x148] = 0xFF71;
    pRSP->anAudioBuffer[0x149] = 0x1BD7;
    pRSP->anAudioBuffer[0x14A] = 0x6106;
    pRSP->anAudioBuffer[0x14B] = 0x03A4;
    pRSP->anAudioBuffer[0x14C] = 0xFF7E;
    pRSP->anAudioBuffer[0x14D] = 0x1A4C;
    pRSP->anAudioBuffer[0x14E] = 0x61F3;
    pRSP->anAudioBuffer[0x14F] = 0x0435;
    pRSP->anAudioBuffer[0x150] = 0xFF8A;
    pRSP->anAudioBuffer[0x151] = 0x18CB;
    pRSP->anAudioBuffer[0x152] = 0x62CB;
    pRSP->anAudioBuffer[0x153] = 0x04D1;
    pRSP->anAudioBuffer[0x154] = 0xFF96;
    pRSP->anAudioBuffer[0x155] = 0x1756;
    pRSP->anAudioBuffer[0x156] = 0x638F;
    pRSP->anAudioBuffer[0x157] = 0x0577;
    pRSP->anAudioBuffer[0x158] = 0xFFA1;
    pRSP->anAudioBuffer[0x159] = 0x15EB;
    pRSP->anAudioBuffer[0x15A] = 0x643F;
    pRSP->anAudioBuffer[0x15B] = 0x0628;
    pRSP->anAudioBuffer[0x15C] = 0xFFAC;
    pRSP->anAudioBuffer[0x15D] = 0x148C;
    pRSP->anAudioBuffer[0x15E] = 0x64D9;
    pRSP->anAudioBuffer[0x15F] = 0x06E4;
    pRSP->anAudioBuffer[0x160] = 0xFFB6;
    pRSP->anAudioBuffer[0x161] = 0x1338;
    pRSP->anAudioBuffer[0x162] = 0x655E;
    pRSP->anAudioBuffer[0x163] = 0x07AB;
    pRSP->anAudioBuffer[0x164] = 0xFFBF;
    pRSP->anAudioBuffer[0x165] = 0x11F0;
    pRSP->anAudioBuffer[0x166] = 0x65CD;
    pRSP->anAudioBuffer[0x167] = 0x087D;
    pRSP->anAudioBuffer[0x168] = 0xFFC8;
    pRSP->anAudioBuffer[0x169] = 0x10B4;
    pRSP->anAudioBuffer[0x16A] = 0x6626;
    pRSP->anAudioBuffer[0x16B] = 0x095A;
    pRSP->anAudioBuffer[0x16C] = 0xFFD0;
    pRSP->anAudioBuffer[0x16D] = 0x0F83;
    pRSP->anAudioBuffer[0x16E] = 0x6669;
    pRSP->anAudioBuffer[0x16F] = 0x0A44;
    pRSP->anAudioBuffer[0x170] = 0xFFD8;
    pRSP->anAudioBuffer[0x171] = 0x0E5F;
    pRSP->anAudioBuffer[0x172] = 0x6696;
    pRSP->anAudioBuffer[0x173] = 0x0B39;
    pRSP->anAudioBuffer[0x174] = 0xFFDF;
    pRSP->anAudioBuffer[0x175] = 0x0D46;
    pRSP->anAudioBuffer[0x176] = 0x66AD;
    pRSP->anAudioBuffer[0x177] = 0x0C39;

    return true;
}

static inline bool rspASetEnvParam3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->vParams.anSlice[0] = 0;
    pRSP->vParams.anSlice[1] = 0;
    pRSP->vParams.anSlice[2] = 0;
    pRSP->vParams.anSlice[3] = 0;
    pRSP->vParams.anSlice[4] = 0;
    pRSP->vParams.anSlice[5] = 0;
    pRSP->vParams.anSlice[6] = 0;
    pRSP->vParams.anSlice[7] = 0;

    pRSP->stepL = (nCommandLo >> 16) & 0xFFFF;
    pRSP->stepR = nCommandLo & 0xFFFF;
    pRSP->vParams.anSlice[4] = (nCommandHi >> 8) & 0xFF00;

    return true;
}

static inline bool rspASetEnvParam32(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    pRSP->vParams.anSlice[0] = (nCommandLo >> 16) & 0xFFFF;
    pRSP->vParams.anSlice[2] = nCommandLo & 0xFFFF;
    return true;
}

static inline bool rspALoadBuffer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(&pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)], pData,
                   (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static inline bool rspASaveBuffer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    void* pData;

    if (ramGetBuffer(SYSTEM_RAM(pRSP->pHost), &pData, AUDIO_SEGMENT_ADDRESS(pRSP, nCommandLo), NULL)) {
        xlHeapCopy(pData, &pRSP->anAudioBuffer[((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)],
                   (nCommandHi >> 12) & 0xFF0);
    }

    return true;
}

static bool rspAEnvMixer3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s16 v2[2];
    s16 v4[8];
    u16 vParams[8];
    int i;
    int j;
    s32 inpp;
    s32 outL;
    s32 outR;
    s32 outFL;
    s32 outFR;
    s32 count;
    // s32 id;
    s32 waveL;
    s32 waveR;
    s32 waveI;
    s32 srcL;
    s32 srcR;
    s32 srcFXL;
    s32 srcFXR;

    for (i = 0; i < 6; i++) {
        !pRSP->anAudioBuffer; // fake
        vParams[i] = pRSP->vParams.anSlice[i];
    }

    inpp = ((s32)((nCommandHi >> 12) & 0xFF0) >> 1) + ((s32)pRSP->nAudioMemOffset >> 1);
    outL = ((s32)((nCommandLo >> 20) & 0xFF0) >> 1) + ((s32)pRSP->nAudioMemOffset >> 1);
    outR = ((s32)((nCommandLo >> 12) & 0xFF0) >> 1) + ((s32)pRSP->nAudioMemOffset >> 1);
    outFL = ((s32)((nCommandLo >> 4) & 0xFF0) >> 1) + ((s32)pRSP->nAudioMemOffset >> 1);
    outFR = ((s32)((nCommandLo << 4) & 0xFF0) >> 1) + ((s32)pRSP->nAudioMemOffset >> 1);
    count = ((s32)(nCommandHi >> 18) & 0xFF) >> 1;

    v4[0] = pRSP->stepL;
    v4[2] = pRSP->stepR;

    v2[0] = pRSP->anAudioBuffer[(((s32)(nCommandHi & 2) >> 1) + 0xE0) >> 1];
    v2[1] = pRSP->anAudioBuffer[(((s32)(nCommandHi & 1) << 1) + 0xE0) >> 1];

    for (i = 0; i < count; i += 4) {
        for (j = 0; j < 8; j++) {
            waveI = pRSP->anAudioBuffer[inpp + (2 * i + j)];
            srcL = pRSP->anAudioBuffer[outL + (2 * i + j)];
            srcR = pRSP->anAudioBuffer[outR + (2 * i + j)];
            srcFXL = pRSP->anAudioBuffer[outFL + (2 * i + j)];
            srcFXR = pRSP->anAudioBuffer[outFR + (2 * i + j)];

            waveL = (vParams[0] * waveI) >> 16;
            waveR = (vParams[2] * waveI) >> 16;

            waveL ^= v2[0];
            waveR ^= v2[1];

            srcL += waveL;
            srcR += waveR;

            if (srcL > 0x7FFF) {
                srcL = 0x7FFF;
            } else if (srcL < -0x8000) {
                srcL = -0x8000;
            }
            if (srcR > 0x7FFF) {
                srcR = 0x7FFF;
            } else if (srcR < -0x8000) {
                srcR = -0x8000;
            }

            waveL = (waveL * vParams[4]) >> 16;
            waveR = (waveR * vParams[4]) >> 16;

            srcFXL += waveL;
            srcFXR += waveR;

            if (srcFXL > 0x7FFF) {
                srcFXL = 0x7FFF;
            } else if (srcFXL < -0x8000) {
                srcFXL = -0x8000;
            }
            if (srcFXR > 0x7FFF) {
                srcFXR = 0x7FFF;
            } else if (srcFXR < -0x8000) {
                srcFXR = -0x8000;
            }

            pRSP->anAudioBuffer[outL + (2 * i + j)] = srcL;
            pRSP->anAudioBuffer[outR + (2 * i + j)] = srcR;
            pRSP->anAudioBuffer[outFL + (2 * i + j)] = srcFXL;
            pRSP->anAudioBuffer[outFR + (2 * i + j)] = srcFXR;
        }

        vParams[0] += v4[0];
        vParams[2] += v4[2];
    }

    return true;
}

static inline bool rspAHalfCut3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    s32 count = nCommandHi & 0xFFFF;
    s32 outp = ((nCommandLo & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1);
    s32 inpp = ((s32)(nCommandLo >> 16) >> 1) + (pRSP->nAudioMemOffset >> 1);
    s32 i;

    for (i = 0; i < count; i++) {
        pRSP->anAudioBuffer[outp + i] = pRSP->anAudioBuffer[inpp + i * 2];
    }
    return true;
}

static bool rspAMix3(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u32 i;
    u32 nCount;
    s16 inScale;
    s16* srcP;
    s16* dstP;
    s32 tmp;
    s32 inData32;
    s32 outData32;

    nCount = (s32)((nCommandHi >> 12) & 0xFF0) >> 1;
    inScale = nCommandHi & 0xFFFF;
    srcP = &pRSP->anAudioBuffer[((s32)((nCommandLo >> 16) & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)];
    dstP = &pRSP->anAudioBuffer[((s32)(nCommandLo & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)];

    for (i = 0; i < nCount; i++) {
        outData32 = dstP[i];
        inData32 = srcP[i];

        outData32 += (inData32 * inScale) >> 15;
        if (outData32 > 0x7FFF) {
            outData32 = 0x7FFF;
        } else if (outData32 < -0x7FFF) {
            outData32 = -0x7FFF;
        }
        dstP[i] = outData32;
    }

    return true;
}

static inline bool rspADMEMCopy(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    xlHeapCopy(&pRSP->anAudioBuffer[(s16)(nCommandLo >> 17) + (pRSP->nAudioMemOffset >> 1)],
               &pRSP->anAudioBuffer[(s16)((nCommandHi & 0xFFFF) >> 1) + (pRSP->nAudioMemOffset >> 1)],
               (s16)((nCommandHi >> 16) & 0xFF) * sizeof(s16));

    return true;
}

static bool rspParseABI3(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    static bool nFirstTime = true;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime) {
        nFirstTime = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 19:
                rspAEnvMixer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 20:
                rspALoadBuffer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample1(pRSP, nCommandLo, nCommandHi);
                break;
            case 21:
                rspASaveBuffer3(pRSP, nCommandLo, nCommandHi);
                break;
            case 7:
                rspASegment1(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer1(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove1(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                break;
            case 12:
                rspAMix3(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave1(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop1(pRSP, nCommandLo, nCommandHi);
                break;
            case 16:
                rspADMEMCopy(pRSP, nCommandLo, nCommandHi);
                break;
            case 17:
                rspAHalfCut3(pRSP, nCommandLo, nCommandHi);
                break;
            case 18:
                rspASetEnvParam3(pRSP, nCommandLo, nCommandHi);
                break;
            case 22:
                rspASetEnvParam32(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    PAD_STACK();
    return true;
}

static bool rspInitAudioDMEM4(Rsp* pRSP) {
    pRSP->anAudioBuffer = pRSP->pDMEM;

    pRSP->anAudioBuffer[0x000] = 0x0000;
    pRSP->anAudioBuffer[0x001] = 0x0001;
    pRSP->anAudioBuffer[0x002] = 0x0002;
    pRSP->anAudioBuffer[0x003] = 0xFFFF;
    pRSP->anAudioBuffer[0x004] = 0x0020;
    pRSP->anAudioBuffer[0x005] = 0x0800;
    pRSP->anAudioBuffer[0x006] = 0x7FFF;
    pRSP->anAudioBuffer[0x007] = 0x4000;
    pRSP->anAudioBuffer[0x008] = 0x1118;
    pRSP->anAudioBuffer[0x009] = 0x12E0;
    pRSP->anAudioBuffer[0x00A] = 0x11DC;
    pRSP->anAudioBuffer[0x00B] = 0x1118;
    pRSP->anAudioBuffer[0x00C] = 0x1E8C;
    pRSP->anAudioBuffer[0x00D] = 0x1568;
    pRSP->anAudioBuffer[0x00E] = 0x1EFC;
    pRSP->anAudioBuffer[0x00F] = 0x1118;
    pRSP->anAudioBuffer[0x010] = 0x120C;
    pRSP->anAudioBuffer[0x011] = 0x1118;
    pRSP->anAudioBuffer[0x012] = 0x1298;
    pRSP->anAudioBuffer[0x013] = 0x1B24;
    pRSP->anAudioBuffer[0x014] = 0x1B40;
    pRSP->anAudioBuffer[0x015] = 0x1220;
    pRSP->anAudioBuffer[0x016] = 0x1D30;
    pRSP->anAudioBuffer[0x017] = 0x12D0;
    pRSP->anAudioBuffer[0x018] = 0x1818;
    pRSP->anAudioBuffer[0x019] = 0x18C4;
    pRSP->anAudioBuffer[0x01A] = 0x1A84;
    pRSP->anAudioBuffer[0x01B] = 0x1918;
    pRSP->anAudioBuffer[0x01C] = 0x1AE8;
    pRSP->anAudioBuffer[0x01D] = 0x1B0C;
    pRSP->anAudioBuffer[0x01E] = 0x1AAC;
    pRSP->anAudioBuffer[0x01F] = 0x1BAC;
    pRSP->anAudioBuffer[0x020] = 0x1C5C;
    pRSP->anAudioBuffer[0x021] = 0x1CB0;
    pRSP->anAudioBuffer[0x022] = 0x1860;
    pRSP->anAudioBuffer[0x023] = 0x1118;
    pRSP->anAudioBuffer[0x024] = 0x1118;
    pRSP->anAudioBuffer[0x025] = 0x1118;
    pRSP->anAudioBuffer[0x026] = 0x1118;
    pRSP->anAudioBuffer[0x027] = 0x1118;
    pRSP->anAudioBuffer[0x028] = 0xF000;
    pRSP->anAudioBuffer[0x029] = 0x0F00;
    pRSP->anAudioBuffer[0x02A] = 0x00F0;
    pRSP->anAudioBuffer[0x02B] = 0x000F;
    pRSP->anAudioBuffer[0x02C] = 0x0001;
    pRSP->anAudioBuffer[0x02D] = 0x0010;
    pRSP->anAudioBuffer[0x02E] = 0x0100;
    pRSP->anAudioBuffer[0x02F] = 0x1000;
    pRSP->anAudioBuffer[0x030] = 0x0002;
    pRSP->anAudioBuffer[0x031] = 0x0004;
    pRSP->anAudioBuffer[0x032] = 0x0006;
    pRSP->anAudioBuffer[0x033] = 0x0008;
    pRSP->anAudioBuffer[0x034] = 0x000A;
    pRSP->anAudioBuffer[0x035] = 0x000C;
    pRSP->anAudioBuffer[0x036] = 0x000E;
    pRSP->anAudioBuffer[0x037] = 0x0010;
    pRSP->anAudioBuffer[0x038] = 0x0001;
    pRSP->anAudioBuffer[0x039] = 0x0001;
    pRSP->anAudioBuffer[0x03A] = 0x0001;
    pRSP->anAudioBuffer[0x03B] = 0x0001;
    pRSP->anAudioBuffer[0x03C] = 0x0001;
    pRSP->anAudioBuffer[0x03D] = 0x0001;
    pRSP->anAudioBuffer[0x03E] = 0x0001;
    pRSP->anAudioBuffer[0x03F] = 0x0001;
    pRSP->anAudioBuffer[0x040] = 0x0000;
    pRSP->anAudioBuffer[0x041] = 0x0001;
    pRSP->anAudioBuffer[0x042] = 0x0002;
    pRSP->anAudioBuffer[0x043] = 0x0004;
    pRSP->anAudioBuffer[0x044] = 0x0008;
    pRSP->anAudioBuffer[0x045] = 0x0010;
    pRSP->anAudioBuffer[0x046] = 0x0100;
    pRSP->anAudioBuffer[0x047] = 0x0200;
    pRSP->anAudioBuffer[0x048] = 0x0001;
    pRSP->anAudioBuffer[0x049] = 0x0000;
    pRSP->anAudioBuffer[0x04A] = 0x0000;
    pRSP->anAudioBuffer[0x04B] = 0x0000;
    pRSP->anAudioBuffer[0x04C] = 0x0001;
    pRSP->anAudioBuffer[0x04D] = 0x0000;
    pRSP->anAudioBuffer[0x04E] = 0x0000;
    pRSP->anAudioBuffer[0x04F] = 0x0000;
    pRSP->anAudioBuffer[0x050] = 0x0000;
    pRSP->anAudioBuffer[0x051] = 0x0001;
    pRSP->anAudioBuffer[0x052] = 0x0000;
    pRSP->anAudioBuffer[0x053] = 0x0000;
    pRSP->anAudioBuffer[0x054] = 0x0000;
    pRSP->anAudioBuffer[0x055] = 0x0001;
    pRSP->anAudioBuffer[0x056] = 0x0000;
    pRSP->anAudioBuffer[0x057] = 0x0000;

    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0001;
    pRSP->anAudioBuffer[0x05B] = 0x0000;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0001;
    pRSP->anAudioBuffer[0x05F] = 0x0000;

    // bug? 0x058-0x05F initialized twice with different values
    pRSP->anAudioBuffer[0x058] = 0x0000;
    pRSP->anAudioBuffer[0x059] = 0x0000;
    pRSP->anAudioBuffer[0x05A] = 0x0000;
    pRSP->anAudioBuffer[0x05B] = 0x0001;
    pRSP->anAudioBuffer[0x05C] = 0x0000;
    pRSP->anAudioBuffer[0x05D] = 0x0000;
    pRSP->anAudioBuffer[0x05E] = 0x0000;
    pRSP->anAudioBuffer[0x05F] = 0x0001;

    pRSP->anAudioBuffer[0x060] = 0x2000;
    pRSP->anAudioBuffer[0x061] = 0x4000;
    pRSP->anAudioBuffer[0x062] = 0x6000;
    pRSP->anAudioBuffer[0x063] = 0x8000;
    pRSP->anAudioBuffer[0x064] = 0xA000;
    pRSP->anAudioBuffer[0x065] = 0xC000;
    pRSP->anAudioBuffer[0x066] = 0xE000;
    pRSP->anAudioBuffer[0x067] = 0xFFFF;
    pRSP->anAudioBuffer[0x068] = 0x0000;
    pRSP->anAudioBuffer[0x069] = 0xFFFF;
    pRSP->anAudioBuffer[0x06A] = 0x0000;
    pRSP->anAudioBuffer[0x06B] = 0x0000;
    pRSP->anAudioBuffer[0x06C] = 0x0000;
    pRSP->anAudioBuffer[0x06D] = 0x0000;
    pRSP->anAudioBuffer[0x06E] = 0x0000;
    pRSP->anAudioBuffer[0x06F] = 0x0000;
    pRSP->anAudioBuffer[0x070] = 0x0000;
    pRSP->anAudioBuffer[0x071] = 0x0000;
    pRSP->anAudioBuffer[0x072] = 0x0000;
    pRSP->anAudioBuffer[0x073] = 0x0000;
    pRSP->anAudioBuffer[0x074] = 0x0000;
    pRSP->anAudioBuffer[0x075] = 0x0000;
    pRSP->anAudioBuffer[0x076] = 0x0000;
    pRSP->anAudioBuffer[0x077] = 0x0000;
    pRSP->anAudioBuffer[0x078] = 0x0C39;
    pRSP->anAudioBuffer[0x079] = 0x66AD;
    pRSP->anAudioBuffer[0x07A] = 0x0D46;
    pRSP->anAudioBuffer[0x07B] = 0xFFDF;
    pRSP->anAudioBuffer[0x07C] = 0x0B39;
    pRSP->anAudioBuffer[0x07D] = 0x6696;
    pRSP->anAudioBuffer[0x07E] = 0x0E5F;
    pRSP->anAudioBuffer[0x07F] = 0xFFD8;
    pRSP->anAudioBuffer[0x080] = 0x0A44;
    pRSP->anAudioBuffer[0x081] = 0x6669;
    pRSP->anAudioBuffer[0x082] = 0x0F83;
    pRSP->anAudioBuffer[0x083] = 0xFFD0;
    pRSP->anAudioBuffer[0x084] = 0x095A;
    pRSP->anAudioBuffer[0x085] = 0x6626;
    pRSP->anAudioBuffer[0x086] = 0x10B4;
    pRSP->anAudioBuffer[0x087] = 0xFFC8;
    pRSP->anAudioBuffer[0x088] = 0x087D;
    pRSP->anAudioBuffer[0x089] = 0x65CD;
    pRSP->anAudioBuffer[0x08A] = 0x11F0;
    pRSP->anAudioBuffer[0x08B] = 0xFFBF;
    pRSP->anAudioBuffer[0x08C] = 0x07AB;
    pRSP->anAudioBuffer[0x08D] = 0x655E;
    pRSP->anAudioBuffer[0x08E] = 0x1338;
    pRSP->anAudioBuffer[0x08F] = 0xFFB6;
    pRSP->anAudioBuffer[0x090] = 0x06E4;
    pRSP->anAudioBuffer[0x091] = 0x64D9;
    pRSP->anAudioBuffer[0x092] = 0x148C;
    pRSP->anAudioBuffer[0x093] = 0xFFAC;
    pRSP->anAudioBuffer[0x094] = 0x0628;
    pRSP->anAudioBuffer[0x095] = 0x643F;
    pRSP->anAudioBuffer[0x096] = 0x15EB;
    pRSP->anAudioBuffer[0x097] = 0xFFA1;
    pRSP->anAudioBuffer[0x098] = 0x0577;
    pRSP->anAudioBuffer[0x099] = 0x638F;
    pRSP->anAudioBuffer[0x09A] = 0x1756;
    pRSP->anAudioBuffer[0x09B] = 0xFF96;
    pRSP->anAudioBuffer[0x09C] = 0x04D1;
    pRSP->anAudioBuffer[0x09D] = 0x62CB;
    pRSP->anAudioBuffer[0x09E] = 0x18CB;
    pRSP->anAudioBuffer[0x09F] = 0xFF8A;
    pRSP->anAudioBuffer[0x0A0] = 0x0435;
    pRSP->anAudioBuffer[0x0A1] = 0x61F3;
    pRSP->anAudioBuffer[0x0A2] = 0x1A4C;
    pRSP->anAudioBuffer[0x0A3] = 0xFF7E;
    pRSP->anAudioBuffer[0x0A4] = 0x03A4;
    pRSP->anAudioBuffer[0x0A5] = 0x6106;
    pRSP->anAudioBuffer[0x0A6] = 0x1BD7;
    pRSP->anAudioBuffer[0x0A7] = 0xFF71;
    pRSP->anAudioBuffer[0x0A8] = 0x031C;
    pRSP->anAudioBuffer[0x0A9] = 0x6007;
    pRSP->anAudioBuffer[0x0AA] = 0x1D6C;
    pRSP->anAudioBuffer[0x0AB] = 0xFF64;
    pRSP->anAudioBuffer[0x0AC] = 0x029F;
    pRSP->anAudioBuffer[0x0AD] = 0x5EF5;
    pRSP->anAudioBuffer[0x0AE] = 0x1F0B;
    pRSP->anAudioBuffer[0x0AF] = 0xFF56;
    pRSP->anAudioBuffer[0x0B0] = 0x022A;
    pRSP->anAudioBuffer[0x0B1] = 0x5DD0;
    pRSP->anAudioBuffer[0x0B2] = 0x20B3;
    pRSP->anAudioBuffer[0x0B3] = 0xFF48;
    pRSP->anAudioBuffer[0x0B4] = 0x01BE;
    pRSP->anAudioBuffer[0x0B5] = 0x5C9A;
    pRSP->anAudioBuffer[0x0B6] = 0x2264;
    pRSP->anAudioBuffer[0x0B7] = 0xFF3A;
    pRSP->anAudioBuffer[0x0B8] = 0x015B;
    pRSP->anAudioBuffer[0x0B9] = 0x5B53;
    pRSP->anAudioBuffer[0x0BA] = 0x241E;
    pRSP->anAudioBuffer[0x0BB] = 0xFF2C;
    pRSP->anAudioBuffer[0x0BC] = 0x0101;
    pRSP->anAudioBuffer[0x0BD] = 0x59FC;
    pRSP->anAudioBuffer[0x0BE] = 0x25E0;
    pRSP->anAudioBuffer[0x0BF] = 0xFF1E;
    pRSP->anAudioBuffer[0x0C0] = 0x00AE;
    pRSP->anAudioBuffer[0x0C1] = 0x5896;
    pRSP->anAudioBuffer[0x0C2] = 0x27A9;
    pRSP->anAudioBuffer[0x0C3] = 0xFF10;
    pRSP->anAudioBuffer[0x0C4] = 0x0063;
    pRSP->anAudioBuffer[0x0C5] = 0x5720;
    pRSP->anAudioBuffer[0x0C6] = 0x297A;
    pRSP->anAudioBuffer[0x0C7] = 0xFF02;
    pRSP->anAudioBuffer[0x0C8] = 0x001F;
    pRSP->anAudioBuffer[0x0C9] = 0x559D;
    pRSP->anAudioBuffer[0x0CA] = 0x2B50;
    pRSP->anAudioBuffer[0x0CB] = 0xFEF4;
    pRSP->anAudioBuffer[0x0CC] = 0xFFE2;
    pRSP->anAudioBuffer[0x0CD] = 0x540D;
    pRSP->anAudioBuffer[0x0CE] = 0x2D2C;
    pRSP->anAudioBuffer[0x0CF] = 0xFEE8;
    pRSP->anAudioBuffer[0x0D0] = 0xFFAC;
    pRSP->anAudioBuffer[0x0D1] = 0x5270;
    pRSP->anAudioBuffer[0x0D2] = 0x2F0D;
    pRSP->anAudioBuffer[0x0D3] = 0xFEDB;
    pRSP->anAudioBuffer[0x0D4] = 0xFF7C;
    pRSP->anAudioBuffer[0x0D5] = 0x50C7;
    pRSP->anAudioBuffer[0x0D6] = 0x30F3;
    pRSP->anAudioBuffer[0x0D7] = 0xFED0;
    pRSP->anAudioBuffer[0x0D8] = 0xFF53;
    pRSP->anAudioBuffer[0x0D9] = 0x4F14;
    pRSP->anAudioBuffer[0x0DA] = 0x32DC;
    pRSP->anAudioBuffer[0x0DB] = 0xFEC6;
    pRSP->anAudioBuffer[0x0DC] = 0xFF2E;
    pRSP->anAudioBuffer[0x0DD] = 0x4D57;
    pRSP->anAudioBuffer[0x0DE] = 0x34C8;
    pRSP->anAudioBuffer[0x0DF] = 0xFEBD;
    pRSP->anAudioBuffer[0x0E0] = 0xFF0F;
    pRSP->anAudioBuffer[0x0E1] = 0x4B91;
    pRSP->anAudioBuffer[0x0E2] = 0x36B6;
    pRSP->anAudioBuffer[0x0E3] = 0xFEB6;
    pRSP->anAudioBuffer[0x0E4] = 0xFEF5;
    pRSP->anAudioBuffer[0x0E5] = 0x49C2;
    pRSP->anAudioBuffer[0x0E6] = 0x38A5;
    pRSP->anAudioBuffer[0x0E7] = 0xFEB0;
    pRSP->anAudioBuffer[0x0E8] = 0xFEDF;
    pRSP->anAudioBuffer[0x0E9] = 0x47ED;
    pRSP->anAudioBuffer[0x0EA] = 0x3A95;
    pRSP->anAudioBuffer[0x0EB] = 0xFEAC;
    pRSP->anAudioBuffer[0x0EC] = 0xFECE;
    pRSP->anAudioBuffer[0x0ED] = 0x4611;
    pRSP->anAudioBuffer[0x0EE] = 0x3C85;
    pRSP->anAudioBuffer[0x0EF] = 0xFEAB;
    pRSP->anAudioBuffer[0x0F0] = 0xFEC0;
    pRSP->anAudioBuffer[0x0F1] = 0x4430;
    pRSP->anAudioBuffer[0x0F2] = 0x3E74;
    pRSP->anAudioBuffer[0x0F3] = 0xFEAC;
    pRSP->anAudioBuffer[0x0F4] = 0xFEB6;
    pRSP->anAudioBuffer[0x0F5] = 0x424A;
    pRSP->anAudioBuffer[0x0F6] = 0x4060;
    pRSP->anAudioBuffer[0x0F7] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F8] = 0xFEAF;
    pRSP->anAudioBuffer[0x0F9] = 0x4060;
    pRSP->anAudioBuffer[0x0FA] = 0x424A;
    pRSP->anAudioBuffer[0x0FB] = 0xFEB6;
    pRSP->anAudioBuffer[0x0FC] = 0xFEAC;
    pRSP->anAudioBuffer[0x0FD] = 0x3E74;
    pRSP->anAudioBuffer[0x0FE] = 0x4430;
    pRSP->anAudioBuffer[0x0FF] = 0xFEC0;
    pRSP->anAudioBuffer[0x100] = 0xFEAB;
    pRSP->anAudioBuffer[0x101] = 0x3C85;
    pRSP->anAudioBuffer[0x102] = 0x4611;
    pRSP->anAudioBuffer[0x103] = 0xFECE;
    pRSP->anAudioBuffer[0x104] = 0xFEAC;
    pRSP->anAudioBuffer[0x105] = 0x3A95;
    pRSP->anAudioBuffer[0x106] = 0x47ED;
    pRSP->anAudioBuffer[0x107] = 0xFEDF;
    pRSP->anAudioBuffer[0x108] = 0xFEB0;
    pRSP->anAudioBuffer[0x109] = 0x38A5;
    pRSP->anAudioBuffer[0x10A] = 0x49C2;
    pRSP->anAudioBuffer[0x10B] = 0xFEF5;
    pRSP->anAudioBuffer[0x10C] = 0xFEB6;
    pRSP->anAudioBuffer[0x10D] = 0x36B6;
    pRSP->anAudioBuffer[0x10E] = 0x4B91;
    pRSP->anAudioBuffer[0x10F] = 0xFF0F;
    pRSP->anAudioBuffer[0x110] = 0xFEBD;
    pRSP->anAudioBuffer[0x111] = 0x34C8;
    pRSP->anAudioBuffer[0x112] = 0x4D57;
    pRSP->anAudioBuffer[0x113] = 0xFF2E;
    pRSP->anAudioBuffer[0x114] = 0xFEC6;
    pRSP->anAudioBuffer[0x115] = 0x32DC;
    pRSP->anAudioBuffer[0x116] = 0x4F14;
    pRSP->anAudioBuffer[0x117] = 0xFF53;
    pRSP->anAudioBuffer[0x118] = 0xFED0;
    pRSP->anAudioBuffer[0x119] = 0x30F3;
    pRSP->anAudioBuffer[0x11A] = 0x50C7;
    pRSP->anAudioBuffer[0x11B] = 0xFF7C;
    pRSP->anAudioBuffer[0x11C] = 0xFEDB;
    pRSP->anAudioBuffer[0x11D] = 0x2F0D;
    pRSP->anAudioBuffer[0x11E] = 0x5270;
    pRSP->anAudioBuffer[0x11F] = 0xFFAC;
    pRSP->anAudioBuffer[0x120] = 0xFEE8;
    pRSP->anAudioBuffer[0x121] = 0x2D2C;
    pRSP->anAudioBuffer[0x122] = 0x540D;
    pRSP->anAudioBuffer[0x123] = 0xFFE2;
    pRSP->anAudioBuffer[0x124] = 0xFEF4;
    pRSP->anAudioBuffer[0x125] = 0x2B50;
    pRSP->anAudioBuffer[0x126] = 0x559D;
    pRSP->anAudioBuffer[0x127] = 0x001F;
    pRSP->anAudioBuffer[0x128] = 0xFF02;
    pRSP->anAudioBuffer[0x129] = 0x297A;
    pRSP->anAudioBuffer[0x12A] = 0x5720;
    pRSP->anAudioBuffer[0x12B] = 0x0063;
    pRSP->anAudioBuffer[0x12C] = 0xFF10;
    pRSP->anAudioBuffer[0x12D] = 0x27A9;
    pRSP->anAudioBuffer[0x12E] = 0x5896;
    pRSP->anAudioBuffer[0x12F] = 0x00AE;
    pRSP->anAudioBuffer[0x130] = 0xFF1E;
    pRSP->anAudioBuffer[0x131] = 0x25E0;
    pRSP->anAudioBuffer[0x132] = 0x59FC;
    pRSP->anAudioBuffer[0x133] = 0x0101;
    pRSP->anAudioBuffer[0x134] = 0xFF2C;
    pRSP->anAudioBuffer[0x135] = 0x241E;
    pRSP->anAudioBuffer[0x136] = 0x5B53;
    pRSP->anAudioBuffer[0x137] = 0x015B;
    pRSP->anAudioBuffer[0x138] = 0xFF3A;
    pRSP->anAudioBuffer[0x139] = 0x2264;
    pRSP->anAudioBuffer[0x13A] = 0x5C9A;
    pRSP->anAudioBuffer[0x13B] = 0x01BE;
    pRSP->anAudioBuffer[0x13C] = 0xFF48;
    pRSP->anAudioBuffer[0x13D] = 0x20B3;
    pRSP->anAudioBuffer[0x13E] = 0x5DD0;
    pRSP->anAudioBuffer[0x13F] = 0x022A;
    pRSP->anAudioBuffer[0x140] = 0xFF56;
    pRSP->anAudioBuffer[0x141] = 0x1F0B;
    pRSP->anAudioBuffer[0x142] = 0x5EF5;
    pRSP->anAudioBuffer[0x143] = 0x029F;
    pRSP->anAudioBuffer[0x144] = 0xFF64;
    pRSP->anAudioBuffer[0x145] = 0x1D6C;
    pRSP->anAudioBuffer[0x146] = 0x6007;
    pRSP->anAudioBuffer[0x147] = 0x031C;
    pRSP->anAudioBuffer[0x148] = 0xFF71;
    pRSP->anAudioBuffer[0x149] = 0x1BD7;
    pRSP->anAudioBuffer[0x14A] = 0x6106;
    pRSP->anAudioBuffer[0x14B] = 0x03A4;
    pRSP->anAudioBuffer[0x14C] = 0xFF7E;
    pRSP->anAudioBuffer[0x14D] = 0x1A4C;
    pRSP->anAudioBuffer[0x14E] = 0x61F3;
    pRSP->anAudioBuffer[0x14F] = 0x0435;
    pRSP->anAudioBuffer[0x150] = 0xFF8A;
    pRSP->anAudioBuffer[0x151] = 0x18CB;
    pRSP->anAudioBuffer[0x152] = 0x62CB;
    pRSP->anAudioBuffer[0x153] = 0x04D1;
    pRSP->anAudioBuffer[0x154] = 0xFF96;
    pRSP->anAudioBuffer[0x155] = 0x1756;
    pRSP->anAudioBuffer[0x156] = 0x638F;
    pRSP->anAudioBuffer[0x157] = 0x0577;
    pRSP->anAudioBuffer[0x158] = 0xFFA1;
    pRSP->anAudioBuffer[0x159] = 0x15EB;
    pRSP->anAudioBuffer[0x15A] = 0x643F;
    pRSP->anAudioBuffer[0x15B] = 0x0628;
    pRSP->anAudioBuffer[0x15C] = 0xFFAC;
    pRSP->anAudioBuffer[0x15D] = 0x148C;
    pRSP->anAudioBuffer[0x15E] = 0x64D9;
    pRSP->anAudioBuffer[0x15F] = 0x06E4;
    pRSP->anAudioBuffer[0x160] = 0xFFB6;
    pRSP->anAudioBuffer[0x161] = 0x1338;
    pRSP->anAudioBuffer[0x162] = 0x655E;
    pRSP->anAudioBuffer[0x163] = 0x07AB;
    pRSP->anAudioBuffer[0x164] = 0xFFBF;
    pRSP->anAudioBuffer[0x165] = 0x11F0;
    pRSP->anAudioBuffer[0x166] = 0x65CD;
    pRSP->anAudioBuffer[0x167] = 0x087D;
    pRSP->anAudioBuffer[0x168] = 0xFFC8;
    pRSP->anAudioBuffer[0x169] = 0x10B4;
    pRSP->anAudioBuffer[0x16A] = 0x6626;
    pRSP->anAudioBuffer[0x16B] = 0x095A;
    pRSP->anAudioBuffer[0x16C] = 0xFFD0;
    pRSP->anAudioBuffer[0x16D] = 0x0F83;
    pRSP->anAudioBuffer[0x16E] = 0x6669;
    pRSP->anAudioBuffer[0x16F] = 0x0A44;
    pRSP->anAudioBuffer[0x170] = 0xFFD8;
    pRSP->anAudioBuffer[0x171] = 0x0E5F;
    pRSP->anAudioBuffer[0x172] = 0x6696;
    pRSP->anAudioBuffer[0x173] = 0x0B39;
    pRSP->anAudioBuffer[0x174] = 0xFFDF;
    pRSP->anAudioBuffer[0x175] = 0x0D46;
    pRSP->anAudioBuffer[0x176] = 0x66AD;
    pRSP->anAudioBuffer[0x177] = 0x0C39;

    return true;
}

static inline bool rspAInterleave4(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nLeft = (s32)(nCommandLo >> 16) / 2;
    u16 nRight = (s32)(nCommandLo & 0xFFFF) / 2;
    u32 nDMEMOut = pRSP->nAudioDMEMOut[0];
    u32 iIndex;
    u32 iIndex2;

    for (iIndex = 0, iIndex2 = 0; iIndex < pRSP->nAudioCount[0]; iIndex++, iIndex2++) {
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 0] = pRSP->anAudioBuffer[nLeft + iIndex2];
        pRSP->anAudioBuffer[nDMEMOut + 2 * iIndex + 1] = pRSP->anAudioBuffer[nRight + iIndex2];
    }

    return true;
}

static inline bool rspADMEMMove4(Rsp* pRSP, u32 nCommandLo, u32 nCommandHi) {
    u16 nDMEMOut = (s32)(nCommandLo >> 16) / 2;
    u16 nCount = nCommandLo & 0xFFFF;
    u32 nDMEMIn = (nCommandHi & 0xFFFF) / 2;

    xlHeapCopy(&pRSP->anAudioBuffer[nDMEMOut], &pRSP->anAudioBuffer[nDMEMIn], nCount);
    return true;
}

static bool rspParseABI4(Rsp* pRSP, RspTask* pTask) {
    u32 nCommandLo;
    u32 nCommandHi;
    u32* pABI32;
    u32* pABILast32;
    u32 nSize;
    s32 pad[2];
    static bool nFirstTime = true;

    nSize = pTask->nLengthMBI & 0x7FFFFF;
    if (!ramGetBuffer(SYSTEM_RAM(pRSP->pHost), (void**)&pABI32, pTask->nOffsetMBI, NULL)) {
        return false;
    }
    pABILast32 = pABI32 + (nSize >> 2);

    if (nFirstTime) {
        nFirstTime = false;
    }

    while (pABI32 < pABILast32) {
        nCommandLo = pABI32[1];
        nCommandHi = pABI32[0];
        pABI32 += 2;
        switch (nCommandHi >> 24) {
            case 0:
                break;
            case 1:
                rspAADPCMDec1Fast(pRSP, nCommandLo, nCommandHi);
                break;
            case 2:
                rspAClearBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 4:
                rspANMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 5:
                rspAResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 6:
                rspASResample2(pRSP, nCommandLo, nCommandHi);
                break;
            case 8:
                rspASetBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 10:
                rspADMEMMove4(pRSP, nCommandLo, nCommandHi);
                break;
            case 11:
                rspALoadADPCM2(pRSP, nCommandLo, nCommandHi);
                PAD_STACK();
                break;
            case 12:
                rspAMix2(pRSP, nCommandLo, nCommandHi);
                break;
            case 13:
                rspAInterleave4(pRSP, nCommandLo, nCommandHi);
                break;
            case 14:
                rspAPoleFilter1(pRSP, nCommandLo, nCommandHi);
                break;
            case 15:
                rspASetLoop2(pRSP, nCommandLo, nCommandHi);
                break;
            case 16:
                rspADMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            case 17:
                rspAHalfCut2(pRSP, nCommandLo, nCommandHi);
                break;
            case 18:
                rspASetEnvParam2(pRSP, nCommandLo, nCommandHi);
                break;
            case 19:
                rspAEnvMixer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 20:
                rspALoadBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 21:
                rspASaveBuffer2(pRSP, nCommandLo, nCommandHi);
                break;
            case 22:
                rspASetEnvParam22(pRSP, nCommandLo, nCommandHi);
                break;
            case 23:
                rspAPCM8Dec2(pRSP, nCommandLo, nCommandHi);
                break;
            case 24:
                rspADistFilter2(pRSP, nCommandLo, nCommandHi);
                break;
            case 25:
                break;
            case 26:
                rspAWMEMCopy2(pRSP, nCommandLo, nCommandHi);
                break;
            default:
                return false;
        }
    }

    PAD_STACK();
    PAD_STACK();
    return true;
}
