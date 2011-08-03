#ifndef _INPUT_RLE
#define _INPUT_RLE

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

game* game_from_rle(FILE* rle_file); 

bool is_number(char c);

char* scan_number(char* str);

char* scan_whitespace(char* str);

#endif
