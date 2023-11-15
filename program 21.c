#include <stdio.h>

#define MAX_MEMORY_SIZE 1000

struct MemoryBlock {
    int size;
    int allocated;
};

struct MemoryBlock memory[MAX_MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

void allocateMemory(int processSize) {
    int worstFitIndex = -1;
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (worstFitIndex == -1 || memory[i].size > memory[worstFitIndex].size) {
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
        if (memory[worstFitIndex].size > processSize) {
            // Split the block if the allocated size is larger than the requested size
            int remainingSize = memory[worstFitIndex].size - processSize;
            memory[worstFitIndex + 1].size = remainingSize;
            memory[worstFitIndex + 1].allocated = 0;
        }
        printf("Memory allocated for process of size %d at block %d\n", processSize, worstFitIndex);
    } else {
        printf("Memory allocation failed for process of size %d\n", processSize);
    }
}

void displayMemoryStatus() {
    printf("\nMemory Status:\n");
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (memory[i].size > 0) {
            printf("Block %d: Size: %d, Allocated: %s\n", i, memory[i].size, memory[i].allocated ? "Yes" : "No");
        }
    }
}

int main() {
    initializeMemory();

    // Assume some initial memory blocks
    memory[0].size = 500;
    memory[1].size = 200;
    memory[2].size = 300;

    displayMemoryStatus();

    allocateMemory(150);
    allocateMemory(400);
    allocateMemory(250);
    allocateMemory(100);

    displayMemoryStatus();

    return 0;
}
