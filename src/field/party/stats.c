#include "common.h"
#include "main/game.h"
#include "field/main.h"
#include "field/actor.h"
#include "field/script_vm.h"

void FieldPartyMemberIncreaseHp(int i, int amount) {
    g_GameState->characters[g_GamePartyMembers[i]].hp += amount;
    if (g_GameState->characters[g_GamePartyMembers[i]].maxHp < g_GameState->characters[g_GamePartyMembers[i]].hp) {
        g_GameState->characters[g_GamePartyMembers[i]].hp = g_GameState->characters[g_GamePartyMembers[i]].maxHp;
    }
}

void FieldPartyMemberDecreaseHp(int partyMemberIndex, int amount) {
    int newHp;
    int characterId = g_GamePartyMembers[partyMemberIndex];
    newHp = g_GameState->characters[characterId].hp - amount;
    if (newHp <= 0) {
        newHp = 1;
    }
    g_GameState->characters[characterId].hp = newHp;
}

void FieldPartyMemberIncreaseMp(int i, int amount) {
    g_GameState->characters[g_GamePartyMembers[i]].mp += amount;
    if (g_GameState->characters[g_GamePartyMembers[i]].maxMp < g_GameState->characters[g_GamePartyMembers[i]].mp) {
        g_GameState->characters[g_GamePartyMembers[i]].mp = g_GameState->characters[g_GamePartyMembers[i]].maxMp;
    }
}

void FieldPartyMemberDecreaseMp(int partyMemberIndex, int amount) {
    int newMp;
    int characterId = g_GamePartyMembers[partyMemberIndex];
    newMp = g_GameState->characters[characterId].mp - amount;
    if (newMp <= 0) {
        newMp = 1;
    }
    g_GameState->characters[characterId].mp = newMp;
}

extern s16 g_FieldNumPartyMembersMasks[4];

void FieldScriptVMHandlerDecreasePartyHp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberDecreaseHp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}


INCLUDE_ASM("asm/field/nonmatchings/party/stats", func_80096AF4);

void FieldScriptVMHandlerWritePartyMemberHp(void) {
    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != CHARACTER_ID_NONE) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(1) & 0xFFFF, 
            g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(3)]].hp
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerWritePartyMemberMp(void) {
    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != CHARACTER_ID_NONE) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(1) & 0xFFFF, 
            g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(3)]].mp
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

// Sets the HP of a character to a target amount, but only if we have a full party
void FieldScriptVMHandlerSetPartyMemberHp(void) {
    int targetHp;
    int characterHp;

    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != 0xFF) {
        targetHp = FieldScriptVMGetArgument(2);
        characterHp = g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].maxHp;
        if (characterHp < targetHp) {
            targetHp = characterHp;
        }
        g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].hp = targetHp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

// Sets the MP of a character to a target amount, but only if we have a full party
void FieldScriptVMHandlerSetPartyMemberMp(void) {
    int targetMp;
    int characterMp;

    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != 0xFF) {
        targetMp = FieldScriptVMGetArgument(2);
        characterMp = g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].maxMp;
        if (characterMp < targetMp) {
            targetMp = characterMp;
        }
        g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].mp = targetMp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerIncreasePartyMp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberIncreaseMp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerDecreasePartyMp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberDecreaseMp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

INCLUDE_ASM("asm/field/nonmatchings/party/stats", func_80097108);

void FieldScriptVMHandlerRestoreCharacterHpAndMp(void) {
    int id = FieldScriptVMGetArgument(1);
    g_GameState->characters[id].hp = g_GameState->characters[id].maxHp;
    g_GameState->characters[id].mp = g_GameState->characters[id].maxMp;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void FieldScriptVMHandlerRestoreHp(void) {
    int i;
    for (i = 0; i < MAX_GAME_CHARACTERS; i++) {
        g_GameState->characters[i].hp = g_GameState->characters[i].maxHp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void FieldScriptVMHandlerRestoreMp(void) {
    int i;
    for (i = 0; i < MAX_GAME_CHARACTERS; i++) {
        g_GameState->characters[i].mp = g_GameState->characters[i].maxMp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}