#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

typedef struct MSGBUF{
    long type;
    int one;
    int two;
} MsgBuffer;

void handleEnd(){
    printf("Terminating");
}

int main(int argc, char *argv[])
{
    // Sets key value to msgQsnd.c
    key_t key;
    if ((key = ftok("msgQsnd.c", 'B')) == -1){
        printf("ERROR: ftok() error!");
        exit(1);
    }

    // Creates the message queue with the key and the privileges rw-r--r-- (0644)
    // IPC_CREAT creates entry if key does not exist
    int Qid;
    if ((Qid = msgget(key, 0644 | IPC_CREAT)) == -1){
        printf("ERROR: msgget() error!");
        exit(1);
    }

    MsgBuffer buffer;
    buffer.type = 1; // Set the message type to 1, must be > 0. Used by the receiving process for message selection
    char *userInput = (char *)calloc(256, sizeof(int));

    puts("Enter two integer values: ");

    for(; ;){
        fgets(userInput, 256, stdin);
        if (feof(stdin)){
            printf("EOF");
            buffer.one = -1;
            buffer.two = -1;
            // Removing the message queue, using msgctl to remove the IPC identifier
            if (msgsnd(Qid, (MsgBuffer *)&buffer, 2 * sizeof(int), 0) == -1){
                printf("ERROR: msgsnd() error!");
            }
            printf("Sending EOF to msgQrcv.c\n");
            if (msgctl(Qid, IPC_RMID, NULL) == -1){
                printf("ERROR: msgctl() error!");
                exit(1);
            }
            return 0;
        }
        // Converting the input into 2 integers and checking for two integers
        if(sscanf(userInput, "%d%d", &buffer.one, &buffer.two) == 2){
            if (buffer.two == -10) {
                printf("You inserted 1 value!\n");
            }
            // Sending the MsgBuffer struct, with our 2 integers, to the message queue
            else if (msgsnd(Qid, (MsgBuffer *)&buffer, 2 * sizeof(int), 0) == -1){
                printf("ERROR: msgsnd() error!");
            }
        }
        
       
        buffer.one = -10; // Clear buffer with custom value
        buffer.two = -10; // Clear buffer with custom value
        puts("Enter two integer values: ");
    }

    return 0;
}