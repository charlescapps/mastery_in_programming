#include "../include/sudoku.h"

const char* NUMBERS = "123456789"; 
const char EMPTY = '-'; 
const char ONE = '1'; 

static const int BUFFER_SIZE = 128; 
static const char* TOP = "  0 1 2  3 4 5  6 7 8   \n";
static const char* MID = "+------+------+------+  \n";

sudoku get_lvl0_soln(sudoku s) {
	sudoku soln = clone_sudoku(s);
	possible p = new_possible(); 
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

	} while (changed && (num_empty(soln) > 0)); //While a change has been made and there are empty slots in the solution

	return soln;  
} 

sudoku get_lvl0_soln_v2(sudoku s, possible p) { //Gets the lvl0 solution and modifies the given possible object with the possible ways to place numbers

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

list* get_all_solns(sudoku s) {

	list* solns = new_list(&free_sudoku); //Create a new list that knows how to free its nodes. 

	possible p = new_possible(); 

	all_solns_helper(s, p, solns); 

	return solns; 

} 

void all_solns_helper(sudoku s, possible p, list* solns) {
	//print_sudoku(s); //Debugging purposes

	if (solns->head != NULL) { //For now, just return if we found any solution 
		return; 
	}

	sudoku closure = get_lvl0_soln_v2(s, p); //Get closure under lvl0 strategy to reduce search space

	//print_possible(p, closure); 

	if (is_impossible(p, closure)) { //If it's impossible, we made an invalid placement. 
		free_sudoku(closure); 
		return; 
	}	

	if (num_empty(closure) <= 0) { //If it's not impossible and the closure has no empty squares, we found a soln
		add_to_list(solns, closure); 
		return; 
	}

	int i, j, k; 
	int min_empty_i = -1, min_empty_j = -1; 
	possible p_clone; 

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

	for (k = 0; k < SIZE; k++) {
		if (!(p[min_empty_i][min_empty_j][k])) { //Skip blatantly invalid placements, with 2 numbers in same row, col, or quadrant
			continue; 
		}
		closure[min_empty_i][min_empty_j] = ONE + k; //Place (k+1) on board at pos (i,j) 
		p_clone = clone_possible(p); 
		all_solns_helper(closure, p_clone, solns); //Recursive call after attempting to place
		//closure[i][j] = EMPTY; 
		free_possible(p_clone); 
	}

	free_sudoku(closure); //We searched all possible placements starting with sudoku s, so free the lvl0 closure
}

bool is_impossible(possible p, sudoku s) {
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

void set_all_possible(sudoku s, possible p) {

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

char get_entry(bool* array) { //Returns a char in '1', ..., '9' if there is one possibility. Otherwise, returns '-', the EMPTY char

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

bool are_sudokus_equal(sudoku s1, sudoku s2) {
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

possible clone_possible(possible p) {
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

void free_possible(possible p) {

	int i, j; 
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			free(p[i][j]);
		}
		free(p[i]); 
	}
}

sudoku new_sudoku() {
	sudoku s = (sudoku)malloc(sizeof(char*)*SIZE); //Allocate row pointers 

	int i;
	for (i = 0; i < SIZE; i++) {
		s[i] = (char*)malloc(sizeof(char)*(SIZE + 1)); 
		memset(s[i], EMPTY, sizeof(char)*SIZE); 
		s[i][SIZE] = '\0'; 
	}

	return s; 
}

sudoku clone_sudoku(sudoku s) {
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

void print_sudoku(sudoku s) {

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
		printf("Soln # %d:\n", ++i); 
		print_sudoku((sudoku)(tmp->data)); 	
		tmp = tmp->next; 
	}

}

void print_soln_list_stats(list* solns) { //Must be passed a list containing sudoku objects. Will print them all 

	node* tmp = solns->head; 
	int i = 0; 

	while (tmp != NULL) {
		printf("Soln # %d:\n", ++i); 
		print_sudoku((sudoku)(tmp->data)); 	
		printf("Statistics for lvl 1 soln #%d:\n", i); 
		print_sudoku_stats((sudoku)(tmp->data)); 
		tmp = tmp->next; 
	}


}

void print_sudoku_stats(sudoku s) {
	int empty_cnt = num_empty(s); 
	printf("Total # of fields: %d\n", SIZE*SIZE); 
	printf("Fields filled: %6d\n", SIZE*SIZE - empty_cnt); 
	printf("Fields empty: %7d\n", empty_cnt); 
}

sudoku sudoku_from_file(FILE* infile) {
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

int num_empty(sudoku s) {
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
