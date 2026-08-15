#include "common.h"
#include "system/memory.h"
#include "system/model.h"

extern u16 D_80059308;
extern u16 D_8005930C;
extern s32 D_80059310;
extern s32 D_80059314;
extern void* g_pCurModelLightData;
extern void* g_pCurModelPacket;
extern SVECTOR* g_pCurModelNormals;
extern SVECTOR* g_pCurModelVertices;

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002AC24);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002B084);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002B2F0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002B5D0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002B8B0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002BA40);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002BA58);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002BB50);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002BF38);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C310);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C3D8);

// When a model file has been loaded somewhere in memory, the relative pointers
// in the file needs to be resolved to their concrete address.
int ModelResolvePointers(ModelFileHeader* pModelFile) {
    int numParts;
    int i;
    int j;
    ModelPart* pCurPart;
    ModelPacketInfo* pPacketInfo;

    i = pModelFile->flags;
    numParts = pModelFile->numModelParts;
    if ((i & 1) == 0) {
        pModelFile->flags = i | 1;
    
        pCurPart = pModelFile->modelParts;
        for (i = 0; i < numParts; i++) {
            pCurPart->pVertices = (mem_addr)pCurPart->pVertices + (mem_addr)pModelFile;
            pCurPart->unkC = (mem_addr)pCurPart->unkC + (mem_addr)pModelFile;
            pCurPart->unk10 = (mem_addr)pCurPart->unk10 + (mem_addr)pModelFile;
            pCurPart->pColors = (mem_addr)pCurPart->pColors + (mem_addr)pModelFile;
            
            if (pCurPart->unk1C != NULL) {
                pCurPart->unk1C = (mem_addr)pCurPart->unk1C + (mem_addr)pModelFile;
                pPacketInfo = pCurPart->unk1C + 1;
                for (j = *pCurPart->unk1C; j != -1; j--) {
                    pPacketInfo[j].lightDataSize += (mem_addr)pModelFile;
                    pPacketInfo[j].modelPacketSize += (mem_addr)pModelFile;
                }
            }
            
            pCurPart++;
        }
    }

    return numParts;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C4BC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C59C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C644);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C68C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C6E0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C700);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002C8CC);

void ModelAllocatePackets(ModelPart* pModelPart, void** pPacket1, void** pPacket2) {
    void* pPacketBuffer;

    HeapSetCurrentContentType(HEAP_CONTENT_MODEL_PACKET);
    pPacketBuffer = HeapAlloc(pModelPart->unk20[1].modelPacketSize * 2, 0x0);
    *pPacket1 = pPacketBuffer;
    *pPacket2 = pPacketBuffer + pModelPart->unk20[1].modelPacketSize;
}

void ModelPartFreeLightData(ModelPart* pModelPart) {
    if (pModelPart->flags & MODEL_FLAG_HAS_LIGHT_DATA) {
        HeapFree(pModelPart->pLightData);
        pModelPart->flags &= ~MODEL_FLAG_HAS_LIGHT_DATA;
    }
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CC10);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CC54);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CC74);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CCAC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CCC8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CD24);

u32 func_8002CD64(PrimitiveHeader* pPrim) {
    if ((pPrim->code & 0xF0) == 0xC0) {
        switch (pPrim->code) {
            case 0xC4: // Tex page
                func_8002CCC8(pPrim);
                return 0;
            case 0xC8: // CLUT
                func_8002CD24(pPrim);
                return 0;
            default:
                return 1;
        }
    }
    return 1;
}


// ---------------------------------------------
// This block of functions are initializer handlers which initializes
// primitives in model packets for rendering. The naming of the functions are
// quite vague for now, and should be renamed to something better if it turns out
// any of these handlers are used in specific ways.
//
// Initializing a primitive for the model packet typically involves setting the length,
// primitive code, color (which can entail lighting computation) and UVs, tpage
// and clut if the primitive is a textured one.
// ---------------------------------------------
INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CDCC);

// NOTE: Could possibly also be LineG2 or PolyF3 based on prim len
s32 func_8002CF34(UntexturedPrimitive* pPrim, short* pIndices, int flags) {
    SPRT* pSprt;

    pSprt = (SPRT*)g_pCurModelPacket;
    setlen(pSprt, 4);
    *(u32*)&pSprt->r0 = *(u32*)pPrim;
    return 1;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CF58);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D0C0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D0E4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D180);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D244);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D354);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D420);

int ModelPacketInitPolyFT4(TexturedQuadPrimitive* pPrim, short* pVertexIndices, int flags) {
    SVECTOR vecNormal;
    POLY_FT4* pPoly;

    if (!func_8002CD64(pPrim)) {
        return 0;
    }
    
    pPoly = g_pCurModelPacket;
    setlen(pPoly, 9);

    *(u32*)&pPoly->u0 = *(u16*)&pPrim->u0 | (D_8005930C << 0x10);
    *(u32*)&pPoly->u1 = *(u16*)&pPrim->u1 | (D_80059308 << 0x10);
    *(u16*)&pPoly->u2 = *(u16*)&pPrim->u2;
    *(u16*)&pPoly->u3 = *(u16*)&pPrim->u3;
    
    if (flags & 1) {
        if (flags & 2) {
            MathTriangleNormal(
                &g_pCurModelVertices[pVertexIndices[0]], 
                &g_pCurModelVertices[pVertexIndices[1]], 
                &g_pCurModelVertices[pVertexIndices[2]], 
                (SVECTOR*)g_pCurModelLightData
            );
            NormalColor((SVECTOR*)g_pCurModelLightData, (CVECTOR*)&pPoly->r0);
        } else {
            MathTriangleNormal(
                &g_pCurModelVertices[pVertexIndices[0]], 
                &g_pCurModelVertices[pVertexIndices[1]], 
                &g_pCurModelVertices[pVertexIndices[2]], 
                &vecNormal
            );
            NormalColor(&vecNormal, (CVECTOR*)&pPoly->r0);
        }
    } else if (flags & 4) {
        NormalColor((SVECTOR*)g_pCurModelLightData, (CVECTOR*)&pPoly->r0);
    }
    
    g_pCurModelLightData += sizeof(SVECTOR);
    pPoly->code = pPrim->code;
    return 1;
}

int ModelPacketInitPolyG3(UntexturedPrimitive* pPrim, short* pIndices, int flags) {
    POLY_G3* pPoly;

    pPoly = g_pCurModelPacket;
    setlen(pPoly, 6);
    
    if (flags & 2) {
        *(u32*)g_pCurModelLightData = *(u32*)pPrim; // TODO: Clean up
        g_pCurModelLightData += sizeof(P_CODE);
    }

    NormalColorCol3(
        &g_pCurModelNormals[pIndices[0]], 
        &g_pCurModelNormals[pIndices[1]],
        &g_pCurModelNormals[pIndices[2]],
        (CVECTOR*)&pPrim->r,
        &pPoly->r0,
        &pPoly->r1,
        &pPoly->r2
    );
    
    pPoly->code = pPrim->code;
    return 1;
}

int ModelPacketInitPolyG3_2(UntexturedPrimitive* pPrim, short* pIndices, int flags) {
    POLY_G3* pPoly;

    pPoly = g_pCurModelPacket;
    setlen(pPoly, 6);
    
    NormalColorCol3(
        &g_pCurModelNormals[pIndices[0]], 
        &g_pCurModelNormals[pIndices[1]],
        &g_pCurModelNormals[pIndices[2]],
        (CVECTOR*)&pPrim->r,
        &pPoly->r0,
        &pPoly->r1,
        &pPoly->r2
    );
    
    pPoly->code = pPrim->code;
    return 1;
}

s32 ModelPacketInitPolyFT3(TexturedTrianglePrimitive* pPrim, short* pIndices, int flags) {
    SVECTOR vecNormal;
    POLY_FT3* pPoly;

    if (func_8002CD64(pPrim) == 0) {
        return 0;
    }
    pPoly = g_pCurModelPacket;
    setlen(pPoly, 7);
    
    // Set UVs, clut and tpage
    *(u32*)&pPoly->u0 = *(u16*)&pPrim->u0 | (D_8005930C << 0x10);
    *(u32*)&pPoly->u1 = *(u16*)&pPrim->u1 | (D_80059308 << 0x10);
    *(u16*)&pPoly->u2 = *(u16*)&pPrim->u2;
    
    if (flags & 1) {
        if (flags & 2) {
            MathTriangleNormal(
                &g_pCurModelVertices[pIndices[0]], 
                &g_pCurModelVertices[pIndices[1]], 
                &g_pCurModelVertices[pIndices[2]], 
                (SVECTOR*)g_pCurModelLightData
            );
            NormalColor((SVECTOR*)g_pCurModelLightData, (CVECTOR*)&pPoly->r0);
        } else {
            MathTriangleNormal(
                &g_pCurModelVertices[pIndices[0]], 
                &g_pCurModelVertices[pIndices[1]], 
                &g_pCurModelVertices[pIndices[2]], 
                &vecNormal
            );
            NormalColor(&vecNormal, (CVECTOR*)&pPoly->r0);
        }
    } else if (flags & 4) {
        NormalColor((SVECTOR*)g_pCurModelLightData, (CVECTOR*)&pPoly->r0);
    }
    
    g_pCurModelLightData += sizeof(SVECTOR);
    pPoly->code = pPrim->code;
    return 1;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D984);

s32 ModelPacketInitPolyGT3(TexturedTrianglePrimitive* pPrim, short* pIndices, int flags) {
    POLY_GT3* pPoly;
    
    if (func_8002CD64(pPrim) == 0) {
        return 0;
    }
    
    pPoly = g_pCurModelPacket;
    setlen(pPoly, 9);
    NormalColor3(
        &g_pCurModelNormals[pIndices[0]], 
        &g_pCurModelNormals[pIndices[1]],
        &g_pCurModelNormals[pIndices[2]],
        (CVECTOR*)&pPoly->r0,
        (CVECTOR*)&pPoly->r1,
        (CVECTOR*)&pPoly->r2
    );

    // Set UVs, clut and tpage
    *(u32*)&pPoly->u0 = *(u16*)&pPrim->u0 | (D_8005930C << 0x10);
    *(u32*)&pPoly->u1 = *(u16*)&pPrim->u1 | (D_80059308 << 0x10);
    *(u16*)&pPoly->u2 = *(u16*)&pPrim->u2;
    
    pPoly->code = pPrim->code;
    return 1;
}

s32 ModelPacketInitPolyFT3_2(void) {
    POLY_FT3* pPoly;

    pPoly = g_pCurModelPacket;
    SetPolyFT3(pPoly);
    SetShadeTex(pPoly, 1);
    pPoly->tpage = (GetTPage(1, 0, 0x280, 0) & 0xFFE0) | D_80059310;
    pPoly->clut = (GetClut(0, 0x1E0) & 0xF) | D_80059314;
    return 1;
}
// -------------------------------------


void MathTriangleNormal(SVECTOR* pVertex1, SVECTOR* pVertex2, SVECTOR* pVertex3, SVECTOR* pNormal) {
    VECTOR edge1;
    VECTOR edge2;
    VECTOR normal;
    int sqrt;
    int largestComponent;

    // Compute vertices from vertex 1 -> vertex 2, and
    // from vertex 1 -> vertex 3
    edge1.vx = pVertex2->vx - pVertex1->vx;
    edge1.vy = pVertex2->vy - pVertex1->vy;
    edge1.vz = pVertex2->vz - pVertex1->vz;
    
    edge2.vx = pVertex3->vx - pVertex1->vx;
    edge2.vy = pVertex3->vy - pVertex1->vy;
    edge2.vz = pVertex3->vz - pVertex1->vz;

    // Taking the cross product of these two vectors gives us a vector
    // perpendicular to the two edges, effectively pointing in the direction of the normal
    OuterProduct0(&edge2, &edge1, &normal);

    // Find the largest component and scale the vector by it
    largestComponent = MathGetLargestVectorComponent(normal.vx, normal.vy, normal.vz);
    if (largestComponent < 0) {
        largestComponent = -largestComponent;
    }
    sqrt = SquareRoot0(largestComponent);
    normal.vx = normal.vx / sqrt;
    normal.vy = normal.vy / sqrt;
    normal.vz = normal.vz / sqrt;
    
    VectorNormalS(&normal, pNormal);
}

// Get largest absolute value
long MathGetLargestVectorComponent(long x, long y, long z) {
    long absX;
    long absY;
    long absZ;
    long result;

    absX = x;
    absY = y;
    absZ = z;
    
    if (x < 0) absX = -x;
    if (y < 0) absY = -y;
    if (z < 0) absZ = -z;
    
    if (absX >= absY && absX >= absZ) {
        return x;
    }
    
    if (absY >= absX && absY >= absZ) {
        return y;
    }

    result = absZ < absX;
    if (result == 0) {
        result = absZ < absY;
        if (result == 0) {
            return z;
        }
    }
    
    return result;
}

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DD20);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DDE4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DFE0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DFF0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002E010);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002E448);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002E64C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002E8B4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002EAB8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002ED20);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002EEF8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002F0E4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002F2E0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002F4B4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002F6B4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002F8D0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002FAE8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002FCFC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002FF0C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003014C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800301C8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030228);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800302D4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800303C8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800305D8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800306D0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030750);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030988);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030A30);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030B14);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030C40);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030C78);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030C98);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80030EE8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003101C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800315A0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800315C4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800315E8);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003160C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031630);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031654);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031678);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003169C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800316C0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800316E4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031708);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003172C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031750);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031774);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031798);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800317BC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_800317E0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031804);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031828);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8003184C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_80031870);
