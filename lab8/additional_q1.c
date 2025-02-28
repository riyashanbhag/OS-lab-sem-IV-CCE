#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to detect deadlock
bool detectDeadlock(int processes, int resources, int allocation[][MAX_RESOURCES], int request[][MAX_RESOURCES], int available[], bool finish[]) {
    int work[MAX_RESOURCES];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Try to allocate resources and mark processes as finished
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            bool canAllocate = true;
            for (int j = 0; j < resources; j++) {
                if (request[i][j] > work[j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < resources; j++) {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
            }
        }
    }

    // Check for deadlock
    bool deadlock = false;
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            deadlock = true;
            printf("Deadlock detected: Process P%d is in a deadlock state.\n", i);
        }
    }

    return deadlock;
}

int main() {
    int processes = 5;
    int resources = 3;

    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int request[MAX_PROCESSES][MAX_RESOURCES] = {{0, 0, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int available[MAX_RESOURCES] = {3, 3, 2};
    bool finish[MAX_PROCESSES] = {false};

    if (detectDeadlock(processes, resources, allocation, request, available, finish)) {
        printf("Deadlock exists in the system.\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
