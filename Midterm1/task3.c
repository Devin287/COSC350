#include<unistd.h>
#include<sys/stat.h>
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
    char buffer[1];
    char buffer2[80];
    int counter = 0;
    int InFileDes;
    int OutFileDes;

    InFileDes = open(argv[1], O_RDONLY);
    OutFileDes = open(argv[2], O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);

    while ((read(InFileDes, buffer, 1) > 0)){
        if(isNum(buffer[0])){

            buffer2[counter] = buffer[0];
            counter++;
        }
    }
    int temp = 0;

    temp= 100 + str_to_int(buffer2);
    
    write(OutFileDes, int_to_str(temp), counter);

    close (InFileDes);
    close (OutFileDes);

    
    exit (0);
}