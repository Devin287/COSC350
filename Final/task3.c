#include <sys/types.h>
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int READ_END = 0;
int WRITE_END = 1;

void handler(int sig) {
  if(sig == SIGUSR1) {
  }
}

int main() {
  
  umask(0);
  int p1[2];

  pipe(p1);

  int fd1 = open("foo", O_CREAT | O_RDWR, 0666);
  int fd2 = dup(fd1);
  pid_t pid = fork(); 

  signal(SIGUSR1, handler); 

  if(pid == 0) { 
    write(fd2, "Hi, Mom", 7);
    close(fd2);
    
    kill(getppid(), SIGUSR1);
    pause();

    close(p1[WRITE_END]);

    char msg[18];
    if(read(p1[READ_END], msg, 18) > 0){
      printf("My Mom said %s\n", msg);
      close(p1[READ_END]);
    }

    return 0;

  }else{

    pause();
    lseek(fd1, SEEK_SET, 0);
    
    char readMSG[7];
    read(fd1, readMSG, 7);
    printf("My son said %s\n", readMSG);
    
    char msgBuf[18] = "what do you want\0";
    write(p1[WRITE_END], msgBuf, 18);
    kill(pid, SIGUSR1);
    
    close(fd1);
    close(p1[READ_END]);
    close(p1[WRITE_END]);
  }

  return 0;

}