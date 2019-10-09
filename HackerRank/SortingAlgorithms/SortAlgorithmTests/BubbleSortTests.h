using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

#ifndef SortingAlgorithmsParameter
#include "..\\SortingAlgorithms\\SortingAlgorithms.h"
#endif

#include <math.h>
namespace SortAlgorithmTests
{
	[TestClass]
	public ref class BubbleSortTests
	{
	public: 
		[TestMethod]
		void BubSmallSizedArrayTest()
		{
			int* arr = new int[5];
			arr[0] = 4;
			arr[1] = 1;
			arr[2] = 12;
			arr[3] = 7;
			arr[4] = 11;
			SortingAlgorithms<int>::BubbleSort(arr, 5);
			int result[5] = {1, 4, 7, 11, 12};
			bool flag = true;
			for(int i=0; i<5; i++)
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
		void BubBigSizedArrayTest()
		{
			int n = 100;
			double* arr = new double[n];
			for(int i=0; i<n; i++)
			{
				arr[i] = sin((double) i);
			}
			
			SortingAlgorithms<double>::BubbleSort(arr, n);
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
		void BubVeryBigSizedArrayTest()
		{
			int n = 10000;
			double* arr = new double[n];
			for(int i=0; i<n; i++)
			{
				arr[i] = sin((double) i);
			}
			
			SortingAlgorithms<double>::BubbleSort(arr, n);
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