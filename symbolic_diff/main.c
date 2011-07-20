#include "include/parser_tree.h"


int main() {

	read_expression(); //Must call this before calling parse() or an error will occur. (Wanted to separate input logic from parsing logic). 

	parse(); 

	if (parse_succeeded()) {
		printf("Parse succeeded!\n"); 
		printf("Original f(x) = "); 
		print_tree_parens(); //Print the expression with all parens indicating how we associated.
	}

	return 0;
}
