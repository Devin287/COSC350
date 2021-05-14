#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2
#define STOP 3

typedef struct MSGBUF{
    long type;
    int one;
    int two;
} MsgBuffer;

struct userInput {
    int num1;
    int num2;
    int finish;
};

struct Memory {
    int status;
    int gostop;
    struct userInput data;
};

int main(int argc, char *argv[]){
    key_t key;
    if ((key = ftok(".", 'B')) == -1){
        printf("ftok() Error.\n");
        exit(1);
    }
    int Qid;
    if ((Qid = msgget(key, 0644 | IPC_CREAT)) == -1){
        printf("msgget() Error.\n");
        exit(1);
    }

    int shmid;
    struct Memory *shm;
    if ((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) <0){
        perror("shmget error \n");
        exit (1);
    }
    shm = (struct Memory *) shmat(shmid, NULL, 0);
    if ((long)shm == -1){
        perror("shmat error \n");
        exit (1);
    }
    shm->status = NOT_READY;
    shm->gostop = GO;

    MsgBuffer recieveBuffer;
    while (1){
        if (msgrcv(Qid, (MsgBuffer *)&recieveBuffer, 2 * sizeof(int), 0, 0) == -1){
            printf("Termination sent from task2a.c\n");
            shm->data.finish = STOP;
            shm->gostop = STOP;
            msgctl(Qid, IPC_RMID, NULL);
            shmctl(shmid, IPC_RMID, NULL);
            exit(0);
        }
        if(recieveBuffer.one != -1 && recieveBuffer.two != -1){
            if(recieveBuffer.one == -11 && recieveBuffer.two == -11){
                printf("Invalid Input\n");
            }else{
                shm->data.num1 = recieveBuffer.one;
                shm->data.num2 = recieveBuffer.two;
                shm->status = FILLED;
            }
        }
    }
    return 0;
}