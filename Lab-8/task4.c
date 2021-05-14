#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int size = 0;
    char *cmd;
    char buf[BUFSIZ];
    FILE *ptr;

    //Stores the length of arguments
    for(int i = 1; i < argc; i++)
    {
        size += strlen(argv[i]);
    }
    //Creates dynamic array of type char
    cmd = malloc(size *sizeof(char));
    //Append text to buffer
    for(int i = 1; i < argc; i++)
    {
        sprintf(cmd, "%s %s", cmd, argv[i]);
    }
    //Calls popen to open a process by creating a pipe, forking, and invoking shell
    if((ptr = popen(cmd, "r")) != NULL)
        //reads a line from the specified stream and stores it into the string
        while(fgets(buf, BUFSIZ, ptr) != NULL)
            (void) printf("%s", buf);
    
    //closes a pipe stream to or from process
    pclose(ptr);
    return 0;
}