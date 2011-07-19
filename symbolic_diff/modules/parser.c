#include "../include/parser.h"

//***********************MODULE CONSTANTS****************************************
const int MAX_SIZE = 1024; 
static const char VARIABLE_CHAR = 'x'; 
static const char END_OF_EXP = '$'; 
static const char WHITESPACE[] = {'\n', ' ', '\t', '\0'};
static const char PLUS_OPS[] = {'+', '-', '\0'}; 
static const char MULT_OPS[] = {'*', '/', '\0'}; 
static const char EXP_OP_CHAR = '^'; 

//***********************MODULE VARIABLES****************************************
static node_ptr token = NULL; 
static char* input = NULL;
static char* current = NULL;
static bool is_eof = false; 

//************************FUNCTION DEFINITIONS***********************************

bool read_expression() { //Read a line of input and store in variable for the module
	bool success;
	input = (char*) malloc(sizeof(char)*(MAX_SIZE + 1)); 

	printf("Enter function to differentiate. f(x) = \n"); 

	if (!(success = fgets(input, MAX_SIZE, stdin)) ) {
		printf("Failure getting input.\n"); 
	}  

	current = input; 

	printf("Expression: %s\n", input);  

	return success;
}

void scan() { //get the next node from the input string

	token = (node_ptr) malloc(sizeof(node_struct)); 

	while (*current != END_OF_EXP && is_whitespace(*current)) { //Throw out whitespace
		current++; 
	}

	if (*current == END_OF_EXP) {
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
	else {
		fprintf(stderr, "Invalid character %c found when parsing input.\n", c); 
		exit(1); 
	}

}

void expression() {

} 

void term() {

}

void factor() {

}

void primary() {

}

bool is_whitespace(char c) {
	char* ptr = (char*)WHITESPACE; 
	while (ptr) {
		if (c == *ptr) {
			return true; 
		}
		ptr++; 
	}
	return false; 
}

bool char_in_string(char needle, char* haystack) {
	while (haystack) {
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
