#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void err_sys(char *);
int main()
{
  int c;
  while ( (c = getchar()) != EOF) /* read input from keyboard */
  {
    if (isupper(c)) /* change to capital to lower case */
      c = tolower(c);
    if (putchar(c) == EOF) /* write on standard output until ctr-D */
      err_sys("output error");
    if (c == '\n')
      fflush(stdout);
  }
  exit(0);
  }
  
  void err_sys(char *s)
  {
    printf ("%s \n", s);
    exit (1);
  }
