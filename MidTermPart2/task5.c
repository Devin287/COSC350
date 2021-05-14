#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void finish(int sig){
    exit(0);
}

void *Thread2(){
    while(1){
        sleep(1);
        printf("Thread Two\n");
    }
}

void *Thread1(void *arg){
    int count = 1;
    while(1){
        sleep(1);
        printf("Thread One\n");
        if(count == 10){
            kill(getpid(),SIGALRM);
        }else{
            count++;
        }
    }
}

int main(){
    int rc;
    pthread_t tid1, tid2;

    if(rc = pthread_create(&tid1, NULL, Thread1, NULL) != 0){
        perror("Pthread Error: Cant make thread One.\n");
    }
    if(rc = pthread_create(&tid2, NULL, Thread2, NULL) != 0){
        perror("Pthread Error: Cant make thread Two.\n");
    }

    while(1){
        sleep(1);
        printf("original thread\n");
        signal(SIGALRM, finish);
    }
}