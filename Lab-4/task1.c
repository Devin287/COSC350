#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include <string.h>

//Converts charcters to integers
int toInt(char *str){
    int result;
    int x;

        result = 0;
        x = 1;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result * x);
}

int main(int argc, char *argv[])
{   

    char buffer[1];
    char buffer2[4];
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

    int curr = 0;
    //Copies ASCII file into char
    while(read(InFileDes, buffer, 1) == 1){
        if(buffer[0] == ' '){
            buffer2[curr] = '\0';
            printf("%c", (char)toInt(buffer2));
            curr= 0;
        }
        else if(buffer[0] == '\n'){
            printf("\n");
            curr=0;
        }
        else{
            buffer2[curr] = buffer[0];
            curr++;
        }
    }
    close (InFileDes);
    close (OutFileDes);

    exit (0);
}