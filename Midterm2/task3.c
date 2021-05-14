#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fun1(void *arg){
    long num = (long)arg;
    num = num + 10;
    return ((void*) num);
}

void *fun2(void *arg){
    long num = (long)arg;
    num = num + 20;
    return ((void*) num);
}

void *fun3(void *arg){
     long num = (long)arg;
    num = num + 30;
    return ((void*) num);
}

int str_to_int(char *input){ 
    int number = 0; 
    int position = 0; 
    while(input[position] != '\0'){ 
        number = (10 * number) + (input[position] - '0'); 
        position++; 
    } 
    return number; 
} 

int main(int args, char *argv[]){
    if(args == 1){
        printf("Invalid Input: too many or too little arguments passed\n");
        return 1;
    }
    long num = atoi(argv[1]);
    int rc;
    pthread_t tid1, tid2, tid3;
    void *tret1, *tret2, *tret3;

    rc = pthread_create(&tid1, NULL, fun1, (void*)num);
    rc = pthread_join(tid1, &tret1);

    rc = pthread_create(&tid2, NULL, fun2, (void*)tret1);
    rc = pthread_join(tid2, &tret2);

    rc = pthread_create(&tid3, NULL, fun3, (void*)tret2);
    rc = pthread_join(tid3, &tret3);

    printf("The final result of three threads calculation is %ld\n", (long) tret3);
    exit(0);
}