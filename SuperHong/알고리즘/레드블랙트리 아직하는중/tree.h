#pragma once
#define BLACK 0
#define RED 1
struct Node {
	Node* left;
	Node* right;
	Node* parent;
	int data;
	int color=BLACK;
};
void makeNode(Node*& node, int data);
void Insert(Node*& node, int data);
void PrintNode(Node* root);
struct Node *grandparent(struct Node *n);
struct Node *uncle(struct Node *n);
void insert_case1(struct Node *n);
void insert_case2(struct Node *n);
void insert_case3(struct Node *n);
void insert_case4(struct Node *n);
static void rotate_right(struct Node *n);
static void rotate_left(struct Node *n);
void insert_case5(struct Node *n);
void PrintColor(int color);