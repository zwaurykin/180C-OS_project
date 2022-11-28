#ifndef __MMS_H__
#define __MMS_H__
#include <vector>
using namespace std;

int maxArr;
vector<int> a;

bool selectionSortUsed = false;
// number of threads
#define THREAD_MAX 3


// array of size MAX
int part = 0;

// merge function for merging two parts
void merge(int low, int mid, int high);
// merge sort function
void merge_sort(int low, int high);
// thread function for multi-threading
void* merge_sort(void* arg);



#endif