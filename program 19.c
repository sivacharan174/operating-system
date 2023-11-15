#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 3 // Number of threads
#define ITERATIONS 5    // Number of iterations each thread runs

pthread_mutex_t mutex; // Mutex declaration

void *threadFunction(void *id) {
    int thread_id = *((int *)id);

    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex); // Lock the critical section using mutex
        printf("Thread %d: Inside critical section, Iteration: %d\n", thread_id, i + 1);
        pthread_mutex_unlock(&mutex); // Unlock the critical section
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy the mutex

    return 0;
}
