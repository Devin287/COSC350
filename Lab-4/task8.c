#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char *argv[])
{   

    char buffer;
    //Checks for three arguments
    if(argc != 3){
        printf("Two arguments required!");
        exit(1);
    }
    //Opens file
    int InFileDes = open(argv[1], O_RDONLY);
    //checks for error
    if (InFileDes == -1)
    {
        printf("Could not open file!");
        close (InFileDes);
        exit(1);
    }
    //determines the settings of the mask that controls how file permissions are set
    umask(0);
    //Opens file
    int OutFileDes = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR | S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH);
    //Checks for error
    if (OutFileDes == -1)
    {
        printf("Could not open file!");
        close (InFileDes);
        close (OutFileDes);
        exit(1);
    }
    //Set new descriptor
    dup2(OutFileDes,1);
    //Copies file into ASCII
    while(read(InFileDes, &buffer, 1) == 1){
        
        if((int)buffer == ' '){
            printf("%d ", (int)buffer);
        }
        if((int)buffer == 10){
            printf("\n");
        }
        else{
            printf("%d ", (int)buffer);
        }
    }
    close (InFileDes);
    close (OutFileDes);

    exit (0);
}