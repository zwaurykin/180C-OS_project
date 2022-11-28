// Merges two sub-arrays of a[].
// First sub-array is a[l..m]
// Second sub-array is a[m+1..r]

#ifndef __SMS_H__
#define __SMS_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int arr[20];
#define MAX 20

void merge(int arr[], int l, int m, int r);
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r);
/* Function to print an array */
void printArray(int A[], int size);

#endif //__SMS_H__