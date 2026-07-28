#include "common.h"
#include "system/menu.h"
#include "system/controller.h"
#include "system/archive.h"
#include "system/graphics.h"
// probably something like: DEBUGGER_ATTACHED, guards a breakpoint left in the code
extern s32* D_8005917C; // TODO: should be in a header for main program stuff since this is not coming from an overlay

extern s8  D_801D697C;
extern int D_801D69A0;
extern int D_801D69A4;
extern u8  D_801D6A20;
extern int D_801D6A60[4];
extern int D_801D6A70[4];
extern u32 D_801D6A80;
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
extern u8  D_801D9084;
extern s32 GEAR_SHOP_AVAILABLE_CHARACTER_COUNT;
extern u8* D_801D9088;

u8 func_8001BD40(int, u8);
u16 GearShopMenuIsCharacterFlagSet(uint, u_char);
void func_801D2054(u8, u8*, u8*, s8, u8, u8 *, u8);
s32 func_801CCA40(u8, u8);
void func_801CC530(u8);
void GearShopMenuSetWindow(u8, u16, u16, u16, u16, u8, s32, u8);
void GearShopMenuSetVertices(SVECTOR*, u32, u32, u32, u32);
void func_801C7E00(u8, u16, u16, u16, u16);
void GearShopMenuInitializeWindowBorderCorners(u8, u16, u16, u16, u16);
void GearShopMenuSetWindowBorderTop(u8, u16, u16, u16);
void GearShopMenuSetWindowBorderBottom(u8, u16, u16, u16, u16);
void GearShopMenuSetWindowBorderLeft(u8, u16, u16, u16);
void GearShopMenuSetWindowBorderRight(u8, u16, u16, u16, u16);

s32 func_8002675C(MenuResourceDirectory*, s32, POLY_FT4 *, s32, s32, s32, u32);

/* this function doesn't seem to get called by anything, possibly dead code? I spent a little time decomping this
 * and got it to 94% but don't want to spend a ton of time on it.
 *
 * https://decomp.me/scratch/t631n
 */
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C511C);

void func_801C51B8(POLY_FT4* quad, s16 x, s16 y, s8 u, s8 v, s16 width, s16 height) {
    setXY4(quad,
        x, y,
        x + width, y,
        x, y + height,
        x + width, y + height
    );
    setUV4(quad,
        u, v,
        u + width, v,
        u, v + height,
        u + width, v + height
    );
}

u16 GearShopMenuIsCharacterFlagSet(u32 arg0, u8 arg1) {
    return D_801D6C68[arg1] & arg0;
}

u16 GearShopMenuGetCharacterBitMask(s32 index) {
    return D_801D6C68[(u8)index];
}

s32 func_801C5260(u8 count) {
    return D_801D6C88[count];
}

s32 func_801C527C(s32 arg0, u8 arg1) {
    return arg0 & D_801D6C88[arg1];
}

/* 801C5298 */void GearShopMenuParseNumberToString(u32 amount) {
    u32 place = 100000000;
    int i;

    for(i = 0; i < 9; i++) {
        g_Menu->digits[i] = amount / place;
        amount = amount % place;
        place /= 10;
    }

    for(i = 1; i < 9; i++) {
        if(g_Menu->digits[i] == 0) {
            g_Menu->digits[i-1] = -1;
        } else {
            if(g_Menu->digits[i-1] == 0) {
                g_Menu->digits[i-1] = -1;
            }
            break;
        }
    }
}

/**
 * Manages the memory allocation for MenuUnk2 in the system menu (g_Menu).
 *
 * @param isInitialization determines action taken; valid values are either MENU_DATA_INITIALIZE or MENU_DATA_FREE
 */
/* 0x801C5344 */void GearShopMenuMenuUnk2Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk2 = HeapAlloc(sizeof(MenuUnk2), 0);
        bzero(g_Menu->menuUnk2, sizeof(MenuUnk2));
        return;
    }
    HeapFree(g_Menu->menuUnk2);
}

/* 801C53A8 */void GearShopMenuMenuManagerManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pManager = HeapAlloc(sizeof(MenuManager), 0);
        bzero(g_Menu->pManager, sizeof(MenuManager));
        return;
    }
    HeapFree(g_Menu->pManager);
}

/* 801C540C */ void GearShopMenuSelectionMenuManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pSelectionMenu = HeapAlloc(sizeof(MenuSelectionMenu), 0);
        bzero(g_Menu->pSelectionMenu, sizeof(MenuSelectionMenu));
        return;
    }
    HeapFree(g_Menu->pSelectionMenu);
}

/* 801C5470 */ void GearShopMenuMenuUnk5Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk354 = HeapAlloc(sizeof(MenuUnk5), 0);
        bzero(g_Menu->unk354, sizeof(MenuUnk5));
        return;
    }
    HeapFree(g_Menu->unk354);
}

/* 801C54D4 */ void GearShopMenuMenuUnk6Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk330 = HeapAlloc(sizeof(MenuUnk6), 0);
        bzero(g_Menu->unk330, sizeof(MenuUnk6));
        return;
    }
    HeapFree(g_Menu->unk330);
}

/* 801C5538 */ void GearShopMenuMenuUnk1Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk348 = HeapAlloc(sizeof(MenuUnk1), 0);
        bzero(g_Menu->unk348, sizeof(MenuUnk1));
        return;
    }
    HeapFree(g_Menu->unk348);
}

/* 801C559C */ void GearShopMenuMenuUnk7Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk1E20 = HeapAlloc(sizeof(MenuUnk7), 0);
        bzero(g_Menu->unk1E20, sizeof(MenuUnk7));
        return;
    }
    HeapFree(g_Menu->unk1E20);
}

/* 801C5600 */ void GearShopMenuMenuShopManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pShop = HeapAlloc(sizeof(MenuShop), 0);
        bzero(g_Menu->pShop, sizeof(MenuShop));
        return;
    }
    HeapFree(g_Menu->pShop);
}

/* 801C5664 */ void GearShopMenuMenuUnk8Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk8 = HeapAlloc(sizeof(MenuUnk8), 0);
        bzero(g_Menu->menuUnk8, sizeof(MenuUnk8));
        return;
    }
    HeapFree(g_Menu->menuUnk8);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", GearShopMenuLoadResources);

/* 801C5B08 */ void GearShopMenuFilterPartyMembers(void) {
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
        if( GearShopMenuIsCharacterFlagSet(masked_bits, i) > 0 && g_GameState.characters[i].gearId != 0xFF ) {
            g_Menu->availableCharacters[i] = TRUE;
        } else {
            g_Menu->availableCharacters[i] = FALSE;
        }
    }

    /* filter by current party */
    for(i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if( g_GameState.partyMembers[i] != 0xFF && g_Menu->availableCharacters[g_GameState.partyMembers[i]]) {
            g_Menu->pManager->currentCharacterIDs[i] = g_GameState.partyMembers[i];
        } else {
            g_Menu->pManager->currentCharacterIDs[i] = 0xFF;
        }
    }

    GearShopMenuLoadResources();
}


void GearShopMenuResetRenderContext(void) {
    g_Menu->renderContext = 0;
}

void func_801C5CA8(MenuString *menuString, s32 arg1, s32 arg2, u8 attributes) {
    s32 tpage_offset;
    int i;
    POLY_FT4* quad;

    for (i = 0; i < 2; i++) {
        quad = &menuString->polys[i];
        tpage_offset = 0;

        SetPolyFT4(quad);
        SetSemiTrans(quad, 0);
        SetShadeTex(quad, 0);
        setRGB0(quad, 0x80, 0x80, 0x80);

        if (!attributes) {
            menuString->unk7C = (arg1 & 1);
            setTPage(quad, 0, 0, 0x140, 0);

#define texCoordV  (((arg1 + arg2) / 4) * 13)
#define texCoordU  (((arg1 / 2) & 1) << 7)

            setUV4(
                quad,
                texCoordU,               texCoordV,
                texCoordU + menuString->width, texCoordV,
                texCoordU,               texCoordV + 13,
                texCoordU + menuString->width, texCoordV + 13
            );
#undef texCoordV
#undef texCoordU
        } else {
            if (!(attributes & 0x80)) {
                tpage_offset = 0x20;
                SetSemiTrans(quad, 1);
                setRGB0(quad, tpage_offset, tpage_offset, tpage_offset);
            }

            menuString->unk7C = (attributes & 0x7F) + 0xFF;
            setTPage(quad, 0, 0, 0x180, 0x80);
            quad->tpage = tpage_offset | quad->tpage;

#define texCoordU ((arg1 & 1) * 0x60)
#define texCoordV (((arg1 / 2) * 13) + arg2)

            setUV4(
                quad,
                texCoordU,               texCoordV,
                texCoordU + menuString->width, texCoordV,
                texCoordU,               texCoordV + 13,
                texCoordU + menuString->width, texCoordV + 13
            );
#undef texCoordV
#undef texCoordU
        }
        menuString->polys[i].clut = menuString->unk7C ? g_SystemPalette2 : g_SystemPalette1;
    }

    menuString->unk7F = 0;
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5EE8);

void func_801C6098(void) {

    u32* imgptr;
    RECT rect;
    u8 dummy[2];

    imgptr = HeapAlloc(0x20U, 0U);
    bzero(imgptr, 0x20);
    ((u16 *)imgptr)[1] = 0x7fff;

    rect.x = 0;
    rect.y = 0x1C0;
    rect.w = 0x10;
    rect.h = 1;

    LoadImage(&rect, imgptr);
    DrawSync(0);
    HeapFree(imgptr);
}

/* initMenuGeometry() ? */
void func_801C6114(void) {
    SystemTransferPaletteToVRAM(0, 0x1D1);
    g_Menu->unk4E0[0].pVramBuffer = HeapAlloc(0x38E, 0);
    func_801C5EE8(g_Menu->unk4E0, &D_801D6A80, 0, 4);
    func_801C6098();
}

void GearShopMenuInitializeWindowBorders(void) {
    POLY_FT4 unused;

    ResourceHelperGetTexCoords(
        g_Menu->resources, // resource table
        MENU_TEX_WINDOW_BORDER_TOP, // resource index
        &g_Menu->texCount0, // out parameter: length of list @ table[index]
        &g_Menu->texPage0,
        &g_Menu->clutX0,
        &g_Menu->clutY0,
        &g_Menu->texPageX0,
        &g_Menu->texPageY0);
    ResourceHelperGetTexCoords(g_Menu->resources, MENU_TEX_WINDOW_BORDER_BOTTOM, &g_Menu->texCount1, &g_Menu->texPage1, &g_Menu->clutX1, &g_Menu->clutY1, &g_Menu->texPageX1, &g_Menu->texPageY1);
    ResourceHelperGetTexCoords(g_Menu->resources, MENU_TEX_WINDOW_BORDER_LEFT, &g_Menu->texCount2, &g_Menu->texPage2, &g_Menu->clutX2, &g_Menu->clutY2, &g_Menu->texPageX2, &g_Menu->texPageY2);
    ResourceHelperGetTexCoords(g_Menu->resources, MENU_TEX_WINDOW_BORDER_RIGHT, &g_Menu->texCount3, &g_Menu->texPage3, &g_Menu->clutX3, &g_Menu->clutY3, &g_Menu->texPageX3, &g_Menu->texPageY3);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6278);

void func_801C665C(void) {
    g_Menu->pManager->unk4 = 0;
    g_Menu->pManager->unk3 = 0;
}

void func_801C668C(POLY_G4* poly, u8 r, u8 g, u8 b) {
    SetPolyG4(poly);
    setRGB0(poly, r, g, b);
    setRGB1(poly, r, g, b);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6708);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6A54);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6E74);

// TODO: counterpart in ShopMenu uses u_short, but a number of matches break if we define this using u_short here
void GearShopMenuSetVertices(SVECTOR* vertices, u32 x, u32 y, u32 w, u32 h) {
    u16 yOffset = -0x70;
    u16 xOffset = -0xA0;
    s16 x1 = x + w;
    s16 y1 = y + h;

    setVector(vertices, x + xOffset, y + yOffset, 0);
    setVector(vertices+1, x1 - 0xA0, y + yOffset, 0);
    setVector(vertices+2, x + xOffset, y1 - 0x70, 0);
    setVector(vertices+3, x1 - 0xA0, y1 - 0x70, 0);
}

void GearShopMenuSetWindowBorderPrimitive(P_TAG* tag) {
    SetSemiTrans(tag, 1);
    SetShadeTex(tag, 0);
    setRGB0(tag, 128, 128, 128);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C76A4);

void GearShopMenuFreeScrollBarHandle(void) {
    g_Menu->pManager->scrollHandleActive = FALSE;
    HeapFree(g_Menu->pScrollHandle);
}

void GearShopMenuInitializeArrowCursor(u8 index) {
    MenuArrowCursor* cursor;

    cursor = HeapAlloc(sizeof(MenuArrowCursor), 0);
    g_Menu->arrowCursors[index] = cursor;
    bzero((u8* ) cursor, sizeof(MenuArrowCursor));
    g_Menu->arrowCursors[index]->curAnimFrame = 4;
    g_Menu->arrowCursors[index]->animFrameDuration = 0;
}

void GearShopMenuUpdateArrowCursor(s32 arg0, s32 arg1, u8 arg2, u8 cursorId) {
    POLY_FT4 *poly;
    MenuArrowCursor *cursor = g_Menu->arrowCursors[cursorId];
    int lineHeight;
    u8 shouldRenderCursor;

    if( ++cursor->animFrameDuration >= 6) {
        if(--cursor->curAnimFrame < 0) {
            cursor->curAnimFrame = 4;
        }
        cursor->animFrameDuration = 0;
    }

    if( arg2 == 0) {
        lineHeight = (FONT_LETTER_HEIGHT * arg0) + 50;
        shouldRenderCursor = TRUE;
    }

    if(shouldRenderCursor) {
        func_8002675C(
            g_Menu->resources,
            cursor->curAnimFrame+0x15B,
            &cursor->polys[0],
            g_Menu->renderContext,
            0,
            0,
            0x1000);
        poly = &cursor->polys[g_Menu->renderContext];
        GearShopMenuSetVertices(cursor->vertices,
                      (u16)(poly->x0 + 0x1c),
                      (u16)(poly->y0 + lineHeight),
                      (u16)(poly->x1 - poly->x0),
                      (u16)(poly->y3 - poly->y0));
        cursor->renderContext = g_Menu->renderContext;
        g_Menu->pManager->shouldRenderArrowCursor[cursorId] = TRUE;
        return;
    }
    g_Menu->pManager->shouldRenderArrowCursor[cursorId] = FALSE;
}

void GearShopMenuFreeArrowCursor(u8 cursor) {
    HeapFree(g_Menu->arrowCursors[cursor]);
    g_Menu->pManager->shouldRenderArrowCursor[cursor] = FALSE;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7AE4);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C7E00);

void GearShopMenuInitializeWindowBorderCorners(u8 windowId, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    MenuWindow *window = g_Menu->windows[windowId];
    int i;

    window->unk710 = 0;
    window->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_TOP_LEFT,
        &window->polysWindowBorderCorners[window->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    window->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_TOP_RIGHT,
        &window->polysWindowBorderCorners[window->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    window->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_BOTTOM_LEFT,
        &window->polysWindowBorderCorners[window->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    window->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_BOTTOM_RIGHT,
        &window->polysWindowBorderCorners[window->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );

    GearShopMenuSetVertices(&window->vertsWindowBorderCorners[0], (u16)(arg1 - 8), (u16)(arg2 +  8), 0x10, 0xFFF0);
    GearShopMenuSetVertices(&window->vertsWindowBorderCorners[4], (u16)(arg1 + arg3 + 8), (u16)(arg2 + 8), 0xFFF0, 0xFFF0);
    GearShopMenuSetVertices(&window->vertsWindowBorderCorners[8], (u16)(arg1 - 8), (u16)((arg2 + arg4) - 8), 0x10, 0x10);
    GearShopMenuSetVertices(&window->vertsWindowBorderCorners[0xC], (u16)(arg1 + arg3 + 8), (u16)((arg2 + arg4) - 8), 0xFFF0, 0x10);

    for(i = 0; i < 4; i++) {
        GearShopMenuSetWindowBorderPrimitive(&window->polysWindowBorderCorners[(i*2) + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderTop(u8 windowId, u16 x, u16 y, u16 width) {
    MenuWindow *window = g_Menu->windows[windowId];
    s32 innerWidth;
    u16 halfInnerWidth;
    int i;

    setUV4(
        &window->polysWindowBorderTop[g_Menu->renderContext],
        0, 132,
        7, 132,
        0, 148,
        7, 148
    );
    setUV4(
        &window->polysWindowBorderTop[2 + g_Menu->renderContext],
        0, 132,
        7, 132,
        0, 148,
        7, 148
    );

    innerWidth = width - (MENU_WINDOW_BORDER_SIZE * 2);
    halfInnerWidth = innerWidth / 2;

    GearShopMenuSetVertices(
        window->vertsWindowBorderTop1,
        (u16)(x + MENU_WINDOW_BORDER_SIZE),
        (u16)(y - MENU_WINDOW_BORDER_SIZE),
        halfInnerWidth,
        MENU_WINDOW_BORDER_SIZE * 2
    );
    GearShopMenuSetVertices(
        window->vertsWindowBorderTop2,
        (u16)(x + MENU_WINDOW_BORDER_SIZE + halfInnerWidth),
        (u16)(y - MENU_WINDOW_BORDER_SIZE),
        halfInnerWidth,
        MENU_WINDOW_BORDER_SIZE * 2
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive(
            (P_TAG *)&window->polysWindowBorderTop[i * 2 + g_Menu->renderContext]
        );
    }
}

void GearShopMenuSetWindowBorderBottom(u8 windowId, u16 x, u16 y, u16 width, u16 height) {
    MenuWindow* window;
    int i;
    int innerWidth;

    window = g_Menu->windows[windowId];

    setUV4(
        &window->polysWindowBorderBottom[g_Menu->renderContext],
        8, 132,
        15, 132,
        8, 148,
        15, 148
    );

    setUV4(
        &window->polysWindowBorderBottom[2 + g_Menu->renderContext],
        8, 132,
        15, 132,
        8, 148,
        15, 148
    );

    innerWidth = width - 16;
    width = innerWidth / 2;
    height = y + height - 8;

    GearShopMenuSetVertices(
        window->vertsWindowBorderBottom1,
        (u16)(x + 8),
        height,
        (u16)width,
        16
    );
    GearShopMenuSetVertices(
        window->vertsWindowBorderBottom2,
        (u16)(x + 8 + width),
        height,
        width,
        16
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive((P_TAG *)&window->polysWindowBorderBottom[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderLeft(u8 windowId, u16 x, u16 y, u16 height) {
    MenuWindow* window;
    int i;
    int innerHeight;
    u16 halfInnerHeight;

    window = g_Menu->windows[windowId];

    setUV4(
        &window->polysWindowBorderLeft[g_Menu->renderContext],
        16, 132,
        32, 132,
        16, 139,
        32, 139
    );

    setUV4(
        &window->polysWindowBorderLeft[2 + g_Menu->renderContext],
        16, 132,
        32, 132,
        16, 139,
        32, 139
    );

    innerHeight = height - 16;
    halfInnerHeight = innerHeight / 2;

    GearShopMenuSetVertices(
        window->vertsWindowBorderLeft1,
        (u16)(x - 8),
        (u16)(y + 8),
        16,
        halfInnerHeight
    );
    GearShopMenuSetVertices(
        window->vertsWindowBorderLeft2,
        (u16)(x - 8),
        (u16)(y + 8 + halfInnerHeight),
        16,
        halfInnerHeight
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive((P_TAG *)&window->polysWindowBorderLeft[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderRight(u8 windowId, u16 x, u16 y, u16 width, u16 height) {
    MenuWindow* window;
    int i;
    int innerHeight;
    u16 halfInnerHeight;

    window = g_Menu->windows[windowId];

    setUV4(
        &window->polysWindowBorderRight[g_Menu->renderContext],
        16, 140,
        32, 140,
        16, 147,
        32, 147
    );

    setUV4(
        &window->polysWindowBorderRight[2 + g_Menu->renderContext],
        16, 140,
        32, 140,
        16, 147,
        32, 147
    );

    width = x + width - 8;
    innerHeight = height - 16;
    halfInnerHeight = innerHeight / 2;

    GearShopMenuSetVertices(
        window->vertsWindowBorderRight1,
        width,
        (u16)(y + 8),
        16,
        halfInnerHeight
    );
    GearShopMenuSetVertices(
        window->vertsWindowBorderRight2,
        width,
        (u16)(y + 8 + halfInnerHeight),
        16,
        halfInnerHeight
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive(&window->polysWindowBorderRight[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindow(u8 windowId, u16 arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5, s32 zIndex, u8 hasScrollbar) {
    MenuWindow* window;

    window = g_Menu->windows[windowId];
    g_Menu->pManager->shouldRenderWindow[windowId] = 0;
    GearShopMenuSetVertices(window->vertsBackground, arg1, arg2, arg3, arg4);
    GearShopMenuInitializeWindowBorderCorners(windowId, arg1, arg2, arg3, arg4);
    GearShopMenuSetWindowBorderTop(windowId, arg1, arg2, arg3);
    GearShopMenuSetWindowBorderBottom(windowId, arg1, arg2, arg3, arg4);
    GearShopMenuSetWindowBorderLeft(windowId, arg1, arg2, arg4);
    GearShopMenuSetWindowBorderRight(windowId, arg1, arg2, arg3, arg4);
    if (hasScrollbar) {
        func_801C7E00(windowId, arg1, arg2, arg3, arg4);
    }
    window->hasScrollBar = hasScrollbar;
    window->unk714 = arg5;
    window->zIndex = zIndex;
    window->renderContext = g_Menu->renderContext;
    g_Menu->pManager->shouldRenderWindow[windowId] = TRUE;
}

void GearShopMenuFreeWindow(u8 index) {
    g_Menu->pManager->shouldRenderWindow[index] = 0;
    g_Menu->pManager->unk27[index] = 0;
    HeapFree(g_Menu->windows[index]);
    HeapFree(g_Menu->windowParameters[index]);
}

void GearShopMenuInitializeWindow(u8 windowId, u16 x, u16 y, u16 width, u16 height, u8 shouldInitializeHandle, u8 arg6, s32 zIndex, u8 hasScrollbar) {
    MenuWindowParameters* windowParameters;

    if (windowId >= 2) {
        g_Menu->windows[windowId] = HeapAlloc(sizeof(MenuWindow), 0);
        bzero((u8* ) g_Menu->windows[windowId], sizeof(MenuWindow));
        g_Menu->windowParameters[windowId] = HeapAlloc(sizeof(MenuWindowParameters), 0);
        bzero((u8* ) g_Menu->windowParameters[windowId], sizeof(MenuWindowParameters));
        func_801C7AE4(windowId);
    }

    windowParameters = g_Menu->windowParameters[windowId];

    if (shouldInitializeHandle) {
        windowParameters->index = windowId;
        windowParameters->unk11 = 0;
        windowParameters->x = x;
        windowParameters->y = y;
        windowParameters->width = width;
        windowParameters->height = height;
        windowParameters->unk8 = 0;
        windowParameters->unkA = 0;
        g_Menu->pManager->unk27[windowId] = TRUE;
        windowParameters->unk12 = arg6;
        windowParameters->zIndex = zIndex;
        return;
    }
    GearShopMenuSetWindow(windowId, x, y, width, height, arg6, zIndex, hasScrollbar);
}

void GearShopMenuUpdateWindows(void) {
    MenuWindowParameters* windowParams;
    u8 clipCount;
    s32 i;
    u16 widthOffset;
    u16 heightOffset;
    u16 clippedWidth;
    u16 clippedHeight;

    for(i = 0; i < MENU_MAX_NUM_WINDOWS; i++) {
        windowParams = g_Menu->windowParameters[i];
        if ((g_Menu->pManager->unk27[i]) && (windowParams->unk11 == 0)) {
            clipCount = 0;
            if ((windowParams->unk8 + 0x20) >= (s32) windowParams->width) {
                clippedWidth = windowParams->width;
                clipCount = 1;
            } else {
                clippedWidth = windowParams->unk8 + 0x20;
            }
            windowParams->unk8 = clippedWidth;
            if ((windowParams->unkA + 0x20) >= (s32) windowParams->height) {
                clippedHeight = windowParams->height;
                clipCount += 1;
            } else {
                clippedHeight = windowParams->unkA + 0x20;
            }
            windowParams->unkA = clippedHeight;
            if (clipCount == 2) {
                windowParams->unk11 = TRUE;
            }
            heightOffset = windowParams->unkA;
            widthOffset = windowParams->unk8;
            GearShopMenuSetWindow(
                windowParams->index,
                ((windowParams->x + ((u16) windowParams->width >> 1)) - (widthOffset >> 1)),
                ((windowParams->y + ((u16) windowParams->height >> 1)) - (heightOffset >> 1)),
                widthOffset,
                (s32) heightOffset,
                (s32) windowParams->unk12,
                windowParams->zIndex,
                (s32) windowParams->hasScrollBar);
        }
    }
}

void GearShopMenuRenderPolygons(int count, SVECTOR* vertices, POLY_FT4* quads, int renderContext) {
    long interpolated;
    long flag;
    int i;

    for (i = 0; i < count; i++) {
        RotTransPers4(
            &vertices[i*4 + 0],
            &vertices[i*4 + 1],
            &vertices[i*4 + 2],
            &vertices[i*4 + 3],
            (long *)&quads[i*2 + renderContext].x0,
            (long *)&quads[i*2 + renderContext].x1,
            (long *)&quads[i*2 + renderContext].x2,
            (long *)&quads[i*2 + renderContext].x3,
            &interpolated,
            &flag
        );

        AddPrim(&g_Menu->pGfxEnv->ot[4], &quads[i*2 + renderContext]);
    }
}

void GearShopMenuRenderString(s32 count, POLY_FT4* polys, u32 renderContext) {
    int i;

    for(i = 0; i < count; i++) {
        AddPrim(&g_Menu->pGfxEnv->ot[4], &polys[(2*i) + renderContext]);
    }
}

void GearShopMenuRenderScrollBarHandle(void) {
    if (g_Menu->pManager->scrollHandleActive) {
        GearShopMenuRenderPolygons(1,
                      g_Menu->pScrollHandle->vertices,
                      g_Menu->pScrollHandle,
                      g_Menu->pScrollHandle->renderContext);
    }
}

void func_801C959C(void) {
    AddPrim(&g_Menu->pGfxEnv->ot[4], &g_Menu->unk348->drModes1[g_Menu->unk348->unk159]);
    if (g_Menu->pManager->unk4) {
        AddPrim(&g_Menu->pGfxEnv->ot[4], &g_Menu->unk348->polysPointerCursor[g_Menu->unk348->cursorRenderContext]);
    }
}

void func_801C962C(void) {
    if ((g_Menu->pManager->unk52[1]) && (GEAR_SHOP_AVAILABLE_CHARACTER_COUNT >= 2)) {
        GearShopMenuRenderPolygons(4, g_Menu->unk440->unk140, g_Menu->unk440, g_Menu->unk440->unk1C0);
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9690);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9864);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9A38);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C9C0C);

void GearShopMenuRenderWindowBackground(s32 windowId) {
    long interpolation;
    long flag;
    MenuWindow* window;

    window = g_Menu->windows[windowId];
    RotTransPers4(
        &window->vertsBackground[0],
        &window->vertsBackground[1],
        &window->vertsBackground[2],
        &window->vertsBackground[3],
        (long* ) &window->polysBackground[window->renderContext].x0,
        (long* ) &window->polysBackground[window->renderContext].x1,
        (long* ) &window->polysBackground[window->renderContext].x2,
        (long* ) &window->polysBackground[window->renderContext].x3,
        &interpolation,
        &flag);
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysBackground[window->renderContext]
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->drawModes[window->renderContext]
    );
}

void GearShopMenuRenderWindowBorderCorners(s32 arg0) {
    long interpolation;
    long code;
    MenuWindow *window;
    int i;

    window = g_Menu->windows[arg0];

    for(i = 0; i < 4; i++) {
        RotTransPers4(
            &window->vertsWindowBorderCorners[(i*4)],
            &window->vertsWindowBorderCorners[(i*4)+1],
            &window->vertsWindowBorderCorners[(i*4)+2],
            &window->vertsWindowBorderCorners[(i*4)+3],
            (long* ) &window->polysWindowBorderCorners[i*2 + window->renderContext].x0,
            (long* ) &window->polysWindowBorderCorners[i*2 + window->renderContext].x1,
            (long* ) &window->polysWindowBorderCorners[i*2 + window->renderContext].x2,
            (long* ) &window->polysWindowBorderCorners[i*2 + window->renderContext].x3,
            &interpolation,
            &code);
        AddPrim(&g_Menu->pGfxEnv->ot[window->zIndex], &window->polysWindowBorderCorners[i*2 + window->renderContext]);
    }
}

void GearShopMenuRenderScrollBar(s32 windowId) {
    int i;
    MenuWindow *window = g_Menu->windows[windowId];
    long p, flag;

    for(i = 0; i < 2; i++) {
        RotTransPers4(
            &window->vertsScrollBarEnds[(i*4)],
            &window->vertsScrollBarEnds[(i*4) + 1],
            &window->vertsScrollBarEnds[(i*4) + 2],
            &window->vertsScrollBarEnds[(i*4) + 3],
            (long *)&window->polysScrollBarEnds[(i*2) + window->renderContext].x0,
            (long *)&window->polysScrollBarEnds[(i*2) + window->renderContext].x1,
            (long *)&window->polysScrollBarEnds[(i*2) + window->renderContext].x2,
            (long *)&window->polysScrollBarEnds[(i*2) + window->renderContext].x3,
            &p,
            &flag
        );
        AddPrim(
            &g_Menu->pGfxEnv->ot[window->zIndex],
            &window->polysScrollBarEnds[(i*2) + window->renderContext]
        );
    }

    RotTransPers4(
        &window->vertsScrollBarEmpty[0],
        &window->vertsScrollBarEmpty[1],
        &window->vertsScrollBarEmpty[2],
        &window->vertsScrollBarEmpty[3],
        (long *)&window->polysScrollBarEmpty[window->renderContext].x0,
        (long *)&window->polysScrollBarEmpty[window->renderContext].x1,
        (long *)&window->polysScrollBarEmpty[window->renderContext].x2,
        (long *)&window->polysScrollBarEmpty[window->renderContext].x3,
        &p,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysScrollBarEmpty[window->renderContext]
    );
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA28C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA404);

void func_801CA754(void) {
    int i;
    int renderContext;

    for(i = 0; i < 4; i++) {
        if(g_Menu->pManager->unk34[i]) {
            renderContext = g_Menu->unk4E0[i].renderContext;
            AddPrim(&g_Menu->pGfxEnv->ot[4], &g_Menu->unk4E0[i].polys[renderContext]);
        }
    }
}

void func_801CA7E4(void) {
    s32 i;

    for(i = 0; i < 8; i++) {
        if (g_Menu->pManager->unkC[i]) {
            AddPrim(
                &g_Menu->pGfxEnv->ot[4],
                &g_Menu->unk6E0[i].polys[g_Menu->unk6E0[i].renderContext]
            );
        }
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CA874);

void func_801CA9EC(void) {
    int i;
    int renderContext;

    for(i = 0; i < 6; i++) {
        if (g_Menu->pManager->unk1A[i]) {
            renderContext = g_Menu->unkDE0[i].renderContext;
            AddPrim(&g_Menu->pGfxEnv->ot[4], &g_Menu->unkDE0[i].polys[renderContext]);
        }
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CAA7C);

void GearShopMenuRenderBackgroundDim(void) {
}

void func_801CABE0(void) {
    func_801CA754();
    func_801CA7E4();
    func_801CA874();
    func_801CA9EC();
    func_801CAA7C();
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CAC20);

void func_801CB2E8(void) {
    if (g_Menu->pManager->unkA) {
        GearShopMenuRenderString(g_Menu->unk354->unk1404, g_Menu->unk354->polys500, g_Menu->unk354->unk1409);
        GearShopMenuRenderString(g_Menu->unk354->unk1400, g_Menu->unk354->polys0, g_Menu->unk354->unk1408);
    }
}

void GearShopMenuRenderArrowCursors(void) {
    MenuArrowCursor* cursor;
    int i;

    for(i = 0; i < MENU_MAX_NUM_ARROW_CURSORS; i++) {
        if (g_Menu->pManager->shouldRenderArrowCursor[i]) {
            cursor = g_Menu->arrowCursors[i];
            GearShopMenuRenderPolygons(1, cursor->vertices, cursor, cursor->renderContext);
        }
    }
}

void GearShopMenuRender(void) {
    if (g_Menu->shouldDrawMenu) {
        GearShopMenuUpdateWindows();
        func_801CF33C();
        func_801CA404();
        func_801CABE0();
        func_801C959C();
        GearShopMenuRenderArrowCursors();
        func_801CE32C();
        func_801C962C();
        GearShopMenuRenderScrollBarHandle();
        func_801CAC20();
        func_801CB2E8();
        func_801CA28C();
        func_801CE82C();
        GearShopMenuRenderString(1, &g_Menu->menuUnk8->unk80, g_Menu->menuUnk8->unk80[0x1E61]);
        func_801CE7E0();
    }
    GearShopMenuRenderBackgroundDim();
}

void GearShopMenuPlaySoundEffect(s32 arg0) {
    if (g_Menu->unk32A) {
        func_80039DB8((g_Menu->unk2E4->sedId << 0x10) | (arg0 & 0xFF), arg0);
    }
}

void GearShopMenuPollInput(void) {
    u8 wasControllerUnplugged;
    u8 isLooping;
    int savedValue;
    u8 input;

    input = MENU_INPUT_IDLE;
    isLooping = TRUE;
    wasControllerUnplugged = FALSE;
    while (isLooping) {
        // Is the main controller not plugged in?
        if (ControllerGetType(0) == CONTROLLER_TYPE_NONE) {
            if (wasControllerUnplugged == 0) {
                wasControllerUnplugged++;
                SoundMuteAllSpuChannels();
                savedValue = D_80059488;
            }
            continue;
        }

        isLooping--;
        if (wasControllerUnplugged) {
            SoundEnableAllSpuChannels();
            D_80059488 = savedValue;
        }
    }

    if (func_80036410()) {
        ControllerResetState();
    } else {
        while (ControllerPopState()) {
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_RIGHT) {
                input = MENU_INPUT_RIGHT;
                GearShopMenuPlaySoundEffect(1);
                break;
            }
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_DOWN) {
                input = MENU_INPUT_DOWN;
                GearShopMenuPlaySoundEffect(1);
                break;
            }
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_LEFT) {
                input = MENU_INPUT_LEFT;
                GearShopMenuPlaySoundEffect(1);
                break;
            }
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_UP) {
                input = MENU_INPUT_UP;
                GearShopMenuPlaySoundEffect(1);
                break;
            }
            if (g_C1ButtonStateReleased & CTRL_BTN_CIRCLE) {
                input = MENU_INPUT_CONFIRM;
                break;
            }
            if (g_C1ButtonStateReleased & CTRL_BTN_CROSS) {
                input = MENU_INPUT_BACK;
                GearShopMenuPlaySoundEffect(3);
                break;
            }
            if (g_C1ButtonStateReleased & CTRL_BTN_SQUARE) {
                input = 6;
                break;
            }
            if (g_C1ButtonStateReleased & CTRL_BTN_TRIANGLE) {
                input = 7;
                break;
            }
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_L1) {
                input = 10;
                break;
            }
            if (g_C1ButtonStatePressedOnce & CTRL_BTN_R1) {
                input = 9;
                break;
            }
        }
    }
    g_Menu->input = input;
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB690);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CBA2C);

void func_801CBDA0(void) {
    func_801CBA2C();
    RotMatrix(&g_Menu->unk218, (MATRIX* ) g_Menu->unk230);
    TransMatrix((MATRIX* ) g_Menu->unk230, &g_Menu->unk220);
    SetRotMatrix((MATRIX* ) g_Menu->unk230);
    SetTransMatrix((MATRIX* ) g_Menu->unk230);
    RotMatrix(&g_Menu->rotation, &g_Menu->matTransform);
    TransMatrix(&g_Menu->matTransform, &g_Menu->translation);
    SetRotMatrix(&g_Menu->matTransform);
    SetTransMatrix(&g_Menu->matTransform);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CBE60);

void GearShopMenuUpdateAndRender(void) {
    if (*D_8005917C != -1) {
        asm("break 0x400");
    }

    GearShopMenuPollInput();
    GameCheckAndHandleSoftReset();

    g_Menu->pGfxEnv = (g_Menu->pGfxEnv == g_Menu->gfxEnvs) ? &g_Menu->gfxEnvs[1] : g_Menu->gfxEnvs;
    g_Menu->renderContext = g_Menu->renderContext == 0;
    ClearOTagR((u32 *)g_Menu->pGfxEnv->ot, 0x10);
    ClearOTagR((u32* )g_Menu->pGfxEnv->unkB0, 0x400);
    func_801CBDA0();
    func_801CBE60();
    GearShopMenuRender();
    DrawSync(0);
    Vsync(0);

    PutDrawEnv(&g_Menu->pGfxEnv->drawEnv);
    PutDispEnv(&g_Menu->pGfxEnv->dispEnv);
    ClearImage(&g_Menu->pGfxEnv->drawEnv.clip, 0U, 0U, 0U);
    AddPrims((void* ) g_Menu->pGfxEnv->unkB0, &g_Menu->pGfxEnv->ot[0xF], g_Menu->pGfxEnv->ot);
    DrawOTag((u32 *)(g_Menu->pGfxEnv->unkB0 + 0xFFC));
}

void GearShopMenuInitializePointerCursors(u8 mode) {
    int i;

    g_Menu->pCursors = HeapAlloc(sizeof(MenuPointerCursors), 0);
    bzero((u8 *)g_Menu->pCursors, sizeof(MenuPointerCursors));

    switch(mode) {
        case 0:
            g_Menu->pManager->shouldRenderCursors = TRUE;
            g_Menu->pCursors->unk144[0] = TRUE;
            g_Menu->pCursors->unk144[1] = TRUE;
        case 2:
            for(i = 0; i < 4; i++) {
                func_8002675C(
                    g_Menu->resources,
                    0x108,
                    &g_Menu->pCursors->polysCursor[i*2],
                    g_Menu->renderContext,
                    D_801D6A60[i],
                    D_801D6A70[i],
                    0x800);
                g_Menu->pCursors->renderContexts[i] = g_Menu->renderContext;
            }
            break;
        case 3:
            func_8002675C(
                g_Menu->resources,
                0x108,
                &g_Menu->pCursors->polysCursor[0],
                g_Menu->renderContext, 0, 0, 0x800);
            g_Menu->pCursors->renderContexts[0] = g_Menu->renderContext;
            g_Menu->pManager->shouldRenderCursors = TRUE;
        case 1:
            break;
    }
}

void GearShopMenuFreePointerCursors(void) {
    g_Menu->pManager->shouldRenderCursors = 0;
    GearShopMenuUpdateAndRender();
    HeapFree(g_Menu->pCursors);
}

void func_801CC520(void) {
}

void func_801CC528(void) {
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CC530);

void GearShopMenuConfirmationWindowFree(void) {
    int i;

    if (g_Menu->pManager->shouldRenderWindow[4]) {
        GearShopMenuFreeWindow(4);

        g_Menu->pManager->unk2B = 0;

        for(i = 0; i < 4; i++) {
            HeapFree(g_Menu->unk1DE0[i]);
        }
    }
    g_Menu->pManager->unk5B = 0;
    GearShopMenuUpdateAndRender();
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCA40);

s32 func_801CCC18(u8 arg0, s32 arg1, s32 arg2) {
    u8 unkBool = TRUE;
    u8 result;

    func_801CC530(arg0);
    if ((u8)arg1 == 0xFF) {
        g_Menu->pCursors->shouldRender[3] = TRUE;
    } else {
        g_Menu->pCursors->shouldRender[2] = FALSE;
        unkBool = 0;
        g_Menu->pCursors->shouldRender[3] = FALSE;
    }

    result = func_801CCA40(arg2, unkBool);
    GearShopMenuConfirmationWindowFree();

    if ((u8)arg1 != 0xFF) {
        g_Menu->pCursors->shouldRender[3] = TRUE;
        func_801CC530(arg1);
        g_Menu->pCursors->shouldRender[3] = TRUE;
        result = func_801CCA40(arg2, 1);
        GearShopMenuConfirmationWindowFree();
    }
    return result;
}

void GearShopMenuFree(void) {
    GearShopMenuUpdateAndRender();
    GearShopMenuUpdateAndRender();
    g_Menu->shouldDrawMenu = 0;
    GearShopMenuUpdateAndRender();
    do {
        GearShopMenuUpdateAndRender();
    } while (g_Menu->renderContext);
    GearShopMenuMenuUnk2Manager(0);
    GearShopMenuMenuManagerManager(0);
    GearShopMenuSelectionMenuManager(0);
    GearShopMenuMenuUnk5Manager(0);
    GearShopMenuMenuUnk6Manager(0);
    GearShopMenuMenuUnk1Manager(0);
    func_801C6A54(0x10);
    GearShopMenuMenuShopManager(0);
    GearShopMenuMenuUnk8Manager(0);
    HeapFree(g_Menu->resources);
    HeapFree(g_Menu->unk2E0);
    HeapFree(g_Menu->unk4E0[0].pVramBuffer);
    if (g_MenuDebugEnabled) {
        func_8003A094(g_Menu->unk2E4);
        GearShopMenuUpdateAndRender();
        func_8003852C(g_Menu->unk2E4);
        GearShopMenuUpdateAndRender();
        HeapFree(g_Menu->unk2E4);
    }
    GearShopMenuMenuUnk7Manager(0);
    HeapFree(g_Menu);
}

void func_801CCE90(s32 count, MenuString *menuString, s8 *arg2, s8 *unused) {
    func_801C5EE8(menuString, arg2, 2, (u8)count);
}

void func_801CCEBC(s32 count, s8* buffer) {
    int i;

    for(i = 0; i < (u8)count; i++) {
        buffer[i] = 0;
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CCEE8);

void func_801CD310(s32 count, s32* resourceIds) {
    int i, j;

    g_Menu->pSelectionMenu->unk1192 = 0;
    g_Menu->pSelectionMenu->unk1193 = 0;

    g_Menu->pManager->shouldRenderSelectionMenu = TRUE;

    for (i = 1; i <= count; i++) {
        if (i != count) {
            g_Menu->pSelectionMenu->numCursors = 0;
            for(j = 0; j < i; j++) {
                g_Menu->pSelectionMenu->numCursors += func_8002675C(
                    g_Menu->resources,
                    resourceIds[j*2],
                    &g_Menu->pSelectionMenu->polysCursors[g_Menu->pSelectionMenu->numCursors*2],
                    g_Menu->renderContext,
                    0xA0,
                    0x96,
                    0x1000
                );
            }
            g_Menu->pSelectionMenu->cursorsRenderCtx = g_Menu->renderContext;
        }

        g_Menu->pSelectionMenu->numTexts = 0;

        if (i != 1) {
            for (j = 0; j < i - 1; j++) {
                g_Menu->pSelectionMenu->numTexts += func_8002675C(
                    g_Menu->resources,
                    resourceIds[(j*2)+1],
                    &g_Menu->pSelectionMenu->polysTexts[g_Menu->pSelectionMenu->numTexts*2],
                    g_Menu->renderContext,
                    0xA0,
                    0x96,
                    0x1000
                );
            }
            g_Menu->pSelectionMenu->textsRenderCtx = g_Menu->renderContext;
        }

        for(j = 0; j < 2; j++) {
            GearShopMenuUpdateAndRender();
        }
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CD564);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CD838);

void func_801CDA0C(u8 arg0) {
    int i;
    int index;

    g_Menu->unk354->unk1400 = 0;
    g_Menu->unk354->unk1404 = 0;

    for(i = 0; i < g_Menu->unk33A; i++) {
        if(i == g_Menu->menu2Choice) {
            index = *(&D_801D69A0 + (((arg0 + g_Menu->menu1Choice) * 8) + (i*2))) + 0xD;
        } else {
            index = *(&D_801D69A0 + (((arg0 + g_Menu->menu1Choice) * 8) + (i*2)));
        }

        g_Menu->unk354->unk1400 += func_8002675C(
            g_Menu->resources,
            index,
            &g_Menu->unk354->polys0[g_Menu->unk354->unk1400*2],
            g_Menu->renderContext,
            0xA0,
            0x96,
            0x1000
        );

        g_Menu->unk354->unk1404 += func_8002675C(
            g_Menu->resources,
            *(&D_801D69A4 + (((arg0 + g_Menu->menu1Choice) * 8) + (i*2))),
            &g_Menu->unk354->polys500[g_Menu->unk354->unk1404*2],
            g_Menu->renderContext,
            0xA0,
            0x96,
            0x1000
        );
    }
    g_Menu->unk354->unk1408 = g_Menu->renderContext;
    g_Menu->unk354->unk1409 = g_Menu->renderContext;
    func_801C6278(g_Menu->menu2Choice + 4, 1);
    g_Menu->pManager->unk4 = TRUE;
}


s32 func_801CDC68(void) {
    s32 result;
    u8 selection;

    result = 1;
    if (g_Menu->menu1Choice) {
        selection = func_801D5828();
    } else {
        result = 0;
    }
    // intentionally using selection w/o intialization
    if (selection) {
        func_801CC528();
        func_801CCE90(4, g_Menu->unk6E0, &D_801D6A20, g_Menu->pManager->unkC);
    }
    g_Menu->pSelectionMenu->unk1192 = 0;
    g_Menu->pSelectionMenu->unk1193 = 1;
    g_Menu->pManager->unk4 = 1;
    g_Menu->pManager->unk3 = 1;
    g_Menu->unk337 = 0xFF;
    g_Menu->pManager->unkA = 0;
    return result;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CDD74);

/* 0x801CE024 */ void GearShopMenuMain(void) {
    GearShopMenuMenuUnk2Manager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuManagerManager(MENU_DATA_INITIALIZE);
    GearShopMenuSelectionMenuManager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuUnk5Manager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuUnk6Manager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuUnk1Manager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuUnk7Manager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuShopManager(MENU_DATA_INITIALIZE);
    GearShopMenuMenuUnk8Manager(MENU_DATA_INITIALIZE);
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
    GearShopMenuFilterPartyMembers();
    GearShopMenuResetRenderContext();
    func_801C6114(); // initMenuGeometry()?
    func_801C6708(); // initMenuUnk1()?
    GearShopMenuInitializeWindowBorders(); // get texture page data
    func_801C6E74();
    func_801D5D38();
    g_Menu->unk440 = HeapAlloc(sizeof(MenuUnknownComponent), 0);
    bzero(g_Menu->unk440, sizeof(MenuUnknownComponent));
    func_801CE1D0();
    g_Menu->shouldDrawMenu = TRUE;
    g_Menu->unk32A = TRUE;
    func_801CDD74();
    GearShopMenuFree();
}

void func_801CE1D0(void) {
    int i;
    POLY_FT4 *poly;
    int temp;

    for(i = 0; i < 2; i++) {
        func_8002675C(
            g_Menu->resources,
            MENU_TEX_L1_RED_ARROW + i,
            &g_Menu->unk440->polys[i*4],
            g_Menu->renderContext,
            D_801D6FD0[i],
            0x64,
            0x1000);
    }

    for(i = 0; i < 4; i++) {
        temp = (i*2 + g_Menu->renderContext);
        GearShopMenuSetVertices(&g_Menu->unk440->unk140[i*4], g_Menu->unk440->polys[temp].x0, g_Menu->unk440->polys[temp].y0, (g_Menu->unk440->polys[temp].x1 - g_Menu->unk440->polys[temp].x0), (g_Menu->unk440->polys[temp].y3 - g_Menu->unk440->polys[temp].y0));
    }

    g_Menu->unk440->unk1C0 = (u8) g_Menu->renderContext;
}

void func_801CE2E8(void) {
    g_Menu->pManager->unk52[1] = 0;
    GearShopMenuUpdateAndRender();
    HeapFree(g_Menu->unk440);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE32C);


/*
 This is the function in gear_shop_menu that calls into gear_shop_helper
 */
void func_801CE7E0(void) {
    // most likely: if helper library is loaded into memory
    if (g_Menu->pManager->unk5C[7]) {
        func_801E7D14(&g_Menu->unk230, &g_Menu->unk298, g_Menu->pGfxEnv->unkB0, g_Menu->renderContext);
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE82C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CEA68);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CEEA8);

void func_801CF184(void) {
    MenuUnk8 *menu;
    int i;
    short t1, t2;

    menu = g_Menu->menuUnk8;

    if(menu->unk1ED8) {
        if(menu->unk1EDC) {
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
                    &g_Menu->menuUnk8->polys[i*4],
                    g_Menu->renderContext,
                    g_Menu->menuUnk8->unk1EF0 + i*0x8,
                    g_Menu->menuUnk8->unk1EF2 + i*0xA,
                    0x1000);
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

void func_801CF38C(u8 arg0) {
    RECT rect;

    D_801D9088 = HeapAlloc(0x3F6U, 0U);
    bzero(D_801D9088, 0x3F6);
    SystemRenderStringEntry(&g_GameState.strings[arg0], D_801D9088, 0x24, 0);
    setRECT(&rect, 0x180, 0x48, 0x28, 0xD);
    LoadImage(&rect, (u32* ) D_801D9088);
    DrawSync(0);
    HeapFree(D_801D9088);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF448);

void func_801CF9BC(u8 arg0, u8 arg1) {
    ArchiveSetIndex(4, 0);

    g_Menu->unk458[arg1]->unk0 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[arg0]), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[arg0], g_Menu->unk458[arg1]->unk0, 0, 0x80);
    ArchiveCdDataSync(0);

    g_Menu->unk458[arg1]->unk4 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[arg0]+1), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[arg0]+1, g_Menu->unk458[arg1]->unk4, 0, 0x80);
    ArchiveCdDataSync(0);

    ArchiveSetIndex(0x10, 0);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CFAB8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CFC60);

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

void func_801D0054(s32 count, POLY_FT4 *polys, u8 mode) {
    int i;

    for(i = 0; i < count; i++) {
        SetShadeTex(&polys[(i*2)+g_Menu->renderContext], 0);
        switch(mode) {
            case 0:
                setRGB0(&polys[(i*2)+g_Menu->renderContext], 0x80, 0x40, 0x40);
                break;
            case 1:
                setRGB0(&polys[(i*2)+g_Menu->renderContext], 0x40, 0x40, 0x80);
                break;
        }
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0220);

void func_801D0348(void) {
    int i;

    for(i = 0; i < 0xB; i++) {
        if(g_Menu->availableCharacters[i]) {
            GEAR_SHOP_AVAILABLE_CHARACTER_COUNT += 1;
        }
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0398);

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D06D8);

void func_801D0C20(int arg0, u8 arg1) {

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
    GearShopMenuParseNumberToString(arg0);
    g_Menu->pShop->finalPriceStrLen = 0;
    for(i = 0; i < 9; i++) {
        if (g_Menu->digits[i] != 0xFF) {
            g_Menu->pShop->finalPriceStrLen +=
                func_8002675C(
                    g_Menu->resources,
                    g_Menu->digits[i],
                    &g_Menu->pShop->polysFinalPrice[g_Menu->pShop->finalPriceStrLen*2],
                    g_Menu->renderContext,
                    var_s1 + 3,
                    var_s2,
                    0x1000);
        }
        var_s1 += 8;
    }
    g_Menu->pShop->finalPriceRenderCtx = (u8) g_Menu->renderContext;
    g_Menu->pManager->unk5B = 2;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0D4C);

void func_801D0EC8(u8 arg0) {
    s32 i;

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1078);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1304);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D18F8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1F20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2054);

void func_801D2784(void) {
    func_801D2054(0x96,
        g_GameState.unk221A,
        g_GameState.unk2184,
        3, 1,
        g_GameState.unk2184,
        0);
}

void func_801D27C4(void) {
    func_801D2054(0x64,
    g_GameState.unk2120,
    g_GameState.unk20BC,
    4, 1,
    g_GameState.unk20BC
    , 0);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2804);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2950);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2B74);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3558);

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3A80);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D3C78);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D44FC);

s32 func_801D4888(s32 itemId) {
    u8 equipped;
    u8 itemType = g_Menu->shopItemTypes[itemId];
    u8 result = TRUE;

    switch(itemType) {

        case 0:
            equipped = g_GameState.gears[D_801D9084].unk0[8];
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
        case 1:
            equipped = g_GameState.gears[D_801D9084].unk0[2];
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
        case 2:
            equipped = g_GameState.gears[D_801D9084].unk0[3];
            if(equipped >= g_Menu->shopItemIDs[itemId]) {
                result = FALSE;
            }
            break;
    }

    return result;
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D498C);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5398);

s32 func_801D573C(void) {
    g_Menu->pManager->unk4 = 0;
    g_Menu->pManager->unk3 = 0;
    func_801CCEBC(4, g_Menu->pManager->unkC);
    func_801D0EC8(0);
    return 2;
}

void func_801D57A8(void) {

    switch(g_Menu->menu2Choice) {
        case 0:
        case 1:
        case 2:
            func_801D498C(0, 1);
            func_801D6150(g_Menu->unk330, D_801D9084);
            break;
        case 3:
            func_801D5398();
    }
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5828);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D5D38);

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

void func_801D5F94(MenuUnk6* view, u8 gearId) {
    GameGear *gear;
    GameCharacter *pilot;
    u16 ether;
    int etherModifier;

    if(g_GameState.unk22B6 & 0x1000) {
        D_801D70FD = 0xA;
    }

    gear = &g_GameState.gears[gearId];
    pilot = &g_GameState.characters[D_801D70F4[gearId]];

    view->hp = gear->hp;
    view->maxHp = gear->maxHp;
    view->totalDefense = gear->baseDefense + gear->defenseFromEquipment;

    view->totalEtherDefense = pilot->etherDefense + pilot->etherDefenseFromEquipment + gear->etherDefenseFromEquipment + gear->baseEtherDefense;
    view->totalWeight = gear->weight + gear->weightFromEquipment;
    view->unkAA = gear->unk6A;
    view->fuel = gear->fuel;
    view->maxFuel = gear->maxFuel;

    ether = gear->unk3C * (gear->unk74 + gear->unk56);

    if(gearId == 0x5 || gearId == 0xD) {
        etherModifier = ((gear->maxEther + gear->unk22) * 6) / 10;
        view->unkB0 = etherModifier + ether;
    } else {
        view->unkB0 = gear->maxEther + ether;
    }

    view->totalResponsiveness = gear->unk9F + gear->responsiveness;
    view->unkB3 = gear->unk98 - gear->unk4A;
    view->unkB4 = gear->unk9E;
    view->unkB5 = gear->unk9D;
    view->unkB6 = gear->unk9C;
}

void func_801D6150(MenuUnk6* arg0, u8 arg1) {
    func_801D61B8(arg0, arg1);
    func_801D62A4(arg0, arg1);
    func_801D6250(arg0, arg1);
    func_801D6334(arg0, arg1);
    func_801D6738(arg0, arg1);
}

void func_801D61B8(MenuUnk6* arg0, u8 gearId) {
    GameGear* gear;
    GearStatsPreview* preview;
    u8 previewId;

    gear = &g_GameState.gears[gearId];
    preview = arg0->pGearStatsPreview;
    previewId = gear->unk0[2];
    preview = &preview[previewId];

    gear->maxHp = preview->hp;

    gear->weight = preview->weight;
    gear->unk98 = preview->unk14;
    gear->unk9E = preview->unk15;
    gear->unk9D = preview->unk16;
    gear->unk9F = preview->unk17;
    if (gear->maxHp < gear->hp) {
        gear->hp = gear->maxHp;
    }
}

void func_801D6250(MenuUnk6* menu, u8 arg1) {
    GameGear *gear;
    MenuUnkItem *itemList;
    MenuUnkItem *item;

    gear = &g_GameState.gears[arg1];
    itemList = menu->unk10;
    item = &itemList[gear->unk0[8]];

    gear->baseDefense = item->unk8;
    gear->baseEtherDefense = item->unkA;
}

void func_801D62A4(MenuUnk6* shopInfo, u8 gearId) {

    GameGear *gear;
    MenuUnk6UnkCItem *item;
    u16 fuel;
    u8 itemId;

    gear = &g_GameState.gears[gearId];
    itemId = gear->unk0[3];
    item = shopInfo->unkC;
    fuel = gear->fuel;
    item = &item[itemId];

    gear->maxFuel = item->maxFuel;
    gear->unk3C = item->unkC;
    gear->unk3D = item->unkD;
    gear->unk3E = item->unkE;
    gear->unk3F = item->unkE;

    if (gear->maxFuel < fuel) {
        gear->fuel = gear->maxFuel;
    }
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6334);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6738);

s32 func_801D690C(u8 index) {
    GameGear* gear;
    s32 temp_v0;
    u8 result;

    gear = &g_GameState.gears[index];
    temp_v0 = (s32) ((gear->weightFromEquipment / 120) - gear->unk75) / 2;
    result = temp_v0;
    if (temp_v0 << 16 < 0) {
        result = 0;
    }
    return result;
}
