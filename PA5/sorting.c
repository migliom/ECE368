#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sorting.h"
#include <string.h>
#define STOP 10
void Merge(long *arr, int lb, int mid, int ub, long *aux)
{
	//Abstract in place merge from book
	int i, j, k;
	for(i = (mid+1); i > lb; i--)
		aux[i-1] = arr[i-1];
	for(j = mid; j < ub; j++)
		aux[(ub+mid-j)] = arr[j+1];
	for(k = lb; k <= ub; k++)
	{
		if(aux[i] < aux[j])
			arr[k] = aux[(i++)];
		else
			arr[k] = aux[(j--)];
	}
	/*
	int m;
	for(m = lb; m <= ub; m++) {aux[m] = arr[m];};
	int i = lb, j = mid+1;

	for(m = lb; m <= ub; m++)
	{
		if(i > mid) {arr[m] = aux[j++];}
		else if(j > ub) {arr[m] = aux[i++];}
		else if(aux[j] < aux[i]) {arr[m] = aux[j++];}
		else {arr[m] = aux[i++];}
	}*/
}
void Merge_Helper(long *Array, int lb, int ub, long *arr)
{
	if(lb >= ub)
		return;
	int mid = (lb + ub) / 2;
	Merge_Helper(Array, lb, mid, arr);
	Merge_Helper(Array, (mid+1), ub, arr);
	Merge(Array, lb, mid, ub, arr);
}
void Merge_Sort(long *Array, int size)
{
	if(size < 2)
		return;
	long *tempArr = malloc((size) * sizeof(long));
	//memset(tempArr, 0, (size*sizeof(tempArr)));
	Merge_Helper(Array, 0, (size - 1), tempArr);
	free(tempArr);
}
/*-----------------------------------------------------*/
/*-----------------------------------------------------*/
static void insertionSort(long *arr, int lb, int ub)
{
	int i;
	for(i = lb; i <= ub; i++)
	{
		long key = arr[i];
		int j = i;
		while(j > lb && arr[j-1] > key)
		{
			arr[j] = arr[j-1];
			j--;
		}

		arr[j] = key;
	}
}

static void exchange(long *a, int lb, int ub)
{
	long temp = a[lb];
	a[lb] = a[ub];
	a[ub] = temp;
}

static void medianOfThree(long *arr, int lb, int ub)
{
	int mid = (lb + ub) / 2;
	if(arr[mid] < arr[lb])
		exchange(arr, mid, lb);
	if(arr[ub] < arr[mid])
	{
		exchange(arr, mid, ub);
		if(arr[mid] < arr[lb])
			exchange(arr, mid, lb);
	}
}

static int partition(long *arr, int lb, int ub)
{
	medianOfThree(arr, lb, ub);
	long pivot = arr[(lb + ub) / 2];
	
	int down = lb + 1;
	int up = ub - 1;

	while(down < up)
	{
		while(arr[down] <= pivot && down < (ub-1))
		{
			down++;
		}
		while(arr[up] > pivot)
			up--;
		if(down < up)
			exchange(arr, down, up);
	}
	//arr[lb] = r[up]
	//arr[up] = pivot
	
	return (up);
}

static void Quick_Helper(long *arr, int lb, int ub)
{	
	while(ub - lb > 10)
	{
		int pivot_idx = partition(arr, lb, ub);

		if(pivot_idx < ((lb+ub) / 2)){
			Quick_Helper(arr, lb, pivot_idx);
			lb = pivot_idx+1;
		}
		else{
			Quick_Helper(arr, pivot_idx + 1, ub);
			ub = pivot_idx-1;
		}
	}	

	/*if(lb >= ub)
		return;
	fprintf(stderr, "Lower Bound: %d, Upper Bound: %d\n", lb, ub);
	int pivot_idx = partition(arr, lb, ub);
	Quick_Helper(arr, lb, pivot_idx);
	Quick_Helper(arr, pivot_idx + 1, ub);*/
}
void Quick_Sort(long *Array, int size)
{
	if(size < 2)
		return;
	
	Quick_Helper(Array, 0, (size -1));
	insertionSort(Array, 0, (size - 1));
}
