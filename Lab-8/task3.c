#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 256 

int main(){
    int n, fd[2], num1, num2;
    pid_t pid;
    char line[MAXLINE] , line2[MAXLINE];

    //Calling pipe to setup connection
    if(pipe(fd) < 0) 
        printf("pipe error");
    //Calling fork to create child
    if( (pid = fork()) < 0) 
        printf("fork error");
    //If child is running
    else if(pid > 0){
        close(fd[0]);
        //Reads standard input
        while(read(STDIN_FILENO, line, MAXLINE) > 0){
            write(fd[1], line, MAXLINE);
            printf("Enter two numbers: ");
        }
    } //Parent is running
    else{
        close(fd[1]);
        //Reads the file
        while((n = read(fd[0], line2, MAXLINE))>0){
            //takes the user input
			if(sscanf(line2, "%d%d", &num1, &num2) == 2){
                //stored string in format as printf in buffer
				sprintf(line2, "The sum is %d\n", num1 + num2);
				n = strlen(line2);
                //Write to standaroutput file descriptor
				if (write(STDOUT_FILENO, line2, n) != n){
                    //Exits program on error
					puts("Writing error.");
					exit(1);
				}
			}
			else{
                //Write to standaroutput file descriptor
				write(STDOUT_FILENO, "Need to enter two integers!\n", 40);
               
			}
		}
    }
    exit(0); 
}