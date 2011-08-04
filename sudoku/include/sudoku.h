#ifndef _SUDOKU
#define _SUDOKU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "list.h"

#define SIZE 9

const char EMPTY; //'-' represents an empty position in sudoku field

typedef char** sudoku; //9x9 board of chars representing a sudoku field

//9 bools for each square of sudoku field, indicating whether it's possible to place a number on a square
typedef bool*** possible; 	 

sudoku new_sudoku(); //Allocate new 9x9 sudoku field

sudoku clone_sudoku(sudoku); //Allocate new 9x9 sudoku field with same contents as given sudoku

bool are_sudokus_equal(sudoku, sudoku); //Check if 2 sudokus have identical entries in each square

void free_sudoku(void*); //Function to free a sudoku object. Argument is void* to be compatible with my generic linked-list module 

possible new_possible(); //New possible with entries set to true, since by default a value is possible until proven otherwise

possible clone_possible(possible p); //Clone the 9x9x9 possible object

void free_possible(possible p); //Free memory for possible object

sudoku sudoku_from_file(FILE*); //get an initial configuration for game of life from a text file 

void print_sudoku(sudoku); //Print sudoku in pretty format

void print_sudoku_stats(sudoku); //Print statistics about a sudoku field

void print_possible(possible, sudoku); //Print which placements have been eliminated

void print_soln_list(list*); //Must be passed a list containing sudoku objects. Will print them all 

void print_soln_list_stats(list*); //Must be passed a list containing sudoku objects. Will print them all 

int num_empty(sudoku);  //Counts number of empty squares in a sudoku field

sudoku get_lvl0_soln(sudoku); //Gets the lvl0 solution that just eliminates possibilities based on simple rules

sudoku get_lvl0_soln_v2(sudoku, possible); //Gets the lvl0 solution and modifies the given possible object with the possible ways to place numbers

list* get_all_solns(sudoku); //Gets all solutions to an initial sudoku field. Returns an empty list if there are zero solutions. 

void all_solns_helper(sudoku, possible, list*); //Recursive helper function for algorithm to get all solutions

bool is_impossible(possible, sudoku); //Checks if there exists an empty square such that no number can possibly be placed on this square

bool set_possible(bool* array, sudoku s, int row, int col); //Helper function to check current quadrant / row / col to eliminate possible numbers

void set_all_possible(sudoku s, possible p); //Sets the possible placements for all empty squares of a sudoku board. Ended up not needing this function. 

char get_entry(bool* array); //Returns a char in '1', ..., '9' if there is exactly one possible placement. Otherwise, returns '-', the EMPTY char

bool is_square_invalid(sudoku s, int row, int col); //Returns true IFF we find more than 1 of any number in the square.

bool is_invalid(sudoku s); //Checks input sudoku to see if it's completely invalid, i.e. it already has 2 of the same number in a row, col, or quad

#endif 
