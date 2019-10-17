// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일입니다. 성공하려면 컴파일이 필요합니다.
#include <iostream>
#include <cmath>
#include "pch.h"
double min = -1;
myPoint minPoint[2];
//void Merge(myPoint* num, int*copy, int left, int right)
//{
//	int k = ((left + right) / 2) + 1;
//	int i = left;
//	int j = left;
//	int mid = k - 1;
//	while (i <= mid && k <= right) {
//		if (num[i].x > num[k].x)
//			copy[j++] = num[k++].x;
//		else
//			copy[j++] = num[i++].x;
//	}
//	while (i <= mid)
//		copy[j++] = num[i++].x;
//	while (k <= right)
//		copy[j++] = num[k++].x;
//	for (int i = 0; i < SIZE; i++) {
//		num[i].x = copy[i];
//	}
//
//}
//void SortByX(myPoint* num, int* copy, int left, int right)//병합정렬 느낌으로 한다
//{
//	int mid = (left + right) / 2;
//	int i = left;
//	int j = mid;
//	if (left < right)
//	{
//		SortByX(num, copy, left, mid);
//		SortByX(num, copy, mid + 1, right);
//		Merge(num, copy, left, right);
//
//	}
//}

void myQSort(myPoint* num, int left, int right)
{

	int p = right;
	int i = left, j = left;
	if (left < right)
	{
		while (j < p) {
			if (num[j].x <= num[p].x) {
				mySwap(num[j], num[i]);
				i++; j++;
			}
			else
				j++;
		}
		mySwap(num[i], num[p]);
		p = i;
		myQSort(num, left, p - 1);
		myQSort(num, p + 1, right);
	}

}
void mySwap(myPoint& a, myPoint& b)
{
	myPoint temp = a;
	a = b;
	b = temp;
}
void GetMinDis(myPoint* num, int left, int right)
{

	//int mid = (left + right) / 2;
	//if (right >left) {
	//	GetMinDis(num, left, mid);//분할을 해준다.
	//	GetMinDis(num, mid+1, right);
	//}
	//if (right == 14 && left == 13)
	//	std::cout << "왜없냐?";
	//if ((right - left)==0) {
	//	for (int i = left; i <= right; i++) {//중간확인용
	//		std::cout << "(" << num[i].x << ", " << num[i].y << ")" << ' ';
	//	}
	//	std::cout << "\n";
	//	std::cout << left << ' ' << right;
	//	std::cout << "\n-----------\n";
	//	int i = 0; 
	//	int j = 0;
	//	while (j < SIZE) {

	//	}
	//	return;
	//}
	
	/*if (right - left == 1) {
		double newMin = GetDis(num[left], num[right]);

		if (min == -1 || min > newMin) {
			min = newMin;
			minPoint[0] = num[left]; minPoint[1] = num[right];
		}
		GetmidDis(num, num[right]);
		return;
	}*/
	//수정
	int i = left;
	int j = left + 1;
	while (j <= right) {
		double newMin = GetDis(num[i], num[j]);
		if (min == -1 || min > newMin) {
			min = newMin;
			minPoint[0] = num[i]; minPoint[1] = num[j];
		}
		i+=2;
		j+=2;
	}
	j = 1;
	while (j <= right - 2)
	{
		GetmidDis(num, num[j]);
		j += 2;
	}
}
double GetDis(myPoint a, myPoint b)
{
	double dis = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
	static int count = 0;
	std::cout << "비교:" << "(" << a.x << ',' << a.y << "), " << "(" << b.x << ',' << b.y << ")";
	std::cout << " 계산된 거리값:";


	count++;
	std::cout << " 비교횟수:" << count << std::endl;
	return dis;
}
void GetmidDis(myPoint* num, myPoint p)
{

	for (int i = 0; i < SIZE; i++) {
		if (p.x == num[i].x)
			i++;
		if (p.x - min <num[i].x&&p.x + min>num[i].x) {//범위 안에 새로운 최솟값이 있다?
			double newMin = GetDis(p, num[i]);
			std::cout << "중간영역검사 ";
			if (min == -1 || min > newMin) {
				min = newMin;
				minPoint[0] = p; minPoint[1] = num[i];
			}
		}
	}
}
