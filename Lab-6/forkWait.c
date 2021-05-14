#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int str_to_int(char *str){
    int result=0;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result);
}

int main(int argc, char* argv[]){
    pid_t pid;
    char *message;
    
    if(argc != 5){
        printf("Not enough arguments!");
        exit(1);
    }
    int n;
    int Nc = str_to_int(argv[1]); 
    int Np = str_to_int(argv[2]);
    int Tc = str_to_int(argv[3]); 
    int Tp = str_to_int(argv[4]);
    int slpTm;
    int exit_code;

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:perror("fork failed");
        exit(1);
    case 0:message = "This is the child";
        n = Nc;
        slpTm = Tc;
        exit_code = 37;
        break;
    default:message = "This is the parent";
        n = Np;
        slpTm = Tp;
        exit_code = 0;
        break;
    }

    for(; n > 0; n--){
        puts(message);
        sleep(slpTm);
    }

    if (pid != 0) {
        int stat_val;
        pid_t child_pid;
        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val)){
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        }
        else{
            printf("Child terminated abnormally\n");
        }
        exit(exit_code);
    }

}