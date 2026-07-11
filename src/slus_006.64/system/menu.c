#include "common.h"
#include "psyq/libgte.h"
#include "system/controller.h"
#include "system/menu.h"
#include "system/memory.h"

void MenuInitializeGfxEnvironment(GfxEnvironment* pGfxEnv) {
    pGfxEnv->drawEnv.dtd = 1;
    pGfxEnv->dispEnv.screen.y = 10;
    pGfxEnv->dispEnv.screen.w = 256;
    pGfxEnv->drawEnv.isbg = 0;
    pGfxEnv->drawEnv.r0 = 0;
    pGfxEnv->drawEnv.g0 = 0;
    pGfxEnv->drawEnv.b0 = 0;
    pGfxEnv->dispEnv.screen.x = 0;
    pGfxEnv->dispEnv.screen.h = 216;
}

void MenuInitializeGfxEnvironments(void) {
    SetGeomOffset(160, 112);
    SetGeomScreen(0x200);
    SetDefDispEnv(&g_Menu->gfxEnvs[0].dispEnv, 0, 0xE0, 0x140, 0xE0);
    SetDefDrawEnv(&g_Menu->gfxEnvs[0].drawEnv, 0, 0, 0x140, 0xE0);
    SetDefDispEnv(&g_Menu->gfxEnvs[1].dispEnv, 0, 0, 0x140, 0xE0);
    SetDefDrawEnv(&g_Menu->gfxEnvs[1].drawEnv, 0, 0xE0, 0x140, 0xE0);
    MenuInitializeGfxEnvironment(&g_Menu->gfxEnvs[0]);
    MenuInitializeGfxEnvironment(&g_Menu->gfxEnvs[1]);
}

void func_8001BEEC(void) {
    g_Menu->translation.vz = 0x800;
    g_Menu->unk220.vz = 0x800;
    g_Menu->rotation.vz = 0;
    g_Menu->rotation.vy = 0;
    g_Menu->rotation.vx = 0;
    g_Menu->translation.vy = 0;
    g_Menu->translation.vx = 0;
    g_Menu->unk218.vz = 0;
    g_Menu->unk218.vy = 0;
    g_Menu->unk218.vx = 0;
    g_Menu->unk220.vy = 0;
    g_Menu->unk220.vx = 0;
    g_Menu->unk2E8 = 1;
    g_Menu->transitionEffectState = 0;
}

void MenuProcessControllerInput(void) {
    u_char input = MENU_INPUT_IDLE;
    if (func_80036410() != 0) {
        ControllerResetState();
        g_Menu->input = input;
        return;
    }
    while (ControllerPopState()) {
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_RIGHT) {
            input = MENU_INPUT_RIGHT;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_DOWN) {
            input = MENU_INPUT_DOWN;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_LEFT) {
            input = MENU_INPUT_LEFT;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_UP) {
            input = MENU_INPUT_UP;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_CIRCLE) {
            input = MENU_INPUT_CONFIRM;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_SELECT) {
            input = 12;
            g_Menu->unk1E94 = g_Menu->unk1E94 == 0;
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_L1) {
            if (g_Menu->unk1E95) {
                g_Menu->unk1E95 -= 1;
            }
            break;
        }
        if (g_C1ButtonStatePressedOnce & CTRL_BTN_L2) {
            g_Menu->unk1E95 += 1;
            break;
        }
    }
    g_Menu->input = input;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/menu", func_8001C074);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/menu", MenuExecute);

// Before calling this, it's expected that the caller have loaded the correct
// menu overlay to the correct address (0x801C5000).
void MenuMain() {
    g_Menu = HeapAlloc(sizeof(SystemMenu), 0);
    bzero(g_Menu, sizeof(SystemMenu));
    g_Menu->input = 8;
    HeapChangeCurrentUser(HEAP_USER_HIG, NULL);
    g_Menu->pGfxEnv = &g_Menu->gfxEnvs[1];
    g_Menu->unk1E94 = 0;
    g_Menu->unk1E95 = 1;
    g_Menu->unk2D8 = 0;
    g_Menu->shouldDrawMenu = FALSE;
    MenuInitializeGfxEnvironments();
    if (g_MenuDebugEnabled) {
        g_Menu->gfxEnvs[0].drawEnv.isbg = 1;
        g_Menu->gfxEnvs[1].drawEnv.isbg = 1;
    }
    func_8001BEEC();
    Vsync(0);
    PutDrawEnv(&g_Menu->gfxEnvs[0].drawEnv);
    PutDrawEnv(&g_Menu->gfxEnvs[1].drawEnv);
    PutDispEnv(&g_Menu->gfxEnvs[0].dispEnv);
    PutDispEnv(&g_Menu->gfxEnvs[1].dispEnv);
    SetDispMask(1);

    // This call takes over control flow and runs the loaded menu until it returns
    MenuExecute();

    g_MenuDebugEnabled = 1;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/menu", func_8001C76C);
