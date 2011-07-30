#ifndef _SUDOKU
#define _SUDOKU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "list.h"

#define SIZE 9

const char* NUMBERS; 
const char EMPTY;

typedef char** sudoku; //Dynamically allocate 9x9 board of chars so it can be returned from functions

//9 bools for each entry, whether that number is possible
typedef bool*** possible; 	 

sudoku new_sudoku(); 

sudoku clone_sudoku(sudoku); 

bool are_sudokus_equal(sudoku, sudoku); 

void free_sudoku(void*); //Function to free a sudoku object. Argument is void* to be compatible with my generic linked-list module 

possible new_possible(); //New possible with entries set to true, since by default a value is possible until proven otherwise

possible clone_possible(possible p);

void free_possible(possible p); 

sudoku sudoku_from_file(FILE*); //get an initial configuration for game of life from a text file 

void print_sudoku(sudoku); 

void print_soln_list(list*); //Must be passed a list containing sudoku objects. Will print them all 

int num_empty(sudoku); 

sudoku get_lvl0_soln(sudoku); //Gets the lvl0 solution that just eliminates possibilities based on simple rules

sudoku get_lvl0_soln_v2(sudoku, possible); //Gets the lvl0 solution and modifies the given possible object with the possible ways to place numbers

list* get_all_solns(sudoku); 

void all_solns_helper(sudoku, possible, list*); 

bool is_impossible(possible, sudoku); 

bool set_possible(bool* array, sudoku s, int row, int col); //Helper function to check current quadrant / row / col to eliminate possible numbers

void set_all_possible(sudoku s, possible p); 

char get_entry(bool* array); //Returns a char in '1', ..., '9' if there is one possibility. Otherwise, returns '-', the EMPTY char

#endif 
