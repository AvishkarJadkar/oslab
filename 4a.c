#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems 5         // Maximum items a producer can produce or consumer can consume
#define BufferSize 5       // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

// ---------------- PRODUCER FUNCTION ----------------
void *producer(void *pno) {
    int item = 0;

    for (int i = 0; i < MaxItems; i++) {
        item = rand();   // Produce a random item

        sem_wait(&empty);              // Decrease empty count
        pthread_mutex_lock(&mutex);    // Enter critical section

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);

        in = (in + 1) % BufferSize;    // Move to next position in circular buffer

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);               // Increase full count
    }

    return NULL;
}

// ---------------- CONSUMER FUNCTION ----------------
void *consumer(void *cno) {
    int item = 0;

    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full);               // Decrease full count
        pthread_mutex_lock(&mutex);    // Enter critical section

        item = buffer[out];
        printf("Consumer %d: Removed Item %d at %d\n", *((int *)cno), buffer[out], out);

        out = (out + 1) % BufferSize;  // Move to next position in circular buffer

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty);              // Increase empty count
    }

    return NULL;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    pthread_t prod[5], con[5];
    int cnt[5] = {1, 2, 3, 4, 5};

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    // Create producer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&prod[i], NULL, producer, (void *)&cnt[i]);
    }

    // Create consumer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, consumer, (void *)&cnt[i]);
    }

    // Join producer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(prod[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    // Destroy semaphores and mutex
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

/*Short Algorithm: Producer–Consumer using Semaphores

Step 1:
Initialize mutex, empty (with value = BufferSize), and full (with value = 0).

Step 2:
Create multiple producer and consumer threads.

Producer Process (each producer thread):

Generate a random item.

Wait (sem_wait(&empty)) → ensures there’s space in buffer.

Acquire mutex → enter critical section.

Insert item into buffer at index in.

Print item insertion details.

Update index in = (in + 1) % BufferSize.

Release mutex.

Signal (sem_post(&full)) → indicates a new item is available.

Consumer Process (each consumer thread):

Wait (sem_wait(&full)) → ensures at least one item is available.

Acquire mutex → enter critical section.

Remove item from buffer at index out.

Print item removal details.

Update index out = (out + 1) % BufferSize.

Release mutex.

Signal (sem_post(&empty)) → indicates a free slot is available.

Step 3:
Join all producer and consumer threads.

Step 4:
Destroy semaphores and mutex to free resources.

Step 5:
End the program.*/