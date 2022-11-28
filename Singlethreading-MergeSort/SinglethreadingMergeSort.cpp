
#include "SinglethreadingMergeSort.h"

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

/* Driver program to test above functions */
int main()
{
	printf("SingleThreading MergeSort\n");
	printf("\n");
	srand(time(NULL));
	// generating random values in array
	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	printf("Given array is \n");
	printArray(arr, arr_size);
	// t1 and t2 for calculating time for
	// merge sort
	clock_t t1, t2;
	double time_difference;
	t1 = clock();
	mergeSort(arr, 0, arr_size - 1);
	t2 = clock();
	time_difference = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	printf("\n\nTotal time taken by CPU: %f\n", time_difference);
	return 0;
}
