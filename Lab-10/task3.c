#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>

#define SIZE 10

#define MUTEX 0
#define EMPTY 2
#define FULL 1

int buffArray[SIZE];
int semid;

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void up(int semid, int index){
    struct sembuf up = {index, 1, 0};
    semop(semid, &up, 1);

}

void down(int semid, int index){
    struct sembuf down = {index, -1, 0};
    semop(semid, &down, 1);
}

void* producer(void* arg){
    int semid = (int) arg;
    int item, index, i;

    while(1){
        item = rand() % 9 + 1;
        
        down(semid, EMPTY);
        down(semid, MUTEX);
        
        index = semctl(semid, FULL, GETVAL);
        buffArray[index] = item;

        printf("Producing %d\n", item);
    
        for(i = 0; i < SIZE; i++){
            printf("%d ", buffArray[i]);
        }

        up(semid, MUTEX);
        up(semid, FULL);
        
        printf("\n\n");
        sleep(1);
    }
}

void* consumer(void* arg){
    int semid = (int) arg;
    int item,index;
    while(1){
        down(semid, FULL);
        down(semid, MUTEX);

        index = semctl(semid,FULL,GETVAL);
        item = buffArray[index];

        printf("Consuming %d\n", item);
        buffArray[index] = 0;

        up(semid, MUTEX);
        up(semid, EMPTY);

        printf("\n\n");
        sleep(2);
    }
}

int main(){
    key_t key;
    union semun sema;
    int semid;
    pthread_t threads[2];
    if((key = ftok("task3.c", 'A')) < 0){
        perror("Error: unable to do ftok().\n");
        exit(1);
    }

    // Creates three semaphores with the key and the privileges rw-rw-rw-
    if((semid = semget(key, 3, 0666 | IPC_CREAT)) < 0){
        perror("Error: unable to do semget().\n");
        exit(1);
    }

    // Sets the values of the semaphores to 0, 1, and N (10)
    sema.val = 1;
    semctl(semid, MUTEX, SETVAL, sema);
    sema.val = 0;
    semctl(semid, FULL, SETVAL, sema);
    sema.val = SIZE;
    semctl(semid, EMPTY, SETVAL, sema);

    // Creates threads for the consumer and the producer
    pthread_create(&threads[0], NULL, producer, (void*)semid);
    pthread_create(&threads[1], NULL, consumer, (void*)semid);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}