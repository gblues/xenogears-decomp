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
    /* 0x0  */ u8 unk0[0x2C];
    /* 0x2C */ u8 etherDefenseFromEquipment;
    /* 0x2D  */ undefined8 unk2D[0x1F];
    /* 0x4C */ u_short hp;
    /* 0x4E */ u_short maxHp;
    /* 0x50 */ u_short mp;
    /* 0x52 */ u_short maxMp;
    /* 0x54 */ undefined32 field_0x54;
    /* 0x58 */ u_char attack;
    /* 0x59 */ u_char defense;
    /* 0x5A */ u_char agility;
    /* 0x5B */ u_char ether;
    /* 0x5C */ u_char etherDefense;
    /* 0x5D */ undefined8 field_0x5D;
    /* 0x5E */ u_char hitPercentage;
    /* 0x5F */ u_char evadePercentage;
    /* 0x60 */ undefined16 field_0x60;
    /* 0x62 */ u_char level;
    /* 0x63 */ undefined8 unk63;
    /* 0x64 */ undefined8 unk64[0x6];
    /* 0x6A */ undefined8 unk6A[0x5]; // Equipped weapons?
    /* 0x6F */ undefined8 unk6F[0x5]; // Equipped weapons?    
    /* 0x74 */ undefined8 unk74[0x3]; // Equipped accessories?
    /* 0x77 */ undefined8 unk77;    
    /* 0x78 */ undefined8 unk78[0x28];
    /* 0xA0 */ u_char gearId;
    /* 0xA1 */ undefined8 field_0xA1[0x3];
} GameCharacter; // size: 0xA4


typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 frameId;
    /* 0x03 */ u8 engineId;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u8 armorId;
    /* 0x09 */ u8 accessorySlots[3];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ s16 ether;
    /* 0x12 */ u8 maxEther;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26[0x12];
    /* 0x38 */ u16 fuel;
    /* 0x3A */ u16 maxFuel;
    /* 0x3C */ u8 engineOutput;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u16 defenseFromEquipment; // total of defense boosts from slot1 + slot 2 + slot 3
    /* 0x42 */ u16 etherDefenseFromEquipment;
    /* 0x44 */ u16 weightFromEquipment;
    /* 0x46 */ u16 unk46;
    /* 0x48 */ u16 unk48;
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 responsiveness;
    /* 0x4E */ u8 unk4E;
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u16 unk52;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 unk57;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u8 unk5E;
    /* 0x5F */ u8 unk5F;
    /* 0x60 */ u32 hp;
    /* 0x64 */ u32 maxHp;
    /* 0x68 */ u16 weight;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u16 unk6E;
    /* 0x70 */ u16 baseDefense; /* impacted by AR value of equipped armor */
    /* 0x72 */ u16 baseEtherDefense;
    /* 0x74 */ u8 unk74;
    /* 0x75 */ u8 unk75;
    /* 0x76 */ u8 unk76[0x10];
    /* 0x86 */ u16 unk86;
    /* 0x88 */ u8 unk88[0x10];
    /* 0x98 */ u8 unk98;
    /* 0x99 */ u8 unk99;
    /* 0x9a */ u8 unk9A;
    /* 0x9b */ u8 unk9B;
    /* 0x9c */ u8 unk9C;
    /* 0x9d */ u8 unk9D;
    /* 0x9e */ u8 unk9E;
    /* 0x9f */ u8 unk9F;
    /* 0xA0 */ int unkA0;
} GameGear; // size: 0xA4

typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkC;
    /* 0x10 */ int unk10;
} StringEntry; /* size: 0x14 */

typedef struct {
    /* 0x0000 */ StringEntry strings[31];
    /* 0x026C */ GameCharacter characters[MAX_GAME_CHARACTERS];
    /* 0x0978 */ GameGear gears[MAX_GAME_GEARS];
    /* 0x1648 */ undefined8 unk1648[0x206];
    /* 0x184E */ undefined16 unk184E;
    /* 0x1850 */ undefined8 unk1850[0x2];
    /* 0x1852 */ undefined16 unk1852;
    /* 0x1854 */ undefined8 unk1854[0xD0];
    /* 0x1924 */ u_int gold;
    /* 0x1928 */ undefined8 unk1928[0x408];
    /* 0x1D30 */ undefined16 unk1D30;
    /* 0x1D32 */ u_short FrMask;
    /* 0x1D34 */ undefined8 partyMembers[MAX_PARTY_MEMBERS];
    /* 0x1D37 */ undefined8 unk1D37;

    // Inventory
    /* 0x1D38 */ u_char weaponQuantities[MAX_INVENTORY_WEAPONS];
    /* 0x1D9C */ u_char weaponIDs[MAX_INVENTORY_WEAPONS];
    /* 0x1E00 */ u_char accessoryQuantities[MAX_INVENTORY_ACCESSORIES];
    /* 0x1EC8 */ u_char accessoryIDs[MAX_INVENTORY_ACCESSORIES];
    /* 0x1F90 */ u_char itemQuantities[MAX_INVENTORY_ITEMS];
    /* 0x2026 */ u_char itemIDs[MAX_INVENTORY_ITEMS];

    /* 0x20BC */ undefined8 unk20BC[0x64];
    /* 0x2120 */ undefined8 unk2120[0x64];
    /* 0x2184 */ undefined8 unk2184[0x96];
    /* 0x221A */ undefined8 unk221A[0x96];
    /* 0x22B0 */ undefined8 unk22B0;
    /* 0x22B1 */ undefined8 gearRide[MAX_PARTY_MEMBERS];
    /* 0x22B4 */ undefined8 unk22B4[0x2];
    /* 0x22B6 */ undefined16 unk22B6;
    /* 0x22B8 */
} GameState; // size: unknown

extern GameState g_GameState;
extern GameState* g_pGameState;
extern int g_GamePartyMembers[MAX_PARTY_MEMBERS];

#endif