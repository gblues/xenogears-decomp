#ifndef _XENO_GRAPHICS_H
#define _XENO_GRAPHICS_H

typedef struct {
    /* 0x0  */ u16 x;
    /* 0x2  */ u16 y;
    /* 0x4  */ u16 modulus;
    /* 0x6  */ u16 width;
    /* 0x8  */ u16 height;
    /* 0xA  */ u16 numLines;
    /* 0xC  */ u16 destX;
    /* 0xE  */ u16 destY;
    /* 0x10 */ s8* pData;
    /* 0x14 */ u16* unk14;
} LineScroll;

#endif