#ifndef _XENO_FIELD_PARTICLES_H
#define _XENO_FIELD_PARTICLES_H

#include "psyq/libgte.h"
#include "psyq/libgpu.h"

#define NUM_PARTICLE_BANKS 0x8
#define NUM_PARTICLES 0x40

#define PARTICLE_FLAG_1(flags) (flags >> 1) & 3
#define PARTICLE_FLAG_TYPE(flags) (flags >> 4) & 3

typedef struct {
    /* 0x0 */ s8 r;
    /* 0x1 */ s8 g;
    /* 0x2 */ s8 b;
    /* 0x3 */ s8 a;
} ParticleColorDelta; // Size: 0x4

typedef struct {
    /* 0x0  */ s16 unk0;
    /* 0x2  */ u16 swait;
    /* 0x4  */ u16 ewait;
    /* 0x6  */ s16 unk6;
    /* 0x8  */ VECTOR unk8;
    /* 0x18 */ VECTOR unk18;
    /* 0x28 */ VECTOR gravity;
    /* 0x38 */ SVECTOR scale;
    /* 0x40 */ SVECTOR scaleOffset;
    /* 0x48 */ CVECTOR color;
    /* 0x4C */ ParticleColorDelta colorOfs;
    /* 0x50 */ POLY_FT4 poly[2];
    /* 0xA0 */ short unkA0;
    /* 0xA2 */ short unkA2;
    /* 0xA4 */ u16 unkA4;
    /* 0xA6 */ u8 unkA6[2];
    /* 0xA8 */ short unkA8;
    /* 0xAA */ short unkAA;
    /* 0xAC */ u16 unkAC;
    /* 0xAE */ u8 unkAE[2];
    /* 0xB0 */ short unkB0;
    /* 0xB2 */ short unkB2;
    /* 0xB4 */ u16 unkB4;
    /* 0xB6 */ u8 unkB6[2];
    /* 0xB8 */ short unkB8;
    /* 0xBA */ short unkBA;
    /* 0xBC */ u16 unkBC;
    /* 0xBE */ u8 unkBE[2];
} ParticlePrimitive; // Size: 0xC0

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 z;
} ParticleBankDirectionData;

typedef struct {
    /* 0x0   */ u16 unk0;
    /* 0x2   */ u16 swait;
    /* 0x4   */ u16 ewait;
    /* 0x6   */ s16 max;
    /* 0x8   */ s32 speed;
    /* 0xC   */ SVECTOR pos;
    /* 0x14  */ SVECTOR epos;
    /* 0x1C  */ SVECTOR gravity;
    /* 0x24  */ s16 speedMultiplier;
    /* 0x26  */ u16 srange;
    /* 0x28  */ u16 erange;
    /* 0x2A  */ u16 flags;
    /* 0x2C  */ ParticlePrimitive* pPrimitives;
    /* 0x30  */ ParticleBankDirectionData directions[8];
    /* 0x50  */ s16 unk50;
    /* 0x52  */ s16 targetActorID;
    /* 0x54  */ s16 shape;
    /* 0x56  */ u16 pswait;
    /* 0x58  */ u16 pewait;
    /* 0x5A  */ SVECTOR scale;
    /* 0x62  */ SVECTOR scaleOffset;
    /* 0x6A  */ CVECTOR color;
    /* 0x6E  */ ParticleColorDelta colorOfs;
    /* 0x72  */ s16 unk72;
    /* 0x74  */ s16 unk74;
    /* 0x76  */ s16 rotAngle;
} ParticleBank; // Size: 0x78

typedef struct { 
    ParticleBank banks[8]; 
} ParticleBanks;

extern int g_FieldParticleCurActor;

extern int g_FieldParticleBankIndex;
extern ParticleBank g_FieldDefaultParticleBanks[NUM_PARTICLE_BANKS];

extern short g_FieldParticleActorIDs[NUM_PARTICLES];
extern u8 g_FieldParticleStatuses[NUM_PARTICLES];
extern ParticleBank* g_FieldParticleBanks[NUM_PARTICLES];

#endif