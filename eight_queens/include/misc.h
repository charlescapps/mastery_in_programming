#ifndef _MISC
#define _MISC

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) ((x) > (y) ? x : y)

#define MIN(x, y) ((x) < (y) ? x : y)

long long unsigned int fact(int);

long long unsigned int choose(int, int);  

int* format_commas(unsigned long long int, int * num_chunks); 

char* print_commas(unsigned long long int); 

#endif 
