#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void handler(int sig){
    if(sig == SIGUSR1){
        printf("I am terminated by my parents\n");
        kill(getppid(), SIGUSR2);
        _exit(0);
    }else if(sig == SIGUSR2){
        printf("My child is gone so I am now\n");
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
            signal(SIGUSR2, handler);
            for(i=0;i<=10;i++){
                printf("parent is running\n");
                sleep(1);
            }
            kill(pid,SIGUSR1);
        }
    }else{
        while(1){
            printf("child is running\n");
            signal(SIGUSR1, handler);
            sleep(1);
        }   
    }
}