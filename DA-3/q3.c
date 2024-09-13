#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 4  // Number of resource types

// Global processes array
int processes[] = {0, 1, 2, 3, 4};

// Function prototypes
void calculateAvailable(int available[], int total[], int allot[][R]);
void calculateNeed(int need[][R], int max[][R], int allot[][R]);
bool isSafe(int avail[], int max[][R], int allot[][R], int safeSeq[]);
bool requestResources(int request[], int avail[], int allot[][R], int max[][R], int processID, int safeSeq[]);

// Function to print the result
void printResult(bool isSafe, int safeSeq[]) {
    if (isSafe) {
        printf("The system is in a safe state.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
}

int main() {
    // Total resources
    int total[] = {3, 14, 12, 12};
    
    // Maximum claim matrix
    int max[][R] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };
    
    // Current allocation matrix
    int allot[][R] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };
    
    // Calculate the available resources
    int available[R];
    calculateAvailable(available, total, allot);
    
    // Check if the system is in a safe state
    int safeSeq[P];
    bool isSafeState = isSafe(available, max, allot, safeSeq);
    
    // Print the result
    printResult(isSafeState, safeSeq);
    
    // Request from process Q
    int request[] = {0, 4, 2, 0};
    int processID = 1; // Process Q
    
    bool requestGranted = requestResources(request, available, allot, max, processID, safeSeq);
    
    if (requestGranted) {
        printf("Request from process Q can be granted.\n");
    } else {
        printf("Request from process Q cannot be granted.\n");
    }
    
    return 0;
}

// Function to calculate the available resources
void calculateAvailable(int available[], int total[], int allot[][R]) {
    for (int i = 0; i < R; i++) {
        available[i] = total[i];
        for (int j = 0; j < P; j++) {
            available[i] -= allot[j][i];
        }
    }
}

// Function to calculate the need matrix
void calculateNeed(int need[][R], int max[][R], int allot[][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int avail[], int max[][R], int allot[][R], int safeSeq[]) {
    int work[R];
    bool finish[P];
    
    // Initialize work and finish
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }
    
    int safeSeqIndex = 0;
    for (int k = 0; k < P; k++) {
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

// Function to request resources and check if it can be granted
bool requestResources(int request[], int avail[], int allot[][R], int max[][R], int processID, int safeSeq[]) {
    int work[R];
    bool finish[P];
    
    // Initialize work and finish
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }
    
    // Check if request is less than or equal to need
    int need[P][R];
    calculateNeed(need, max, allot);
    for (int i = 0; i < R; i++) {
        if (request[i] > need[processID][i]) {
            return false;
        }
    }
    
    // Check if request is less than or equal to available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            return false;
        }
    }
    
    // Pretend to allocate the resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
        need[processID][i] -= request[i];
    }
    
    // Check if the system is in a safe state
    bool safeState = isSafe(avail, max, allot, safeSeq);
    
    // Rollback if not safe
    if (!safeState) {
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
    }
    
    return safeState;
}
