#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>

#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2
#define STOP 3

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
    int shmid, sum;
    key_t key;
    struct Memory *shm;
    key = ftok(".", 'B'); 

    if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0){
        perror("shmget error \n");
        exit (1);
    }

    shm = (struct Memory *) shmat(shmid, NULL, 0);
    if ((long)shm == -1){
        perror("shmat error \n");
        exit (1);
    }

    while (shm->gostop == GO){
        while (shm->status != FILLED){
            if (shm->gostop == STOP)
                break;
            ;
        }
        if(shm->data.finish == STOP){
            printf("\ntask2a.c exited by EOF and stopped sending data\n");
            break;
        }else{
            
            sum = shm->data.num1 + shm->data.num2;
            printf ("First number is %d and Second number is %d\n", shm->data.num1, shm->data.num2);
            printf ("The sum is %d\n",sum);
            shm->status = TAKEN;
        }
    }
    shmdt((void *) shm);
    return 0;
}