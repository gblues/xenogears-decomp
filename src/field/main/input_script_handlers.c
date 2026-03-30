#include "common.h"
#include "field/actor.h"
#include "field/script_vm.h"

extern u16 D_800AFC6C; // Held buttons state?

void FieldScriptVMCheckControllerInput(u_short buttonState) {
    u_short nButtonMask;
    
    nButtonMask = FieldScriptVMGetInstructionArgument(1);
    if (nButtonMask & buttonState) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer = FieldScriptVMGetInstructionArgument(3);
    }
}

void FieldScriptCheckControllerInputExact(u_short buttonState) {
    u_short buttonMask;

    buttonMask = FieldScriptVMGetInstructionArgument(1);
    if (buttonMask == buttonState) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer = FieldScriptVMGetInstructionArgument(3);
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/input_script_handlers", func_80096150);
/*
void func_80096150(u_short targetButtonState) {
    FieldScriptCheckControllerInputExact(targetButtonState);
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/input_script_handlers", func_80096178);
/*
void func_80096178(void) {
    FieldScriptCheckControllerInputExact(D_800AFC6C);
}
*/

// Is button pressed handler
INCLUDE_ASM("asm/field/nonmatchings/main/input_script_handlers", func_800961A0);
/*
void func_800961A0(void) {
    FieldScriptVMCheckControllerInput(D_800AFE9C);
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/input_script_handlers", func_800961C8);

INCLUDE_ASM("asm/field/nonmatchings/main/input_script_handlers", func_800961F0);
