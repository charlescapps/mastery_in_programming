#ifndef _BOARD
#define _BOARD

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool** board_t; //Board is 2d array of bools, queen present or not present

const int B_SIZE; //declare board size (8), it's defined in board.c

board_t new_board();  //Allocate board

void print_board(board_t board); 

void print_boardsx3(board_t b1, board_t b2, board_t b3); 

board_t clone_board(board_t board); 

#endif
