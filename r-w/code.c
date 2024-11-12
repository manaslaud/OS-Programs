#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared resources
int readCount = 0; // To count the number of readers currently reading
sem_t mutex;       // Mutex for managing readCount
sem_t writeLock;   // Semaphore for writer's exclusive access
sem_t resourceLock; // Mutex for exclusive resource access

void* reader(void* arg) {
    int id = *((int*)arg);

    while (1) {
        // Reader arrives
        sem_wait(&mutex);           // Enter critical section to update readCount
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeLock);   // Block writers when the first reader arrives
        }
        sem_post(&mutex);           // Leave critical section

        // Reading critical section
        printf("Reader %d: Reading the resource\n", id);
        sleep(1);  // Simulate reading time

        // Reader leaves
        sem_wait(&mutex);           // Enter critical section to update readCount
        readCount--;
        if (readCount == 0) {
            sem_post(&writeLock);   // Allow writers if there are no readers
        }
        sem_post(&mutex);           // Leave critical section

        sleep(1);  // Simulate some delay between reads
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    while (1) {
        sem_wait(&writeLock);  // Wait for exclusive access to resource

        // Writing critical section
        printf("Writer %d: Writing to the resource\n", id);
        sleep(2);  // Simulate writing time

        sem_post(&writeLock);  // Release write lock

        sleep(2);  // Simulate some delay between writes
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);        // Semaphore for managing readCount
    sem_init(&writeLock, 0, 1);    // Semaphore for writer mutual exclusion
    sem_init(&resourceLock, 0, 1); // Mutex for exclusive access to resource

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeLock);
    sem_destroy(&resourceLock);

    return 0;
}
