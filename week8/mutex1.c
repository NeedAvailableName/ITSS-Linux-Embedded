#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* program1(void* arg) {
    pthread_mutex_lock(&mutex); // Lock the mutex
    printf("Program 1: Mutex locked\n");

    printf("Program 1: Press Enter to unlock the mutex\n");
    while (getchar() != '\n') {} // Wait for Enter key

    pthread_mutex_unlock(&mutex); // Unlock the mutex
    printf("Program 1: Mutex unlocked\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, program1, NULL);
    pthread_join(thread, NULL);

    return 0;
}
