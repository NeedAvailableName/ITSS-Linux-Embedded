#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 20
#define KEYPATH "."
#define KEYCHAR 'a'

// Pham Hai Dang - 20194736
int main(int argc, char const *argv[]) {

	int shmid;
	char *shm, *ptr;
	key_t key;

	key = ftok(KEYPATH, (int)KEYCHAR);

	if ((shmid = shmget(key, SHMSIZE*sizeof(char), IPC_CREAT|0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("shmat");
		exit(1);
	}

	printf("Client has attached the shared memory...\n");
	printf("Data in shared memory: ");

	for (ptr = shm; *ptr != NULL; ptr++) {
		putchar(*ptr);
	}

	putchar('\n');

	return 0;
}