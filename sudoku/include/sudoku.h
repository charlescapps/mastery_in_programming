#ifndef _SUDOKU
#define _SUDOKU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE 9

const char* NUMBERS; 
const char EMPTY;

typedef char** sudoku; //Dynamically allocate 9x9 board of chars so it can be returned from functions

//9 bools for each entry, whether that number is possible
typedef bool*** possible; 	 

sudoku new_sudoku(); 

sudoku clone_sudoku(sudoku); 

possible new_possible(); //New possible with entries set to true, since by default a value is possible until proven otherwise

sudoku sudoku_from_file(FILE*); //get an initial configuration for game of life from a text file 

void print_sudoku(sudoku); 

int num_empty(sudoku); 

sudoku get_lvl0_soln(sudoku); //Gets the lvl0 solution that just eliminates possibilities based on simple rules

bool set_possible(bool* array, sudoku s, int row, int col); //Helper function to check current quadrant / row / col to eliminate possible numbers

char get_entry(bool* array); //Returns a char in '1', ..., '9' if there is one possibility. Otherwise, returns '-', the EMPTY char

#endif 
