#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE_PATH "/home/dang/IT4946E/week8/fifo.txt"

int main(int argc, char *argv[]) {
    int fileFd, fifoFd;
    char buffer[256];
    ssize_t bytesRead;

    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    fileFd = open(argv[1], O_RDONLY);
    if (fileFd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Create the FIFO file
    mkfifo(FIFO_FILE_PATH, 0666);

    // Open the FIFO file for writing
    fifoFd = open(FIFO_FILE_PATH, O_WRONLY);
    if (fifoFd == -1) {
        perror("Error opening FIFO file");
        return 1;
    }

    // Read the file and write its contents to the FIFO file
    while ((bytesRead = read(fileFd, buffer, sizeof(buffer))) > 0) {
        write(fifoFd, buffer, bytesRead);
    }

    // Close file descriptors
    close(fileFd);
    close(fifoFd);

    return 0;
}
