#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int alarm_fired = 0;

void ding(int sig){
    alarm_fired = 1;
}

int main(){
    pid_t pid;
    struct sigaction act;
    memset(&act, 0, sizeof(act));

    printf("alarm application starting\n");
    
    pid = fork();
    switch(pid) {
    case -1:
        /* Failure */
        perror("fork failed");
        exit(1);
    case 0:
        /* child */
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(0);
    }
    
        /* if we get here we are the parent process */
        printf("waiting for alarm to go off\n");
        
        act.sa_handler = ding;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGALRM, &act, 0);

        pause();
        if (alarm_fired) 
            printf("Ding!\n");
        printf("done\n");
        exit(0);
}