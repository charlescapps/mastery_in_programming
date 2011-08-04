#include "../include/sudoku.h"

const char EMPTY = '-'; 
const char ONE = '1'; 

static const int BUFFER_SIZE = 128; 
static const char* TOP = "  0 1 2  3 4 5  6 7 8   \n"; //Top of sudoku board for printing
static const char* MID = "+------+------+------+  \n"; //Separator between rows for sudoku board

//sudoku s: Input incomplete sudoku field
sudoku get_lvl0_soln(sudoku s) { //Returns lvl0 solution given input sudoku field s

	sudoku soln = clone_sudoku(s); //Clone so that original sudoku isn't modified
	possible p = new_possible(); //Record possible ways to place numbers in empty squares
	bool entry_changed = false; //Indicates a change occurred in the set of possible placements
	bool changed = false; //Indicates something changed in one pass through the board

	int i, j; 

	do {
		changed = false; 

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				entry_changed = set_possible(p[i][j], soln, i, j); //Set the possible placements for this row / column
				changed = changed || entry_changed;  	          //Something changed this pass if ANY square changed

				if (entry_changed) { //If the set of possible values changed, there's a chance there's a unique possible entry
					soln[i][j] = get_entry(p[i][j]); //Set the only possible placement for this square, or EMPTY if there's more than one
				}				
			}
		}

	} while (changed && (num_empty(soln) > 0)); //While a change has been made and there are empty squares in the solution

	return soln;  
} 

//sudoku s: input, incomplete sudoku field to be solved
//possible p: record of which placements are possible in each square of sudoku 's', to be populated. 
sudoku get_lvl0_soln_v2(sudoku s, possible p) { //Returns the lvl0 solution and modifies the given possible object with the possible ways to place numbers

	sudoku soln = clone_sudoku(s);
	bool entry_changed = false; 
	bool changed = false; 

	int i, j; 

	do {
		changed = false; 

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				entry_changed = set_possible(p[i][j], soln, i, j);
				changed = changed || entry_changed;  	

				if (entry_changed) { //If the set of possible values changed, there's a chance there's a unique possible entry
					soln[i][j] = get_entry(p[i][j]); 
				}				
			}
		}

	} while (changed); //While a change has been made and there are empty slots in the solution

	return soln;  
}

//sudoku s: input, incomplete sudoku field to be solved
list* get_all_solns(sudoku s) { //Returns the list of all solutions for the given input sudoku field

	list* solns = new_list(&free_sudoku); //Create an empty list of sudokus

	possible p = new_possible(); //Create a new record of what placements are possible

	all_solns_helper(s, p, solns); //Call the recursive helper to populate solution list

	return solns; 
} 

//sudoku s: current sudoku field we are searching for solutions
//possible p: record of which placements are possible in each square of sudoku field s
//list* 'solns': list to be populated with solutions to sudoku puzzle
void all_solns_helper(sudoku s, possible p, list* solns) { //Main algorithm for getting solutions. Recursive function to sequentially place numbers on empty squares. 

	sudoku closure = get_lvl0_soln_v2(s, p); //Get closure under lvl0 strategy to reduce search space

	if (is_impossible(p, closure)) { //If it's impossible, we made an invalid placement, so return  
		free_sudoku(closure); 
		return; 
	}	

	if (num_empty(closure) <= 0) { //If it's not impossible and has no empty squares, we found a soln
		add_to_list(solns, closure); 
		return; 
	}

	int i, j, k; 
	int min_empty_i = -1, min_empty_j = -1; //Row and col of first empty square
	possible p_clone; //Clone possible object so we don't overwrite the current one

	//Find the first i,j that is empty
	for (i = 0; i < SIZE; i++) {
		if (min_empty_i >= 0 && min_empty_j >=0) {
			break; 
		}
		for (j = 0; j < SIZE; j++) {
			if (closure[i][j] != EMPTY) {
				continue; 
			}
			else {
				min_empty_i = i; 
				min_empty_j = j;
				break;  
			}
		}
	}

	//Try placing 1, 2, ..., 9 in first empty square. If placed successfully, recursively call this function. 
	for (k = 0; k < SIZE; k++) {
		if (!(p[min_empty_i][min_empty_j][k])) { //Skip blatantly invalid placements, with 2 numbers in same row, col, or quadrant
			continue; 
		}
		closure[min_empty_i][min_empty_j] = ONE + k; //Place number on board at first empty position
		p_clone = clone_possible(p); 
		all_solns_helper(closure, p_clone, solns); //Recursive call after successful placement
		free_possible(p_clone); 
	}

	free_sudoku(closure); //We searched all possible placements starting with input sudoku, so free it and return
}

//possible p: valid record of which placements are possible for sudoku field s
//sudoku s: corresponding sudoku field 
//Assumption: (p, s) is a valid pair of possible placements 'p' for sudoku field 's'
bool is_impossible(possible p, sudoku s) { //Returns true IFF there exists an empty square with no possible placements
	bool any_true = false; 
	int i, j, k; 

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (s[i][j] != EMPTY) {
				continue; 
			}
			any_true = false; 
			for (k = 0; k < SIZE; k++) { //Check if any numbers can be places in square (i,j)
				any_true = any_true || p[i][j][k]; 
			}	
			if (!any_true) { //If nothing can be placed in this square, the sudoku board is impossible to solve
				return true; 
			}
		}
	}	
	return false; 
} 

void set_all_possible(sudoku s, possible p) { //Not needed in final algorithm. Sets the possible placements from scratch. 

	int i, j, k; 

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			memset(p[i][j], true, sizeof(bool)*SIZE); //Default is true
			for (k = 0; k < SIZE; k++) {
				set_possible(p[i][j], s, i, j); //Set false entries based on this board
			} 
		}
	}

}

//bool* array: array of bools recording what placements are possible. To be populated with false wherever a number placement is impossible. 
//sudoku s: sudoku field we are checking
//int row: Row of square we are examining
//int col: Col of square we are examining
bool set_possible(bool* array, sudoku s, int row, int col) {//Returns true if a change was made, false otherwise
	bool changed = false; 

	if (s[row][col] != EMPTY) { //If it's already filled with a number, do nothing
		return changed; 
	}

	int i, j; 
	char ch; 
	//Check current row
	for (j = 0; j < SIZE; j++) {
		ch = s[row][j]; 
		if (ch != EMPTY) {
			changed = array[ch - ONE] || changed; 
			array[ch - ONE] = false; //Number not possible if found on same row
		}
	}	

	//Check current col
	for (i = 0; i < SIZE; i++) {
		ch = s[i][col]; 
		if (ch != EMPTY) {
			changed = array[ch - ONE] || changed; 
			array[ch - ONE] = false; //"" if on same col
		}
	}

	//Check current quadrant
	int quad_row = (row / 3)*3; 
	int quad_col = (col / 3)*3; 	

	for (i = quad_row; i < quad_row + 3; i++) {
		for (j = quad_col; j < quad_col + 3; j++) {
			ch = s[i][j]; 
			if (ch != EMPTY) {
				changed = array[ch - ONE] || changed; 
				array[ch - ONE] = false; 
			}
		}
	}

	return changed; 
}

//bool* array: record of which placements are possible for a fixed square
char get_entry(bool* array) { //Returns a char in '1', ..., '9' if there is exactly one possibility. Otherwise, returns '-', the EMPTY char

	char entry = '-'; 

	int i; 
	for (i = 0; i < SIZE; i++) {//Find first true value
		if (array[i] == true) {
			entry = ONE + i;
			i++;  
			break; 
		}
	}		

	for (; i < SIZE; i++) { //If there's another true value after the first one, just return '-'
		if (array[i] == true) {
			entry = '-'; 
			break; 
		}
	}

	return entry; 
}

possible new_possible() { //New possible with entries set to true, since by default a value is possible until proven otherwise

	possible p = (possible)malloc(sizeof(bool**)*SIZE); //9 pointers to rows

	int i, j, k; 
	for (i = 0; i < SIZE; i++) {
		p[i] = (bool**)malloc(sizeof(bool*)*SIZE); //9 arrays of bools for each entry
		for (j = 0; j < SIZE; j++) {
			p[i][j] = malloc(sizeof(bool)*SIZE); //9 bools in each array
			for (k = 0; k < SIZE; k++) {
				p[i][j][k] = true; 
			} 
		}
	}

	return p; 
}

bool are_sudokus_equal(sudoku s1, sudoku s2) {//Returns true IFF s1 and s1 have the same entries in every square
	int i, j; 

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (s1[i][j] != s2[i][j]) {
				return false; 
			}
		}
	}
	return true; 

}

//possible p: input possible to be cloned
possible clone_possible(possible p) { //Allocates a new possible object and fills it with values from input 'p'
	possible clone = new_possible(); 

	int i, j, k ;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < SIZE; k++) {
				clone[i][j][k] = p[i][j][k]; 
			}
		}
	}

	return clone; 

}

//possible p: input possible to be freed
void free_possible(possible p) {//Frees memory for possible object p

	int i, j; 
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			free(p[i][j]);
		}
		free(p[i]); 
	}
}

sudoku new_sudoku() { //Allocates a new sudoku field, every square filled with EMPTY
	sudoku s = (sudoku)malloc(sizeof(char*)*SIZE); //Allocate row pointers 

	int i;
	for (i = 0; i < SIZE; i++) {
		s[i] = (char*)malloc(sizeof(char)*(SIZE + 1)); 
		memset(s[i], EMPTY, sizeof(char)*SIZE); 
		s[i][SIZE] = '\0'; 
	}

	return s; 
}

//sudoku s: input sudoku field
sudoku clone_sudoku(sudoku s) { //Returns clone of sudoku 's' with completely separate memory on heap. 
	sudoku clone = new_sudoku(); 

	int i, j; 
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			clone[i][j] = s[i][j]; 
		}
	}

	return clone; 
} 

void free_sudoku(void* obj) { //Function to free a sudoku object. Argument is void* to be compatible with my generic linked-list module 
	sudoku s = (sudoku)obj; 
	int i; 
	for (i = 0; i < SIZE; i++) {
		free(s[i]); 
	}
}

void print_sudoku(sudoku s) { //Prints sudoku 's' in pretty format

	printf("%s", TOP);

	int i; 
	for (i = 0; i < SIZE; i++) {
			if (i % 3 == 0 ) { //Print dividers
				printf("%s", MID); 
			}

			//Print row with values
			printf("| %c %c %c| %c %c %c| %c %c %c| %d\n", s[i][0], s[i][1], s[i][2], s[i][3], s[i][4], s[i][5], s[i][6], s[i][7], s[i][8], i); 
	}
	 
	printf("%s", MID); //Print bottom 
}

void print_possible(possible p, sudoku s){ //Print which placements have been eliminated
	int i, j, k; 

	for (i = 0; i < SIZE; i++) {
		printf("Row %d:", i); 
		for (j = 0; j < SIZE; j++) {
			if (s[i][j] == EMPTY) {
				printf(" Col %d:", j); 
				for (k = 0 ; k < SIZE; k++) {
					if (p[i][j][k] == false) {
						printf(" %c", ONE + k); 
					}
				}
			}
		}
		printf("\n"); 
	}

}

void print_soln_list(list* solns) { //Must be passed a list containing sudoku objects. Will print them all 

	node* tmp = solns->head; 
	int i = 0; 

	while (tmp != NULL) {
		printf("\nSoln # %d:\n", ++i); 
		print_sudoku((sudoku)(tmp->data)); 	
		tmp = tmp->next; 
	}

}

void print_soln_list_stats(list* solns) { //Must be passed a list containing sudoku objects. Will print them all 

	node* tmp = solns->head; 
	int i = 0; 

	while (tmp != NULL) {
		printf("\nSoln # %d:\n", ++i); 
		print_sudoku((sudoku)(tmp->data)); 	
		printf("Statistics for lvl 1 soln #%d:\n", i); 
		print_sudoku_stats((sudoku)(tmp->data)); 
		tmp = tmp->next; 
	}
}

void print_sudoku_stats(sudoku s) { //Prints total # of fields, # of fields filled, and # of fields empty
	int empty_cnt = num_empty(s); 
	printf("Total # of fields: %d\n", SIZE*SIZE); 
	printf("Fields filled: %6d\n", SIZE*SIZE - empty_cnt); 
	printf("Fields empty: %7d\n", empty_cnt); 
}

sudoku sudoku_from_file(FILE* infile) { //Reads a sudoku in from a file
	char buffer[BUFFER_SIZE]; // need to check if row is larger than expected so allocate larger buffer
	sudoku s = new_sudoku(); 

	int i, len; 
	for (i = 0; i < SIZE; i++) {
		if (NULL == fgets(buffer, BUFFER_SIZE, infile)) {
			printf("Reached end-of-file before reading in %d rows.\n", SIZE); 
			return NULL; //file didn't have proper number of rows. Return NULL	
		}

		len = strlen(buffer); 

		if (buffer[len - 1] == '\n') { //fgets puts the endline in buffer, must remove
			buffer[len - 1] = '\0';
		}

		if (strlen(buffer) != SIZE) {
			printf("%s", "Number of columns in file does not match the size of a sudoku game!\n"); 
			return NULL; 
		}

		strcpy(s[i], buffer); //copy buffer to game array
	}

	return s; 
}

int num_empty(sudoku s) { //Returns number of empty squares in sudoku field 's'
	int i, j, cnt = 0; 
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (s[i][j] == EMPTY) {
				cnt++; 
			}
		}
	}	
	return cnt; 
}

bool is_invalid(sudoku s) { //Checks input sudoku to see if it's completely invalid, i.e. already has 2 of the same number in a row, col, or quad
	int i, j; 

	for (i = 0; i < SIZE; i++) { //Init to zero
		for (j = 0; j < SIZE; j++) {
			if (is_square_invalid(s, i, j)) {
				return true; 
			}
		}
	}

	return false; 
}


bool is_square_invalid(sudoku s, int row, int col) { //Returns false if we find > 1 of any number in the square. Otherwise, returns true. 

	int num_found[SIZE]; //Count how many of each number we find in same row, col, quad. 

	char ch; 
	int i, j; 

	memset(num_found, 0, sizeof(int)*SIZE); //Set to zero initially

	//Check current row
	for (j = 0; j < SIZE; j++) {
		ch = s[row][j]; 
		if (ch != EMPTY) {
			num_found[ch - ONE]++; 
			if (num_found[ch - ONE] > 1) {
				return true; 
			} 
		}
	}	

	memset(num_found, 0, sizeof(int)*SIZE); //Set to zero initially

	//Check current col
	for (i = 0; i < SIZE; i++) {
		ch = s[i][col]; 
		if (ch != EMPTY) {
			num_found[ch - ONE]++; 
			if (num_found[ch - ONE] > 1) {
				return true; 
			}
		}
	}

	memset(num_found, 0, sizeof(int)*SIZE); //Set to zero initially

	//Check current quadrant
	int quad_row = (row / 3)*3; 
	int quad_col = (col / 3)*3; 	

	for (i = quad_row; i < quad_row + 3; i++) {
		for (j = quad_col; j < quad_col + 3; j++) {
			ch = s[i][j]; 
			if (ch != EMPTY) {
				num_found[ch - ONE]++; 
				if (num_found[ch - ONE] > 1) {
					return true; 
				}
			}
		}
	}

	return false; 

}
