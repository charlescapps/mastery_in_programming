#ifndef _SUDOKU
#define _SUDOKU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int SIZE; 
const char* NUMBERS; 
const char EMPTY;

typedef char** sudoku;

sudoku new_sudoku(); 

sudoku sudoku_from_file(FILE*); //get an initial configuration for game of life from a text file 

void print_sudoku(sudoku); 

int num_empty(sudoku); 

#endif 
