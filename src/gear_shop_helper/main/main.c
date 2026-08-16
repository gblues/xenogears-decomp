#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"
#include "psyq/gtemac.h"
#include "psyq/inline_c.h"
#include "system/memory.h"
#include "menuhelper/main.h"

extern s32 D_80050100;

extern s32 D_801E8640;
extern s16 D_801E869C;
extern VertexBuffer g_MenuHelperVertexBuffer;
extern Temp4 D_801E86A8;

ModelMesh* MenuHelperInitializeMesh(ModelFileHeader* pModelFile, ModelMesh* pModel) {
    u_int numParts;
    int i;

    HeapChangeCurrentUser(HEAP_USER_MASA, HEAP_CONTENT_NULL);
    numParts = ModelResolvePointers(pModelFile);
    pModel->pParts = HeapAlloc(numParts * sizeof(ModelPart*), 0x0);
    pModel->numParts = numParts;
    if (pModel->pParts != NULL) {
        for (i = 0; i < numParts; i++) {
            pModel->pParts[i] = &pModelFile->modelParts[i];
        }
    }
    return pModel;
}

ModelJoint* MenuHelperInitializeSkeleton(ModelMesh* pModel, ModelJointEntry* pJointEntries, s32 arg2, s32 hasTexture, s16 texX, s16 texY, s16 clutX, s16 clutY) {
    int i;
    int numJoints;
    u_short jointIndex;
    u_short parentIndex;
    ModelJointEntry* pCurJointEntry;
    ModelJoint* pSkeleton;
    ModelJoint* pCurJoint;

    HeapChangeCurrentUser(HEAP_USER_MASA, HEAP_CONTENT_NULL);
    
    pCurJointEntry = pJointEntries;
    jointIndex = pCurJointEntry->jointIndex;
    numJoints = 0;
    while (jointIndex < pModel->numParts || jointIndex == 0xFFFF) {
        pCurJointEntry++;
        jointIndex = pCurJointEntry->jointIndex;
        numJoints++;
    }

    if (numJoints == 0) {
        return NULL;
    }

    // ALways account for root scene
    numJoints++;
    
    pSkeleton = HeapAlloc(numJoints * sizeof(ModelJoint), 0x0);
    if (pSkeleton == NULL) {
        return NULL;
    }
    
    pCurJointEntry = pJointEntries;
    pCurJoint = pSkeleton + 1;
    i = 1;
    jointIndex = pCurJointEntry->jointIndex;
    parentIndex = pCurJointEntry->parentIndex;

    // Root scene
    pSkeleton[0].doTransform = TRUE;
    pSkeleton[0].doRotate = TRUE;
    pSkeleton[0].rotDirection = 1;
    pSkeleton[0].vec1.vx = 0x1000;
    pSkeleton[0].vec1.vy = 0x1000;
    pSkeleton[0].vec1.vz = 0x1000;
    pSkeleton[0].pParent = NULL;
    pSkeleton[0].unk7 = 0;
    pSkeleton[0].jointIndex = 0xFFFF;
    pSkeleton[0].length = numJoints;
    pSkeleton[0].pModelPacketBuffer = NULL;
    pSkeleton[0].pCurModelPacket = NULL;
    pSkeleton[0].vec2.vx = 0;
    pSkeleton[0].vec2.vy = 0;
    pSkeleton[0].vec2.vz = 0;
    pSkeleton[0].unk5C[0] = 0;
    pSkeleton[0].unk5C[1] = 0;
    pSkeleton[0].unk5C[2] = 0;
    pSkeleton[0].unk70 = 0;
    pSkeleton[0].unk74 = 0;
    pSkeleton[0].unk78 = 0;
  
    while (jointIndex < pModel->numParts || jointIndex == 0xFFFF) {
        if (parentIndex == 0xFFFF) {
            pCurJoint->pParent = NULL;
        } else {
            pCurJoint->pParent = &pSkeleton[parentIndex] + 1;
        }
        
        pCurJoint->length = i++;
        pCurJoint->doTransform = TRUE;
        pCurJoint->doRotate = TRUE;
        pCurJoint->unk7 = 1;
        pCurJoint->vec1.vx = 0x1000;
        pCurJoint->vec1.vy = 0x1000;
        pCurJoint->vec1.vz = 0x1000;
        pCurJoint->rotDirection = 0;
        pCurJoint->vec1.pad = 0;
        pCurJoint->jointIndex = jointIndex;
    
        if (jointIndex != 0xFFFF) {
            // Allocate model packets
            ModelAllocatePackets(pModel->pParts[jointIndex], &pCurJoint->pModelPacketBuffer, &pCurJoint->pCurModelPacket);
            if (pCurJoint->pModelPacketBuffer == NULL) {
                MenuHelperFreeModelSkeleton(pSkeleton);
                return NULL;
            }
    
            if (hasTexture) {
                ModelPacketSetBaseTexPage(texX, texY);
                ModelPacketSetBaseClut(clutX, clutY);
            }
    
            // Initialize model packets
            ModelInitializePacket(pModel->pParts[jointIndex], pCurJoint->pModelPacketBuffer, arg2);
            memcpy(pCurJoint->pCurModelPacket, pCurJoint->pModelPacketBuffer, pModel->pParts[jointIndex]->unk20[1].modelPacketSize);
        } else {
            pCurJoint->pModelPacketBuffer = NULL;
            pCurJoint->pCurModelPacket = NULL;
        }
    
        pCurJoint->vec2.vx = 0;
        pCurJoint->vec2.vy = 0;
        pCurJoint->vec2.vz = 0;
        pCurJoint->unk5C[0] = 0;
        pCurJoint->unk5C[1] = 0;
        pCurJoint->unk5C[2] = 0;
        pCurJoint->unk70 = 0;
        pCurJoint->unk74 = 0;
        pCurJoint->unk78 = 0;
        
        pCurJoint++;
        pCurJointEntry++;
        
        jointIndex = pCurJointEntry->jointIndex;
        parentIndex = pCurJointEntry->parentIndex;
    }
    
    return pSkeleton;
}

unsigned func_801DC5C0(ModelJoint* pJoint, s32 degrees) {
    MATRIX* matrix1;
    MATRIX* matrix2;
    MATRIX* nextMatrix2;
    ModelJoint* pSkeleton = pJoint;
    SVECTOR* vec;
    short *scratch = (short *)PSX_SCRATCH;
    unsigned i;
    unsigned length;

    pJoint->matrix2.t[0] = pJoint->unk5C[0];
    pJoint->matrix2.t[1] = pJoint->unk5C[1];
    pJoint->matrix2.t[2] = pJoint->unk5C[2];
    length = pJoint->length;

    if (pJoint->rotDirection != 0) {
        RotMatrixYXZ(&pJoint->vec2, &pJoint->matrix2);
    } else {
        RotMatrix(&pJoint->vec2, &pJoint->matrix2);
    }

    scratch[0] = (degrees * pJoint->vec1.vx) >> 0xC;
    scratch[1] = 0;
    scratch[2] = 0;
    scratch[3] = 0;
    scratch[4] = (degrees * pJoint->vec1.vy) >> 0xC;
    scratch[5] = 0;
    scratch[6] = 0;
    scratch[7] = 0;
    scratch[8] = (degrees * pJoint->vec1.vz) >> 0xC;

    MulMatrix0(&pJoint->matrix2, (MATRIX* )scratch, &pJoint->matrix1);

    pJoint->matrix1.t[0] = pJoint->matrix2.t[0];
    pJoint->matrix1.t[1] = pJoint->matrix2.t[1];
    pJoint->matrix1.t[2] = pJoint->matrix2.t[2];

    for (i = 1; i < length; i++) {
        pJoint++;

        if (pJoint->doRotate != 0) {
            if (pJoint->rotDirection != 0) {
                RotMatrixYXZ(&pJoint->vec2, &pJoint->matrix1);
                pJoint->doRotate = 0;
            } else {
                RotMatrix(&pJoint->vec2, &pJoint->matrix1);
                pJoint->doRotate = 0;
            }
        }
        if ((pJoint->pParent != NULL) && (pJoint->pParent->doTransform == 1)) {
            pJoint->doTransform = 1;
        }

        if(pJoint->doTransform != 0) {
            pJoint->matrix1.t[0] = pJoint->unk5C[0];
            pJoint->matrix1.t[1] = pJoint->unk5C[1];
            pJoint->matrix1.t[2] = pJoint->unk5C[2];

            if(pJoint->pParent != NULL) {
                CompMatrix(&pJoint->pParent->matrix2, &pJoint->matrix1, &pJoint->matrix2);
            } else {
                pJoint->matrix2 = pJoint->matrix1;
            }
        }
    }

    for(i = 1; i < length; i++) {
        pSkeleton++;
        pSkeleton->doTransform = FALSE;
    }

    return length;
}


INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DC848);

void func_801DCC34(void) {}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DCC3C);

void MenuHelperFreeModelSkeleton(ModelJoint* pSkeleton) {
    int i;
    ModelJoint* pJoint = pSkeleton;

    if (pSkeleton != NULL) {
        for (i = 0; i < pSkeleton->length; i++) {
            if (pJoint->pModelPacketBuffer != NULL) {
                HeapFree(pJoint->pModelPacketBuffer);
                pJoint->pModelPacketBuffer = NULL;
                pJoint->pCurModelPacket = NULL;
            }
            pJoint++;
        }
        pSkeleton->length = 0;
        HeapFree(pSkeleton);
    }
}

void MenuHelperFreeModelMesh(ModelMesh* pMesh, s32 shouldFreeLightData) {
    int i;

    if (pMesh != NULL) {
        for (i = 0; i < pMesh->numParts; i++) {
            if (pMesh->pParts != NULL) {
                if (pMesh->pParts[i] && shouldFreeLightData) {
                    ModelPartFreeLightData(pMesh->pParts[i]);
                }
            }
        }
        
        if (pMesh->pParts != NULL) {
            HeapFree(pMesh->pParts);
            pMesh->pParts = NULL;
        }
    }
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DCEC8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DDBF8);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DEF10);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF0B4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF52C);

void* func_801DF5F4(Temp4* pUnk, int numObjects) {
    if (numObjects <= 0) {
        return NULL;
    }

    pUnk->numObjects = numObjects;
    HeapChangeCurrentUser(HEAP_USER_MASA, HEAP_CONTENT_NULL);
    pUnk->pObjects = HeapAlloc(numObjects * sizeof(Temp3), 0x0);
    if (pUnk->pObjects) {
        func_801DF6A8(pUnk);
        return pUnk;
    }
    
    return NULL;
}

void func_801DF668(Temp4* pUnk) {
    pUnk->unk4 = 0;
    if (pUnk->pObjects != NULL) {
        HeapFree(pUnk->pObjects);
    }
    pUnk->pObjects = NULL;
}

void func_801DF6A8(Temp4* pUnk) {
    int i;
    Temp3* pCurObject;

    if (pUnk->pObjects == NULL) {
        return;
    }

    pCurObject = pUnk->pObjects;
    pUnk->unk4 = 0;

    for (i = 0; i < pUnk->numObjects; i++) {
        pCurObject->unk0 = 0;
        pCurObject++;
    }
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF6F0);

int func_801DF7A8(Temp4* pUnk, s8* arg1) {
    int index;

    if (arg1 == NULL) {
        return -1;
    }
    
    index = ((mem_addr)arg1 - (mem_addr)pUnk->pObjects) / sizeof(Temp3);
    if (index < pUnk->unk4) {
        pUnk->unk4 = index;
    }
    *arg1 = 0;
    return index;
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DF7F4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFAC4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFE8C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801DFF78);

void* MenuHelperInitializeVertexBuffer(VertexBuffer* pVertexBuffer, u32 capacity) {
    HeapChangeCurrentUser(HEAP_USER_MASA, HEAP_CONTENT_NULL);
    pVertexBuffer->capacity = capacity;
    pVertexBuffer->curIndex = 0;
    pVertexBuffer->pVertices = HeapAlloc((capacity + 1) * sizeof(Vertex), 0x0);
    
    if (pVertexBuffer->pVertices) {
        MenuHelperInitializeVertices(pVertexBuffer);
        return pVertexBuffer;
    }
    
    return NULL;
}

void MenuHelperFreeVertexBuffer(VertexBuffer* pVertexBuffer) {
    pVertexBuffer->capacity = 0;
    pVertexBuffer->curIndex = 0;
    if (pVertexBuffer->pVertices != NULL) {
        HeapFree(pVertexBuffer->pVertices);
    }
    pVertexBuffer->pVertices = NULL;
}

void MenuHelperInitializeVertices(VertexBuffer* pVertexBuffer) {
    int i;
    int j;
    Vertex* pVertex;

    pVertex = pVertexBuffer->pVertices;
    for (i = 0; i < pVertexBuffer->capacity + 1; i++) {
        pVertex->unk16 = -1;
        pVertex->unk1E = 0;
        
        for (j = 0; j < 2; j++) {
            SetPolyFT4(&pVertex->polys[j]);
            SetSemiTrans(&pVertex->polys[j], 1);
            
            pVertex->polys[j].clut = GetClut(0, 0x1CD);
            pVertex->polys[j].tpage = GetTPage(0, 1, 0x340, 0x100);

            setUV4(
                &pVertex->polys[j],
                0x0, 0xBD,
                0x0, 0xBD,
                0xF, 0xBD,
                0xF, 0xBD
            );
        }

        pVertex++;
    }
}

void* func_801E0248(VertexBuffer* pVertexBuffer, short isSemiTrans) {
    Vertex* pVertex;
    
    if (pVertexBuffer->curIndex < pVertexBuffer->capacity) {
        pVertex = &pVertexBuffer->pVertices[pVertexBuffer->curIndex];
        if (pVertex->unk16 == -1) {
            for (
                pVertexBuffer->curIndex++; 
                pVertexBuffer->curIndex < pVertexBuffer->capacity; 
                pVertexBuffer->curIndex++
            ) {
                if (pVertexBuffer->pVertices[pVertexBuffer->curIndex].unk16 == -1) {
                    break;
                }
            }
            
            SetSemiTrans(&pVertex->polys[0], isSemiTrans);
            SetSemiTrans(&pVertex->polys[1], isSemiTrans);
            return pVertex;
        }
    }
    
    return &pVertexBuffer->pVertices[pVertexBuffer->capacity];
}

int func_801E0354(VertexBuffer* pVertexBuffer, Vertex* pObject) {
    int index;

    index = ((mem_addr)pObject - (mem_addr)pVertexBuffer->pVertices) / sizeof(Vertex);
    if (pVertexBuffer->curIndex >= index) {
        pVertexBuffer->curIndex = index;
    }
    
    pObject->unk16 = -1;
    return index;
}

void func_801E0398(VertexBuffer* pVertexBuffer, MATRIX* pMatrix, s32 arg2, s32* pOT, s32 renderCtx) {
    long otz;
    int i;
    Vertex* pVertex;

    SetRotMatrix(pMatrix);
    SetTransMatrix(pMatrix);
    
    pVertex = pVertexBuffer->pVertices;
    for (i = 0; i < pVertexBuffer->capacity; i++, pVertex++) {
        if (pVertex->unk16 == -1) {
            continue;
        }
        
        if (pVertex->unk16 >= pVertex->unk1E) {
            func_801E0354(pVertexBuffer, pVertex);
            continue;
        }

        // Does not match w/ setRGB0 macro
        pVertex->polys[renderCtx].r0 = pVertex->red >> 6;
        pVertex->polys[renderCtx].g0 = pVertex->green >> 6;
        pVertex->polys[renderCtx].b0 = pVertex->blue >> 6;
        
        if (pVertex->unkE == 0) {
            setXY4(
                &pVertex->polys[renderCtx],
                pVertex->x0, pVertex->y0,
                pVertex->x1, pVertex->y1,
                pVertex->x2, pVertex->y2,
                pVertex->x3, pVertex->y3
            );
            addPrim(pOT, &pVertex->polys[renderCtx]);
        } else {
            // RotTransPers3
            gte_ldv3(
                (SVECTOR*) &pVertex->x0,
                (SVECTOR*) &pVertex->x1,
                (SVECTOR*) &pVertex->x2
            );
            gte_rtpt();
            gte_stsxy3(
                (long*) &pVertex->polys[renderCtx].x0,
                (long*) &pVertex->polys[renderCtx].x1,
                (long*) &pVertex->polys[renderCtx].x2
            );
            gte_stszotz(&otz);
            otz >>= D_80050100;

            // RotTransPers
            gte_ldv0((SVECTOR*) &pVertex->x3);
            gte_rtps();
            gte_stsxy((long*) &pVertex->polys[renderCtx].x3);

            addPrim(&pOT[otz], &pVertex->polys[renderCtx]);
        }
        
        pVertex->unk16 += arg2;
        pVertex->red -= pVertex->redDelta * arg2;
        pVertex->green -= pVertex->greenDelta * arg2;
        pVertex->blue -= pVertex->blueDelta * arg2;
    }
}

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

void func_801E72CC(MATRIX* pMatrix, void* _unk, int index, int jointIndex) {
    MATRIX _mat;
    Model* pModel;

    pModel = g_MenuHelperModels[index];
    if (pModel == NULL) {
        return;
    }
    
    if (jointIndex != 0) {
        CompMatrix(
            &pModel->pSkeleton[0].matrix1, 
            &pModel->pSkeleton[jointIndex].matrix2, 
            pMatrix
        );
        return;
    }
    
    *pMatrix = pModel->pSkeleton[0].matrix1;
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7378);

void MenuHelperInitialize(int capacity) {
    int i;

    D_801E8640 = 0;
    D_801E869C = 0;
    
    func_801DF5F4(&D_801E86A8, capacity);
    MenuHelperInitializeVertexBuffer(&g_MenuHelperVertexBuffer, 0x10);

    for (i = 0; i < MAX_MODELS; i++) {
        g_MenuHelperModels[i] = NULL;
    }

    for (i = 0; i < MAX_MODEL_MESHES; i++) {
        g_MenuHelperMeshes[i].pParts = NULL;
    }

    for (i = 0; i < 2; i++) {
        D_801E8648[i].unk6 = 0;
    }
}

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E742C);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7D14);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E7FD4);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8030);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8330);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8394);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8430);

INCLUDE_ASM("asm/gear_shop_helper/nonmatchings/main/main", func_801E8480);

void func_801E8510(Model* pModel) {
    int i;
    UnkInner1* pObjects;

    if (pModel->unk10C) {
        pObjects = HeapAlloc(pModel->unk10C * sizeof(UnkInner1), 0x0);
        for (i = 0; i < pModel->unk10C; i++) {
            pObjects[i].unk0 = -1;
            pObjects[i].unk8 = 0;
        }
        pModel->unk110 = pObjects;
    }
}
