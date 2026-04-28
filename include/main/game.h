#ifndef _XENO_GAME_H
#define _XENO_GAME_H

#define MAX_GAME_CHARACTERS 11
#define MAX_GAME_GEARS 20
#define MAX_PARTY_MEMBERS 3
#define MAX_BENCHED_PARTY_MEMBERS 6
#define CHARACTER_ID_NONE 0xFF

#define MAX_ITEM_QUANTITY 99
#define MAX_INVENTORY_WEAPONS 100
#define MAX_INVENTORY_ACCESSORIES 200
#define MAX_INVENTORY_ITEMS 150

#define MAX_GOLD_AMOUNT 9999999


typedef struct {
    /* 0x0  */ u8 field_0x0[0x4C];
    /* 0x4C */ unsigned short hp;
    /* 0x4E */ unsigned short maxHp;
    /* 0x50 */ unsigned short mp;
    /* 0x52 */ unsigned short maxMp;
    /* 0x54 */ u32 field_0x54;
    /* 0x58 */ u8 attack;
    /* 0x59 */ u8 defense;
    /* 0x5A */ u8 agility;
    /* 0x5B */ u8 ether;
    /* 0x5C */ u8 etherDefence;
    /* 0x5D */ u8 field_0x5D;
    /* 0x5E */ u8 hitPercentage;
    /* 0x5F */ u8 evadePercentage;
    /* 0x60 */ u16 field_0x60;
    /* 0x62 */ u8 level;
    /* 0x63 */ u8 unk63;
    /* 0x64 */ u8 unk64[0x6];
    /* 0x6A */ u8 unk6A[0x5]; // Equipped weapons?
    /* 0x6F */ u8 unk6F[0x5]; // Equipped weapons?    
    /* 0x74 */ u8 unk74[0x3]; // Equipped accessories?
    /* 0x77 */ u8 unk77;    
    /* 0x78 */ u8 unk78[0x28];
    /* 0xA0 */ u8 gearId;
    /* 0xA1 */ u8 field_0xA1[0x3];
} GameCharacter; // size: 0xA4


typedef struct {
    /* 0x0  */ u8 field_0x0[0x10];
    /* 0x10 */ s16 ether;
    /* 0x12 */ s16 maxEther;
    /* 0x14 */ u8 field_0x14[0x24];
    /* 0x38 */ s32 fuel;
    /* 0x3C */ s32 maxFuel;
    /* 0x40 */ u8 field_0x40[0x20];
    /* 0x60 */ unsigned int hp;
    /* 0x64 */ unsigned int maxHp;
    /* 0x68 */ u8 field_0x68[0x3C];
} GameGear; // size: 0xA4

typedef struct {
    /* 0x0    */ u8 field_0x0[0x26C];
    /* 0x26C  */ GameCharacter characters[MAX_GAME_CHARACTERS];
    /* 0x978  */ GameGear gears[MAX_GAME_GEARS];
    /* 0x1648 */ u8 field_0x1648[0x2DC];
    /* 0x1924 */ unsigned int gold;
    /* 0x1928 */ u8 unk1928[0x408];
    /* 0x1D30 */ u16 unk1D30;
    /* 0x1D32 */ u16 FrMask;
    /* 0x1D34 */ u8 partyMembers[MAX_PARTY_MEMBERS];
    /* 0x1D37 */ u8 unk1D37;

    // Inventory
    /* 0x1D38 */ u_char weaponQuantities[MAX_INVENTORY_WEAPONS];
    /* 0x1D9C */ u_char weaponIDs[MAX_INVENTORY_WEAPONS];
    /* 0x1E00 */ u_char accessoryQuantities[MAX_INVENTORY_ACCESSORIES];
    /* 0x1EC8 */ u_char accessoryIDs[MAX_INVENTORY_ACCESSORIES];
    /* 0x1F90 */ u_char itemQuantities[MAX_INVENTORY_ITEMS];
    /* 0x2026 */ u_char itemIDs[MAX_INVENTORY_ITEMS];

    /* 0x20BC */ u8 unk20BC[0x1F5];
    /* 0x22B1 */ u8 gearRide[MAX_PARTY_MEMBERS];
} GameState; // size: unknown

extern GameState g_GameState;
extern GameState* g_pGameState;
extern int g_GamePartyMembers[MAX_PARTY_MEMBERS];

#endif