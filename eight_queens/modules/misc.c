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

int* format_commas(unsigned long long int num, int * num_chunks) {

	(*num_chunks) = log10(num) / 3 + 1; 

	int* chunks = (int*) malloc(sizeof(int)*(*num_chunks)); 

	int i; 
	for (i = 0; i < *num_chunks; i++) {
		chunks[(*num_chunks) - i - 1] = num % 1000;
		num /= 1000;  	
	}	

	return chunks; 

}

char* print_commas(unsigned long long int n) {
	int num_chunks; 
	int* chunks = format_commas(n, &num_chunks); 
	char* pretty = (char*) malloc(sizeof(char)*(5*num_chunks+1)); 
	pretty[0] = '\0'; 
	char buffer[100]; 

	int i; 
	for (i = 0; i < num_chunks - 1; i++) {
		sprintf(buffer, "%d,", chunks[i]); 
		strcat(pretty, buffer); 
	}	 
	sprintf(buffer, "%d", chunks[i]);

	strcat(pretty, buffer);  

	return pretty; 

}
