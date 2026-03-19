#ifndef _XENO_FIELD_PARTICLES_H
#define _XENO_FIELD_PARTICLES_H

#include "psyq/libgte.h"

#define NUM_PARTICLE_BANKS 0x8
#define NUM_PARTICLES 0x40

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
} ParticleBankSub;

typedef struct {
    /* 0x0   */ u16 unk0;
    /* 0x2   */ u16 swait;
    /* 0x4   */ u16 ewait;
    /* 0x6   */ u16 max;
    /* 0x8   */ u32 speed;
    /* 0xC   */ SVECTOR pos;
    /* 0x14  */ SVECTOR epos;
    /* 0x1C  */ SVECTOR gravity;
    /* 0x24  */ s16 speedMultiplier;
    /* 0x26  */ u16 srange;
    /* 0x28  */ u16 erange;
    /* 0x2A  */ u16 flags;
    /* 0x2C  */ u8 unk2C[4];
    /* 0x30  */ ParticleBankSub unk30[8];
    /* 0x50  */ u16 unk50;
    /* 0x52  */ u16 targetActorID;
    /* 0x54  */ s16 shape;
    /* 0x56  */ u16 pswait;
    /* 0x58  */ u16 pewait;
    /* 0x5A  */ SVECTOR scale;
    /* 0x62  */ SVECTOR scaleOffset;
    /* 0x6A  */ u8 colorRed;
    /* 0x6B  */ u8 colorGreen;
    /* 0x6C  */ u8 colorBlue;
    /* 0x6D  */ u8 unk6D;
    /* 0x6E  */ s8 colOfsRed;
    /* 0x6F  */ s8 colOfsGreen;
    /* 0x70  */ s8 colOfsBlue;
    /* 0x71  */ s8 unk71;
    /* 0x72  */ u8 unk72[4];
    /* 0x76  */ s16 rotAngle;
} ParticleBank; // Size: 0x78

extern int g_FieldParticleBankIndex;
extern ParticleBank g_FieldDefaultParticleBanks[NUM_PARTICLE_BANKS];

extern s16 g_FieldParticleActorIDs[NUM_PARTICLES];
extern u8 g_FieldParticleStatuses[NUM_PARTICLES];
extern ParticleBank g_FieldParticleBanks[NUM_PARTICLES];

#endif