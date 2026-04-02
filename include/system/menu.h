#ifndef _XENO_MENU_H
#define _XENO_MENU_H

#include "psyq/libgpu.h"

typedef struct {
    /* 0x0  */ DRAWENV drawEnv;
    /* 0x5C */ DISPENV dispEnv;
    /* 0x70 */ unsigned long ot[16];
    /* 0xB0 */ u32 unkB0;
} GfxEnvironment; // Size: 0xB4

typedef struct {
    /* 0x0    */ u8 unk0[108];
    /* 0x6C   */ GfxEnvironment gfxEnvs[2];
    /* 0x1D4  */ GfxEnvironment* pGfxEnv;
    /* 0x1D8  */ u8 unk1D8[0x100];
    /* 0x2D8  */ u32 unk2D8;
    /* 0x2DC  */ u8 unk2DC[0x48];
    /* 0x324  */ u8 unk324;
    /* 0x325  */ u8 unk325;
    /* 0x326  */ u8 unk326;
    /* 0x327  */ u8 unk327;
    /* 0x328  */ u8 unk328[0x1B6C];
    /* 0x1E94 */ u8 unk1E94;
    /* 0x1E95 */ u8 unk1E95;
    /* 0x1E96 */ u8 unk1E96[2];
} SystemMenu; // Size: 0x1E98

extern SystemMenu* g_Menu;
extern u8 g_MenuDebugEnabled;

#endif