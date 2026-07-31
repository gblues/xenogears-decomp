#include "common.h"
#include "system/menu.h"
#include "system/controller.h"
#include "system/archive.h"
#include "system/graphics.h"
#include "system/debug.h"

// Confirmation window choices
#define MENU_CHOICE_NO 0
#define MENU_CHOICE_YES 1

// Selection modes
#define MENU_AUTO_ADVANCE 0
#define MENU_MANUAL_CHOICE 0xFF


// probably something like: DEBUGGER_ATTACHED, guards a breakpoint left in the code
extern s32* D_8005917C; // TODO: should be in a header for main program stuff since this is not coming from an overlay

extern s8  D_801D697C;
extern int D_801D69A0;
extern int D_801D69A4;
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
extern u8  D_801D9084;
extern s32 g_gearShopAvailableCharacterCount;
extern u8* D_801D9088;

extern s32 D_801D6980[];
// = {
//    MENU_TEX_BALL_CURSOR_1, MENU_TEX_STRING_BUY,
//    MENU_TEX_BALL_CURSOR_2, MENU_TEX_STRING_SELL,
//    MENU_TEX_BALL_CURSOR_3, MENU_TEX_STRING_EXIT,
//    MENU_TEX_BALL_CURSOR_4, MENU_TEX_STRING_TUNE_UP,
//    }
extern s32 D_801D6A30[];



/* this function doesn't seem to get called by anything, possibly dead code? I spent a little time decomping this
 * and got it to 94% but don't want to spend a ton of time on it.
 *
 * https://decomp.me/scratch/t631n
 */
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C511C);

void func_801C51B8(POLY_FT4* pPoly, short x, short y, u_char u, u_char v, short width, short height) {
    setXY4(
        pPoly,
        x,         y,
        x + width, y,
        x,         y + height,
        x + width, y + height
    );

    setUV4(
        pPoly,
        u,         v,
        u + width, v,
        u,         v + height,
        u + width, v + height
    );
}

u_short GearShopMenuIsCharacterFlagSet(u_short value, u_char maskIndex) {
    return D_801D6C68[maskIndex] & value;
}

u_short GearShopMenuGetCharacterBitMask(int index) {
    return D_801D6C68[index & 0xFF];
}

s32 func_801C5260(u8 count) {
    return D_801D6C88[count];
}

s32 func_801C527C(s32 arg0, u8 arg1) {
    return arg0 & D_801D6C88[arg1];
}

void GearShopMenuParseNumberToString(u_int amount) {
    int i;
    u_int place = 100000000;

    for(i = 0; i < MENU_MAX_DIGITS; i++) {
        g_Menu->digits[i] = amount / place;
        amount = amount % place;
        place /= 10;
    }

    for(i = 1; i < MENU_MAX_DIGITS; i++) {
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
void GearShopMenuMenuUnk2Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk2 = HeapAlloc(sizeof(MenuUnk2), 0);
        bzero(g_Menu->menuUnk2, sizeof(MenuUnk2));
        return;
    }
    HeapFree(g_Menu->menuUnk2);
}

void GearShopMenuMenuManagerManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pManager = HeapAlloc(sizeof(MenuManager), 0);
        bzero(g_Menu->pManager, sizeof(MenuManager));
        return;
    }
    HeapFree(g_Menu->pManager);
}

void GearShopMenuSelectionMenuManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pSelectionMenu = HeapAlloc(sizeof(MenuSelectionMenu), 0);
        bzero(g_Menu->pSelectionMenu, sizeof(MenuSelectionMenu));
        return;
    }
    HeapFree(g_Menu->pSelectionMenu);
}

void GearShopMenuMenuUnk5Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk354 = HeapAlloc(sizeof(MenuUnk5), 0);
        bzero(g_Menu->unk354, sizeof(MenuUnk5));
        return;
    }
    HeapFree(g_Menu->unk354);
}

void GearShopMenuMenuUnk6Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk330 = HeapAlloc(sizeof(MenuUnk6), 0);
        bzero(g_Menu->unk330, sizeof(MenuUnk6));
        return;
    }
    HeapFree(g_Menu->unk330);
}

void GearShopMenuMenuUnk1Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk348 = HeapAlloc(sizeof(MenuUnk1), 0);
        bzero(g_Menu->unk348, sizeof(MenuUnk1));
        return;
    }
    HeapFree(g_Menu->unk348);
}

void GearShopMenuMenuUnk7Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->unk1E20 = HeapAlloc(sizeof(MenuUnk7), 0);
        bzero(g_Menu->unk1E20, sizeof(MenuUnk7));
        return;
    }
    HeapFree(g_Menu->unk1E20);
}

void GearShopMenuMenuShopManager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->pShop = HeapAlloc(sizeof(MenuShop), 0);
        bzero(g_Menu->pShop, sizeof(MenuShop));
        return;
    }
    HeapFree(g_Menu->pShop);
}

void GearShopMenuMenuUnk8Manager(u_char isInitialization) {
    if (isInitialization) {
        g_Menu->menuUnk8 = HeapAlloc(sizeof(MenuUnk8), 0);
        bzero(g_Menu->menuUnk8, sizeof(MenuUnk8));
        return;
    }
    HeapFree(g_Menu->menuUnk8);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", GearShopMenuLoadResources);

void GearShopMenuFilterPartyMembers(void) {
    int i;
    int flags;

    g_Menu->menu1Choice = 4;
    g_Menu->unk337 = 0xFF;
    g_Menu->unk326 = 0x3C;
    g_Menu->unk334 = 0;
    g_Menu->unk335 = 0;

    flags = g_GameState.unk1D30 & g_GameState.FrMask & 0x77F;

    // Filter availableCharacters by if gearId != 0xff
    for(i = 0; i < 16; i++) {
        if( GearShopMenuIsCharacterFlagSet(flags, i) > 0 && g_GameState.characters[i].gearId != 0xFF ) {
            g_Menu->availableCharacters[i] = TRUE;
        } else {
            g_Menu->availableCharacters[i] = FALSE;
        }
    }

    // Filter by current party
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

void func_801C5CA8(MenuString* pMenuString, s32 arg1, s32 arg2, u8 attributes) {
    s32 tpage_offset;
    int i;
    POLY_FT4* quad;

    for (i = 0; i < 2; i++) {
        quad = &pMenuString->polys[i];
        tpage_offset = 0;

        SetPolyFT4(quad);
        SetSemiTrans(quad, 0);
        SetShadeTex(quad, 0);
        setRGB0(quad, 0x80, 0x80, 0x80);

        if (!attributes) {
            pMenuString->unk7C = (arg1 & 1);
            setTPage(quad, 0, 0, 0x140, 0);

#define texCoordV  (((arg1 + arg2) / 4) * 13)
#define texCoordU  (((arg1 / 2) & 1) << 7)

            setUV4(
                quad,
                texCoordU,               texCoordV,
                texCoordU + pMenuString->width, texCoordV,
                texCoordU,               texCoordV + 13,
                texCoordU + pMenuString->width, texCoordV + 13
            );
#undef texCoordV
#undef texCoordU
        } else {
            if (!(attributes & 0x80)) {
                tpage_offset = 0x20;
                SetSemiTrans(quad, 1);
                setRGB0(quad, tpage_offset, tpage_offset, tpage_offset);
            }

            pMenuString->unk7C = (attributes & 0x7F) + 0xFF;
            setTPage(quad, 0, 0, 0x180, 0x80);
            quad->tpage = tpage_offset | quad->tpage;

#define texCoordU ((arg1 & 1) * 0x60)
#define texCoordV (((arg1 / 2) * 13) + arg2)

            setUV4(
                quad,
                texCoordU,               texCoordV,
                texCoordU + pMenuString->width, texCoordV,
                texCoordU,               texCoordV + 13,
                texCoordU + pMenuString->width, texCoordV + 13
            );
#undef texCoordV
#undef texCoordU
        }
        pMenuString->polys[i].clut = pMenuString->unk7C ? g_SystemPalette2 : g_SystemPalette1;
    }

    pMenuString->unk7F = 0;
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C5EE8);

void func_801C6098(void) {
    u32* pImg;
    RECT rect;
    u8 _unused[2];

    pImg = HeapAlloc(0x20, 0x0);
    bzero(pImg, 0x20);
    ((u16 *)pImg)[1] = 0x7fff;

    rect.x = 0;
    rect.y = 0x1C0;
    rect.w = 0x10;
    rect.h = 1;

    LoadImage(&rect, pImg);
    DrawSync(0);
    HeapFree(pImg);
}

/* initMenuGeometry() ? */
void func_801C6114(void) {
    SystemTransferPaletteToVRAM(0, 0x1D1);
    g_Menu->unk4E0[0].pVramBuffer = HeapAlloc(0x38E, 0);
    func_801C5EE8(g_Menu->unk4E0, &D_801D6A80, 0, 4);
    func_801C6098();
}

void GearShopMenuInitializeWindowBorders(void) {
    POLY_FT4 _unused;

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

// GearShopMenuSetPolyGradientColor
void func_801C668C(POLY_G4* pPoly, u_char red, u_char green, u_char blue) {
    SetPolyG4(pPoly);
    setRGB0(pPoly, red, green, blue);
    setRGB1(pPoly, red, green, blue);
    setRGB2(pPoly, 0, 0, 0);
    setRGB3(pPoly, 0, 0, 0);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6708);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6A54);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801C6E74);

// TODO: counterpart in ShopMenu uses u_short, but a number of matches break if we define this using u_short here
void GearShopMenuSetVertices(SVECTOR* pVertices, u_short x, u_short y, u_short width, u_short height) {
    pVertices[0].vx = x - 160;
    pVertices[0].vy = y - 112;
    pVertices[0].vz = 0;

    pVertices[1].vx = x + width - 160;
    pVertices[1].vy = y - 112;
    pVertices[1].vz = 0;

    pVertices[2].vx = x - 160;
    pVertices[2].vy = y + height - 112;
    pVertices[2].vz = 0;

    pVertices[3].vx = x + width - 160;
    pVertices[3].vy = y + height - 112;
    pVertices[3].vz = 0;
}

void GearShopMenuSetWindowBorderPrimitive(P_TAG* pTag) {
    SetSemiTrans(pTag, 1);
    SetShadeTex(pTag, 0);
    setRGB0(pTag, 128, 128, 128);
}

void GearShopMenuUpdateScrollBarHandle(int x, int y, int scrollHandleHeight, int numItems, int scrollOffset) {
    int yOffset = 0;

    if (!g_Menu->pManager->scrollHandleActive) {
        g_Menu->pScrollHandle = HeapAlloc(sizeof(MenuScrollBarHandle), 0x0);
        bzero((u8 *)g_Menu->pScrollHandle, sizeof(MenuScrollBarHandle));
    }

    // If the total number of items in the window fits within what we can view,
    // there's no need for scrolling so we set the scroll handle height to fill
    // the entire scroll bar.
    if (numItems <= SHOP_MAX_ITEMS_IN_VIEW) {
        scrollHandleHeight = 100;
    }
    // Compute the Y offset based on our current scroll offset
    else {
        yOffset = (scrollOffset * 100) / (numItems - SHOP_MAX_ITEMS_IN_VIEW);
        yOffset = (yOffset * 4000) / 10000;
    }

    func_8002675C(g_Menu->resources, MENU_TEX_SCROLL_BAR_HANDLE,
        g_Menu->pScrollHandle->polys, g_Menu->renderContext,
        x, y, 0x1000
    );

    GearShopMenuSetVertices(
        g_Menu->pScrollHandle->vertices,
        x, y + yOffset,
        8, scrollHandleHeight
    );

    g_Menu->pScrollHandle->renderContext = g_Menu->renderContext;
    g_Menu->pManager->scrollHandleActive = TRUE;
}

void GearShopMenuFreeScrollBarHandle(void) {
    g_Menu->pManager->scrollHandleActive = FALSE;
    HeapFree(g_Menu->pScrollHandle);
}

void GearShopMenuInitializeArrowCursor(u_char index) {
    MenuArrowCursor* pCursor;

    pCursor = HeapAlloc(sizeof(MenuArrowCursor), 0);
    g_Menu->arrowCursors[index] = pCursor;
    bzero((u8* ) pCursor, sizeof(MenuArrowCursor));
    g_Menu->arrowCursors[index]->curAnimFrame = 4;
    g_Menu->arrowCursors[index]->animFrameDuration = 0;
}

void GearShopMenuUpdateArrowCursor(s32 arg0, s32 arg1, u8 arg2, u_char cursorIndex) {
    POLY_FT4* pPoly;
    MenuArrowCursor* pCursor = g_Menu->arrowCursors[cursorIndex];
    int lineHeight;
    u8 shouldRenderCursor;

    if( ++pCursor->animFrameDuration >= 6) {
        if(--pCursor->curAnimFrame < 0) {
            pCursor->curAnimFrame = 4;
        }
        pCursor->animFrameDuration = 0;
    }

    if( arg2 == 0) {
        lineHeight = (FONT_LETTER_HEIGHT * arg0) + 50;
        shouldRenderCursor = TRUE;
    }

    if(shouldRenderCursor) {
        func_8002675C(
            g_Menu->resources,
            pCursor->curAnimFrame + MENU_TEX_ARROW_CURSOR,
            &pCursor->polys[0],
            g_Menu->renderContext,
            0,
            0,
            0x1000
        );
        pPoly = &pCursor->polys[g_Menu->renderContext];
        GearShopMenuSetVertices(
            pCursor->vertices,
            pPoly->x0 + 0x1c,
            pPoly->y0 + lineHeight,
            pPoly->x1 - pPoly->x0,
            pPoly->y3 - pPoly->y0
        );
        pCursor->renderContext = g_Menu->renderContext;
        g_Menu->pManager->shouldRenderArrowCursor[cursorIndex] = TRUE;
        return;
    }
    g_Menu->pManager->shouldRenderArrowCursor[cursorIndex] = FALSE;
}

void GearShopMenuFreeArrowCursor(u_char cursorIndex) {
    HeapFree(g_Menu->arrowCursors[cursorIndex]);
    g_Menu->pManager->shouldRenderArrowCursor[cursorIndex] = FALSE;
}

void GearShopMenuInitializeWindowGraphics(u_char windowIndex) {
    RECT rect;
    MenuWindow* pWindow;
    u_char i;

    pWindow = g_Menu->windows[windowIndex];

    rect.y = 0;
    rect.x = 0;
    rect.h = 256;
    rect.w = 256;

    g_Menu->pManager->shouldRenderWindow[windowIndex] = FALSE;
    g_Menu->pManager->unk27[windowIndex] = FALSE;

    // Window background
    for (i = 0; i < 2; i++) {
        SetPolyG4(&pWindow->polysBackground[i]);
        setRGB0(&pWindow->polysBackground[i], 104, 104, 104);
        setRGB1(&pWindow->polysBackground[i], 104, 104, 104);
        setRGB2(&pWindow->polysBackground[i], 104, 104, 104);
        setRGB3(&pWindow->polysBackground[i], 104, 104, 104);
        SetSemiTrans(&pWindow->polysBackground[i], 1);
        SetDrawMode(
            &pWindow->drawModes[i],
            0, 0,
            GetTPage(0, 0, g_Menu->texPageX0, g_Menu->texPageY0),
            &rect
        );
    }

    // Window borders
    for (i = 0; i < 4; i++) {
        SetPolyFT4(&pWindow->polysWindowBorderTop[i]);
        SetShadeTex(&pWindow->polysWindowBorderTop[i], 1);
        setRGB0(&pWindow->polysWindowBorderTop[i], 0xFF, 0xFF, 0xFF);
        pWindow->polysWindowBorderTop[i].tpage = GetTPage(g_Menu->texPage0, 0, g_Menu->texPageX0, g_Menu->texPageY0);
        pWindow->polysWindowBorderTop[i].clut = GetClut(g_Menu->clutX0, g_Menu->clutY0);

        SetPolyFT4(&pWindow->polysWindowBorderBottom[i]);
        SetShadeTex(&pWindow->polysWindowBorderBottom[i], 1);
        setRGB0(&pWindow->polysWindowBorderBottom[i], 0xFF, 0xFF, 0xFF);
        pWindow->polysWindowBorderBottom[i].tpage = GetTPage(g_Menu->texPage1, 0, g_Menu->texPageX1, g_Menu->texPageY1);
        pWindow->polysWindowBorderBottom[i].clut = GetClut(g_Menu->clutX1, g_Menu->clutY1);

        SetPolyFT4(&pWindow->polysWindowBorderLeft[i]);
        SetShadeTex(&pWindow->polysWindowBorderLeft[i], 1);
        setRGB0(&pWindow->polysWindowBorderLeft[i], 0xFF, 0xFF, 0xFF);
        pWindow->polysWindowBorderLeft[i].tpage = GetTPage(g_Menu->texPage2, 0, g_Menu->texPageX2, g_Menu->texPageY2);
        pWindow->polysWindowBorderLeft[i].clut = GetClut(g_Menu->clutX2, g_Menu->clutY2);

        SetPolyFT4(&pWindow->polysWindowBorderRight[i]);
        SetShadeTex(&pWindow->polysWindowBorderRight[i], 1);
        setRGB0(&pWindow->polysWindowBorderRight[i], 0xFF, 0xFF, 0xFF);
        pWindow->polysWindowBorderRight[i].tpage = GetTPage(g_Menu->texPage3, 0, g_Menu->texPageX3, g_Menu->texPageY3);
        pWindow->polysWindowBorderRight[i].clut = GetClut(g_Menu->clutX3, g_Menu->clutY3);
    }
}

void GearShopMenuInitializeScrollBar(u_char windowIndex, u_short x, u_short y, u_short width, u_short height) {
    MenuWindow* pWindow = g_Menu->windows[windowIndex];

    // Top ornament
    func_8002675C(
        g_Menu->resources,
        MENU_TEX_SCROLL_BAR_ORNAMENT,
        pWindow->polysScrollBarEnds,
        g_Menu->renderContext,
        x, y, 0x1000
    );

    // Bottom ornament
    func_800263E4(
        g_Menu->resources,
        MENU_TEX_SCROLL_BAR_ORNAMENT,
        &pWindow->polysScrollBarEnds[2],
        g_Menu->renderContext,
        x,
        y + height - 8,
        0x1000, 0, 1
    );

    func_8002675C(
        g_Menu->resources,
        MENU_TEX_SCROLL_BAR_EMPTY,
        pWindow->polysScrollBarEmpty,
        g_Menu->renderContext,
        x,
        y + 8,
        0x1000
    );

    GearShopMenuSetVertices(&pWindow->vertsScrollBarEnds[0], x, y, 8, 8);
    GearShopMenuSetVertices(&pWindow->vertsScrollBarEnds[4], x, y + height, 8, -8);
    GearShopMenuSetVertices(&pWindow->vertsScrollBarEmpty[0], x, y + 8, 8, height - 8);
}

void GearShopMenuInitializeWindowBorderCorners(u_char windowIndex, u_short x, u_short y, u_short width, u_short height) {
    MenuWindow* pWindow = g_Menu->windows[windowIndex];
    int i;

    pWindow->unk710 = 0;
    pWindow->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_TOP_LEFT,
        &pWindow->polysWindowBorderCorners[pWindow->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    pWindow->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_TOP_RIGHT,
        &pWindow->polysWindowBorderCorners[pWindow->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    pWindow->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_BOTTOM_LEFT,
        &pWindow->polysWindowBorderCorners[pWindow->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );
    pWindow->unk710 += func_8002675C(
        g_Menu->resources,
        MENU_TEX_WINDOW_BORDER_BOTTOM_RIGHT,
        &pWindow->polysWindowBorderCorners[pWindow->unk710*2],
        g_Menu->renderContext, 0, 0, 0x1000
    );

    GearShopMenuSetVertices(
        &pWindow->vertsWindowBorderCorners[0], 
        x - 8, y +  8, 16, -16
    );
    GearShopMenuSetVertices(
        &pWindow->vertsWindowBorderCorners[4], 
        x + width + 8, y + 8, -16, -16
    );
    GearShopMenuSetVertices(
        &pWindow->vertsWindowBorderCorners[8], 
        x - 8, (y + height) - 8, 16, 16
    );
    GearShopMenuSetVertices(
        &pWindow->vertsWindowBorderCorners[0xC], 
        x + width + 8, (y + height) - 8, -16, 16
    );

    for(i = 0; i < 4; i++) {
        GearShopMenuSetWindowBorderPrimitive(&pWindow->polysWindowBorderCorners[(i*2) + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderTop(u_char windowIndex, u_short x, u_short y, u_short width) {
    MenuWindow* pWindow = g_Menu->windows[windowIndex];
    int i;
    int innerWidth;
    u_short halfInnerWidth;

    setUV4(
        &pWindow->polysWindowBorderTop[g_Menu->renderContext],
        0, 132,
        7, 132,
        0, 148,
        7, 148
    );
    setUV4(
        &pWindow->polysWindowBorderTop[2 + g_Menu->renderContext],
        0, 132,
        7, 132,
        0, 148,
        7, 148
    );

    innerWidth = width - (MENU_WINDOW_BORDER_SIZE * 2);
    halfInnerWidth = innerWidth / 2;

    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderTop1,
        x + MENU_WINDOW_BORDER_SIZE,
        y - MENU_WINDOW_BORDER_SIZE,
        halfInnerWidth,
        MENU_WINDOW_BORDER_SIZE * 2
    );
    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderTop2,
        x + MENU_WINDOW_BORDER_SIZE + halfInnerWidth,
        y - MENU_WINDOW_BORDER_SIZE,
        halfInnerWidth,
        MENU_WINDOW_BORDER_SIZE * 2
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive(
            (P_TAG *)&pWindow->polysWindowBorderTop[i * 2 + g_Menu->renderContext]
        );
    }
}

void GearShopMenuSetWindowBorderBottom(u_char windowIndex, u_short x, u_short y, u_short width, u_short height) {
    MenuWindow* pWindow;
    int i;
    int innerWidth;

    pWindow = g_Menu->windows[windowIndex];

    setUV4(
        &pWindow->polysWindowBorderBottom[g_Menu->renderContext],
        8, 132,
        15, 132,
        8, 148,
        15, 148
    );

    setUV4(
        &pWindow->polysWindowBorderBottom[2 + g_Menu->renderContext],
        8, 132,
        15, 132,
        8, 148,
        15, 148
    );

    innerWidth = width - 16;
    width = innerWidth / 2;
    height = y + height - 8;

    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderBottom1,
        x + 8,
        height,
        width,
        16
    );
    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderBottom2,
        x + 8 + width,
        height,
        width,
        16
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive((P_TAG *)&pWindow->polysWindowBorderBottom[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderLeft(u_char windowIndex, u_short x, u_short y, u_short height) {
    MenuWindow* pWindow;
    int i;
    int innerHeight;
    u_short halfInnerHeight;

    pWindow = g_Menu->windows[windowIndex];

    setUV4(
        &pWindow->polysWindowBorderLeft[g_Menu->renderContext],
        16, 132,
        32, 132,
        16, 139,
        32, 139
    );

    setUV4(
        &pWindow->polysWindowBorderLeft[2 + g_Menu->renderContext],
        16, 132,
        32, 132,
        16, 139,
        32, 139
    );

    innerHeight = height - 16;
    halfInnerHeight = innerHeight / 2;

    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderLeft1,
        x - 8,
        y + 8,
        16,
        halfInnerHeight
    );
    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderLeft2,
        x - 8,
        y + 8 + halfInnerHeight,
        16,
        halfInnerHeight
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive((P_TAG *)&pWindow->polysWindowBorderLeft[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindowBorderRight(u_char windowIndex, u_short x, u_short y, u_short width, u_short height) {
    MenuWindow* pWindow;
    int i;
    int innerHeight;
    u_short halfInnerHeight;

    pWindow = g_Menu->windows[windowIndex];

    setUV4(
        &pWindow->polysWindowBorderRight[g_Menu->renderContext],
        16, 140,
        32, 140,
        16, 147,
        32, 147
    );

    setUV4(
        &pWindow->polysWindowBorderRight[2 + g_Menu->renderContext],
        16, 140,
        32, 140,
        16, 147,
        32, 147
    );

    width = x + width - 8;
    innerHeight = height - 16;
    halfInnerHeight = innerHeight / 2;

    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderRight1,
        width,
        y + 8,
        16,
        halfInnerHeight
    );
    GearShopMenuSetVertices(
        pWindow->vertsWindowBorderRight2,
        width,
        y + 8 + halfInnerHeight,
        16,
        halfInnerHeight
    );

    for (i = 0; i < 2; i++) {
        GearShopMenuSetWindowBorderPrimitive(&pWindow->polysWindowBorderRight[i * 2 + g_Menu->renderContext]);
    }
}

void GearShopMenuSetWindow(u_char windowIndex, u_short x, u_short y, u_short width, u_short height, u8 arg5, int zIndex, u_char hasScrollbar) {
    MenuWindow* pWindow;

    pWindow = g_Menu->windows[windowIndex];
    g_Menu->pManager->shouldRenderWindow[windowIndex] = FALSE;
    GearShopMenuSetVertices(pWindow->vertsBackground, x, y, width, height);
    GearShopMenuInitializeWindowBorderCorners(windowIndex, x, y, width, height);
    GearShopMenuSetWindowBorderTop(windowIndex, x, y, width);
    GearShopMenuSetWindowBorderBottom(windowIndex, x, y, width, height);
    GearShopMenuSetWindowBorderLeft(windowIndex, x, y, height);
    GearShopMenuSetWindowBorderRight(windowIndex, x, y, width, height);
    if (hasScrollbar) {
        GearShopMenuInitializeScrollBar(windowIndex, x, y, width, height);
    }
    pWindow->hasScrollBar = hasScrollbar;
    pWindow->unk714 = arg5;
    pWindow->zIndex = zIndex;
    pWindow->renderContext = g_Menu->renderContext;
    g_Menu->pManager->shouldRenderWindow[windowIndex] = TRUE;
}

void GearShopMenuFreeWindow(u_char index) {
    g_Menu->pManager->shouldRenderWindow[index] = FALSE;
    g_Menu->pManager->unk27[index] = FALSE;
    HeapFree(g_Menu->windows[index]);
    HeapFree(g_Menu->windowParameters[index]);
}

void GearShopMenuInitializeWindow(u_char windowIndex, u_short x, u_short y, u_short width, u_short height, u_char shouldInitializeHandle, u8 arg6, int zIndex, u_char hasScrollbar) {
    MenuWindowParameters* pWindowParameters;

    if (windowIndex >= 2) {
        g_Menu->windows[windowIndex] = HeapAlloc(sizeof(MenuWindow), 0);
        bzero((u8* ) g_Menu->windows[windowIndex], sizeof(MenuWindow));
        g_Menu->windowParameters[windowIndex] = HeapAlloc(sizeof(MenuWindowParameters), 0);
        bzero((u8* ) g_Menu->windowParameters[windowIndex], sizeof(MenuWindowParameters));
        GearShopMenuInitializeWindowGraphics(windowIndex);
    }

    pWindowParameters = g_Menu->windowParameters[windowIndex];
    if (shouldInitializeHandle) {
        pWindowParameters->index = windowIndex;
        pWindowParameters->unk11 = 0;
        pWindowParameters->x = x;
        pWindowParameters->y = y;
        pWindowParameters->width = width;
        pWindowParameters->height = height;
        pWindowParameters->unk8 = 0;
        pWindowParameters->unkA = 0;
        g_Menu->pManager->unk27[windowIndex] = TRUE;
        pWindowParameters->unk12 = arg6;
        pWindowParameters->zIndex = zIndex;
        return;
    }

    GearShopMenuSetWindow(windowIndex, x, y, width, height, arg6, zIndex, hasScrollbar);
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

void GearShopMenuRenderPolygons(int count, SVECTOR* pVertices, POLY_FT4* pPolys, int renderContext) {
    long interpolated;
    long flag;
    int i;

    for (i = 0; i < count; i++) {
        RotTransPers4(
            &pVertices[i*4 + 0],
            &pVertices[i*4 + 1],
            &pVertices[i*4 + 2],
            &pVertices[i*4 + 3],
            (long *)&pPolys[i*2 + renderContext].x0,
            (long *)&pPolys[i*2 + renderContext].x1,
            (long *)&pPolys[i*2 + renderContext].x2,
            (long *)&pPolys[i*2 + renderContext].x3,
            &interpolated,
            &flag
        );

        AddPrim(&g_Menu->pGfxEnv->ot[4], &pPolys[i*2 + renderContext]);
    }
}

void GearShopMenuRenderString(int stringLength, POLY_FT4* pPolys, int renderContext) {
    int i;

    for(i = 0; i < stringLength; i++) {
        AddPrim(&g_Menu->pGfxEnv->ot[4], &pPolys[(2*i) + renderContext]);
    }
}

void GearShopMenuRenderScrollBarHandle(void) {
    if (g_Menu->pManager->scrollHandleActive) {
        GearShopMenuRenderPolygons(
            1,
            g_Menu->pScrollHandle->vertices,
            g_Menu->pScrollHandle,
            g_Menu->pScrollHandle->renderContext
        );
    }
}

void func_801C959C(void) {
    AddPrim(
        &g_Menu->pGfxEnv->ot[4], 
        &g_Menu->unk348->drModes1[g_Menu->unk348->unk159]
    );
    if (g_Menu->pManager->unk4) {
        AddPrim(
            &g_Menu->pGfxEnv->ot[4], 
            &g_Menu->unk348->polysPointerCursor[g_Menu->unk348->cursorRenderContext]
        );
    }
}

void func_801C962C(void) {
    if ((g_Menu->pManager->unk52[1]) && (g_gearShopAvailableCharacterCount >= 2)) {
        GearShopMenuRenderPolygons(4, g_Menu->unk440->unk140, g_Menu->unk440, g_Menu->unk440->unk1C0);
    }
}

void GearShopMenuRenderTopWindowBorder(int windowId) {
    long interpolated;
    long flag;
    MenuWindow* window;

    window = g_Menu->windows[windowId];

    RotTransPers4(
        &window->vertsWindowBorderTop1[0],
        &window->vertsWindowBorderTop1[1],
        &window->vertsWindowBorderTop1[2],
        &window->vertsWindowBorderTop1[3],
        (long*) &window->polysWindowBorderTop[window->renderContext].x0,
        (long*) &window->polysWindowBorderTop[window->renderContext].x1,
        (long*) &window->polysWindowBorderTop[window->renderContext].x2,
        (long*) &window->polysWindowBorderTop[window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderTop[window->renderContext]
    );

    RotTransPers4(
        &window->vertsWindowBorderTop2[0],
        &window->vertsWindowBorderTop2[1],
        &window->vertsWindowBorderTop2[2],
        &window->vertsWindowBorderTop2[3],
        (long*) &window->polysWindowBorderTop[2 + window->renderContext].x0,
        (long*) &window->polysWindowBorderTop[2 + window->renderContext].x1,
        (long*) &window->polysWindowBorderTop[2 + window->renderContext].x2,
        (long*) &window->polysWindowBorderTop[2 + window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderTop[2 + window->renderContext]
    );
}

void GearShopMenuRenderBottomWindowBorder(int windowId) {
    long interpolated;
    long flag;
    MenuWindow* window;

    window = g_Menu->windows[windowId];

    RotTransPers4(
        &window->vertsWindowBorderBottom1[0],
        &window->vertsWindowBorderBottom1[1],
        &window->vertsWindowBorderBottom1[2],
        &window->vertsWindowBorderBottom1[3],
        (long*) &window->polysWindowBorderBottom[window->renderContext].x0,
        (long*) &window->polysWindowBorderBottom[window->renderContext].x1,
        (long*) &window->polysWindowBorderBottom[window->renderContext].x2,
        (long*) &window->polysWindowBorderBottom[window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderBottom[window->renderContext]
    );

    RotTransPers4(
        &window->vertsWindowBorderBottom2[0],
        &window->vertsWindowBorderBottom2[1],
        &window->vertsWindowBorderBottom2[2],
        &window->vertsWindowBorderBottom2[3],
        (long*) &window->polysWindowBorderBottom[2 + window->renderContext].x0,
        (long*) &window->polysWindowBorderBottom[2 + window->renderContext].x1,
        (long*) &window->polysWindowBorderBottom[2 + window->renderContext].x2,
        (long*) &window->polysWindowBorderBottom[2 + window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderBottom[2 + window->renderContext]
    );
}


void GearShopMenuRenderLeftWindowBorder(int windowId) {
    long interpolated;
    long flag;
    MenuWindow* window;

    window = g_Menu->windows[windowId];

    RotTransPers4(
        &window->vertsWindowBorderLeft1[0],
        &window->vertsWindowBorderLeft1[1],
        &window->vertsWindowBorderLeft1[2],
        &window->vertsWindowBorderLeft1[3],
        (long*) &window->polysWindowBorderLeft[window->renderContext].x0,
        (long*) &window->polysWindowBorderLeft[window->renderContext].x1,
        (long*) &window->polysWindowBorderLeft[window->renderContext].x2,
        (long*) &window->polysWindowBorderLeft[window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderLeft[window->renderContext]
    );

    RotTransPers4(
        &window->vertsWindowBorderLeft2[0],
        &window->vertsWindowBorderLeft2[1],
        &window->vertsWindowBorderLeft2[2],
        &window->vertsWindowBorderLeft2[3],
        (long*) &window->polysWindowBorderLeft[2 + window->renderContext].x0,
        (long*) &window->polysWindowBorderLeft[2 + window->renderContext].x1,
        (long*) &window->polysWindowBorderLeft[2 + window->renderContext].x2,
        (long*) &window->polysWindowBorderLeft[2 + window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderLeft[2 + window->renderContext]
    );
}

void GearShopMenuRenderRightWindowBorder(int windowId) {
    long interpolated;
    long flag;
    MenuWindow* window;

    window = g_Menu->windows[windowId];

    RotTransPers4(
        &window->vertsWindowBorderRight1[0],
        &window->vertsWindowBorderRight1[1],
        &window->vertsWindowBorderRight1[2],
        &window->vertsWindowBorderRight1[3],
        (long*) &window->polysWindowBorderRight[window->renderContext].x0,
        (long*) &window->polysWindowBorderRight[window->renderContext].x1,
        (long*) &window->polysWindowBorderRight[window->renderContext].x2,
        (long*) &window->polysWindowBorderRight[window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderRight[window->renderContext]
    );

    RotTransPers4(
        &window->vertsWindowBorderRight2[0],
        &window->vertsWindowBorderRight2[1],
        &window->vertsWindowBorderRight2[2],
        &window->vertsWindowBorderRight2[3],
        (long*) &window->polysWindowBorderRight[2 + window->renderContext].x0,
        (long*) &window->polysWindowBorderRight[2 + window->renderContext].x1,
        (long*) &window->polysWindowBorderRight[2 + window->renderContext].x2,
        (long*) &window->polysWindowBorderRight[2 + window->renderContext].x3,
        &interpolated,
        &flag
    );
    AddPrim(
        &g_Menu->pGfxEnv->ot[window->zIndex],
        &window->polysWindowBorderRight[2 + window->renderContext]
    );
}

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

void GearShopMenuRenderWindows(void) {
    SVECTOR rotation;
    VECTOR translation;
    MATRIX matTransform;
    SVECTOR _unused;
    MenuWindow* pWindow;
    int i;

    for(i = 0; i < MENU_MAX_NUM_WINDOWS; i++) {
        if (g_Menu->pManager->shouldRenderWindow[i]) {
            pWindow = g_Menu->windows[i];

            if(pWindow->unk714 == 0) {
                PushMatrix();
                rotation.vz = 0;
                rotation.vy = 0;
                rotation.vx = 0;
                translation.vy = 0;
                translation.vx = 0;
                translation.vz = 512;
                RotMatrix(&rotation, &matTransform);
                TransMatrix(&matTransform, &translation);
                SetRotMatrix(&matTransform);
                SetTransMatrix(&matTransform);

                GearShopMenuRenderWindowBorderCorners(i);
                if (pWindow->hasScrollBar) {
                    GearShopMenuRenderScrollBar(i);
                }
                GearShopMenuRenderTopWindowBorder(i);
                GearShopMenuRenderBottomWindowBorder(i);
                GearShopMenuRenderLeftWindowBorder(i);
                GearShopMenuRenderRightWindowBorder(i);
                GearShopMenuRenderWindowBackground(i);

                PopMatrix();
            } else {
                GearShopMenuRenderWindowBorderCorners(i);
                if (pWindow->hasScrollBar) {
                    GearShopMenuRenderScrollBar(i);
                }
                GearShopMenuRenderTopWindowBorder(i);
                GearShopMenuRenderBottomWindowBorder(i);
                GearShopMenuRenderLeftWindowBorder(i);
                GearShopMenuRenderRightWindowBorder(i);
                GearShopMenuRenderWindowBackground(i);
            }
        }
    }
}

void GearShopMenuRenderPointerCursors(void) {
    int i;

    if (g_Menu->pManager->shouldRenderCursors) {
        for (i = 0; i < MENU_MAX_NUM_CURSORS; i++) {
            if (g_Menu->pCursors->shouldRender[i]) {
                if (g_Menu->pCursors->unk144[i]) {
                    setXY4(
                        &g_Menu->pCursors->polysCursor[i * 2 + g_Menu->pCursors->renderContexts[i]],
                        D_801D6AFC[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 8,
                        D_801D6B7C[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] - 6,
                        D_801D6AFC[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 24,
                        D_801D6B7C[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] - 6,
                        D_801D6AFC[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 8,
                        D_801D6B7C[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 10,
                        D_801D6AFC[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 24,
                        D_801D6B7C[D_801D6A84[g_Menu->menuUnk2->unk4F7C]] + 10
                    );
                }

                AddPrim(
                    &g_Menu->pGfxEnv->ot[4],
                    &g_Menu->pCursors->polysCursor[i * 2 + g_Menu->pCursors->renderContexts[i]]
                );
            }
        }
    }
}

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
    int i;

    for(i = 0; i < 8; i++) {
        if (g_Menu->pManager->unkC[i]) {
            AddPrim(
                &g_Menu->pGfxEnv->ot[4],
                &g_Menu->unk6E0[i].polys[g_Menu->unk6E0[i].renderContext]
            );
        }
    }
}
// identical to func_801CA09C() in ShopMenu
void func_801CA874(void) {
    long interpolated;
    long flag;
    int i;

    for (i = 0; i < 6; i++) {
        if (g_Menu->pManager->unk14[i]) {
            if (g_Menu->unkAE0[i].unk7F) {
                RotTransPers4(
                    &g_Menu->unkAE0[i].vertices[0],
                    &g_Menu->unkAE0[i].vertices[1],
                    &g_Menu->unkAE0[i].vertices[2],
                    &g_Menu->unkAE0[i].vertices[3],
                    (long*)&g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext].x0,
                    (long*)&g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext].x1,
                    (long*)&g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext].x2,
                    (long*)&g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext].x3,
                    &interpolated,
                    &flag
                );
                AddPrim(
                    &g_Menu->pGfxEnv->ot[4],
                    &g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext]
                );
            } else {
                AddPrim(
                    &g_Menu->pGfxEnv->ot[4],
                    &g_Menu->unkAE0[i].polys[g_Menu->unkAE0[i].renderContext]
                );
            }

        }
    }
}

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

// identical to func_801CA22C in ShopMenu
void func_801CAA7C(void) {
    long interpolation;
    long code;
    MenuString* pMenuString;
    int i;

    if(g_Menu->pManager->unk2B != 0) {
        for(i = 0; i < 3; i++) {
            pMenuString = g_Menu->unk1DE0[i];

            if(pMenuString->unk7F) {
                RotTransPers4(
                    &pMenuString->vertices[0],
                    &pMenuString->vertices[1],
                    &pMenuString->vertices[2],
                    &pMenuString->vertices[3],
                    (long *)&pMenuString->polys[pMenuString->renderContext].x0,
                    (long *)&pMenuString->polys[pMenuString->renderContext].x1,
                    (long *)&pMenuString->polys[pMenuString->renderContext].x2,
                    (long *)&pMenuString->polys[pMenuString->renderContext].x3,
                    &interpolation,
                    &code
                );
                AddPrim(&g_Menu->pGfxEnv->ot[4], &pMenuString->polys[pMenuString->renderContext]);
            } else {
                AddPrim(&g_Menu->pGfxEnv->ot[4], &pMenuString->polys[pMenuString->renderContext]);
            }
        }
    }
}

void GearShopMenuRenderBackgroundDim(void) {
}

void func_801CABE0(void) {
    func_801CA754();
    func_801CA7E4();
    func_801CA874();
    func_801CA9EC();
    func_801CAA7C();
}

void GearShopMenuRenderSelectionMenu(void) {
    int i;

    if (g_Menu->pManager->shouldRenderSelectionMenu) {
        if (g_Menu->pSelectionMenu->unk1192 != g_Menu->pSelectionMenu->unk1193) {

            // Render the selection menu as disabled
            if (g_Menu->pSelectionMenu->unk1192) {
                for (i = 0; i < g_Menu->pSelectionMenu->numTexts; i++) {
                    SetSemiTrans(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 1);
                    SetShadeTex(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 0);
                    g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx].tpage |= 0x20;
                    setRGB0(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 32, 32, 32);
                }

                for (i = 0; i < g_Menu->pSelectionMenu->numCursors; i++) {
                    SetSemiTrans(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 1);
                    SetShadeTex(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 0);
                    g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx].tpage |= 0x20;
                    setRGB0(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 32, 32, 32);
                }

            // Render the seleciton menu as active
            } else {
                for (i = 0; i < g_Menu->pSelectionMenu->numTexts; i++) {
                    SetSemiTrans(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 0);
                    SetShadeTex(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 0);
                    g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx].tpage |= 0x20;
                    setRGB0(&g_Menu->pSelectionMenu->polysTexts[i*2 + g_Menu->pSelectionMenu->textsRenderCtx], 128, 128, 128);
                }

                for (i = 0; i < g_Menu->pSelectionMenu->numCursors; i++) {
                    SetSemiTrans(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 0);
                    SetShadeTex(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 0);
                    g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx].tpage |= 0x20;
                    setRGB0(&g_Menu->pSelectionMenu->polysCursors[i*2 + g_Menu->pSelectionMenu->cursorsRenderCtx], 128, 128, 128);
                }
            }

            g_Menu->pSelectionMenu->unk1193 = g_Menu->pSelectionMenu->unk1192;
        }

        GearShopMenuRenderString(g_Menu->pSelectionMenu->numTexts, g_Menu->pSelectionMenu->polysTexts, g_Menu->pSelectionMenu->textsRenderCtx);
        GearShopMenuRenderString(g_Menu->pSelectionMenu->numCursors, g_Menu->pSelectionMenu->polysCursors, g_Menu->pSelectionMenu->cursorsRenderCtx);
    }
}

void func_801CB2E8(void) {
    if (g_Menu->pManager->unkA) {
        GearShopMenuRenderString(g_Menu->unk354->unk1404, g_Menu->unk354->polys500, g_Menu->unk354->unk1409);
        GearShopMenuRenderString(g_Menu->unk354->unk1400, g_Menu->unk354->polys0, g_Menu->unk354->unk1408);
    }
}

void GearShopMenuRenderArrowCursors(void) {
    MenuArrowCursor* pCursor;
    int i;

    for(i = 0; i < MENU_MAX_NUM_ARROW_CURSORS; i++) {
        if (g_Menu->pManager->shouldRenderArrowCursor[i]) {
            pCursor = g_Menu->arrowCursors[i];
            GearShopMenuRenderPolygons(1, pCursor->vertices, pCursor, pCursor->renderContext);
        }
    }
}

void GearShopMenuRender(void) {
    if (g_Menu->shouldDrawMenu) {
        GearShopMenuUpdateWindows();
        func_801CF33C();
        GearShopMenuRenderPointerCursors();
        func_801CABE0();
        func_801C959C();
        GearShopMenuRenderArrowCursors();
        func_801CE32C();
        func_801C962C();
        GearShopMenuRenderScrollBarHandle();
        GearShopMenuRenderSelectionMenu();
        func_801CB2E8();
        GearShopMenuRenderWindows();
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

/* TODO: this function appears to just manipulate objects in memory, it doesn't make any function calls */
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CB690);

/* TODO: This is probably updating a transition effect, but it's not the same effect as ShopMenuUpdateTransitionEffect() */
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
                    0x800
                );
                g_Menu->pCursors->renderContexts[i] = g_Menu->renderContext;
            }
            break;
        case 3:
            func_8002675C(
                g_Menu->resources,
                0x108,
                &g_Menu->pCursors->polysCursor[0],
                g_Menu->renderContext, 0, 0, 0x800
            );
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

void GearShopMenuConfirmationWindowInitialize(u8 stringIndex) {
    MenuWindowParameters* pWindowParams;
    MenuString* pString;
    int i;
    int xPosition;

    xPosition = 0x50;

    GearShopMenuInitializeWindow(4, 0x42, 0x46, 0xC0, 0x40, 1, 1, 4, 0);
    pWindowParams = g_Menu->windowParameters[4];
    while (!pWindowParams->unk11) {
        GearShopMenuUpdateAndRender();
    }

    for (i = 0; i < 4; i++) {
        g_Menu->unk1DE0[i] = HeapAlloc(sizeof(MenuString), 0);
        bzero((u8 *)g_Menu->unk1DE0[i], sizeof(MenuString));

        // Even indices
        if (!(i & 1)) {
            // Buffer size = FONT_LETTER_HEIGHT * 57 * 2
            g_Menu->unk1DE0[i]->pVramBuffer = HeapAlloc(0x5CA, 0);
            g_Menu->unk1DE0[i]->vramDest.x = 320;
            g_Menu->unk1DE0[i]->vramDest.y = ((i / 2) * FONT_LETTER_HEIGHT) + 78;
            g_Menu->unk1DE0[i]->vramDest.w = 58;
            g_Menu->unk1DE0[i]->vramDest.h = FONT_LETTER_HEIGHT;
            continue;
        }

        // Odd indices, share VRAM buffer w/ prev entry
        g_Menu->unk1DE0[i]->pVramBuffer = g_Menu->unk1DE0[i - 1]->pVramBuffer;
    }

    // Render strings to text areas
    for (i = 0; i < 3; i++) {
        pString = g_Menu->unk1DE0[i];
        pString->width = SystemRenderStringEntry(
            GetStringEntry(g_Menu->unk2E0, stringIndex + i),
            pString->pVramBuffer, 0x36, i % 2
        );
        func_801C5CA8(pString, i, 0, 0);
        GearShopMenuSetVertices(
            pString->vertices,
            xPosition,
            (i * 16) + 0x50,
            pString->width,
            FONT_LETTER_HEIGHT
        );
        setUV4(
            &pString->polys[g_Menu->renderContext],
            0,                (i / 2) * FONT_LETTER_HEIGHT + 0x4E,
            pString->width,   (i / 2) * FONT_LETTER_HEIGHT + 0x4E,
            0,                (i / 2) * FONT_LETTER_HEIGHT + 0x5B,
            pString->width,   (i / 2) * FONT_LETTER_HEIGHT + 0x5B
        );
        pString->renderContext = g_Menu->renderContext;
        pString->unk7F = 1;
    }

    // Transfer text areas to VRAM
    LoadImage(&g_Menu->unk1DE0[0]->vramDest, g_Menu->unk1DE0[0]->pVramBuffer);
    LoadImage(&g_Menu->unk1DE0[2]->vramDest, g_Menu->unk1DE0[2]->pVramBuffer);
    DrawSync(0);

    g_Menu->pManager->unk2B = 1;
    HeapFree(g_Menu->unk1DE0[0]->pVramBuffer);
    HeapFree(g_Menu->unk1DE0[2]->pVramBuffer);
    if (g_Menu->pManager->unk5B == 2) {
        g_Menu->pManager->unk5B = 1;
    }
    GearShopMenuUpdateAndRender();
    GearShopMenuUpdateAndRender();
}

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

// GearShopMenuConfirmationWindowGetChoice
u_char func_801CCA40(u_char mode, u8 arg1) {
    u_char choice;
    u_char isRunning;
    u_char curTimer;

    isRunning = TRUE;
    choice = MENU_CHOICE_NO;
    curTimer = 60;

    while (isRunning) {
        if (mode == MENU_AUTO_ADVANCE) {
            g_Menu->pCursors->shouldRender[2] = FALSE;
            g_Menu->pCursors->shouldRender[3] = FALSE;

            // Was any button pressed?
            if (g_Menu->input != MENU_INPUT_IDLE)
                break;

            curTimer--;
            if (curTimer == 0)
                break;
        }
        
        GearShopMenuUpdateAndRender();
        switch (g_Menu->input) {
            case MENU_INPUT_CONFIRM:
                GearShopMenuPlaySoundEffect(2);
                isRunning = FALSE;
                break;
            case MENU_INPUT_BACK:
                choice = MENU_CHOICE_NO;
                isRunning = FALSE;
                break;
            case MENU_INPUT_LEFT:
                if (arg1 == 0) 
                    break;
                g_Menu->pCursors->shouldRender[2] = TRUE;
                g_Menu->pCursors->shouldRender[3] = FALSE;
                choice = MENU_CHOICE_YES;
                break;
            case MENU_INPUT_RIGHT:
                if (arg1 == 0) 
                    break;
                g_Menu->pCursors->shouldRender[2] = FALSE;
                g_Menu->pCursors->shouldRender[3] = TRUE;
                choice = MENU_CHOICE_NO;
                break;
        }
    }
    g_Menu->pCursors->shouldRender[2] = FALSE;
    g_Menu->pCursors->shouldRender[3] = FALSE;

    POSSIBLE_DEBUG_CODE;
    
    return choice;
}

s32 func_801CCC18(u8 arg0, s32 arg1, s32 arg2) {
    u8 unkBool = TRUE;
    u8 result;

    GearShopMenuConfirmationWindowInitialize(arg0);
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
        GearShopMenuConfirmationWindowInitialize(arg1);
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

void GearShopMenuInitializeShopModeSelectionMenu(int count, int* pResourceIDs) {
    int i, j;

    g_Menu->pSelectionMenu->unk1192 = FALSE;
    g_Menu->pSelectionMenu->unk1193 = FALSE;

    g_Menu->pManager->shouldRenderSelectionMenu = TRUE;

    for (i = 1; i <= count; i++) {
        if (i != count) {
            g_Menu->pSelectionMenu->numCursors = 0;
            for(j = 0; j < i; j++) {
                g_Menu->pSelectionMenu->numCursors += func_8002675C(
                    g_Menu->resources,
                    pResourceIDs[j * 2],
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
                    pResourceIDs[j * 2 + 1],
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

// GearShopMenuShopModeMenuHandleSelectedOption
u_char func_801CDC68(void) {
    u_char isRunning;
    u_char selection;

    isRunning = TRUE;
    if (g_Menu->menu1Choice) {
        // Always returns true?
        selection = func_801D5828();
    } else {
        // "Exit" option was selected
        isRunning = FALSE;
    }

    // intentionally using selection w/o intialization
    if (selection) {
        func_801CC528();
        func_801CCE90(4, g_Menu->unk6E0, &D_801D6A20, g_Menu->pManager->unkC);
    }

    // Render selection menu as active agian
    g_Menu->pSelectionMenu->unk1192 = FALSE;
    g_Menu->pSelectionMenu->unk1193 = TRUE;

    g_Menu->pManager->unk4 = TRUE;
    g_Menu->pManager->unk3 = TRUE;
    g_Menu->unk337 = 0xFF;
    g_Menu->pManager->unkA = FALSE;
    
    return isRunning;
}

// Tune up / Buy / Sell / Exit menu
void func_801CDD74(void) {
    u_char isRunning;

    isRunning = TRUE;
    func_801CFAB8(1, D_801D9084);
    g_Menu->pManager->unk5C[7] = 1;

    // Options here are "Tune up", "Buy", "Sell", "Exit"
    g_Menu->menu1Choice = 2; // Start cursor at "Buy" option
    GearShopMenuInitializeShopModeSelectionMenu(5, &D_801D6980);

    func_801CCE90(4, g_Menu->unk6E0, &D_801D6A20, g_Menu->pManager->unkC);
    if (g_gearShopAvailableCharacterCount >= 2) {
        g_Menu->pManager->unk52[1] = 1;
    }
    
    while (isRunning) {
        GearShopMenuUpdateAndRender();
        switch (g_Menu->input) {
            case MENU_INPUT_CONFIRM:
                GearShopMenuPlaySoundEffect(2);
                
                g_Menu->pSelectionMenu->unk1192 = TRUE;
                
                func_801C665C();
                func_801CCEBC(4, g_Menu->pManager->unkC);
                g_Menu->unk348->unk15B = 0x4C;
                isRunning = func_801CDC68();
                g_Menu->unk348->unk15B = 0x40;
                break;
                
            case MENU_INPUT_BACK:
                isRunning = FALSE;
                break;
                
            case MENU_INPUT_DOWN:
                if (g_Menu->menu1Choice) {
                    g_Menu->menu1Choice--;
                } else {
                    g_Menu->menu1Choice = 3;
                }
                break;
                
            case MENU_INPUT_UP:
                if (++g_Menu->menu1Choice >= 4) {
                    g_Menu->menu1Choice = 0;
                }
                break;

            // R1 (Next gear)
            case 9:
                func_801D0398(0);
                break;
                
            // L1 (Prev gear)
            case 10:
                func_801D0398(1);
                break;
        }
        
        if (g_Menu->menu1Choice != g_Menu->unk337) {
            func_801CD838(4, g_Menu->menu1Choice, &D_801D6980);
            func_801CCEE8(4, g_Menu->unk6E0, &D_801D6A20, &D_801D6A30, g_Menu->pManager->unkC, g_Menu->menu1Choice, 0, 0);
            g_Menu->unk337 = g_Menu->menu1Choice;
        }
    }
    
    D_801D697C = 0;
    func_801D5EB8();
    func_801CE2E8();
}

void GearShopMenuMain(void) {
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
    func_801C6708(); // GearShopMenuInitializeBackgrounds
    GearShopMenuInitializeWindowBorders();
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

/*
This is the only function where GearShopMenuSetVertices seem to need two arguments to be defined as int.
It does match if not function signature is provided, so it could be that this function belongs to a different TU
than where GearShopMenuSetVertices is defined.
*/
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CE1D0);
/*
void func_801CE1D0(void) {
    int i;
    int temp;

    for(i = 0; i < 2; i++) {
        func_8002675C(
            g_Menu->resources,
            MENU_TEX_L1_RED_ARROW + i,
            &g_Menu->unk440->polys[i*4],
            g_Menu->renderContext,
            D_801D6FD0[i],
            0x64,
            0x1000
        );
    }

    for(i = 0; i < 4; i++) {
        temp = (i * 2 + g_Menu->renderContext);

        // !!! DOES NOT MATCH DUE TO FUNCTION SIGNATURE !!!
        GearShopMenuSetVertices(
            &g_Menu->unk440->unk140[i*4], 
            g_Menu->unk440->polys[temp].x0, 
            g_Menu->unk440->polys[temp].y0, 
            (g_Menu->unk440->polys[temp].x1 - g_Menu->unk440->polys[temp].x0), 
            (g_Menu->unk440->polys[temp].y3 - g_Menu->unk440->polys[temp].y0)
        );
    }

    g_Menu->unk440->unk1C0 = (u8) g_Menu->renderContext;
}
*/

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

void func_801CF38C(u8 arg0) {
    RECT rect;

    D_801D9088 = HeapAlloc(0x3F6, 0x0);
    bzero(D_801D9088, 0x3F6);
    SystemRenderStringEntry(&g_GameState.strings[arg0], D_801D9088, 0x24, 0);
    setRECT(&rect, 0x180, 0x48, 0x28, 0xD);
    LoadImage(&rect, (u32* ) D_801D9088);
    DrawSync(0);
    HeapFree(D_801D9088);
}

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801CF448);

void func_801CF9BC(u8 arg0, u8 arg1) {
    ArchiveSetIndex(ARCHIVE_DIR_FIELD, 0);

    g_Menu->unk458[arg1]->unk0 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[arg0]), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[arg0], g_Menu->unk458[arg1]->unk0, 0, 0x80);
    ArchiveCdDataSync(0);

    g_Menu->unk458[arg1]->unk4 = HeapAlloc(ArchiveDecodeAlignedSize(D_801D6D7C[arg0] + 1), 0);
    ArchiveReadFileToBuffer(D_801D6D7C[arg0]+1, g_Menu->unk458[arg1]->unk4, 0, 0x80);
    ArchiveCdDataSync(0);

    ArchiveSetIndex(ARCHIVE_DIR_MENUS, 0);
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


// GearShopMenuSetAvailableCharacterCount
void func_801D0348(void) {
    int i;

    for(i = 0; i < MAX_GAME_CHARACTERS; i++) {
        if(g_Menu->availableCharacters[i]) {
            g_gearShopAvailableCharacterCount += 1;
        }
    }
}

// Function handling changing current gear
INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0398);

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D06D8);

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D0D4C);

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

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1078);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1304);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D18F8);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D1F20);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D2054);

void func_801D2784(void) {
    func_801D2054(
        0x96,
        g_GameState.unk221A,
        g_GameState.unk2184,
        3, 1,
        g_GameState.unk2184,
        0
    );
}

void func_801D27C4(void) {
    func_801D2054(
        0x64,
        g_GameState.unk2120,
        g_GameState.unk20BC,
        4, 1,
        g_GameState.unk20BC,
        0
    );
}

// the code is very similar to ShopMenuSellModeMenuHandleSelectedOption but idk what the actual context
// for this is.
void func_801D2804(u8 arg0) {
    int choice;
    u8 unkBool = 1;
    g_Menu->pManager->unk4 = 0;
    g_Menu->pManager->unk3 = 0;
    g_Menu->pManager->unkA = 0;
    func_801CCEBC(4, g_Menu->pManager->unkC);
    choice = g_Menu->menu2Choice + (arg0 * 3);

    switch (choice) {
        case 3:
            func_801D2784();
            break;

        case 4:
            func_801D27C4();
            break;
    }
    func_801D0EC8(unkBool);
    g_Menu->pManager->unkA = 1;
    g_Menu->pManager->unk4 = 1;
    g_Menu->pManager->unk3 = 1;
    func_801CCE90(4, g_Menu->unk6E0, &D_801D6A24, g_Menu->pManager->unkC);
}

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

// https://decomp.me/scratch/7SJpB
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

void func_801D5F94(MenuUnk6* pView, u_char gearId) {
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

    ether = pGear->unk3C * (pGear->unk74 + pGear->unk56);

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

void func_801D6150(MenuUnk6* arg0, u8 arg1) {
    func_801D61B8(arg0, arg1);
    func_801D62A4(arg0, arg1);
    func_801D6250(arg0, arg1);
    func_801D6334(arg0, arg1);
    func_801D6738(arg0, arg1);
}

void func_801D61B8(MenuUnk6* arg0, u_char gearIndex) {
    GameGear* pGear;
    GearStatsPreview* pPreview;
    u_char previewId;

    pGear = &g_GameState.gears[gearIndex];
    pPreview = arg0->pGearStatsPreview;
    previewId = pGear->unk0[2];
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

void func_801D6250(MenuUnk6* menu, u_char gearIndex) {
    GameGear* pGear;
    MenuUnkItem* itemList;
    MenuUnkItem* pItem;

    pGear = &g_GameState.gears[gearIndex];
    itemList = menu->unk10;
    pItem = &itemList[pGear->unk0[8]];

    pGear->baseDefense = pItem->unk8;
    pGear->baseEtherDefense = pItem->unkA;
}

void func_801D62A4(MenuUnk6* shopInfo, u8 gearId) {
    GameGear* pGear;
    MenuUnk6UnkCItem *item;
    u16 fuel;
    u8 itemId;

    pGear = &g_GameState.gears[gearId];
    itemId = pGear->unk0[3];
    item = shopInfo->unkC;
    fuel = pGear->fuel;
    item = &item[itemId];

    pGear->maxFuel = item->maxFuel;
    pGear->unk3C = item->unkC;
    pGear->unk3D = item->unkD;
    pGear->unk3E = item->unkE;
    pGear->unk3F = item->unkE;

    if (pGear->maxFuel < fuel) {
        pGear->fuel = pGear->maxFuel;
    }
}


INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6334);

INCLUDE_ASM("asm/gear_shop_menu/nonmatchings/main/main", func_801D6738);

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
