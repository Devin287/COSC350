#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define READ_END 0
#define WRITE_END 1

int main(){
    int data_processed;
    const char some_data[] = "123";
    char *buffer = malloc(3 *sizeof(char));

    memset(buffer, '\0', 3);
    /*
        called mkfifo /tmp/task4_fifo and chmod 0777 task4_fifo

        Could have also used  mkfifo -m 0777 /tmp/task4_fifo
    */
    int fd = open("/tmp/task4_fifo", O_RDWR);

    data_processed = write(fd, some_data, strlen(some_data));
    printf("Wrote %d bytes\n", data_processed);
    data_processed = read(fd, buffer, 3);
    printf("Read %d bytes: %s\n", data_processed, buffer);
        
    free(buffer);
    exit(EXIT_SUCCESS);
}