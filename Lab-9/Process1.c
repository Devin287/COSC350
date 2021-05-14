//sender.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>
#include <ctype.h>
#include "header.h"

int main(int argc, char *argv[]){
    int shmid;
    key_t key;
    struct Memory *shm;
    char *userInput = (char *)calloc(256, sizeof(int));
    //get key value
    key = ftok(".", 'x');
    //open shared memory
    if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0){ 
        perror("shmget error \n");
        exit (1);
    }
    //attach to shared memory
    shm = (struct Memory *) shmat(shmid, NULL, 0); 
    if ((long)shm == -1){
        perror("shmat error \n");
        exit (1);
    }
    
    shm->gostop = GO;
    shm->status = NOT_READY;

    while(1){//runs forever
        printf("Enter two integers.\n");
        fgets(userInput, 256, stdin);
        if(feof(stdin)){//checks for EOF
            shm->gostop = STOP;
            break;
        }
        //Checks for two integers from keyboard and assigns num1 and num2
        if(sscanf(userInput, "%d%d",&shm->data.num1,&shm->data.num2 ) == 2){
            shm->status = FILLED;
        }
        else{//Reiterates through loop if program does not get two integers
            printf("Wrong input! Please input two integers!");
            continue;
        }    
        while (shm->status != TAKEN)
            ;
        printf("Data is taken by other process\n");
    }
    shm->gostop = STOP;
    shmdt((void *) shm); //detach
    free(userInput);
    return 0;
}