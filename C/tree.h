#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define MAX_LENGTH 100

typedef enum {CMP, IF, INTEGER, VINT} types;

struct Node {
	types type;
	char* value; //cambiar!! deberia ser algo mas generico
	int tot_nodes;
	struct Node* nodes[MAX_NODES];
};

char* printNode(struct Node* n);
void printTree(struct Node* node);
struct Node createNewVariableIntegerNode(char* name, int value);
void addLeaves(struct Node* root, struct Node* leave);