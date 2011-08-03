#include "../include/input_rle.h"

static const int MAX_LINE_SIZE = 1024; 
static const char RLE_ALIVE = 'o'; 
static const char RLE_DEAD = 'b'; 
static const char RLE_ENDROW = '$'; 
static const char RLE_ENDFILE = '!'; 

game* game_from_rle(FILE* rle_file) {
	char buffer[MAX_LINE_SIZE ]; // need to check if row is larger than expected so allocate larger buffer
	char* pos; 
	int x = -1, y = -1;
	int i; 
	int row = 0; 
	int col = 0; 
	int line = 0; 
	int num_repeat; 
	game* g = NULL;  

	while (NULL != fgets(buffer, MAX_LINE_SIZE, rle_file)) {

		++line; //Increment current line
		//printf("Inputting row: %d\n", row); 

		if (buffer[0]=='#') { //Comments, ignore the line
			continue; 
		}

		else if (buffer[0] == 'x') { //This is the special line declaring the size of the matrix
			sscanf(buffer, "x = %d, y = %d", &x, &y); 
			if (x < 0 || y < 0) {
				fprintf(stderr, "Error reading RLE file.\n"); 
				return NULL; 
			}

			printf("x=%d, y=%d\n", x, y); 
			
			g = new_game(y, x*2); //Extra space to the right 			
			continue; 
		}
		
		pos = buffer; 

		while ( (pos = scan_whitespace(pos)) && ('\0' != *pos) ) { //while we haven't hit the of the line, or gone outside bounds of 2D-array
			num_repeat = 1; //Number to repeat is 1 by default
 
			if (is_number(*pos)) {
				sscanf(pos, "%d", &num_repeat); //Get the number of times the next character repeats 
				//printf("num_repeat: %d\n", num_repeat); 
				pos = scan_number(pos); //Scan past the number
			}
			if (RLE_ENDROW == *pos) { //If we hit the end of row character, increment rows and go to next char
				for (i = 0; i < num_repeat; i++) { //Make a new row num_repeat times
					for ( ; col < x; col++) { //Implicitly the end of the row is all dead cells
						g->board[row][col] = DEAD; 
					} 
					col = 0; //Start at first column of the next row
					row++; 
				}
				pos++; 
				continue; 
			}
			if (RLE_ALIVE == *pos) {
				for (i = 0; i < num_repeat; i++) {
					g->board[row][col++] = ALIVE; 
				}
				pos++; 
			}	
			else if (RLE_DEAD == *pos) {
				for (i = 0; i < num_repeat; i++) {
					g->board[row][col++] = DEAD; 
				}
				pos++; 
			}
			else if (RLE_ENDFILE == *pos) {
				printf("RLE INPUT SUCCESSFULLY COMPLETED\n"); 
				return g; 
			}
			else {
				fprintf(stderr, "INVALID CHARACTER FOUND IN RLE FILE on line %d, col %d: %c\n", line, pos - buffer,  *pos); 
				return NULL; 
			}
			
		}
	}
	return g; 
}

bool is_number(char c) {
	if ('0' <= c && c <= '9') {
		return true; 
	}

	return false; 
}

char* scan_number(char* str) {
	while ('\0' != str && is_number(*str)) {
		str++; 
	}

	return str; 
}

char* scan_whitespace(char* str) {
	while (' ' == *str || '\n' == *str || '\t' == *str) {
		++str; 
	}
	return str; 
}
