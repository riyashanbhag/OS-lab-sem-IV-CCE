#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a task
typedef struct {
    int id;         // Task ID
    int period;     // Task period
    int execution;  // Task execution time
    int deadline;   // Task deadline
    int remaining;  // Remaining execution time
    int arrival;    // Arrival time (assumed 0 for all tasks)
} Task;

// Function prototypes
void rate_monotonic(Task *tasks, int n);
void earliest_deadline_first(Task *tasks, int n);
bool is_completed(Task *tasks, int n);
void sort_by_period(Task *tasks, int n);
void sort_by_deadline(Task *tasks, int n);

int main() {
    int choice, n;

    // Input number of tasks
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task *tasks = (Task *)malloc(n * sizeof(Task));

    // Input task details
    for (int i = 0; i < n; i++) {
        printf("Enter details for Task %d\n", i + 1);
        tasks[i].id = i + 1;
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution);
        tasks[i].remaining = tasks[i].execution;
        tasks[i].arrival = 0;
        tasks[i].deadline = tasks[i].period;  // Deadline = Period for RMS
    }

    do {
        printf("\nScheduler Algorithms:\n");
        printf("1. Rate-Monotonic Scheduling (RMS)\n");
        printf("2. Earliest-Deadline-First (EDF)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Restore remaining execution time for a new simulation
        for (int i = 0; i < n; i++) {
            tasks[i].remaining = tasks[i].execution;
        }

        switch (choice) {
            case 1:
                rate_monotonic(tasks, n);
                break;
            case 2:
                earliest_deadline_first(tasks, n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    free(tasks);
    return 0;
}

// Function to simulate Rate-Monotonic Scheduling (RMS)
void rate_monotonic(Task *tasks, int n) {
    int time = 0;

    // Sort tasks by period (smallest period first)
    sort_by_period(tasks, n);

    printf("\nRate-Monotonic Scheduling (RMS)\n");

    // Run the scheduler for a fixed simulation time
    while (time < 50) {  // Change this to adjust the simulation duration
        printf("Time %d: ", time);
        bool task_executed = false;

        // Execute the highest priority task (smallest period)
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                tasks[i].remaining--;
                printf("Task %d executed", tasks[i].id);
                task_executed = true;
                break;
            }
        }

        if (!task_executed) {
            printf("No task executed.");
        }
        printf("\n");

        // Reset remaining execution time at the end of each period
        for (int i = 0; i < n; i++) {
            if ((time + 1) % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
            }
        }

        time++;
        if (is_completed(tasks, n)) break;
    }
    printf("All tasks are completed.\n");
}

// Function to simulate Earliest-Deadline-First (EDF)
void earliest_deadline_first(Task *tasks, int n) {
    int time = 0;

    printf("\nEarliest-Deadline-First (EDF)\n");

    // Run the scheduler for a fixed simulation time
    while (time < 50) {
        printf("Time %d: ", time);
        bool task_executed = false;

        // Sort tasks by deadline (earliest deadline first)
        sort_by_deadline(tasks, n);

        // Execute the task with the earliest deadline
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                tasks[i].remaining--;
                printf("Task %d executed", tasks[i].id);
                task_executed = true;
                break;
            }
        }

        if (!task_executed) {
            printf("No task executed.");
        }
        printf("\n");

        // Reset execution time and update deadlines at the end of each period
        for (int i = 0; i < n; i++) {
            if ((time + 1) % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].deadline = time + tasks[i].period;  // Update deadline dynamically
            }
        }

        time++;
        if (is_completed(tasks, n)) break;
    }
    printf("All tasks are completed.\n");
}

// Function to check if all tasks are completed
bool is_completed(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        if (tasks[i].remaining > 0) {
            return false;
        }
    }
    return true;
}

// Function to sort tasks by period (smallest period first)
void sort_by_period(Task *tasks, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

// Function to sort tasks by deadline (earliest deadline first)
void sort_by_deadline(Task *tasks, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}
