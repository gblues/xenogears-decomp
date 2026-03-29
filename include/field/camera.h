#ifndef _XENO_FIELD_CAMERA_H
#define _XENO_FIELD_CAMERA_H

#include "psyq/libgte.h"

typedef struct {
    /* 0x0  */ u16 duration;
    /* 0x2  */ u16 _pad2;
    /* 0x4  */ VECTOR current;
    /* 0x14 */ VECTOR delta;
} FieldCameraMovement; // Size: 0x28

#endif