#include "include/parser.h"


int main() {

	node_ptr np; 

	read_expression(); 

	parse(); 

	if (parse_succeeded()) {
		printf("Parse succeeded!\n"); 
	}

	return 0;
}
