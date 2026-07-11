#ifndef __MENUHELPER_MAIN_H__
#define __MENUHELPER_MAIN_H__

#include "psyq/libgte.h"

struct _menu_scene;
typedef struct _menu_scene MenuScene;

struct _menu_scene {
    /* 0x00 */ MenuScene *parent;
    /* 0x04 */ u_char doTransform;
    /* 0x05 */ u_char doRotate;
    /* 0x06 */ u_char rotDirection;
    /* 0x07 */ u_char unk7;
    /* 0x08 */ u_char unk8;
    /* 0x09 */ u_char unk9;
    /* 0x0A */ u_short length;
    /* 0x0c */ MATRIX matrix1;
    /* 0x2c */ MATRIX matrix2;
    /* 0x4c */ SVECTOR vec1;
    /* 0x54 */ SVECTOR vec2;
    /* 0x5c */ long unk5C[3];
    /* 0x68 */ void *unk68;
    /* 0x6c */ int unk6C;
    /* 0x70 */ u_char unk70[12];
};

#endif