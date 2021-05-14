#include <stdio.h>
#include <stdlib.h>

int str_to_int(char* str){
    int result;
    int x;

        result = 0;
        x = 1;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result);
}

int main(int argc, char *argv[])
{
    int sumEven = 0;
    int sumOdd = 0;
    
    if(argc<2){
	exit(0);
    }
    else{
       for(int i; i<argc; i++){
	   if(str_to_int(argv[i])%2!=0){
	     sumOdd = sumOdd + str_to_int(argv[i]);
	   }
       }
    }

    printf("The sum of odd numbers are %d\n", sumOdd);

    
    exit (0);
}