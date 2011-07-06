#ifndef _BOARD
#define _BOARD

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool** board_t; //Board is 2d array of bools, queen present or not present

//Simple struct with row, column
typedef struct {
	unsigned char r; 
	unsigned char c; 
} position;

const int B_SIZE; //declare board size (8), it's defined in board.c

board_t new_board();  //Allocate a new board on the heap with no queens

void print_board(board_t board); //print board to stdout

void print_boardsx3(board_t b1, board_t b2, board_t b3); //print 3 boards to stdout side-by-side

board_t clone_board(board_t board); //Allocate new board on heap with same queen config as argument

void place_b(position p, board_t b); 

void remove_b(position p, board_t b); 

#endif
