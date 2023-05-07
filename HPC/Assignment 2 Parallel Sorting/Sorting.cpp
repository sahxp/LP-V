#include <bits/stdc++.h>
#include <chrono>
#include <cstdlib>
#include "omp.h"
using namespace std;

void printArray(int arr[],int n){
	
	for (int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void bubbleSort(int arr[], int n)
{	
	int i,j;
	for (int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if (arr[j]>arr[j+1])
				swap(arr[j],arr[j+1]);
		}
	}
	
}

void swap_para(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}
void bubbleSort_para(int arr[],int n)
{
	int i=0, j=0; 
	int first;
	for( i = 0; i < n-1; i++ )
	{
		first = i % 2; 
		#pragma omp parallel for default(none),shared(arr,first,n)
		for( j = first; j < n-1; j += 1 )
		{
			if( arr[ j ] > arr[ j+1 ] )
			{
				swap_para( &arr[ j ], &arr[ j+1 ] );
			}
		}
	}
}
void merge(int arr[], int p, int q, int r) {
  
  // Create L ? A[p..q] and M ? A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r){
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
}
}

void mergeSort_para(int arr[], int l, int r){
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    
    #pragma omp parallel sections num_threads(2)
    {
    #pragma omp section
    {
    mergeSort_para(arr, l, m);
    }
    #pragma omp section
    {
    mergeSort_para(arr, m + 1, r);
    }
    }
    // Merge the sorted subarrays
    merge(arr, l, m, r);
}
}


int main()
{
	int n;
	cout<<"Enter n: ";
	cin>>n;
	
	int arr[n],arr1[n],arr2[n],arr3[n],arr4[n];
	for (int i=0;i<n;i++){	
		arr[i] = rand()%100;
		//cin>>arr[i];
	}
	
	for (int i=0;i<n;i++){
		arr1[i] = arr[i];
		arr2[i] = arr[i];
		arr3[i] = arr[i];
		arr4[i] = arr[i];
	}
	cout<<"Before Sorting:\n";
	printArray(arr,n);
	
	cout<<"Bubble Sort Sequential:\n";
	auto start = chrono::steady_clock::now();
	bubbleSort(arr1,n);
	auto end = chrono::steady_clock::now();
	chrono::duration<double, milli> fp_ms = end - start;
	cout<<fp_ms.count()<<" ms\n";
	//printArray(arr1,n);
	
	cout<<"Merge Sort Sequential:\n";
	auto start1 = chrono::steady_clock::now();
	mergeSort(arr2,0,n-1);
	auto end1 = chrono::steady_clock::now();
	chrono::duration<double, milli> fp_ms1 = end1 - start1;
	cout<<fp_ms1.count()<<" ms\n";
	//printArray(arr2,n);
	
	cout<<"Bubble Sort Parallel:\n";
	auto start2 = chrono::steady_clock::now();
	bubbleSort_para(arr1,n);
	auto end2 = chrono::steady_clock::now();
	chrono::duration<double, milli> fp_ms2 = end2- start2;
	cout<<fp_ms2.count()<<" ms\n";
	//printArray(arr1,n);
	
	cout<<"Merge Sort Parallel:\n";
	auto start3 = chrono::steady_clock::now();
	mergeSort_para(arr3,0,n-1);
	auto end3 = chrono::steady_clock::now();
	chrono::duration<double, milli> fp_ms3 = end3 - start3;
	cout<<fp_ms3.count()<<" ms\n";
	//printArray(arr3,n);
	
	return 0;
}
