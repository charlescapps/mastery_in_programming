#include "../include/misc.h"

long long unsigned int fact(int n) {
		
	if (n <= 0) {
		return 1; 
	}

	long long int val = 1; 
	int i; 
	for (i = n; i > 1; i--) {
		val *= i; 
	}

	return val; 
}

//This function uses a simplification (n choose k) = n*(n-1)*...*(n-k+1)/k!
//This makes overflow less likely, so larger choose values can be computed
long long unsigned int choose(int n, int k) {

	if (k > n) { //invalid input, return -1 as error code
		return -1; 
	}

	int i; 
	unsigned long long int val = 1; 

	for (i = n; i> n-k; i--) {
		val *= i; 
	}

	return val / fact(k);

}  
