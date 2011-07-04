#include <stdio.h>
#include "include/board.h"
#include "include/eight_queens.h" 

extern const int B_SIZE; //Import constant from board.c

int main() {


	board_t * solns = NULL; 
	int num_solns = -1; 
	long long int num_pos_searched = -1; 

	get_solutions(solns, &num_solns, &num_pos_searched); 	

	board_t blank_b = new_board(); 

	printf("Extern int B_SIZE: %d\n", B_SIZE); 

	printf("Blank board:\n"); 
	print_board(blank_b); 

	printf("Clone:\n"); 
	print_board(clone_board(blank_b)); 
	

	return 0; 
}
