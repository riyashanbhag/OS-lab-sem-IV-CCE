#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

// Function to calculate the Need matrix
void calculateNeed(int need[][R], int max[][R], int allot[][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Safety algorithm to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {0}; // To track which processes are finished
    int safeSeq[P];       // To store safe sequence

    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i]; // Initially, work is the available resources
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                // Check if process can be finished with available resources
                bool canFinish = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canFinish = false;
                        break;
                    }
                }

                // If process can be finished, add its resources to work
                if (canFinish) {
                    for (int r = 0; r < R; r++) {
                        work[r] += allot[p][r];
                    }
                    safeSeq[count++] = p; // Add process to safe sequence
                    finish[p] = true;
                    found = true;
                    break;
                }
            }
        }
        
        // If no process can be found, the system is in unsafe state
        if (!found) {
            printf("System is in an unsafe state\n");
            return false;
        }
    }

    // If we reach here, the system is in a safe state
    printf("System is in a safe state.\nSafe Sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

// Function to check if a request can be granted
bool requestResources(int processes[], int avail[], int max[][R], int allot[][R], int request[], int pid) {
    // Check if request is less than need
    for (int i = 0; i < R; i++) {
        if (request[i] > max[pid][i] || request[i] > avail[i]) {
            printf("Error: Request exceeds available resources or process maximum claim.\n");
            return false;
        }
    }

    // Pretend to allocate requested resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[pid][i] += request[i];
    }

    // Check for safety after allocation
    if (isSafe(processes, avail, max, allot)) {
        return true;
    }

    // If not safe, revert the allocation
    for (int i = 0; i < R; i++) {
        avail[i] += request[i];
        allot[pid][i] -= request[i];
    }

    printf("Error: Request cannot be granted as it leads to an unsafe state.\n");
    return false;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Available resources
    int avail[] = {3, 3, 2};

    // Maximum resources needed by each process
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources currently allocated to each process
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Calculate the Need matrix
    int need[P][R];
    calculateNeed(need, max, allot);

    // Request resources for process 1
    int request[] = {1, 0, 2};
    int pid = 1;

    if (requestResources(processes, avail, max, allot, request, pid)) {
        printf("Request can be granted.\n");
    } else {
        printf("Request cannot be granted.\n");
    }

    return 0;
} 
