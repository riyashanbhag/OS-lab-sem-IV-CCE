#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10

// Structure to hold the process information
typedef struct {
    int pid;            // Process ID
    int burstTime;      // Burst Time
    int arrivalTime;    // Arrival Time
    int priority;       // Priority (for priority scheduling)
    int remainingTime;  // Remaining time (for preemptive SJF and RR)
    int completionTime; // Completion Time
    int turnAroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
} Process;

// Function to find the waiting time and turn around time for all processes
void calculateTimes(Process processes[], int n) {
    int totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        totalTurnaroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
}

// Function for Non-Preemptive Priority Scheduling
void nonPreemptivePriorityScheduling(Process processes[], int n) {
    Process temp;
    int completed = 0, currentTime = 0;
    float totalTurnaroundTime = 0, totalWaitingTime = 0;

    // Sort processes based on priority (lower number indicates higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            currentTime++;
            continue;
        }

        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        currentTime = processes[idx].completionTime;
        completed++;

        totalTurnaroundTime += processes[idx].turnAroundTime;
        totalWaitingTime += processes[idx].waitingTime;
    }

    calculateTimes(processes, n);
}

// Function to perform Round Robin Scheduling
void roundRobinScheduling(Process processes[], int n, int quantum) {
    int currentTime = 0, completed = 0;
    float totalTurnaroundTime = 0, totalWaitingTime = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                int timeToRun = (processes[i].remainingTime > quantum) ? quantum : processes[i].remainingTime;
                processes[i].remainingTime -= timeToRun;
                currentTime += timeToRun;

                if (processes[i].remainingTime == 0) {
                    processes[i].completionTime = currentTime;
                    completed++;
                }
            }
        }
    }

    calculateTimes(processes, n);
}

// Function to perform Preemptive SJF Scheduling
void preemptiveSJF(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    Process temp;
    float totalTurnaroundTime = 0, totalWaitingTime = 0;

    while (completed < n) {
        int minBurstTime = INT_MAX;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minBurstTime) {
                minBurstTime = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++;
            continue;
        }

        processes[idx].remainingTime = 0;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        currentTime = processes[idx].completionTime;
        completed++;

        totalTurnaroundTime += processes[idx].turnAroundTime;
        totalWaitingTime += processes[idx].waitingTime;
    }

    calculateTimes(processes, n);
}

int main() {
    Process processes[MAX];
    int n, choice, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
        printf("Priority (lower value = higher priority): ");
        scanf("%d", &processes[i].priority);
    }

    do {
        printf("\n\nMenu:\n");
        printf("1. Preemptive Shortest Job First Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptiveSJF(processes, n);
                break;
            case 2:
                printf("Enter the time quantum: ");
                scanf("%d", &quantum);
                roundRobinScheduling(processes, n, quantum);
                break;
            case 3:
                nonPreemptivePriorityScheduling(processes, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
