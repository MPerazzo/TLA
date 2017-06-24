#include <stdio.h>
#include <stdlib.h>
#include "tree.c"

int main_test(){
	printf("En main_test()\n");
	struct Node root;
	root.type = CMP;
	root.value = ">";

	struct Node l;
	l.type = INTEGER;
	l.value = "100";

	struct Node r;
	r.type = INTEGER;
	r.value = "10";

	root.tot_nodes = 2;
	l.tot_nodes = 0;
	r.tot_nodes = 0;

	root.nodes[0] = &l;
	root.nodes[1] = &r;

	printTree(&root);

}

int main(void){
	//main_test();

	
	/*struct Node vint1 = createNewVariableIntegerNode("var1", 1);
	struct Node vint2 = createNewVariableIntegerNode("var2", 3);
	struct Node vint3 = createNewVariableIntegerNode("var3", 5);
	struct Node vint4 = createNewVariableIntegerNode("var4", 7);
	
	addLeaves(&vint1, &vint2);
	addLeaves(&vint1, &vint3);
	addLeaves(&vint2, &vint4);

	printf("IMPRIMO EL ARBOL\n");
	printTree(&vint1);
	
	*/
	printf("Entro\n");

	struct Node* i1 = createIntegerNode(100);
	struct Node* i2 = createIntegerNode(50);

	printf("Primer print\n");
	printStack();
	
	struct Node* cmp_val = createCMPNode(">");
	
	printf("Segundo print\n");
	printStack();
	
	/*
	printf("IMPRIMO NUEVAMENTE EL ARBOL\n");
	printTree(&cmp_val);
	*/

	return 0;
	
}
