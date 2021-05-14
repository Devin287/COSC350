#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int inputFile, outputFile, inputFile2;
    char buffer;

    /* Open file for read only */
    inputFile = open("foo", O_RDONLY);
    if(inputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        exit(1);
    }
    //Opens file 
    inputFile2 = open("foo1", O_RDONLY);
    //Checks for error
    if(inputFile2 == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (inputFile2);
        exit(1);
    }
    //determines the seettings of the mask that controls how file permissions are set
    umask(0);
    //Opens file
    outputFile = open("foo12", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
    //Checks for error
    if(outputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (inputFile2);
        close (outputFile);
        exit(1);
    }
    //Copys file
    while(read(inputFile, &buffer, 1) == 1){
        write(outputFile, &buffer, 1);
    }
    //Set descriptor
    lseek(outputFile, 0, SEEK_END);
    //Copy file
    while(read(inputFile2, &buffer, 1) == 1){
        write(outputFile, &buffer, 1);
    }
    close (inputFile);
    close (inputFile2);
    close (outputFile);

    exit (0);
}