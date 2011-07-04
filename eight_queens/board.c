#include "include/board.h"

const int B_SIZE = 8;	//Board is 8x8 square

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
	printf("  +"); //Top-left corner  
	for (j = 0; j < B_SIZE; j++) {		
		printf(" %c", 'A' + j); //Column labels
	}
	printf(" +\n"); //Top-right corner

	for (i = 0; i < B_SIZE; i++) {
		printf("%d |", i + 1); //Row labels
		for (j = 0; j < B_SIZE; j++) {
			printf(" %c", board[i][j] ? 'Q': '.'); //'Q' or '.'
		}
		printf (" |\n"); //Right sides
	}

	printf("  +"); //Bottom-left corner
	for (j = 0; j < B_SIZE; j++) {
		printf("--"); //Bottom sides
	}
	printf(" +\n"); //Bottom-right corner 
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
