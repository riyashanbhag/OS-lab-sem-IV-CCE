#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex, readCountMutex, writeSemaphore;
int readCount = 0;

void* reader(void* param) {
    int id = *((int*)param);
    
    sem_wait(&readCountMutex);  // Lock readCountMutex
    readCount++;
    if (readCount == 1) {
        sem_wait(&writeSemaphore);  // First reader locks writer access
    }
    sem_post(&readCountMutex);  // Unlock readCountMutex

    // Critical section: reading the shared resource
    printf("Reader %d is reading\n", id);
    sleep(1);  // Simulate reading time

    sem_wait(&readCountMutex);  // Lock readCountMutex
    readCount--;
    if (readCount == 0) {
        sem_post(&writeSemaphore);  // Last reader releases the write semaphore
    }
    sem_post(&readCountMutex);  // Unlock readCountMutex

    return NULL;
}

void* writer(void* param) {
    int id = *((int*)param);
    
    sem_wait(&writeSemaphore);  // Wait for writer access (lock the write semaphore)
    
    // Critical section: writing the shared resource
    printf("Writer %d is writing\n", id);
    sleep(2);  // Simulate writing time
    
    sem_post(&writeSemaphore);  // Release write access

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int readerIds[MAX_READERS], writerIds[MAX_WRITERS];
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // Mutex for critical section
    sem_init(&readCountMutex, 0, 1); // Mutex for readCount
    sem_init(&writeSemaphore, 0, 1); // Semaphore for writers

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        readerIds[i] = i;
        pthread_create(&readers[i], NULL, reader, (void*)&readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        writerIds[i] = i;
        pthread_create(&writers[i], NULL, writer, (void*)&writerIds[i]);
    }

    // Join reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&readCountMutex);
    sem_destroy(&writeSemaphore);

    return 0;
}
