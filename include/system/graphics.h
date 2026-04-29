#ifndef _XENO_GRAPHICS_H
#define _XENO_GRAPHICS_H

typedef struct {
    /* 0x0  */ u_short x;
    /* 0x2  */ u_short y;
    /* 0x4  */ u_short modulus;
    /* 0x6  */ u_short width;
    /* 0x8  */ u_short height;
    /* 0xA  */ u_short numLines;
    /* 0xC  */ u_short destX;
    /* 0xE  */ u_short destY;
    /* 0x10 */ s8* pData;
    /* 0x14 */ u_short* unk14;
} LineScroll;

#endif