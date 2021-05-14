#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//Displays an array that is passed to the function
void displayArray(int * array){
    printf("Displaying array: ");
    for (int i = 0; i <= 20; i++){
        if(array[i] == -1){
            break;
        }
        else{
            printf("%d ",array[i]);
        }
    }
    printf("\n\n");
}

//Stores values in array that is passed to function and sorts them
void getScores(int *array){
    int number = 0;
    int size = 0;
	for (int i = 0; i <= 20; i++) {
        printf("Type in a score(-1 to exit): ");
        scanf("%d", &number);
        if(number == -1){
            break;
        }
        else{
            array[i]=number;
            size++;
        }
    }
    //Array is sorted to easily manipulate values
    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-i-1; j++){
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    array[size]= -1;
    //Terminates thread
    pthread_exit(NULL);
}

//Gets the average and median of an array that is passed to function
void getAvgAndMed(int *array){
	int sum = 0;
    float avg, med;

    for (int i = 0; i <= 20; i++) {
        
        if(array[i] == -1){
            if(sum == 0){
                printf("There are no entries or curve the scores");
                pthread_exit(NULL);
            }
            else{
                avg = (float)sum/i;

                if(i % 2 == 0){
                    int rs = (i/2);
                    int ls = (i/2)-1;
                    med = ((float)array[ls] + (float)array[rs])/2;
                }
                else{
                    med = array[i / 2];
                }
            }
        }
        sum = array[i] + sum;
    }
    //Prints average and median and diplays array
    printf("Average score is %2.2f\n", avg);
    printf("Median score is %2.2f\n", med);
    displayArray(array);

    //Terminates thread
    pthread_exit(NULL);
}

//Gets the minimum and maximum of an array passed to function
void getMinAndMax(int *array){
    int max = 0;
    int min = array[0];
    for (int i = 0; i <= 20; i++) {
        if(array[i] == -1){
            if(max == 0){
                printf("Not enough scores");
            }
            break;
        }
        max = array[i];
    }
    //Prints the minimum and maximum score and displays array
    printf("\nMinimum score is %d\n", min);
    printf("Max score is %d\n", max);
    displayArray(array);
    //Terminates thread
    pthread_exit(NULL);
}

//Clears array and input buffer
void clearBuffer(int *array){
    printf("Clearing buffer..\n");
    //Causes any unwritten data for that stream to be written to the file
    fflush(stdin);
    fflush(stdout);
    for (int i = 0; i <= 20; i++) {
        array[i] = 0;
    }
    //Terminates thread
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    //Creates array of three threads
    pthread_t thread[3];
    int rc;
    //Creates a dynamic integer arrray of size 20 
    int *scores = malloc(20 * sizeof(int));
    
    //Creates thread and call getscores
    if(rc = pthread_create(&thread[0], NULL, (void* )(int*)getScores, (void *)scores) != 0){
        printf("ERROR; return code from pthread_create()");
    }
    //Making sure specific thread exits
    pthread_join(thread[0], NULL);
    //Creates thread and call getAvgAndMed
    if(rc = pthread_create(&thread[1], NULL, (void* )(int*)getAvgAndMed, (void *)scores) != 0){
        printf("ERROR; return code from pthread_create()");
    }
    //Creates thread and call getMinAndMax
    if(rc = pthread_create(&thread[2], NULL, (void* )(int*)getMinAndMax, (void *)scores) != 0){
        printf("ERROR; return code from pthread_create()");
    }
    //Making sure specific thread exits
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    //Creates thread and call clearBuffer
    if(rc = pthread_create(&thread[3], NULL,(void* )(int*) clearBuffer, (void *)scores) != 0){
        printf("ERROR; return code from pthread_create()");
    }
    //Making sure specific thread exits
    pthread_join(thread[3], NULL);
    
    //Displays the array at end of program
    displayArray(scores);
    //Terminates thread
    pthread_exit(NULL);
    
    exit(0);
}