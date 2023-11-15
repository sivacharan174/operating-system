#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

struct message {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key = 1234;  // Key for the message queue

    // Create a message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid > 0) {
        // Process 1: Send a message to the queue
        struct message msg;
        msg.mtype = 1;  // Message type
        printf("Enter a message to send: ");
        fgets(msg.mtext, MSG_SIZE, stdin);

        // Send the message
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    } else {
        // Process 2: Receive the message from the queue
        struct message msg;
        // Receive the message of type 1
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Message received in child process: %s", msg.mtext);
    }

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
