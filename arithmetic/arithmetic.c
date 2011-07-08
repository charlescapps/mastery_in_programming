#include "arithmetic.h"


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
	
	if (y < 0) { // x = z (mod y) IFF x = z (mod -y) from the def. of modulo. Hence may as well return mod of -y
		return modulo(x, -y);
	}
	
	if (x >= 0 && x < y) { //x in [0, y) so just return it
		return x; 
	}

	if (x < 0) {
		return modulo(add(x, y), y); //Add y until we get an equivalence class in [0, y)
	}


	return modulo(subtract(x, y), y);  // subtract y
}

int expon(int base, int power) {
	
	if (power < 0 && base == 0) {
		PREVIOUS_ERROR = DIVIDE_BY_ZERO; 
		return -1; 
	}
	else {
		PREVIOUS_ERROR = GOOD; 
	}

	if (base < 0) {
		if (modulo(power, 2) == 0) { //If power is even, negative sign goes away
			return expon(-base, power); 
		}
		else return -expon(-base, power); //Else we have to multiply by -1
	}

	if (base == 1) { //1^0 = 1^(any power) = 1
		return 1; 
	}
	
	if (power == 1) {
		return base; 
	}
	//Base is non-negative here	
	if (power == 0) { //In particular, defining 0^0 = 1, depends on how you take limit
		return 1; 
	}	

	if (power > 1) { //recursive case
		return mult(base, expon(base, --power)); 
	}

	return 0; //Covered all cases besides something > 1 to a negative power. For integers, this is 0	

}
