#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initially, no process is allocated
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    // Allocate blocks to processes
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\n** First Fit **\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d \t\t %d \t\t ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initially, no process is allocated
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    // Allocate blocks to processes
    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;

        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\n** Best Fit **\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d \t\t %d \t\t ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initially, no process is allocated
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    // Allocate blocks to processes
    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;

        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\n** Worst Fit **\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d \t\t %d \t\t ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[] = {64, 128, 32, 16};  // Available memory blocks
    int processSize[] = {10, 8, 15, 12};  // Process sizes

    int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
    int processes = sizeof(processSize) / sizeof(processSize[0]);

    // First Fit Allocation
    int blockSizeCopy1[] = {64, 128, 32, 16};  // Copy for first fit (as it modifies the block sizes)
    firstFit(blockSizeCopy1, blocks, processSize, processes);

    // Best Fit Allocation
    int blockSizeCopy2[] = {64, 128, 32, 16};  // Copy for best fit
    bestFit(blockSizeCopy2, blocks, processSize, processes);

    // Worst Fit Allocation
    int blockSizeCopy3[] = {64, 128, 32, 16};  // Copy for worst fit
    worstFit(blockSizeCopy3, blocks, processSize, processes);

    return 0;
}
