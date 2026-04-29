#ifndef _TYPES_H
#define _TYPES_H

#include "psyq/sys/types.h"

#ifndef NULL
#define NULL 0
#endif

// Explicitly signed variants
typedef signed char 	   byte;
typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;
typedef signed char        s_char;
typedef signed short       s_short;
typedef signed int         s_int;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef unsigned int mem_addr;

// Typedefs for making uncertain and tentative fields, variables etc. explicit
typedef unsigned char       undefined8;
typedef unsigned short      undefined16;
typedef unsigned int        undefined32;
typedef unsigned long long  undefined64;

#define TRUE 1
#define FALSE 0

#ifndef __cplusplus
typedef enum { false, true } bool;
#endif
typedef bool b32;

#define NO_VALUE -1

#endif