#ifndef _XENO_FIELD_PARTICLES_H
#define _XENO_FIELD_PARTICLES_H

#include "psyq/libgte.h"
#include "psyq/libgpu.h"

#define NUM_PARTICLE_BANKS 0x8
#define NUM_PARTICLES 0x40

#define PARTICLE_SORT_TOP 0x0
#define PARTICLE_SORT_MID 0x1
#define PARTICLE_SORT_NORMAL 0x2
#define PARTICLE_SORT_BACK 0x3

#define PARTICLE_RANGE_MODE_RANDOM 0x0
#define PARTICLE_RANGE_MODE_LINE 0x1
#define PARTICLE_RANGE_MODE_CIRCLE 0x2

#define PARTICLE_FLAG_RANDROT(flags) (flags & 0x1)
#define PARTICLE_FLAG_SORT(flags) (flags >> 1) & 3
#define PARTICLE_FLAG_TYPE(flags) (flags >> 4) & 3
#define PARTICLE_FLAG_RANGE_MODE(flags) (flags >> 6) & 3

// 0: 1.0*Bk + 1.0*Fw
// 1: 1.0*Bk - 1.0*Fw
// 2: 1.0*Bk + 0.25*Fw
// 3: 0.5*Bk + 0.5*Fw
#define PARTICLE_FLAG_COLOR_MODE(flags) (flags >> 8) & 3

typedef struct {
    /* 0x0  */ u16 x0;
    /* 0x2  */ u16 y0;
    /* 0x4  */ u16 x1;
    /* 0x6  */ u16 y1;
    /* 0x8  */ u16 u0;
    /* 0xA  */ u16 v0;
    /* 0xC  */ u16 u1;
    /* 0xE  */ u16 v1;
    /* 0x10 */ u16 u2;
    /* 0x12 */ u16 v2;
    /* 0x14 */ u16 u3;
    /* 0x16 */ u16 v3;
} ParticleShape; // Size: 0x18

typedef struct {
    /* 0x0 */ s8 r;
    /* 0x1 */ s8 g;
    /* 0x2 */ s8 b;
    /* 0x3 */ s8 a;
} ParticleColorDelta; // Size: 0x4

typedef struct {
    /* 0x0  */ s16 active;
    /* 0x2  */ u16 swait; // Delay before particle starts
    /* 0x4  */ u16 ewait; // Duration of particle
    /* 0x6  */ s16 zRotation;
    /* 0x8  */ VECTOR position;
    /* 0x18 */ VECTOR velocity;
    /* 0x28 */ VECTOR gravity;
    /* 0x38 */ SVECTOR scale;
    /* 0x40 */ SVECTOR scaleDelta;
    /* 0x48 */ CVECTOR color;
    /* 0x4C */ ParticleColorDelta colorDelta;
    /* 0x50 */ POLY_FT4 poly[2];
    /* 0xA0 */ SVECTOR vertices[4];
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
    /* 0x62  */ SVECTOR scaleDelta;
    /* 0x6A  */ CVECTOR color;
    /* 0x6E  */ ParticleColorDelta colorDelta;
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