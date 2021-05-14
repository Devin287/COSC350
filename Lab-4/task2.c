#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>



int str_to_int(char *str){
    int result=0;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result);
}

int convIntToStr(char * str, int x){
    sprintf(str, "%d", x);
    return (strlen(str));
}

int isNum(char c){
    int num = (int)c;
	if(num >= (int)'0' && num <= (int)'9'){
		return num;
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

    //Opens file
    InFileDes = open(argv[1], O_RDONLY);
    //Checks if file was opened
    if (InFileDes == -1)
    {
        printf("Could not open file!");
        exit(1);
    }
    //Opens file
    OutFileDes = open("discover", O_WRONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP);
    //Checks if file was opened
    if (OutFileDes == -1)
    {
        printf("Could not open file!");
        close (InFileDes);
        exit(1);
    }
    //reads file
    while ((read(InFileDes, buffer, 1) > 0)){
        //checks if it is a number
        if(isNum(buffer[0])){
            //Fills buffer with numbers
            buffer2[counter] = buffer[0];
            counter++;
        }
    }
    int temp = 0;
    //Cnverts string to int so 10 can be added
    temp= (str_to_int(buffer2));
    temp+=10;
  
    char temp2[counter];
    //Converts back to char so it can be written to a file
    convIntToStr(temp2,temp);

    write(OutFileDes, temp2, counter);
    //closes file
    close (InFileDes);
    close (OutFileDes);

    
    exit (0);
}