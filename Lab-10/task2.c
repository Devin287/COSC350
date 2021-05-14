#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

int buffer[10];
int curr = 0;

void producer()
{
    for(; ;){
        int item = rand() % 10;
    	if(curr < 10){
    		buffer[curr++] = item;
        }
    	else{
    		printf("No space to insert. \n");
        }
        printf("Producing %d\n", item);
        int i;
        for(i = 0; i < 10; i++)
        {
            printf("%d ", buffer[i]);
        }
        puts("");
        sleep(1);
    }
}
void consumer()
{
    for(; ;){
        int temp = buffer[curr - 1];
    	if(curr >= 0)
    	{
    		curr--;
    		buffer[curr] = 0;
    	}
    	else{
    		printf("No value to remove\n");
        }
        printf("Consuming %d\n", temp);
        int i;
    	for(i = 0; i < 10; i++)
        {
    		printf("%d ", buffer[i]);
        }
    	puts("");
    	sleep(2);
    }
}

int main(int argc, char* argv[])
{
    pthread_t thread_ID[2];
    pthread_create(&thread_ID[0], NULL, (void*)producer, NULL);
    pthread_create(&thread_ID[1], NULL, (void*)consumer, NULL);

    pthread_join(thread_ID[0], NULL);
    pthread_join(thread_ID[1], NULL);

    return 0;
}