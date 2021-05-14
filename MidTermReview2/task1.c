#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void terminate(int sig){
    if(sig == SIGUSR1){
        printf("terminated by parent\n");
        kill(getppid(), SIGUSR2);
        _exit(0);
    }else if(sig == SIGUSR2){
        printf("my child is gone so i am now\n");
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
            signal(SIGUSR2, terminate);
            for(i=0;i<=10;i++){
                printf("parent running\n");
                sleep(1);
            }
            kill(pid,SIGUSR1);
        }
    }else{
        while(1){
            printf("child is running forever\n");
            signal(SIGUSR1, terminate);
            sleep(1);
        }   
    }
}