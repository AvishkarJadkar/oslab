#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;                // Semaphore to control access for writers
pthread_mutex_t mutex;    // Mutex to protect numreader variable
int cnt = 1;              // Shared resource
int numreader = 0;        // Number of readers currently reading

// Writer thread function
void *writer(void *wno)
{   
    sem_wait(&wrt);   // Wait for exclusive access
    cnt = cnt * 2;    // Modify shared resource
    printf("Writer %d modified count to %d\n", (*((int *)wno)), cnt);
    sem_post(&wrt);   // Signal that writing is done
    return NULL;
}

// Reader thread function
void *reader(void *rno)
{   
    pthread_mutex_lock(&mutex);   // Lock to safely update numreader
    numreader++;
    if (numreader == 1) {         // If first reader, block writers
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d: read count as %d\n", *((int *)rno), cnt);

    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0) {         // If last reader, allow writers
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{   
    pthread_t read[10], write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; 

    // Create reader threads
    for (int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, reader, (void *)&a[i]);
    }

    // Create writer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, (void *)&a[i]);
    }

    // Wait for all readers to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }

    // Wait for all writers to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

/*Short Algorithm (Readers-Writers Problem)

1.Initialize:

-A semaphore wrt = 1 to ensure only one writer (or group of readers) accesses the shared resource at a time.

-A mutex mutex to protect the numreader counter.

2.Reader Process:

-Lock mutex and increment numreader.

-If it’s the first reader, wait (sem_wait) on wrt to block writers.

-Unlock mutex and read the shared data.

-Lock mutex again and decrement numreader.

-If it’s the last reader, post (sem_post) to wrt to allow writers.

-Unlock mutex.

3.Writer Process:

-Wait (sem_wait) on wrt for exclusive access.

-Modify the shared data.

-Post (sem_post) to release access.

5.Main Function:

-Create multiple reader and writer threads.

-Wait for all threads to complete.

-Destroy mutex and semaphore.*/