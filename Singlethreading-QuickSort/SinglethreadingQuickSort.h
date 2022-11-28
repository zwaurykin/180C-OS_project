#ifndef __SQS_H__
#define __SQS_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int arr[20];
#define MAX 20

void swap(int *a, int *b);
int partition(int arr[], int low, int high);
//function that implements QuickSort
void quickSort(int arr[], int low, int high);
/* function to print an array */
void printArray(int A[], int size);
void merge(int arr[], int left, int middle, int right);


#endif //__SQS_H__