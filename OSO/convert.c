#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

int p(char* v){
	printf("***%s***\n",v);
}

void convert(struct Node* n){
	int value = n->type;

	switch(value){
		case CMP :
		break;

		case IFNODE :
		break;

		case INTEGERNODE :
			printNewVariableIntegerNode(n);
		break;

		case VINT :
		break;

		case MAIN :
			printMain(n);
		break;

		case FROMTO :
		break;

		case FORNODE :
		break;

		case WHILENODE :
		break;

		case FUNPARAM :
		break;
	}
}

void printMain(struct Node* n){
	printf("%s(",n->value);

	for(int i = 0 ; i < n->tot_nodes ; i++){
		struct Node* s = n->nodes[i];
		if(s->type != FUNPARAM){
			printf("int reserved)\n");
			return;
		}
		else{
			printf("%s, ",s->value);
		}
	}

}

void printNewVariableIntegerNode(struct Node* n){
	printf("%s\n",n->value);
}