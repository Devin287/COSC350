#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

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
    int sum;
    //Adds the arguments 
    for(int i; i<argc; i++){
        sum = sum + toInt(argv[i]);
    }
    printf("The sum is %d\n", sum);
    
    exit (0);
}