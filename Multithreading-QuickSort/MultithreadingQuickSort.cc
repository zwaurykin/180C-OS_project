#include "MultithreadingQuickSort.h"

void merge(vector<int> arr, int left, int middle, int right)
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

int partition(vector<int> &arr, int start, int end)
{

	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i)
	{
		if (arr[i] < arr[pivot])
		{
			swap(arr[i], arr[j]);
			++j;
		}
	}
	swap(arr[j], arr[pivot]);
	return j;
}

void quickSort(vector<int> &arr, int start, int end)
{

	if (start < end)
	{
		int p = partition(arr, start, end);
		quickSort(arr, start, p - 1);
		quickSort(arr, p + 1, end);
	}
}

void *run(void *p)
{
	int midpoint = maxArr / 2;
	if (strcmp((char *)p, "first") == 0)
	{
		quickSort(arr, 0, midpoint);
	}

	if (strcmp((char *)p, "second") == 0)
	{
		quickSort(arr, midpoint + 1, maxArr - 1);
	}

	if (strcmp((char *)p, "third") == 0)
	{
		merge(arr, 0, (maxArr / 2), maxArr - 1);
	}
	pthread_exit(0);
}

void selectionSort(vector<int> &a)
{
	// step 1: loop from the beginning of the array to the second to last item
	for (int currentIndex = 0; currentIndex < a.size() - 1; currentIndex++)
	{
		// step 2: save a copy of the currentIndex
		int minIndex = currentIndex;
		// step 3: loop through all indexes that proceed the currentIndex
		for (int i = currentIndex + 1; i < a.size(); i++)
		{
			/* step 4:  if the value of the index of the current loop is less
						than the value of the item at minIndex, update minIndex
						with the new lowest value index */
			if (a[i] < a[minIndex])
			{
				// update minIndex with the new lowest value index
				minIndex = i;
			}
		}
		// step 5: if minIndex has been updated, swap the values at minIndex and currentIndex
		if (minIndex != currentIndex)
		{
			int temp = a[currentIndex];
			a[currentIndex] = a[minIndex];
			a[minIndex] = temp;
		}
	}
}
int main(int argc, char *argv[])
{
	clock_t start, end;
	double time_difference;

	cout << "Please enter the size of the list." << endl
		 << endl;
	cin >> maxArr;

	cout << endl
		 << "*****************************************************************************************************" << endl;

	/* Intializes random number generator */
	srand((unsigned)time(NULL));
	// generating random values in array
	for (int i = 0; i < maxArr; i++)
	{
		arr.push_back(1 + rand() % 1000);
	}
	cout<<"Given array is: "<<endl;
	for (int i = 0; i < maxArr; i++)
		cout<< arr[i]<<" ";

	cout<<endl<<endl;


	start = clock();

	if (maxArr < 100)
	{
		selectionSort(arr);
		selectionSortUsed = true;
	}
	else
	{
		pthread_t tid;		  /* the thread identifier */
		pthread_attr_t attr1; // first thread attributes

		pthread_t tid2;		  // second thread id
		pthread_attr_t attr2; // second thread attributes

		pthread_t tid3; // third thread id
		pthread_attr_t attr3;

		char thread1[] = "first";
		pthread_attr_init(&attr1);
		pthread_create(&tid, &attr1, run, thread1); /* create the thread */

		char thread2[] = "second";
		pthread_attr_init(&attr2);
		pthread_create(&tid2, &attr2, run, thread2); /* create the thread */

		char thread3[] = "third";
		pthread_attr_init(&attr3);
		pthread_create(&tid3, &attr2, run, thread3); /* create the thread */

		pthread_join(tid, NULL);  /* join the thread */
		pthread_join(tid2, NULL); /* join the thread */
		pthread_join(tid3, NULL); /* join the thread */
	}
	end = clock();
	
	cout << "Sorted array via ";
	selectionSortUsed ? cout << "Selection sort" : cout << "Multithreaded Quick sort";
	cout << " is :" << endl;

	for (int j = 0; j < maxArr; j++)
		cout<<arr[j]<<" ";

	time_difference = (end - start) / (double)CLOCKS_PER_SEC;
	cout<< endl<<endl<<"Total time taken by CPU: "<<time_difference;
	pthread_exit(0);

	return 0;
}
