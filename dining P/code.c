#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];  // Semaphores for forks
sem_t mutex;                    // Semaphore for mutual exclusion

void *philosopher(void *num) {
    int philosopher_num = *((int *)num);

    while (1) {
        printf("Philosopher %d is thinking...\n", philosopher_num);
        sleep(1);  // Simulate thinking time

        // Try to pick up the forks
        sem_wait(&mutex);  // Ensure mutual exclusion
        sem_wait(&forks[philosopher_num]);        // Pick up left fork
        sem_wait(&forks[(philosopher_num + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        // Eating
        printf("Philosopher %d is eating...\n", philosopher_num);
        sleep(2);  // Simulate eating time

        // Put down the forks
        sem_post(&forks[philosopher_num]);        // Put down left fork
        sem_post(&forks[(philosopher_num + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
        sem_post(&mutex);  // Release mutual exclusion

        // Philosophers will alternate between thinking and eating
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // Initialize mutual exclusion semaphore
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Initialize each fork semaphore (available = 1)
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    // Wait for all philosophers to finish (this will never happen in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up semaphores (this will never happen in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}
