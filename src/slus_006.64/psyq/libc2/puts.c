#include "common.h"
#include "psyq/stdio.h"

extern u32 D_8005A234;
extern u8 _ctype_[];
extern char* D_80018F3C; // "<NULL>"

void puts(char* str) {
    char ch;
    if (!str)
        str = (char*)&D_80018F3C;

    while ((ch = *str++)) {
        putchar(ch);
    }
}

void putchar(char ch) {
    if (ch != 0x9) {
        if (ch == 0xa) {
            putchar(0xd);
            D_8005A234 = 0;
            write(1, &ch, 1);
            return;
        }
    } else {
        do {
            putchar(0x20);
        } while (D_8005A234 & 0x7);
        return;
    }

    if (_ctype_[ch] & 0x97) {
        D_8005A234++;
    }

    write(1, &ch, 1);
}

char toupper(char ch) {
    if (_ctype_[ch] & 0x2) {
        ch -= 0x20;
    }
    return ch;
}

char tolower(char ch) {
    if (_ctype_[ch] & 0x1) {
        ch += 0x20;
    }
    return ch;
}
