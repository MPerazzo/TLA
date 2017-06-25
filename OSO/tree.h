#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 30
#define MAX_LENGTH 100

typedef enum {CMP, IFNODE, INTEGERNODE, VINT, MAIN, FROMTO, FORNODE, WHILENODE} types;

struct Node {
	types type;
	char* value; //cambiar!! deberia ser algo mas generico
	int tot_nodes;
	struct Node* nodes[MAX_NODES];
};

char* printNode(struct Node* n);
void printTree(struct Node* node);
struct Node* createNewVariableIntegerNode(char* name, int value);
struct Node* createIntegerNode(int value);
struct Node* createCMPNode(char* symbol);
struct Node* createIfNode();
struct Node* createMainNode(char* function_name);
void addLeaveAtPosition(struct Node* root, struct Node* leave, int pos);
void addLeaves(struct Node* root, struct Node* leave);
struct Node* createForNode();
struct Node* createFromToNode(char* name, int from, int to);
struct Node* createIntegerNodeNoToStack(int value);
struct Node* createWhileNode();