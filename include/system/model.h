#ifndef _XENO_3D_MODEL_H
#define _XENO_3D_MODEL_H

#include "psyq/libgpu.h"
#include "psyq/libgte.h"

// Model part flags
#define MODEL_FLAG_HAS_LIGHT_DATA 0x1


typedef struct {
    u32 unk0;
    u32 lightDataSize;
    u32 modelPacketSize;
} ModelPacketInfo; // Size: 0xC

typedef struct {
    /* 0x0  */ u_short flags;
    /* 0x2  */ u8 unk2[0x2];
    /* 0x4  */ u_short polyCount;
    /* 0x6  */ u16 unk6;
    /* 0x8  */ SVECTOR* pVertices;
    /* 0xC  */ u32 unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ CVECTOR* pColors;
    /* 0x18 */ void* pLightData;
    /* 0x1C */ u32* unk1C;
    /* 0x20 */ ModelPacketInfo unk20[2];
} ModelPart; // Size: 0x38

typedef struct {
    /* 0x0  */ int numModelParts;
    /* 0x4  */ u_int flags;
    /* 0x8  */ u8 unk8[0x8];
    /* 0x10 */ ModelPart modelParts[0]; // numModelParts sized
} ModelFileHeader; // Size: 0x10


#endif