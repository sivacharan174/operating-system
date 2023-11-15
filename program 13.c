#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100
#define UNUSED -1

int memory[MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = UNUSED;
    }
}

void displayMemory() {
    printf("Memory: ");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == UNUSED) {
            printf("_ ");
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

void firstFit(int processSize, int processId) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == UNUSED) {
            int j;
            for (j = i; j < i + processSize; j++) {
                if (memory[j] != UNUSED) {
                    break;
                }
            }
            if (j == i + processSize) {
                for (int k = i; k < j; k++) {
                    memory[k] = processId;
                }
                printf("Process %d of size %d allocated using First Fit\n", processId, processSize);
                return;
            }
        }
    }
    printf("Process %d of size %d cannot be allocated using First Fit\n", processId, processSize);
}

void bestFit(int processSize, int processId) {
    int bestFitStart = -1;
    int bestFitSize = MEMORY_SIZE + 1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == UNUSED) {
            int j;
            for (j = i; j < i + processSize; j++) {
                if (memory[j] != UNUSED) {
                    break;
                }
            }
            if (j == i + processSize && j - i < bestFitSize) {
                bestFitStart = i;
                bestFitSize = j - i;
            }
        }
    }

    if (bestFitStart != -1) {
        for (int k = bestFitStart; k < bestFitStart + processSize; k++) {
            memory[k] = processId;
        }
        printf("Process %d of size %d allocated using Best Fit\n", processId, processSize);
    } else {
        printf("Process %d of size %d cannot be allocated using Best Fit\n", processId, processSize);
    }
}

void worstFit(int processSize, int processId) {
    int worstFitStart = -1;
    int worstFitSize = 0;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == UNUSED) {
            int j;
            for (j = i; j < i + processSize; j++) {
                if (memory[j] != UNUSED) {
                    break;
                }
            }
            if (j == i + processSize && j - i > worstFitSize) {
                worstFitStart = i;
                worstFitSize = j - i;
            }
        }
    }

    if (worstFitStart != -1) {
        for (int k = worstFitStart; k < worstFitStart + processSize; k++) {
            memory[k] = processId;
        }
        printf("Process %d of size %d allocated using Worst Fit\n", processId, processSize);
    } else {
        printf("Process %d of size %d cannot be allocated using Worst Fit\n", processId, processSize);
    }
}

int main() {
    initializeMemory();
    displayMemory();

    firstFit(20, 1);
    displayMemory();

    bestFit(10, 2);
    displayMemory();

    worstFit(30, 3);
    displayMemory();

    firstFit(50, 4);
    displayMemory();

    return 0;
}
