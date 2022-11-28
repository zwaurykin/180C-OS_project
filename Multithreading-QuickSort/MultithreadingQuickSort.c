#include "MultithreadingQuickSort.h"


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

	i = 0; // Initialization
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

// function to swap two elements in the array
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
// function to partition in the array
int partition(int arr[], int low, int high)
{
	int pivot = arr[high], i = (low - 1); // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void *run(void *p)
{
	int midpoint = MAX / 2;
	if (strcmp(p, "first") == 0)
	{
		quickSort(array_master, 0, midpoint);
	}

	if (strcmp(p, "second") == 0)
	{
		quickSort(array_master, midpoint + 1, MAX - 1);
	}

	if (strcmp(p, "third") == 0)
	{
		merge(array_master, 0, (MAX / 2), MAX - 1);
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	printf("Multi-Threading QuickSort\n");
	printf("\n");

	/* Intializes random number generator */
	srand((unsigned)time(NULL));
	// generating random values in array
	for (int i = 0; i < MAX; i++)
	{
		array_master[i] = rand() % 100;
	}
	printf("Given array is: \n");
	for (int i = 0; i < MAX; i++)
		printf("%d ", array_master[i]);

	printf("\n \n");

	// t1 and t2 for calculating time for
	// merge sort
	clock_t start, end;
	double time_difference;

	start = clock();

	pthread_t tid;		  /* the thread identifier */
	pthread_attr_t attr1; // first thread attributes

	pthread_t tid2;		  // second thread id
	pthread_attr_t attr2; // second thread attributes

	pthread_t tid3; // third thread id
	pthread_attr_t attr3;

	char *thread_no = "first";
	pthread_attr_init(&attr1);
	pthread_create(&tid, &attr1, run, thread_no); /* create the thread */

	char *thread2 = "second";
	pthread_attr_init(&attr2);
	pthread_create(&tid2, &attr2, run, thread2); /* create the thread */

	char *thread3 = "third";
	pthread_attr_init(&attr3);
	pthread_create(&tid3, &attr2, run, thread3); /* create the thread */

	pthread_join(tid, NULL);  /* join the thread */
	pthread_join(tid2, NULL); /* join the thread */
	pthread_join(tid3, NULL); /* join the thread */
	end = clock();
	printf("Sorted Array:\n");
	int j;
	for (j = 0; j < MAX; j++)
	{
		if (j == MAX - 1)
		{
			printf("%d", array_master[j]);
		}
		else
		{
			printf("%d ", array_master[j]);
		}
	}
	time_difference = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n\nTotal time taken by CPU: %f\n", time_difference);
	pthread_exit(0);

	return 0;
}
