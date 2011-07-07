#include "../include/arithmetic.h"


const int DIVIDE_BY_ZERO = -1; 
const int GOOD = 0; 
int PREVIOUS_ERROR = 0; 

int add(int x, int y) {
	if (y == 0) { //x+0 = x
		return x; 
	}

	int tmp; 

	if (y > 0) {
		tmp = add(x, --y); // x + y = ++(x + --y)
		return ++tmp; 
	}
	else {	
		tmp = add(x, ++y); // symmetric case for y < 0
		return --tmp; 
	}
}

int subtract(int x, int y) {

	return add(x, -y); 

}

int mult(int x, int y) {
	
	if (y == 0) { //x * 0 = 0
		return 0; 
	}

	if (y > 0) { // x * y = x + x * (y-1)
		return add(x, mult(x, y-1)); 
	}

	else { //x * (-|y|) = - (x * |y|), reducing to positive case
		return -add(x, mult(x, (-y) - 1)); 
	}
}

int divide(int x, int y) {

	if (y == 0 ) {
		PREVIOUS_ERROR = DIVIDE_BY_ZERO; 
		return -1; 
	}
	else {
		PREVIOUS_ERROR = GOOD; 
	}

	if (x < 0 && y < 0) {
		return divide(-x, -y); 
	}	

	if (x < 0) {
		return -divide(-x, y); 
	}

	if (y < 0) {
		return -divide(x, -y); 
	}

	if (x < y) { // x / y == 0 for positive x, y iff x < y
		return 0; 
	}	

	return add(1, divide(subtract(x, y), y)); // x / y = 1 + (x - y) / y 
}

int modulo(int x, int y) { // x % y

	if ( y == 0) {
		PREVIOUS_ERROR = DIVIDE_BY_ZERO; 
		return -1; 
	}
	else {
		PREVIOUS_ERROR = GOOD; 
	}
	
	if (y < 0) {
		return modulo(x, -y); // x = y (mod m) IFF x = y (mod -m). Falls out directly from definition of mod 
	}

	if (x < 0) {
		return modulo(add(x, y), y); //Add y until we get an equivalence class in [0, y)
	}

	if (x < y) { //x in [0, y) so just return it
		return x; 
	}

	return modulo(subtract(x, y), y);  // x == x - y (mod y)

}

int expon(int base, int power) {
	
	
	
	return -1; 
}
