#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void handler(int sig){
    if(sig == SIGINT){
        printf("SIGINT was used during loop\n");
    }else if(sig == SIGQUIT){
        printf("SIGQUIT was used during loop\n");
    }
}

int main(){
    sigset_t mask;
    sigset_t orig_mask;

    struct sigaction act;
    memset (&act, 0, sizeof(act)); //clear structure
    act.sa_handler = handler; // set signal handler as hd1

// set signlal handler for SIGINT
    if (sigaction(SIGINT, &act, 0)) {
        perror ("sigaction");
        return 1;
    }

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
   
    if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) {
        perror ("sigprocmask");
        return 1;
    }

    for(int i=0; i<5;i++){
        printf("SIGINT and SIGQUIT are blocked %d\n",i);
        sleep(1);
    }

    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);

    printf("Unblocking SIGQUIT\n");

    sigprocmask(SIG_SETMASK, &orig_mask, NULL);

    sigdelset(&mask, SIGQUIT);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    
    for(int i=0; i<5; i++){
        printf("SIGINT is blocked %d\n",i);
        sleep(1);
    }
    return 0;
}