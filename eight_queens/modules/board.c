#include "../include/board.h"

const int B_SIZE = 8;	//Board is 8x8 square
const char* TOP = "  + A B C D E F G H +"; 
const char* BOTTOM = "  +-----------------+"; 

board_t new_board() { //Allocate board
	board_t board = (bool**) malloc(B_SIZE*sizeof(bool*)); 

	int i, j; 

	for (i = 0; i < B_SIZE; i++) {
		board[i] = (bool*) malloc(B_SIZE*sizeof(bool)); 
		for (j = 0; j < B_SIZE; j++) {
			board[i][j] = false; 
		}
	}

	return board; 
}


void print_board(board_t board) {

	int i, j; 
	printf("%s\n", TOP); //Top row 

	for (i = 0; i < B_SIZE; i++) {
		printf("%d |", i + 1); //Row labels
		for (j = 0; j < B_SIZE; j++) {
			printf(" %c", board[i][j] ? 'Q': '.'); //'Q' or '.'
		}
		printf (" |\n"); //Right sides
	}

	printf("%s\n", BOTTOM); //Bottom-right corner 
}

void print_boardsx3(board_t b1, board_t b2, board_t b3) {
	int i, j; 
	printf("%s  %s  %s\n", TOP, TOP, TOP); //Top row 

	for (i = 0; i < B_SIZE; i++) {
		//BOARD 1
		printf("%d |", i + 1); //Row labels
		for (j = 0; j < B_SIZE; j++) {
			printf(" %c", b1[i][j] ? 'Q': '.'); //'Q' or '.'
		}
		printf (" |  "); //Right side and 2 spaces

		//BOARD 2
		printf("%d |", i + 1); //Row labels
		for (j = 0; j < B_SIZE; j++) {
			printf(" %c", b2[i][j] ? 'Q': '.'); //'Q' or '.'
		}
		printf (" |  "); //Right side
	
		//BOARD 3
		printf("%d |", i + 1); //Row labels
		for (j = 0; j < B_SIZE; j++) {
			printf(" %c", b3[i][j] ? 'Q': '.'); //'Q' or '.'
		}
		printf (" |\n"); //Right side

	}

	printf("%s  %s  %s\n", BOTTOM, BOTTOM, BOTTOM); //Bottom-right corner 

}

board_t clone_board(board_t board) {

	board_t clone = new_board(); 
	int i, j; 
	for (i = 0; i < B_SIZE; i++) {
		for (j= 0; j < B_SIZE; j++) {
			clone[i][j] = board[i][j]; 
		}
	}

	return clone; 
}

void place_b(position p, board_t b) {
	b[p.r][p.c] = true; 
} 

void remove_b(position p, board_t b) {
	b[p.r][p.c] = false; 
} 
