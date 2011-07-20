#include "include/parser_tree.h"


int main() {

	node_ptr np; 

	read_expression(); 

	parse(); 

	if (parse_succeeded()) {
		printf("Parse succeeded!\n"); 
		print_tree_parens(); //Print the expression with all parens indicating how we associated.
	}

	return 0;
}
