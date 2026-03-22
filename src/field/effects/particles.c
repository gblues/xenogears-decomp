#include "common.h"
#include "system/memory.h"
#include "field/particles.h"

extern s32 D_800ADB34;
extern MATRIX g_CameraMatrix;
extern s32 g_FieldSystemMode;
extern u8 D_8006FDC8[]; // "PARTICLE  "


void FieldInitializeParticles(void) {
    int i;

    for (i = 0; i < NUM_PARTICLES; i++) {
        g_FieldParticleStatuses[i] = 0;
        g_FieldParticleActorIDs[i] = -1;
    }
}

void FieldParticlesFree(int index) {
    int i;
    ParticleBank* pCurBank;

    if (g_FieldParticleStatuses[index] == 1) {
        for (i = 0, pCurBank = g_FieldParticleBanks[index]; i < NUM_PARTICLE_BANKS; i++, pCurBank++) {
            if (pCurBank->max != 0) {
                HeapFree(pCurBank->pPrimitives);
            }            
        }
        HeapFree(g_FieldParticleBanks[index]);
    }
    
    g_FieldParticleStatuses[index] = 0;
    g_FieldParticleActorIDs[index] = -1;
}

void FieldParticleResetEWait(int index) {
    int i;
    ParticleBank* pCurBank;

    if (g_FieldParticleStatuses[index] != 1) {
        return;
    }

    for (i = 0, pCurBank = g_FieldParticleBanks[index]; i < NUM_PARTICLE_BANKS; i++, pCurBank++) {
        if (pCurBank->max != 0) {
            pCurBank->ewait = 0;
        }
    }
}

void func_800A93CC(int index) {
    int i, j;
    ParticleBank* pCurBank;

    if (g_FieldParticleStatuses[index] != 1) {
        return;
    }

    pCurBank = g_FieldParticleBanks[index];
    for (i = 0; i < NUM_PARTICLE_BANKS; i++, pCurBank++) {
        if (pCurBank->max == 0) 
            continue;
        
        pCurBank->ewait = 0;
        for (j = 0; j < pCurBank->max; j++) {
            ParticlePrimitive* pPrim = &pCurBank->pPrimitives[j];
            pPrim->ewait = 1;
        }
    }
}

void FieldParticlesFreeAll(void) {
    int i;
    
    for (i = 0; i < NUM_PARTICLES; i++) {
        FieldParticlesFree(i);
    }
    FieldRenderSync();
}

static inline SetVector(SVECTOR* pVec, short value) {
    pVec->vx = value;
    pVec->vy = value;
    pVec->vz = value;
}

void FieldInitializeDefaultParticleBanks(short targetActorID) {
    int i;
    int j;
    SVECTOR* pVec;

    g_FieldParticleBankIndex = 0;

    for (i = 0; i < NUM_PARTICLE_BANKS; i++) {
        g_FieldDefaultParticleBanks[i].targetActorID = targetActorID;
        g_FieldDefaultParticleBanks[i].unk0 = 0x0;
        g_FieldDefaultParticleBanks[i].swait = 0x0;
        g_FieldDefaultParticleBanks[i].ewait = 0x80;
        g_FieldDefaultParticleBanks[i].max = 0x0;
        SetVector(&g_FieldDefaultParticleBanks[i].pos, 0x0);
        pVec = &g_FieldDefaultParticleBanks[i].epos;
        pVec->vy = -1000;
        pVec->vx = 0;
        pVec->vz = 0;
        g_FieldDefaultParticleBanks[i].speed = 0x8000;
        g_FieldDefaultParticleBanks[i].unk50 = 0x800;
        g_FieldDefaultParticleBanks[i].speedMultiplier = 0x1;
        SetVector(&g_FieldDefaultParticleBanks[i].gravity, 0x0);
        g_FieldDefaultParticleBanks[i].erange = 0x100;
        g_FieldDefaultParticleBanks[i].pewait = 0x1C;
        g_FieldDefaultParticleBanks[i].srange = 0x0;   
        g_FieldDefaultParticleBanks[i].flags = 0x0;
        g_FieldDefaultParticleBanks[i].rotAngle = 0x0;
        g_FieldDefaultParticleBanks[i].pswait = 0x1;
        g_FieldDefaultParticleBanks[i].shape = 0x0;
        SetVector(&g_FieldDefaultParticleBanks[i].scale, 456);
        SetVector(&g_FieldDefaultParticleBanks[i].scaleOffset, 0x20);
        g_FieldDefaultParticleBanks[i].color.r = 128;
        g_FieldDefaultParticleBanks[i].color.g = 32;
        g_FieldDefaultParticleBanks[i].color.b = 0;
        g_FieldDefaultParticleBanks[i].colorOfs.r = -4;
        g_FieldDefaultParticleBanks[i].colorOfs.g = -1;
        g_FieldDefaultParticleBanks[i].colorOfs.b = 0;

        for (j = 0; j < 8; j++) {
            g_FieldDefaultParticleBanks[i].directions[j].x = 0x0;
            g_FieldDefaultParticleBanks[i].directions[j].z = 0x0;
        } 
    }
}

void func_800A9688(void) {
    MATRIX cameraMat;
    int timer;
    int maxElements;
    int bInUse;
    int primIndex;
    ParticleBank* pCurBank;
    int i, j;

    if (D_800ADB34 == 0) {
        cameraMat = g_CameraMatrix;

        for (i = 0; i < NUM_PARTICLES; i++) {
            bInUse = 0;
            if (g_FieldParticleStatuses[i] == 1) {
                for (j = 0, pCurBank = g_FieldParticleBanks[i]; j < NUM_PARTICLE_BANKS; pCurBank++, j++) {
                    timer = 0;
                    if (pCurBank->max == 0)
                        continue;
                    
                    if (pCurBank->swait == 0) {
                        for (primIndex = 0; primIndex < pCurBank->max; primIndex++) {
                            if (pCurBank->pPrimitives[primIndex].unk0 == 0) {
                                if (pCurBank->ewait != 0) {
                                    func_800AA6B4(pCurBank, &pCurBank->pPrimitives[primIndex], &timer);
                                    func_800A9F18(pCurBank, &pCurBank->pPrimitives[primIndex], &cameraMat);
                                    bInUse = 1;
                                }
                            } else {
                                func_800A9F18(pCurBank, &pCurBank->pPrimitives[primIndex], &cameraMat);
                                bInUse = 1;
                            }
                        }
                            
                        if (pCurBank->ewait) {
                            if (pCurBank->ewait != 0x7FFF) {
                                 pCurBank->ewait--;
                            }
                            bInUse = 1;
                        }
                    } else {
                        bInUse = 1;
                        pCurBank->swait--;
                    }
                }
                
                if (bInUse == 0) {
                    FieldParticlesFree(i);
                }
            }
        }
        
        if (g_FieldSystemMode == 0) {
            func_80281B00(&D_8006FDC8);
        }
    }
}

int FieldParticlesRandRange(int range) {
    return ((rand() * range) + 1) >> 15;
}

int FieldParticlesFindFreeIndex(void) {
    int i;

    for (i = 0; i < NUM_PARTICLES; i++) {
        if (g_FieldParticleStatuses[i] == 0) {
            return i;
        }
    }
    return -1;
}

// Mode 0x0 => Turn of particle effect?
// Mode 0x1 => Turn on particle effect?
void func_800A98E8(int actorIndex, int mode) {
    int i;
    
    for (i = 0; i < NUM_PARTICLES; i++) {
        if (g_FieldParticleActorIDs[i] == actorIndex) {
            if (mode == 0) {
                g_FieldParticleBanks[i]->ewait = 0;
                g_FieldParticleBanks[i]->swait = 0;
                FieldParticleResetEWait(i);
            } else {
                g_FieldParticleBanks[i]->ewait = 0;
                g_FieldParticleBanks[i]->swait = 0;
                func_800A93CC(i);
            }
        }      
    }
}

int FieldInitializeParticleBanks(int actorIndex) {
    int i, j;
    ParticleBank* pCurrent;
    ParticleBank* pBanks;

    i = FieldParticlesFindFreeIndex();
    if (i == -1) {
        return -1;
    }
    
    HeapChangeCurrentUser(HEAP_USER_YOSI, 0);
    g_FieldParticleCurActor = actorIndex;
    g_FieldParticleStatuses[i] = 1;
    g_FieldParticleActorIDs[i] = actorIndex;
    pBanks = HeapAlloc(sizeof(ParticleBank) * NUM_PARTICLE_BANKS, 0);
    g_FieldParticleBanks[i] = pBanks;

    // Cast to a ParticleBanks struct wrapping an array of ParticleBank objects
    // in order to match the original code.
    *(ParticleBanks*)pBanks = *(ParticleBanks*)g_FieldDefaultParticleBanks;
    
    for (i = 0, pCurrent = &pBanks[i]; i < NUM_PARTICLE_BANKS; i++, pCurrent++) {
        if (pCurrent->max == 0)
            continue;
        
        pCurrent->pPrimitives = HeapAlloc(pCurrent->max * sizeof(ParticlePrimitive), 0);
        for (j = 0; j < pCurrent->max; j++) {
            pCurrent->pPrimitives[j].unk0 = 0;
            func_800A8EAC(
                &pCurrent->pPrimitives[j], 
                pCurrent->shape, 
                (((pCurrent->flags << 0x10) >> 0x18) + 1) & 3
            );
        }
    }
    
    return 1;
}