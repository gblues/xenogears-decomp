#ifndef _XENO_FIELD_PARTICLES_H
#define _XENO_FIELD_PARTICLES_H

#include "psyq/libgte.h"

#define NUM_PARTICLE_BANKS 0x8
#define NUM_PARTICLES 0x40

typedef struct {
    /* 0x0  */ u16 unk0;
    /* 0x2  */ u16 unk2;
    /* 0x4  */ s16 unk4;
    /* 0x6  */ u8 unk6[0x4A];
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
} Unk; // Size: 0xC0

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
} ParticleBankSub;

typedef struct {
    /* 0x0   */ u16 unk0;
    /* 0x2   */ u16 swait;
    /* 0x4   */ s16 ewait;
    /* 0x6   */ s16 max;
    /* 0x8   */ u32 speed;
    /* 0xC   */ SVECTOR pos;
    /* 0x14  */ SVECTOR epos;
    /* 0x1C  */ SVECTOR gravity;
    /* 0x24  */ s16 speedMultiplier;
    /* 0x26  */ u16 srange;
    /* 0x28  */ u16 erange;
    /* 0x2A  */ u16 flags;
    /* 0x2C  */ Unk* unk2C;
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

extern short g_FieldParticleActorIDs[NUM_PARTICLES];
extern u8 g_FieldParticleStatuses[NUM_PARTICLES];
extern ParticleBank* g_FieldParticleBanks[NUM_PARTICLES];

#endif