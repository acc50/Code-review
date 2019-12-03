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
		std::cout << "����";
	else
		std::cout << "����";
}
void Insert(Node*& node, int data)
{
	if (node == NIL || node == nullptr) {// Ʈ���� ������
		node = NewNode(data);
	}
	else {
		if (data < node->data) {
			if (node == NIL)
				return;
			Node* parent = node;

			Insert(node->left, data);
			node->left->parents = parent;
			if (node->left->left == NIL && node->left->right == NIL)  //������϶� üũ�Ѵ�.
				CheckTree(node);
		}
		else {
			if (node == NIL)
				return;
			Node* parent = node;

			Insert(node->right, data);
			node->right->parents = parent;
			if (node->right->left == NIL && node->right->right == NIL)  //������϶� üũ�Ѵ�.
				CheckTree(node);
		}
	}
}

void PrintAll(Node* ROOT)
{
	if (ROOT == NIL)
		return;
	else {
		std::cout << "�����ּ�" << ROOT << " �θ��ּ�:" << ROOT->parents << " ���� data:" << ROOT->data << " ����:";
		printColor(ROOT->color);
		std::cout << std::endl;
		PrintAll(ROOT->left);
		PrintAll(ROOT->right);
	}
}
void CheckTree(Node* node)
{
	if (node->parents == nullptr) { //node�� ��Ʈ�ΰ����
		if (node->color == RED) {
			node->color = BLACK;
			return;
		}
		else
			return;
	}
	if (node->parents->color == BLACK)
		return;
	else {  //�θ� ����
		Node* uncle = GetSibling(node->parents);

		if (uncle->color == BLACK) {//���� ��Ŭ null����
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
	if (node->parents == nullptr)  //�θ𰡾����� ������ ����.
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
	std::cout << "����ȸ��" << std::endl;
	Node*Parent = node->parents;
	Parent->right = node->left;
	node->left = Parent;
	node->parents = Parent->parents;

	if (Parent->parents != nullptr) {
		if (Parent == Parent->parents->left) {		// �θ��尡 �� �θ����� �����̸�
			Parent->parents->left = node;
		}
		else {
			Parent->parents->right = node;
		}
	}
	else {					// node �� ��Ʈ��尡 ��
		ROOT = node;
	}

	Parent->parents = node;
	Parent->right->parents = Parent;
}
void rightRotate(Node*node)
{
	std::cout << "������ȸ��" << std::endl;
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
	std::cout << "������ȸ��" << std::endl;
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
			std::cout << "ȸ���� node" << node << '\n';
			leftRotate(node);
			std::cout << "ȸ���� node" << node << '\n';
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