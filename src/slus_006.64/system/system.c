#include "common.h"
#include "psyq/libgpu.h"
#include "system/memory.h"


extern void* g_SystemDataFile;
extern void* g_SystemFontFile;
extern void* g_SystemDataEntries;

extern u8 g_SystemPaletteData[];
extern s16 g_SystemPalette1;
extern s16 g_SystemPalette2;


INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80032F54);

unsigned int ResolveArchiveEntryPointers(u32* header) {
    int i;
    u32 base_address = (u32)header;
    u32* pointers = header;

    for (i = 1; i <= *header; i++) {
        pointers[i] += base_address;
    }

    return *header;
}

// Same as ResolveArchiveEntryPointers, but no return value
void ResolveFileEntryPointers(u32* header) {
    int i;
    u32 base_address = (u32)header;
    u32* pointers = header;

    for (i = 1; i <= *header; i++) {
        pointers[i] += base_address;
    }
}

void* GetSystemFontFile(void) {
    return g_SystemFontFile;
}

void* GetSystemDataFile(void) {
    return g_SystemDataFile;
}

void SystemFreeFont(void) {
    HeapUnpinBlock(g_SystemFontFile);
    HeapFree(g_SystemFontFile);
    g_SystemFontFile = NULL;
}

void SystemFreeData(void) {
    HeapUnpinBlock(g_SystemDataFile);
    HeapFree(g_SystemDataFile);
    g_SystemDataFile = NULL;
}


INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", SystemInitializeFont);

void SystemInitializeData(void* pSystemData) {
    if (pSystemData == 0) {
        HeapSetCurrentContentType(HEAP_CONTENT_NONE);
        return;
    }
    HeapPinBlock(pSystemData);
    g_SystemDataFile = pSystemData;
    g_SystemDataEntries = pSystemData;
    ResolveArchiveEntryPointers(pSystemData);
    g_SystemDataEntries += 4;
}

void SystemInitialize(void* pSystemFont, void* pSystemData) {
    SystemInitializeFont(pSystemFont);
    SystemInitializeData(pSystemData);
}


void SystemTransferPaletteToVRAM(short xDest, short yDest) {
    RECT dest;
    setRECT(&dest, xDest, yDest, 32, 1);
    LoadImage(&dest, &g_SystemPaletteData);
    g_SystemPalette1 = GetClut(xDest, yDest);
    g_SystemPalette2 = GetClut(xDest + 16, yDest);
}

void* GetStringEntry(void* stringData, u32 entry) {
    return stringData + ((u16 *)stringData)[entry+2];
}

// TODO: Cleanup code
// Dialog data format:
// 0x0: Offset to dimension data
// 0x2: ?
// 0x4: ?
// 0x6: u16 dimensions[dialog_count]
u8 DialogGetWidth(u16* pDialogData, int dialogIndex) {
    u8* pDialog = (pDialogData + 3) + *pDialogData + dialogIndex;
    return pDialog[0];
}

u8 DialogGetHeight(u16* pDialogData, int dialogIndex) {
    u8* pDialog = (pDialogData + 3) + *pDialogData + dialogIndex;
    return pDialog[1];
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033784);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800337B8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", GetAccessoryName);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", GetItemName);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", GetWeaponName);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033878);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800338A8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800338D8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033908);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033938);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033968);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033998);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800339C8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800339FC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033A2C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033A5C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033A8C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033ABC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033B34);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033BAC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033C20);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033CD0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033CF0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033DD4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80033DF0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800345E0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034614);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_8003463C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800346A4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800346D4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034714);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800347AC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_800347C0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034800);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034874);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_8003487C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034888);

// Render string entry to a buffer
INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", SystemRenderStringEntry);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034F98);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/system", func_80034FFC);
