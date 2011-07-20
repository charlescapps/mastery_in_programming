#include "../include/parser_tree.h"

//*************************GLOBAL CONSTANTS DEFINED*****************************
const int MAX_SIZE = 1024; 
const char* node_class_strings[8] = {"NUMBER", "CONSTANT", "VARIABLE", "PLUS_OP", "MULT_OP", "EXP_OP", "LOG_OP", "UNDEFINED"};
//***********************MODULE CONSTANTS****************************************
static const char VARIABLE_CHAR = 'x'; 
static const char END_OF_EXP = '$'; 
static const char WHITESPACE[] = {'\n', ' ', '\t', '\0'};

static const char PLUS_CHAR = '+'; 
static const char MINUS_CHAR = '-'; 
static const char PLUS_OPS[] = {'+', '-', '\0'}; 

static const char MULT_CHAR = '*'; 
static const char DIV_CHAR = '/'; 
static const char MULT_OPS[] = {'*', '/', '\0'}; 

static const char EXP_CHAR = '^'; 
static const char LOG_CHAR = '&'; 

static const char OPEN_PAREN = '('; 
static const char CLOSE_PAREN = ')'; 

static const char BIG_NUMBER = 'N'; 

//***********************MODULE VARIABLES****************************************
static node_ptr token = NULL; 
static node_ptr parse_tree = NULL;
static node_ptr derivative_tree = NULL;  
static node_ptr simplified_deriv = NULL; 
static char* input = NULL;
static char* current = NULL;
static bool is_eof = false; 
static bool parse_fail_early = false; //Indicates if we already encountered an error. Substitute for throwing exceptions, since they aren't supported by C. 
static bool parse_success = false; //Default is false, so it is only set to true if (!parse_fail_early) and we finish the parse successfully

//************************INPUT / PRINT FUNCTIONS***********************************

bool read_expression() { //Read a line of input and store in variable for the module
	bool success;
	input = (char*) malloc(sizeof(char)*(MAX_SIZE + 1)); 

	printf("Enter f(x), terminating with '$': "); 

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
		parse_fail_early = true; 
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
		token -> nclass = NUMBER;
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
		parse_fail_early = true; 
		return; 
	}

	//printf("At end of scan function\n"); 
	//print_node(token); 
	//printf("\n"); 
}

//*******************NODE / TREE FUNCTIONS**********************************

node_ptr get_derivative_tree() {
	return derivative_tree; 
}

node_ptr new_node(void) {
	
	node_ptr np = (node_ptr) malloc(sizeof(node_struct)); 
	np->nclass = UNDEFINED; 
	np->number = -1; 
	np->symbol = '#';
	np->left = np->right = NULL; 

	return np; 

}

node_ptr new_node_v2(node_class nc, char sym) { //Bah C doesn't have function overloading :-(
	node_ptr new_guy = new_node(); 
	new_guy -> nclass = nc; 
	new_guy -> symbol = sym; 
	return new_guy; 
} 

node_ptr new_node_v3(node_class nc, char sym, node_ptr l, node_ptr r) { //Allocate a new node with given node class, symbol, and left / right 
	node_ptr new_guy = new_node_v2(nc, sym); 
	new_guy -> left = l; 
	new_guy -> right = r; 
	return new_guy; 
}

node_ptr new_number(int n) {
	node_ptr new_guy = new_node(); 
	new_guy -> nclass = NUMBER; 
	new_guy -> number = n; 
	if (n < 0 || n > 9) {
		new_guy -> symbol = BIG_NUMBER; 
	}
	else {
		new_guy -> symbol = '0' + n; 
	}
	return new_guy; 
}

node_ptr clone_node(node_ptr old) {

	node_ptr clone = new_node();
	clone->nclass = old->nclass; 
	clone->number = old->number;  
	clone->symbol = old->symbol; 

	return clone; 
}

node_ptr clone_tree(node_ptr old_root) {

	if (old_root == NULL) {
		return NULL; 
	}

	node_ptr new_root = clone_node(old_root); 
	new_root -> left = clone_tree(old_root -> left); 
	new_root -> right = clone_tree(old_root -> right); 

	return new_root;
}

void free_tree(node_ptr root) {

	if (root == NULL) {
		return; 
	}

	free_tree(root -> left); //POST-order traversal so that we don't reference anything after it has been freed

	free_tree(root -> right); 

	free(root); 
} 

void print_node(node_ptr n) {

	printf("Node class: %s\n", node_class_strings[n->nclass]); 
	printf("Node symbol: %c\n", n->symbol); 
	printf("Node value: %d\n", n->number); 
}

void print_parse_tree() {
	print_tree_parens(parse_tree); 
	printf("\n"); 
}

void print_derivative() {
	print_tree_parens(derivative_tree); 
	printf("\n"); 
}

void print_simplified() {
	print_tree_parens(simplified_deriv); 
	printf("\n"); 
}

void print_tree_parens(node_ptr np) {
	if (np == NULL) {
		return; 
	}	

	if (np -> nclass == PLUS_OP || np -> nclass == MULT_OP || np -> nclass == EXP_OP) { //If it's an operator, print the result with surrounding parens
		printf("(");  
		print_tree_parens(np->left); 
		printf(" %c ", np->symbol); 
		print_tree_parens(np->right); 
		printf(")");	
		return; 
	}

	if (np -> nclass == LOG_OP) {
		assert(np->right == NULL); //Log is a unary operation. Assert right child is NULL. 
		printf("&("); 
		print_tree_parens(np->left); 
		printf(")"); 
		return; 
	}

	//Else we must have enountered a variable, constant, or number. So just print the char.
	printf("%c", np->symbol); 

}

//**************************LL(1) PARSER FUNCTIONS****************************

void parse() {
	if (input == NULL) {
		fprintf(stderr, "Parse error: Must call read_expression() before calling parse().\n"); 
		return; 
	}
	scan(); 		
	parse_tree = expression();

	if (!is_eof) {
		fprintf(stderr, "Parse error: Parse finished before reaching '$'.\n"); 
		return; 
	} 

	if (!parse_fail_early) {
		parse_success = true; 
	}

}

node_ptr expression() {
	if (parse_fail_early) return NULL; 

	node_ptr plus_node = NULL, expr_root = NULL, right_node = NULL; 

	expr_root = term(); 
	
	while (token -> nclass == PLUS_OP) {
		plus_node = token; 

		scan(); 

		right_node = term(); 

		plus_node -> left = expr_root; 
		plus_node -> right = right_node; 
		
		expr_root = plus_node; 
		
	}

	return expr_root; 
} 

node_ptr term() {
	if (parse_fail_early) return NULL; 

	node_ptr mult_node = NULL, term_root = NULL, right_node = NULL; 

	term_root = factor(); 

	while (token -> nclass == MULT_OP) {
		mult_node = token; 
		scan(); 
		right_node = factor();

		mult_node -> left = term_root; 
		mult_node -> right = right_node; 

		term_root = mult_node;  	
	}

	return term_root; 
}

node_ptr factor() {
	if (parse_fail_early) return NULL; 

	node_ptr exp_node = NULL, left_node = NULL, right_node = NULL; 

	left_node = primary(); 
	
	if (token -> nclass == EXP_OP) {
		exp_node = token; 
		scan(); 
		right_node = factor(); 		
	}

	if (exp_node != NULL) { //If we found a '^', return the node that has the operands as its children
		exp_node -> left = left_node; 
		exp_node -> right = right_node; 
		return exp_node; 
	}
	else { //Else just return the primary expression
		return left_node; 
	}
}

node_ptr primary() {
	if (parse_fail_early) return NULL; 

	node_ptr primary_node = NULL; 

	if ( token -> symbol == OPEN_PAREN ) {
		scan(); 
		primary_node = expression(); 
		must_be(CLOSE_PAREN); 
	}
	else {
		primary_node = ident(); 
	} 

	return primary_node; 
}

node_ptr ident() { //Note: this function is different from the others, since it's a leaf of the tree. Could be called must_be since the parse fails if it doesn't find an ident.
	if (parse_fail_early) return NULL; 

	node_ptr leaf = NULL; 

	if ( (token -> nclass == VARIABLE) || (token -> nclass == CONSTANT) || (token->nclass == NUMBER) ) {
		leaf = token; 
		scan(); 
	}
	else {
		fprintf(stderr, "Parse error: Required variable, constant, or number. Found: '%c'\n", token->symbol);
		parse_fail_early = true;  
	}

	return leaf; 
}

void must_be(char c) {
	if (parse_fail_early) return; 

	if (token -> symbol == c) {
		scan(); 
	}
	else {
		fprintf(stderr, "Parse error: Expected '%c', found '%c'\n", c, token->symbol); 
		parse_fail_early = true; 
	}
}

bool parse_succeeded() {
	return parse_success; 
}

//**********************DIFFERENTIATION FUNCTIONS***************************

void take_derivative() {
	derivative_tree = clone_tree(parse_tree); 

	derivative_tree = derivative_recurse(derivative_tree); 	
}

node_ptr derivative_recurse(node_ptr current) {

	if (current == NULL) {
		return NULL; 
	}

	if (current -> nclass == VARIABLE) { // d/dx(x) = 1
		assert(current -> left == NULL && current -> right == NULL);  //variable has no children
		current -> nclass = NUMBER; 
		current -> number = 1; 
		current -> symbol = '1'; 
		return current; 
	}

	if (current -> nclass == CONSTANT || current -> nclass == NUMBER) { //derivative of a constant is 0
		assert(current -> left == NULL && current -> right == NULL);  //constant has no children
		current -> nclass = NUMBER;
		current -> number = 0; 
		current -> symbol = '0';
		return current;   
	}

	if (current -> nclass == PLUS_OP) { // d/dx (u(x) +- v(x)) = u'(x) +- v'(x)
		current -> left = derivative_recurse(current -> left); 
		current -> right = derivative_recurse(current -> right);  
		return current; 
	}

	if (current -> nclass == MULT_OP && current -> symbol == MULT_CHAR ) { // d/dx (u(x)*v(x)) = u'(x)*v(x) + u(x)*v'(x) 

		//Root of new function is an addition
		node_ptr new_root = new_node_v2(PLUS_OP, PLUS_CHAR); 
		
		//Build the left operand
		node_ptr left_mult = new_node_v2(MULT_OP, MULT_CHAR); 
		left_mult -> left = derivative_recurse(clone_tree(current->left)); 
		left_mult -> right = clone_tree(current -> right); 

		//Build the right operand
		node_ptr right_mult = new_node_v2(MULT_OP, MULT_CHAR); 
		right_mult -> left = current -> left; 
		right_mult -> right = derivative_recurse(current->right); 

		//Glue them together.
		new_root -> left = left_mult; 
		new_root -> right = right_mult; 

		return new_root; 
	}

	if ( (current -> nclass == MULT_OP) && (current -> symbol == DIV_CHAR) ) { // d/dx ( u(x) / v(x) = (u'(x)*v(x) - u(x)*v'(x)) / [v(x)]^2
		//Root of new function is a division operation
		node_ptr new_root = new_node(); 
		new_root -> nclass = MULT_OP; 
		new_root -> symbol = DIV_CHAR; 

		//Build the numerator
		node_ptr numerator = new_node(); 
		numerator -> nclass = PLUS_OP; 
		numerator -> symbol = MINUS_CHAR; 		

		node_ptr left_numerator = new_node(); 
		left_numerator -> nclass = MULT_OP; 
		left_numerator -> symbol = MULT_CHAR;

		left_numerator -> left = derivative_recurse(clone_tree(current -> left));
		left_numerator -> right = clone_tree(current -> right); 	 

		node_ptr right_numerator = new_node(); 
		right_numerator -> nclass = MULT_OP; 
		right_numerator -> symbol = MULT_CHAR; 

		right_numerator -> left = clone_tree(current -> left); 
		right_numerator -> right = derivative_recurse(clone_tree(current -> right)); 

		numerator -> left = left_numerator; 
		numerator -> right = right_numerator; 

		//Build the denominator
		node_ptr denom = new_node(); 
		denom -> nclass = EXP_OP; 
		denom -> symbol = EXP_CHAR; 
		denom -> left = clone_tree(current -> right); 
		
		node_ptr power_two = new_node(); 
		power_two -> nclass = NUMBER; 
		power_two -> number = 2; 
		power_two -> symbol = '2'; 

		denom -> right = power_two; 
	
		//Add numerator, denominator to division op
		new_root -> left = numerator; 
		new_root -> right = denom; 

		return new_root; 
	} 

	if (current -> nclass == LOG_OP) { // d/dx(log(f(x))) = f'(x) / f(x)

		assert(current -> right == NULL); //Log is a unary operator. 
	
		node_ptr new_root = new_node_v2(MULT_OP, DIV_CHAR); 
		new_root -> left = derivative_recurse(clone_tree(current -> left)); 
		new_root -> right = current -> left; 
		
		return new_root; 
	}

	if (current -> nclass == EXP_OP) { //d/dx (f^g)  = f^g * ( (f'/f) * g + log(f) * g' )     Just factored the f^g here to simplify expression

		if (current -> right -> nclass == CONSTANT || current -> right -> nclass == NUMBER) {//Special case of power rule. f^c = (c*f^(c-1))*f'

			node_ptr inner_mult = new_node_v3(MULT_OP, MULT_CHAR, clone_node(current -> right), NULL );
			node_ptr inner_exp = new_node_v3(EXP_OP, EXP_CHAR, clone_tree(current->left), NULL );
			node_ptr inner_minus = new_node_v3(PLUS_OP, MINUS_CHAR, clone_node(current->right), new_number(1)); 

			inner_exp -> right = inner_minus; 
			inner_mult -> right = inner_exp;   			

			return new_node_v3(MULT_OP, MULT_CHAR, inner_mult, derivative_recurse(current->left)); 
		}

		//New root is a multiplication op
		node_ptr new_root = new_node_v2(MULT_OP, MULT_CHAR); 
		new_root -> left = clone_tree(current); 

		//Build right operand of mult op
		node_ptr right_mult = new_node_v2(PLUS_OP, PLUS_CHAR); 

		//Build left of inner plus 
		node_ptr left_plus = new_node_v2(MULT_OP, MULT_CHAR); 

		node_ptr left_plus_left = new_node_v2(MULT_OP, DIV_CHAR); 
		left_plus_left -> left = derivative_recurse(clone_tree(current -> left)); 
		left_plus_left -> right = clone_tree(current->left); 

		left_plus -> left = left_plus_left; 
		left_plus -> right = clone_tree(current -> right); 

		//Build right of inner plus
		node_ptr right_plus = new_node_v2(MULT_OP, MULT_CHAR); 
		right_plus -> left = new_node_v3(LOG_OP, LOG_CHAR, current-> left, NULL); //No need to clone current -> left the last time. Avoid memory leaks. 
		right_plus -> right = derivative_recurse(current -> right); //Same with current -> right. May as well re-attach this branch once.  	

		//Glue together
		right_mult -> left = left_plus; 
		right_mult -> right = right_plus; 

		new_root -> right = right_mult; 
	
		return new_root; 	
	}

	return NULL;	
} 

void simplify_derivative(void) {
	simplified_deriv = clone_tree(derivative_tree); 
	simplified_deriv = simplify_recurse(simplified_deriv); 	
}

node_ptr simplify_recurse(node_ptr current) {

	//*****************************BASE CASES: current is NULL or current is a number, variable, or constant*******************
	if (current == NULL) {
		return NULL; 
	}

	if (current -> nclass == NUMBER || current -> nclass == VARIABLE || current -> nclass == CONSTANT) {
		return current; //Nothing to simplify
	}

	current -> left = simplify_recurse(current -> left); //simplify left, right, then attempt to simplify current node. 
	current -> right = simplify_recurse(current -> right); 

	//**********************************Simplify log of 1 = 0********************************************************************
	if (current -> nclass == LOG_OP) {
		assert(current -> right == NULL); //Assert log only has 1 argument

		//Check if argument is 1
		if ( (current -> left -> nclass == NUMBER) && (current -> left -> number == 1) ) {
			free_tree(current); 
			return new_number(0); 
		}

		return current; 
	}

	//********************************SIMPLIFY +,-,*,/,^ applied to 2 numbers*****************************************************
	if ( (current -> left -> nclass == NUMBER) && (current -> right -> nclass == NUMBER) ) { //case for simplifying binary op on two literal numbers
		int num_1 = current->left -> number; 
		int num_2 = current->right -> number; 
		int result; 

		switch(current -> symbol) {
			case ('*') : 
				result = num_1*num_2; 
				break; 
			case ('/') : 
				assert(num_2 != 0); //Assert we aren't dividing by 0
				result = num_1 / num_2; 
				break; 
			case ('+') : 
				result = num_1 + num_2; 
				break; 
			case ('-') : 
				result = num_1 - num_2; 
				break; 
			case ('^') : 
				if (num_1 == 0) { //Assert we don't have 0^0 or division by 0
					assert(num_2 > 0); 
				}

				result = (int) pow( (double) num_1, (double) num_2); 
				break; 
		}

		free_tree(current); 

		return new_number(result); //Nothing else to simplify if we reduced current to a number
	}

	assert(current -> left != NULL && current -> right != NULL); //Must have non-null children for binary op

	//**********************************Simplifications involving multiplication**************************************************
	if (current -> nclass == MULT_OP && current -> symbol == MULT_CHAR) { 

		if ( (current -> left -> nclass == NUMBER) && (current -> left -> number == 1) ) { //Multiply by 1
			node_ptr new_root = clone_tree(current -> right);
			free_tree(current); 
			return new_root; 
		}

		if ( (current -> right -> nclass == NUMBER) && (current -> right -> number == 1) ) { //Multiply by 1
			node_ptr new_root = clone_tree(current -> left); 
			free_tree(current); 
			return new_root; 
		}

		if ( (current -> left -> nclass == NUMBER && current -> left -> number == 0) 
			|| (current -> right -> nclass == NUMBER && current -> right -> number == 0) ) { //Multiply by 0
			free_tree(current); 
			return new_number(0); //Multiply by 0 always results in zero
		}
	}

	if (current -> nclass == PLUS_OP && current -> symbol == PLUS_CHAR) { //Simplifications involving +
		if (current -> left -> nclass == NUMBER && current -> left -> number == 0) { // 0 + u(x) = u(x) for any function u
			node_ptr new_root = clone_tree(current -> right); 
			free_tree(current); 
			return new_root; 
		}

		if (current -> right -> nclass == NUMBER && current -> right -> number == 0) { // u(x) + 0 = u(x) for any function u
			node_ptr new_root = clone_tree(current -> left); 
			free_tree(current); 
			return new_root; 
		}
	}

	if (current -> nclass == EXP_OP) { //Simplifications involving ^

		if (current -> right -> nclass == NUMBER && current -> right -> number == 1) { // u(x)^1 = u(x)
			node_ptr new_root = clone_tree(current -> left); 
			free_tree(current); 
			return new_root; 
		}

		if (current -> right -> nclass == NUMBER && current -> right -> number == 0) { // u(x)^0 = 1 provided u(x) != 0. Already checked that case.
			free_tree(current); 
			return new_number(1); 
		}

		if (current -> left -> nclass == NUMBER && current -> left -> number == 0) { // 0^u(x) = 0 provided u(x) > 0. Already checked that case.
			free_tree(current); 
			return new_number(0); 
		}

		if (current -> left -> nclass == NUMBER && current -> left -> number == 1) { //1^u(x) = 1 for any possible well-defined u(x)
			free_tree(current); 
			return new_number(1); 
		}
	}

	return current; 

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
	return (c == EXP_CHAR); 
}
