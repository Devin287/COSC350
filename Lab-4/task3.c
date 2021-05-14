#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int palind(int fd1, int fd2){
    //Moves file descriptor to end of file
    int counter = lseek(fd2, O_RDONLY, SEEK_END);
    char buffer[counter];
    //reads the file
    read(fd1, buffer, counter);
   //Checks for palindromes 
    for(int i =0; i < counter; i++){
         if(buffer[i] != buffer[(counter- 1)- i]){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char buffer2[80];
    int InFileDes, InFileDes2;
    //Opens file
    InFileDes = open(argv[1], O_RDONLY);
    //Checks if file was opened
    if (InFileDes == -1)
    {
        printf("Could not open file!");
        exit(1);
    }
    //Opens file
    InFileDes2 = open(argv[1], O_RDONLY);
    //Checks if file was opened
    if (InFileDes2 == -1)
    {
        printf("Could not open file!");
        close (InFileDes);
        exit(1);
    }
    //Calls palindrome function to check file for palindrome
    if(palind(InFileDes, InFileDes2) == 1){
        printf("There is a palindrome!\n");
    }
    else{
        printf("There is not a palindrome!");
    }
    //Closes file
    close (InFileDes);
    close (InFileDes2);
    exit (0);
}