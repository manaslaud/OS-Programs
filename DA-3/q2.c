#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 4  // Number of resource types

// Function prototypes
void calculateAvailable(int available[], int max[][R], int allot[][R]);
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R], int safeSeq[]);

// Function to print the result
void printResult(bool isSafe, int safeSeq[]) {
    if (isSafe) {
        printf("The system is in a safe state.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < P ; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
}

int main() {
    // Number of processes and resources
    int processes[] = {0, 1, 2, 3, 4};
    
    // Maximum claim matrix
    int max[][R] = {
        {2, 1, 2, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 0},
        {0, 1, 0, 0},
        {2, 1, 2, 1}
    };
    
    // Current allocation matrix
    int allot[][R] = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 1}
    };
    
    // Total resources
    int total[] = {6, 4, 4, 2};
    
    // Calculate the available resources
    int available[R];
    calculateAvailable(available, max, allot);
    
    // Check if the system is in a safe state
    int safeSeq[P];
    bool isSafeState = isSafe(processes, available, max, allot, safeSeq);
    
    // Print the result
    printResult(isSafeState, safeSeq);
    
    return 0;
}

// Function to calculate the available resources
void calculateAvailable(int available[], int max[][R], int allot[][R]) {
    int total[] = {6, 4, 4, 2};
    int need[P][R];
    
    // Calculate the need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
    
    // Initialize available array
    for (int i = 0; i < R; i++) {
        available[i] = total[i];
        for (int j = 0; j < P; j++) {
            available[i] -= allot[j][i];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R], int safeSeq[]) {
    int work[R];
    bool finish[P];
    
    // Initialize work and finish
    for (int i = 0; i < R ; i++) {
        work[i] = avail[i];
    }
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }
    
    int safeSeqIndex = 0;
    for (int k = 0; k < P ; k++) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (max[i][j] - allot[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    // Add allocation to work
                    for (int y = 0; y < R; y++) {
                        work[y] += allot[i][y];
                    }
                    safeSeq[safeSeqIndex++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }
    return true; // System is in a safe state
}
