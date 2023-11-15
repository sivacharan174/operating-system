#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define READERS_COUNT 3
#define WRITERS_COUNT 2
#define READER_ITERATIONS 3
#define WRITER_ITERATIONS 2

pthread_t readerThreads[READERS_COUNT], writerThreads[WRITERS_COUNT];
sem_t mutex, resource, readerCount;
int readers = 0;

void *readerFunction(void *id) {
    int reader_id = *((int *)id);

    for (int i = 0; i < READER_ITERATIONS; i++) {
        sem_wait(&mutex);
        readers++;
        if (readers == 1) {
            sem_wait(&resource);
        }
        sem_post(&mutex);

        printf("Reader %d is reading. Iteration: %d\n", reader_id, i + 1);

        sem_wait(&mutex);
        readers--;
        if (readers == 0) {
            sem_post(&resource);
        }
        sem_post(&mutex);
    }

    pthread_exit(NULL);
}

void *writerFunction(void *id) {
    int writer_id = *((int *)id);

    for (int i = 0; i < WRITER_ITERATIONS; i++) {
        sem_wait(&resource);

        printf("Writer %d is writing. Iteration: %d\n", writer_id, i + 1);

        sem_post(&resource);
    }

    pthread_exit(NULL);
}

int main() {
    int reader_ids[READERS_COUNT], writer_ids[WRITERS_COUNT];

    sem_init(&mutex, 0, 1);
    sem_init(&resource, 0, 1);

    for (int i = 0; i < READERS_COUNT; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, readerFunction, &reader_ids[i]);
    }

    for (int i = 0; i < WRITERS_COUNT; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writerThreads[i], NULL, writerFunction, &writer_ids[i]);
    }

    for (int i = 0; i < READERS_COUNT; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    for (int i = 0; i < WRITERS_COUNT; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&resource);

    return 0;
}
