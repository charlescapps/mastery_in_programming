#include <stdio.h>
#include "include/board.h"
#include "include/eight_queens.h" 

int main() {


	int num_solns = -1; 
	long long int num_pos_searched = -1; 

	board_t* solns = get_solutions(&num_solns, &num_pos_searched); 	

	int i; 
	for (i = 0; i <= num_solns-3; i+=3) {
		printf("Soln. nos %d, %d, %d:\n", i+1, i+2, i+3); 
		print_boardsx3(solns[i], solns[i+1], solns[i+2] ); 
	}

	for ( ; i < num_solns; i++) {
		printf("Soln. no %d:\n", i+1); 
		print_board(solns[i]); 
	}	


	
	return 0; 
}
