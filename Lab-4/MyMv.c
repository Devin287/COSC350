#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{ 
    //Checks for three arguments
    if(argc != 3){
        printf("Not enough arguments!\n");
        return -1;
    }
    //Links file and checks if link was created
   if(link(argv[1], argv[2]) <0){
       printf("Link error!");
       exit(1);
   }
    unlink(argv[1]);
   
    exit(0);
}