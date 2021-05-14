#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SIZE 10
typedef int semaphore;
semaphore mutex = 0;
semaphore empty = 2;
semaphore full = 1;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void up(int i, int semid) {
    struct sembuf up = {i, 1, 0};
    semop(semid, &up, 1);
}

void down(int i, int semid) {
    struct sembuf down = {i, -1, 0};
    semop(semid, &down, 1);
}

void handler(int sig){
    if(sig == SIGUSR1){
        //printf("Parent terminated by child\n");
        exit(0);
    }else if(sig == SIGUSR2){
        //printf("I am child and must leave\n");
        exit(0);
    }
}

int main() {
    union semun arg;
    key_t key = ftok(".", 'K');
    int semid = semget(key, 1, 0);

    pid_t pid = fork();
    int count = 0;
    if(pid == 0) {
        while(1){
            if(count == 2){
                kill(getppid(),SIGUSR1);
                wait(NULL);
                kill(pid, SIGUSR2);
                
            }
            signal(SIGUSR2, handler);
            
            down(empty, semid);
            down(mutex, semid);
            printf("Child is in critical section %d\n",count);
            up(mutex, semid);
            up(full, semid);

            count++;
            sleep(2);
        }
    } else { 
        while(1) { 
            signal(SIGUSR1, handler);  
            
            down(empty, semid);
            down(mutex, semid);
            printf("Parent is in critical section\n");
            up(mutex, semid);
            up(full, semid);
            sleep(1);
        }
    } 
    semctl(semid, 0, IPC_RMID, arg);
    return 0;
}