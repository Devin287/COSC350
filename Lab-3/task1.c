#include <stdio.h>
#include <unistd.h>

int main(){

  //Creates buffer to read charcters
  char buffer[1];
  int nread;
  
  //loop to read and write to a file
  while ((nread = read(0, buffer, 1) > 0)){
    write (1, buffer, nread);
  }

  return 0;

}
