#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  // Include this for wait()

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Function to compare strings for sorting
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide at least one string as a command-line argument.\n");
        return 1;
    }

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error occurred in creating child process
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: Sort and display strings
        printf("Child Process: Sorted Strings\n");
        
        // Sort the strings (using qsort)
        qsort(argv + 1, argc - 1, sizeof(char *), compareStrings);

        // Display the sorted strings
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    } else {
        // Parent process: Wait for the child to display the sorted strings
        wait(NULL); // Wait for child process to finish
        
        // Display unsorted strings (after child process displays sorted ones)
        printf("\nParent Process: Unsorted Strings\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
