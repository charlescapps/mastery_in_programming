#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/sudoku.h"
#include "include/list.h"

/*
Charles L. Capps
Homework 6, CS 510: Mastery in Programming
Program to find all solns for any sudoku field (or indicate if there are zero solutions). 
*/

const char* USAGE = "solve_sudoku <input_file> [--help | -?]\n"; 

//sudoku is a typedef for char**, see sudoku.h

int main(int argc, char** args) {

	//Check if first argument is -? or --help
	if (strcmp(args[1], "--help") == 0 || strcmp(args[1], "-?") == 0) {
		printf("Usage: %s", USAGE); 
		exit(EXIT_SUCCESS); 
	}

	if (argc != 2) {
		printf("Wrong number of arguments. Must provide file name.\nUsage: %s", USAGE); 
		exit(EXIT_FAILURE); 
	}

	FILE* input_file = fopen(args[1], "r"); //Open input for read-only

	if (input_file == NULL) { //Failure opening file
		fprintf(stderr, "Error: Failure opening file. Are you sure file '%s' exists?\n", args[1]); 
		exit(EXIT_FAILURE); 
	}

	sudoku s = sudoku_from_file(input_file); //Get sudoku input from file

	//************Check if input sudoku is invalid**********************
	if (is_invalid(s)) {
		fprintf(stderr, "Error: Input sudoku is invalid. A number appears twice in the same row, column, or quadrant.\n"); 
		exit(EXIT_FAILURE); 
	}
	
	//****************Print initial sudoku field************************
	printf("Initial, incomplete input field:\n"); 
	print_sudoku(s); 

	printf("Statistics initially:\n"); 
	print_sudoku_stats(s); 

	//***************Get lvl0 solution and print result*****************
	sudoku soln = get_lvl0_soln(s); 
	int empty_cnt = num_empty(soln); 

	if (empty_cnt <= 0) { //If lvl0 solved the field, print lvl0 solution and exit

		printf("\nSudoku level 0 sudoku board.\n"); 
		print_sudoku(soln); 

		printf("Statistics Sudoku level 0:\n"); 
		print_sudoku_stats(soln); 

		printf("\nField was solvable with level 0\n"); 
		return 0; 
	}

	//***If lvl0 didn't solve the field, get all solutions and print them***
	
	list* solns = get_all_solns(s); 

	if (list_size(solns) <= 0) {
		printf("\nZero solutions exist for given sudoku field.\nExiting...\n"); 
		return 0; 
	}

	printf("\nLvl 1 solutions:\n"); 
	print_soln_list_stats(solns); 	

	return 0; 
}

