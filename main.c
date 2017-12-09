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

struct thread_data  thread_data_array[NUM_THREADS];


void *CalcAvg(void *threadarg)
{
    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
    int total = 0;
	int nums = 0;

	
	int i = 0;
	
	// Change for into while loop and eliminate if, examine each element of the array

	while(strlen(mydata->array1[i]) != 0)
	{
		val = atoi(mydata->array1[i]);
        total += val;
	    i++;
	}
	mydata->value = total / i;
 	
    pthread_exit(NULL);
}

void *CalcMin(void *threadarg)
{

    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
	int i = 0;
	int min = atoi(mydata->array1[0]);


	while(strlen(mydata->array1[i]) != 0)
	{
		val = atoi(mydata->array1[i]);
		if (val < min)
        {
            min = val;
            
        }
	    i++;
	}
	mydata->value = min;
    

    pthread_exit(NULL);
}

void *CalcMax(void *threadarg)
{
    struct thread_data *mydata;
    mydata = (struct thread_data *) threadarg;
    int val;
	int i = 0;
	int max = atoi(mydata->array1[0]);


	while(strlen(mydata->array1[i]) != 0)
	{
		val = atoi(mydata->array1[i]);
		if (val > max)
        {
            max = val;
        }
	    i++;
	}
	mydata->value = max;
    

    pthread_exit(NULL);
	
}
