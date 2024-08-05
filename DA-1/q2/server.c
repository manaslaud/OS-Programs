#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <int1> <int2> <operator>\n", argv[0]);
        exit(1);
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    char operator = argv[3][0];
    int result;

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        default:
            fprintf(stderr, "Invalid operator. Use '+' or '-'.\n");
            exit(1);
    }

    printf("Server: Calculated result = %d\n", result);
    exit(result);
}
