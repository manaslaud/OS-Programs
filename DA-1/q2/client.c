#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        int num1, num2;
        char operator;
        printf("Enter two integers and an operator (+ or -): ");
        if (scanf("%d %d %c", &num1, &num2, &operator) != 3) {
            fprintf(stderr, "Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Failed to fork");
            exit(1);
        } else if (pid == 0) {
            char num1_str[20], num2_str[20];
            snprintf(num1_str, sizeof(num1_str), "%d", num1);
            snprintf(num2_str, sizeof(num2_str), "%d", num2);

            execl("./server", "server", num1_str, num2_str, &operator, (char *)NULL);
            perror("execl failed");
            exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                int result = WEXITSTATUS(status);
                printf("Result: %d\n", result);
            } else {
                printf("Child process did not terminate normally.\n");
            }
        }
    }

    return 0;
}
