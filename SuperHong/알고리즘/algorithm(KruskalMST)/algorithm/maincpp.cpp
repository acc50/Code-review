#include <iostream>
#define V 6
//KruskalMST(G) 알고리즘
struct Node
{
	int p1, p2;
	int value;
};
struct Tree
{
	int root;
	Tree* next = nullptr;
	bool exit = true;  //각원소가 종속되었는지 안되었는지 확인하는 변수
};
void K(int graph[][V]);
bool find(Tree*, int);
int main()
{
	int graph[][V] = {
	{0,8,2,0,4,0},
	{8,0,4,1,0,2},
	{2,4,0,0,3,7},
	{0,1,0,0,0,1},
	{4,0,3,0,0,9},
	{0,2,7,1,9,0}
	};
	K(graph);

}
void mySwap(Node& a, Node& b)
{
	Node temp = a;
	a = b;
	b = temp;
}

void myQsort(Node* value, int left, int right)
{
	int i = left;
	int j = left;
	int p = right;
	if (left < right)
	{
		while (j < p)
		{
			if (value[j].value < value[p].value) {
				mySwap(value[i++], value[j++]);

			}
			else
				j++;
		}
		mySwap(value[i], value[p]);
		p = i;
		myQsort(value, left, p - 1);
		myQsort(value, p + 1, right);
	}

}

void K(int graph[][V])
{
	Node list[10];
	int min = 0; //가장작은 가중치를 가리키는 인덱스;
	for (int k = 0; k < V + 4;) {
		for (int i = 0; i < V; i++) {
			for (int j = i; j < V; j++) {
				if (graph[i][j] != 0) {
					list[k].p1 = i; list[k].p2 = j; list[k].value = graph[i][j];
					k++;
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		std::cout << "점" << list[i].p1 << ',' << list[i].p2 << " 가중치:" << list[i].value << std::endl;
	}
	myQsort(list, 0, 9);
	std::cout << "정렬후\n";
	for (int i = 0; i < 10; i++) {
		std::cout << "점" << list[i].p1 << ',' << list[i].p2 << " 가중치:" << list[i].value << std::endl;
	}
	Tree tree[6];  //집합 만들기
	for (int i = 0; i < V; i++) {
		tree[i].root = i;   //집합 {0,1,2,3,4,5,6 넣기
	}
	int count = 0; //선그은 횟수
	while (count < V-1)
	{
	
		int p1 = list[min].p1;
		int p2 = list[min].p2;
		int value = list[min].value;
		
		if (tree[p1].exit == true) {// 각원소가 루트인지 아닌지 알려주는거임 만약 tree[0]==true 그원소는 루트원소 false면 어딘가에 종속되어있는 원소
			if (find(tree[p1].next, p2)) {
				tree[p1].next = &tree[p2];
				tree[p2].exit = false;
				std::cout << "간선:" << value << "점" << list[min].p1 << ',' << list[min].p2 << '\n';
				count++;
			}
		}
		min++;
	}


}

bool find(Tree* next, int p)
{
	if (next == nullptr)
		return true;
	else if (next->root == p)
		return false;
	else {
		find(next->next, p);
	}
}