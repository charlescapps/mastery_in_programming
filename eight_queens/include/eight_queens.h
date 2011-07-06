#ifndef _EIGHT_QUEENS
#define _EIGHT_QUEENS

#include "board.h"
#include "misc.h"
#include <math.h>
#include <stdbool.h>

const int NUM_POS; //will be set to 64 
const int MAX_SLNS; //will be set to 128, arbitrary upper bound on number of solutions


/*
	Allocates an array of board_t 's of size MAX_SLNS to store solutions in. 
Could implement a dynamic array module in C but haven't bothered :-) 
Assumes num_solns and num_queens_placed are already allocated on stack, just modifies the values. 

	Function works by considering the 8 queens as ordered. We may as well assume q1 < q2 < ... < q8, 
i.e. if i < j then qi is on a lower row, or the same row and a lower col, than qj. If we didn't prune 
branches, this would walk through the (64 choose 8) possibilities since the order of the queens doesn't matter
in this construction. (In other words, we don't search both position  q1 = (r1, c1), q2 = (r2, c2) and the equivalent
position q1 = (r2, c2), q2 = (r1, c1) ).

	It attempts to place successive queens by simply seeing if the square in question is attacked by any 
previously placed queen. If it's attacked, continue the loop and try a new square. If it's not attacked, 
attempt to place the next queen, etc. 

	When eight queens are successfully placed, we have found a solution, so store it in the board_t* solns array 
by cloning it with clone_board(board_t). 
*/

board_t* get_solutions(int * num_solns, long long int * num_queens_placed);

//Want to implement a more dynamic version of this code, but may not have time. 
board_t* get_solutions_mk2(int * num_solns, long long int * num_iterations);

bool attacked(board_t b, position p); //Returns true IFF (r, c) is occupied or can be attacked by another queen

void init_table(); //Inits table converting n in [0, 64) to a board position (r, c) 

void print_pos(position p); //Print position to stdout

#endif
