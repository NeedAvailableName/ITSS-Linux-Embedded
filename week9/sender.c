#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MESSAGE_TYPE 1

struct message {
    long type;
    char text[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate the same key used in Program 1
    key = ftok("/tmp", 'Q');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Connect to the existing message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Prompt the user to enter a message
    printf("Enter a message to send: ");
    fgets(msg.text, sizeof(msg.text), stdin);
    msg.type = MESSAGE_TYPE;

    // Send the message to Program 1
    msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0);

    // Display a success message
    printf("Message sent successfully.\n");

    return 0;
}
