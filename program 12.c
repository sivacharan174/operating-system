#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N];
pthread_t philosophers[N];
sem_t room;

void *philosopher(void *num) {
    int philosopher_number = *(int *)num;
    int right = (philosopher_number + 1) % N;
    int left = (philosopher_number + N - 1) % N;

    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher_number);

        sem_wait(&room);
        pthread_mutex_lock(&forks[right]);
        pthread_mutex_lock(&forks[left]);

        printf("Philosopher %d is eating.\n", philosopher_number);

        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
        sem_post(&room);
    }
    return NULL;
}

int main() {
    int i;
    int philosopher_numbers[N];

    sem_init(&room, 0, N);

    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < N; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    sem_destroy(&room);

    return 0;
}
