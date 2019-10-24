#include <iostream>
#include <random>
#include "mySort.h"
int main()
{
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	int A[SIZE];
	int copy[SIZE];
	for (int i = 0; i < SIZE; i++) {
		A[i] = uid(dre);
		copy[i] = A[i];
	}
	for (int d : A) std::cout << d << std::endl;
	MergeSort(A, 0, 9);
	std::cout << "----------------" << std::endl;
	//for (int i = 0; i < SIZE; i++) A[i] = copy[i];
	for (int d : A) std::cout << d << std::endl;

}