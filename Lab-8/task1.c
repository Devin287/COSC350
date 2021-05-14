#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int str_to_int(char *str){
    int result;
    int x;
        result = 0;
        while ((*str >= '0') && (*str <= '9'))
        {
            result = (result * 10) + ((*str) - '0');
            str++;
        }
        return (result);
}

//Calculates the sum of integers
void *sumUp(void *n){
    int sum = 0;
	for (int i = 1; i <= n; i++) {
        sum += i;
    }
	n = (void *) sum;
}

//Calculates the sum of n!
void *factorial(void *n){
	int fact = 1;
	for (int i = 1; i <= n; i++) {
            fact *= i;
    }
	n = (void *)fact;
}

int main(int argc, char* argv[]){
    //Checks for 2 arguments  
    if(argc != 2){
        printf("Not enough arguments!");
        exit(1);
    }
    
    //Initializing threads
    pthread_t thread1;
    pthread_t thread2;
    int rc;

    //Storing user input
    int input = str_to_int(argv[1]);

    //Creating thread and passing to function
    if(rc = pthread_create(&thread1, NULL, sumUp, (void*) input) != 0){
        printf("ERROR; return code from pthread_create()");
    }
    //Creating thread and passing to function
    if(rc = pthread_create(&thread2, NULL, factorial, (void*) input) != 0){
        printf("ERROR; return code from pthread_create()");
    }

    void *sum, *fact;
    //Making sure specific thread exits
    pthread_join(thread1, &sum);
    pthread_join(thread2, &fact);

    //Printing sum and factorial
    printf("Sum is %d \n", (int)sum);
    printf("Factorial is %d\n", (int)fact);

    //Terminating threads
    pthread_exit(NULL);
    exit(0);
}