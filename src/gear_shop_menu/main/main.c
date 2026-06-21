#include "common.h"
#include "system/menu.h"

extern s32 D_801D9050;
extern s32 D_801D9054;
extern s32 D_801D9058;
extern s32 D_801D905C;
extern s32 D_801D9060;
extern s32 D_801D9064;
extern s8 D_801D9083;

u16 func_801C5228(uint, u_char);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C511C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C51B8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5228);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5244);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5260);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C527C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5298);

/**
 * Manages the memory allocation for MenuUnk2 in the system menu (g_Menu).
 *
 * @param isInitialization determines action taken; valid values are either MENU_DATA_INITIALIZE or MENU_DATA_FREE
 */
/* 0x801C5344 */void GearMenu_MenuUnk2Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk2 = HeapAlloc(sizeof(MenuUnk2), 0);
        bzero(g_Menu->menuUnk2, sizeof(MenuUnk2));
        return;
    }
    HeapFree(g_Menu->menuUnk2);
}

/* 801C53A8 */void GearMenu_MenuManagerManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pManager = HeapAlloc(sizeof(MenuManager), 0);
        bzero(g_Menu->pManager, sizeof(MenuManager));
        return;
    }
    HeapFree(g_Menu->pManager);
}

/* 801C540C */ void GearMenu_SelectionMenuManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pSelectionMenu = HeapAlloc(sizeof(MenuSelectionMenu), 0);
        bzero(g_Menu->pSelectionMenu, sizeof(MenuSelectionMenu));
        return;
    }
    HeapFree(g_Menu->pSelectionMenu);
}

/* 801C5470 */ void GearMenu_MenuUnk5Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk354 = HeapAlloc(sizeof(MenuUnk5), 0);
        bzero(g_Menu->unk354, sizeof(MenuUnk5));
        return;
    }
    HeapFree(g_Menu->unk354);
}

/* 801C54D4 */ void GearMenu_MenuUnk6Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk330 = HeapAlloc(sizeof(MenuUnk6), 0);
        bzero(g_Menu->unk330, sizeof(MenuUnk6));
        return;
    }
    HeapFree(g_Menu->unk330);
}

/* 801C5538 */ void GearMenu_MenuUnk1Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk348 = HeapAlloc(sizeof(MenuUnk1), 0);
        bzero(g_Menu->unk348, sizeof(MenuUnk1));
        return;
    }
    HeapFree(g_Menu->unk348);
}

/* 801C559C */ void GearMenu_MenuUnk7Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk1E20 = HeapAlloc(sizeof(MenuUnk7), 0);
        bzero(g_Menu->unk1E20, sizeof(MenuUnk7));
        return;
    }
    HeapFree(g_Menu->unk1E20);
}

/* 801C5600 */ void GearMenu_MenuShopManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pShop = HeapAlloc(sizeof(MenuShop), 0);
        bzero(g_Menu->pShop, sizeof(MenuShop));
        return;
    }
    HeapFree(g_Menu->pShop);
}

/* 801C5664 */ void GearMenu_MenuUnk8Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk8 = HeapAlloc(sizeof(MenuUnk8), 0);
        bzero(g_Menu->menuUnk8, sizeof(MenuUnk8));
        return;
    }
    HeapFree(g_Menu->menuUnk8);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C56C8);

/* 801C5B08 */ void GearMenu_FilterPartyMembers(void) {
    s32 i;
    u_short masked_bits;

    g_Menu->menu1Choice = 4;
    g_Menu->unk337 = 0xFF;
    g_Menu->unk326 = 0x3C;
    g_Menu->unk334 = 0;
    g_Menu->unk335 = 0;

    masked_bits = g_GameState.unk1D30 & g_GameState.FrMask & 0x77F;

    /* filter availableCharacters by if gearId != 0xff */
    for(i = 0; i < 16; i++) {
        if( func_801C5228(masked_bits, i) > 0 && g_GameState.characters[i].gearId != 0xFF ) {
            g_Menu->availableCharacters[i] = 1;
        } else {
            g_Menu->availableCharacters[i] = 0;
        }
    }

    /* filter by current party */
    for(i = 0; i < 3; i++) {
        if( g_GameState.partyMembers[i] != 0xff && g_Menu->availableCharacters[g_GameState.partyMembers[i]] != 0) {
            g_Menu->pManager->currentCharacterIDs[i] = g_GameState.partyMembers[i];
        } else {
            g_Menu->pManager->currentCharacterIDs[i] = 0xff;
        }
    }

    func_801C56C8();
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5C98);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5CA8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5EE8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6098);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6114);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6170);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6278);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C665C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C668C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6708);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6A54);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6E74);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7604);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C765C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C76A4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C782C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7870);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C78EC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7A88);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7AE4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7E00);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7F64);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C81AC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C84F0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C883C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C8B84);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C8ED0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9054);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C90E0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9264);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C93B0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C94CC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9550);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C959C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C962C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9690);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9864);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9A38);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9C0C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9DE0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9F1C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA068);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA28C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA404);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA754);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA7E4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA874);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA9EC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CAA7C);

void func_801CABD8(void) {
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CABE0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CAC20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB2E8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB35C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB3D0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB498);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB4E4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB690);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CBA2C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CBDA0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CBE60);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC1C4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC31C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC4DC);

void func_801CC520(void) {
}

void func_801CC528(void) {
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC530);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC9A0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCA40);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCC18);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCD20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCE90);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCEBC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCEE8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CD310);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CD564);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CD838);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CDA0C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CDC68);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CDD74);

/* 0x801CE024 */ void GearMenuEntrypoint(void) {
    GearMenu_MenuUnk2Manager(MENU_DATA_INITIALIZE);
    GearMenu_MenuManagerManager(MENU_DATA_INITIALIZE);
    GearMenu_SelectionMenuManager(MENU_DATA_INITIALIZE);
    GearMenu_MenuUnk5Manager(MENU_DATA_INITIALIZE);
    GearMenu_MenuUnk6Manager(MENU_DATA_INITIALIZE);
    GearMenu_MenuUnk1Manager(MENU_DATA_INITIALIZE);
    GearMenu_MenuUnk7Manager(MENU_DATA_INITIALIZE);
    GearMenu_MenuShopManager(MENU_DATA_INITIALIZE);
    GearMenu_MenuUnk8Manager(MENU_DATA_INITIALIZE);
    g_Menu->pSelectionMenu->unk1180.x = 0x2C0;
    g_Menu->pSelectionMenu->unk1180.y = 0x100;
    g_Menu->pSelectionMenu->unk1180.w = 0x140;
    g_Menu->pSelectionMenu->unk1180.h = 0xE0;
    g_Menu->unk348->unk15B = 0x40;
    g_Menu->translation.vz = 0x200;
    g_Menu->rotation.vz = 0;
    g_Menu->rotation.vx = 0;
    g_Menu->rotation.vy = 0;
    g_Menu->unk220.vz = 0x400;
    g_Menu->unk218.vz = 0;
    g_Menu->unk218.vx = 0;
    g_Menu->unk218.vy = 0x400;
    g_Menu->transitionEffectState = 0;
    D_801D9058 = -0x400;
    D_801D9064 = -0x400;
    D_801D9050 = 0x400;
    D_801D9054 = 0;
    D_801D905C = 0x400;
    D_801D9060 = 0;
    D_801D9083 = 0x10;
    GearMenu_FilterPartyMembers();
    func_801C5C98();
    func_801C6114();
    func_801C6708();
    func_801C6170();
    func_801C6E74();
    func_801D5D38();
    g_Menu->unk440 = HeapAlloc(sizeof(MenuUnknownComponent), 0);
    bzero(g_Menu->unk440, sizeof(MenuUnknownComponent));
    func_801CE1D0();
    g_Menu->shouldDrawMenu = 1;
    g_Menu->unk32A = 1;
    func_801CDD74();
    func_801CCD20();
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE1D0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE2E8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE32C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE7E0);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE82C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CEA68);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CEEA8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF184);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF33C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF38C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF448);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF9BC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CFAB8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CFC60);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CFF18);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0054);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0220);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0348);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0398);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D04E8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D05EC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D06D8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0C20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0D4C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0EC8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1078);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1304);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D18F8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1F20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2054);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2784);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D27C4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2804);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2950);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2B74);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3558);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3A3C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3A80);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3C78);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D44FC);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D4888);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D498C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5398);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D573C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D57A8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5828);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5D38);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5EB8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5F94);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6150);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D61B8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6250);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D62A4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6334);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6738);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D690C);
