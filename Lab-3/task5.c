#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int inputFile, outputFile;
    char buffer;
    //Opens file
    inputFile = open("foo", O_RDONLY);
    //Checks for error
    if(inputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        exit(1);
    }
    //determines the settings of the mask that controls how file permissions are set
    umask(0);
    //Opens file
    outputFile = open("foorev", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
    //Checks for error
    if(outputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (outputFile);
        exit(1);
    }
    //Sets descriptor
    int fileSize = lseek(inputFile, -1, SEEK_END);
    //Copies file
    while(fileSize > -1){
        read(inputFile, &buffer, 1);
        write(outputFile, &buffer, 1);
        lseek(inputFile, -2, SEEK_CUR);
        fileSize--;
    }

    close (inputFile);
    close (outputFile);

    exit (0);
}