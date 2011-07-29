#include "../include/sudoku.h"

const int SIZE = 9; 
const char* NUMBERS = "123456789"; 
const char EMPTY = '-'; 

static const int BUFFER_SIZE = 128; 
static const char* TOP = "  0 1 2  3 4 5  6 7 8   \n";
static const char* MID = "+------+------+------+  \n";

sudoku new_sudoku() {
	sudoku s = (sudoku)malloc(sizeof(char*)*SIZE); //Allocate row pointers 

	int i;
	for (i = 0; i < SIZE; i++) {
		s[i] = (char*)malloc(sizeof(char)*(SIZE + 1)); 
		memset(s[i], EMPTY, sizeof(char)*SIZE); 
		s[i][SIZE] = '\0'; 
	}

	return s; 
}

void print_sudoku(sudoku s) {

	printf("%s", TOP);

	int i; 
	for (i = 0; i < SIZE; i++) {
			if (i % 3 == 0 ) { //Print dividers
				printf("%s", MID); 
			}

			//Print row with values
			printf("| %c %c %c| %c %c %c| %c %c %c| %d\n", s[i][0], s[i][1], s[i][2], s[i][3], s[i][4], s[i][5], s[i][6], s[i][7], s[i][8], i); 
	}
	 
	printf("%s", MID); //Print bottom 
}

sudoku sudoku_from_file(FILE* infile) {
	char buffer[BUFFER_SIZE]; // need to check if row is larger than expected so allocate larger buffer
	sudoku s = new_sudoku(); 

	int i, len; 
	for (i = 0; i < SIZE; i++) {
		if (NULL == fgets(buffer, BUFFER_SIZE, infile)) {
			printf("Reached end-of-file before reading in %d rows.\n", SIZE); 
			return NULL; //file didn't have proper number of rows. Return NULL	
		}

		len = strlen(buffer); 

		if (buffer[len - 1] == '\n') { //fgets puts the endline in buffer, must remove
			buffer[len - 1] = '\0';
		}

		if (strlen(buffer) != SIZE) {
			printf("%s", "Number of columns in file does not match the size of a sudoku game!\n"); 
			return NULL; 
		}

		strcpy(s[i], buffer); //copy buffer to game array
	}

	return s; 
}

int num_empty(sudoku s) {
	int i, j, cnt = 0; 
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (s[i][j] == EMPTY) {
				cnt++; 
			}
		}
	}	
	return cnt; 
}
