#include <iostream>
#include <intrin.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int b[10];

	__cpuid(b, 0x80000008);
	char buffer[100];
	printf("__cpuid(b, 0x80000008)�� ���� %x �Դϴ�.\n", b[0]);
	char* a = itoa(b[0], buffer, 16); //16������ ���ڿ��� ��ȯ
	int Physical = (a[3] - 48) + ((a[2] - 48) * 16);
	std::cout<<"Physical: " << Physical << std::endl;
	int Virtual = (a[1] - 48) + (a[0] - 48) * 16;
	std::cout <<"Virtual: "<< Virtual << std::endl;

}