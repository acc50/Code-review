#include <iostream>
#define V 6
//KruskalMST(G) �˰���
struct Node
{
	int p1, p2;
	int value;
};
struct Tree
{
	int root;
	Tree* next = nullptr;
	bool exit = true;  //�����Ұ� ���ӵǾ����� �ȵǾ����� Ȯ���ϴ� ����
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
	int min = 0; //�������� ����ġ�� ����Ű�� �ε���;
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
		std::cout << "��" << list[i].p1 << ',' << list[i].p2 << " ����ġ:" << list[i].value << std::endl;
	}
	myQsort(list, 0, 9);
	std::cout << "������\n";
	for (int i = 0; i < 10; i++) {
		std::cout << "��" << list[i].p1 << ',' << list[i].p2 << " ����ġ:" << list[i].value << std::endl;
	}
	Tree tree[6];  //���� �����
	for (int i = 0; i < V; i++) {
		tree[i].root = i;   //���� {0,1,2,3,4,5,6 �ֱ�
	}
	int count = 0; //������ Ƚ��
	while (count < V-1)
	{
	
		int p1 = list[min].p1;
		int p2 = list[min].p2;
		int value = list[min].value;
		
		if (tree[p1].exit == true) {// �����Ұ� ��Ʈ���� �ƴ��� �˷��ִ°��� ���� tree[0]==true �׿��Ҵ� ��Ʈ���� false�� ��򰡿� ���ӵǾ��ִ� ����
			if (find(tree[p1].next, p2)) {
				tree[p1].next = &tree[p2];
				tree[p2].exit = false;
				std::cout << "����:" << value << "��" << list[min].p1 << ',' << list[min].p2 << '\n';
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