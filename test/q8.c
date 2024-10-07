#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 100
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty;
sem_t full;
sem_t mutex;
void* producer(void* arg) {
int item;
for (int i = 0; i < 200; i++) {
item = rand() % 100;
sem_wait(&empty);
sem_wait(&mutex);
buffer[in] = item;
printf("Producer produced: %d\n", item);
in = (in + 1) % BUFFER_SIZE;
sem_post(&mutex);
sem_post(&full);
sleep(1);
}
return NULL;
}
void* consumer(void* arg) {
int item;
for (int i = 0; i < 200; i++) {
sem_wait(&full);
sem_wait(&mutex);
item = buffer[out];
printf("Consumer consumed: %d\n", item);
out = (out + 1) % BUFFER_SIZE;
sem_post(&mutex);
sem_post(&empty);
sleep(1);
}
return NULL;
}
int main() {
pthread_t producer_thread, consumer_thread;
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
sem_init(&mutex, 0, 1);
pthread_create(&producer_thread, NULL, producer, NULL);
pthread_create(&consumer_thread, NULL, consumer, NULL);
pthread_join(producer_thread, NULL);
pthread_join(consumer_thread, NULL);
sem_destroy(&empty);
sem_destroy(&full);
sem_destroy(&mutex);
return 0;
}