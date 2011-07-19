#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//***********************CONSTANTS***************************************

const int MAX_SIZE; //Max length of input from user



//*********************TYPEDEFS******************************************
typedef enum {NUMBER, CONSTANT, VARIABLE, PLUS_OP, MULT_OP, EXP_OP, ZERO, ONE} node_class; 

typedef struct node_type* node_ptr; 

typedef struct node_type {

	node_class nclass; 
	char symbol; 
	int number; 
	node_ptr left; 
	node_ptr right; 

} node_struct; 


//**********************FUNCTIONS*****************************************

bool read_expression(); //Read a line of input and store in variable for the module. true / false on success/failure

void scan(); //get the next node from the input string

void expression(); 

void term(); 

void factor(); 

void primary(); 

bool is_whitespace(char c);

bool is_const(char c);//Constants are any letter besides 'x', the special letter

bool is_variable(char c);

bool is_number(char c);

bool is_plus_op(char c);

bool is_mult_op(char c);

bool is_exp_op(char c); 

bool char_in_string(char needle, char* haystack);

#endif
