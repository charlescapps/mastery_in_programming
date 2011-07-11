#ifndef _GAME
#define _GAME

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "macros.h"

const char ALIVE;
const char DEAD;
const char* INPUT_FILE_ALIVE; 
const char* INPUT_FILE_DEAD; 

typedef struct { //Board is just 2d array of chars. Could have used bools, arbitrarily decided to go with chars for more expressiveness. 
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

int neighbors_torus(game* g, int r, int c); //Helper function - count number of living neighbors

#endif
