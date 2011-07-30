#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/sudoku.h"
#include "include/list.h"

const char* USAGE = "solve_sudoku <input_file> [--help | -?]\n"; 

//game is a typedef for char**, see game section (from game.h) 

int main(int argc, char** args) {

	if (argc != 2) {
		printf("Must provide a filename.\nUsage: %s", USAGE); 
		exit(1); 
	}

	if (strcmp(args[1], "--help") == 0 || strcmp(args[1], "-?") == 0) {
		printf("Usage: %s", USAGE); 
		exit(0); 
	}

	FILE* input_file = fopen(args[1], "r"); //Open input for read-only

	sudoku s = sudoku_from_file(input_file); 

	printf("Input sudoku:\n"); 
	print_sudoku(s); 

	int empty_cnt = num_empty(s); 
	printf("Total # of fields: %d\n", SIZE*SIZE); 
	printf("Fields filled: %d\n", SIZE*SIZE - empty_cnt); 
	printf("Fields empty: %d\n", empty_cnt); 

	sudoku soln = get_lvl0_soln(s); 

	printf("\nLevel 0 Solution:\n"); 
	print_sudoku(soln); 

	printf("\nAll solutions:\n"); 
	list* solns = get_all_solns(s); 
	print_soln_list(solns); 	

	return 0; 
}

