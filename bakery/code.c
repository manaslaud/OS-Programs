#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5

// Shared resources
int flag[NUM_THREADS];   // To indicate if a thread wants to enter the critical section
int label[NUM_THREADS];  // The "ticket" for each thread

// Function to implement the Bakery Algorithm
void lock(int i) {
    int j;
    
    // Mark the thread as wanting to enter the critical section
    flag[i] = 1;
    
    // Give the thread a ticket (max label + 1)
    label[i] = 1 + max(label, NUM_THREADS);
    
    // Wait until no other thread has a smaller ticket or has the same ticket but a higher priority
    for (j = 0; j < NUM_THREADS; j++) {
        while (flag[j] && (label[j] < label[i] || (label[j] == label[i] && j < i)));
    }
}

void unlock(int i) {
    flag[i] = 0;  // Release the lock
}

// Helper function to find the maximum value in the label array
int max(int arr[], int n) {
    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Critical section for each thread
void* critical_section(void* arg) {
    int i = *((int*)arg);

    lock(i);  // Enter the critical section
    printf("Thread %d is in the critical section\n", i);
    sleep(1);  // Simulate work in the critical section
    unlock(i);  // Exit the critical section

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize flag and label arrays
    for (int i = 0; i < NUM_THREADS; i++) {
        flag[i] = 0;
        label[i] = 0;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, critical_section, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
