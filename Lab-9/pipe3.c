#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define READ_END 0
#define WRITE_END 1

int main(int argc, char** argv){
	int data_processed;
	int file_pipes[2];
	const char some_data[]="123";
	char buffer[BUFSIZ+1];
	pid_t fork_result;

	memset(buffer,'\0',sizeof(buffer));
	
	if(pipe(file_pipes)==0){
		fork_result=fork();	
		if(fork_result==(pid_t)-1){
			fprintf(stderr,"Fork Failure\n");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0){
			sprintf(buffer,"%d",file_pipes[READ_END]);
			(void)execl("pipe4","pipe4",buffer,(char *)0);
			close(file_pipes[0]);
			exit(EXIT_FAILURE);
		}
		else{
			data_processed=write(file_pipes[WRITE_END],some_data,strlen(some_data));
			wait(&fork_result);
			close(file_pipes[1]);
			printf("%d ~> wrote %d bytes\n",getpid(),data_processed);
		}
	}
	
	exit(EXIT_SUCCESS);
}