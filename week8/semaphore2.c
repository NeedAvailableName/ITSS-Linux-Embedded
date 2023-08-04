#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define SEM_KEY 1234

void semWait(int semId) {
    struct sembuf semBuf;

    semBuf.sem_num = 0;
    semBuf.sem_op = -1;
    semBuf.sem_flg = SEM_UNDO;

    if (semop(semId, &semBuf, 1) == -1) {
        perror("Error performing semaphore wait operation");
        exit(1);
    }
}

void semSignal(int semId) {
    struct sembuf semBuf;

    semBuf.sem_num = 0;
    semBuf.sem_op = 1;
    semBuf.sem_flg = SEM_UNDO;

    if (semop(semId, &semBuf, 1) == -1) {
        perror("Error performing semaphore signal operation");
        exit(1);
    }
}

int main() {
    int semId;
    key_t semKey;
    char str[] = "Program 2 ends";

    // Generate a key for the semaphore
    semKey = ftok(".", SEM_KEY);
    if (semKey == -1) {
        perror("Error generating semaphore key");
        exit(1);
    }

    // Create or get the semaphore
    semId = semget(semKey, 1, IPC_CREAT | 0666);
    if (semId == -1) {
        perror("Error creating/getting semaphore");
        exit(1);
    }

    // Signal the semaphore
    semSignal(semId);

    // Output the character string
    printf("%s\n", str);

    return 0;
}
