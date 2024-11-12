#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid > 0) {
        // Parent process: Sleeps for a while, allowing the child to become a zombie
        printf("Parent process sleeping. PID: %d\n", getpid());
        sleep(10);  // Sleep for 10 seconds to observe the zombie process in the system
        printf("Parent process exiting.\n");
    } else if (pid == 0) {
        // Child process: Exits immediately
        printf("Child process exiting. PID: %d\n", getpid());
        exit(0);  // Child process terminates
    } else {
        // If fork() fails
        perror("fork failed");
        return 1;
    }

    return 0;
}
