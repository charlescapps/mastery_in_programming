#include <stdio.h>
#include "include/arithmetic.h"

static const int MAX = 6; 

int main() {

	int i, j;
	int result;  
	for (i = -MAX; i < MAX; i++) {
		for (j = -MAX; j < MAX; j++) {
			printf("add(%2d, %2d) = %3d, ", i, j, add(i, j)); 
			printf("mult(%2d, %2d) = %3d, ", i, j, mult(i, j)); 
			result = divide(i, j); 
			PREVIOUS_ERROR == GOOD ? 			
				printf("divide(%2d, %2d) = %3d, ", i, j, result)
			:
				printf("%-22s", "Division by zero."); 
			
			result = expon(i, j); 

			PREVIOUS_ERROR == GOOD ? 
				printf("expon(%2d, %2d) = %4d, ", i, j, result)
			:
				printf("%-22s", "Division by zero."); 
			//if (PREVIOUS_ERROR == DIVIDE_BY_ZERO) printf("Division by zero."); 
			//printf("modulo(%2d, %2d) = %3d, ", i, j, modulo(i, j));
			//if (j!=0) printf("%2d %% %2d = %3d, ", i, j, i % j);
			printf("\n");  
		}
	}


	return 0; 

}
