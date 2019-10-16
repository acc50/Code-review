#include <iostream>
#include <random>
#include <cassert>
//#include "treePrint.h"

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution <int> uid(100, 1000);

enum Color {
	Color_Red,
	Color_Black
};

struct Node {
	int data;
	int color;
	Node *left;
	Node *right;
	Node *parent;
};

void check_tree_recursion(struct Node *p, struct Node *NIL, int B_sofar, int B_total) {

	if (p == NIL) {

		assert(B_sofar == B_total);

		return;

	}



	check_tree_recursion(p->left, NIL, B_sofar + (p->left && p->left->color), B_total);

	check_tree_recursion(p->right, NIL, B_sofar + (p->right && p->right->color), B_total);

	if (p->left)

		assert(!(!p->left->color && !p->color));

	if (p->right)

		assert(!(!p->right->color && !p->color));

}



void check_tree(struct Node *root, struct Node *NIL) {

	int cnt = 0;

	struct Node *p;

	if (root == NIL) return;

	//root->color = BLACK;

	for (p = root; p != NIL; p = p->left)

		cnt += p->color;

	check_tree_recursion(root, NIL, 0, cnt);

}

void Check_PrintAll(struct Node *node, struct Node *NIL)
{
	if (node == NIL)
		cout << "NIL " << endl << endl;

	else if (node != NIL) {

		cout << "왼쪽 진입" << endl;
		Check_PrintAll(node->left, NIL);

		cout << node->data << " ";

		if (node->color == Color_Red)
			cout << "RED" << endl << endl;
		else
			cout << "Black" << endl << endl;

		cout << "오른쪽 진입" << endl;
		Check_PrintAll(node->right, NIL);
	}

}

void PrintAll(struct Node *node, struct Node *NIL)
{

	if (node != NIL) {

		PrintAll(node->left, NIL);
		cout << node->data << " ";
		PrintAll(node->right, NIL);
	}

}

void Tree_Rotation(struct Node *node, struct Node *Parent, struct Node *&root, int type)		// pivot, pivot의 부모, root의 원본, 회전방향
{
	if (type == 1) {				// 오른쪽
		Parent->left = node->right;
		node->right = Parent;
		node->parent = Parent->parent;

		if (Parent->parent != nullptr) {				// 회전시 루트노드가 변하지 않음
			if (Parent == Parent->parent->left) {	//부모노드가 그 부모노드의 왼쪽
				Parent->parent->left = node;
			}
			else {
				Parent->parent->right = node;
			}
		}
		else {					// node 가 루트노드가 됨
			root = node;
		}

		Parent->parent = node;
		Parent->left->parent = Parent;
	}

	else {							// 왼쪽 회전

		Parent->right = node->left;
		node->left = Parent;
		node->parent = Parent->parent;

		if (Parent->parent != nullptr) {
			if (Parent == Parent->parent->left) {		// 부모노드가 그 부모노드의 왼쪽이면
				Parent->parent->left = node;
			}
			else {
				Parent->parent->right = node;
			}
		}
		else {					// node 가 루트노드가 됨
			root = node;
		}

		Parent->parent = node;
		Parent->right->parent = Parent;
	}
}

void RB_Insert(struct Node *node, struct Node *Parent, struct Node *&root)
{
	if (Parent == nullptr) {					// 루트노드
		node->color = Color_Black;
	}

	else if (Parent->parent == nullptr) {		// 루트노드  자식노드 삽입
		node->color = Color_Red;
	}

	else {						// 루트노드의 자식노드가 아님

		if (Parent->color == Color_Black) {		// 부모노드가 블랙
			node->color = Color_Red;
		}

		else {		// 루트노드의 자식노드가 아니고 부모노드가 레드

			if (Parent == Parent->parent->left) {			// 부모노드가 그 부모노드의 왼쪽
				if (Parent->parent->right->color == Color_Red) {	// Case 1
					Parent->color = Color_Black;					// p = 검은색
					Parent->parent->right->color = Color_Black;		// s  = 검은색
					Parent->parent->color = Color_Red;

					// 재귀
					RB_Insert(Parent->parent, Parent->parent->parent, root);	// p' 에 대한 검사
				}

				else if (Parent->parent->right->color == Color_Black) {	// Case 2
					if (node == Parent->right) {
						// x 기준 왼쪽회전
						Tree_Rotation(node, Parent, root, 2);
						// x 기준 오른쪽회전
						Tree_Rotation(node, node->parent, root, 1);
						node->color = Color_Black;
						node->right->color = Color_Red;
					}

					else if (node == Parent->left) {
						// p 기준 오른쪽회전
						// p = 블랙, p' 레드로 바꿈
						Tree_Rotation(Parent, Parent->parent, root, 1);
						Parent->color = Color_Black;
						Parent->right->color = Color_Red;
					}
				}

			}

			else if (Parent == Parent->parent->right) {		// 부모노드가 그 부모노드의 오른쪽
				if (Parent->parent->left->color == Color_Red) {	// Case 1
					Parent->color = Color_Black;
					Parent->parent->left->color = Color_Black;
					Parent->parent->color = Color_Red;
					// 재귀
					RB_Insert(Parent->parent, Parent->parent->parent, root);	// p' 에 대한 검사
				}

				else if (Parent->parent->left->color == Color_Black) {	// Case 2

					if (node == Parent->right) {			//  삽입하는 노드가 부모노드의 오른쪽
															// p 기준 왼쪽회전
															// p = 블랙, p' 레드로 바꿈
						Tree_Rotation(Parent, Parent->parent, root, 2);
						Parent->color = Color_Black;
						Parent->left->color = Color_Red;
					}

					else if (node == Parent->left) {		//  삽입하는 노드가 부모노드의 왼쪽
															// x 기준 오른쪽회전
						Tree_Rotation(node, Parent, root, 1);
						// x 기준 왼쪽 회전
						Tree_Rotation(node, node->parent, root, 2);
						node->color = Color_Black;
						node->left->color = Color_Red;
					}
				}

			}

		}		// 부모노드가 그 부모노드의 오른쪽일 경우

	}
}

void Insert(struct Node *node, struct Node *new_node, struct Node *NIL, struct Node *&root)	// root, node, NIL의 복사본  root의 원본 들어옴
{
	if (root == nullptr)		// 루트가 비어있으면
		root = new_node;

	else {
		if (new_node->data <= node->data) {		// 새로운 노드의 데이터가 비교하는 노드보다 작음
			if (node->left == NIL) {		// 노드의 왼쪽이 비어있으면
				node->left = new_node;
				new_node->parent = node;
				RB_Insert(new_node, new_node->parent, root);
			}
			else {
				Insert(node->left, new_node, NIL, root);
			}
		}

		else if (new_node->data > node->data) {		// 새로운 노드의 데이터가 비교하는 노드보다 큼
			if (node->right == NIL) {
				node->right = new_node;
				new_node->parent = node;
				RB_Insert(new_node, new_node->parent, root);
			}
			else {
				Insert(node->right, new_node, NIL, root);
			}
		}
	}
}

void RB_Delete_Red(struct Node *node, struct Node *NIL, bool &red_check)	// 삭제노드 혹은 자식노드가 레드, 레드 삭제 시 블랙삭제 넘어감
{
	if (node->color == Color_Black) {
		if (node->left != NIL) {	// 자식노드는 왼쪽
			if (node->left->color == Color_Red) {
				node->left->color = Color_Black;
				cout << "레드 삭제" << endl;
				red_check = true;
			}
		}
		else {
			if (node->right->color == Color_Red) {
				node->right->color = Color_Black;
				cout << "레드 삭제" << endl;
				red_check = true;
			}
		}
	}
}

void RB_Delete_Black(struct Node *node, struct Node *Parent, struct Node *&root)	// 삭제된 후 삭제된 노드의 자식노드, 그 부모노드  2-1, 2-4, 1-1, *-3, *-2 순서로 처리
{
	if (node == Parent->left) {		// x 가 p의 왼쪽

		struct Node *x = node;
		struct Node *s = Parent->right;
		struct Node *l = Parent->right->left;
		struct Node *r = Parent->right->right;
		int Color_temp = Color_Black;

		if (Parent->color == Color_Black && s->color == Color_Black &&
			l->color == Color_Black && r->color == Color_Black)  // 2-1
		{
			s->color = Color_Red;
			cout << "case 2-1" << endl;
			RB_Delete_Black(Parent, Parent->parent, root);	// Parent 가 재귀함수의 x가 됨
		}

		else if (Parent->color == Color_Black && s->color == Color_Red &&
			l->color == Color_Black && r->color == Color_Black) // 2-4
		{
			Tree_Rotation(s, Parent, root, 2);		// s, p 왼쪽 회전
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;				// p, s 색상 바꾸기
			cout << "case 2-4" << endl;
			RB_Delete_Black(x, Parent, root);		// 케이스 1로 가기위한 재귀
		}

		else if (Parent->color == Color_Red && l->color == Color_Black &&
			r->color == Color_Black)	// 1-1		p = red, s,l,r = black
		{
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s 색상 바꾸기
			cout << "case 1-1" << endl;
		}

		else if (s->color == Color_Black && r->color == Color_Red) // *-2		s = black r = red
		{
			Tree_Rotation(s, Parent, root, 2);		// s, p 왼쪽회전
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s 색상 바꾸기
			r->color = Color_Black;
			cout << "case *-2" << endl;
		}

		else if (s->color == Color_Black && r->color == Color_Black &&
			l->color == Color_Red) // *-3
		{
			Tree_Rotation(l, s, root, 1);		// l, s 오른쪽 회전
			Color_temp = l->color;
			l->color = s->color;
			s->color = Color_temp;		// l, s 색상 바꾸기
			cout << "case *-3" << endl;
			RB_Delete_Black(x, Parent, root);		// *-2 로 넘어가도록 함
		}
	}

	else {					// x 는 Parent 의 오른쪽
		struct Node *x = node;
		struct Node *s = Parent->left;
		struct Node *l = Parent->left->left;
		struct Node *r = Parent->left->right;
		int Color_temp = Color_Black;

		if (Parent->color == Color_Black && s->color == Color_Black &&
			l->color == Color_Black && r->color == Color_Black)  // 2-1
		{
			s->color = Color_Red;
			cout << "case 2-1" << endl;
			RB_Delete_Black(Parent, Parent->parent, root);	// Parent 가 재귀함수의 x가 됨
		}

		else if (Parent->color == Color_Black && s->color == Color_Red &&
			l->color == Color_Black && r->color == Color_Black) // 2-4
		{
			Tree_Rotation(s, Parent, root, 1);		// s, p 오른쪽 회전
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;				// p, s 색상 바꾸기
			cout << "case 2-4" << endl;
			RB_Delete_Black(x, Parent, root);		// 케이스 1로 가기위한 재귀
		}

		else if (Parent->color == Color_Red && l->color == Color_Black &&
			r->color == Color_Black)	// 1-1		p = red, s,l,r = black
		{
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s 색상 바꾸기
			cout << "case 1-1" << endl;
		}

		else if (s->color == Color_Black && l->color == Color_Red) // *-2		s = black l = red
		{
			Tree_Rotation(s, Parent, root, 1);		// s, p 오른쪽회전
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s 색상 바꾸기
			l->color = Color_Black;
			cout << "case *-2" << endl;
		}

		else if (s->color == Color_Black && l->color == Color_Black &&			// s = black , l=black, r=red
			r->color == Color_Red) // *-3
		{
			Tree_Rotation(r, s, root, 2);		// r, s 왼쪽 회전
			Color_temp = r->color;
			r->color = s->color;
			s->color = Color_temp;		// l, s 색상 바꾸기
			cout << "case *-3" << endl;
			RB_Delete_Black(x, Parent, root);		// *-2 로 넘어가도록 함
		}
	}
}

void DeleteNode(struct Node *node, struct Node *NIL, struct Node *&root)
{
	bool red_check = false;

	if (node->left == NIL && node->right == NIL) {		// 자식노드 X
		if (node->parent->left == node) {		// 지우려는 노드가 부모노드의 왼쪽
			RB_Delete_Red(node, NIL, red_check);
			node->parent->left = NIL;
			if(node->color == Color_Black && !red_check)
				RB_Delete_Black(node->parent->left, node->parent, root);	// NIL 이 x, Parent 가 p가 됨
			delete node;
		}

		else {
			RB_Delete_Red(node, NIL, red_check);
			node->parent->right = NIL;
			if (node->color == Color_Black && !red_check)
				RB_Delete_Black(node->parent->right, node->parent, root);	// NIL 이 x, Parent 가 p가 됨
			delete node;
		}
	}

	else if (node->left != NIL && node->right != NIL) {		// 자식노드 2개

		struct Node *temp = node->right;		// 예비 노드

		while (temp->left != NIL) {			// temp 는 노드의 왼쪽 끝으로 찾아감
			temp = temp->left;
		}

		node->data = temp->data;

		if (temp->parent->left == temp) {	// 삭제할 노드가 그 부모노드의 왼쪽
			if (temp->right == NIL) {				// temp -> right가 NIL 이면		자식 x
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->left = NIL;
				if (temp->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->left, temp->parent, root);	// NIL이 x, temp->parent 가 p
			}

			else if (temp->right != NIL) {			// temp->right 가 있다면
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->left = temp->right;
				temp->right->parent = temp->parent;
				if (temp->color == Color_Black && temp->right->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->left, temp->parent, root);	// temp의 right 가 x, temp->parent 가 p
			}
		}

		else if (temp->parent->right == temp) {	// 삭제할 노드가 그 부모노드의 오른쪽
			if (temp->right == NIL) {				// temp -> right가 NIL 이면		자식 x
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->right = NIL;
				if (temp->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->right, temp->parent, root);	// NIL 이 x, temp->parent 가 p
			}

			else if (temp->right != NIL) {			// temp->right 가 있다면
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->right = temp->right;
				temp->right->parent = temp->parent;
				if (temp->color == Color_Black && temp->right->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->right, temp->parent, root);	// temp의 right 가 x, temp->parent 가 p
			}
		}

		delete temp;

	}

	else if (node->left != NIL || node->right != NIL) {
		if (node->parent->left == node) {		// 지우려는 노드가 부모노드의 왼쪽

			if (node->left != NIL) {			// 지우려는 노드의 왼쪽 노드가 있음
				RB_Delete_Red(node, NIL, red_check);
				node->parent->left = node->left;
				node->left->parent = node->parent;
				if (node->color == Color_Black && node->left->color == Color_Black && !red_check)
					RB_Delete_Black(node->left, node->parent, root);	// 노드의 왼쪽이x, 노드의 부모가 p
				delete node;
			}

			else {
				RB_Delete_Red(node, NIL, red_check);
				node->parent->left = node->right;
				node->right->parent = node->parent;
				if (node->color == Color_Black && node->right->color == Color_Black && !red_check)
					RB_Delete_Black(node->right, node->parent, root);	// 노드의 오른쪽이x, 노드의 부모가 p
				delete node;
			}

		}

		else {					// 지우려는 노드가 부모노드의 오른쪽

			if (node->left != NIL) {			// 지우려는 노드의 왼쪽 노드가 있음
				RB_Delete_Red(node, NIL, red_check);
				node->parent->right = node->left;
				node->left->parent = node->parent;
				if (node->color == Color_Black && node->left->color == Color_Black && !red_check)
					RB_Delete_Black(node->left, node->parent, root);	// 노드의 왼쪽이x, 노드의 부모가 p
				delete node;
			}

			else {
				RB_Delete_Red(node, NIL, red_check);
				node->parent->right = node->right;
				node->right->parent = node->parent;
				if (node->color == Color_Black && node->right->color == Color_Black && !red_check)
					RB_Delete_Black(node->right, node->parent, root);	// 노드의 오른쪽이x, 노드의 부모가 p
				delete node;
			}

		}
	}
}

void Delete(struct Node *node, struct Node *NIL, struct Node *&root, int key)
{
	if (node == NIL) {
		cout << "지우려는 값이 없습니다" << endl;
	}

	else {
		if (node->data == key) {
			DeleteNode(node, NIL, root);
		}

		else if (node->data > key) {				// 해당 노드의 값이 찾는 값보다 큼
			Delete(node->left, NIL, root, key);
		}

		else {
			Delete(node->right, NIL, root, key);
		}
	}
}

void Search(struct Node *root, int key)
{
	if (root == NULL) {
		cout << key << "을 찾지 못했습니다 " << endl;
	}

	else {
		if (root->data == key) {
			cout << key << " 을 찾았습니다" << endl;
		}

		else if (root->data <= key) {				// 루트의 데이터가 찾는 값보다 작으면
			Search(root->right, key);
		}

		else if (root->data > key) {				// 루트의 데이터가 찾는 값보다 크면
			Search(root->left, key);
		}
	}
}

void DeleteAll(struct Node *node, struct Node *NIL)
{
	if (node != NIL) {

		DeleteAll(node->left, NIL);
		DeleteAll(node->right, NIL);
		cout << node->data << "삭제" << endl;
		delete node;
	}
}

int main()
{
	struct Node *NIL = new Node;

	NIL->left = nullptr;
	NIL->right = nullptr;
	NIL->parent = nullptr;
	NIL->data = -1;
	NIL->color = Color_Black;

	int n = 0;
	int loop = 1;
	while (loop) {
		cout << "자료의 갯수를 입력하시오: ";
		cin >> n;

		if (n >= 1)
			loop = 0;
	}

	struct Node *root = nullptr;

	for (int i = 0; i < n; i++) {

		struct Node *node = new Node;
		node->left = NIL;
		node->right = NIL;
		node->parent = nullptr;
		node->color = Color_Red;
		node->data = uid(dre);				// 노드의 초기화

		cout << node->data << "생성" << endl;

		Insert(root, node, NIL, root);		// 루트부터 순회해서 새로운 노드와 비교, NIL이 마지막 노드, root는 항상 트리의 머리를 가리킴

		cout << "루트의 값은 : " << root->data << endl << endl;
	}


	cout << "중위 순회: " << endl;
	Check_PrintAll(root, NIL);
	cout << endl;

	char command;
	int search_data = -1;
	int input_data = 0;
	struct Node *parent = new Node;
	parent = root;

	loop = 1;
	while (loop) {

		cout << "명령어를 입력하시오: (P : 출력  S : 검색  D : 삭제  I : 삽입  C : 트리 체크  Q : 종료)";
		cin >> command;

		switch (command) {
		case 'P':

			PrintAll(root, NIL);
			cout << endl;


			cout << "루트의 값 : " << root->data << endl;
			//print_ascii_tree(ROOT);
			break;

		case 'C':

			check_tree(root, NIL);
			cout << "트리 조건 만족" << endl;
			break;

		case 'S':

			cout << "찾을 데이터를 입력하시오: ";
			cin >> search_data;
			Search(root, search_data);
			break;

		case 'D':

			cout << "찾을 데이터를 입력하시오: ";
			cin >> search_data;
			Delete(root, NIL, root, search_data);

			check_tree(root, NIL);
			cout << "트리 조건 만족" << endl;
			break;

		case 'Q':
			loop = 0;
			DeleteAll(root, NIL);

			break;

		default:
			cout << "없는 명령어입니다" << endl;
			cout << root->data << endl;
			break;

		case 'I':
			cout << "값을 입력하시오: ";
			cin >> input_data;

			struct Node *node = new Node;
			node->left = NIL;
			node->right = NIL;
			node->parent = nullptr;
			node->data = input_data;
			node->color = Color_Red;

			Insert(root, node, NIL, root);
			break;


		}
	}
}