using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

#ifndef SortingAlgorithmsParameter
#include "..\\SortingAlgorithms\\SortingAlgorithms.h"
#endif

#include <math.h>

namespace SortAlgorithmTests
{
	[TestClass]
	public ref class QuickSortTests
	{
	public: 
		[TestMethod]
		void QuiSmallSizedArrayTest()
		{
			int* arr = new int[6];
			arr[0] = 1;
			arr[1] = 4;
			arr[2] = 7;
			arr[3] = 11;
			arr[4] = 12;
			arr[5] = 16;
			SortingAlgorithms<int>::QuickSort(arr, 6);
			int result[6] = {1, 4, 7, 11, 12, 16};
			bool flag = true;
			for(int i=0; i<6; i++)
			{
				if(result[i] != arr[i])
				{
					flag = false;
					break;
				}
			}

			Assert::IsTrue(flag == true);
		};

		[TestMethod]
		void QuiBigSizedArrayTest()
		{
			int n = 100;
			double* arr = new double[n];
			for(int i=0; i<n; i++)
			{
				arr[i] = sin((double) i);
			}
			
			SortingAlgorithms<double>::QuickSort(arr, n);
			bool flag = true;
			for(int i=0; i<n-1; i++)
			{
				if(arr[i] > arr[i+1])
				{
					flag = false;
					break;
				}
			}

			Assert::IsTrue(flag == true);
		};

		[TestMethod]
		void QuiVeryBigSizedArrayTest()
		{
			int n = 10000;
			double* arr = new double[n];
			for(int i=0; i<n; i++)
			{
				arr[i] = sin((double) i);
			}
			
			SortingAlgorithms<double>::QuickSort(arr, n);
			bool flag = true;
			for(int i=0; i<n-1; i++)
			{
				if(arr[i] > arr[i+1])
				{
					flag = false;
					break;
				}
			}

			Assert::IsTrue(flag == true);
		};
	};
}