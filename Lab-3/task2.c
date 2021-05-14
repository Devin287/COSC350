#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int inputFile, outputFile;
    char buffer;

    //Opens the file to be copied
    inputFile = open("foo", O_RDONLY);
    //Throws error if file not found
    if(inputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        exit(1);
    }
    //determines the seettings of the mask that controls how file permissions are set
    umask(0);
    //Opens file to for outputting
    outputFile = open("clone1", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);
    //Checks if outputfile exits
    if(outputFile == -1){
        printf("File cannot be opened. \n");
        close (inputFile);
        close (outputFile);
        exit(1);
    }
    //loops through charcters to copy files
    while(read(inputFile, &buffer, 1) == 1){
        write(outputFile, &buffer, 1);
    }
    close (inputFile);
    close (outputFile);
    
    exit (0);
}