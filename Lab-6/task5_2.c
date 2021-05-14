#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>



int str_to_int(char *str){
    int result;
    int x;

        result = 0;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result);
}

char* int_to_str(int value){
    char *c = calloc(sizeof(value), sizeof(char));
    for(int i=0; i<sizeof(value);i++){
        c[(sizeof(value)-i)-1]=(value%10)+'0';
        value/=10;
    }
    return c;
}

int isNum(char c){

	int ascii = (int)c;

	if(ascii >= (int)'0' && ascii <= (int)'9'){
		return ascii;
	}
	return 0;
}

int main(int argc, char *argv[])
{   
    pid_t pid;
    char buffer[1];
    int InFileDes;
    int OutFileDes;
    int OutFileDes2;

    InFileDes = open(argv[1], O_RDONLY);

    printf("fork program starting\n");
    pid = fork();

    switch(pid) {
        case -1:perror("fork failed");
        exit(1);
    case 0:
        OutFileDes = open("child.txt", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
        lseek(InFileDes, 0, SEEK_SET);
        while ((read(InFileDes, buffer, 1) > 0)){
            
            if(isNum(buffer[0]) == 0){
                write(OutFileDes, &buffer, 1);
            }
        }
        break;
    default:
        OutFileDes2 = open("parent.txt", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);

        while ((read(InFileDes, buffer, 1) > 0)){
            if(isNum(buffer[0])){
                write(OutFileDes2, &buffer, 1);
            }
        }
        break;
    }

    close (InFileDes);
    close (OutFileDes);
    close (OutFileDes2);

    
    exit (0);
}