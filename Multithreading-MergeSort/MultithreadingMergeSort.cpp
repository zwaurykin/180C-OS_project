#include "MultithreadingMergeSort.h"

void merge(vector<int> &v, int s, int m, int e)
{

	// temp is used to temporary store the vector obtained by merging
	// elements from [s to m] and [m+1 to e] in v
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e)
	{

		if (v[i] <= v[j])
		{
			temp.push_back(v[i]);
			++i;
		}
		else
		{
			temp.push_back(v[j]);
			++j;
		}
	}

	while (i <= m)
	{
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e)
	{
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void merge_sort(vector<int> &v, int s, int e)
{
	if (s < e)
	{
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
		merge_sort(a, low, mid);
		merge_sort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
	pthread_exit(0);
}

void selectionSort(vector<int> &arr)
{
	for (int currentIndex = 0; currentIndex < arr.size() - 1; currentIndex++)
	{
		int minIndex = currentIndex;
		for (int i = currentIndex + 1; i < arr.size(); i++)
		{
			if (arr[i] < arr[minIndex])
			{
				minIndex = i;
			}
		}
		if (minIndex != currentIndex)
		{
			int temp = arr[currentIndex];
			arr[currentIndex] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
}

// Driver Code
int main()
{
	cout << "Please enter the size of the list." << endl;
	cin >> maxArr;

	cout << "*************************************************************************************************************" << endl;

	srand(time(nullptr));
	// generating random values in array
	for (int i = 0; i < maxArr; i++)
	{
		int r = 1 + (rand() % 1000);
		a.push_back(r);
	}
	cout << "Given array with size " << maxArr << " is:";

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
			pthread_create(&threads[i], NULL, merge_sort, (void *)NULL);
		}

		// joining all 3 threads
		for (int i = 0; i < 3; i++)
		{
			pthread_join(threads[i], NULL);
		}

		// merging the final 3 parts
		merge(a, 0, (maxArr / 2 - 1) / 2, maxArr / 2 - 1);
		merge(a, maxArr / 2, maxArr / 2 + (maxArr - 1 - maxArr / 2) / 2, maxArr - 1);
		merge(a, 0, (maxArr - 1) / 2, maxArr - 1);
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
