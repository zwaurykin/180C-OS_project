#ifndef __MQS_H__
#define __MQS_H__

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

int maxArr;
vector<int> arr;
bool selectionSortUsed = false;

// threads call this function
void *run(void *p); 
//int array_master[20];
void merge(vector<int> arr, int left, int middle, int right);
// function to swap two elements in the array
void swap(int *a, int *b);
// function to partition in the array
int partition(vector<int> &arr, int start, int end);
// The main function that implements QuickSort
void quickSort(vector<int> &arr, int start, int end);
// function for selection sort
void selectionSort(vector<int> &a);




#endif //__MQS_H__