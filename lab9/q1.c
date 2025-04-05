#include <stdio.h>
#include <stdlib.h>

void firstFit(int *blockSize, int blocks, int *processSize, int processes) {
    int *allocation = (int *)malloc(processes * sizeof(int));
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d of size %d allocated to block %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("Process %d of size %d not allocated\n", i + 1, processSize[i]);
    }

    free(allocation);
}

void bestFit(int *blockSize, int blocks, int *processSize, int processes) {
    int *allocation = (int *)malloc(processes * sizeof(int));
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d of size %d allocated to block %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("Process %d of size %d not allocated\n", i + 1, processSize[i]);
    }

    free(allocation);
}

int main() {
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    int *blockSize1 = (int *)malloc(blocks * sizeof(int));
    int *blockSize2 = (int *)malloc(blocks * sizeof(int));

    printf("Enter size of each memory block:\n");
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &blockSize1[i]);
        blockSize2[i] = blockSize1[i]; // backup for second strategy
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    int *processSize = (int *)malloc(processes * sizeof(int));

    printf("Enter size of each process:\n");
    for (int i = 0; i < processes; i++) {
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize1, blocks, processSize, processes);
    bestFit(blockSize2, blocks, processSize, processes);

    free(blockSize1);
    free(blockSize2);
    free(processSize);

    return 0;
}
