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

//Simply allocates an array of board_t 's of size MAX_SLNS
//Could implement a dynamic array module in C but haven't bothered :-) 
//Assumes num_solns and num_pos_searched are already allocated on stack, just modifies the value
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

board_t* get_solutions_mk2(int num_queens, int* num_solns, long long int* num_pos_searched) {

	return NULL; 
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
