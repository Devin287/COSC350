#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define READ_END 0
#define WRITE_END 1

int main(int argc, char** argv){
	int data_processed, data_processed2;
	int file_pipes[2];
	int file_pipes2[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	char buffer2[BUFSIZ+1];
	pid_t fork_result;

	memset(buffer,'\0',sizeof(buffer));
	
	if(pipe(file_pipes)==0 && pipe(file_pipes2) ==0){
		fork_result=fork();	
		if(fork_result==(pid_t)-1){
			fprintf(stderr,"Fork Failure\n");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0){
			close(file_pipes[1]);
			close(file_pipes2[0]);
			sprintf(buffer,"%d",file_pipes[READ_END]);
			sprintf(buffer2,"%d",file_pipes2[WRITE_END]);
			(void)execl("twoPipesChild","twoPipesChild", buffer, buffer2,(char *)0);
			close(file_pipes[0]);
			exit(EXIT_FAILURE);
		}
		else{
			data_processed = write(file_pipes[WRITE_END],some_data,strlen(some_data));
			data_processed2 = read(file_pipes2[0], buffer, 6);
			printf("Parent %d sent %d bytes to child. \n", getpid(), 15);
			wait(&fork_result);
			printf("Parent (%d) recieved the message \" %s \" Byte count: %d\n", getpid(), buffer, data_processed2);
			close(file_pipes2[1]);
		}
	}
	
	exit(EXIT_SUCCESS);
}