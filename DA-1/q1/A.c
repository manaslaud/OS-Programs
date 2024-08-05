#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pidB;

    pidB = fork();
    if (pidB < 0) {
        perror("Failed to fork B");
        exit(1);
    } else if (pidB == 0) {
        execl("./X", "X", (char *)NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent A: Child B has finished executing program X.\n");
    }

    return 0;
}
