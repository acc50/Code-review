#pragma once
#include <iostream>
#include <random>
#define SIZE 5
#define BLACK 0
#define RED 1
struct Node {
	Node* parents = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int data;
	int color = BLACK;
};
extern Node* ROOT;
extern Node* NIL;
void printColor(int d);
Node* NewNode(int data);
void PrintAll(Node* ROOT);
void Insert(Node*& node, int data);
void CheckTree(Node* node);
Node* GetSibling(Node* node);
void case2_1(Node* node);
void case2_2(Node*& node);
void leftRotate(Node* node);
void rightRotate(Node* node);


