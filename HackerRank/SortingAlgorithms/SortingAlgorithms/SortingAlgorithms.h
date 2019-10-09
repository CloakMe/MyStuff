#define SortingAlgorithmsParameter

template <class T>
class SortingAlgorithms
{
private:
	static void Merge(T* arr, int end1, int end2);
	SortingAlgorithms(){}
public:
	static void BubbleSort(T* arr, int size);
	static void InsertionSort(T* arr, int size);
	static void MergeSort(T* arr, int size);
	static void QuickSort(T* arr, int size);
};

template <class T>
void SortingAlgorithms<T>::BubbleSort(T* arr, int size)
{
	int n = size;
	int i;
	T temp;
	while(n-1>0)
	{
		i=0;
		while(i<=n-2)
		{
			if(arr[i]>arr[i+1])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
			i++;
		}
		n--;
	}
}

template <class T>
void SortingAlgorithms<T>::InsertionSort(T* arr, int size)
{
	if(size < 2)
		return;
	int i;
	T temp;
	for(int j=1; j<size; j++) 
	{
		i=j;
		while(i>0)
		{
			if(arr[i-1]>arr[i])
			{
				temp = arr[i-1];
				arr[i-1] = arr[i];
				arr[i] = temp;
				i--;
			}else{
				break;
			}
		}
	}
}

template <class T>
void SortingAlgorithms<T>::MergeSort(T* arr, int size)
{
	for(int i=1;i<size; i=2*i)
	{
		for(int j=0; j<size-i; j=j+2*i)
		{
			int defaultSize = 2*i;
			int endSize = size - j;
			int size = defaultSize > endSize ? endSize:defaultSize;
			Merge(&arr[j], i, size);
		}
	}
}

template <class T>
void SortingAlgorithms<T>::Merge(T* arr, int end1, int end2)
{
	if(end1==0 || end2<=1)
		return;
	int k=end1;
	int l=0, counter = 0;
	T* temp = new T[end2];
	while(k<end2 && l<end1)
	{
		if(arr[l]>arr[k])
		{
			temp[counter] = arr[k];
			k++;
		}else{
			temp[counter] = arr[l];
			l++;
		}
		counter++;
	}
	while(k<end2)
	{
		temp[counter] = arr[k];
		k++;
		counter++;
	}
	while(l<end1)
	{
		temp[counter] = arr[l];
		l++;
		counter++;
	}
	for(int m=0;m<end2;m++)
	{
		arr[m] = temp[m];
	}
	delete [] temp;
}


template <class T>
void SortingAlgorithms<T>::QuickSort(T* arr, int size)
{
	if(size < 2)
	{
		return;
	}
	int pivotIndex = size/2;
	T temp;
	T pivot = arr[pivotIndex];
	int leftIndex=0, rightIndex = size-1;
	while(leftIndex != rightIndex)
	{
		while(true)
		{
			if(arr[leftIndex]>=pivot)
			{
				break;
			}
			leftIndex++;
		}
		while(true)
		{
			if(arr[rightIndex]<=pivot)
			{
				break;
			}
			rightIndex--;
		}
		temp = arr[leftIndex];
		arr[leftIndex] = arr[rightIndex];
		arr[rightIndex] = temp;
	}
	if(leftIndex == 0)
	{
		QuickSort(&arr[1], size-1);
		return;
	}
	if(leftIndex == size-1)
	{
		QuickSort(&arr[0], size-1);
		return;
	}
	QuickSort(&arr[0], leftIndex);
	QuickSort(&arr[leftIndex+1], size-1-leftIndex);
}