#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){

	if(argc < 3){
		printf("Both input and output files are not passed as arguments\n");
		exit(1);
	}
	
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 < 0){
		printf("open file error\n");
		exit(1);
	}
	umask(0);
	int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666);
	if(fd2 < 0){
		printf("open file error\n");
		exit(1);
	}

	char buffer[1];
	int nread;
	int size = 0;
	while(nread = pread(fd1, buffer, 1, size) > 0){
		size++;
	}
	int i = 1;
	while(nread = pread(fd1, buffer, 1, size - i) > 0){
		write(fd2, buffer, nread);
	}
	close(fd1);
	close(fd2);
	exit(0);
}

