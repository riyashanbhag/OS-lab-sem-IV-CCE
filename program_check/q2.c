#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();  // Create first child process
    if (pid1 < 0) {
        perror("Fork failed for first child");
        return 1;
    }

    if (pid1 == 0) {
        // First child: Bubble Sort
        printf("Child 1: happy\n");
        

    } else {
        pid_t pid2 = fork();  // Create second child process
        if (pid2 < 0) {
            perror("Fork failed for second child");
            return 1;
        }

        if (pid2 == 0) {
            // Second child: Quick Sort
            printf("Child 2: new year\n");
        } else {
            // Parent process: Wait for any child to terminate
            int status;
            waitpid(pid1, &status, 0);  // Wait for first child
            waitpid(pid2, &status, 0);  // Wait for second child
            printf("\nParent Process:2025 \n");
        }
    }

    return 0;
}
