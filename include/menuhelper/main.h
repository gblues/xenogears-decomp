#ifndef __MENUHELPER_MAIN_H__
#define __MENUHELPER_MAIN_H__

#include "psyq/libgpu.h"
#include "psyq/libgte.h"
#include "system/model.h"


struct _ModelJoint;
typedef struct _ModelJoint ModelJoint;
struct _ModelJoint {
    /* 0x00 */ ModelJoint* pParent;
    /* 0x04 */ u_char doTransform;
    /* 0x05 */ u_char doRotate;
    /* 0x06 */ u_char rotDirection;
    /* 0x07 */ u_char unk7;
    /* 0x08 */ u_short jointIndex;
    /* 0x0A */ u_short length;
    /* 0x0c */ MATRIX matrix1;
    /* 0x2c */ MATRIX matrix2;
    /* 0x4c */ SVECTOR vec1;
    /* 0x54 */ SVECTOR vec2;
    /* 0x5c */ long unk5C[3];
    /* 0x68 */ void* pModelPacketBuffer;
    /* 0x6c */ void* pCurModelPacket;
    /* 0x70 */ u32 unk70;
    /* 0x74 */ u32 unk74;
    /* 0x78 */ u32 unk78;
}; // Size: 0x7C

// Joint entry
typedef struct {
    /* 0x0 */ u_short jointIndex;
    /* 0x2 */ u_short parentIndex;
} ModelJointEntry; // Size: 0x4

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
    /* 0x0 */ ModelPart** pParts;
    /* 0x4 */ u_int numParts;
} ModelMesh; // Size: 0x8



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
    /* 0x0   */ ModelMesh* pMesh;
    /* 0x4   */ ModelJoint* pSkeleton; // Array of joints
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
} Model; // Size: 0x134

#define MAX_MODEL_MESHES 8
#define MAX_MODELS 10

extern ModelMesh g_MenuHelperMeshes[MAX_MODEL_MESHES];
extern Temp6 D_801E8648[2];
extern Model* g_MenuHelperModels[MAX_MODELS];

#endif