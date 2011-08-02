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

	sudoku s = sudoku_from_file(input_file); //Get sudoku input from file
	
	//****************Print initial sudoku field************************
	printf("Initial, incomplete input field:\n"); 
	print_sudoku(s); 

	int empty_cnt = num_empty(s); 
	printf("Statistics initially:\n"); 
	print_sudoku_stats(s); 

	//***************Get lvl0 solution and print result*****************
	sudoku soln = get_lvl0_soln(s); 
	empty_cnt = num_empty(soln); 

	if (empty_cnt <= 0) {

		printf("\nSudoku level 0 sudoku board.\n"); 
		print_sudoku(soln); 

		printf("Statistics Sudoku level 0:\n"); 
		print_sudoku_stats(soln); 

		printf("\nField was solvable with level 0\n"); 
		return 0; 
	}

	//***If lvl0 didn't solve the field, get all solutions and print them***
	printf("\nLvl 1 solutions:\n"); 
	list* solns = get_all_solns(s); 
	print_soln_list_stats(solns); 	

	return 0; 
}

