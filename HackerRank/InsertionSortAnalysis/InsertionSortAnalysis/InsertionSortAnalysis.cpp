// InsertionSortAnalysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;


// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
long long result = 0;
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k;
    const int n1 = m - l + 1;
    const int n2 =  r - m;
  
    //create temp arrays 
    vector<int> L(n1), R(n2);
  
    //Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
  
    // Merge the temp arrays back into arr[l..r]
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
			result += n1 - i;
            j++; 
			
        } 
        k++; 
    }

    // Copy the remaining elements of L[], if there 
    // are any 
    while (i < n1)
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of R[], if there 
    //   are any 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
// l is for left index and r is right index of the 
 //  sub-array of arr to be sorted 
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

vector<string> split_string(string input_string) 
{

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

void printArray(int arr[], int size)  
{  
    int i;
    for (i = 0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
}  

int main()
{
	ifstream myfile ("allinput.txt");
	string line;
	int n;
	int t;
	if (myfile.is_open())
	{
		getline(myfile,line);
		t = stoi(line.c_str());
		for (int t_itr = 0; t_itr < t; t_itr++) 
		{
			getline(myfile,line);
			n = stoi(line.c_str());
			result = 0;
			string arr_temp_temp;
			getline(myfile, arr_temp_temp);

			vector<string> arr_temp = split_string(arr_temp_temp);

			vector<int> arr (n);

			for (int i = 0; i < n; i++) {
				int arr_item = stoi(arr_temp[i]);

				arr[i] = arr_item;
			}

			mergeSort(&arr[0], 0, n-1);

			cout << result << "\n";
		}
		myfile.close();
	}
	else 
		cout << "Unable to open file";

	return 0;
    //int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

	

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
		result = 0;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        int *arr = new int[n];

		for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

		mergeSort(&arr[0], 0, n-1);

		cout << result << "\n";
    }	
    return 0;
}


/*

void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
			if(arr[i] != arr[j])
				k += j - i;
        }  
    }  
    swap(&arr[i + 1], &arr[high]); 
	if(arr[i + 1] != arr[high])
		k += high - i - 1;
    return (i + 1);  
}  
  

void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  
  
void printArray(int arr[], int size)  
{  
    int i;  
    for (i = 0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
}  


int insertionSort3 (int arr[], int length){
    int j, temp, k = 0;
	
    
    for (int i = 0; i < length; i++)
	{
        for(int j=i+1; j<length; j++)
		{
			if( arr[i] > arr[j] )
				k++;
		}

    }

	return k;
}


int insertionSort (int arr[], int length){
    int j, temp, k = 0;

                
    for (int i = 0; i < length; i++)
	{
        j = i;                
        while (j > 0 && arr[j] < arr[j-1])
		{
			k++;
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            j--;
        }
    }

	return k;
}

// A utility function to swap two elements  

void quickSort0(int arr[], int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];//
	while (i <= j) 
	{
		while (arr[i] < pivot)
				i++;

		while (arr[j] > pivot)
				j--;

		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	if (left < j)
		quickSort0(arr, left, j);

	if (i < right)
		quickSort0(arr, i, right);
}

void quickSort2(int arr[], int posArr[], int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];//
	while (i <= j) 
	{
		while (arr[i] < pivot)
				i++;

		while (arr[j] > pivot)
				j--;

		if (i <= j) {
			tmp = posArr[i];
			posArr[i] = posArr[j];
			posArr[j] = tmp;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	if (left < j)
		quickSort2(arr, posArr, left, j);

	if (i < right)
		quickSort2(arr, posArr, i, right);
}

*/

