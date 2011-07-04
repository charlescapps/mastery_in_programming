#ifndef _EIGHT_QUEENS
#define _EIGHT_QUEENS

#include "board.h"
#include "misc.h"
#include <math.h>
#include <stdbool.h>

void get_solutions(board_t* solns, int * num_solns, long long int * num_pos_searched);

bool attacked(board_t b, int r, int c); //Returns true IFF (r, c) is occupied or can be attacked by another queen

#endif
