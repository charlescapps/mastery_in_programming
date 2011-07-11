/*
Game of life by Charles Capps
Homework 3 for CS510: Mastery in Programming

Usage of this program: 
game_of_life <num_rows> <num_cols> <input_file> <num_evolutions> [<pause_time_ms>] [--help | -?]
	
	num_rows : specify number of rows in game of life <= 1024.
	num_cols : specify number of cols in game of life <= 1024.
	input_file : specify input file name. If file does not contain a rectangle of O's and X's with given rows/cols an error will occur.
	num_evolutions : specify number of iterations to perform in game of life <= 1024.
	pause_time_ms : specify time in milliseconds to pause between each evolution for your viewing pleasure
	--help or -? : show this usage and exit
*/


#ifndef _MACROS
#define _MACROS

#define MAX(a, b) ( (a) > (b) ? (a) : (b) )
#define MIN(a, b) ( (a) < (b) ? (a) : (b) )

#endif
#ifndef _GAME
#define _GAME

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char ALIVE; //Constant representing an Alive cell
const char DEAD; //Constant for a dead cell
const char* INPUT_FILE_ALIVE; //The constant used in the input file for an alive cell
const char* INPUT_FILE_DEAD; //Same for dead cell. 

typedef struct { //Board is just 2d array of chars. Also has number of rows, cols. 
	int rows; 
	int cols; 
	char** board; 
} game; 


game* new_game(int rows, int cols); //Allocate new game

game* clone_game(game* g); //Allocate space for new game of same size. Copy over 2d array. 

void print_game(game* g); //Print game to stdout

void free_game(game* g); //Frees memory dynamically allocated for this game. Do not refer to game after calling this function.

game* evolve(game* g); //Evolves game of life by one step and stores in a new game object. Client must free old games with free_game if desired.

game* evolve_torus(game* g); //Same as evolve, but game wraps around vertically and horizontally

int neighbors(game* g, int r, int c); //Helper function - count number of living neighbors

int neighbors_torus(game* g, int r, int c); //Helper function - count number of living neighbors with wrapping around like a torus

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char* USAGE = "game_of_life <num_rows> <num_cols> <input_file> <num_evolutions> [<pause_time_ms>] [--help | -?]\n" 
					"\tnum_rows : specify number of rows in game of life <= 1024.\n" 
					"\tnum_cols : specify number of cols in game of life <= 1024.\n"
					"\tinput_file : specify input file name. If file does not contain a rectangle of O's and X's with given rows/cols an error will occur.\n" 
					"\tnum_evolutions : specify number of iterations to perform in game of life <= 1024.\n"
					"\tpause_time_ms : specify time in milliseconds to pause between each evolution for your viewing pleasure\n"
					"\t--help or -? : show this usage and exit\n"; 

const int MAX_ROWS_COLS = 1024; //max allowed rows / cols
const int MAX_EVOLUTIONS = 1024; //max allowed iterations

//game is a typedef for char**, see game section (from game.h) 
game* game_from_file(FILE* in, int num_rows, int num_cols); //get an initial configuration for game of life from a text file 

int main(int argc, char** args) {

	//If user gives wrong number of arguments or a help command is given, print USAGE and exit
	if ((argc != 5 && argc != 6) || strcmp(args[1], "-?") == 0 || strcmp(args[1], "--help") == 0 ) {
		printf("%s", USAGE); 
		exit(0); 
	}

	int rows = atoi(args[1]); //num rows is first arg
	int cols = atoi(args[2]); //num cols is second arg
	char* infile_str = args[3]; //file name is third arg
	int num_evolutions = atoi(args[4]); //number of evolutions is last arg	
	unsigned int pause_time = 0; //Default pause

	if (argc == 6 ) { //If the optional pause time argument is present
		pause_time = atoi(args[5])*1000; //Convert milliseconds to microseconds for usleep function
	}

	if (rows < 1 || rows > MAX_ROWS_COLS || cols < 1 || cols > MAX_ROWS_COLS) {//If invalid number of rows / cols is given, exit
		printf("Invalid integer given for row or column.\n\n%s", USAGE); 
		exit(1); 
	}
	if (num_evolutions < 0 || num_evolutions > MAX_EVOLUTIONS) {
		printf("Invalid number of evolutions given.\n\n%s", USAGE); 
		exit(1); 
	}

	FILE* infile = fopen(infile_str, "r"); //Open read-only 

	if (infile == NULL) {
		printf("Error opening file '%s'!\n", infile_str); 
		exit(1); 
	}
	
	game* my_game; 	

	if ( NULL == (my_game = game_from_file(infile, rows, cols)) ) { //Get starting configuration from a file
		printf("%s", "An error occurred while getting initial game from file. Exiting...\n"); 
		exit(1); 
	}

	printf("****************INITIAL GAME****************\n"); 
	print_game(my_game); 

	//Evolve num_evolutions times
	game* prev_game;
	int i;
	for (i = 0; i < num_evolutions; i++) {
		prev_game = my_game; //Store old game so it can be freed
		my_game = evolve_torus(my_game); //Evolve 1 step
		printf("****************EVOLUTION %d****************\n", i + 1); 
		print_game(my_game); //Print game
		free_game(prev_game); //Free previous game
		usleep(pause_time); 
	}

	return 0; 
}

game* game_from_file(FILE* infile, int rows, int cols) {
	char buffer[MAX_ROWS_COLS + 1]; // need to check if row is larger than expected so allocate larger buffer
	game* g = new_game(rows, cols); 
	char* tmp; 

	int i, len; 
	for (i = 0; i < rows; i++) {
		if (NULL == fgets(buffer, MAX_ROWS_COLS + 1, infile)) {
			printf("Reached end-of-file before reading in %d rows.\n", rows); 
			return NULL; //file didn't have proper number of rows. Return NULL	
		}

		len = strlen(buffer); 

		if (buffer[len - 1] == '\n') { //fgets puts the endline in buffer, must remove
			buffer[len - 1] = '\0';
		}

		if (strlen(buffer) != cols) {
			printf("%s", "Number of columns in file does not match given arg!\n"); 
			return NULL; 
		}

		strcpy(g->board[i], buffer); //copy buffer to game array

		while ( (tmp = strstr(g->board[i], INPUT_FILE_DEAD) ) ) {//Replace the X's in the input file with blanks
			*tmp = DEAD; 
		}
	}


	return g; 
		
		
}

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
		printf("Invalid row or col passed to neighbors functions.\n"); 
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

	if (r < 0 || r > (g->rows - 1) || c < 0 || c > (g->cols - 1)) {
		printf("Invalid row or col passed to neighbors functions.\n"); 
		return -1; 
	}

	int cnt = 0; 

	char** b = g->board; 

	int i, j, i_mod, j_mod; 
	for (i = r - 1; i <= r + 1; i++) {
		for (j = c - 1; j <= c + 1; j++) { //Calculate neighbors with modulo arithmetic to use torus topology
			if (i == r && j == c) {
				continue; //Do not count the center cell in calculation
			}
			i_mod = i; 	
			j_mod = j; 
			if (i_mod < 0) i_mod = g->rows + i_mod; //i wraps around left
			if (j_mod < 0) j_mod = g->cols + j_mod; //j wraps around top
			if (i_mod > g->rows - 1) i_mod -= g->rows; //i wraps around right
			if (j_mod > g->cols - 1) j_mod -= g->cols; //j wraps around right
			if (b[i_mod][j_mod] == ALIVE) { //If a neighbor is alive and it's not the center point
				cnt++; 
			}
		}	
	}	
	return cnt; 


}
