#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

typedef struct MSGBUF{
  long type;
  int one;
  int two;
} MsgBuffer;

int main(int argc, char *argv[]){
  // Sets key value to msgQsnd.c
  key_t key;
  if ((key = ftok("msgQsnd.c", 'B')) == -1){
    printf("ERROR: ftok() error!");
    exit(1);
  }

  // Creates the message queue with the key and the privileges rw-r--r-- (0644)
  // IPC_CREAT creates entry if key does not exist
  int Qid;
  if ((Qid = msgget(key, 0644 | IPC_CREAT)) == -1){
    printf("ERROR: msgget() error!");
    exit(1);
  }

  MsgBuffer buffer;
  for(; ;){
    // Reads the message from the buffer and store into MsgBuffer object
    if (msgrcv(Qid, (MsgBuffer *)&buffer, 2 * sizeof(int), 0, 0) == -1){
      printf("msgQsnd.c sent termination, killing this program");
      msgctl(Qid, IPC_RMID, NULL);
      exit(0);
    } 
    printf("The sum of the digits is %d \n", buffer.one + buffer.two);
  }


  return 0;
}