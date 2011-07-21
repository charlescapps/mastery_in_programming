#ifndef _PARSER
#define _PARSER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
parser_tree.h 
Charles Capps
Parser + symbolic differentiation program for homework 4 of CS510 

The way this module works is--the client who includes this code must call the following functions: 

read_expression() - get user input to parse
parse() - perform parse and store result in static variable
take_derivative() - perform derivative ""
simplify_derivative() - algebraically simplify as much as this program is capable

The client program can call this sequence any number of times. 

After parse() is called at least once, print_parse_tree() may be called. 
After take_derivative() is called, print_derivative() may be called. 
After simplify_derivative() is called, print_simplified() may be called. 

Since it uses standard in, you can pipe the input expression into the program from a file. 
*/

//***********************CONSTANTS***************************************

const int MAX_SIZE; //Max length of input from user

//*********************TYPEDEFS******************************************
typedef enum {NUMBER, CONSTANT, VARIABLE, PLUS_OP, MULT_OP, EXP_OP, LOG_OP, UNDEFINED} node_class; //Types of nodes. Undefined is default. 

const char* node_class_strings[8]; //Strings corresponding to these enums. Just for printing to screen. 

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

node_ptr new_number(int); //Allocate a number node. Allows for numbers < 0 or > 9, but if so the symbol is set to 'N' for "big number"

node_ptr new_node_v2(node_class nc, char sym); //Allocate a new node with given node class and symbol 

node_ptr new_node_v3(node_class nc, char sym, node_ptr l, node_ptr r); //Allocate a new node with given nclass, symbol, left, and right

node_ptr clone_node(node_ptr); //Allocate a new node with same data as old node. left = right = NULL to avoid horrible errors. 

node_ptr clone_tree(node_ptr); //Get deep copy of a tree. Structure and values copied from old tree. 

void free_tree(node_ptr); //Free the memory for a tree recursively

bool are_trees_equal(node_ptr tree_1, node_ptr tree_2); //Recursively checks if trees are equal. 

bool are_nodes_equal(node_ptr node_1, node_ptr node_2); //Checks if 2 nodes are equal, ignoring children. Note the number field isn't compared unless nclass == NUMBER 

void print_parse_tree(); //Interface for client program to print the static parse tree 

void print_derivative(); //""												derivative tree

void print_simplified(); //""												simplified derivative tree

void print_tree_parens(node_ptr);// Print a tree with explicit parens showing how we associated operations

//*************************LL(1) PARSER FUNCTIONS**************************************

void parse(); //Parse input from user. Must be called after read_expression or an error will occur. Stores result in static variable parse_tree.

node_ptr expression(); //Functions corresponding to non-terminals for the LL(1) language

node_ptr term(); 

node_ptr factor(); 

node_ptr primary(); 

node_ptr plus_op();

node_ptr mult_op(); 

node_ptr exp_op(); 

node_ptr ident();  

void must_be(char c); //Set error flag if char c isn't the symbol in the current token. Otherwise, scan. 

bool parse_succeeded(); //Check if the most recent parse failed or succeeded. 

//************************DIFFERENTIATION FUNCTIONS***********************************

void take_derivative(void); //Interface to take the derivative of static variable parse_tree

node_ptr derivative_recurse(node_ptr); //Function that does actual work. 

void simplify_derivative(void); //Interface to simplify the derivative

node_ptr simplify_recurse(node_ptr); //Actual work done here.

void simplify_division(node_ptr root_division, node_ptr factor); //helper to simplify u(x)*v(x)*...*w(x) / u(x) = v(x)*...*w(x)

//************************CONVENIENCE / STRING FUNCTIONS*****************************

bool is_whitespace(char c);

bool is_const(char c); //Constants are any letter besides 'x', the special letter

bool is_variable(char c);

bool is_number(char c);

bool is_plus_op(char c);

bool is_mult_op(char c); //'*' or '/'

bool is_exp_op(char c); //'^'

bool char_in_string(char needle, char* haystack); //Helper to check if a char occurs in a null-terminated string

#endif
