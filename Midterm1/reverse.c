#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>



int main()
{
    int inputFile, outputFile ;
    char buffer;

    inputFile = open("foo", O_RDONLY);

    outputFile = open("symmetry", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    int fileSize = lseek(inputFile, -1, SEEK_END);
    
    while(fileSize > -1){
        read(inputFile, &buffer, 1);
        write(outputFile, &buffer, 1);
        lseek(inputFile, -2, SEEK_CUR);
        fileSize--;
    }

    lseek(outputFile, 0, SEEK_END);
    write(outputFile, " || ", 4);
    lseek(outputFile, 0, SEEK_END);

    lseek(inputFile, 0, SEEK_SET);

    while(read(inputFile, &buffer, 1) > 0){
        write(outputFile, &buffer, 1);
    }

    
    close (inputFile);
    close (outputFile);
    
    exit (0);
}
