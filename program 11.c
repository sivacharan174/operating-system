#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function for the threads to execute
void *threadFunction(void *threadID) {
    long tid;
    tid = (long)threadID;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
[10:30 am, 07/11/2023] ................A:     for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, threadFunction, (void *)t);

        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
