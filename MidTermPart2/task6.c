#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0; // global variable

void *increment(){
  for(; ;){
    if(count < 10){
      pthread_mutex_lock(&count_mutex);
      count++;
      printf("Increment thread Count: %d\n", count);
      pthread_mutex_unlock(&count_mutex);
    }
  }
}

void *decrement(){
  for(; ;){
    if(count > 0){
      pthread_mutex_lock(&count_mutex);
      count--;
      printf("Decrement thread Count: %d\n", count);
      pthread_mutex_unlock(&count_mutex);
    }
  }
}

int main()
{
  pthread_t T[2];
  int code;
  code = pthread_create(&T[0], NULL, increment, NULL);
  code = pthread_create(&T[1], NULL, decrement, NULL);

  pthread_exit(NULL);
  return 0;
}