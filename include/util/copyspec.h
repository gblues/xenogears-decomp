#ifndef __UTIL_COPYSPEC
#define __UTIL_COPYSPEC

/*
 * x, y, and z will be written to pHeadX, pHeadY, and pHeadZ respectively, and the old values will be moved to
 * pNextX, pNextY, and pNextZ respectively.
 */
inline static void pushXYZ(int x, int y, int z, int *pHeadX, int *pHeadY, int *pHeadZ, int *pNextX, int *pNextY, int *pNextZ) {
    int tmpX, tmpY, tmpZ;

    tmpX = *pHeadX;
    tmpY = *pHeadY;
    tmpZ = *pHeadZ;

    *pHeadX = x;
    *pHeadY = y;
    *pHeadZ = z;

    *pNextX = tmpX;
    *pNextY = tmpY;
    *pNextZ = tmpZ;
}

#endif