#include "common.h"
#include "menuhelper/main.h"


unsigned func_801DC5C0(MenuScene* menu, s32 degrees) {
    MATRIX* matrix1;
    MATRIX* matrix2;
    MATRIX* nextMatrix2;
    MenuScene* scene = menu;
    SVECTOR* vec;
    short *scratch = (short *)PSX_SCRATCH;
    unsigned i;
    unsigned length;

    menu->matrix2.t[0] = menu->unk5C[0];
    menu->matrix2.t[1] = menu->unk5C[1];
    menu->matrix2.t[2] = menu->unk5C[2];
    length = menu->length;

    if (menu->rotDirection != 0) {
        RotMatrixYXZ(&menu->vec2, &menu->matrix2);
    } else {
        RotMatrix(&menu->vec2, &menu->matrix2);
    }

    scratch[0] = (degrees * menu->vec1.vx) >> 0xC;
    scratch[1] = 0;
    scratch[2] = 0;
    scratch[3] = 0;
    scratch[4] = (degrees * menu->vec1.vy) >> 0xC;
    scratch[5] = 0;
    scratch[6] = 0;
    scratch[7] = 0;
    scratch[8] = (degrees * menu->vec1.vz) >> 0xC;

    MulMatrix0(&menu->matrix2, (MATRIX* )scratch, &menu->matrix1);

    menu->matrix1.t[0] = menu->matrix2.t[0];
    menu->matrix1.t[1] = menu->matrix2.t[1];
    menu->matrix1.t[2] = menu->matrix2.t[2];

    for(i = 1; i < length; i++) {
        menu++;

        if(menu->doRotate != 0) {
            if(menu->rotDirection != 0) {
                RotMatrixYXZ(&menu->vec2, &menu->matrix1);
                menu->doRotate = 0;
            } else {
                RotMatrix(&menu->vec2, &menu->matrix1);
                menu->doRotate = 0;
            }
        }
        if ((menu->parent != NULL) && (menu->parent->doTransform == 1)) {
            menu->doTransform = 1;
        }

        if(menu->doTransform != 0) {
            menu->matrix1.t[0] = menu->unk5C[0];
            menu->matrix1.t[1] = menu->unk5C[1];
            menu->matrix1.t[2] = menu->unk5C[2];

            if(menu->parent != NULL) {
                CompMatrix(&menu->parent->matrix2, &menu->matrix1, &menu->matrix2);
            } else {
                menu->matrix2 = menu->matrix1;
            }
        }
    }

    for(i = 1; i < length; i++) {
        scene++;
        scene->doTransform = 0;
    }

    return length;
}


INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DC848);

void func_801DCC34(void) {
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DCC3C);

void MenuHelperFreeMenuScene(MenuScene* menu) {
    int i;
    MenuScene *scene = menu;

    if(menu != NULL) {
        for(i = 0; i < menu->length; i++) {
            if(scene->unk68 != NULL) {
                HeapFree(scene->unk68);
                scene->unk68 = NULL;
                scene->unk6C = 0;
            }
            scene++;
        }
        menu->length = 0;
        HeapFree(menu);
    }
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DCE18);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DCEC8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DDBF8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DEF10);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF0B4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF52C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF5F4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF668);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF6A8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF6F0);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF7A8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF7F4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFAC4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFE8C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFF78);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0064);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E00DC);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E011C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0248);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0354);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0398);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0698);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0844);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0850);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E08D4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0938);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0988);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E0A00);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E1258);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E165C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E1708);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E17B8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E1880);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E1A14);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E22F8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E3438);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E34BC);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E3534);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E35D0);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E36BC);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E37D0);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E39F0);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E59D4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E5B50);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E5C74);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E5CD8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E5D44);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E632C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6338);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E63A8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6578);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6668);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E66BC);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E67F8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6830);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6910);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6974);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6D94);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6E48);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E6F64);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7094);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7298);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E72CC);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7378);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E738C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E742C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7D14);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7FD4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8030);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8330);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8394);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8430);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8480);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8510);
