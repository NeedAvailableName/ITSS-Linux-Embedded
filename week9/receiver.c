#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_TYPE 1

struct message {
    long type;
    char text[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'Q');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive and display messages until an empty message is received
    while (1) {
        // Receive a message of type MESSAGE_TYPE
        msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), MESSAGE_TYPE, 0);

        // Check if the message is empty
        if (msg.text[0] == '\0') {
            printf("Received empty message. Exiting...\n");
            break;
        }

        // Display the received message
        printf("Received message: %s\n", msg.text);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
