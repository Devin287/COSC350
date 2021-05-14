#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void message(int sig){
    if(sig == SIGUSR1){
        printf("From now on I am zombie\n");
        _exit(0);
    }
}

int main(){
    pid_t pid;
    int i;

    if((pid =fork())< 0){
        perror("fork failed\n");
        exit(1);
    }
    if(pid > 0){
        while(1){
            for(i=0;i<10;i++){
                printf("I am your parent\n");
                sleep(1);
            }
            kill(pid,SIGUSR1);
        }
    }else{
        while(1){
            printf("I am your child\n");
            signal(SIGUSR1, message);
            sleep(1);
        }   
    }
}