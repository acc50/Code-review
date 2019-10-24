#include <iostream>
#include "mySort.h"
void MergeSort(int* array, int left, int right)
{
	int* copy = new int[right + 1];
	for (int m = 0; m < right + 1; m++) copy[m]=array[m];
	int mid = (left + right) / 2;
	int k = mid + 1;
	int i = left;
	int j = left;
	if (left < right)
	{
		MergeSort(array, left, mid);
		MergeSort(array, k, right);

		while (i <= mid && k <= right) {
			if (array[i] > array[k]) {
				copy[j++] = array[k++];
			}
			else
				copy[j++] = array[i++];
		}
		while (i <= mid)
			copy[j++] = array[i++];
		while (j <= right)
			copy[j++] = array[k++];
		
	}
	for (int m = 0; m < right+1; m++) array[m] = copy[m];

	delete[] copy;

}

