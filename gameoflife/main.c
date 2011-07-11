#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

const char* USAGE = "game_of_life <num_rows> <num_cols> <input_file>  [--help | -?]\n" 
					"\tnum_rows : specify number of rows in game of life <= 1024.\n" 
					"\tnum_cols : specify number of cols in game of life <= 1024.\n"
					"\tinput_file : specify input file name. If file does not contain a rectangle of O's and X's with given rows/cols an error will occur.\n" 
					"\t--help or -? : show this usage and exit\n"; 

const int MAX_ROWS_COLS = 1024; //max allowed rows / cols

//game is a typedef for char** 
game* game_from_file(FILE* in, int num_rows, int num_cols); //get an initial configuration for game of life from a text file 

int main(int argc, char** args) {

	//If user gives wrong number of arguments or a help command is given, print USAGE and exit
	if (argc != 4 || strcmp(args[1], "-?") == 0 || strcmp(args[1], "--help") == 0 ) {
		printf("%s", USAGE); 
		exit(0); 
	}

	int rows = atoi(args[1]); //num rows is first arg
	int cols = atoi(args[2]); //num cols is second arg
	char* infile_str = args[3]; //file name is third arg

	if (rows < 1 || rows > MAX_ROWS_COLS || cols < 1 || cols > MAX_ROWS_COLS) {//If invalid number of rows / cols is given, exit
		printf("Invalid integer given for row or column.\n\n%s", USAGE); 
		exit(1); 
	}

	FILE* infile = fopen(infile_str, "r"); //Open read-only 
	
	game* my_game; 	

	if ( NULL == (my_game = game_from_file(infile, rows, cols)) ) { //Get starting configuration from a file
		printf("%s", "An error occurred while getting initial game from file. Exiting...\n"); 
		exit(1); 
	}

	print_game(my_game); 

	return 0; 
}

game* game_from_file(FILE* infile, int rows, int cols) {
	char buffer[MAX_ROWS_COLS + 1]; // need to check if row is larger than expected so allocate larger buffer
	game* g = new_game(rows, cols); 

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
	}


	return g; 
		
		
}
