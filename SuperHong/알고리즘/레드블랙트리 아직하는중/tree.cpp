#include <iostream>
#include <random>
#include <time.h>
#include "tree.h"
struct Node *grandparent(struct Node *n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}
struct Node *uncle(struct Node *n)
{
	struct Node *g = grandparent(n);
	if (g == NULL)
		return NULL; // No grandparent means no uncle
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}
void insert_case1(struct Node *n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}
void insert_case2(struct Node *n)
{
	if (n->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(n);
}
void insert_case3(struct Node *n)
{
	struct Node *u = uncle(n), *g;

	if ((u != NULL) && (u->color == RED)) {
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(g);
	}
	else {
		insert_case4(n);
	}
}
void insert_case4(struct Node *n)
{
	struct Node *g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) {
		rotate_left(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right)) {
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

static void rotate_left(struct Node *n)
{
	struct Node *c = n->right;
	struct Node *p = n->parent;

	if (c->left != NULL)
		c->left->parent = n;

	n->right = c->left;
	n->parent = c;
	c->left = n;
	c->parent = p;

	if (p != NULL) {
		if (p->left == n)
			p->left = c;
		else
			p->right = c;
	}
}

static void rotate_right(struct Node *n)
{
	struct Node *c = n->left;
	struct Node *p = n->parent;

	if (c->right != NULL)
		c->right->parent = n;

	n->left = c->right;
	n->parent = c;
	c->right = n;
	c->parent = p;

	if (p != NULL) {
		if (p->right == n)
			p->right = c;
		else
			p->left = c;
	}
}
void insert_case5(struct Node *n)
{
	struct Node *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;
	if (n == n->parent->left)
		rotate_right(g);
	else
		rotate_left(g);
}

void PrintColor(int color)
{
	if (color == RED)
		std::cout << " 색깔:" << "빨강";
	else
		std::cout << " 색깔:" << "검정";
}

void PrintNode(Node* root)
{
	if (root == NULL)
		return;
	else {
		std::cout << "자기주소" << root << "부모주소" << root->parent << " 값" << root->data; PrintColor(root->color); std::cout << '\n';
		PrintNode(root->left);
		PrintNode(root->right);
	}
}

void makeNode(Node*& node, int data)
{
	Node* newNode = new Node;
	node = newNode;
	node->left = NULL; node->right = NULL;
	node->data = data;
	node->color = RED;
}

void Insert(Node*& node, int data)
{
	if (node == NULL) {
		makeNode(node, data);
	}
	else {
		if (node->data >= data) {
			Insert(node->left, data);
			node->left->parent = node;
	
		}
		else {

			Insert(node->right, data);
			node->right->parent = node;
		
		}
	}
}