#include "tree.h"


std::default_random_engine dre;
std::uniform_int_distribution<int> uid(0, 100);
Node* ROOT = nullptr;
Node* NIL = nullptr;
int main()
{
	int arr[SIZE];
	for (int& d : arr) d = uid(dre);
	for (int d : arr)std::cout << d << ' ';
	std::cout << std::endl;
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = NIL->right = nullptr;
	NIL->data = 9999;

	Node* node = nullptr;
	Insert(ROOT, arr[0]);
	ROOT->color = BLACK;
	/*std::cout << "----------------\n";
	PrintAll(ROOT);
	std::cout << "----------------\n";
	Insert(ROOT, 20);
	PrintAll(ROOT);
	std::cout << "----------------\n";
	Insert(ROOT, 10);
	PrintAll(ROOT);
	std::cout << "----------------\n";*/
	
	for (int i = 1; i < SIZE; i++) {
		std::cout << "----------------\n";
		Insert(ROOT, arr[i]);
		PrintAll(ROOT);
	}
	


}