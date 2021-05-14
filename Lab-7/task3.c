#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 7

int main(){
    umask(0);
    char buffer[BUFFER_SIZE];
    
    int fileDes1 = open("foo",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if(fileDes1 == -1){
        printf("File Error: Unable to open file\n");
        return 1;
    }

    int fileDes2 = dup(fileDes1);
    if(fileDes2 == -1){
        printf("File Two Error: Unable to open file\n");
        close(fileDes1);
        return 1;
    }

    pid_t pid = fork();
    if(pid == -1){
        perror("fork failed");
        exit(1);
    }else if(pid == 0){
        write(fileDes2,"Hi, Mom",BUFFER_SIZE);
        close(fileDes2);
        return 0;
    }

    wait(&pid);
    lseek(fileDes1, SEEK_SET, 0);
    read(fileDes1,buffer,BUFFER_SIZE);
    printf("My son said %s\n",buffer);

    close(fileDes1);
    return 0;
}
