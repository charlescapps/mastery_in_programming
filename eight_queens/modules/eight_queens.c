#include "../include/eight_queens.h"

extern const int B_SIZE; //8

//Prototpye for main workhorse function
//Dynamically allocates board_t* solns since we don't apriori know how many solns there are
//Assumes num_solns and num_pos_searched are already allocated on stack
void get_solutions(board_t* solns, int * num_solns, long long int * num_pos_searched){

}

bool attacked(board_t b, int r, int c) {

	int i, j; 

	const int UB = B_SIZE - 1;  //convenience and technically save computation

	//Check horizontally
	i = r;
 
	for (j = 0; j < B_SIZE; j++) {
		if (b[i][j]) return true; 		
	}

	//Check vertically
	j = c; 

	for (i = 0; i < B_SIZE; i++) {
		if (b[i][j]) return true; 
	}

	//Check diagonal 1
	//These are just the bounds for the line (r, c) + x*(1, 1)
	int x; 
	int x_lb = -MIN(r, c); 
	int x_ub = MIN(UB - r,  - c); 

	for (x = x_lb ; x <= x_ub; x++) {
		if (b[r + x][c + x]) return true; 
	}

	//These are bounds for line (r, c) + x*(-1, 1)
	x_lb = MAX(r - UB, -c); 
	x_ub = MIN(r, UB - c); 

	for (x = x_lb; x <= x_ub; x++) {
		if (b[r-x][c+x]) return true; 
	}

	//Exhausted possibilities, return false
	return false; 

}
