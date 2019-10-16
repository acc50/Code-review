#pragma once

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

typedef struct node node;

struct node {
	int key;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
	asciinode * left, *right;

	int edge_length;

	int height;

	int lablen;

	int parent_dir;

	char label[11];
};


struct node *ROOT;
struct node *NILL;

struct node *make_empty(struct node *t);

struct node *find_min(struct node *t);

struct node *find_max(struct node *t);

struct node *find(int elem, struct node *t);


struct node * pInsert(int value, struct node * t);

struct node * pDelete(int value, struct node * t);



int MIN(int X, int Y);

int MAX(int X, int Y);

asciinode * build_ascii_tree_recursive(struct node * t);


asciinode * build_ascii_tree(struct node * t);

void free_ascii_tree(asciinode *node);

void compute_lprofile(asciinode *node, int x, int y);

void compute_rprofile(asciinode *node, int x, int y);

void compute_edge_lengths(asciinode *node);


void print_level(asciinode *node, int x, int level);

void print_ascii_tree(struct node * t);