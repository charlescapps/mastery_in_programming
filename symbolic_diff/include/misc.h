#ifndef _MISC
#define _MISC

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//To be agnostic about primitive type being used, implement MAX, MIN as macros
#define MAX(x, y) ((x) > (y) ? x : y)
#define MIN(x, y) ((x) < (y) ? x : y)

long long unsigned int fact(int); //Get the factorial, FIXME: figure out how to return error code when overflow occurs

long long unsigned int choose(int, int); //The choose function. Overflows pretty quickly, much like factorial. 

int* format_commas(unsigned long long int, int * num_chunks); //helper function for print_commas. Breaks a long long int into 3-digit chunks

char* print_commas(unsigned long long int); //turns an unsigned long long int into decimal representation string with commas

char* get_padding(int num); //Stupid helper function to get padding for 3-digit sequence sandwiched by commas
#endif 
