//receiver.c
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"

int main(int argc, char *argv[]){
    int shmid;
    key_t key;
    struct Memory *shm;
    key = ftok(".", 'x'); //get key value
    // open existing shared memory
    if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0){
        perror("shmget error \n");
        exit (1);
    }
    //a pointer is attach to shared memory
    shm = (struct Memory *) shmat(shmid, NULL, 0);
    if ((long)shm == -1){
        perror("shmat error \n");
        exit (1);
    }
    //continue…
    // read from the shared memory
    while (shm->gostop == GO){
        while (shm->status != FILLED){
            if (shm->gostop == STOP)
                break;
            ;
        }
        //Program prints if EOF is not triggered
        if(shm->gostop != STOP){
            printf ("The sum is: %d \n", (shm->data.num1 + shm->data.num2));
            shm->status = TAKEN;
        }
        
    }
    shmdt((void *) shm); //detach
    return 0;
}