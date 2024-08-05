#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void childY() {
    printf("Child Y: Waiting for input...\n");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    printf("Child Y: You entered: %s\n", buffer);
}

void childZ() {
    printf("Child Z: Writing output...\n");
    printf("Child Z: This is a message from Child Z.\n");
}

int main() {
    pid_t pidY, pidZ;
    pidY = fork();
    if (pidY < 0) {
        perror("Failed to fork Y");
        exit(1);
    } else if (pidY == 0) {
        childY();
        exit(0);
    } else {
        pidZ = fork();
        if (pidZ < 0) {
            perror("Failed to fork Z");
            exit(1);
        } else if (pidZ == 0) {
            childZ();
            exit(0);
        } else {
            wait(NULL); 
            wait(NULL); 
        }
    }

    printf("Parent of Y and Z: Both children have finished.\n");
    return 0;
}
