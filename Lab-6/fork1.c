#include <sys/types.h>
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

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:perror("fork failed");
        exit(1);
    case 0:message = "This is the child";
        n = Nc;
        slpTm= Tc;
        break;
    default:message = "This is the parent";
        n = Np;
        slpTm=Tp;
        break;
    }

    for(; n > 0; n--) {
            puts(message);
            sleep(slpTm);
        }
    exit(0);
}