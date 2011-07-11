#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game.h"

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
