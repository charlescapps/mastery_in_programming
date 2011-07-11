#include "game.h"

const char ALIVE = 'O'; 
const char DEAD = 'X';

game* new_game(int rows, int cols) {

	char** game_board = (char**)malloc(rows*sizeof(char*)); //Allocate each pointer to a row

	int i;
	for ( i = 0; i < rows; i++) {
		game_board[i] = (char*)malloc((cols+1)*sizeof(char)); //Allocate each row of chars
		memset(game_board[i], DEAD, (cols)*sizeof(char));
		game_board[i][cols] = '\0'; //end each row with null character 
	}

	game* tmp_game = (game*)malloc(sizeof(game));
	tmp_game->board = game_board;  
	tmp_game->rows = rows; 
	tmp_game->cols = cols; 

	return tmp_game; 
}

game* clone_game(game* g) {
	game* clone = new_game(g->rows, g->cols); 

	int i; 
	for (i = 0; i < g->rows; i++) {
		strcpy(clone->board[i], g->board[i]); 
	}	

	return clone; 
}

void free_game(game* g) {

	int i; 
	for (i =0; i < g->rows; i++) { //Free each row
		free(g->board[i]); 
	}

	free(g->board); //Free the board

	free(g); //Free the game
}

void print_game(game* g) {

	char top[(g->cols)+1]; //Top-sides
	memset(top, '-', (g->cols)*sizeof(char)); //Set to '-'
	top[g->cols] = '\0'; //End with null char
	printf("+%s+\n", top); //Print top

	int i;
	for (i = 0; i < g->rows; i++) { //Print each row
		printf("|%s|\n", g->board[i]); 
	}	

	printf("+%s+\n", top); //Print bottom
}

game* evolve(game* g) {
	
	game* next = clone_game(g); //Clone game for evolution

	int i, j; 
	for (i = 0; i < g->rows; i++) {
		for (j = 0; j < g->cols; j++) {
				
		}
	}
}
