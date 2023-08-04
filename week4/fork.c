#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // 1. Confirm operation when execv is replaced with other exec* and other Linux commands.
    pid = fork();
    if (pid == 0) {
        // Child process
        // Replace execv with execvp and run "ls" command
        char* args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        // If execvp fails, this line will be reached
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        // Fork failed
        perror("fork");
        exit(1);
    }

    // 2. Confirm the operation when kill pid is executed from the console and the child process is ended
    pid = fork();
    if (pid == 0) {
        // Child process
        while (1) {
            printf("Child process running...\n");
            sleep(1);
        }
    } else if (pid > 0) {
        // Parent process
        printf("Child process PID: %d\n", pid);
        printf("Enter 'kill %d' from the console to end the child process.\n", pid);
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        // Fork failed
        perror("fork");
        exit(1);
    }

    // 3. Confirm the state of the process of the child process when wait is not used by the parent process, and the child process ends.
    pid = fork();
    if (pid == 0) {
        // Child process
        sleep(3);
        printf("Child process exiting...\n");
        exit(0);
    } else if (pid > 0) {
        // Parent process
        // Do not use wait() to wait for child process
        printf("Parent process exiting without waiting for child process...\n");
    } else {
        // Fork failed
        perror("fork");
        exit(1);
    }

    // 4. Make the program that generates and ends two or more child processes.
    for (int i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0) {
            // Child process
            printf("Child process %d running...\n", i+1);
            sleep(2);
            printf("Child process %d exiting...\n", i+1);
            exit(0);
        } else if (pid < 0) {
            // Fork failed
            perror("fork");
            exit(1);
        }
    }

    // Wait for all child processes to exit
    for (int i = 0; i < 2; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status: %d\n", i+1, WEXITSTATUS(status));
        }
    }

    return 0;
}
