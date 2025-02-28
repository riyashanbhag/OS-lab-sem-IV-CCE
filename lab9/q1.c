#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;         // Size of the memory block
    int isAllocated;  // 0 if free, 1 if allocated
    struct Block* next; // Pointer to the next block
} Block;

// Function to create a memory pool
Block* createMemoryPool(int totalSize) {
    Block* pool = (Block*)malloc(sizeof(Block));  // Create the first block
    pool->size = totalSize;
    pool->isAllocated = 0;
    pool->next = NULL;
    return pool;
}

// First Fit Allocation
void* firstFitAllocate(Block* pool, int size) {
    Block* current = pool;
    while (current != NULL) {
        if (!current->isAllocated && current->size >= size) {
            // Allocate memory
            current->isAllocated = 1;
            int remainingSize = current->size - size;

            // If there is remaining space, split the block
            if (remainingSize > 0) {
                Block* newBlock = (Block*)malloc(sizeof(Block));
                newBlock->size = remainingSize;
                newBlock->isAllocated = 0;
                newBlock->next = current->next;
                current->next = newBlock;
                current->size = size;
            }
            printf("First Fit Allocation: Block of size %d allocated.\n", size);
            return (void*)current;  // Return the allocated block
        }
        current = current->next;
    }
    printf("First Fit Allocation: No suitable block found.\n");
    return NULL;
}

// Best Fit Allocation
void* bestFitAllocate(Block* pool, int size) {
    Block* current = pool;
    Block* bestFit = NULL;
    int minSizeDifference = __INT_MAX__;
    
    // Traverse the memory pool to find the best fit
    while (current != NULL) {
        if (!current->isAllocated && current->size >= size) {
            int sizeDifference = current->size - size;
            if (sizeDifference < minSizeDifference) {
                minSizeDifference = sizeDifference;
                bestFit = current;
            }
        }
        current = current->next;
    }

    // If we found the best fit block, allocate memory
    if (bestFit != NULL) {
        bestFit->isAllocated = 1;
        int remainingSize = bestFit->size - size;
        
        // If there is remaining space, split the block
        if (remainingSize > 0) {
            Block* newBlock = (Block*)malloc(sizeof(Block));
            newBlock->size = remainingSize;
            newBlock->isAllocated = 0;
            newBlock->next = bestFit->next;
            bestFit->next = newBlock;
            bestFit->size = size;
        }
        printf("Best Fit Allocation: Block of size %d allocated.\n", size);
        return (void*)bestFit;  // Return the allocated block
    } else {
        printf("Best Fit Allocation: No suitable block found.\n");
        return NULL;
    }
}

// Free the allocated memory block
void freeMemory(Block* pool, void* ptr) {
    Block* current = pool;
    while (current != NULL) {
        if ((void*)current == ptr) {
            current->isAllocated = 0;  // Free the block
            printf("Block of size %d freed.\n", current->size);
            return;
        }
        current = current->next;
    }
    printf("Error: Block not found.\n");
}

// Print the memory pool status
void printMemoryPool(Block* pool) {
    Block* current = pool;
    while (current != NULL) {
        printf("Block of size %d, %s\n", current->size, current->isAllocated ? "Allocated" : "Free");
        current = current->next;
    }
    printf("\n");
}

int main() {
    int totalSize = 1000;
    Block* pool = createMemoryPool(totalSize);  // Create a memory pool of size 1000
    
    // Print the initial memory pool status
    printf("Initial Memory Pool:\n");
    printMemoryPool(pool);
    
    // First Fit Allocations
    void* allocatedBlock1 = firstFitAllocate(pool, 200);
    void* allocatedBlock2 = firstFitAllocate(pool, 300);
    void* allocatedBlock3 = firstFitAllocate(pool, 150);
    
    // Print memory pool status after First Fit allocations
    printf("\nMemory Pool after First Fit Allocations:\n");
    printMemoryPool(pool);
    
    // Best Fit Allocations
    void* allocatedBlock4 = bestFitAllocate(pool, 100);
    void* allocatedBlock5 = bestFitAllocate(pool, 50);
    
    // Print memory pool status after Best Fit allocations
    printf("\nMemory Pool after Best Fit Allocations:\n");
    printMemoryPool(pool);
    
    // Free some blocks
    freeMemory(pool, allocatedBlock1);
    freeMemory(pool, allocatedBlock4);
    
    // Print memory pool status after freeing blocks
    printf("\nMemory Pool after Freeing Blocks:\n");
    printMemoryPool(pool);
    
    // Clean up
    free(pool);  // Free the entire memory pool
    return 0;
}
