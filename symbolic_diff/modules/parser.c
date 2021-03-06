#include "../include/parser.h"

//***********************MODULE CONSTANTS****************************************
const int MAX_SIZE = 1024; 
const char* node_class_strings[9] = {"NUMBER", "CONSTANT", "VARIABLE", "PLUS_OP", "MULT_OP", "EXP_OP", "ZERO", "ONE", "UNDEFINED"};
static const char VARIABLE_CHAR = 'x'; 
static const char END_OF_EXP = '$'; 
static const char WHITESPACE[] = {'\n', ' ', '\t', '\0'};
static const char PLUS_OPS[] = {'+', '-', '\0'}; 
static const char MULT_OPS[] = {'*', '/', '\0'}; 
static const char EXP_OP_CHAR = '^'; 
static const char OPEN_PAREN = '('; 
static const char CLOSE_PAREN = ')'; 

//***********************MODULE VARIABLES****************************************
static node_ptr token = NULL; 
static char* input = NULL;
static char* current = NULL;
static bool is_eof = false; 
static bool parse_determined = false; //Indicates if we already encountered an error. Substitute for throwing exceptions, since they aren't supported by C. 
static bool parse_success = false; //Default is false, so it is only set to true if (!parse_determined) and we finish the parse successfully

//************************INPUT / PRINT FUNCTIONS***********************************

bool read_expression() { //Read a line of input and store in variable for the module
	bool success;
	input = (char*) malloc(sizeof(char)*(MAX_SIZE + 1)); 

	printf("Enter function to differentiate. f(x) = \n"); 

	if (!(success = fgets(input, MAX_SIZE, stdin)) ) {
		printf("Failure getting input.\n"); 
		return false; 
	}  

	int len = strlen(input); 

	if (input[len - 1] == '\n') { //get rid of the endline. 
		input[len - 1] = '\0'; 
	}

	printf("Expression: %s\n", input);  

	return success;
}

void scan() { //get the next node from the input string

	token = new_node();  

	if (is_eof) {
		return; 
	}

	if (current == NULL) {
		current = input; 
	}
	else {
		current++; 
	}

	while ((*current) && (*current != END_OF_EXP) && is_whitespace(*current)) { //Throw out whitespace
		current++; 
	}

	if (!(*current)) {
		fprintf(stderr, "Parse error: No '$' present.\n"); 
		is_eof = true; 
		parse_determined = true; 
		return; 
	}

	if (*current == END_OF_EXP) {
		token->symbol = END_OF_EXP; 
		is_eof = true; 
		return; 
	}


	char c = *current; 

	token -> symbol = c; 

	if (is_number(c)) {
		if (c == '0') {
			token -> nclass = ZERO; 
		}
		else if (c == '1') {
			token -> nclass = ONE; 
		}
		else {
			token -> nclass = NUMBER;
		} 
		token->number = c - '0'; 
	}
	else if (is_plus_op(c)) { 
		token -> nclass = PLUS_OP; 
	}
	else if (is_mult_op(c)) {
		token -> nclass = MULT_OP; 
	}
	else if (is_exp_op(c)) {
		token -> nclass = EXP_OP; 
	}
	else if (is_const(c) ) {
		token -> nclass = CONSTANT; 
	}
	else if (is_variable(c)) {
		token -> nclass = VARIABLE; 
	}
	else if (c == OPEN_PAREN || c == CLOSE_PAREN) { //If we encounter a paren, node is UNDEFINED type with the character stored inside it. 
		; 											//This node will never actually be added to the tree
	}
	else {
		fprintf(stderr, "Parse error: Invalid character %c found.\n", c);
		parse_determined = true; 
		return; 
	}

	printf("At end of scan function\n"); 
	print_node(token); 
	printf("\n"); 

}


//*******************NODE / TREE FUNCTIONS**********************************

node_ptr new_node() {
	
	node_ptr np = (node_ptr) malloc(sizeof(node_struct)); 
	np->nclass = UNDEFINED; 
	np->number = -1; 
	np->symbol = '#';
	np->left = np->right = NULL; 

	return np; 

}

void print_node(node_ptr n) {

	printf("Node class: %s\n", node_class_strings[n->nclass]); 
	printf("Node symbol: %c\n", n->symbol); 
	printf("Node value: %d\n", n->number); 
}

//**************************LL(1) PARSER FUNCTIONS****************************

void parse() {
	if (input == NULL) {
		fprintf(stderr, "Parse error: Must call read_expression() before calling parse().\n"); 
		return; 
	}
	scan(); 		
	expression();
	if (!is_eof) {
		fprintf(stderr, "Parse error: Parse finished before reaching '$'.\n"); 
		return; 
	} 

	if (!parse_determined) {
		parse_success = true; 
	}

}

void expression() {
	if (parse_determined) return; 

	term(); 
	
	if (token -> nclass == PLUS_OP) {
		scan(); 
		expression(); 
	}
	
} 

void term() {
	if (parse_determined) return; 

	factor(); 

	if (token -> nclass == MULT_OP) {
		scan(); 
		term(); 	
	}

}

void factor() {
	if (parse_determined) return; 

	primary(); 
	
	if (token -> nclass == EXP_OP) {
		scan(); 
		factor(); 		
	}
}

void primary() {
	if (parse_determined) return; 

	if ( token -> symbol == OPEN_PAREN ) {
		scan(); 
		expression(); 
		must_be(CLOSE_PAREN); 
	}
	else {
		ident(); 
	} 
	
}

void ident() {
	if (parse_determined) return; 

	if ( (token -> nclass == VARIABLE) || (token -> nclass == CONSTANT) || (token->nclass == NUMBER) ) {
		scan(); 
	}
	else {
		fprintf(stderr, "Parse error: Required variable, constant, or number. Found: '%c'\n", token->symbol);
		parse_determined = true;  
	}
}

void must_be(char c) {
	if (parse_determined) return; 

	if (token -> symbol == c) {
		scan(); 
	}
	else {
		fprintf(stderr, "Parse error: Expected '%c', found '%c'\n", c, token->symbol); 
		parse_success = false; 
		parse_determined = true; 
	}
}

bool parse_succeeded() {
	return parse_success; 
}

//*********************FUNCTIONS FOR CONVENIENCE*****************************

bool is_whitespace(char c) {
	char* ptr = (char*)WHITESPACE; 
	while (*ptr) {
		if (c == *ptr) {
			return true; 
		}
		ptr++; 
	}
	return false; 
}

bool char_in_string(char needle, char* haystack) {
	while (*haystack) {
		if (needle == *haystack) {
			return true; 
		}
		haystack++; 
	}
	return false; 
}

bool is_const(char c) {//Constants are any letter besides 'x', the special letter
	return ( (c != VARIABLE_CHAR && ( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) )); 
}

bool is_variable(char c) {
	return (c == VARIABLE_CHAR); 
}

bool is_number(char c) {
	return '0' <= c && c <= '9'; 
}

bool is_plus_op(char c) {
	return char_in_string(c, (char*)PLUS_OPS); 
}

bool is_mult_op(char c) {
	return char_in_string(c, (char*)MULT_OPS); 
}

bool is_exp_op(char c) {
	return (c == EXP_OP_CHAR); 
}
