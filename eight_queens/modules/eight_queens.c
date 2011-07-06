#include "../include/eight_queens.h"

const int NUM_POS = 64; //stupid C won't let me write B_SIZE*B_SIZE
const int MAX_SLNS = 128; //Rather than bother making a dynamic array module in C...assume there are < 128 solns
position* int_to_pos;


void init_table() {
	int_to_pos = (position*)malloc(NUM_POS*sizeof(position));

	int i; 
	for (i = 0; i < NUM_POS; i++) {
		int_to_pos[i].r = i / 8; 
		int_to_pos[i].c = i % 8;
	}
}

void print_pos(position p) {
	printf("Row=%d, Col=%d\n", p.r, p.c); 
}

//Allocates an array of board_t 's of size MAX_SLNS to store solutions in. 
//Could implement a dynamic array module in C but haven't bothered :-) 
//Assumes num_solns and num_queens_placed are already allocated on stack, just modifies the value
//This is kind of a horrid solution with 8-level nested for-loops. See get_solutions_mk2 for a better solution
board_t* get_solutions(int * num_solns, long long int * num_queens_placed) {
	
	init_table(); 
	board_t b = new_board(); 
	board_t* solns = (board_t*)malloc(sizeof(board_t)*MAX_SLNS); 
	int soln_i = 0; 
	int tmp_num = 0; 
	position p1, p2, p3, p4, p5, p6, p7, p8;

	int i1, i2, i3, i4, i5, i6, i7, i8; 

	for (i1 = 0; i1 <= NUM_POS - 8; i1++) {
		p1 = int_to_pos[i1]; 
		b[p1.r][p1.c] = true; 
		tmp_num++;

		for (i2 = i1 + 1; i2 <= NUM_POS - 7; i2++) {
			p2 = int_to_pos[i2]; 
			if (attacked(b, p2)) {
				//print_board(b);
				continue;
			} 
			b[p2.r][p2.c] = true; 
			tmp_num++;

			for (i3 = i2 + 1; i3 <= NUM_POS - 6; i3++) {
				p3 = int_to_pos[i3]; 
				if (attacked(b, p3)) {
					continue; 
				}
				b[p3.r][p3.c] = true; 
				tmp_num++;

				for (i4 = i3 + 1; i4 <= NUM_POS - 5; i4++) {
					p4 = int_to_pos[i4]; 
					if (attacked(b, p4)) {
						continue; 
					}
					b[p4.r][p4.c] = true; 
					tmp_num++;

					for (i5 = i4 + 1; i5 <= NUM_POS - 4; i5++) {
						p5 = int_to_pos[i5]; 
						if (attacked(b, p5)) {
							continue; 
						}
						b[p5.r][p5.c] = true; 
						tmp_num++;
	
						for (i6 = i5 + 1; i6 <= NUM_POS - 3; i6++) {
							p6 = int_to_pos[i6]; 
							if (attacked(b, p6)) {
								continue; 	
							}
							b[p6.r][p6.c] = true; 
							tmp_num++;

							for (i7 = i6 + 1; i7 <= NUM_POS - 2; i7++) {
								p7 = int_to_pos[i7]; 
								if (attacked(b, p7)) {
									continue; 
								}
								b[p7.r][p7.c] = true; 
								tmp_num++;

								for (i8 = i7 + 1; i8 <= NUM_POS - 1; i8++) {
									p8 = int_to_pos[i8]; 
									if (attacked(b, p8)) {
										continue; 
									}	
									else {
										b[p8.r][p8.c] = true; 
										tmp_num++;
										solns[soln_i++] = clone_board(b); 						
										b[p8.r][p8.c] = false; 
									}
								}
								b[p7.r][p7.c] = false; //clear queen position when you get to the end of the iteration
							}
							b[p6.r][p6.c] = false; //clear queen position when you get to the end of the iteration
						}
						b[p5.r][p5.c] = false; //clear queen position when you get to the end of the iteration
					}
					b[p4.r][p4.c] = false; //clear queen position when you get to the end of the iteration
				}
				b[p3.r][p3.c] = false; //clear queen position when you get to the end of the iteration
			}
			b[p2.r][p2.c] = false; //clear queen position when you get to the end of the iteration
		}
		b[p1.r][p1.c] = false; //clear queen position when you get to the end of the iteration
	}
	*num_solns = soln_i; 
	*num_queens_placed = tmp_num; 

	return solns; 
}

board_t* get_solutions_mk2(int* num_solns, long long int* num_iterations) {


	int* q_pos = (int*)malloc(sizeof(int)*B_SIZE); //Allocate 8 integers representing the column of each queen, assuming queen i is in row i
	memset(q_pos, 0, sizeof(int)*B_SIZE); //Initialize queens to column 0
	board_t b = new_board(); 			//The temp board object used 
	board_t* solns = (board_t*)malloc(sizeof(board_t)*MAX_SLNS); //The collection of solutions

	//Other variables to be used in loop
	int q_index = 0, soln_i = 0; 
	position p; 
	int iterations = 0; 

	while (q_pos[0] < B_SIZE) {
		iterations++; 
		p.r = q_index; p.c = q_pos[q_index]; //Get the position of the currently considered queen

		while ( (p.c < B_SIZE) && attacked(b, p)) p.c++; //Find the first col s.t. this queen isn't attacked

		if (p.c < B_SIZE) { //If we are at a valid board position
			if (q_index == B_SIZE - 1) { //If we're placing the final queen, add board to solutions
				place_b(p, b); 
			//	print_board(b); 
				solns[soln_i++] = clone_board(b); 	
				remove_b(p, b); 
				q_pos[q_index] = p.c + 1; //Increment so we evaluate new positions, avoid infinite loop
				continue; 
			}
			//Else if q_index < B_SIZE - 1...my style is to not use else's when they are not necessary due to continue/return/etc.
			q_pos[q_index++] = p.c; //Store the position of this queen for later removal
			place_b(p, b); //If we're not placing the final queen, place on board and go to next queen
			q_pos[q_index] = 0; //When we first evaluate a queen for a given set of previous queens, we must start at 0 to 
								//ensure all combinations are considered
			continue;   
			
		}

		if (q_index <= 0) {
			break; //If we got to the end of the column for queen 0, this implies we have exhausted all combinations
		}
		
		//q_pos[q_index] = 0; //Reset index since we're failed with this branch
		p.r = --q_index; p.c = q_pos[q_index];  
		remove_b(p, b); //Remove previous queen from board
		q_pos[q_index]++; //Incr position of previous queen

	}

	(*num_iterations) = iterations; 
	(*num_solns) = soln_i; 
	return solns; 
	
}

bool attacked(board_t b, position p) {

	int i, j; 

	const int UB = B_SIZE - 1;  //convenience and technically save computation

	//Check horizontally to the left
	i = p.r;
 
	for (j = 0; j < p.c; j++) {
		if (b[i][j]) return true; 		
	}

	//Check vertically and above
	j = p.c; 

	for (i = 0; i < p.r; i++) {
		if (b[i][j]) return true; 
	}

	//These are just the bounds for the line (r, c) + x*(1, 1)
	//Note we only need to check for queens places on a previous row or same row previous col
	int x; 
	int x_lb = -MIN(p.r, p.c); 
	int x_ub = -1; 

	//Check first diagonal
	for (x = x_lb ; x <= x_ub; x++) {
		if (b[p.r + x][p.c + x]) return true; 
	}

	//These are bounds for line (r, c) + x*(-1, 1)
	x_lb = 1; 
	x_ub = MIN(p.r, UB - p.c); 

	//Check second diagonal
	for (x = x_lb; x <= x_ub; x++) {
		if (b[p.r-x][p.c+x]) return true; 
	}

	//Exhausted possibilities, return false
	return false; 

}
