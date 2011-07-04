#ifndef _BOARD
#define _BOARD

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef bool** board_t; //Board is 2d array of bools, queen present or not present

board_t new_board();  //Allocate board

void print_board(board_t board); 

board_t clone_board(board_t board); 

#endif
