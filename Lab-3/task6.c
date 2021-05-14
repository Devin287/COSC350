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
    //determines the seettings of the mask that controls how file permissions are set
    umask(0);
    //Opens file
    outputFile = open("foorev1", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
    //Checks for errors
    if(outputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (outputFile);
        exit(1);
    }
    //for file size
    int fileSize = 0;
    //reads charcters and increases file size to keep track
    while(read(inputFile, &buffer, 1) > 0){
        fileSize++;
    }
    //Copies file
    while(fileSize > 0){
        pread(inputFile, &buffer, 1, fileSize);
        write(outputFile, &buffer, 1);
        fileSize--;
    }

    close (inputFile);
    close (outputFile);

    exit (0);
}