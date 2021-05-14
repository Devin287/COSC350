#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int READ_END = 0;
  int WRITE_END = 1;
  int mypipe1[2], mypipe2[2];

  pipe(mypipe1);
  pipe(mypipe2);
  
  pid_t pid = fork();

  if (pid == 0)
  { 
    close(mypipe1[READ_END]);
    close(mypipe2[WRITE_END]);

    char message[] = "Hi, Mom";
    write(mypipe1[WRITE_END], message, 8);
    close(mypipe1[READ_END]);

    char buffer[11];
    if (read(mypipe2[READ_END], buffer, 11) > 0){
      printf("My mon said %s\n", buffer);
      close(mypipe2[WRITE_END]);
    }
  }
  else if (pid > 0){ 
    close(mypipe1[WRITE_END]);
    close(mypipe2[READ_END]);

    char buffer2[8];
    if (read(mypipe1[READ_END], buffer2, 8) > 0){
      printf("My child said %s\n", buffer2);
      close(mypipe1[READ_END]);
    }

    char message2[] = "I love you\n";
    write(mypipe2[WRITE_END], message2, 11);
    close(mypipe2[WRITE_END]);
  }

  return 0;
}