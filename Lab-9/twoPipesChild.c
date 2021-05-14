#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
    int data_processed, data_processed2;
    char buffer[BUFSIZ + 1];
    int file_descriptor;
    int file_descriptor2;

    memset(buffer, '\0', sizeof(buffer));
    
    sscanf(argv[1], "%d", &file_descriptor);
    sscanf(argv[2], "%d", &file_descriptor2);

    data_processed = read(file_descriptor, buffer, BUFSIZ);
    data_processed2 = write(file_descriptor2, "Hi Mom", BUFSIZ);

    printf("Child (%d) recieved \" %s \" Byte count: %d\n", getpid(), buffer, data_processed);
    printf("Child (%d) Byte count: %d \n", getpid(), data_processed2);

    exit(EXIT_SUCCESS);
}