#include <stdio.h>
#include <stdbool.h>

#define PROCESSES 5     
#define RESOURCES 3     

int available[RESOURCES] = {3, 3, 2};  // Available resources
int maximum[PROCESSES][RESOURCES] = {   // Maximum demand of each process
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[PROCESSES][RESOURCES] = { // Currently allocated resources
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[PROCESSES][RESOURCES];         // Resources needed by each process

void calculate_need() {
    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool is_safe() {
    bool finish[PROCESSES] = {false};    // To mark finished processes
    int work[RESOURCES];                 // Work vector to keep track of available resources

    for (int i = 0; i < RESOURCES; i++) {
        work[i] = available[i];
    }

    int safe_sequence[PROCESSES];
    int count = 0;

    while (count < PROCESSES) {
        bool found = false;
        
        for (int i = 0; i < PROCESSES; i++) {
            if (!finish[i]) {  // Process i is not finished
                int j;
                for (j = 0; j < RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == RESOURCES) { // If all needs can be satisfied
                    for (int k = 0; k < RESOURCES; k++) {
                        work[k] += allocation[i][k];  // Release resources
                    }
                    safe_sequence[count++] = i;  // Add process to safe sequence
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < PROCESSES; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    calculate_need();    // Calculate need matrix
    is_safe();           // Check if system is in a safe state
    return 0;
}
