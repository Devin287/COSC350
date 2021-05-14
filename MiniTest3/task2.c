#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int char_to_int(char *input){ 
    int number = 0; 
    int position = 0; 
    while(input[position] != '\0'){ 
        number = (10 * number) + (input[position] - '0'); 
        position++; 
    } 
    return number; 
} 

int main(int argc, char* argv[]){
    if(argc<2){
        printf("Argument Error: Not enough arguments passed\n");
        exit(0);
    }
    int number;
    if((number= char_to_int(argv[1]))<1){
        printf("Invalis number input: Number is less that 1\n");
        exit(1);
    }else{
        char* stringOfRandom = malloc(number*sizeof(char));
        for(int i=0; i<number;i++){
            stringOfRandom[i]=rand()%26 + 'a';
        }
        write(0,stringOfRandom,number);
        printf("\n");
    }
    exit(0);
}