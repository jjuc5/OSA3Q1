/*
 * OS Design & System Programming
 * Professor:  Cristina Ribeiro
 * Assignment 3 Question 1
 * File:   main.c
 * Author: Melanie Iarocci, John Urbanowicz
 *
 * Created on November 1, 2017, 3:03 PM
 * Modified On 12/09/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define NUM_THREADS 3

struct thread_data {
    int thread_id;
    char array1[256][256];
    int value;
};

struct thread_data thread_data_array[NUM_THREADS];

void *CalcAvg(void *threadarg) {
    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
    int total = 0;
    int nums = 0;


    int i = 0;

    // Change for into while loop and eliminate if, examine each element of the array

    while (strlen(mydata->array1[i]) != 0) {
        val = atoi(mydata->array1[i]);
        total += val;
        i++;
    }
    mydata->value = total / i;

    pthread_exit(NULL);
}

void *CalcMin(void *threadarg) {

    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
    int i = 0;
    int min = atoi(mydata->array1[0]);


    while (strlen(mydata->array1[i]) != 0) {
        val = atoi(mydata->array1[i]);
        if (val < min) {
            min = val;

        }
        i++;
    }
    mydata->value = min;


    pthread_exit(NULL);
}

void *CalcMax(void *threadarg) {
    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
    int i = 0;
    int max = atoi(mydata->array1[0]);


    while (strlen(mydata->array1[i]) != 0) {
        val = atoi(mydata->array1[i]);
        if (val > max) {
            max = val;
        }
        i++;
    }
    mydata->value = max;


    pthread_exit(NULL);

}

/*
 *
 */
int main(int argc, char *argv[]) {
    // argc is the number of arguments given
    // argv is a list of string containing command line arguments



    long t;
    int rc;
    void *status;
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;

    // Initialize and set thread detached attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);




    // Initializing the struct and doing the pthread_create
    for (t = 0; t < NUM_THREADS; t++) {
        thread_data_array[t].thread_id = t;

        int index;
        for (index = 1; index < argc; ++index) {
            strcpy(thread_data_array[t].array1[index - 1], argv[index]);
        }

        thread_data_array[t].value = 0;

        printf("Main: creating thread %ld\n", t);
        if (t == 0) {
            rc = pthread_create(&thread[t], &attr, CalcAvg, (void *) &thread_data_array[t]);
        } else if (t == 1) {
            rc = pthread_create(&thread[t], &attr, CalcMin, (void *) &thread_data_array[t]);
        } else if (t == 2) {
            rc = pthread_create(&thread[t], &attr, CalcMax, (void *) &thread_data_array[t]);
        }
        if (rc) {
            printf("ERROR; return code from pthread_create is %d\n", rc);
            exit(-1);
        }
    }
    // Free attribute and wait for the other threads
    //pthread_attr_destroy(&attr);
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        if (t == 0) printf("The average value is %d\n", thread_data_array[t].value);
        if (t == 1) printf("The minimum value is %d\n", thread_data_array[t].value);
        if (t == 2) printf("The maximum value is %d\n", thread_data_array[t].value);

    }
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}