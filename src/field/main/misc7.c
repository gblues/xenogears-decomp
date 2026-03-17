#include "common.h"
#include "main/game.h"
#include "field/main.h"
#include "field/actor.h"
#include "field/script_vm.h"
#include "field/text_box.h"

extern ActorData* D_800B06B8;
extern s32 D_800AFD1C;

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800972F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009731C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097364);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_800973A4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80097410);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009744C);

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
        speed = (0x8000000 / g_FieldScriptVMCurActor->moveSpeed) >> 0x10;
    } else {
        speed = (0x4000000 / g_FieldScriptVMCurActor->moveSpeed) >> 0x10;
    }
    if (speed == 0) {
        speed = 1;
    }
    
    animationId = 1;
    g_FieldScriptVMCurActor->scriptFlags_0xX = 1;
    if (SCRIPT_READ_U8_REL(1) == 0) {
        scriptArg1 = func_8009CF78(2, SCRIPT_READ_U8_REL(0x8)) << 0x10;
        scriptArg2 = func_8009CFBC(4, SCRIPT_READ_U8_REL(0x8)) << 0x10;
        scriptArg3 = func_8009D000(6, SCRIPT_READ_U8_REL(0x8)) << 0x10;
        g_FieldScriptVMCurActor->unk102 = FieldGetVec3Magnitude(
            (scriptArg1 - g_FieldScriptVMCurActor->position.vx) >> 0x10, 
            (scriptArg3 - g_FieldScriptVMCurActor->position.vy) >> 0x10, 
            (scriptArg2 - g_FieldScriptVMCurActor->position.vz) >> 0x10
        ) / speed;

        if ((g_FieldScriptVMCurActor->unk102 << 0x10) == 0) {
            g_FieldScriptVMCurActor->unk102++;
        }
        
        g_FieldScriptVMCurActor->unkD0.vx = (scriptArg1 - g_FieldScriptVMCurActor->position.vx) / g_FieldScriptVMCurActor->unk102;
        g_FieldScriptVMCurActor->unkD0.vy = (scriptArg3 - g_FieldScriptVMCurActor->position.vy) / g_FieldScriptVMCurActor->unk102;
        g_FieldScriptVMCurActor->unkD0.vz = (scriptArg2 - g_FieldScriptVMCurActor->position.vz) / g_FieldScriptVMCurActor->unk102;
        if ((scriptArg1 >> 0x10) != (g_FieldScriptVMCurActor->position.vx >> 0x10) || 
            (scriptArg2 >> 0x10) != (g_FieldScriptVMCurActor->position.vz >> 0x10)
        ) {
            rotation = -func_8004B32C(
                g_FieldScriptVMCurActor->unkD0.vz >> 0x10, 
                g_FieldScriptVMCurActor->unkD0.vx >> 0x10
            );
            g_FieldScriptVMCurActor->rotationX = rotation;
            g_FieldScriptVMCurActor->rotationY = rotation;
        }
        g_FieldScriptVMCurActor->scriptInstructionPointer += 9;
    } else {
        if (g_FieldScriptVMCurActor->unk102 <= 0 || g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 == 0) {
            g_FieldScriptVMCurActor->scriptInstructionPointer -= 9;
            if (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0 != 0) {
                prevPosition.x = g_FieldScriptVMCurActor->position.vx;
                prevPosition.y = g_FieldScriptVMCurActor->position.vy;
                prevPosition.z = g_FieldScriptVMCurActor->position.vz;
                g_FieldScriptVMCurActor->position.vx = func_8009CF78(2, SCRIPT_READ_U8_REL(0x8)) << 0x10;
                g_FieldScriptVMCurActor->position.vz = func_8009CFBC(4, SCRIPT_READ_U8_REL(0x8)) << 0x10;
                g_FieldScriptVMCurActor->position.vy = func_8009D000(6, SCRIPT_READ_U8_REL(0x8)) << 0x10;
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
        g_FieldActors[D_800AFD1C].transformMatrix.t[0] = g_FieldScriptVMCurActor->position.vx >> 0x10;
        g_FieldActors[D_800AFD1C].transformMatrix.t[1] = g_FieldScriptVMCurActor->position.vy >> 0x10;
        g_FieldActors[D_800AFD1C].transformMatrix.t[2] = g_FieldScriptVMCurActor->position.vz >> 0x10;
        pSprite->position.x = g_FieldScriptVMCurActor->position.vx;
        pSprite->position.y = g_FieldScriptVMCurActor->position.vy;
        pSprite->position.z = g_FieldScriptVMCurActor->position.vz;
    }
    
    if (g_FieldScriptVMCurActor->unkAnimationId != 0xFF) {
        animationId = g_FieldScriptVMCurActor->unkAnimationId;
    }
    
    if (g_FieldScriptVMCurActor->curAnimationId != animationId &&  
        !g_FieldScriptVMCurActor->scriptFlags_0x18
    ) {
        g_FieldScriptVMCurActor->curAnimationId = animationId;
        func_800821F4(pSprite, animationId, D_800B06B8, g_FieldScriptVMCurActor);
    }
    func_80081F80(pSprite, g_FieldScriptVMCurActor->rotationX, D_800B06B8);
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

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80099AC0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80099EF8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_80099F48);

void FieldScriptVMHandlerGetActorFacingAngle(void) {
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(1) & 0xFFFF,
        ((g_FieldScriptVMCurActor->rotationY + 0x100 >> 9) + 2) & 7 // What
    );
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void FieldScriptVMHandlerGetActorPosition(void) {
    int nActorIndex = FieldScriptVMGetActorIndex(1);
    if (nActorIndex != 0xFF) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(2) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[0]
        );
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(4) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[2]
        );
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(6) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[1]
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A0FC);

void FieldScriptVMHandlerPlayAnimation(void) {
    unsigned char animationID;
    
    g_FieldScriptVMCurActor->flags &= 0xFEFFFFFF;
    animationID = *(u8*)&g_FieldScriptVMCurScriptData[g_FieldScriptVMCurActor->scriptInstructionPointer + 1];
    g_FieldScriptVMCurActor->unkAnimationId = animationID;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A174);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A1AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A1E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A2A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A34C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A420);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A490);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A514);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A534);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A58C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A5E0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A634);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A670);

// Write cosine of angle to script memory?
void func_8009A6AC(void) {
    int nValue;
    int angle;
    int nFactor;
    int nVariableAddress;

    nVariableAddress = FieldScriptVMGetInstructionArgument(1) & 0xFFFF;
    angle = func_8009CFBC(3, SCRIPT_READ_U8_REL(7));
    nFactor = func_8009D000(5,  SCRIPT_READ_U8_REL(7)); // ?
    nValue = rcos(angle) * nFactor;
    FieldScriptMemoryWriteU16(nVariableAddress, nValue >> 0xC);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

// Write sine of angle to script memory?
void func_8009A768(void) {
    int nValue;
    int angle;
    int nFactor;
    int nVariableAddress;

    nVariableAddress = FieldScriptVMGetInstructionArgument(1) & 0xFFFF;
    angle = func_8009CFBC(3, SCRIPT_READ_U8_REL(7));
    nFactor = func_8009D000(5,  SCRIPT_READ_U8_REL(7));
    nValue = rsin(angle) * nFactor;
    FieldScriptMemoryWriteU16(nVariableAddress, nValue >> 0xC);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A824);

// Get 8-directional movement direction based on Y Rotation of current actor?
s32 func_8009A8DC(void) {
    return (((g_FieldScriptVMCurActor->rotationY + 0x100) >> 9) + 2) & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS;
}

extern s32 D_800ADB1C; // Is current actor a 2D actor (0) maybe?
void FieldSetCurrentActorRotation(int rotation) {
    short rotationValue2D;
    short rotationValue3D;

    if (D_800ADB1C == 0) {
        rotationValue3D = rotation | 0x8000;
        g_FieldScriptVMCurActor->rotationX = rotationValue3D;
        g_FieldScriptVMCurActor->rotationY = rotationValue3D;
        g_FieldScriptVMCurActor->rotationZ = rotationValue3D;
    }
    rotationValue2D = rotation | 0x8000;
    g_FieldScriptVMCurActor->rotationX = rotationValue2D;
    g_FieldScriptVMCurActor->rotationY = rotationValue2D;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009A958);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AA00);

extern u16 D_800AF98C;
void func_8009AB08(int rotation) {
    short rotationValue;

    rotationValue = ((rotation - D_800AF98C) & 0xFFF) | 0x8000;
    g_FieldScriptVMCurActor->rotationX = rotationValue;
    g_FieldScriptVMCurActor->rotationY = rotationValue;

    // 3D Actor?
    if (D_800ADB1C == 0) {
        g_FieldScriptVMCurActor->rotationZ = rotationValue;
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

extern u16 D_800AEA34[]; // 8-directional movement rotation value table?

// Set Current Actor Rotation (Clockwise)
void func_8009AB5C(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[nRotationLUTIndex + func_8009A8DC() & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS]);
}

// Set Current Actor Rotation (Counter-clockwise)
void func_8009ABAC(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[func_8009A8DC() - nRotationLUTIndex & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS]);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009ABFC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AC34);

void FieldScriptVMHandlerSetCurActorRotation(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[nRotationLUTIndex]);
}

void func_8009ACB4(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    func_8009AB08(D_800AEA34[nRotationLUTIndex]);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009ACEC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AD6C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009ADDC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AE0C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AE3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009AEE0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B15C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B184);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B210);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B338);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B398);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B664);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B6AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B708);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B7A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B824);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B884);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B8E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009B9A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009BA0C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc7", func_8009BA7C);
