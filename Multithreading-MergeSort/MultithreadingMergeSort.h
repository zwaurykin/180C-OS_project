#ifndef __MMS_H__
#define __MMS_H__

#include <iostream>
#include <pthread.h>
#include <time.h>
#include <vector>
using namespace std;

int maxArr;
vector<int> a;

bool selectionSortUsed = false;
// number of threads
#define THREAD_MAX 2


// array of size MAX
int part = 0;

// merge function for merging two parts
// the interval from [s to m] and [m+1 to e] in v are sorted
// the function will merge both of these intervals
// such the interval from [s to e] in v becomes sorted
void merge(vector<int> &v, int s, int m, int e);
// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void merge_sort(vector<int> &v, int s, int e);
// thread function for multi-threading
void* merge_sort(void* arg);
// selection sort function
void selectionSort(vector<int> &arr);



#endif