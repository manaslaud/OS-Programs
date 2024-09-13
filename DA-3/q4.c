#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 20
#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 3

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0;   // Index for the next item to be produced
int out = 0;  // Index for the next item to be consumed

// Semaphores and mutexes
sem_t empty_slots;
sem_t filled_slots;
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        int item = rand() % 100;  // Produce an item (random number)
        
        sem_wait(&empty_slots);   // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        buffer[in] = item; // Add the item to the buffer
        printf("Producer %d produced %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&filled_slots);     // Signal that there's a new item

        sleep(rand() % 3); // Simulate production time
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&filled_slots);    // Wait for a filled slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        int item = buffer[out]; // Remove the item from the buffer
        printf("Consumer %d consumed %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty_slots);      // Signal that there's an empty slot

        sleep(rand() % 3); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&filled_slots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Join threads (in a real application, you'd handle thread exit conditions)
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up (not reached in this code, but good practice)
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
