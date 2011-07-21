#include "include/parser_tree.h"


int main() {

	read_expression(); //Must call this before calling parse() or an error will occur. (Wanted to separate input logic from parsing logic). 

	parse(); 

	if (parse_succeeded()) {
		printf("Parse succeeded!\n"); 
		printf("original f(x) = "); 
		print_parse_tree(); //Print the expression with all parens indicating how we associated.

		take_derivative(); 
		printf("derived f'(x) = "); 
		print_derivative(); 

		simplify_derivative(); 
		printf("reduced f'(x) = "); 
		print_simplified(); 
	}

	return 0;
}
