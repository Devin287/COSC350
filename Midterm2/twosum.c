#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 256
void err_sys(char *);
int main(void){
    char line[MAXLINE];
    FILE *fpin;
    int arg1,arg2,temp;
    if ( (fpin = popen("./anyinput", "r")) == NULL)
        err_sys("popen error");

        while(1){
        printf("Enter Two Integers: ");
        fflush(stdout);

        if (fgets(line, MAXLINE, fpin) == NULL) 
            break;
        if(sscanf(line,"%d%d",&arg1,&arg2)==2){
            if (fputs(line, stdout) == EOF) 
                err_sys("fputs error to pipe");
            printf("The product is: %d\n",(arg1*arg2));
        }
        else{
            printf("Please use two integers for input\n");
        }
    }

    if (pclose(fpin) == -1)
        printf("pclose did not work!");
        exit(1);

    putchar('\n');
    exit(0);
}
void err_sys(char *s)
{
printf ("%s \n", s);
exit (1);
}