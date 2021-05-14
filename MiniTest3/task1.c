#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
   pid_t pid, pid1, ppid;
   int i, endID, status;
   pid = fork();
   if(pid == 0){
       pid1 = fork();
       if(pid1 == 0){
            ppid = getppid();
            while(1){
                if(getppid()==ppid){
                   printf("I am your grandchild with ID = %d\n",getpid());
                   sleep(1);
                }else{
                   printf("Since my parent gone, I am done my life");
                   _exit(0);
                }
            }
        }else{
            for(i=0; i<30; i++){
               printf("I am your child which ID = %d\n",getpid());
               sleep(1);
           }
            _exit(0);
        }
    }else{
        while (1){
            endID=waitpid(pid,&status, WNOHANG|WUNTRACED);
            if(endID==0){
                printf("I am your parent with ID = %d\n",getpid());
                sleep(1);
            }else{
                printf("Now my job is over\n");
                exit(0);
            }
       }
    }
    return 0;
}