#include "common.h"
#include "main/game.h"
#include "system/math.h"
#include "field/main.h"
#include "field/actor.h"
#include "field/camera.h"
#include "field/script_vm.h"
#include "field/text_box.h"

extern FieldActor* D_800B06B8;
extern s32 D_800AFD1C;
extern s32 g_PlayerActorIndex;


INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800972F4);

void FieldScriptFadeOut(void) {
    int duration;
    
    FieldFadeInitializePrimitives(0);
    duration = FieldScriptVMGetArgument(1);
    FieldFadeToBlack(duration);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void FieldScriptFadeIn(void) {
    int duration = FieldScriptVMGetArgument(1);
    FieldFadeToWhite(duration);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_800973A4(void) {
    if (func_8001B484(FieldScriptVMGetInstructionArgument(2) & 0xFFFF, SCRIPT_READ_U8_REL(1)) == 0) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097410);

int FieldGetPlayerActorDirection(void) {
    int halfDirection = PSX_DEGREES(22.5);
    return (PSX_ANGLE_TO_DIRECTION_8(g_FieldActors[g_PlayerActorIndex].pActorData->rotation.vy + halfDirection) + 2) 
        & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009749C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800975C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800976A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800977A4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097864);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097954);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800979F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097A50);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098038);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800980FC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098184);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098274);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098370);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098430);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800984EC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800985BC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009861C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098738);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800988B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009899C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800989F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80098A7C);

void func_80098C00(void) {
    g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 = 0xFFFF;
    func_80098CAC(0);
}

void func_80098C3C(void) {
    if (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 == 0xFFFF) {
        g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 = FieldScriptVMGetArgument(0xB);
    }
    func_80098CAC(1);
}

extern s32 D_800AFD1C;
extern s32 D_800B00C0;

void func_80098CAC(s32 arg0) {
    IVEC3 prevPosition;
    s16 rotation;
    s32 animationId;
    s32 scriptArg2;
    s32 scriptArg1;
    s32 scriptArg3;
    s32 speed;
    SpriteData* pSprite;
    FieldActor* pFieldActor;
    ActorData *pActorData;

    pFieldActor = g_FieldActors;
    pActorData = pFieldActor[D_800AFD1C].pActorData;
    pSprite = pFieldActor[D_800AFD1C].pSpriteData;
    if (pActorData->flags & 0x2000) {
        speed = CONV_TO_GTE(0x8000000 / g_FieldScriptVMCurActor->moveSpeed);
    } else {
        speed = CONV_TO_GTE(0x4000000 / g_FieldScriptVMCurActor->moveSpeed);
    }
    if (speed == 0) {
        speed = 1;
    }
    
    animationId = 1;
    g_FieldScriptVMCurActor->scriptFlags.fields.scriptFlags_0xX = 1;
    if (SCRIPT_READ_U8_REL(1) == 0) {
        scriptArg1 = CONV_FROM_GTE(FieldScriptArgument1(2, SCRIPT_READ_U8_REL(0x8)));
        scriptArg2 = CONV_FROM_GTE(FieldScriptArgument2(4, SCRIPT_READ_U8_REL(0x8)));
        scriptArg3 = CONV_FROM_GTE(FieldScriptArgument3(6, SCRIPT_READ_U8_REL(0x8)));
        g_FieldScriptVMCurActor->unk102 = FieldGetVec3Magnitude(
            CONV_TO_GTE(scriptArg1 - g_FieldScriptVMCurActor->position.vx), 
            CONV_TO_GTE(scriptArg3 - g_FieldScriptVMCurActor->position.vy), 
            CONV_TO_GTE(scriptArg2 - g_FieldScriptVMCurActor->position.vz)
        ) / speed;

        if (CONV_FROM_GTE(g_FieldScriptVMCurActor->unk102) == 0) {
            g_FieldScriptVMCurActor->unk102++;
        }
        
        g_FieldScriptVMCurActor->unkD0.vx = (scriptArg1 - g_FieldScriptVMCurActor->position.vx) / g_FieldScriptVMCurActor->unk102;
        g_FieldScriptVMCurActor->unkD0.vy = (scriptArg3 - g_FieldScriptVMCurActor->position.vy) / g_FieldScriptVMCurActor->unk102;
        g_FieldScriptVMCurActor->unkD0.vz = (scriptArg2 - g_FieldScriptVMCurActor->position.vz) / g_FieldScriptVMCurActor->unk102;
        if (CONV_TO_GTE(scriptArg1) != CONV_TO_GTE(g_FieldScriptVMCurActor->position.vx) || 
            CONV_TO_GTE(scriptArg2) != CONV_TO_GTE(g_FieldScriptVMCurActor->position.vz)
        ) {
            rotation = -ratan2(
                CONV_TO_GTE(g_FieldScriptVMCurActor->unkD0.vz), 
                CONV_TO_GTE(g_FieldScriptVMCurActor->unkD0.vx)
            );
            g_FieldScriptVMCurActor->rotation.vx = rotation;
            g_FieldScriptVMCurActor->rotation.vy = rotation;
        }
        g_FieldScriptVMCurActor->scriptInstructionPointer += 9;
    } else {
        if (g_FieldScriptVMCurActor->unk102 <= 0 || g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 == 0) {
            g_FieldScriptVMCurActor->scriptInstructionPointer -= 9;
            if (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 != 0) {
                prevPosition.x = g_FieldScriptVMCurActor->position.vx;
                prevPosition.y = g_FieldScriptVMCurActor->position.vy;
                prevPosition.z = g_FieldScriptVMCurActor->position.vz;
                g_FieldScriptVMCurActor->position.vx = CONV_FROM_GTE(FieldScriptArgument1(2, SCRIPT_READ_U8_REL(0x8)));
                g_FieldScriptVMCurActor->position.vz = CONV_FROM_GTE(FieldScriptArgument2(4, SCRIPT_READ_U8_REL(0x8)));
                g_FieldScriptVMCurActor->position.vy = CONV_FROM_GTE(FieldScriptArgument3(6, SCRIPT_READ_U8_REL(0x8)));
                g_FieldScriptVMCurActor->moveModified.vx = g_FieldScriptVMCurActor->position.vx - prevPosition.x;
                g_FieldScriptVMCurActor->moveModified.vy = g_FieldScriptVMCurActor->position.vy - prevPosition.y;
                g_FieldScriptVMCurActor->moveModified.vz = g_FieldScriptVMCurActor->position.vz - prevPosition.z;
            }
            animationId = g_FieldScriptVMCurActor->defaultAnimationId;
            if (arg0 == 0) {
                g_FieldScriptVMCurActor->scriptInstructionPointer += 0xB;
            } else {
                g_FieldScriptVMCurActor->scriptInstructionPointer += 0xD;
            }
            g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 = 0xFFFF;
        } else {
            g_FieldScriptVMCurActor->position.vx += g_FieldScriptVMCurActor->unkD0.vx;
            g_FieldScriptVMCurActor->position.vz += g_FieldScriptVMCurActor->unkD0.vz;
            g_FieldScriptVMCurActor->position.vy +=  g_FieldScriptVMCurActor->unkD0.vy;
            g_FieldScriptVMCurActor->moveModified.vx = g_FieldScriptVMCurActor->unkD0.vx;
            g_FieldScriptVMCurActor->moveModified.vy = g_FieldScriptVMCurActor->unkD0.vy;
            g_FieldScriptVMCurActor->moveModified.vz = g_FieldScriptVMCurActor->unkD0.vz;
            g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0--;
            D_800B00C0 = 1;
        }
        g_FieldScriptVMCurActor->unk102--;
        g_FieldActors[D_800AFD1C].transformMatrix.t[0] = CONV_TO_GTE(g_FieldScriptVMCurActor->position.vx);
        g_FieldActors[D_800AFD1C].transformMatrix.t[1] = CONV_TO_GTE(g_FieldScriptVMCurActor->position.vy);
        g_FieldActors[D_800AFD1C].transformMatrix.t[2] = CONV_TO_GTE(g_FieldScriptVMCurActor->position.vz);
        pSprite->position.x = g_FieldScriptVMCurActor->position.vx;
        pSprite->position.y = g_FieldScriptVMCurActor->position.vy;
        pSprite->position.z = g_FieldScriptVMCurActor->position.vz;
    }
    
    if (g_FieldScriptVMCurActor->unkAnimationId != 0xFF) {
        animationId = g_FieldScriptVMCurActor->unkAnimationId;
    }
    
    if (g_FieldScriptVMCurActor->curAnimationId != animationId &&  
        !g_FieldScriptVMCurActor->scriptFlags.fields.scriptFlags_0x18
    ) {
        g_FieldScriptVMCurActor->curAnimationId = animationId;
        func_800821F4(pSprite, animationId, D_800B06B8, g_FieldScriptVMCurActor);
    }
    func_80081F80(pSprite, g_FieldScriptVMCurActor->rotation.vx, D_800B06B8);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80099214);

void func_80099980(void) {
    g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0x17 = 0;
    g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 = 0xFFFF;
    if (func_80099AC0(0xFFFF) == 0) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 0x6;
    }
}

long FieldGetVec3Magnitude(long x, long y, long z) {
    VECTOR vec;
    VECTOR vecSquared;

    vec.vx = x;
    vec.vy = y;
    vec.vz = z;

    Square0(&vec, &vecSquared);
    return SquareRoot0(vecSquared.vx + vecSquared.vy + vecSquared.vz);
}

long FieldGetVec2Magnitude(long x, long y) {
    VECTOR vec;
    VECTOR vecSquared;

    vec.vx = x;
    vec.vy = y;
    vec.vz = 0;
    Square0(&vec, &vecSquared);
    return SquareRoot0(vecSquared.vx + vecSquared.vy);
}

long FieldGetVec1Magnitude(long x) {
    VECTOR vec;
    VECTOR vecSquared;

    vec.vx = x;
    Square0(&vec, &vecSquared);
    return SquareRoot0(vecSquared.vx);
}

