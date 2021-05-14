#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void Bye1(void *);
void Bye(void *);
void *Thread1(void *);
void *Thread2(void *);

int main(int argc, char** argv){
    pthread_t tid, tid1, tid2;
    int rc=0;
    void *tmp1, *tmp2;
    tid = pthread_self();

    pthread_cleanup_push(Bye1, NULL);

    rc = pthread_create(&tid2, NULL, Thread1, (void *)tid);
    rc = pthread_create(&tid1, NULL, Thread2, (void *)tid2);
    while(1){
        printf("This is original thread!\n");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return 0;
}

void Bye1(void *arg){
    printf("Original thread job is done!\n");
}

void Bye(void *arg){
    pthread_t tid = (pthread_t)arg;
    int rc;
    printf("The first thread job is done! \n");
    rc = pthread_cancel(tid);
}

void *Thread1(void *arg){
    pthread_t tid = (pthread_t)arg;
    printf("Entered the first thread\n");
    pthread_cleanup_push(Bye, (void *)tid);
    while(1){
        printf("This is the first thread!\n");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
}

void *Thread2(void *arg){
    int count, rc;
    pthread_t tid = (pthread_t)arg;
    printf("Entered the second thread\n");
    for(count=1; count<=10; count++){
        printf("This is the second thread running %d times\n", count);
        sleep(1);
    }
    rc = pthread_cancel(tid);
}