#include <stdio.h>
#include <stdlib.h>

void sstf(int *requests, int num_requests, int head) {
    int *visited = (int *)calloc(num_requests, sizeof(int));
    int total_seek = 0;
    int count = 0;

    while (count < num_requests) {
        int min_distance = __INT_MAX__;
        int index = -1;

        // Find the closest request
        for (int i = 0; i < num_requests; i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = i;
                }
            }
        }

        // Visit the closest request
        visited[index] = 1;
        total_seek += min_distance;
        head = requests[index];
        count++;

        printf("Head moves to: %d\n", head);
    }

    printf("Total seek time: %d\n", total_seek);

    free(visited);
}

void scan(int *requests, int num_requests, int head, int disk_size) {
    int total_seek = 0;

    // Sort requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Move towards 0
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
            break;
        }
    }

    // Move from 0 to disk_size (end)
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] > head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
        }
    }

    printf("Total seek time: %d\n", total_seek);
}

void cscan(int *requests, int num_requests, int head, int disk_size) {
    int total_seek = 0;

    // Sort requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Move towards disk size
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
            break;
        }
    }

    // Go back to start
    total_seek += disk_size - head;
    printf("Head moves to: 0\n");
    head = 0;

    // Visit remaining requests
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] > head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
        }
    }

    printf("Total seek time: %d\n", total_seek);
}

void clook(int *requests, int num_requests, int head) {
    int total_seek = 0;

    // Sort requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Move towards end
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
            break;
        }
    }

    // Go to the first request (circular movement)
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] > head) {
            total_seek += abs(head - requests[i]);
            head = requests[i];
            printf("Head moves to: %d\n", head);
        }
    }

    printf("Total seek time: %d\n", total_seek);
}

int main() {
    int choice, num_requests, head, disk_size;

    printf("Enter the size of the disk: ");
    scanf("%d", &disk_size);

    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);

    int *requests = (int *)malloc(num_requests * sizeof(int));

    printf("Enter the request queue: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the head: ");
    scanf("%d", &head);

    do {
        printf("\nDisk Scheduling Algorithms Menu\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. C-LOOK\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(requests, num_requests, head);
                break;
            case 2:
                scan(requests, num_requests, head, disk_size);
                break;
            case 3:
                cscan(requests, num_requests, head, disk_size);
                break;
            case 4:
                clook(requests, num_requests, head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    free(requests);
    return 0;
}
