#include <stdio.h>
#include "include/board.h"
#include "include/eight_queens.h" 

/*
	Charles L. Capps
	Homework 1 solution for CS510: Mastery in Programming

	See include/eight_queens.h, include/board.h for detailed comments on implementation

	TODO: write more dynamic solution that takes any number of queens
*/

int main() {


	int num_solns = -1; 
	long long int num_iterations = -1; 

	//Get array of board_t with all solutions, allocated on heap
	board_t* solns = get_solutions_mk2(&num_solns, &num_iterations); 	

	//Print solutions 3 per row
	int i; 
	for (i = 0; i <= num_solns-3; i+=3) {
		printf("Soln. nos %d, %d, %d:\n", i+1, i+2, i+3); 
		print_boardsx3(solns[i], solns[i+1], solns[i+2] ); 
	}

	for ( ; i < num_solns; i++) {
		printf("Soln. no %d:\n", i+1); 
		print_board(solns[i]); 
	}	

	//Output total number of ways to place 8 queens
	//Checked result with Wolfram Alpha to make sure no overflow occurred
	printf("Total no. of ways to place 8 queens on distinct squares\n\t=(64 choose 8) = %s\n\n", print_commas(choose(64, 8))); 

	//Number of queens placed. This is the only real measure I can think of for the possibilities my program searches
	//It doesn't ever place 8 queens unless we have arrived at a solution
	printf("Number of iterations= %s\n\n", print_commas(num_iterations));

	printf("Infer that 'backtracking' massively reduces search space!\n");  
	
	return 0; 
}
