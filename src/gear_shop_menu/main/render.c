#include "common.h"
#include "system/menu.h"
#include "system/controller.h"
#include "system/archive.h"
#include "system/graphics.h"
#include "system/debug.h"

#define MAX_NUM_SUBMENU_OPTIONS 0x4

// Confirmation window choices
#define MENU_CHOICE_NO 0
#define MENU_CHOICE_YES 1

// Selection modes
#define MENU_AUTO_ADVANCE 0
#define MENU_MANUAL_CHOICE 0xFF


// Submenu choices for "Tune up"
#define MENU_CHOICE_ARMOR 0x0
#define MENU_CHOICE_FRAME 0x1
#define MENU_CHOICE_ENGINE 0x2
#define MENU_CHOICE_FUEL 0x3

// Submenu choices for "Sell"
#define MENU_CHOICE_WEAPONS 0x3
#define MENU_CHOICE_PARTS 0x4


#define MENU_CYCLE_TO_NEXT 0x0
#define MENU_CYCLE_TO_PREV 0x1


// probably something like: DEBUGGER_ATTACHED, guards a breakpoint left in the code
extern s32* D_8005917C; // TODO: should be in a header for main program stuff since this is not coming from an overlay

extern s8  D_801D697C;


extern int D_801D69A0[]; // MENU_TEX_BALL_CURSOR_8
extern int D_801D69A4[];
// = {
//    Buy Submenu
//                             MENU_TEX_STRING_WEAPONS,
//    MENU_TEX_BALL_CURSOR_9,  MENU_TEX_STRING_PARTS,
//    MENU_TEX_BALL_CURSOR_10, MENU_TEX_STRING_FUEL,
//    MENU_TEX_BALL_CURSOR_11, MENU_TEX_STRING_ENGINE,
//    MENU_TEX_BALL_CURSOR_8,  MENU_TEX_STRING_PARTS,
//    MENU_TEX_BALL_CURSOR_9,  MENU_TEX_STRING_WEAPONS,
//    0xFFFF, 0xFFFF
//    0xFFFF, 0xFFFF,
//    ------------------------------------------------
//    Sell Submenu
//    MENU_TEX_BALL_CURSOR_8, MENU_TEX_STRING_PARTS,
//    MENU_TEX_BALL_CURSOR_9, MENU_TEX_STRING_WEAPONS,
//    0xFFFF, 0xFFFF,
//    0xFFFF, 0xFFFF,
//    ------------------------------------------------
//    Tune up Submenu
//    MENU_TEX_BALL_CURSOR_8,  MENU_TEX_STRING_ARMOR,
//    MENU_TEX_BALL_CURSOR_9,  MENU_TEX_STRING_FRAME,
//    MENU_TEX_BALL_CURSOR_10, MENU_TEX_STRING_ENGINE,
//    MENU_TEX_BALL_CURSOR_11, MENU_TEX_STRING_FUEL
//   }

extern u8  D_801D6A20;
extern u8  D_801D6A24;
extern int D_801D6A60[4];
extern int D_801D6A70[4];
extern u32 D_801D6A80;
extern int D_801D6A84[];
extern int D_801D6AFC[];
extern int D_801D6B7C[];
extern int D_801D6C44[];
extern u16 D_801D6C68[];
extern int D_801D6C88[];
extern u8  D_801D6D08[8]; // indexed by (renderContext * 4)+i
extern u8  D_801D6D10[2]; // indexed by renderContext
extern int D_801D6D14[8]; // indexed by (renderContext * 4)+i
extern s32 D_801D6D34[2]; // indexed by renderContext
extern int D_801D6D3C[8]; // indexed by (renderContext * 4)+i
extern s32 D_801D6D5C[2]; // indexed by renderContext
extern u16 D_801D6D7C[2];
extern int D_801D6D14[8];
extern int D_801D6D3C[8];

// // D_801D6D7C
extern s32 D_801D6FD0[2];

extern u16 D_801D7074[6];
extern u16 D_801D7080[6];
extern u8  D_801D70F4[9];

extern s8  D_801D70FD;
extern s32 D_801D9050;
extern s32 D_801D9054;
extern s32 D_801D9058;
extern s32 D_801D905C;
extern s32 D_801D9060;
extern s32 D_801D9064;
extern s8  D_801D9083;
extern int g_gearShopAvailableCharacterCount;
extern int g_gearShopCurCharacterIndex;

extern u_char  g_gearShopCurrentGearId;
extern u8* D_801D9088;

extern s32 D_801D6980[];
// = {
//    MENU_TEX_BALL_CURSOR_1, MENU_TEX_STRING_BUY,
//    MENU_TEX_BALL_CURSOR_2, MENU_TEX_STRING_SELL,
//    MENU_TEX_BALL_CURSOR_3, MENU_TEX_STRING_EXIT,
//    MENU_TEX_BALL_CURSOR_4, MENU_TEX_STRING_TUNE_UP,
//    }
extern s32 D_801D6A30[];

void GearShopMenuShoulderButtonUiInitialize(void) {
    int i;
    int polyIndex;

    for(i = 0; i < 2; i++) {
        func_8002675C(
            g_Menu->resources,
            MENU_TEX_L1_RED_ARROW + i,
            &g_Menu->pShoulderButtonUi->polys[i * 4],
            g_Menu->renderContext,
            D_801D6FD0[i],
            0x64,
            0x1000
        );
    }

    for(i = 0; i < 4; i++) {
        polyIndex = (i * 2 + g_Menu->renderContext);
        GearShopMenuSetVertices(
            &g_Menu->pShoulderButtonUi->vertices[i * 4],
            g_Menu->pShoulderButtonUi->polys[polyIndex].x0,
            g_Menu->pShoulderButtonUi->polys[polyIndex].y0,
            g_Menu->pShoulderButtonUi->polys[polyIndex].x1 - g_Menu->pShoulderButtonUi->polys[polyIndex].x0,
            g_Menu->pShoulderButtonUi->polys[polyIndex].y3 - g_Menu->pShoulderButtonUi->polys[polyIndex].y0
        );
    }

    g_Menu->pShoulderButtonUi->renderContext = g_Menu->renderContext;
}

void GearShopMenuShoulderButtonUiFree(void) {
    g_Menu->pManager->shoulderButtonUiActive = FALSE;
    GearShopMenuUpdateAndRender();
    HeapFree(g_Menu->pShoulderButtonUi);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CE32C);


/*
 This is the function in gear_shop_menu that calls into gear_shop_helper
 */
void func_801CE7E0(void) {
    // most likely: if helper library is loaded into memory
    if (g_Menu->pManager->unk5C[7]) {
        func_801E7D14(&g_Menu->unk230, &g_Menu->unk298, g_Menu->pGfxEnv->unkB0, g_Menu->renderContext);
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CE82C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CEA68);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CEEA8);

u8 func_8001BD40(int, u8); // Required signature for function below to match
void func_801CF184(void) {
    MenuUnk8* pMenu;
    int i;
    short t1, t2;

    pMenu = g_Menu->menuUnk8;

    if (pMenu->unk1ED8) {
        if(pMenu->unk1EDC) {
            g_Menu->menuUnk8->unk1EDC--;
        } else {
            if(func_8001BD40(0, 0xFF) < 8) {
                t1 = D_801D7074[func_8001BD40(0, 5)];
                t2 = D_801D7080[func_8001BD40(0, 5)];
                g_Menu->menuUnk8->unk1EF0 = t1;
                g_Menu->menuUnk8->unk1EF2 = t2;
            }

            for(i = 0; i < 3; i++) {
                g_Menu->menuUnk8->unk1ED0 = func_8002675C(
                    g_Menu->resources,
                    g_Menu->menuUnk8->unk1EE0 + 0x167,
                    &g_Menu->menuUnk8->polys[i * 4],
                    g_Menu->renderContext,
                    g_Menu->menuUnk8->unk1EF0 + i * 0x8,
                    g_Menu->menuUnk8->unk1EF2 + i * 0xA,
                    0x1000
                );
            }

            g_Menu->menuUnk8->unk1EE0 ^= 1;
            g_Menu->menuUnk8->unk1ED4 = g_Menu->renderContext;
            g_Menu->menuUnk8->unk1EDC = 4;
        }
    }
}

void func_801CF33C(void) {
    if (g_Menu->pManager->unk5C[9]) {
        func_801CEA68();
        func_801CEEA8();
        func_801CF184();
    }
}

// Render gear name
void func_801CF38C(u_char stringIndex) {
    RECT rect;

    D_801D9088 = HeapAlloc(0x3F6, 0x0);
    bzero(D_801D9088, 0x3F6);
    SystemRenderStringEntry(&g_GameState.strings[stringIndex], D_801D9088, 0x24, 0);
    setRECT(&rect, 0x180, 0x48, 0x28, 0xD);
    LoadImage(&rect, (u32* ) D_801D9088);
    DrawSync(0);
    HeapFree(D_801D9088);
}

// Render gear stats (Fuel, HP, Weight) - https://decomp.me/scratch/SfkHu
// Resource IDs for text:
// 0x11, 0x19 = HP
// 0xF, 0x1E, 0xE, 0x15 = FUEL
// 0x20, 0xE, 0x12, 0x10, 0x11, 0x1D = WEIGHT
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CF448);

void func_801CF9BC(u_char gearId, u8 arg1) {
    ArchiveSetIndex(ARCHIVE_DIR_FIELD, 0);

    g_Menu->unk458[arg1]->unk0 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[gearId]), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[gearId], g_Menu->unk458[arg1]->unk0, 0, 0x80);
    ArchiveCdDataSync(0);

    g_Menu->unk458[arg1]->unk4 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[gearId] + 1), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[gearId] + 1, g_Menu->unk458[arg1]->unk4, 0, 0x80);
    ArchiveCdDataSync(0);

    ArchiveSetIndex(ARCHIVE_DIR_MENUS, 0);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CFAB8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801CFC60);

void func_801CFF18(void) {
    s32 temp1;
    s32 temp2;
    s32 temp3;

    g_Menu->menuUnk8->unk1ED9 = 3;
    g_Menu->menuUnk8->unk1EDA = 3;
    g_Menu->menuUnk8->unk1EDB = 3;
    g_Menu->menuUnk8->unk1EDC = 0;
    g_Menu->menuUnk8->unk1EDD = 0;
    g_Menu->menuUnk8->unk1EDE = 0;
    g_Menu->menuUnk8->unk1EDF = 0;
    g_Menu->pManager->unk5C[9] = 1;
    // this is probably some swappy-copy function but without the data better defined we have to do it explicitly
    temp1 = D_801D905C;
    temp2 = D_801D9060;
    temp3 = D_801D9064;
    D_801D905C = 0x400;
    D_801D9060 = 0;
    D_801D9064 = -0x400;
    D_801D9050 = temp1;
    D_801D9054 = temp2;
    D_801D9058 = temp3;
    func_801CB690(D_801D9050, D_801D9054);
    g_Menu->transitionEffectState = 7;
}

void func_801D0054(int count, POLY_FT4 *pPolys, u_char mode) {
    int i;

    for(i = 0; i < count; i++) {
        SetShadeTex(&pPolys[(i*2)+g_Menu->renderContext], 0);
        switch(mode) {
            case 0:
                setRGB0(&pPolys[(i*2)+g_Menu->renderContext], 0x80, 0x40, 0x40);
                break;
            case 1:
                setRGB0(&pPolys[(i*2)+g_Menu->renderContext], 0x40, 0x40, 0x80);
                break;
        }
    }
}

void GearShopMenuUpdateCharacterPortraits(void) {
    int i;
    int characterIndex;
    int numCharacters;

    g_Menu->pManager->unk5A = 1;

    // This loop seems horribly inefficient, because for each character index, all
    // portraits are recomputed and the entire menu redrawn...
    for (i = 1; i < MAX_GAME_CHARACTERS + 1; i++) {
        g_Menu->pShop->numPortraits = 0;

        numCharacters = 0;
        for (characterIndex = 0; characterIndex < i; characterIndex++) {
            if (g_Menu->availableCharacters[characterIndex]) {
                g_Menu->pShop->numPortraits += func_8002675C(
                    g_Menu->resources, characterIndex + MENU_TEX_CHARACTER_PORTRAITS_SMALL,
                    &g_Menu->pShop->polysCharacterPortraits[numCharacters * 2],
                    g_Menu->renderContext,
                    D_801D6C44[numCharacters], 166,
                    0x1000
                );
                numCharacters++;
            }
        }

        g_Menu->pShop->portraitsRenderCtx = g_Menu->renderContext;
        GearShopMenuUpdateAndRender();
    }
}

void GearShopMenuSetAvailableCharacterCount(void) {
    int i;

    for(i = 0; i < MAX_GAME_CHARACTERS; i++) {
        if(g_Menu->availableCharacters[i]) {
            g_gearShopAvailableCharacterCount += 1;
        }
    }
}

void GearShopMenuChangeCurrentGear(u_char mode) {
    int characterIndex;
    int index;
    int tmp;

    if ((g_Menu->transitionEffectState == 0) && (g_gearShopAvailableCharacterCount >= 2)) {
        // Cycle to next or previous character
        index = g_gearShopCurCharacterIndex;
        if (mode == MENU_CYCLE_TO_NEXT) {
            index++;
            if (index >= g_gearShopAvailableCharacterCount) {
                index = 0;
            }
        } else {
            index--;
            if (index < 0) {
                index = g_gearShopAvailableCharacterCount - 1;
            }
        }
        g_gearShopCurCharacterIndex = index;

        index++;
        for (characterIndex = -1; index != 0; characterIndex++) {
            if (g_Menu->availableCharacters[++characterIndex]) {
                index--;
            }
            characterIndex--;
        }

        GearShopMenuUpdateAndRender();
        g_Menu->unk458[1]->unk12 = 0;
        func_801E8030(1);
        GearShopMenuUpdateAndRender();
        func_801CF9BC(g_GameState.characters[characterIndex].gearId, 1);
        g_gearShopCurrentGearId = g_GameState.characters[characterIndex].gearId;
        func_801CFAB8(1, g_GameState.characters[characterIndex].gearId);
        GearShopMenuUpdateAndRender();
    }
}

// GearShopMenuUpdate ??? MenuExplanationGraphics
void func_801D04E8(u8 renderContext) {
    int i;

    g_Menu->pShop->explanationsLen = 0;
    for(i = 0; i < 4; i++) {
        g_Menu->pShop->explanationsLen += func_8002675C(
            g_Menu->resources,
            D_801D6D08[(renderContext*4) + i],
            &g_Menu->pShop->polysExplanations[g_Menu->pShop->explanationsLen*2],
            g_Menu->renderContext,
            D_801D6D14[(renderContext*4) + i],
            D_801D6D3C[(renderContext*4) + i],
            0x1000
        );

    }

    g_Menu->pShop->explanationsRenderCtx = g_Menu->renderContext;
}

// GearShopMenuUpdate ??? MenuExplanationGraphics
void func_801D05EC(void) {
    int i;

    g_Menu->pShop->explanationsLen = 0;

    for(i = 0; i < 2; i++) {
        g_Menu->pShop->explanationsLen += func_8002675C(
            g_Menu->resources,
            D_801D6D10[i],
            &g_Menu->pShop->polysExplanations[g_Menu->pShop->explanationsLen*2],
            g_Menu->renderContext,
            D_801D6D34[i],
            D_801D6D5C[i],
            0x1000
        );
    }

    g_Menu->pShop->explanationsRenderCtx = g_Menu->renderContext;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D06D8);

// GearShopMenuSetFinalPriceGraphics ?
void func_801D0C20(int number, u8 arg1) {

    s32 i;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0x68;
    var_s2 = 0x54;
    if (arg1) {
        var_s1 = 0x50;
        var_s2 = 0x64;
    }
    i = 0;
    GearShopMenuParseNumberToString(number);
    g_Menu->pShop->finalPriceStrLen = 0;
    for(i = 0; i < MENU_MAX_DIGITS; i++) {
        if (g_Menu->digits[i] != 0xFF) {
            g_Menu->pShop->finalPriceStrLen += func_8002675C(
                g_Menu->resources,
                g_Menu->digits[i],
                &g_Menu->pShop->polysFinalPrice[g_Menu->pShop->finalPriceStrLen*2],
                g_Menu->renderContext,
                var_s1 + 3,
                var_s2,
                0x1000
            );
        }
        var_s1 += 8;
    }
    g_Menu->pShop->finalPriceRenderCtx = g_Menu->renderContext;
    g_Menu->pManager->unk5B = 2;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D0D4C);

void func_801D0EC8(u8 arg0) {
    int i;

    g_Menu->pManager->unk5A = 0;
    g_Menu->pShop->unk46A7 = 0;
    g_Menu->pShop->unk46B5 = 0;
    g_Menu->pShop->unk46B2 = 0;
    g_Menu->pShop->explanationsLen = 0;
    g_Menu->pShop->unk46A9 = 0;
    g_Menu->pShop->numPortraits = 0;
    for(i = 0; i < 9; i++) {
        g_Menu->pShop->unk469C[i] = 0;
        g_Menu->pShop->unk46BC[i] = 0;
        g_Menu->pShop->unk46C5[i] = 0;
    }
    for(i = 0; i < 8; i++) {
        g_Menu->pShop->unk4684[i] = 0;
        g_Menu->pShop->unk468C[i] = 0;
    }

    g_Menu->pShop->unk46B6[0] = 0;
    if (arg0) {
        GearShopMenuFreeWindow(2);
        GearShopMenuFreeWindow(3);
        GearShopMenuFreeScrollBarHandle();
        GearShopMenuFreeArrowCursor(0);
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D1078);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D1304);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D18F8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D1F20);

// Spawn and run the logic for a sell menu
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", GearShopMenuSellMenu);

void GearShopMenuSellWeaponsMenu(void) {
    GearShopMenuSellMenu(
        0x96,
        g_GameState.unk221A,
        g_GameState.unk2184,
        3, 1,
        g_GameState.unk2184,
        0
    );
}

void GearShopMenuSellPartsMenu(void) {
    GearShopMenuSellMenu(
        0x64,
        g_GameState.unk2120,
        g_GameState.unk20BC,
        4, 1,
        g_GameState.unk20BC,
        0
    );
}

void GearShopMenuSellModeMenuHandleSelectedOption(u_char offset) {
    int choice;
    u8 unkBool = 1;
    g_Menu->pManager->unk4 = 0;
    g_Menu->pManager->unk3 = 0;
    g_Menu->pManager->unkA = 0;
    func_801CCEBC(4, g_Menu->pManager->unkC);

    // Here, subMenuChoice 0 and 1 correspond to Weapons and Parts
    choice = g_Menu->subMenuChoice + (offset * 3);

    // The functions here goes into and will run the actual sell menus
    switch (choice) {
        case MENU_CHOICE_WEAPONS:
            GearShopMenuSellWeaponsMenu();
            break;

        case MENU_CHOICE_PARTS:
            GearShopMenuSellPartsMenu();
            break;
    }

    func_801D0EC8(unkBool);
    g_Menu->pManager->unkA = 1;
    g_Menu->pManager->unk4 = 1;
    g_Menu->pManager->unk3 = 1;
    func_801CCE90(4, g_Menu->unk6E0, &D_801D6A24, g_Menu->pManager->unkC);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D2950);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D2B74);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D3558);

u8 func_801D3A3C(u8* index, u8* haystack, s32 size, u8 needle) {
    int i;
    u8 result = 0;

    for(i = 0; i < size; i++) {
        if(index[i] == needle) {
            result = haystack[i];
            break;
        }
    }

    return result;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D3A80);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D3C78);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D44FC);

u8 func_801D4888(s32 itemId) {
    u8 equipped;
    u8 itemType = g_Menu->shopItemTypes[itemId];
    u8 result = TRUE;

    switch(itemType) {
        case 0:
            equipped = g_GameState.gears[g_gearShopCurrentGearId].armorId;
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
        case 1:
            equipped = g_GameState.gears[g_gearShopCurrentGearId].frameId;
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
        case 2:
            equipped = g_GameState.gears[g_gearShopCurrentGearId].engineId;
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
    }

    return result;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D498C);

// Handles the logic for the "Fuel" option under "Tune up"
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D5398);

u_char func_801D573C(void) {
    g_Menu->pManager->unk4 = 0;
    g_Menu->pManager->unk3 = 0;
    func_801CCEBC(4, g_Menu->pManager->unkC);
    func_801D0EC8(0);
    return 2;
}

// Called if we chose "Tune up", dispatches into the correct menu based on
// the submenu choice
void func_801D57A8(void) {
    switch(g_Menu->subMenuChoice) {
        case MENU_CHOICE_ARMOR:
        case MENU_CHOICE_FRAME:
        case MENU_CHOICE_ENGINE:
            func_801D498C(0, 1);
            func_801D6150(g_Menu->pDressingRoom, g_gearShopCurrentGearId);
            break;
        case MENU_CHOICE_FUEL:
            func_801D5398();
    }
}

// https://decomp.me/scratch/7SJpB - Main logic for submenus
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D5828);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D5D38);

void func_801D5EB8(void) {
    while (g_Menu->transitionEffectState != 0) {
        GearShopMenuUpdateAndRender();
    }

    D_801D697C = 0;
    g_Menu->pManager->unk5C[7] = 0;
    GearShopMenuUpdateAndRender();
    func_801E7FD4();
    g_Menu->unk458[0]->unk12 = 0;
    g_Menu->unk458[1]->unk12 = 0;
    HeapFree(g_Menu->unk458[0]);
    HeapFree(g_Menu->unk458[1]);
}

void func_801D5F94(MenuDressingRoom* pView, u_char gearId) {
    GameGear* pGear;
    GameCharacter* pPilot;
    u_short ether;
    int etherModifier;

    if(g_GameState.unk22B6 & 0x1000) {
        D_801D70FD = 0xA;
    }

    pGear = &g_GameState.gears[gearId];
    pPilot = &g_GameState.characters[D_801D70F4[gearId]];

    pView->hp = pGear->hp;
    pView->maxHp = pGear->maxHp;
    pView->totalDefense = pGear->baseDefense + pGear->defenseFromEquipment;

    pView->totalEtherDefense = pPilot->etherDefense + pPilot->etherDefenseFromEquipment + pGear->etherDefenseFromEquipment + pGear->baseEtherDefense;
    pView->totalWeight = pGear->weight + pGear->weightFromEquipment;
    pView->unkAA = pGear->unk6A;
    pView->fuel = pGear->fuel;
    pView->maxFuel = pGear->maxFuel;

    ether = pGear->engineOutput * (pGear->unk74 + pGear->unk56);

    if(gearId == 0x5 || gearId == 0xD) {
        etherModifier = ((pGear->maxEther + pGear->unk22) * 6) / 10;
        pView->unkB0 = etherModifier + ether;
    } else {
        pView->unkB0 = pGear->maxEther + ether;
    }

    pView->totalResponsiveness = pGear->unk9F + pGear->responsiveness;
    pView->unkB3 = pGear->unk98 - pGear->unk4A;
    pView->unkB4 = pGear->unk9E;
    pView->unkB5 = pGear->unk9D;
    pView->unkB6 = pGear->unk9C;
}

void func_801D6150(MenuDressingRoom* arg0, u8 arg1) {
    func_801D61B8(arg0, arg1);
    func_801D62A4(arg0, arg1);
    func_801D6250(arg0, arg1);
    func_801D6334(arg0, arg1);
    func_801D6738(arg0, arg1);
}

void func_801D61B8(MenuDressingRoom* arg0, u_char gearIndex) {
    GameGear* pGear;
    GearFrame* pPreview;
    u_char previewId;

    pGear = &g_GameState.gears[gearIndex];
    pPreview = arg0->pGearFrames;
    previewId = pGear->frameId;
    pPreview = &pPreview[previewId];

    pGear->maxHp = pPreview->hp;

    pGear->weight = pPreview->weight;
    pGear->unk98 = pPreview->unk14;
    pGear->unk9E = pPreview->unk15;
    pGear->unk9D = pPreview->unk16;
    pGear->unk9F = pPreview->unk17;
    if (pGear->maxHp < pGear->hp) {
        pGear->hp = pGear->maxHp;
    }
}

void func_801D6250(MenuDressingRoom* menu, u_char gearIndex) {
    GameGear* pGear;
    GearArmor* itemList;
    GearArmor* pItem;

    pGear = &g_GameState.gears[gearIndex];
    itemList = menu->pGearArmor
;
    pItem = &itemList[pGear->armorId];

    pGear->baseDefense = pItem->unk8;
    pGear->baseEtherDefense = pItem->unkA;
}

void func_801D62A4(MenuDressingRoom* shopInfo, u8 gearId) {
    GameGear* pGear;
    GearEngine *item;
    u16 fuel;
    u8 itemId;

    pGear = &g_GameState.gears[gearId];
    itemId = pGear->engineId;
    item = shopInfo->pGearEngines;
    fuel = pGear->fuel;
    item = &item[itemId];

    pGear->maxFuel = item->maxFuel;
    pGear->engineOutput = item->powerOutput;
    pGear->unk3D = item->unkD;
    pGear->unk3E = item->unkE;
    pGear->unk3F = item->unkE;

    if (pGear->maxFuel < fuel) {
        pGear->fuel = pGear->maxFuel;
    }
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D6334);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/render", func_801D6738);

s32 func_801D690C(u8 index) {
    GameGear* pGear;
    s32 temp_v0;
    u8 result;

    pGear = &g_GameState.gears[index];
    temp_v0 = (s32) ((pGear->weightFromEquipment / 120) - pGear->unk75) / 2;
    result = temp_v0;
    if (temp_v0 << 16 < 0) {
        result = 0;
    }
    return result;
}
