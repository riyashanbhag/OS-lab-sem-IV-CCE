#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5      // Size of the bounded buffer
#define MAX_ITERATIONS 10  // Maximum number of times producer and consumer run

// Shared buffer and index
int buffer[BUFFER_SIZE];
int in = 0;  // Points to the next empty slot in the buffer
int out = 0; // Points to the next filled slot in the buffer

// Semaphores
sem_t empty;  // Semaphore to count the empty slots
sem_t full;   // Semaphore to count the full slots
sem_t mutex;  // Mutex to ensure mutual exclusion

// Shared counter to control the number of iterations
int counter = 0;  // Shared counter between producer and consumer

// Producer function
void *producer(void *param) {
    int item;

    while(counter < MAX_ITERATIONS) {
        item = rand() % 100;  // Produce an item (random number for simplicity)
        
        // Wait for an empty slot
        sem_wait(&empty);
        
        // Lock the buffer (critical section)
        sem_wait(&mutex);
        
        // Insert item into the buffer
        buffer[in] = item;
        printf("Producer produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;  // Update the index
        
        // Unlock the buffer
        sem_post(&mutex);
        
        // Signal that there is a new full slot
        sem_post(&full);
        
        sleep(rand() % 3);  // Simulate time taken to produce an item
        
        // Increment the counter (producer's work is done)
        counter++;
    }

    pthread_exit(NULL);  // Exit the producer thread when done
}

// Consumer function
void *consumer(void *param) {
    int item;

    while(counter < MAX_ITERATIONS) {
        // Wait for a full slot
        sem_wait(&full);
        
        // Lock the buffer (critical section)
        sem_wait(&mutex);
        
        // Consume an item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;  // Update the index
        
        // Unlock the buffer
        sem_post(&mutex);
        
        // Signal that there is a new empty slot
        sem_post(&empty);
        
        sleep(rand() % 3);  // Simulate time taken to consume an item
        
        // Increment the counter (consumer's work is done)
        counter++;
    }

    pthread_exit(NULL);  // Exit the consumer thread when done
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, the buffer is empty
    sem_init(&full, 0, 0);  // Initially, no items are in the buffer
    sem_init(&mutex, 0, 1);  // Initially, the buffer is unlocked

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("Producer and Consumer have finished executing.\n");

    return 0;
}
