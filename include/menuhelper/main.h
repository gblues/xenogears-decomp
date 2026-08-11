#ifndef __MENUHELPER_MAIN_H__
#define __MENUHELPER_MAIN_H__

#include "psyq/libgpu.h"
#include "psyq/libgte.h"

struct _menu_scene;
typedef struct _menu_scene MenuScene;

struct _menu_scene {
    /* 0x00 */ MenuScene* parent;
    /* 0x04 */ u_char doTransform;
    /* 0x05 */ u_char doRotate;
    /* 0x06 */ u_char rotDirection;
    /* 0x07 */ u_char unk7;
    /* 0x08 */ u_char unk8;
    /* 0x09 */ u_char unk9;
    /* 0x0A */ u_short length;
    /* 0x0c */ MATRIX matrix1;
    /* 0x2c */ MATRIX matrix2;
    /* 0x4c */ SVECTOR vec1;
    /* 0x54 */ SVECTOR vec2;
    /* 0x5c */ long unk5C[3];
    /* 0x68 */ void *unk68;
    /* 0x6c */ int unk6C;
    /* 0x70 */ u_char unk70[12];
}; // Size: 0x7C

typedef struct {
    // NOTE: These first four blocks are sometimes used as SVECTORs, but
    // they can't be defined as such since the padding field is actually used
    
    /* 0x0  */ u_short x0;
    /* 0x2  */ u_short y0;
    /* 0x4  */ u_short z0;
    /* 0x6  */ u16 unk6;
    
    /* 0x8  */ u_short x1;
    /* 0xA  */ u_short y1;
    /* 0xC  */ u_short z1;
    /* 0xE  */ short unkE;
    
    /* 0x10 */ u_short x2;
    /* 0x12 */ u_short y2;
    /* 0x14 */ u_short z2;
    /* 0x16 */ short unk16;
    
    /* 0x18 */ u_short x3;
    /* 0x1A */ u_short y3;
    /* 0x1C */ u_short z3;
    /* 0x1E */ short unk1E;
    
    /* 0x20 */ u_short red;
    /* 0x22 */ u_short green;
    /* 0x24 */ u_short blue;
    /* 0x26 */ short redDelta;
    /* 0x28 */ short greenDelta;
    /* 0x2A */ short blueDelta;
    /* 0x2C */ POLY_FT4 polys[2];
} Vertex;

typedef struct {
    /* 0x0 */ Vertex* pVertices;
    /* 0x4 */ short capacity;
    /* 0x6 */ short curIndex;
} VertexBuffer;

/* Unknown list */
typedef struct {
    /* 0x0 */ s8 unk0;
    /* 0x1 */ u8 unk1[0x3];
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6[0xE];
} Temp3; // Size: 0x14

typedef struct {
    /* 0x0 */ Temp3* pObjects;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 numObjects;
} Temp4;
/* -------------- */


typedef struct {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u32 unk4;
} Temp5; // Size: 0x8

typedef struct {
    /* 0x0 */ u8 unk0[0x6];
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8[0xC];
} Temp6; // Size: 0x14

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2[0x6];
    /* 0x8 */ u32 unk8;
    /* 0xC */ u8 unkC[0x64];
} UnkInner1; // Size: 0x70

typedef struct {
    /* 0x0   */ u8 unk0[0x4];
    /* 0x4   */ MenuScene* pScenes;
    /* 0x8   */ u8 unk8[0xB0];
    /* 0xB8  */ POLY_FT4 polys[2];
    /* 0x108 */ u8 unk108[0x4];
    /* 0x10C */ u8 unk10C;
    /* 0x10D */ u8 unk10D;
    /* 0x10E */ u8 unk10E;
    /* 0x10F */ u8 unk10F;
    /* 0x110 */ UnkInner1* unk110; // 0x70 sized array, unk10C entries
    /* 0x114 */ void* unk114; // 0x24 sized array, unk10D entries
    /* 0x118 */ void* unk118; // 0x30 sized array, unk10E entries
    /* 0x11C */ u8 unk11C[0x18];
} Unk; // Size: 0x134


extern Temp5 D_801E85F4[8];
extern Temp6 D_801E8648[2];
extern Unk* D_801E8670[10];

#endif