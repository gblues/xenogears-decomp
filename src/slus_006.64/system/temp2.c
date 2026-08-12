#include "common.h"
#include "system/memory.h"
#include "system/model.h"

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

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CD64);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CDCC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CF34);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002CF58);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D0C0);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D0E4);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D180);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D244);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D354);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D420);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D530);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D6AC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D77C);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D814);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002D984);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DA14);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DAFC);

INCLUDE_ASM("asm/slus_006.64/nonmatchings/system/temp2", func_8002DB84);

// Get largest absolute value
long func_8002DC9C(long x, long y, long z) {
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
