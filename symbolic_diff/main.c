#include "include/parser_tree.h"


int main() {

	read_expression(); //Must call this before calling parse() or an error will occur. (Wanted to separate input logic from parsing logic). 

	parse(); 

	if (parse_succeeded()) {
		printf("Parse succeeded!\n"); 
		printf("Original f(x) = "); 
		print_parse_tree(); //Print the expression with all parens indicating how we associated.

		take_derivative(); 

		printf("Derivative of f(x) = "); 
		print_derivative(); 
	}

	return 0;
}
