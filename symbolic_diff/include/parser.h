#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//***********************CONSTANTS***************************************

const int MAX_SIZE; //Max length of input from user



//*********************TYPEDEFS******************************************
typedef enum {NUMBER, CONSTANT, VARIABLE, PLUS_OP, MULT_OP, EXP_OP, ZERO, ONE, UNDEFINED} node_class; 
const char* node_class_strings[9];

typedef struct node_type* node_ptr; 

typedef struct node_type {

	node_class nclass; 
	char symbol; 
	int number; 
	node_ptr left; 
	node_ptr right; 

} node_struct; 


//**********************INPUT / PRINT FUNCTIONS*****************************************

bool read_expression(); //Read a line of input and store in variable for the module. true / false on success / failure

void scan(); //get the next node from the input string. Exit program with error message if invalid char is found.

void print_node(node_ptr n); 

//***************************NODE / TREE FUNCTIONS************************************

node_ptr new_node();

//*************************LL(1) PARSER FUNCTIONS**************************************

void parse(); 

void expression(); 

void term(); 

void factor(); 

void primary(); 

void plus_op();

void mult_op(); 

void exp_op(); 

void ident();  

void must_be(char c); 

bool parse_succeeded();

//************************CONVENIENCE / STRING FUNCTIONS**********************

bool is_whitespace(char c);

bool is_const(char c); //Constants are any letter besides 'x', the special letter

bool is_variable(char c);

bool is_number(char c);

bool is_plus_op(char c);

bool is_mult_op(char c);

bool is_exp_op(char c); 

bool char_in_string(char needle, char* haystack);

#endif
