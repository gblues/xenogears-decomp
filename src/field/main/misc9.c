#include "common.h"
#include "field/main.h"
#include "field/actor.h"
#include "system/memory.h"
#include "psyq/libgpu.h"
#include "field/effects.h"
#include "field/graphics.h"
#include "field/particles.h"


extern u8 D_800AF474[8];
extern s16 D_800AF98E;
extern s32 D_800B00B4;

int FieldParticleUpdateColor(int color, int delta) {
    int newColor;

    if (delta < 0) {
        newColor = color + delta;
        if (newColor < 0) {
            newColor = 0;
        }
    } else {
        newColor = color + delta;
        if (newColor >= 256) {
            newColor = 255;
        }
    }
    
    return newColor;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800A9B54);

// Particle Updating
void func_800A9F18(ParticleBank* pParticleBank, ParticlePrimitive* pPrim, MATRIX* pMatrix) {
    VECTOR sp18;
    SVECTOR rotationVec;
    MATRIX matrix;
    MATRIX transformMatrix;
    VECTOR sp70;
    VECTOR sp80;
    VECTOR sp90;
    VECTOR spA0;
    long flag;
    FieldActor* pFieldActors;
    int var_s5;

    if (pPrim->swait != 0) {
        pPrim->swait--;
        if (pPrim->swait != 0) {
            return;
        }
        
        matrix.t[2] = 0;
        matrix.t[1] = 0;
        matrix.t[0] = 0;
        
        var_s5 = 0;
        switch (PARTICLE_FLAG_TYPE(pParticleBank->flags)) {
            case 3:
                rotationVec.vx = 0;
                rotationVec.vy = g_FieldActors[pParticleBank->targetActorID].pActorData->rotationZ;
                rotationVec.vz = 0;
                RotMatrix(&rotationVec, &matrix);
                pFieldActors = g_FieldActors;
                sp70.vx = pFieldActors[pParticleBank->targetActorID].pActorData->position.vx >> 0x10;
                sp70.vy = pFieldActors[pParticleBank->targetActorID].pActorData->position.vy >> 0x10;
                sp70.vz = pFieldActors[pParticleBank->targetActorID].pActorData->position.vz >> 0x10;
                pParticleBank->unk50 = pFieldActors[pParticleBank->targetActorID].pActorData->scaleX;
                var_s5 = 1;
                break;
            case 0:
                rotationVec.vx = 0;
                rotationVec.vy = g_FieldActors[pParticleBank->targetActorID].pActorData->rotationZ;
                rotationVec.vz = 0;
                RotMatrix(&rotationVec, &matrix);
                pFieldActors = g_FieldActors;
                sp70.vx = pFieldActors[pParticleBank->targetActorID].pActorData->position.vx >> 0x10;
                sp70.vy = pFieldActors[pParticleBank->targetActorID].pActorData->position.vy >> 0x10;
                sp70.vz = pFieldActors[pParticleBank->targetActorID].pActorData->position.vz >> 0x10;
                pParticleBank->unk50 = 0x1000;
                break;
            case 1:
                func_801E72CC(&matrix, &transformMatrix, pParticleBank->unk72, pParticleBank->unk74);
                SetRotMatrix(&matrix);
                SetTransMatrix(&matrix);
                rotationVec.vx = pParticleBank->pos.vx;
                rotationVec.vy = pParticleBank->pos.vy;
                rotationVec.vz = pParticleBank->pos.vz;
                RotTrans(&rotationVec, &sp70, &flag);
                pParticleBank->unk50 = 0x1000;
                break;
            case 2:
                matrix = g_FieldActors[pParticleBank->targetActorID].childMatrix;
                SetRotMatrix(&matrix);
                SetTransMatrix(&matrix);
                rotationVec.vx = pParticleBank->pos.vx;
                rotationVec.vy = pParticleBank->pos.vy;
                rotationVec.vz = pParticleBank->pos.vz;
                RotTrans(&rotationVec, &sp70, &flag);
                pParticleBank->unk50 = 0x1000;
                break;
        }
        
        matrix.t[2] = 0;
        matrix.t[1] = 0;
        matrix.t[0] = 0;
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        rotationVec.vx = pPrim->unk18.vx;
        rotationVec.vy = pPrim->unk18.vy;
        rotationVec.vz = pPrim->unk18.vz;
        ApplyRotMatrix(&rotationVec, &sp18);
        func_80048D7C(&sp18, &pPrim->unk18);
        pPrim->unk18.vx = ((pPrim->unk18.vx * pParticleBank->speed) >> 0xC) * pParticleBank->speedMultiplier;
        pPrim->unk18.vy = ((pPrim->unk18.vy * pParticleBank->speed) >> 0xC) * pParticleBank->speedMultiplier;
        pPrim->unk18.vz = ((pPrim->unk18.vz * pParticleBank->speed) >> 0xC) * pParticleBank->speedMultiplier;
        
        if (var_s5 == 1) {
            pPrim->unk8.vx = (pPrim->unk8.vx * pParticleBank->unk50) >> 0xC;
            pPrim->unk8.vy = (pPrim->unk8.vy * pParticleBank->unk50) >> 0xC;
            pPrim->unk8.vz = (pPrim->unk8.vz * pParticleBank->unk50) >> 0xC;
        }
        
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        rotationVec.vx = pPrim->unk8.vx;
        rotationVec.vy = pPrim->unk8.vy;
        rotationVec.vz = pPrim->unk8.vz;
        RotTrans(&rotationVec, &sp18, &flag);
        
        if (var_s5 == 1) {
            rotationVec.vx = D_800B00B4 - 0x400;
            rotationVec.vy = -D_800AF98E;
            rotationVec.vz = 0;
            RotMatrixZYX(&rotationVec, &transformMatrix);
            SetRotMatrix(&transformMatrix);
            SetTransMatrix(&transformMatrix);
            sp80.vx = 0;
            sp80.vy = sp18.vy;
            sp80.vz = 0;
            ApplyRotMatrixLV(&sp80, &sp90);
            sp18.vx += sp90.vx;
            sp18.vz += sp90.vz;
            sp18.vy = sp90.vy;
            pPrim->unk8.vx = (sp70.vx + sp18.vx) * (0x1000000 / pParticleBank->unk50);
            pPrim->unk8.vy = (sp70.vy + sp18.vy) * (0x1000000 / pParticleBank->unk50);
            pPrim->unk8.vz = (sp70.vz + sp18.vz) * (0x1000000 / pParticleBank->unk50);
            return;
        }
        
        pPrim->unk8.vx = ((sp70.vx + sp18.vx) << 0xC);
        pPrim->unk8.vy = ((sp70.vy + sp18.vy) << 0xC);
        pPrim->unk8.vz = ((sp70.vz + sp18.vz) << 0xC);    
        return;
    } 
    
    pPrim->unk18.vx += pPrim->gravity.vx;
    pPrim->unk18.vy += pPrim->gravity.vy;
    pPrim->unk18.vz += pPrim->gravity.vz;
    pPrim->unk8.vx += pPrim->unk18.vx;
    pPrim->unk8.vy += pPrim->unk18.vy;
    pPrim->unk8.vz += pPrim->unk18.vz;
    pPrim->scale.vx += pPrim->scaleOffset.vx;
    pPrim->scale.vy += pPrim->scaleOffset.vy;
    pPrim->scale.vz += pPrim->scaleOffset.vz;
    pPrim->color.r = FieldParticleUpdateColor(pPrim->color.r, pPrim->colorOfs.r);
    pPrim->color.g = FieldParticleUpdateColor(pPrim->color.g, pPrim->colorOfs.g);
    pPrim->color.b = FieldParticleUpdateColor(pPrim->color.b, pPrim->colorOfs.b);
    
    spA0.vx = pParticleBank->unk50;
    spA0.vy = pParticleBank->unk50;
    spA0.vz = pParticleBank->unk50;
    if (pPrim->ewait != 1) {
        func_800A9B54(pPrim, pMatrix, pPrim->unk6, 
            PARTICLE_FLAG_1(pParticleBank->flags), 
            &spA0, 
            PARTICLE_FLAG_TYPE(pParticleBank->flags)
        );
    }
    
    pPrim->ewait--;
    if (pPrim->ewait == 0) {
        pPrim->unk0 = 0;
    }
}

void func_800AA6B4(ParticleBank* pParticleBank, ParticlePrimitive* pPrim, int* pTimer) {
    VECTOR _unused;
    VECTOR sp20;
    VECTOR sp30;
    int angle;
    int factor;
    u16 rotAngle;
    int direction;
    u_int rotation;

    pPrim->unk0 = 1;
    pPrim->swait = pParticleBank->pswait + *pTimer;
    *pTimer += pParticleBank->pswait;
    pPrim->ewait = pParticleBank->pewait;
    
    if (pParticleBank->flags & 1) {
        rotAngle = rand() & 0xFFF;
    } else {
        rotAngle = pParticleBank->rotAngle;
    }
    pPrim->unk6 = rotAngle;
    
    if (!(pParticleBank->flags & 0x80)) {
        factor = FieldParticlesRandRange(pParticleBank->srange);
    } else {
        factor = pParticleBank->srange;
    }
    
    angle = FieldParticlesRandRange(0xFFF);
    sp20.vx = (rsin(angle) * factor) >> 0xC;
    if (!(pParticleBank->flags & 0x40)) {
        sp20.vz = (rcos(angle) * factor) >> 0xC;
    } else {
        sp20.vz = 0;
    }

    rotation = D_800AF98E + g_FieldActors[pParticleBank->targetActorID].pActorData->rotationZ & 0xFFF;
    direction = D_800AF474[rotation >> 9];
    
    sp20.vx += pParticleBank->pos.vx + pParticleBank->directions[direction].x;
    sp20.vz += pParticleBank->pos.vz + pParticleBank->directions[direction].z;
    sp20.vy = pParticleBank->pos.vy;
    pPrim->unk8.vx = sp20.vx;
    pPrim->unk8.vz = sp20.vz;
    pPrim->unk8.vy = sp20.vy;
    
    factor = FieldParticlesRandRange(pParticleBank->erange);
    sp30.vx = pParticleBank->epos.vx + ((rsin(angle) * factor) >> 0xC);
    sp30.vz = pParticleBank->epos.vz + ((rcos(angle) * factor) >> 0xC);
    sp30.vy = pParticleBank->epos.vy;
    
    pPrim->unk18.vx = (sp30.vx - sp20.vx);
    pPrim->unk18.vy = (sp30.vy - sp20.vy);
    pPrim->unk18.vz = (sp30.vz - sp20.vz);
    
    pPrim->gravity.vx = pParticleBank->gravity.vx;
    pPrim->gravity.vy = pParticleBank->gravity.vy;
    pPrim->gravity.vz = pParticleBank->gravity.vz;
    pPrim->scale.vx = pParticleBank->scale.vx;
    pPrim->scale.vy = pParticleBank->scale.vy;
    pPrim->scale.vz = pParticleBank->scale.vz;
    pPrim->scaleOffset.vx = pParticleBank->scaleOffset.vx;
    pPrim->scaleOffset.vy = pParticleBank->scaleOffset.vy;
    pPrim->scaleOffset.vz = pParticleBank->scaleOffset.vz;
    pPrim->color.r = pParticleBank->color.r;
    pPrim->color.g = pParticleBank->color.g;
    pPrim->color.b = pParticleBank->color.b;
    pPrim->colorOfs.r = pParticleBank->colorOfs.r;
    pPrim->colorOfs.g = pParticleBank->colorOfs.g;
    pPrim->colorOfs.b = pParticleBank->colorOfs.b;
}
// ------------------------------------

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AA9DC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AAA74);

extern SpriteList* D_800AFC68;

void func_800AABD8(void) {
    HeapFree(D_800AFC68);
    DrawSync(0);
}

void func_800AAC08(void) {
    RECT rect;
    SPRT* pSprite;
    SPRT* pSprite2;
    int i;

    D_800AFC68 = HeapAlloc(0x840, 0x0);
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 0xFF;
    rect.h = 0xFF;
    
    for (i = 0; i < 0x21; i++) {
        SetDrawMode(&D_800AFC68->drModes[i][0], 0, 0, GetTPage(0, 0, 0x3C0, 0x100) & 0xFFFF, &rect);
        SetDrawMode(&D_800AFC68->drModes[i][1], 0, 0, GetTPage(0, 0, 0x3C0, 0x140) & 0xFFFF, &rect);
        pSprite = &D_800AFC68->sprites[i][0];
        pSprite2 = &D_800AFC68->sprites[i][1];
        
        SetSprt(pSprite);
        setRGB0(pSprite, 0x80, 0x80, 0x80);
        if (i == 0) {
            setUV0(pSprite, 0xE0, 0x70);
            setWH(pSprite, 0x10, 0x10);
        } else {
            setUV0(pSprite, 0xE0, 0x60);
            setWH(pSprite, 8, 8);
        }
        setXY0(pSprite, 0xA0, 0x70);
        pSprite->clut = GetClut(0x100, 0xF7);
        *pSprite2 = *pSprite;
    };
}

// Set RGB of sprites
void func_800AADC8(int index, int red, int green, int blue) {
    setRGB0(&D_800AFC68->sprites[index][0], red, green, blue);
    setRGB0(&D_800AFC68->sprites[index][1], red, green, blue);
}

void func_800AAE4C(int index, int x, int y, int type) {
    switch (type) {
        case 0:
            y -= 0xC;
            x -= 4;
            break;
        case 1:
            y -= 4;
            x -= 4;
            break;
    }

    D_800AFC68->sprites[index][g_FieldCurRenderContextIndex].x0 = x;
    D_800AFC68->sprites[index][g_FieldCurRenderContextIndex].y0 = y;
    addPrim(g_FieldCurRenderContext->ot3, &D_800AFC68->sprites[index][g_FieldCurRenderContextIndex]);
    addPrim(g_FieldCurRenderContext->ot3, &D_800AFC68->drModes[index][g_FieldCurRenderContextIndex]);
}

extern SpriteList2* D_800B1DF0;
extern PolyList2* D_800C3A3C;

void func_800AAF80(void) {
    RECT rect;
    POLY_FT4* pPoly;
    POLY_FT4* pPoly2;
    SPRT* pSprite;
    SPRT* pSprite2;
    int i;

    D_800C3A3C = HeapAlloc(0x2F8, 0x0);
    D_800B1DF0 = HeapAlloc(0x400, 0x0);
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 0xFF;
    rect.h = 0xFF;
    
    for (i = 0; i < 4; i++) {
        SetDrawMode(&D_800B1DF0->drModes[i][0], 0, 0, GetTPage(0, 0, 0x3C0, 0x140), &rect);
        SetDrawMode(&D_800B1DF0->drModes[i][1], 0, 0, GetTPage(0, 0, 0x3C0, 0x140), &rect);
        pSprite = &D_800B1DF0->sprites[i][0];
        pSprite2 = pSprite + 1;
        SetSprt(pSprite);
        setRGB0(pSprite, 0x80, 0x80, 0x80);
        setXY0(pSprite, 0xA0, 0x70);
        if (i == 0) {
            setUV0(pSprite, 0xE0, 0x70);
            setWH(pSprite, 0x10, 0x10);
        } else {
            setUV0(pSprite, 0xE0, 0x60);
            setWH(pSprite, 0x8, 0x8);
        }
        pSprite->clut = GetClut(0x100, 0xF7);
        *pSprite2 = *pSprite;
    }

    for (i = 0; i < 3; i++) {
        pPoly = &D_800C3A3C->polys[i][0];
        pPoly2 = pPoly + 1;
        SetPolyFT4(pPoly);
        setXY4(pPoly, 
           i * 0x80, 0x0, 
           i * 0x80 + 0x80, 0x0, 
           i * 0x80, 0xDF, 
           i * 0x80 + 0x80, 0xDF
        );
        setRECT(&D_800C3A3C->rects[i][0], 0x0, 0x0, 0xFF, 0xFF);
        setRECT(&D_800C3A3C->rects[i][1], 0x0, 0x0, 0xFF, 0xFF);
        SetDrawMode(&D_800C3A3C->drModes[i][0], 0, 0, GetTPage(1, 0, 0x300 + (i * 0x40), 0x100), &D_800C3A3C->rects[i][0]);
        SetDrawMode(&D_800C3A3C->drModes[i][1], 0, 0, GetTPage(1, 0, 0x300 + (i * 0x40), 0x100), &D_800C3A3C->rects[i][1]);
        setRGB0(pPoly, 0x80, 0x80, 0x80);
        SetSemiTrans(pPoly, 0x1);
        setUV4(pPoly, 0x0, 0x0, 0x80, 0x0, 0x0, 0xDF, 0x80, 0xDF);
        pPoly->tpage = GetTPage(1, 0, 0x300 + (i * 0x40), 0x100);
        pPoly->clut = GetClut(0, 0xF6);
        *pPoly2 = *pPoly;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AB328);

extern SpriteList2* D_800B1DF0;
extern PolyList2* D_800C3A3C;

extern s32 D_800AFE78;
extern s32 D_800AFE7C;
extern s32 g_PlayerActorIndex;
extern s32 D_800C3914;
extern s32 D_800C3A18;

void func_800AB378(s8 color) {
    ActorData* pActor;
    int i;
    int y;
    int x;
    
    pActor = g_FieldActors[g_PlayerActorIndex].pActorData;
    x = (pActor->position.vx >> 0x10) * D_800C3914 >> 0x10;
    y = -((pActor->position.vz >> 0x10) * D_800C3A18) >> 0x10;
    
    for (i = 0; i < 1; i++) {
        if (i == 0) {
            y -= 0xC;
            x -= 4;
        }
        
        D_800B1DF0->sprites[i][g_FieldCurRenderContextIndex].x0 = x + D_800AFE78;
        D_800B1DF0->sprites[i][g_FieldCurRenderContextIndex].y0 = y + D_800AFE7C;
        
        setRGB0(&D_800B1DF0->sprites[i][g_FieldCurRenderContextIndex & 1], color, color, color);
        addPrim(g_FieldCurRenderContext->ot3, &D_800B1DF0->sprites[i][g_FieldCurRenderContextIndex]);
        addPrim(g_FieldCurRenderContext->ot3, &D_800B1DF0->drModes[i][g_FieldCurRenderContextIndex]);
    }

    for (i = 0; i < 3; i++) {
        setRGB0(&D_800C3A3C->polys[i][g_FieldCurRenderContextIndex & 1], color, color, color);
        addPrim(g_FieldCurRenderContext->ot3, &D_800C3A3C->polys[i][g_FieldCurRenderContextIndex]);
        addPrim(g_FieldCurRenderContext->ot3, &D_800C3A3C->drModes[i][g_FieldCurRenderContextIndex]);
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AB748);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AB808);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ABA98);


extern SpriteList3 D_800B0188;

void func_800ABD18(void) {
    int i;
    RECT rect;
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 0xFF;
    rect.h = 0xFF;
    
    for (i = 0; i < 5; i++) {
        SetDrawMode(&D_800B0188.drModes[i][0], 0, 0, GetTPage(1, 0, 0x280 + (i * 0x40), 0), &rect);
        SetDrawMode(&D_800B0188.drModes[i][1], 0, 0, GetTPage(1, 0, 0x280 + (i * 0x40), 0), &rect);
        SetSprt(&D_800B0188.sprites[i][0]);
        setRGB0(&D_800B0188.sprites[i][0], 0x80, 0x80, 0x80);
        setXY0(&D_800B0188.sprites[i][0], i * 0x80, 0x0);
        setUV0(&D_800B0188.sprites[i][0], 0x0, 0x0);
        setWH(&D_800B0188.sprites[i][0], 0x80, 0xE0);
        SetSemiTrans(&D_800B0188.sprites[i][0], 0);
        (&D_800B0188.sprites[i][0])->clut = GetClut(0, 0xE8);
        D_800B0188.sprites[i][1] = D_800B0188.sprites[i][0];
    }
}

extern s16 D_800ADB54;

void func_800ABEC8(void) {
    int i;

    if (D_800ADB54) {
        for (i = 0; i < 5; i++) {
            addPrim(g_FieldCurRenderContext->ot3, &D_800B0188.sprites[i][g_FieldCurRenderContextIndex]);
            addPrim(g_FieldCurRenderContext->ot3, &D_800B0188.drModes[i][g_FieldCurRenderContextIndex]);
        }
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ABFDC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AC03C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AC0F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AC308);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AC3AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800AC99C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ACB90);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ACC58);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ACCB0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc9", func_800ACCF4);

short FieldScriptVMGetInstructionArgumentS16(int offset) {
    u_char* pData;

    pData = g_FieldScriptVMCurScriptData + (g_FieldScriptVMCurActor->scriptInstructionPointer + offset);
    return (pData[0] + (pData[1] << 8));
}

int FieldScriptVMGetInstructionArgument(int argumentIndex) {
    u_char* pData;

    pData = g_FieldScriptVMCurScriptData + (g_FieldScriptVMCurActor->scriptInstructionPointer + argumentIndex);
    return *pData | *(pData + 1) <<  8;
}

int FieldScriptVMGetArgument(int index) {
    int nArgument;

    nArgument = FieldScriptVMGetInstructionArgument(index);
    if (!(nArgument & 0x8000)) 
        return FieldScriptVMGetVariableValue(nArgument & 0xFFFF);
    return nArgument & 0x7FFF;
}
