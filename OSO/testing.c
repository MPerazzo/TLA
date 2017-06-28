#include <stdio.h>
#include <stdlib.h>

#include "tree.c"

int main(void){

	printf("Entro\n");

	struct Node* var1 = createNewVariableIntegerNode("var1",15);
	struct Node* var2 = createNewVariableIntegerNode("var2",37);


	struct Node* i1 = createIntegerNode(100);
	struct Node* i2 = createIntegerNode(50);

	printf("Primer print\n");
	printStack();
	
	struct Node* cmp_val = createCMPNode(">");
	
	printf("Segundo print\n");
	printStack();

	struct Node* var3 = createNewVariableIntegerNode("var3",77);
	struct Node* var4 = createNewVariableIntegerNode("var4",80);

	printf("Tercer print\n");
	printStack();

	createIfNode();

	printf("Cuarto print\n");
	printStack();

	printf("Termine... Ahora creo el nodo principal\n");
	struct Node* main = createMainNode("function name");	
	printTree(main);

	return 0;
	
}
