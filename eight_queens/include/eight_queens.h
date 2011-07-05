#ifndef _EIGHT_QUEENS
#define _EIGHT_QUEENS

#include "board.h"
#include "misc.h"
#include <math.h>
#include <stdbool.h>

const int NUM_POS;  
const int MAX_SLNS; 

typedef struct {
	unsigned char r; 
	unsigned char c; 
} position;

board_t* get_solutions(int * num_solns, long long int * num_queens_placed);

board_t* get_solutions_mk2(int num_queens, int * num_solns, long long int * num_pos_searched);

bool attacked(board_t b, position p); //Returns true IFF (r, c) is occupied or can be attacked by another queen

void init_table(); 

void print_pos(position p); 

#endif
