#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE_PATH "/home/dang/IT4946E/week8/fifo.txt"

int main() {
    int fifoFd;
    char buffer[256];
    ssize_t bytesRead;

    // Open the FIFO file for reading
    fifoFd = open(FIFO_FILE_PATH, O_RDONLY);
    if (fifoFd == -1) {
        perror("Error opening FIFO file");
        return 1;
    }

    // Read data from the FIFO file and write it to the console
    while ((bytesRead = read(fifoFd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
        printf("\n");
    }

    // Close the FIFO file descriptor
    close(fifoFd);

    return 0;
}
