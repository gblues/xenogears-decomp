#include "common.h"
#include "system/menu.h"
#include "system/controller.h"
#include "system/archive.h"
#include "system/graphics.h"
#include "system/debug.h"
#include "util/copyspec.h"
#include "gear_shop/gear_shop.h"

// TODO: remove once matched
void func_801D2950(u8, u8);
s32 func_801D2B74(s32, u32, u8*);

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
    g_Menu->menuUnk8->unk1ED9 = 3;
    g_Menu->menuUnk8->unk1EDA = 3;
    g_Menu->menuUnk8->unk1EDB = 3;
    g_Menu->menuUnk8->unk1EDC = 0;
    g_Menu->menuUnk8->unk1EDD = 0;
    g_Menu->menuUnk8->unk1EDE = 0;
    g_Menu->menuUnk8->unk1EDF = 0;
    g_Menu->pManager->unk5C[9] = 1;

    pushXYZ(
         0x400, 0, -0x400,
        &g_gearShopTransitionState.target.cameraX,
        &g_gearShopTransitionState.target.cameraY,
        &g_gearShopTransitionState.target.gearY,
        &g_gearShopTransitionState.start.cameraX,
        &g_gearShopTransitionState.start.cameraY,
        &g_gearShopTransitionState.start.gearY

    );

    func_801CB690(g_gearShopTransitionState.start.cameraX, g_gearShopTransitionState.start.cameraY);
    g_Menu->transitionEffectState = MENU_OPEN_ANIMATION|MENU_CLOSE_ANIMATION|MENU_CLOSE_ANIMATION_START;
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

void func_801D3558(s32* pDelta, s8* pIsImprovement, u8 itemId, u8 itemType, u8 characterId) {
    s16 oldValue[2];
    s16 newValue[2];
    u8 itemSlots[8];

    u8 gearId;
    u8 changeDetected;
    int i;
    u32 smallest;
    u8 leastDefense = 0xFF;
    GearAccessory* pAccessory;
    GearWeapon* pWeaponList;
    GearAccessory* pCurAccesory;


    gearId = g_GameState.characters[characterId].gearId;

    itemSlots[0] = g_GameState.gears[gearId].weaponId;

    itemSlots[1] = g_GameState.gears[gearId].unk4[0];
    itemSlots[2] = g_GameState.gears[gearId].unk4[1];
    itemSlots[3] = g_GameState.gears[gearId].unk4[2];
    itemSlots[4] = g_GameState.gears[gearId].unk4[3];

    itemSlots[5] = g_GameState.gears[gearId].accessorySlots[0];
    itemSlots[6] = g_GameState.gears[gearId].accessorySlots[1];
    itemSlots[7] = g_GameState.gears[gearId].accessorySlots[2];

    switch(itemType) {
        case ITEM_TYPE_GEAR_WEAPON:
            // This **may** be a check to see if the weapon belongs to Billy or not,
            // since Billy uses guns w/ ammo which needs special handling? This should be double checked though.
            if (itemId < 0x32) {
                g_GameState.gears[gearId].weaponId = itemId;
            } else {
                pWeaponList = g_Menu->pDressingRoom->pGearWeapons;

                for(i = 0; i < 4; i++) {
                    if(g_Menu->pDressingRoom->pGearWeapons[g_GameState.gears[gearId].unk4[i]].unkF == pWeaponList[itemId].unkF) {
                        g_GameState.gears[gearId].unk4[i] = itemId;
                    }
                }
            }
            break;
        case ITEM_TYPE_GEAR_ACCESSORY:
            changeDetected = TRUE;
            pAccessory = &g_Menu->pDressingRoom->pGearAccessories[itemId];

            for (i = 0; i < 3; i++) {
                int index = itemSlots[5+i];
                pCurAccesory = &g_Menu->pDressingRoom->pGearAccessories[index];

                if (pCurAccesory->unk8 && pCurAccesory->unk8 == pAccessory->unk8) {
                    changeDetected = FALSE;
                    g_GameState.gears[gearId].accessorySlots[i] = itemId;
                }
            }

            leastDefense = 0xFF;
            if (changeDetected) {
                for (i = 0; i < 3; i++) {
                    int index = itemSlots[5+i];
                    pCurAccesory = &g_Menu->pDressingRoom->pGearAccessories[index];
                    if (leastDefense >= pCurAccesory->defense) {
                        leastDefense = pCurAccesory->defense;
                        smallest = i;
                    }
                }
                g_GameState.gears[gearId].accessorySlots[smallest] = itemId;
            }
            break;
    }

    func_801D6150(g_Menu->pDressingRoom, g_GameState.characters[characterId].gearId);
    func_801D5F94(g_Menu->pDressingRoom, g_GameState.characters[characterId].gearId);

    oldValue[0] = g_Menu->pDressingRoom->unkB0;
    oldValue[1] = g_Menu->pDressingRoom->totalDefense;
    newValue[0] = g_Menu->pShop->unk46E0[characterId];
    newValue[1] = g_Menu->pShop->unk4700[characterId];

    for(i = 0; i < 2; i++) {
        if(oldValue[i] >= newValue[i]) {
            pDelta[i] = oldValue[i] - newValue[i];
            pIsImprovement[i] = FALSE;
        } else {
            pDelta[i] = newValue[i] - oldValue[i];
            pIsImprovement[i] = TRUE;
        }
    }

    g_GameState.gears[gearId].weaponId = itemSlots[0];
    g_GameState.gears[gearId].unk4[0] = itemSlots[1];
    g_GameState.gears[gearId].unk4[1] = itemSlots[2];
    g_GameState.gears[gearId].unk4[2] = itemSlots[3];
    g_GameState.gears[gearId].unk4[3] = itemSlots[4];
    g_GameState.gears[gearId].accessorySlots[0] = itemSlots[5];
    g_GameState.gears[gearId].accessorySlots[1] = itemSlots[6];
    g_GameState.gears[gearId].accessorySlots[2] = itemSlots[7];

    func_801D6150(g_Menu->pDressingRoom, g_GameState.characters[characterId].gearId);
}

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

s32 func_801D3C78(s32 rowIndex, s32 scrollOffset, u8 *unused) {
    int currentItem = scrollOffset + rowIndex;

    u8 gearId;
    u8 *pStringBuffer;
    int price, totalPrice;
    u8 itemId = g_Menu->shopItemIDs[currentItem];
    u8 itemType = g_Menu->shopItemTypes[currentItem];
    int i, j, currentSlot;
    RECT rect;
    int sp28[2];
    u8 sp30[2];
    GearArmor *pArmor;
    GearFrame *pFrame;
    GearEngine *pEngine;
    GearWeapon *pWeapon;
    GearAccessory *pAccessory;
    int equipFlags;
    int xPos;

    pStringBuffer = HeapAlloc(0x618, 0);
    bzero(pStringBuffer, 0x618);

    equipFlags = 0;
    switch(itemType) {
        case ITEM_TYPE_GEAR_ARMOR:
            g_Menu->pShop->strItemDesc.width = SystemRenderStringEntry(GetStringEntry(g_Menu->pShop->pGearFrameDescriptions, itemId), (u32* ) pStringBuffer, 0x39U, 0U);
            pArmor = &g_Menu->pDressingRoom->pGearArmor[itemId];

            price = pArmor->price;
            equipFlags = pArmor->equipFlags;
            break;
        case ITEM_TYPE_GEAR_FRAME:
            g_Menu->pShop->strItemDesc.width = SystemRenderStringEntry(GetStringEntry(g_Menu->pShop->pGearEngineDescriptions, itemId), (u32* ) pStringBuffer, 0x39U, 0U);
            pFrame = &g_Menu->pDressingRoom->pGearFrames[itemId];
            price = pFrame->price;
            equipFlags = pFrame->equipFlags;
            break;
        case ITEM_TYPE_GEAR_ENGINE:
            g_Menu->pShop->strItemDesc.width = SystemRenderStringEntry(GetStringEntry(g_Menu->pShop->pAmmoDescriptions, itemId), (u32* ) pStringBuffer, 0x39U, 0U);
            pEngine = &g_Menu->pDressingRoom->pGearEngines[itemId];
            price = pEngine->price;
            equipFlags = pEngine->equipFlags;
            break;
        case ITEM_TYPE_GEAR_WEAPON:
            g_Menu->pShop->strItemDesc.width = SystemRenderStringEntry(GetStringEntry(g_Menu->pShop->pWeaponDescriptions, itemId), (u32* ) pStringBuffer, 0x39U, 0U);
            pWeapon = &g_Menu->pDressingRoom->pGearWeapons[itemId];
            price = pWeapon->price;
            equipFlags = pWeapon->equipFlags;
            break;
        case ITEM_TYPE_GEAR_ACCESSORY:
            g_Menu->pShop->strItemDesc.width = SystemRenderStringEntry(GetStringEntry(g_Menu->pShop->pAccessoryDescriptions, itemId), (u32* ) pStringBuffer, 0x39U, 0U);
            pAccessory = &g_Menu->pDressingRoom->pGearAccessories[itemId];
            price = pAccessory->price;
            equipFlags = pAccessory->equipFlags;
            break;
    }

    totalPrice = func_801D1078(itemId, itemType);
    setRECT(&rect, 0x140, 0x4E, 0x3C, 0xD);
    LoadImage(&rect, (u32 *)pStringBuffer);
    DrawSync(0);
    func_801C5CA8(&g_Menu->pShop->strItemDesc, 0, 0, 0U);
    func_801C51B8(&g_Menu->pShop->strItemDesc.polys[g_Menu->renderContext], 0x2C, 0x12, 0, 0x4E, (s32) g_Menu->pShop->strItemDesc.width, 0xD);
    GearShopMenuSetVertices(g_Menu->pShop->strItemDesc.vertices, 0x2C, 0x12, g_Menu->pShop->strItemDesc.width, 0xD);

    g_Menu->pShop->strItemDesc.renderContext = g_Menu->renderContext;
    HeapFree(pStringBuffer);
    if(itemId) {
        g_Menu->pShop->unk46A7 = TRUE;
    } else {
        g_Menu->pShop->unk46A7 = FALSE                                ;
    }

    g_Menu->pShop->unk46A9 = 0;

    xPos = 0x49;
    for(i = 0, currentSlot = 0; i < 0x10; i++) {
        if(g_Menu->availableCharacters[i] != 0) {
            gearId = g_GameState.characters[i].gearId;
            if(GearShopMenuGearCanEquip(equipFlags, gearId)) {
                g_Menu->pShop->unk469C[currentSlot] = TRUE;
            } else {
                g_Menu->pShop->unk469C[currentSlot] = FALSE;
            }

            if(GearShopMenuGearCanEquip(totalPrice, gearId)) {
                g_Menu->pShop->unk46A9 += func_8002675C(
                    g_Menu->resources,
                    0xE,
                    &g_Menu->pShop->polys2D0[g_Menu->pShop->unk46A9*2],
                    g_Menu->renderContext,
                    D_801D6C44[currentSlot] + 0xE,
                    0xB4,
                    0x1000
                );
            }
            g_Menu->pShop->unk46BC[currentSlot] = 0;
            g_Menu->pShop->unk46C5[currentSlot] = 0;
            if( (u8)(itemType + 0xFD) < 2 && g_Menu->pShop->unk469C[currentSlot]) {
                sp28[1] = 0;
                sp28[0] = 0;
                func_801D3558(&sp28[0], &sp30[0], itemId, itemType, (u8)i);
                if(sp28[0]) {
                    GearShopMenuParseNumberToString(sp28[0]);
                    for(j = 0; j < 3; j++) {
                        if(g_Menu->digits[6+j] != 0xff) {
                            g_Menu->pShop->unk46BC[currentSlot] += func_8002675C(
                                g_Menu->resources,
                                g_Menu->digits[6+j],
                                &g_Menu->pShop->polys27B0[currentSlot][g_Menu->pShop->unk46BC[currentSlot]*2],
                                g_Menu->renderContext,
                                (currentSlot * FONT_LETTER_HEIGHT * 2) + xPos + (8*j),
                                0xBE,
                                0x1000U);
                        }
                    }
                    func_801D0054(g_Menu->pShop->unk46BC[currentSlot], &g_Menu->pShop->polys27B0[currentSlot], sp30[0]);
                    g_Menu->pShop->unk46CE[currentSlot] = g_Menu->renderContext;
                }

                if(sp28[1]) {
                    GearShopMenuParseNumberToString(sp28[1]);
                    for(j = 0; j < 3; j++) {
                        if(g_Menu->digits[6+j] != 0xff) {
                            g_Menu->pShop->unk46C5[currentSlot] += func_8002675C(
                                g_Menu->resources,
                                g_Menu->digits[6+j],
                                &g_Menu->pShop->polys3020[currentSlot][g_Menu->pShop->unk46C5[currentSlot]*2],
                                g_Menu->renderContext,
                                (currentSlot * FONT_LETTER_HEIGHT * 2) + xPos + (8*j),
                                0xC6,
                                0x1000U);
                        }
                    }
                    func_801D0054(g_Menu->pShop->unk46C5[currentSlot], &g_Menu->pShop->polys3020[currentSlot], sp30[1]);
                    g_Menu->pShop->unk46D7[currentSlot] = g_Menu->renderContext;
                }
            }
            currentSlot++;
        }

    }
    g_Menu->pShop->unk46A8 = g_Menu->renderContext;
    func_801D3A80(itemType, itemId);
    return price;
}

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


s32 GearShopMenuPurchaseDialog(u8 arg0, u8 disableQuantitySelection) {
    u8 values[8]; // sp28
    int i; // s0
    u8 *temp; // s0
    u8 continueProcessing = TRUE; // s3
    u8 redrawWindows = TRUE; // sp40
    u8 redrawTransactionSummary = TRUE; // fp
    int rowIndex = 0; // s4
    int newRowIndex = 0xFF; // sp48
    int scrollOffset = 0; // s2
    int newScrollOffset = 0xFF; // sp50
    int cartTotal = 0; // s6
    int current_gold; // sp58
    int newProjectedRemainingFunds; // sp60
    int sellPrice; // sp68
    int salesTotal; // sp70
    u8 purchaseConfirmStringId1; // sp78
    u8 purchaseConfirmStringId2; // sp80
    int unkWindowX; // sp88
    int unkWindowWidth; // sp90
    int numItems; // sp98
    int projectedRemainingFunds; // s5
    int itemPrice; // s7

    current_gold = g_GameState.gold;
    purchaseConfirmStringId1 = 0x8F;
    purchaseConfirmStringId2 = 0xFF;
    unkWindowX = 0xE0;
    projectedRemainingFunds = current_gold;
    newProjectedRemainingFunds = projectedRemainingFunds;
    salesTotal = 0;
    unkWindowWidth = 0x40;
    for(i = 0; i < MAX_GAME_CHARACTERS; i++) {
        if(g_GameState.characters[i].gearId != GEAR_ID_NONE) {
            func_801D6150(g_Menu->pDressingRoom, g_GameState.characters[i].gearId);
            func_801D5F94(g_Menu->pDressingRoom, g_GameState.characters[i].gearId);
            g_Menu->pShop->unk46E0[i] = g_Menu->pDressingRoom->unkB0;
            g_Menu->pShop->unk4700[i] = g_Menu->pDressingRoom->totalDefense;
        }
    }

    bzero(g_Menu->shopItemIDs, MAX_SHOP_ITEMS);
    bzero(g_Menu->shopItemTypes, MAX_SHOP_ITEMS);
    bzero(g_Menu->pShop->curItemQuantities, MAX_SHOP_ITEMS);

    for(i = 0; i < MAX_GEAR_SHOP_ITEMS; i++) {
        u_char *table = (u_char *)g_Menu->pShop->gearShopItemTables;
        g_Menu->shopItemIDs[i] = table[((arg0 * 3) + g_Menu->subMenuChoice) * 20 + i];
        g_Menu->shopItemTypes[i] = (arg0 * 3) + g_Menu->subMenuChoice;
    }

    numItems = g_GearShopInventoryCounts[(arg0 * 3) + g_Menu->subMenuChoice];
    g_Menu->pSelectionMenu->unk1192 = 1;
    GearShopMenuInitializeArrowCursor(0);

     while(continueProcessing) {
        GearShopMenuUpdateAndRender();

        if ((scrollOffset != newScrollOffset) || (redrawTransactionSummary)) {
            if (disableQuantitySelection) {
                sellPrice = func_801D2B74(scrollOffset, newProjectedRemainingFunds, values);
            } else {
                sellPrice = func_801D2B74(scrollOffset, projectedRemainingFunds, values);
            }
            GearShopMenuUpdateScrollBarHandle(12, 50, 60, numItems, scrollOffset);
        }

        if ((rowIndex != newRowIndex) || (scrollOffset != newScrollOffset)) {
            newRowIndex = rowIndex;
            itemPrice = func_801D3C78(rowIndex, scrollOffset, values);
            newScrollOffset = scrollOffset;
            g_Menu->pManager->unk5A = 1;
            if (disableQuantitySelection) {
                unkWindowX = 0xC8;
                projectedRemainingFunds = newProjectedRemainingFunds;
                unkWindowWidth = 0x70; // 112
                redrawTransactionSummary = TRUE;
                cartTotal = 0;
                salesTotal = 0;
                if (values[rowIndex]) {
                    cartTotal = itemPrice;
                    projectedRemainingFunds -= itemPrice;
                    salesTotal = sellPrice;
                    projectedRemainingFunds += sellPrice;
                }
            }
        }

        GearShopMenuUpdateArrowCursor(rowIndex, scrollOffset, 0, 0);

            if (redrawWindows) {
                // void GearShopMenuInitializeWindow(u_char windowIndex, u_short x, u_short y, u_short width, u_short height, u_char shouldInitializeHandle, u8 arg6, int zIndex, u_char hasScrollbar)
                GearShopMenuInitializeWindow(2, 0xC, 0x2A, 0xC4 - (disableQuantitySelection * 0x14), 0x74, 0, 1, 4, 1);
                GearShopMenuInitializeWindow(3, 0x20, 0xE, 0xFCU, 0x14U, 0U, 1, 4, 0);
                GearShopMenuInitializeWindow(5, unkWindowX, 0x7A, unkWindowWidth, 0x24, FALSE, 1, 4, FALSE);
                temp = D_801D6A2C;
                func_801CCE90(2, g_Menu->unk6E0, (s8* ) temp, (s8* ) g_Menu->pManager->unkC);
                func_801CCEE8(2, g_Menu->unk6E0, (s32) temp, D_801D6A40, g_Menu->pManager->unkC, disableQuantitySelection, 0, 1);
                if (disableQuantitySelection) {
                    func_801D2950((g_Menu->subMenuChoice + (arg0 * 3)), arg0);
                }
                GearShopMenuUpdateCharacterPortraits();
                func_801D04E8(disableQuantitySelection);
                redrawWindows = FALSE;
            }

        if (redrawTransactionSummary) {
            func_801D06D8(current_gold, cartTotal, projectedRemainingFunds, salesTotal, disableQuantitySelection);
            redrawTransactionSummary = FALSE;
        }
        switch (g_Menu->input) {
            case MENU_INPUT_CONFIRM:

                if (cartTotal != 0) {
                    GearShopMenuPlaySoundEffect(MENU_SOUND_CONFIRM);
                    g_Menu->pManager->unk5A = FALSE;
                    g_Menu->pManager->shouldRenderWindow[2] = FALSE;
                    g_Menu->pManager->shouldRenderWindow[3] = FALSE;
                    g_Menu->pManager->scrollHandleActive = FALSE;
                    g_Menu->pManager->shouldRenderArrowCursor[0] = FALSE;
                    g_Menu->pManager->shouldRenderWindow[5] = FALSE;
                    continueProcessing = FALSE;
                    g_Menu->pManager->unkC[disableQuantitySelection] = FALSE;
                    if (disableQuantitySelection) {
                        if (func_801D4888(scrollOffset + rowIndex) & 0xFF) {
                            purchaseConfirmStringId1 = MENU_STRING_CONFIRM_PURCHASE;
                        } else {
                            purchaseConfirmStringId1 = MENU_STRING_NOT_AN_UPGRADE;
                            purchaseConfirmStringId2 = MENU_STRING_BUY_ANYWAY;
                        }
                    } else {
                        func_801D0C20(cartTotal, 0);
                    }
                    GearShopMenuInitializePointerCursors(0);
                    if (GearShopMenuShowModal(purchaseConfirmStringId1, purchaseConfirmStringId2, TRUE) != MENU_CHOICE_NO) {
                        if (disableQuantitySelection) {
                            g_Menu->pShop->curItemQuantities[scrollOffset + rowIndex] = 1;
                        }
                        func_801D44FC(projectedRemainingFunds);
                    } else {
                        continueProcessing = TRUE;
                        g_Menu->pManager->shouldRenderWindow[2] = TRUE;
                        g_Menu->pManager->shouldRenderWindow[3] = TRUE;
                        g_Menu->pManager->shouldRenderWindow[5] = TRUE;
                        g_Menu->pManager->unkC[disableQuantitySelection] = TRUE;
                        g_Menu->pManager->scrollHandleActive = TRUE;
                        newScrollOffset = 0xFF;
                        newRowIndex = 0xFF;
                        g_Menu->pManager->shouldRenderArrowCursor[0] = TRUE;
                    }
                    GearShopMenuFreePointerCursors();
                    purchaseConfirmStringId2 = 0xFF;
                } else {
                    GearShopMenuPlaySoundEffect(MENU_SOUND_ERROR);
                }
                break;
            case MENU_INPUT_BACK:
                g_Menu->pManager->shouldRenderWindow[5] = FALSE;
                continueProcessing = FALSE;
                g_Menu->pManager->unkC[disableQuantitySelection] = 0;
                if(cartTotal && !disableQuantitySelection) {
                    g_Menu->pManager->unk5A = 0;
                    g_Menu->pManager->shouldRenderWindow[2] = 0;
                    g_Menu->pManager->shouldRenderWindow[3] = 0;
                    g_Menu->pManager->scrollHandleActive = 0;
                    g_Menu->pManager->shouldRenderArrowCursor[0] = 0;
                    GearShopMenuInitializePointerCursors(0U);
                    // display the "Cancel all purchases?" modal; returns 1 for "yes" and 0 for "no"
                    if (GearShopMenuShowModal(MENU_STRING_CANCEL_ALL_PURCHASES, MENU_STRING_NONE, TRUE) == MENU_CHOICE_NO) { // user chose "no" so reactivate the windows and keep on
                        continueProcessing = TRUE;
                        g_Menu->pManager->shouldRenderWindow[2] = 1;
                        g_Menu->pManager->shouldRenderWindow[3] = 1;
                        g_Menu->pManager->shouldRenderWindow[5] = 1;
                        g_Menu->pManager->unkC[0] = 1;
                        g_Menu->pManager->scrollHandleActive = 1;
                        newScrollOffset = 0xFF;
                        newRowIndex = 0xFF;
                        g_Menu->pManager->shouldRenderArrowCursor[0] = 1;

                    }
                    GearShopMenuFreePointerCursors();
                }
                break;
            case MENU_INPUT_DOWN:
                rowIndex += 1;

                if (rowIndex >= 8) {
                    rowIndex = 7;
                    scrollOffset += 1;
                    if ((numItems - 8) < scrollOffset) {
                        scrollOffset -= 1;
                    }
                }
                break;
            case MENU_INPUT_UP:
                rowIndex -= 1;

                if (rowIndex < 0) {
                    scrollOffset -= 1;
                    rowIndex = 0;
                    if (scrollOffset < 0) {
                        scrollOffset = 0;
                    }
                }
                break;
            case MENU_INPUT_RIGHT:
                if(values[rowIndex]) {
                if(!disableQuantitySelection) {
                    if ((g_Menu->pShop->curItemQuantities[scrollOffset + rowIndex] + 1 + (g_gearShopCurrentItemQuantityHeld)) <= MAX_ITEM_QUANTITY) {
                        cartTotal += itemPrice;
                        projectedRemainingFunds -= itemPrice;
                        redrawTransactionSummary = TRUE;
                        g_Menu->pShop->curItemQuantities[scrollOffset + rowIndex]++;
                    }
                }
                }

                break;
            case MENU_INPUT_LEFT:
                if(!disableQuantitySelection) {
                    if(g_Menu->pShop->curItemQuantities[scrollOffset+rowIndex]) {
                        cartTotal -= itemPrice;
                        projectedRemainingFunds += itemPrice;
                        redrawTransactionSummary = TRUE;
                        g_Menu->pShop->curItemQuantities[scrollOffset+rowIndex] += 0xFF;
                    }
                }
                break;
        }
    }
    g_Menu->pShop->unk4785 = 0;
    GearShopMenuFreeWindow(5);
    func_801CCEBC(2, (s8* ) g_Menu->pManager->unkC);
    func_801D0EC8(1);
    return 1;
}

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
            GearShopMenuPurchaseDialog(0, 1);
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

    ether = pGear->engineOutput * (pGear->attackPower + pGear->unk56);

    if(gearId == 0x5 || gearId == 0xD) {
        etherModifier = ((pGear->maxEther + pGear->unk22) * 6) / 10;
        pView->unkB0 = etherModifier + ether;
    } else {
        pView->unkB0 = pGear->maxEther + ether;
    }

    pView->totalResponsiveness = pGear->unk9F + pGear->responsiveness;
    pView->unkB3 = pGear->agility - pGear->unk4A;
    pView->unkB4 = pGear->etherAmplification;
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
    pGear->agility = pPreview->unk14;
    pGear->etherAmplification = pPreview->unk15;
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
