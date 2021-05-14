#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void parentResponse(int sig){
    if(sig == SIGUSR1){
        printf("Hi Honey! Anything wrong?\n");
    }else if(sig == SIGUSR2){
        printf("Do you make trouble again?\n");
    }
} 

int main(){
    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_handler = parentResponse;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;

    pid_t pid = fork();
    switch(pid){
        case -1: 
            printf("Fork Error\n");
            exit(1);
        break;
        
        case 0:
            kill(pid,SIGUSR1);
            exit(0);
        break;
    }
    sigaction(SIGUSR1,&act,NULL);
    pause();

    pid_t child = fork();
    switch (child){
        case -1:
            printf("Fork Error\n");
            exit(1);
        break;
    
        case 0:
            kill(child,SIGUSR2);
            exit(0);
        break;
    }

    sigaction(SIGUSR2,&act,NULL);

    wait(NULL);
    wait(NULL);
    return 0;
}