#include <stdio.h>
#include "include/arithmetic.h"

static const int MAX = 6; 

int main() {

	int i, j; 
	for (i = -MAX; i < MAX; i++) {
		for (j = -MAX; j < MAX; j++) {
			printf("add(%2d, %2d) = %3d, ", i, j, add(i, j)); 
			printf("mult(%2d, %2d) = %3d, ", i, j, mult(i, j)); 
			printf("divide(%2d, %2d) = %3d, ", i, j, divide(i, j));
			//if (PREVIOUS_ERROR == DIVIDE_BY_ZERO) printf("Division by zero."); 
			printf("\n");  
		}
	}


	return 0; 

}
