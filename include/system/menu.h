#ifndef _XENO_MENU_H
#define _XENO_MENU_H

#include "psyq/libgpu.h"
#include "main/game.h"

#define MENU_TEX_WINDOW_BORDER_TOP_LEFT 0xFD
#define MENU_TEX_WINDOW_BORDER_TOP 0xFE
#define MENU_TEX_WINDOW_BORDER_TOP_RIGHT 0xFF
#define MENU_TEX_WINDOW_BORDER_LEFT 0x100
#define MENU_TEX_WINDOW_BORDER_RIGHT 0x101
#define MENU_TEX_WINDOW_BORDER_BOTTOM_LEFT 0x102
#define MENU_TEX_WINDOW_BORDER_BOTTOM 0x103
#define MENU_TEX_WINDOW_BORDER_BOTTOM_RIGHT 0x104

#define MENU_TEX_SCROLL_BAR_ORNAMENT 0x105
#define MENU_TEX_SCROLL_BAR_EMPTY 0x106

#define MENU_TEX_POINTER_CURSOR 0x108

#define MENU_TEX_CHARACTER_PORTRAITS_SMALL 0x14E
#define MENU_TEX_FEI_PORTRAIT_SMALL 0x14E
#define MENU_TEX_ELLY_PORTRAIT_SMALL 0x14F
#define MENU_TEX_CITAN_PORTRAIT_SMALL 0x150
#define MENU_TEX_BART_PORTRAIT_SMALL 0x151
#define MENU_TEX_BILLY_PORTRAIT_SMALL 0x152
#define MENU_TEX_RICO_PORTRAIT_SMALL 0x153
#define MENU_TEX_EMERALDA_YOUNG_PORTRAIT_SMALL 0x154
#define MENU_TEX_CHU_CHU_PORTRAIT_SMALL 0x155
#define MENU_TEX_MARIA_PORTRAIT_SMALL 0x156
#define MENU_TEX_UNUSED_PORTRAIT_SMALL 0x157 // Possibly intended for Margie?
#define MENU_TEX_EMERALDA_ADULT_PORTRAIT_SMALL 0x158


// Mapped inputs
#define MENU_INPUT_RIGHT 0x0
#define MENU_INPUT_DOWN 0x1
#define MENU_INPUT_LEFT 0x2
#define MENU_INPUT_UP 0x3
#define MENU_INPUT_CONFIRM 0x4
#define MENU_INPUT_BACK 0x5




#define MENU_MAX_NUM_WINDOWS 0x7
#define MENU_MAX_NUM_CURSORS 0x4
#define MENU_WINDOW_BORDER_SIZE 0x8

#define MENU_DATA_INITIALIZE 0x1
#define MENU_DATA_FREE 0x0


typedef struct {
    /* 0x0  */ DRAWENV drawEnv;
    /* 0x5C */ DISPENV dispEnv;
    /* 0x70 */ unsigned long ot[16];
    /* 0xB0 */ u32 unkB0;
} GfxEnvironment; // Size: 0xB4

typedef struct {
    /* 0x0   */ u8 unk8[0x50];
    /* 0x50  */ POLY_G4 polyG4s[2];
    /* 0x98  */ POLY_F4 polyF4s[2];
    /* 0xC8  */ LINE_F3 lines1[2];
    /* 0xF8  */ LINE_F3 lines2[2];
    /* 0x128 */ DR_MODE drModes1[2];
    /* 0x140 */ DR_MODE drModes2[2];
    /* 0x158 */ u8 unk158[3];
    /* 0x15B */ u8 unk15B;
} MenuUnk1; // Size: 0x15C

typedef struct {
    /* 0x0   */ u8 unk0[0xB80];
    /* 0xB80 */ TIM_IMAGE tim;
    /* 0xB94 */ u8 unkB94[0x4000];
    /* 0x4B94 */ u8 unk4B94;
    /* 0x4B95 */ u8 unk4B95;
    /* 0x4B96 */ u8 unk4B96;
    /* 0x4B97 */ u8 unk4B97;
    /* 0x4B98 */ u8 unk4B98[0x5C];
    /* 0x4BF4 */ u8 unk4BF4[0x20];
    /* 0x4C14 */ u8 unk4C14[0x80];
    /* 0x4C94 */ u8 unk4C94[0x2E8];
    /* 0x4F7C */ s32 unk4F7C;
    /* 0x4F80 */ u8 unk4F80[0xB4];
} MenuUnk2; // Size: 0x5034

typedef struct {
    /* 0x0  */ u8 unk0[0x3];
    /* 0x3  */ u8 unk3;
    /* 0x4  */ u8 unk4;
    /* 0x5  */ u8 unk5[0x7];
    /* 0xC  */ u8 unkC[0x8];
    /* 0x14 */ u8 unk14[0x6];
    /* 0x1A */ u8 unk1A[0x6];
    /* 0x20 */ u8 shouldRenderWindow[MENU_MAX_NUM_WINDOWS];
    /* 0x27 */ u8 unk27[MENU_MAX_NUM_WINDOWS];
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u_char shouldRenderCursors;
    /* 0x30 */ u8 currentCharacterIDs[0x3];
    /* 0x33 */ u8 _pad33;
    /* 0x34 */ u8 unk34[0x4];
    /* 0x38 */ u8 unk38[0xE];
    /* 0x46 */ u8 unk46; // Should render characters?
    /* 0x47 */ u8 unk47[0x25];
} MenuManager; // Size: 0x6C

typedef struct {
    /* 0x0    */ u8 unk0[0x1180];
    /* 0x1180 */ RECT unk1180;
    /* 0x1188 */ u8 unk1188[0xC];
} MenuUnk4; // Size: 0x1194

typedef struct {
    /* 0x0 */ u8 unk0[0x140C];
} MenuUnk5; // Size: 0x140C

typedef struct {
    /* 0x0 */ u8 unk0[0xCC];
} MenuUnk6; // Size: 0xCC

// Character Info
typedef struct {
    /* 0x0   */ POLY_FT4 polysDescriptionStrings[18];
    /* 0x2D0 */ POLY_FT4 polys2D0[2]; // Unknown if bigger or not
    /* 0x320 */ u8 unk320[0x140];
    /* 0x460 */ POLY_FT4 polysPortraitSmall[2];
    /* 0x4B0 */ POLY_FT4 polys4B0[2];
    /* 0x500 */ POLY_FT4 polysLevelString[6];
    /* 0x5F0 */ POLY_FT4 polys5F0[6];
    /* 0x6E0 */ POLY_FT4 polysHpString[6];
    /* 0x7D0 */ u8 unk7D0[0xA0];
    /* 0x870 */ POLY_FT4 polysMaxHpString[6];
    /* 0x960 */ u8 unk960[0xA0];
    /* 0xA00 */ POLY_FT4 polysMpString[4];
    /* 0xAA0 */ u8 unkAA0[0x50];
    /* 0xAF0 */ POLY_FT4 polysMaxMpString[4];
    /* 0xB90 */ u8 unkB90[0x50];
    /* 0xBE0 */ u8 levelStringLength;
    /* 0xBE1 */ u8 unkBE1; // Num polys5F0
    /* 0xBE2 */ u8 hpStringLength;
    /* 0xBE3 */ u8 maxHpStringLength;
    /* 0xBE4 */ u8 mpStringLength;
    /* 0xBE5 */ u8 maxMpStringLength;
    /* 0xBE6 */ u8 renderContext;
    /* 0xBE7 */ u8 unkBE7; // Is active / should render?
    /* 0xBE8 */ u8 descriptionStringsLength;
    /* 0xBE9 */ u8 unkBE9;
    /* 0xBEA */ u8 unkBEA[0x2];
} MenuCharacter; // Size: 0xBEC

typedef struct {
    /* 0x0  */ POLY_FT4 polys[2];
    /* 0x50 */ u8 unk50[0x28];
    /* 0x78 */ void* unk78;
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
} MenuUnk8; // Size: 0x80

typedef struct {
    /* 0x0   */ POLY_FT4 polysWindowBorderCorners[8];
    /* 0x140 */ POLY_FT4 polysWindowBorderTop[4]; // First 2 = Halo, Second 2 = White Border
    /* 0x1E0 */ POLY_FT4 polysWindowBorderBottom[4]; // First 2 = Halo, Second 2 = White Border
    /* 0x280 */ POLY_FT4 polysWindowBorderLeft[4]; // First 2 = Halo, Second 2 = White Border
    /* 0x320 */ POLY_FT4 polysWindowBorderRight[4]; // First 2 = Halo, Second 2 = White Border
    /* 0x3C0 */ POLY_FT4 polysScrollBarEmpty[2];
    /* 0x410 */ POLY_FT4 polysScrollBarEnds[4];
    /* 0x4B0 */ POLY_G4 polysBackground[2];
    /* 0x4F8 */ DR_MODE drawModes[2];
    /* 0x510 */ SVECTOR vertsWindowBorderCorners[16];
    /* 0x590 */ SVECTOR vertsWindowBorderTop1[4]; // First half of top border
    /* 0x5B0 */ SVECTOR vertsWindowBorderTop2[4]; // Second half of top border
    /* 0x5D0 */ SVECTOR vertsWindowBorderBottom1[4]; // First half of bottom border
    /* 0x5F0 */ SVECTOR vertsWindowBorderBottom2[4]; // Second half of bottom border
    /* 0x610 */ SVECTOR vertsWindowBorderLeft1[4]; // First half of left border
    /* 0x630 */ SVECTOR vertsWindowBorderLeft2[4]; // Second half of left border
    /* 0x650 */ SVECTOR vertsWindowBorderRight1[4]; // First half of right border
    /* 0x670 */ SVECTOR vertsWindowBorderRight2[4]; // Second half of right border
    /* 0x690 */ SVECTOR vertsBackground[4];
    /* 0x6B0 */ SVECTOR vertsScrollBarEmpty[4];
    /* 0x6D0 */ SVECTOR vertsScrollBarEnds[8];
    /* 0x710 */ s32 unk710;
    /* 0x714 */ s32 unk714; // If 0, use default transform matrix when rendering
    /* 0x718 */ int zIndex; // Current OT index / offset
    /* 0x71C */ u8 renderContext;
    /* 0x71D */ u8 hasScrollBar;
    /* 0x71E */ u8 _pad71E[0x2];
} MenuWindow; // Size: 0x720

// Pointer Cursors (up to 4)?
typedef struct {
    /* 0x0  */  POLY_FT4 polysCursor[8];
    /* 0x140 */ u8 shouldRender[0x4]; // Should render / isActive?
    /* 0x144 */ u8 unk144[0x4]; // Should update positions?
    /* 0x148 */ u8 renderContexts[0x4];
} MenuPointerCursors; // Size: 0x14C

typedef struct {
    /* 0x0  */ u_short x;
    /* 0x2  */ u_short y;
    /* 0x4  */ u_short width;
    /* 0x6  */ u_short height;
    /* 0x8  */ u_short unk8; // Width
    /* 0xA  */ u_short unkA; // Height
    /* 0xC  */ int zIndex;
    /* 0x10 */ u_char index;
    /* 0x11 */ u_char unk11;
    /* 0x12 */ u_char unk12;
    /* 0x13 */ u_char hasScrollBar;
    /* 0x13 */ u8 unk14[0x4];
} MenuWindowParameters; // Size: 0x18

typedef struct {
    /* 0x0  */ POLY_FT4 polys[2];
    /* 0x50 */ SVECTOR vertices[4];
    /* 0x70 */ u8 unk70[0xD];
    /* 0x7D */ u8 renderContext;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
} MenuUnk11; // Size 0x80

typedef struct {
    /* 0x0    */ u8 unk0[108];
    /* 0x6C   */ GfxEnvironment gfxEnvs[2];
    /* 0x1D4  */ GfxEnvironment* pGfxEnv;
    /* 0x1D8  */ u8 unk1D8[0x100];
    /* 0x2D8  */ u32 unk2D8;
    /* 0x2DC  */ void* unk2DC; // Resources / Textured polys
    /* 0x2E0  */ void* unk2E0; // Pointer to resources (bin 3)
    /* 0x2E4  */ void* unk2E4; // Pointer to SEDS file
    /* 0x2E8  */ u8 unk2E8[0x20];
    /* 0x308  */ s32 renderContext;
    /* 0x30C  */ u8 availableCharacters[0x10];
    /* 0x31C  */ u8 digits[0x9]; // Digits
    /* 0x325  */ u8 input;
    /* 0x326  */ u8 unk326;
    /* 0x327  */ u8 unk327;
    /* 0x328  */ u8 unk328[0x4];
    /* 0x32C  */ MenuUnk2* unk32C;
    /* 0x330  */ MenuUnk6* unk330;
    /* 0x334  */ u8 unk334;
    /* 0x335  */ u8 unk335;
    /* 0x336  */ u8 unk336;
    /* 0x337  */ u8 unk337;
    /* 0x338  */ u8 unk338[0x4];
    /* 0x33C */ MenuManager* pManager;
    /* 0x340  */ u8 unk340[0x8];
    /* 0x348  */ MenuUnk1* unk348;
    /* 0x34C  */ u8 unk34C[0x4];
    /* 0x350  */ MenuUnk4* unk350;
    /* 0x354  */ MenuUnk5* unk354;
    /* 0x358  */ u8 unk358[0xC];
    /* 0x364  */ MenuWindow* windows[MENU_MAX_NUM_WINDOWS];
    /* 0x380  */ MenuWindowParameters* windowParameters[MENU_MAX_NUM_WINDOWS];
    /* 0x39C  */ u8 unk39C[0x8C];
    /* 0x428  */ MenuPointerCursors* pCursors;
    /* 0x42C  */ u8 unk42C[0x40];

    // Window borders
    /* 0x46C  */ u32 unk46C; // UV?
    /* 0x470  */ s32 texPage0;
    /* 0x474  */ s32 clutX0;
    /* 0x478  */ s32 clutY0;
    /* 0x47C  */ s32 texPageX0;
    /* 0x480  */ s32 texPageY0;
    /* 0x484  */ u32 unk484; // UV?
    /* 0x488  */ s32 texPage1;
    /* 0x48C  */ s32 clutX1;
    /* 0x490  */ s32 clutY1;
    /* 0x494  */ s32 texPageX1;
    /* 0x498  */ s32 texPageY1;
    /* 0x49C  */ u32 unk49C; // UV?
    /* 0x4A0  */ s32 texPage2;
    /* 0x4A4  */ s32 clutX2;
    /* 0x4A8  */ s32 clutY2;
    /* 0x4AC  */ s32 texPageX2;
    /* 0x4B0  */ s32 texPageY2;
    /* 0x4B4  */ u32 unk4B4; // UV?
    /* 0x4B8  */ s32 texPage3;
    /* 0x4BC  */ s32 clutX3;
    /* 0x4C0  */ s32 clutY3;
    /* 0x4C4  */ s32 texPageX3;
    /* 0x4C8  */ s32 texPageY3;

    /* 0x4CC  */ u8 unk4CC[0x14];
    /* 0x4E0  */ MenuUnk8 unk4E0[4];
    /* 0x6E0  */ MenuUnk8 unk6E0[8];
    /* 0xAE0  */ MenuUnk11 unkAE0[6];
    /* 0xDE0  */ u8 unk8D0[0x1010];
    /* 0x1DF0 */ MenuCharacter* benchedCharacters[MAX_BENCHED_PARTY_MEMBERS];
    /* 0x1E08 */ MenuCharacter* currentCharacters[MAX_PARTY_MEMBERS];
    /* 0x1E14 */ u8 unk1E14[MAX_GAME_CHARACTERS];
    /* 0x1E1F */ u8 unk1E1F[0x75];
    /* 0x1E94 */ u8 unk1E94;
    /* 0x1E95 */ u8 unk1E95;
    /* 0x1E96 */ u8 unk1E96[2];
} SystemMenu; // Size: 0x1E98

extern SystemMenu* g_Menu;
extern u8 g_MenuDebugEnabled;

#endif