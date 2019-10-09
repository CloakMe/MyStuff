#ifndef SortingAlgorithmsParameter
#include "..\\SortingAlgorithms\\SortingAlgorithms.h"
#endif

#include <math.h>

int main()
{
	int n = 100;
	double* arr = new double[n];
	for(int i=0; i<n; i++)
	{
		arr[i] = sin((double) i);
	}
			
	SortingAlgorithms<double>::MergeSort(arr, n);
	bool flag = true;
	for(int i=0; i<n-1; i++)
	{
		if(arr[i] > arr[i+1])
		{
			flag = false;
			break;
		}
	}
	return 0;
}

