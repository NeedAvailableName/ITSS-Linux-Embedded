#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* program2(void* arg) {
    printf("Program 2: Waiting for mutex to unlock\n");
    pthread_mutex_lock(&mutex); // Wait until the mutex is unlocked
    pthread_mutex_unlock(&mutex); // Release the mutex
    printf("Program 2: Mutex unlocked\n");

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, program2, NULL);
    pthread_join(thread, NULL);

    return 0;
}
