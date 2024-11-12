#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid > 0) {
        // Parent process: Exits immediately
        printf("Parent process exiting. PID: %d\n", getpid());
        exit(0);  // Parent terminates
    } else if (pid == 0) {
        // Child process: Continues running
        sleep(5);  // Sleep for a while to simulate work
        printf("Child process still running. PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        // If fork() fails
        perror("fork failed");
        return 1;
    }

    return 0;
}
