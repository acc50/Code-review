#include "tree.h"


Node* NewNode(int data)
{
	Node* node = new Node;
	node->data = data;
	node->left = node->right = NIL;
	node->color = RED;
	return node;
}
void printColor(int d) {
	if (d == BLACK)
		std::cout << "검정";
	else
		std::cout << "빨강";
}
void Insert(Node*& node, int data)
{
	if (node == NIL || node == nullptr) {// 트리의 마지막
		node = NewNode(data);
	}
	else {
		if (data < node->data) {
			if (node == NIL)
				return;
			Node* parent = node;

			Insert(node->left, data);
			node->left->parents = parent;
			if (node->left->left == NIL && node->left->right == NIL)  //끝노드일때 체크한다.
				CheckTree(node);
		}
		else {
			if (node == NIL)
				return;
			Node* parent = node;

			Insert(node->right, data);
			node->right->parents = parent;
			if (node->right->left == NIL && node->right->right == NIL)  //끝노드일때 체크한다.
				CheckTree(node);
		}
	}
}

void PrintAll(Node* ROOT)
{
	if (ROOT == NIL)
		return;
	else {
		std::cout << "본인주소" << ROOT << " 부모주소:" << ROOT->parents << " 본인 data:" << ROOT->data << " 색깔:";
		printColor(ROOT->color);
		std::cout << std::endl;
		PrintAll(ROOT->left);
		PrintAll(ROOT->right);
	}
}
void CheckTree(Node* node)
{
	if (node->parents == nullptr) { //node가 루트인경우임
		if (node->color == RED) {
			node->color = BLACK;
			return;
		}
		else
			return;
	}
	if (node->parents->color == BLACK)
		return;
	else {  //부모가 레드
		Node* uncle = GetSibling(node->parents);

		if (uncle->color == BLACK) {//여기 엉클 null수정
			case2_1(node);
			return;
		}
		else if (uncle->color == RED) {
			node->parents->color = BLACK;
			uncle->color = BLACK;
			CheckTree(node->parents);
		}

	}
}

Node* GetSibling(Node* node)
{
	if (node->parents == nullptr)  //부모가없으면 형제는 없다.
		return nullptr;
	else {
		if (node->parents->left != node) {
			return node->parents->left;
		}
		else
			return node->parents->right;
	}
}


void leftRotate(Node*node)
{
	std::cout << "왼쪽회전" << std::endl;
	Node*Parent = node->parents;
	Parent->right = node->left;
	node->left = Parent;
	node->parents = Parent->parents;

	if (Parent->parents != nullptr) {
		if (Parent == Parent->parents->left) {		// 부모노드가 그 부모노드의 왼쪽이면
			Parent->parents->left = node;
		}
		else {
			Parent->parents->right = node;
		}
	}
	else {					// node 가 루트노드가 됨
		ROOT = node;
	}

	Parent->parents = node;
	Parent->right->parents = Parent;
}
void rightRotate(Node*node)
{
	std::cout << "오른쪽회전" << std::endl;
	Node*Parent = node->parents;
	Parent->left = node->right;
	node->right = Parent;
	node->parents = Parent->parents;

	if (Parent->parents != nullptr) {
		if (Parent == Parent->parents->left) {
			Parent->parents->left = node;
		}
		else {
			Parent->parents->right = node;
		}
	}
	else {
		ROOT = node;
	}

	Parent->parents = node;
	Parent->left->parents = Parent;
}
void rightRotate1(Node*node)
{
	std::cout << "오른쪽회전" << std::endl;
	Node* gp = node->parents->parents;
	Node*Parent = node->parents;
	Parent->left = node->right;
	node->right = Parent;
	node->parents = Parent->parents;

	if (Parent->parents != nullptr) {
		if (Parent == Parent->parents->left) {
			Parent->parents->left = node;
		}
		else {
			Parent->parents->right = node;
		}
	}
	else {
		ROOT = node;
	}

	Parent->parents = node;
	Parent->left->parents = Parent;
}

void case2_1(Node* node)
{
	Node*Parent = node->parents;
	if (Parent->parents->right->color == BLACK) {
		if (node == Parent->right) {
			std::cout << "회전전 node" << node << '\n';
			leftRotate(node);
			std::cout << "회전후 node" << node << '\n';
			rightRotate(node);
			node->color = BLACK;
			node->right->color = RED;
			CheckTree(node);
		}

		else if (node == Parent->left) {
			rightRotate(Parent);
			Parent->color = BLACK;
			node;
			node->left;
			Parent->right->color = RED;
			CheckTree(Parent);
		}
	}

	else if (Parent->parents->left->color == BLACK) {

		if (node == Parent->right) {
			rightRotate(Parent);
			Parent->color = BLACK;
			Parent->left->color = RED;
			CheckTree(node);
		}

		else if (node == Parent->left) {
			leftRotate(node);
			rightRotate(node);
			node->color = BLACK;
			node->left->color = RED;
			CheckTree(Parent);
		}
	}

}