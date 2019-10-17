#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "tree.h"

int main()
{
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::vector<int> v;
	Node* root;
	std::cout << "원하는 숫자를 입력하세용!";
	int Num = 0;
	std::cin >> Num;

	for (int i = 0; i < Num; i++) {
		v.push_back(uid(dre));
	}
	for (int i = 0; i < v.size(); i++)std::cout << v[i] << std::endl;
	for (int i = 0; i < v.size(); i++) {
		Insert(root,v[i]);
		insert_case1(root);
		PrintNode(root);
	}
	std::cout << "왜 안되니?";

}