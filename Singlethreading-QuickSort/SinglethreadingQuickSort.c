#include "SinglethreadingQuickSort.h"

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high], i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
/* function to print an array */
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

void merge(int arr[], int left, int middle, int right)
{
	int i, j, k;
	int half1 = middle - left + 1, half2 = right - middle;
	int first[half1], second[half2]; // temp arrays
	for (i = 0; i < half1; i++)
	{
		first[i] = arr[left + i];
	}
	for (j = 0; j < half2; j++)
	{
		second[j] = arr[middle + 1 + j];
	}
	i = 0;
	j = 0;
	k = left;
	while (i < half1 && j < half2)
	{
		if (first[i] <= second[j])
		{
			arr[k] = first[i];
			++i;
		}
		else
		{
			arr[k] = second[j];
			j++;
		}
		k++;
	}
	while (i < half1)
	{
		arr[k] = first[i];
		i++;
		k++;
	}
	while (j < half2)
	{
		arr[k] = second[j];
		j++;
		k++;
	}
}
/* Driver program to test above functions */
int main()
{
	printf("SingleThreading QuickSort\n");
	printf("\n");
	/* Intializes random number generator */
	srand((unsigned)time(NULL));
	// generating random values in array
	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);
	clock_t start, end;
	double time_difference;
	start = clock(); // Time take by CPU
	int midpoint = MAX / 2;
	quickSort(arr, 0, midpoint);
	quickSort(arr, midpoint + 1, MAX - 1);
	merge(arr, 0, (MAX / 2), MAX - 1);
	end = clock();
	time_difference = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	printf("\n\nTotal time taken by CPU: %f\n", time_difference);
	return 0;
}
