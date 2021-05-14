#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	char buffer[BUFSIZ];
	int nread,arg1,arg2;
	while ((nread = read(0, buffer, BUFSIZ) > 0)){
        if (feof(stdin)) {
            printf("EOF");
            return 0;
        }
        if(sscanf(buffer,"%d%d",&arg1,&arg2)==2){
            if(write(STDOUT_FILENO,buffer,strlen(buffer))!=strlen(buffer)){ // writes to the standard output
                break;
            }
        }
	}
	exit(0);
}