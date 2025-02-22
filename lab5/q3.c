#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Bubble sort function
void bubbleSort(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Selection sort function
void selectionSort(char *arr[], int n) {
    int min_idx;
    char *temp;
    for (int i = 0; i < n-1; i++) {
        min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// Quick sort comparison function
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Quick sort function
void quickSort(char *arr[], int n) {
    qsort(arr, n, sizeof(char *), compareStrings);
}

int main() {
    int N;
    printf("Enter the number of strings: ");
    scanf("%d", &N);

    char *arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    pid_t pid1 = fork();  // Create first child process
    if (pid1 < 0) {
        perror("Fork failed for first child");
        return 1;
    }

    if (pid1 == 0) {
        // First child: Bubble Sort
        printf("Child 1 (Bubble Sort): Sorted Strings\n");
        bubbleSort(arr, N);
        for (int i = 0; i < N; i++) {
            printf("%s\n", arr[i]);
        }
        exit(0);  // Exit child process
    } else {
        pid_t pid2 = fork();  // Create second child process
        if (pid2 < 0) {
            perror("Fork failed for second child");
            return 1;
        }

        if (pid2 == 0) {
            // Second child: Quick Sort
            printf("Child 2 (Quick Sort): Sorted Strings\n");
            quickSort(arr, N);
            for (int i = 0; i < N; i++) {
                printf("%s\n", arr[i]);
            }
            exit(0);  // Exit child process
        } else {
            // Parent process: Wait for any child to terminate
            int status;
            waitpid(pid1, &status, 0);  // Wait for first child
            waitpid(pid2, &status, 0);  // Wait for second child
            printf("\nParent Process: One child has terminated.\n");
        }
    }

    // Free dynamically allocated memory for strings
    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }

    return 0;
}
