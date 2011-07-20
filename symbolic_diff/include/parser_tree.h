#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//***********************CONSTANTS***************************************

const int MAX_SIZE; //Max length of input from user


//*********************TYPEDEFS******************************************
typedef enum {NUMBER, CONSTANT, VARIABLE, PLUS_OP, MULT_OP, EXP_OP, LOG_OP, UNDEFINED} node_class; 
const char* node_class_strings[8];

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

node_ptr new_node(void); //Allocate a new node with default values. node_class = UNDEFINED by default. 

node_ptr new_number(int); 

node_ptr new_node_v2(node_class nc, char sym); //Allocate a new node with given node class and symbol 

node_ptr new_node_v3(node_class nc, char sym, node_ptr l, node_ptr r); //Allocate a new node with given node class and symbol 

node_ptr clone_node(node_ptr); //Allocate a new node with the same values as the old node. left = right = NULL to avoid horrible errors. 

node_ptr clone_tree(node_ptr); //Get a new tree with completely different memory space. Copy over structure and values from old tree. 

void free_tree(node_ptr); 

void print_parse_tree();

void print_derivative(); 

void print_simplified(); 

void print_tree_parens(node_ptr);

node_ptr get_derivative_tree();

//*************************LL(1) PARSER FUNCTIONS**************************************

void parse(); 

node_ptr expression(); 

node_ptr term(); 

node_ptr factor(); 

node_ptr primary(); 

node_ptr plus_op();

node_ptr mult_op(); 

node_ptr exp_op(); 

node_ptr ident();  

void must_be(char c); 

bool parse_succeeded();

//************************DIFFERENTIATION FUNCTIONS***********************************

void take_derivative(void); 

node_ptr derivative_recurse(node_ptr); 

void simplify_derivative(void); 

void simplify_recurse(node_ptr); 
//************************CONVENIENCE / STRING FUNCTIONS*****************************

bool is_whitespace(char c);

bool is_const(char c); //Constants are any letter besides 'x', the special letter

bool is_variable(char c);

bool is_number(char c);

bool is_plus_op(char c);

bool is_mult_op(char c);

bool is_exp_op(char c); 

bool char_in_string(char needle, char* haystack);

#endif
