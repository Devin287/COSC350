#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

#define BUFFER_SIZE 32

int main()
{
    int inputFile, outputFile;
    int temp;
    //Opens file
    inputFile = open("foo", O_RDONLY);
    //Checks for error
    if(inputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        exit(1);
    }
    //determines the seettings of the mask that controls how file permissions are set
    umask(0);
    //Opens file
    outputFile = open("clone2", O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG);
    //Checks for error
    if(inputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (outputFile);
        exit(1);
    }

    int nbyte;
    char buffer[BUFFER_SIZE];
    //Loops through to copy
    while((nbyte = read(inputFile, buffer, BUFFER_SIZE)) >0){
        if(write (outputFile, buffer, nbyte) != nbyte){
            printf("Error");
        }
    }
        

    close (inputFile);
    close (outputFile);
    exit (0);
}