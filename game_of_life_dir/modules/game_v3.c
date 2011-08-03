#include "../include/game.h"

const char ALIVE = 'O'; 
const char DEAD = ' ';
const char* INPUT_FILE_ALIVE = "O"; 
const char* INPUT_FILE_DEAD = "X";

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

	int i, j, neighbor_cnt; 
	for (i = 0; i < g->rows; i++) {
		for (j = 0; j < g->cols; j++) {
			neighbor_cnt = neighbors(g, i, j); 			
			if (g->board[i][j] == ALIVE) { //ALIVE case
				if (neighbor_cnt == 2 || neighbor_cnt ==3) {
					; //Do nothing, stays alive
				}
				else {
					next->board[i][j] = DEAD; //Else it dies
				}
			}
			else { //DEAD case
				if (neighbor_cnt == 3) { //If it has 3 living neighbors, it comes back to life
					next->board[i][j] = ALIVE; 
				}
			}
		}
	}

	return next; 
}

game* evolve_torus(game* g) {
	
	game* next = clone_game(g); //Clone game for evolution

	int i, j, neighbor_cnt; 
	for (i = 0; i < g->rows; i++) {
		for (j = 0; j < g->cols; j++) {
			neighbor_cnt = neighbors_torus(g, i, j); 			
			if (g->board[i][j] == ALIVE) { //ALIVE case
				if (neighbor_cnt == 2 || neighbor_cnt ==3) {
					; //Do nothing, stays alive
				}
				else {
					next->board[i][j] = DEAD; //Else it dies
				}
			}
			else { //DEAD case
				if (neighbor_cnt == 3) { //If it has 3 living neighbors, it comes back to life
					next->board[i][j] = ALIVE; 
				}
			}
		}
	}

	return next; 
}

int neighbors(game* g, int r, int c) {
	if (r < 0 || r > (g->rows - 1) || c < 0 || c > (g->cols - 1)) {
		printf("Invalid row or col passed to neighbors function.\n"); 
		return -1; 
	}

	int cnt = 0; 

	char** b = g->board; 

	int i, j; 
	int r_lb = MAX(0, r-1), r_ub = MIN(g->rows - 1, r + 1); //Must have 0 <= r < rows 
	int c_lb = MAX(0, c-1), c_ub = MIN(g->cols - 1, c + 1); //Must have 0 <= c < cols
	for (i = r_lb; i <= r_ub; i++) {
		for (j = c_lb; j <= c_ub; j++) {
			if (b[i][j] == ALIVE && (i != r || j != c)) { //If a neighbor is alive and it's not the center point
				cnt++; 
			}
		}	
	}	
	return cnt; 
}

int neighbors_torus(game* g, int r, int c) {
//Comment out error-checking for now to improve performance
//This is the most performance critical function
/*
	if (r < 0 || r > (g->rows - 1) || c < 0 || c > (g->cols - 1)) {
		printf("Invalid row or col passed to neighbors functions.\n"); 
		return -1; 
	}
*/

	const int NUM_ROWS = g->rows; 
	const int NUM_COLS = g->cols; 

	int cnt = 0; 

	char** b = g->board; 

	int i, j, i_mod, j_mod; 
	for (i = r - 1; i <= r + 1; i++) {
		for (j = c - 1; j <= c + 1; j++) { //Calculate neighbors with modulo arithmetic to use torus topology
			if (i == r && j == c) {
				continue; //Do not count the center cell in calculation
			}

			if (i < 0) 
				i_mod = i + NUM_ROWS; //i wraps around left
			else if (i > NUM_ROWS - 1) 
				i_mod = i - NUM_ROWS; //i wraps around right
			else 
				i_mod = i; 

			if (j < 0) 
				j_mod = j + NUM_COLS; //j wraps around top
			else if (j > NUM_COLS - 1) 
				j_mod = j - NUM_COLS; //j wraps around right
			else
				j_mod = j; 

			if (b[i_mod][j_mod] == ALIVE) { //If a neighbor is alive and it's not the center point
				cnt++; 
			}
		}	
	}	
	return cnt; 

}
