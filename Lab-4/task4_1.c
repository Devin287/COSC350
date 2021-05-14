#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{ 
    char buffer[1];
    int InFileDes;
    int OutFileDes;

    //Opens file
    InFileDes = open("/home/dev/COSC350/Lab-4/hello", O_RDONLY);
    //Checks if file was opened
    if (InFileDes == -1)
    {
        printf("Could not open file!");
        exit(1);
    }

    //Makes directories
    umask(0);
    mkdir(("/home/dev/Dir1"), 0777);
    umask(0);
    mkdir(("/home/dev/Dir2"), 0777);
    umask(0);
    mkdir(("/home/dev/Dir2/Dir21"), 0777);
    
    //Opens file
    OutFileDes = open("/home/dev/Dir2/Dir21/hello", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
    //Checks if file was opened
    if (OutFileDes == -1)
    {
        printf("Could not open file!");
        close (InFileDes);
        exit(1);
    }
    //Copies file
    while ((read(InFileDes, buffer, 1) > 0)){
        write(OutFileDes, buffer, 1);
    }
    //Creates symbolic link
    if(symlink("/home/dev/Dir2/Dir21", "/home/dev/Dir1/toDir21") <0){
        printf("Symbolic link error!");
        exit(1);
    }
    //Creates symbolic link
    if(symlink("/home/dev/Dir2/Dir21/hello", "/home/dev/Dir1/toHello") <0){
        printf("Symbolic link error!");
        exit(1);
    }
    //Closes files
    close(InFileDes);
    close(OutFileDes);
    
    exit(0);
}