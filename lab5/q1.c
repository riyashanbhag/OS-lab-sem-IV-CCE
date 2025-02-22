#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error occurred
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("Hello from the child process!\n");
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("Hello from the parent process!\n");
    }

    return 0;
}
