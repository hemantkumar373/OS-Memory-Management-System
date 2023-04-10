#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MEMORY_SIZE 100

struct MemoryManager {
    int memorySize;
    int allocatedMemory;
    int numProcesses;
    int numWastedBlocks;
    int numFragments;
    int *freeList;
    int *processMap;
};

void initMemoryManager(struct MemoryManager *memoryManager) {
    memoryManager->memorySize = MEMORY_SIZE;
    memoryManager->allocatedMemory = 0;
    memoryManager->numProcesses = 0;
    memoryManager->numWastedBlocks = 0;
    memoryManager->numFragments = 0;
    memoryManager->freeList = (int*)malloc(sizeof(int));
    memoryManager->freeList[0] = 0;
    memoryManager->processMap = (int*)calloc(MEMORY_SIZE, sizeof(int));
}

bool allocateMemory(struct MemoryManager *memoryManager, int processId, int processSize) {
    if (processSize > memoryManager->memorySize - memoryManager->allocatedMemory) {
        return false;
    }

    int i, j, startIndex, endIndex;
    bool isFree;

            startIndex = i;
            endIndex = i + processSize - 1;
            if (endIndex >= memoryManager->memorySize) {
            }
            isFree = true;
           
            if (isFree) {
                memoryManager->numProcesses++;
                memoryManager->allocatedMemory += processSize;
                
                return true;
            }

    memoryManager->numWastedBlocks++;
    return false;
}

void deallocateMemory(struct MemoryManager *memoryManager, int processId) {
    int i, j;
    for (i = 0; i < memoryManager->memorySize; i++) {
        if (memoryManager->processMap[i] == processId) {
            memoryManager->processMap[i] = 0;
            memoryManager->freeList = (int*)realloc(memoryManager->freeList, (memoryManager->numProcesses + 1) * sizeof(int));
            memoryManager->freeList[memoryManager->numProcesses] = i;
            memoryManager->numProcesses--;
            memoryManager->allocatedMemory--;
        }
    }
}

void runSimulation(struct MemoryManager *memoryManager, int numTimeUnits) {
    int i;
    for (i = 0; i < numTimeUnits; i++) {
        memoryManager->numFragments += memoryManager->numProcesses;
        printf("Time Unit %d:\n", i);
        printf("No. of Processes: %d\n", memoryManager->numProcesses);
        printf("No. of Wasted Blocks: %d\n", memoryManager->numWastedBlocks);
        printf("No. of Fragments: %d\n", memoryManager->numFragments);
        printf("Allocated Memory: %d/%d\n", memoryManager->allocatedMemory, memoryManager->memorySize);
  }
}

int main() {
    struct MemoryManager memoryManager;
    initMemoryManager(&memoryManager);
    allocateMemory(&memoryManager, 1, 20);
    allocateMemory(&memoryManager, 2, 30);
    allocateMemory(&memoryManager, 3, 20);
    allocateMemory(&memoryManager, 4, 20);
    runSimulation(&memoryManager, 6);
    return 0;
}
