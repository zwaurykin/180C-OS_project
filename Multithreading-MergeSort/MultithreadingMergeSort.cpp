#include <iostream>
#include "MultithreadingMergeSort.h"
#include <pthread.h>
#include <time.h>

/*void merge(int low, int mid, int high)
{
	int *left = new int[mid - low + 1];
	int *right = new int[high - mid];

	// n1 is size of left part and n2 is size
	// of right part
	int n1 = mid - low + 1, n2 = high - mid, i, j;

	// storing values in left part
	// cout <<"LEFT ";

	for (i = 0; i < n1; i++)
	{
		left[i] = a[i + low];
		// cout << a[i] << " ";
	}
	// storing values in right part
	// cout <<"RIGHT ";

	for (i = 0; i < n2; i++)
	{
		right[i] = a[i + mid + 1];
		// cout << a[i] << " ";
	}
	// cout << a[i] << " ";

	int k = low;
	i = j = 0;

	// merge left and right in ascending order
	while (i < n1 && j < n2)
	{
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}

	// insert remaining values from left
	while (i < n1)
	{
		a[k++] = left[i++];
	}

	// insert remaining values from right
	while (j < n2)
	{
		a[k++] = right[j++];
	}
}

// merge sort function
void merge_sort(int low, int high)
{
	// calculating mid point of array
	int mid = low + (high - low) / 2;
	if (low < high)
	{

		// calling first half
		merge_sort(low, mid);

		// calling second half
		merge_sort(mid + 1, high);

		// merging the two halves
		merge(low, mid, high);
	}
}*/

// the interval from [s to m] and [m+1 to e] in v are sorted
// the function will merge both of these intervals
// such the interval from [s to e] in v becomes sorted
void merge(vector<int>& v, int s, int m, int e) {
	
    // temp is used to temporary store the vector obtained by merging
    // elements from [s to m] and [m+1 to e] in v
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void merge_sort(vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge_sort(v, s, m);
		merge_sort(v, m + 1, e);
		merge(v, s, m, e);
	}
}

// thread function for multi-threading
void *merge_sort(void *arg)
{
	// which part out of 3 parts
	int thread_part = part++;

	// calculating low and high
	int low = thread_part * (maxArr / 4);
	int high = (thread_part + 1) * (maxArr / 4) - 1;

	// evaluating mid point
	int mid = low + (high - low) / 2;
	if (low < high)
	{
		merge_sort(a,low, mid);
		merge_sort(a,mid + 1, high);
		merge(a,low, mid, high);
	}
}

// void swap(int *xp, int *yp)
// {
// 	int temp = *xp;
// 	*xp = *yp;
// 	*yp = temp;
// }

void selectionSort(vector<int> &arr)
{
    // step 1: loop from the beginning of the array to the second to last item
    for (int currentIndex = 0; currentIndex < arr.size() - 1; currentIndex++) {
        // step 2: save a copy of the currentIndex
        int minIndex = currentIndex;
        // step 3: loop through all indexes that proceed the currentIndex
        for (int i = currentIndex + 1; i < arr.size(); i++) {
          /* step 4:  if the value of the index of the current loop is less
                      than the value of the item at minIndex, update minIndex
                      with the new lowest value index */
            if (arr[i] < arr[minIndex]) {
                // update minIndex with the new lowest value index
                minIndex = i;
            }
        }
        // step 5: if minIndex has been updated, swap the values at minIndex and currentIndex
        if (minIndex != currentIndex) {
            int temp = arr[currentIndex];
            arr[currentIndex] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// Driver Code
int main()
{
	cout << "Please enter the size of the list."<< endl;
	cin >> maxArr;

	cout<<"*************************************************************************************************************"<<endl;

	srand(time(nullptr));
	// generating random values in array
	for (int i = 0; i < maxArr; i++)
	{
		int r = 1 + (rand() % 100);
		a.push_back(r);
	}
	cout << "Given array with size "<< maxArr<<" is:";

	cout << endl;
	for (int i = 0; i < maxArr; i++)
		cout << a[i] << " ";
	cout << endl;
	cout << endl;
	// t1 and t2 for calculating time for
	// merge sort
	clock_t t1, t2;

	t1 = clock();
	if (maxArr < 100)
	{
		selectionSort(a);
		selectionSortUsed = true;
	}
	else
	{
		pthread_t threads[THREAD_MAX];

		// creating 3 threads
		for (int i = 0; i < THREAD_MAX; i++)
		{
			pthread_create(&threads[i], NULL, merge_sort,
						   (void *)NULL);
		}

		// joining all 3 threads
		for (int i = 0; i < 3; i++)
		{
			pthread_join(threads[i], NULL);
		}

		// merging the final 3 parts
		merge(a, 0, (maxArr / 2 - 1) / 2, maxArr / 2 - 1);
		merge(a,maxArr / 2, maxArr / 2 + (maxArr - 1 - maxArr / 2) / 2, maxArr - 1);
		merge(a,0, (maxArr - 1) / 2, maxArr - 1);
	}
	t2 = clock();
	cout << endl;
	// displaying sorted array
	cout << "Sorted array via ";
	selectionSortUsed ? cout << "Selection sort" : cout << "Multithreaded Merge sort";
	cout << " is :" << endl;
	for (int i = 0; i < maxArr; i++)
		cout << a[i] << " ";
	cout << endl;
	// time taken by merge sort in seconds
	cout << endl;
	cout << "Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl;

	return 0;
}
