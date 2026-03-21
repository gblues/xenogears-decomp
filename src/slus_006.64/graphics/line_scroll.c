#include "common.h"
#include "system/graphics.h"
#include "system/memory.h"
#include "psyq/libgpu.h"

LineScroll* GfxLineScrollInitialize(LineScroll* pLineScroll, 
    u16 x, u16 y, u16 modulus, s16 width, s16 numLines, u16 destX, u16 destY, s8* pData
) {
    u_short* pWork;
    int i;

    HeapChangeCurrentUser(HEAP_USER_MASA, 0);
    pLineScroll->x = x;
    pLineScroll->y = y;
    pLineScroll->modulus = modulus;
    pLineScroll->width = width;
    pLineScroll->numLines = numLines;
    pLineScroll->destX = destX;
    pLineScroll->destY = destY;
    pLineScroll->pData = pData;
    pLineScroll->height = width / numLines;
    
    pWork = HeapAlloc(numLines * sizeof(u_short), 0);
    pLineScroll->unk14 = pWork;
    if (pWork == 0) {
        pLineScroll = NULL;
    } else {
        for (i = 0; i < numLines; i++) {
            pLineScroll->unk14[i] = 0;
        }
    }
    return pLineScroll;
}

void GfxLineScrollUpdate(LineScroll* pLineScroll) {
    RECT srcRect;
    int i;
    u16 destY;
    u16 offset;
    u16 remainder;

    if (!pLineScroll->unk14) {
        return;
    }

    srcRect.y = pLineScroll->y;
    srcRect.h = pLineScroll->height;
    destY = pLineScroll->destY;
    
    for (i = 0; i < pLineScroll->numLines; i++) {
        pLineScroll->unk14[i] += pLineScroll->pData[i];

        // Divide pLineScroll->unk14[i] by 0x10 and modulo it
        remainder = (u32) (((pLineScroll->unk14[i] << 0x10) >> 0x14) & 0xFFFF) % pLineScroll->modulus;
        
        offset = pLineScroll->modulus - remainder;
        
        srcRect.x = pLineScroll->x;
        srcRect.w = remainder;
        MoveImage(&srcRect, pLineScroll->destX + offset, destY);
        
        srcRect.x = remainder + pLineScroll->x;
        srcRect.w = offset;
        MoveImage(&srcRect, pLineScroll->destX, destY);
        
        destY += pLineScroll->height;
        srcRect.y += pLineScroll->height;
    }
}

void GfxLineScrollFree(LineScroll* pLineScroll) {
    if (pLineScroll->unk14) {
        HeapFree(pLineScroll->unk14);
        pLineScroll->unk14 = NULL;
    }
}


// NOTE: Probably part of libarchive, not line_scroll
INCLUDE_ASM("asm/slus_006.64/nonmatchings/graphics/line_scroll", func_8002804C);
