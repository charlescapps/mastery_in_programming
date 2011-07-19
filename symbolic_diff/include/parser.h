#ifndef _PARSER
#define _PARSER

typedef enum {NUMBER, CONSTANT, VARIABLE, OPERATOR, ZERO, ONE} node_class; 

typedef struct node* node_ptr; 

typedef struct {

	node_class nclass; 
	char symbol; 
	int number; 
	node_ptr left; 
	node_ptr right; 

} node; 

void read_expression(); //Read a line of input and store in variable for the module

void scan(); //get the next node from the input string

void expression(); 

void term(); 

void factor(); 

void primary(); 

#endif
